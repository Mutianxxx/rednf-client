00836f3f  8d55b8                   lea        edx, [ebp - 0x48]
00836f42  68284be100               push       0xe14b28
00836f47  52                       push       edx
00836f48  e883d8bcff               call       0x4047d0
00836f4d  83c408                   add        esp, 8
00836f50  84c0                     test       al, al
00836f52  7430                     je         0x836f84
00836f54  8d45d4                   lea        eax, [ebp - 0x2c]
00836f57  50                       push       eax
00836f58  e8b397ffff               call       0x830710
00836f5d  8b45ec                   mov        eax, dword ptr [ebp - 0x14]
00836f60  83c404                   add        esp, 4
00836f63  83f808                   cmp        eax, 8
00836f66  8b45d8                   mov        eax, dword ptr [ebp - 0x28]
00836f69  7303                     jae        0x836f6e
00836f6b  8d45d8                   lea        eax, [ebp - 0x28]
00836f6e  50                       push       eax
00836f6f  e8fc8cffff               call       0x82fc70
00836f74  83c404                   add        esp, 4
00836f77  50                       push       eax
00836f78  8bcf                     mov        ecx, edi
00836f7a  e8b168c3ff               call       0x46d830
00836f7f  e97e0e0000               jmp        0x837e02
