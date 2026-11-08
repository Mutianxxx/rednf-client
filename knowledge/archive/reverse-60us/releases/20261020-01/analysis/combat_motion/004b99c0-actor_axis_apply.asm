004b99c0  55                       push       ebp
004b99c1  8bec                     mov        ebp, esp
004b99c3  83ec08                   sub        esp, 8
004b99c6  8a4510                   mov        al, byte ptr [ebp + 0x10]
004b99c9  84c0                     test       al, al
004b99cb  53                       push       ebx
004b99cc  56                       push       esi
004b99cd  57                       push       edi
004b99ce  8b7d08                   mov        edi, dword ptr [ebp + 8]
004b99d1  8bf1                     mov        esi, ecx
004b99d3  8d8cfee4150000           lea        ecx, [esi + edi*8 + 0x15e4]
004b99da  7507                     jne        0x4b99e3
004b99dc  8d8cfed4150000           lea        ecx, [esi + edi*8 + 0x15d4]
004b99e3  e87886f4ff               call       0x402060
004b99e8  8d8cfef4150000           lea        ecx, [esi + edi*8 + 0x15f4]
004b99ef  894508                   mov        dword ptr [ebp + 8], eax
004b99f2  e86986f4ff               call       0x402060
004b99f7  8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
004b99fa  85db                     test       ebx, ebx
004b99fc  8945fc                   mov        dword ptr [ebp - 4], eax
004b99ff  c7451000000000           mov        dword ptr [ebp + 0x10], 0
004b9a06  7418                     je         0x4b9a20
004b9a08  83fb02                   cmp        ebx, 2
004b9a0b  7413                     je         0x4b9a20
004b9a0d  83fb01                   cmp        ebx, 1
004b9a10  7405                     je         0x4b9a17
004b9a12  83fb03                   cmp        ebx, 3
004b9a15  7510                     jne        0x4b9a27
004b9a17  c745100000803f           mov        dword ptr [ebp + 0x10], 0x3f800000
004b9a1e  eb07                     jmp        0x4b9a27
004b9a20  c74510000080bf           mov        dword ptr [ebp + 0x10], 0xbf800000
004b9a27  8d8e18160000             lea        ecx, [esi + 0x1618]
004b9a2d  e82e86f4ff               call       0x402060
004b9a32  3de8030000               cmp        eax, 0x3e8
004b9a37  741d                     je         0x4b9a56
004b9a39  8d8e18160000             lea        ecx, [esi + 0x1618]
004b9a3f  e81c86f4ff               call       0x402060
004b9a44  8945f8                   mov        dword ptr [ebp - 8], eax
004b9a47  db45f8                   fild       dword ptr [ebp - 8]
004b9a4a  d84d10                   fmul       dword ptr [ebp + 0x10]
004b9a4d  d80df811cc00             fmul       dword ptr [0xcc11f8]
004b9a53  d95d10                   fstp       dword ptr [ebp + 0x10]
004b9a56  8a4514                   mov        al, byte ptr [ebp + 0x14]
004b9a59  84c0                     test       al, al
004b9a5b  745f                     je         0x4b9abc
004b9a5d  8b8ef8000000             mov        ecx, dword ptr [esi + 0xf8]
004b9a63  8b01                     mov        eax, dword ptr [ecx]
004b9a65  85c0                     test       eax, eax
004b9a67  7404                     je         0x4b9a6d
004b9a69  8bc8                     mov        ecx, eax
004b9a6b  eb03                     jmp        0x4b9a70
004b9a6d  83c108                   add        ecx, 8
004b9a70  db4508                   fild       dword ptr [ebp + 8]
004b9a73  8b01                     mov        eax, dword ptr [ecx]
004b9a75  51                       push       ecx
004b9a76  d84d10                   fmul       dword ptr [ebp + 0x10]
004b9a79  d91c24                   fstp       dword ptr [esp]
004b9a7c  57                       push       edi
004b9a7d  ff500c                   call       dword ptr [eax + 0xc]
004b9a80  8b86f8000000             mov        eax, dword ptr [esi + 0xf8]
004b9a86  8b08                     mov        ecx, dword ptr [eax]
004b9a88  85c9                     test       ecx, ecx
004b9a8a  8bd9                     mov        ebx, ecx
004b9a8c  7503                     jne        0x4b9a91
004b9a8e  8d5808                   lea        ebx, [eax + 8]
004b9a91  db45fc                   fild       dword ptr [ebp - 4]
004b9a94  d84d10                   fmul       dword ptr [ebp + 0x10]
004b9a97  e8a87a7400               call       0xc01544
004b9a9c  8944bb1c                 mov        dword ptr [ebx + edi*4 + 0x1c], eax
004b9aa0  8b86f8000000             mov        eax, dword ptr [esi + 0xf8]
004b9aa6  8b08                     mov        ecx, dword ptr [eax]
004b9aa8  85c9                     test       ecx, ecx
004b9aaa  7503                     jne        0x4b9aaf
004b9aac  8d4808                   lea        ecx, [eax + 8]
004b9aaf  8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
004b9ab2  c744b928ffffffff         mov        dword ptr [ecx + edi*4 + 0x28], 0xffffffff
004b9aba  eb2e                     jmp        0x4b9aea
004b9abc  db4508                   fild       dword ptr [ebp + 8]
004b9abf  51                       push       ecx
004b9ac0  8b8ef8000000             mov        ecx, dword ptr [esi + 0xf8]
004b9ac6  d84d10                   fmul       dword ptr [ebp + 0x10]
004b9ac9  d91c24                   fstp       dword ptr [esp]
004b9acc  57                       push       edi
004b9acd  e86e750500               call       0x511040
004b9ad2  db45fc                   fild       dword ptr [ebp - 4]
004b9ad5  d84d10                   fmul       dword ptr [ebp + 0x10]
004b9ad8  e8677a7400               call       0xc01544
004b9add  8b8ef8000000             mov        ecx, dword ptr [esi + 0xf8]
004b9ae3  50                       push       eax
004b9ae4  57                       push       edi
004b9ae5  e8e6820500               call       0x511dd0
004b9aea  8a843704160000           mov        al, byte ptr [edi + esi + 0x1604]
004b9af1  84c0                     test       al, al
004b9af3  740c                     je         0x4b9b01
004b9af5  8b8ef8000000             mov        ecx, dword ptr [esi + 0xf8]
004b9afb  57                       push       edi
004b9afc  e86f720500               call       0x510d70
004b9b01  899cbe08160000           mov        dword ptr [esi + edi*4 + 0x1608], ebx
004b9b08  5f                       pop        edi
004b9b09  5e                       pop        esi
004b9b0a  5b                       pop        ebx
004b9b0b  8be5                     mov        esp, ebp
004b9b0d  5d                       pop        ebp
004b9b0e  c21000                   ret        0x10
