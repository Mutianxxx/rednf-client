005f5b40 55                       push      ebp
005f5b41 8bec                     mov       ebp, esp
005f5b43 8b4518                   mov       eax, dword ptr [ebp + 0x18]
005f5b46 8b5510                   mov       edx, dword ptr [ebp + 0x10]
005f5b49 56                       push      esi
005f5b4a 50                       push      eax
005f5b4b 8b450c                   mov       eax, dword ptr [ebp + 0xc]
005f5b4e 8bf1                     mov       esi, ecx
005f5b50 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
005f5b53 51                       push      ecx
005f5b54 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005f5b57 52                       push      edx
005f5b58 50                       push      eax
005f5b59 51                       push      ecx
005f5b5a 8bce                     mov       ecx, esi
005f5b5c e87f75eaff               call      0x49d0e0
005f5b61 8b16                     mov       edx, dword ptr [esi]
005f5b63 8bce                     mov       ecx, esi
005f5b65 ff9234020000             call      dword ptr [edx + 0x234]
005f5b6b 85c0                     test      eax, eax
005f5b6d 7f36                     jg        0x5f5ba5
005f5b6f 8b867c080000             mov       eax, dword ptr [esi + 0x87c]
005f5b75 3b8684080000             cmp       eax, dword ptr [esi + 0x884]
005f5b7b 7d28                     jge       0x5f5ba5
005f5b7d 40                       inc       eax
005f5b7e 89867c080000             mov       dword ptr [esi + 0x87c], eax
005f5b84 8b06                     mov       eax, dword ptr [esi]
005f5b86 57                       push      edi
005f5b87 8bce                     mov       ecx, esi
005f5b89 ff9088030000             call      dword ptr [eax + 0x388]
005f5b8f 8b3e                     mov       edi, dword ptr [esi]
005f5b91 8bce                     mov       ecx, esi
005f5b93 ff9738020000             call      dword ptr [edi + 0x238]
005f5b99 50                       push      eax
005f5b9a 8bce                     mov       ecx, esi
005f5b9c ff975c030000             call      dword ptr [edi + 0x35c]
005f5ba2 5f                       pop       edi
005f5ba3 eb4b                     jmp       0x5f5bf0
005f5ba5 8b8e20010000             mov       ecx, dword ptr [esi + 0x120]
005f5bab 85c9                     test      ecx, ecx
005f5bad 7441                     je        0x5f5bf0
005f5baf 8b8624010000             mov       eax, dword ptr [esi + 0x124]
005f5bb5 2bc1                     sub       eax, ecx
005f5bb7 c1f802                   sar       eax, 2
005f5bba 83f801                   cmp       eax, 1
005f5bbd 7631                     jbe       0x5f5bf0
005f5bbf 8bc1                     mov       eax, ecx
005f5bc1 8b4804                   mov       ecx, dword ptr [eax + 4]
005f5bc4 85c9                     test      ecx, ecx
005f5bc6 7428                     je        0x5f5bf0
005f5bc8 c7863c09000001000000     mov       dword ptr [esi + 0x93c], 1
005f5bd2 8b4804                   mov       ecx, dword ptr [eax + 4]
005f5bd5 e886174300               call      0xa27360
005f5bda 8b8620010000             mov       eax, dword ptr [esi + 0x120]
005f5be0 8b16                     mov       edx, dword ptr [esi]
005f5be2 83c004                   add       eax, 4
005f5be5 8b00                     mov       eax, dword ptr [eax]
005f5be7 50                       push      eax
005f5be8 8bce                     mov       ecx, esi
005f5bea ff92f0000000             call      dword ptr [edx + 0xf0]
005f5bf0 8b8e7c080000             mov       ecx, dword ptr [esi + 0x87c]
005f5bf6 3b8e84080000             cmp       ecx, dword ptr [esi + 0x884]
005f5bfc 7c17                     jl        0x5f5c15
005f5bfe 80be8808000001           cmp       byte ptr [esi + 0x888], 1
005f5c05 750e                     jne       0x5f5c15
005f5c07 8b4508                   mov       eax, dword ptr [ebp + 8]
005f5c0a 8b16                     mov       edx, dword ptr [esi]
005f5c0c 50                       push      eax
005f5c0d 8bce                     mov       ecx, esi
005f5c0f ff928c030000             call      dword ptr [edx + 0x38c]
005f5c15 5e                       pop       esi
005f5c16 5d                       pop       ebp
005f5c17 c21400                   ret       0x14
005f5c1a cc                       int3      
