004c1d30  55                       push       ebp
004c1d31  8bec                     mov        ebp, esp
004c1d33  56                       push       esi
004c1d34  57                       push       edi
004c1d35  8bf1                     mov        esi, ecx
004c1d37  e854a3fdff               call       0x49c090
004c1d3c  84c0                     test       al, al
004c1d3e  7457                     je         0x4c1d97
004c1d40  8b06                     mov        eax, dword ptr [esi]
004c1d42  8bce                     mov        ecx, esi
004c1d44  ff5034                   call       dword ptr [eax + 0x34]
004c1d47  84c0                     test       al, al
004c1d49  744c                     je         0x4c1d97
004c1d4b  8b8674280000             mov        eax, dword ptr [esi + 0x2874]
004c1d51  85c0                     test       eax, eax
004c1d53  7442                     je         0x4c1d97
004c1d55  8b86a02a0000             mov        eax, dword ptr [esi + 0x2aa0]
004c1d5b  85c0                     test       eax, eax
004c1d5d  7438                     je         0x4c1d97
004c1d5f  8b8674280000             mov        eax, dword ptr [esi + 0x2874]
004c1d65  8b88e00a0000             mov        ecx, dword ptr [eax + 0xae0]
004c1d6b  6aff                     push       -1
004c1d6d  51                       push       ecx
004c1d6e  c780e00a0000ffffffff     mov        dword ptr [eax + 0xae0], 0xffffffff
004c1d78  8b8e74280000             mov        ecx, dword ptr [esi + 0x2874]
004c1d7e  81c1e4080000             add        ecx, 0x8e4
004c1d84  51                       push       ecx
004c1d85  8bce                     mov        ecx, esi
004c1d87  e884f5ffff               call       0x4c1310
004c1d8c  8b8ea02a0000             mov        ecx, dword ptr [esi + 0x2aa0]
004c1d92  e8b9190700               call       0x533750
004c1d97  8b5514                   mov        edx, dword ptr [ebp + 0x14]
004c1d9a  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004c1d9d  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004c1da0  52                       push       edx
004c1da1  8b5508                   mov        edx, dword ptr [ebp + 8]
004c1da4  50                       push       eax
004c1da5  51                       push       ecx
004c1da6  52                       push       edx
004c1da7  8bce                     mov        ecx, esi
004c1da9  e892720100               call       0x4d9040
004c1dae  8bce                     mov        ecx, esi
004c1db0  0fb6f8                   movzx      edi, al
004c1db3  e8d8a2fdff               call       0x49c090
004c1db8  84c0                     test       al, al
004c1dba  743a                     je         0x4c1df6
004c1dbc  8b06                     mov        eax, dword ptr [esi]
004c1dbe  8bce                     mov        ecx, esi
004c1dc0  ff5034                   call       dword ptr [eax + 0x34]
004c1dc3  84c0                     test       al, al
004c1dc5  742f                     je         0x4c1df6
004c1dc7  8b8ea02a0000             mov        ecx, dword ptr [esi + 0x2aa0]
004c1dcd  6a00                     push       0
004c1dcf  e8ec220700               call       0x5340c0
004c1dd4  50                       push       eax
004c1dd5  8bce                     mov        ecx, esi
004c1dd7  e8f4faffff               call       0x4c18d0
004c1ddc  8b8e74280000             mov        ecx, dword ptr [esi + 0x2874]
004c1de2  8b89f80a0000             mov        ecx, dword ptr [ecx + 0xaf8]
004c1de8  85c9                     test       ecx, ecx
004c1dea  740a                     je         0x4c1df6
004c1dec  68f418cd00               push       0xcd18f4
004c1df1  e8eab00600               call       0x52cee0
004c1df6  33c0                     xor        eax, eax
004c1df8  85ff                     test       edi, edi
004c1dfa  5f                       pop        edi
004c1dfb  0f95c0                   setne      al
004c1dfe  5e                       pop        esi
004c1dff  5d                       pop        ebp
004c1e00  c21000                   ret        0x10
004c1e03  cc                       int3       
004c1e04  cc                       int3       
004c1e05  cc                       int3       
004c1e06  cc                       int3       
004c1e07  cc                       int3       
004c1e08  cc                       int3       
004c1e09  cc                       int3       
004c1e0a  cc                       int3       
004c1e0b  cc                       int3       
004c1e0c  cc                       int3       
004c1e0d  cc                       int3       
004c1e0e  cc                       int3       
004c1e0f  cc                       int3       
004c1e10  55                       push       ebp
004c1e11  8bec                     mov        ebp, esp
004c1e13  53                       push       ebx
004c1e14  56                       push       esi
004c1e15  57                       push       edi
004c1e16  8bf1                     mov        esi, ecx
004c1e18  e873a2fdff               call       0x49c090
004c1e1d  84c0                     test       al, al
004c1e1f  7416                     je         0x4c1e37
004c1e21  8b06                     mov        eax, dword ptr [esi]
004c1e23  8bce                     mov        ecx, esi
004c1e25  ff5034                   call       dword ptr [eax + 0x34]
004c1e28  84c0                     test       al, al
004c1e2a  740b                     je         0x4c1e37
004c1e2c  8b8ea02a0000             mov        ecx, dword ptr [esi + 0x2aa0]
004c1e32  e839190700               call       0x533770
004c1e37  8b5d10                   mov        ebx, dword ptr [ebp + 0x10]
004c1e3a  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004c1e3d  8b7d08                   mov        edi, dword ptr [ebp + 8]
004c1e40  53                       push       ebx
004c1e41  51                       push       ecx
004c1e42  57                       push       edi
004c1e43  8bce                     mov        ecx, esi
004c1e45  e876d90100               call       0x4df7c0
004c1e4a  8bce                     mov        ecx, esi
004c1e4c  894510                   mov        dword ptr [ebp + 0x10], eax
004c1e4f  e83ca2fdff               call       0x49c090
004c1e54  84c0                     test       al, al
004c1e56  7456                     je         0x4c1eae
004c1e58  8b16                     mov        edx, dword ptr [esi]
004c1e5a  8bce                     mov        ecx, esi
004c1e5c  ff5234                   call       dword ptr [edx + 0x34]
004c1e5f  84c0                     test       al, al
004c1e61  744b                     je         0x4c1eae
004c1e63  85ff                     test       edi, edi
004c1e65  7447                     je         0x4c1eae
004c1e67  8b450c                   mov        eax, dword ptr [ebp + 0xc]
004c1e6a  8b8ea02a0000             mov        ecx, dword ptr [esi + 0x2aa0]
004c1e70  53                       push       ebx
004c1e71  50                       push       eax
004c1e72  57                       push       edi
004c1e73  6a00                     push       0
004c1e75  e8b6220700               call       0x534130
004c1e7a  50                       push       eax
004c1e7b  8bce                     mov        ecx, esi
004c1e7d  e84efaffff               call       0x4c18d0
004c1e82  8b8e74280000             mov        ecx, dword ptr [esi + 0x2874]
004c1e88  8b89f80a0000             mov        ecx, dword ptr [ecx + 0xaf8]
004c1e8e  85c9                     test       ecx, ecx
004c1e90  740a                     je         0x4c1e9c
004c1e92  680819cd00               push       0xcd1908
004c1e97  e844b00600               call       0x52cee0
004c1e9c  8b17                     mov        edx, dword ptr [edi]
004c1e9e  8bcf                     mov        ecx, edi
004c1ea0  ff92a8020000             call       dword ptr [edx + 0x2a8]
004c1ea6  50                       push       eax
004c1ea7  8bce                     mov        ecx, esi
004c1ea9  e862eaffff               call       0x4c0910
004c1eae  8b4510                   mov        eax, dword ptr [ebp + 0x10]
004c1eb1  5f                       pop        edi
004c1eb2  5e                       pop        esi
004c1eb3  5b                       pop        ebx
004c1eb4  5d                       pop        ebp
004c1eb5  c20c00                   ret        0xc
004c1eb8  cc                       int3       
004c1eb9  cc                       int3       
004c1eba  cc                       int3       
004c1ebb  cc                       int3       
004c1ebc  cc                       int3       
004c1ebd  cc                       int3       
004c1ebe  cc                       int3       
004c1ebf  cc                       int3       