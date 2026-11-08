00404560  55                       push       ebp
00404561  8bec                     mov        ebp, esp
00404563  8b15d8012101             mov        edx, dword ptr [0x12101d8]
00404569  8b5244                   mov        edx, dword ptr [edx + 0x44]
0040456c  8bc1                     mov        eax, ecx
0040456e  8b4804                   mov        ecx, dword ptr [eax + 4]
00404571  8d0c8a                   lea        ecx, [edx + ecx*4]
00404574  8b5508                   mov        edx, dword ptr [ebp + 8]
00404577  56                       push       esi
00404578  8b32                     mov        esi, dword ptr [edx]
0040457a  33f1                     xor        esi, ecx
0040457c  3335dc012101             xor        esi, dword ptr [0x12101dc]
00404582  8931                     mov        dword ptr [ecx], esi
00404584  8b35d8012101             mov        esi, dword ptr [0x12101d8]
0040458a  8b7648                   mov        esi, dword ptr [esi + 0x48]
0040458d  8b4804                   mov        ecx, dword ptr [eax + 4]
00404590  8b12                     mov        edx, dword ptr [edx]
00404592  8d0c8e                   lea        ecx, [esi + ecx*4]
00404595  8b35dc012101             mov        esi, dword ptr [0x12101dc]
0040459b  33d1                     xor        edx, ecx
0040459d  33d6                     xor        edx, esi
0040459f  8911                     mov        dword ptr [ecx], edx
004045a1  5e                       pop        esi
004045a2  5d                       pop        ebp
004045a3  c20400                   ret        4
004045a6  cc                       int3       
004045a7  cc                       int3       
004045a8  cc                       int3       
004045a9  cc                       int3       
004045aa  cc                       int3       
004045ab  cc                       int3       
004045ac  cc                       int3       
004045ad  cc                       int3       
004045ae  cc                       int3       
004045af  cc                       int3       
004045b0  55                       push       ebp
004045b1  8bec                     mov        ebp, esp
004045b3  56                       push       esi
004045b4  8b7508                   mov        esi, dword ptr [ebp + 8]
004045b7  8bc1                     mov        eax, ecx
004045b9  3bc6                     cmp        eax, esi
004045bb  7441                     je         0x4045fe
004045bd  8b5604                   mov        edx, dword ptr [esi + 4]
004045c0  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004045c6  8b4944                   mov        ecx, dword ptr [ecx + 0x44]
004045c9  53                       push       ebx
004045ca  8b1c91                   mov        ebx, dword ptr [ecx + edx*4]
004045cd  57                       push       edi
004045ce  8b7804                   mov        edi, dword ptr [eax + 4]
004045d1  8d1491                   lea        edx, [ecx + edx*4]
004045d4  8d0cb9                   lea        ecx, [ecx + edi*4]
004045d7  8bf9                     mov        edi, ecx
004045d9  33fa                     xor        edi, edx
004045db  33fb                     xor        edi, ebx
004045dd  8939                     mov        dword ptr [ecx], edi
004045df  8b5604                   mov        edx, dword ptr [esi + 4]
004045e2  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004045e8  8b4948                   mov        ecx, dword ptr [ecx + 0x48]
004045eb  8b7004                   mov        esi, dword ptr [eax + 4]
004045ee  8d                       .byte      0x8d
