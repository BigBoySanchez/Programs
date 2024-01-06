        .intel_syntax noprefix
        .data
intPrin:
        .asciz  "%d\n"

        .text
        .globl  main
main:
        # caller prolog (calling __main)
        push    rbp
        mov     rbp, rsp
        add     rsp, -32        # WHY?  
        call    __main

        movq    [rbp], 1        # init i

while:
        # print contents of rax and a newline
        movq    rdx, [rbp]
        lea     rcx, intPrin[rip]
        call    printf

        # increment i and check again
        addq    [rbp], 1

        # loop while i <= 10
        cmpq    [rbp], 10
        jle     while
        nop
        
        # get ready to return from __main
        add     rsp, 32
        pop     rbp

        # exit code = 0 and exit program
        mov     rax, 0
        ret
