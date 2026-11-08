008b26e0  55                       push       ebp
008b26e1  8bec                     mov        ebp, esp
008b26e3  51                       push       ecx
008b26e4  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
008b26e7  85c9                     test       ecx, ecx
008b26e9  0f84b4000000             je         0x8b27a3
008b26ef  53                       push       ebx
008b26f0  8b5d08                   mov        ebx, dword ptr [ebp + 8]
008b26f3  8b13                     mov        edx, dword ptr [ebx]
008b26f5  57                       push       edi
008b26f6  8bfa                     mov        edi, edx
008b26f8  83e73f                   and        edi, 0x3f
008b26fb  b840000000               mov        eax, 0x40
008b2700  03d1                     add        edx, ecx
008b2702  2bc7                     sub        eax, edi
008b2704  3bd1                     cmp        edx, ecx
008b2706  8945fc                   mov        dword ptr [ebp - 4], eax
008b2709  8913                     mov        dword ptr [ebx], edx
008b270b  7303                     jae        0x8b2710
008b270d  ff4304                   inc        dword ptr [ebx + 4]
008b2710  85ff                     test       edi, edi
008b2712  56                       push       esi
008b2713  743d                     je         0x8b2752
008b2715  3bc8                     cmp        ecx, eax
008b2717  7239                     jb         0x8b2752
008b2719  8b750c                   mov        esi, dword ptr [ebp + 0xc]
008b271c  8bc8                     mov        ecx, eax
008b271e  c1e902                   shr        ecx, 2
008b2721  8d7c1f28                 lea        edi, [edi + ebx + 0x28]
008b2725  f3a5                     rep movsd  dword ptr es:[edi], dword ptr [esi]
008b2727  8bc8                     mov        ecx, eax
008b2729  83e103                   and        ecx, 3
008b272c  f3a4                     rep movsb  byte ptr es:[edi], byte ptr [esi]
008b272e  8d4b28                   lea        ecx, [ebx + 0x28]
008b2731  51                       push       ecx
008b2732  53                       push       ebx
008b2733  e8c8c4ffff               call       0x8aec00
008b2738  8b45fc                   mov        eax, dword ptr [ebp - 4]
008b273b  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
008b273e  8b5510                   mov        edx, dword ptr [ebp + 0x10]
008b2741  03c8                     add        ecx, eax
008b2743  2bd0                     sub        edx, eax
008b2745  83c408                   add        esp, 8
008b2748  894d0c                   mov        dword ptr [ebp + 0xc], ecx
008b274b  895510                   mov        dword ptr [ebp + 0x10], edx
008b274e  33ff                     xor        edi, edi
008b2750  8bca                     mov        ecx, edx
008b2752  83f940                   cmp        ecx, 0x40
008b2755  7230                     jb         0x8b2787
008b2757  8bf1                     mov        esi, ecx
008b2759  c1ee06                   shr        esi, 6
008b275c  8d642400                 lea        esp, [esp]
008b2760  8b550c                   mov        edx, dword ptr [ebp + 0xc]
008b2763  52                       push       edx
008b2764  53                       push       ebx
008b2765  e896c4ffff               call       0x8aec00
008b276a  8b5510                   mov        edx, dword ptr [ebp + 0x10]
008b276d  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
008b2770  b840000000               mov        eax, 0x40
008b2775  2bd0                     sub        edx, eax
008b2777  03c8                     add        ecx, eax
008b2779  83c408                   add        esp, 8
008b277c  4e                       dec        esi
008b277d  895510                   mov        dword ptr [ebp + 0x10], edx
008b2780  894d0c                   mov        dword ptr [ebp + 0xc], ecx
008b2783  75db                     jne        0x8b2760
008b2785  8bca                     mov        ecx, edx
008b2787  85c9                     test       ecx, ecx
008b2789  7415                     je         0x8b27a0
008b278b  8b750c                   mov        esi, dword ptr [ebp + 0xc]
008b278e  8bc1                     mov        eax, ecx
008b2790  c1e902                   shr        ecx, 2
008b2793  8d7c1f28                 lea        edi, [edi + ebx + 0x28]
008b2797  f3a5                     rep movsd  dword ptr es:[edi], dword ptr [esi]
008b2799  8bc8                     mov        ecx, eax
008b279b  83e103                   and        ecx, 3
008b279e  f3a4                     rep movsb  byte ptr es:[edi], byte ptr [esi]
008b27a0  5e                       pop        esi
008b27a1  5f                       pop        edi
008b27a2  5b                       pop        ebx
008b27a3  8be5                     mov        esp, ebp
008b27a5  5d                       pop        ebp
008b27a6  c3                       ret        
008b27a7  cc                       int3       
008b27a8  cc                       int3       
008b27a9  cc                       int3       
008b27aa  cc                       int3       
008b27ab  cc                       int3       
008b27ac  cc                       int3       
008b27ad  cc                       int3       
008b27ae  cc                       int3       
008b27af  cc                       int3       