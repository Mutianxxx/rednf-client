00a26990 55                       push       ebp
00a26991 8bec                     mov        ebp, esp
00a26993 83ec14                   sub        esp, 0x14
00a26996 56                       push       esi
00a26997 57                       push       edi
00a26998 8bf1                     mov        esi, ecx
00a2699a e8c1daffff               call       0xa24460
00a2699f 8b8680010000             mov        eax, dword ptr [esi + 0x180]
00a269a5 8b38                     mov        edi, dword ptr [eax]
00a269a7 3bf8                     cmp        edi, eax
00a269a9 897df8                   mov        dword ptr [ebp - 8], edi
00a269ac 7435                     je         0xa269e3
00a269ae eb03                     jmp        0xa269b3
00a269b0 8b7df8                   mov        edi, dword ptr [ebp - 8]
00a269b3 8b4708                   mov        eax, dword ptr [edi + 8]
00a269b6 85c0                     test       eax, eax
00a269b8 7d29                     jge        0xa269e3
00a269ba 8b4f0c                   mov        ecx, dword ptr [edi + 0xc]
00a269bd 85c9                     test       ecx, ecx
00a269bf 7415                     je         0xa269d6
00a269c1 8b4514                   mov        eax, dword ptr [ebp + 0x14]
00a269c4 8b5510                   mov        edx, dword ptr [ebp + 0x10]
00a269c7 50                       push       eax
00a269c8 8b450c                   mov        eax, dword ptr [ebp + 0xc]
00a269cb 52                       push       edx
00a269cc 8b5508                   mov        edx, dword ptr [ebp + 8]
00a269cf 50                       push       eax
00a269d0 52                       push       edx
00a269d1 e8baffffff               call       0xa26990
00a269d6 8b07                     mov        eax, dword ptr [edi]
00a269d8 3b8680010000             cmp        eax, dword ptr [esi + 0x180]
00a269de 8945f8                   mov        dword ptr [ebp - 8], eax
00a269e1 75cd                     jne        0xa269b0
00a269e3 8b4640                   mov        eax, dword ptr [esi + 0x40]
00a269e6 85c0                     test       eax, eax
00a269e8 53                       push       ebx
00a269e9 0f840c010000             je         0xa26afb
00a269ef 8b4e44                   mov        ecx, dword ptr [esi + 0x44]
00a269f2 8d5e34                   lea        ebx, [esi + 0x34]
00a269f5 8b4310                   mov        eax, dword ptr [ebx + 0x10]
00a269f8 03430c                   add        eax, dword ptr [ebx + 0xc]
00a269fb 3bdb                     cmp        ebx, ebx
00a269fd 894df0                   mov        dword ptr [ebp - 0x10], ecx
00a26a00 7508                     jne        0xa26a0a
00a26a02 3bc8                     cmp        ecx, eax
00a26a04 0f8497000000             je         0xa26aa1
00a26a0a 8b7b08                   mov        edi, dword ptr [ebx + 8]
00a26a0d 8bc1                     mov        eax, ecx
00a26a0f c1e808                   shr        eax, 8
00a26a12 8bd1                     mov        edx, ecx
00a26a14 c1e002                   shl        eax, 2
00a26a17 8b3c38                   mov        edi, dword ptr [eax + edi]
00a26a1a 81e2ff000000             and        edx, 0xff
00a26a20 c1e205                   shl        edx, 5
00a26a23 8b3c3a                   mov        edi, dword ptr [edx + edi]
00a26a26 85ff                     test       edi, edi
00a26a28 7471                     je         0xa26a9b
00a26a2a 8b4b08                   mov        ecx, dword ptr [ebx + 8]
00a26a2d 8b0c08                   mov        ecx, dword ptr [eax + ecx]
00a26a30 837c111c00               cmp        dword ptr [ecx + edx + 0x1c], 0
00a26a35 8b4b08                   mov        ecx, dword ptr [ebx + 8]
00a26a38 8b0408                   mov        eax, dword ptr [eax + ecx]
00a26a3b 751d                     jne        0xa26a5a
00a26a3d 8b4c1018                 mov        ecx, dword ptr [eax + edx + 0x18]
00a26a41 03c2                     add        eax, edx
00a26a43 0fb65017                 movzx      edx, byte ptr [eax + 0x17]
00a26a47 51                       push       ecx
00a26a48 8b4814                   mov        ecx, dword ptr [eax + 0x14]
00a26a4b c1e218                   shl        edx, 0x18
00a26a4e 81caffffff00             or         edx, 0xffffff
00a26a54 52                       push       edx
00a26a55 51                       push       ecx
00a26a56 6a00                     push       0
00a26a58 eb1b                     jmp        0xa26a75
00a26a5a 8b4c1018                 mov        ecx, dword ptr [eax + edx + 0x18]
00a26a5e 03c2                     add        eax, edx
00a26a60 0fb65017                 movzx      edx, byte ptr [eax + 0x17]
00a26a64 51                       push       ecx
00a26a65 8b4814                   mov        ecx, dword ptr [eax + 0x14]
00a26a68 c1e218                   shl        edx, 0x18
00a26a6b 81caffffff00             or         edx, 0xffffff
00a26a71 52                       push       edx
00a26a72 51                       push       ecx
00a26a73 6a01                     push       1
00a26a75 8b501c                   mov        edx, dword ptr [eax + 0x1c]
00a26a78 8b4810                   mov        ecx, dword ptr [eax + 0x10]
00a26a7b 52                       push       edx
00a26a7c 33d2                     xor        edx, edx
00a26a7e 8a500c                   mov        dl, byte ptr [eax + 0xc]
00a26a81 51                       push       ecx
00a26a82 8b4808                   mov        ecx, dword ptr [eax + 8]
00a26a85 52                       push       edx
00a26a86 8b5004                   mov        edx, dword ptr [eax + 4]
00a26a89 a12ca90d01               mov        eax, dword ptr [0x10da92c]
00a26a8e 51                       push       ecx
00a26a8f 52                       push       edx
00a26a90 8bcf                     mov        ecx, edi
00a26a92 50                       push       eax
00a26a93 e838fbffff               call       0xa265d0
00a26a98 8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
00a26a9b 41                       inc        ecx
00a26a9c e954ffffff               jmp        0xa269f5
00a26aa1 8b4308                   mov        eax, dword ptr [ebx + 8]
00a26aa4 85c0                     test       eax, eax
00a26aa6 7453                     je         0xa26afb
00a26aa8 8b4b10                   mov        ecx, dword ptr [ebx + 0x10]
00a26aab 8b430c                   mov        eax, dword ptr [ebx + 0xc]
00a26aae 03c1                     add        eax, ecx
00a26ab0 8bd3                     mov        edx, ebx
00a26ab2 3bda                     cmp        ebx, edx
00a26ab4 7504                     jne        0xa26aba
00a26ab6 3bc8                     cmp        ecx, eax
00a26ab8 7403                     je         0xa26abd
00a26aba 41                       inc        ecx
00a26abb ebf5                     jmp        0xa26ab2
00a26abd 8b4304                   mov        eax, dword ptr [ebx + 4]
00a26ac0 33ff                     xor        edi, edi
00a26ac2 85c0                     test       eax, eax
00a26ac4 897b0c                   mov        dword ptr [ebx + 0xc], edi
00a26ac7 897b10                   mov        dword ptr [ebx + 0x10], edi
00a26aca 761b                     jbe        0xa26ae7
00a26acc 8d642400                 lea        esp, [esp]
00a26ad0 8b4b08                   mov        ecx, dword ptr [ebx + 8]
00a26ad3 8b14b9                   mov        edx, dword ptr [ecx + edi*4]
00a26ad6 52                       push       edx
00a26ad7 e82d961d00               call       0xc00109
00a26adc 8b4304                   mov        eax, dword ptr [ebx + 4]
00a26adf 83c404                   add        esp, 4
00a26ae2 47                       inc        edi
00a26ae3 3bf8                     cmp        edi, eax
00a26ae5 72e9                     jb         0xa26ad0
00a26ae7 8b4308                   mov        eax, dword ptr [ebx + 8]
00a26aea 50                       push       eax
00a26aeb e819961d00               call       0xc00109
00a26af0 83c404                   add        esp, 4
00a26af3 33c0                     xor        eax, eax
00a26af5 894308                   mov        dword ptr [ebx + 8], eax
00a26af8 894304                   mov        dword ptr [ebx + 4], eax
00a26afb a174070c01               mov        eax, dword ptr [0x10c0774]
00a26b00 85c0                     test       eax, eax
00a26b02 7e54                     jle        0xa26b58
00a26b04 803e00                   cmp        byte ptr [esi], 0
00a26b07 744f                     je         0xa26b58
00a26b09 8b4608                   mov        eax, dword ptr [esi + 8]
00a26b0c 85c0                     test       eax, eax
00a26b0e 7448                     je         0xa26b58
00a26b10 8b4e0c                   mov        ecx, dword ptr [esi + 0xc]
00a26b13 2bc8                     sub        ecx, eax
00a26b15 b867666666               mov        eax, 0x66666667
00a26b1a f7e9                     imul       ecx
00a26b1c c1fa03                   sar        edx, 3
00a26b1f 8bca                     mov        ecx, edx
00a26b21 c1e91f                   shr        ecx, 0x1f
00a26b24 03ca                     add        ecx, edx
00a26b26 894df0                   mov        dword ptr [ebp - 0x10], ecx
00a26b29 742d                     je         0xa26b58
00a26b2b 8b5e08                   mov        ebx, dword ptr [esi + 8]
00a26b2e 3b5e0c                   cmp        ebx, dword ptr [esi + 0xc]
00a26b31 c645ff01                 mov        byte ptr [ebp - 1], 1
00a26b35 0f845d010000             je         0xa26c98
00a26b3b eb03                     jmp        0xa26b40
00a26b3d 8d4900                   lea        ecx, [ecx]
00a26b40 8a4308                   mov        al, byte ptr [ebx + 8]
00a26b43 84c0                     test       al, al
00a26b45 0f853f010000             jne        0xa26c8a
00a26b4b 8b7e14                   mov        edi, dword ptr [esi + 0x14]
00a26b4e 85ff                     test       edi, edi
00a26b50 750f                     jne        0xa26b61
00a26b52 0fb64303                 movzx      eax, byte ptr [ebx + 3]
00a26b56 eb58                     jmp        0xa26bb0
00a26b58 c645ff00                 mov        byte ptr [ebp - 1], 0
00a26b5c e937010000               jmp        0xa26c98
00a26b61 8d4e48                   lea        ecx, [esi + 0x48]
00a26b64 e897030e00               call       0xb06f00
00a26b69 8b530c                   mov        edx, dword ptr [ebx + 0xc]
00a26b6c 8b4b10                   mov        ecx, dword ptr [ebx + 0x10]
00a26b6f 8955f0                   mov        dword ptr [ebp - 0x10], edx
00a26b72 894df4                   mov        dword ptr [ebp - 0xc], ecx
00a26b75 99                       cdq        
00a26b76 8d0c3f                   lea        ecx, [edi + edi]
00a26b79 f7f9                     idiv       ecx
00a26b7b 57                       push       edi
00a26b7c 3bd7                     cmp        edx, edi
00a26b7e 7d10                     jge        0xa26b90
00a26b80 db45f0                   fild       dword ptr [ebp - 0x10]
00a26b83 52                       push       edx
00a26b84 83ec08                   sub        esp, 8
00a26b87 d95c2404                 fstp       dword ptr [esp + 4]
00a26b8b db45f4                   fild       dword ptr [ebp - 0xc]
00a26b8e eb10                     jmp        0xa26ba0
00a26b90 db45f4                   fild       dword ptr [ebp - 0xc]
00a26b93 2bd7                     sub        edx, edi
00a26b95 52                       push       edx
00a26b96 83ec08                   sub        esp, 8
00a26b99 d95c2404                 fstp       dword ptr [esp + 4]
00a26b9d db45f0                   fild       dword ptr [ebp - 0x10]
00a26ba0 d91c24                   fstp       dword ptr [esp]
00a26ba3 e8082e0e00               call       0xb099b0
00a26ba8 83c410                   add        esp, 0x10
00a26bab e894a91d00               call       0xc01544
00a26bb0 0fb60b                   movzx      ecx, byte ptr [ebx]
00a26bb3 33d2                     xor        edx, edx
00a26bb5 8af0                     mov        dh, al
00a26bb7 0fb64301                 movzx      eax, byte ptr [ebx + 1]
00a26bbb 6a00                     push       0
00a26bbd 8a5302                   mov        dl, byte ptr [ebx + 2]
00a26bc0 c1e208                   shl        edx, 8
00a26bc3 0bd0                     or         edx, eax
00a26bc5 c1e208                   shl        edx, 8
00a26bc8 0bd1                     or         edx, ecx
00a26bca 8bc2                     mov        eax, edx
00a26bcc 8b5514                   mov        edx, dword ptr [ebp + 0x14]
00a26bcf 8bf8                     mov        edi, eax
00a26bd1 c1ef18                   shr        edi, 0x18
00a26bd4 c1e718                   shl        edi, 0x18
00a26bd7 81cfffffff00             or         edi, 0xffffff
00a26bdd 57                       push       edi
00a26bde 50                       push       eax
00a26bdf 6a01                     push       1
00a26be1 6a02                     push       2
00a26be3 8d8ea8000000             lea        ecx, [esi + 0xa8]
00a26be9 51                       push       ecx
00a26bea 8b4b04                   mov        ecx, dword ptr [ebx + 4]
00a26bed 52                       push       edx
00a26bee 8b5508                   mov        edx, dword ptr [ebp + 8]
00a26bf1 8945f4                   mov        dword ptr [ebp - 0xc], eax
00a26bf4 8b4510                   mov        eax, dword ptr [ebp + 0x10]
00a26bf7 50                       push       eax
00a26bf8 034d0c                   add        ecx, dword ptr [ebp + 0xc]
00a26bfb 51                       push       ecx
00a26bfc 52                       push       edx
00a26bfd 8bce                     mov        ecx, esi
00a26bff e88cd2ffff               call       0xa23e90
00a26c04 8b45f4                   mov        eax, dword ptr [ebp - 0xc]
00a26c07 8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
00a26c0a 8b5510                   mov        edx, dword ptr [ebp + 0x10]
00a26c0d 6a00                     push       0
00a26c0f 57                       push       edi
00a26c10 50                       push       eax
00a26c11 6a01                     push       1
00a26c13 6a02                     push       2
00a26c15 8d86a8000000             lea        eax, [esi + 0xa8]
00a26c1b 50                       push       eax
00a26c1c 8b450c                   mov        eax, dword ptr [ebp + 0xc]
00a26c1f 51                       push       ecx
00a26c20 8b4d08                   mov        ecx, dword ptr [ebp + 8]
00a26c23 52                       push       edx
00a26c24 2b4304                   sub        eax, dword ptr [ebx + 4]
00a26c27 50                       push       eax
00a26c28 51                       push       ecx
00a26c29 8bce                     mov        ecx, esi
00a26c2b e860d2ffff               call       0xa23e90
00a26c30 8b55f4                   mov        edx, dword ptr [ebp - 0xc]
00a26c33 8b4b04                   mov        ecx, dword ptr [ebx + 4]
00a26c36 6a00                     push       0
00a26c38 57                       push       edi
00a26c39 52                       push       edx
00a26c3a 8b550c                   mov        edx, dword ptr [ebp + 0xc]
00a26c3d 6a01                     push       1
00a26c3f 6a02                     push       2
00a26c41 8d86a8000000             lea        eax, [esi + 0xa8]
00a26c47 50                       push       eax
00a26c48 8b4514                   mov        eax, dword ptr [ebp + 0x14]
00a26c4b 50                       push       eax
00a26c4c 034d10                   add        ecx, dword ptr [ebp + 0x10]
00a26c4f 8b4508                   mov        eax, dword ptr [ebp + 8]
00a26c52 51                       push       ecx
00a26c53 52                       push       edx
00a26c54 50                       push       eax
00a26c55 8bce                     mov        ecx, esi
00a26c57 e834d2ffff               call       0xa23e90
00a26c5c 8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a26c5f 6a00                     push       0
00a26c61 57                       push       edi
00a26c62 51                       push       ecx
00a26c63 6a01                     push       1
00a26c65 6a02                     push       2
00a26c67 8d86a8000000             lea        eax, [esi + 0xa8]
00a26c6d 8b4b04                   mov        ecx, dword ptr [ebx + 4]
00a26c70 8b5514                   mov        edx, dword ptr [ebp + 0x14]
00a26c73 50                       push       eax
00a26c74 8b4510                   mov        eax, dword ptr [ebp + 0x10]
00a26c77 52                       push       edx
00a26c78 8b5508                   mov        edx, dword ptr [ebp + 8]
00a26c7b 2bc1                     sub        eax, ecx
00a26c7d 8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00a26c80 50                       push       eax
00a26c81 51                       push       ecx
00a26c82 52                       push       edx
00a26c83 8bce                     mov        ecx, esi
00a26c85 e806d2ffff               call       0xa23e90
00a26c8a 8b460c                   mov        eax, dword ptr [esi + 0xc]
00a26c8d 83c314                   add        ebx, 0x14
00a26c90 3bd8                     cmp        ebx, eax
00a26c92 0f85a8feffff             jne        0xa26b40
00a26c98 8b4514                   mov        eax, dword ptr [ebp + 0x14]
00a26c9b 8b7d10                   mov        edi, dword ptr [ebp + 0x10]
00a26c9e 8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00a26ca1 8b5508                   mov        edx, dword ptr [ebp + 8]
00a26ca4 8d9ea8000000             lea        ebx, [esi + 0xa8]
00a26caa 53                       push       ebx
00a26cab 50                       push       eax
00a26cac 57                       push       edi
00a26cad 51                       push       ecx
00a26cae 52                       push       edx
00a26caf 8bce                     mov        ecx, esi
00a26cb1 e8aad0ffff               call       0xa23d60
00a26cb6 8a8664010000             mov        al, byte ptr [esi + 0x164]
00a26cbc 84c0                     test       al, al
00a26cbe 7446                     je         0xa26d06
00a26cc0 8b8674010000             mov        eax, dword ptr [esi + 0x174]
00a26cc6 8b8e70010000             mov        ecx, dword ptr [esi + 0x170]
00a26ccc 6a00                     push       0
00a26cce 50                       push       eax
00a26ccf 8b8668010000             mov        eax, dword ptr [esi + 0x168]
00a26cd5 33d2                     xor        edx, edx
00a26cd7 8a966c010000             mov        dl, byte ptr [esi + 0x16c]
00a26cdd 51                       push       ecx
00a26cde 8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
00a26ce1 52                       push       edx
00a26ce2 8b550c                   mov        edx, dword ptr [ebp + 0xc]
00a26ce5 50                       push       eax
00a26ce6 8b4508                   mov        eax, dword ptr [ebp + 8]
00a26ce9 53                       push       ebx
00a26cea 51                       push       ecx
00a26ceb 57                       push       edi
00a26cec 52                       push       edx
00a26ced 50                       push       eax
00a26cee 8bce                     mov        ecx, esi
00a26cf0 e89bd1ffff               call       0xa23e90
00a26cf5 8a8678010000             mov        al, byte ptr [esi + 0x178]
00a26cfb 84c0                     test       al, al
00a26cfd 7407                     je         0xa26d06
00a26cff c6866401000000           mov        byte ptr [esi + 0x164], 0
00a26d06 8a45ff                   mov        al, byte ptr [ebp - 1]
00a26d09 84c0                     test       al, al
00a26d0b 0f8460010000             je         0xa26e71
00a26d11 8b5e08                   mov        ebx, dword ptr [esi + 8]
00a26d14 3b5e0c                   cmp        ebx, dword ptr [esi + 0xc]
