00a32b50 55                       push      ebp
00a32b51 8bec                     mov       ebp, esp
00a32b53 8b4510                   mov       eax, dword ptr [ebp + 0x10]
00a32b56 56                       push      esi
00a32b57 8b750c                   mov       esi, dword ptr [ebp + 0xc]
00a32b5a 57                       push      edi
00a32b5b 8b7d08                   mov       edi, dword ptr [ebp + 8]
00a32b5e 50                       push      eax
00a32b5f 56                       push      esi
00a32b60 57                       push      edi
00a32b61 e82affffff               call      0xa32a90
00a32b66 84c0                     test      al, al
00a32b68 7526                     jne       0xa32b90
00a32b6a 56                       push      esi
00a32b6b 57                       push      edi
00a32b6c 68d055e400               push      0xe455d0
00a32b71 68d850e400               push      0xe450d8
00a32b76 ff15bc2eff00             call      dword ptr [0xff2ebc]
00a32b7c 56                       push      esi
00a32b7d 57                       push      edi
00a32b7e 68d055e400               push      0xe455d0
00a32b83 686855e400               push      0xe45568
00a32b88 e8b3270e00               call      0xb15340
00a32b8d 83c420                   add       esp, 0x20
00a32b90 5f                       pop       edi
00a32b91 5e                       pop       esi
00a32b92 5d                       pop       ebp
00a32b93 c20c00                   ret       0xc
00a32b96 cc                       int3      
00a32b97 cc                       int3      
00a32b98 cc                       int3      
00a32b99 cc                       int3      
00a32b9a cc                       int3      
00a32b9b cc                       int3      
00a32b9c cc                       int3      
00a32b9d cc                       int3      
00a32b9e cc                       int3      
00a32b9f cc                       int3      
00a32ba0 56                       push      esi
00a32ba1 8bf1                     mov       esi, ecx
00a32ba3 57                       push      edi
00a32ba4 8b3e                     mov       edi, dword ptr [esi]
00a32ba6 85ff                     test      edi, edi
00a32ba8 7410                     je        0xa32bba
00a32baa 8bcf                     mov       ecx, edi
00a32bac e8efffffff               call      0xa32ba0
00a32bb1 57                       push      edi
00a32bb2 e826d41c00               call      0xbfffdd
00a32bb7 83c404                   add       esp, 4
00a32bba 8b7e04                   mov       edi, dword ptr [esi + 4]
00a32bbd 85ff                     test      edi, edi
00a32bbf c70600000000             mov       dword ptr [esi], 0
00a32bc5 7410                     je        0xa32bd7
00a32bc7 8bcf                     mov       ecx, edi
00a32bc9 e8d2ffffff               call      0xa32ba0
00a32bce 57                       push      edi
00a32bcf e809d41c00               call      0xbfffdd
00a32bd4 83c404                   add       esp, 4
00a32bd7 5f                       pop       edi
00a32bd8 c7460400000000           mov       dword ptr [esi + 4], 0
00a32bdf 5e                       pop       esi
00a32be0 c3                       ret       
00a32be1 cc                       int3      
00a32be2 cc                       int3      
00a32be3 cc                       int3      
00a32be4 cc                       int3      
00a32be5 cc                       int3      
00a32be6 cc                       int3      
00a32be7 cc                       int3      
00a32be8 cc                       int3      
00a32be9 cc                       int3      
00a32bea cc                       int3      
00a32beb cc                       int3      
00a32bec cc                       int3      
00a32bed cc                       int3      
00a32bee cc                       int3      
00a32bef cc                       int3      
00a32bf0 56                       push      esi
00a32bf1 8bf1                     mov       esi, ecx
00a32bf3 57                       push      edi
00a32bf4 8b3e                     mov       edi, dword ptr [esi]
00a32bf6 85ff                     test      edi, edi
00a32bf8 7410                     je        0xa32c0a
00a32bfa 8bcf                     mov       ecx, edi
00a32bfc e8efffffff               call      0xa32bf0
00a32c01 57                       push      edi
00a32c02 e8d6d31c00               call      0xbfffdd
00a32c07 83c404                   add       esp, 4
00a32c0a 8b7e04                   mov       edi, dword ptr [esi + 4]
00a32c0d 85ff                     test      edi, edi
00a32c0f c70600000000             mov       dword ptr [esi], 0
00a32c15 7410                     je        0xa32c27
00a32c17 8bcf                     mov       ecx, edi
00a32c19 e8d2ffffff               call      0xa32bf0
00a32c1e 57                       push      edi
00a32c1f e8b9d31c00               call      0xbfffdd
00a32c24 83c404                   add       esp, 4
00a32c27 5f                       pop       edi
00a32c28 c7460400000000           mov       dword ptr [esi + 4], 0
00a32c2f 5e                       pop       esi
00a32c30 c3                       ret       
00a32c31 cc                       int3      
00a32c32 cc                       int3      
00a32c33 cc                       int3      
00a32c34 cc                       int3      
00a32c35 cc                       int3      
00a32c36 cc                       int3      
00a32c37 cc                       int3      
00a32c38 cc                       int3      
00a32c39 cc                       int3      
00a32c3a cc                       int3      
00a32c3b cc                       int3      
00a32c3c cc                       int3      
00a32c3d cc                       int3      
00a32c3e cc                       int3      
00a32c3f cc                       int3      
00a32c40 55                       push      ebp
00a32c41 8bec                     mov       ebp, esp
00a32c43 6a1c                     push      0x1c
00a32c45 e8d3ac1b00               call      0xbed91d
00a32c4a 83c404                   add       esp, 4
00a32c4d 85c0                     test      eax, eax
00a32c4f 742f                     je        0xa32c80
00a32c51 8b550c                   mov       edx, dword ptr [ebp + 0xc]
00a32c54 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00a32c57 8908                     mov       dword ptr [eax], ecx
00a32c59 895004                   mov       dword ptr [eax + 4], edx
00a32c5c 8b5510                   mov       edx, dword ptr [ebp + 0x10]
00a32c5f 56                       push      esi
00a32c60 8b32                     mov       esi, dword ptr [edx]
00a32c62 8d4808                   lea       ecx, [eax + 8]
00a32c65 8931                     mov       dword ptr [ecx], esi
00a32c67 8b7204                   mov       esi, dword ptr [edx + 4]
00a32c6a 897104                   mov       dword ptr [ecx + 4], esi
00a32c6d 8b7208                   mov       esi, dword ptr [edx + 8]
00a32c70 897108                   mov       dword ptr [ecx + 8], esi
00a32c73 8b720c                   mov       esi, dword ptr [edx + 0xc]
00a32c76 89710c                   mov       dword ptr [ecx + 0xc], esi
00a32c79 8b5210                   mov       edx, dword ptr [edx + 0x10]
00a32c7c 895110                   mov       dword ptr [ecx + 0x10], edx
00a32c7f 5e                       pop       esi
00a32c80 5d                       pop       ebp
00a32c81 c20c00                   ret       0xc
00a32c84 cc                       int3      
00a32c85 cc                       int3      
00a32c86 cc                       int3      
00a32c87 cc                       int3      
00a32c88 cc                       int3      
00a32c89 cc                       int3      
00a32c8a cc                       int3      
00a32c8b cc                       int3      
00a32c8c cc                       int3      
00a32c8d cc                       int3      
00a32c8e cc                       int3      
00a32c8f cc                       int3      
00a32c90 55                       push      ebp
00a32c91 8bec                     mov       ebp, esp
00a32c93 8b450c                   mov       eax, dword ptr [ebp + 0xc]
00a32c96 85c0                     test      eax, eax
00a32c98 763e                     jbe       0xa32cd8
00a32c9a 8b5510                   mov       edx, dword ptr [ebp + 0x10]
00a32c9d 53                       push      ebx
00a32c9e 56                       push      esi
00a32c9f 8bc8                     mov       ecx, eax
00a32ca1 8b4508                   mov       eax, dword ptr [ebp + 8]
00a32ca4 57                       push      edi
00a32ca5 85c0                     test      eax, eax
00a32ca7 7426                     je        0xa32ccf
00a32ca9 8bf2                     mov       esi, edx
00a32cab 8b1e                     mov       ebx, dword ptr [esi]
00a32cad 8bf8                     mov       edi, eax
00a32caf 891f                     mov       dword ptr [edi], ebx
00a32cb1 8b5e04                   mov       ebx, dword ptr [esi + 4]
00a32cb4 895f04                   mov       dword ptr [edi + 4], ebx
00a32cb7 8b5e08                   mov       ebx, dword ptr [esi + 8]
00a32cba 895f08                   mov       dword ptr [edi + 8], ebx
00a32cbd 8b5e0c                   mov       ebx, dword ptr [esi + 0xc]
00a32cc0 895f0c                   mov       dword ptr [edi + 0xc], ebx
00a32cc3 8b5e10                   mov       ebx, dword ptr [esi + 0x10]
00a32cc6 895f10                   mov       dword ptr [edi + 0x10], ebx
00a32cc9 8b7614                   mov       esi, dword ptr [esi + 0x14]
00a32ccc 897714                   mov       dword ptr [edi + 0x14], esi
00a32ccf 83c018                   add       eax, 0x18
00a32cd2 49                       dec       ecx
00a32cd3 75d0                     jne       0xa32ca5
00a32cd5 5f                       pop       edi
00a32cd6 5e                       pop       esi
00a32cd7 5b                       pop       ebx
00a32cd8 5d                       pop       ebp
00a32cd9 c3                       ret       
00a32cda cc                       int3      
00a32cdb cc                       int3      
00a32cdc cc                       int3      
00a32cdd cc                       int3      
00a32cde cc                       int3      
00a32cdf cc                       int3      
00a32ce0 55                       push      ebp
00a32ce1 8bec                     mov       ebp, esp
00a32ce3 8b4510                   mov       eax, dword ptr [ebp + 0x10]
00a32ce6 56                       push      esi
00a32ce7 8b750c                   mov       esi, dword ptr [ebp + 0xc]
00a32cea 57                       push      edi
00a32ceb 8b7d08                   mov       edi, dword ptr [ebp + 8]
00a32cee 50                       push      eax
00a32cef 51                       push      ecx
00a32cf0 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
00a32cf3 51                       push      ecx
00a32cf4 56                       push      esi
00a32cf5 57                       push      edi
00a32cf6 e895ffffff               call      0xa32c90
00a32cfb 8d1476                   lea       edx, [esi + esi*2]
00a32cfe 83c414                   add       esp, 0x14
00a32d01 8d04d7                   lea       eax, [edi + edx*8]
00a32d04 5f                       pop       edi
00a32d05 5e                       pop       esi
00a32d06 5d                       pop       ebp
00a32d07 c20c00                   ret       0xc
00a32d0a cc                       int3      
00a32d0b cc                       int3      
00a32d0c cc                       int3      
00a32d0d cc                       int3      
00a32d0e cc                       int3      
00a32d0f cc                       int3      
00a32d10 55                       push      ebp
00a32d11 8bec                     mov       ebp, esp
00a32d13 56                       push      esi
00a32d14 57                       push      edi
00a32d15 8b7d08                   mov       edi, dword ptr [ebp + 8]
00a32d18 33c0                     xor       eax, eax
00a32d1a 6aff                     push      -1
00a32d1c 8bf1                     mov       esi, ecx
00a32d1e 50                       push      eax
00a32d1f c7461807000000           mov       dword ptr [esi + 0x18], 7
00a32d26 894614                   mov       dword ptr [esi + 0x14], eax
00a32d29 57                       push      edi
00a32d2a 66894604                 mov       word ptr [esi + 4], ax
00a32d2e e82d009dff               call      0x402d60
00a32d33 8b471c                   mov       eax, dword ptr [edi + 0x1c]
00a32d36 89461c                   mov       dword ptr [esi + 0x1c], eax
00a32d39 5f                       pop       edi
00a32d3a 8bc6                     mov       eax, esi
00a32d3c 5e                       pop       esi
00a32d3d 5d                       pop       ebp
00a32d3e c20400                   ret       4
00a32d41 cc                       int3      
00a32d42 cc                       int3      
00a32d43 cc                       int3      
00a32d44 cc                       int3      
00a32d45 cc                       int3      
00a32d46 cc                       int3      
00a32d47 cc                       int3      
00a32d48 cc                       int3      
00a32d49 cc                       int3      
00a32d4a cc                       int3      
00a32d4b cc                       int3      
00a32d4c cc                       int3      
00a32d4d cc                       int3      
00a32d4e cc                       int3      
00a32d4f cc                       int3      
00a32d50 55                       push      ebp
00a32d51 8bec                     mov       ebp, esp
00a32d53 6aff                     push      -1
00a32d55 6858e7c800               push      0xc8e758
00a32d5a 64a100000000             mov       eax, dword ptr fs:[0]
00a32d60 50                       push      eax
00a32d61 64892500000000           mov       dword ptr fs:[0], esp
00a32d68 83ec44                   sub       esp, 0x44
00a32d6b 6a1b                     push      0x1b
00a32d6d 683458cb00               push      0xcb5834
00a32d72 8d4dd8                   lea       ecx, [ebp - 0x28]
00a32d75 c745f00f000000           mov       dword ptr [ebp - 0x10], 0xf
00a32d7c c745ec00000000           mov       dword ptr [ebp - 0x14], 0
00a32d83 c645dc00                 mov       byte ptr [ebp - 0x24], 0
00a32d87 e824059dff               call      0x4032b0
00a32d8c 8d45d8                   lea       eax, [ebp - 0x28]
00a32d8f 50                       push      eax
00a32d90 8d4db0                   lea       ecx, [ebp - 0x50]
00a32d93 c745fc00000000           mov       dword ptr [ebp - 4], 0
00a32d9a e8f1079dff               call      0x403590
00a32d9f 68c867ed00               push      0xed67c8
00a32da4 8d4db0                   lea       ecx, [ebp - 0x50]
00a32da7 51                       push      ecx
00a32da8 c745b0f0baca00           mov       dword ptr [ebp - 0x50], 0xcabaf0
00a32daf e8bbd71c00               call      0xc0056f
00a32db4 cc                       int3      
00a32db5 cc                       int3      
00a32db6 cc                       int3      
00a32db7 cc                       int3      
00a32db8 cc                       int3      
00a32db9 cc                       int3      
00a32dba cc                       int3      
00a32dbb cc                       int3      
00a32dbc cc                       int3      
00a32dbd cc                       int3      
00a32dbe cc                       int3      
00a32dbf cc                       int3      
00a32dc0 55                       push      ebp
00a32dc1 8bec                     mov       ebp, esp
00a32dc3 6aff                     push      -1
00a32dc5 6858e7c800               push      0xc8e758
00a32dca 64a100000000             mov       eax, dword ptr fs:[0]
00a32dd0 50                       push      eax
00a32dd1 64892500000000           mov       dword ptr fs:[0], esp
00a32dd8 83ec44                   sub       esp, 0x44
00a32ddb 8b4108                   mov       eax, dword ptr [ecx + 8]
00a32dde 8b5508                   mov       edx, dword ptr [ebp + 8]
00a32de1 56                       push      esi
00a32de2 becccccc0c               mov       esi, 0xccccccc
00a32de7 2bf0                     sub       esi, eax
00a32de9 3bf2                     cmp       esi, edx
00a32deb 5e                       pop       esi
00a32dec 7349                     jae       0xa32e37
00a32dee 6a10                     push      0x10
00a32df0 68f8baca00               push      0xcabaf8
00a32df5 8d4dd8                   lea       ecx, [ebp - 0x28]
00a32df8 c745f00f000000           mov       dword ptr [ebp - 0x10], 0xf
00a32dff c745ec00000000           mov       dword ptr [ebp - 0x14], 0
00a32e06 c645dc00                 mov       byte ptr [ebp - 0x24], 0
00a32e0a e8a1049dff               call      0x4032b0
00a32e0f 8d45d8                   lea       eax, [ebp - 0x28]
00a32e12 50                       push      eax
00a32e13 8d4db0                   lea       ecx, [ebp - 0x50]
00a32e16 c745fc00000000           mov       dword ptr [ebp - 4], 0
00a32e1d e86e079dff               call      0x403590
00a32e22 681463ed00               push      0xed6314
00a32e27 8d4db0                   lea       ecx, [ebp - 0x50]
00a32e2a 51                       push      ecx
00a32e2b c745b0a4b9ca00           mov       dword ptr [ebp - 0x50], 0xcab9a4
00a32e32 e838d71c00               call      0xc0056f
00a32e37 03c2                     add       eax, edx
00a32e39 894108                   mov       dword ptr [ecx + 8], eax
00a32e3c 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00a32e3f 64890d00000000           mov       dword ptr fs:[0], ecx
00a32e46 8be5                     mov       esp, ebp
00a32e48 5d                       pop       ebp
00a32e49 c20400                   ret       4
00a32e4c cc                       int3      
00a32e4d cc                       int3      
00a32e4e cc                       int3      
00a32e4f cc                       int3      
