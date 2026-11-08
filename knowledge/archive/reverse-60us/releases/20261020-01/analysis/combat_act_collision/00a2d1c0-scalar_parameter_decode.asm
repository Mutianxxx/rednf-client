00a2d1c0 55                       push       ebp
00a2d1c1 8bec                     mov        ebp, esp
00a2d1c3 53                       push       ebx
00a2d1c4 8b5d08                   mov        ebx, dword ptr [ebp + 8]
00a2d1c7 56                       push       esi
00a2d1c8 57                       push       edi
00a2d1c9 8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
00a2d1cc 8b07                     mov        eax, dword ptr [edi]
00a2d1ce 8d4801                   lea        ecx, [eax + 1]
00a2d1d1 8d7324                   lea        esi, [ebx + 0x24]
00a2d1d4 890f                     mov        dword ptr [edi], ecx
00a2d1d6 8b5608                   mov        edx, dword ptr [esi + 8]
00a2d1d9 2b5604                   sub        edx, dword ptr [esi + 4]
00a2d1dc c1fa02                   sar        edx, 2
00a2d1df 3bd0                     cmp        edx, eax
00a2d1e1 0f8601010000             jbe        0xa2d2e8
00a2d1e7 50                       push       eax
00a2d1e8 8bce                     mov        ecx, esi
00a2d1ea e891150100               call       0xa3e780
00a2d1ef 8b00                     mov        eax, dword ptr [eax]
00a2d1f1 83f801                   cmp        eax, 1
00a2d1f4 7575                     jne        0xa2d26b
00a2d1f6 8b07                     mov        eax, dword ptr [edi]
00a2d1f8 8d4801                   lea        ecx, [eax + 1]
00a2d1fb 890f                     mov        dword ptr [edi], ecx
00a2d1fd 8b5608                   mov        edx, dword ptr [esi + 8]
00a2d200 2b5604                   sub        edx, dword ptr [esi + 4]
00a2d203 c1fa02                   sar        edx, 2
00a2d206 3bd0                     cmp        edx, eax
00a2d208 760c                     jbe        0xa2d216
00a2d20a 50                       push       eax
00a2d20b 8bce                     mov        ecx, esi
00a2d20d e86e150100               call       0xa3e780
00a2d212 8b18                     mov        ebx, dword ptr [eax]
00a2d214 eb03                     jmp        0xa2d219
00a2d216 83cbff                   or         ebx, 0xffffffff
00a2d219 8b07                     mov        eax, dword ptr [edi]
00a2d21b 8d4801                   lea        ecx, [eax + 1]
00a2d21e 890f                     mov        dword ptr [edi], ecx
00a2d220 8b5608                   mov        edx, dword ptr [esi + 8]
00a2d223 2b5604                   sub        edx, dword ptr [esi + 4]
00a2d226 c1fa02                   sar        edx, 2
00a2d229 3bd0                     cmp        edx, eax
00a2d22b 760c                     jbe        0xa2d239
00a2d22d 50                       push       eax
00a2d22e 8bce                     mov        ecx, esi
00a2d230 e84b150100               call       0xa3e780
00a2d235 8b30                     mov        esi, dword ptr [eax]
00a2d237 eb03                     jmp        0xa2d23c
00a2d239 83ceff                   or         esi, 0xffffffff
00a2d23c 3bf3                     cmp        esi, ebx
00a2d23e 8bfe                     mov        edi, esi
00a2d240 7c02                     jl         0xa2d244
00a2d242 8bfb                     mov        edi, ebx
00a2d244 6a00                     push       0
00a2d246 e8a50ee8ff               call       0x8ae0f0
00a2d24b 8bc8                     mov        ecx, eax
00a2d24d 8bc6                     mov        eax, esi
00a2d24f 2bc3                     sub        eax, ebx
00a2d251 99                       cdq        
00a2d252 8bf0                     mov        esi, eax
00a2d254 33f2                     xor        esi, edx
00a2d256 2bf2                     sub        esi, edx
00a2d258 8bc1                     mov        eax, ecx
00a2d25a 99                       cdq        
00a2d25b f7fe                     idiv       esi
00a2d25d 83c404                   add        esp, 4
00a2d260 8bc2                     mov        eax, edx
00a2d262 03c7                     add        eax, edi
00a2d264 5f                       pop        edi
00a2d265 5e                       pop        esi
00a2d266 5b                       pop        ebx
00a2d267 5d                       pop        ebp
00a2d268 c20800                   ret        8
00a2d26b 83f802                   cmp        eax, 2
00a2d26e 756a                     jne        0xa2d2da
00a2d270 8b07                     mov        eax, dword ptr [edi]
00a2d272 8d5001                   lea        edx, [eax + 1]
00a2d275 8917                     mov        dword ptr [edi], edx
00a2d277 8b4e08                   mov        ecx, dword ptr [esi + 8]
00a2d27a 2b4e04                   sub        ecx, dword ptr [esi + 4]
00a2d27d c1f902                   sar        ecx, 2
00a2d280 3bc8                     cmp        ecx, eax
00a2d282 760c                     jbe        0xa2d290
00a2d284 50                       push       eax
00a2d285 8bce                     mov        ecx, esi
00a2d287 e8f4140100               call       0xa3e780
00a2d28c 8b18                     mov        ebx, dword ptr [eax]
00a2d28e eb03                     jmp        0xa2d293
00a2d290 83cbff                   or         ebx, 0xffffffff
00a2d293 6a00                     push       0
00a2d295 e8560ee8ff               call       0x8ae0f0
00a2d29a 99                       cdq        
00a2d29b f7fb                     idiv       ebx
00a2d29d 8b07                     mov        eax, dword ptr [edi]
00a2d29f 8b4e04                   mov        ecx, dword ptr [esi + 4]
00a2d2a2 83c404                   add        esp, 4
00a2d2a5 03d0                     add        edx, eax
00a2d2a7 8b4608                   mov        eax, dword ptr [esi + 8]
00a2d2aa 2bc1                     sub        eax, ecx
00a2d2ac c1f802                   sar        eax, 2
00a2d2af 3bc2                     cmp        eax, edx
00a2d2b1 7617                     jbe        0xa2d2ca
00a2d2b3 52                       push       edx
00a2d2b4 8bce                     mov        ecx, esi
00a2d2b6 e8c5140100               call       0xa3e780
00a2d2bb 8b0f                     mov        ecx, dword ptr [edi]
00a2d2bd 8b00                     mov        eax, dword ptr [eax]
00a2d2bf 03cb                     add        ecx, ebx
00a2d2c1 890f                     mov        dword ptr [edi], ecx
00a2d2c3 5f                       pop        edi
00a2d2c4 5e                       pop        esi
00a2d2c5 5b                       pop        ebx
00a2d2c6 5d                       pop        ebp
00a2d2c7 c20800                   ret        8
00a2d2ca 8b0f                     mov        ecx, dword ptr [edi]
00a2d2cc 83c8ff                   or         eax, 0xffffffff
00a2d2cf 03cb                     add        ecx, ebx
00a2d2d1 890f                     mov        dword ptr [edi], ecx
00a2d2d3 5f                       pop        edi
00a2d2d4 5e                       pop        esi
00a2d2d5 5b                       pop        ebx
00a2d2d6 5d                       pop        ebp
00a2d2d7 c20800                   ret        8
00a2d2da 83f803                   cmp        eax, 3
00a2d2dd 7509                     jne        0xa2d2e8
00a2d2df 5f                       pop        edi
00a2d2e0 5e                       pop        esi
00a2d2e1 33c0                     xor        eax, eax
00a2d2e3 5b                       pop        ebx
00a2d2e4 5d                       pop        ebp
00a2d2e5 c20800                   ret        8
00a2d2e8 8b07                     mov        eax, dword ptr [edi]
00a2d2ea 8d4801                   lea        ecx, [eax + 1]
00a2d2ed 890f                     mov        dword ptr [edi], ecx
00a2d2ef 50                       push       eax
00a2d2f0 8bcb                     mov        ecx, ebx
00a2d2f2 e8095eb0ff               call       0x533100
00a2d2f7 5f                       pop        edi
00a2d2f8 5e                       pop        esi
00a2d2f9 5b                       pop        ebx
00a2d2fa 5d                       pop        ebp
00a2d2fb c20800                   ret        8
