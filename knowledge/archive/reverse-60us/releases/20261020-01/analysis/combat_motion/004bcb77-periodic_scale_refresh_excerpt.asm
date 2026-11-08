004bcb77  8d4e60                   lea        ecx, [esi + 0x60]
004bcb7a  e881a36400               call       0xb06f00
004bcb7f  50                       push       eax
004bcb80  8d8e44160000             lea        ecx, [esi + 0x1644]
004bcb86  e825545900               call       0xa51fb0
004bcb8b  84c0                     test       al, al
004bcb8d  0f849a000000             je         0x4bcc2d
004bcb93  8bbe10160000             mov        edi, dword ptr [esi + 0x1610]
004bcb99  85ff                     test       edi, edi
004bcb9b  7443                     je         0x4bcbe0
004bcb9d  8d8e28160000             lea        ecx, [esi + 0x1628]
004bcba3  e80868f7ff               call       0x4333b0
004bcba8  d95dec                   fstp       dword ptr [ebp - 0x14]
004bcbab  8b16                     mov        edx, dword ptr [esi]
004bcbad  57                       push       edi
004bcbae  8bce                     mov        ecx, esi
004bcbb0  ff9284050000             call       dword ptr [edx + 0x584]
004bcbb6  8945f0                   mov        dword ptr [ebp - 0x10], eax
004bcbb9  db45f0                   fild       dword ptr [ebp - 0x10]
004bcbbc  d84dec                   fmul       dword ptr [ebp - 0x14]
004bcbbf  e880497400               call       0xc01544
004bcbc4  8d8e18160000             lea        ecx, [esi + 0x1618]
004bcbca  8bf8                     mov        edi, eax
004bcbcc  e88f54f4ff               call       0x402060
004bcbd1  3bf8                     cmp        edi, eax
004bcbd3  740b                     je         0x4bcbe0
004bcbd5  8b06                     mov        eax, dword ptr [esi]
004bcbd7  57                       push       edi
004bcbd8  8bce                     mov        ecx, esi
004bcbda  ff9088050000             call       dword ptr [eax + 0x588]
004bcbe0  8bbe14160000             mov        edi, dword ptr [esi + 0x1614]
004bcbe6  85ff                     test       edi, edi
004bcbe8  7443                     je         0x4bcc2d
004bcbea  8d8e30160000             lea        ecx, [esi + 0x1630]
004bcbf0  e8bb67f7ff               call       0x4333b0
004bcbf5  d95df0                   fstp       dword ptr [ebp - 0x10]
004bcbf8  8b16                     mov        edx, dword ptr [esi]
004bcbfa  57                       push       edi
004bcbfb  8bce                     mov        ecx, esi
004bcbfd  ff9284050000             call       dword ptr [edx + 0x584]
004bcc03  8945ec                   mov        dword ptr [ebp - 0x14], eax
004bcc06  db45ec                   fild       dword ptr [ebp - 0x14]
004bcc09  d84df0                   fmul       dword ptr [ebp - 0x10]
004bcc0c  e833497400               call       0xc01544
004bcc11  8d8e20160000             lea        ecx, [esi + 0x1620]
004bcc17  8bf8                     mov        edi, eax
004bcc19  e84254f4ff               call       0x402060
004bcc1e  3bf8                     cmp        edi, eax
004bcc20  740b                     je         0x4bcc2d
004bcc22  8b06                     mov        eax, dword ptr [esi]
004bcc24  57                       push       edi
004bcc25  8bce                     mov        ecx, esi
004bcc27  ff908c050000             call       dword ptr [eax + 0x58c]
004bcc2d  8b                       .byte      0x8b
