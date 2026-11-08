006d7592  6a01                     push       1
006d7594  6a01                     push       1
006d7596  6a01                     push       1
006d7598  6a2d                     push       0x2d
006d759a  8bce                     mov        ecx, esi
006d759c  ff9068070000             call       dword ptr [eax + 0x768]
006d75a2  84c0                     test       al, al
006d75a4  0f841a010000             je         0x6d76c4
006d75aa  8b16                     mov        edx, dword ptr [esi]
006d75ac  6a2d                     push       0x2d
006d75ae  8bce                     mov        ecx, esi
006d75b0  ff927c060000             call       dword ptr [edx + 0x67c]
006d75b6  8bd8                     mov        ebx, eax
006d75b8  89bdc8feffff             mov        dword ptr [ebp - 0x138], edi
006d75be  89bdccfeffff             mov        dword ptr [ebp - 0x134], edi
006d75c4  89bdd0feffff             mov        dword ptr [ebp - 0x130], edi
006d75ca  8d45f0                   lea        eax, [ebp - 0x10]
006d75cd  50                       push       eax
006d75ce  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
006d75d4  c745fc4f000000           mov        dword ptr [ebp - 4], 0x4f
006d75db  897df0                   mov        dword ptr [ebp - 0x10], edi
006d75de  e83dfbd2ff               call       0x407120
006d75e3  8d4df0                   lea        ecx, [ebp - 0x10]
006d75e6  51                       push       ecx
006d75e7  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
006d75ed  897df0                   mov        dword ptr [ebp - 0x10], edi
006d75f0  e82bfbd2ff               call       0x407120
006d75f5  8d55f0                   lea        edx, [ebp - 0x10]
006d75f8  52                       push       edx
006d75f9  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
006d75ff  c745f02d000000           mov        dword ptr [ebp - 0x10], 0x2d
006d7606  e815fbd2ff               call       0x407120
006d760b  56                       push       esi
006d760c  6a02                     push       2
006d760e  8bcb                     mov        ecx, ebx
006d7610  e84b89e7ff               call       0x54ff60
006d7615  8945f0                   mov        dword ptr [ebp - 0x10], eax
006d7618  8d45f0                   lea        eax, [ebp - 0x10]
006d761b  50                       push       eax
006d761c  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
006d7622  e8f9fad2ff               call       0x407120
006d7627  56                       push       esi
006d7628  57                       push       edi
006d7629  8bcb                     mov        ecx, ebx
006d762b  e83089e7ff               call       0x54ff60
006d7630  8d4df0                   lea        ecx, [ebp - 0x10]
006d7633  51                       push       ecx
006d7634  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
006d763a  8945f0                   mov        dword ptr [ebp - 0x10], eax
006d763d  e8defad2ff               call       0x407120
006d7642  8d55f0                   lea        edx, [ebp - 0x10]
006d7645  52                       push       edx
006d7646  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
006d764c  c745f001000000           mov        dword ptr [ebp - 0x10], 1
006d7653  e8c8fad2ff               call       0x407120
006d7658  8d45f0                   lea        eax, [ebp - 0x10]
006d765b  bb03000000               mov        ebx, 3
006d7660  50                       push       eax
006d7661  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
006d7667  895df0                   mov        dword ptr [ebp - 0x10], ebx
006d766a  e8b1fad2ff               call       0x407120
006d766f  8d4df0                   lea        ecx, [ebp - 0x10]
006d7672  51                       push       ecx
006d7673  8d8dc4feffff             lea        ecx, [ebp - 0x13c]
006d7679  895df0                   mov        dword ptr [ebp - 0x10], ebx
006d767c  e89ffad2ff               call       0x407120
006d7681  8b16                     mov        edx, dword ptr [esi]
006d7683  57                       push       edi
006d7684  57                       push       edi
006d7685  6a01                     push       1
006d7687  8d85c4feffff             lea        eax, [ebp - 0x13c]
006d768d  50                       push       eax
006d768e  6a0a                     push       0xa
006d7690  8bce                     mov        ecx, esi
006d7692  ff928c020000             call       dword ptr [edx + 0x28c]