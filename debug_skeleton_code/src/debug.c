#define _GNU_SOURCE
#include <stdio.h>
#include "debug.h"
#include <dlfcn.h>
#include <assert.h>

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
void
_debug_dump_registers(long const *regs)
{
    for (int i = 0; i < 16; ++i) {
        printf("%s\t%ld\t(0x%lx)\n", regnames[i], regs[i], regs[i]);
    }
}
/*
void _dump_backtrace(void) {
    void **rbp = __builtin_frame_address(0);
    int depth = 0;

    while (rbp && depth < 64) {
        void *return_addr = *(rbp + 1);
        assert(return_addr);
        if (!return_addr) break;

        Dl_info info;
        if (dladdr(return_addr, &info)) {
            printf("%3d: [%lx] %s () %s\n",
                depth,
                (unsigned long)return_addr,
                info.dli_sname ? info.dli_sname : "(null)",
                info.dli_fname ? info.dli_fname : "(null)");
        } else {
            printf("%3d: [%lx] (unknown) () (unknown)\n",
                depth, (unsigned long)return_addr);
        }

        rbp = (void **)(*rbp); // move to previous frame
        depth++;
    }
}
*/
void _dump_backtrace(void) {
    printf(">> Starting dump_backtrace\n");

    void **rbp = __builtin_frame_address(0);
    printf("Initial RBP: %p\n", rbp);

    int depth = 0;

    while (rbp && depth < 64) {
        printf("Frame %d:\n", depth);
        printf("  Current rbp: %p\n", rbp);

        void *return_addr = *(rbp + 1);
        printf("  Retrieved return address: %p\n", return_addr);

        // Optional: Comment out assert for production debug
        // assert(return_addr);  
        if (!return_addr) {
            printf("  Null return address — breaking.\n");
            break;
        }

        Dl_info info;
        if (dladdr(return_addr, &info)) {
            printf("  Symbol found: %s from %s\n",
                   info.dli_sname ? info.dli_sname : "(null)",
                   info.dli_fname ? info.dli_fname : "(null)");

            printf("%3d: [%lx] %s () %s\n",
                depth,
                (unsigned long)return_addr,
                info.dli_sname ? info.dli_sname : "(null)",
                info.dli_fname ? info.dli_fname : "(null)");
        } else {
            printf("  Symbol not found\n");
            printf("%3d: [%lx] (unknown) () (unknown)\n",
                   depth, (unsigned long)return_addr);
        }

        void **next_rbp = (void **)(*rbp);
        printf("  Next frame rbp: %p\n", next_rbp);

        rbp = next_rbp;
        depth++;
    }

    printf("<< Finished dump_backtrace\n");
}