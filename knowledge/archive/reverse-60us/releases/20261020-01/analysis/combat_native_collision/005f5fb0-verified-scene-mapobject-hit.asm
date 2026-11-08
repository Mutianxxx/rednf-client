005f5fb0 55                       push      ebp
005f5fb1 8bec                     mov       ebp, esp
005f5fb3 6aff                     push      -1
005f5fb5 68ba75c600               push      0xc675ba
005f5fba 64a100000000             mov       eax, dword ptr fs:[0]
005f5fc0 50                       push      eax
005f5fc1 64892500000000           mov       dword ptr fs:[0], esp
005f5fc8 83ec14                   sub       esp, 0x14
005f5fcb 56                       push      esi
005f5fcc 8bf1                     mov       esi, ecx
005f5fce 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005f5fd1 8b01                     mov       eax, dword ptr [ecx]
005f5fd3 57                       push      edi
005f5fd4 ff909c010000             call      dword ptr [eax + 0x19c]
005f5fda 8bf8                     mov       edi, eax
005f5fdc 8d4f1c                   lea       ecx, [edi + 0x1c]
005f5fdf e87cc0e0ff               call      0x402060
005f5fe4 85c0                     test      eax, eax
005f5fe6 7524                     jne       0x5f600c
005f5fe8 8bcf                     mov       ecx, edi
005f5fea e8c1d3e3ff               call      0x4333b0
005f5fef d81da4d7e900             fcomp     dword ptr [0xe9d7a4]
005f5ff5 dfe0                     fnstsw    ax
005f5ff7 f6c441                   test      ah, 0x41
005f5ffa 7410                     je        0x5f600c
005f5ffc 8d4f08                   lea       ecx, [edi + 8]
005f5fff e85cc0e0ff               call      0x402060
005f6004 85c0                     test      eax, eax
005f6006 0f8ed3000000             jle       0x5f60df
005f600c 8b86e8080000             mov       eax, dword ptr [esi + 0x8e8]
005f6012 53                       push      ebx
005f6013 33db                     xor       ebx, ebx
005f6015 3bc3                     cmp       eax, ebx
005f6017 0f8494000000             je        0x5f60b1
005f601d 8b16                     mov       edx, dword ptr [esi]
005f601f 8bc8                     mov       ecx, eax
005f6021 8b39                     mov       edi, dword ptr [ecx]
005f6023 8bce                     mov       ecx, esi
005f6025 ff929c000000             call      dword ptr [edx + 0x9c]
005f602b 038678080000             add       eax, dword ptr [esi + 0x878]
005f6031 50                       push      eax
005f6032 8b06                     mov       eax, dword ptr [esi]
005f6034 8bce                     mov       ecx, esi
005f6036 ff9098000000             call      dword ptr [eax + 0x98]
005f603c 038674080000             add       eax, dword ptr [esi + 0x874]
005f6042 8b16                     mov       edx, dword ptr [esi]
005f6044 50                       push      eax
005f6045 8bce                     mov       ecx, esi
005f6047 ff9294000000             call      dword ptr [edx + 0x94]
005f604d 8b9670080000             mov       edx, dword ptr [esi + 0x870]
005f6053 8b8ee8080000             mov       ecx, dword ptr [esi + 0x8e8]
005f6059 03c2                     add       eax, edx
005f605b 50                       push      eax
005f605c ff5728                   call      dword ptr [edi + 0x28]
005f605f 8b8ee8080000             mov       ecx, dword ptr [esi + 0x8e8]
005f6065 8b01                     mov       eax, dword ptr [ecx]
005f6067 53                       push      ebx
005f6068 ff500c                   call      dword ptr [eax + 0xc]
005f606b 8b8ee8080000             mov       ecx, dword ptr [esi + 0x8e8]
005f6071 8b11                     mov       edx, dword ptr [ecx]
005f6073 8d45e0                   lea       eax, [ebp - 0x20]
005f6076 50                       push      eax
005f6077 ff525c                   call      dword ptr [edx + 0x5c]
005f607a 53                       push      ebx
005f607b 8d4de0                   lea       ecx, [ebp - 0x20]
005f607e 51                       push      ecx
005f607f 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
005f6085 53                       push      ebx
005f6086 6a02                     push      2
005f6088 56                       push      esi
005f6089 895dfc                   mov       dword ptr [ebp - 4], ebx
005f608c e8cf7ff1ff               call      0x50e060
005f6091 8b45e4                   mov       eax, dword ptr [ebp - 0x1c]
005f6094 3bc3                     cmp       eax, ebx
005f6096 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005f609d 7409                     je        0x5f60a8
005f609f 50                       push      eax
005f60a0 e8389f6000               call      0xbfffdd
005f60a5 83c404                   add       esp, 4
005f60a8 895de4                   mov       dword ptr [ebp - 0x1c], ebx
005f60ab 895de8                   mov       dword ptr [ebp - 0x18], ebx
005f60ae 895dec                   mov       dword ptr [ebp - 0x14], ebx
005f60b1 8dbef4080000             lea       edi, [esi + 0x8f4]
005f60b7 8bcf                     mov       ecx, edi
005f60b9 e832d04500               call      0xa530f0
005f60be 85c0                     test      eax, eax
005f60c0 741c                     je        0x5f60de
005f60c2 8b06                     mov       eax, dword ptr [esi]
005f60c4 53                       push      ebx
005f60c5 53                       push      ebx
005f60c6 6aff                     push      -1
005f60c8 8bcf                     mov       ecx, edi
005f60ca 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f60cd e81ed04500               call      0xa530f0
005f60d2 50                       push      eax
005f60d3 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
005f60d6 8bce                     mov       ecx, esi
005f60d8 ff900c010000             call      dword ptr [eax + 0x10c]
005f60de 5b                       pop       ebx
005f60df 8b5510                   mov       edx, dword ptr [ebp + 0x10]
005f60e2 8b450c                   mov       eax, dword ptr [ebp + 0xc]
005f60e5 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005f60e8 52                       push      edx
005f60e9 50                       push      eax
005f60ea 51                       push      ecx
005f60eb 8bce                     mov       ecx, esi
005f60ed e81e92eaff               call      0x49f310
005f60f2 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f60f5 5f                       pop       edi
005f60f6 5e                       pop       esi
005f60f7 64890d00000000           mov       dword ptr fs:[0], ecx
005f60fe 8be5                     mov       esp, ebp
005f6100 5d                       pop       ebp
005f6101 c20c00                   ret       0xc
