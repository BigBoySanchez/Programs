        .intel_syntax noprefix

        .data
.LC0:
        .asciz "Hello, World!"

        .text
        .globl  main
main:
        push	rbp
        mov	rbp, rsp
        sub	rsp, 32
	call	__main

        lea     rcx, [.LC0+rip]
        call    printf

        mov     rax, 0
        add	rsp, 32
	pop	rbp
        ret
