00b08200 55                       push       ebp
00b08201 8bec                     mov        ebp, esp
00b08203 83ec0c                   sub        esp, 0xc
00b08206 53                       push       ebx
00b08207 56                       push       esi
00b08208 57                       push       edi
00b08209 8bf1                     mov        esi, ecx
00b0820b 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b0820e 8b10                     mov        edx, dword ptr [eax]
00b08210 8d4e10                   lea        ecx, [esi + 0x10]
00b08213 51                       push       ecx
00b08214 33db                     xor        ebx, ebx
00b08216 53                       push       ebx
00b08217 6844010000               push       0x144
00b0821c 6800020000               push       0x200
00b08221 6800ac0d00               push       0xdac00
00b08226 50                       push       eax
00b08227 ff525c                   call       dword ptr [edx + 0x5c]
00b0822a 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b0822d 8b08                     mov        ecx, dword ptr [eax]
00b0822f 8d7e14                   lea        edi, [esi + 0x14]
00b08232 57                       push       edi
00b08233 53                       push       ebx
00b08234 6a65                     push       0x65
00b08236 6800020000               push       0x200
00b0823b 6800770100               push       0x17700
00b08240 50                       push       eax
00b08241 ff5160                   call       dword ptr [ecx + 0x60]
00b08244 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08247 8b10                     mov        edx, dword ptr [eax]
00b08249 8d4e18                   lea        ecx, [esi + 0x18]
00b0824c 51                       push       ecx
00b0824d 53                       push       ebx
00b0824e 6a65                     push       0x65
00b08250 6800020000               push       0x200
00b08255 68e0c40000               push       0xc4e0
00b0825a 50                       push       eax
00b0825b ff5260                   call       dword ptr [edx + 0x60]
00b0825e 8b07                     mov        eax, dword ptr [edi]
00b08260 3bc3                     cmp        eax, ebx
00b08262 747c                     je         0xb082e0
00b08264 8b10                     mov        edx, dword ptr [eax]
00b08266 6a10                     push       0x10
00b08268 8d4dfc                   lea        ecx, [ebp - 4]
00b0826b 51                       push       ecx
00b0826c 53                       push       ebx
00b0826d 53                       push       ebx
00b0826e 50                       push       eax
00b0826f ff522c                   call       dword ptr [edx + 0x2c]
00b08272 85c0                     test       eax, eax
00b08274 0f8526020000             jne        0xb084a0
00b0827a 895df8                   mov        dword ptr [ebp - 8], ebx
00b0827d 8d4900                   lea        ecx, [ecx]
00b08280 8b5dfc                   mov        ebx, dword ptr [ebp - 4]
00b08283 8b4df8                   mov        ecx, dword ptr [ebp - 8]
00b08286 c1e102                   shl        ecx, 2
00b08289 8d5102                   lea        edx, [ecx + 2]
00b0828c 66891418                 mov        word ptr [eax + ebx], dx
00b08290 8955f4                   mov        dword ptr [ebp - 0xc], edx
00b08293 8b55fc                   mov        edx, dword ptr [ebp - 4]
00b08296 66894c1002               mov        word ptr [eax + edx + 2], cx
00b0829b 8b5dfc                   mov        ebx, dword ptr [ebp - 4]
00b0829e 8d5101                   lea        edx, [ecx + 1]
00b082a1 6689541804               mov        word ptr [eax + ebx + 4], dx
00b082a6 8b5dfc                   mov        ebx, dword ptr [ebp - 4]
00b082a9 83c103                   add        ecx, 3
00b082ac 66894c1806               mov        word ptr [eax + ebx + 6], cx
00b082b1 8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00b082b4 668b5df4                 mov        bx, word ptr [ebp - 0xc]
00b082b8 66895c0808               mov        word ptr [eax + ecx + 8], bx
00b082bd 8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00b082c0 8b5df8                   mov        ebx, dword ptr [ebp - 8]
00b082c3 668954080a               mov        word ptr [eax + ecx + 0xa], dx
00b082c8 43                       inc        ebx
00b082c9 83c00c                   add        eax, 0xc
00b082cc 3d00770100               cmp        eax, 0x17700
00b082d1 895df8                   mov        dword ptr [ebp - 8], ebx
00b082d4 7caa                     jl         0xb08280
00b082d6 8b07                     mov        eax, dword ptr [edi]
00b082d8 8b10                     mov        edx, dword ptr [eax]
00b082da 50                       push       eax
00b082db ff5230                   call       dword ptr [edx + 0x30]
00b082de 33db                     xor        ebx, ebx
00b082e0 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b082e3 8b08                     mov        ecx, dword ptr [eax]
00b082e5 6a01                     push       1
00b082e7 6a1b                     push       0x1b
00b082e9 50                       push       eax
00b082ea ff91c8000000             call       dword ptr [ecx + 0xc8]
00b082f0 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b082f3 8b10                     mov        edx, dword ptr [eax]
00b082f5 6a05                     push       5
00b082f7 6a19                     push       0x19
00b082f9 50                       push       eax
00b082fa ff92c8000000             call       dword ptr [edx + 0xc8]
00b08300 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08303 8b08                     mov        ecx, dword ptr [eax]
00b08305 6a03                     push       3
00b08307 6a18                     push       0x18
00b08309 50                       push       eax
00b0830a ff91c8000000             call       dword ptr [ecx + 0xc8]
00b08310 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08313 8b10                     mov        edx, dword ptr [eax]
00b08315 6a01                     push       1
00b08317 6a0f                     push       0xf
00b08319 50                       push       eax
00b0831a ff92c8000000             call       dword ptr [edx + 0xc8]
00b08320 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08323 8b08                     mov        ecx, dword ptr [eax]
00b08325 6a01                     push       1
00b08327 6a16                     push       0x16
00b08329 50                       push       eax
00b0832a ff91c8000000             call       dword ptr [ecx + 0xc8]
00b08330 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08333 8b10                     mov        edx, dword ptr [eax]
00b08335 6a06                     push       6
00b08337 6a14                     push       0x14
00b08339 50                       push       eax
00b0833a ff92c8000000             call       dword ptr [edx + 0xc8]
00b08340 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08343 8b08                     mov        ecx, dword ptr [eax]
00b08345 53                       push       ebx
00b08346 6889000000               push       0x89
00b0834b 50                       push       eax
00b0834c ff91c8000000             call       dword ptr [ecx + 0xc8]
00b08352 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08355 8b10                     mov        edx, dword ptr [eax]
00b08357 6a05                     push       5
00b08359 6a13                     push       0x13
00b0835b 50                       push       eax
00b0835c ff92c8000000             call       dword ptr [edx + 0xc8]
00b08362 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08365 8b08                     mov        ecx, dword ptr [eax]
00b08367 53                       push       ebx
00b08368 6a34                     push       0x34
00b0836a 50                       push       eax
00b0836b ff91c8000000             call       dword ptr [ecx + 0xc8]
00b08371 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08374 8b10                     mov        edx, dword ptr [eax]
00b08376 53                       push       ebx
00b08377 6897000000               push       0x97
00b0837c 50                       push       eax
00b0837d ff92c8000000             call       dword ptr [edx + 0xc8]
00b08383 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08386 8b08                     mov        ecx, dword ptr [eax]
00b08388 6a02                     push       2
00b0838a 6a05                     push       5
00b0838c 53                       push       ebx
00b0838d 50                       push       eax
00b0838e ff91fc000000             call       dword ptr [ecx + 0xfc]
00b08394 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b08397 8b10                     mov        edx, dword ptr [eax]
00b08399 53                       push       ebx
00b0839a 6a06                     push       6
00b0839c 53                       push       ebx
00b0839d 50                       push       eax
00b0839e ff92fc000000             call       dword ptr [edx + 0xfc]
00b083a4 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b083a7 8b08                     mov        ecx, dword ptr [eax]
00b083a9 6a04                     push       4
00b083ab 6a04                     push       4
00b083ad 53                       push       ebx
00b083ae 50                       push       eax
00b083af ff91fc000000             call       dword ptr [ecx + 0xfc]
00b083b5 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b083b8 8b10                     mov        edx, dword ptr [eax]
00b083ba 6a04                     push       4
00b083bc 6a01                     push       1
00b083be 53                       push       ebx
00b083bf 50                       push       eax
00b083c0 ff92fc000000             call       dword ptr [edx + 0xfc]
00b083c6 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b083c9 8b08                     mov        ecx, dword ptr [eax]
00b083cb 53                       push       ebx
00b083cc 6a03                     push       3
00b083ce 53                       push       ebx
00b083cf 50                       push       eax
00b083d0 ff91fc000000             call       dword ptr [ecx + 0xfc]
00b083d6 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b083d9 8b10                     mov        edx, dword ptr [eax]
00b083db 6a03                     push       3
00b083dd 6a0d                     push       0xd
00b083df 53                       push       ebx
00b083e0 50                       push       eax
00b083e1 ff92fc000000             call       dword ptr [edx + 0xfc]
00b083e7 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b083ea 8b08                     mov        ecx, dword ptr [eax]
00b083ec 6a03                     push       3
00b083ee 6a0e                     push       0xe
00b083f0 53                       push       ebx
00b083f1 50                       push       eax
00b083f2 ff91fc000000             call       dword ptr [ecx + 0xfc]
00b083f8 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b083fb 8b10                     mov        edx, dword ptr [eax]
00b083fd 6a03                     push       3
00b083ff 6a10                     push       0x10
00b08401 53                       push       ebx
00b08402 50                       push       eax
00b08403 ff92fc000000             call       dword ptr [edx + 0xfc]
00b08409 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b0840c 8b08                     mov        ecx, dword ptr [eax]
00b0840e 6a02                     push       2
00b08410 6a11                     push       0x11
00b08412 53                       push       ebx
00b08413 50                       push       eax
00b08414 ff91fc000000             call       dword ptr [ecx + 0xfc]
00b0841a 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b0841d 8b10                     mov        edx, dword ptr [eax]
00b0841f 53                       push       ebx
00b08420 6a07                     push       7
00b08422 50                       push       eax
00b08423 ff92c8000000             call       dword ptr [edx + 0xc8]
00b08429 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b0842c 8b08                     mov        ecx, dword ptr [eax]
00b0842e 53                       push       ebx
00b0842f 6a0e                     push       0xe
00b08431 50                       push       eax
00b08432 ff91c8000000             call       dword ptr [ecx + 0xc8]
00b08438 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b0843b 8b10                     mov        edx, dword ptr [eax]
00b0843d 6a04                     push       4
00b0843f 6a17                     push       0x17
00b08441 50                       push       eax
00b08442 ff92c8000000             call       dword ptr [edx + 0xc8]
00b08448 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b0844b 8b08                     mov        ecx, dword ptr [eax]
00b0844d 6844010000               push       0x144
00b08452 50                       push       eax
00b08453 ff9130010000             call       dword ptr [ecx + 0x130]
00b08459 8b0f                     mov        ecx, dword ptr [edi]
00b0845b 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b0845e 8b10                     mov        edx, dword ptr [eax]
00b08460 53                       push       ebx
00b08461 51                       push       ecx
00b08462 50                       push       eax
00b08463 ff9254010000             call       dword ptr [edx + 0x154]
00b08469 8b4e10                   mov        ecx, dword ptr [esi + 0x10]
00b0846c 8b461c                   mov        eax, dword ptr [esi + 0x1c]
00b0846f 8b10                     mov        edx, dword ptr [eax]
00b08471 6a1c                     push       0x1c
00b08473 51                       push       ecx
00b08474 53                       push       ebx
00b08475 50                       push       eax
00b08476 ff924c010000             call       dword ptr [edx + 0x14c]
00b0847c 899e48030500             mov        dword ptr [esi + 0x50348], ebx
00b08482 5f                       pop        edi
00b08483 899e4c030500             mov        dword ptr [esi + 0x5034c], ebx
00b08489 899e40030500             mov        dword ptr [esi + 0x50340], ebx
00b0848f 899e44030500             mov        dword ptr [esi + 0x50344], ebx
00b08495 5e                       pop        esi
00b08496 b801000000               mov        eax, 1
00b0849b 5b                       pop        ebx
00b0849c 8be5                     mov        esp, ebp
00b0849e 5d                       pop        ebp
00b0849f c3                       ret        