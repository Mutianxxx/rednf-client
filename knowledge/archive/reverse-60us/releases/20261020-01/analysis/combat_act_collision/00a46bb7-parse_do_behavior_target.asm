00a46bb7 8d9540ffffff             lea        edx, [ebp - 0xc0]
00a46bbd 685c74e400               push       0xe4745c
00a46bc2 52                       push       edx
00a46bc3 e808dc9bff               call       0x4047d0
00a46bc8 f6d8                     neg        al
00a46bca 56                       push       esi
00a46bcb 1bc0                     sbb        eax, eax
00a46bcd 83e031                   and        eax, 0x31
00a46bd0 898560ffffff             mov        dword ptr [ebp - 0xa0], eax
00a46bd6 8d45b4                   lea        eax, [ebp - 0x4c]
00a46bd9 50                       push       eax
00a46bda e8019cdeff               call       0x8307e0
00a46bdf 83c410                   add        esp, 0x10
00a46be2 84c0                     test       al, al
00a46be4 0f8470010000             je         0xa46d5a
00a46bea 8d4db4                   lea        ecx, [ebp - 0x4c]
00a46bed 685c2fe200               push       0xe22f5c
00a46bf2 51                       push       ecx
00a46bf3 e8d8db9bff               call       0x4047d0
00a46bf8 83c408                   add        esp, 8
00a46bfb 84c0                     test       al, al
00a46bfd 7414                     je         0xa46c13
00a46bff 8d55f0                   lea        edx, [ebp - 0x10]
00a46c02 52                       push       edx
00a46c03 8d4d84                   lea        ecx, [ebp - 0x7c]
00a46c06 897df0                   mov        dword ptr [ebp - 0x10], edi
00a46c09 e822050000               call       0xa47130
00a46c0e e915010000               jmp        0xa46d28
00a46c13 8d45b4                   lea        eax, [ebp - 0x4c]
00a46c16 68c88de400               push       0xe48dc8
00a46c1b 50                       push       eax
00a46c1c e8afdb9bff               call       0x4047d0
00a46c21 83c408                   add        esp, 8
00a46c24 84c0                     test       al, al
00a46c26 7418                     je         0xa46c40
00a46c28 8d4df0                   lea        ecx, [ebp - 0x10]
00a46c2b 51                       push       ecx
00a46c2c 8d4d84                   lea        ecx, [ebp - 0x7c]
00a46c2f c745f003000000           mov        dword ptr [ebp - 0x10], 3
00a46c36 e8f5040000               call       0xa47130
00a46c3b e9e8000000               jmp        0xa46d28
00a46c40 8d55b4                   lea        edx, [ebp - 0x4c]
00a46c43 689c8de400               push       0xe48d9c
00a46c48 52                       push       edx
00a46c49 e882db9bff               call       0x4047d0
00a46c4e 83c408                   add        esp, 8
00a46c51 84c0                     test       al, al
00a46c53 7418                     je         0xa46c6d
00a46c55 8d45f0                   lea        eax, [ebp - 0x10]
00a46c58 50                       push       eax
00a46c59 8d4d84                   lea        ecx, [ebp - 0x7c]
00a46c5c c745f004000000           mov        dword ptr [ebp - 0x10], 4
00a46c63 e8c8040000               call       0xa47130
00a46c68 e9bb000000               jmp        0xa46d28
00a46c6d 8d4db4                   lea        ecx, [ebp - 0x4c]
00a46c70 687c8de400               push       0xe48d7c
00a46c75 51                       push       ecx
00a46c76 e855db9bff               call       0x4047d0
00a46c7b 83c408                   add        esp, 8
00a46c7e 84c0                     test       al, al
00a46c80 7418                     je         0xa46c9a
00a46c82 8d55f0                   lea        edx, [ebp - 0x10]
00a46c85 52                       push       edx
00a46c86 8d4d84                   lea        ecx, [ebp - 0x7c]
00a46c89 c745f002000000           mov        dword ptr [ebp - 0x10], 2
00a46c90 e89b040000               call       0xa47130
00a46c95 e98e000000               jmp        0xa46d28
00a46c9a 8d45b4                   lea        eax, [ebp - 0x4c]
00a46c9d 68688de400               push       0xe48d68
00a46ca2 50                       push       eax
00a46ca3 e828db9bff               call       0x4047d0
00a46ca8 83c408                   add        esp, 8
00a46cab 84c0                     test       al, al
00a46cad 7414                     je         0xa46cc3
00a46caf 8d4df0                   lea        ecx, [ebp - 0x10]
00a46cb2 51                       push       ecx
00a46cb3 8d4d84                   lea        ecx, [ebp - 0x7c]
00a46cb6 8975f0                   mov        dword ptr [ebp - 0x10], esi
00a46cb9 e872040000               call       0xa47130
00a46cbe e965000000               jmp        0xa46d28
00a46cc3 8d55b4                   lea        edx, [ebp - 0x4c]
00a46cc6 68448de400               push       0xe48d44
00a46ccb 52                       push       edx
00a46ccc e8ffda9bff               call       0x4047d0
00a46cd1 83c408                   add        esp, 8
00a46cd4 84c0                     test       al, al
00a46cd6 0f85a3e8ffff             jne        0xa4557f
00a46cdc 8d4db4                   lea        ecx, [ebp - 0x4c]
00a46cdf 68b072e400               push       0xe472b0
00a46ce4 51                       push       ecx
00a46ce5 e8e6da9bff               call       0x4047d0
00a46cea 83c408                   add        esp, 8
00a46ced 84c0                     test       al, al
00a46cef 0f846d020000             je         0xa46f62
00a46cf5 8d55f0                   lea        edx, [ebp - 0x10]
00a46cf8 52                       push       edx
00a46cf9 8d4d84                   lea        ecx, [ebp - 0x7c]
00a46cfc c745f006000000           mov        dword ptr [ebp - 0x10], 6
00a46d03 e828040000               call       0xa47130
00a46d08 8d45d0                   lea        eax, [ebp - 0x30]
00a46d0b 50                       push       eax
00a46d0c e82f81ffff               call       0xa3ee40
00a46d11 8b4dd8                   mov        ecx, dword ptr [ebp - 0x28]
00a46d14 8b                       .byte      0x8b
00a46d15 55                       push       ebp
