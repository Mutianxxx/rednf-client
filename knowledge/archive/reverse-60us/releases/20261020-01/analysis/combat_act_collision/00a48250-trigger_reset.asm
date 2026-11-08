00a48250 56                       push       esi
00a48251 57                       push       edi
00a48252 8bf9                     mov        edi, ecx
00a48254 8b7704                   mov        esi, dword ptr [edi + 4]
00a48257 85f6                     test       esi, esi
00a48259 742e                     je         0xa48289
00a4825b 53                       push       ebx
00a4825c 8b5f08                   mov        ebx, dword ptr [edi + 8]
00a4825f 3bf3                     cmp        esi, ebx
00a48261 740e                     je         0xa48271
00a48263 8bce                     mov        ecx, esi
00a48265 e8c6a0a5ff               call       0x4a2330
00a4826a 83c634                   add        esi, 0x34
00a4826d 3bf3                     cmp        esi, ebx
00a4826f 75f2                     jne        0xa48263
00a48271 8b4704                   mov        eax, dword ptr [edi + 4]
00a48274 50                       push       eax
00a48275 e88f7e1b00               call       0xc00109
00a4827a 83c404                   add        esp, 4
00a4827d 33c0                     xor        eax, eax
00a4827f 89470c                   mov        dword ptr [edi + 0xc], eax
00a48282 894708                   mov        dword ptr [edi + 8], eax
00a48285 894704                   mov        dword ptr [edi + 4], eax
00a48288 5b                       pop        ebx
00a48289 33c0                     xor        eax, eax
00a4828b 894710                   mov        dword ptr [edi + 0x10], eax
00a4828e 894714                   mov        dword ptr [edi + 0x14], eax
00a48291 884719                   mov        byte ptr [edi + 0x19], al
00a48294 c6471801                 mov        byte ptr [edi + 0x18], 1
00a48298 5f                       pop        edi
00a48299 5e                       pop        esi
00a4829a c3                       ret        
