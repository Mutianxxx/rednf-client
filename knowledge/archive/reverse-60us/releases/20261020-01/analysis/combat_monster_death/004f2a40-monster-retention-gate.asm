004f2a40 56                       push      esi
004f2a41 8bf1                     mov       esi, ecx
004f2a43 8b06                     mov       eax, dword ptr [esi]
004f2a45 ff5038                   call      dword ptr [eax + 0x38]
004f2a48 84c0                     test      al, al
004f2a4a 7430                     je        0x4f2a7c
004f2a4c 57                       push      edi
004f2a4d 68e0baca00               push      0xcabae0
004f2a52 8dbef01a0000             lea       edi, [esi + 0x1af0]
004f2a58 e870d37000               call      0xbffdcd
004f2a5d 8b4f14                   mov       ecx, dword ptr [edi + 0x14]
004f2a60 83c404                   add       esp, 4
004f2a63 50                       push      eax
004f2a64 68e0baca00               push      0xcabae0
004f2a69 51                       push      ecx
004f2a6a 6a00                     push      0
004f2a6c 8bcf                     mov       ecx, edi
004f2a6e e87d15f1ff               call      0x403ff0
004f2a73 85c0                     test      eax, eax
004f2a75 5f                       pop       edi
004f2a76 7404                     je        0x4f2a7c
004f2a78 32c0                     xor       al, al
004f2a7a 5e                       pop       esi
004f2a7b c3                       ret       
004f2a7c 8b86e4190000             mov       eax, dword ptr [esi + 0x19e4]
004f2a82 83f803                   cmp       eax, 3
004f2a85 7405                     je        0x4f2a8c
004f2a87 83f808                   cmp       eax, 8
004f2a8a 7559                     jne       0x4f2ae5
004f2a8c 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004f2a92 81c140100000             add       ecx, 0x1040
004f2a98 e8c3f5f0ff               call      0x402060
004f2a9d 83f803                   cmp       eax, 3
004f2aa0 7416                     je        0x4f2ab8
004f2aa2 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004f2aa8 81c140100000             add       ecx, 0x1040
004f2aae e8adf5f0ff               call      0x402060
004f2ab3 83f80a                   cmp       eax, 0xa
004f2ab6 752d                     jne       0x4f2ae5
004f2ab8 8b16                     mov       edx, dword ptr [esi]
004f2aba 8bce                     mov       ecx, esi
004f2abc ff9278030000             call      dword ptr [edx + 0x378]
004f2ac2 85c0                     test      eax, eax
004f2ac4 750e                     jne       0x4f2ad4
004f2ac6 8b06                     mov       eax, dword ptr [esi]
004f2ac8 8bce                     mov       ecx, esi
004f2aca ff90a0030000             call      dword ptr [eax + 0x3a0]
004f2ad0 85c0                     test      eax, eax
004f2ad2 7411                     je        0x4f2ae5
004f2ad4 8a86fc240000             mov       al, byte ptr [esi + 0x24fc]
004f2ada 84c0                     test      al, al
004f2adc 7507                     jne       0x4f2ae5
004f2ade b801000000               mov       eax, 1
004f2ae3 5e                       pop       esi
004f2ae4 c3                       ret       
004f2ae5 33c0                     xor       eax, eax
004f2ae7 5e                       pop       esi
004f2ae8 c3                       ret       
