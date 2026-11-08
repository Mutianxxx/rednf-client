00884c99  8d45c4                   lea        eax, [ebp - 0x3c]
00884c9c  685cf1e100               push       0xe1f15c
00884ca1  50                       push       eax
00884ca2  e829fbb7ff               call       0x4047d0
00884ca7  83c408                   add        esp, 8
00884caa  84c0                     test       al, al
00884cac  7411                     je         0x884cbf
00884cae  8d4e70                   lea        ecx, [esi + 0x70]
00884cb1  51                       push       ecx
00884cb2  e829b8faff               call       0x8304e0
00884cb7  83c404                   add        esp, 4
00884cba  e95d0c0000               jmp        0x88591c