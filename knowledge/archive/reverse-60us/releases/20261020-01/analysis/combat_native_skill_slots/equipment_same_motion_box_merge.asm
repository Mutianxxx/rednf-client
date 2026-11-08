00456770  55                       push       ebp
00456771  8bec                     mov        ebp, esp
00456773  53                       push       ebx
00456774  8b5d08                   mov        ebx, dword ptr [ebp + 8]
00456777  85db                     test       ebx, ebx
00456779  0f84ac000000             je         0x45682b
0045677f  56                       push       esi
00456780  8b750c                   mov        esi, dword ptr [ebp + 0xc]
00456783  85f6                     test       esi, esi
00456785  0f849f000000             je         0x45682a
0045678b  8b5304                   mov        edx, dword ptr [ebx + 4]
0045678e  8b4b08                   mov        ecx, dword ptr [ebx + 8]
00456791  2bca                     sub        ecx, edx
00456793  b8eba00eea               mov        eax, 0xea0ea0eb
00456798  f7e9                     imul       ecx
0045679a  03d1                     add        edx, ecx
0045679c  c1fa07                   sar        edx, 7
0045679f  8bc2                     mov        eax, edx
004567a1  c1e81f                   shr        eax, 0x1f
004567a4  03c2                     add        eax, edx
004567a6  83f801                   cmp        eax, 1
004567a9  0f827b000000             jb         0x45682a
004567af  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
004567b2  57                       push       edi
004567b3  51                       push       ecx
004567b4  6a00                     push       0
004567b6  8bcb                     mov        ecx, ebx
004567b8  e8d3fd0000               call       0x466590
004567bd  8bc8                     mov        ecx, eax
004567bf  83c104                   add        ecx, 4
004567c2  e8d9810500               call       0x4ae9a0
004567c7  8b5604                   mov        edx, dword ptr [esi + 4]
004567ca  8b4e08                   mov        ecx, dword ptr [esi + 8]
004567cd  2bca                     sub        ecx, edx
004567cf  b8eba00eea               mov        eax, 0xea0ea0eb
004567d4  f7e9                     imul       ecx
004567d6  03d1                     add        edx, ecx
004567d8  c1fa07                   sar        edx, 7
004567db  8bc2                     mov        eax, edx
004567dd  c1e81f                   shr        eax, 0x1f
004567e0  33ff                     xor        edi, edi
004567e2  03c2                     add        eax, edx
004567e4  7443                     je         0x456829
004567e6  8b4d10                   mov        ecx, dword ptr [ebp + 0x10]
004567e9  51                       push       ecx
004567ea  57                       push       edi
004567eb  8bce                     mov        ecx, esi
004567ed  e89efd0000               call       0x466590
004567f2  83c004                   add        eax, 4
004567f5  50                       push       eax
004567f6  6a00                     push       0
004567f8  8bcb                     mov        ecx, ebx
004567fa  e891fd0000               call       0x466590
004567ff  8bc8                     mov        ecx, eax
00456801  83c104                   add        ecx, 4
00456804  e887830500               call       0x4aeb90
00456809  8b5604                   mov        edx, dword ptr [esi + 4]
0045680c  8b4e08                   mov        ecx, dword ptr [esi + 8]
0045680f  2bca                     sub        ecx, edx
00456811  b8eba00eea               mov        eax, 0xea0ea0eb
00456816  f7e9                     imul       ecx
00456818  03d1                     add        edx, ecx
0045681a  c1fa07                   sar        edx, 7
0045681d  8bc2                     mov        eax, edx
0045681f  c1e81f                   shr        eax, 0x1f
00456822  47                       inc        edi
00456823  03c2                     add        eax, edx
00456825  3bf8                     cmp        edi, eax
00456827  72bd                     jb         0x4567e6
00456829  5f                       pop        edi
0045682a  5e                       pop        esi
0045682b  5b                       pop        ebx
0045682c  5d                       pop        ebp
0045682d  c3                       ret        
