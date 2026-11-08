; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 00a55fa0..00a55fef (end exclusive); file offset 00655fa0
; This is an instruction excerpt, not a recovered original source file.
00a55fa0  55                       push       ebp
00a55fa1  8bec                     mov        ebp, esp
00a55fa3  56                       push       esi
00a55fa4  8b7508                   mov        esi, dword ptr [ebp + 8]
00a55fa7  57                       push       edi
00a55fa8  8bf9                     mov        edi, ecx
00a55faa  8d4708                   lea        eax, [edi + 8]
00a55fad  56                       push       esi
00a55fae  50                       push       eax
00a55faf  e8bcfbffff               call       0xa55b70
00a55fb4  8b0e                     mov        ecx, dword ptr [esi]
00a55fb6  8b11                     mov        edx, dword ptr [ecx]
00a55fb8  895724                   mov        dword ptr [edi + 0x24], edx
00a55fbb  830604                   add        dword ptr [esi], 4
00a55fbe  8b4724                   mov        eax, dword ptr [edi + 0x24]
00a55fc1  83c003                   add        eax, 3
00a55fc4  83e0fc                   and        eax, 0xfffffffc
00a55fc7  894728                   mov        dword ptr [edi + 0x28], eax
00a55fca  8b0e                     mov        ecx, dword ptr [esi]
00a55fcc  8b11                     mov        edx, dword ptr [ecx]
00a55fce  89572c                   mov        dword ptr [edi + 0x2c], edx
00a55fd1  8b0e                     mov        ecx, dword ptr [esi]
00a55fd3  83c104                   add        ecx, 4
00a55fd6  890e                     mov        dword ptr [esi], ecx
00a55fd8  8bc1                     mov        eax, ecx
00a55fda  8b00                     mov        eax, dword ptr [eax]
00a55fdc  894730                   mov        dword ptr [edi + 0x30], eax
00a55fdf  8b06                     mov        eax, dword ptr [esi]
00a55fe1  83c408                   add        esp, 8
00a55fe4  83c004                   add        eax, 4
00a55fe7  8906                     mov        dword ptr [esi], eax
00a55fe9  5f                       pop        edi
00a55fea  33c0                     xor        eax, eax
00a55fec  5e                       pop        esi
00a55fed  5d                       pop        ebp
