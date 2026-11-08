00836e57  8d4db8                   lea        ecx, [ebp - 0x48]
00836e5a  68b44be100               push       0xe14bb4
00836e5f  51                       push       ecx
00836e60  e86bd9bcff               call       0x4047d0
00836e65  83c408                   add        esp, 8
00836e68  84c0                     test       al, al
00836e6a  7425                     je         0x836e91
00836e6c  56                       push       esi
00836e6d  e85e89ffff               call       0x82f7d0
00836e72  83c404                   add        esp, 4
00836e75  85c0                     test       eax, eax
00836e77  0f95c2                   setne      dl
00836e7a  0fb6c2                   movzx      eax, dl
00836e7d  8d4df0                   lea        ecx, [ebp - 0x10]
00836e80  51                       push       ecx
00836e81  8d4f1c                   lea        ecx, [edi + 0x1c]
00836e84  8945f0                   mov        dword ptr [ebp - 0x10], eax
00836e87  e8d4d6bcff               call       0x404560
00836e8c  e9710f0000               jmp        0x837e02
