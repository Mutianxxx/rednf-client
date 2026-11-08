00a27500  55                       push       ebp
00a27501  8bec                     mov        ebp, esp
00a27503  83ec10                   sub        esp, 0x10
00a27506  53                       push       ebx
00a27507  57                       push       edi
00a27508  8b7d08                   mov        edi, dword ptr [ebp + 8]
00a2750b  85ff                     test       edi, edi
00a2750d  8bd9                     mov        ebx, ecx
00a2750f  895df4                   mov        dword ptr [ebp - 0xc], ebx
00a27512  0f846a010000             je         0xa27682
00a27518  8b8398000000             mov        eax, dword ptr [ebx + 0x98]
00a2751e  85c0                     test       eax, eax
00a27520  56                       push       esi
00a27521  7504                     jne        0xa27527
00a27523  33f6                     xor        esi, esi
00a27525  eb1b                     jmp        0xa27542
00a27527  8b8b9c000000             mov        ecx, dword ptr [ebx + 0x9c]
00a2752d  2bc8                     sub        ecx, eax
00a2752f  b843082184               mov        eax, 0x84210843
00a27534  f7e9                     imul       ecx
00a27536  03d1                     add        edx, ecx
00a27538  c1fa06                   sar        edx, 6
00a2753b  8bf2                     mov        esi, edx
00a2753d  c1ee1f                   shr        esi, 0x1f
00a27540  03f2                     add        esi, edx
00a27542  8b8798000000             mov        eax, dword ptr [edi + 0x98]
00a27548  85c0                     test       eax, eax
00a2754a  741b                     je         0xa27567
00a2754c  8b8f9c000000             mov        ecx, dword ptr [edi + 0x9c]
00a27552  2bc8                     sub        ecx, eax
00a27554  b843082184               mov        eax, 0x84210843
00a27559  f7e9                     imul       ecx
00a2755b  03d1                     add        edx, ecx
00a2755d  c1fa06                   sar        edx, 6
00a27560  8bc2                     mov        eax, edx
00a27562  c1e81f                   shr        eax, 0x1f
00a27565  03c2                     add        eax, edx
00a27567  3bf0                     cmp        esi, eax
00a27569  7d16                     jge        0xa27581
00a2756b  8b8398000000             mov        eax, dword ptr [ebx + 0x98]
00a27571  85c0                     test       eax, eax
00a27573  7504                     jne        0xa27579
00a27575  33db                     xor        ebx, ebx
00a27577  eb31                     jmp        0xa275aa
00a27579  8b8b9c000000             mov        ecx, dword ptr [ebx + 0x9c]
00a2757f  eb14                     jmp        0xa27595
00a27581  8b8798000000             mov        eax, dword ptr [edi + 0x98]
00a27587  85c0                     test       eax, eax
00a27589  7504                     jne        0xa2758f
00a2758b  33db                     xor        ebx, ebx
00a2758d  eb1b                     jmp        0xa275aa
00a2758f  8b8f9c000000             mov        ecx, dword ptr [edi + 0x9c]
00a27595  2bc8                     sub        ecx, eax
00a27597  b843082184               mov        eax, 0x84210843
00a2759c  f7e9                     imul       ecx
00a2759e  03d1                     add        edx, ecx
00a275a0  c1fa06                   sar        edx, 6
00a275a3  8bda                     mov        ebx, edx
00a275a5  c1eb1f                   shr        ebx, 0x1f
00a275a8  03da                     add        ebx, edx
00a275aa  33f6                     xor        esi, esi
00a275ac  3bde                     cmp        ebx, esi
00a275ae  8975f8                   mov        dword ptr [ebp - 8], esi
00a275b1  0f8eca000000             jle        0xa27681
00a275b7  8975fc                   mov        dword ptr [ebp - 4], esi
00a275ba  eb04                     jmp        0xa275c0
00a275bc  8b7d08                   mov        edi, dword ptr [ebp + 8]
00a275bf  90                       nop        
00a275c0  8b8798000000             mov        eax, dword ptr [edi + 0x98]
00a275c6  85c0                     test       eax, eax
00a275c8  741b                     je         0xa275e5
00a275ca  8b8f9c000000             mov        ecx, dword ptr [edi + 0x9c]
00a275d0  2bc8                     sub        ecx, eax
00a275d2  b843082184               mov        eax, 0x84210843
00a275d7  f7e9                     imul       ecx
00a275d9  03d1                     add        edx, ecx
00a275db  c1fa06                   sar        edx, 6
00a275de  8bc2                     mov        eax, edx
00a275e0  c1e81f                   shr        eax, 0x1f
00a275e3  03c2                     add        eax, edx
00a275e5  3bf0                     cmp        esi, eax
00a275e7  7d0b                     jge        0xa275f4
00a275e9  8b8798000000             mov        eax, dword ptr [edi + 0x98]
00a275ef  0345fc                   add        eax, dword ptr [ebp - 4]
00a275f2  eb02                     jmp        0xa275f6
00a275f4  33c0                     xor        eax, eax
00a275f6  8b783c                   mov        edi, dword ptr [eax + 0x3c]
00a275f9  85ff                     test       edi, edi
00a275fb  746c                     je         0xa27669
00a275fd  8b7040                   mov        esi, dword ptr [eax + 0x40]
00a27600  8bce                     mov        ecx, esi
00a27602  2bcf                     sub        ecx, edi
00a27604  b8abaaaa2a               mov        eax, 0x2aaaaaab
00a27609  f7e9                     imul       ecx
00a2760b  c1fa03                   sar        edx, 3
00a2760e  8bc2                     mov        eax, edx
00a27610  c1e81f                   shr        eax, 0x1f
00a27613  03c2                     add        eax, edx
00a27615  8945f0                   mov        dword ptr [ebp - 0x10], eax
00a27618  744f                     je         0xa27669
00a2761a  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a2761d  8b8198000000             mov        eax, dword ptr [ecx + 0x98]
00a27623  85c0                     test       eax, eax
00a27625  741e                     je         0xa27645
00a27627  8b899c000000             mov        ecx, dword ptr [ecx + 0x9c]
00a2762d  2bc8                     sub        ecx, eax
00a2762f  b843082184               mov        eax, 0x84210843
00a27634  f7e9                     imul       ecx
00a27636  03d1                     add        edx, ecx
00a27638  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a2763b  c1fa06                   sar        edx, 6
00a2763e  8bc2                     mov        eax, edx
00a27640  c1e81f                   shr        eax, 0x1f
00a27643  03c2                     add        eax, edx
00a27645  3945f8                   cmp        dword ptr [ebp - 8], eax
00a27648  7d0b                     jge        0xa27655
00a2764a  8b8198000000             mov        eax, dword ptr [ecx + 0x98]
00a27650  0345fc                   add        eax, dword ptr [ebp - 4]
00a27653  eb02                     jmp        0xa27657
00a27655  33c0                     xor        eax, eax
00a27657  8b5508                   mov        edx, dword ptr [ebp + 8]
00a2765a  52                       push       edx
00a2765b  8d4838                   lea        ecx, [eax + 0x38]
00a2765e  8b4108                   mov        eax, dword ptr [ecx + 8]
00a27661  56                       push       esi
00a27662  57                       push       edi
00a27663  50                       push       eax
00a27664  e8373ec2ff               call       0x64b4a0
00a27669  8b75f8                   mov        esi, dword ptr [ebp - 8]
00a2766c  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00a2766f  46                       inc        esi
00a27670  83c17c                   add        ecx, 0x7c
00a27673  3bf3                     cmp        esi, ebx
00a27675  8975f8                   mov        dword ptr [ebp - 8], esi
00a27678  894dfc                   mov        dword ptr [ebp - 4], ecx
00a2767b  0f8c3bffffff             jl         0xa275bc
00a27681  5e                       pop        esi
00a27682  5f                       pop        edi
00a27683  5b                       pop        ebx
00a27684  8be5                     mov        esp, ebp
00a27686  5d                       pop        ebp
00a27687  c2                       .byte      0xc2
