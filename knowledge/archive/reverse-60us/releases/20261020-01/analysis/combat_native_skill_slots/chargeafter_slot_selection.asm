0073219d  8b1e                     mov        ebx, dword ptr [esi]
0073219f  6a11                     push       0x11
007321a1  8bce                     mov        ecx, esi
007321a3  8945d8                   mov        dword ptr [ebp - 0x28], eax
007321a6  ff938c030000             call       dword ptr [ebx + 0x38c]
007321ac  50                       push       eax
007321ad  8bce                     mov        ecx, esi
007321af  ff93f0000000             call       dword ptr [ebx + 0xf0]
007321b5  8b1e                     mov        ebx, dword ptr [esi]
007321b7  6a14                     push       0x14
007321b9  8bce                     mov        ecx, esi
007321bb  e8304fdfff               call       0x5270f0
007321c0  50                       push       eax
007321c1  8bce                     mov        ecx, esi
007321c3  ff9398010000             call       dword ptr [ebx + 0x198]
