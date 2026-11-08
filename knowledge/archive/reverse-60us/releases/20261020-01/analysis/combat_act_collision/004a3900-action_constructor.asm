004a3900 55                       push       ebp
004a3901 8bec                     mov        ebp, esp
004a3903 6aff                     push       -1
004a3905 68126fc500               push       0xc56f12
004a390a 64a100000000             mov        eax, dword ptr fs:[0]
004a3910 50                       push       eax
004a3911 64892500000000           mov        dword ptr fs:[0], esp
004a3918 51                       push       ecx
004a3919 53                       push       ebx
004a391a 56                       push       esi
004a391b 8bf1                     mov        esi, ecx
004a391d 57                       push       edi
004a391e c706d0efcc00             mov        dword ptr [esi], 0xccefd0
004a3924 33ff                     xor        edi, edi
004a3926 c7461c07000000           mov        dword ptr [esi + 0x1c], 7
004a392d 897e18                   mov        dword ptr [esi + 0x18], edi
004a3930 8975f0                   mov        dword ptr [ebp - 0x10], esi
004a3933 66897e08                 mov        word ptr [esi + 8], di
004a3937 897dfc                   mov        dword ptr [ebp - 4], edi
004a393a 897e28                   mov        dword ptr [esi + 0x28], edi
004a393d 897e2c                   mov        dword ptr [esi + 0x2c], edi
004a3940 897e30                   mov        dword ptr [esi + 0x30], edi
004a3943 8d5e34                   lea        ebx, [esi + 0x34]
004a3946 8bcb                     mov        ecx, ebx
004a3948 c645fc01                 mov        byte ptr [ebp - 4], 1
004a394c e89f0df6ff               call       0x4046f0
004a3951 894304                   mov        dword ptr [ebx + 4], eax
004a3954 897b08                   mov        dword ptr [ebx + 8], edi
004a3957 897e44                   mov        dword ptr [esi + 0x44], edi
004a395a 897e48                   mov        dword ptr [esi + 0x48], edi
004a395d 897e4c                   mov        dword ptr [esi + 0x4c], edi
004a3960 897e54                   mov        dword ptr [esi + 0x54], edi
004a3963 897e58                   mov        dword ptr [esi + 0x58], edi
004a3966 897e5c                   mov        dword ptr [esi + 0x5c], edi
004a3969 897e64                   mov        dword ptr [esi + 0x64], edi
004a396c 897e68                   mov        dword ptr [esi + 0x68], edi
004a396f 897e6c                   mov        dword ptr [esi + 0x6c], edi
004a3972 89be90000000             mov        dword ptr [esi + 0x90], edi
004a3978 89be94000000             mov        dword ptr [esi + 0x94], edi
004a397e 89be98000000             mov        dword ptr [esi + 0x98], edi
004a3984 89bea0000000             mov        dword ptr [esi + 0xa0], edi
004a398a 89bea4000000             mov        dword ptr [esi + 0xa4], edi
004a3990 89bea8000000             mov        dword ptr [esi + 0xa8], edi
004a3996 8d8eb0000000             lea        ecx, [esi + 0xb0]
004a399c c645fc07                 mov        byte ptr [ebp - 4], 7
004a39a0 e88b43f9ff               call       0x437d30
004a39a5 89be6c020000             mov        dword ptr [esi + 0x26c], edi
004a39ab 89be70020000             mov        dword ptr [esi + 0x270], edi
004a39b1 89be74020000             mov        dword ptr [esi + 0x274], edi
004a39b7 89be90020000             mov        dword ptr [esi + 0x290], edi
004a39bd 89be94020000             mov        dword ptr [esi + 0x294], edi
004a39c3 89be98020000             mov        dword ptr [esi + 0x298], edi
004a39c9 8d9e9c020000             lea        ebx, [esi + 0x29c]
004a39cf 8bcb                     mov        ecx, ebx
004a39d1 c645fc0a                 mov        byte ptr [ebp - 4], 0xa
004a39d5 e8b63efcff               call       0x467890
004a39da 894304                   mov        dword ptr [ebx + 4], eax
004a39dd c6401501                 mov        byte ptr [eax + 0x15], 1
004a39e1 8b4304                   mov        eax, dword ptr [ebx + 4]
004a39e4 894004                   mov        dword ptr [eax + 4], eax
004a39e7 8b4304                   mov        eax, dword ptr [ebx + 4]
004a39ea 8900                     mov        dword ptr [eax], eax
004a39ec 8b4304                   mov        eax, dword ptr [ebx + 4]
004a39ef 894008                   mov        dword ptr [eax + 8], eax
004a39f2 897b08                   mov        dword ptr [ebx + 8], edi
004a39f5 89beac020000             mov        dword ptr [esi + 0x2ac], edi
004a39fb 89beb0020000             mov        dword ptr [esi + 0x2b0], edi
004a3a01 89beb4020000             mov        dword ptr [esi + 0x2b4], edi
004a3a07 8d9ed4020000             lea        ebx, [esi + 0x2d4]
004a3a0d 8bcb                     mov        ecx, ebx
004a3a0f c645fc0c                 mov        byte ptr [ebp - 4], 0xc
004a3a13 e878780800               call       0x52b290
004a3a18 894304                   mov        dword ptr [ebx + 4], eax
004a3a1b c6402d01                 mov        byte ptr [eax + 0x2d], 1
004a3a1f 8b4304                   mov        eax, dword ptr [ebx + 4]
004a3a22 894004                   mov        dword ptr [eax + 4], eax
004a3a25 8b4304                   mov        eax, dword ptr [ebx + 4]
004a3a28 8900                     mov        dword ptr [eax], eax
004a3a2a 8b4304                   mov        eax, dword ptr [ebx + 4]
004a3a2d 894008                   mov        dword ptr [eax + 8], eax
004a3a30 897b08                   mov        dword ptr [ebx + 8], edi
004a3a33 8bce                     mov        ecx, esi
004a3a35 c645fc0d                 mov        byte ptr [ebp - 4], 0xd
004a3a39 e8f29e5800               call       0xa2d930
004a3a3e 8b4510                   mov        eax, dword ptr [ebp + 0x10]
004a3a41 8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004a3a44 8b5508                   mov        edx, dword ptr [ebp + 8]
004a3a47 50                       push       eax
004a3a48 51                       push       ecx
004a3a49 52                       push       edx
004a3a4a 8bce                     mov        ecx, esi
004a3a4c e8fff05800               call       0xa32b50
004a3a51 8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004a3a54 5f                       pop        edi
004a3a55 8bc6                     mov        eax, esi
004a3a57 5e                       pop        esi
004a3a58 5b                       pop        ebx
004a3a59 64890d00000000           mov        dword ptr fs:[0], ecx
004a3a60 8be5                     mov        esp, ebp
004a3a62 5d                       pop        ebp
004a3a63 c20c00                   ret        0xc
