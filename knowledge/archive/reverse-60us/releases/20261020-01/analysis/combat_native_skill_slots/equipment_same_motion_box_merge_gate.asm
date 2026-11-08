004b4960  55                       push       ebp
004b4961  8bec                     mov        ebp, esp
004b4963  51                       push       ecx
004b4964  57                       push       edi
004b4965  8b7d08                   mov        edi, dword ptr [ebp + 8]
004b4968  85ff                     test       edi, edi
004b496a  0f8401010000             je         0x4b4a71
004b4970  81c758070000             add        edi, 0x758
004b4976  0f84f5000000             je         0x4b4a71
004b497c  837d0cff                 cmp        dword ptr [ebp + 0xc], -1
004b4980  0f84eb000000             je         0x4b4a71
004b4986  8b01                     mov        eax, dword ptr [ecx]
004b4988  53                       push       ebx
004b4989  ff9064030000             call       dword ptr [eax + 0x364]
004b498f  8b4f08                   mov        ecx, dword ptr [edi + 8]
004b4992  8945fc                   mov        dword ptr [ebp - 4], eax
004b4995  2b4f04                   sub        ecx, dword ptr [edi + 4]
004b4998  b8eba00eea               mov        eax, 0xea0ea0eb
004b499d  f7e9                     imul       ecx
004b499f  03d1                     add        edx, ecx
004b49a1  c1fa07                   sar        edx, 7
004b49a4  8bca                     mov        ecx, edx
004b49a6  c1e91f                   shr        ecx, 0x1f
004b49a9  33db                     xor        ebx, ebx
004b49ab  03ca                     add        ecx, edx
004b49ad  0f84bd000000             je         0x4b4a70
004b49b3  56                       push       esi
004b49b4  53                       push       ebx
004b49b5  8bcf                     mov        ecx, edi
004b49b7  e8d41bfbff               call       0x466590
004b49bc  8bf0                     mov        esi, eax
004b49be  8b4e3c                   mov        ecx, dword ptr [esi + 0x3c]
004b49c1  83c604                   add        esi, 4
004b49c4  85c9                     test       ecx, ecx
004b49c6  7431                     je         0x4b49f9
004b49c8  8b463c                   mov        eax, dword ptr [esi + 0x3c]
004b49cb  2bc1                     sub        eax, ecx
004b49cd  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004b49d0  c1f802                   sar        eax, 2
004b49d3  3bc8                     cmp        ecx, eax
004b49d5  7325                     jae        0x4b49fc
004b49d7  8b5638                   mov        edx, dword ptr [esi + 0x38]
004b49da  8d048a                   lea        eax, [edx + ecx*4]
004b49dd  8b00                     mov        eax, dword ptr [eax]
004b49df  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004b49e2  50                       push       eax
004b49e3  e8e8aeffff               call       0x4af8d0
004b49e8  84c0                     test       al, al
004b49ea  743f                     je         0x4b4a2b
004b49ec  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004b49ef  51                       push       ecx
004b49f0  8bce                     mov        ecx, esi
004b49f2  e859dcffff               call       0x4b2650
004b49f7  eb39                     jmp        0x4b4a32
004b49f9  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004b49fc  8b4638                   mov        eax, dword ptr [esi + 0x38]
004b49ff  85c0                     test       eax, eax
004b4a01  7511                     jne        0x4b4a14
004b4a03  33f6                     xor        esi, esi
004b4a05  56                       push       esi
004b4a06  51                       push       ecx
004b4a07  682811cd00               push       0xcd1128
004b4a0c  ff15bc2eff00             call       dword ptr [0xff2ebc]
004b4a12  eb34                     jmp        0x4b4a48
004b4a14  8b763c                   mov        esi, dword ptr [esi + 0x3c]
004b4a17  2bf0                     sub        esi, eax
004b4a19  c1fe02                   sar        esi, 2
004b4a1c  56                       push       esi
004b4a1d  51                       push       ecx
004b4a1e  682811cd00               push       0xcd1128
004b4a23  ff15bc2eff00             call       dword ptr [0xff2ebc]
004b4a29  eb1d                     jmp        0x4b4a48
004b4a2b  8a4510                   mov        al, byte ptr [ebp + 0x10]
004b4a2e  84c0                     test       al, al
004b4a30  7419                     je         0x4b4a4b
004b4a32  8b550c                   mov        edx, dword ptr [ebp + 0xc]
004b4a35  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004b4a38  8b01                     mov        eax, dword ptr [ecx]
004b4a3a  52                       push       edx
004b4a3b  57                       push       edi
004b4a3c  ff9038010000             call       dword ptr [eax + 0x138]
004b4a42  50                       push       eax
004b4a43  e8281dfaff               call       0x456770
004b4a48  83c40c                   add        esp, 0xc
004b4a4b  8b4704                   mov        eax, dword ptr [edi + 4]
004b4a4e  8b4f08                   mov        ecx, dword ptr [edi + 8]
004b4a51  2bc8                     sub        ecx, eax
004b4a53  b8eba00eea               mov        eax, 0xea0ea0eb
004b4a58  f7e9                     imul       ecx
004b4a5a  03d1                     add        edx, ecx
004b4a5c  c1fa07                   sar        edx, 7
004b4a5f  8bca                     mov        ecx, edx
004b4a61  c1e91f                   shr        ecx, 0x1f
004b4a64  43                       inc        ebx
004b4a65  03ca                     add        ecx, edx
004b4a67  3bd9                     cmp        ebx, ecx
004b4a69  0f8245ffffff             jb         0x4b49b4
004b4a6f  5e                       pop        esi
004b4a70  5b                       pop        ebx
004b4a71  5f                       pop        edi
004b4a72  8be5                     mov        esp, ebp
004b4a74  5d                       pop        ebp
004b4a75  c2                       .byte      0xc2
