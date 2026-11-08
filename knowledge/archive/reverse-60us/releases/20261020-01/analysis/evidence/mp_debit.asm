; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 004d954f..004d9575 (end exclusive); file offset 000d954f
; This is an instruction excerpt, not a recovered original source file.
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
