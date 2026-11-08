005f5e80 55                       push      ebp
005f5e81 8bec                     mov       ebp, esp
005f5e83 6aff                     push      -1
005f5e85 68a875c600               push      0xc675a8
005f5e8a 64a100000000             mov       eax, dword ptr fs:[0]
005f5e90 50                       push      eax
005f5e91 64892500000000           mov       dword ptr fs:[0], esp
005f5e98 83ec14                   sub       esp, 0x14
005f5e9b 53                       push      ebx
005f5e9c 56                       push      esi
005f5e9d 8bf1                     mov       esi, ecx
005f5e9f 8a8689080000             mov       al, byte ptr [esi + 0x889]
005f5ea5 33db                     xor       ebx, ebx
005f5ea7 3ac3                     cmp       al, bl
005f5ea9 0f85e3000000             jne       0x5f5f92
005f5eaf 8b86ec080000             mov       eax, dword ptr [esi + 0x8ec]
005f5eb5 3bc3                     cmp       eax, ebx
005f5eb7 57                       push      edi
005f5eb8 0f8490000000             je        0x5f5f4e
005f5ebe 8b16                     mov       edx, dword ptr [esi]
005f5ec0 8b38                     mov       edi, dword ptr [eax]
005f5ec2 ff929c000000             call      dword ptr [edx + 0x9c]
005f5ec8 038678080000             add       eax, dword ptr [esi + 0x878]
005f5ece 50                       push      eax
005f5ecf 8b06                     mov       eax, dword ptr [esi]
005f5ed1 8bce                     mov       ecx, esi
005f5ed3 ff9098000000             call      dword ptr [eax + 0x98]
005f5ed9 038674080000             add       eax, dword ptr [esi + 0x874]
005f5edf 8b16                     mov       edx, dword ptr [esi]
005f5ee1 50                       push      eax
005f5ee2 8bce                     mov       ecx, esi
005f5ee4 ff9294000000             call      dword ptr [edx + 0x94]
005f5eea 8b9670080000             mov       edx, dword ptr [esi + 0x870]
005f5ef0 8b8eec080000             mov       ecx, dword ptr [esi + 0x8ec]
005f5ef6 03c2                     add       eax, edx
005f5ef8 50                       push      eax
005f5ef9 ff5728                   call      dword ptr [edi + 0x28]
005f5efc 8b8eec080000             mov       ecx, dword ptr [esi + 0x8ec]
005f5f02 8b01                     mov       eax, dword ptr [ecx]
005f5f04 53                       push      ebx
005f5f05 ff500c                   call      dword ptr [eax + 0xc]
005f5f08 8b8eec080000             mov       ecx, dword ptr [esi + 0x8ec]
005f5f0e 8b11                     mov       edx, dword ptr [ecx]
005f5f10 8d45e0                   lea       eax, [ebp - 0x20]
005f5f13 50                       push      eax
005f5f14 ff525c                   call      dword ptr [edx + 0x5c]
005f5f17 53                       push      ebx
005f5f18 8d4de0                   lea       ecx, [ebp - 0x20]
005f5f1b 51                       push      ecx
005f5f1c 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
005f5f22 53                       push      ebx
005f5f23 6a02                     push      2
005f5f25 56                       push      esi
005f5f26 895dfc                   mov       dword ptr [ebp - 4], ebx
005f5f29 e83281f1ff               call      0x50e060
005f5f2e 8b45e4                   mov       eax, dword ptr [ebp - 0x1c]
005f5f31 3bc3                     cmp       eax, ebx
005f5f33 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005f5f3a 7409                     je        0x5f5f45
005f5f3c 50                       push      eax
005f5f3d e89ba06000               call      0xbfffdd
005f5f42 83c404                   add       esp, 4
005f5f45 895de4                   mov       dword ptr [ebp - 0x1c], ebx
005f5f48 895de8                   mov       dword ptr [ebp - 0x18], ebx
005f5f4b 895dec                   mov       dword ptr [ebp - 0x14], ebx
005f5f4e 8dbef8080000             lea       edi, [esi + 0x8f8]
005f5f54 8bcf                     mov       ecx, edi
005f5f56 e895d14500               call      0xa530f0
005f5f5b 85c0                     test      eax, eax
005f5f5d 741c                     je        0x5f5f7b
005f5f5f 8b06                     mov       eax, dword ptr [esi]
005f5f61 53                       push      ebx
005f5f62 53                       push      ebx
005f5f63 6aff                     push      -1
005f5f65 8bcf                     mov       ecx, edi
005f5f67 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f5f6a e881d14500               call      0xa530f0
005f5f6f 50                       push      eax
005f5f70 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
005f5f73 8bce                     mov       ecx, esi
005f5f75 ff900c010000             call      dword ptr [eax + 0x10c]
005f5f7b 8bce                     mov       ecx, esi
005f5f7d e80e61eaff               call      0x49c090
005f5f82 84c0                     test      al, al
005f5f84 5f                       pop       edi
005f5f85 740b                     je        0x5f5f92
005f5f87 8b16                     mov       edx, dword ptr [esi]
005f5f89 53                       push      ebx
005f5f8a 8bce                     mov       ecx, esi
005f5f8c ff9264010000             call      dword ptr [edx + 0x164]
005f5f92 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f5f95 5e                       pop       esi
005f5f96 5b                       pop       ebx
005f5f97 64890d00000000           mov       dword ptr fs:[0], ecx
005f5f9e 8be5                     mov       esp, ebp
005f5fa0 5d                       pop       ebp
005f5fa1 c20400                   ret       4
005f5fa4 cc                       int3      
005f5fa5 cc                       int3      
005f5fa6 cc                       int3      
005f5fa7 cc                       int3      
005f5fa8 cc                       int3      
005f5fa9 cc                       int3      
005f5faa cc                       int3      
005f5fab cc                       int3      
005f5fac cc                       int3      
005f5fad cc                       int3      
005f5fae cc                       int3      
005f5faf cc                       int3      
