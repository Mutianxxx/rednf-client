004afd90  55                       push       ebp
004afd91  8bec                     mov        ebp, esp
004afd93  83ec10                   sub        esp, 0x10
004afd96  53                       push       ebx
004afd97  56                       push       esi
004afd98  8bf1                     mov        esi, ecx
004afd9a  8b8edc120000             mov        ecx, dword ptr [esi + 0x12dc]
004afda0  85c9                     test       ecx, ecx
004afda2  57                       push       edi
004afda3  7405                     je         0x4afdaa
004afda5  e8066e0000               call       0x4b6bb0
004afdaa  8b06                     mov        eax, dword ptr [esi]
004afdac  8bce                     mov        ecx, esi
004afdae  ff90f4040000             call       dword ptr [eax + 0x4f4]
004afdb4  84c0                     test       al, al
004afdb6  0f846b020000             je         0x4b0027
004afdbc  33db                     xor        ebx, ebx
004afdbe  8d8e88180000             lea        ecx, [esi + 0x1888]
004afdc4  895dfc                   mov        dword ptr [ebp - 4], ebx
004afdc7  8d7e60                   lea        edi, [esi + 0x60]
004afdca  e89122f5ff               call       0x402060
004afdcf  8bcf                     mov        ecx, edi
004afdd1  8945f0                   mov        dword ptr [ebp - 0x10], eax
004afdd4  e827716500               call       0xb06f00
004afdd9  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
004afddc  2bc1                     sub        eax, ecx
004afdde  3de8030000               cmp        eax, 0x3e8
004afde3  7f1e                     jg         0x4afe03
004afde5  68e8030000               push       0x3e8
004afdea  50                       push       eax
004afdeb  53                       push       ebx
004afdec  6800007f43               push       0x437f0000
004afdf1  e8ba9b6500               call       0xb099b0
004afdf6  83c410                   add        esp, 0x10
004afdf9  e846177500               call       0xc01544
004afdfe  8945fc                   mov        dword ptr [ebp - 4], eax
004afe01  8bd8                     mov        ebx, eax
004afe03  8b16                     mov        edx, dword ptr [esi]
004afe05  8bce                     mov        ecx, esi
004afe07  ff92f4000000             call       dword ptr [edx + 0xf4]
004afe0d  85c0                     test       eax, eax
004afe0f  7477                     je         0x4afe88
004afe11  8b06                     mov        eax, dword ptr [esi]
004afe13  8bce                     mov        ecx, esi
004afe15  ff90f4000000             call       dword ptr [eax + 0xf4]
004afe1b  8bc8                     mov        ecx, eax
004afe1d  e83e815700               call       0xa27f60
004afe22  3935d4f10401             cmp        dword ptr [0x104f1d4], esi
004afe28  742d                     je         0x4afe57
004afe2a  8b16                     mov        edx, dword ptr [esi]
004afe2c  8bce                     mov        ecx, esi
004afe2e  ff92c4010000             call       dword ptr [edx + 0x1c4]
004afe34  8b0dd4f10401             mov        ecx, dword ptr [0x104f1d4]
004afe3a  8bf8                     mov        edi, eax
004afe3c  8b01                     mov        eax, dword ptr [ecx]
004afe3e  ff90c4010000             call       dword ptr [eax + 0x1c4]
004afe44  3bf8                     cmp        edi, eax
004afe46  740f                     je         0x4afe57
004afe48  0fb6cb                   movzx      ecx, bl
004afe4b  c1e118                   shl        ecx, 0x18
004afe4e  81c9ffffff00             or         ecx, 0xffffff
004afe54  51                       push       ecx
004afe55  eb1b                     jmp        0x4afe72
004afe57  81fb80000000             cmp        ebx, 0x80
004afe5d  8bc3                     mov        eax, ebx
004afe5f  7f05                     jg         0x4afe66
004afe61  b880000000               mov        eax, 0x80
004afe66  0fb6c0                   movzx      eax, al
004afe69  c1e018                   shl        eax, 0x18
004afe6c  0dffffff00               or         eax, 0xffffff
004afe71  50                       push       eax
004afe72  8b16                     mov        edx, dword ptr [esi]
004afe74  8bce                     mov        ecx, esi
004afe76  68000000ff               push       0xff000000
004afe7b  ff92f4000000             call       dword ptr [edx + 0xf4]
004afe81  8bc8                     mov        ecx, eax
004afe83  e848595700               call       0xa257d0
004afe88  8b06                     mov        eax, dword ptr [esi]
004afe8a  8bce                     mov        ecx, esi
004afe8c  ff9004010000             call       dword ptr [eax + 0x104]
004afe92  85c0                     test       eax, eax
004afe94  0f845b010000             je         0x4afff5
004afe9a  8b16                     mov        edx, dword ptr [esi]
004afe9c  8bce                     mov        ecx, esi
004afe9e  ff9204010000             call       dword ptr [edx + 0x104]
004afea4  8b5028                   mov        edx, dword ptr [eax + 0x28]
004afea7  83c024                   add        eax, 0x24
004afeaa  85d2                     test       edx, edx
004afeac  0f8443010000             je         0x4afff5
004afeb2  8b4808                   mov        ecx, dword ptr [eax + 8]
004afeb5  2bca                     sub        ecx, edx
004afeb7  b8abaaaa2a               mov        eax, 0x2aaaaaab
004afebc  f7e9                     imul       ecx
004afebe  c1fa02                   sar        edx, 2
004afec1  8bc2                     mov        eax, edx
004afec3  c1e81f                   shr        eax, 0x1f
004afec6  03c2                     add        eax, edx
004afec8  85c0                     test       eax, eax
004afeca  0f8e25010000             jle        0x4afff5
004afed0  8b06                     mov        eax, dword ptr [esi]
004afed2  8bce                     mov        ecx, esi
004afed4  ff9004010000             call       dword ptr [eax + 0x104]
004afeda  8b5028                   mov        edx, dword ptr [eax + 0x28]
004afedd  83c024                   add        eax, 0x24
004afee0  85d2                     test       edx, edx
004afee2  7504                     jne        0x4afee8
004afee4  33db                     xor        ebx, ebx
004afee6  eb16                     jmp        0x4afefe
004afee8  8b4808                   mov        ecx, dword ptr [eax + 8]
004afeeb  2bca                     sub        ecx, edx
004afeed  b8abaaaa2a               mov        eax, 0x2aaaaaab
004afef2  f7e9                     imul       ecx
004afef4  c1fa02                   sar        edx, 2
004afef7  8bda                     mov        ebx, edx
004afef9  c1eb1f                   shr        ebx, 0x1f
004afefc  03da                     add        ebx, edx
004afefe  85db                     test       ebx, ebx
004aff00  895df8                   mov        dword ptr [ebp - 8], ebx
004aff03  c745f400000000           mov        dword ptr [ebp - 0xc], 0
004aff0a  0f8ee5000000             jle        0x4afff5
004aff10  c745f000000000           mov        dword ptr [ebp - 0x10], 0
004aff17  eb07                     jmp        0x4aff20
004aff19  8da42400000000           lea        esp, [esp]
004aff20  8b16                     mov        edx, dword ptr [esi]
004aff22  8bce                     mov        ecx, esi
004aff24  ff9204010000             call       dword ptr [edx + 0x104]
004aff2a  8bf8                     mov        edi, eax
004aff2c  8b4728                   mov        eax, dword ptr [edi + 0x28]
004aff2f  85c0                     test       eax, eax
004aff31  0f84a6000000             je         0x4affdd
004aff37  8b4f2c                   mov        ecx, dword ptr [edi + 0x2c]
004aff3a  2bc8                     sub        ecx, eax
004aff3c  b8abaaaa2a               mov        eax, 0x2aaaaaab
004aff41  f7e9                     imul       ecx
004aff43  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004aff46  c1fa02                   sar        edx, 2
004aff49  8bc2                     mov        eax, edx
004aff4b  c1e81f                   shr        eax, 0x1f
004aff4e  03c2                     add        eax, edx
004aff50  3bc1                     cmp        eax, ecx
004aff52  0f8685000000             jbe        0x4affdd
004aff58  8b4728                   mov        eax, dword ptr [edi + 0x28]
004aff5b  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
004aff5e  8b3c08                   mov        edi, dword ptr [eax + ecx]
004aff61  03c1                     add        eax, ecx
004aff63  85ff                     test       edi, edi
004aff65  7476                     je         0x4affdd
004aff67  8bcf                     mov        ecx, edi
004aff69  e8f27f5700               call       0xa27f60
004aff6e  3935d4f10401             cmp        dword ptr [0x104f1d4], esi
004aff74  743f                     je         0x4affb5
004aff76  8b06                     mov        eax, dword ptr [esi]
004aff78  8bce                     mov        ecx, esi
004aff7a  ff90c4010000             call       dword ptr [eax + 0x1c4]
004aff80  8b0dd4f10401             mov        ecx, dword ptr [0x104f1d4]
004aff86  8b11                     mov        edx, dword ptr [ecx]
004aff88  8bd8                     mov        ebx, eax
004aff8a  ff92c4010000             call       dword ptr [edx + 0x1c4]
004aff90  3bd8                     cmp        ebx, eax
004aff92  741e                     je         0x4affb2
004aff94  0fb645fc                 movzx      eax, byte ptr [ebp - 4]
004aff98  c1e018                   shl        eax, 0x18
004aff9b  0dffffff00               or         eax, 0xffffff
004affa0  50                       push       eax
004affa1  68000000ff               push       0xff000000
004affa6  8bcf                     mov        ecx, edi
004affa8  e823585700               call       0xa257d0
004affad  8b5df8                   mov        ebx, dword ptr [ebp - 8]
004affb0  eb2b                     jmp        0x4affdd
004affb2  8b5df8                   mov        ebx, dword ptr [ebp - 8]
004affb5  8b45fc                   mov        eax, dword ptr [ebp - 4]
004affb8  3d80000000               cmp        eax, 0x80
004affbd  7f05                     jg         0x4affc4
004affbf  b880000000               mov        eax, 0x80
004affc4  0fb6c8                   movzx      ecx, al
004affc7  c1e118                   shl        ecx, 0x18
004affca  81c9ffffff00             or         ecx, 0xffffff
004affd0  51                       push       ecx
004affd1  68000000ff               push       0xff000000
004affd6  8bcf                     mov        ecx, edi
004affd8  e8f3575700               call       0xa257d0
004affdd  8b45f4                   mov        eax, dword ptr [ebp - 0xc]
004affe0  8b55f0                   mov        edx, dword ptr [ebp - 0x10]
004affe3  40                       inc        eax
004affe4  83c218                   add        edx, 0x18
004affe7  3bc3                     cmp        eax, ebx
004affe9  8945f4                   mov        dword ptr [ebp - 0xc], eax
004affec  8955f0                   mov        dword ptr [ebp - 0x10], edx
004affef  0f8c2bffffff             jl         0x4aff20
004afff5  8d8e90180000             lea        ecx, [esi + 0x1890]
004afffb  e86020f5ff               call       0x402060
004b0000  8d4e60                   lea        ecx, [esi + 0x60]
004b0003  8bf8                     mov        edi, eax
004b0005  e8f66e6500               call       0xb06f00
004b000a  3bc7                     cmp        eax, edi
004b000c  0f8cd4000000             jl         0x4b00e6
004b0012  8b16                     mov        edx, dword ptr [esi]
004b0014  6aff                     push       -1
004b0016  6a00                     push       0
004b0018  8bce                     mov        ecx, esi
004b001a  ff92f8040000             call       dword ptr [edx + 0x4f8]
004b0020  5f                       pop        edi
004b0021  5e                       pop        esi
004b0022  5b                       pop        ebx
004b0023  8be5                     mov        esp, ebp
004b0025  5d                       pop        ebp
004b0026  c3                       ret        
004b0027  8dbe90180000             lea        edi, [esi + 0x1890]
004b002d  8bcf                     mov        ecx, edi
004b002f  e82c20f5ff               call       0x402060
004b0034  83f8ff                   cmp        eax, -1
004b0037  0f84a9000000             je         0x4b00e6
004b003d  8d8e88180000             lea        ecx, [esi + 0x1888]
004b0043  e81820f5ff               call       0x402060
004b0048  8d4e60                   lea        ecx, [esi + 0x60]
004b004b  8bd8                     mov        ebx, eax
004b004d  e8ae6e6500               call       0xb06f00
004b0052  2bc3                     sub        eax, ebx
004b0054  3de8030000               cmp        eax, 0x3e8
004b0059  7f79                     jg         0x4b00d4
004b005b  68e8030000               push       0x3e8
004b0060  50                       push       eax
004b0061  6800007f43               push       0x437f0000
004b0066  6a00                     push       0
004b0068  e843996500               call       0xb099b0
004b006d  83c410                   add        esp, 0x10
004b0070  e8cf147500               call       0xc01544
004b0075  8bd8                     mov        ebx, eax
004b0077  8b06                     mov        eax, dword ptr [esi]
004b0079  8bce                     mov        ecx, esi
004b007b  ff90f4000000             call       dword ptr [eax + 0xf4]
004b0081  85c0                     test       eax, eax
004b0083  7461                     je         0x4b00e6
004b0085  8b16                     mov        edx, dword ptr [esi]
004b0087  8bce                     mov        ecx, esi
004b0089  ff92f4000000             call       dword ptr [edx + 0xf4]
004b008f  8bc8                     mov        ecx, eax
004b0091  e8ca7e5700               call       0xa27f60
004b0096  3935d4f10401             cmp        dword ptr [0x104f1d4], esi
004b009c  750d                     jne        0x4b00ab
004b009e  81fb80000000             cmp        ebx, 0x80
004b00a4  7f05                     jg         0x4b00ab
004b00a6  bb80000000               mov        ebx, 0x80
004b00ab  8b16                     mov        edx, dword ptr [esi]
004b00ad  0fb6c3                   movzx      eax, bl
004b00b0  c1e018                   shl        eax, 0x18
004b00b3  0dffffff00               or         eax, 0xffffff
004b00b8  50                       push       eax
004b00b9  68000000ff               push       0xff000000
004b00be  8bce                     mov        ecx, esi
004b00c0  ff92f4000000             call       dword ptr [edx + 0xf4]
004b00c6  8bc8                     mov        ecx, eax
004b00c8  e803575700               call       0xa257d0
004b00cd  5f                       pop        edi
004b00ce  5e                       pop        esi
004b00cf  5b                       pop        ebx
004b00d0  8be5                     mov        esp, ebp
004b00d2  5d                       pop        ebp
004b00d3  c3                       ret        
004b00d4  8d45f0                   lea        eax, [ebp - 0x10]
004b00d7  50                       push       eax
004b00d8  8bcf                     mov        ecx, edi
004b00da  c745f0ffffffff           mov        dword ptr [ebp - 0x10], 0xffffffff
004b00e1  e87a44f5ff               call       0x404560
004b00e6  5f                       pop        edi
004b00e7  5e                       pop        esi
004b00e8  5b                       pop        ebx
004b00e9  8be5                     mov        esp, ebp
004b00eb  5d                       pop        ebp
004b00ec  c3                       ret        
004b00ed  cc                       int3       
004b00ee  cc                       int3       
004b00ef  cc                       int3       
004b00f0  55                       push       ebp
004b00f1  8bec                     mov        ebp, esp
004b00f3  53                       push       ebx
004b00f4  56                       push       esi
004b00f5  8bf1                     mov        esi, ecx
004b00f7  33db                     xor        ebx, ebx
004b00f9  85f6                     test       esi, esi
004b00fb  0f84c3000000             je         0x4b01c4
004b0101  8b06                     mov        eax, dword ptr [esi]
004b0103  ff5064                   call       dword ptr [eax + 0x64]
004b0106  84c0                     test       al, al
004b0108  0f84b6000000             je         0x4b01c4
004b010e  8b16                     mov        edx, dword ptr [esi]
004b0110  8bce                     mov        ecx, esi
004b0112  ff92c4030000             call       dword ptr [edx + 0x3c4]
004b0118  85c0                     test       eax, eax
004b011a  0f84a4000000             je         0x4b01c4
004b0120  57                       push       edi
004b0121  33ff                     xor        edi, edi
004b0123  8b06                     mov        eax, dword ptr [esi]
004b0125  8bce                     mov        ecx, esi
004b0127  ff90c4030000             call       dword ptr [eax + 0x3c4]
004b012d  8b4804                   mov        ecx, dword ptr [eax + 4]
004b0130  85c9                     test       ecx, ecx
004b0132  7504                     jne        0x4b0138
004b0134  33c0                     xor        eax, eax
004b0136  eb08                     jmp        0x4b0140
004b0138  8b4008                   mov        eax, dword ptr [eax + 8]
004b013b  2bc1                     sub        eax, ecx
004b013d  c1f802                   sar        eax, 2
004b0140  3bf8                     cmp        edi, eax
004b0142  0f8d7b000000             jge        0x4b01c3
004b0148  8b16                     mov        edx, dword ptr [esi]
004b014a  8bce                     mov        ecx, esi
004b014c  ff92c4030000             call       dword ptr [edx + 0x3c4]
004b0152  8b4804                   mov        ecx, dword ptr [eax + 4]
004b0155  85c9                     test       ecx, ecx
004b0157  7411                     je         0x4b016a
004b0159  8b4008                   mov        eax, dword ptr [eax + 8]
004b015c  2bc1                     sub        eax, ecx
004b015e  c1f802                   sar        eax, 2
004b0161  3bf8                     cmp        edi, eax
004b0163  7305                     jae        0x4b016a
004b0165  8b0cb9                   mov        ecx, dword ptr [ecx + edi*4]
004b0168  eb02                     jmp        0x4b016c
004b016a  33c9                     xor        ecx, ecx
004b016c  397104                   cmp        dword ptr [ecx + 4], esi
004b016f  754c                     jne        0x4b01bd
004b0171  8b06                     mov        eax, dword ptr [esi]
004b0173  8bce                     mov        ecx, esi
004b0175  ff90c4030000             call       dword ptr [eax + 0x3c4]
004b017b  8b4804                   mov        ecx, dword ptr [eax + 4]
004b017e  85c9                     test       ecx, ecx
004b0180  7411                     je         0x4b0193
004b0182  8b4008                   mov        eax, dword ptr [eax + 8]
004b0185  2bc1                     sub        eax, ecx
004b0187  c1f802                   sar        eax, 2
004b018a  3bf8                     cmp        edi, eax
004b018c  7305                     jae        0x4b0193
004b018e  8b0cb9                   mov        ecx, dword ptr [ecx + edi*4]
004b0191  eb02                     jmp        0x4b0195
004b0193  33c9                     xor        ecx, ecx
004b0195  6a00                     push       0
004b0197  683c96f500               push       0xf5963c
004b019c  68f451f500               push       0xf551f4
004b01a1  6a00                     push       0
004b01a3  51                       push       ecx
004b01a4  e8620b7500               call       0xc00d0b
004b01a9  8bd8                     mov        ebx, eax
004b01ab  83c414                   add        esp, 0x14
004b01ae  85db                     test       ebx, ebx
004b01b0  740b                     je         0x4b01bd
004b01b2  8b13                     mov        edx, dword ptr [ebx]
004b01b4  8bcb                     mov        ecx, ebx
004b01b6  ff5260                   call       dword ptr [edx + 0x60]
004b01b9  84c0                     test       al, al
004b01bb  7506                     jne        0x4b01c3
004b01bd  47                       inc        edi
004b01be  e960ffffff               jmp        0x4b0123
004b01c3  5f                       pop        edi
004b01c4  8b06                     mov        eax, dword ptr [esi]
004b01c6  6a10                     push       0x10
004b01c8  8bce                     mov        ecx, esi
004b01ca  ff9010040000             call       dword ptr [eax + 0x410]
004b01d0  84c0                     test       al, al
004b01d2  741a                     je         0x4b01ee
004b01d4  85db                     test       ebx, ebx
004b01d6  7516                     jne        0x4b01ee
004b01d8  8b16                     mov        edx, dword ptr [esi]
004b01da  8bce                     mov        ecx, esi
004b01dc  ff9230020000             call       dword ptr [edx + 0x230]
004b01e2  83f805                   cmp        eax, 5
004b01e5  5e                       pop        esi
004b01e6  0f94c0                   sete       al
004b01e9  5b                       pop        ebx
004b01ea  5d                       pop        ebp
004b01eb  c20c00                   ret        0xc
004b01ee  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004b01f1  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004b01f4  8b5508                   mov        edx, dword ptr [ebp + 8]
004b01f7  50                       push       eax
004b01f8  51                       push       ecx
004b01f9  52                       push       edx
004b01fa  8bce                     mov        ecx, esi
004b01fc  e8cf7b0300               call       0x4e7dd0
004b0201  5e                       pop        esi
004b0202  5b                       pop        ebx
004b0203  5d                       pop        ebp
004b0204  c20c00                   ret        0xc
004b0207  cc                       int3       
004b0208  cc                       int3       
004b0209  cc                       int3       
004b020a  cc                       int3       
004b020b  cc                       int3       
004b020c  cc                       int3       
004b020d  cc                       int3       
004b020e  cc                       int3       
004b020f  cc                       int3       
004b0210  53                       push       ebx
004b0211  56                       push       esi
004b0212  57                       push       edi
004b0213  8bf9                     mov        edi, ecx
004b0215  8a87f4010000             mov        al, byte ptr [edi + 0x1f4]
004b021b  84c0                     test       al, al
004b021d  7427                     je         0x4b0246
004b021f  8db7ec140000             lea        esi, [edi + 0x14ec]
004b0225  bb17000000               mov        ebx, 0x17
004b022a  8d9b00000000             lea        ebx, [ebx]
004b0230  8b06                     mov        eax, dword ptr [esi]
004b0232  85c0                     test       eax, eax
004b0234  740a                     je         0x4b0240
004b0236  8bc8                     mov        ecx, eax
004b0238  8b01                     mov        eax, dword ptr [ecx]
004b023a  ff90d4000000             call       dword ptr [eax + 0xd4]
004b0240  83c604                   add        esi, 4
004b0243  4b                       dec        ebx
004b0244  75ea                     jne        0x4b0230
004b0246  8bcf                     mov        ecx, edi
004b0248  e8839bfeff               call       0x499dd0
004b024d  8db7ec140000             lea        esi, [edi + 0x14ec]
004b0253  bb17000000               mov        ebx, 0x17
004b0258  8b06                     mov        eax, dword ptr [esi]
004b025a  85c0                     test       eax, eax
004b025c  740a                     je         0x4b0268
004b025e  8bc8                     mov        ecx, eax
004b0260  8b11                     mov        edx, dword ptr [ecx]
004b0262  ff92d0000000             call       dword ptr [edx + 0xd0]
004b0268  83c604                   add        esi, 4
004b026b  4b                       dec        ebx
004b026c  75ea                     jne        0x4b0258
004b026e  8b8fdc120000             mov        ecx, dword ptr [edi + 0x12dc]
004b0274  85c9                     test       ecx, ecx
004b0276  5f                       pop        edi
004b0277  5e                       pop        esi
004b0278  5b                       pop        ebx
004b0279  7405                     je         0x4b0280
004b027b  e9a0690000               jmp        0x4b6c20
004b0280  c3                       ret        
004b0281  cc                       int3       
004b0282  cc                       int3       
004b0283  cc                       int3       
004b0284  cc                       int3       
004b0285  cc                       int3       
004b0286  cc                       int3       
004b0287  cc                       int3       
004b0288  cc                       int3       
004b0289  cc                       int3       
004b028a  cc                       int3       
004b028b  cc                       int3       
004b028c  cc                       int3       
004b028d  cc                       int3       
004b028e  cc                       int3       
004b028f  cc                       int3       
004b0290  55                       push       ebp
004b0291  8bec                     mov        ebp, esp
004b0293  53                       push       ebx
004b0294  56                       push       esi
004b0295  8bf1                     mov        esi, ecx
004b0297  57                       push       edi
004b0298  8d8e0c190000             lea        ecx, [esi + 0x190c]
004b029e  e8bd1df5ff               call       0x402060
004b02a3  85c0                     test       eax, eax
004b02a5  8b5d08                   mov        ebx, dword ptr [ebp + 8]
004b02a8  742f                     je         0x4b02d9
004b02aa  8dbefc180000             lea        edi, [esi + 0x18fc]
004b02b0  8d4f38                   lea        ecx, [edi + 0x38]
004b02b3  e8a81df5ff               call       0x402060
004b02b8  8bcf                     mov        ecx, edi
004b02ba  894508                   mov        dword ptr [ebp + 8], eax
004b02bd  e83e6c6500               call       0xb06f00
004b02c2  3b4508                   cmp        eax, dword ptr [ebp + 8]
004b02c5  7d12                     jge        0x4b02d9
004b02c7  8b06                     mov        eax, dword ptr [esi]
004b02c9  8bce                     mov        ecx, esi
004b02cb  ff90f8030000             call       dword ptr [eax + 0x3f8]
004b02d1  3bd8                     cmp        ebx, eax
004b02d3  0f8c85000000             jl         0x4b035e
004b02d9  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004b02df  8b4244                   mov        eax, dword ptr [edx + 0x44]
004b02e2  8b8e3c120000             mov        ecx, dword ptr [esi + 0x123c]
004b02e8  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004b02ee  8d0488                   lea        eax, [eax + ecx*4]
004b02f1  8bc8                     mov        ecx, eax
004b02f3  33cf                     xor        ecx, edi
004b02f5  33cb                     xor        ecx, ebx
004b02f7  8908                     mov        dword ptr [eax], ecx
004b02f9  a1d8012101               mov        eax, dword ptr [0x12101d8]
004b02fe  8b963c120000             mov        edx, dword ptr [esi + 0x123c]
004b0304  8b4848                   mov        ecx, dword ptr [eax + 0x48]
004b0307  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004b030d  8d0491                   lea        eax, [ecx + edx*4]
004b0310  8bd0                     mov        edx, eax
004b0312  33d7                     xor        edx, edi
004b0314  33d3                     xor        edx, ebx
004b0316  8910                     mov        dword ptr [eax], edx
004b0318  8a450c                   mov        al, byte ptr [ebp + 0xc]
004b031b  84c0                     test       al, al
004b031d  743f                     je         0x4b035e
004b031f  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004b0325  8b5144                   mov        edx, dword ptr [ecx + 0x44]
004b0328  8b86d0150000             mov        eax, dword ptr [esi + 0x15d0]
004b032e  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004b0334  8d0482                   lea        eax, [edx + eax*4]
004b0337  8bc8                     mov        ecx, eax
004b0339  f7d1                     not        ecx
004b033b  33cf                     xor        ecx, edi
004b033d  8908                     mov        dword ptr [eax], ecx
004b033f  a1d8012101               mov        eax, dword ptr [0x12101d8]
004b0344  8b96d0150000             mov        edx, dword ptr [esi + 0x15d0]
004b034a  8b4848                   mov        ecx, dword ptr [eax + 0x48]
004b034d  8d0491                   lea        eax, [ecx + edx*4]
004b0350  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
004b0356  8bd0                     mov        edx, eax
004b0358  f7d2                     not        edx
004b035a  33d1                     xor        edx, ecx
004b035c  8910                     mov        dword ptr [eax], edx
004b035e  5f                       pop        edi
004b035f  5e                       pop        esi
004b0360  5b                       pop        ebx
004b0361  5d                       pop        ebp
004b0362  c20800                   ret        8
004b0365  cc                       int3       
004b0366  cc                       int3       
004b0367  cc                       int3       
004b0368  cc                       int3       
004b0369  cc                       int3       
004b036a  cc                       int3       
004b036b  cc                       int3       
004b036c  cc                       int3       
004b036d  cc                       int3       
004b036e  cc                       int3       
004b036f  cc                       int3       
004b0370  55                       push       ebp
004b0371  8bec                     mov        ebp, esp
004b0373  83ec0c                   sub        esp, 0xc
004b0376  894df4                   mov        dword ptr [ebp - 0xc], ecx
004b0379  8b899c190000             mov        ecx, dword ptr [ecx + 0x199c]
004b037f  57                       push       edi
004b0380  8b39                     mov        edi, dword ptr [ecx]
004b0382  33c0                     xor        eax, eax
004b0384  3bf9                     cmp        edi, ecx
004b0386  8945f8                   mov        dword ptr [ebp - 8], eax
004b0389  897dfc                   mov        dword ptr [ebp - 4], edi
004b038c  0f848c000000             je         0x4b041e
004b0392  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004b0398  53                       push       ebx
004b0399  8b1ddc012101             mov        ebx, dword ptr [0x12101dc]
004b039f  56                       push       esi
004b03a0  eb03                     jmp        0x4b03a5
004b03a2  8b7dfc                   mov        edi, dword ptr [ebp - 4]
004b03a5  8b470c                   mov        eax, dword ptr [edi + 0xc]
004b03a8  8b5710                   mov        edx, dword ptr [edi + 0x10]
004b03ab  83c70c                   add        edi, 0xc
004b03ae  33c3                     xor        eax, ebx
004b03b0  2bc7                     sub        eax, edi
004b03b2  3bc2                     cmp        eax, edx
004b03b4  7414                     je         0x4b03ca
004b03b6  6a3f                     push       0x3f
004b03b8  57                       push       edi
004b03b9  e8f26c6600               call       0xb170b0
004b03be  8b1ddc012101             mov        ebx, dword ptr [0x12101dc]
004b03c4  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004b03ca  8b4704                   mov        eax, dword ptr [edi + 4]
004b03cd  8b5144                   mov        edx, dword ptr [ecx + 0x44]
004b03d0  c1e002                   shl        eax, 2
004b03d3  8b3402                   mov        esi, dword ptr [edx + eax]
004b03d6  03d0                     add        edx, eax
004b03d8  33f2                     xor        esi, edx
004b03da  8b5148                   mov        edx, dword ptr [ecx + 0x48]
004b03dd  03c2                     add        eax, edx
004b03df  8b                       .byte      0x8b