.intel_syntax

.section .data

.section .text
.global _start

        mov %eax, 1     # syscall code
        mov %ebx, 65    # exit code
        int 0x80