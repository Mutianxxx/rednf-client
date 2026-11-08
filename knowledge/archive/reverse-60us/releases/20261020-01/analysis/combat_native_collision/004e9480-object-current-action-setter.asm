004e9480 55                       push      ebp
004e9481 8bec                     mov       ebp, esp
004e9483 56                       push      esi
004e9484 8b7508                   mov       esi, dword ptr [ebp + 8]
004e9487 57                       push      edi
004e9488 56                       push      esi
004e9489 8bf9                     mov       edi, ecx
004e948b e8800afbff               call      0x499f10
004e9490 85f6                     test      esi, esi
004e9492 743d                     je        0x4e94d1
004e9494 81c6b0000000             add       esi, 0xb0
004e949a 8d4e1c                   lea       ecx, [esi + 0x1c]
004e949d e8be8bf1ff               call      0x402060
004e94a2 85c0                     test      eax, eax
004e94a4 7520                     jne       0x4e94c6
004e94a6 8bce                     mov       ecx, esi
004e94a8 e8039ff4ff               call      0x4333b0
004e94ad d81da4d7e900             fcomp     dword ptr [0xe9d7a4]
004e94b3 dfe0                     fnstsw    ax
004e94b5 f6c441                   test      ah, 0x41
004e94b8 740c                     je        0x4e94c6
004e94ba 8d4e08                   lea       ecx, [esi + 8]
004e94bd e89e8bf1ff               call      0x402060
004e94c2 85c0                     test      eax, eax
004e94c4 7e0b                     jle       0x4e94d1
004e94c6 8b07                     mov       eax, dword ptr [edi]
004e94c8 56                       push      esi
004e94c9 8bcf                     mov       ecx, edi
004e94cb ff9098010000             call      dword ptr [eax + 0x198]
004e94d1 5f                       pop       edi
004e94d2 5e                       pop       esi
004e94d3 5d                       pop       ebp
004e94d4 c20400                   ret       4
004e94d7 cc                       int3      
004e94d8 cc                       int3      
004e94d9 cc                       int3      
004e94da cc                       int3      
004e94db cc                       int3      
004e94dc cc                       int3      
004e94dd cc                       int3      
004e94de cc                       int3      
004e94df cc                       int3      
004e94e0 55                       push      ebp
004e94e1 8bec                     mov       ebp, esp
004e94e3 81ecc8010000             sub       esp, 0x1c8
004e94e9 56                       push      esi
004e94ea 8b7508                   mov       esi, dword ptr [ebp + 8]
004e94ed 85f6                     test      esi, esi
004e94ef 57                       push      edi
004e94f0 8bf9                     mov       edi, ecx
004e94f2 0f8421020000             je        0x4e9719
004e94f8 8b06                     mov       eax, dword ptr [esi]
004e94fa 8bce                     mov       ecx, esi
004e94fc ff909c010000             call      dword ptr [eax + 0x19c]
004e9502 85c0                     test      eax, eax
004e9504 0f840f020000             je        0x4e9719
004e950a 8b16                     mov       edx, dword ptr [esi]
004e950c 53                       push      ebx
004e950d 8bce                     mov       ecx, esi
004e950f ff929c010000             call      dword ptr [edx + 0x19c]
004e9515 8d8d38feffff             lea       ecx, [ebp - 0x1c8]
004e951b 8bd8                     mov       ebx, eax
004e951d e82ec5f6ff               call      0x455a50
004e9522 8a4318                   mov       al, byte ptr [ebx + 0x18]
004e9525 8d8b00010000             lea       ecx, [ebx + 0x100]
004e952b 88                       .byte     0x88
004e952c 85                       .byte     0x85
004e952d 3d                       .byte     0x3d
004e952e fe                       .byte     0xfe
004e952f ff                       .byte     0xff
