004d9536  1084c0c7869821           adc        byte ptr [eax + eax*8 + 0x219886c7], al
004d953d  0000                     add        byte ptr [eax], al
004d953f  0000                     add        byte ptr [eax], al
004d9541  0000                     add        byte ptr [eax], al
004d9543  c7869421000001000000     mov        dword ptr [esi + 0x2194], 1
004d954d  743d                     je         0x4d958c
004d954f  6aff                     push       -1
004d9551  56                       push       esi
004d9552  8bcb                     mov        ecx, ebx
004d9554  e8b7780700               call       0x550e10
004d9559  8b1e                     mov        ebx, dword ptr [esi]
004d955b  6a01                     push       1
004d955d  8d8e38120000             lea        ecx, [esi + 0x1238]
004d9563  8bf8                     mov        edi, eax
004d9565  e8f68af2ff               call       0x402060
004d956a  2bc7                     sub        eax, edi
004d956c  50                       push       eax
004d956d  8bce                     mov        ecx, esi
004d956f  ff93f4030000             call       dword ptr [ebx + 0x3f4]
004d9575  8b06                     mov        eax, dword ptr [esi]
004d9577  8bce                     mov        ecx, esi
004d9579  ff5034                   call       dword ptr [eax + 0x34]
004d957c  84c0                     test       al, al