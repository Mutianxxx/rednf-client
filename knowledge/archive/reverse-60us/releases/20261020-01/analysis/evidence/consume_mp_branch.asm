; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 008a167f..008a1700 (end exclusive); file offset 004a167f
; This is an instruction excerpt, not a recovered original source file.
008a167f  8d55c8                   lea        edx, [ebp - 0x38]
008a1682  68c893e200               push       0xe293c8
008a1687  52                       push       edx
008a1688  e84331b6ff               call       0x4047d0
008a168d  83c408                   add        esp, 8
008a1690  84c0                     test       al, al
008a1692  746c                     je         0x8a1700
008a1694  8b7510                   mov        esi, dword ptr [ebp + 0x10]
008a1697  8d9f80010000             lea        ebx, [edi + 0x180]
008a169d  c745e802000000           mov        dword ptr [ebp - 0x18], 2
008a16a4  83fe01                   cmp        esi, 1
008a16a7  742e                     je         0x8a16d7
008a16a9  83fe02                   cmp        esi, 2
008a16ac  7429                     je         0x8a16d7
008a16ae  83fe04                   cmp        esi, 4
008a16b1  7424                     je         0x8a16d7
008a16b3  83fe03                   cmp        esi, 3
008a16b6  741f                     je         0x8a16d7
008a16b8  85f6                     test       esi, esi
008a16ba  741b                     je         0x8a16d7
008a16bc  83fe05                   cmp        esi, 5
008a16bf  7416                     je         0x8a16d7
008a16c1  6a00                     push       0
008a16c3  e898e1f8ff               call       0x82f860
008a16c8  d80d2c5bcd00             fmul       dword ptr [0xcd5b2c]
008a16ce  83c404                   add        esp, 4
008a16d1  8d45ec                   lea        eax, [ebp - 0x14]
008a16d4  50                       push       eax
008a16d5  eb0e                     jmp        0x8a16e5
008a16d7  6a00                     push       0
008a16d9  e882e1f8ff               call       0x82f860
008a16de  83c404                   add        esp, 4
008a16e1  8d4dec                   lea        ecx, [ebp - 0x14]
008a16e4  51                       push       ecx
008a16e5  8bcb                     mov        ecx, ebx
008a16e7  d95dec                   fstp       dword ptr [ebp - 0x14]
008a16ea  e8712eb6ff               call       0x404560
008a16ef  8b45e8                   mov        eax, dword ptr [ebp - 0x18]
008a16f2  83c308                   add        ebx, 8
008a16f5  48                       dec        eax
008a16f6  8945e8                   mov        dword ptr [ebp - 0x18], eax
008a16f9  75a9                     jne        0x8a16a4
008a16fb  e9e80b0000               jmp        0x8a22e8
