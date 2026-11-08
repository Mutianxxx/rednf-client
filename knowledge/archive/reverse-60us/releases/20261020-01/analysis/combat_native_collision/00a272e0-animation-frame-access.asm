00a272e0 53                       push      ebx
00a272e1 e8bab70200               call      0xa52aa0
00a272e6 83c410                   add       esp, 0x10
00a272e9 50                       push      eax
00a272ea 8d4d80                   lea       ecx, [ebp - 0x80]
00a272ed e84e789eff               call      0x40eb40
00a272f2 eb0f                     jmp       0xa27303
00a272f4 6aff                     push      -1
00a272f6 53                       push      ebx
00a272f7 8d45d4                   lea       eax, [ebp - 0x2c]
00a272fa 50                       push      eax
00a272fb 8d4d80                   lea       ecx, [ebp - 0x80]
00a272fe e85dba9dff               call      0x402d60
00a27303 837d9808                 cmp       dword ptr [ebp - 0x68], 8
00a27307 8b4584                   mov       eax, dword ptr [ebp - 0x7c]
00a2730a 7303                     jae       0xa2730f
00a2730c 8d4584                   lea       eax, [ebp - 0x7c]
00a2730f 8b0dd8300001             mov       ecx, dword ptr [0x10030d8]
00a27315 8b11                     mov       edx, dword ptr [ecx]
00a27317 50                       push      eax
00a27318 ff5210                   call      dword ptr [edx + 0x10]
00a2731b 8d4d80                   lea       ecx, [ebp - 0x80]
00a2731e c645fc03                 mov       byte ptr [ebp - 4], 3
00a27322 e8496d1600               call      0xb8e070
00a27327 8b4508                   mov       eax, dword ptr [ebp + 8]
00a2732a 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
00a2732d 40                       inc       eax
00a2732e 3bc1                     cmp       eax, ecx
00a27330 894508                   mov       dword ptr [ebp + 8], eax
00a27333 0f8cfafeffff             jl        0xa27233
00a27339 8d4dd4                   lea       ecx, [ebp - 0x2c]
00a2733c e82f6d1600               call      0xb8e070
00a27341 8d4db8                   lea       ecx, [ebp - 0x48]
00a27344 e8276d1600               call      0xb8e070
00a27349 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00a2734c 5f                       pop       edi
00a2734d 5e                       pop       esi
00a2734e 32c0                     xor       al, al
00a27350 5b                       pop       ebx
00a27351 64890d00000000           mov       dword ptr fs:[0], ecx
00a27358 8be5                     mov       esp, ebp
00a2735a 5d                       pop       ebp
00a2735b c3                       ret       
00a2735c cc                       int3      
00a2735d cc                       int3      
00a2735e cc                       int3      
00a2735f cc                       int3      
00a27360 53                       push      ebx
00a27361 56                       push      esi
00a27362 8bf1                     mov       esi, ecx
00a27364 57                       push      edi
00a27365 8d4e48                   lea       ecx, [esi + 0x48]
00a27368 e883db9dff               call      0x404ef0
00a2736d 33db                     xor       ebx, ebx
00a2736f 8d8ea8000000             lea       ecx, [esi + 0xa8]
00a27375 899e88000000             mov       dword ptr [esi + 0x88], ebx
00a2737b 899e8c000000             mov       dword ptr [esi + 0x8c], ebx
00a27381 889e38010000             mov       byte ptr [esi + 0x138], bl
00a27387 889e39010000             mov       byte ptr [esi + 0x139], bl
00a2738d 889e3a010000             mov       byte ptr [esi + 0x13a], bl
00a27393 e8f86fa4ff               call      0x46e390
00a27398 399e84010000             cmp       dword ptr [esi + 0x184], ebx
00a2739e c78624010000ffffffff     mov       dword ptr [esi + 0x124], 0xffffffff
00a273a8 899e28010000             mov       dword ptr [esi + 0x128], ebx
00a273ae 899e2c010000             mov       dword ptr [esi + 0x12c], ebx
00a273b4 7622                     jbe       0xa273d8
00a273b6 8b8680010000             mov       eax, dword ptr [esi + 0x180]
00a273bc 8b38                     mov       edi, dword ptr [eax]
00a273be 3bf8                     cmp       edi, eax
00a273c0 7416                     je        0xa273d8
00a273c2 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
00a273c5 3bcb                     cmp       ecx, ebx
00a273c7 7405                     je        0xa273ce
00a273c9 e892ffffff               call      0xa27360
00a273ce 8b3f                     mov       edi, dword ptr [edi]
00a273d0 3bbe80010000             cmp       edi, dword ptr [esi + 0x180]
00a273d6 75ea                     jne       0xa273c2
00a273d8 899e90000000             mov       dword ptr [esi + 0x90], ebx
00a273de 33ff                     xor       edi, edi
00a273e0 8b8698000000             mov       eax, dword ptr [esi + 0x98]
00a273e6 85c0                     test      eax, eax
00a273e8 741b                     je        0xa27405
00a273ea 8b8e9c000000             mov       ecx, dword ptr [esi + 0x9c]
00a273f0 2bc8                     sub       ecx, eax
00a273f2 b843082184               mov       eax, 0x84210843
00a273f7 f7e9                     imul      ecx
00a273f9 03d1                     add       edx, ecx
00a273fb c1fa06                   sar       edx, 6
00a273fe 8bc2                     mov       eax, edx
00a27400 c1e81f                   shr       eax, 0x1f
00a27403 03c2                     add       eax, edx
00a27405 3bd8                     cmp       ebx, eax
00a27407 7d2a                     jge       0xa27433
00a27409 8b8698000000             mov       eax, dword ptr [esi + 0x98]
00a2740f 8b9690000000             mov       edx, dword ptr [esi + 0x90]
00a27415 03c7                     add       eax, edi
00a27417 8b4830                   mov       ecx, dword ptr [eax + 0x30]
00a2741a 83c030                   add       eax, 0x30
00a2741d 2bc8                     sub       ecx, eax
00a2741f 330df83e0d01             xor       ecx, dword ptr [0x10d3ef8]
00a27425 03d1                     add       edx, ecx
00a27427 43                       inc       ebx
00a27428 899690000000             mov       dword ptr [esi + 0x90], edx
00a2742e 83c77c                   add       edi, 0x7c
00a27431 ebad                     jmp       0xa273e0
00a27433 33ff                     xor       edi, edi
00a27435 33db                     xor       ebx, ebx
00a27437 eb07                     jmp       0xa27440
00a27439 8da42400000000           lea       esp, [esp]
