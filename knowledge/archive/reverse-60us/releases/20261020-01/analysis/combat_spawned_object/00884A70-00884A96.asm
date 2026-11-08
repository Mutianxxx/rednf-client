00884a70  8d55c4                   lea        edx, [ebp - 0x3c]
00884a73  682035e200               push       0xe23520
00884a78  52                       push       edx
00884a79  e852fdb7ff               call       0x4047d0
00884a7e  83c408                   add        esp, 8
00884a81  84c0                     test       al, al
00884a83  7411                     je         0x884a96
00884a85  8d4634                   lea        eax, [esi + 0x34]
00884a88  50                       push       eax
00884a89  e852bafaff               call       0x8304e0
00884a8e  83c404                   add        esp, 4
00884a91  e9860e0000               jmp        0x88591c