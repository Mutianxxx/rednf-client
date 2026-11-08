0073b42c  8b8628240000             mov        eax, dword ptr [esi + 0x2428]
0073b432  85c0                     test       eax, eax
0073b434  0f85e31f0000             jne        0x73d41d
0073b43a  8b3e                     mov        edi, dword ptr [esi]
0073b43c  8d9e2c240000             lea        ebx, [esi + 0x242c]
0073b442  8bcb                     mov        ecx, ebx
0073b444  e8176cccff               call       0x402060
0073b449  50                       push       eax
0073b44a  8bce                     mov        ecx, esi
0073b44c  ff977c060000             call       dword ptr [edi + 0x67c]
0073b452  8bf8                     mov        edi, eax
0073b454  8b06                     mov        eax, dword ptr [esi]
0073b456  8bcb                     mov        ecx, ebx
0073b458  894514                   mov        dword ptr [ebp + 0x14], eax
0073b45b  e8006cccff               call       0x402060
0073b460  50                       push       eax
0073b461  8b4514                   mov        eax, dword ptr [ebp + 0x14]
0073b464  8bce                     mov        ecx, esi
0073b466  ff904c060000             call       dword ptr [eax + 0x64c]
0073b46c  8bd8                     mov        ebx, eax
0073b46e  8d8e2c240000             lea        ecx, [esi + 0x242c]
0073b474  895d14                   mov        dword ptr [ebp + 0x14], ebx
0073b477  e8e46bccff               call       0x402060