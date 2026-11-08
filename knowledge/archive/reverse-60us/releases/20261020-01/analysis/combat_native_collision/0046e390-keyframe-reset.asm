0046e390 55                       push      ebp
0046e391 8bec                     mov       ebp, esp
0046e393 51                       push      ecx
0046e394 53                       push      ebx
0046e395 33db                     xor       ebx, ebx
0046e397 56                       push      esi
0046e398 8bf1                     mov       esi, ecx
0046e39a 891e                     mov       dword ptr [esi], ebx
0046e39c 895e04                   mov       dword ptr [esi + 4], ebx
0046e39f 895e08                   mov       dword ptr [esi + 8], ebx
0046e3a2 895e0c                   mov       dword ptr [esi + 0xc], ebx
0046e3a5 8b0dfc3e0d01             mov       ecx, dword ptr [0x10d3efc]
0046e3ab c745fc0000803f           mov       dword ptr [ebp - 4], 0x3f800000
0046e3b2 334dfc                   xor       ecx, dword ptr [ebp - 4]
0046e3b5 8d4610                   lea       eax, [esi + 0x10]
0046e3b8 03c8                     add       ecx, eax
0046e3ba 8908                     mov       dword ptr [eax], ecx
0046e3bc 8b15fc3e0d01             mov       edx, dword ptr [0x10d3efc]
0046e3c2 c745fc0000803f           mov       dword ptr [ebp - 4], 0x3f800000
0046e3c9 3355fc                   xor       edx, dword ptr [ebp - 4]
0046e3cc 8d4614                   lea       eax, [esi + 0x14]
0046e3cf 03d0                     add       edx, eax
0046e3d1 8910                     mov       dword ptr [eax], edx
0046e3d3 895e18                   mov       dword ptr [esi + 0x18], ebx
0046e3d6 c7461cffffffff           mov       dword ptr [esi + 0x1c], 0xffffffff
0046e3dd 885e20                   mov       byte ptr [esi + 0x20], bl
0046e3e0 895e24                   mov       dword ptr [esi + 0x24], ebx
0046e3e3 895e28                   mov       dword ptr [esi + 0x28], ebx
0046e3e6 895e2c                   mov       dword ptr [esi + 0x2c], ebx
0046e3e9 a1f83e0d01               mov       eax, dword ptr [0x10d3ef8]
0046e3ee 8d4c3030                 lea       ecx, [eax + esi + 0x30]
0046e3f2 894e30                   mov       dword ptr [esi + 0x30], ecx
0046e3f5 8d4e38                   lea       ecx, [esi + 0x38]
0046e3f8 e8237bf9ff               call      0x405f20
0046e3fd 8d4e48                   lea       ecx, [esi + 0x48]
0046e400 e81b7bf9ff               call      0x405f20
0046e405 68e0baca00               push      0xcabae0
0046e40a 895e58                   mov       dword ptr [esi + 0x58], ebx
0046e40d 885e78                   mov       byte ptr [esi + 0x78], bl
0046e410 e8b8197900               call      0xbffdcd
0046e415 83c404                   add       esp, 4
0046e418 50                       push      eax
0046e419 68e0baca00               push      0xcabae0
0046e41e 8d4e5c                   lea       ecx, [esi + 0x5c]
0046e421 e85a4af9ff               call      0x402e80
0046e426 885e78                   mov       byte ptr [esi + 0x78], bl
0046e429 5e                       pop       esi
0046e42a 5b                       pop       ebx
0046e42b 8be5                     mov       esp, ebp
0046e42d 5d                       pop       ebp
0046e42e c3                       ret       
0046e42f cc                       int3      
0046e430 55                       push      ebp
0046e431 8bec                     mov       ebp, esp
0046e433 6aff                     push      -1
0046e435 68713dc500               push      0xc53d71
0046e43a 64a100000000             mov       eax, dword ptr fs:[0]
0046e440 50                       push      eax
0046e441 64892500000000           mov       dword ptr fs:[0], esp
0046e448 51                       push      ecx
0046e449 a0f43e0d01               mov       al, byte ptr [0x10d3ef4]
0046e44e 53                       push      ebx
0046e44f 56                       push      esi
0046e450 33db                     xor       ebx, ebx
0046e452 3ac3                     cmp       al, bl
0046e454 8bf1                     mov       esi, ecx
0046e456 57                       push      edi
0046e457 8975f0                   mov       dword ptr [ebp - 0x10], esi
0046e45a 7537                     jne       0x46e493
0046e45c ff15d8f04001             call      dword ptr [0x140f0d8]
0046e462 50                       push      eax
0046e463 e844397900               call      0xc01dac
0046e468 83c404                   add       esp, 4
0046e46b c705fc3e0d011e23ef6d     mov       dword ptr [0x10d3efc], 0x6def231e
0046e475 e83f397900               call      0xc01db9
0046e47a 8bf8                     mov       edi, eax
0046e47c c1e710                   shl       edi, 0x10
0046e47f e835397900               call      0xc01db9
0046e484 0bf8                     or        edi, eax
0046e486 313dfc3e0d01             xor       dword ptr [0x10d3efc], edi
0046e48c c6                       .byte     0xc6
0046e48d 05                       .byte     0x05
0046e48e f4                       hlt       
0046e48f 3e                       .byte     0x3e
