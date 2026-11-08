0049b250  55                       push       ebp
0049b251  8bec                     mov        ebp, esp
0049b253  56                       push       esi
0049b254  8bf1                     mov        esi, ecx
0049b256  8b06                     mov        eax, dword ptr [esi]
0049b258  57                       push       edi
0049b259  ff90f4000000             call       dword ptr [eax + 0xf4]
0049b25f  85c0                     test       eax, eax
0049b261  8b7d08                   mov        edi, dword ptr [ebp + 8]
0049b264  7420                     je         0x49b286
0049b266  8b16                     mov        edx, dword ptr [esi]
0049b268  8bce                     mov        ecx, esi
0049b26a  ff92f4000000             call       dword ptr [edx + 0xf4]
0049b270  3bf8                     cmp        edi, eax
0049b272  7412                     je         0x49b286
0049b274  8b06                     mov        eax, dword ptr [esi]
0049b276  8bce                     mov        ecx, esi
0049b278  ff90f4000000             call       dword ptr [eax + 0xf4]
0049b27e  8d4834                   lea        ecx, [eax + 0x34]
0049b281  e81a852a00               call       0x7437a0
0049b286  85ff                     test       edi, edi
0049b288  89be04010000             mov        dword ptr [esi + 0x104], edi
0049b28e  7436                     je         0x49b2c6
0049b290  8b8648010000             mov        eax, dword ptr [esi + 0x148]
0049b296  85c0                     test       eax, eax
0049b298  740c                     je         0x49b2a6
0049b29a  8b16                     mov        edx, dword ptr [esi]
0049b29c  6a00                     push       0
0049b29e  8bce                     mov        ecx, esi
0049b2a0  ff9200010000             call       dword ptr [edx + 0x100]
0049b2a6  8b86e0000000             mov        eax, dword ptr [esi + 0xe0]
0049b2ac  50                       push       eax
0049b2ad  8d4f48                   lea        ecx, [edi + 0x48]
0049b2b0  e82bbe6600               call       0xb070e0
0049b2b5  8a8738010000             mov        al, byte ptr [edi + 0x138]
0049b2bb  84c0                     test       al, al
0049b2bd  7407                     je         0x49b2c6
0049b2bf  8bcf                     mov        ecx, edi
0049b2c1  e89acc5800               call       0xa27f60
0049b2c6  5f                       pop        edi
0049b2c7  5e                       pop        esi
0049b2c8  5d                       pop        ebp
0049b2c9  c2                       .byte      0xc2
