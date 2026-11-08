004bc645  8a4510                   mov        al, byte ptr [ebp + 0x10]
004bc648  84c0                     test       al, al
004bc64a  7418                     je         0x4bc664
004bc64c  8dbe64150000             lea        edi, [esi + 0x1564]
004bc652  8bcf                     mov        ecx, edi
004bc654  e89788f4ff               call       0x404ef0
004bc659  6a00                     push       0
004bc65b  6a00                     push       0
004bc65d  8bcf                     mov        ecx, edi
004bc65f  e8fca86400               call       0xb06f60
004bc664  8a4514                   mov        al, byte ptr [ebp + 0x14]
004bc667  84c0                     test       al, al
004bc669  741a                     je         0x4bc685
004bc66b  8b8e04010000             mov        ecx, dword ptr [esi + 0x104]
004bc671  85c9                     test       ecx, ecx
004bc673  7410                     je         0x4bc685
004bc675  e8e6ac5600               call       0xa27360
004bc67a  8b8e04010000             mov        ecx, dword ptr [esi + 0x104]
004bc680  e80b765600               call       0xa23c90
004bc685  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004bc68b  8b5144                   mov        edx, dword ptr [ecx + 0x44]
004bc68e  8b8660150000             mov        eax, dword ptr [esi + 0x1560]
004bc694  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004bc69a  8b5d08                   mov        ebx, dword ptr [ebp + 8]
004bc69d  8d0482                   lea        eax, [edx + eax*4]
004bc6a0  8bc8                     mov        ecx, eax
004bc6a2  33cf                     xor        ecx, edi
004bc6a4  33cb                     xor        ecx, ebx
004bc6a6  8908                     mov        dword ptr [eax], ecx
004bc6a8  a1d8012101               mov        eax, dword ptr [0x12101d8]
004bc6ad  8b9660150000             mov        edx, dword ptr [esi + 0x1560]
004bc6b3  8b4848                   mov        ecx, dword ptr [eax + 0x48]
004bc6b6  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004bc6bc  8d0491                   lea        eax, [ecx + edx*4]
004bc6bf  8bd0                     mov        edx, eax
004bc6c1  33d7                     xor        edx, edi
004bc6c3  33d3                     xor        edx, ebx
004bc6c5  8910                     mov        dword ptr [eax], edx