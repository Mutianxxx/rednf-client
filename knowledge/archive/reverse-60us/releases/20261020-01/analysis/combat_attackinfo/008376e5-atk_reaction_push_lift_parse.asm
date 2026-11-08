008376e5  8d45b8                   lea        eax, [ebp - 0x48]
008376e8  68c849e100               push       0xe149c8
008376ed  50                       push       eax
008376ee  e8ddd0bcff               call       0x4047d0
008376f3  83c408                   add        esp, 8
008376f6  84c0                     test       al, al
008376f8  0f8495000000             je         0x837793
008376fe  8d4dd4                   lea        ecx, [ebp - 0x2c]
00837701  51                       push       ecx
00837702  e80990ffff               call       0x830710
00837707  8d55d4                   lea        edx, [ebp - 0x2c]
0083770a  68743dcc00               push       0xcc3d74
0083770f  52                       push       edx
00837710  e8bbd0bcff               call       0x4047d0
00837715  83c40c                   add        esp, 0xc
00837718  84c0                     test       al, al
0083771a  740b                     je         0x837727
0083771c  89b7ec000000             mov        dword ptr [edi + 0xec], esi
00837722  e9db060000               jmp        0x837e02
00837727  8d45d4                   lea        eax, [ebp - 0x2c]
0083772a  68b43ee100               push       0xe13eb4
0083772f  50                       push       eax
00837730  e89bd0bcff               call       0x4047d0
00837735  83c408                   add        esp, 8
00837738  84c0                     test       al, al
0083773a  740f                     je         0x83774b
0083773c  c787ec00000001000000     mov        dword ptr [edi + 0xec], 1
00837746  e9b7060000               jmp        0x837e02
0083774b  8d4dd4                   lea        ecx, [ebp - 0x2c]
0083774e  68a43ee100               push       0xe13ea4
00837753  51                       push       ecx
00837754  e877d0bcff               call       0x4047d0
00837759  83c408                   add        esp, 8
0083775c  84c0                     test       al, al
0083775e  740b                     je         0x83776b
00837760  899fec000000             mov        dword ptr [edi + 0xec], ebx
00837766  e997060000               jmp        0x837e02
0083776b  8d55d4                   lea        edx, [ebp - 0x2c]
0083776e  689c49e100               push       0xe1499c
00837773  52                       push       edx
00837774  e857d0bcff               call       0x4047d0
00837779  83c408                   add        esp, 8
0083777c  84c0                     test       al, al
0083777e  0f847e060000             je         0x837e02
00837784  c787ec00000003000000     mov        dword ptr [edi + 0xec], 3
0083778e  e96f060000               jmp        0x837e02
00837793  8d45b8                   lea        eax, [ebp - 0x48]
00837796  688049e100               push       0xe14980
0083779b  50                       push       eax
0083779c  e82fd0bcff               call       0x4047d0
008377a1  83c408                   add        esp, 8
008377a4  84c0                     test       al, al
008377a6  7420                     je         0x8377c8
008377a8  56                       push       esi
008377a9  e82280ffff               call       0x82f7d0
008377ae  83c404                   add        esp, 4
008377b1  8d4df0                   lea        ecx, [ebp - 0x10]
008377b4  51                       push       ecx
008377b5  8d8ff0000000             lea        ecx, [edi + 0xf0]
008377bb  8945f0                   mov        dword ptr [ebp - 0x10], eax
008377be  e89dcdbcff               call       0x404560
008377c3  e93a060000               jmp        0x837e02
008377c8  8d55b8                   lea        edx, [ebp - 0x48]
008377cb  686c49e100               push       0xe1496c
008377d0  52                       push       edx
008377d1  e8facfbcff               call       0x4047d0
008377d6  83c408                   add        esp, 8
008377d9  84c0                     test       al, al
008377db  7420                     je         0x8377fd
008377dd  56                       push       esi
008377de  e8ed7fffff               call       0x82f7d0
008377e3  8945f0                   mov        dword ptr [ebp - 0x10], eax
008377e6  83c404                   add        esp, 4
008377e9  8d45f0                   lea        eax, [ebp - 0x10]
008377ec  50                       push       eax
008377ed  8d8ff8000000             lea        ecx, [edi + 0xf8]
008377f3  e868cdbcff               call       0x404560
008377f8  e905060000               jmp        0x837e02
