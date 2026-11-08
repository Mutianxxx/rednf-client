004c5780  8ea02a000052             mov        fs, word ptr [eax + 0x5200002a]
004c5786  57                       push       edi
004c5787  e8a4e00600               call       0x533830
004c578c  8b4514                   mov        eax, dword ptr [ebp + 0x14]
004c578f  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
004c5792  8b550c                   mov        edx, dword ptr [ebp + 0xc]
004c5795  50                       push       eax
004c5796  51                       push       ecx
004c5797  52                       push       edx
004c5798  57                       push       edi
004c5799  8bce                     mov        ecx, esi
004c579b  e8d08b0100               call       0x4de370
004c57a0  8b06                     mov        eax, dword ptr [esi]
004c57a2  8bce                     mov        ecx, esi
004c57a4  ff                       .byte      0xff
004c57a5  50                       push       eax
