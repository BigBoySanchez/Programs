   # caller prolog (calling __main)
   1400016d0:   55                      push   rbp
   1400016d1:   48 89 e5                mov    rbp,rsp
   1400016d4:   48 83 ec 50             sub    rsp,0x50
   1400016d8:   e8 ca 01 00 00          call   1400018a7 <__main>
   
   # store LIMIT and i on stack and check i <= LIMIT
   1400016dd:   c7 45 f8 45 00 00 00    mov    DWORD PTR [rbp-0x8],0x45
   1400016e4:   c7 45 fc 01 00 00 00    mov    DWORD PTR [rbp-0x4],0x1
   1400016eb:   e9 e5 00 00 00          jmp    1400017d5 <main+0x105>
   
   # char out[32] = ""
   1400016f0:   48 c7 45 d0 00 00 00    mov    QWORD PTR [rbp-0x30],0x0
   1400016f7:   00
   1400016f8:   48 c7 45 d8 00 00 00    mov    QWORD PTR [rbp-0x28],0x0
   1400016ff:   00
   140001700:   48 c7 45 e0 00 00 00    mov    QWORD PTR [rbp-0x20],0x0
   140001707:   00
   140001708:   48 c7 45 e8 00 00 00    mov    QWORD PTR [rbp-0x18],0x0
   14000170f:   00

   # i%3?
   140001710:   8b 4d fc                mov    ecx,DWORD PTR [rbp-0x4]  # ecx = i
   140001713:   48 63 c1                movsxd rax,ecx
   140001716:   48 69 c0 56 55 55 55    imul   rax,rax,0x55555556
   14000171d:   48 c1 e8 20             shr    rax,0x20
   140001721:   48 89 c2                mov    rdx,rax
   140001724:   89 c8                   mov    eax,ecx
   140001726:   c1 f8 1f                sar    eax,0x1f
   140001729:   29 c2                   sub    edx,eax
   14000172b:   89 d0                   mov    eax,edx
   14000172d:   01 c0                   add    eax,eax
   14000172f:   01 d0                   add    eax,edx
   140001731:   29 c1                   sub    ecx,eax
   140001733:   89 ca                   mov    edx,ecx
   
   # check i%5 if i%3 != 0
   140001735:   85 d2                   test   edx,edx
   140001737:   75 20                   jne    140001759 <main+0x89>
   
   # pass out into strlen (rcx) and call
   140001739:   48 8d 45 d0             lea    rax,[rbp-0x30]
   14000173d:   48 89 c1                mov    rcx,rax
   140001740:   e8 bb 1a 00 00          call   140003200 <strlen>

   # cat "Fizz\0" to out
   140001745:   48 89 c2                mov    rdx,rax                     # rdx = length of out  (return of strlen)
   140001748:   48 8d 45 d0             lea    rax,[rbp-0x30]              # rax = out
   14000174c:   48 01 d0                add    rax,rdx                     # rax = addr of NULL byte in out (out + length of out)
   14000174f:   c7 00 46 69 7a 7a       mov    DWORD PTR [rax],0x7a7a6946  # NULL BYTES (*rax) = "Fizz" (0x7a7a6946)
   140001755:   c6 40 04 00             mov    BYTE PTR [rax+0x4],0x0      # add \0 to end of out
   
   # i%5
   140001759:   8b 4d fc                mov    ecx,DWORD PTR [rbp-0x4]     # ecx = i
   14000175c:   48 63 c1                movsxd rax,ecx
   14000175f:   48 69 c0 67 66 66 66    imul   rax,rax,0x66666667
   140001766:   48 c1 e8 20             shr    rax,0x20
   14000176a:   89 c2                   mov    edx,eax
   14000176c:   d1 fa                   sar    edx,1
   14000176e:   89 c8                   mov    eax,ecx
   140001770:   c1 f8 1f                sar    eax,0x1f
   140001773:   29 c2                   sub    edx,eax
   140001775:   89 d0                   mov    eax,edx
   140001777:   c1 e0 02                shl    eax,0x2
   14000177a:   01 d0                   add    eax,edx
   14000177c:   29 c1                   sub    ecx,eax
   14000177e:   89 ca                   mov    edx,ecx
   
   # skip code if i%5 != 0
   140001780:   85 d2                   test   edx,edx
   140001782:   75 20                   jne    1400017a4 <main+0xd4>


   # call strlen(rcx = out)
   140001784:   48 8d 45 d0             lea    rax,[rbp-0x30]
   140001788:   48 89 c1                mov    rcx,rax
   14000178b:   e8 70 1a 00 00          call   140003200 <strlen>
   
   # cat "Buzz\0" to out
   140001790:   48 89 c2                mov    rdx,rax                     # 
   140001793:   48 8d 45 d0             lea    rax,[rbp-0x30]
   140001797:   48 01 d0                add    rax,rdx
   14000179a:   c7 00 42 75 7a 7a       mov    DWORD PTR [rax],0x7a7a7542
   1400017a0:   c6 40 04 00             mov    BYTE PTR [rax+0x4],0x0
   1400017a4:   48 8d 45 d0             lea    rax,[rbp-0x30]
   1400017a8:   0f b6 00                movzx  eax,BYTE PTR [rax]
   1400017ab:   84 c0                   test   al,al
   1400017ad:   75 16                   jne    1400017c5 <main+0xf5>
   1400017af:   8b 45 fc                mov    eax,DWORD PTR [rbp-0x4]
   1400017b2:   89 c2                   mov    edx,eax
   1400017b4:   48 8d 05 95 38 00 00    lea    rax,[rip+0x3895]        # 140005050 <.rdata>
   1400017be:   e8 0d 17 00 00          call   140002ed0 <printf>
   1400017c3:   eb 0c                   jmp    1400017d1 <main+0x101>
   1400017c5:   48 8d 45 d0             lea    rax,[rbp-0x30]
   1400017c9:   48 89 c1                mov    rcx,rax
   1400017cc:   e8 6f 1a 00 00          call   140003240 <puts>
   1400017d1:   83 45 fc 01             add    DWORD PTR [rbp-0x4],0x1
   
   1400017d5:   8b 45 fc                mov    eax,DWORD PTR [rbp-0x4]  # move i into eax
   1400017d8:   3b 45 f8                cmp    eax,DWORD PTR [rbp-0x8]  # compare i to LIMIT
   1400017db:   0f 8e 0f ff ff ff       jle    1400016f0 <main+0x20>    # loop if i <= LIMIT
   1400017e1:   b8 00 00 00 00          mov    eax,0x0
   1400017e6:   48 83 c4 50             add    rsp,0x50
   1400017ea:   5d                      pop    rbp
   1400017eb:   c3                      ret
   1400017ec:   90                      nop
   1400017ed:   90                      nop
   1400017ee:   90                      nop
   1400017ef:   90                      nop
