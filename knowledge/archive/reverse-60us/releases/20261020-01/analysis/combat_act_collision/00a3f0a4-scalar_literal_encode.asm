00a3f0a4 8d4508                   lea        eax, [ebp + 8]
00a3f0a7 50                       push       eax
00a3f0a8 8bce                     mov        ecx, esi
00a3f0aa 895d08                   mov        dword ptr [ebp + 8], ebx
00a3f0ad e87e800000               call       0xa47130
00a3f0b2 8d4dec                   lea        ecx, [ebp - 0x14]
00a3f0b5 51                       push       ecx
00a3f0b6 8bce                     mov        ecx, esi
00a3f0b8 e873800000               call       0xa47130
