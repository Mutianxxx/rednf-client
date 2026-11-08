00498e60 55                       push      ebp
00498e61 8bec                     mov       ebp, esp
00498e63 56                       push      esi
00498e64 8bf1                     mov       esi, ecx
00498e66 8b86c4010000             mov       eax, dword ptr [esi + 0x1c4]
00498e6c 57                       push      edi
00498e6d 8b7d08                   mov       edi, dword ptr [ebp + 8]
00498e70 85f8                     test      eax, edi
00498e72 743f                     je        0x498eb3
00498e74 53                       push      ebx
00498e75 8b9e04010000             mov       ebx, dword ptr [esi + 0x104]
00498e7b 85db                     test      ebx, ebx
00498e7d 7415                     je        0x498e94
00498e7f 8bcb                     mov       ecx, ebx
00498e81 e80aae5800               call      0xa23c90
00498e86 8b838c000000             mov       eax, dword ptr [ebx + 0x8c]
00498e8c 50                       push      eax
00498e8d 8bcb                     mov       ecx, ebx
00498e8f e8acf45800               call      0xa28340
00498e94 8b96c0010000             mov       edx, dword ptr [esi + 0x1c0]
00498e9a 8b86c4010000             mov       eax, dword ptr [esi + 0x1c4]
00498ea0 0bd7                     or        edx, edi
00498ea2 f7d7                     not       edi
00498ea4 23c7                     and       eax, edi
00498ea6 8996c0010000             mov       dword ptr [esi + 0x1c0], edx
00498eac 8986c4010000             mov       dword ptr [esi + 0x1c4], eax
00498eb2 5b                       pop       ebx
00498eb3 5f                       pop       edi
00498eb4 5e                       pop       esi
00498eb5 5d                       pop       ebp
00498eb6 c20400                   ret       4
