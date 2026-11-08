00b06f00  56                       push       esi
00b06f01  8bf1                     mov        esi, ecx
00b06f03  8d4e10                   lea        ecx, [esi + 0x10]
00b06f06  e855b18fff               call       0x402060
00b06f0b  85c0                     test       eax, eax
00b06f0d  7442                     je         0xb06f51
00b06f0f  8d4e18                   lea        ecx, [esi + 0x18]
00b06f12  e849b18fff               call       0x402060
00b06f17  85c0                     test       eax, eax
00b06f19  7436                     je         0xb06f51
00b06f1b  8d4e20                   lea        ecx, [esi + 0x20]
00b06f1e  e83db18fff               call       0x402060
00b06f23  85c0                     test       eax, eax
00b06f25  7409                     je         0xb06f30
00b06f27  8d4e30                   lea        ecx, [esi + 0x30]
00b06f2a  5e                       pop        esi
00b06f2b  e930b18fff               jmp        0x402060
00b06f30  57                       push       edi
00b06f31  8d4e08                   lea        ecx, [esi + 8]
00b06f34  e827b18fff               call       0x402060
00b06f39  50                       push       eax
00b06f3a  e841bb0000               call       0xb12a80
00b06f3f  83c404                   add        esp, 4
00b06f42  8d4e28                   lea        ecx, [esi + 0x28]
00b06f45  8bf8                     mov        edi, eax
00b06f47  e814b18fff               call       0x402060
00b06f4c  03c7                     add        eax, edi
00b06f4e  5f                       pop        edi
00b06f4f  5e                       pop        esi
00b06f50  c3                       ret        
00b06f51  33c0                     xor        eax, eax
00b06f53  5e                       pop        esi
00b06f54  c3                       ret        
