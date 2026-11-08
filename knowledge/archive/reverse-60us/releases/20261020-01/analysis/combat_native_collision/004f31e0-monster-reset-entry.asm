004f31e0 5d                       pop       ebp
004f31e1 c20800                   ret       8
004f31e4 57                       push      edi
004f31e5 686459cd00               push      0xcd5964
004f31ea ff15bc2eff00             call      dword ptr [0xff2ebc]
004f31f0 83c408                   add       esp, 8
004f31f3 5f                       pop       edi
004f31f4 5e                       pop       esi
004f31f5 8be5                     mov       esp, ebp
004f31f7 5d                       pop       ebp
004f31f8 c20800                   ret       8
004f31fb cc                       int3      
004f31fc cc                       int3      
004f31fd cc                       int3      
004f31fe cc                       int3      
004f31ff cc                       int3      
004f3200 55                       push      ebp
004f3201 8bec                     mov       ebp, esp
004f3203 51                       push      ecx
004f3204 56                       push      esi
004f3205 57                       push      edi
004f3206 8bf1                     mov       esi, ecx
004f3208 e803bafbff               call      0x4aec10
004f320d 8a8614250000             mov       al, byte ptr [esi + 0x2514]
004f3213 84c0                     test      al, al
004f3215 753b                     jne       0x4f3252
004f3217 83be5c1b000008           cmp       dword ptr [esi + 0x1b5c], 8
004f321e 7208                     jb        0x4f3228
004f3220 8b86481b0000             mov       eax, dword ptr [esi + 0x1b48]
004f3226 eb06                     jmp       0x4f322e
004f3228 8d86481b0000             lea       eax, [esi + 0x1b48]
004f322e 8b3e                     mov       edi, dword ptr [esi]
004f3230 50                       push      eax
004f3231 6a03                     push      3
004f3233 8bce                     mov       ecx, esi
004f3235 ff9744030000             call      dword ptr [edi + 0x344]
004f323b 8bc8                     mov       ecx, eax
004f323d e81eeef0ff               call      0x402060
004f3242 50                       push      eax
004f3243 8bce                     mov       ecx, esi
004f3245 ff97a4050000             call      dword ptr [edi + 0x5a4]
004f324b c6861425000001           mov       byte ptr [esi + 0x2514], 1
004f3252 8b06                     mov       eax, dword ptr [esi]
004f3254 33ff                     xor       edi, edi
004f3256 57                       push      edi
004f3257 8bce                     mov       ecx, esi
004f3259 ff9028030000             call      dword ptr [eax + 0x328]
004f325f 8b16                     mov       edx, dword ptr [esi]
004f3261 8bce                     mov       ecx, esi
004f3263 89be801b0000             mov       dword ptr [esi + 0x1b80], edi
004f3269 89be841b0000             mov       dword ptr [esi + 0x1b84], edi
004f326f ff92c4010000             call      dword ptr [edx + 0x1c4]
004f3275 85c0                     test      eax, eax
004f3277 7c1b                     jl        0x4f3294
004f3279 8b06                     mov       eax, dword ptr [esi]
004f327b 8bce                     mov       ecx, esi
004f327d ff90c4010000             call      dword ptr [eax + 0x1c4]
004f3283 83f80b                   cmp       eax, 0xb
004f3286 7f0c                     jg        0x4f3294
004f3288 c786881b000018fcffff     mov       dword ptr [esi + 0x1b88], 0xfffffc18
004f3292 eb06                     jmp       0x4f329a
004f3294 89be881b0000             mov       dword ptr [esi + 0x1b88], edi
004f329a 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
004f32a0 89be8c1b0000             mov       dword ptr [esi + 0x1b8c], edi
004f32a6 89be901b0000             mov       dword ptr [esi + 0x1b90], edi
004f32ac 89be941b0000             mov       dword ptr [esi + 0x1b94], edi
004f32b2 89beb41d0000             mov       dword ptr [esi + 0x1db4], edi
004f32b8 39b914010000             cmp       dword ptr [ecx + 0x114], edi
004f32be 0f844f010000             je        0x4f3413
004f32c4 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004f32ca 81c140100000             add       ecx, 0x1040
004f32d0 e88bedf0ff               call      0x402060
004f32d5 83f80a                   cmp       eax, 0xa
004f32d8 741a                     je        0x4f32f4
004f32da 8b0d48280001             mov       ecx, dword ptr [0x1002848]
