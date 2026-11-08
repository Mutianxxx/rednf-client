004a0140 8b8fe0000000             mov       ecx, dword ptr [edi + 0xe0]
004a0146 898e5c050000             mov       dword ptr [esi + 0x55c], ecx
004a014c 8b97e4000000             mov       edx, dword ptr [edi + 0xe4]
004a0152 899660050000             mov       dword ptr [esi + 0x560], edx
004a0158 8b87ec000000             mov       eax, dword ptr [edi + 0xec]
004a015e 85c0                     test      eax, eax
004a0160 7504                     jne       0x4a0166
004a0162 33db                     xor       ebx, ebx
004a0164 eb0b                     jmp       0x4a0171
004a0166 8b9ff0000000             mov       ebx, dword ptr [edi + 0xf0]
004a016c 2bd8                     sub       ebx, eax
004a016e c1fb02                   sar       ebx, 2
004a0171 6a00                     push      0
004a0173 53                       push      ebx
004a0174 8d8e64050000             lea       ecx, [esi + 0x564]
004a017a 895d08                   mov       dword ptr [ebp + 8], ebx
004a017d e8ce200000               call      0x4a2250
004a0182 33c0                     xor       eax, eax
004a0184 85db                     test      ebx, ebx
004a0186 7e22                     jle       0x4a01aa
004a0188 eb06                     jmp       0x4a0190
004a018a 8d9b00000000             lea       ebx, [ebx]
004a0190 8b8fec000000             mov       ecx, dword ptr [edi + 0xec]
004a0196 8b0c81                   mov       ecx, dword ptr [ecx + eax*4]
004a0199 8b9668050000             mov       edx, dword ptr [esi + 0x568]
004a019f 890c82                   mov       dword ptr [edx + eax*4], ecx
004a01a2 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004a01a5 40                       inc       eax
004a01a6 3bc1                     cmp       eax, ecx
004a01a8 7ce6                     jl        0x4a0190
