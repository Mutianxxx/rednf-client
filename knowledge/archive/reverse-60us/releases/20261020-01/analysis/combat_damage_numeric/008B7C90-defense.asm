008b7c90 55                       push       ebp
008b7c91 8bec                     mov        ebp, esp
008b7c93 83ec0c                   sub        esp, 0xc
008b7c96 56                       push       esi
008b7c97 8b7510                   mov        esi, dword ptr [ebp + 0x10]
008b7c9a 0fbe868a010000           movsx      eax, byte ptr [esi + 0x18a]
008b7ca1 83e804                   sub        eax, 4
008b7ca4 57                       push       edi
008b7ca5 7456                     je         0x8b7cfd
008b7ca7 83e802                   sub        eax, 2
008b7caa 742f                     je         0x8b7cdb
008b7cac 48                       dec        eax
008b7cad 7409                     je         0x8b7cb8
008b7caf 0fbebe8b010000           movsx      edi, byte ptr [esi + 0x18b]
008b7cb6 eb4a                     jmp        0x8b7d02
008b7cb8 a148280001               mov        eax, dword ptr [0x1002848]
008b7cbd 8b8864100000             mov        ecx, dword ptr [eax + 0x1064]
008b7cc3 8b8180000000             mov        eax, dword ptr [ecx + 0x80]
008b7cc9 8d1480                   lea        edx, [eax + eax*4]
008b7ccc a128a10d01               mov        eax, dword ptr [0x10da128]
008b7cd1 0fbf7c9002               movsx      edi, word ptr [eax + edx*4 + 2]
008b7cd6 8d0490                   lea        eax, [eax + edx*4]
008b7cd9 eb27                     jmp        0x8b7d02
008b7cdb 8b0d48280001             mov        ecx, dword ptr [0x1002848]
008b7ce1 8b9160100000             mov        edx, dword ptr [ecx + 0x1060]
008b7ce7 8b4274                   mov        eax, dword ptr [edx + 0x74]
008b7cea 8b0d40a40d01             mov        ecx, dword ptr [0x10da440]
008b7cf0 8d0480                   lea        eax, [eax + eax*4]
008b7cf3 0fbf7c8102               movsx      edi, word ptr [ecx + eax*4 + 2]
008b7cf8 8d0481                   lea        eax, [ecx + eax*4]
008b7cfb eb05                     jmp        0x8b7d02
008b7cfd bf32000000               mov        edi, 0x32
008b7d02 8a4605                   mov        al, byte ptr [esi + 5]
008b7d05 84c0                     test       al, al
008b7d07 897df4                   mov        dword ptr [ebp - 0xc], edi
008b7d0a c7451000000000           mov        dword ptr [ebp + 0x10], 0
008b7d11 c745fc00000000           mov        dword ptr [ebp - 4], 0
008b7d18 c745f800000000           mov        dword ptr [ebp - 8], 0
008b7d1f 7532                     jne        0x8b7d53
008b7d21 db868f000000             fild       dword ptr [esi + 0x8f]
008b7d27 b9b0fe0b01               mov        ecx, 0x10bfeb0
008b7d2c d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b7d32 d805581fcc00             fadd       dword ptr [0xcc1f58]
008b7d38 db868b000000             fild       dword ptr [esi + 0x8b]
008b7d3e dec9                     fmulp      st(1)
008b7d40 d95d10                   fstp       dword ptr [ebp + 0x10]
008b7d43 e868b6b7ff               call       0x4333b0
008b7d48 d95df8                   fstp       dword ptr [ebp - 8]
008b7d4b d98693000000             fld        dword ptr [esi + 0x93]
008b7d51 eb34                     jmp        0x8b7d87
008b7d53 3c01                     cmp        al, 1
008b7d55 7539                     jne        0x8b7d90
008b7d57 db869b000000             fild       dword ptr [esi + 0x9b]
008b7d5d b9d0fe0b01               mov        ecx, 0x10bfed0
008b7d62 d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b7d68 d805581fcc00             fadd       dword ptr [0xcc1f58]
008b7d6e db8697000000             fild       dword ptr [esi + 0x97]
008b7d74 dec9                     fmulp      st(1)
008b7d76 d95d10                   fstp       dword ptr [ebp + 0x10]
008b7d79 e832b6b7ff               call       0x4333b0
008b7d7e d95df8                   fstp       dword ptr [ebp - 8]
008b7d81 d9869f000000             fld        dword ptr [esi + 0x9f]
008b7d87 d80dac10cc00             fmul       dword ptr [0xcc10ac]
008b7d8d d95dfc                   fstp       dword ptr [ebp - 4]
008b7d90 8b5514                   mov        edx, dword ptr [ebp + 0x14]
008b7d93 6a01                     push       1
008b7d95 52                       push       edx
008b7d96 e8750eb9ff               call       0x448c10
008b7d9b d84d10                   fmul       dword ptr [ebp + 0x10]
008b7d9e 8a86bc010000             mov        al, byte ptr [esi + 0x1bc]
008b7da4 83c408                   add        esp, 8
008b7da7 84c0                     test       al, al
008b7da9 d95d10                   fstp       dword ptr [ebp + 0x10]
008b7dac d945f8                   fld        dword ptr [ebp - 8]
008b7daf 7402                     je         0x8b7db3
008b7db1 dcc0                     fadd       st(0), st(0)
008b7db3 da4df4                   fimul      dword ptr [ebp - 0xc]
008b7db6 d84510                   fadd       dword ptr [ebp + 0x10]
008b7db9 d815581fcc00             fcom       dword ptr [0xcc1f58]
008b7dbf dfe0                     fnstsw     ax
008b7dc1 f6c441                   test       ah, 0x41
008b7dc4 7408                     je         0x8b7dce
008b7dc6 ddd8                     fstp       st(0)
008b7dc8 d905581fcc00             fld        dword ptr [0xcc1f58]
008b7dce d94510                   fld        dword ptr [ebp + 0x10]
008b7dd1 8b4d08                   mov        ecx, dword ptr [ebp + 8]
008b7dd4 d8f1                     fdiv       st(1)
008b7dd6 d919                     fstp       dword ptr [ecx]
008b7dd8 ddd8                     fstp       st(0)
008b7dda d94510                   fld        dword ptr [ebp + 0x10]
008b7ddd d81da4d7e900             fcomp      dword ptr [0xe9d7a4]
008b7de3 dfe0                     fnstsw     ax
008b7de5 f6c405                   test       ah, 5
008b7de8 7a1e                     jp         0x8b7e08
008b7dea 83ff0a                   cmp        edi, 0xa
008b7ded 7d27                     jge        0x8b7e16
008b7def d94510                   fld        dword ptr [ebp + 0x10]
008b7df2 8b450c                   mov        eax, dword ptr [ebp + 0xc]
008b7df5 d80d48a8d500             fmul       dword ptr [0xd5a848]
008b7dfb 5f                       pop        edi
008b7dfc 5e                       pop        esi
008b7dfd d919                     fstp       dword ptr [ecx]
008b7dff d945fc                   fld        dword ptr [ebp - 4]
008b7e02 d918                     fstp       dword ptr [eax]
008b7e04 8be5                     mov        esp, ebp
008b7e06 5d                       pop        ebp
008b7e07 c3                       ret        
008b7e08 d945fc                   fld        dword ptr [ebp - 4]
008b7e0b 8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
008b7e0e 5f                       pop        edi
008b7e0f d919                     fstp       dword ptr [ecx]
008b7e11 5e                       pop        esi
008b7e12 8be5                     mov        esp, ebp
008b7e14 5d                       pop        ebp
008b7e15 c3                       ret        
008b7e16 d945fc                   fld        dword ptr [ebp - 4]
008b7e19 8b550c                   mov        edx, dword ptr [ebp + 0xc]
008b7e1c 5f                       pop        edi
008b7e1d d91a                     fstp       dword ptr [edx]
008b7e1f 5e                       pop        esi
008b7e20 8be5                     mov        esp, ebp
008b7e22 5d                       pop        ebp
008b7e23 c3                       ret        