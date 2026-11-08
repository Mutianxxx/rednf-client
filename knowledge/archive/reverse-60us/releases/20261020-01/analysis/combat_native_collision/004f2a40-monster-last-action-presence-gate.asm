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
004f2ae9 cc                       int3      
004f2aea cc                       int3      
004f2aeb cc                       int3      
004f2aec cc                       int3      
004f2aed cc                       int3      
004f2aee cc                       int3      
004f2aef cc                       int3      
004f2af0 55                       push      ebp
004f2af1 8bec                     mov       ebp, esp
004f2af3 81ece4000000             sub       esp, 0xe4
004f2af9 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004f2afc 56                       push      esi
004f2afd 8bf1                     mov       esi, ecx
004f2aff 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004f2b02 50                       push      eax
004f2b03 51                       push      ecx
004f2b04 8bce                     mov       ecx, esi
004f2b06 e8d59afbff               call      0x4ac5e0
004f2b0b 8b16                     mov       edx, dword ptr [esi]
004f2b0d 8bce                     mov       ecx, esi
004f2b0f ff92f4040000             call      dword ptr [edx + 0x4f4]
004f2b15 84c0                     test      al, al
004f2b17 0f85aa020000             jne       0x4f2dc7
004f2b1d 8b06                     mov       eax, dword ptr [esi]
004f2b1f 53                       push      ebx
004f2b20 57                       push      edi
004f2b21 8bce                     mov       ecx, esi
004f2b23 ff90e4000000             call      dword ptr [eax + 0xe4]
004f2b29 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004f2b2c b9e2ffffff               mov       ecx, 0xffffffe2
004f2b31 2bc8                     sub       ecx, eax
004f2b33 03d1                     add       edx, ecx
004f2b35 33db                     xor       ebx, ebx
004f2b37 53                       push      ebx
004f2b38 89550c                   mov       dword ptr [ebp + 0xc], edx
004f2b3b 53                       push      ebx
004f2b3c 8d550c                   lea       edx, [ebp + 0xc]
004f2b3f 52                       push      edx
004f2b40 8d4508                   lea       eax, [ebp + 8]
004f2b43 50                       push      eax
004f2b44 e8674c0400               call      0x5377b0
004f2b49 8b5508                   mov       edx, dword ptr [ebp + 8]
004f2b4c 83ea4b                   sub       edx, 0x4b
004f2b4f 33c0                     xor       eax, eax
004f2b51 66899d1cffffff           mov       word ptr [ebp - 0xe4], bx
004f2b58 b937000000               mov       ecx, 0x37
004f2b5d 8dbd1effffff             lea       edi, [ebp - 0xe2]
004f2b63 895508                   mov       dword ptr [ebp + 8], edx
004f2b66 8b16                     mov       edx, dword ptr [esi]
004f2b68 f3ab                     rep stosd dword ptr es:[edi], eax
004f2b6a 83c410                   add       esp, 0x10
004f2b6d 8bce                     mov       ecx, esi
004f2b6f ff9250050000             call      dword ptr [edx + 0x550]
004f2b75 84c0                     test      al, al
004f2b77 0f8442010000             je        0x4f2cbf
004f2b7d 8b06                     mov       eax, dword ptr [esi]
004f2b7f 8b                       .byte     0x8b
