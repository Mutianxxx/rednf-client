00a2912b 3bf3                     cmp        esi, ebx
00a2912d 0f8457fdffff             je         0xa28e8a
00a29133 53                       push       ebx
00a29134 e82767e0ff               call       0x82f860
00a29139 d95e18                   fstp       dword ptr [esi + 0x18]
00a2913c 83c404                   add        esp, 4
00a2913f e946fdffff               jmp        0xa28e8a
00a29144 53                       push       ebx
00a29145 e88666e0ff               call       0x82f7d0
00a2914a 53                       push       ebx
00a2914b 8945b0                   mov        dword ptr [ebp - 0x50], eax
00a2914e e87d66e0ff               call       0x82f7d0
00a29153 53                       push       ebx
00a29154 8945d0                   mov        dword ptr [ebp - 0x30], eax
00a29157 e87466e0ff               call       0x82f7d0
00a2915c 53                       push       ebx
00a2915d 89450c                   mov        dword ptr [ebp + 0xc], eax
00a29160 e86b66e0ff               call       0x82f7d0
00a29165 83c410                   add        esp, 0x10
00a29168 3bf3                     cmp        esi, ebx
00a2916a 0f841afdffff             je         0xa28e8a
00a29170 0fb655d0                 movzx      edx, byte ptr [ebp - 0x30]
00a29174 33c9                     xor        ecx, ecx
00a29176 8ae8                     mov        ch, al
00a29178 0fb645b0                 movzx      eax, byte ptr [ebp - 0x50]
00a2917c 8a4d0c                   mov        cl, byte ptr [ebp + 0xc]
00a2917f c1e108                   shl        ecx, 8
00a29182 0bca                     or         ecx, edx
00a29184 c1e108                   shl        ecx, 8
00a29187 0bc8                     or         ecx, eax
00a29189 894e1c                   mov        dword ptr [esi + 0x1c], ecx
00a2918c e9f9fcffff               jmp        0xa28e8a
