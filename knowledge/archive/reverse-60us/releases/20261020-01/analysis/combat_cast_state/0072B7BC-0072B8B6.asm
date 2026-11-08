0072b7bc  6a01                     push       1
0072b7be  6a01                     push       1
0072b7c0  6a01                     push       1
0072b7c2  6a20                     push       0x20
0072b7c4  8bce                     mov        ecx, esi
0072b7c6  ff9068070000             call       dword ptr [eax + 0x768]
0072b7cc  84c0                     test       al, al
0072b7ce  0f84f4000000             je         0x72b8c8
0072b7d4  899d10ffffff             mov        dword ptr [ebp - 0xf0], ebx
0072b7da  899d14ffffff             mov        dword ptr [ebp - 0xec], ebx
0072b7e0  899d18ffffff             mov        dword ptr [ebp - 0xe8], ebx
0072b7e6  8d4dec                   lea        ecx, [ebp - 0x14]
0072b7e9  51                       push       ecx
0072b7ea  8d8d0cffffff             lea        ecx, [ebp - 0xf4]
0072b7f0  c745fc26000000           mov        dword ptr [ebp - 4], 0x26
0072b7f7  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072b7fa  e821b9cdff               call       0x407120
0072b7ff  8d55ec                   lea        edx, [ebp - 0x14]
0072b802  52                       push       edx
0072b803  8d8d0cffffff             lea        ecx, [ebp - 0xf4]
0072b809  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072b80c  e80fb9cdff               call       0x407120
0072b811  8d45ec                   lea        eax, [ebp - 0x14]
0072b814  50                       push       eax
0072b815  8d8d0cffffff             lea        ecx, [ebp - 0xf4]
0072b81b  c745ec20000000           mov        dword ptr [ebp - 0x14], 0x20
0072b822  e8f9b8cdff               call       0x407120
0072b827  8d4dec                   lea        ecx, [ebp - 0x14]
0072b82a  51                       push       ecx
0072b82b  8d8d0cffffff             lea        ecx, [ebp - 0xf4]
0072b831  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072b834  e8e7b8cdff               call       0x407120
0072b839  8b16                     mov        edx, dword ptr [esi]
0072b83b  56                       push       esi
0072b83c  53                       push       ebx
0072b83d  6a20                     push       0x20
0072b83f  8bce                     mov        ecx, esi
0072b841  ff927c060000             call       dword ptr [edx + 0x67c]
0072b847  8bc8                     mov        ecx, eax
0072b849  e81247e2ff               call       0x54ff60
0072b84e  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072b851  8d45ec                   lea        eax, [ebp - 0x14]
0072b854  50                       push       eax
0072b855  8d8d0cffffff             lea        ecx, [ebp - 0xf4]
0072b85b  e8c0b8cdff               call       0x407120
0072b860  8d4dec                   lea        ecx, [ebp - 0x14]
0072b863  51                       push       ecx
0072b864  8d8d0cffffff             lea        ecx, [ebp - 0xf4]
0072b86a  c745ec01000000           mov        dword ptr [ebp - 0x14], 1
0072b871  e8aab8cdff               call       0x407120
0072b876  8d55ec                   lea        edx, [ebp - 0x14]
0072b879  bf04000000               mov        edi, 4
0072b87e  52                       push       edx
0072b87f  8d8d0cffffff             lea        ecx, [ebp - 0xf4]
0072b885  897dec                   mov        dword ptr [ebp - 0x14], edi
0072b888  e893b8cdff               call       0x407120
0072b88d  8d45ec                   lea        eax, [ebp - 0x14]
0072b890  50                       push       eax
0072b891  8d8d0cffffff             lea        ecx, [ebp - 0xf4]
0072b897  897dec                   mov        dword ptr [ebp - 0x14], edi
0072b89a  e881b8cdff               call       0x407120
0072b89f  8b16                     mov        edx, dword ptr [esi]
0072b8a1  53                       push       ebx
0072b8a2  53                       push       ebx
0072b8a3  6a01                     push       1
0072b8a5  8d850cffffff             lea        eax, [ebp - 0xf4]
0072b8ab  50                       push       eax
0072b8ac  6a0a                     push       0xa
0072b8ae  8bce                     mov        ecx, esi
0072b8b0  ff928c020000             call       dword ptr [edx + 0x28c]