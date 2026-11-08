00a24bb0  55                       push       ebp
00a24bb1  8bec                     mov        ebp, esp
00a24bb3  51                       push       ecx
00a24bb4  8b8198000000             mov        eax, dword ptr [ecx + 0x98]
00a24bba  53                       push       ebx
00a24bbb  56                       push       esi
00a24bbc  57                       push       edi
00a24bbd  33ff                     xor        edi, edi
00a24bbf  85c0                     test       eax, eax
00a24bc1  897dfc                   mov        dword ptr [ebp - 4], edi
00a24bc4  741b                     je         0xa24be1
00a24bc6  8bb19c000000             mov        esi, dword ptr [ecx + 0x9c]
00a24bcc  2bf0                     sub        esi, eax
00a24bce  b843082184               mov        eax, 0x84210843
00a24bd3  f7ee                     imul       esi
00a24bd5  03d6                     add        edx, esi
00a24bd7  c1fa06                   sar        edx, 6
00a24bda  8bc2                     mov        eax, edx
00a24bdc  c1e81f                   shr        eax, 0x1f
00a24bdf  03c2                     add        eax, edx
00a24be1  8a5508                   mov        dl, byte ptr [ebp + 8]
00a24be4  84d2                     test       dl, dl
00a24be6  746c                     je         0xa24c54
00a24be8  8b9124010000             mov        edx, dword ptr [ecx + 0x124]
00a24bee  3bd0                     cmp        edx, eax
00a24bf0  0f8db3000000             jge        0xa24ca9
00a24bf6  d905581fcc00             fld        dword ptr [0xcc1f58]
00a24bfc  8b1df83e0d01             mov        ebx, dword ptr [0x10d3ef8]
00a24c02  d8b134010000             fdiv       dword ptr [ecx + 0x134]
00a24c08  8b8998000000             mov        ecx, dword ptr [ecx + 0x98]
00a24c0e  8bf2                     mov        esi, edx
00a24c10  6bf67c                   imul       esi, esi, 0x7c
00a24c13  2bc2                     sub        eax, edx
00a24c15  8d740e30                 lea        esi, [esi + ecx + 0x30]
00a24c19  8bf8                     mov        edi, eax
00a24c1b  eb03                     jmp        0xa24c20
00a24c1d  8d4900                   lea        ecx, [ecx]
00a24c20  8b16                     mov        edx, dword ptr [esi]
00a24c22  2bd6                     sub        edx, esi
00a24c24  33d3                     xor        edx, ebx
00a24c26  895508                   mov        dword ptr [ebp + 8], edx
00a24c29  db4508                   fild       dword ptr [ebp + 8]
00a24c2c  d8c9                     fmul       st(1)
00a24c2e  d80dd8b9cc00             fmul       dword ptr [0xccb9d8]
00a24c34  e80bc91d00               call       0xc01544
00a24c39  8b55fc                   mov        edx, dword ptr [ebp - 4]
00a24c3c  03d0                     add        edx, eax
00a24c3e  83c67c                   add        esi, 0x7c
00a24c41  4f                       dec        edi
00a24c42  8955fc                   mov        dword ptr [ebp - 4], edx
00a24c45  75d9                     jne        0xa24c20
00a24c47  5f                       pop        edi
00a24c48  ddd8                     fstp       st(0)
00a24c4a  5e                       pop        esi
00a24c4b  8bc2                     mov        eax, edx
00a24c4d  5b                       pop        ebx
00a24c4e  8be5                     mov        esp, ebp
00a24c50  5d                       pop        ebp
00a24c51  c20400                   ret        4
00a24c54  8bb990000000             mov        edi, dword ptr [ecx + 0x90]
00a24c5a  85ff                     test       edi, edi
00a24c5c  897dfc                   mov        dword ptr [ebp - 4], edi
00a24c5f  7553                     jne        0xa24cb4
00a24c61  85c0                     test       eax, eax
00a24c63  7e44                     jle        0xa24ca9
00a24c65  d905581fcc00             fld        dword ptr [0xcc1f58]
00a24c6b  8bb198000000             mov        esi, dword ptr [ecx + 0x98]
00a24c71  d8b134010000             fdiv       dword ptr [ecx + 0x134]
00a24c77  83c630                   add        esi, 0x30
00a24c7a  8bd8                     mov        ebx, eax
00a24c7c  8d642400                 lea        esp, [esp]
00a24c80  8b06                     mov        eax, dword ptr [esi]
00a24c82  8b0df83e0d01             mov        ecx, dword ptr [0x10d3ef8]
00a24c88  2bc6                     sub        eax, esi
00a24c8a  33c1                     xor        eax, ecx
00a24c8c  894508                   mov        dword ptr [ebp + 8], eax
00a24c8f  db4508                   fild       dword ptr [ebp + 8]
00a24c92  d8c9                     fmul       st(1)
00a24c94  d80dd8b9cc00             fmul       dword ptr [0xccb9d8]
00a24c9a  e8a5c81d00               call       0xc01544
00a24c9f  03f8                     add        edi, eax
00a24ca1  83c67c                   add        esi, 0x7c
00a24ca4  4b                       dec        ebx
00a24ca5  75d9                     jne        0xa24c80
00a24ca7  ddd8                     fstp       st(0)
00a24ca9  8bc7                     mov        eax, edi
00a24cab  5f                       pop        edi
00a24cac  5e                       pop        esi
00a24cad  5b                       pop        ebx
00a24cae  8be5                     mov        esp, ebp
00a24cb0  5d                       pop        ebp
00a24cb1  c20400                   ret        4
00a24cb4  db45fc                   fild       dword ptr [ebp - 4]
