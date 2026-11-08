006f29c0  cb                       retf       
006f29c1  e89af6d0ff               call       0x402060
006f29c6  85c0                     test       eax, eax
006f29c8  7428                     je         0x6f29f2
006f29ca  8bcb                     mov        ecx, ebx
006f29cc  e88ff6d0ff               call       0x402060
006f29d1  83f80b                   cmp        eax, 0xb
006f29d4  741c                     je         0x6f29f2
006f29d6  8bcb                     mov        ecx, ebx
006f29d8  e883f6d0ff               call       0x402060
006f29dd  83f808                   cmp        eax, 8
006f29e0  7410                     je         0x6f29f2
006f29e2  8bcb                     mov        ecx, ebx
006f29e4  e877f6d0ff               call       0x402060
006f29e9  83f816                   cmp        eax, 0x16
006f29ec  0f85a5000000             jne        0x6f2a97
006f29f2  8b16                     mov        edx, dword ptr [esi]
006f29f4  57                       push       edi
006f29f5  6a0c                     push       0xc
006f29f7  8bce                     mov        ecx, esi
006f29f9  ff923c070000             call       dword ptr [edx + 0x73c]
006f29ff  8bc8                     mov        ecx, eax
006f2a01  e83a67e6ff               call       0x559140
006f2a06  83f8ff                   cmp        eax, -1
006f2a09  0f8488000000             je         0x6f2a97
006f2a0f  8b06                     mov        eax, dword ptr [esi]
006f2a11  6a01                     push       1
006f2a13  6a01                     push       1
006f2a15  6a01                     push       1
006f2a17  6a0c                     push       0xc
006f2a19  8bce                     mov        ecx, esi
006f2a1b  ff9068070000             call       dword ptr [eax + 0x768]
006f2a21  84c0                     test       al, al
006f2a23  7472                     je         0x6f2a97
006f2a25  89bd94feffff             mov        dword ptr [ebp - 0x16c], edi
006f2a2b  89bd98feffff             mov        dword ptr [ebp - 0x168], edi
006f2a31  89bd9cfeffff             mov        dword ptr [ebp - 0x164], edi
006f2a37  8d4dec                   lea        ecx, [ebp - 0x14]
006f2a3a  51                       push       ecx
006f2a3b  8d8d90feffff             lea        ecx, [ebp - 0x170]
006f2a41  c745fc51000000           mov        dword ptr [ebp - 4], 0x51
006f2a48  c745ec0c000000           mov        dword ptr [ebp - 0x14], 0xc
006f2a4f  e8cc46d1ff               call       0x407120
006f2a54  8b16                     mov        edx, dword ptr [esi]
006f2a56  57                       push       edi
006f2a57  57                       push       edi
006f2a58  6a01                     push       1
006f2a5a  8d8590feffff             lea        eax, [ebp - 0x170]
006f2a60  50                       push       eax
006f2a61  6a17                     push       0x17
006f2a63  8bce                     mov        ecx, esi
006f2a65  ff928c020000             call       dword ptr [edx + 0x28c]
006f2a6b  8b8594feffff             mov        eax, dword ptr [ebp - 0x16c]
006f2a71  3bc7                     cmp        eax, edi
006f2a73  c745fcffffffff           mov        dword ptr [ebp - 4], 0xffffffff
006f2a7a  7409                     je         0x6f2a85
006f2a7c  50                       push       eax
006f2a7d  e85bd55000               call       0xbfffdd
006f2a82  83c404                   add        esp, 4
006f2a85  89bd94feffff             mov        dword ptr [ebp - 0x16c], edi
006f2a8b  89bd98feffff             mov        dword ptr [ebp - 0x168], edi
006f2a91  89bd9cfeffff             mov        dword ptr [ebp - 0x164], edi