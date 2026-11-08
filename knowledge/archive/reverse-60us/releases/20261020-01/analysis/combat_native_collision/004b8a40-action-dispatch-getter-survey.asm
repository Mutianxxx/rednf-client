004b8a40 55                       push      ebp
004b8a41 8bec                     mov       ebp, esp
004b8a43 53                       push      ebx
004b8a44 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004b8a47 8b0b                     mov       ecx, dword ptr [ebx]
004b8a49 85c9                     test      ecx, ecx
004b8a4b 56                       push      esi
004b8a4c 57                       push      edi
004b8a4d 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
004b8a50 740c                     je        0x4b8a5e
004b8a52 8b07                     mov       eax, dword ptr [edi]
004b8a54 85c0                     test      eax, eax
004b8a56 7406                     je        0x4b8a5e
004b8a58 50                       push      eax
004b8a59 e862ed5600               call      0xa277c0
004b8a5e 8b4b04                   mov       ecx, dword ptr [ebx + 4]
004b8a61 85c9                     test      ecx, ecx
004b8a63 740d                     je        0x4b8a72
004b8a65 8b4704                   mov       eax, dword ptr [edi + 4]
004b8a68 85c0                     test      eax, eax
004b8a6a 7406                     je        0x4b8a72
004b8a6c 50                       push      eax
004b8a6d e84eed5600               call      0xa277c0
004b8a72 8b4b08                   mov       ecx, dword ptr [ebx + 8]
004b8a75 85c9                     test      ecx, ecx
004b8a77 740d                     je        0x4b8a86
004b8a79 8b4708                   mov       eax, dword ptr [edi + 8]
004b8a7c 85c0                     test      eax, eax
004b8a7e 7406                     je        0x4b8a86
004b8a80 50                       push      eax
004b8a81 e83aed5600               call      0xa277c0
004b8a86 8d730c                   lea       esi, [ebx + 0xc]
004b8a89 2bfb                     sub       edi, ebx
004b8a8b c7450802000000           mov       dword ptr [ebp + 8], 2
004b8a92 8b0e                     mov       ecx, dword ptr [esi]
004b8a94 85c9                     test      ecx, ecx
004b8a96 740d                     je        0x4b8aa5
004b8a98 8b0437                   mov       eax, dword ptr [edi + esi]
004b8a9b 85c0                     test      eax, eax
004b8a9d 7406                     je        0x4b8aa5
004b8a9f 50                       push      eax
004b8aa0 e81bed5600               call      0xa277c0
004b8aa5 8b4508                   mov       eax, dword ptr [ebp + 8]
004b8aa8 83c604                   add       esi, 4
004b8aab 48                       dec       eax
004b8aac 894508                   mov       dword ptr [ebp + 8], eax
004b8aaf 75e1                     jne       0x4b8a92
004b8ab1 8b4b14                   mov       ecx, dword ptr [ebx + 0x14]
004b8ab4 85c9                     test      ecx, ecx
004b8ab6 8b750c                   mov       esi, dword ptr [ebp + 0xc]
004b8ab9 740d                     je        0x4b8ac8
004b8abb 8b4614                   mov       eax, dword ptr [esi + 0x14]
004b8abe 85c0                     test      eax, eax
