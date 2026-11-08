00a30d20 55                       push       ebp
00a30d21 8bec                     mov        ebp, esp
00a30d23 6aff                     push       -1
00a30d25 6826e9c800               push       0xc8e926
00a30d2a 64a100000000             mov        eax, dword ptr fs:[0]
00a30d30 50                       push       eax
00a30d31 64892500000000           mov        dword ptr fs:[0], esp
00a30d38 83ec28                   sub        esp, 0x28
00a30d3b 53                       push       ebx
00a30d3c 57                       push       edi
00a30d3d 8bf9                     mov        edi, ecx
00a30d3f 8b4f7c                   mov        ecx, dword ptr [edi + 0x7c]
00a30d42 33db                     xor        ebx, ebx
00a30d44 3bcb                     cmp        ecx, ebx
00a30d46 897ddc                   mov        dword ptr [ebp - 0x24], edi
00a30d49 0f8482040000             je         0xa311d1
00a30d4f e83cb3a6ff               call       0x49c090
00a30d54 84c0                     test       al, al
00a30d56 0f8475040000             je         0xa311d1
00a30d5c 8b8790000000             mov        eax, dword ptr [edi + 0x90]
00a30d62 3bc3                     cmp        eax, ebx
00a30d64 c645f201                 mov        byte ptr [ebp - 0xe], 1
00a30d68 c645f101                 mov        byte ptr [ebp - 0xf], 1
00a30d6c 885df0                   mov        byte ptr [ebp - 0x10], bl
00a30d6f 895de4                   mov        dword ptr [ebp - 0x1c], ebx
00a30d72 0f8459040000             je         0xa311d1
00a30d78 8b8f94000000             mov        ecx, dword ptr [edi + 0x94]
00a30d7e 2bc8                     sub        ecx, eax
00a30d80 b893244992               mov        eax, 0x92492493
00a30d85 f7e9                     imul       ecx
00a30d87 03d1                     add        edx, ecx
00a30d89 c1fa04                   sar        edx, 4
00a30d8c 8bc2                     mov        eax, edx
00a30d8e c1e81f                   shr        eax, 0x1f
00a30d91 03c2                     add        eax, edx
00a30d93 8945e0                   mov        dword ptr [ebp - 0x20], eax
00a30d96 0f8435040000             je         0xa311d1
00a30d9c 8b8794000000             mov        eax, dword ptr [edi + 0x94]
00a30da2 56                       push       esi
00a30da3 8bb790000000             mov        esi, dword ptr [edi + 0x90]
00a30da9 3bf0                     cmp        esi, eax
00a30dab 8975e8                   mov        dword ptr [ebp - 0x18], esi
00a30dae 0f841c040000             je         0xa311d0
00a30db4 8b4614                   mov        eax, dword ptr [esi + 0x14]
00a30db7 3bc3                     cmp        eax, ebx
00a30db9 7e09                     jle        0xa30dc4
00a30dbb 394610                   cmp        dword ptr [esi + 0x10], eax
00a30dbe 0f8df1030000             jge        0xa311b5
00a30dc4 8a4619                   mov        al, byte ptr [esi + 0x19]
00a30dc7 84c0                     test       al, al
00a30dc9 0f85e6030000             jne        0xa311b5
00a30dcf 8a4618                   mov        al, byte ptr [esi + 0x18]
00a30dd2 84c0                     test       al, al
00a30dd4 0f84db030000             je         0xa311b5
00a30dda c645f300                 mov        byte ptr [ebp - 0xd], 0
00a30dde c645ef00                 mov        byte ptr [ebp - 0x11], 0
00a30de2 895dd0                   mov        dword ptr [ebp - 0x30], ebx
00a30de5 895dd4                   mov        dword ptr [ebp - 0x2c], ebx
00a30de8 895dd8                   mov        dword ptr [ebp - 0x28], ebx
00a30deb 8d477c                   lea        eax, [edi + 0x7c]
00a30dee 50                       push       eax
00a30def 8d4dcc                   lea        ecx, [ebp - 0x34]
00a30df2 895dfc                   mov        dword ptr [ebp - 4], ebx
00a30df5 e8f6d6a5ff               call       0x48e4f0
00a30dfa 8b5e04                   mov        ebx, dword ptr [esi + 4]
00a30dfd 8d4b24                   lea        ecx, [ebx + 0x24]
00a30e00 894de0                   mov        dword ptr [ebp - 0x20], ecx
00a30e03 3b5e08                   cmp        ebx, dword ptr [esi + 8]
00a30e06 0f8485030000             je         0xa31191
00a30e0c 8b03                     mov        eax, dword ptr [ebx]
00a30e0e 83f809                   cmp        eax, 9
00a30e11 742d                     je         0xa30e40
00a30e13 83f806                   cmp        eax, 6
00a30e16 7428                     je         0xa30e40
00a30e18 83f80a                   cmp        eax, 0xa
00a30e1b 7423                     je         0xa30e40
00a30e1d 83f80b                   cmp        eax, 0xb
00a30e20 741e                     je         0xa30e40
00a30e22 83f80c                   cmp        eax, 0xc
00a30e25 7419                     je         0xa30e40
00a30e27 83f80d                   cmp        eax, 0xd
00a30e2a 7414                     je         0xa30e40
00a30e2c 83f80e                   cmp        eax, 0xe
00a30e2f 740f                     je         0xa30e40
00a30e31 83f80f                   cmp        eax, 0xf
00a30e34 740a                     je         0xa30e40
00a30e36 83f810                   cmp        eax, 0x10
00a30e39 7405                     je         0xa30e40
00a30e3b 83f811                   cmp        eax, 0x11
00a30e3e 7510                     jne        0xa30e50
00a30e40 83f811                   cmp        eax, 0x11
00a30e43 0f8548030000             jne        0xa31191
00a30e49 b101                     mov        cl, 1
00a30e4b 884df3                   mov        byte ptr [ebp - 0xd], cl
00a30e4e eb03                     jmp        0xa30e53
00a30e50 8a4df3                   mov        cl, byte ptr [ebp - 0xd]
00a30e53 83f831                   cmp        eax, 0x31
00a30e56 0f870b030000             ja         0xa31167
00a30e5c 0fb6900c12a300           movzx      edx, byte ptr [eax + 0xa3120c]
00a30e63 ff2495e411a300           jmp        dword ptr [edx*4 + 0xa311e4]
00a30e6a 6a00                     push       0
00a30e6c 8bcb                     mov        ecx, ebx
00a30e6e e88d22b0ff               call       0x533100
00a30e73 85c0                     test       eax, eax
00a30e75 751b                     jne        0xa30e92
00a30e77 8845f1                   mov        byte ptr [ebp - 0xf], al
00a30e7a 8845f0                   mov        byte ptr [ebp - 0x10], al
00a30e7d 8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00a30e80 83c334                   add        ebx, 0x34
00a30e83 83c034                   add        eax, 0x34
00a30e86 c645f201                 mov        byte ptr [ebp - 0xe], 1
00a30e8a 8945e0                   mov        dword ptr [ebp - 0x20], eax
00a30e8d e971ffffff               jmp        0xa30e03
00a30e92 83f801                   cmp        eax, 1
00a30e95 751c                     jne        0xa30eb3
00a30e97 8845f1                   mov        byte ptr [ebp - 0xf], al
00a30e9a 8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00a30e9d 83c334                   add        ebx, 0x34
00a30ea0 83c034                   add        eax, 0x34
00a30ea3 c645f200                 mov        byte ptr [ebp - 0xe], 0
00a30ea7 c645f000                 mov        byte ptr [ebp - 0x10], 0
00a30eab 8945e0                   mov        dword ptr [ebp - 0x20], eax
00a30eae e950ffffff               jmp        0xa30e03
00a30eb3 83f802                   cmp        eax, 2
00a30eb6 0f85c1020000             jne        0xa3117d
00a30ebc 8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00a30ebf 83c334                   add        ebx, 0x34
00a30ec2 83c034                   add        eax, 0x34
00a30ec5 c645f200                 mov        byte ptr [ebp - 0xe], 0
00a30ec9 c645f100                 mov        byte ptr [ebp - 0xf], 0
00a30ecd c645f001                 mov        byte ptr [ebp - 0x10], 1
00a30ed1 8945e0                   mov        dword ptr [ebp - 0x20], eax
00a30ed4 e92affffff               jmp        0xa30e03
00a30ed9 8b45d0                   mov        eax, dword ptr [ebp - 0x30]
00a30edc 85c0                     test       eax, eax
00a30ede 7504                     jne        0xa30ee4
00a30ee0 33f6                     xor        esi, esi
00a30ee2 eb08                     jmp        0xa30eec
00a30ee4 8b75d4                   mov        esi, dword ptr [ebp - 0x2c]
00a30ee7 2bf0                     sub        esi, eax
00a30ee9 c1fe02                   sar        esi, 2
00a30eec 8b4de0                   mov        ecx, dword ptr [ebp - 0x20]
00a30eef 6a01                     push       1
00a30ef1 e88ad80000               call       0xa3e780
00a30ef6 8b4de0                   mov        ecx, dword ptr [ebp - 0x20]
00a30ef9 6a00                     push       0
00a30efb 8bf8                     mov        edi, eax
00a30efd e87ed80000               call       0xa3e780
00a30f02 8b0f                     mov        ecx, dword ptr [edi]
00a30f04 8b10                     mov        edx, dword ptr [eax]
00a30f06 51                       push       ecx
00a30f07 52                       push       edx
00a30f08 56                       push       esi
00a30f09 e8c2e4b3ff               call       0x56f3d0
00a30f0e 8b7ddc                   mov        edi, dword ptr [ebp - 0x24]
00a30f11 83c40c                   add        esp, 0xc
00a30f14 84c0                     test       al, al
00a30f16 0f8472020000             je         0xa3118e
00a30f1c 85f6                     test       esi, esi
00a30f1e 8b75e8                   mov        esi, dword ptr [ebp - 0x18]
00a30f21 0f8556020000             jne        0xa3117d
00a30f27 8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00a30f2a 83c334                   add        ebx, 0x34
00a30f2d 83c034                   add        eax, 0x34
00a30f30 c645ef01                 mov        byte ptr [ebp - 0x11], 1
00a30f34 8945e0                   mov        dword ptr [ebp - 0x20], eax
00a30f37 e9c7feffff               jmp        0xa30e03
00a30f3c 8b4508                   mov        eax, dword ptr [ebp + 8]
00a30f3f 85c0                     test       eax, eax
00a30f41 7522                     jne        0xa30f65
00a30f43 8a45f2                   mov        al, byte ptr [ebp - 0xe]
00a30f46 84c0                     test       al, al
00a30f48 7406                     je         0xa30f50
00a30f4a c645f301                 mov        byte ptr [ebp - 0xd], 1
00a30f4e eb41                     jmp        0xa30f91
00a30f50 8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00a30f53 83c334                   add        ebx, 0x34
00a30f56 83c034                   add        eax, 0x34
00a30f59 c645f300                 mov        byte ptr [ebp - 0xd], 0
00a30f5d 8945e0                   mov        dword ptr [ebp - 0x20], eax
00a30f60 e99efeffff               jmp        0xa30e03
00a30f65 83f801                   cmp        eax, 1
00a30f68 750d                     jne        0xa30f77
00a30f6a 8a45f1                   mov        al, byte ptr [ebp - 0xf]
00a30f6d 84c0                     test       al, al
00a30f6f 74df                     je         0xa30f50
00a30f71 c645f301                 mov        byte ptr [ebp - 0xd], 1
00a30f75 eb1a                     jmp        0xa30f91
00a30f77 83f802                   cmp        eax, 2
00a30f7a 750d                     jne        0xa30f89
00a30f7c 8a45f0                   mov        al, byte ptr [ebp - 0x10]
00a30f7f 84c0                     test       al, al
00a30f81 74cd                     je         0xa30f50
00a30f83 c645f301                 mov        byte ptr [ebp - 0xd], 1
00a30f87 eb08                     jmp        0xa30f91
00a30f89 84c9                     test       cl, cl
00a30f8b 0f84ec010000             je         0xa3117d
00a30f91 6a00                     push       0
00a30f93 8bcb                     mov        ecx, ebx
00a30f95 e86621b0ff               call       0x533100
00a30f9a 8b4dd0                   mov        ecx, dword ptr [ebp - 0x30]
00a30f9d 85c9                     test       ecx, ecx
00a30f9f 740c                     je         0xa30fad
00a30fa1 8b45d4                   mov        eax, dword ptr [ebp - 0x2c]
00a30fa4 2bc1                     sub        eax, ecx
00a30fa6 c1f802                   sar        eax, 2
00a30fa9 85c0                     test       eax, eax
00a30fab 770b                     ja         0xa30fb8
00a30fad 8a45ef                   mov        al, byte ptr [ebp - 0x11]
00a30fb0 84c0                     test       al, al
00a30fb2 0f84c5010000             je         0xa3117d
00a30fb8 8b4e10                   mov        ecx, dword ptr [esi + 0x10]
00a30fbb 6a00                     push       0
00a30fbd 41                       inc        ecx
00a30fbe 8d45cc                   lea        eax, [ebp - 0x34]
00a30fc1 50                       push       eax
00a30fc2 894e10                   mov        dword ptr [esi + 0x10], ecx
00a30fc5 8b4de4                   mov        ecx, dword ptr [ebp - 0x1c]
00a30fc8 53                       push       ebx
00a30fc9 51                       push       ecx
00a30fca 8bcf                     mov        ecx, edi
00a30fcc e84f820100               call       0xa49220
00a30fd1 8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00a30fd4 83c334                   add        ebx, 0x34
00a30fd7 83c034                   add        eax, 0x34
00a30fda 8945e0                   mov        dword ptr [ebp - 0x20], eax
00a30fdd e921feffff               jmp        0xa30e03
00a30fe2 8b4f7c                   mov        ecx, dword ptr [edi + 0x7c]
00a30fe5 8b11                     mov        edx, dword ptr [ecx]
00a30fe7 ff9208010000             call       dword ptr [edx + 0x108]
00a30fed 85c0                     test       eax, eax
00a30fef 0f8488010000             je         0xa3117d
00a30ff5 8b4508                   mov        eax, dword ptr [ebp + 8]
00a30ff8 85c0                     test       eax, eax
00a30ffa 7511                     jne        0xa3100d
00a30ffc 8a45f2                   mov        al, byte ptr [ebp - 0xe]
00a30fff 84c0                     test       al, al
00a31001 0f8449ffffff             je         0xa30f50
00a31007 c645f301                 mov        byte ptr [ebp - 0xd], 1
00a3100b eb37                     jmp        0xa31044
00a3100d 83f801                   cmp        eax, 1
00a31010 7511                     jne        0xa31023
00a31012 8a45f1                   mov        al, byte ptr [ebp - 0xf]
00a31015 84c0                     test       al, al
00a31017 0f8433ffffff             je         0xa30f50
00a3101d c645f301                 mov        byte ptr [ebp - 0xd], 1
00a31021 eb21                     jmp        0xa31044
00a31023 83f802                   cmp        eax, 2
00a31026 7511                     jne        0xa31039
00a31028 8a45f0                   mov        al, byte ptr [ebp - 0x10]
00a3102b 84c0                     test       al, al
00a3102d 0f841dffffff             je         0xa30f50
00a31033 c645f301                 mov        byte ptr [ebp - 0xd], 1
00a31037 eb0b                     jmp        0xa31044
00a31039 8a45f3                   mov        al, byte ptr [ebp - 0xd]
00a3103c 84c0                     test       al, al
00a3103e 0f8439010000             je         0xa3117d
00a31044 8b4f7c                   mov        ecx, dword ptr [edi + 0x7c]
00a31047 8b01                     mov        eax, dword ptr [ecx]
00a31049 ff9008010000             call       dword ptr [eax + 0x108]
00a3104f 85c0                     test       eax, eax
00a31051 0f8426010000             je         0xa3117d
00a31057 6a00                     push       0
00a31059 8bcb                     mov        ecx, ebx
00a3105b e8a020b0ff               call       0x533100
00a31060 8b4dd0                   mov        ecx, dword ptr [ebp - 0x30]
00a31063 85c9                     test       ecx, ecx
00a31065 740c                     je         0xa31073
00a31067 8b45d4                   mov        eax, dword ptr [ebp - 0x2c]
00a3106a 2bc1                     sub        eax, ecx
00a3106c c1f802                   sar        eax, 2
00a3106f 85c0                     test       eax, eax
00a31071 770b                     ja         0xa3107e
00a31073 8a45ef                   mov        al, byte ptr [ebp - 0x11]
00a31076 84c0                     test       al, al
00a31078 0f84ff000000             je         0xa3117d
00a3107e 8b4e10                   mov        ecx, dword ptr [esi + 0x10]
00a31081 8b55e4                   mov        edx, dword ptr [ebp - 0x1c]
00a31084 41                       inc        ecx
00a31085 894e10                   mov        dword ptr [esi + 0x10], ecx
00a31088 6a01                     push       1
00a3108a 8d4dcc                   lea        ecx, [ebp - 0x34]
00a3108d 51                       push       ecx
00a3108e 53                       push       ebx
00a3108f 52                       push       edx
00a31090 8bcf                     mov        ecx, edi
00a31092 e889810100               call       0xa49220
00a31097 8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00a3109a 83c334                   add        ebx, 0x34
00a3109d 83c034                   add        eax, 0x34
00a310a0 8945e0                   mov        dword ptr [ebp - 0x20], eax
00a310a3 e95bfdffff               jmp        0xa30e03
00a310a8 6a00                     push       0
00a310aa 8bcb                     mov        ecx, ebx
00a310ac e84f20b0ff               call       0x533100
00a310b1 6a01                     push       1
00a310b3 8bcb                     mov        ecx, ebx
00a310b5 8bf0                     mov        esi, eax
00a310b7 e84420b0ff               call       0x533100
00a310bc 8d4dcc                   lea        ecx, [ebp - 0x34]
00a310bf 51                       push       ecx
00a310c0 50                       push       eax
00a310c1 56                       push       esi
00a310c2 8bcf                     mov        ecx, edi
00a310c4 e8078f0100               call       0xa49fd0
00a310c9 8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00a310cc 8b75e8                   mov        esi, dword ptr [ebp - 0x18]
00a310cf 83c334                   add        ebx, 0x34
00a310d2 83c034                   add        eax, 0x34
00a310d5 8945e0                   mov        dword ptr [ebp - 0x20], eax
00a310d8 e926fdffff               jmp        0xa30e03
00a310dd 84c9                     test       cl, cl
00a310df 0f8498000000             je         0xa3117d
00a310e5 6a00                     push       0
00a310e7 8bcb                     mov        ecx, ebx
00a310e9 e81220b0ff               call       0x533100
00a310ee 8b4dd0                   mov        ecx, dword ptr [ebp - 0x30]
00a310f1 85c9                     test       ecx, ecx
00a310f3 740c                     je         0xa31101
00a310f5 8b45d4                   mov        eax, dword ptr [ebp - 0x2c]
00a310f8 2bc1                     sub        eax, ecx
00a310fa c1f802                   sar        eax, 2
00a310fd 85c0                     test       eax, eax
00a310ff 7707                     ja         0xa31108
00a31101 8a45ef                   mov        al, byte ptr [ebp - 0x11]
00a31104 84c0                     test       al, al
00a31106 7475                     je         0xa3117d
00a31108 8b5610                   mov        edx, dword ptr [esi + 0x10]
00a3110b 8b45e4                   mov        eax, dword ptr [ebp - 0x1c]
00a3110e 42                       inc        edx
00a3110f 6a00                     push       0
00a31111 895610                   mov        dword ptr [esi + 0x10], edx
00a31114 8d55cc                   lea        edx, [ebp - 0x34]
00a31117 52                       push       edx
00a31118 53                       push       ebx
00a31119 50                       push       eax
00a3111a 8bcf                     mov        ecx, edi
00a3111c e8ff800100               call       0xa49220
00a31121 8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00a31124 83c334                   add        ebx, 0x34
00a31127 83c034                   add        eax, 0x34
00a3112a 8945e0                   mov        dword ptr [ebp - 0x20], eax
00a3112d e9d1fcffff               jmp        0xa30e03
00a31132 8d4dcc                   lea        ecx, [ebp - 0x34]
00a31135 51                       push       ecx
00a31136 53                       push       ebx
00a31137 8bcf                     mov        ecx, edi
00a31139 e842850100               call       0xa49680
00a3113e 8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00a31141 83c334                   add        ebx, 0x34
00a31144 83c034                   add        eax, 0x34
00a31147 8945e0                   mov        dword ptr [ebp - 0x20], eax
00a3114a e9b4fcffff               jmp        0xa30e03
00a3114f 8b5720                   mov        edx, dword ptr [edi + 0x20]
00a31152 8b8224010000             mov        eax, dword ptr [edx + 0x124]
00a31158 8d4dcc                   lea        ecx, [ebp - 0x34]
00a3115b 51                       push       ecx
00a3115c 53                       push       ebx
00a3115d 50                       push       eax
00a3115e 8bcf                     mov        ecx, edi
00a31160 e85b790100               call       0xa48ac0
00a31165 eb0c                     jmp        0xa31173
00a31167 8d55cc                   lea        edx, [ebp - 0x34]
00a3116a 52                       push       edx
00a3116b 53                       push       ebx
00a3116c 8bcf                     mov        ecx, edi
00a3116e e80d920100               call       0xa4a380
00a31173 f6d8                     neg        al
00a31175 1ac0                     sbb        al, al
00a31177 fec0                     inc        al
00a31179 84c0                     test       al, al
00a3117b 7514                     jne        0xa31191
00a3117d 8b45e0                   mov        eax, dword ptr [ebp - 0x20]
00a31180 83c334                   add        ebx, 0x34
00a31183 83c034                   add        eax, 0x34
00a31186 8945e0                   mov        dword ptr [ebp - 0x20], eax
00a31189 e975fcffff               jmp        0xa30e03
00a3118e 8b75e8                   mov        esi, dword ptr [ebp - 0x18]
00a31191 8b45d0                   mov        eax, dword ptr [ebp - 0x30]
00a31194 33db                     xor        ebx, ebx
00a31196 3bc3                     cmp        eax, ebx
00a31198 c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
00a3119f 7409                     je         0xa311aa
00a311a1 50                       push       eax
00a311a2 e836ee1c00               call       0xbfffdd
00a311a7 83c404                   add        esp, 4
00a311aa 895dd0                   mov        dword ptr [ebp - 0x30], ebx
00a311ad 895dd4                   mov        dword ptr [ebp - 0x2c], ebx
00a311b0 895dd8                   mov        dword ptr [ebp - 0x28], ebx
00a311b3 33db                     xor        ebx, ebx
00a311b5 8b4de4                   mov        ecx, dword ptr [ebp - 0x1c]
00a311b8 8b8794000000             mov        eax, dword ptr [edi + 0x94]
00a311be 83c61c                   add        esi, 0x1c
00a311c1 41                       inc        ecx
00a311c2 3bf0                     cmp        esi, eax
00a311c4 8975e8                   mov        dword ptr [ebp - 0x18], esi
00a311c7 894de4                   mov        dword ptr [ebp - 0x1c], ecx
00a311ca 0f85e4fbffff             jne        0xa30db4
00a311d0 5e                       pop        esi
00a311d1 8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a311d4 5f                       pop        edi
00a311d5 5b                       pop        ebx
00a311d6 64890d00000000           mov        dword ptr fs:[0], ecx
00a311dd 8be5                     mov        esp, ebp
00a311df 5d                       pop        ebp
00a311e0 c20c00                   ret        0xc
00a311e3 90                       nop        
00a311e4 3c0f                     cmp        al, 0xf
00a311e6 a3004f11a3               mov        dword ptr [0xa3114f00], eax
00a311eb 0032                     add        byte ptr [edx], dh
00a311ed 11a3007d11a3             adc        dword ptr [ebx - 0x5cee8300], esp
00a311f3 00d9                     add        cl, bl
00a311f5 0e                       push       cs
00a311f6 a300dd10a3               mov        dword ptr [0xa310dd00], eax
00a311fb 006a0e                   add        byte ptr [edx + 0xe], ch
00a311fe a300a810a3               mov        dword ptr [0xa310a800], eax
00a31203 00e2                     add        dl, ah
00a31205 0fa300                   bt         dword ptr [eax], eax
00a31208 6711a30000               adc        dword ptr [bp + di], esp
00a3120d 0109                     add        dword ptr [ecx], ecx
00a3120f 0909                     or         dword ptr [ecx], ecx
00a31211 0909                     or         dword ptr [ecx], ecx
00a31213 0909                     or         dword ptr [ecx], ecx
00a31215 0909                     or         dword ptr [ecx], ecx
00a31217 0909                     or         dword ptr [ecx], ecx
00a31219 0909                     or         dword ptr [ecx], ecx
00a3121b 0909                     or         dword ptr [ecx], ecx
00a3121d 0909                     or         dword ptr [ecx], ecx
00a3121f 0909                     or         dword ptr [ecx], ecx
00a31221 0909                     or         dword ptr [ecx], ecx
00a31223 0909                     or         dword ptr [ecx], ecx
00a31225 0203                     add        al, byte ptr [ebx]
00a31227 0909                     or         dword ptr [ecx], ecx
00a31229 0409                     add        al, 9
00a3122b 0909                     or         dword ptr [ecx], ecx
00a3122d 0509090909               add        eax, 0x9090909
00a31232 0909                     or         dword ptr [ecx], ecx
00a31234 0909                     or         dword ptr [ecx], ecx
00a31236 0909                     or         dword ptr [ecx], ecx
00a31238 0909                     or         dword ptr [ecx], ecx
00a3123a 0906                     or         dword ptr [esi], eax
00a3123c 07                       pop        es
00a3123d 08                       .byte      0x08
