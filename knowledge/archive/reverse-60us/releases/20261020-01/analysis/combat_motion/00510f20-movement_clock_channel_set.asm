00510f20  55                       push       ebp
00510f21  8bec                     mov        ebp, esp
00510f23  56                       push       esi
00510f24  57                       push       edi
00510f25  8b7d08                   mov        edi, dword ptr [ebp + 8]
00510f28  8bf1                     mov        esi, ecx
00510f2a  57                       push       edi
00510f2b  8d8ea0000000             lea        ecx, [esi + 0xa0]
00510f31  e8aa615f00               call       0xb070e0
00510f36  8b4678                   mov        eax, dword ptr [esi + 0x78]
00510f39  85c0                     test       eax, eax
00510f3b  7408                     je         0x510f45
00510f3d  8bc8                     mov        ecx, eax
00510f3f  8b01                     mov        eax, dword ptr [ecx]
00510f41  57                       push       edi
00510f42  ff5044                   call       dword ptr [eax + 0x44]
00510f45  5f                       pop        edi
00510f46  5e                       pop        esi
00510f47  5d                       pop        ebp
00510f48  c20400                   ret        4
