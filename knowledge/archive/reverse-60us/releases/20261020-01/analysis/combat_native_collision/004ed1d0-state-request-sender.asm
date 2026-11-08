004ed1d0 55                       push      ebp
004ed1d1 8bec                     mov       ebp, esp
004ed1d3 56                       push      esi
004ed1d4 8bf1                     mov       esi, ecx
004ed1d6 8a869c040000             mov       al, byte ptr [esi + 0x49c]
004ed1dc 84c0                     test      al, al
004ed1de 0f84ee000000             je        0x4ed2d2
004ed1e4 e8a7eefaff               call      0x49c090
004ed1e9 84c0                     test      al, al
004ed1eb 750b                     jne       0x4ed1f8
004ed1ed 8a4514                   mov       al, byte ptr [ebp + 0x14]
004ed1f0 84c0                     test      al, al
004ed1f2 0f84da000000             je        0x4ed2d2
004ed1f8 8b06                     mov       eax, dword ptr [esi]
004ed1fa 57                       push      edi
004ed1fb 6881000000               push      0x81
004ed200 8bce                     mov       ecx, esi
004ed202 ff502c                   call      dword ptr [eax + 0x2c]
004ed205 84c0                     test      al, al
004ed207 7461                     je        0x4ed26a
004ed209 8b4518                   mov       eax, dword ptr [ebp + 0x18]
004ed20c 85c0                     test      eax, eax
004ed20e 745a                     je        0x4ed26a
004ed210 53                       push      ebx
004ed211 b960070001               mov       ecx, 0x1000760
004ed216 e8055bf1ff               call      0x402d20
004ed21b 8b16                     mov       edx, dword ptr [esi]
004ed21d 8bce                     mov       ecx, esi
004ed21f ff9230020000             call      dword ptr [edx + 0x230]
004ed225 8d8e08020000             lea       ecx, [esi + 0x208]
004ed22b 8bf8                     mov       edi, eax
004ed22d e8be5e5600               call      0xa530f0
004ed232 8b16                     mov       edx, dword ptr [esi]
004ed234 8bd8                     mov       ebx, eax
004ed236 8b4508                   mov       eax, dword ptr [ebp + 8]
004ed239 50                       push      eax
004ed23a 57                       push      edi
004ed23b 8bce                     mov       ecx, esi
004ed23d ff5240                   call      dword ptr [edx + 0x40]
004ed240 50                       push      eax
004ed241 8b4518                   mov       eax, dword ptr [ebp + 0x18]
004ed244 53                       push      ebx
004ed245 50                       push      eax
004ed246 68404fcd00               push      0xcd4f40
004ed24b 6a00                     push      0
004ed24d e84e585600               call      0xa52aa0
004ed252 8bf8                     mov       edi, eax
004ed254 57                       push      edi
004ed255 e8732b7100               call      0xbffdcd
004ed25a 83c420                   add       esp, 0x20
004ed25d 50                       push      eax
004ed25e 57                       push      edi
004ed25f b960070001               mov       ecx, 0x1000760
004ed264 e8175cf1ff               call      0x402e80
004ed269 5b                       pop       ebx
004ed26a 8b16                     mov       edx, dword ptr [esi]
004ed26c 6811020000               push      0x211
004ed271 8bce                     mov       ecx, esi
004ed273 ff522c                   call      dword ptr [edx + 0x2c]
004ed276 84c0                     test      al, al
004ed278 7409                     je        0x4ed283
004ed27a 83bea004000005           cmp       dword ptr [esi + 0x4a0], 5
004ed281 744e                     je        0x4ed2d1
004ed283 83bea0040000ff           cmp       dword ptr [esi + 0x4a0], -1
004ed28a 8b7d10                   mov       edi, dword ptr [ebp + 0x10]
004ed28d 7408                     je        0x4ed297
004ed28f 39beb4040000             cmp       dword ptr [esi + 0x4b4], edi
004ed295 7f3a                     jg        0x4ed2d1
004ed297 8b4508                   mov       eax, dword ptr [ebp + 8]
004ed29a 8986a0040000             mov       dword ptr [esi + 0x4a0], eax
004ed2a0 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004ed2a3 85c0                     test      eax, eax
004ed2a5 c6869d04000000           mov       byte ptr [esi + 0x49d], 0
004ed2ac 8d8ea4040000             lea       ecx, [esi + 0x4a4]
004ed2b2 7412                     je        0x4ed2c6
004ed2b4 50                       push      eax
004ed2b5 e886a60100               call      0x507940
004ed2ba 89beb4040000             mov       dword ptr [esi + 0x4b4], edi
004ed2c0 5f                       pop       edi
004ed2c1 5e                       pop       esi
004ed2c2 5d                       pop       ebp
004ed2c3 c21400                   ret       0x14
004ed2c6 e8857a1500               call      0x644d50
004ed2cb 89beb4040000             mov       dword ptr [esi + 0x4b4], edi
004ed2d1 5f                       pop       edi
004ed2d2 5e                       pop       esi
004ed2d3 5d                       pop       ebp
004ed2d4 c21400                   ret       0x14
004ed2d7 cc                       int3      
004ed2d8 cc                       int3      
004ed2d9 cc                       int3      
004ed2da cc                       int3      
004ed2db cc                       int3      
004ed2dc cc                       int3      
004ed2dd cc                       int3      
004ed2de cc                       int3      
004ed2df cc                       int3      
