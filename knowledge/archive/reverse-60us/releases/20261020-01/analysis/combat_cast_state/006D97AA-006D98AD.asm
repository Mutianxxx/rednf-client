006d97aa  6a01                     push       1
006d97ac  6a01                     push       1
006d97ae  6a01                     push       1
006d97b0  6a4e                     push       0x4e
006d97b2  8bce                     mov        ecx, esi
006d97b4  ff9068070000             call       dword ptr [eax + 0x768]
006d97ba  84c0                     test       al, al
006d97bc  0f8413010000             je         0x6d98d5
006d97c2  8b16                     mov        edx, dword ptr [esi]
006d97c4  6a4e                     push       0x4e
006d97c6  8bce                     mov        ecx, esi
006d97c8  ff927c060000             call       dword ptr [edx + 0x67c]
006d97ce  8bd8                     mov        ebx, eax
006d97d0  89bd28ffffff             mov        dword ptr [ebp - 0xd8], edi
006d97d6  89bd2cffffff             mov        dword ptr [ebp - 0xd4], edi
006d97dc  89bd30ffffff             mov        dword ptr [ebp - 0xd0], edi
006d97e2  8d45f0                   lea        eax, [ebp - 0x10]
006d97e5  50                       push       eax
006d97e6  8d8d24ffffff             lea        ecx, [ebp - 0xdc]
006d97ec  c745fc6c000000           mov        dword ptr [ebp - 4], 0x6c
006d97f3  897df0                   mov        dword ptr [ebp - 0x10], edi
006d97f6  e825d9d2ff               call       0x407120
006d97fb  8d4df0                   lea        ecx, [ebp - 0x10]
006d97fe  51                       push       ecx
006d97ff  8d8d24ffffff             lea        ecx, [ebp - 0xdc]
006d9805  897df0                   mov        dword ptr [ebp - 0x10], edi
006d9808  e813d9d2ff               call       0x407120
006d980d  8d55f0                   lea        edx, [ebp - 0x10]
006d9810  52                       push       edx
006d9811  8d8d24ffffff             lea        ecx, [ebp - 0xdc]
006d9817  c745f04e000000           mov        dword ptr [ebp - 0x10], 0x4e
006d981e  e8fdd8d2ff               call       0x407120
006d9823  56                       push       esi
006d9824  6a08                     push       8
006d9826  8bcb                     mov        ecx, ebx
006d9828  e83367e7ff               call       0x54ff60
006d982d  8945f0                   mov        dword ptr [ebp - 0x10], eax
006d9830  8d45f0                   lea        eax, [ebp - 0x10]
006d9833  50                       push       eax
006d9834  8d8d24ffffff             lea        ecx, [ebp - 0xdc]
006d983a  e8e1d8d2ff               call       0x407120
006d983f  8d4df0                   lea        ecx, [ebp - 0x10]
006d9842  51                       push       ecx
006d9843  83cbff                   or         ebx, 0xffffffff
006d9846  8d8d24ffffff             lea        ecx, [ebp - 0xdc]
006d984c  895df0                   mov        dword ptr [ebp - 0x10], ebx
006d984f  e8ccd8d2ff               call       0x407120
006d9854  8d55f0                   lea        edx, [ebp - 0x10]
006d9857  52                       push       edx
006d9858  8d8d24ffffff             lea        ecx, [ebp - 0xdc]
006d985e  c745f003000000           mov        dword ptr [ebp - 0x10], 3
006d9865  e8b6d8d2ff               call       0x407120
006d986a  8d45f0                   lea        eax, [ebp - 0x10]
006d986d  50                       push       eax
006d986e  8d8d24ffffff             lea        ecx, [ebp - 0xdc]
006d9874  c745f003000000           mov        dword ptr [ebp - 0x10], 3
006d987b  e8a0d8d2ff               call       0x407120
006d9880  8d4df0                   lea        ecx, [ebp - 0x10]
006d9883  51                       push       ecx
006d9884  8d8d24ffffff             lea        ecx, [ebp - 0xdc]
006d988a  c745f003000000           mov        dword ptr [ebp - 0x10], 3
006d9891  e88ad8d2ff               call       0x407120
006d9896  8b16                     mov        edx, dword ptr [esi]
006d9898  57                       push       edi
006d9899  57                       push       edi
006d989a  6a01                     push       1
006d989c  8d8524ffffff             lea        eax, [ebp - 0xdc]
006d98a2  50                       push       eax
006d98a3  6a0a                     push       0xa
006d98a5  8bce                     mov        ecx, esi
006d98a7  ff928c020000             call       dword ptr [edx + 0x28c]