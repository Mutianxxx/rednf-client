004bd06a 8d8ec0160000             lea        ecx, [esi + 0x16c0]
004bd070 e8eb4ff4ff               call       0x402060
004bd075 8d8e64150000             lea        ecx, [esi + 0x1564]
004bd07b 8bf8                     mov        edi, eax
004bd07d e87e9e6400               call       0xb06f00
004bd082 3bc7                     cmp        eax, edi
004bd084 0f8c76090000             jl         0x4bda00
004bd08a 8b06                     mov        eax, dword ptr [esi]
004bd08c 6a03                     push       3
004bd08e 8bce                     mov        ecx, esi
004bd090 ff9010040000             call       dword ptr [eax + 0x410]
004bd096 84c0                     test       al, al
004bd098 6a00                     push       0
004bd09a 8bce                     mov        ecx, esi
004bd09c 6a00                     push       0
004bd09e 0f844e090000             je         0x4bd9f2
004bd0a4 8b16                     mov        edx, dword ptr [esi]
004bd0a6 6a03                     push       3
004bd0a8 6a00                     push       0
004bd0aa 6a09                     push       9
004bd0ac ff928c020000             call       dword ptr [edx + 0x28c]
004bd0b2 e949090000               jmp        0x4bda00
