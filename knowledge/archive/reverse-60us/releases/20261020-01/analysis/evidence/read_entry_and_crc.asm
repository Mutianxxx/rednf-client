; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 00a55320..00a55500 (end exclusive); file offset 00655320
; This is an instruction excerpt, not a recovered original source file.
00a55320  55                       push       ebp
00a55321  8bec                     mov        ebp, esp
00a55323  53                       push       ebx
00a55324  56                       push       esi
00a55325  8b7508                   mov        esi, dword ptr [ebp + 8]
00a55328  8a467c                   mov        al, byte ptr [esi + 0x7c]
00a5532b  84c0                     test       al, al
00a5532d  8bd9                     mov        ebx, ecx
00a5532f  741e                     je         0xa5534f
00a55331  8b4518                   mov        eax, dword ptr [ebp + 0x18]
00a55334  8b4d14                   mov        ecx, dword ptr [ebp + 0x14]
00a55337  8b5510                   mov        edx, dword ptr [ebp + 0x10]
00a5533a  50                       push       eax
00a5533b  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00a5533e  51                       push       ecx
00a5533f  52                       push       edx
00a55340  50                       push       eax
00a55341  56                       push       esi
00a55342  8bcb                     mov        ecx, ebx
00a55344  e827feffff               call       0xa55170
00a55349  5e                       pop        esi
00a5534a  5b                       pop        ebx
00a5534b  5d                       pop        ebp
00a5534c  c21400                   ret        0x14
00a5534f  57                       push       edi
00a55350  8b7d10                   mov        edi, dword ptr [ebp + 0x10]
00a55353  85ff                     test       edi, edi
00a55355  0f84d1010000             je         0xa5552c
00a5535b  8b4518                   mov        eax, dword ptr [ebp + 0x18]
00a5535e  85c0                     test       eax, eax
00a55360  0f84c6010000             je         0xa5552c
00a55366  8bce                     mov        ecx, esi
00a55368  c70000000000             mov        dword ptr [eax], 0
00a5536e  e8ddf9ffff               call       0xa54d50
00a55373  85c0                     test       eax, eax
00a55375  750f                     jne        0xa55386
00a55377  6838a8e400               push       0xe4a838
00a5537c  6824020000               push       0x224
00a55381  e9b0010000               jmp        0xa55536
00a55386  8b4b24                   mov        ecx, dword ptr [ebx + 0x24]
00a55389  3b4d14                   cmp        ecx, dword ptr [ebp + 0x14]
00a5538c  763c                     jbe        0xa553ca
00a5538e  68aca7e400               push       0xe4a7ac
00a55393  68808eff00               push       0xff8e80
00a55398  e852cf1a00               call       0xc022ef
00a5539d  6838a8e400               push       0xe4a838
00a553a2  6829020000               push       0x229
00a553a7  68f0a5e400               push       0xe4a5f0
00a553ac  68eca4e400               push       0xe4a4ec
00a553b1  68808eff00               push       0xff8e80
00a553b6  e834cf1a00               call       0xc022ef
00a553bb  83c41c                   add        esp, 0x1c
00a553be  5f                       pop        edi
00a553bf  5e                       pop        esi
00a553c0  b801000000               mov        eax, 1
00a553c5  5b                       pop        ebx
00a553c6  5d                       pop        ebp
00a553c7  c21400                   ret        0x14
00a553ca  8b4334                   mov        eax, dword ptr [ebx + 0x34]
00a553cd  85c0                     test       eax, eax
00a553cf  7418                     je         0xa553e9
00a553d1  8bd1                     mov        edx, ecx
00a553d3  c1e902                   shr        ecx, 2
00a553d6  8bf0                     mov        esi, eax
00a553d8  f3a5                     rep movsd  dword ptr es:[edi], dword ptr [esi]
00a553da  8bca                     mov        ecx, edx
00a553dc  83e103                   and        ecx, 3
00a553df  f3a4                     rep movsb  byte ptr es:[edi], byte ptr [esi]
00a553e1  8b7d10                   mov        edi, dword ptr [ebp + 0x10]
00a553e4  e9e6000000               jmp        0xa554cf
00a553e9  8b4304                   mov        eax, dword ptr [ebx + 4]
00a553ec  83f801                   cmp        eax, 1
00a553ef  753c                     jne        0xa5542d
00a553f1  68a0a6e400               push       0xe4a6a0
00a553f6  68808eff00               push       0xff8e80
00a553fb  e8efce1a00               call       0xc022ef
00a55400  6838a8e400               push       0xe4a838
00a55405  6834020000               push       0x234
00a5540a  68f0a5e400               push       0xe4a5f0
00a5540f  68eca4e400               push       0xe4a4ec
00a55414  68808eff00               push       0xff8e80
00a55419  e8d1ce1a00               call       0xc022ef
00a5541e  83c41c                   add        esp, 0x1c
00a55421  5f                       pop        edi
00a55422  5e                       pop        esi
00a55423  b801000000               mov        eax, 1
00a55428  5b                       pop        ebx
00a55429  5d                       pop        ebp
00a5542a  c21400                   ret        0x14
00a5542d  85c0                     test       eax, eax
00a5542f  0f859a000000             jne        0xa554cf
00a55435  8b4328                   mov        eax, dword ptr [ebx + 0x28]
00a55438  85c0                     test       eax, eax
00a5543a  0f8487000000             je         0xa554c7
00a55440  6a00                     push       0
00a55442  6a00                     push       0
00a55444  8bce                     mov        ecx, esi
00a55446  e805f9ffff               call       0xa54d50
00a5544b  50                       push       eax
00a5544c  e863d21a00               call       0xc026b4
00a55451  8b4608                   mov        eax, dword ptr [esi + 8]
00a55454  8b4b30                   mov        ecx, dword ptr [ebx + 0x30]
00a55457  83c40c                   add        esp, 0xc
00a5545a  03c8                     add        ecx, eax
00a5545c  6a00                     push       0
00a5545e  51                       push       ecx
00a5545f  8bce                     mov        ecx, esi
00a55461  e8eaf8ffff               call       0xa54d50
00a55466  50                       push       eax
00a55467  e848d21a00               call       0xc026b4
00a5546c  83c40c                   add        esp, 0xc
00a5546f  8bce                     mov        ecx, esi
00a55471  e8daf8ffff               call       0xa54d50
00a55476  8b5328                   mov        edx, dword ptr [ebx + 0x28]
00a55479  50                       push       eax
00a5547a  6a01                     push       1
00a5547c  52                       push       edx
00a5547d  57                       push       edi
00a5547e  e8b3cf1a00               call       0xc02436
00a55483  83c410                   add        esp, 0x10
00a55486  83f801                   cmp        eax, 1
00a55489  743c                     je         0xa554c7
00a5548b  6890a7e400               push       0xe4a790
00a55490  68808eff00               push       0xff8e80
00a55495  e855ce1a00               call       0xc022ef
00a5549a  6838a8e400               push       0xe4a838
00a5549f  683c020000               push       0x23c
00a554a4  68f0a5e400               push       0xe4a5f0
00a554a9  68eca4e400               push       0xe4a4ec
00a554ae  68808eff00               push       0xff8e80
00a554b3  e837ce1a00               call       0xc022ef
00a554b8  83c41c                   add        esp, 0x1c
00a554bb  5f                       pop        edi
00a554bc  5e                       pop        esi
00a554bd  b801000000               mov        eax, 1
00a554c2  5b                       pop        ebx
00a554c3  5d                       pop        ebp
00a554c4  c21400                   ret        0x14
00a554c7  8b4324                   mov        eax, dword ptr [ebx + 0x24]
00a554ca  8b4d18                   mov        ecx, dword ptr [ebp + 0x18]
00a554cd  8901                     mov        dword ptr [ecx], eax
00a554cf  8b5328                   mov        edx, dword ptr [ebx + 0x28]
00a554d2  8b432c                   mov        eax, dword ptr [ebx + 0x2c]
00a554d5  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00a554d8  52                       push       edx
00a554d9  57                       push       edi
00a554da  50                       push       eax
00a554db  e890f9ffff               call       0xa54e70
00a554e0  83c40c                   add        esp, 0xc
00a554e3  85c0                     test       eax, eax
00a554e5  753c                     jne        0xa55523
00a554e7  6878a7e400               push       0xe4a778
00a554ec  68808eff00               push       0xff8e80
00a554f1  e8f9cd1a00               call       0xc022ef
00a554f6  6838a8e400               push       0xe4a838
00a554fb  6845020000               push       0x245
