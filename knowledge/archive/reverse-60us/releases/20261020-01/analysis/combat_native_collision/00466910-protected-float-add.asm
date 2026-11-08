00466910 55                       push      ebp
00466911 8bec                     mov       ebp, esp
00466913 51                       push      ecx
00466914 8b15d8012101             mov       edx, dword ptr [0x12101d8]
0046691a 8b5244                   mov       edx, dword ptr [edx + 0x44]
0046691d 8bc1                     mov       eax, ecx
0046691f 8b4804                   mov       ecx, dword ptr [eax + 4]
00466922 8d148a                   lea       edx, [edx + ecx*4]
00466925 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
0046692b 56                       push      esi
0046692c 8b32                     mov       esi, dword ptr [edx]
0046692e 33f2                     xor       esi, edx
00466930 33f1                     xor       esi, ecx
00466932 8975fc                   mov       dword ptr [ebp - 4], esi
00466935 8b7508                   mov       esi, dword ptr [ebp + 8]
00466938 d945fc                   fld       dword ptr [ebp - 4]
0046693b d806                     fadd      dword ptr [esi]
0046693d 57                       push      edi
0046693e 8bfa                     mov       edi, edx
00466940 33f9                     xor       edi, ecx
00466942 d95d08                   fstp      dword ptr [ebp + 8]
00466945 337d08                   xor       edi, dword ptr [ebp + 8]
00466948 893a                     mov       dword ptr [edx], edi
0046694a 8b15d8012101             mov       edx, dword ptr [0x12101d8]
00466950 8b4804                   mov       ecx, dword ptr [eax + 4]
00466953 8b5248                   mov       edx, dword ptr [edx + 0x48]
00466956 8b3c8a                   mov       edi, dword ptr [edx + ecx*4]
00466959 8d148a                   lea       edx, [edx + ecx*4]
0046695c 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
00466962 33fa                     xor       edi, edx
00466964 33f9                     xor       edi, ecx
00466966 897d08                   mov       dword ptr [ebp + 8], edi
00466969 d94508                   fld       dword ptr [ebp + 8]
0046696c 5f                       pop       edi
0046696d d806                     fadd      dword ptr [esi]
0046696f 8bf2                     mov       esi, edx
00466971 33f1                     xor       esi, ecx
00466973 d95d08                   fstp      dword ptr [ebp + 8]
00466976 337508                   xor       esi, dword ptr [ebp + 8]
00466979 8932                     mov       dword ptr [edx], esi
0046697b 5e                       pop       esi
0046697c 8be5                     mov       esp, ebp
0046697e 5d                       pop       ebp
0046697f c20400                   ret       4
00466982 cc                       int3      
00466983 cc                       int3      
00466984 cc                       int3      
00466985 cc                       int3      
00466986 cc                       int3      
00466987 cc                       int3      
00466988 cc                       int3      
00466989 cc                       int3      
0046698a cc                       int3      
0046698b cc                       int3      
0046698c cc                       int3      
0046698d cc                       int3      
0046698e cc                       int3      
0046698f cc                       int3      
00466990 55                       push      ebp
00466991 8bec                     mov       ebp, esp
00466993 51                       push      ecx
00466994 8bc1                     mov       eax, ecx
00466996 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
0046699c 8b4944                   mov       ecx, dword ptr [ecx + 0x44]
0046699f 8b5004                   mov       edx, dword ptr [eax + 4]
004669a2 53                       push      ebx
004669a3 8d1491                   lea       edx, [ecx + edx*4]
004669a6 56                       push      esi
004669a7 8b35dc012101             mov       esi, dword ptr [0x12101dc]
004669ad 57                       push      edi
004669ae 8b3a                     mov       edi, dword ptr [edx]
004669b0 33fa                     xor       edi, edx
004669b2 33fe                     xor       edi, esi
004669b4 897dfc                   mov       dword ptr [ebp - 4], edi
004669b7 8b7d08                   mov       edi, dword ptr [ebp + 8]
004669ba 8b5f04                   mov       ebx, dword ptr [edi + 4]
004669bd 8d0c99                   lea       ecx, [ecx + ebx*4]
004669c0 8bd9                     mov       ebx, ecx
004669c2 33de                     xor       ebx, esi
004669c4 3319                     xor       ebx, dword ptr [ecx]
004669c6 8bca                     mov       ecx, edx
004669c8 895d08                   mov       dword ptr [ebp + 8], ebx
004669cb d94508                   fld       dword ptr [ebp + 8]
004669ce 33ce                     xor       ecx, esi
