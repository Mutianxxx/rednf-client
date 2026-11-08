005f6e10 55                       push      ebp
005f6e11 8bec                     mov       ebp, esp
005f6e13 6aff                     push      -1
005f6e15 688676c600               push      0xc67686
005f6e1a 64a100000000             mov       eax, dword ptr fs:[0]
005f6e20 50                       push      eax
005f6e21 64892500000000           mov       dword ptr fs:[0], esp
005f6e28 51                       push      ecx
005f6e29 53                       push      ebx
005f6e2a 56                       push      esi
005f6e2b 57                       push      edi
005f6e2c 68e8010000               push      0x1e8
005f6e31 8bf1                     mov       esi, ecx
005f6e33 e818cee0ff               call      0x403c50
005f6e38 83c404                   add       esp, 4
005f6e3b 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f6e3e 85c0                     test      eax, eax
005f6e40 c745fc00000000           mov       dword ptr [ebp - 4], 0
005f6e47 7412                     je        0x5f6e5b
005f6e49 6a01                     push      1
005f6e4b 68581cd500               push      0xd51c58
005f6e50 8bc8                     mov       ecx, eax
005f6e52 e879c8e9ff               call      0x4936d0
005f6e57 8bd8                     mov       ebx, eax
005f6e59 eb02                     jmp       0x5f6e5d
005f6e5b 33db                     xor       ebx, ebx
005f6e5d a148280001               mov       eax, dword ptr [0x1002848]
005f6e62 85c0                     test      eax, eax
005f6e64 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005f6e6b 7448                     je        0x5f6eb5
005f6e6d 8b8054100000             mov       eax, dword ptr [eax + 0x1054]
005f6e73 85c0                     test      eax, eax
005f6e75 743e                     je        0x5f6eb5
005f6e77 8b4814                   mov       ecx, dword ptr [eax + 0x14]
005f6e7a 85c9                     test      ecx, ecx
005f6e7c 7437                     je        0x5f6eb5
005f6e7e 8bc1                     mov       eax, ecx
005f6e80 8b88b4000000             mov       ecx, dword ptr [eax + 0xb4]
005f6e86 85c9                     test      ecx, ecx
005f6e88 742b                     je        0x5f6eb5
005f6e8a e89119e9ff               call      0x488820
005f6e8f 85c0                     test      eax, eax
005f6e91 7c22                     jl        0x5f6eb5
005f6e93 83f804                   cmp       eax, 4
005f6e96 7d1d                     jge       0x5f6eb5
005f6e98 8b04856c7ef500           mov       eax, dword ptr [eax*4 + 0xf57e6c]
005f6e9f 83f864                   cmp       eax, 0x64
005f6ea2 8945f0                   mov       dword ptr [ebp - 0x10], eax
005f6ea5 740e                     je        0x5f6eb5
005f6ea7 db45f0                   fild      dword ptr [ebp - 0x10]
005f6eaa 51                       push      ecx
005f6eab 8bcb                     mov       ecx, ebx
005f6ead d91c24                   fstp      dword ptr [esp]
005f6eb0 e8bb2d4300               call      0xa29c70
005f6eb5 68fc010000               push      0x1fc
005f6eba e891cde0ff               call      0x403c50
005f6ebf 8bf8                     mov       edi, eax
005f6ec1 83c404                   add       esp, 4
005f6ec4 897df0                   mov       dword ptr [ebp - 0x10], edi
005f6ec7 85ff                     test      edi, edi
005f6ec9 c745fc01000000           mov       dword ptr [ebp - 4], 1
005f6ed0 7414                     je        0x5f6ee6
005f6ed2 6a00                     push      0
005f6ed4 6a01                     push      1
005f6ed6 53                       push      ebx
005f6ed7 8bcf                     mov       ecx, edi
005f6ed9 e8d2d6e9ff               call      0x4945b0
005f6ede c707c4ffcc00             mov       dword ptr [edi], 0xccffc4
005f6ee4 eb02                     jmp       0x5f6ee8
005f6ee6 33ff                     xor       edi, edi
005f6ee8 8b07                     mov       eax, dword ptr [edi]
005f6eea 6a02                     push      2
005f6eec 8bcf                     mov       ecx, edi
005f6eee 897df0                   mov       dword ptr [ebp - 0x10], edi
005f6ef1 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005f6ef8 ff5054                   call      dword ptr [eax + 0x54]
005f6efb 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
005f6f01 6a00                     push      0
005f6f03 6a00                     push      0
005f6f05 56                       push      esi
005f6f06 57                       push      edi
005f6f07 6a00                     push      0
005f6f09 6a02                     push      2
005f6f0b 56                       push      esi
005f6f0c e85f6ef1ff               call      0x50dd70
005f6f11 8b16                     mov       edx, dword ptr [esi]
005f6f13 8b1f                     mov       ebx, dword ptr [edi]
005f6f15 8bce                     mov       ecx, esi
005f6f17 ff92e4000000             call      dword ptr [edx + 0xe4]
005f6f1d 8bf8                     mov       edi, eax
005f6f1f 8b06                     mov       eax, dword ptr [esi]
005f6f21 8bce                     mov       ecx, esi
005f6f23 ff909c000000             call      dword ptr [eax + 0x9c]
005f6f29 8b16                     mov       edx, dword ptr [esi]
005f6f2b 03f8                     add       edi, eax
005f6f2d 57                       push      edi
005f6f2e 8bce                     mov       ecx, esi
005f6f30 ff9298000000             call      dword ptr [edx + 0x98]
005f6f36 50                       push      eax
005f6f37 8b06                     mov       eax, dword ptr [esi]
005f6f39 8bce                     mov       ecx, esi
005f6f3b ff9094000000             call      dword ptr [eax + 0x94]
005f6f41 8b7df0                   mov       edi, dword ptr [ebp - 0x10]
005f6f44 50                       push      eax
005f6f45 8bcf                     mov       ecx, edi
005f6f47 ff9388000000             call      dword ptr [ebx + 0x88]
005f6f4d 8b17                     mov       edx, dword ptr [edi]
005f6f4f 56                       push      esi
005f6f50 8bcf                     mov       ecx, edi
005f6f52 ff5248                   call      dword ptr [edx + 0x48]
005f6f55 8bc8                     mov       ecx, eax
005f6f57 e8249ff1ff               call      0x510e80
005f6f5c 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f6f5f 5f                       pop       edi
005f6f60 5e                       pop       esi
005f6f61 5b                       pop       ebx
005f6f62 64890d00000000           mov       dword ptr fs:[0], ecx
005f6f69 8be5                     mov       esp, ebp
005f6f6b 5d                       pop       ebp
005f6f6c c3                       ret       
005f6f6d cc                       int3      
005f6f6e cc                       int3      
005f6f6f cc                       int3      
005f6f70 56                       push      esi
005f6f71 57                       push      edi
005f6f72 8bf1                     mov       esi, ecx
005f6f74 e8e7fbffff               call      0x5f6b60
005f6f79 8d7e60                   lea       edi, [esi + 0x60]
005f6f7c 8bcf                     mov       ecx, edi
005f6f7e e87dff5000               call      0xb06f00
005f6f83 8b8e4c090000             mov       ecx, dword ptr [esi + 0x94c]
005f6f89 81c1f4010000             add       ecx, 0x1f4
005f6f8f 3bc8                     cmp       ecx, eax
005f6f91 7319                     jae       0x5f6fac
005f6f93 8bcf                     mov       ecx, edi
005f6f95 e866ff5000               call      0xb06f00
005f6f9a 8b16                     mov       edx, dword ptr [esi]
005f6f9c 5f                       pop       edi
005f6f9d 89864c090000             mov       dword ptr [esi + 0x94c], eax
005f6fa3 8bce                     mov       ecx, esi
005f6fa5 5e                       pop       esi
005f6fa6 ffa2a0010000             jmp       dword ptr [edx + 0x1a0]
005f6fac 5f                       pop       edi
005f6fad 5e                       pop       esi
005f6fae c3                       ret       
005f6faf cc                       int3      
005f6fb0 55                       push      ebp
005f6fb1 8bec                     mov       ebp, esp
005f6fb3 6aff                     push      -1
005f6fb5 689876c600               push      0xc67698
005f6fba 64a100000000             mov       eax, dword ptr fs:[0]
005f6fc0 50                       push      eax
005f6fc1 64892500000000           mov       dword ptr fs:[0], esp
005f6fc8 83ec10                   sub       esp, 0x10
005f6fcb 53                       push      ebx
005f6fcc 56                       push      esi
005f6fcd 8bf1                     mov       esi, ecx
005f6fcf 8b06                     mov       eax, dword ptr [esi]
005f6fd1 ff90f4000000             call      dword ptr [eax + 0xf4]
005f6fd7 8b8024010000             mov       eax, dword ptr [eax + 0x124]
005f6fdd 83f802                   cmp       eax, 2
005f6fe0 7d0a                     jge       0x5f6fec
005f6fe2 8b16                     mov       edx, dword ptr [esi]
005f6fe4 8bce                     mov       ecx, esi
005f6fe6 ff92a0010000             call      dword ptr [edx + 0x1a0]
005f6fec 8a8650090000             mov       al, byte ptr [esi + 0x950]
005f6ff2 33db                     xor       ebx, ebx
005f6ff4 3ac3                     cmp       al, bl
005f6ff6 7539                     jne       0x5f7031
005f6ff8 8b06                     mov       eax, dword ptr [esi]
005f6ffa 8bce                     mov       ecx, esi
005f6ffc ff90f4000000             call      dword ptr [eax + 0xf4]
005f7002 83b82401000006           cmp       dword ptr [eax + 0x124], 6
005f7009 7e1a                     jle       0x5f7025
005f700b 8b16                     mov       edx, dword ptr [esi]
005f700d 8bce                     mov       ecx, esi
005f700f ff92f4000000             call      dword ptr [edx + 0xf4]
005f7015 83b8240100000e           cmp       dword ptr [eax + 0x124], 0xe
005f701c 7d07                     jge       0x5f7025
005f701e c6865009000001           mov       byte ptr [esi + 0x950], 1
005f7025 389e50090000             cmp       byte ptr [esi + 0x950], bl
005f702b 0f8497000000             je        0x5f70c8
005f7031 8b8e4c090000             mov       ecx, dword ptr [esi + 0x94c]
005f7037 3bcb                     cmp       ecx, ebx
005f7039 0f8489000000             je        0x5f70c8
005f703f 8b01                     mov       eax, dword ptr [ecx]
005f7041 57                       push      edi
005f7042 53                       push      ebx
005f7043 ff500c                   call      dword ptr [eax + 0xc]
005f7046 8b8e4c090000             mov       ecx, dword ptr [esi + 0x94c]
005f704c 8b39                     mov       edi, dword ptr [ecx]
005f704e 8b16                     mov       edx, dword ptr [esi]
005f7050 8bce                     mov       ecx, esi
005f7052 ff929c000000             call      dword ptr [edx + 0x9c]
005f7058 50                       push      eax
005f7059 8b06                     mov       eax, dword ptr [esi]
005f705b 8bce                     mov       ecx, esi
005f705d ff9098000000             call      dword ptr [eax + 0x98]
005f7063 8b16                     mov       edx, dword ptr [esi]
005f7065 50                       push      eax
005f7066 8bce                     mov       ecx, esi
005f7068 ff9294000000             call      dword ptr [edx + 0x94]
005f706e 8b8e4c090000             mov       ecx, dword ptr [esi + 0x94c]
005f7074 50                       push      eax
005f7075 ff5728                   call      dword ptr [edi + 0x28]
005f7078 8b8e4c090000             mov       ecx, dword ptr [esi + 0x94c]
005f707e 8b01                     mov       eax, dword ptr [ecx]
005f7080 8d55e4                   lea       edx, [ebp - 0x1c]
005f7083 52                       push      edx
005f7084 ff505c                   call      dword ptr [eax + 0x5c]
005f7087 8b16                     mov       edx, dword ptr [esi]
005f7089 53                       push      ebx
005f708a 8d45e4                   lea       eax, [ebp - 0x1c]
005f708d 50                       push      eax
005f708e 53                       push      ebx
005f708f 6a02                     push      2
005f7091 56                       push      esi
005f7092 8bce                     mov       ecx, esi
005f7094 895dfc                   mov       dword ptr [ebp - 4], ebx
005f7097 ff525c                   call      dword ptr [edx + 0x5c]
005f709a 8bc8                     mov       ecx, eax
005f709c e8bf6ff1ff               call      0x50e060
005f70a1 8b45e8                   mov       eax, dword ptr [ebp - 0x18]
005f70a4 3bc3                     cmp       eax, ebx
005f70a6 889e50090000             mov       byte ptr [esi + 0x950], bl
005f70ac c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005f70b3 5f                       pop       edi
005f70b4 7409                     je        0x5f70bf
005f70b6 50                       push      eax
005f70b7 e8218f6000               call      0xbfffdd
005f70bc 83c404                   add       esp, 4
005f70bf 895de8                   mov       dword ptr [ebp - 0x18], ebx
005f70c2 895dec                   mov       dword ptr [ebp - 0x14], ebx
005f70c5 895df0                   mov       dword ptr [ebp - 0x10], ebx
005f70c8 8bce                     mov       ecx, esi
005f70ca e891faffff               call      0x5f6b60
005f70cf 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005f70d2 5e                       pop       esi
005f70d3 5b                       pop       ebx
005f70d4 64890d00000000           mov       dword ptr fs:[0], ecx
005f70db 8be5                     mov       esp, ebp
005f70dd 5d                       pop       ebp
005f70de c3                       ret       
005f70df cc                       int3      
005f70e0 e97bfaffff               jmp       0x5f6b60
005f70e5 cc                       int3      
005f70e6 cc                       int3      
005f70e7 cc                       int3      
005f70e8 cc                       int3      
005f70e9 cc                       int3      
005f70ea cc                       int3      
005f70eb cc                       int3      
005f70ec cc                       int3      
005f70ed cc                       int3      
005f70ee cc                       int3      
005f70ef cc                       int3      
005f70f0 55                       push      ebp
005f70f1 8bec                     mov       ebp, esp
005f70f3 51                       push      ecx
005f70f4 53                       push      ebx
005f70f5 56                       push      esi
005f70f6 8bf1                     mov       esi, ecx
005f70f8 8b864c090000             mov       eax, dword ptr [esi + 0x94c]
005f70fe 3b8650090000             cmp       eax, dword ptr [esi + 0x950]
005f7104 750c                     jne       0x5f7112
005f7106 8b16                     mov       edx, dword ptr [esi]
005f7108 6a00                     push      0
005f710a 8bce                     mov       ecx, esi
005f710c ff9264010000             call      dword ptr [edx + 0x164]
005f7112 8b06                     mov       eax, dword ptr [esi]
005f7114 8bce                     mov       ecx, esi
005f7116 ff90f4000000             call      dword ptr [eax + 0xf4]
005f711c 8bd8                     mov       ebx, eax
005f711e 83bb2401000003           cmp       dword ptr [ebx + 0x124], 3
005f7125 7e50                     jle       0x5f7177
005f7127 8b16                     mov       edx, dword ptr [esi]
005f7129 57                       push      edi
005f712a 8bce                     mov       ecx, esi
005f712c ff928c010000             call      dword ptr [edx + 0x18c]
005f7132 8bf8                     mov       edi, eax
005f7134 8b0f                     mov       ecx, dword ptr [edi]
005f7136 8b8324010000             mov       eax, dword ptr [ebx + 0x124]
005f713c 6a01                     push      1
005f713e 6a02                     push      2
005f7140 894dfc                   mov       dword ptr [ebp - 4], ecx
005f7143 50                       push      eax
005f7144 8bcb                     mov       ecx, ebx
005f7146 e845eb4200               call      0xa25c90
005f714b 50                       push      eax
005f714c e88fd14200               call      0xa242e0
005f7151 83c40c                   add       esp, 0xc
005f7154 50                       push      eax
005f7155 8b06                     mov       eax, dword ptr [esi]
005f7157 8bce                     mov       ecx, esi
005f7159 ff9098000000             call      dword ptr [eax + 0x98]
005f715f 8b16                     mov       edx, dword ptr [esi]
005f7161 50                       push      eax
005f7162 8bce                     mov       ecx, esi
005f7164 ff9294000000             call      dword ptr [edx + 0x94]
005f716a 50                       push      eax
005f716b 8b45fc                   mov       eax, dword ptr [ebp - 4]
005f716e 8bcf                     mov       ecx, edi
005f7170 ff9080000000             call      dword ptr [eax + 0x80]
005f7176 5f                       pop       edi
005f7177 8bce                     mov       ecx, esi
005f7179 e8e2f9ffff               call      0x5f6b60
005f717e 5e                       pop       esi
005f717f 5b                       pop       ebx
005f7180 8be5                     mov       esp, ebp
005f7182 5d                       pop       ebp
005f7183 c3                       ret       
005f7184 cc                       int3      
005f7185 cc                       int3      
005f7186 cc                       int3      
005f7187 cc                       int3      
005f7188 cc                       int3      
005f7189 cc                       int3      
005f718a cc                       int3      
005f718b cc                       int3      
005f718c cc                       int3      
005f718d cc                       int3      
005f718e cc                       int3      
005f718f cc                       int3      
005f7190 56                       push      esi
005f7191 8bf1                     mov       esi, ecx
005f7193 57                       push      edi
005f7194 8dbe98090000             lea       edi, [esi + 0x998]
005f719a 8bcf                     mov       ecx, edi
005f719c e85ffd5000               call      0xb06f00
005f71a1 3db80b0000               cmp       eax, 0xbb8
005f71a6 7e1c                     jle       0x5f71c4
005f71a8 8b06                     mov       eax, dword ptr [esi]
005f71aa 8bce                     mov       ecx, esi
005f71ac ff90a0010000             call      dword ptr [eax + 0x1a0]
005f71b2 8bcf                     mov       ecx, edi
005f71b4 e837dde0ff               call      0x404ef0
005f71b9 6a00                     push      0
005f71bb 6a00                     push      0
005f71bd 8bcf                     mov       ecx, edi
005f71bf e89cfd5000               call      0xb06f60
005f71c4 8b16                     mov       edx, dword ptr [esi]
005f71c6 8bce                     mov       ecx, esi
005f71c8 ff92f4000000             call      dword ptr [edx + 0xf4]
005f71ce 85c0                     test      eax, eax
005f71d0 741b                     je        0x5f71ed
005f71d2 83b82401000004           cmp       dword ptr [eax + 0x124], 4
005f71d9 7e12                     jle       0x5f71ed
005f71db 8b3e                     mov       edi, dword ptr [esi]
005f71dd 6a00                     push      0
005f71df 8bce                     mov       ecx, esi
005f71e1 ff577c                   call      dword ptr [edi + 0x7c]
005f71e4 50                       push      eax
005f71e5 8bce                     mov       ecx, esi
005f71e7 ff97f0000000             call      dword ptr [edi + 0xf0]
005f71ed 5f                       pop       edi
005f71ee 8bce                     mov       ecx, esi
005f71f0 5e                       pop       esi
005f71f1 e96af9ffff               jmp       0x5f6b60
005f71f6 cc                       int3      
005f71f7 cc                       int3      
005f71f8 cc                       int3      
005f71f9 cc                       int3      
005f71fa cc                       int3      
005f71fb cc                       int3      
005f71fc cc                       int3      
005f71fd cc                       int3      
005f71fe cc                       int3      
005f71ff cc                       int3      
005f7200 56                       push      esi
005f7201 8bf1                     mov       esi, ecx
005f7203 e898f1ffff               call      0x5f63a0
005f7208 8bce                     mov       ecx, esi
005f720a 5e                       pop       esi
005f720b e950f9ffff               jmp       0x5f6b60
005f7210 56                       push      esi
005f7211 8bf1                     mov       esi, ecx
005f7213 8a864d090000             mov       al, byte ptr [esi + 0x94d]
005f7219 84c0                     test      al, al
005f721b 750b                     jne       0x5f7228
005f721d e8fee7ffff               call      0x5f5a20
005f7222 88864d090000             mov       byte ptr [esi + 0x94d], al
005f7228 8a864c090000             mov       al, byte ptr [esi + 0x94c]
005f722e 84c0                     test      al, al
005f7230 7549                     jne       0x5f727b
005f7232 8a864d090000             mov       al, byte ptr [esi + 0x94d]
005f7238 84c0                     test      al, al
005f723a 7435                     je        0x5f7271
005f723c 57                       push      edi
005f723d 8dbe50090000             lea       edi, [esi + 0x950]
005f7243 8bcf                     mov       ecx, edi
005f7245 e8b6fc5000               call      0xb06f00
005f724a 3db80b0000               cmp       eax, 0xbb8
005f724f 7e1f                     jle       0x5f7270
005f7251 8bce                     mov       ecx, esi
005f7253 e858e1ffff               call      0x5f53b0
005f7258 8bcf                     mov       ecx, edi
005f725a 88864c090000             mov       byte ptr [esi + 0x94c], al
005f7260 e88bdce0ff               call      0x404ef0
005f7265 6a00                     push      0
005f7267 6a00                     push      0
005f7269 8bcf                     mov       ecx, edi
005f726b e8f0fc5000               call      0xb06f60
005f7270 5f                       pop       edi
005f7271 8a864c090000             mov       al, byte ptr [esi + 0x94c]
005f7277 84c0                     test      al, al
005f7279 747f                     je        0x5f72fa
005f727b 8a864f090000             mov       al, byte ptr [esi + 0x94f]
005f7281 84c0                     test      al, al
005f7283 7575                     jne       0x5f72fa
005f7285 8b8620010000             mov       eax, dword ptr [esi + 0x120]
005f728b 8b00                     mov       eax, dword ptr [eax]
005f728d 8b16                     mov       edx, dword ptr [esi]
005f728f 50                       push      eax
005f7290 8bce                     mov       ecx, esi
005f7292 ff92fc000000             call      dword ptr [edx + 0xfc]
005f7298 8b8620010000             mov       eax, dword ptr [esi + 0x120]
005f729e 8b16                     mov       edx, dword ptr [esi]
005f72a0 6a01                     push      1
005f72a2 6a00                     push      0
005f72a4 6a00                     push      0
005f72a6 6a00                     push      0
005f72a8 6a00                     push      0
005f72aa 6a00                     push      0
005f72ac 6a00                     push      0
005f72ae 83c004                   add       eax, 4
005f72b1 8b00                     mov       eax, dword ptr [eax]
005f72b3 6a00                     push      0
005f72b5 50                       push      eax
005f72b6 6a64                     push      0x64
005f72b8 8bce                     mov       ecx, esi
005f72ba ff92f8000000             call      dword ptr [edx + 0xf8]
005f72c0 8b8620010000             mov       eax, dword ptr [esi + 0x120]
005f72c6 8b16                     mov       edx, dword ptr [esi]
005f72c8 6a01                     push      1
005f72ca 6a00                     push      0
005f72cc 6a00                     push      0
005f72ce 6a00                     push      0
005f72d0 6a00                     push      0
005f72d2 6a00                     push      0
005f72d4 6a00                     push      0
005f72d6 83c008                   add       eax, 8
005f72d9 8b00                     mov       eax, dword ptr [eax]
005f72db 6a00                     push      0
005f72dd 50                       push      eax
005f72de 68c8000000               push      0xc8
005f72e3 8bce                     mov       ecx, esi
005f72e5 ff92f8000000             call      dword ptr [edx + 0xf8]
005f72eb c6864f09000001           mov       byte ptr [esi + 0x94f], 1
005f72f2 8bce                     mov       ecx, esi
005f72f4 5e                       pop       esi
005f72f5 e966f8ffff               jmp       0x5f6b60
005f72fa 8a864e090000             mov       al, byte ptr [esi + 0x94e]
005f7300 84c0                     test      al, al
005f7302 752c                     jne       0x5f7330
005f7304 8b8620010000             mov       eax, dword ptr [esi + 0x120]
005f730a 8b00                     mov       eax, dword ptr [eax]
005f730c 8b16                     mov       edx, dword ptr [esi]
005f730e 6a01                     push      1
005f7310 6a00                     push      0
005f7312 6a00                     push      0
005f7314 6a00                     push      0
005f7316 6a00                     push      0
005f7318 6a00                     push      0
005f731a 6a00                     push      0
005f731c 6a00                     push      0
005f731e 50                       push      eax
005f731f 6a64                     push      0x64
005f7321 8bce                     mov       ecx, esi
005f7323 ff92f8000000             call      dword ptr [edx + 0xf8]
005f7329 c6864e09000001           mov       byte ptr [esi + 0x94e], 1
005f7330 8bce                     mov       ecx, esi
005f7332 5e                       pop       esi
005f7333 e928f8ffff               jmp       0x5f6b60
005f7338 cc                       int3      
005f7339 cc                       int3      
005f733a cc                       int3      
005f733b cc                       int3      
005f733c cc                       int3      
005f733d cc                       int3      
005f733e cc                       int3      
005f733f cc                       int3      
