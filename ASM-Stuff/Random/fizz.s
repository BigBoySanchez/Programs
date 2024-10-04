        .intel_syntax noprefix
        .data
num:
        .asciz  "%d"            # prints an int
fizz:
        .asciz  "Fizz"
buzz:
        .asciz  "Buzz"
lf:
        .asciz  "\n"            # linefeed; goes to newline
TO_ALLOC:
        .8byte  48              # minimum = 46 bytes
LIMIT:
        .8byte   69

        .text
        .globl  main
main:
        # caller prolog (calling __main)
        push    rbp
        mov     rbp, rsp
        sub     rsp, TO_ALLOC[rip]         # WHY? space for 4 parameters + ret addr? call doesn't move stack ptr? need space for at least 1 qword?
        call    __main

        movq     -8[rbp], 1              # init i to 1

check:
        # increment i and loop again if i <= LIMIT
        mov     rax, LIMIT[rip]
        cmp     -8[rbp], rax
        jle     case_1
        
        # get ready to return from __main
        add     rsp, TO_ALLOC[rip]
        pop     rbp

        # exit code = 0 and exit program
        mov     rax, 0
        ret

case_1:
        # rdx = i%3
        mov     rdx, 0                  # NOTE: top = rdx, bottom = rax
        mov     rax, -8[rbp]            # rax = i
        mov     rbx, 3
        div     rbx                     # i/3 (rdx = remainder)

        # go to next case if rdx != 0
        mov     -16[rbp], rdx
        cmp     rdx, 0
        jne     case_2

        # print fizz if rdx == 0
        lea     rcx, fizz[rip]
        call    printf

case_2:
        # rdx = i%5
        mov     rdx, 0                  # NOTE: top = rdx, bottom = rax
        mov     rax, -8[rbp]            # rax = i
        mov     rbx, 5
        div     rbx                     # i/5 (rdx = remainder)

        # skip print if rdx != 0
        cmp     rdx, 0
        jne     default

        # print buzz if rdx == 0
        lea     rcx, buzz[rip]
        call    printf

        jmp     inc

default:
        cmpq    -16[rbp], 0
        je     inc             # skip if fizz was printed
        
        # print i
        mov     rdx, -8[rbp]
        lea     rcx, num[rip]
        call    printf

inc:        
        # print newline
        lea     rcx, lf[rip]
        call    printf

        addq    -8[rbp], 1
        jmp     check           # increment and check if i <= LIMIT
