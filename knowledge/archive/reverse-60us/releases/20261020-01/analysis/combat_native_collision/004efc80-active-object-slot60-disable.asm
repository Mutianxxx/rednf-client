004efc80 55                       push      ebp
004efc81 8bec                     mov       ebp, esp
004efc83 56                       push      esi
004efc84 8bf1                     mov       esi, ecx
004efc86 8b06                     mov       eax, dword ptr [esi]
004efc88 ff90a0050000             call      dword ptr [eax + 0x5a0]
004efc8e 84c0                     test      al, al
004efc90 8a4508                   mov       al, byte ptr [ebp + 8]
004efc93 741b                     je        0x4efcb0
004efc95 84c0                     test      al, al
004efc97 7517                     jne       0x4efcb0
004efc99 8b16                     mov       edx, dword ptr [esi]
004efc9b 56                       push      esi
004efc9c 8bce                     mov       ecx, esi
004efc9e ff92c4030000             call      dword ptr [edx + 0x3c4]
004efca4 8bc8                     mov       ecx, eax
004efca6 e8955a0700               call      0x565740
004efcab 5e                       pop       esi
004efcac 5d                       pop       ebp
004efcad c20400                   ret       4
004efcb0 888684010000             mov       byte ptr [esi + 0x184], al
004efcb6 5e                       pop       esi
004efcb7 5d                       pop       ebp
004efcb8 c20400                   ret       4
004efcbb cc                       int3      
004efcbc cc                       int3      
004efcbd cc                       int3      
004efcbe cc                       int3      
004efcbf cc                       int3      
004efcc0 55                       push      ebp
004efcc1 8bec                     mov       ebp, esp
004efcc3 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004efcc6 8b4508                   mov       eax, dword ptr [ebp + 8]
004efcc9 3981301a0000             cmp       dword ptr [ecx + 0x1a30], eax
004efccf 741b                     je        0x4efcec
004efcd1 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004efcd4 8991bc1d0000             mov       dword ptr [ecx + 0x1dbc], edx
004efcda 8b5514                   mov       edx, dword ptr [ebp + 0x14]
004efcdd 8991b81d0000             mov       dword ptr [ecx + 0x1db8], edx
004efce3 8b11                     mov       edx, dword ptr [ecx]
004efce5 50                       push      eax
004efce6 ff92f0050000             call      dword ptr [edx + 0x5f0]
004efcec 5d                       pop       ebp
004efced c21000                   ret       0x10
004efcf0 55                       push      ebp
004efcf1 8bec                     mov       ebp, esp
004efcf3 56                       push      esi
004efcf4 8bf1                     mov       esi, ecx
004efcf6 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004efcfc 85c9                     test      ecx, ecx
004efcfe 7507                     jne       0x4efd07
004efd00 32c0                     xor       al, al
004efd02 5e                       pop       esi
004efd03 5d                       pop       ebp
004efd04 c20800                   ret       8
004efd07 8b4508                   mov       eax, dword ptr [ebp + 8]
004efd0a 83f8ff                   cmp       eax, -1
004efd0d 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004efd10 0f858d000000             jne       0x4efda3
004efd16 83faff                   cmp       edx, -1
004efd19 0f8584000000             jne       0x4efda3
004efd1f 8b01                     mov       eax, dword ptr [ecx]
004efd21 57                       push      edi
004efd22 ff9094000000             call      dword ptr [eax + 0x94]
004efd28 8b16                     mov       edx, dword ptr [esi]
004efd2a 8bce                     mov       ecx, esi
004efd2c 8bf8                     mov       edi, eax
004efd2e ff9294000000             call      dword ptr [edx + 0x94]
004efd34 3bc7                     cmp       eax, edi
004efd36 8bce                     mov       ecx, esi
004efd38 7d0f                     jge       0x4efd49
004efd3a 8b06                     mov       eax, dword ptr [esi]
004efd3c ff9094000000             call      dword ptr [eax + 0x94]
004efd42 2d2c010000               sub       eax, 0x12c
004efd47 eb0d                     jmp       0x4efd56
004efd49 8b16                     mov       edx, dword ptr [esi]
004efd4b ff9294000000             call      dword ptr [edx + 0x94]
004efd51 052c010000               add       eax, 0x12c
004efd56 8b8e801b0000             mov       ecx, dword ptr [esi + 0x1b80]
004efd5c 8986bc1d0000             mov       dword ptr [esi + 0x1dbc], eax
004efd62 8b01                     mov       eax, dword ptr [ecx]
004efd64 ff9098000000             call      dword ptr [eax + 0x98]
004efd6a 8b16                     mov       edx, dword ptr [esi]
004efd6c 8bce                     mov       ecx, esi
004efd6e 8bf8                     mov       edi, eax
004efd70 ff9298000000             call      dword ptr [edx + 0x98]
004efd76 3bc7                     cmp       eax, edi
004efd78 5f                       pop       edi
004efd79 8bce                     mov       ecx, esi
004efd7b 7d13                     jge       0x4efd90
004efd7d 8b06                     mov       eax, dword ptr [esi]
004efd7f ff9098000000             call      dword ptr [eax + 0x98]
004efd85 83c032                   add       eax, 0x32
004efd88 8986b81d0000             mov       dword ptr [esi + 0x1db8], eax
004efd8e eb1f                     jmp       0x4efdaf
004efd90 8b16                     mov       edx, dword ptr [esi]
004efd92 ff9298000000             call      dword ptr [edx + 0x98]
004efd98 83e832                   sub       eax, 0x32
004efd9b 8986b81d0000             mov       dword ptr [esi + 0x1db8], eax
004efda1 eb0c                     jmp       0x4efdaf
004efda3 8986bc1d0000             mov       dword ptr [esi + 0x1dbc], eax
004efda9 8996b81d0000             mov       dword ptr [esi + 0x1db8], edx
004efdaf 8b06                     mov       eax, dword ptr [esi]
004efdb1 8bce                     mov       ecx, esi
004efdb3 ff9094000000             call      dword ptr [eax + 0x94]
004efdb9 8b16                     mov       edx, dword ptr [esi]
004efdbb 8bce                     mov       ecx, esi
004efdbd 8986c41d0000             mov       dword ptr [esi + 0x1dc4], eax
004efdc3 ff9298000000             call      dword ptr [edx + 0x98]
004efdc9 8986c01d0000             mov       dword ptr [esi + 0x1dc0], eax
004efdcf 8b06                     mov       eax, dword ptr [esi]
004efdd1 6a06                     push      6
004efdd3 8bce                     mov       ecx, esi
004efdd5 ff90f0050000             call      dword ptr [eax + 0x5f0]
004efddb b001                     mov       al, 1
004efddd 5e                       pop       esi
004efdde 5d                       pop       ebp
004efddf c20800                   ret       8
004efde2 cc                       int3      
004efde3 cc                       int3      
004efde4 cc                       int3      
004efde5 cc                       int3      
004efde6 cc                       int3      
004efde7 cc                       int3      
004efde8 cc                       int3      
004efde9 cc                       int3      
004efdea cc                       int3      
004efdeb cc                       int3      
004efdec cc                       int3      
004efded cc                       int3      
004efdee cc                       int3      
004efdef cc                       int3      
004efdf0 55                       push      ebp
004efdf1 8bec                     mov       ebp, esp
004efdf3 8b4508                   mov       eax, dword ptr [ebp + 8]
004efdf6 56                       push      esi
004efdf7 8bf1                     mov       esi, ecx
004efdf9 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004efdfc 8b16                     mov       edx, dword ptr [esi]
004efdfe 898eb81d0000             mov       dword ptr [esi + 0x1db8], ecx
004efe04 8bce                     mov       ecx, esi
004efe06 8986bc1d0000             mov       dword ptr [esi + 0x1dbc], eax
004efe0c ff9294000000             call      dword ptr [edx + 0x94]
004efe12 8986c41d0000             mov       dword ptr [esi + 0x1dc4], eax
004efe18 8b06                     mov       eax, dword ptr [esi]
004efe1a 8bce                     mov       ecx, esi
004efe1c ff9098000000             call      dword ptr [eax + 0x98]
004efe22 8b16                     mov       edx, dword ptr [esi]
004efe24 6a19                     push      0x19
004efe26 8bce                     mov       ecx, esi
004efe28 8986c01d0000             mov       dword ptr [esi + 0x1dc0], eax
004efe2e ff92f0050000             call      dword ptr [edx + 0x5f0]
004efe34 5e                       pop       esi
004efe35 5d                       pop       ebp
004efe36 c20800                   ret       8
004efe39 cc                       int3      
004efe3a cc                       int3      
004efe3b cc                       int3      
004efe3c cc                       int3      
004efe3d cc                       int3      
004efe3e cc                       int3      
004efe3f cc                       int3      
004efe40 55                       push      ebp
004efe41 8bec                     mov       ebp, esp
004efe43 8b4508                   mov       eax, dword ptr [ebp + 8]
004efe46 56                       push      esi
004efe47 8bf1                     mov       esi, ecx
004efe49 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004efe4c 8b16                     mov       edx, dword ptr [esi]
004efe4e 898eb81d0000             mov       dword ptr [esi + 0x1db8], ecx
004efe54 8bce                     mov       ecx, esi
004efe56 8986bc1d0000             mov       dword ptr [esi + 0x1dbc], eax
004efe5c ff9294000000             call      dword ptr [edx + 0x94]
004efe62 8986c41d0000             mov       dword ptr [esi + 0x1dc4], eax
004efe68 8b06                     mov       eax, dword ptr [esi]
004efe6a 8bce                     mov       ecx, esi
004efe6c ff9098000000             call      dword ptr [eax + 0x98]
004efe72 8b16                     mov       edx, dword ptr [esi]
004efe74 6a1a                     push      0x1a
004efe76 8bce                     mov       ecx, esi
004efe78 8986c01d0000             mov       dword ptr [esi + 0x1dc0], eax
004efe7e ff92f0050000             call      dword ptr [edx + 0x5f0]
004efe84 5e                       pop       esi
004efe85 5d                       pop       ebp
004efe86 c20800                   ret       8
004efe89 cc                       int3      
004efe8a cc                       int3      
004efe8b cc                       int3      
004efe8c cc                       int3      
004efe8d cc                       int3      
004efe8e cc                       int3      
004efe8f cc                       int3      
004efe90 55                       push      ebp
004efe91 8bec                     mov       ebp, esp
004efe93 83ec1c                   sub       esp, 0x1c
004efe96 53                       push      ebx
004efe97 56                       push      esi
004efe98 8bf1                     mov       esi, ecx
004efe9a 8b06                     mov       eax, dword ptr [esi]
004efe9c 57                       push      edi
004efe9d ff9094000000             call      dword ptr [eax + 0x94]
004efea3 99                       cdq       
004efea4 83e20f                   and       edx, 0xf
004efea7 03c2                     add       eax, edx
004efea9 8b16                     mov       edx, dword ptr [esi]
004efeab c1f804                   sar       eax, 4
004efeae 8bce                     mov       ecx, esi
004efeb0 8945ec                   mov       dword ptr [ebp - 0x14], eax
004efeb3 ff9298000000             call      dword ptr [edx + 0x98]
004efeb9 8bc8                     mov       ecx, eax
004efebb b8abaaaa2a               mov       eax, 0x2aaaaaab
004efec0 f7e9                     imul      ecx
004efec2 8b86bc1d0000             mov       eax, dword ptr [esi + 0x1dbc]
004efec8 d1fa                     sar       edx, 1
004efeca 8bca                     mov       ecx, edx
004efecc c1e91f                   shr       ecx, 0x1f
004efecf 03ca                     add       ecx, edx
004efed1 99                       cdq       
004efed2 83e20f                   and       edx, 0xf
004efed5 03c2                     add       eax, edx
004efed7 8b96b81d0000             mov       edx, dword ptr [esi + 0x1db8]
004efedd 8bd8                     mov       ebx, eax
004efedf b8abaaaa2a               mov       eax, 0x2aaaaaab
004efee4 f7ea                     imul      edx
004efee6 8b45ec                   mov       eax, dword ptr [ebp - 0x14]
004efee9 d1fa                     sar       edx, 1
004efeeb 8bfa                     mov       edi, edx
004efeed c1ef1f                   shr       edi, 0x1f
004efef0 894de8                   mov       dword ptr [ebp - 0x18], ecx
004efef3 03fa                     add       edi, edx
004efef5 8b16                     mov       edx, dword ptr [esi]
004efef7 894df0                   mov       dword ptr [ebp - 0x10], ecx
004efefa 8bce                     mov       ecx, esi
004efefc c1fb04                   sar       ebx, 4
004efeff 8945f4                   mov       dword ptr [ebp - 0xc], eax
004eff02 ff9208020000             call      dword ptr [edx + 0x208]
004eff08 8b16                     mov       edx, dword ptr [esi]
004eff0a 85c0                     test      eax, eax
004eff0c 0f9fc0                   setg      al
004eff0f 8845f8                   mov       byte ptr [ebp - 8], al
004eff12 8b4df8                   mov       ecx, dword ptr [ebp - 8]
004eff15 51                       push      ecx
004eff16 8bce                     mov       ecx, esi
004eff18 ff92c4010000             call      dword ptr [edx + 0x1c4]
004eff1e 50                       push      eax
004eff1f 57                       push      edi
004eff20 53                       push      ebx
004eff21 b9f046f400               mov       ecx, 0xf446f0
004eff26 e8f5f25500               call      0xa4f220
004eff2b 85c0                     test      eax, eax
004eff2d 8945fc                   mov       dword ptr [ebp - 4], eax
004eff30 7564                     jne       0x4eff96
004eff32 8b4df8                   mov       ecx, dword ptr [ebp - 8]
004eff35 8b16                     mov       edx, dword ptr [esi]
004eff37 8d43ff                   lea       eax, [ebx - 1]
004eff3a 51                       push      ecx
004eff3b 8bce                     mov       ecx, esi
004eff3d 8945e4                   mov       dword ptr [ebp - 0x1c], eax
004eff40 ff92c4010000             call      dword ptr [edx + 0x1c4]
004eff46 50                       push      eax
004eff47 8b45e4                   mov       eax, dword ptr [ebp - 0x1c]
004eff4a 57                       push      edi
004eff4b 50                       push      eax
004eff4c b9f046f400               mov       ecx, 0xf446f0
004eff51 e8caf25500               call      0xa4f220
004eff56 83f801                   cmp       eax, 1
004eff59 7505                     jne       0x4eff60
004eff5b 8b5de4                   mov       ebx, dword ptr [ebp - 0x1c]
004eff5e eb2c                     jmp       0x4eff8c
004eff60 8b55f8                   mov       edx, dword ptr [ebp - 8]
004eff63 8b06                     mov       eax, dword ptr [esi]
004eff65 8d4b01                   lea       ecx, [ebx + 1]
004eff68 894de4                   mov       dword ptr [ebp - 0x1c], ecx
004eff6b 52                       push      edx
004eff6c 8bce                     mov       ecx, esi
004eff6e ff90c4010000             call      dword ptr [eax + 0x1c4]
004eff74 8b4de4                   mov       ecx, dword ptr [ebp - 0x1c]
004eff77 50                       push      eax
004eff78 57                       push      edi
004eff79 51                       push      ecx
004eff7a b9f046f400               mov       ecx, 0xf446f0
004eff7f e89cf25500               call      0xa4f220
004eff84 83f801                   cmp       eax, 1
004eff87 750a                     jne       0x4eff93
004eff89 8b5de4                   mov       ebx, dword ptr [ebp - 0x1c]
004eff8c c745fc01000000           mov       dword ptr [ebp - 4], 1
004eff93 8b45fc                   mov       eax, dword ptr [ebp - 4]
004eff96 8b55ec                   mov       edx, dword ptr [ebp - 0x14]
004eff99 3b965c200000             cmp       edx, dword ptr [esi + 0x205c]
004eff9f 7530                     jne       0x4effd1
004effa1 8b4de8                   mov       ecx, dword ptr [ebp - 0x18]
004effa4 3b8e60200000             cmp       ecx, dword ptr [esi + 0x2060]
004effaa 7525                     jne       0x4effd1
004effac 3b9e64200000             cmp       ebx, dword ptr [esi + 0x2064]
004effb2 751d                     jne       0x4effd1
004effb4 3bbe68200000             cmp       edi, dword ptr [esi + 0x2068]
004effba 7515                     jne       0x4effd1
004effbc 8b966c200000             mov       edx, dword ptr [esi + 0x206c]
004effc2 83c9ff                   or        ecx, 0xffffffff
004effc5 3bd1                     cmp       edx, ecx
004effc7 7408                     je        0x4effd1
004effc9 398e70200000             cmp       dword ptr [esi + 0x2070], ecx
004effcf 7544                     jne       0x4f0015
004effd1 83f801                   cmp       eax, 1
004effd4 753f                     jne       0x4f0015
004effd6 8b55f8                   mov       edx, dword ptr [ebp - 8]
004effd9 8b06                     mov       eax, dword ptr [esi]
004effdb 52                       push      edx
004effdc 8bce                     mov       ecx, esi
004effde ff90c4010000             call      dword ptr [eax + 0x1c4]
004effe4 50                       push      eax
004effe5 8b45e8                   mov       eax, dword ptr [ebp - 0x18]
004effe8 8d4df0                   lea       ecx, [ebp - 0x10]
004effeb 51                       push      ecx
004effec 8b4dec                   mov       ecx, dword ptr [ebp - 0x14]
004effef 8d55f4                   lea       edx, [ebp - 0xc]
004efff2 52                       push      edx
004efff3 57                       push      edi
004efff4 53                       push      ebx
004efff5 50                       push      eax
004efff6 51                       push      ecx
004efff7 b9f046f400               mov       ecx, 0xf446f0
004efffc e86ff65500               call      0xa4f670
004f0001 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004f0004 8b55f0                   mov       edx, dword ptr [ebp - 0x10]
004f0007 898e6c200000             mov       dword ptr [esi + 0x206c], ecx
004f000d 899670200000             mov       dword ptr [esi + 0x2070], edx
004f0013 eb66                     jmp       0x4f007b
004f0015 85c0                     test      eax, eax
004f0017 8b8e6c200000             mov       ecx, dword ptr [esi + 0x206c]
004f001d 8b9670200000             mov       edx, dword ptr [esi + 0x2070]
004f0023 894df4                   mov       dword ptr [ebp - 0xc], ecx
004f0026 8955f0                   mov       dword ptr [ebp - 0x10], edx
004f0029 754b                     jne       0x4f0076
004f002b 8b55f8                   mov       edx, dword ptr [ebp - 8]
004f002e 8b06                     mov       eax, dword ptr [esi]
004f0030 52                       push      edx
004f0031 8bce                     mov       ecx, esi
004f0033 ff90c4010000             call      dword ptr [eax + 0x1c4]
004f0039 50                       push      eax
004f003a 8b8668200000             mov       eax, dword ptr [esi + 0x2068]
004f0040 8d4df0                   lea       ecx, [ebp - 0x10]
004f0043 51                       push      ecx
004f0044 8b8e64200000             mov       ecx, dword ptr [esi + 0x2064]
004f004a 8d55f4                   lea       edx, [ebp - 0xc]
004f004d 52                       push      edx
004f004e 8b55e8                   mov       edx, dword ptr [ebp - 0x18]
004f0051 50                       push      eax
004f0052 8b45ec                   mov       eax, dword ptr [ebp - 0x14]
004f0055 51                       push      ecx
004f0056 52                       push      edx
004f0057 50                       push      eax
004f0058 b9f046f400               mov       ecx, 0xf446f0
004f005d e80ef65500               call      0xa4f670
004f0062 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004f0065 8b55f0                   mov       edx, dword ptr [ebp - 0x10]
004f0068 898e6c200000             mov       dword ptr [esi + 0x206c], ecx
004f006e 899670200000             mov       dword ptr [esi + 0x2070], edx
004f0074 eb11                     jmp       0x4f0087
004f0076 83f801                   cmp       eax, 1
004f0079 750c                     jne       0x4f0087
004f007b 899e64200000             mov       dword ptr [esi + 0x2064], ebx
004f0081 89be68200000             mov       dword ptr [esi + 0x2068], edi
004f0087 8b7dec                   mov       edi, dword ptr [ebp - 0x14]
004f008a 3bf9                     cmp       edi, ecx
004f008c 8b45e8                   mov       eax, dword ptr [ebp - 0x18]
004f008f 89be5c200000             mov       dword ptr [esi + 0x205c], edi
004f0095 898660200000             mov       dword ptr [esi + 0x2060], eax
004f009b 898e6c200000             mov       dword ptr [esi + 0x206c], ecx
004f00a1 899670200000             mov       dword ptr [esi + 0x2070], edx
004f00a7 7d0b                     jge       0x4f00b4
004f00a9 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004f00ac c70101000000             mov       dword ptr [ecx], 1
004f00b2 eb10                     jmp       0x4f00c4
004f00b4 33db                     xor       ebx, ebx
004f00b6 3bf9                     cmp       edi, ecx
004f00b8 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004f00bb 0f9fc3                   setg      bl
004f00be 4b                       dec       ebx
004f00bf 83e304                   and       ebx, 4
004f00c2 8919                     mov       dword ptr [ecx], ebx
004f00c4 3bc2                     cmp       eax, edx
004f00c6 5f                       pop       edi
004f00c7 5e                       pop       esi
004f00c8 5b                       pop       ebx
004f00c9 7e0f                     jle       0x4f00da
004f00cb 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004f00ce c70202000000             mov       dword ptr [edx], 2
004f00d4 8be5                     mov       esp, ebp
004f00d6 5d                       pop       ebp
004f00d7 c20800                   ret       8
004f00da 33c9                     xor       ecx, ecx
004f00dc 3bc2                     cmp       eax, edx
004f00de 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004f00e1 0f9dc1                   setge     cl
004f00e4 83c103                   add       ecx, 3
004f00e7 890a                     mov       dword ptr [edx], ecx
004f00e9 8be5                     mov       esp, ebp
004f00eb 5d                       pop       ebp
004f00ec c20800                   ret       8
004f00ef cc                       int3      
004f00f0 8b8104020000             mov       eax, dword ptr [ecx + 0x204]
004f00f6 3d50c30000               cmp       eax, 0xc350
004f00fb 7c0a                     jl        0x4f0107
004f00fd 3d38c70000               cmp       eax, 0xc738
004f0102 7f03                     jg        0x4f0107
004f0104 b001                     mov       al, 1
004f0106 c3                       ret       
004f0107 3dc0da0000               cmp       eax, 0xdac0
004f010c 7c07                     jl        0x4f0115
004f010e 3d60ea0000               cmp       eax, 0xea60
004f0113 7eef                     jle       0x4f0104
004f0115 32c0                     xor       al, al
004f0117 c3                       ret       
004f0118 cc                       int3      
004f0119 cc                       int3      
004f011a cc                       int3      
004f011b cc                       int3      
004f011c cc                       int3      
004f011d cc                       int3      
004f011e cc                       int3      
004f011f cc                       int3      
004f0120 55                       push      ebp
004f0121 8bec                     mov       ebp, esp
004f0123 8b4508                   mov       eax, dword ptr [ebp + 8]
004f0126 50                       push      eax
004f0127 81c1501e0000             add       ecx, 0x1e50
004f012d 51                       push      ecx
004f012e e83ddc3b00               call      0x8add70
004f0133 83c408                   add       esp, 8
004f0136 5d                       pop       ebp
004f0137 c20400                   ret       4
004f013a cc                       int3      
004f013b cc                       int3      
004f013c cc                       int3      
004f013d cc                       int3      
004f013e cc                       int3      
004f013f cc                       int3      
004f0140 55                       push      ebp
004f0141 8bec                     mov       ebp, esp
004f0143 8a4508                   mov       al, byte ptr [ebp + 8]
004f0146 84c0                     test      al, al
004f0148 53                       push      ebx
004f0149 8b5d0c                   mov       ebx, dword ptr [ebp + 0xc]
004f014c 56                       push      esi
004f014d 57                       push      edi
004f014e 8b7d10                   mov       edi, dword ptr [ebp + 0x10]
004f0151 8bf1                     mov       esi, ecx
004f0153 0f85b5000000             jne       0x4f020e
004f0159 8b868c200000             mov       eax, dword ptr [esi + 0x208c]
004f015f 85c0                     test      eax, eax
004f0161 0f84a7000000             je        0x4f020e
004f0167 8b06                     mov       eax, dword ptr [esi]
004f0169 ff9034050000             call      dword ptr [eax + 0x534]
004f016f 84c0                     test      al, al
004f0171 0f8497000000             je        0x4f020e
004f0177 8b0de0b80d01             mov       ecx, dword ptr [0x10db8e0]
004f017d 6a02                     push      2
004f017f e82c836100               call      0xb084b0
004f0184 8b16                     mov       edx, dword ptr [esi]
004f0186 8bce                     mov       ecx, esi
004f0188 ff92c4010000             call      dword ptr [edx + 0x1c4]
004f018e 8b0dd4f10401             mov       ecx, dword ptr [0x104f1d4]
004f0194 8bd8                     mov       ebx, eax
004f0196 8b01                     mov       eax, dword ptr [ecx]
004f0198 ff90c4010000             call      dword ptr [eax + 0x1c4]
004f019e 3bd8                     cmp       ebx, eax
