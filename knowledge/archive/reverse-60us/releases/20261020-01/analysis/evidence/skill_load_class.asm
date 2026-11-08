; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 008a2940..008a2a7f (end exclusive); file offset 004a2940
; This is an instruction excerpt, not a recovered original source file.
008a2940  55                       push       ebp
008a2941  8bec                     mov        ebp, esp
008a2943  6aff                     push       -1
008a2945  68f024c800               push       0xc824f0
008a294a  64a100000000             mov        eax, dword ptr fs:[0]
008a2950  50                       push       eax
008a2951  64892500000000           mov        dword ptr fs:[0], esp
008a2958  51                       push       ecx
008a2959  53                       push       ebx
008a295a  56                       push       esi
008a295b  57                       push       edi
008a295c  6830030000               push       0x330
008a2961  e8b7af3400               call       0xbed91d
008a2966  83c404                   add        esp, 4
008a2969  8945f0                   mov        dword ptr [ebp - 0x10], eax
008a296c  33ff                     xor        edi, edi
008a296e  3bc7                     cmp        eax, edi
008a2970  897dfc                   mov        dword ptr [ebp - 4], edi
008a2973  740c                     je         0x8a2981
008a2975  8bc8                     mov        ecx, eax
008a2977  e8f437cbff               call       0x556170
008a297c  8945f0                   mov        dword ptr [ebp - 0x10], eax
008a297f  eb03                     jmp        0x8a2984
008a2981  897df0                   mov        dword ptr [ebp - 0x10], edi
008a2984  8b7510                   mov        esi, dword ptr [ebp + 0x10]
008a2987  83fe06                   cmp        esi, 6
008a298a  8b1d28f04001             mov        ebx, dword ptr [0x140f028]
008a2990  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
008a2997  7220                     jb         0x8a29b9
008a2999  6a06                     push       6
008a299b  56                       push       esi
008a299c  686ccbcd00               push       0xcdcb6c
008a29a1  68a0b3cb00               push       0xcbb3a0
008a29a6  ff15bc2eff00             call       dword ptr [0xff2ebc]
008a29ac  83c410                   add        esp, 0x10
008a29af  57                       push       edi
008a29b0  57                       push       edi
008a29b1  57                       push       edi
008a29b2  688c0000c0               push       0xc000008c
008a29b7  ffd3                     call       ebx
008a29b9  8d0476                   lea        eax, [esi + esi*2]
008a29bc  8b04858cf00b01           mov        eax, dword ptr [eax*4 + 0x10bf08c]
008a29c3  8b38                     mov        edi, dword ptr [eax]
008a29c5  897d10                   mov        dword ptr [ebp + 0x10], edi
008a29c8  83fe06                   cmp        esi, 6
008a29cb  7223                     jb         0x8a29f0
008a29cd  6a06                     push       6
008a29cf  56                       push       esi
008a29d0  686ccbcd00               push       0xcdcb6c
008a29d5  68a0b3cb00               push       0xcbb3a0
008a29da  ff15bc2eff00             call       dword ptr [0xff2ebc]
008a29e0  83c410                   add        esp, 0x10
008a29e3  6a00                     push       0
008a29e5  6a00                     push       0
008a29e7  6a00                     push       0
008a29e9  688c0000c0               push       0xc000008c
008a29ee  ffd3                     call       ebx
008a29f0  8d0476                   lea        eax, [esi + esi*2]
008a29f3  3b3c858cf00b01           cmp        edi, dword ptr [eax*4 + 0x10bf08c]
008a29fa  744b                     je         0x8a2a47
008a29fc  837f2808                 cmp        dword ptr [edi + 0x28], 8
008a2a00  7205                     jb         0x8a2a07
008a2a02  8b4714                   mov        eax, dword ptr [edi + 0x14]
008a2a05  eb03                     jmp        0x8a2a0a
008a2a07  8d4714                   lea        eax, [edi + 0x14]
008a2a0a  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
008a2a0d  6a00                     push       0
008a2a0f  56                       push       esi
008a2a10  50                       push       eax
008a2a11  51                       push       ecx
008a2a12  e889e3ffff               call       0x8a0da0
008a2a17  83c410                   add        esp, 0x10
008a2a1a  84c0                     test       al, al
008a2a1c  741c                     je         0x8a2a3a
008a2a1e  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
008a2a21  83c108                   add        ecx, 8
008a2a24  e8c7061b00               call       0xa530f0
008a2a29  8b570c                   mov        edx, dword ptr [edi + 0xc]
008a2a2c  52                       push       edx
008a2a2d  50                       push       eax
008a2a2e  8d0cf5d0f00b01           lea        ecx, [esi*8 + 0x10bf0d0]
008a2a35  e80638f9ff               call       0x836240
008a2a3a  8d4d10                   lea        ecx, [ebp + 0x10]
008a2a3d  e82e8d3000               call       0xbab770
008a2a42  8b7d10                   mov        edi, dword ptr [ebp + 0x10]
008a2a45  eb81                     jmp        0x8a29c8
008a2a47  8b75f0                   mov        esi, dword ptr [ebp - 0x10]
008a2a4a  85f6                     test       esi, esi
008a2a4c  7410                     je         0x8a2a5e
008a2a4e  8bce                     mov        ecx, esi
008a2a50  e8cb3acbff               call       0x556520
008a2a55  56                       push       esi
008a2a56  e882d53500               call       0xbfffdd
008a2a5b  83c404                   add        esp, 4
008a2a5e  8b450c                   mov        eax, dword ptr [ebp + 0xc]
008a2a61  8b4d08                   mov        ecx, dword ptr [ebp + 8]
008a2a64  50                       push       eax
008a2a65  51                       push       ecx
008a2a66  e8f5d6f8ff               call       0x830160
008a2a6b  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
008a2a6e  83c408                   add        esp, 8
008a2a71  5f                       pop        edi
008a2a72  5e                       pop        esi
008a2a73  5b                       pop        ebx
008a2a74  64890d00000000           mov        dword ptr fs:[0], ecx
008a2a7b  8be5                     mov        esp, ebp
008a2a7d  5d                       pop        ebp
008a2a7e  c3                       ret        
