; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 00b8ba50..00b8ba8c (end exclusive); file offset 0078ba50
; This is an instruction excerpt, not a recovered original source file.
00b8ba50  55                       push       ebp
00b8ba51  8bec                     mov        ebp, esp
00b8ba53  56                       push       esi
00b8ba54  8bf1                     mov        esi, ecx
00b8ba56  8b467c                   mov        eax, dword ptr [esi + 0x7c]
00b8ba59  85c0                     test       eax, eax
00b8ba5b  7413                     je         0xb8ba70
00b8ba5d  8d4900                   lea        ecx, [ecx]
00b8ba60  6a01                     push       1
00b8ba62  8bce                     mov        ecx, esi
00b8ba64  e827faffff               call       0xb8b490
00b8ba69  8b467c                   mov        eax, dword ptr [esi + 0x7c]
00b8ba6c  85c0                     test       eax, eax
00b8ba6e  75f0                     jne        0xb8ba60
00b8ba70  8b4514                   mov        eax, dword ptr [ebp + 0x14]
00b8ba73  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
00b8ba76  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00b8ba79  50                       push       eax
00b8ba7a  8b4508                   mov        eax, dword ptr [ebp + 8]
00b8ba7d  51                       push       ecx
00b8ba7e  52                       push       edx
00b8ba7f  50                       push       eax
00b8ba80  8bce                     mov        ecx, esi
00b8ba82  e839fbffff               call       0xb8b5c0
00b8ba87  5e                       pop        esi
00b8ba88  5d                       pop        ebp
00b8ba89  c21000                   ret        0x10
