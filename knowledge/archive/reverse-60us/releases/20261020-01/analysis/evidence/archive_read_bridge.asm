; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 00a56180..00a56213 (end exclusive); file offset 00656180
; This is an instruction excerpt, not a recovered original source file.
00a56180  55                       push       ebp
00a56181  8bec                     mov        ebp, esp
00a56183  8b4508                   mov        eax, dword ptr [ebp + 8]
00a56186  85c0                     test       eax, eax
00a56188  53                       push       ebx
00a56189  56                       push       esi
00a5618a  57                       push       edi
00a5618b  8bf1                     mov        esi, ecx
00a5618d  7457                     je         0xa561e6
00a5618f  8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
00a56192  85db                     test       ebx, ebx
00a56194  7450                     je         0xa561e6
00a56196  8b7d14                   mov        edi, dword ptr [ebp + 0x14]
00a56199  85ff                     test       edi, edi
00a5619b  7449                     je         0xa561e6
00a5619d  50                       push       eax
00a5619e  8d4508                   lea        eax, [ebp + 8]
00a561a1  50                       push       eax
00a561a2  e859feffff               call       0xa56000
00a561a7  8b00                     mov        eax, dword ptr [eax]
00a561a9  3b4618                   cmp        eax, dword ptr [esi + 0x18]
00a561ac  750c                     jne        0xa561ba
00a561ae  6840aae400               push       0xe4aa40
00a561b3  6881010000               push       0x181
00a561b8  eb36                     jmp        0xa561f0
00a561ba  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
00a561bd  8b10                     mov        edx, dword ptr [eax]
00a561bf  57                       push       edi
00a561c0  51                       push       ecx
00a561c1  53                       push       ebx
00a561c2  52                       push       edx
00a561c3  56                       push       esi
00a561c4  8d4804                   lea        ecx, [eax + 4]
00a561c7  e854f1ffff               call       0xa55320
00a561cc  83f801                   cmp        eax, 1
00a561cf  750c                     jne        0xa561dd
00a561d1  6840aae400               push       0xe4aa40
00a561d6  6886010000               push       0x186
00a561db  eb13                     jmp        0xa561f0
00a561dd  5f                       pop        edi
00a561de  5e                       pop        esi
00a561df  33c0                     xor        eax, eax
00a561e1  5b                       pop        ebx
00a561e2  5d                       pop        ebp
00a561e3  c21000                   ret        0x10
00a561e6  6840aae400               push       0xe4aa40
00a561eb  687b010000               push       0x17b
00a561f0  68f0a5e400               push       0xe4a5f0
00a561f5  68eca4e400               push       0xe4a4ec
00a561fa  68808eff00               push       0xff8e80
00a561ff  e8ebc01a00               call       0xc022ef
00a56204  83c414                   add        esp, 0x14
00a56207  5f                       pop        edi
00a56208  5e                       pop        esi
00a56209  b801000000               mov        eax, 1
00a5620e  5b                       pop        ebx
00a5620f  5d                       pop        ebp
00a56210  c21000                   ret        0x10
