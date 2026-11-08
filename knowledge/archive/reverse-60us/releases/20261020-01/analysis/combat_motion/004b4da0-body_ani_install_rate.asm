004b4da0  55                       push       ebp
004b4da1  8bec                     mov        ebp, esp
004b4da3  56                       push       esi
004b4da4  57                       push       edi
004b4da5  8b7d08                   mov        edi, dword ptr [ebp + 8]
004b4da8  6a13                     push       0x13
004b4daa  57                       push       edi
004b4dab  8bf1                     mov        esi, ecx
004b4dad  e8cefcffff               call       0x4b4a80
004b4db2  57                       push       edi
004b4db3  8bce                     mov        ecx, esi
004b4db5  e89664feff               call       0x49b250
004b4dba  8b8604010000             mov        eax, dword ptr [esi + 0x104]
004b4dc0  85c0                     test       eax, eax
004b4dc2  7436                     je         0x4b4dfa
004b4dc4  8d8e20160000             lea        ecx, [esi + 0x1620]
004b4dca  e891d2f4ff               call       0x402060
004b4dcf  894508                   mov        dword ptr [ebp + 8], eax
004b4dd2  db4508                   fild       dword ptr [ebp + 8]
004b4dd5  b904340001               mov        ecx, 0x1003404
004b4dda  d95d08                   fstp       dword ptr [ebp + 8]
004b4ddd  e8cee5f7ff               call       0x4333b0
004b4de2  d84d08                   fmul       dword ptr [ebp + 8]
004b4de5  51                       push       ecx
004b4de6  8b8e04010000             mov        ecx, dword ptr [esi + 0x104]
004b4dec  d80df811cc00             fmul       dword ptr [0xcc11f8]
004b4df2  d91c24                   fstp       dword ptr [esp]
004b4df5  e8764e5700               call       0xa29c70
004b4dfa  5f                       pop        edi
004b4dfb  5e                       pop        esi
004b4dfc  5d                       pop        ebp
004b4dfd  c20400                   ret        4
