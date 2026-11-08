00437d30  55                       push       ebp
00437d31  8bec                     mov        ebp, esp
00437d33  6aff                     push       -1
00437d35  686209c500               push       0xc50962
00437d3a  64a100000000             mov        eax, dword ptr fs:[0]
00437d40  50                       push       eax
00437d41  64892500000000           mov        dword ptr fs:[0], esp
00437d48  51                       push       ecx
00437d49  53                       push       ebx
00437d4a  56                       push       esi
00437d4b  8bf1                     mov        esi, ecx
00437d4d  57                       push       edi
00437d4e  8975f0                   mov        dword ptr [ebp - 0x10], esi
00437d51  e83ac4fcff               call       0x404190
00437d56  33db                     xor        ebx, ebx
00437d58  8d4e08                   lea        ecx, [esi + 8]
00437d5b  895dfc                   mov        dword ptr [ebp - 4], ebx
00437d5e  e87dc7fcff               call       0x4044e0
00437d63  8d4e10                   lea        ecx, [esi + 0x10]
00437d66  c645fc01                 mov        byte ptr [ebp - 4], 1
00437d6a  e871c7fcff               call       0x4044e0
00437d6f  8d4e1c                   lea        ecx, [esi + 0x1c]
00437d72  c645fc02                 mov        byte ptr [ebp - 4], 2
00437d76  e865c7fcff               call       0x4044e0
00437d7b  6810204000               push       0x402010
00437d80  68e0444000               push       0x4044e0
00437d85  6a03                     push       3
00437d87  6a08                     push       8
00437d89  8d4624                   lea        eax, [esi + 0x24]
00437d8c  50                       push       eax
00437d8d  c645fc03                 mov        byte ptr [ebp - 4], 3
00437d91  e8ce8a7c00               call       0xc00864
00437d96  8d7e3c                   lea        edi, [esi + 0x3c]
00437d99  8bcf                     mov        ecx, edi
00437d9b  c645fc04                 mov        byte ptr [ebp - 4], 4
00437d9f  e86cc9fcff               call       0x404710
00437da4  894704                   mov        dword ptr [edi + 4], eax
00437da7  c6401101                 mov        byte ptr [eax + 0x11], 1
00437dab  8b4704                   mov        eax, dword ptr [edi + 4]
00437dae  894004                   mov        dword ptr [eax + 4], eax
00437db1  8b4704                   mov        eax, dword ptr [edi + 4]
00437db4  8900                     mov        dword ptr [eax], eax
00437db6  8b4704                   mov        eax, dword ptr [edi + 4]
00437db9  894008                   mov        dword ptr [eax + 8], eax
00437dbc  895f08                   mov        dword ptr [edi + 8], ebx
00437dbf  6810204000               push       0x402010
00437dc4  6890414000               push       0x404190
00437dc9  6a03                     push       3
00437dcb  6a08                     push       8
00437dcd  8d4e54                   lea        ecx, [esi + 0x54]
00437dd0  51                       push       ecx
00437dd1  c645fc05                 mov        byte ptr [ebp - 4], 5
00437dd5  e88a8a7c00               call       0xc00864
00437dda  6810204000               push       0x402010
00437ddf  68e0444000               push       0x4044e0
00437de4  6a03                     push       3
00437de6  6a08                     push       8
00437de8  8d566c                   lea        edx, [esi + 0x6c]
00437deb  52                       push       edx
00437dec  c645fc06                 mov        byte ptr [ebp - 4], 6
00437df0  e86f8a7c00               call       0xc00864
00437df5  6810204000               push       0x402010
00437dfa  68e0444000               push       0x4044e0
00437dff  6a03                     push       3
00437e01  6a08                     push       8
00437e03  8d8684000000             lea        eax, [esi + 0x84]
00437e09  50                       push       eax
00437e0a  c645fc07                 mov        byte ptr [ebp - 4], 7
00437e0e  e8518a7c00               call       0xc00864
00437e13  6810204000               push       0x402010
00437e18  68e0444000               push       0x4044e0
00437e1d  6a03                     push       3
00437e1f  6a08                     push       8
00437e21  8d8e9c000000             lea        ecx, [esi + 0x9c]
00437e27  51                       push       ecx
00437e28  c645fc08                 mov        byte ptr [ebp - 4], 8
00437e2c  e8338a7c00               call       0xc00864
00437e31  c645fc09                 mov        byte ptr [ebp - 4], 9
00437e35  68e05f4300               push       0x435fe0
00437e3a  6880c96d00               push       0x6dc980
00437e3f  6a03                     push       3
00437e41  6a10                     push       0x10
00437e43  8d96b4000000             lea        edx, [esi + 0xb4]
00437e49  52                       push       edx
00437e4a  e8158a7c00               call       0xc00864
00437e4f  8d8ee4000000             lea        ecx, [esi + 0xe4]
00437e55  c645fc0a                 mov        byte ptr [ebp - 4], 0xa
00437e59  e832c3fcff               call       0x404190
00437e5e  8d8ef0000000             lea        ecx, [esi + 0xf0]
00437e64  c645fc0b                 mov        byte ptr [ebp - 4], 0xb
00437e68  e873c6fcff               call       0x4044e0
00437e6d  8d8ef8000000             lea        ecx, [esi + 0xf8]
00437e73  c645fc0c                 mov        byte ptr [ebp - 4], 0xc
00437e77  e864c6fcff               call       0x4044e0
00437e7c  8d8e00010000             lea        ecx, [esi + 0x100]
00437e82  c645fc0d                 mov        byte ptr [ebp - 4], 0xd
00437e86  e805c3fcff               call       0x404190
00437e8b  8d8e08010000             lea        ecx, [esi + 0x108]
00437e91  c645fc0e                 mov        byte ptr [ebp - 4], 0xe
00437e95  e8f6c2fcff               call       0x404190
00437e9a  8d8e10010000             lea        ecx, [esi + 0x110]
00437ea0  c645fc0f                 mov        byte ptr [ebp - 4], 0xf
00437ea4  e837c6fcff               call       0x4044e0
00437ea9  8d8e18010000             lea        ecx, [esi + 0x118]
00437eaf  c645fc10                 mov        byte ptr [ebp - 4], 0x10
00437eb3  e828c6fcff               call       0x4044e0
00437eb8  8d8e20010000             lea        ecx, [esi + 0x120]
00437ebe  c645fc11                 mov        byte ptr [ebp - 4], 0x11
00437ec2  e8c9c2fcff               call       0x404190
00437ec7  8d8e28010000             lea        ecx, [esi + 0x128]
00437ecd  c645fc12                 mov        byte ptr [ebp - 4], 0x12
00437ed1  e8bac2fcff               call       0x404190
00437ed6  8d8e30010000             lea        ecx, [esi + 0x130]
00437edc  c645fc13                 mov        byte ptr [ebp - 4], 0x13
00437ee0  e8fbc5fcff               call       0x4044e0
00437ee5  8d8e38010000             lea        ecx, [esi + 0x138]
00437eeb  c645fc14                 mov        byte ptr [ebp - 4], 0x14
00437eef  e8ecc5fcff               call       0x4044e0
00437ef4  6810204000               push       0x402010
00437ef9  6890414000               push       0x404190
00437efe  6a03                     push       3
00437f00  6a08                     push       8
00437f02  8d8640010000             lea        eax, [esi + 0x140]
00437f08  50                       push       eax
00437f09  c645fc15                 mov        byte ptr [ebp - 4], 0x15
00437f0d  e852897c00               call       0xc00864
00437f12  c7867001000007000000     mov        dword ptr [esi + 0x170], 7
00437f1c  899e6c010000             mov        dword ptr [esi + 0x16c], ebx
00437f22  66899e5c010000           mov        word ptr [esi + 0x15c], bx
00437f29  8d8e80010000             lea        ecx, [esi + 0x180]
00437f2f  c645fc17                 mov        byte ptr [ebp - 4], 0x17
00437f33  e8a8c5fcff               call       0x4044e0
00437f38  8d8e88010000             lea        ecx, [esi + 0x188]
00437f3e  c645fc18                 mov        byte ptr [ebp - 4], 0x18
00437f42  e849c2fcff               call       0x404190
00437f47  8d8e94010000             lea        ecx, [esi + 0x194]
00437f4d  c645fc19                 mov        byte ptr [ebp - 4], 0x19
00437f51  e88ac5fcff               call       0x4044e0
00437f56  8d8e9c010000             lea        ecx, [esi + 0x19c]
00437f5c  c645fc1a                 mov        byte ptr [ebp - 4], 0x1a
00437f60  e87bc5fcff               call       0x4044e0
00437f65  c645fc1b                 mov        byte ptr [ebp - 4], 0x1b
00437f69  8d8ea4010000             lea        ecx, [esi + 0x1a4]
00437f6f  e81cc2fcff               call       0x404190
00437f74  8d8eac010000             lea        ecx, [esi + 0x1ac]
00437f7a  c645fc1c                 mov        byte ptr [ebp - 4], 0x1c
00437f7e  e80dc2fcff               call       0x404190
00437f83  8bce                     mov        ecx, esi
00437f85  c645fc1d                 mov        byte ptr [ebp - 4], 0x1d
00437f89  e8a2d4ffff               call       0x435430
00437f8e  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00437f91  5f                       pop        edi
00437f92  8bc6                     mov        eax, esi
00437f94  5e                       pop        esi
00437f95  5b                       pop        ebx
00437f96  64890d00000000           mov        dword ptr fs:[0], ecx
00437f9d  8be5                     mov        esp, ebp
00437f9f  5d                       pop        ebp
00437fa0  c3                       ret        