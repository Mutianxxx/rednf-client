004b8266  8b17                     mov        edx, dword ptr [edi]
004b8268  8bcf                     mov        ecx, edi
004b826a  ff9238010000             call       dword ptr [edx + 0x138]
004b8270  8b5804                   mov        ebx, dword ptr [eax + 4]
004b8273  3b5808                   cmp        ebx, dword ptr [eax + 8]
004b8276  8945fc                   mov        dword ptr [ebp - 4], eax
004b8279  0f849b000000             je         0x4b831a
004b827f  8d4304                   lea        eax, [ebx + 4]
004b8282  894508                   mov        dword ptr [ebp + 8], eax
004b8285  8b03                     mov        eax, dword ptr [ebx]
004b8287  8b16                     mov        edx, dword ptr [esi]
004b8289  50                       push       eax
004b828a  8bce                     mov        ecx, esi
004b828c  ff9224050000             call       dword ptr [edx + 0x524]
004b8292  84c0                     test       al, al
004b8294  7569                     jne        0x4b82ff
004b8296  8b0d48280001             mov        ecx, dword ptr [0x1002848]
004b829c  e8cf23f8ff               call       0x43a670
004b82a1  84c0                     test       al, al
004b82a3  7538                     jne        0x4b82dd
004b82a5  8b17                     mov        edx, dword ptr [edi]
004b82a7  8bcf                     mov        ecx, edi
004b82a9  ff92e0000000             call       dword ptr [edx + 0xe0]
004b82af  833809                   cmp        dword ptr [eax], 9
004b82b2  7529                     jne        0x4b82dd
004b82b4  8b07                     mov        eax, dword ptr [edi]
004b82b6  8bcf                     mov        ecx, edi
004b82b8  ff90f4000000             call       dword ptr [eax + 0xf4]
004b82be  8bc8                     mov        ecx, eax
004b82c0  83c108                   add        ecx, 8
004b82c3  e8989df4ff               call       0x402060
004b82c8  8b16                     mov        edx, dword ptr [esi]
004b82ca  8845f8                   mov        byte ptr [ebp - 8], al
004b82cd  8b4508                   mov        eax, dword ptr [ebp + 8]
004b82d0  8b4df8                   mov        ecx, dword ptr [ebp - 8]
004b82d3  50                       push       eax
004b82d4  51                       push       ecx
004b82d5  8bce                     mov        ecx, esi
004b82d7  ff9230050000             call       dword ptr [edx + 0x530]
004b82dd  8a878c070000             mov        al, byte ptr [edi + 0x78c]
004b82e3  84c0                     test       al, al
004b82e5  7418                     je         0x4b82ff
004b82e7  8b4508                   mov        eax, dword ptr [ebp + 8]
004b82ea  8b16                     mov        edx, dword ptr [esi]
004b82ec  50                       push       eax
004b82ed  8b03                     mov        eax, dword ptr [ebx]
004b82ef  8d8e40120000             lea        ecx, [esi + 0x1240]
004b82f5  51                       push       ecx
004b82f6  50                       push       eax
004b82f7  8bce                     mov        ecx, esi
004b82f9  ff92bc030000             call       dword ptr [edx + 0x3bc]
