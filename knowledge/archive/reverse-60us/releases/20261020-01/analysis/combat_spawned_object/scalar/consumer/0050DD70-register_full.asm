0050dd70  55                       push       ebp
0050dd71  8bec                     mov        ebp, esp
0050dd73  51                       push       ecx
0050dd74  53                       push       ebx
0050dd75  56                       push       esi
0050dd76  8b7514                   mov        esi, dword ptr [ebp + 0x14]
0050dd79  85f6                     test       esi, esi
0050dd7b  8bd9                     mov        ebx, ecx
0050dd7d  895dfc                   mov        dword ptr [ebp - 4], ebx
0050dd80  0f84cc020000             je         0x50e052
0050dd86  56                       push       esi
0050dd87  e844d3ffff               call       0x50b0d0
0050dd8c  84c0                     test       al, al
0050dd8e  0f85be020000             jne        0x50e052
0050dd94  e8579bf3ff               call       0x4478f0
0050dd99  84c0                     test       al, al
0050dd9b  755a                     jne        0x50ddf7
0050dd9d  6a00                     push       0
0050dd9f  68f48ef500               push       0xf58ef4
0050dda4  681009f400               push       0xf40910
0050dda9  6a00                     push       0
0050ddab  56                       push       esi
0050ddac  e85a2f6f00               call       0xc00d0b
0050ddb1  83c414                   add        esp, 0x14
0050ddb4  85c0                     test       eax, eax
0050ddb6  743f                     je         0x50ddf7
0050ddb8  8b06                     mov        eax, dword ptr [esi]
0050ddba  8bce                     mov        ecx, esi
0050ddbc  ff5068                   call       dword ptr [eax + 0x68]
0050ddbf  3c01                     cmp        al, 1
0050ddc1  7534                     jne        0x50ddf7
0050ddc3  837d0c02                 cmp        dword ptr [ebp + 0xc], 2
0050ddc7  752e                     jne        0x50ddf7
0050ddc9  8b4508                   mov        eax, dword ptr [ebp + 8]
0050ddcc  85c0                     test       eax, eax
0050ddce  7427                     je         0x50ddf7
0050ddd0  3b05d4f10401             cmp        eax, dword ptr [0x104f1d4]
0050ddd6  741f                     je         0x50ddf7
0050ddd8  3b05d8f10401             cmp        eax, dword ptr [0x104f1d8]
0050ddde  7417                     je         0x50ddf7
0050dde0  8d4d14                   lea        ecx, [ebp + 0x14]
0050dde3  51                       push       ecx
0050dde4  8d8b9c000000             lea        ecx, [ebx + 0x9c]
0050ddea  e80107f8ff               call       0x48e4f0
0050ddef  5e                       pop        esi
0050ddf0  5b                       pop        ebx
0050ddf1  8be5                     mov        esp, ebp
0050ddf3  5d                       pop        ebp
0050ddf4  c21c00                   ret        0x1c
0050ddf7  8b16                     mov        edx, dword ptr [esi]
0050ddf9  8bce                     mov        ecx, esi
0050ddfb  ff5228                   call       dword ptr [edx + 0x28]
0050ddfe  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
0050de01  8b5510                   mov        edx, dword ptr [ebp + 0x10]
0050de04  8908                     mov        dword ptr [eax], ecx
0050de06  8d4508                   lea        eax, [ebp + 8]
0050de09  895508                   mov        dword ptr [ebp + 8], edx
0050de0c  8b16                     mov        edx, dword ptr [esi]
0050de0e  50                       push       eax
0050de0f  8bce                     mov        ecx, esi
0050de11  ff5228                   call       dword ptr [edx + 0x28]
0050de14  8bc8                     mov        ecx, eax
0050de16  83c104                   add        ecx, 4
0050de19  e84267efff               call       0x404560
0050de1e  8b06                     mov        eax, dword ptr [esi]
0050de20  8bce                     mov        ecx, esi
0050de22  ff505c                   call       dword ptr [eax + 0x5c]
0050de25  85c0                     test       eax, eax
0050de27  7413                     je         0x50de3c
0050de29  8b16                     mov        edx, dword ptr [esi]
0050de2b  6a00                     push       0
0050de2d  6a00                     push       0
0050de2f  56                       push       esi
0050de30  8bce                     mov        ecx, esi
0050de32  ff525c                   call       dword ptr [edx + 0x5c]
0050de35  8bc8                     mov        ecx, eax
0050de37  e8b4e8ffff               call       0x50c6f0
0050de3c  8b06                     mov        eax, dword ptr [esi]
0050de3e  57                       push       edi
0050de3f  53                       push       ebx
0050de40  8bce                     mov        ecx, esi
0050de42  ff5058                   call       dword ptr [eax + 0x58]
0050de45  8d5514                   lea        edx, [ebp + 0x14]
0050de48  8d4b0c                   lea        ecx, [ebx + 0xc]
0050de4b  52                       push       edx
0050de4c  e89f06f8ff               call       0x48e4f0
0050de51  8b06                     mov        eax, dword ptr [esi]
0050de53  8bce                     mov        ecx, esi
0050de55  ff5028                   call       dword ptr [eax + 0x28]
0050de58  83780c07                 cmp        dword ptr [eax + 0xc], 7
0050de5c  747d                     je         0x50dedb
0050de5e  8b16                     mov        edx, dword ptr [esi]
0050de60  8bce                     mov        ecx, esi
0050de62  ff5228                   call       dword ptr [edx + 0x28]
0050de65  8b400c                   mov        eax, dword ptr [eax + 0xc]
0050de68  c1e004                   shl        eax, 4
0050de6b  8d7c181c                 lea        edi, [eax + ebx + 0x1c]
0050de6f  8b4518                   mov        eax, dword ptr [ebp + 0x18]
0050de72  85c0                     test       eax, eax
0050de74  745a                     je         0x50ded0
0050de76  8b5f08                   mov        ebx, dword ptr [edi + 8]
0050de79  8b4704                   mov        eax, dword ptr [edi + 4]
0050de7c  8d4d18                   lea        ecx, [ebp + 0x18]
0050de7f  51                       push       ecx
0050de80  53                       push       ebx
0050de81  50                       push       eax
0050de82  8d5508                   lea        edx, [ebp + 8]
0050de85  52                       push       edx
0050de86  e815691a00               call       0x6b47a0
0050de8b  8b4508                   mov        eax, dword ptr [ebp + 8]
0050de8e  83c410                   add        esp, 0x10
0050de91  3bc3                     cmp        eax, ebx
0050de93  7510                     jne        0x50dea5
0050de95  8d4514                   lea        eax, [ebp + 0x14]
0050de98  50                       push       eax
0050de99  8bcf                     mov        ecx, edi
0050de9b  e85006f8ff               call       0x48e4f0
0050dea0  8b5dfc                   mov        ebx, dword ptr [ebp - 4]
0050dea3  eb36                     jmp        0x50dedb
0050dea5  8a4d1c                   mov        cl, byte ptr [ebp + 0x1c]
0050dea8  84c9                     test       cl, cl
0050deaa  8d4d14                   lea        ecx, [ebp + 0x14]
0050dead  51                       push       ecx
0050deae  8d551c                   lea        edx, [ebp + 0x1c]
0050deb1  8bcf                     mov        ecx, edi
0050deb3  740c                     je         0x50dec1
0050deb5  50                       push       eax
0050deb6  52                       push       edx
0050deb7  e844f8f7ff               call       0x48d700
0050debc  8b5dfc                   mov        ebx, dword ptr [ebp - 4]
0050debf  eb1a                     jmp        0x50dedb
0050dec1  83c004                   add        eax, 4
0050dec4  50                       push       eax
0050dec5  52                       push       edx
0050dec6  e835f8f7ff               call       0x48d700
0050decb  8b5dfc                   mov        ebx, dword ptr [ebp - 4]
0050dece  eb0b                     jmp        0x50dedb
0050ded0  8d4514                   lea        eax, [ebp + 0x14]
0050ded3  50                       push       eax
0050ded4  8bcf                     mov        ecx, edi
0050ded6  e81506f8ff               call       0x48e4f0
0050dedb  8b16                     mov        edx, dword ptr [esi]
0050dedd  6a01                     push       1
0050dedf  8bce                     mov        ecx, esi
0050dee1  ff522c                   call       dword ptr [edx + 0x2c]
0050dee4  84c0                     test       al, al
0050dee6  741a                     je         0x50df02
0050dee8  8d451c                   lea        eax, [ebp + 0x1c]
0050deeb  50                       push       eax
0050deec  8d8b8c000000             lea        ecx, [ebx + 0x8c]
0050def2  89751c                   mov        dword ptr [ebp + 0x1c], esi
0050def5  e8d69cffff               call       0x507bd0
0050defa  56                       push       esi
0050defb  8bcb                     mov        ecx, ebx
0050defd  e82efcffff               call       0x50db30
0050df02  8b0dd4f10401             mov        ecx, dword ptr [0x104f1d4]
0050df08  85c9                     test       ecx, ecx
0050df0a  7418                     je         0x50df24
0050df0c  8b11                     mov        edx, dword ptr [ecx]
0050df0e  ff92e0060000             call       dword ptr [edx + 0x6e0]
0050df14  39450c                   cmp        dword ptr [ebp + 0xc], eax
0050df17  750b                     jne        0x50df24
0050df19  8b4510                   mov        eax, dword ptr [ebp + 0x10]
0050df1c  50                       push       eax
0050df1d  8bcb                     mov        ecx, ebx
0050df1f  e87ce6ffff               call       0x50c5a0
0050df24  33ff                     xor        edi, edi
0050df26  8b4b10                   mov        ecx, dword ptr [ebx + 0x10]
0050df29  85c9                     test       ecx, ecx
0050df2b  897d1c                   mov        dword ptr [ebp + 0x1c], edi
0050df2e  7450                     je         0x50df80
0050df30  8b4314                   mov        eax, dword ptr [ebx + 0x14]
0050df33  2bc1                     sub        eax, ecx
0050df35  c1f802                   sar        eax, 2
0050df38  3bf8                     cmp        edi, eax
0050df3a  7344                     jae        0x50df80
0050df3c  8b04b9                   mov        eax, dword ptr [ecx + edi*4]
0050df3f  3bc6                     cmp        eax, esi
0050df41  8d14b9                   lea        edx, [ecx + edi*4]
0050df44  742c                     je         0x50df72
0050df46  8b4520                   mov        eax, dword ptr [ebp + 0x20]
0050df49  85c0                     test       eax, eax
0050df4b  7425                     je         0x50df72
0050df4d  8b4808                   mov        ecx, dword ptr [eax + 8]
0050df50  8b4004                   mov        eax, dword ptr [eax + 4]
0050df53  3bc1                     cmp        eax, ecx
0050df55  741b                     je         0x50df72
0050df57  8b3a                     mov        edi, dword ptr [edx]
0050df59  8da42400000000           lea        esp, [esp]
0050df60  3938                     cmp        dword ptr [eax], edi
0050df62  7407                     je         0x50df6b
0050df64  83c004                   add        eax, 4
0050df67  3bc1                     cmp        eax, ecx
0050df69  75f5                     jne        0x50df60
0050df6b  3bc1                     cmp        eax, ecx
0050df6d  8b7d1c                   mov        edi, dword ptr [ebp + 0x1c]
0050df70  750b                     jne        0x50df7d
0050df72  8b0a                     mov        ecx, dword ptr [edx]
0050df74  8b11                     mov        edx, dword ptr [ecx]
0050df76  56                       push       esi
0050df77  ff9258010000             call       dword ptr [edx + 0x158]
0050df7d  47                       inc        edi
0050df7e  eba6                     jmp        0x50df26
0050df80  8d8b2c010000             lea        ecx, [ebx + 0x12c]
0050df86  e8d540efff               call       0x402060
0050df8b  83f801                   cmp        eax, 1
0050df8e  745f                     je         0x50dfef
0050df90  a1d4f10401               mov        eax, dword ptr [0x104f1d4]
0050df95  85c0                     test       eax, eax
0050df97  7456                     je         0x50dfef
0050df99  8b06                     mov        eax, dword ptr [esi]
0050df9b  6a11                     push       0x11
0050df9d  8bce                     mov        ecx, esi
0050df9f  c6451c00                 mov        byte ptr [ebp + 0x1c], 0
0050dfa3  ff502c                   call       dword ptr [eax + 0x2c]
0050dfa6  84c0                     test       al, al
0050dfa8  7420                     je         0x50dfca
0050dfaa  8b0dd4f10401             mov        ecx, dword ptr [0x104f1d4]
0050dfb0  8b11                     mov        edx, dword ptr [ecx]
0050dfb2  ff92c4010000             call       dword ptr [edx + 0x1c4]
0050dfb8  8bf8                     mov        edi, eax
0050dfba  8b06                     mov        eax, dword ptr [esi]
0050dfbc  8bce                     mov        ecx, esi
0050dfbe  ff90c4010000             call       dword ptr [eax + 0x1c4]
0050dfc4  3bf8                     cmp        edi, eax
0050dfc6  741c                     je         0x50dfe4
0050dfc8  eb16                     jmp        0x50dfe0
0050dfca  8b16                     mov        edx, dword ptr [esi]
0050dfcc  6a21                     push       0x21
0050dfce  8bce                     mov        ecx, esi
0050dfd0  ff522c                   call       dword ptr [edx + 0x2c]
0050dfd3  84c0                     test       al, al
0050dfd5  740d                     je         0x50dfe4
0050dfd7  83be2005000001           cmp        dword ptr [esi + 0x520], 1
0050dfde  7504                     jne        0x50dfe4
0050dfe0  c6451c01                 mov        byte ptr [ebp + 0x1c], 1
0050dfe4  8b451c                   mov        eax, dword ptr [ebp + 0x1c]
0050dfe7  50                       push       eax
0050dfe8  8bcb                     mov        ecx, ebx
0050dfea  e8d170efff               call       0x4050c0
0050dfef  8b16                     mov        edx, dword ptr [esi]
0050dff1  8bce                     mov        ecx, esi
0050dff3  ff5210                   call       dword ptr [edx + 0x10]
0050dff6  8b06                     mov        eax, dword ptr [esi]
0050dff8  6a21                     push       0x21
0050dffa  8bce                     mov        ecx, esi
0050dffc  ff502c                   call       dword ptr [eax + 0x2c]
0050dfff  84c0                     test       al, al
0050e001  742a                     je         0x50e02d
0050e003  8b16                     mov        edx, dword ptr [esi]
0050e005  8bce                     mov        ecx, esi
0050e007  ff923c030000             call       dword ptr [edx + 0x33c]
0050e00d  8b4808                   mov        ecx, dword ptr [eax + 8]
0050e010  85c9                     test       ecx, ecx
0050e012  7419                     je         0x50e02d
0050e014  8b8314010000             mov        eax, dword ptr [ebx + 0x114]
0050e01a  85c0                     test       eax, eax
0050e01c  740f                     je         0x50e02d
0050e01e  8b4850                   mov        ecx, dword ptr [eax + 0x50]
0050e021  85c9                     test       ecx, ecx
0050e023  7408                     je         0x50e02d
0050e025  6a01                     push       1
0050e027  56                       push       esi
0050e028  e83380f7ff               call       0x486060
0050e02d  8b06                     mov        eax, dword ptr [esi]
0050e02f  6811010000               push       0x111
0050e034  8bce                     mov        ecx, esi
0050e036  ff502c                   call       dword ptr [eax + 0x2c]
0050e039  84c0                     test       al, al
0050e03b  7414                     je         0x50e051
0050e03d  33ff                     xor        edi, edi
0050e03f  90                       nop        
0050e040  6a01                     push       1
0050e042  57                       push       edi
0050e043  56                       push       esi
0050e044  8bcb                     mov        ecx, ebx
0050e046  e835cbffff               call       0x50ab80
0050e04b  47                       inc        edi
0050e04c  83ff13                   cmp        edi, 0x13
0050e04f  7cef                     jl         0x50e040
0050e051  5f                       pop        edi
0050e052  5e                       pop        esi
0050e053  5b                       pop        ebx
0050e054  8be5                     mov        esp, ebp
0050e056  5d                       pop        ebp
0050e057  c21c00                   ret        0x1c
0050e05a  cc                       int3       