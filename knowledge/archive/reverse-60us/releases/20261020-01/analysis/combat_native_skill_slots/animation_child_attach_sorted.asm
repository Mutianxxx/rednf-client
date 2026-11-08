00a29d70  55                       push       ebp
00a29d71  8bec                     mov        ebp, esp
00a29d73  83ec08                   sub        esp, 8
00a29d76  8b450c                   mov        eax, dword ptr [ebp + 0xc]
00a29d79  85c0                     test       eax, eax
00a29d7b  53                       push       ebx
00a29d7c  8bd9                     mov        ebx, ecx
00a29d7e  746d                     je         0xa29ded
00a29d80  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00a29d83  8945fc                   mov        dword ptr [ebp - 4], eax
00a29d86  8b8380010000             mov        eax, dword ptr [ebx + 0x180]
00a29d8c  56                       push       esi
00a29d8d  8b30                     mov        esi, dword ptr [eax]
00a29d8f  3bf0                     cmp        esi, eax
00a29d91  57                       push       edi
00a29d92  894df8                   mov        dword ptr [ebp - 8], ecx
00a29d95  740b                     je         0xa29da2
00a29d97  394e08                   cmp        dword ptr [esi + 8], ecx
00a29d9a  7f06                     jg         0xa29da2
00a29d9c  8b36                     mov        esi, dword ptr [esi]
00a29d9e  3bf0                     cmp        esi, eax
00a29da0  75f5                     jne        0xa29d97
00a29da2  8b5604                   mov        edx, dword ptr [esi + 4]
00a29da5  8d45f8                   lea        eax, [ebp - 8]
00a29da8  50                       push       eax
00a29da9  52                       push       edx
00a29daa  8d8b7c010000             lea        ecx, [ebx + 0x17c]
00a29db0  56                       push       esi
00a29db1  e89aa3adff               call       0x504150
00a29db6  6a01                     push       1
00a29db8  8d8b7c010000             lea        ecx, [ebx + 0x17c]
00a29dbe  8bf8                     mov        edi, eax
00a29dc0  e85b090000               call       0xa2a720
00a29dc5  897e04                   mov        dword ptr [esi + 4], edi
00a29dc8  8b4704                   mov        eax, dword ptr [edi + 4]
00a29dcb  8b750c                   mov        esi, dword ptr [ebp + 0xc]
00a29dce  8938                     mov        dword ptr [eax], edi
00a29dd0  8bce                     mov        ecx, esi
00a29dd2  899e88010000             mov        dword ptr [esi + 0x188], ebx
00a29dd8  e883d5ffff               call       0xa27360
00a29ddd  8b8b34010000             mov        ecx, dword ptr [ebx + 0x134]
00a29de3  51                       push       ecx
00a29de4  8bce                     mov        ecx, esi
00a29de6  e885feffff               call       0xa29c70
00a29deb  5f                       pop        edi
00a29dec  5e                       pop        esi
00a29ded  5b                       pop        ebx
00a29dee  8be5                     mov        esp, ebp
00a29df0  5d                       pop        ebp
00a29df1  c20800                   ret        8
