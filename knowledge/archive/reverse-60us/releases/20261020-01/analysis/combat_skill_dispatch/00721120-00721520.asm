00721120  55                       push       ebp
00721121  8bec                     mov        ebp, esp
00721123  6aff                     push       -1
00721125  68640cc700               push       0xc70c64
0072112a  64a100000000             mov        eax, dword ptr fs:[0]
00721130  50                       push       eax
00721131  64892500000000           mov        dword ptr fs:[0], esp
00721138  83ec2c                   sub        esp, 0x2c
0072113b  53                       push       ebx
0072113c  56                       push       esi
0072113d  57                       push       edi
0072113e  8b7d08                   mov        edi, dword ptr [ebp + 8]
00721141  8b07                     mov        eax, dword ptr [edi]
00721143  8bf1                     mov        esi, ecx
00721145  8bcf                     mov        ecx, edi
00721147  ff909c010000             call       dword ptr [eax + 0x19c]
0072114d  8bce                     mov        ecx, esi
0072114f  8945ec                   mov        dword ptr [ebp - 0x14], eax
00721152  e839afd7ff               call       0x49c090
00721157  84c0                     test       al, al
00721159  0f846e010000             je         0x7212cd
0072115f  8b16                     mov        edx, dword ptr [esi]
00721161  6a02                     push       2
00721163  8bce                     mov        ecx, esi
00721165  ff924c060000             call       dword ptr [edx + 0x64c]
0072116b  85c0                     test       eax, eax
0072116d  0f8e5a010000             jle        0x7212cd
00721173  8d8e5c150000             lea        ecx, [esi + 0x155c]
00721179  e8e20eceff               call       0x402060
0072117e  83f813                   cmp        eax, 0x13
00721181  0f8546010000             jne        0x7212cd
00721187  83becc2e0000ff           cmp        dword ptr [esi + 0x2ecc], -1
0072118e  0f8439010000             je         0x7212cd
00721194  8d8ea0000000             lea        ecx, [esi + 0xa0]
0072119a  e8615d3e00               call       0xb06f00
0072119f  3b86cc2e0000             cmp        eax, dword ptr [esi + 0x2ecc]
007211a5  0f8f22010000             jg         0x7212cd
007211ab  8b07                     mov        eax, dword ptr [edi]
007211ad  8bcf                     mov        ecx, edi
007211af  ff90b4010000             call       dword ptr [eax + 0x1b4]
007211b5  84c0                     test       al, al
007211b7  0f8410010000             je         0x7212cd
007211bd  8b17                     mov        edx, dword ptr [edi]
007211bf  56                       push       esi
007211c0  8bcf                     mov        ecx, edi
007211c2  ff921c030000             call       dword ptr [edx + 0x31c]
007211c8  8bd8                     mov        ebx, eax
007211ca  8b06                     mov        eax, dword ptr [esi]
007211cc  8bce                     mov        ecx, esi
007211ce  ff90c0000000             call       dword ptr [eax + 0xc0]
007211d4  3bd8                     cmp        ebx, eax
007211d6  0f85f1000000             jne        0x7212cd
007211dc  8b16                     mov        edx, dword ptr [esi]
007211de  6a01                     push       1
007211e0  6a01                     push       1
007211e2  33db                     xor        ebx, ebx
007211e4  53                       push       ebx
007211e5  6a02                     push       2
007211e7  8bce                     mov        ecx, esi
007211e9  ff9268070000             call       dword ptr [edx + 0x768]
007211ef  84c0                     test       al, al
007211f1  0f84d6000000             je         0x7212cd
007211f7  8b07                     mov        eax, dword ptr [edi]
007211f9  6a01                     push       1
007211fb  8bcf                     mov        ecx, edi
007211fd  ff9064010000             call       dword ptr [eax + 0x164]
00721203  895dcc                   mov        dword ptr [ebp - 0x34], ebx
00721206  895dd0                   mov        dword ptr [ebp - 0x30], ebx
00721209  895dd4                   mov        dword ptr [ebp - 0x2c], ebx
0072120c  8d4d08                   lea        ecx, [ebp + 8]
0072120f  51                       push       ecx
00721210  8d4dc8                   lea        ecx, [ebp - 0x38]
00721213  895dfc                   mov        dword ptr [ebp - 4], ebx
00721216  c7450801000000           mov        dword ptr [ebp + 8], 1
0072121d  e8fe5eceff               call       0x407120
00721222  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
00721225  8d4f28                   lea        ecx, [edi + 0x28]
00721228  e88321d1ff               call       0x4333b0
0072122d  d80dd04bcd00             fmul       dword ptr [0xcd4bd0]
00721233  8d4f10                   lea        ecx, [edi + 0x10]
00721236  d95d08                   fstp       dword ptr [ebp + 8]
00721239  e87221d1ff               call       0x4333b0
0072123e  d84508                   fadd       dword ptr [ebp + 8]
00721241  e8fe024e00               call       0xc01544
00721246  8d5508                   lea        edx, [ebp + 8]
00721249  52                       push       edx
0072124a  8d4dc8                   lea        ecx, [ebp - 0x38]
0072124d  894508                   mov        dword ptr [ebp + 8], eax
00721250  e8cb5eceff               call       0x407120
00721255  8d4508                   lea        eax, [ebp + 8]
00721258  50                       push       eax
00721259  8d4dc8                   lea        ecx, [ebp - 0x38]
0072125c  c7450801000000           mov        dword ptr [ebp + 8], 1
00721263  e8b85eceff               call       0x407120
00721268  8b16                     mov        edx, dword ptr [esi]
0072126a  8bce                     mov        ecx, esi
0072126c  ff92c0000000             call       dword ptr [edx + 0xc0]
00721272  894508                   mov        dword ptr [ebp + 8], eax
00721275  8d4508                   lea        eax, [ebp + 8]
00721278  50                       push       eax
00721279  8d4dc8                   lea        ecx, [ebp - 0x38]
0072127c  e89f5eceff               call       0x407120
00721281  8b16                     mov        edx, dword ptr [esi]
00721283  53                       push       ebx
00721284  53                       push       ebx
00721285  53                       push       ebx
00721286  8d45c8                   lea        eax, [ebp - 0x38]
00721289  50                       push       eax
0072128a  6a13                     push       0x13
0072128c  8bce                     mov        ecx, esi
0072128e  ff928c020000             call       dword ptr [edx + 0x28c]
00721294  8b16                     mov        edx, dword ptr [esi]
00721296  53                       push       ebx
00721297  6aff                     push       -1
00721299  6a09                     push       9
0072129b  8bce                     mov        ecx, esi
0072129d  ff9228060000             call       dword ptr [edx + 0x628]
007212a3  8d4dc8                   lea        ecx, [ebp - 0x38]
007212a6  c686dc2e000001           mov        byte ptr [esi + 0x2edc], 1
007212ad  899ed82e0000             mov        dword ptr [esi + 0x2ed8], ebx
007212b3  e8983af2ff               call       0x644d50
007212b8  5f                       pop        edi
007212b9  5e                       pop        esi
007212ba  33c0                     xor        eax, eax
007212bc  5b                       pop        ebx
007212bd  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
007212c0  64890d00000000           mov        dword ptr fs:[0], ecx
007212c7  8be5                     mov        esp, ebp
007212c9  5d                       pop        ebp
007212ca  c20c00                   ret        0xc
007212cd  32db                     xor        bl, bl
007212cf  8d8e5c150000             lea        ecx, [esi + 0x155c]
007212d5  885df3                   mov        byte ptr [ebp - 0xd], bl
007212d8  e8830dceff               call       0x402060
007212dd  83f813                   cmp        eax, 0x13
007212e0  0f85c1000000             jne        0x7213a7
007212e6  8b07                     mov        eax, dword ptr [edi]
007212e8  56                       push       esi
007212e9  8bcf                     mov        ecx, edi
007212eb  ff901c030000             call       dword ptr [eax + 0x31c]
007212f1  8b16                     mov        edx, dword ptr [esi]
007212f3  8bce                     mov        ecx, esi
007212f5  8bf8                     mov        edi, eax
007212f7  ff92c0000000             call       dword ptr [edx + 0xc0]
007212fd  3bf8                     cmp        edi, eax
007212ff  0f859f000000             jne        0x7213a4
00721305  8b7dec                   mov        edi, dword ptr [ebp - 0x14]
00721308  8bcf                     mov        ecx, edi
0072130a  e87161d4ff               call       0x467480
0072130f  84c0                     test       al, al
00721311  750e                     jne        0x721321
00721313  8b87ec000000             mov        eax, dword ptr [edi + 0xec]
00721319  85c0                     test       eax, eax
0072131b  0f8483000000             je         0x7213a4
00721321  8a4510                   mov        al, byte ptr [ebp + 0x10]
00721324  84c0                     test       al, al
00721326  757c                     jne        0x7213a4
00721328  83bee42e0000ff           cmp        dword ptr [esi + 0x2ee4], -1
0072132f  c686dc2e000001           mov        byte ptr [esi + 0x2edc], 1
00721336  0f84a8010000             je         0x7214e4
0072133c  8dbea0000000             lea        edi, [esi + 0xa0]
00721342  8bcf                     mov        ecx, edi
00721344  e8b75b3e00               call       0xb06f00
00721349  3b86e42e0000             cmp        eax, dword ptr [esi + 0x2ee4]
0072134f  0f8f8f010000             jg         0x7214e4
00721355  83bee02e0000ff           cmp        dword ptr [esi + 0x2ee0], -1
0072135c  7431                     je         0x72138f
0072135e  8b06                     mov        eax, dword ptr [esi]
00721360  56                       push       esi
00721361  6a04                     push       4
00721363  6a01                     push       1
00721365  8bce                     mov        ecx, esi
00721367  ff907c060000             call       dword ptr [eax + 0x67c]
0072136d  8bc8                     mov        ecx, eax
0072136f  e8ecebe2ff               call       0x54ff60
00721374  0386e02e0000             add        eax, dword ptr [esi + 0x2ee0]
0072137a  8bcf                     mov        ecx, edi
0072137c  8945e8                   mov        dword ptr [ebp - 0x18], eax
0072137f  e87c5b3e00               call       0xb06f00
00721384  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
00721387  3bc1                     cmp        eax, ecx
00721389  0f8e55010000             jle        0x7214e4
0072138f  8b86e82e0000             mov        eax, dword ptr [esi + 0x2ee8]
00721395  85c0                     test       eax, eax
00721397  0f8547010000             jne        0x7214e4
0072139d  b301                     mov        bl, 1
0072139f  e940010000               jmp        0x7214e4
007213a4  8b7d08                   mov        edi, dword ptr [ebp + 8]
007213a7  8b8ecc330000             mov        ecx, dword ptr [esi + 0x33cc]
007213ad  85c9                     test       ecx, ecx
007213af  0f8432010000             je         0x7214e7
007213b5  8b11                     mov        edx, dword ptr [ecx]
007213b7  ff5260                   call       dword ptr [edx + 0x60]
007213ba  84c0                     test       al, al
007213bc  0f8425010000             je         0x7214e7
007213c2  8d8ebc040000             lea        ecx, [esi + 0x4bc]
007213c8  e8930cceff               call       0x402060
007213cd  85c0                     test       eax, eax
007213cf  740d                     je         0x7213de
007213d1  8d8ec4040000             lea        ecx, [esi + 0x4c4]
007213d7  e8840cceff               call       0x402060
007213dc  eb07                     jmp        0x7213e5
007213de  8bce                     mov        ecx, esi
007213e0  e8fb8bd7ff               call       0x499fe0
007213e5  85c0                     test       eax, eax
007213e7  0f85fa000000             jne        0x7214e7
007213ed  8b06                     mov        eax, dword ptr [esi]
007213ef  6a03                     push       3
007213f1  8bce                     mov        ecx, esi
007213f3  ff904c060000             call       dword ptr [eax + 0x64c]
007213f9  85c0                     test       eax, eax
007213fb  0f8ee6000000             jle        0x7214e7
00721401  8b16                     mov        edx, dword ptr [esi]
00721403  6a01                     push       1
00721405  8bce                     mov        ecx, esi
00721407  ff924c060000             call       dword ptr [edx + 0x64c]
0072140d  85c0                     test       eax, eax
0072140f  0f8ed2000000             jle        0x7214e7
00721415  8b4dec                   mov        ecx, dword ptr [ebp - 0x14]
00721418  e86360d4ff               call       0x467480
0072141d  84c0                     test       al, al
0072141f  7511                     jne        0x721432
00721421  8b45ec                   mov        eax, dword ptr [ebp - 0x14]
00721424  8b88ec000000             mov        ecx, dword ptr [eax + 0xec]
0072142a  85c9                     test       ecx, ecx
0072142c  0f84b5000000             je         0x7214e7
00721432  8b16                     mov        edx, dword ptr [esi]
00721434  8bce                     mov        ecx, esi
00721436  ff929c000000             call       dword ptr [edx + 0x9c]
0072143c  85c0                     test       eax, eax
0072143e  0f85a3000000             jne        0x7214e7
00721444  8dbe5c150000             lea        edi, [esi + 0x155c]
0072144a  8bcf                     mov        ecx, edi
0072144c  e80f0cceff               call       0x402060
00721451  83f804                   cmp        eax, 4
00721454  0f848a000000             je         0x7214e4
0072145a  8bcf                     mov        ecx, edi
0072145c  e8ff0bceff               call       0x402060
00721461  83f809                   cmp        eax, 9
00721464  747e                     je         0x7214e4
00721466  8a4510                   mov        al, byte ptr [ebp + 0x10]
00721469  84c0                     test       al, al
0072146b  7577                     jne        0x7214e4
0072146d  8b06                     mov        eax, dword ptr [esi]
0072146f  6a00                     push       0
00721471  6a00                     push       0
00721473  6a0c                     push       0xc
00721475  6aff                     push       -1
00721477  6aff                     push       -1
00721479  56                       push       esi
0072147a  6a03                     push       3
0072147c  8bce                     mov        ecx, esi
0072147e  ff904c060000             call       dword ptr [eax + 0x64c]
00721484  8b16                     mov        edx, dword ptr [esi]
00721486  50                       push       eax
00721487  6a00                     push       0
00721489  6a03                     push       3
0072148b  8bce                     mov        ecx, esi
0072148d  ff927c060000             call       dword ptr [edx + 0x67c]
00721493  8bc8                     mov        ecx, eax
00721495  e8e6ebe2ff               call       0x550080
0072149a  8b0d64310001             mov        ecx, dword ptr [0x1003164]
007214a0  6810270000               push       0x2710
007214a5  689a6c4a01               push       0x14a6c9a
007214aa  8bf8                     mov        edi, eax
007214ac  e81fd31900               call       0x8be7d0
007214b1  6bff64                   imul       edi, edi, 0x64
007214b4  3bc7                     cmp        eax, edi
007214b6  7d2c                     jge        0x7214e4
007214b8  8b06                     mov        eax, dword ptr [esi]
007214ba  6a01                     push       1
007214bc  6a01                     push       1
007214be  6a00                     push       0
007214c0  6a01                     push       1
007214c2  8bce                     mov        ecx, esi
007214c4  ff9068070000             call       dword ptr [eax + 0x768]
007214ca  84c0                     test       al, al
007214cc  7416                     je         0x7214e4
007214ce  8d8ee4250000             lea        ecx, [esi + 0x25e4]
007214d4  c686dc2e000001           mov        byte ptr [esi + 0x2edc], 1
007214db  c645f301                 mov        byte ptr [ebp - 0xd], 1
007214df  e88c16d3ff               call       0x452b70
007214e4  8b7d08                   mov        edi, dword ptr [ebp + 8]
007214e7  8a86dc2e0000             mov        al, byte ptr [esi + 0x2edc]
007214ed  84c0                     test       al, al
007214ef  0f84c3010000             je         0x7216b8
007214f5  8b16                     mov        edx, dword ptr [esi]
007214f7  6a01                     push       1
007214f9  8bce                     mov        ecx, esi
007214fb  ff927c060000             call       dword ptr [edx + 0x67c]
00721501  8bf8                     mov        edi, eax
00721503  8b06                     mov        eax, dword ptr [esi]
00721505  6a01                     push       1
00721507  8bce                     mov        ecx, esi
00721509  ff904c060000             call       dword ptr [eax + 0x64c]
0072150f  8b4dec                   mov        ecx, dword ptr [ebp - 0x14]
00721512  8b4918                   mov        ecx, dword ptr [ecx + 0x18]
00721515  83f901                   cmp        ecx, 1
00721518  7524                     jne        0x72153e
0072151a  6a00                     push       0
0072151c  6a00                     push       0
0072151e  6a0c                     push       0xc