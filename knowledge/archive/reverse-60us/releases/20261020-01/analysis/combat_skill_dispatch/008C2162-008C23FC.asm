008c2162  33db                     xor        ebx, ebx
008c2164  885d0b                   mov        byte ptr [ebp + 0xb], bl
008c2167  895de0                   mov        dword ptr [ebp - 0x20], ebx
008c216a  895de8                   mov        dword ptr [ebp - 0x18], ebx
008c216d  895d98                   mov        dword ptr [ebp - 0x68], ebx
008c2170  895d9c                   mov        dword ptr [ebp - 0x64], ebx
008c2173  895da0                   mov        dword ptr [ebp - 0x60], ebx
008c2176  8b16                     mov        edx, dword ptr [esi]
008c2178  8d45e0                   lea        eax, [ebp - 0x20]
008c217b  50                       push       eax
008c217c  8bce                     mov        ecx, esi
008c217e  c745fc01000000           mov        dword ptr [ebp - 4], 1
008c2185  ff5254                   call       dword ptr [edx + 0x54]
008c2188  8b16                     mov        edx, dword ptr [esi]
008c218a  8d45e8                   lea        eax, [ebp - 0x18]
008c218d  50                       push       eax
008c218e  8bce                     mov        ecx, esi
008c2190  ff5254                   call       dword ptr [edx + 0x54]
008c2193  8b16                     mov        edx, dword ptr [esi]
008c2195  8d450b                   lea        eax, [ebp + 0xb]
008c2198  50                       push       eax
008c2199  8bce                     mov        ecx, esi
008c219b  ff5250                   call       dword ptr [edx + 0x50]
008c219e  8b16                     mov        edx, dword ptr [esi]
008c21a0  8d4510                   lea        eax, [ebp + 0x10]
008c21a3  50                       push       eax
008c21a4  8bce                     mov        ecx, esi
008c21a6  895d10                   mov        dword ptr [ebp + 0x10], ebx
008c21a9  ff5254                   call       dword ptr [edx + 0x54]
008c21ac  899d50ffffff             mov        dword ptr [ebp - 0xb0], ebx
008c21b2  899d54ffffff             mov        dword ptr [ebp - 0xac], ebx
008c21b8  899d58ffffff             mov        dword ptr [ebp - 0xa8], ebx
008c21be  0fb74d10                 movzx      ecx, word ptr [ebp + 0x10]
008c21c2  51                       push       ecx
008c21c3  8d8d4cffffff             lea        ecx, [ebp - 0xb4]
008c21c9  c645fc02                 mov        byte ptr [ebp - 4], 2
008c21cd  e8be400000               call       0x8c6290
008c21d2  33ff                     xor        edi, edi
008c21d4  66395d10                 cmp        word ptr [ebp + 0x10], bx
008c21d8  7629                     jbe        0x8c2203
008c21da  8d9b00000000             lea        ebx, [ebx]
008c21e0  8b16                     mov        edx, dword ptr [esi]
008c21e2  8d450f                   lea        eax, [ebp + 0xf]
008c21e5  50                       push       eax
008c21e6  8bce                     mov        ecx, esi
008c21e8  ff5250                   call       dword ptr [edx + 0x50]
008c21eb  8d4d0f                   lea        ecx, [ebp + 0xf]
008c21ee  51                       push       ecx
008c21ef  8d8d4cffffff             lea        ecx, [ebp - 0xb4]
008c21f5  e896d6b5ff               call       0x41f890
008c21fa  0fb75510                 movzx      edx, word ptr [ebp + 0x10]
008c21fe  47                       inc        edi
008c21ff  3bfa                     cmp        edi, edx
008c2201  7cdd                     jl         0x8c21e0
008c2203  895d80                   mov        dword ptr [ebp - 0x80], ebx
008c2206  895d84                   mov        dword ptr [ebp - 0x7c], ebx
008c2209  895d88                   mov        dword ptr [ebp - 0x78], ebx
008c220c  8d854cffffff             lea        eax, [ebp - 0xb4]
008c2212  50                       push       eax
008c2213  8d8d7cffffff             lea        ecx, [ebp - 0x84]
008c2219  c645fc03                 mov        byte ptr [ebp - 4], 3
008c221d  e8de430000               call       0x8c6600
008c2222  8d4d94                   lea        ecx, [ebp - 0x6c]
008c2225  51                       push       ecx
008c2226  8d8d7cffffff             lea        ecx, [ebp - 0x84]
008c222c  e85fb2c2ff               call       0x4ed490
008c2231  8bb660a01000             mov        esi, dword ptr [esi + 0x10a060]
008c2237  3bf3                     cmp        esi, ebx
008c2239  0f8436360000             je         0x8c5875
008c223f  8b8eb0000000             mov        ecx, dword ptr [esi + 0xb0]
008c2245  3bcb                     cmp        ecx, ebx
008c2247  0f8428360000             je         0x8c5875
008c224d  0fb755e8                 movzx      edx, word ptr [ebp - 0x18]
008c2251  0fb745e0                 movzx      eax, word ptr [ebp - 0x20]
008c2255  53                       push       ebx
008c2256  687c28f400               push       0xf4287c
008c225b  681009f400               push       0xf40910
008c2260  53                       push       ebx
008c2261  52                       push       edx
008c2262  50                       push       eax
008c2263  e8b895c4ff               call       0x50b820
008c2268  50                       push       eax
008c2269  e89dea3300               call       0xc00d0b
008c226e  8bf0                     mov        esi, eax
008c2270  83c414                   add        esp, 0x14
008c2273  3bf3                     cmp        esi, ebx
008c2275  0f84fa350000             je         0x8c5875
008c227b  8b16                     mov        edx, dword ptr [esi]
008c227d  8bce                     mov        ecx, esi
008c227f  ff9224010000             call       dword ptr [edx + 0x124]
008c2285  8bf8                     mov        edi, eax
008c2287  8b06                     mov        eax, dword ptr [esi]
008c2289  8bce                     mov        ecx, esi
008c228b  897df0                   mov        dword ptr [ebp - 0x10], edi
008c228e  ff902c010000             call       dword ptr [eax + 0x12c]
008c2294  8b16                     mov        edx, dword ptr [esi]
008c2296  8bce                     mov        ecx, esi
008c2298  8945d0                   mov        dword ptr [ebp - 0x30], eax
008c229b  ff9228010000             call       dword ptr [edx + 0x128]
008c22a1  3bfb                     cmp        edi, ebx
008c22a3  8945c8                   mov        dword ptr [ebp - 0x38], eax
008c22a6  740e                     je         0x8c22b6
008c22a8  8b06                     mov        eax, dword ptr [esi]
008c22aa  53                       push       ebx
008c22ab  6aff                     push       -1
008c22ad  53                       push       ebx
008c22ae  8bce                     mov        ecx, esi
008c22b0  ff901c010000             call       dword ptr [eax + 0x11c]
008c22b6  b928070001               mov        ecx, 0x1000728
008c22bb  e8600ab4ff               call       0x402d20
008c22c0  8b16                     mov        edx, dword ptr [esi]
008c22c2  6a21                     push       0x21
008c22c4  8bce                     mov        ecx, esi
008c22c6  c7450cffffffff           mov        dword ptr [ebp + 0xc], 0xffffffff
008c22cd  ff522c                   call       dword ptr [edx + 0x2c]
008c22d0  84c0                     test       al, al
008c22d2  8bce                     mov        ecx, esi
008c22d4  751d                     jne        0x8c22f3
008c22d6  8b16                     mov        edx, dword ptr [esi]
008c22d8  6a11                     push       0x11
008c22da  ff522c                   call       dword ptr [edx + 0x2c]
008c22dd  84c0                     test       al, al
008c22df  8bce                     mov        ecx, esi
008c22e1  7510                     jne        0x8c22f3
008c22e3  8b16                     mov        edx, dword ptr [esi]
008c22e5  6881000000               push       0x81
008c22ea  ff522c                   call       dword ptr [edx + 0x2c]
008c22ed  84c0                     test       al, al
008c22ef  740d                     je         0x8c22fe
008c22f1  8bce                     mov        ecx, esi
008c22f3  8b06                     mov        eax, dword ptr [esi]
008c22f5  ff9030020000             call       dword ptr [eax + 0x230]
008c22fb  89450c                   mov        dword ptr [ebp + 0xc], eax
008c22fe  8b4598                   mov        eax, dword ptr [ebp - 0x68]
008c2301  3bc3                     cmp        eax, ebx
008c2303  7504                     jne        0x8c2309
008c2305  33ff                     xor        edi, edi
008c2307  eb08                     jmp        0x8c2311
008c2309  8b7d9c                   mov        edi, dword ptr [ebp - 0x64]
008c230c  2bf8                     sub        edi, eax
008c230e  c1ff02                   sar        edi, 2
008c2311  8d8e08020000             lea        ecx, [esi + 0x208]
008c2317  e8d40d1900               call       0xa530f0
008c231c  0fb64d0b                 movzx      ecx, byte ptr [ebp + 0xb]
008c2320  8b550c                   mov        edx, dword ptr [ebp + 0xc]
008c2323  57                       push       edi
008c2324  51                       push       ecx
008c2325  8945ec                   mov        dword ptr [ebp - 0x14], eax
008c2328  8b06                     mov        eax, dword ptr [esi]
008c232a  52                       push       edx
008c232b  8bce                     mov        ecx, esi
008c232d  ff5040                   call       dword ptr [eax + 0x40]
008c2330  8b4dec                   mov        ecx, dword ptr [ebp - 0x14]
008c2333  50                       push       eax
008c2334  51                       push       ecx
008c2335  680812e300               push       0xe31208
008c233a  53                       push       ebx
008c233b  e860071900               call       0xa52aa0
008c2340  83c41c                   add        esp, 0x1c
008c2343  50                       push       eax
008c2344  b928070001               mov        ecx, 0x1000728
008c2349  e8f2c7b4ff               call       0x40eb40
008c234e  33ff                     xor        edi, edi
008c2350  8b4d98                   mov        ecx, dword ptr [ebp - 0x68]
008c2353  3bcb                     cmp        ecx, ebx
008c2355  742d                     je         0x8c2384
008c2357  8b459c                   mov        eax, dword ptr [ebp - 0x64]
008c235a  2bc1                     sub        eax, ecx
008c235c  c1f802                   sar        eax, 2
008c235f  3bf8                     cmp        edi, eax
008c2361  7321                     jae        0x8c2384
008c2363  8b14b9                   mov        edx, dword ptr [ecx + edi*4]
008c2366  52                       push       edx
008c2367  57                       push       edi
008c2368  68e411e300               push       0xe311e4
008c236d  53                       push       ebx
008c236e  e82d071900               call       0xa52aa0
008c2373  83c410                   add        esp, 0x10
008c2376  50                       push       eax
008c2377  b928070001               mov        ecx, 0x1000728
008c237c  e8efc7b4ff               call       0x40eb70
008c2381  47                       inc        edi
008c2382  ebcc                     jmp        0x8c2350
008c2384  0fb6550b                 movzx      edx, byte ptr [ebp + 0xb]
008c2388  8b06                     mov        eax, dword ptr [esi]
008c238a  6a01                     push       1
008c238c  6a01                     push       1
008c238e  8d4d94                   lea        ecx, [ebp - 0x6c]
008c2391  51                       push       ecx
008c2392  52                       push       edx
008c2393  8bce                     mov        ecx, esi
008c2395  ff902c020000             call       dword ptr [eax + 0x22c]
008c239b  8b7df0                   mov        edi, dword ptr [ebp - 0x10]
008c239e  3bfb                     cmp        edi, ebx
008c23a0  743e                     je         0x8c23e0
008c23a2  8b06                     mov        eax, dword ptr [esi]
008c23a4  6a11                     push       0x11
008c23a6  8bce                     mov        ecx, esi
008c23a8  ff502c                   call       dword ptr [eax + 0x2c]
008c23ab  84c0                     test       al, al
008c23ad  741e                     je         0x8c23cd
008c23af  8a450b                   mov        al, byte ptr [ebp + 0xb]
008c23b2  3c03                     cmp        al, 3
008c23b4  7417                     je         0x8c23cd
008c23b6  3c04                     cmp        al, 4
008c23b8  7413                     je         0x8c23cd
008c23ba  3c05                     cmp        al, 5
008c23bc  740f                     je         0x8c23cd
008c23be  3c09                     cmp        al, 9
008c23c0  740b                     je         0x8c23cd
008c23c2  83ff01                   cmp        edi, 1
008c23c5  7506                     jne        0x8c23cd
008c23c7  837dd0ff                 cmp        dword ptr [ebp - 0x30], -1
008c23cb  7513                     jne        0x8c23e0
008c23cd  8b45c8                   mov        eax, dword ptr [ebp - 0x38]
008c23d0  8b4dd0                   mov        ecx, dword ptr [ebp - 0x30]
008c23d3  8b16                     mov        edx, dword ptr [esi]
008c23d5  50                       push       eax
008c23d6  51                       push       ecx
008c23d7  57                       push       edi
008c23d8  8bce                     mov        ecx, esi
008c23da  ff921c010000             call       dword ptr [edx + 0x11c]
008c23e0  8b16                     mov        edx, dword ptr [esi]
008c23e2  8bce                     mov        ecx, esi
008c23e4  ff9294020000             call       dword ptr [edx + 0x294]
008c23ea  0fb64d0b                 movzx      ecx, byte ptr [ebp + 0xb]
008c23ee  3bc1                     cmp        eax, ecx
008c23f0  750a                     jne        0x8c23fc
008c23f2  8b16                     mov        edx, dword ptr [esi]
008c23f4  8bce                     mov        ecx, esi
008c23f6  ff9298020000             call       dword ptr [edx + 0x298]