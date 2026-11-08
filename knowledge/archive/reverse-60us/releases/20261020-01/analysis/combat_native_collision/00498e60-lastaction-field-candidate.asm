00498e60 55                       push      ebp
00498e61 8bec                     mov       ebp, esp
00498e63 56                       push      esi
00498e64 8bf1                     mov       esi, ecx
00498e66 8b86c4010000             mov       eax, dword ptr [esi + 0x1c4]
00498e6c 57                       push      edi
00498e6d 8b7d08                   mov       edi, dword ptr [ebp + 8]
00498e70 85f8                     test      eax, edi
00498e72 743f                     je        0x498eb3
00498e74 53                       push      ebx
00498e75 8b9e04010000             mov       ebx, dword ptr [esi + 0x104]
00498e7b 85db                     test      ebx, ebx
00498e7d 7415                     je        0x498e94
00498e7f 8bcb                     mov       ecx, ebx
00498e81 e80aae5800               call      0xa23c90
00498e86 8b838c000000             mov       eax, dword ptr [ebx + 0x8c]
00498e8c 50                       push      eax
00498e8d 8bcb                     mov       ecx, ebx
00498e8f e8acf45800               call      0xa28340
00498e94 8b96c0010000             mov       edx, dword ptr [esi + 0x1c0]
00498e9a 8b86c4010000             mov       eax, dword ptr [esi + 0x1c4]
00498ea0 0bd7                     or        edx, edi
00498ea2 f7d7                     not       edi
00498ea4 23c7                     and       eax, edi
00498ea6 8996c0010000             mov       dword ptr [esi + 0x1c0], edx
00498eac 8986c4010000             mov       dword ptr [esi + 0x1c4], eax
00498eb2 5b                       pop       ebx
00498eb3 5f                       pop       edi
00498eb4 5e                       pop       esi
00498eb5 5d                       pop       ebp
00498eb6 c20400                   ret       4
00498eb9 cc                       int3      
00498eba cc                       int3      
00498ebb cc                       int3      
00498ebc cc                       int3      
00498ebd cc                       int3      
00498ebe cc                       int3      
00498ebf cc                       int3      
00498ec0 53                       push      ebx
00498ec1 33db                     xor       ebx, ebx
00498ec3 b801000000               mov       eax, 1
00498ec8 56                       push      esi
00498ec9 8bf1                     mov       esi, ecx
00498ecb 83c9ff                   or        ecx, 0xffffffff
00498ece 8986e0000000             mov       dword ptr [esi + 0xe0], eax
00498ed4 899ee4000000             mov       dword ptr [esi + 0xe4], ebx
00498eda 899ef8000000             mov       dword ptr [esi + 0xf8], ebx
00498ee0 899efc000000             mov       dword ptr [esi + 0xfc], ebx
00498ee6 899e00010000             mov       dword ptr [esi + 0x100], ebx
00498eec 899e04010000             mov       dword ptr [esi + 0x104], ebx
00498ef2 889e14010000             mov       byte ptr [esi + 0x114], bl
00498ef8 899e18010000             mov       dword ptr [esi + 0x118], ebx
00498efe 888684010000             mov       byte ptr [esi + 0x184], al
00498f04 889e85010000             mov       byte ptr [esi + 0x185], bl
00498f0a 889e86010000             mov       byte ptr [esi + 0x186], bl
00498f10 899e48010000             mov       dword ptr [esi + 0x148], ebx
00498f16 899e4c010000             mov       dword ptr [esi + 0x14c], ebx
00498f1c 899e50010000             mov       dword ptr [esi + 0x150], ebx
00498f22 899e54010000             mov       dword ptr [esi + 0x154], ebx
00498f28 898e88010000             mov       dword ptr [esi + 0x188], ecx
00498f2e 899e8c010000             mov       dword ptr [esi + 0x18c], ebx
00498f34 899e90010000             mov       dword ptr [esi + 0x190], ebx
00498f3a 888694010000             mov       byte ptr [esi + 0x194], al
00498f40 899eb0010000             mov       dword ptr [esi + 0x1b0], ebx
00498f46 899eb4010000             mov       dword ptr [esi + 0x1b4], ebx
00498f4c 899eb8010000             mov       dword ptr [esi + 0x1b8], ebx
00498f52 889ebc010000             mov       byte ptr [esi + 0x1bc], bl
00498f58 898ec0010000             mov       dword ptr [esi + 0x1c0], ecx
00498f5e 899ec4010000             mov       dword ptr [esi + 0x1c4], ebx
00498f64 889ec8010000             mov       byte ptr [esi + 0x1c8], bl
00498f6a 899ecc010000             mov       dword ptr [esi + 0x1cc], ebx
00498f70 899ed0010000             mov       dword ptr [esi + 0x1d0], ebx
00498f76 899ed4010000             mov       dword ptr [esi + 0x1d4], ebx
00498f7c 889ed8010000             mov       byte ptr [esi + 0x1d8], bl
00498f82 899edc010000             mov       dword ptr [esi + 0x1dc], ebx
00498f88 8886e0010000             mov       byte ptr [esi + 0x1e0], al
00498f8e c786e401000002000000     mov       dword ptr [esi + 0x1e4], 2
00498f98 899eec010000             mov       dword ptr [esi + 0x1ec], ebx
00498f9e 899ef0010000             mov       dword ptr [esi + 0x1f0], ebx
00498fa4 8886f4010000             mov       byte ptr [esi + 0x1f4], al
00498faa 88                       .byte     0x88
00498fab 9e                       sahf      
00498fac f5                       cmc       
00498fad 01                       .byte     0x01
