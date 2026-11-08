00867cea  4d                       dec        ebp
00867ceb  ac                       lodsb      al, byte ptr [esi]
00867cec  6838e8e100               push       0xe1e838
00867cf1  51                       push       ecx
00867cf2  e8d9cab9ff               call       0x4047d0
00867cf7  83c408                   add        esp, 8
00867cfa  84c0                     test       al, al
00867cfc  7447                     je         0x867d45
00867cfe  8b55a4                   mov        edx, dword ptr [ebp - 0x5c]
00867d01  52                       push       edx
00867d02  8bcf                     mov        ecx, edi
00867d04  e867950000               call       0x871270
00867d09  8bf0                     mov        esi, eax
00867d0b  8a45f3                   mov        al, byte ptr [ebp - 0xd]
00867d0e  84c0                     test       al, al
00867d10  53                       push       ebx
00867d11  7419                     je         0x867d2c
00867d13  e8b87afcff               call       0x82f7d0
00867d18  53                       push       ebx
00867d19  894634                   mov        dword ptr [esi + 0x34], eax
00867d1c  e8af7afcff               call       0x82f7d0
00867d21  83c408                   add        esp, 8
00867d24  894638                   mov        dword ptr [esi + 0x38], eax
00867d27  e98c040000               jmp        0x8681b8
00867d2c  e89f7afcff               call       0x82f7d0
00867d31  53                       push       ebx
00867d32  894610                   mov        dword ptr [esi + 0x10], eax
00867d35  e8967afcff               call       0x82f7d0
00867d3a  83c408                   add        esp, 8
00867d3d  894614                   mov        dword ptr [esi + 0x14], eax
00867d40  e973040000               jmp        0x8681b8
