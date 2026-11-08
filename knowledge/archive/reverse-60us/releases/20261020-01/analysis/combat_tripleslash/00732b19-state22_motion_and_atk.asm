00732b19  8b861c2f0000             mov        eax, dword ptr [esi + 0x2f1c]
00732b1f  83c003                   add        eax, 3
00732b22  50                       push       eax
00732b23  8bce                     mov        ecx, esi
00732b25  ff978c030000             call       dword ptr [edi + 0x38c]
00732b2b  50                       push       eax
00732b2c  8bce                     mov        ecx, esi
00732b2e  ff97f0000000             call       dword ptr [edi + 0xf0]
00732b34  83be202f000003           cmp        dword ptr [esi + 0x2f20], 3
00732b3b  750d                     jne        0x732b4a
00732b3d  83be1c2f000002           cmp        dword ptr [esi + 0x2f1c], 2
00732b44  7504                     jne        0x732b4a
00732b46  6a07                     push       7
00732b48  eb0a                     jmp        0x732b54
00732b4a  8b8e1c2f0000             mov        ecx, dword ptr [esi + 0x2f1c]
00732b50  83c102                   add        ecx, 2
00732b53  51                       push       ecx
00732b54  8b3e                     mov        edi, dword ptr [esi]
00732b56  8bce                     mov        ecx, esi
00732b58  e89345dfff               call       0x5270f0
00732b5d  8bce                     mov        ecx, esi
00732b5f  50                       push       eax
00732b60  ff9798010000             call       dword ptr [edi + 0x198]
