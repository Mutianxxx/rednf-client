0049ef20 86ac0500008918           xchg      byte ptr [ebp + eax + 0x18890000], ch
0049ef27 8b8eac050000             mov       ecx, dword ptr [esi + 0x5ac]
0049ef2d 895904                   mov       dword ptr [ecx + 4], ebx
0049ef30 8b96ac050000             mov       edx, dword ptr [esi + 0x5ac]
0049ef36 895a08                   mov       dword ptr [edx + 8], ebx
0049ef39 8b86ac050000             mov       eax, dword ptr [esi + 0x5ac]
0049ef3f 89580c                   mov       dword ptr [eax + 0xc], ebx
0049ef42 8b8eac050000             mov       ecx, dword ptr [esi + 0x5ac]
0049ef48 895910                   mov       dword ptr [ecx + 0x10], ebx
0049ef4b ff15d8f04001             call      dword ptr [0x140f0d8]
0049ef51 898618080000             mov       dword ptr [esi + 0x818], eax
0049ef57 889e2c080000             mov       byte ptr [esi + 0x82c], bl
0049ef5d 899e68080000             mov       dword ptr [esi + 0x868], ebx
0049ef63 899e6c080000             mov       dword ptr [esi + 0x86c], ebx
0049ef69 a1d8012101               mov       eax, dword ptr [0x12101d8]
0049ef6e 8b4844                   mov       ecx, dword ptr [eax + 0x44]
0049ef71 8b96f0070000             mov       edx, dword ptr [esi + 0x7f0]
0049ef77 8d0491                   lea       eax, [ecx + edx*4]
0049ef7a 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
0049ef80 8bd0                     mov       edx, eax
0049ef82 33d1                     xor       edx, ecx
0049ef84 83f202                   xor       edx, 2
0049ef87 8910                     mov       dword ptr [eax], edx
0049ef89 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0049ef8f 8b5148                   mov       edx, dword ptr [ecx + 0x48]
0049ef92 8b86f0070000             mov       eax, dword ptr [esi + 0x7f0]
0049ef98 8d0482                   lea       eax, [edx + eax*4]
0049ef9b 8b15dc012101             mov       edx, dword ptr [0x12101dc]
0049efa1 8bc8                     mov       ecx, eax
0049efa3 33ca                     xor       ecx, edx
0049efa5 83f102                   xor       ecx, 2
0049efa8 8908                     mov       dword ptr [eax], ecx
0049efaa 8b860c080000             mov       eax, dword ptr [esi + 0x80c]
0049efb0 83f808                   cmp       eax, 8
0049efb3 8d8ef4070000             lea       ecx, [esi + 0x7f4]
0049efb9 8d5104                   lea       edx, [ecx + 4]
0049efbc 7204                     jb        0x49efc2
0049efbe 8b32                     mov       esi, dword ptr [edx]
0049efc0 eb02                     jmp       0x49efc4
0049efc2 8bf2                     mov       esi, edx
0049efc4 83f808                   cmp       eax, 8
0049efc7 8b7914                   mov       edi, dword ptr [ecx + 0x14]
0049efca 8d347e                   lea       esi, [esi + edi*2]
0049efcd 7204                     jb        0x49efd3
0049efcf 8b3a                     mov       edi, dword ptr [edx]
0049efd1 eb02                     jmp       0x49efd5
0049efd3 8bfa                     mov       edi, edx
0049efd5 83f808                   cmp       eax, 8
0049efd8 7202                     jb        0x49efdc
0049efda 8b12                     mov       edx, dword ptr [edx]
0049efdc 3bfb                     cmp       edi, ebx
0049efde 7504                     jne       0x49efe4
0049efe0 33c0                     xor       eax, eax
0049efe2 eb06                     jmp       0x49efea
0049efe4 8bc7                     mov       eax, edi
0049efe6 2bc2                     sub       eax, edx
0049efe8 d1f8                     sar       eax, 1
0049efea 3bf3                     cmp       esi, ebx
0049efec 750d                     jne       0x49effb
0049efee 33f6                     xor       esi, esi
0049eff0 56                       push      esi
0049eff1 50                       push      eax
0049eff2 e8392cf6ff               call      0x401c30
0049eff7 5f                       pop       edi
0049eff8 5e                       pop       esi
0049eff9 5b                       pop       ebx
0049effa c3                       ret       
0049effb 2bf7                     sub       esi, edi
0049effd d1fe                     sar       esi, 1
0049efff 56                       push      esi
0049f000 50                       push      eax
0049f001 e82a2cf6ff               call      0x401c30
0049f006 5f                       pop       edi
0049f007 5e                       pop       esi
0049f008 5b                       pop       ebx
0049f009 c3                       ret       
0049f00a cc                       int3      
0049f00b cc                       int3      
0049f00c cc                       int3      
0049f00d cc                       int3      
0049f00e cc                       int3      
0049f00f cc                       int3      
0049f010 56                       push      esi
0049f011 8bf1                     mov       esi, ecx
0049f013 e828e10400               call      0x4ed140
0049f018 8b06                     mov       eax, dword ptr [esi]
0049f01a 8d8edc050000             lea       ecx, [esi + 0x5dc]
0049f020 51                       push      ecx
0049f021 8bce                     mov       ecx, esi
0049f023 ff9098010000             call      dword ptr [eax + 0x198]
0049f029 8b8648010000             mov       eax, dword ptr [esi + 0x148]
0049f02f 85c0                     test      eax, eax
0049f031 744a                     je        0x49f07d
0049f033 57                       push      edi
0049f034 8db8b0000000             lea       edi, [eax + 0xb0]
0049f03a 8d4f1c                   lea       ecx, [edi + 0x1c]
0049f03d e81e30f6ff               call      0x402060
0049f042 85c0                     test      eax, eax
0049f044 7520                     jne       0x49f066
0049f046 8bcf                     mov       ecx, edi
0049f048 e86343f9ff               call      0x4333b0
0049f04d d81da4d7e900             fcomp     dword ptr [0xe9d7a4]
0049f053 dfe0                     fnstsw    ax
0049f055 f6c441                   test      ah, 0x41
0049f058 740c                     je        0x49f066
0049f05a 8d4f08                   lea       ecx, [edi + 8]
0049f05d e8fe2ff6ff               call      0x402060
0049f062 85c0                     test      eax, eax
0049f064 7e16                     jle       0x49f07c
0049f066 8b8648010000             mov       eax, dword ptr [esi + 0x148]
0049f06c 8b16                     mov       edx, dword ptr [esi]
0049f06e 05b0000000               add       eax, 0xb0
0049f073 50                       push      eax
0049f074 8bce                     mov       ecx, esi
0049f076 ff9298010000             call      dword ptr [edx + 0x198]
0049f07c 5f                       pop       edi
0049f07d 8bce                     mov       ecx, esi
0049f07f 5e                       pop       esi
0049f080 e94bfcffff               jmp       0x49ecd0
0049f085 cc                       int3      
0049f086 cc                       int3      
0049f087 cc                       int3      
0049f088 cc                       int3      
0049f089 cc                       int3      
0049f08a cc                       int3      
0049f08b cc                       int3      
0049f08c cc                       int3      
0049f08d cc                       int3      
0049f08e cc                       int3      
0049f08f cc                       int3      
0049f090 55                       push      ebp
0049f091 8bec                     mov       ebp, esp
0049f093 56                       push      esi
0049f094 8b7508                   mov       esi, dword ptr [ebp + 8]
0049f097 8b4604                   mov       eax, dword ptr [esi + 4]
0049f09a 57                       push      edi
0049f09b 33ff                     xor       edi, edi
0049f09d 3bc7                     cmp       eax, edi
0049f09f 74                       .byte     0x74
