00a29c70  55                       push       ebp
00a29c71  8bec                     mov        ebp, esp
00a29c73  83ec0c                   sub        esp, 0xc
00a29c76  d94508                   fld        dword ptr [ebp + 8]
00a29c79  57                       push       edi
00a29c7a  d9e1                     fabs       
00a29c7c  8bf9                     mov        edi, ecx
00a29c7e  d94508                   fld        dword ptr [ebp + 8]
00a29c81  d9e1                     fabs       
00a29c83  dc0de8b8ca00             fmul       qword ptr [0xcab8e8]
00a29c89  ded9                     fcompp     
00a29c8b  dfe0                     fnstsw     ax
00a29c8d  f6c401                   test       ah, 1
00a29c90  7507                     jne        0xa29c99
00a29c92  c745080000803f           mov        dword ptr [ebp + 8], 0x3f800000
00a29c99  d94508                   fld        dword ptr [ebp + 8]
00a29c9c  d8a734010000             fsub       dword ptr [edi + 0x134]
00a29ca2  d9e1                     fabs       
00a29ca4  d94508                   fld        dword ptr [ebp + 8]
00a29ca7  d9e1                     fabs       
00a29ca9  dc0de8b8ca00             fmul       qword ptr [0xcab8e8]
00a29caf  ded9                     fcompp     
00a29cb1  dfe0                     fnstsw     ax
00a29cb3  f6c401                   test       ah, 1
00a29cb6  0f84a4000000             je         0xa29d60
00a29cbc  8b8734010000             mov        eax, dword ptr [edi + 0x134]
00a29cc2  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00a29cc5  8945f8                   mov        dword ptr [ebp - 8], eax
00a29cc8  8b8788010000             mov        eax, dword ptr [edi + 0x188]
00a29cce  85c0                     test       eax, eax
00a29cd0  898f34010000             mov        dword ptr [edi + 0x134], ecx
00a29cd6  8bcf                     mov        ecx, edi
00a29cd8  753f                     jne        0xa29d19
00a29cda  8b978c000000             mov        edx, dword ptr [edi + 0x8c]
00a29ce0  8a8739010000             mov        al, byte ptr [edi + 0x139]
00a29ce6  8955fc                   mov        dword ptr [ebp - 4], edx
00a29ce9  8845f4                   mov        byte ptr [ebp - 0xc], al
00a29cec  e86fd6ffff               call       0xa27360
00a29cf1  db45fc                   fild       dword ptr [ebp - 4]
00a29cf4  d87508                   fdiv       dword ptr [ebp + 8]
00a29cf7  d84df8                   fmul       dword ptr [ebp - 8]
00a29cfa  e845781d00               call       0xc01544
00a29cff  8bcf                     mov        ecx, edi
00a29d01  898788000000             mov        dword ptr [edi + 0x88], eax
00a29d07  e8849fffff               call       0xa23c90
00a29d0c  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a29d0f  51                       push       ecx
00a29d10  8bcf                     mov        ecx, edi
00a29d12  e8f9e3ffff               call       0xa28110
00a29d17  eb05                     jmp        0xa29d1e
00a29d19  e812bda2ff               call       0x455a30
00a29d1e  8b8784010000             mov        eax, dword ptr [edi + 0x184]
00a29d24  85c0                     test       eax, eax
00a29d26  7431                     je         0xa29d59
00a29d28  8b8780010000             mov        eax, dword ptr [edi + 0x180]
00a29d2e  56                       push       esi
00a29d2f  8b30                     mov        esi, dword ptr [eax]
00a29d31  3bf0                     cmp        esi, eax
00a29d33  7423                     je         0xa29d58
00a29d35  53                       push       ebx
00a29d36  8b5d08                   mov        ebx, dword ptr [ebp + 8]
00a29d39  8da42400000000           lea        esp, [esp]
00a29d40  8b4e0c                   mov        ecx, dword ptr [esi + 0xc]
00a29d43  85c9                     test       ecx, ecx
00a29d45  7406                     je         0xa29d4d
00a29d47  53                       push       ebx
00a29d48  e823ffffff               call       0xa29c70
00a29d4d  8b36                     mov        esi, dword ptr [esi]
00a29d4f  3bb780010000             cmp        esi, dword ptr [edi + 0x180]
00a29d55  75e9                     jne        0xa29d40
00a29d57  5b                       pop        ebx
00a29d58  5e                       pop        esi
00a29d59  8bcf                     mov        ecx, edi
00a29d5b  e800e2ffff               call       0xa27f60
00a29d60  5f                       pop        edi
00a29d61  8be5                     mov        esp, ebp
00a29d63  5d                       pop        ebp
00a29d64  c2                       .byte      0xc2
