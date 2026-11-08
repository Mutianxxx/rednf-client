008c39a0 64890d00000000           mov       dword ptr fs:[0], ecx
008c39a7 5f                       pop       edi
008c39a8 5e                       pop       esi
008c39a9 5b                       pop       ebx
008c39aa 8be5                     mov       esp, ebp
008c39ac 5d                       pop       ebp
008c39ad c20c00                   ret       0xc
008c39b0 33db                     xor       ebx, ebx
008c39b2 8d8d5cffffff             lea       ecx, [ebp - 0xa4]
008c39b8 885d0b                   mov       byte ptr [ebp + 0xb], bl
008c39bb 895de8                   mov       dword ptr [ebp - 0x18], ebx
008c39be 895dd0                   mov       dword ptr [ebp - 0x30], ebx
008c39c1 895de4                   mov       dword ptr [ebp - 0x1c], ebx
008c39c4 895d10                   mov       dword ptr [ebp + 0x10], ebx
008c39c7 895de0                   mov       dword ptr [ebp - 0x20], ebx
008c39ca e8e138baff               call      0x4672b0
008c39cf 8b16                     mov       edx, dword ptr [esi]
008c39d1 8d45e8                   lea       eax, [ebp - 0x18]
008c39d4 50                       push      eax
008c39d5 8bce                     mov       ecx, esi
008c39d7 c745fc09000000           mov       dword ptr [ebp - 4], 9
008c39de ff5254                   call      dword ptr [edx + 0x54]
008c39e1 8b16                     mov       edx, dword ptr [esi]
008c39e3 8d45d0                   lea       eax, [ebp - 0x30]
008c39e6 50                       push      eax
008c39e7 8bce                     mov       ecx, esi
008c39e9 ff5254                   call      dword ptr [edx + 0x54]
008c39ec 8b16                     mov       edx, dword ptr [esi]
008c39ee 8d45e4                   lea       eax, [ebp - 0x1c]
008c39f1 50                       push      eax
008c39f2 8bce                     mov       ecx, esi
008c39f4 ff5254                   call      dword ptr [edx + 0x54]
008c39f7 8b16                     mov       edx, dword ptr [esi]
008c39f9 8d4510                   lea       eax, [ebp + 0x10]
008c39fc 50                       push      eax
008c39fd 8bce                     mov       ecx, esi
008c39ff ff5254                   call      dword ptr [edx + 0x54]
008c3a02 8b16                     mov       edx, dword ptr [esi]
008c3a04 6a04                     push      4
008c3a06 8d45ec                   lea       eax, [ebp - 0x14]
008c3a09 50                       push      eax
008c3a0a 8bce                     mov       ecx, esi
008c3a0c ff5264                   call      dword ptr [edx + 0x64]
008c3a0f 8d4dec                   lea       ecx, [ebp - 0x14]
008c3a12 51                       push      ecx
008c3a13 8d8d08ffffff             lea       ecx, [ebp - 0xf8]
008c3a19 e8f295b8ff               call      0x44d010
008c3a1e 50                       push      eax
008c3a1f 8d8d5cffffff             lea       ecx, [ebp - 0xa4]
008c3a25 e8860bb4ff               call      0x4045b0
008c3a2a 8d8d08ffffff             lea       ecx, [ebp - 0xf8]
008c3a30 e8dbe5b3ff               call      0x402010
008c3a35 8b16                     mov       edx, dword ptr [esi]
008c3a37 6a02                     push      2
008c3a39 8d450e                   lea       eax, [ebp + 0xe]
008c3a3c 50                       push      eax
008c3a3d 8bce                     mov       ecx, esi
008c3a3f ff5264                   call      dword ptr [edx + 0x64]
008c3a42 0fbf4d0e                 movsx     ecx, word ptr [ebp + 0xe]
008c3a46 894df0                   mov       dword ptr [ebp - 0x10], ecx
008c3a49 8d55f0                   lea       edx, [ebp - 0x10]
008c3a4c db45f0                   fild      dword ptr [ebp - 0x10]
008c3a4f 52                       push      edx
008c3a50 8d8df8feffff             lea       ecx, [ebp - 0x108]
008c3a56 d95df0                   fstp      dword ptr [ebp - 0x10]
008c3a59 e8b295b8ff               call      0x44d010
008c3a5e 50                       push      eax
008c3a5f 8d8d64ffffff             lea       ecx, [ebp - 0x9c]
008c3a65 e8460bb4ff               call      0x4045b0
008c3a6a 8d8df8feffff             lea       ecx, [ebp - 0x108]
008c3a70 e89be5b3ff               call      0x402010
008c3a75 8b06                     mov       eax, dword ptr [esi]
008c3a77 6a02                     push      2
008c3a79 8d4d0e                   lea       ecx, [ebp + 0xe]
008c3a7c 51                       push      ecx
008c3a7d 8bce                     mov       ecx, esi
008c3a7f ff5064                   call      dword ptr [eax + 0x64]
008c3a82 0fbf550e                 movsx     edx, word ptr [ebp + 0xe]
008c3a86 8955f0                   mov       dword ptr [ebp - 0x10], edx
008c3a89 8d45f0                   lea       eax, [ebp - 0x10]
008c3a8c db45f0                   fild      dword ptr [ebp - 0x10]
008c3a8f 50                       push      eax
008c3a90 8d8d00ffffff             lea       ecx, [ebp - 0x100]
008c3a96 d95df0                   fstp      dword ptr [ebp - 0x10]
008c3a99 e87295b8ff               call      0x44d010
008c3a9e 50                       push      eax
008c3a9f 8d8d6cffffff             lea       ecx, [ebp - 0x94]
008c3aa5 e8060bb4ff               call      0x4045b0
008c3aaa 8d8d00ffffff             lea       ecx, [ebp - 0x100]
008c3ab0 e85be5b3ff               call      0x402010
008c3ab5 8b16                     mov       edx, dword ptr [esi]
008c3ab7 6a02                     push      2
008c3ab9 8d450e                   lea       eax, [ebp + 0xe]
008c3abc 50                       push      eax
008c3abd 8bce                     mov       ecx, esi
008c3abf ff5264                   call      dword ptr [edx + 0x64]
008c3ac2 0fbf4d0e                 movsx     ecx, word ptr [ebp + 0xe]
008c3ac6 894df0                   mov       dword ptr [ebp - 0x10], ecx
008c3ac9 8d55f0                   lea       edx, [ebp - 0x10]
008c3acc db45f0                   fild      dword ptr [ebp - 0x10]
008c3acf 52                       push      edx
008c3ad0 8d8d18ffffff             lea       ecx, [ebp - 0xe8]
008c3ad6 d95df0                   fstp      dword ptr [ebp - 0x10]
008c3ad9 e83295b8ff               call      0x44d010
008c3ade 50                       push      eax
008c3adf 8d8d74ffffff             lea       ecx, [ebp - 0x8c]
008c3ae5 e8c60ab4ff               call      0x4045b0
008c3aea 8d8d18ffffff             lea       ecx, [ebp - 0xe8]
008c3af0 e81be5b3ff               call      0x402010
008c3af5 8b06                     mov       eax, dword ptr [esi]
008c3af7 6a02                     push      2
008c3af9 8d4d0e                   lea       ecx, [ebp + 0xe]
008c3afc 51                       push      ecx
008c3afd 8bce                     mov       ecx, esi
008c3aff ff5064                   call      dword ptr [eax + 0x64]
008c3b02 0fbf550e                 movsx     edx, word ptr [ebp + 0xe]
008c3b06 8955f0                   mov       dword ptr [ebp - 0x10], edx
008c3b09 8d45f0                   lea       eax, [ebp - 0x10]
008c3b0c db45f0                   fild      dword ptr [ebp - 0x10]
008c3b0f 50                       push      eax
008c3b10 8d8de8feffff             lea       ecx, [ebp - 0x118]
008c3b16 d95df0                   fstp      dword ptr [ebp - 0x10]
008c3b19 e8f294b8ff               call      0x44d010
008c3b1e 50                       push      eax
008c3b1f 8d8d7cffffff             lea       ecx, [ebp - 0x84]
008c3b25 e8860ab4ff               call      0x4045b0
008c3b2a 8d8de8feffff             lea       ecx, [ebp - 0x118]
008c3b30 e8dbe4b3ff               call      0x402010
008c3b35 8b16                     mov       edx, dword ptr [esi]
008c3b37 6a02                     push      2
008c3b39 8d450e                   lea       eax, [ebp + 0xe]
008c3b3c 50                       push      eax
008c3b3d 8bce                     mov       ecx, esi
008c3b3f ff5264                   call      dword ptr [edx + 0x64]
008c3b42 0fbf4d0e                 movsx     ecx, word ptr [ebp + 0xe]
008c3b46 894df0                   mov       dword ptr [ebp - 0x10], ecx
008c3b49 8d55f0                   lea       edx, [ebp - 0x10]
008c3b4c db45f0                   fild      dword ptr [ebp - 0x10]
008c3b4f 52                       push      edx
008c3b50 8d8d20ffffff             lea       ecx, [ebp - 0xe0]
008c3b56 d95df0                   fstp      dword ptr [ebp - 0x10]
008c3b59 e8b294b8ff               call      0x44d010
008c3b5e 50                       push      eax
008c3b5f 8d4d84                   lea       ecx, [ebp - 0x7c]
008c3b62 e8490ab4ff               call      0x4045b0
008c3b67 8d8d20ffffff             lea       ecx, [ebp - 0xe0]
008c3b6d e89ee4b3ff               call      0x402010
008c3b72 8b06                     mov       eax, dword ptr [esi]
008c3b74 8d4d0b                   lea       ecx, [ebp + 0xb]
008c3b77 51                       push      ecx
008c3b78 8bce                     mov       ecx, esi
008c3b7a ff5050                   call      dword ptr [eax + 0x50]
008c3b7d 8b16                     mov       edx, dword ptr [esi]
008c3b7f 8d45e0                   lea       eax, [ebp - 0x20]
008c3b82 50                       push      eax
008c3b83 8bce                     mov       ecx, esi
008c3b85 ff5254                   call      dword ptr [edx + 0x54]
008c3b88 0fb77de8                 movzx     edi, word ptr [ebp - 0x18]
008c3b8c 8d8d64ffffff             lea       ecx, [ebp - 0x9c]
008c3b92 e819f8b6ff               call      0x4333b0
008c3b97 8d8d5cffffff             lea       ecx, [ebp - 0xa4]
008c3b9d d95df0                   fstp      dword ptr [ebp - 0x10]
008c3ba0 e80bf8b6ff               call      0x4333b0
008c3ba5 d845f0                   fadd      dword ptr [ebp - 0x10]
008c3ba8 0fb755e0                 movzx     edx, word ptr [ebp - 0x20]
008c3bac 8d4f01                   lea       ecx, [edi + 1]
008c3baf d805581fcc00             fadd      dword ptr [0xcc1f58]
008c3bb5 0fb74510                 movzx     eax, word ptr [ebp + 0x10]
008c3bb9 0fafca                   imul      ecx, edx
008c3bbc 894df0                   mov       dword ptr [ebp - 0x10], ecx
008c3bbf da4df0                   fimul     dword ptr [ebp - 0x10]
008c3bc2 8945f0                   mov       dword ptr [ebp - 0x10], eax
008c3bc5 da45f0                   fiadd     dword ptr [ebp - 0x10]
008c3bc8 e877d93300               call      0xc01544
008c3bcd 8986c8a51000             mov       dword ptr [esi + 0x10a5c8], eax
008c3bd3 8b8660a01000             mov       eax, dword ptr [esi + 0x10a060]
008c3bd9 3bc3                     cmp       eax, ebx
008c3bdb 0f84b2010000             je        0x8c3d93
008c3be1 8b80b0000000             mov       eax, dword ptr [eax + 0xb0]
008c3be7 3bc3                     cmp       eax, ebx
008c3be9 0f84a4010000             je        0x8c3d93
008c3bef 0fb74dd0                 movzx     ecx, word ptr [ebp - 0x30]
008c3bf3 53                       push      ebx
008c3bf4 687c28f400               push      0xf4287c
008c3bf9 681009f400               push      0xf40910
008c3bfe 53                       push      ebx
008c3bff 51                       push      ecx
008c3c00 57                       push      edi
008c3c01 8bc8                     mov       ecx, eax
008c3c03 e8187cc4ff               call      0x50b820
008c3c08 50                       push      eax
008c3c09 e8fdd03300               call      0xc00d0b
008c3c0e 8b9660a01000             mov       edx, dword ptr [esi + 0x10a060]
008c3c14 8b8ab0000000             mov       ecx, dword ptr [edx + 0xb0]
008c3c1a 0fb755e4                 movzx     edx, word ptr [ebp - 0x1c]
008c3c1e 83c414                   add       esp, 0x14
008c3c21 53                       push      ebx
008c3c22 687c28f400               push      0xf4287c
008c3c27 681009f400               push      0xf40910
008c3c2c 8bf8                     mov       edi, eax
008c3c2e 0fb74510                 movzx     eax, word ptr [ebp + 0x10]
008c3c32 53                       push      ebx
008c3c33 50                       push      eax
008c3c34 52                       push      edx
008c3c35 e8e67bc4ff               call      0x50b820
008c3c3a 50                       push      eax
008c3c3b e8cbd03300               call      0xc00d0b
008c3c40 83c414                   add       esp, 0x14
008c3c43 3bfb                     cmp       edi, ebx
008c3c45 8bf0                     mov       esi, eax
008c3c47 0f8446010000             je        0x8c3d93
008c3c4d 3bf3                     cmp       esi, ebx
008c3c4f 0f843e010000             je        0x8c3d93
008c3c55 8b07                     mov       eax, dword ptr [edi]
008c3c57 8bcf                     mov       ecx, edi
008c3c59 ff90c8010000             call      dword ptr [eax + 0x1c8]
008c3c5f 8b16                     mov       edx, dword ptr [esi]
008c3c61 8bce                     mov       ecx, esi
008c3c63 8bf8                     mov       edi, eax
008c3c65 ff92c8010000             call      dword ptr [edx + 0x1c8]
008c3c6b 385d0b                   cmp       byte ptr [ebp + 0xb], bl
008c3c6e 0f95c1                   setne     cl
008c3c71 8d955cffffff             lea       edx, [ebp - 0xa4]
008c3c77 8bf0                     mov       esi, eax
008c3c79 8b07                     mov       eax, dword ptr [edi]
008c3c7b 51                       push      ecx
008c3c7c 52                       push      edx
008c3c7d 56                       push      esi
008c3c7e 8bcf                     mov       ecx, edi
008c3c80 ff9050020000             call      dword ptr [eax + 0x250]
008c3c86 8a4d0b                   mov       cl, byte ptr [ebp + 0xb]
008c3c89 8b06                     mov       eax, dword ptr [esi]
008c3c8b 3acb                     cmp       cl, bl
008c3c8d 0f95c1                   setne     cl
008c3c90 8d955cffffff             lea       edx, [ebp - 0xa4]
008c3c96 51                       push      ecx
008c3c97 52                       push      edx
008c3c98 57                       push      edi
008c3c99 8bce                     mov       ecx, esi
008c3c9b ff905c020000             call      dword ptr [eax + 0x25c]
008c3ca1 8a4d0b                   mov       cl, byte ptr [ebp + 0xb]
008c3ca4 8b07                     mov       eax, dword ptr [edi]
008c3ca6 3acb                     cmp       cl, bl
008c3ca8 0f95c1                   setne     cl
008c3cab 8d955cffffff             lea       edx, [ebp - 0xa4]
008c3cb1 51                       push      ecx
008c3cb2 52                       push      edx
008c3cb3 56                       push      esi
008c3cb4 8bcf                     mov       ecx, edi
008c3cb6 ff9054020000             call      dword ptr [eax + 0x254]
008c3cbc 8a4d0b                   mov       cl, byte ptr [ebp + 0xb]
008c3cbf 8b06                     mov       eax, dword ptr [esi]
008c3cc1 3acb                     cmp       cl, bl
008c3cc3 0f95c1                   setne     cl
008c3cc6 8d955cffffff             lea       edx, [ebp - 0xa4]
008c3ccc 51                       push      ecx
008c3ccd 52                       push      edx
008c3cce 57                       push      edi
008c3ccf 8bce                     mov       ecx, esi
008c3cd1 ff9060020000             call      dword ptr [eax + 0x260]
008c3cd7 8a4d0b                   mov       cl, byte ptr [ebp + 0xb]
008c3cda 8b07                     mov       eax, dword ptr [edi]
008c3cdc 3acb                     cmp       cl, bl
008c3cde 0f95c1                   setne     cl
008c3ce1 8d955cffffff             lea       edx, [ebp - 0xa4]
008c3ce7 51                       push      ecx
008c3ce8 52                       push      edx
008c3ce9 56                       push      esi
008c3cea 8bcf                     mov       ecx, edi
008c3cec ff9058020000             call      dword ptr [eax + 0x258]
008c3cf2 8a4d0b                   mov       cl, byte ptr [ebp + 0xb]
008c3cf5 8b06                     mov       eax, dword ptr [esi]
008c3cf7 3acb                     cmp       cl, bl
008c3cf9 0f95c1                   setne     cl
008c3cfc 8d955cffffff             lea       edx, [ebp - 0xa4]
008c3d02 51                       push      ecx
008c3d03 52                       push      edx
008c3d04 57                       push      edi
008c3d05 8bce                     mov       ecx, esi
008c3d07 ff9064020000             call      dword ptr [eax + 0x264]
008c3d0d 8b06                     mov       eax, dword ptr [esi]
008c3d0f 6a11                     push      0x11
008c3d11 8bce                     mov       ecx, esi
008c3d13 ff502c                   call      dword ptr [eax + 0x2c]
008c3d16 84c0                     test      al, al
008c3d18 7420                     je        0x8c3d3a
008c3d1a 385d0b                   cmp       byte ptr [ebp + 0xb], bl
008c3d1d 8b06                     mov       eax, dword ptr [esi]
008c3d1f 0f95c1                   setne     cl
008c3d22 8d955cffffff             lea       edx, [ebp - 0xa4]
008c3d28 51                       push      ecx
008c3d29 52                       push      edx
008c3d2a 57                       push      edi
008c3d2b 8bce                     mov       ecx, esi
008c3d2d ff90c4030000             call      dword ptr [eax + 0x3c4]
008c3d33 8bc8                     mov       ecx, eax
008c3d35 e876230000               call      0x8c60b0
008c3d3a 8b17                     mov       edx, dword ptr [edi]
008c3d3c 8bcf                     mov       ecx, edi
008c3d3e ff92a4020000             call      dword ptr [edx + 0x2a4]
008c3d44 85c0                     test      eax, eax
008c3d46 744b                     je        0x8c3d93
008c3d48 8b07                     mov       eax, dword ptr [edi]
008c3d4a 8bcf                     mov       ecx, edi
008c3d4c ff90a4020000             call      dword ptr [eax + 0x2a4]
008c3d52 385d0b                   cmp       byte ptr [ebp + 0xb], bl
008c3d55 0f95c1                   setne     cl
008c3d58 8d955cffffff             lea       edx, [ebp - 0xa4]
008c3d5e 8945f0                   mov       dword ptr [ebp - 0x10], eax
008c3d61 51                       push      ecx
008c3d62 52                       push      edx
008c3d63 8b10                     mov       edx, dword ptr [eax]
008c3d65 56                       push      esi
008c3d66 57                       push      edi
008c3d67 8bc8                     mov       ecx, eax
008c3d69 ff92c4030000             call      dword ptr [edx + 0x3c4]
008c3d6f 8bc8                     mov       ecx, eax
008c3d71 e8ba220000               call      0x8c6030
008c3d76 8a550b                   mov       dl, byte ptr [ebp + 0xb]
008c3d79 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
008c3d7c 8b01                     mov       eax, dword ptr [ecx]
008c3d7e 3ad3                     cmp       dl, bl
008c3d80 0f95c2                   setne     dl
008c3d83 52                       push      edx
008c3d84 8d955cffffff             lea       edx, [ebp - 0xa4]
008c3d8a 52                       push      edx
008c3d8b 56                       push      esi
008c3d8c 57                       push      edi
008c3d8d ff90a8040000             call      dword ptr [eax + 0x4a8]
008c3d93 8d8d5cffffff             lea       ecx, [ebp - 0xa4]
008c3d99 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
008c3da0 e85b05b4ff               call      0x404300
008c3da5 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
008c3da8 64890d00000000           mov       dword ptr fs:[0], ecx
008c3daf 5f                       pop       edi
008c3db0 5e                       pop       esi
008c3db1 5b                       pop       ebx
008c3db2 8be5                     mov       esp, ebp
008c3db4 5d                       pop       ebp
008c3db5 c20c00                   ret       0xc
008c3db8 33db                     xor       ebx, ebx
008c3dba 8d8d5cffffff             lea       ecx, [ebp - 0xa4]
008c3dc0 885d0b                   mov       byte ptr [ebp + 0xb], bl
008c3dc3 885d0f                   mov       byte ptr [ebp + 0xf], bl
008c3dc6 895de0                   mov       dword ptr [ebp - 0x20], ebx
008c3dc9 895de8                   mov       dword ptr [ebp - 0x18], ebx
008c3dcc 895dcc                   mov       dword ptr [ebp - 0x34], ebx
008c3dcf 89                       .byte     0x89
