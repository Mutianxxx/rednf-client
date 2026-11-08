; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 00a570d0..00a57431 (end exclusive); file offset 006570d0
; This is an instruction excerpt, not a recovered original source file.
00a570d0  55                       push       ebp
00a570d1  8bec                     mov        ebp, esp
00a570d3  6aff                     push       -1
00a570d5  68c5fbc800               push       0xc8fbc5
00a570da  64a100000000             mov        eax, dword ptr fs:[0]
00a570e0  50                       push       eax
00a570e1  64892500000000           mov        dword ptr fs:[0], esp
00a570e8  83ec28                   sub        esp, 0x28
00a570eb  56                       push       esi
00a570ec  8bf1                     mov        esi, ecx
00a570ee  8a467c                   mov        al, byte ptr [esi + 0x7c]
00a570f1  84c0                     test       al, al
00a570f3  7424                     je         0xa57119
00a570f5  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00a570f8  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00a570fb  8b5508                   mov        edx, dword ptr [ebp + 8]
00a570fe  50                       push       eax
00a570ff  51                       push       ecx
00a57100  52                       push       edx
00a57101  8bce                     mov        ecx, esi
00a57103  e868f7ffff               call       0xa56870
00a57108  5e                       pop        esi
00a57109  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a5710c  64890d00000000           mov        dword ptr fs:[0], ecx
00a57113  8be5                     mov        esp, ebp
00a57115  5d                       pop        ebp
00a57116  c20c00                   ret        0xc
00a57119  33c9                     xor        ecx, ecx
00a5711b  c745e407000000           mov        dword ptr [ebp - 0x1c], 7
00a57122  894de0                   mov        dword ptr [ebp - 0x20], ecx
00a57125  66894dd0                 mov        word ptr [ebp - 0x30], cx
00a57129  8b4614                   mov        eax, dword ptr [esi + 0x14]
00a5712c  3bc1                     cmp        eax, ecx
00a5712e  894dfc                   mov        dword ptr [ebp - 4], ecx
00a57131  7477                     je         0xa571aa
00a57133  8b4e18                   mov        ecx, dword ptr [esi + 0x18]
00a57136  2bc8                     sub        ecx, eax
00a57138  b889888888               mov        eax, 0x88888889
00a5713d  f7e9                     imul       ecx
00a5713f  03d1                     add        edx, ecx
00a57141  c1fa05                   sar        edx, 5
00a57144  8bc2                     mov        eax, edx
00a57146  c1e81f                   shr        eax, 0x1f
00a57149  03c2                     add        eax, edx
00a5714b  8945e8                   mov        dword ptr [ebp - 0x18], eax
00a5714e  745a                     je         0xa571aa
00a57150  682cace400               push       0xe4ac2c
00a57155  68808eff00               push       0xff8e80
00a5715a  e890b11a00               call       0xc022ef
00a5715f  6874ace400               push       0xe4ac74
00a57164  68f7030000               push       0x3f7
00a57169  68f0a5e400               push       0xe4a5f0
00a5716e  68eca4e400               push       0xe4a4ec
00a57173  68808eff00               push       0xff8e80
00a57178  e872b11a00               call       0xc022ef
00a5717d  8b45e4                   mov        eax, dword ptr [ebp - 0x1c]
00a57180  83c41c                   add        esp, 0x1c
00a57183  83f808                   cmp        eax, 8
00a57186  720c                     jb         0xa57194
00a57188  8b4dd0                   mov        ecx, dword ptr [ebp - 0x30]
00a5718b  51                       push       ecx
00a5718c  e84c8e1a00               call       0xbfffdd
00a57191  83c404                   add        esp, 4
00a57194  b801000000               mov        eax, 1
00a57199  5e                       pop        esi
00a5719a  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a5719d  64890d00000000           mov        dword ptr fs:[0], ecx
00a571a4  8be5                     mov        esp, ebp
00a571a6  5d                       pop        ebp
00a571a7  c20c00                   ret        0xc
00a571aa  53                       push       ebx
00a571ab  8b5d08                   mov        ebx, dword ptr [ebp + 8]
00a571ae  57                       push       edi
00a571af  68a036e100               push       0xe136a0
00a571b4  53                       push       ebx
00a571b5  e86fab1a00               call       0xc01d29
00a571ba  8bf8                     mov        edi, eax
00a571bc  83c408                   add        esp, 8
00a571bf  85ff                     test       edi, edi
00a571c1  755d                     jne        0xa57220
00a571c3  53                       push       ebx
00a571c4  684cace400               push       0xe4ac4c
00a571c9  68808eff00               push       0xff8e80
00a571ce  e81cb11a00               call       0xc022ef
00a571d3  6874ace400               push       0xe4ac74
00a571d8  68fe030000               push       0x3fe
00a571dd  68f0a5e400               push       0xe4a5f0
00a571e2  68eca4e400               push       0xe4a4ec
00a571e7  68808eff00               push       0xff8e80
00a571ec  e8feb01a00               call       0xc022ef
00a571f1  8b45e4                   mov        eax, dword ptr [ebp - 0x1c]
00a571f4  83c420                   add        esp, 0x20
00a571f7  83f808                   cmp        eax, 8
00a571fa  720c                     jb         0xa57208
00a571fc  8b55d0                   mov        edx, dword ptr [ebp - 0x30]
00a571ff  52                       push       edx
00a57200  e8d88d1a00               call       0xbfffdd
00a57205  83c404                   add        esp, 4
00a57208  5f                       pop        edi
00a57209  5b                       pop        ebx
00a5720a  b801000000               mov        eax, 1
00a5720f  5e                       pop        esi
00a57210  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a57213  64890d00000000           mov        dword ptr fs:[0], ecx
00a5721a  8be5                     mov        esp, ebp
00a5721c  5d                       pop        ebp
00a5721d  c20c00                   ret        0xc
00a57220  8d45cc                   lea        eax, [ebp - 0x34]
00a57223  50                       push       eax
00a57224  8bc7                     mov        eax, edi
00a57226  e8c5e8ffff               call       0xa55af0
00a5722b  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00a5722e  83c404                   add        esp, 4
00a57231  85c0                     test       eax, eax
00a57233  747c                     je         0xa572b1
00a57235  8b4de4                   mov        ecx, dword ptr [ebp - 0x1c]
00a57238  bb08000000               mov        ebx, 8
00a5723d  3bcb                     cmp        ecx, ebx
00a5723f  8b4dd0                   mov        ecx, dword ptr [ebp - 0x30]
00a57242  7303                     jae        0xa57247
00a57244  8d4dd0                   lea        ecx, [ebp - 0x30]
00a57247  50                       push       eax
00a57248  51                       push       ecx
00a57249  e89d9b1a00               call       0xc00deb
00a5724e  83c408                   add        esp, 8
00a57251  85c0                     test       eax, eax
00a57253  745c                     je         0xa572b1
00a57255  395de4                   cmp        dword ptr [ebp - 0x1c], ebx
00a57258  8b45d0                   mov        eax, dword ptr [ebp - 0x30]
00a5725b  7303                     jae        0xa57260
00a5725d  8d45d0                   lea        eax, [ebp - 0x30]
00a57260  50                       push       eax
00a57261  6848abe400               push       0xe4ab48
00a57266  68808eff00               push       0xff8e80
00a5726b  e87fb01a00               call       0xc022ef
00a57270  6874ace400               push       0xe4ac74
00a57275  6804040000               push       0x404
00a5727a  68f0a5e400               push       0xe4a5f0
00a5727f  68eca4e400               push       0xe4a4ec
00a57284  68808eff00               push       0xff8e80
00a57289  e861b01a00               call       0xc022ef
00a5728e  83c420                   add        esp, 0x20
00a57291  8d4dcc                   lea        ecx, [ebp - 0x34]
00a57294  e8d76d1300               call       0xb8e070
00a57299  5f                       pop        edi
00a5729a  5b                       pop        ebx
00a5729b  b801000000               mov        eax, 1
00a572a0  5e                       pop        esi
00a572a1  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a572a4  64890d00000000           mov        dword ptr fs:[0], ecx
00a572ab  8be5                     mov        esp, ebp
00a572ad  5d                       pop        ebp
00a572ae  c20c00                   ret        0xc
00a572b1  57                       push       edi
00a572b2  6a01                     push       1
00a572b4  8d4e04                   lea        ecx, [esi + 4]
00a572b7  6a04                     push       4
00a572b9  51                       push       ecx
00a572ba  e877b11a00               call       0xc02436
00a572bf  57                       push       edi
00a572c0  6a01                     push       1
00a572c2  8d5508                   lea        edx, [ebp + 8]
00a572c5  6a04                     push       4
00a572c7  52                       push       edx
00a572c8  e869b11a00               call       0xc02436
00a572cd  57                       push       edi
00a572ce  6a01                     push       1
00a572d0  8d45ec                   lea        eax, [ebp - 0x14]
00a572d3  6a04                     push       4
00a572d5  50                       push       eax
00a572d6  e85bb11a00               call       0xc02436
00a572db  57                       push       edi
00a572dc  6a01                     push       1
00a572de  8d4df0                   lea        ecx, [ebp - 0x10]
00a572e1  6a04                     push       4
00a572e3  51                       push       ecx
00a572e4  e84db11a00               call       0xc02436
00a572e9  8b5508                   mov        edx, dword ptr [ebp + 8]
00a572ec  83c440                   add        esp, 0x40
00a572ef  52                       push       edx
00a572f0  e8cc661900               call       0xbed9c1
00a572f5  8bd8                     mov        ebx, eax
00a572f7  8b4508                   mov        eax, dword ptr [ebp + 8]
00a572fa  57                       push       edi
00a572fb  6a01                     push       1
00a572fd  50                       push       eax
00a572fe  53                       push       ebx
00a572ff  895de8                   mov        dword ptr [ebp - 0x18], ebx
00a57302  e82fb11a00               call       0xc02436
00a57307  57                       push       edi
00a57308  e8d7b21a00               call       0xc025e4
00a5730d  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00a57310  51                       push       ecx
00a57311  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
00a57314  894608                   mov        dword ptr [esi + 8], eax
00a57317  8b45ec                   mov        eax, dword ptr [ebp - 0x14]
00a5731a  53                       push       ebx
00a5731b  50                       push       eax
00a5731c  893e                     mov        dword ptr [esi], edi
00a5731e  e84ddbffff               call       0xa54e70
00a57323  83c424                   add        esp, 0x24
00a57326  85c0                     test       eax, eax
00a57328  7529                     jne        0xa57353
00a5732a  53                       push       ebx
00a5732b  e8569f1a00               call       0xc01286
00a57330  83c404                   add        esp, 4
00a57333  8d4dcc                   lea        ecx, [ebp - 0x34]
00a57336  e8356d1300               call       0xb8e070
00a5733b  5f                       pop        edi
00a5733c  5b                       pop        ebx
00a5733d  b801000000               mov        eax, 1
00a57342  5e                       pop        esi
00a57343  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a57346  64890d00000000           mov        dword ptr fs:[0], ecx
00a5734d  8be5                     mov        esp, ebp
00a5734f  5d                       pop        ebp
00a57350  c20c00                   ret        0xc
00a57353  8b55f0                   mov        edx, dword ptr [ebp - 0x10]
00a57356  52                       push       edx
00a57357  8d4e10                   lea        ecx, [esi + 0x10]
00a5735a  895d0c                   mov        dword ptr [ebp + 0xc], ebx
00a5735d  e80e280000               call       0xa59b70
00a57362  8b5e14                   mov        ebx, dword ptr [esi + 0x14]
00a57365  3b5e18                   cmp        ebx, dword ptr [esi + 0x18]
00a57368  7429                     je         0xa57393
00a5736a  8d9b00000000             lea        ebx, [ebx]
00a57370  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00a57373  8b08                     mov        ecx, dword ptr [eax]
00a57375  8d550c                   lea        edx, [ebp + 0xc]
00a57378  890b                     mov        dword ptr [ebx], ecx
00a5737a  83c004                   add        eax, 4
00a5737d  52                       push       edx
00a5737e  8d4b04                   lea        ecx, [ebx + 4]
00a57381  89450c                   mov        dword ptr [ebp + 0xc], eax
00a57384  e817ecffff               call       0xa55fa0
00a57389  8b4618                   mov        eax, dword ptr [esi + 0x18]
00a5738c  83c33c                   add        ebx, 0x3c
00a5738f  3bd8                     cmp        ebx, eax
00a57391  75dd                     jne        0xa57370
00a57393  8b45e8                   mov        eax, dword ptr [ebp - 0x18]
00a57396  50                       push       eax
00a57397  e8ea9e1a00               call       0xc01286
00a5739c  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00a5739f  83c404                   add        esp, 4
00a573a2  85c0                     test       eax, eax
00a573a4  755e                     jne        0xa57404
00a573a6  6a02                     push       2
00a573a8  6a00                     push       0
00a573aa  57                       push       edi
00a573ab  e804b31a00               call       0xc026b4
00a573b0  57                       push       edi
00a573b1  e82eb21a00               call       0xc025e4
00a573b6  6a00                     push       0
00a573b8  8bd8                     mov        ebx, eax
00a573ba  6a00                     push       0
00a573bc  57                       push       edi
00a573bd  895d0c                   mov        dword ptr [ebp + 0xc], ebx
00a573c0  e8efb21a00               call       0xc026b4
00a573c5  53                       push       ebx
00a573c6  e8f6651900               call       0xbed9c1
00a573cb  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00a573ce  57                       push       edi
00a573cf  6a01                     push       1
00a573d1  8bd8                     mov        ebx, eax
00a573d3  51                       push       ecx
00a573d4  53                       push       ebx
00a573d5  e85cb01a00               call       0xc02436
00a573da  8b7e14                   mov        edi, dword ptr [esi + 0x14]
00a573dd  8b4618                   mov        eax, dword ptr [esi + 0x18]
00a573e0  83c430                   add        esp, 0x30
00a573e3  3bf8                     cmp        edi, eax
00a573e5  7414                     je         0xa573fb
00a573e7  56                       push       esi
00a573e8  53                       push       ebx
00a573e9  8d4f04                   lea        ecx, [edi + 4]
00a573ec  e81fdcffff               call       0xa55010
00a573f1  8b4618                   mov        eax, dword ptr [esi + 0x18]
00a573f4  83c73c                   add        edi, 0x3c
00a573f7  3bf8                     cmp        edi, eax
00a573f9  75ec                     jne        0xa573e7
00a573fb  53                       push       ebx
00a573fc  e8859e1a00               call       0xc01286
00a57401  83c404                   add        esp, 4
00a57404  837de408                 cmp        dword ptr [ebp - 0x1c], 8
00a57408  8b5510                   mov        edx, dword ptr [ebp + 0x10]
00a5740b  89560c                   mov        dword ptr [esi + 0xc], edx
00a5740e  720c                     jb         0xa5741c
00a57410  8b45d0                   mov        eax, dword ptr [ebp - 0x30]
00a57413  50                       push       eax
00a57414  e8c48b1a00               call       0xbfffdd
00a57419  83c404                   add        esp, 4
00a5741c  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a5741f  5f                       pop        edi
00a57420  5b                       pop        ebx
00a57421  33c0                     xor        eax, eax
00a57423  5e                       pop        esi
00a57424  64890d00000000           mov        dword ptr fs:[0], ecx
00a5742b  8be5                     mov        esp, ebp
00a5742d  5d                       pop        ebp
00a5742e  c20c00                   ret        0xc
