 ###############################################################################################
 #                                                                                             #
 # link: "https://github.com/simon-whitehead/assembly-fun/blob/master/windows-x64/README.md"   #
 # has all the answers to the comment on line 18                                               #
 #                                                                                             #
 ###############################################################################################      
        
        
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
        add     rsp, -40       # WHY? space for 4 parameters + ret addr? call doesn't move stack ptr? need space for first and last word?
        call    __main

        movq    -8[rbp], 1        # init i

while:
        # print contents of rax and a newline
        movq    rdx, -8[rbp]
        lea     rcx, intPrin[rip]
        call    printf

        # increment i and check again
        addq    -8[rbp], 1

        # loop while i <= 10
        cmpq    -8[rbp], 10
        jle     while
        
        # get ready to return from __main
        add     rsp, 40
        pop     rbp

        # exit code = 0 and exit program
        mov     rax, 0
        ret
