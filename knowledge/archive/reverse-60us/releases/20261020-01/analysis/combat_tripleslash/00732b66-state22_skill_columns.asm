00732b66  83be202f000003           cmp        dword ptr [esi + 0x2f20], 3
00732b6d  7523                     jne        0x732b92
00732b6f  8b861c2f0000             mov        eax, dword ptr [esi + 0x2f1c]
00732b75  83f803                   cmp        eax, 3
00732b78  7d18                     jge        0x732b92
00732b7a  33c9                     xor        ecx, ecx
00732b7c  894dbc                   mov        dword ptr [ebp - 0x44], ecx
00732b7f  894dc0                   mov        dword ptr [ebp - 0x40], ecx
00732b82  c745c401000000           mov        dword ptr [ebp - 0x3c], 1
00732b89  8b5485bc                 mov        edx, dword ptr [ebp + eax*4 - 0x44]
00732b8d  8955e8                   mov        dword ptr [ebp - 0x18], edx
00732b90  eb26                     jmp        0x732bb8
00732b92  33c0                     xor        eax, eax
00732b94  8945b4                   mov        dword ptr [ebp - 0x4c], eax
00732b97  8945b8                   mov        dword ptr [ebp - 0x48], eax
00732b9a  8945bc                   mov        dword ptr [ebp - 0x44], eax
00732b9d  8b861c2f0000             mov        eax, dword ptr [esi + 0x2f1c]
00732ba3  c745c001000000           mov        dword ptr [ebp - 0x40], 1
00732baa  c745c402000000           mov        dword ptr [ebp - 0x3c], 2
00732bb1  8b4c85b4                 mov        ecx, dword ptr [ebp + eax*4 - 0x4c]
00732bb5  894de8                   mov        dword ptr [ebp - 0x18], ecx
00732bb8  8b16                     mov        edx, dword ptr [esi]
00732bba  6a0c                     push       0xc
00732bbc  8bce                     mov        ecx, esi
00732bbe  ff92d0010000             call       dword ptr [edx + 0x1d0]
00732bc4  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
00732bc7  50                       push       eax
00732bc8  8b45dc                   mov        eax, dword ptr [ebp - 0x24]
00732bcb  56                       push       esi
00732bcc  50                       push       eax
00732bcd  51                       push       ecx
00732bce  8bcb                     mov        ecx, ebx
00732bd0  e84b7ed9ff               call       0x4caa20
00732bd5  8d55f0                   lea        edx, [ebp - 0x10]
00732bd8  83e864                   sub        eax, 0x64
00732bdb  8dbe70020000             lea        edi, [esi + 0x270]
00732be1  52                       push       edx
00732be2  8bcf                     mov        ecx, edi
00732be4  8945f0                   mov        dword ptr [ebp - 0x10], eax
00732be7  e87419cdff               call       0x404560
00732bec  8b06                     mov        eax, dword ptr [esi]
00732bee  6a00                     push       0
00732bf0  8bce                     mov        ecx, esi
00732bf2  ff90d0010000             call       dword ptr [eax + 0x1d0]
00732bf8  8b4ddc                   mov        ecx, dword ptr [ebp - 0x24]
00732bfb  8b55e8                   mov        edx, dword ptr [ebp - 0x18]
00732bfe  50                       push       eax
00732bff  56                       push       esi
00732c00  51                       push       ecx
00732c01  83c203                   add        edx, 3
00732c04  52                       push       edx
00732c05  8bcb                     mov        ecx, ebx
00732c07  e8147ed9ff               call       0x4caa20
00732c0c  6bc064                   imul       eax, eax, 0x64
00732c0f  8bcf                     mov        ecx, edi
00732c11  8945f0                   mov        dword ptr [ebp - 0x10], eax
00732c14  e847f4ccff               call       0x402060
00732c19  8bc8                     mov        ecx, eax
00732c1b  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
00732c1e  83c164                   add        ecx, 0x64
00732c21  99                       cdq        
00732c22  f7f9                     idiv       ecx
00732c24  8d55f0                   lea        edx, [ebp - 0x10]
00732c27  52                       push       edx
00732c28  8d8e60020000             lea        ecx, [esi + 0x260]
00732c2e  8945f0                   mov        dword ptr [ebp - 0x10], eax
00732c31  db45f0                   fild       dword ptr [ebp - 0x10]
00732c34  d95df0                   fstp       dword ptr [ebp - 0x10]
00732c37  e82419cdff               call       0x404560
00732c3c  83be202f000005           cmp        dword ptr [esi + 0x2f20], 5
00732c43  751e                     jne        0x732c63
00732c45  83be1c2f000004           cmp        dword ptr [esi + 0x2f1c], 4
00732c4c  7515                     jne        0x732c63
00732c4e  8b45d8                   mov        eax, dword ptr [ebp - 0x28]
00732c51  8d4df0                   lea        ecx, [ebp - 0x10]
00732c54  51                       push       ecx
00732c55  8d8e58030000             lea        ecx, [esi + 0x358]
00732c5b  8945f0                   mov        dword ptr [ebp - 0x10], eax
00732c5e  e8fd18cdff               call       0x404560
