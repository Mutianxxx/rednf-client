00a0bb30 890d00000000             mov       dword ptr [0], ecx
00a0bb36 8be5                     mov       esp, ebp
00a0bb38 5d                       pop       ebp
00a0bb39 c3                       ret       
00a0bb3a cc                       int3      
00a0bb3b cc                       int3      
00a0bb3c cc                       int3      
00a0bb3d cc                       int3      
00a0bb3e cc                       int3      
00a0bb3f cc                       int3      
00a0bb40 56                       push      esi
00a0bb41 57                       push      edi
00a0bb42 8bf9                     mov       edi, ecx
00a0bb44 8d7764                   lea       esi, [edi + 0x64]
00a0bb47 8bce                     mov       ecx, esi
00a0bb49 e8b2b30f00               call      0xb06f00
00a0bb4e 3d20030000               cmp       eax, 0x320
00a0bb53 7c23                     jl        0xa0bb78
00a0bb55 6a10                     push      0x10
00a0bb57 e894bea3ff               call      0x4479f0
00a0bb5c 83c404                   add       esp, 4
00a0bb5f 8bce                     mov       ecx, esi
00a0bb61 c7475800000000           mov       dword ptr [edi + 0x58], 0
00a0bb68 e883939fff               call      0x404ef0
00a0bb6d 6a00                     push      0
00a0bb6f 6a00                     push      0
00a0bb71 8bce                     mov       ecx, esi
00a0bb73 e8e8b30f00               call      0xb06f60
00a0bb78 5f                       pop       edi
00a0bb79 5e                       pop       esi
00a0bb7a c3                       ret       
00a0bb7b cc                       int3      
00a0bb7c cc                       int3      
00a0bb7d cc                       int3      
00a0bb7e cc                       int3      
00a0bb7f cc                       int3      
00a0bb80 55                       push      ebp
00a0bb81 8bec                     mov       ebp, esp
00a0bb83 6aff                     push      -1
00a0bb85 6886d4c800               push      0xc8d486
00a0bb8a 64a100000000             mov       eax, dword ptr fs:[0]
00a0bb90 50                       push      eax
00a0bb91 64892500000000           mov       dword ptr fs:[0], esp
00a0bb98 51                       push      ecx
00a0bb99 53                       push      ebx
00a0bb9a 56                       push      esi
00a0bb9b 8bf1                     mov       esi, ecx
00a0bb9d 8975f0                   mov       dword ptr [ebp - 0x10], esi
00a0bba0 e8fb140000               call      0xa0d0a0
00a0bba5 33db                     xor       ebx, ebx
00a0bba7 8d4e6c                   lea       ecx, [esi + 0x6c]
00a0bbaa 895dfc                   mov       dword ptr [ebp - 4], ebx
00a0bbad c706f431e400             mov       dword ptr [esi], 0xe431f4
00a0bbb3 e8a8979fff               call      0x405360
00a0bbb8 8d8eb4000000             lea       ecx, [esi + 0xb4]
00a0bbbe c645fc01                 mov       byte ptr [ebp - 4], 1
00a0bbc2 e8e9b6a5ff               call      0x4672b0
00a0bbc7 8d8ee4000000             lea       ecx, [esi + 0xe4]
00a0bbcd c645fc02                 mov       byte ptr [ebp - 4], 2
00a0bbd1 e8dab6a5ff               call      0x4672b0
00a0bbd6 8d8e1c010000             lea       ecx, [esi + 0x11c]
00a0bbdc c645fc03                 mov       byte ptr [ebp - 4], 3
00a0bbe0 e8ab859fff               call      0x404190
00a0bbe5 8d8e24010000             lea       ecx, [esi + 0x124]
00a0bbeb c645fc04                 mov       byte ptr [ebp - 4], 4
00a0bbef e89c859fff               call      0x404190
00a0bbf4 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00a0bbf7 895e64                   mov       dword ptr [esi + 0x64], ebx
00a0bbfa 895e58                   mov       dword ptr [esi + 0x58], ebx
00a0bbfd 895e5c                   mov       dword ptr [esi + 0x5c], ebx
00a0bc00 889eac000000             mov       byte ptr [esi + 0xac], bl
00a0bc06 899eb0000000             mov       dword ptr [esi + 0xb0], ebx
00a0bc0c 899e14010000             mov       dword ptr [esi + 0x114], ebx
00a0bc12 889e2c010000             mov       byte ptr [esi + 0x12c], bl
00a0bc18 c78618010000ffffffff     mov       dword ptr [esi + 0x118], 0xffffffff
00a0bc22 8bc6                     mov       eax, esi
00a0bc24 5e                       pop       esi
00a0bc25 5b                       pop       ebx
00a0bc26 64890d00000000           mov       dword ptr fs:[0], ecx
00a0bc2d 8be5                     mov       esp, ebp
00a0bc2f 5d                       pop       ebp
00a0bc30 c3                       ret       
00a0bc31 cc                       int3      
00a0bc32 cc                       int3      
00a0bc33 cc                       int3      
00a0bc34 cc                       int3      
00a0bc35 cc                       int3      
00a0bc36 cc                       int3      
00a0bc37 cc                       int3      
00a0bc38 cc                       int3      
00a0bc39 cc                       int3      
00a0bc3a cc                       int3      
00a0bc3b cc                       int3      
00a0bc3c cc                       int3      
00a0bc3d cc                       int3      
00a0bc3e cc                       int3      
00a0bc3f cc                       int3      
00a0bc40 55                       push      ebp
00a0bc41 8bec                     mov       ebp, esp
00a0bc43 6aff                     push      -1
00a0bc45 68d0d4c800               push      0xc8d4d0
00a0bc4a 64a100000000             mov       eax, dword ptr fs:[0]
00a0bc50 50                       push      eax
00a0bc51 64892500000000           mov       dword ptr fs:[0], esp
00a0bc58 83ec1c                   sub       esp, 0x1c
00a0bc5b 53                       push      ebx
00a0bc5c 56                       push      esi
00a0bc5d 57                       push      edi
00a0bc5e 8bf1                     mov       esi, ecx
00a0bc60 e84baa1000               call      0xb166b0
00a0bc65 8bf8                     mov       edi, eax
00a0bc67 e844aa1000               call      0xb166b0
00a0bc6c 0fafc7                   imul      eax, edi
00a0bc6f 99                       cdq       
00a0bc70 b98d000000               mov       ecx, 0x8d
00a0bc75 f7f9                     idiv      ecx
00a0bc77 8d4de0                   lea       ecx, [ebp - 0x20]
00a0bc7a 8955f0                   mov       dword ptr [ebp - 0x10], edx
00a0bc7d 8d55f0                   lea       edx, [ebp - 0x10]
00a0bc80 52                       push      edx
00a0bc81 e8ca649fff               call      0x402150
00a0bc86 33db                     xor       ebx, ebx
00a0bc88 895dfc                   mov       dword ptr [ebp - 4], ebx
00a0bc8b e820aa1000               call      0xb166b0
00a0bc90 8bf8                     mov       edi, eax
00a0bc92 e819aa1000               call      0xb166b0
00a0bc97 0fafc7                   imul      eax, edi
00a0bc9a 99                       cdq       
00a0bc9b b983000000               mov       ecx, 0x83
00a0bca0 f7f9                     idiv      ecx
00a0bca2 8d4de8                   lea       ecx, [ebp - 0x18]
00a0bca5 8955f0                   mov       dword ptr [ebp - 0x10], edx
00a0bca8 8d55f0                   lea       edx, [ebp - 0x10]
00a0bcab 52                       push      edx
00a0bcac e89f649fff               call      0x402150
00a0bcb1 8d4de0                   lea       ecx, [ebp - 0x20]
00a0bcb4 c645fc01                 mov       byte ptr [ebp - 4], 1
00a0bcb8 e8a3639fff               call      0x402060
00a0bcbd 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00a0bcc3 83c05f                   add       eax, 0x5f
00a0bcc6 8945f0                   mov       dword ptr [ebp - 0x10], eax
00a0bcc9 db45f0                   fild      dword ptr [ebp - 0x10]
00a0bccc a1d8012101               mov       eax, dword ptr [0x12101d8]
00a0bcd1 8b4844                   mov       ecx, dword ptr [eax + 0x44]
00a0bcd4 8b4608                   mov       eax, dword ptr [esi + 8]
00a0bcd7 d95df0                   fstp      dword ptr [ebp - 0x10]
00a0bcda c1e002                   shl       eax, 2
00a0bcdd 8d3c08                   lea       edi, [eax + ecx]
00a0bce0 33fa                     xor       edi, edx
00a0bce2 8b55f0                   mov       edx, dword ptr [ebp - 0x10]
00a0bce5 33fa                     xor       edi, edx
00a0bce7 893c08                   mov       dword ptr [eax + ecx], edi
00a0bcea 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
00a0bcf0 8b4608                   mov       eax, dword ptr [esi + 8]
00a0bcf3 8b4948                   mov       ecx, dword ptr [ecx + 0x48]
00a0bcf6 c1e002                   shl       eax, 2
00a0bcf9 8d3c08                   lea       edi, [eax + ecx]
00a0bcfc 333ddc012101             xor       edi, dword ptr [0x12101dc]
00a0bd02 33fa                     xor       edi, edx
00a0bd04 893c08                   mov       dword ptr [eax + ecx], edi
00a0bd07 8d4de8                   lea       ecx, [ebp - 0x18]
00a0bd0a e851639fff               call      0x402060
00a0bd0f 8b15d8012101             mov       edx, dword ptr [0x12101d8]
00a0bd15 8b4a44                   mov       ecx, dword ptr [edx + 0x44]
00a0bd18 8b15dc012101             mov       edx, dword ptr [0x12101dc]
00a0bd1e 83c07d                   add       eax, 0x7d
00a0bd21 8945f0                   mov       dword ptr [ebp - 0x10], eax
00a0bd24 db45f0                   fild      dword ptr [ebp - 0x10]
00a0bd27 8b4610                   mov       eax, dword ptr [esi + 0x10]
00a0bd2a c1e002                   shl       eax, 2
00a0bd2d 8d3c08                   lea       edi, [eax + ecx]
00a0bd30 d95df0                   fstp      dword ptr [ebp - 0x10]
00a0bd33 33fa                     xor       edi, edx
00a0bd35 8b55f0                   mov       edx, dword ptr [ebp - 0x10]
00a0bd38 33fa                     xor       edi, edx
00a0bd3a 893c08                   mov       dword ptr [eax + ecx], edi
00a0bd3d a1d8012101               mov       eax, dword ptr [0x12101d8]
00a0bd42 8b4848                   mov       ecx, dword ptr [eax + 0x48]
00a0bd45 8b4610                   mov       eax, dword ptr [esi + 0x10]
00a0bd48 c1e002                   shl       eax, 2
00a0bd4b 8d3c08                   lea       edi, [eax + ecx]
00a0bd4e 33                       .byte     0x33
00a0bd4f 3d                       .byte     0x3d
