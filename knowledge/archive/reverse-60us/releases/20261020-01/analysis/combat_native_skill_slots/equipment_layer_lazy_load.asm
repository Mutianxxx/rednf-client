004b2650  55                       push       ebp
004b2651  8bec                     mov        ebp, esp
004b2653  6aff                     push       -1
004b2655  680775c500               push       0xc57507
004b265a  64a100000000             mov        eax, dword ptr fs:[0]
004b2660  50                       push       eax
004b2661  64892500000000           mov        dword ptr fs:[0], esp
004b2668  51                       push       ecx
004b2669  53                       push       ebx
004b266a  56                       push       esi
004b266b  8bf1                     mov        esi, ecx
004b266d  8b4e48                   mov        ecx, dword ptr [esi + 0x48]
004b2670  85c9                     test       ecx, ecx
004b2672  57                       push       edi
004b2673  0f8454010000             je         0x4b27cd
004b2679  8b464c                   mov        eax, dword ptr [esi + 0x4c]
004b267c  2bc1                     sub        eax, ecx
004b267e  c1f806                   sar        eax, 6
004b2681  85c0                     test       eax, eax
004b2683  0f8644010000             jbe        0x4b27cd
004b2689  8b4e38                   mov        ecx, dword ptr [esi + 0x38]
004b268c  85c9                     test       ecx, ecx
004b268e  0f8439010000             je         0x4b27cd
004b2694  8b463c                   mov        eax, dword ptr [esi + 0x3c]
004b2697  2bc1                     sub        eax, ecx
004b2699  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004b269c  c1f802                   sar        eax, 2
004b269f  3bc8                     cmp        ecx, eax
004b26a1  0f8326010000             jae        0x4b27cd
004b26a7  8b7e38                   mov        edi, dword ptr [esi + 0x38]
004b26aa  8d1c8d00000000           lea        ebx, [ecx*4]
004b26b1  8b043b                   mov        eax, dword ptr [ebx + edi]
004b26b4  50                       push       eax
004b26b5  8bce                     mov        ecx, esi
004b26b7  e814d2ffff               call       0x4af8d0
004b26bc  84c0                     test       al, al
004b26be  0f8409010000             je         0x4b27cd
004b26c4  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004b26c7  51                       push       ecx
004b26c8  8bce                     mov        ecx, esi
004b26ca  e8c1d1ffff               call       0x4af890
004b26cf  84c0                     test       al, al
004b26d1  0f84e8000000             je         0x4b27bf
004b26d7  8b3c3b                   mov        edi, dword ptr [ebx + edi]
004b26da  85ff                     test       edi, edi
004b26dc  7410                     je         0x4b26ee
004b26de  8bcf                     mov        ecx, edi
004b26e0  e8eb62f5ff               call       0x4089d0
004b26e5  57                       push       edi
004b26e6  e865f8f4ff               call       0x401f50
004b26eb  83c404                   add        esp, 4
004b26ee  8b4638                   mov        eax, dword ptr [esi + 0x38]
004b26f1  68e8010000               push       0x1e8
004b26f6  c7040300000000           mov        dword ptr [ebx + eax], 0
004b26fd  e84e15f5ff               call       0x403c50
004b2702  83c404                   add        esp, 4
004b2705  8945f0                   mov        dword ptr [ebp - 0x10], eax
004b2708  85c0                     test       eax, eax
004b270a  c745fc00000000           mov        dword ptr [ebp - 4], 0
004b2711  7447                     je         0x4b275a
004b2713  8b5508                   mov        edx, dword ptr [ebp + 8]
004b2716  8b7e48                   mov        edi, dword ptr [esi + 0x48]
004b2719  c1e206                   shl        edx, 6
004b271c  8b443a3c                 mov        eax, dword ptr [edx + edi + 0x3c]
004b2720  b908000000               mov        ecx, 8
004b2725  3bc1                     cmp        eax, ecx
004b2727  7206                     jb         0x4b272f
004b2729  8b443a28                 mov        eax, dword ptr [edx + edi + 0x28]
004b272d  eb04                     jmp        0x4b2733
004b272f  8d443a28                 lea        eax, [edx + edi + 0x28]
004b2733  394c3a20                 cmp        dword ptr [edx + edi + 0x20], ecx
004b2737  7206                     jb         0x4b273f
004b2739  8b4c3a0c                 mov        ecx, dword ptr [edx + edi + 0xc]
004b273d  eb04                     jmp        0x4b2743
004b273f  8d4c3a0c                 lea        ecx, [edx + edi + 0xc]
004b2743  6a01                     push       1
004b2745  50                       push       eax
004b2746  8b443a04                 mov        eax, dword ptr [edx + edi + 4]
004b274a  51                       push       ecx
004b274b  8b0c3a                   mov        ecx, dword ptr [edx + edi]
004b274e  50                       push       eax
004b274f  51                       push       ecx
004b2750  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
004b2753  e82804fcff               call       0x472b80
004b2758  eb02                     jmp        0x4b275c
004b275a  33c0                     xor        eax, eax
004b275c  8b4e38                   mov        ecx, dword ptr [esi + 0x38]
004b275f  03cb                     add        ecx, ebx
004b2761  8901                     mov        dword ptr [ecx], eax
004b2763  8b4638                   mov        eax, dword ptr [esi + 0x38]
004b2766  8b0c18                   mov        ecx, dword ptr [eax + ebx]
004b2769  03c3                     add        eax, ebx
004b276b  6a02                     push       2
004b276d  83c148                   add        ecx, 0x48
004b2770  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004b2777  e864496500               call       0xb070e0
004b277c  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004b277f  8b7e48                   mov        edi, dword ptr [esi + 0x48]
004b2782  8bc1                     mov        eax, ecx
004b2784  c1e006                   shl        eax, 6
004b2787  8b54383c                 mov        edx, dword ptr [eax + edi + 0x3c]
004b278b  03c7                     add        eax, edi
004b278d  83fa08                   cmp        edx, 8
004b2790  7205                     jb         0x4b2797
004b2792  8b4028                   mov        eax, dword ptr [eax + 0x28]
004b2795  eb03                     jmp        0x4b279a
004b2797  83c028                   add        eax, 0x28
004b279a  50                       push       eax
004b279b  51                       push       ecx
004b279c  68b80bcd00               push       0xcd0bb8
004b27a1  ff15bc2eff00             call       dword ptr [0xff2ebc]
004b27a7  83c40c                   add        esp, 0xc
004b27aa  5f                       pop        edi
004b27ab  5e                       pop        esi
004b27ac  b001                     mov        al, 1
004b27ae  5b                       pop        ebx
004b27af  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004b27b2  64890d00000000           mov        dword ptr fs:[0], ecx
004b27b9  8be5                     mov        esp, ebp
004b27bb  5d                       pop        ebp
004b27bc  c20400                   ret        4
004b27bf  68840bcd00               push       0xcd0b84
004b27c4  ff15bc2eff00             call       dword ptr [0xff2ebc]
004b27ca  83c404                   add        esp, 4
004b27cd  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004b27d0  5f                       pop        edi
004b27d1  5e                       pop        esi
004b27d2  32c0                     xor        al, al
004b27d4  5b                       pop        ebx
004b27d5  64890d00000000           mov        dword ptr fs:[0], ecx
004b27dc  8be5                     mov        esp, ebp
004b27de  5d                       pop        ebp
004b27df  c2                       .byte      0xc2
