00a60940  55                       push       ebp
00a60941  8bec                     mov        ebp, esp
00a60943  81ec00040000             sub        esp, 0x400
00a60949  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00a6094c  56                       push       esi
00a6094d  50                       push       eax
00a6094e  8bf1                     mov        esi, ecx
00a60950  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00a60953  51                       push       ecx
00a60954  68f8b8ca00               push       0xcab8f8
00a60959  8d9500fcffff             lea        edx, [ebp - 0x400]
00a6095f  6800020000               push       0x200
00a60964  52                       push       edx
00a60965  e806010000               call       0xa60a70
00a6096a  8b4518                   mov        eax, dword ptr [ebp + 0x18]
00a6096d  8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
00a60970  8b5510                   mov        edx, dword ptr [ebp + 0x10]
00a60973  83c414                   add        esp, 0x14
00a60976  50                       push       eax
00a60977  51                       push       ecx
00a60978  52                       push       edx
00a60979  8d8500fcffff             lea        eax, [ebp - 0x400]
00a6097f  50                       push       eax
00a60980  8bce                     mov        ecx, esi
00a60982  e889feffff               call       0xa60810
00a60987  5e                       pop        esi
00a60988  8be5                     mov        esp, ebp
00a6098a  5d                       pop        ebp
00a6098b  c2                       .byte      0xc2
