004cbd90  55                       push       ebp
004cbd91  8bec                     mov        ebp, esp
004cbd93  83ec08                   sub        esp, 8
004cbd96  56                       push       esi
004cbd97  8bf1                     mov        esi, ecx
004cbd99  e8f202fdff               call       0x49c090
004cbd9e  84c0                     test       al, al
004cbda0  0f84f8000000             je         0x4cbe9e
004cbda6  8b86b0010000             mov        eax, dword ptr [esi + 0x1b0]
004cbdac  85c0                     test       eax, eax
004cbdae  0f85ea000000             jne        0x4cbe9e
004cbdb4  8a8606160000             mov        al, byte ptr [esi + 0x1606]
004cbdba  84c0                     test       al, al
004cbdbc  750e                     jne        0x4cbdcc
004cbdbe  8a8607160000             mov        al, byte ptr [esi + 0x1607]
004cbdc4  84c0                     test       al, al
004cbdc6  0f84d2000000             je         0x4cbe9e
004cbdcc  8b06                     mov        eax, dword ptr [esi]
004cbdce  53                       push       ebx
004cbdcf  57                       push       edi
004cbdd0  6a00                     push       0
004cbdd2  8bce                     mov        ecx, esi
004cbdd4  ff9044060000             call       dword ptr [eax + 0x644]
004cbdda  8b16                     mov        edx, dword ptr [esi]
004cbddc  6a01                     push       1
004cbdde  8bce                     mov        ecx, esi
004cbde0  8bf8                     mov        edi, eax
004cbde2  ff9244060000             call       dword ptr [edx + 0x644]
004cbde8  8a9606160000             mov        dl, byte ptr [esi + 0x1606]
004cbdee  84d2                     test       dl, dl
004cbdf0  8945fc                   mov        dword ptr [ebp - 4], eax
004cbdf3  7444                     je         0x4cbe39
004cbdf5  8a8e07160000             mov        cl, byte ptr [esi + 0x1607]
004cbdfb  84c9                     test       cl, cl
004cbdfd  7436                     je         0x4cbe35
004cbdff  8b8e78160000             mov        ecx, dword ptr [esi + 0x1678]
004cbe05  85c9                     test       ecx, ecx
004cbe07  750d                     jne        0x4cbe16
004cbe09  83ff04                   cmp        edi, 4
004cbe0c  751d                     jne        0x4cbe2b
004cbe0e  8bbe7c160000             mov        edi, dword ptr [esi + 0x167c]
004cbe14  eb1f                     jmp        0x4cbe35
004cbe16  83f901                   cmp        ecx, 1
004cbe19  751a                     jne        0x4cbe35
004cbe1b  83f804                   cmp        eax, 4
004cbe1e  750b                     jne        0x4cbe2b
004cbe20  8b867c160000             mov        eax, dword ptr [esi + 0x167c]
004cbe26  8945fc                   mov        dword ptr [ebp - 4], eax
004cbe29  eb0a                     jmp        0x4cbe35
004cbe2b  c78678160000ffffffff     mov        dword ptr [esi + 0x1678], 0xffffffff
004cbe35  84d2                     test       dl, dl
004cbe37  7506                     jne        0x4cbe3f
004cbe39  8bbe08160000             mov        edi, dword ptr [esi + 0x1608]
004cbe3f  8a8e07160000             mov        cl, byte ptr [esi + 0x1607]
004cbe45  84c9                     test       cl, cl
004cbe47  750b                     jne        0x4cbe54
004cbe49  8b8e0c160000             mov        ecx, dword ptr [esi + 0x160c]
004cbe4f  894dfc                   mov        dword ptr [ebp - 4], ecx
004cbe52  8bc1                     mov        eax, ecx
004cbe54  83ff04                   cmp        edi, 4
004cbe57  c645f801                 mov        byte ptr [ebp - 8], 1
004cbe5b  7405                     je         0x4cbe62
004cbe5d  83f804                   cmp        eax, 4
004cbe60  7504                     jne        0x4cbe66
004cbe62  c645f800                 mov        byte ptr [ebp - 8], 0
004cbe66  3bbe08160000             cmp        edi, dword ptr [esi + 0x1608]
004cbe6c  8b5df8                   mov        ebx, dword ptr [ebp - 8]
004cbe6f  7413                     je         0x4cbe84
004cbe71  8b16                     mov        edx, dword ptr [esi]
004cbe73  6a00                     push       0
004cbe75  53                       push       ebx
004cbe76  57                       push       edi
004cbe77  6a00                     push       0
004cbe79  8bce                     mov        ecx, esi
004cbe7b  ff9298040000             call       dword ptr [edx + 0x498]
004cbe81  8b45fc                   mov        eax, dword ptr [ebp - 4]
004cbe84  3b860c160000             cmp        eax, dword ptr [esi + 0x160c]
004cbe8a  7410                     je         0x4cbe9c
004cbe8c  8b16                     mov        edx, dword ptr [esi]
004cbe8e  6a00                     push       0
004cbe90  53                       push       ebx
004cbe91  50                       push       eax
004cbe92  6a01                     push       1
004cbe94  8bce                     mov        ecx, esi
004cbe96  ff9298040000             call       dword ptr [edx + 0x498]
004cbe9c  5f                       pop        edi
004cbe9d  5b                       pop        ebx
004cbe9e  5e                       pop        esi
004cbe9f  8be5                     mov        esp, ebp
004cbea1  5d                       pop        ebp
004cbea2  c3                       ret        
