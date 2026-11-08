00c3788e 55                       push       ebp
00c3788f 8bec                     mov        ebp, esp
00c37891 837d0800                 cmp        dword ptr [ebp + 8], 0
00c37895 56                       push       esi
00c37896 57                       push       edi
00c37897 751e                     jne        0xc378b7
00c37899 6a39                     push       0x39
00c3789b 59                       pop        ecx
00c3789c be68b1ff00               mov        esi, 0xffb168
00c378a1 bf80b0ff00               mov        edi, 0xffb080
00c378a6 c70554b2ff00ffff0000     mov        dword ptr [0xffb254], 0xffff
00c378b0 f3a5                     rep movsd  dword ptr es:[edi], dword ptr [esi]
00c378b2 e9a9000000               jmp        0xc37960
00c378b7 813d54b2ff00ffff0000     cmp        dword ptr [0xffb254], 0xffff
00c378c1 0f8599000000             jne        0xc37960
00c378c7 832554b2ff0000           and        dword ptr [0xffb254], 0
00c378ce 53                       push       ebx
00c378cf 6a39                     push       0x39
00c378d1 bb80b0ff00               mov        ebx, 0xffb080
00c378d6 59                       pop        ecx
00c378d7 be68b1ff00               mov        esi, 0xffb168
00c378dc 8bfb                     mov        edi, ebx
00c378de 53                       push       ebx
00c378df f3a5                     rep movsd  dword ptr es:[edi], dword ptr [esi]
00c378e1 e8c1a40000               call       0xc41da7
00c378e6 6a04                     push       4
00c378e8 8d4508                   lea        eax, [ebp + 8]
00c378eb 50                       push       eax
00c378ec 682058ea00               push       0xea5820
00c378f1 6a04                     push       4
00c378f3 e8ebfcffff               call       0xc375e3
00c378f8 83c414                   add        esp, 0x14
00c378fb 85c0                     test       eax, eax
00c378fd 7503                     jne        0xc37902
00c378ff 214508                   and        dword ptr [ebp + 8], eax
00c37902 33f6                     xor        esi, esi
00c37904 46                       inc        esi
00c37905 397508                   cmp        dword ptr [ebp + 8], esi
00c37908 7455                     je         0xc3795f
00c3790a 6a07                     push       7
00c3790c e8c9feffff               call       0xc377da
00c37911 85c0                     test       eax, eax
00c37913 59                       pop        ecx
00c37914 740e                     je         0xc37924
00c37916 53                       push       ebx
00c37917 e8099e0000               call       0xc41725
00c3791c 893554b2ff00             mov        dword ptr [0xffb254], esi
00c37922 eb3a                     jmp        0xc3795e
00c37924 6a0a                     push       0xa
00c37926 e8affeffff               call       0xc377da
00c3792b 85c0                     test       eax, eax
00c3792d 59                       pop        ecx
00c3792e 7412                     je         0xc37942
00c37930 53                       push       ebx
00c37931 e80a9c0000               call       0xc41540
00c37936 c70554b2ff0002000000     mov        dword ptr [0xffb254], 2
00c37940 eb1c                     jmp        0xc3795e
00c37942 6a06                     push       6
00c37944 e891feffff               call       0xc377da
00c37949 85c0                     test       eax, eax
00c3794b 59                       pop        ecx
00c3794c 7411                     je         0xc3795f
00c3794e 53                       push       ebx
00c3794f e8dc9a0000               call       0xc41430
00c37954 c70554b2ff0003000000     mov        dword ptr [0xffb254], 3
00c3795e 59                       pop        ecx
00c3795f 5b                       pop        ebx
00c37960 a154b2ff00               mov        eax, dword ptr [0xffb254]
00c37965 5f                       pop        edi
00c37966 5e                       pop        esi
00c37967 5d                       pop        ebp
