004bedf0  8975e4                   mov        dword ptr [ebp - 0x1c], esi
004bedf3  e89853f4ff               call       0x404190
004bedf8  8d7e08                   lea        edi, [esi + 8]
004bedfb  8bcf                     mov        ecx, edi
004bedfd  c745fc00000000           mov        dword ptr [ebp - 4], 0
004bee04  e88753f4ff               call       0x404190
004bee09  6810204000               push       0x402010
004bee0e  6890414000               push       0x404190
004bee13  6a06                     push       6
004bee15  6a08                     push       8
004bee17  8d4610                   lea        eax, [esi + 0x10]
004bee1a  50                       push       eax
004bee1b  c645fc01                 mov        byte ptr [ebp - 4], 1
004bee1f  e8401a7400               call       0xc00864
004bee24  6810204000               push       0x402010
004bee29  6890414000               push       0x404190
004bee2e  6a06                     push       6
004bee30  6a08                     push       8
004bee32  8d4e40                   lea        ecx, [esi + 0x40]
004bee35  51                       push       ecx
004bee36  c645fc02                 mov        byte ptr [ebp - 4], 2
004bee3a  e8251a7400               call       0xc00864
004bee3f  a1d8012101               mov        eax, dword ptr [0x12101d8]
004bee44  8b4844                   mov        ecx, dword ptr [eax + 0x44]
004bee47  8b5604                   mov        edx, dword ptr [esi + 4]
004bee4a  8d0491                   lea        eax, [ecx + edx*4]
004bee4d  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
004bee53  8bd0                     mov        edx, eax
004bee55  33d1                     xor        edx, ecx
004bee57  c745f00000a041           mov        dword ptr [ebp - 0x10], 0x41a00000
004bee5e  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
004bee61  33d1                     xor        edx, ecx
004bee63  8910                     mov        dword ptr [eax], edx
004bee65  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004bee6b  8b5248                   mov        edx, dword ptr [edx + 0x48]
004bee6e  8b4604                   mov        eax, dword ptr [esi + 4]
004bee71  8b1ddc012101             mov        ebx, dword ptr [0x12101dc]
004bee77  8d0482                   lea        eax, [edx + eax*4]
004bee7a  8bd0                     mov        edx, eax
004bee7c  33d3                     xor        edx, ebx
004bee7e  33d1                     xor        edx, ecx
004bee80  8910                     mov        dword ptr [eax], edx
004bee82  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004bee88  8b5144                   mov        edx, dword ptr [ecx + 0x44]
004bee8b  8b4704                   mov        eax, dword ptr [edi + 4]
004bee8e  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
004bee94  8d0482                   lea        eax, [edx + eax*4]
004bee97  8bd0                     mov        edx, eax
004bee99  33d1                     xor        edx, ecx
004bee9b  c745f000000041           mov        dword ptr [ebp - 0x10], 0x41000000
004beea2  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
004beea5  33d1                     xor        edx, ecx
004beea7  8910                     mov        dword ptr [eax], edx
004beea9  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004beeaf  8b5248                   mov        edx, dword ptr [edx + 0x48]
004beeb2  8b4704                   mov        eax, dword ptr [edi + 4]
004beeb5  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004beebb  8d0482                   lea        eax, [edx + eax*4]
004beebe  8bd0                     mov        edx, eax
004beec0  33d7                     xor        edx, edi
004beec2  33d1                     xor        edx, ecx
004beec4  8910                     mov        dword ptr [eax], edx
004beec6  33c0                     xor        eax, eax
004beec8  eb06                     jmp        0x4beed0
004beeca  8d9b00000000             lea        ebx, [ebx]
004beed0  83f805                   cmp        eax, 5
004beed3  0f87ff000000             ja         0x4befd8
004beed9  ff2485f8ef4b00           jmp        dword ptr [eax*4 + 0x4beff8]
004beee0  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004beee6  8b5244                   mov        edx, dword ptr [edx + 0x44]
004beee9  8b4cc614                 mov        ecx, dword ptr [esi + eax*8 + 0x14]
004beeed  8d0c8a                   lea        ecx, [edx + ecx*4]