#define _GNU_SOURCE
#include <stdio.h>
#include "debug.h"
#include <dlfcn.h>
#include <assert.h>

/*thanks for this*/
char const *regnames[] = {
    "rax",
    "rbx",
    "rcx",
    "rdx",
    "rsi",
    "rdi",
    "rbp",
    "rsp",
    "r8",
    "r9",
    "r10",
    "r11",
    "r12",
    "r13",
    "r14",
    "r15",
};

/* Internal helper function */
void _debug_dump_registers(long const *regs)
{
    /* this exact code was graciously written in class in about 12 seconds, but looking up all these symbols helped me learn a lot about printf*/
    /*%s prints a string , but more specfically, it prints characters from a char* until a null byte is printed (thus printing a whole string)
      %ld prints a long int
      0x%lx = 0x is just the common prefix for hexadecimal numbers, and I will look up why after turning this in. %lx means long hex*/
    for (int i = 0; i < 16; ++i) {
        printf("%s\t%ld\t(0x%lx)\n", regnames[i], regs[i], regs[i]);
    }
}

/* this function walks back through the stack using dladdr to find the symbols and rbp values of the function used beforehand until rbp is null or depth grows to 64*/
void _dump_backtrace(void) {
    printf(">> Starting dump_backtrace\n");
    /* get stack frame, apparently the below call only works in GCC */
    void **rbp = __builtin_frame_address(0);
    printf("Initial RBP: %p\n", rbp);

    int depth = 0;
    //limit stack frames to 64 for safety to prevent a stack overflow . it is possible to have more than 64 stack frames, but this is a pretty normal limit
    while (rbp && depth < 64) {
        printf("Frame %d:\n", depth);
        printf("Current rbp: %p\n", rbp);

        void *return_addr = *(rbp + 1);
        printf("  Retrieved return address: %p\n", return_addr);

        /* make sure return address exists */
        if (!return_addr) {
            printf("  Null return address — breaking.\n");
            break;
        }
        /* use dladdr to get symbol information */
        Dl_info info;
        /* dladdr assertion */
        if (dladdr(return_addr, &info)) {
            printf("Symbol found: %s from %s\n",
                   info.dli_sname ? info.dli_sname : "(null)",
                   info.dli_fname ? info.dli_fname : "(null)");

            printf("%3d: [%lx] %s () %s\n",
                depth,
                (unsigned long)return_addr,
                info.dli_sname ? info.dli_sname : "(null)",
                info.dli_fname ? info.dli_fname : "(null)");
        } else {
            printf("Symbol not found\n");
            printf("%3d: [%lx] (unknown) () (unknown)\n",
                   depth, (unsigned long)return_addr);
        }
        /* print the next frame's rbp */
        void **next_rbp = (void **)(*rbp);
        printf("  Next frame rbp: %p\n", next_rbp);

        rbp = next_rbp;
        depth++;
    }

    printf("<< Finished dump_backtrace\n");
}


/*
Just gonna leave this here as a reminder of how clueless we were for a while
void _dump_backtrace(void) {
    printf("please print\n");
    return 0;
}
*/