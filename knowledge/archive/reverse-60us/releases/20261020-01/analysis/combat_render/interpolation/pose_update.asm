00a24950 55                       push       ebp
00a24951 8bec                     mov        ebp, esp
00a24953 83ec14                   sub        esp, 0x14
00a24956 56                       push       esi
00a24957 8bf1                     mov        esi, ecx
00a24959 8a86c8000000             mov        al, byte ptr [esi + 0xc8]
00a2495f 84c0                     test       al, al
00a24961 0f8444020000             je         0xa24bab
00a24967 80be3a01000001           cmp        byte ptr [esi + 0x13a], 1
00a2496e 0f8437020000             je         0xa24bab
00a24974 8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a2497a 85c0                     test       eax, eax
00a2497c 0f8429020000             je         0xa24bab
00a24982 8b8e9c000000             mov        ecx, dword ptr [esi + 0x9c]
00a24988 2bc8                     sub        ecx, eax
00a2498a b843082184               mov        eax, 0x84210843
00a2498f f7e9                     imul       ecx
00a24991 03d1                     add        edx, ecx
00a24993 c1fa06                   sar        edx, 6
00a24996 8bc2                     mov        eax, edx
00a24998 c1e81f                   shr        eax, 0x1f
00a2499b 03c2                     add        eax, edx
00a2499d 8945ec                   mov        dword ptr [ebp - 0x14], eax
00a249a0 0f8405020000             je         0xa24bab
00a249a6 8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a249ac 85c0                     test       eax, eax
00a249ae 741b                     je         0xa249cb
00a249b0 8b8e9c000000             mov        ecx, dword ptr [esi + 0x9c]
00a249b6 2bc8                     sub        ecx, eax
00a249b8 b843082184               mov        eax, 0x84210843
00a249bd f7e9                     imul       ecx
00a249bf 03d1                     add        edx, ecx
00a249c1 c1fa06                   sar        edx, 6
00a249c4 8bc2                     mov        eax, edx
00a249c6 c1e81f                   shr        eax, 0x1f
00a249c9 03c2                     add        eax, edx
00a249cb 53                       push       ebx
00a249cc 8b9e24010000             mov        ebx, dword ptr [esi + 0x124]
00a249d2 48                       dec        eax
00a249d3 3bd8                     cmp        ebx, eax
00a249d5 7519                     jne        0xa249f0
00a249d7 8a8630010000             mov        al, byte ptr [esi + 0x130]
00a249dd 84c0                     test       al, al
00a249df 0f84c5010000             je         0xa24baa
00a249e5 8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a249eb 8945fc                   mov        dword ptr [ebp - 4], eax
00a249ee eb11                     jmp        0xa24a01
00a249f0 8b8698000000             mov        eax, dword ptr [esi + 0x98]
00a249f6 8d4b01                   lea        ecx, [ebx + 1]
00a249f9 6bc97c                   imul       ecx, ecx, 0x7c
00a249fc 03c8                     add        ecx, eax
00a249fe 894dfc                   mov        dword ptr [ebp - 4], ecx
00a24a01 8b8e88010000             mov        ecx, dword ptr [esi + 0x188]
00a24a07 6bdb7c                   imul       ebx, ebx, 0x7c
00a24a0a 03d8                     add        ebx, eax
00a24a0c 85c9                     test       ecx, ecx
00a24a0e 7407                     je         0xa24a17
00a24a10 e8eb5faaff               call       0x4caa00
00a24a15 eb06                     jmp        0xa24a1d
00a24a17 8b868c000000             mov        eax, dword ptr [esi + 0x8c]
00a24a1d 8b8e28010000             mov        ecx, dword ptr [esi + 0x128]
00a24a23 57                       push       edi
00a24a24 8bbe2c010000             mov        edi, dword ptr [esi + 0x12c]
00a24a2a 2bc1                     sub        eax, ecx
00a24a2c 2bf9                     sub        edi, ecx
00a24a2e 8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00a24a31 8b5108                   mov        edx, dword ptr [ecx + 8]
00a24a34 57                       push       edi
00a24a35 50                       push       eax
00a24a36 8945f8                   mov        dword ptr [ebp - 8], eax
00a24a39 8b4308                   mov        eax, dword ptr [ebx + 8]
00a24a3c 52                       push       edx
00a24a3d 50                       push       eax
00a24a3e e8ddf4a4ff               call       0x473f20
00a24a43 8b4df8                   mov        ecx, dword ptr [ebp - 8]
00a24a46 8b55fc                   mov        edx, dword ptr [ebp - 4]
00a24a49 57                       push       edi
00a24a4a 8986b0000000             mov        dword ptr [esi + 0xb0], eax
00a24a50 8b420c                   mov        eax, dword ptr [edx + 0xc]
00a24a53 51                       push       ecx
00a24a54 8b4b0c                   mov        ecx, dword ptr [ebx + 0xc]
00a24a57 50                       push       eax
00a24a58 51                       push       ecx
00a24a59 e8c2f4a4ff               call       0x473f20
00a24a5e 8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00a24a61 83c110                   add        ecx, 0x10
00a24a64 8986b4000000             mov        dword ptr [esi + 0xb4], eax
00a24a6a 8b01                     mov        eax, dword ptr [ecx]
00a24a6c 8b15fc3e0d01             mov        edx, dword ptr [0x10d3efc]
00a24a72 2bc1                     sub        eax, ecx
00a24a74 8d4b10                   lea        ecx, [ebx + 0x10]
00a24a77 894df4                   mov        dword ptr [ebp - 0xc], ecx
00a24a7a 8b09                     mov        ecx, dword ptr [ecx]
00a24a7c 2b4df4                   sub        ecx, dword ptr [ebp - 0xc]
00a24a7f 33c2                     xor        eax, edx
00a24a81 33ca                     xor        ecx, edx
00a24a83 8b55f8                   mov        edx, dword ptr [ebp - 8]
00a24a86 57                       push       edi
00a24a87 52                       push       edx
00a24a88 50                       push       eax
00a24a89 51                       push       ecx
00a24a8a e8214f0e00               call       0xb099b0
00a24a8f d95df4                   fstp       dword ptr [ebp - 0xc]
00a24a92 8b15fc3e0d01             mov        edx, dword ptr [0x10d3efc]
00a24a98 8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a24a9b 33ca                     xor        ecx, edx
00a24a9d 8d86b8000000             lea        eax, [esi + 0xb8]
00a24aa3 03c8                     add        ecx, eax
00a24aa5 8908                     mov        dword ptr [eax], ecx
00a24aa7 8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00a24aaa 8b4114                   mov        eax, dword ptr [ecx + 0x14]
00a24aad 8b15fc3e0d01             mov        edx, dword ptr [0x10d3efc]
00a24ab3 83c114                   add        ecx, 0x14
00a24ab6 2bc1                     sub        eax, ecx
00a24ab8 8d4b14                   lea        ecx, [ebx + 0x14]
00a24abb 894df4                   mov        dword ptr [ebp - 0xc], ecx
00a24abe 8b09                     mov        ecx, dword ptr [ecx]
00a24ac0 2b4df4                   sub        ecx, dword ptr [ebp - 0xc]
00a24ac3 33c2                     xor        eax, edx
00a24ac5 33ca                     xor        ecx, edx
00a24ac7 8b55f8                   mov        edx, dword ptr [ebp - 8]
00a24aca 57                       push       edi
00a24acb 52                       push       edx
00a24acc 50                       push       eax
00a24acd 51                       push       ecx
00a24ace e8dd4e0e00               call       0xb099b0
00a24ad3 d95df4                   fstp       dword ptr [ebp - 0xc]
00a24ad6 8b15fc3e0d01             mov        edx, dword ptr [0x10d3efc]
00a24adc 8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a24adf 33ca                     xor        ecx, edx
00a24ae1 8b55f8                   mov        edx, dword ptr [ebp - 8]
00a24ae4 83c440                   add        esp, 0x40
00a24ae7 8d86bc000000             lea        eax, [esi + 0xbc]
00a24aed 03c8                     add        ecx, eax
00a24aef 8908                     mov        dword ptr [eax], ecx
00a24af1 8b45fc                   mov        eax, dword ptr [ebp - 4]
00a24af4 8b4818                   mov        ecx, dword ptr [eax + 0x18]
00a24af7 57                       push       edi
00a24af8 52                       push       edx
00a24af9 8b5318                   mov        edx, dword ptr [ebx + 0x18]
00a24afc 51                       push       ecx
00a24afd 52                       push       edx
00a24afe e8ad4e0e00               call       0xb099b0
00a24b03 d99ec0000000             fstp       dword ptr [esi + 0xc0]
00a24b09 8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00a24b0c 8b45f8                   mov        eax, dword ptr [ebp - 8]
00a24b0f 0fb6511c                 movzx      edx, byte ptr [ecx + 0x1c]
00a24b13 57                       push       edi
00a24b14 50                       push       eax
00a24b15 0fb6431c                 movzx      eax, byte ptr [ebx + 0x1c]
00a24b19 52                       push       edx
00a24b1a 50                       push       eax
00a24b1b e800f4a4ff               call       0x473f20
00a24b20 8b55fc                   mov        edx, dword ptr [ebp - 4]
00a24b23 8b4df8                   mov        ecx, dword ptr [ebp - 8]
00a24b26 57                       push       edi
00a24b27 8945ec                   mov        dword ptr [ebp - 0x14], eax
00a24b2a 0fb6421d                 movzx      eax, byte ptr [edx + 0x1d]
00a24b2e 51                       push       ecx
00a24b2f 0fb64b1d                 movzx      ecx, byte ptr [ebx + 0x1d]
00a24b33 50                       push       eax
00a24b34 51                       push       ecx
00a24b35 e8e6f3a4ff               call       0x473f20
00a24b3a 8b55f8                   mov        edx, dword ptr [ebp - 8]
00a24b3d 8945f0                   mov        dword ptr [ebp - 0x10], eax
00a24b40 8b45fc                   mov        eax, dword ptr [ebp - 4]
00a24b43 0fb6481e                 movzx      ecx, byte ptr [eax + 0x1e]
00a24b47 57                       push       edi
00a24b48 52                       push       edx
00a24b49 0fb6531e                 movzx      edx, byte ptr [ebx + 0x1e]
00a24b4d 51                       push       ecx
00a24b4e 52                       push       edx
00a24b4f e8ccf3a4ff               call       0x473f20
00a24b54 8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00a24b57 0fb6511f                 movzx      edx, byte ptr [ecx + 0x1f]
00a24b5b 83c440                   add        esp, 0x40
00a24b5e 8945f4                   mov        dword ptr [ebp - 0xc], eax
00a24b61 8b45f8                   mov        eax, dword ptr [ebp - 8]
00a24b64 57                       push       edi
00a24b65 50                       push       eax
00a24b66 0fb6431f                 movzx      eax, byte ptr [ebx + 0x1f]
00a24b6a 52                       push       edx
00a24b6b 50                       push       eax
00a24b6c e8aff3a4ff               call       0x473f20
00a24b71 0fb655f0                 movzx      edx, byte ptr [ebp - 0x10]
00a24b75 d986c0000000             fld        dword ptr [esi + 0xc0]
00a24b7b 33c9                     xor        ecx, ecx
00a24b7d 8ae8                     mov        ch, al
00a24b7f 0fb645ec                 movzx      eax, byte ptr [ebp - 0x14]
00a24b83 83c410                   add        esp, 0x10
00a24b86 5f                       pop        edi
00a24b87 8a4df4                   mov        cl, byte ptr [ebp - 0xc]
00a24b8a c1e108                   shl        ecx, 8
00a24b8d 0bca                     or         ecx, edx
00a24b8f c1e108                   shl        ecx, 8
00a24b92 0bc8                     or         ecx, eax
00a24b94 898ec4000000             mov        dword ptr [esi + 0xc4], ecx
00a24b9a d86318                   fsub       dword ptr [ebx + 0x18]
00a24b9d c7863c01000000000000     mov        dword ptr [esi + 0x13c], 0
00a24ba7 d95e2c                   fstp       dword ptr [esi + 0x2c]
00a24baa 5b                       pop        ebx
00a24bab 5e                       pop        esi
00a24bac 8be5                     mov        esp, ebp
00a24bae 5d                       pop        ebp
00a24baf c3                       ret        
