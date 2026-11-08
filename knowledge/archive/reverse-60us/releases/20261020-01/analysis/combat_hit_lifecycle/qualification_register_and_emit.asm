004ee130 8b06                     mov        eax, dword ptr [esi]
004ee132 57                       push       edi
004ee133 8bce                     mov        ecx, esi
004ee135 ff90a4010000             call       dword ptr [eax + 0x1a4]
004ee13b 6a01                     push       1
004ee13d 6a00                     push       0
004ee13f 8d4dbc                   lea        ecx, [ebp - 0x44]
004ee142 51                       push       ecx
004ee143 57                       push       edi
004ee144 56                       push       esi
004ee145 e8a6caffff               call       0x4eabf0
004ee14a 8a5df3                   mov        bl, byte ptr [ebp - 0xd]
004ee14d 83c414                   add        esp, 0x14
