.extern _debug_dump_registers
.globl dump_registers
.type dump_registers, @function
dump_registers:
/*Need to implement in this order: rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, r8–r15*/ 

subq $(16*8), %rsp
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
call _debug_dump_registers
addq $(16*8), %rsp
ret
