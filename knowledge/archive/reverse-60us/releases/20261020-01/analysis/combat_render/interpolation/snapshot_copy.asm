0066f900 55                       push       ebp
0066f901 8bec                     mov        ebp, esp
0066f903 56                       push       esi
0066f904 8bf1                     mov        esi, ecx
0066f906 57                       push       edi
0066f907 8b7d08                   mov        edi, dword ptr [ebp + 8]
0066f90a 8b07                     mov        eax, dword ptr [edi]
0066f90c 8906                     mov        dword ptr [esi], eax
0066f90e 8b4f04                   mov        ecx, dword ptr [edi + 4]
0066f911 894e04                   mov        dword ptr [esi + 4], ecx
0066f914 8b5708                   mov        edx, dword ptr [edi + 8]
0066f917 895608                   mov        dword ptr [esi + 8], edx
0066f91a 8b470c                   mov        eax, dword ptr [edi + 0xc]
0066f91d 89460c                   mov        dword ptr [esi + 0xc], eax
0066f920 8b5710                   mov        edx, dword ptr [edi + 0x10]
0066f923 8d4710                   lea        eax, [edi + 0x10]
0066f926 2bd0                     sub        edx, eax
0066f928 8d4e10                   lea        ecx, [esi + 0x10]
0066f92b 03d1                     add        edx, ecx
0066f92d 8911                     mov        dword ptr [ecx], edx
0066f92f 8b5714                   mov        edx, dword ptr [edi + 0x14]
0066f932 8d4714                   lea        eax, [edi + 0x14]
0066f935 2bd0                     sub        edx, eax
0066f937 8d4e14                   lea        ecx, [esi + 0x14]
0066f93a 03d1                     add        edx, ecx
0066f93c 8911                     mov        dword ptr [ecx], edx
0066f93e 8b4718                   mov        eax, dword ptr [edi + 0x18]
0066f941 894618                   mov        dword ptr [esi + 0x18], eax
0066f944 8b4f1c                   mov        ecx, dword ptr [edi + 0x1c]
0066f947 894e1c                   mov        dword ptr [esi + 0x1c], ecx
0066f94a 8a5720                   mov        dl, byte ptr [edi + 0x20]
0066f94d 885620                   mov        byte ptr [esi + 0x20], dl
0066f950 8b4724                   mov        eax, dword ptr [edi + 0x24]
0066f953 894624                   mov        dword ptr [esi + 0x24], eax
0066f956 8b4f28                   mov        ecx, dword ptr [edi + 0x28]
0066f959 894e28                   mov        dword ptr [esi + 0x28], ecx
0066f95c 8b572c                   mov        edx, dword ptr [edi + 0x2c]
0066f95f 8d4730                   lea        eax, [edi + 0x30]
0066f962 8d4e30                   lea        ecx, [esi + 0x30]
0066f965 3bc8                     cmp        ecx, eax
0066f967 89562c                   mov        dword ptr [esi + 0x2c], edx
0066f96a 7408                     je         0x66f974
0066f96c 8b10                     mov        edx, dword ptr [eax]
0066f96e 2bd0                     sub        edx, eax
0066f970 03d1                     add        edx, ecx
0066f972 8911                     mov        dword ptr [ecx], edx
0066f974 8d4734                   lea        eax, [edi + 0x34]
0066f977 8d4e34                   lea        ecx, [esi + 0x34]
0066f97a 3bc8                     cmp        ecx, eax
0066f97c 7408                     je         0x66f986
0066f97e 8b10                     mov        edx, dword ptr [eax]
0066f980 2bd0                     sub        edx, eax
0066f982 03d1                     add        edx, ecx
0066f984 8911                     mov        dword ptr [ecx], edx
0066f986 8d4738                   lea        eax, [edi + 0x38]
0066f989 50                       push       eax
0066f98a 8d4e38                   lea        ecx, [esi + 0x38]
0066f98d e86e02fdff               call       0x63fc00
0066f992 8d4f48                   lea        ecx, [edi + 0x48]
0066f995 51                       push       ecx
0066f996 8d4e48                   lea        ecx, [esi + 0x48]
0066f999 e86202fdff               call       0x63fc00
0066f99e 8b5758                   mov        edx, dword ptr [edi + 0x58]
0066f9a1 6aff                     push       -1
0066f9a3 6a00                     push       0
0066f9a5 8d475c                   lea        eax, [edi + 0x5c]
0066f9a8 50                       push       eax
0066f9a9 8d4e5c                   lea        ecx, [esi + 0x5c]
0066f9ac 895658                   mov        dword ptr [esi + 0x58], edx
0066f9af e8ac33d9ff               call       0x402d60
0066f9b4 8a4f78                   mov        cl, byte ptr [edi + 0x78]
0066f9b7 5f                       pop        edi
0066f9b8 884e78                   mov        byte ptr [esi + 0x78], cl
0066f9bb 8bc6                     mov        eax, esi
0066f9bd 5e                       pop        esi
0066f9be 5d                       pop        ebp
