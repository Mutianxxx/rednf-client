00726150  55                       push       ebp
00726151  8bec                     mov        ebp, esp
00726153  6aff                     push       -1
00726155  685113c700               push       0xc71351
0072615a  64a100000000             mov        eax, dword ptr fs:[0]
00726160  50                       push       eax
00726161  64892500000000           mov        dword ptr fs:[0], esp
00726168  81ec98070000             sub        esp, 0x798
0072616e  53                       push       ebx
0072616f  56                       push       esi
00726170  57                       push       edi
00726171  8bf1                     mov        esi, ecx
00726173  e85898d9ff               call       0x4bf9d0
00726178  8b86582b0000             mov        eax, dword ptr [esi + 0x2b58]
0072617e  33db                     xor        ebx, ebx
00726180  3bc3                     cmp        eax, ebx
00726182  7413                     je         0x726197
00726184  38983a010000             cmp        byte ptr [eax + 0x13a], bl
0072618a  740b                     je         0x726197
0072618c  8b16                     mov        edx, dword ptr [esi]
0072618e  50                       push       eax
0072618f  8bce                     mov        ecx, esi
00726191  ff92fc000000             call       dword ptr [edx + 0xfc]
00726197  8bce                     mov        ecx, esi
00726199  e8928cffff               call       0x71ee30
0072619e  8b06                     mov        eax, dword ptr [esi]
007261a0  6a35                     push       0x35
007261a2  8bce                     mov        ecx, esi
007261a4  ff904c060000             call       dword ptr [eax + 0x64c]
007261aa  85c0                     test       eax, eax
007261ac  7e1f                     jle        0x7261cd
007261ae  8d4e60                   lea        ecx, [esi + 0x60]
007261b1  e84a0d3e00               call       0xb06f00
007261b6  50                       push       eax
007261b7  8d8e88330000             lea        ecx, [esi + 0x3388]
007261bd  e8eebd3200               call       0xa51fb0
007261c2  84c0                     test       al, al
007261c4  7407                     je         0x7261cd
007261c6  8bce                     mov        ecx, esi
007261c8  e803f1ffff               call       0x7252d0
007261cd  8bce                     mov        ecx, esi
007261cf  e84cbbffff               call       0x721d20
007261d4  8d8e5c150000             lea        ecx, [esi + 0x155c]
007261da  e881becdff               call       0x402060
007261df  83f834                   cmp        eax, 0x34
007261e2  0f8749490000             ja         0x72ab31
007261e8  0fb68804037300           movzx      ecx, byte ptr [eax + 0x730304]
007261ef  ff248d80027300           jmp        dword ptr [ecx*4 + 0x730280]
007261f6  8d8eb4160000             lea        ecx, [esi + 0x16b4]
007261fc  e85fbecdff               call       0x402060
00726201  85c0                     test       eax, eax
00726203  743e                     je         0x726243
00726205  8b8e6c300000             mov        ecx, dword ptr [esi + 0x306c]
0072620b  3bcb                     cmp        ecx, ebx
0072620d  7434                     je         0x726243
0072620f  8b11                     mov        edx, dword ptr [ecx]
00726211  ff5260                   call       dword ptr [edx + 0x60]
00726214  84c0                     test       al, al
00726216  742b                     je         0x726243
00726218  389e70300000             cmp        byte ptr [esi + 0x3070], bl
0072621e  0f850d490000             jne        0x72ab31
00726224  8b06                     mov        eax, dword ptr [esi]
00726226  53                       push       ebx
00726227  53                       push       ebx
00726228  6a16                     push       0x16
0072622a  6830c1d700               push       0xd7c130
0072622f  8bce                     mov        ecx, esi
00726231  ff900c010000             call       dword ptr [eax + 0x10c]
00726237  c6867030000001           mov        byte ptr [esi + 0x3070], 1
0072623e  e9ee480000               jmp        0x72ab31
00726243  389e70300000             cmp        byte ptr [esi + 0x3070], bl
00726249  0f84e2480000             je         0x72ab31
0072624f  8b16                     mov        edx, dword ptr [esi]
00726251  6a16                     push       0x16
00726253  8bce                     mov        ecx, esi
00726255  ff9210010000             call       dword ptr [edx + 0x110]
0072625b  889e70300000             mov        byte ptr [esi + 0x3070], bl
00726261  e9cb480000               jmp        0x72ab31
00726266  8dbea82a0000             lea        edi, [esi + 0x2aa8]
0072626c  8bcf                     mov        ecx, edi
0072626e  e8edbdcdff               call       0x402060
00726273  83f82e                   cmp        eax, 0x2e
00726276  0f85b0000000             jne        0x72632c
0072627c  389eb4330000             cmp        byte ptr [esi + 0x33b4], bl
00726282  7554                     jne        0x7262d8
00726284  8b8604010000             mov        eax, dword ptr [esi + 0x104]
0072628a  83b82401000003           cmp        dword ptr [eax + 0x124], 3
00726291  7c45                     jl         0x7262d8
00726293  c686b433000001           mov        byte ptr [esi + 0x33b4], 1
0072629a  8b16                     mov        edx, dword ptr [esi]
0072629c  8bce                     mov        ecx, esi
0072629e  33ff                     xor        edi, edi
007262a0  895df0                   mov        dword ptr [ebp - 0x10], ebx
007262a3  ff9220060000             call       dword ptr [edx + 0x620]
007262a9  85c0                     test       eax, eax
007262ab  750c                     jne        0x7262b9
007262ad  bf05000000               mov        edi, 5
007262b2  b8eeffffff               mov        eax, 0xffffffee
007262b7  eb03                     jmp        0x7262bc
007262b9  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
007262bc  8b16                     mov        edx, dword ptr [esi]
007262be  6a01                     push       1
007262c0  53                       push       ebx
007262c1  53                       push       ebx
007262c2  53                       push       ebx
007262c3  53                       push       ebx
007262c4  53                       push       ebx
007262c5  50                       push       eax
007262c6  8b86ac330000             mov        eax, dword ptr [esi + 0x33ac]
007262cc  57                       push       edi
007262cd  50                       push       eax
007262ce  6a01                     push       1
007262d0  8bce                     mov        ecx, esi
007262d2  ff92f8000000             call       dword ptr [edx + 0xf8]
007262d8  8b86ac330000             mov        eax, dword ptr [esi + 0x33ac]
007262de  3bc3                     cmp        eax, ebx
007262e0  7413                     je         0x7262f5
007262e2  38983a010000             cmp        byte ptr [eax + 0x13a], bl
007262e8  740b                     je         0x7262f5
007262ea  8b16                     mov        edx, dword ptr [esi]
007262ec  50                       push       eax
007262ed  8bce                     mov        ecx, esi
007262ef  ff92fc000000             call       dword ptr [edx + 0xfc]
007262f5  389ebc2a0000             cmp        byte ptr [esi + 0x2abc], bl
007262fb  0f8530480000             jne        0x72ab31
00726301  8b8604010000             mov        eax, dword ptr [esi + 0x104]
00726307  83b82401000001           cmp        dword ptr [eax + 0x124], 1
0072630e  0f8e1d480000             jle        0x72ab31
00726314  8b16                     mov        edx, dword ptr [esi]
00726316  53                       push       ebx
00726317  53                       push       ebx
00726318  8bce                     mov        ecx, esi
0072631a  ff92e0020000             call       dword ptr [edx + 0x2e0]
00726320  c686bc2a000001           mov        byte ptr [esi + 0x2abc], 1
00726327  e905480000               jmp        0x72ab31
0072632c  8bcf                     mov        ecx, edi
0072632e  e82dbdcdff               call       0x402060
00726333  83f8ff                   cmp        eax, -1
00726336  0f85c9000000             jne        0x726405
0072633c  389e80320000             cmp        byte ptr [esi + 0x3280], bl
00726342  0f84e9470000             je         0x72ab31
00726348  8d8e28180000             lea        ecx, [esi + 0x1828]
0072634e  e80dbdcdff               call       0x402060
00726353  83f802                   cmp        eax, 2
00726356  0f85d5470000             jne        0x72ab31
0072635c  389e81320000             cmp        byte ptr [esi + 0x3281], bl
00726362  0f85c9470000             jne        0x72ab31
00726368  8b8604010000             mov        eax, dword ptr [esi + 0x104]
0072636e  83b82401000002           cmp        dword ptr [eax + 0x124], 2
00726375  0f8cb6470000             jl         0x72ab31
0072637b  8bce                     mov        ecx, esi
0072637d  e80e5dd7ff               call       0x49c090
00726382  84c0                     test       al, al
00726384  7473                     je         0x7263f9
00726386  8b16                     mov        edx, dword ptr [esi]
00726388  6a0c                     push       0xc
0072638a  8bce                     mov        ecx, esi
0072638c  ff92d0010000             call       dword ptr [edx + 0x1d0]
00726392  50                       push       eax
00726393  8b06                     mov        eax, dword ptr [esi]
00726395  56                       push       esi
00726396  6a58                     push       0x58
00726398  8bce                     mov        ecx, esi
0072639a  ff904c060000             call       dword ptr [eax + 0x64c]
007263a0  8b16                     mov        edx, dword ptr [esi]
007263a2  50                       push       eax
007263a3  6a08                     push       8
007263a5  6a58                     push       0x58
007263a7  8bce                     mov        ecx, esi
007263a9  ff927c060000             call       dword ptr [edx + 0x67c]
007263af  8bc8                     mov        ecx, eax
007263b1  e86a46daff               call       0x4caa20
007263b6  8b3e                     mov        edi, dword ptr [esi]
007263b8  53                       push       ebx
007263b9  53                       push       ebx
007263ba  53                       push       ebx
007263bb  53                       push       ebx
007263bc  53                       push       ebx
007263bd  6a04                     push       4
007263bf  83e864                   sub        eax, 0x64
007263c2  680cc1d700               push       0xd7c10c
007263c7  b918030501               mov        ecx, 0x1050318
007263cc  8945f0                   mov        dword ptr [ebp - 0x10], eax
007263cf  e87c5c1800               call       0x8ac050
007263d4  50                       push       eax
007263d5  53                       push       ebx
007263d6  68e8c0d700               push       0xd7c0e8
007263db  b918030501               mov        ecx, 0x1050318
007263e0  e86b5c1800               call       0x8ac050
007263e5  50                       push       eax
007263e6  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
007263e9  53                       push       ebx
007263ea  53                       push       ebx
007263eb  50                       push       eax
007263ec  68594e0000               push       0x4e59
007263f1  8bce                     mov        ecx, esi
007263f3  ff97b8020000             call       dword ptr [edi + 0x2b8]
007263f9  c6868132000001           mov        byte ptr [esi + 0x3281], 1
00726400  e92c470000               jmp        0x72ab31
00726405  8bcf                     mov        ecx, edi
00726407  e854bccdff               call       0x402060
0072640c  83f843                   cmp        eax, 0x43
0072640f  0f851c470000             jne        0x72ab31
00726415  389ec82a0000             cmp        byte ptr [esi + 0x2ac8], bl
0072641b  0f8410470000             je         0x72ab31
00726421  389ed8010000             cmp        byte ptr [esi + 0x1d8], bl
00726427  740c                     je         0x726435
00726429  81bedc010000ff0000ff     cmp        dword ptr [esi + 0x1dc], 0xff0000ff
00726433  7415                     je         0x72644a
00726435  8b16                     mov        edx, dword ptr [esi]
00726437  6a02                     push       2
00726439  6a01                     push       1
0072643b  68ff0000ff               push       0xff0000ff
00726440  6a01                     push       1
00726442  8bce                     mov        ecx, esi
00726444  ff924c010000             call       dword ptr [edx + 0x14c]
0072644a  8d8ec4040000             lea        ecx, [esi + 0x4c4]
00726450  e80bbccdff               call       0x402060
00726455  83f801                   cmp        eax, 1
00726458  0f84d3460000             je         0x72ab31
0072645e  8b06                     mov        eax, dword ptr [esi]
00726460  6a01                     push       1
00726462  6a01                     push       1
00726464  8bce                     mov        ecx, esi
00726466  ff90e0020000             call       dword ptr [eax + 0x2e0]
0072646c  e9c0460000               jmp        0x72ab31
00726471  83bec02e000001           cmp        dword ptr [esi + 0x2ec0], 1
00726478  0f85b3460000             jne        0x72ab31
0072647e  8b8ef8000000             mov        ecx, dword ptr [esi + 0xf8]
00726484  e8579bcfff               call       0x41ffe0
00726489  8b10                     mov        edx, dword ptr [eax]
0072648b  53                       push       ebx
0072648c  8bc8                     mov        ecx, eax
0072648e  ff5208                   call       dword ptr [edx + 8]
00726491  d9e1                     fabs       
00726493  d81d7081cc00             fcomp      dword ptr [0xcc8170]
00726499  dfe0                     fnstsw     ax
0072649b  f6c405                   test       ah, 5
0072649e  0f8a06010000             jp         0x7265aa
007264a4  389ed02e0000             cmp        byte ptr [esi + 0x2ed0], bl
007264aa  0f85fa000000             jne        0x7265aa
007264b0  68e8010000               push       0x1e8
007264b5  e896d7cdff               call       0x403c50
007264ba  8bf8                     mov        edi, eax
007264bc  83c404                   add        esp, 4
007264bf  897dec                   mov        dword ptr [ebp - 0x14], edi
007264c2  3bfb                     cmp        edi, ebx
007264c4  895dfc                   mov        dword ptr [ebp - 4], ebx
007264c7  741e                     je         0x7264e7
007264c9  6a01                     push       1
007264cb  68a8c0d700               push       0xd7c0a8
007264d0  8d8e44020000             lea        ecx, [esi + 0x244]
007264d6  e8d5cfd0ff               call       0x4334b0
007264db  50                       push       eax
007264dc  8bcf                     mov        ecx, edi
007264de  e87dc5d4ff               call       0x472a60
007264e3  8bf8                     mov        edi, eax
007264e5  eb02                     jmp        0x7264e9
007264e7  33ff                     xor        edi, edi
007264e9  68fc010000               push       0x1fc
007264ee  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
007264f5  e856d7cdff               call       0x403c50
007264fa  83c404                   add        esp, 4
007264fd  8945ec                   mov        dword ptr [ebp - 0x14], eax
00726500  3bc3                     cmp        eax, ebx
00726502  c745fc01000000           mov        dword ptr [ebp - 4], 1
00726509  740e                     je         0x726519
0072650b  6a01                     push       1
0072650d  57                       push       edi
0072650e  8bc8                     mov        ecx, eax
00726510  e80b58d8ff               call       0x4abd20
00726515  8bf8                     mov        edi, eax
00726517  eb02                     jmp        0x72651b
00726519  33ff                     xor        edi, edi
0072651b  8b8e00010000             mov        ecx, dword ptr [esi + 0x100]
00726521  53                       push       ebx
00726522  53                       push       ebx
00726523  56                       push       esi
00726524  57                       push       edi
00726525  53                       push       ebx
00726526  6a02                     push       2
00726528  56                       push       esi
00726529  897ddc                   mov        dword ptr [ebp - 0x24], edi
0072652c  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
00726533  e83878deff               call       0x50dd70
00726538  8b07                     mov        eax, dword ptr [edi]
0072653a  8b16                     mov        edx, dword ptr [esi]
0072653c  8bce                     mov        ecx, esi
0072653e  8945f0                   mov        dword ptr [ebp - 0x10], eax
00726541  ff92c0000000             call       dword ptr [edx + 0xc0]
00726547  50                       push       eax
00726548  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
0072654b  8bcf                     mov        ecx, edi
0072654d  ff90bc000000             call       dword ptr [eax + 0xbc]
00726553  8b06                     mov        eax, dword ptr [esi]
00726555  8bce                     mov        ecx, esi
00726557  ff90c0000000             call       dword ptr [eax + 0xc0]
0072655d  85c0                     test       eax, eax
0072655f  8bce                     mov        ecx, esi
00726561  750d                     jne        0x726570
00726563  8b16                     mov        edx, dword ptr [esi]
00726565  ff9294000000             call       dword ptr [edx + 0x94]
0072656b  83c02d                   add        eax, 0x2d
0072656e  eb0b                     jmp        0x72657b
00726570  8b06                     mov        eax, dword ptr [esi]
00726572  ff9094000000             call       dword ptr [eax + 0x94]
00726578  83e82d                   sub        eax, 0x2d
0072657b  8b16                     mov        edx, dword ptr [esi]
0072657d  8b3f                     mov        edi, dword ptr [edi]
0072657f  8bce                     mov        ecx, esi
00726581  8945f0                   mov        dword ptr [ebp - 0x10], eax
00726584  ff929c000000             call       dword ptr [edx + 0x9c]
0072658a  50                       push       eax
0072658b  8b06                     mov        eax, dword ptr [esi]
0072658d  8bce                     mov        ecx, esi
0072658f  ff9098000000             call       dword ptr [eax + 0x98]
00726595  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
00726598  50                       push       eax
00726599  51                       push       ecx
0072659a  8b4ddc                   mov        ecx, dword ptr [ebp - 0x24]
0072659d  ff9788000000             call       dword ptr [edi + 0x88]
007265a3  c686d02e000001           mov        byte ptr [esi + 0x2ed0], 1
007265aa  8d8e64150000             lea        ecx, [esi + 0x1564]
007265b0  e84b093e00               call       0xb06f00
007265b5  3b86c82e0000             cmp        eax, dword ptr [esi + 0x2ec8]
007265bb  0f8c70450000             jl         0x72ab31
007265c1  83bee82e000001           cmp        dword ptr [esi + 0x2ee8], 1
007265c8  0f8509020000             jne        0x7267d7
007265ce  8b16                     mov        edx, dword ptr [esi]
007265d0  56                       push       esi
007265d1  6a03                     push       3
007265d3  6a01                     push       1
007265d5  8bce                     mov        ecx, esi
007265d7  ff927c060000             call       dword ptr [edx + 0x67c]
007265dd  8bc8                     mov        ecx, eax
007265df  e87c99e2ff               call       0x54ff60
007265e4  56                       push       esi
007265e5  6a02                     push       2
007265e7  8bf8                     mov        edi, eax
007265e9  8b06                     mov        eax, dword ptr [esi]
007265eb  6a01                     push       1
007265ed  8bce                     mov        ecx, esi
007265ef  ff907c060000             call       dword ptr [eax + 0x67c]
007265f5  8bc8                     mov        ecx, eax
007265f7  e86499e2ff               call       0x54ff60
007265fc  8bc8                     mov        ecx, eax
007265fe  8bc7                     mov        eax, edi
00726600  69c018fcffff             imul       eax, eax, 0xfffffc18
00726606  99                       cdq        
00726607  f7f9                     idiv       ecx
00726609  8b16                     mov        edx, dword ptr [esi]
0072660b  6a01                     push       1
0072660d  894df0                   mov        dword ptr [ebp - 0x10], ecx
00726610  8bce                     mov        ecx, esi
00726612  50                       push       eax
00726613  53                       push       ebx
00726614  57                       push       edi
00726615  57                       push       edi
00726616  53                       push       ebx
00726617  ff9288040000             call       dword ptr [edx + 0x488]
0072661d  8b3e                     mov        edi, dword ptr [esi]
0072661f  53                       push       ebx
00726620  6a04                     push       4
00726622  8bce                     mov        ecx, esi
00726624  ff97c0000000             call       dword ptr [edi + 0xc0]
0072662a  50                       push       eax
0072662b  8bce                     mov        ecx, esi
0072662d  ff979c040000             call       dword ptr [edi + 0x49c]
00726633  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
00726636  8bbec82e0000             mov        edi, dword ptr [esi + 0x2ec8]
0072663c  83c064                   add        eax, 0x64
0072663f  03f8                     add        edi, eax
00726641  89bec82e0000             mov        dword ptr [esi + 0x2ec8], edi
00726647  8b8e04010000             mov        ecx, dword ptr [esi + 0x104]
0072664d  53                       push       ebx
0072664e  e80d3dd9ff               call       0x4ba360
00726653  8bce                     mov        ecx, esi
00726655  e8365ad7ff               call       0x49c090
0072665a  84c0                     test       al, al
0072665c  0f8466010000             je         0x7267c8
00726662  8b16                     mov        edx, dword ptr [esi]
00726664  8bce                     mov        ecx, esi
00726666  ff9220060000             call       dword ptr [edx + 0x620]
0072666c  83f803                   cmp        eax, 3
0072666f  7533                     jne        0x7266a4
00726671  8b06                     mov        eax, dword ptr [esi]
00726673  6a0e                     push       0xe
00726675  8bce                     mov        ecx, esi
00726677  ff904c060000             call       dword ptr [eax + 0x64c]
0072667d  85c0                     test       eax, eax
0072667f  7e23                     jle        0x7266a4
00726681  8b16                     mov        edx, dword ptr [esi]
00726683  6a0e                     push       0xe
00726685  8bce                     mov        ecx, esi
00726687  ff927c060000             call       dword ptr [edx + 0x67c]
0072668d  8bf8                     mov        edi, eax
0072668f  8b06                     mov        eax, dword ptr [esi]
00726691  6a0e                     push       0xe
00726693  8bce                     mov        ecx, esi
00726695  ff904c060000             call       dword ptr [eax + 0x64c]
0072669b  c745e403000000           mov        dword ptr [ebp - 0x1c], 3
007266a2  eb47                     jmp        0x7266eb
007266a4  8b16                     mov        edx, dword ptr [esi]
007266a6  8bce                     mov        ecx, esi
007266a8  ff9220060000             call       dword ptr [edx + 0x620]
007266ae  85c0                     test       eax, eax
007266b0  0f8512010000             jne        0x7267c8
007266b6  8b06                     mov        eax, dword ptr [esi]
007266b8  6a0c                     push       0xc
007266ba  8bce                     mov        ecx, esi
007266bc  ff904c060000             call       dword ptr [eax + 0x64c]
007266c2  85c0                     test       eax, eax
007266c4  0f8efe000000             jle        0x7267c8
007266ca  8b16                     mov        edx, dword ptr [esi]
007266cc  6a0c                     push       0xc
007266ce  8bce                     mov        ecx, esi
007266d0  ff927c060000             call       dword ptr [edx + 0x67c]
007266d6  8bf8                     mov        edi, eax
007266d8  8b06                     mov        eax, dword ptr [esi]
007266da  6a0c                     push       0xc
007266dc  8bce                     mov        ecx, esi
007266de  ff904c060000             call       dword ptr [eax + 0x64c]
007266e4  c745e404000000           mov        dword ptr [ebp - 0x1c], 4
007266eb  3bfb                     cmp        edi, ebx
007266ed  8945d8                   mov        dword ptr [ebp - 0x28], eax
007266f0  0f84d2000000             je         0x7267c8
007266f6  8b16                     mov        edx, dword ptr [esi]
007266f8  6a0c                     push       0xc
007266fa  8bce                     mov        ecx, esi
007266fc  ff92d0010000             call       dword ptr [edx + 0x1d0]
00726702  8b4de4                   mov        ecx, dword ptr [ebp - 0x1c]
00726705  50                       push       eax
00726706  8b45d8                   mov        eax, dword ptr [ebp - 0x28]
00726709  56                       push       esi
0072670a  50                       push       eax
0072670b  51                       push       ecx
0072670c  8bcf                     mov        ecx, edi
0072670e  e80d43daff               call       0x4caa20
00726713  8b55d8                   mov        edx, dword ptr [ebp - 0x28]
00726716  53                       push       ebx
00726717  53                       push       ebx
00726718  6a0c                     push       0xc
0072671a  6aff                     push       -1
0072671c  83e864                   sub        eax, 0x64
0072671f  6aff                     push       -1
00726721  8945e0                   mov        dword ptr [ebp - 0x20], eax
00726724  8b45e4                   mov        eax, dword ptr [ebp - 0x1c]
00726727  56                       push       esi
00726728  52                       push       edx
00726729  40                       inc        eax
0072672a  50                       push       eax
0072672b  8bcf                     mov        ecx, edi
0072672d  891d8c47f500             mov        dword ptr [0xf5478c], ebx
00726733  e84899e2ff               call       0x550080
00726738  8945f0                   mov        dword ptr [ebp - 0x10], eax
0072673b  db45f0                   fild       dword ptr [ebp - 0x10]
0072673e  51                       push       ecx
0072673f  b98447f500               mov        ecx, 0xf54784
00726744  d80d3088cc00             fmul       dword ptr [0xcc8830]
0072674a  d91c24                   fstp       dword ptr [esp]
0072674d  e8                       .byte      0xe8
0072674e  de18                     ficomp     word ptr [eax]