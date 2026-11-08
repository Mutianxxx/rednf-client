00836dcb  68a4a4cd00               push       0xcda4a4
00836dd0  e8f88f3c00               call       0xbffdcd
00836dd5  8b55cc                   mov        edx, dword ptr [ebp - 0x34]
00836dd8  83c404                   add        esp, 4
00836ddb  50                       push       eax
00836ddc  68a4a4cd00               push       0xcda4a4
00836de1  52                       push       edx
00836de2  56                       push       esi
00836de3  8d4db8                   lea        ecx, [ebp - 0x48]
00836de6  e805d2bcff               call       0x403ff0
00836deb  85c0                     test       eax, eax
00836ded  7568                     jne        0x836e57
00836def  8d45d4                   lea        eax, [ebp - 0x2c]
00836df2  50                       push       eax
00836df3  e81899ffff               call       0x830710
00836df8  8d4dd4                   lea        ecx, [ebp - 0x2c]
00836dfb  68144ce100               push       0xe14c14
00836e00  51                       push       ecx
00836e01  e8cad9bcff               call       0x4047d0
00836e06  83c40c                   add        esp, 0xc
00836e09  84c0                     test       al, al
00836e0b  7408                     je         0x836e15
00836e0d  897718                   mov        dword ptr [edi + 0x18], esi
00836e10  e9ed0f0000               jmp        0x837e02
00836e15  8d55d4                   lea        edx, [ebp - 0x2c]
00836e18  68044ce100               push       0xe14c04
00836e1d  52                       push       edx
00836e1e  e8add9bcff               call       0x4047d0
00836e23  83c408                   add        esp, 8
00836e26  84c0                     test       al, al
00836e28  740c                     je         0x836e36
00836e2a  c7471801000000           mov        dword ptr [edi + 0x18], 1
00836e31  e9cc0f0000               jmp        0x837e02
00836e36  8d45d4                   lea        eax, [ebp - 0x2c]
00836e39  68e04be100               push       0xe14be0
00836e3e  50                       push       eax
00836e3f  e88cd9bcff               call       0x4047d0
00836e44  83c408                   add        esp, 8
00836e47  84c0                     test       al, al
00836e49  0f84b30f0000             je         0x837e02
00836e4f  895f18                   mov        dword ptr [edi + 0x18], ebx
00836e52  e9ab0f0000               jmp        0x837e02
