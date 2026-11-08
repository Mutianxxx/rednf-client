004ecf00  f1                       int1       
004ecf01  ff899e5c0400             dec        dword ptr [ecx + 0x45c9e]
004ecf07  0033                     add        byte ptr [ebx], dh
004ecf09  c0888640040000           ror        byte ptr [eax + 0x44086], 0
004ecf10  898658040000             mov        dword ptr [esi + 0x458], eax
004ecf16  83c9ff                   or         ecx, 0xffffffff
004ecf19  898e54040000             mov        dword ptr [esi + 0x454], ecx
004ecf1f  898e68040000             mov        dword ptr [esi + 0x468], ecx
004ecf25  898e6c040000             mov        dword ptr [esi + 0x46c], ecx
004ecf2b  898660040000             mov        dword ptr [esi + 0x460], eax
004ecf31  898664040000             mov        dword ptr [esi + 0x464], eax
004ecf37  898ea0040000             mov        dword ptr [esi + 0x4a0], ecx
004ecf3d  898698040000             mov        dword ptr [esi + 0x498], eax
004ecf43  8986b4040000             mov        dword ptr [esi + 0x4b4], eax
004ecf49  889e9c040000             mov        byte ptr [esi + 0x49c], bl
004ecf4f  889eb8040000             mov        byte ptr [esi + 0x4b8], bl
004ecf55  889eb9040000             mov        byte ptr [esi + 0x4b9], bl
004ecf5b  8b3dd8012101             mov        edi, dword ptr [0x12101d8]
004ecf61  8b7f44                   mov        edi, dword ptr [edi + 0x44]
004ecf64  8b96c0040000             mov        edx, dword ptr [esi + 0x4c0]
004ecf6a  8d1497                   lea        edx, [edi + edx*4]
004ecf6d  8bfa                     mov        edi, edx
004ecf6f  333ddc012101             xor        edi, dword ptr [0x12101dc]
004ecf75  893a                     mov        dword ptr [edx], edi
004ecf77  8b3dd8012101             mov        edi, dword ptr [0x12101d8]
004ecf7d  8b7f48                   mov        edi, dword ptr [edi + 0x48]
004ecf80  8b96c0040000             mov        edx, dword ptr [esi + 0x4c0]
004ecf86  8d1497                   lea        edx, [edi + edx*4]
004ecf89  8bfa                     mov        edi, edx
004ecf8b  333ddc012101             xor        edi, dword ptr [0x12101dc]
004ecf91  893a                     mov        dword ptr [edx], edi
004ecf93  8b3dd8012101             mov        edi, dword ptr [0x12101d8]
004ecf99  8b7f44                   mov        edi, dword ptr [edi + 0x44]
004ecf9c  8b96c8040000             mov        edx, dword ptr [esi + 0x4c8]
004ecfa2  8d1497                   lea        edx, [edi + edx*4]
004ecfa5  8bfa                     mov        edi, edx
004ecfa7  333ddc012101             xor        edi, dword ptr [0x12101dc]
004ecfad  893a                     mov        dword ptr [edx], edi
004ecfaf  8b3dd8012101             mov        edi, dword ptr [0x12101d8]
004ecfb5  8b7f48                   mov        edi, dword ptr [edi + 0x48]
004ecfb8  8b96c8040000             mov        edx, dword ptr [esi + 0x4c8]
004ecfbe  8d1497                   lea        edx, [edi + edx*4]
004ecfc1  8bfa                     mov        edi, edx
004ecfc3  333ddc012101             xor        edi, dword ptr [0x12101dc]
004ecfc9  893a                     mov        dword ptr [edx], edi
004ecfcb  898ee8040000             mov        dword ptr [esi + 0x4e8], ecx
004ecfd1  898efc040000             mov        dword ptr [esi + 0x4fc], ecx
004ecfd7  898e04050000             mov        dword ptr [esi + 0x504], ecx
004ecfdd  8986e0040000             mov        dword ptr [esi + 0x4e0], eax
004ecfe3  8986e4040000             mov        dword ptr [esi + 0x4e4], eax
004ecfe9  8986ec040000             mov        dword ptr [esi + 0x4ec], eax
004ecfef  89860c050000             mov        dword ptr [esi + 0x50c], eax
004ecff5  888600050000             mov        byte ptr [esi + 0x500], al
004ecffb  888608050000             mov        byte ptr [esi + 0x508], al
004ed001  888609050000             mov        byte ptr [esi + 0x509], al
004ed007  889e0a050000             mov        byte ptr [esi + 0x50a], bl
004ed00d  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004ed013  8b5144                   mov        edx, dword ptr [ecx + 0x44]
004ed016  8b8600020000             mov        eax, dword ptr [esi + 0x200]
004ed01c  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004ed022  8d0482                   lea        eax, [edx + eax*4]
004ed025  8bc8                     mov        ecx, eax
004ed027  33cf                     xor        ecx, edi
004ed029  81f100800000             xor        ecx, 0x8000
004ed02f  8908                     mov        dword ptr [eax], ecx
004ed031  a1d8012101               mov        eax, dword ptr [0x12101d8]
004ed036  8b9600020000             mov        edx, dword ptr [esi + 0x200]
004ed03c  8b4848                   mov        ecx, dword ptr [eax + 0x48]
004ed03f  8d0491                   lea        eax, [ecx + edx*4]
004ed042  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
004ed048  8bd0                     mov        edx, eax
004ed04a  33d1                     xor        edx, ecx
004ed04c  81f200800000             xor        edx, 0x8000
004ed052  8910                     mov        dword ptr [eax], edx
004ed054  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004ed05a  8b5144                   mov        edx, dword ptr [ecx + 0x44]
004ed05d  8b8614050000             mov        eax, dword ptr [esi + 0x514]
004ed063  8d0482                   lea        eax, [edx + eax*4]
004ed066  8b1ddc012101             mov        ebx, dword ptr [0x12101dc]
004ed06c  8bd0                     mov        edx, eax
004ed06e  c745fc00000000           mov        dword ptr [ebp - 4], 0
004ed075  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004ed078  33d1                     xor        edx, ecx
004ed07a  33d3                     xor        edx, ebx
004ed07c  8910                     mov        dword ptr [eax], edx
004ed07e  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004ed084  8b5248                   mov        edx, dword ptr [edx + 0x48]
004ed087  8b8614050000             mov        eax, dword ptr [esi + 0x514]
004ed08d  8b1ddc012101             mov        ebx, dword ptr [0x12101dc]
004ed093  8d0482                   lea        eax, [edx + eax*4]
004ed096  8bd0                     mov        edx, eax
004ed098  33d1                     xor        edx, ecx
004ed09a  33d3                     xor        edx, ebx
004ed09c  8910                     mov        dword ptr [eax], edx
004ed09e  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004ed0a4  8b5144                   mov        edx, dword ptr [ecx + 0x44]
004ed0a7  8b861c050000             mov        eax, dword ptr [esi + 0x51c]
004ed0ad  8b1ddc012101             mov        ebx, dword ptr [0x12101dc]
004ed0b3  8d0482                   lea        eax, [edx + eax*4]
004ed0b6  8bd0                     mov        edx, eax
004ed0b8  c745fc00000000           mov        dword ptr [ebp - 4], 0
004ed0bf  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004ed0c2  33d1                     xor        edx, ecx
004ed0c4  33d3                     xor        edx, ebx
004ed0c6  8910                     mov        dword ptr [eax], edx
004ed0c8  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004ed0ce  8b5248                   mov        edx, dword ptr [edx + 0x48]
004ed0d1  8b861c050000             mov        eax, dword ptr [esi + 0x51c]
004ed0d7  8d0482                   lea        eax, [edx + eax*4]
004ed0da  8bd0                     mov        edx, eax
004ed0dc  33d1                     xor        edx, ecx
004ed0de  3315dc012101             xor        edx, dword ptr [0x12101dc]
004ed0e4  8910                     mov        dword ptr [eax], edx
004ed0e6  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004ed0ec  8b5144                   mov        edx, dword ptr [ecx + 0x44]
004ed0ef  8b86f8040000             mov        eax, dword ptr [esi + 0x4f8]
004ed0f5  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004ed0fb  8d0482                   lea        eax, [edx + eax*4]
004ed0fe  c745fc0000803f           mov        dword ptr [ebp - 4], 0x3f800000
004ed105  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004ed108  8bd0                     mov        edx, eax
004ed10a  33d1                     xor        edx, ecx
004ed10c  33d7                     xor        edx, edi
004ed10e  8910                     mov        dword ptr [eax], edx
004ed110  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004ed116  8b5248                   mov        edx, dword ptr [edx + 0x48]
004ed119  8b86f8040000             mov        eax, dword ptr [esi + 0x4f8]
004ed11f  8d0482                   lea        eax, [edx + eax*4]
004ed122  8bd0                     mov        edx, eax
004ed124  33d1                     xor        edx, ecx
004ed126  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
004ed12c  5f                       pop        edi
004ed12d  33d1                     xor        edx, ecx
004ed12f  5e                       pop        esi
004ed130  8910                     mov        dword ptr [eax], edx
004ed132  5b                       pop        ebx
004ed133  8be5                     mov        esp, ebp
004ed135  5d                       pop        ebp
004ed136  c3                       ret        
004ed137  cc                       int3       
004ed138  cc                       int3       
004ed139  cc                       int3       
004ed13a  cc                       int3       
004ed13b  cc                       int3       
004ed13c  cc                       int3       
004ed13d  cc                       int3       
004ed13e  cc                       int3       
004ed13f  cc                       int3       
004ed140  56                       push       esi
004ed141  57                       push       edi
004ed142  8bf1                     mov        esi, ecx
004ed144  e807d0faff               call       0x49a150
004ed149  8d8e60020000             lea        ecx, [esi + 0x260]
004ed14f  e8dc82f4ff               call       0x435430
004ed154  8b06                     mov        eax, dword ptr [esi]
004ed156  8bce                     mov        ecx, esi
004ed158  ff90a0010000             call       dword ptr [eax + 0x1a0]
004ed15e  8b16                     mov        edx, dword ptr [esi]
004ed160  8bce                     mov        ecx, esi
004ed162  c6869c04000001           mov        byte ptr [esi + 0x49c], 1
004ed169  ff9298020000             call       dword ptr [edx + 0x298]
004ed16f  8b06                     mov        eax, dword ptr [esi]
004ed171  6a01                     push       1
004ed173  8bce                     mov        ecx, esi
004ed175  ff90d0020000             call       dword ptr [eax + 0x2d0]
004ed17b  8b16                     mov        edx, dword ptr [esi]
004ed17d  6a01                     push       1
004ed17f  8bce                     mov        ecx, esi
004ed181  ff92d8020000             call       dword ptr [edx + 0x2d8]
004ed187  8b06                     mov        eax, dword ptr [esi]
004ed189  33ff                     xor        edi, edi
004ed18b  57                       push       edi
004ed18c  57                       push       edi
004ed18d  8bce                     mov        ecx, esi
004ed18f  ff90e0020000             call       dword ptr [eax + 0x2e0]
004ed195  89be58040000             mov        dword ptr [esi + 0x458], edi
004ed19b  83c8ff                   or         eax, 0xffffffff
004ed19e  898654040000             mov        dword ptr [esi + 0x454], eax
004ed1a4  89be60040000             mov        dword ptr [esi + 0x460], edi
004ed1aa  89be64040000             mov        dword ptr [esi + 0x464], edi
004ed1b0  898668040000             mov        dword ptr [esi + 0x468], eax
004ed1b6  89866c040000             mov        dword ptr [esi + 0x46c], eax
004ed1bc  89be0c050000             mov        dword ptr [esi + 0x50c], edi
004ed1c2  5f                       pop        edi
004ed1c3  5e                       pop        esi
004ed1c4  c3                       ret        
004ed1c5  cc                       int3       
004ed1c6  cc                       int3       
004ed1c7  cc                       int3       
004ed1c8  cc                       int3       
004ed1c9  cc                       int3       
004ed1ca  cc                       int3       
004ed1cb  cc                       int3       
004ed1cc  cc                       int3       
004ed1cd  cc                       int3       
004ed1ce  cc                       int3       
004ed1cf  cc                       int3       