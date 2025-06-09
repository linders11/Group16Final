.extern _debug_dump_registers
.globl dump_registers
.type dump_registers, @function
dump_registers:
/*Need to implement in this order: rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, r8–r15*/ 

subq $8, %rsp
movq %rsp, %rdi
/*push all register values to the stack to print the values. must be reverse
order due to the nature of stacks*/
pushq %r15
pushq %r14
pushq %r13
pushq %r12
pushq %r11
pushq %r10
pushq %r9
pushq %r8
pushq %rsp
pushq %rbp
pushq %rdi
pushq %rsi
pushq %rdx
pushq %rcx
pushq %rbx
pushq %rax
/* this label was to make sure it was pushing the register values properly */
/* rsp being in the middle also makes it a bit awkward to test it using info registers and x/16gx , but it has been off by the same multiple of 8 each time so I think it's right */
pre_call:
call _debug_dump_registers
/* 8 bytes to the stack pointer to account for the pushed registers
   and the 8 bytes i subtracted at the beginning */
addq $136, %rsp
/* that took forever to figure out */
ret
