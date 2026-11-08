00a277c0  55                       push       ebp
00a277c1  8bec                     mov        ebp, esp
00a277c3  56                       push       esi
00a277c4  8bf1                     mov        esi, ecx
00a277c6  8b8e80010000             mov        ecx, dword ptr [esi + 0x180]
00a277cc  8b01                     mov        eax, dword ptr [ecx]
00a277ce  3bc1                     cmp        eax, ecx
00a277d0  7451                     je         0xa27823
00a277d2  8b5508                   mov        edx, dword ptr [ebp + 8]
00a277d5  39500c                   cmp        dword ptr [eax + 0xc], edx
00a277d8  740b                     je         0xa277e5
00a277da  8b00                     mov        eax, dword ptr [eax]
00a277dc  3bc1                     cmp        eax, ecx
00a277de  75f5                     jne        0xa277d5
00a277e0  5e                       pop        esi
00a277e1  5d                       pop        ebp
00a277e2  c20400                   ret        4
00a277e5  8b480c                   mov        ecx, dword ptr [eax + 0xc]
00a277e8  85c9                     test       ecx, ecx
00a277ea  740a                     je         0xa277f6
00a277ec  c7818801000000000000     mov        dword ptr [ecx + 0x188], 0
00a277f6  3b8680010000             cmp        eax, dword ptr [esi + 0x180]
00a277fc  7425                     je         0xa27823
00a277fe  8b4804                   mov        ecx, dword ptr [eax + 4]
00a27801  8b10                     mov        edx, dword ptr [eax]
00a27803  8911                     mov        dword ptr [ecx], edx
00a27805  8b08                     mov        ecx, dword ptr [eax]
00a27807  8b5004                   mov        edx, dword ptr [eax + 4]
00a2780a  50                       push       eax
00a2780b  895104                   mov        dword ptr [ecx + 4], edx
00a2780e  e8ca871d00               call       0xbfffdd
00a27813  8b8684010000             mov        eax, dword ptr [esi + 0x184]
00a27819  83c404                   add        esp, 4
00a2781c  48                       dec        eax
00a2781d  898684010000             mov        dword ptr [esi + 0x184], eax
00a27823  5e                       pop        esi
00a27824  5d                       pop        ebp
00a27825  c2                       .byte      0xc2
00a27826  04                       .byte      0x04
