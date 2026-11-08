004b9fa0 55                       push       ebp
004b9fa1 8bec                     mov        ebp, esp
004b9fa3 6aff                     push       -1
004b9fa5 684978c500               push       0xc57849
004b9faa 64a100000000             mov        eax, dword ptr fs:[0]
004b9fb0 50                       push       eax
004b9fb1 64892500000000           mov        dword ptr fs:[0], esp
004b9fb8 83ec0c                   sub        esp, 0xc
004b9fbb 8a4508                   mov        al, byte ptr [ebp + 8]
004b9fbe 53                       push       ebx
004b9fbf 56                       push       esi
004b9fc0 33db                     xor        ebx, ebx
004b9fc2 84c0                     test       al, al
004b9fc4 57                       push       edi
004b9fc5 8bf1                     mov        esi, ecx
004b9fc7 895df0                   mov        dword ptr [ebp - 0x10], ebx
004b9fca 7420                     je         0x4b9fec
004b9fcc 8d45f0                   lea        eax, [ebp - 0x10]
004b9fcf 50                       push       eax
004b9fd0 8d4de8                   lea        ecx, [ebp - 0x18]
004b9fd3 c745f024faffff           mov        dword ptr [ebp - 0x10], 0xfffffa24
004b9fda e87181f4ff               call       0x402150
004b9fdf 895dfc                   mov        dword ptr [ebp - 4], ebx
004b9fe2 bb01000000               mov        ebx, 1
004b9fe7 895df0                   mov        dword ptr [ebp - 0x10], ebx
004b9fea eb06                     jmp        0x4b9ff2
004b9fec 8d863c160000             lea        eax, [esi + 0x163c]
004b9ff2 8bc8                     mov        ecx, eax
004b9ff4 e86780f4ff               call       0x402060
004b9ff9 f6c301                   test       bl, 1
004b9ffc 8bf8                     mov        edi, eax
004b9ffe c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
004ba005 7408                     je         0x4ba00f
004ba007 8d4de8                   lea        ecx, [ebp - 0x18]
004ba00a e80180f4ff               call       0x402010
004ba00f 8a4d08                   mov        cl, byte ptr [ebp + 8]
004ba012 84c9                     test       cl, cl
004ba014 7504                     jne        0x4ba01a
004ba016 85ff                     test       edi, edi
004ba018 743b                     je         0x4ba055
004ba01a 8b8600010000             mov        eax, dword ptr [esi + 0x100]
004ba020 85c0                     test       eax, eax
004ba022 7418                     je         0x4ba03c
004ba024 8b8014010000             mov        eax, dword ptr [eax + 0x114]
004ba02a 85c0                     test       eax, eax
004ba02c 740e                     je         0x4ba03c
004ba02e 8b90dc090000             mov        edx, dword ptr [eax + 0x9dc]
004ba034 039660160000             add        edx, dword ptr [esi + 0x1660]
004ba03a 03fa                     add        edi, edx
004ba03c 84c9                     test       cl, cl
004ba03e 7415                     je         0x4ba055
004ba040 8bc7                     mov        eax, edi
004ba042 5f                       pop        edi
004ba043 5e                       pop        esi
004ba044 5b                       pop        ebx
004ba045 8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004ba048 64890d00000000           mov        dword ptr fs:[0], ecx
004ba04f 8be5                     mov        esp, ebp
004ba051 5d                       pop        ebp
004ba052 c20400                   ret        4
004ba055 8b06                     mov        eax, dword ptr [esi]
004ba057 6a03                     push       3
004ba059 8bce                     mov        ecx, esi
004ba05b ff9044030000             call       dword ptr [eax + 0x344]
004ba061 8bf0                     mov        esi, eax
004ba063 8d8e38020000             lea        ecx, [esi + 0x238]
004ba069 e8f27ff4ff               call       0x402060
004ba06e 894508                   mov        dword ptr [ebp + 8], eax
004ba071 db4508                   fild       dword ptr [ebp + 8]
004ba074 8d8e40020000             lea        ecx, [esi + 0x240]
004ba07a d95d08                   fstp       dword ptr [ebp + 8]
004ba07d e82e93f7ff               call       0x4333b0
004ba082 d84d08                   fmul       dword ptr [ebp + 8]
004ba085 e8ba747400               call       0xc01544
004ba08a 8bc8                     mov        ecx, eax
004ba08c 0fafcf                   imul       ecx, edi
004ba08f b81f85eb51               mov        eax, 0x51eb851f
004ba094 f7e9                     imul       ecx
004ba096 8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004ba099 c1fa05                   sar        edx, 5
004ba09c 5f                       pop        edi
004ba09d 8bc2                     mov        eax, edx
004ba09f c1e81f                   shr        eax, 0x1f
004ba0a2 5e                       pop        esi
004ba0a3 03c2                     add        eax, edx
004ba0a5 5b                       pop        ebx
004ba0a6 64890d00000000           mov        dword ptr fs:[0], ecx
004ba0ad 8be5                     mov        esp, ebp
004ba0af 5d                       pop        ebp
004ba0b0 c20400                   ret        4
