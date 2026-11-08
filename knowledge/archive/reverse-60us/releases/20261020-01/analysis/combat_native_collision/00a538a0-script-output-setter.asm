00a538a0 55                       push      ebp
00a538a1 8bec                     mov       ebp, esp
00a538a3 57                       push      edi
00a538a4 8bf9                     mov       edi, ecx
00a538a6 8b07                     mov       eax, dword ptr [edi]
00a538a8 85c0                     test      eax, eax
00a538aa 742a                     je        0xa538d6
00a538ac ff4808                   dec       dword ptr [eax + 8]
00a538af 8b07                     mov       eax, dword ptr [edi]
00a538b1 8b4808                   mov       ecx, dword ptr [eax + 8]
00a538b4 85c9                     test      ecx, ecx
00a538b6 7518                     jne       0xa538d0
00a538b8 8b00                     mov       eax, dword ptr [eax]
00a538ba 50                       push      eax
00a538bb b968420d01               mov       ecx, 0x10d4268
00a538c0 e83bfbffff               call      0xa53400
00a538c5 8b0f                     mov       ecx, dword ptr [edi]
00a538c7 51                       push      ecx
00a538c8 e810c71a00               call      0xbfffdd
00a538cd 83c404                   add       esp, 4
00a538d0 c70700000000             mov       dword ptr [edi], 0
00a538d6 8b4508                   mov       eax, dword ptr [ebp + 8]
00a538d9 85c0                     test      eax, eax
00a538db 0f8491000000             je        0xa53972
00a538e1 56                       push      esi
00a538e2 50                       push      eax
00a538e3 e8e5c41a00               call      0xbffdcd
00a538e8 8bf0                     mov       esi, eax
00a538ea 83c404                   add       esp, 4
00a538ed 81fe00100000             cmp       esi, 0x1000
00a538f3 737c                     jae       0xa53971
00a538f5 85f6                     test      esi, esi
00a538f7 7508                     jne       0xa53901
00a538f9 5e                       pop       esi
00a538fa 8907                     mov       dword ptr [edi], eax
00a538fc 5f                       pop       edi
00a538fd 5d                       pop       ebp
00a538fe c2                       .byte     0xc2
00a538ff 04                       .byte     0x04
