004b2d90 008dbeec1400             add       byte ptr [ebp + 0x14ecbe], cl
004b2d96 00c7                     add       bh, al
004b2d98 45                       inc       ebp
004b2d99 dc17                     fcom      qword ptr [edi]
004b2d9b 0000                     add       byte ptr [eax], al
004b2d9d 008bff8b0785             add       byte ptr [ebx - 0x7af87401], cl
004b2da3 c074168b55               sal       byte ptr [esi + edx - 0x75], 0x55
004b2da8 0c6a                     or        al, 0x6a
004b2daa 005256                   add       byte ptr [edx + 0x56], dl
004b2dad 6a00                     push      0
004b2daf 8bc8                     mov       ecx, eax
004b2db1 8b01                     mov       eax, dword ptr [ecx]
004b2db3 53                       push      ebx
004b2db4 6a01                     push      1
004b2db6 ff9098010000             call      dword ptr [eax + 0x198]
004b2dbc 8b45dc                   mov       eax, dword ptr [ebp - 0x24]
004b2dbf 83c704                   add       edi, 4
004b2dc2 48                       dec       eax
004b2dc3 8945dc                   mov       dword ptr [ebp - 0x24], eax
004b2dc6 75d8                     jne       0x4b2da0
004b2dc8 8bce                     mov       ecx, esi
004b2dca e8c192feff               call      0x49c090
004b2dcf 84c0                     test      al, al
004b2dd1 0f8455080000             je        0x4b362c
004b2dd7 8b06                     mov       eax, dword ptr [esi]
004b2dd9 8bce                     mov       ecx, esi
004b2ddb ff90f4000000             call      dword ptr [eax + 0xf4]
004b2de1 85c0                     test      eax, eax
004b2de3 0f8443080000             je        0x4b362c
004b2de9 8b8ebc040000             mov       ecx, dword ptr [esi + 0x4bc]
004b2def 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004b2df5 8b86c0040000             mov       eax, dword ptr [esi + 0x4c0]
004b2dfb 8d9ebc040000             lea       ebx, [esi + 0x4bc]
004b2e01 33cf                     xor       ecx, edi
004b2e03 2bcb                     sub       ecx, ebx
004b2e05 3bc8                     cmp       ecx, eax
004b2e07 740e                     je        0x4b2e17
004b2e09 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004b2e0f 6a3f                     push      0x3f
004b2e11 53                       push      ebx
004b2e12 e899426600               call      0xb170b0
004b2e17 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004b2e1d 8b4a44                   mov       ecx, dword ptr [edx + 0x44]
004b2e20 8b4304                   mov       eax, dword ptr [ebx + 4]
004b2e23 c1e002                   shl       eax, 2
004b2e26 8d3c08                   lea       edi, [eax + ecx]
004b2e29 333c08                   xor       edi, dword ptr [eax + ecx]
004b2e2c 333ddc012101             xor       edi, dword ptr [0x12101dc]
004b2e32 8b4a48                   mov       ecx, dword ptr [edx + 0x48]
004b2e35 8d1408                   lea       edx, [eax + ecx]
004b2e38 331408                   xor       edx, dword ptr [eax + ecx]
004b2e3b 3315dc012101             xor       edx, dword ptr [0x12101dc]
004b2e41 3bfa                     cmp       edi, edx
004b2e43 740e                     je        0x4b2e53
004b2e45 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004b2e4b 6a40                     push      0x40
004b2e4d 53                       push      ebx
004b2e4e e85d426600               call      0xb170b0
004b2e53 85ff                     test      edi, edi
004b2e55 740d                     je        0x4b2e64
004b2e57 8d8ec4040000             lea       ecx, [esi + 0x4c4]
004b2e5d e8fef1f4ff               call      0x402060
004b2e62 eb07                     jmp       0x4b2e6b
004b2e64 8bce                     mov       ecx, esi
004b2e66 e87571feff               call      0x499fe0
004b2e6b 85c0                     test      eax, eax
004b2e6d 7409                     je        0x4b2e78
004b2e6f 83f801                   cmp       eax, 1
004b2e72 0f855f030000             jne       0x4b31d7
004b2e78 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004b2e7b 8b06                     mov       eax, dword ptr [esi]
004b2e7d 53                       push      ebx
004b2e7e 8bce                     mov       ecx, esi
