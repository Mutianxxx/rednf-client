00c05078 6a6c                     push       0x6c
00c0507a 6888d5e900               push       0xe9d588
00c0507f e88c1e0000               call       0xc06f10
00c05084 bf94000000               mov        edi, 0x94
00c05089 90                       nop        
00c0508a 90                       nop        
00c0508b 90                       nop        
00c0508c 90                       nop        
00c0508d 90                       nop        
00c0508e 90                       nop        
00c0508f 90                       nop        
00c05090 8965e8                   mov        dword ptr [ebp - 0x18], esp
00c05093 8bf4                     mov        esi, esp
00c05095 893e                     mov        dword ptr [esi], edi
00c05097 56                       push       esi
00c05098 ff1574f44001             call       dword ptr [0x140f474]
00c0509e 8b4e10                   mov        ecx, dword ptr [esi + 0x10]
00c050a1 890d28aa2301             mov        dword ptr [0x123aa28], ecx
00c050a7 8b4604                   mov        eax, dword ptr [esi + 4]
00c050aa a334aa2301               mov        dword ptr [0x123aa34], eax
00c050af 8b5608                   mov        edx, dword ptr [esi + 8]
00c050b2 891538aa2301             mov        dword ptr [0x123aa38], edx
00c050b8 8b760c                   mov        esi, dword ptr [esi + 0xc]
00c050bb 81e6ff7f0000             and        esi, 0x7fff
00c050c1 89352caa2301             mov        dword ptr [0x123aa2c], esi
00c050c7 83f902                   cmp        ecx, 2
00c050ca 740c                     je         0xc050d8
00c050cc 81ce00800000             or         esi, 0x8000
00c050d2 89352caa2301             mov        dword ptr [0x123aa2c], esi
00c050d8 c1e008                   shl        eax, 8
00c050db 03c2                     add        eax, edx
00c050dd a330aa2301               mov        dword ptr [0x123aa30], eax
00c050e2 33f6                     xor        esi, esi
00c050e4 56                       push       esi
00c050e5 8b3d94f54001             mov        edi, dword ptr [0x140f594]
00c050eb ffd7                     call       edi
00c050ed 6681384d5a               cmp        word ptr [eax], 0x5a4d
00c050f2 751f                     jne        0xc05113
00c050f4 8b483c                   mov        ecx, dword ptr [eax + 0x3c]
00c050f7 03c8                     add        ecx, eax
00c050f9 813950450000             cmp        dword ptr [ecx], 0x4550
00c050ff 7512                     jne        0xc05113
00c05101 0fb74118                 movzx      eax, word ptr [ecx + 0x18]
00c05105 3d0b010000               cmp        eax, 0x10b
00c0510a 741f                     je         0xc0512b
00c0510c 3d0b020000               cmp        eax, 0x20b
00c05111 7405                     je         0xc05118
00c05113 8975e4                   mov        dword ptr [ebp - 0x1c], esi
00c05116 eb27                     jmp        0xc0513f
00c05118 83b9840000000e           cmp        dword ptr [ecx + 0x84], 0xe
00c0511f 76f2                     jbe        0xc05113
00c05121 33c0                     xor        eax, eax
00c05123 39b1f8000000             cmp        dword ptr [ecx + 0xf8], esi
00c05129 eb0e                     jmp        0xc05139
00c0512b 8379740e                 cmp        dword ptr [ecx + 0x74], 0xe
00c0512f 76e2                     jbe        0xc05113
00c05131 33c0                     xor        eax, eax
00c05133 39b1e8000000             cmp        dword ptr [ecx + 0xe8], esi
00c05139 0f95c0                   setne      al
00c0513c 8945e4                   mov        dword ptr [ebp - 0x1c], eax
00c0513f 6a01                     push       1
00c05141 e80c550000               call       0xc0a652
00c05146 59                       pop        ecx
00c05147 85c0                     test       eax, eax
00c05149 7508                     jne        0xc05153
00c0514b 6a1c                     push       0x1c
00c0514d e802ffffff               call       0xc05054
00c05152 59                       pop        ecx
00c05153 e88e620000               call       0xc0b3e6
00c05158 85c0                     test       eax, eax
00c0515a 7508                     jne        0xc05164
00c0515c 6a10                     push       0x10
00c0515e e8f1feffff               call       0xc05054
00c05163 59                       pop        ecx
00c05164 e8f7720000               call       0xc0c460
00c05169 8975fc                   mov        dword ptr [ebp - 4], esi
00c0516c e8ac960000               call       0xc0e81d
00c05171 85c0                     test       eax, eax
00c05173 7d08                     jge        0xc0517d
00c05175 6a1b                     push       0x1b
