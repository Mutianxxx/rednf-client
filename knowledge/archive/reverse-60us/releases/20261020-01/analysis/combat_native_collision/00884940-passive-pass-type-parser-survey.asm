00884940 680036e200               push      0xe23600
00884945 8d4df0                   lea       ecx, [ebp - 0x10]
00884948 e8a39eb8ff               call      0x40e7f0
0088494d 84c0                     test      al, al
0088494f 740c                     je        0x88495d
00884951 c7461802000000           mov       dword ptr [esi + 0x18], 2
00884958 e9bf0f0000               jmp       0x88591c
0088495d 68d435e200               push      0xe235d4
00884962 8d4df0                   lea       ecx, [ebp - 0x10]
00884965 e8869eb8ff               call      0x40e7f0
0088496a 84c0                     test      al, al
0088496c 740c                     je        0x88497a
0088496e c7461803000000           mov       dword ptr [esi + 0x18], 3
00884975 e9a20f0000               jmp       0x88591c
0088497a 68a835e200               push      0xe235a8
0088497f 8d4df0                   lea       ecx, [ebp - 0x10]
00884982 e8699eb8ff               call      0x40e7f0
00884987 84c0                     test      al, al
00884989 0f848d0f0000             je        0x88591c
0088498f c7461804000000           mov       dword ptr [esi + 0x18], 4
00884996 e9810f0000               jmp       0x88591c
0088499b 8d55c4                   lea       edx, [ebp - 0x3c]
0088499e 688435e200               push      0xe23584
008849a3 52                       push      edx
008849a4 e827feb7ff               call      0x4047d0
008849a9 83c408                   add       esp, 8
008849ac 84c0                     test      al, al
008849ae 7411                     je        0x8849c1
008849b0 57                       push      edi
008849b1 e81aaefaff               call      0x82f7d0
008849b6 83c404                   add       esp, 4
008849b9 89461c                   mov       dword ptr [esi + 0x1c], eax
008849bc e95b0f0000               jmp       0x88591c
008849c1 8d45c4                   lea       eax, [ebp - 0x3c]
008849c4 685835e200               push      0xe23558
008849c9 50                       push      eax
008849ca e801feb7ff               call      0x4047d0
008849cf 83c408                   add       esp, 8
008849d2 84c0                     test      al, al
008849d4 7411                     je        0x8849e7
008849d6 57                       push      edi
008849d7 e8f4adfaff               call      0x82f7d0
008849dc 83c404                   add       esp, 4
008849df 894620                   mov       dword ptr [esi + 0x20], eax
008849e2 e9350f0000               jmp       0x88591c
008849e7 8d4dc4                   lea       ecx, [ebp - 0x3c]
008849ea 684035e200               push      0xe23540
008849ef 51                       push      ecx
008849f0 e8dbfdb7ff               call      0x4047d0
008849f5 83c408                   add       esp, 8
008849f8 84c0                     test      al, al
008849fa 7474                     je        0x884a70
008849fc 8d5e24                   lea       ebx, [esi + 0x24]
008849ff 8bcb                     mov       ecx, ebx
00884a01 e84a03dcff               call      0x644d50
00884a06 8d55f0                   lea       edx, [ebp - 0x10]
00884a09 52                       push      edx
00884a0a e8d1bafaff               call      0x8304e0
00884a0f 83c404                   add       esp, 4
00884a12 84c0                     test      al, al
00884a14 0f84020f0000             je        0x88591c
00884a1a 8d9b00000000             lea       ebx, [ebx]
00884a20 33ff                     xor       edi, edi
00884a22 897dec                   mov       dword ptr [ebp - 0x14], edi
00884a25 8b04bdf025f700           mov       eax, dword ptr [edi*4 + 0xf725f0]
00884a2c 50                       push      eax
00884a2d 8d4df0                   lea       ecx, [ebp - 0x10]
00884a30 e8bbe61c00               call      0xa530f0
00884a35 50                       push      eax
00884a36 e8b0c33700               call      0xc00deb
00884a3b 83c408                   add       esp, 8
00884a3e 85c0                     test      eax, eax
00884a40 740b                     je        0x884a4d
00884a42 47                       inc       edi
00884a43 83ff29                   cmp       edi, 0x29
00884a46 7cdd                     jl        0x884a25
00884a48 897dec                   mov       dword ptr [ebp - 0x14], edi
00884a4b eb0e                     jmp       0x884a5b
00884a4d 8d45ec                   lea       eax, [ebp - 0x14]
00884a50 50                       push      eax
00884a51 8bcb                     mov       ecx, ebx
00884a53 897dec                   mov       dword ptr [ebp - 0x14], edi
00884a56 e8c526b8ff               call      0x407120
00884a5b 8d4df0                   lea       ecx, [ebp - 0x10]
00884a5e 51                       push      ecx
00884a5f e87cbafaff               call      0x8304e0
00884a64 83c404                   add       esp, 4
00884a67 84c0                     test      al, al
00884a69 75b5                     jne       0x884a20
00884a6b e9ac0e0000               jmp       0x88591c
00884a70 8d55c4                   lea       edx, [ebp - 0x3c]
00884a73 682035e200               push      0xe23520
00884a78 52                       push      edx
00884a79 e852fdb7ff               call      0x4047d0
00884a7e 83c408                   add       esp, 8
00884a81 84c0                     test      al, al
00884a83 7411                     je        0x884a96
00884a85 8d4634                   lea       eax, [esi + 0x34]
00884a88 50                       push      eax
00884a89 e852bafaff               call      0x8304e0
00884a8e 83c404                   add       esp, 4
00884a91 e9860e0000               jmp       0x88591c
00884a96 8d4dc4                   lea       ecx, [ebp - 0x3c]
00884a99 688ce8e100               push      0xe1e88c
00884a9e 51                       push      ecx
00884a9f e82cfdb7ff               call      0x4047d0
00884aa4 83c408                   add       esp, 8
00884aa7 84c0                     test      al, al
00884aa9 7445                     je        0x884af0
00884aab 8d7e38                   lea       edi, [esi + 0x38]
00884aae 8bcf                     mov       ecx, edi
00884ab0 e87bebb7ff               call      0x403630
00884ab5 8d55f0                   lea       edx, [ebp - 0x10]
00884ab8 52                       push      edx
00884ab9 e822bafaff               call      0x8304e0
00884abe 83                       .byte     0x83
00884abf c4                       .byte     0xc4
