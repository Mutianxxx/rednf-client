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
005f6104 cc                       int3      
005f6105 cc                       int3      
005f6106 cc                       int3      
005f6107 cc                       int3      
005f6108 cc                       int3      
005f6109 cc                       int3      
005f610a cc                       int3      
005f610b cc                       int3      
005f610c cc                       int3      
005f610d cc                       int3      
005f610e cc                       int3      
005f610f cc                       int3      
005f6110 55                       push      ebp
005f6111 8bec                     mov       ebp, esp
005f6113 56                       push      esi
005f6114 8b7508                   mov       esi, dword ptr [ebp + 8]
005f6117 85f6                     test      esi, esi
005f6119 57                       push      edi
005f611a 8bf9                     mov       edi, ecx
005f611c 7418                     je        0x5f6136
005f611e 8b06                     mov       eax, dword ptr [esi]
005f6120 8bce                     mov       ecx, esi
005f6122 ff909c010000             call      dword ptr [eax + 0x19c]
005f6128 83781801                 cmp       dword ptr [eax + 0x18], 1
005f612c 7508                     jne       0x5f6136
005f612e 5f                       pop       edi
005f612f 33c0                     xor       eax, eax
005f6131 5e                       pop       esi
005f6132 5d                       pop       ebp
005f6133 c20c00                   ret       0xc
005f6136 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
005f6139 8b550c                   mov       edx, dword ptr [ebp + 0xc]
005f613c 51                       push      ecx
005f613d 52                       push      edx
005f613e 56                       push      esi
005f613f 8bcf                     mov       ecx, edi
005f6141 e86afeffff               call      0x5f5fb0
005f6146 5f                       pop       edi
005f6147 5e                       pop       esi
005f6148 5d                       pop       ebp
005f6149 c20c00                   ret       0xc
005f614c cc                       int3      
005f614d cc                       int3      
005f614e cc                       int3      
005f614f cc                       int3      
005f6150 55                       push      ebp
005f6151 8bec                     mov       ebp, esp
005f6153 ff814c090000             inc       dword ptr [ecx + 0x94c]
005f6159 5d                       pop       ebp
005f615a e951feffff               jmp       0x5f5fb0
005f615f cc                       int3      
005f6160 55                       push      ebp
005f6161 8bec                     mov       ebp, esp
005f6163 5d                       pop       ebp
005f6164 e947feffff               jmp       0x5f5fb0
005f6169 cc                       int3      
005f616a cc                       int3      
005f616b cc                       int3      
005f616c cc                       int3      
005f616d cc                       int3      
005f616e cc                       int3      
005f616f cc                       int3      
005f6170 55                       push      ebp
005f6171 8bec                     mov       ebp, esp
005f6173 6aff                     push      -1
005f6175 68cc75c600               push      0xc675cc
005f617a 64a100000000             mov       eax, dword ptr fs:[0]
005f6180 50                       push      eax
005f6181 64892500000000           mov       dword ptr fs:[0], esp
005f6188 83ec10                   sub       esp, 0x10
005f618b 56                       push      esi
005f618c 8bf1                     mov       esi, ecx
005f618e 8b964c090000             mov       edx, dword ptr [esi + 0x94c]
005f6194 8b8e68090000             mov       ecx, dword ptr [esi + 0x968]
005f619a 42                       inc       edx
005f619b 89964c090000             mov       dword ptr [esi + 0x94c], edx
005f61a1 8b01                     mov       eax, dword ptr [ecx]
005f61a3 ff5040                   call      dword ptr [eax + 0x40]
005f61a6 84c0                     test      al, al
005f61a8 740d                     je        0x5f61b7
005f61aa 8b8e68090000             mov       ecx, dword ptr [esi + 0x968]
005f61b0 8b11                     mov       edx, dword ptr [ecx]
005f61b2 6a00                     push      0
005f61b4 ff520c                   call      dword ptr [edx + 0xc]
005f61b7 8b8668090000             mov       eax, dword ptr [esi + 0x968]
005f61bd 8b16                     mov       edx, dword ptr [esi]
005f61bf 57                       push      edi
005f61c0 8b38                     mov       edi, dword ptr [eax]
005f61c2 8bce                     mov       ecx, esi
005f61c4 ff929c000000             call      dword ptr [edx + 0x9c]
005f61ca 50                       push      eax
005f61cb 8b06                     mov       eax, dword ptr [esi]
005f61cd 8bce                     mov       ecx, esi
005f61cf ff9098000000             call      dword ptr [eax + 0x98]
005f61d5 8b16                     mov       edx, dword ptr [esi]
005f61d7 83e81e                   sub       eax, 0x1e
005f61da 50                       push      eax
005f61db 8bce                     mov       ecx, esi
005f61dd ff9294000000             call      dword ptr [edx + 0x94]
005f61e3 8b8e68090000             mov       ecx, dword ptr [esi + 0x968]
005f61e9 50                       push      eax
005f61ea ff5728                   call      dword ptr [edi + 0x28]
005f61ed 8b8e68090000             mov       ecx, dword ptr [esi + 0x968]
005f61f3 8b01                     mov       eax, dword ptr [ecx]
005f61f5 8d55e4                   lea       edx, [ebp - 0x1c]
005f61f8 52                       push      edx
005f61f9 ff505c                   call      dword ptr [eax + 0x5c]
005f61fc 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
005f6202 6a00                     push      0
005f6204 8d45e4                   lea       eax, [ebp - 0x1c]
005f6207 50                       push      eax
005f6208 6a00                     push      0
005f620a 6a02                     push      2
005f620c 56                       push      esi
005f620d c745fc00000000           mov       dword ptr [ebp - 4], 0
005f6214 e8477ef1ff               call      0x50e060
005f6219 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
005f621c 8b550c                   mov       edx, dword ptr [ebp + 0xc]
005f621f 8b4508                   mov       eax, dword ptr [ebp + 8]
005f6222 51                       push      ecx
005f6223 52                       push      edx
005f6224 50                       push      eax
005f6225 8bce                     mov       ecx, esi
005f6227 e884fdffff               call      0x5f5fb0
005f622c 8bf0                     mov       esi, eax
005f622e 8b45e8                   mov       eax, dword ptr [ebp - 0x18]
005f6231 85c0                     test      eax, eax
005f6233 5f                       pop       edi
005f6234 7409                     je        0x5f623f
005f6236 50                       push      eax
005f6237 e8a19d6000               call      0xbfffdd
005f623c 83c404                   add       esp, 4
005f623f 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f6242 8bc6                     mov       eax, esi
005f6244 5e                       pop       esi
005f6245 64890d00000000           mov       dword ptr fs:[0], ecx
005f624c 8be5                     mov       esp, ebp
005f624e 5d                       pop       ebp
005f624f c20c00                   ret       0xc
005f6252 cc                       int3      
005f6253 cc                       int3      
005f6254 cc                       int3      
005f6255 cc                       int3      
005f6256 cc                       int3      
005f6257 cc                       int3      
005f6258 cc                       int3      
005f6259 cc                       int3      
005f625a cc                       int3      
005f625b cc                       int3      
005f625c cc                       int3      
005f625d cc                       int3      
005f625e cc                       int3      
005f625f cc                       int3      
