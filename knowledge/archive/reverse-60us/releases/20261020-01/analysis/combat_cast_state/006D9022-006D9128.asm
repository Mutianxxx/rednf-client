006d9022  6a01                     push       1
006d9024  6a01                     push       1
006d9026  6a01                     push       1
006d9028  6a4c                     push       0x4c
006d902a  8bce                     mov        ecx, esi
006d902c  ff9068070000             call       dword ptr [eax + 0x768]
006d9032  84c0                     test       al, al
006d9034  0f841a010000             je         0x6d9154
006d903a  8b16                     mov        edx, dword ptr [esi]
006d903c  6a4c                     push       0x4c
006d903e  8bce                     mov        ecx, esi
006d9040  ff927c060000             call       dword ptr [edx + 0x67c]
006d9046  8bd8                     mov        ebx, eax
006d9048  89bdd8feffff             mov        dword ptr [ebp - 0x128], edi
006d904e  89bddcfeffff             mov        dword ptr [ebp - 0x124], edi
006d9054  89bde0feffff             mov        dword ptr [ebp - 0x120], edi
006d905a  8d45f0                   lea        eax, [ebp - 0x10]
006d905d  50                       push       eax
006d905e  8d8dd4feffff             lea        ecx, [ebp - 0x12c]
006d9064  c745fc65000000           mov        dword ptr [ebp - 4], 0x65
006d906b  897df0                   mov        dword ptr [ebp - 0x10], edi
006d906e  e8ade0d2ff               call       0x407120
006d9073  8d4df0                   lea        ecx, [ebp - 0x10]
006d9076  51                       push       ecx
006d9077  8d8dd4feffff             lea        ecx, [ebp - 0x12c]
006d907d  897df0                   mov        dword ptr [ebp - 0x10], edi
006d9080  e89be0d2ff               call       0x407120
006d9085  8d55f0                   lea        edx, [ebp - 0x10]
006d9088  52                       push       edx
006d9089  8d8dd4feffff             lea        ecx, [ebp - 0x12c]
006d908f  c745f04c000000           mov        dword ptr [ebp - 0x10], 0x4c
006d9096  e885e0d2ff               call       0x407120
006d909b  56                       push       esi
006d909c  6a04                     push       4
006d909e  8bcb                     mov        ecx, ebx
006d90a0  e8bb6ee7ff               call       0x54ff60
006d90a5  8945f0                   mov        dword ptr [ebp - 0x10], eax
006d90a8  8d45f0                   lea        eax, [ebp - 0x10]
006d90ab  50                       push       eax
006d90ac  8d8dd4feffff             lea        ecx, [ebp - 0x12c]
006d90b2  e869e0d2ff               call       0x407120
006d90b7  56                       push       esi
006d90b8  57                       push       edi
006d90b9  8bcb                     mov        ecx, ebx
006d90bb  e8a06ee7ff               call       0x54ff60
006d90c0  8d4df0                   lea        ecx, [ebp - 0x10]
006d90c3  51                       push       ecx
006d90c4  8d8dd4feffff             lea        ecx, [ebp - 0x12c]
006d90ca  8945f0                   mov        dword ptr [ebp - 0x10], eax
006d90cd  e84ee0d2ff               call       0x407120
006d90d2  8d55f0                   lea        edx, [ebp - 0x10]
006d90d5  52                       push       edx
006d90d6  8d8dd4feffff             lea        ecx, [ebp - 0x12c]
006d90dc  c745f003000000           mov        dword ptr [ebp - 0x10], 3
006d90e3  e838e0d2ff               call       0x407120
006d90e8  8d45f0                   lea        eax, [ebp - 0x10]
006d90eb  bb02000000               mov        ebx, 2
006d90f0  50                       push       eax
006d90f1  8d8dd4feffff             lea        ecx, [ebp - 0x12c]
006d90f7  895df0                   mov        dword ptr [ebp - 0x10], ebx
006d90fa  e821e0d2ff               call       0x407120
006d90ff  8d4df0                   lea        ecx, [ebp - 0x10]
006d9102  51                       push       ecx
006d9103  8d8dd4feffff             lea        ecx, [ebp - 0x12c]
006d9109  895df0                   mov        dword ptr [ebp - 0x10], ebx
006d910c  e80fe0d2ff               call       0x407120
006d9111  8b16                     mov        edx, dword ptr [esi]
006d9113  57                       push       edi
006d9114  57                       push       edi
006d9115  6a01                     push       1
006d9117  8d85d4feffff             lea        eax, [ebp - 0x12c]
006d911d  50                       push       eax
006d911e  6a0a                     push       0xa
006d9120  8bce                     mov        ecx, esi
006d9122  ff928c020000             call       dword ptr [edx + 0x28c]