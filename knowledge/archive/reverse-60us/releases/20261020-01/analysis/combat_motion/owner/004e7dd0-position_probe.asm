004e7dd0  55                       push       ebp
004e7dd1  8bec                     mov        ebp, esp
004e7dd3  83ec0c                   sub        esp, 0xc
004e7dd6  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004e7dd9  85c0                     test       eax, eax
004e7ddb  56                       push       esi
004e7ddc  8bf1                     mov        esi, ecx
004e7dde  7406                     je         0x4e7de6
004e7de0  c70000000000             mov        dword ptr [eax], 0
004e7de6  8b8600010000             mov        eax, dword ptr [esi + 0x100]
004e7dec  85c0                     test       eax, eax
004e7dee  7509                     jne        0x4e7df9
004e7df0  b001                     mov        al, 1
004e7df2  5e                       pop        esi
004e7df3  8be5                     mov        esp, ebp
004e7df5  5d                       pop        ebp
004e7df6  c20c00                   ret        0xc
004e7df9  53                       push       ebx
004e7dfa  57                       push       edi
004e7dfb  c745f400000000           mov        dword ptr [ebp - 0xc], 0
004e7e02  c745f800000000           mov        dword ptr [ebp - 8], 0
004e7e09  c745fc00000000           mov        dword ptr [ebp - 4], 0
004e7e10  33ff                     xor        edi, edi
004e7e12  8b86f8000000             mov        eax, dword ptr [esi + 0xf8]
004e7e18  8b08                     mov        ecx, dword ptr [eax]
004e7e1a  85c9                     test       ecx, ecx
004e7e1c  7503                     jne        0x4e7e21
004e7e1e  8d4808                   lea        ecx, [eax + 8]
004e7e21  8b01                     mov        eax, dword ptr [ecx]
004e7e23  57                       push       edi
004e7e24  ff10                     call       dword ptr [eax]
004e7e26  d95cbdf4                 fstp       dword ptr [ebp + edi*4 - 0xc]
004e7e2a  47                       inc        edi
004e7e2b  83ff03                   cmp        edi, 3
004e7e2e  7ce2                     jl         0x4e7e12
004e7e30  8b3e                     mov        edi, dword ptr [esi]
004e7e32  8bce                     mov        ecx, esi
004e7e34  ff979c000000             call       dword ptr [edi + 0x9c]
004e7e3a  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004e7e3d  8b5508                   mov        edx, dword ptr [ebp + 8]
004e7e40  50                       push       eax
004e7e41  51                       push       ecx
004e7e42  52                       push       edx
004e7e43  8bce                     mov        ecx, esi
004e7e45  ff9788000000             call       dword ptr [edi + 0x88]
004e7e4b  8b86f8000000             mov        eax, dword ptr [esi + 0xf8]
004e7e51  c6407c00                 mov        byte ptr [eax + 0x7c], 0
004e7e55  8b8e00010000             mov        ecx, dword ptr [esi + 0x100]
004e7e5b  56                       push       esi
004e7e5c  b301                     mov        bl, 1
004e7e5e  e8dd330200               call       0x50b240
004e7e63  8bf8                     mov        edi, eax
004e7e65  85ff                     test       edi, edi
004e7e67  7439                     je         0x4e7ea2
004e7e69  6a00                     push       0
004e7e6b  68a028f400               push       0xf428a0
004e7e70  687c28f400               push       0xf4287c
004e7e75  6a00                     push       0
004e7e77  57                       push       edi
004e7e78  e88e8e7100               call       0xc00d0b
004e7e7d  83c414                   add        esp, 0x14
004e7e80  85c0                     test       eax, eax
004e7e82  7411                     je         0x4e7e95
004e7e84  8b10                     mov        edx, dword ptr [eax]
004e7e86  8bc8                     mov        ecx, eax
004e7e88  ff923c030000             call       dword ptr [edx + 0x33c]
004e7e8e  8b4808                   mov        ecx, dword ptr [eax + 8]
004e7e91  85c9                     test       ecx, ecx
004e7e93  7432                     je         0x4e7ec7
004e7e95  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004e7e98  32db                     xor        bl, bl
004e7e9a  85c0                     test       eax, eax
004e7e9c  7429                     je         0x4e7ec7
004e7e9e  8938                     mov        dword ptr [eax], edi
004e7ea0  eb25                     jmp        0x4e7ec7
004e7ea2  8b8600010000             mov        eax, dword ptr [esi + 0x100]
004e7ea8  8b8014010000             mov        eax, dword ptr [eax + 0x114]
004e7eae  85c0                     test       eax, eax
004e7eb0  7415                     je         0x4e7ec7
004e7eb2  8b4050                   mov        eax, dword ptr [eax + 0x50]
004e7eb5  85c0                     test       eax, eax
004e7eb7  740e                     je         0x4e7ec7
004e7eb9  56                       push       esi
004e7eba  8bc8                     mov        ecx, eax
004e7ebc  e88fdaf9ff               call       0x485950
004e7ec1  84c0                     test       al, al
004e7ec3  7502                     jne        0x4e7ec7
004e7ec5  32db                     xor        bl, bl
004e7ec7  33ff                     xor        edi, edi
004e7ec9  8da42400000000           lea        esp, [esp]
004e7ed0  8b86f8000000             mov        eax, dword ptr [esi + 0xf8]
004e7ed6  8b08                     mov        ecx, dword ptr [eax]
004e7ed8  85c9                     test       ecx, ecx
004e7eda  7503                     jne        0x4e7edf
004e7edc  8d4808                   lea        ecx, [eax + 8]
004e7edf  8b44bdf4                 mov        eax, dword ptr [ebp + edi*4 - 0xc]
004e7ee3  8b11                     mov        edx, dword ptr [ecx]
004e7ee5  50                       push       eax
004e7ee6  57                       push       edi
004e7ee7  ff5204                   call       dword ptr [edx + 4]
004e7eea  47                       inc        edi
004e7eeb  83ff03                   cmp        edi, 3
004e7eee  7ce0                     jl         0x4e7ed0
004e7ef0  8b8ef8000000             mov        ecx, dword ptr [esi + 0xf8]
004e7ef6  5f                       pop        edi
004e7ef7  8ac3                     mov        al, bl
004e7ef9  5b                       pop        ebx
004e7efa  c6417c01                 mov        byte ptr [ecx + 0x7c], 1
004e7efe  5e                       pop        esi
004e7eff  8be5                     mov        esp, ebp
004e7f01  5d                       pop        ebp
004e7f02  c20c00                   ret        0xc
