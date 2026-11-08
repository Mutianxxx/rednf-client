00510d70  55                       push       ebp
00510d71  8bec                     mov        ebp, esp
00510d73  56                       push       esi
00510d74  8bf1                     mov        esi, ecx
00510d76  8b06                     mov        eax, dword ptr [esi]
00510d78  85c0                     test       eax, eax
00510d7a  57                       push       edi
00510d7b  8bc8                     mov        ecx, eax
00510d7d  7503                     jne        0x510d82
00510d7f  8d4e08                   lea        ecx, [esi + 8]
00510d82  85c0                     test       eax, eax
00510d84  8b7d08                   mov        edi, dword ptr [ebp + 8]
00510d87  8b4cb91c                 mov        ecx, dword ptr [ecx + edi*4 + 0x1c]
00510d8b  894d08                   mov        dword ptr [ebp + 8], ecx
00510d8e  7503                     jne        0x510d93
00510d90  8d4608                   lea        eax, [esi + 8]
00510d93  8b10                     mov        edx, dword ptr [eax]
00510d95  57                       push       edi
00510d96  8bc8                     mov        ecx, eax
00510d98  ff5208                   call       dword ptr [edx + 8]
00510d9b  db4508                   fild       dword ptr [ebp + 8]
00510d9e  d9c0                     fld        st(0)
00510da0  d8ca                     fmul       st(2)
00510da2  dc1d60b2cc00             fcomp      qword ptr [0xccb260]
00510da8  dfe0                     fnstsw     ax
00510daa  f6c401                   test       ah, 1
00510dad  7428                     je         0x510dd7
00510daf  8b06                     mov        eax, dword ptr [esi]
00510db1  85c0                     test       eax, eax
00510db3  7404                     je         0x510db9
00510db5  8bf0                     mov        esi, eax
00510db7  eb03                     jmp        0x510dbc
00510db9  83c608                   add        esi, 8
00510dbc  d9c9                     fxch       st(1)
00510dbe  d80d2869cd00             fmul       dword ptr [0xcd6928]
00510dc4  d8f1                     fdiv       st(1)
00510dc6  e879076f00               call       0xc01544
00510dcb  ddd8                     fstp       st(0)
00510dcd  8944be28                 mov        dword ptr [esi + edi*4 + 0x28], eax
00510dd1  5f                       pop        edi
00510dd2  5e                       pop        esi
00510dd3  5d                       pop        ebp
00510dd4  c20400                   ret        4
00510dd7  ddd8                     fstp       st(0)
00510dd9  5f                       pop        edi
00510dda  ddd8                     fstp       st(0)
00510ddc  5e                       pop        esi
00510ddd  5d                       pop        ebp
00510dde  c20400                   ret        4
