00836cb4  68b43ee100               push       0xe13eb4
00836cb9  e80f913c00               call       0xbffdcd
00836cbe  83c408                   add        esp, 8
00836cc1  50                       push       eax
00836cc2  8b45cc                   mov        eax, dword ptr [ebp - 0x34]
00836cc5  68b43ee100               push       0xe13eb4
00836cca  50                       push       eax
00836ccb  56                       push       esi
00836ccc  8d4db8                   lea        ecx, [ebp - 0x48]
00836ccf  e81cd3bcff               call       0x403ff0
00836cd4  85c0                     test       eax, eax
00836cd6  754a                     jne        0x836d22
00836cd8  56                       push       esi
00836cd9  e8828bffff               call       0x82f860
00836cde  d95df0                   fstp       dword ptr [ebp - 0x10]
00836ce1  8b15d8012101             mov        edx, dword ptr [0x12101d8]
00836ce7  8b4244                   mov        eax, dword ptr [edx + 0x44]
00836cea  8b4f04                   mov        ecx, dword ptr [edi + 4]
00836ced  8b15dc012101             mov        edx, dword ptr [0x12101dc]
00836cf3  8d0488                   lea        eax, [eax + ecx*4]
00836cf6  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
00836cf9  33d0                     xor        edx, eax
00836cfb  33d1                     xor        edx, ecx
00836cfd  8910                     mov        dword ptr [eax], edx
00836cff  8b15d8012101             mov        edx, dword ptr [0x12101d8]
00836d05  8b5248                   mov        edx, dword ptr [edx + 0x48]
00836d08  8b4704                   mov        eax, dword ptr [edi + 4]
00836d0b  8d0482                   lea        eax, [edx + eax*4]
00836d0e  8b15dc012101             mov        edx, dword ptr [0x12101dc]
00836d14  33d0                     xor        edx, eax
00836d16  83c404                   add        esp, 4
00836d19  33d1                     xor        edx, ecx
00836d1b  8910                     mov        dword ptr [eax], edx
00836d1d  e9e0100000               jmp        0x837e02
00836d22  68484ce100               push       0xe14c48
00836d27  e8a1903c00               call       0xbffdcd
00836d2c  83c404                   add        esp, 4
00836d2f  50                       push       eax
00836d30  8b45cc                   mov        eax, dword ptr [ebp - 0x34]
00836d33  68484ce100               push       0xe14c48
00836d38  50                       push       eax
00836d39  56                       push       esi
00836d3a  8d4db8                   lea        ecx, [ebp - 0x48]
00836d3d  e8aed2bcff               call       0x403ff0
00836d42  85c0                     test       eax, eax
00836d44  7544                     jne        0x836d8a
00836d46  56                       push       esi
00836d47  e8848affff               call       0x82f7d0
00836d4c  8b15d8012101             mov        edx, dword ptr [0x12101d8]
00836d52  8b5244                   mov        edx, dword ptr [edx + 0x44]
00836d55  8b4f0c                   mov        ecx, dword ptr [edi + 0xc]
00836d58  8d0c8a                   lea        ecx, [edx + ecx*4]
00836d5b  8b15dc012101             mov        edx, dword ptr [0x12101dc]
00836d61  33d1                     xor        edx, ecx
00836d63  33d0                     xor        edx, eax
00836d65  8911                     mov        dword ptr [ecx], edx
00836d67  8b15d8012101             mov        edx, dword ptr [0x12101d8]
00836d6d  8b5248                   mov        edx, dword ptr [edx + 0x48]
00836d70  8b4f0c                   mov        ecx, dword ptr [edi + 0xc]
00836d73  8d0c8a                   lea        ecx, [edx + ecx*4]
00836d76  8b15dc012101             mov        edx, dword ptr [0x12101dc]
00836d7c  33d1                     xor        edx, ecx
00836d7e  83c404                   add        esp, 4
00836d81  33d0                     xor        edx, eax
00836d83  8911                     mov        dword ptr [ecx], edx
00836d85  e978100000               jmp        0x837e02
00836d8a  68284ce100               push       0xe14c28
00836d8f  e839903c00               call       0xbffdcd
00836d94  83c404                   add        esp, 4
00836d97  50                       push       eax
00836d98  8b45cc                   mov        eax, dword ptr [ebp - 0x34]
00836d9b  68284ce100               push       0xe14c28
00836da0  50                       push       eax
00836da1  56                       push       esi
00836da2  8d4db8                   lea        ecx, [ebp - 0x48]
00836da5  e846d2bcff               call       0x403ff0
00836daa  85c0                     test       eax, eax
00836dac  751d                     jne        0x836dcb
00836dae  56                       push       esi
00836daf  e81c8affff               call       0x82f7d0
00836db4  83c404                   add        esp, 4
00836db7  8d4df0                   lea        ecx, [ebp - 0x10]
00836dba  51                       push       ecx
00836dbb  8d4f10                   lea        ecx, [edi + 0x10]
00836dbe  8945f0                   mov        dword ptr [ebp - 0x10], eax
00836dc1  e89ad7bcff               call       0x404560
00836dc6  e937100000               jmp        0x837e02
