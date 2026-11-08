004b28d0 55                       push      ebp
004b28d1 8bec                     mov       ebp, esp
004b28d3 6aff                     push      -1
004b28d5 688975c500               push      0xc57589
004b28da 64a100000000             mov       eax, dword ptr fs:[0]
004b28e0 50                       push      eax
004b28e1 64892500000000           mov       dword ptr fs:[0], esp
004b28e8 83ec4c                   sub       esp, 0x4c
004b28eb 53                       push      ebx
004b28ec 56                       push      esi
004b28ed 57                       push      edi
004b28ee 8bf1                     mov       esi, ecx
004b28f0 e84bcbffff               call      0x4af440
004b28f5 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004b28f8 8dbeec140000             lea       edi, [esi + 0x14ec]
004b28fe c745dc17000000           mov       dword ptr [ebp - 0x24], 0x17
004b2905 8b07                     mov       eax, dword ptr [edi]
004b2907 85c0                     test      eax, eax
004b2909 7415                     je        0x4b2920
004b290b 8b5510                   mov       edx, dword ptr [ebp + 0x10]
004b290e 6a01                     push      1
004b2910 52                       push      edx
004b2911 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004b2914 8bc8                     mov       ecx, eax
004b2916 8b01                     mov       eax, dword ptr [ecx]
004b2918 52                       push      edx
004b2919 53                       push      ebx
004b291a ff90bc000000             call      dword ptr [eax + 0xbc]
004b2920 8b45dc                   mov       eax, dword ptr [ebp - 0x24]
004b2923 83c704                   add       edi, 4
004b2926 48                       dec       eax
004b2927 8945dc                   mov       dword ptr [ebp - 0x24], eax
004b292a 75d9                     jne       0x4b2905
004b292c 8b03                     mov       eax, dword ptr [ebx]
004b292e 8bcb                     mov       ecx, ebx
004b2930 ff909c010000             call      dword ptr [eax + 0x19c]
004b2936 8b481c                   mov       ecx, dword ptr [eax + 0x1c]
004b2939 8b5020                   mov       edx, dword ptr [eax + 0x20]
004b293c 8d781c                   lea       edi, [eax + 0x1c]
004b293f 8945dc                   mov       dword ptr [ebp - 0x24], eax
004b2942 a1dc012101               mov       eax, dword ptr [0x12101dc]
004b2947 33c8                     xor       ecx, eax
004b2949 2bcf                     sub       ecx, edi
004b294b 3bca                     cmp       ecx, edx
004b294d 7413                     je        0x4b2962
004b294f 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004b2955 6a3f                     push      0x3f
004b2957 57                       push      edi
004b2958 e853476600               call      0xb170b0
004b295d a1dc012101               mov       eax, dword ptr [0x12101dc]
004b2962 8b5704                   mov       edx, dword ptr [edi + 4]
004b2965 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004b296b 8b5944                   mov       ebx, dword ptr [ecx + 0x44]
004b296e c1e202                   shl       edx, 2
004b2971 8d3c1a                   lea       edi, [edx + ebx]
004b2974 333c1a                   xor       edi, dword ptr [edx + ebx]
004b2977 33f8                     xor       edi, eax
004b2979 897dd0                   mov       dword ptr [ebp - 0x30], edi
004b297c 8b7948                   mov       edi, dword ptr [ecx + 0x48]
004b297f 8d1c3a                   lea       ebx, [edx + edi]
004b2982 331c3a                   xor       ebx, dword ptr [edx + edi]
004b2985 8b7dd0                   mov       edi, dword ptr [ebp - 0x30]
004b2988 33d8                     xor       ebx, eax
004b298a 3bfb                     cmp       edi, ebx
004b298c 8b5ddc                   mov       ebx, dword ptr [ebp - 0x24]
004b298f 7416                     je        0x4b29a7
004b2991 6a40                     push      0x40
004b2993 8d431c                   lea       eax, [ebx + 0x1c]
004b2996 50                       push      eax
004b2997 e814476600               call      0xb170b0
004b299c a1dc012101               mov       eax, dword ptr [0x12101dc]
004b29a1 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004b29a7 85ff                     test      edi, edi
004b29a9 752f                     jne       0x4b29da
004b29ab 8bcb                     mov       ecx, ebx
004b29ad e8fe09f8ff               call      0x4333b0
004b29b2 d81da4d7e900             fcomp     dword ptr [0xe9d7a4]
004b29b8 dfe0                     fnstsw    ax
004b29ba f6c441                   test      ah, 0x41
004b29bd 7410                     je        0x4b29cf
004b29bf 8d4b08                   lea       ecx, [ebx + 8]
004b29c2 e899f6f4ff               call      0x402060
004b29c7 85c0                     test      eax, eax
004b29c9 0f8ec5020000             jle       0x4b2c94
004b29cf a1dc012101               mov       eax, dword ptr [0x12101dc]
004b29d4 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004b29da 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004b29dd 8dbee8190000             lea       edi, [esi + 0x19e8]
004b29e3 3bfa                     cmp       edi, edx
004b29e5 7469                     je        0x4b2a50
004b29e7 8b5a04                   mov       ebx, dword ptr [edx + 4]
004b29ea 8b4944                   mov       ecx, dword ptr [ecx + 0x44]
004b29ed c1e302                   shl       ebx, 2
004b29f0 8d140b                   lea       edx, [ebx + ecx]
004b29f3 33140b                   xor       edx, dword ptr [ebx + ecx]
004b29f6 8b5f04                   mov       ebx, dword ptr [edi + 4]
004b29f9 33d0                     xor       edx, eax
004b29fb c1e302                   shl       ebx, 2
004b29fe 895dd0                   mov       dword ptr [ebp - 0x30], ebx
004b2a01 03d9                     add       ebx, ecx
004b2a03 33da                     xor       ebx, edx
004b2a05 8b55d0                   mov       edx, dword ptr [ebp - 0x30]
004b2a08 33d8                     xor       ebx, eax
004b2a0a 891c0a                   mov       dword ptr [edx + ecx], ebx
004b2a0d a1d8012101               mov       eax, dword ptr [0x12101d8]
004b2a12 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004b2a15 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004b2a18 8b5204                   mov       edx, dword ptr [edx + 4]
004b2a1b c1e202                   shl       edx, 2
004b2a1e 8b1c0a                   mov       ebx, dword ptr [edx + ecx]
004b2a21 8d040a                   lea       eax, [edx + ecx]
004b2a24 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004b2a2a 33c3                     xor       eax, ebx
004b2a2c 33c2                     xor       eax, edx
004b2a2e 8b5704                   mov       edx, dword ptr [edi + 4]
004b2a31 c1e202                   shl       edx, 2
004b2a34 8d1c0a                   lea       ebx, [edx + ecx]
004b2a37 33d8                     xor       ebx, eax
004b2a39 331ddc012101             xor       ebx, dword ptr [0x12101dc]
004b2a3f 891c0a                   mov       dword ptr [edx + ecx], ebx
004b2a42 a1dc012101               mov       eax, dword ptr [0x12101dc]
004b2a47 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004b2a4d 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004b2a50 83c208                   add       edx, 8
004b2a53 8d5f08                   lea       ebx, [edi + 8]
004b2a56 3bda                     cmp       ebx, edx
004b2a58 746a                     je        0x4b2ac4
004b2a5a 8b5a04                   mov       ebx, dword ptr [edx + 4]
004b2a5d 8b4944                   mov       ecx, dword ptr [ecx + 0x44]
004b2a60 c1e302                   shl       ebx, 2
004b2a63 8d140b                   lea       edx, [ebx + ecx]
004b2a66 33140b                   xor       edx, dword ptr [ebx + ecx]
004b2a69 8b5f0c                   mov       ebx, dword ptr [edi + 0xc]
004b2a6c 33d0                     xor       edx, eax
004b2a6e c1e302                   shl       ebx, 2
004b2a71 895dd0                   mov       dword ptr [ebp - 0x30], ebx
004b2a74 03d9                     add       ebx, ecx
004b2a76 33da                     xor       ebx, edx
004b2a78 33d8                     xor       ebx, eax
004b2a7a 8b45d0                   mov       eax, dword ptr [ebp - 0x30]
004b2a7d 891c08                   mov       dword ptr [eax + ecx], ebx
004b2a80 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004b2a83 8b500c                   mov       edx, dword ptr [eax + 0xc]
004b2a86 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004b2a8c 8b4948                   mov       ecx, dword ptr [ecx + 0x48]
004b2a8f 83c008                   add       eax, 8
004b2a92 c1e202                   shl       edx, 2
004b2a95 8b1c0a                   mov       ebx, dword ptr [edx + ecx]
004b2a98 8d040a                   lea       eax, [edx + ecx]
004b2a9b 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004b2aa1 33c3                     xor       eax, ebx
004b2aa3 33c2                     xor       eax, edx
004b2aa5 8b570c                   mov       edx, dword ptr [edi + 0xc]
004b2aa8 c1e202                   shl       edx, 2
004b2aab 8d1c0a                   lea       ebx, [edx + ecx]
004b2aae 33d8                     xor       ebx, eax
004b2ab0 331ddc012101             xor       ebx, dword ptr [0x12101dc]
004b2ab6 891c0a                   mov       dword ptr [edx + ecx], ebx
004b2ab9 a1dc012101               mov       eax, dword ptr [0x12101dc]
004b2abe 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004b2ac4 8b550c                   mov       edx, dword ptr [ebp + 0xc]
004b2ac7 83c210                   add       edx, 0x10
004b2aca 8d5f10                   lea       ebx, [edi + 0x10]
004b2acd 3bda                     cmp       ebx, edx
004b2acf 7469                     je        0x4b2b3a
004b2ad1 8b5a04                   mov       ebx, dword ptr [edx + 4]
004b2ad4 8b4944                   mov       ecx, dword ptr [ecx + 0x44]
004b2ad7 c1e302                   shl       ebx, 2
004b2ada 8d140b                   lea       edx, [ebx + ecx]
004b2add 33140b                   xor       edx, dword ptr [ebx + ecx]
004b2ae0 8b5f14                   mov       ebx, dword ptr [edi + 0x14]
004b2ae3 33d0                     xor       edx, eax
004b2ae5 c1e302                   shl       ebx, 2
004b2ae8 895dd0                   mov       dword ptr [ebp - 0x30], ebx
004b2aeb 03d9                     add       ebx, ecx
004b2aed 33da                     xor       ebx, edx
004b2aef 8b55d0                   mov       edx, dword ptr [ebp - 0x30]
004b2af2 33d8                     xor       ebx, eax
004b2af4 891c0a                   mov       dword ptr [edx + ecx], ebx
004b2af7 a1d8012101               mov       eax, dword ptr [0x12101d8]
004b2afc 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004b2aff 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004b2b02 8b5014                   mov       edx, dword ptr [eax + 0x14]
004b2b05 83c010                   add       eax, 0x10
004b2b08 c1e202                   shl       edx, 2
004b2b0b 8b1c0a                   mov       ebx, dword ptr [edx + ecx]
004b2b0e 8d                       .byte     0x8d
004b2b0f 04                       .byte     0x04
