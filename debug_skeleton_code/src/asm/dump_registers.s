.extern _debug_dump_registers
.globl dump_registers
.type dump_registers, @function
dump_registers:
/*Need to implement in this order: rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, r8–r15*/ 

subq $(16*8), %rsp
movq %rsp, %rdi
pushq %rax
pushq %rbx
pushq %rcx
pushq %rdx
pushq %rsi
pushq %rdi
pushq %rbp
pushq %rsp
pushq %r8
pushq %r9
pushq %r10
pushq %r11
pushq %r12
pushq %r13
pushq %r14
pushq %r15
call _debug_dump_registers
addq $(16*8), %rsp
ret
