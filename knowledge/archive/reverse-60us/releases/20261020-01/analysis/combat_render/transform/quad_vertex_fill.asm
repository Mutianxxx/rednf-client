00b08d30 55                       push       ebp
00b08d31 8bec                     mov        ebp, esp
00b08d33 83ec60                   sub        esp, 0x60
00b08d36 53                       push       ebx
00b08d37 8bd9                     mov        ebx, ecx
00b08d39 8a8338030500             mov        al, byte ptr [ebx + 0x50338]
00b08d3f 84c0                     test       al, al
00b08d41 56                       push       esi
00b08d42 57                       push       edi
00b08d43 0f8513030000             jne        0xb0905c
00b08d49 8b4508                   mov        eax, dword ptr [ebp + 8]
00b08d4c 33ff                     xor        edi, edi
00b08d4e 3bc7                     cmp        eax, edi
00b08d50 0f8406030000             je         0xb0905c
00b08d56 8b08                     mov        ecx, dword ptr [eax]
00b08d58 8d55a0                   lea        edx, [ebp - 0x60]
00b08d5b 52                       push       edx
00b08d5c 57                       push       edi
00b08d5d 50                       push       eax
00b08d5e ff5138                   call       dword ptr [ecx + 0x38]
00b08d61 db45b8                   fild       dword ptr [ebp - 0x48]
00b08d64 8b45b8                   mov        eax, dword ptr [ebp - 0x48]
00b08d67 85c0                     test       eax, eax
00b08d69 7d06                     jge        0xb08d71
00b08d6b d805cc46cc00             fadd       dword ptr [0xcc46cc]
00b08d71 8b4dbc                   mov        ecx, dword ptr [ebp - 0x44]
00b08d74 d95de8                   fstp       dword ptr [ebp - 0x18]
00b08d77 85c9                     test       ecx, ecx
00b08d79 db45bc                   fild       dword ptr [ebp - 0x44]
00b08d7c 7d06                     jge        0xb08d84
00b08d7e d805cc46cc00             fadd       dword ptr [0xcc46cc]
00b08d84 8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00b08d87 d95dec                   fstp       dword ptr [ebp - 0x14]
00b08d8a 3bcf                     cmp        ecx, edi
00b08d8c 745f                     je         0xb08ded
00b08d8e 8b4108                   mov        eax, dword ptr [ecx + 8]
00b08d91 8b11                     mov        edx, dword ptr [ecx]
00b08d93 8945e4                   mov        dword ptr [ebp - 0x1c], eax
00b08d96 2bc2                     sub        eax, edx
00b08d98 8945dc                   mov        dword ptr [ebp - 0x24], eax
00b08d9b 8b410c                   mov        eax, dword ptr [ecx + 0xc]
00b08d9e db45dc                   fild       dword ptr [ebp - 0x24]
00b08da1 89550c                   mov        dword ptr [ebp + 0xc], edx
00b08da4 8b5104                   mov        edx, dword ptr [ecx + 4]
00b08da7 8945f0                   mov        dword ptr [ebp - 0x10], eax
00b08daa 2bc2                     sub        eax, edx
00b08dac 8945d8                   mov        dword ptr [ebp - 0x28], eax
00b08daf db45d8                   fild       dword ptr [ebp - 0x28]
00b08db2 8955e0                   mov        dword ptr [ebp - 0x20], edx
00b08db5 d905581fcc00             fld        dword ptr [0xcc1f58]
00b08dbb d875e8                   fdiv       dword ptr [ebp - 0x18]
00b08dbe db450c                   fild       dword ptr [ebp + 0xc]
00b08dc1 d8c9                     fmul       st(1)
00b08dc3 d95dc8                   fstp       dword ptr [ebp - 0x38]
00b08dc6 d905581fcc00             fld        dword ptr [0xcc1f58]
00b08dcc d875ec                   fdiv       dword ptr [ebp - 0x14]
00b08dcf db45e0                   fild       dword ptr [ebp - 0x20]
00b08dd2 d8c9                     fmul       st(1)
00b08dd4 d95dcc                   fstp       dword ptr [ebp - 0x34]
00b08dd7 db45e4                   fild       dword ptr [ebp - 0x1c]
00b08dda d8ca                     fmul       st(2)
00b08ddc d95dd0                   fstp       dword ptr [ebp - 0x30]
00b08ddf db45f0                   fild       dword ptr [ebp - 0x10]
00b08de2 d8c9                     fmul       st(1)
00b08de4 d95dd4                   fstp       dword ptr [ebp - 0x2c]
00b08de7 ddd8                     fstp       st(0)
00b08de9 ddd8                     fstp       st(0)
00b08deb eb22                     jmp        0xb08e0f
00b08ded d945e8                   fld        dword ptr [ebp - 0x18]
00b08df0 c745c800000000           mov        dword ptr [ebp - 0x38], 0
00b08df7 d945ec                   fld        dword ptr [ebp - 0x14]
00b08dfa c745cc00000000           mov        dword ptr [ebp - 0x34], 0
00b08e01 c745d00000803f           mov        dword ptr [ebp - 0x30], 0x3f800000
00b08e08 c745d40000803f           mov        dword ptr [ebp - 0x2c], 0x3f800000
00b08e0f d9c0                     fld        st(0)
00b08e11 8b4514                   mov        eax, dword ptr [ebp + 0x14]
00b08e14 d84810                   fmul       dword ptr [eax + 0x10]
00b08e17 d900                     fld        dword ptr [eax]
00b08e19 d80da4d7e900             fmul       dword ptr [0xe9d7a4]
00b08e1f d9c1                     fld        st(1)
00b08e21 d8c1                     fadd       st(1)
00b08e23 d84030                   fadd       dword ptr [eax + 0x30]
00b08e26 d95d0c                   fstp       dword ptr [ebp + 0xc]
00b08e29 d9ca                     fxch       st(2)
00b08e2b d84814                   fmul       dword ptr [eax + 0x14]
00b08e2e d95de8                   fstp       dword ptr [ebp - 0x18]
00b08e31 d94004                   fld        dword ptr [eax + 4]
00b08e34 d80da4d7e900             fmul       dword ptr [0xe9d7a4]
00b08e3a d945e8                   fld        dword ptr [ebp - 0x18]
00b08e3d d8c1                     fadd       st(1)
00b08e3f d84034                   fadd       dword ptr [eax + 0x34]
00b08e42 d95d14                   fstp       dword ptr [ebp + 0x14]
00b08e45 d94010                   fld        dword ptr [eax + 0x10]
00b08e48 d80da4d7e900             fmul       dword ptr [0xe9d7a4]
00b08e4e d955e4                   fst        dword ptr [ebp - 0x1c]
00b08e51 d8c3                     fadd       st(3)
00b08e53 d84030                   fadd       dword ptr [eax + 0x30]
00b08e56 d95dfc                   fstp       dword ptr [ebp - 4]
00b08e59 d94014                   fld        dword ptr [eax + 0x14]
00b08e5c d80da4d7e900             fmul       dword ptr [0xe9d7a4]
00b08e62 d955e0                   fst        dword ptr [ebp - 0x20]
00b08e65 d8c1                     fadd       st(1)
00b08e67 d84034                   fadd       dword ptr [eax + 0x34]
00b08e6a d95df8                   fstp       dword ptr [ebp - 8]
00b08e6d ddd8                     fstp       st(0)
00b08e6f ddd9                     fstp       st(1)
00b08e71 d9c1                     fld        st(1)
00b08e73 d808                     fmul       dword ptr [eax]
00b08e75 d955ec                   fst        dword ptr [ebp - 0x14]
00b08e78 d8c1                     fadd       st(1)
00b08e7a d84030                   fadd       dword ptr [eax + 0x30]
00b08e7d d95df4                   fstp       dword ptr [ebp - 0xc]
00b08e80 ddd8                     fstp       st(0)
00b08e82 d84804                   fmul       dword ptr [eax + 4]
00b08e85 d945e8                   fld        dword ptr [ebp - 0x18]
00b08e88 d8c1                     fadd       st(1)
00b08e8a d84034                   fadd       dword ptr [eax + 0x34]
00b08e8d d95df0                   fstp       dword ptr [ebp - 0x10]
00b08e90 d945ec                   fld        dword ptr [ebp - 0x14]
00b08e93 d845e4                   fadd       dword ptr [ebp - 0x1c]
00b08e96 d84030                   fadd       dword ptr [eax + 0x30]
00b08e99 d95dec                   fstp       dword ptr [ebp - 0x14]
00b08e9c d845e0                   fadd       dword ptr [ebp - 0x20]
00b08e9f d84034                   fadd       dword ptr [eax + 0x34]
00b08ea2 803b01                   cmp        byte ptr [ebx], 1
00b08ea5 d95de8                   fstp       dword ptr [ebp - 0x18]
00b08ea8 0f8534040000             jne        0xb092e2
00b08eae 3bcf                     cmp        ecx, edi
00b08eb0 0f84b4010000             je         0xb0906a
00b08eb6 8b4ddc                   mov        ecx, dword ptr [ebp - 0x24]
00b08eb9 b80e000000               mov        eax, 0xe
00b08ebe 3bc8                     cmp        ecx, eax
00b08ec0 0f85a4010000             jne        0xb0906a
00b08ec6 3945d8                   cmp        dword ptr [ebp - 0x28], eax
00b08ec9 0f859b010000             jne        0xb0906a
00b08ecf 8b5320                   mov        edx, dword ptr [ebx + 0x20]
00b08ed2 8b4308                   mov        eax, dword ptr [ebx + 8]
00b08ed5 42                       inc        edx
00b08ed6 3d401f0000               cmp        eax, 0x1f40
00b08edb 895320                   mov        dword ptr [ebx + 0x20], edx
00b08ede 7d1a                     jge        0xb08efa
00b08ee0 8b4b10                   mov        ecx, dword ptr [ebx + 0x10]
00b08ee3 6bc070                   imul       eax, eax, 0x70
00b08ee6 8b11                     mov        edx, dword ptr [ecx]
00b08ee8 6800100000               push       0x1000
00b08eed 8d7328                   lea        esi, [ebx + 0x28]
00b08ef0 56                       push       esi
00b08ef1 6a70                     push       0x70
00b08ef3 50                       push       eax
00b08ef4 51                       push       ecx
00b08ef5 ff522c                   call       dword ptr [edx + 0x2c]
00b08ef8 eb22                     jmp        0xb08f1c
00b08efa 8bcb                     mov        ecx, ebx
00b08efc e80ff8ffff               call       0xb08710
00b08f01 8b4310                   mov        eax, dword ptr [ebx + 0x10]
00b08f04 6800200000               push       0x2000
00b08f09 8d7328                   lea        esi, [ebx + 0x28]
00b08f0c 56                       push       esi
00b08f0d 6a70                     push       0x70
00b08f0f 57                       push       edi
00b08f10 897b08                   mov        dword ptr [ebx + 8], edi
00b08f13 897b04                   mov        dword ptr [ebx + 4], edi
00b08f16 8b08                     mov        ecx, dword ptr [eax]
00b08f18 50                       push       eax
00b08f19 ff512c                   call       dword ptr [ecx + 0x2c]
00b08f1c 3bc7                     cmp        eax, edi
00b08f1e db4320                   fild       dword ptr [ebx + 0x20]
00b08f21 d80d58dce600             fmul       dword ptr [0xe6dc58]
00b08f27 d82d5cdce600             fsubr      dword ptr [0xe6dc5c]
00b08f2d 0f85c1050000             jne        0xb094f4
00b08f33 8b16                     mov        edx, dword ptr [esi]
00b08f35 d9450c                   fld        dword ptr [ebp + 0xc]
00b08f38 d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b08f3e 8b7dc8                   mov        edi, dword ptr [ebp - 0x38]
00b08f41 d91a                     fstp       dword ptr [edx]
00b08f43 8b06                     mov        eax, dword ptr [esi]
00b08f45 d94514                   fld        dword ptr [ebp + 0x14]
00b08f48 d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b08f4e d95804                   fstp       dword ptr [eax + 4]
00b08f51 8b0e                     mov        ecx, dword ptr [esi]
00b08f53 b80000803f               mov        eax, 0x3f800000
00b08f58 d95108                   fst        dword ptr [ecx + 8]
00b08f5b 8b16                     mov        edx, dword ptr [esi]
00b08f5d 89420c                   mov        dword ptr [edx + 0xc], eax
00b08f60 d945fc                   fld        dword ptr [ebp - 4]
00b08f63 8b16                     mov        edx, dword ptr [esi]
00b08f65 d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b08f6b 8b4d18                   mov        ecx, dword ptr [ebp + 0x18]
00b08f6e 894a10                   mov        dword ptr [edx + 0x10], ecx
00b08f71 8b16                     mov        edx, dword ptr [esi]
00b08f73 897a14                   mov        dword ptr [edx + 0x14], edi
00b08f76 8b16                     mov        edx, dword ptr [esi]
00b08f78 8b7dd4                   mov        edi, dword ptr [ebp - 0x2c]
00b08f7b 897a18                   mov        dword ptr [edx + 0x18], edi
00b08f7e 8b16                     mov        edx, dword ptr [esi]
00b08f80 d95a1c                   fstp       dword ptr [edx + 0x1c]
00b08f83 8b16                     mov        edx, dword ptr [esi]
00b08f85 d945f8                   fld        dword ptr [ebp - 8]
00b08f88 8b7dc8                   mov        edi, dword ptr [ebp - 0x38]
00b08f8b d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b08f91 d95a20                   fstp       dword ptr [edx + 0x20]
00b08f94 8b16                     mov        edx, dword ptr [esi]
00b08f96 d95224                   fst        dword ptr [edx + 0x24]
00b08f99 8b16                     mov        edx, dword ptr [esi]
00b08f9b 894228                   mov        dword ptr [edx + 0x28], eax
00b08f9e d945f4                   fld        dword ptr [ebp - 0xc]
00b08fa1 8b16                     mov        edx, dword ptr [esi]
00b08fa3 d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b08fa9 894a2c                   mov        dword ptr [edx + 0x2c], ecx
00b08fac 8b16                     mov        edx, dword ptr [esi]
00b08fae 897a30                   mov        dword ptr [edx + 0x30], edi
00b08fb1 8b16                     mov        edx, dword ptr [esi]
00b08fb3 8b7dcc                   mov        edi, dword ptr [ebp - 0x34]
00b08fb6 897a34                   mov        dword ptr [edx + 0x34], edi
00b08fb9 8b16                     mov        edx, dword ptr [esi]
00b08fbb d95a38                   fstp       dword ptr [edx + 0x38]
00b08fbe 8b16                     mov        edx, dword ptr [esi]
00b08fc0 d945f0                   fld        dword ptr [ebp - 0x10]
00b08fc3 8b7dd0                   mov        edi, dword ptr [ebp - 0x30]
00b08fc6 d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b08fcc d95a3c                   fstp       dword ptr [edx + 0x3c]
00b08fcf 8b16                     mov        edx, dword ptr [esi]
00b08fd1 d95240                   fst        dword ptr [edx + 0x40]
00b08fd4 8b16                     mov        edx, dword ptr [esi]
00b08fd6 d945ec                   fld        dword ptr [ebp - 0x14]
00b08fd9 894244                   mov        dword ptr [edx + 0x44], eax
00b08fdc 8b16                     mov        edx, dword ptr [esi]
00b08fde d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b08fe4 894a48                   mov        dword ptr [edx + 0x48], ecx
00b08fe7 8b16                     mov        edx, dword ptr [esi]
00b08fe9 897a4c                   mov        dword ptr [edx + 0x4c], edi
00b08fec 8b16                     mov        edx, dword ptr [esi]
00b08fee 8b7dd4                   mov        edi, dword ptr [ebp - 0x2c]
00b08ff1 897a50                   mov        dword ptr [edx + 0x50], edi
00b08ff4 8b16                     mov        edx, dword ptr [esi]
00b08ff6 d95a54                   fstp       dword ptr [edx + 0x54]
00b08ff9 8b16                     mov        edx, dword ptr [esi]
00b08ffb d945e8                   fld        dword ptr [ebp - 0x18]
00b08ffe d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b09004 d95a58                   fstp       dword ptr [edx + 0x58]
00b09007 8b16                     mov        edx, dword ptr [esi]
00b09009 d95a5c                   fstp       dword ptr [edx + 0x5c]
00b0900c 8b16                     mov        edx, dword ptr [esi]
00b0900e 894260                   mov        dword ptr [edx + 0x60], eax
00b09011 8b06                     mov        eax, dword ptr [esi]
00b09013 8b55d0                   mov        edx, dword ptr [ebp - 0x30]
00b09016 894864                   mov        dword ptr [eax + 0x64], ecx
00b09019 8b0e                     mov        ecx, dword ptr [esi]
00b0901b 895168                   mov        dword ptr [ecx + 0x68], edx
00b0901e 8b06                     mov        eax, dword ptr [esi]
00b09020 8b4dcc                   mov        ecx, dword ptr [ebp - 0x34]
00b09023 89486c                   mov        dword ptr [eax + 0x6c], ecx
00b09026 8b4310                   mov        eax, dword ptr [ebx + 0x10]
00b09029 8b10                     mov        edx, dword ptr [eax]
00b0902b 50                       push       eax
00b0902c ff5230                   call       dword ptr [edx + 0x30]
00b0902f 8b7508                   mov        esi, dword ptr [ebp + 8]
00b09032 8b06                     mov        eax, dword ptr [esi]
00b09034 56                       push       esi
00b09035 ff5004                   call       dword ptr [eax + 4]
00b09038 8b4b08                   mov        ecx, dword ptr [ebx + 8]
00b0903b 51                       push       ecx
00b0903c 56                       push       esi
00b0903d 8bcb                     mov        ecx, ebx
00b0903f e8dcf0ffff               call       0xb08120
00b09044 85c0                     test       eax, eax
00b09046 7511                     jne        0xb09059
00b09048 e8c3f6ffff               call       0xb08710
00b0904d 8b5308                   mov        edx, dword ptr [ebx + 8]
00b09050 52                       push       edx
00b09051 56                       push       esi
00b09052 8bcb                     mov        ecx, ebx
00b09054 e8c7f0ffff               call       0xb08120
00b09059 ff4308                   inc        dword ptr [ebx + 8]
00b0905c 5f                       pop        edi
00b0905d 5e                       pop        esi
00b0905e b801000000               mov        eax, 1
00b09063 5b                       pop        ebx
00b09064 8be5                     mov        esp, ebp
00b09066 5d                       pop        ebp
00b09067 c21800                   ret        0x18
00b0906a 837da019                 cmp        dword ptr [ebp - 0x60], 0x19
00b0906e 8b7d18                   mov        edi, dword ptr [ebp + 0x18]
00b09071 7523                     jne        0xb09096
00b09073 8b8348030500             mov        eax, dword ptr [ebx + 0x50348]
00b09079 0b834c030500             or         eax, dword ptr [ebx + 0x5034c]
00b0907f 7515                     jne        0xb09096
00b09081 83ffff                   cmp        edi, -1
00b09084 7510                     jne        0xb09096
00b09086 8a451c                   mov        al, byte ptr [ebp + 0x1c]
00b09089 84c0                     test       al, al
00b0908b 7509                     jne        0xb09096
00b0908d ff4320                   inc        dword ptr [ebx + 0x20]
00b09090 c6451f00                 mov        byte ptr [ebp + 0x1f], 0
00b09094 eb04                     jmp        0xb0909a
00b09096 c6451f01                 mov        byte ptr [ebp + 0x1f], 1
00b0909a 8b4308                   mov        eax, dword ptr [ebx + 8]
00b0909d 3d401f0000               cmp        eax, 0x1f40
00b090a2 7d17                     jge        0xb090bb
00b090a4 8b4b10                   mov        ecx, dword ptr [ebx + 0x10]
00b090a7 6bc070                   imul       eax, eax, 0x70
00b090aa 8b11                     mov        edx, dword ptr [ecx]
00b090ac 6800100000               push       0x1000
00b090b1 8d7328                   lea        esi, [ebx + 0x28]
00b090b4 56                       push       esi
00b090b5 6a70                     push       0x70
00b090b7 50                       push       eax
00b090b8 51                       push       ecx
00b090b9 eb21                     jmp        0xb090dc
00b090bb 8bcb                     mov        ecx, ebx
00b090bd e84ef6ffff               call       0xb08710
00b090c2 8b4310                   mov        eax, dword ptr [ebx + 0x10]
00b090c5 6800200000               push       0x2000
00b090ca 8d7328                   lea        esi, [ebx + 0x28]
00b090cd 56                       push       esi
00b090ce 33c9                     xor        ecx, ecx
00b090d0 6a70                     push       0x70
00b090d2 51                       push       ecx
00b090d3 894b08                   mov        dword ptr [ebx + 8], ecx
00b090d6 894b04                   mov        dword ptr [ebx + 4], ecx
00b090d9 8b10                     mov        edx, dword ptr [eax]
00b090db 50                       push       eax
00b090dc ff522c                   call       dword ptr [edx + 0x2c]
00b090df db4320                   fild       dword ptr [ebx + 0x20]
00b090e2 85c0                     test       eax, eax
00b090e4 d80d58dce600             fmul       dword ptr [0xe6dc58]
00b090ea d82d5cdce600             fsubr      dword ptr [0xe6dc5c]
00b090f0 0f85fe030000             jne        0xb094f4
00b090f6 8b06                     mov        eax, dword ptr [esi]
00b090f8 d9450c                   fld        dword ptr [ebp + 0xc]
00b090fb d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b09101 d918                     fstp       dword ptr [eax]
00b09103 8b0e                     mov        ecx, dword ptr [esi]
00b09105 d94514                   fld        dword ptr [ebp + 0x14]
00b09108 b80000803f               mov        eax, 0x3f800000
00b0910d d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b09113 d95904                   fstp       dword ptr [ecx + 4]
00b09116 8b16                     mov        edx, dword ptr [esi]
00b09118 d95208                   fst        dword ptr [edx + 8]
00b0911b 8b0e                     mov        ecx, dword ptr [esi]
00b0911d 89410c                   mov        dword ptr [ecx + 0xc], eax
00b09120 d945fc                   fld        dword ptr [ebp - 4]
00b09123 8b16                     mov        edx, dword ptr [esi]
00b09125 d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b0912b 897a10                   mov        dword ptr [edx + 0x10], edi
00b0912e 8b0e                     mov        ecx, dword ptr [esi]
00b09130 8b55c8                   mov        edx, dword ptr [ebp - 0x38]
00b09133 895114                   mov        dword ptr [ecx + 0x14], edx
00b09136 8b0e                     mov        ecx, dword ptr [esi]
00b09138 8b55d4                   mov        edx, dword ptr [ebp - 0x2c]
00b0913b 895118                   mov        dword ptr [ecx + 0x18], edx
00b0913e 8b0e                     mov        ecx, dword ptr [esi]
00b09140 d9591c                   fstp       dword ptr [ecx + 0x1c]
00b09143 8b16                     mov        edx, dword ptr [esi]
00b09145 d945f8                   fld        dword ptr [ebp - 8]
00b09148 d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b0914e d95a20                   fstp       dword ptr [edx + 0x20]
00b09151 8b0e                     mov        ecx, dword ptr [esi]
00b09153 d95124                   fst        dword ptr [ecx + 0x24]
00b09156 8b16                     mov        edx, dword ptr [esi]
00b09158 894228                   mov        dword ptr [edx + 0x28], eax
00b0915b d945f4                   fld        dword ptr [ebp - 0xc]
00b0915e 8b0e                     mov        ecx, dword ptr [esi]
00b09160 d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b09166 89792c                   mov        dword ptr [ecx + 0x2c], edi
00b09169 8b16                     mov        edx, dword ptr [esi]
00b0916b 8b4dc8                   mov        ecx, dword ptr [ebp - 0x38]
00b0916e 894a30                   mov        dword ptr [edx + 0x30], ecx
00b09171 8b16                     mov        edx, dword ptr [esi]
00b09173 8b4dcc                   mov        ecx, dword ptr [ebp - 0x34]
00b09176 894a34                   mov        dword ptr [edx + 0x34], ecx
00b09179 8b16                     mov        edx, dword ptr [esi]
00b0917b d95a38                   fstp       dword ptr [edx + 0x38]
00b0917e 8b0e                     mov        ecx, dword ptr [esi]
00b09180 d945f0                   fld        dword ptr [ebp - 0x10]
00b09183 d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b09189 d9593c                   fstp       dword ptr [ecx + 0x3c]
00b0918c 8b16                     mov        edx, dword ptr [esi]
00b0918e d95240                   fst        dword ptr [edx + 0x40]
00b09191 8b0e                     mov        ecx, dword ptr [esi]
00b09193 d945ec                   fld        dword ptr [ebp - 0x14]
00b09196 894144                   mov        dword ptr [ecx + 0x44], eax
00b09199 8b16                     mov        edx, dword ptr [esi]
00b0919b d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b091a1 897a48                   mov        dword ptr [edx + 0x48], edi
00b091a4 8b0e                     mov        ecx, dword ptr [esi]
00b091a6 8b55d0                   mov        edx, dword ptr [ebp - 0x30]
00b091a9 89514c                   mov        dword ptr [ecx + 0x4c], edx
00b091ac 8b0e                     mov        ecx, dword ptr [esi]
00b091ae 8b55d4                   mov        edx, dword ptr [ebp - 0x2c]
00b091b1 895150                   mov        dword ptr [ecx + 0x50], edx
00b091b4 8b0e                     mov        ecx, dword ptr [esi]
00b091b6 d95954                   fstp       dword ptr [ecx + 0x54]
00b091b9 8b16                     mov        edx, dword ptr [esi]
00b091bb d945e8                   fld        dword ptr [ebp - 0x18]
00b091be d825d04bcd00             fsub       dword ptr [0xcd4bd0]
00b091c4 d95a58                   fstp       dword ptr [edx + 0x58]
00b091c7 8b0e                     mov        ecx, dword ptr [esi]
00b091c9 d9595c                   fstp       dword ptr [ecx + 0x5c]
00b091cc 8b16                     mov        edx, dword ptr [esi]
00b091ce 894260                   mov        dword ptr [edx + 0x60], eax
00b091d1 8b06                     mov        eax, dword ptr [esi]
00b091d3 8b55d0                   mov        edx, dword ptr [ebp - 0x30]
00b091d6 897864                   mov        dword ptr [eax + 0x64], edi
00b091d9 8b0e                     mov        ecx, dword ptr [esi]
00b091db 895168                   mov        dword ptr [ecx + 0x68], edx
00b091de 8b06                     mov        eax, dword ptr [esi]
00b091e0 8b4dcc                   mov        ecx, dword ptr [ebp - 0x34]
00b091e3 89486c                   mov        dword ptr [eax + 0x6c], ecx
00b091e6 8b4310                   mov        eax, dword ptr [ebx + 0x10]
00b091e9 8b10                     mov        edx, dword ptr [eax]
00b091eb 50                       push       eax
00b091ec ff5230                   call       dword ptr [edx + 0x30]
00b091ef 8b4324                   mov        eax, dword ptr [ebx + 0x24]
00b091f2 8a4d1f                   mov        cl, byte ptr [ebp + 0x1f]
00b091f5 8d0480                   lea        eax, [eax + eax*4]
00b091f8 888cc358210000           mov        byte ptr [ebx + eax*8 + 0x2158], cl
00b091ff 8b4324                   mov        eax, dword ptr [ebx + 0x24]
00b09202 8d1480                   lea        edx, [eax + eax*4]
00b09205 8b8348030500             mov        eax, dword ptr [ebx + 0x50348]
