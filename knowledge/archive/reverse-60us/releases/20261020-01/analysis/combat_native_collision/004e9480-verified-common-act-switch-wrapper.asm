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
