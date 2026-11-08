; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 0082f790..0082f7c8 (end exclusive); file offset 0042f790
; This is an instruction excerpt, not a recovered original source file.
0082f790  55                       push       ebp
0082f791  8bec                     mov        ebp, esp
0082f793  a164070501               mov        eax, dword ptr [0x1050764]
0082f798  85c0                     test       eax, eax
0082f79a  7402                     je         0x82f79e
0082f79c  ffd0                     call       eax
0082f79e  8b450c                   mov        eax, dword ptr [ebp + 0xc]
0082f7a1  6a00                     push       0
0082f7a3  6a00                     push       0
0082f7a5  50                       push       eax
0082f7a6  e845352600               call       0xa92cf0
0082f7ab  8b4d08                   mov        ecx, dword ptr [ebp + 8]
0082f7ae  83c404                   add        esp, 4
0082f7b1  50                       push       eax
0082f7b2  51                       push       ecx
0082f7b3  e838352600               call       0xa92cf0
0082f7b8  83c404                   add        esp, 4
0082f7bb  50                       push       eax
0082f7bc  b928120501               mov        ecx, 0x1051228
0082f7c1  e88a310800               call       0x8b2950
0082f7c6  5d                       pop        ebp
0082f7c7  c3                       ret        
