004edf70 55                       push      ebp
004edf71 8bec                     mov       ebp, esp
004edf73 6aff                     push      -1
004edf75 68de98c500               push      0xc598de
004edf7a 64a100000000             mov       eax, dword ptr fs:[0]
004edf80 50                       push      eax
004edf81 64892500000000           mov       dword ptr fs:[0], esp
004edf88 83ec38                   sub       esp, 0x38
004edf8b 8a450c                   mov       al, byte ptr [ebp + 0xc]
004edf8e 84c0                     test      al, al
004edf90 56                       push      esi
004edf91 57                       push      edi
004edf92 8b7d08                   mov       edi, dword ptr [ebp + 8]
004edf95 8bf1                     mov       esi, ecx
004edf97 7414                     je        0x4edfad
004edf99 e8f2e0faff               call      0x49c090
004edf9e 84c0                     test      al, al
004edfa0 750b                     jne       0x4edfad
004edfa2 8bcf                     mov       ecx, edi
004edfa4 e8e7e0faff               call      0x49c090
004edfa9 84c0                     test      al, al
004edfab 741b                     je        0x4edfc8
004edfad 8b06                     mov       eax, dword ptr [esi]
004edfaf 57                       push      edi
004edfb0 8bce                     mov       ecx, esi
004edfb2 ff90a8010000             call      dword ptr [eax + 0x1a8]
004edfb8 83bed803000002           cmp       dword ptr [esi + 0x3d8], 2
004edfbf 88450b                   mov       byte ptr [ebp + 0xb], al
004edfc2 7418                     je        0x4edfdc
004edfc4 84c0                     test      al, al
004edfc6 7414                     je        0x4edfdc
004edfc8 5f                       pop       edi
004edfc9 32c0                     xor       al, al
004edfcb 5e                       pop       esi
004edfcc 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004edfcf 64890d00000000           mov       dword ptr fs:[0], ecx
004edfd6 8be5                     mov       esp, ebp
004edfd8 5d                       pop       ebp
004edfd9 c20c00                   ret       0xc
004edfdc 53                       push      ebx
004edfdd 8d8e84020000             lea       ecx, [esi + 0x284]
004edfe3 e87840f1ff               call      0x402060
004edfe8 85c0                     test      eax, eax
004edfea 751e                     jne       0x4ee00a
004edfec 8b17                     mov       edx, dword ptr [edi]
004edfee 8bcf                     mov       ecx, edi
004edff0 ff92a0020000             call      dword ptr [edx + 0x2a0]
004edff6 8bd8                     mov       ebx, eax
004edff8 8b06                     mov       eax, dword ptr [esi]
004edffa 8bce                     mov       ecx, esi
004edffc ff90a0020000             call      dword ptr [eax + 0x2a0]
004ee002 3bc3                     cmp       eax, ebx
004ee004 0f84b0000000             je        0x4ee0ba
004ee00a 8d8e8c020000             lea       ecx, [esi + 0x28c]
004ee010 e84b40f1ff               call      0x402060
004ee015 85c0                     test      eax, eax
004ee017 7530                     jne       0x4ee049
004ee019 8a8740040000             mov       al, byte ptr [edi + 0x440]
004ee01f 84c0                     test      al, al
004ee021 7526                     jne       0x4ee049
004ee023 57                       push      edi
004ee024 8bce                     mov       ecx, esi
004ee026 e8a5abffff               call      0x4e8bd0
004ee02b 84c0                     test      al, al
004ee02d 751a                     jne       0x4ee049
004ee02f 8b17                     mov       edx, dword ptr [edi]
004ee031 8bcf                     mov       ecx, edi
004ee033 ff92a0020000             call      dword ptr [edx + 0x2a0]
004ee039 8bd8                     mov       ebx, eax
004ee03b 8b06                     mov       eax, dword ptr [esi]
004ee03d 8bce                     mov       ecx, esi
004ee03f ff90a0020000             call      dword ptr [eax + 0x2a0]
004ee045 3bc3                     cmp       eax, ebx
004ee047 7571                     jne       0x4ee0ba
004ee049 8d8e94020000             lea       ecx, [esi + 0x294]
004ee04f e80c40f1ff               call      0x402060
004ee054 85c0                     test      eax, eax
004ee056 750c                     jne       0x4ee064
004ee058 57                       push      edi
004ee059 8bce                     mov       ecx, esi
004ee05b e870abffff               call      0x4e8bd0
004ee060 84c0                     test      al, al
004ee062 7556                     jne       0x4ee0ba
004ee064 8d4dbc                   lea       ecx, [ebp - 0x44]
004ee067 e84492f7ff               call      0x4672b0
004ee06c 8b16                     mov       edx, dword ptr [esi]
004ee06e 8d45bc                   lea       eax, [ebp - 0x44]
004ee071 50                       push      eax
004ee072 57                       push      edi
004ee073 8bce                     mov       ecx, esi
004ee075 c745fc00000000           mov       dword ptr [ebp - 4], 0
004ee07c ff9240020000             call      dword ptr [edx + 0x240]
004ee082 8ad8                     mov       bl, al
004ee084 84db                     test      bl, bl
004ee086 885df3                   mov       byte ptr [ebp - 0xd], bl
004ee089 0f84c1000000             je        0x4ee150
004ee08f 83bed803000002           cmp       dword ptr [esi + 0x3d8], 2
004ee096 7537                     jne       0x4ee0cf
004ee098 57                       push      edi
004ee099 8d4d0b                   lea       ecx, [ebp + 0xb]
004ee09c 51                       push      ecx
004ee09d 8bce                     mov       ecx, esi
004ee09f e80cfeffff               call      0x4edeb0
004ee0a4 8a450b                   mov       al, byte ptr [ebp + 0xb]
004ee0a7 84c0                     test      al, al
004ee0a9 7424                     je        0x4ee0cf
004ee0ab 8d4dbc                   lea       ecx, [ebp - 0x44]
004ee0ae c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004ee0b5 e84662f1ff               call      0x404300
004ee0ba 5b                       pop       ebx
004ee0bb 5f                       pop       edi
004ee0bc 32c0                     xor       al, al
004ee0be 5e                       pop       esi
004ee0bf 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004ee0c2 64890d00000000           mov       dword ptr fs:[0], ecx
004ee0c9 8be5                     mov       esp, ebp
004ee0cb 5d                       pop       ebp
004ee0cc c20c00                   ret       0xc
004ee0cf 8b16                     mov       edx, dword ptr [esi]
004ee0d1 8b1f                     mov       ebx, dword ptr [edi]
004ee0d3 8bce                     mov       ecx, esi
004ee0d5 c745ec64000000           mov       dword ptr [ebp - 0x14], 0x64
004ee0dc ff92c8010000             call      dword ptr [edx + 0x1c8]
004ee0e2 50                       push      eax
004ee0e3 8d45ec                   lea       eax, [ebp - 0x14]
004ee0e6 50                       push      eax
004ee0e7 8bcf                     mov       ecx, edi
004ee0e9 ff9310030000             call      dword ptr [ebx + 0x310]
004ee0ef 83f803                   cmp       eax, 3
004ee0f2 74b7                     je        0x4ee0ab
004ee0f4 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
004ee0f7 85c9                     test      ecx, ecx
004ee0f9 7409                     je        0x4ee104
004ee0fb 8d55bc                   lea       edx, [ebp - 0x44]
004ee0fe 52                       push      edx
004ee0ff e81c73fcff               call      0x4b5420
004ee104 8a450c                   mov       al, byte ptr [ebp + 0xc]
004ee107 84c0                     test      al, al
004ee109 7525                     jne       0x4ee130
004ee10b 8d4dbc                   lea       ecx, [ebp - 0x44]
004ee10e c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004ee115 e8e661f1ff               call      0x404300
004ee11a 8a45f3                   mov       al, byte ptr [ebp - 0xd]
004ee11d 5b                       pop       ebx
004ee11e 5f                       pop       edi
004ee11f 5e                       pop       esi
004ee120 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004ee123 64890d00000000           mov       dword ptr fs:[0], ecx
004ee12a 8be5                     mov       esp, ebp
004ee12c 5d                       pop       ebp
004ee12d c20c00                   ret       0xc
004ee130 8b06                     mov       eax, dword ptr [esi]
004ee132 57                       push      edi
004ee133 8bce                     mov       ecx, esi
004ee135 ff90a4010000             call      dword ptr [eax + 0x1a4]
004ee13b 6a01                     push      1
004ee13d 6a00                     push      0
004ee13f 8d4dbc                   lea       ecx, [ebp - 0x44]
004ee142 51                       push      ecx
004ee143 57                       push      edi
004ee144 56                       push      esi
004ee145 e8a6caffff               call      0x4eabf0
004ee14a 8a5df3                   mov       bl, byte ptr [ebp - 0xd]
004ee14d 83c414                   add       esp, 0x14
004ee150 8d4dbc                   lea       ecx, [ebp - 0x44]
004ee153 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
004ee15a e8a161f1ff               call      0x404300
004ee15f 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004ee162 8ac3                     mov       al, bl
004ee164 5b                       pop       ebx
004ee165 5f                       pop       edi
004ee166 5e                       pop       esi
004ee167 64890d00000000           mov       dword ptr fs:[0], ecx
004ee16e 8be5                     mov       esp, ebp
004ee170 5d                       pop       ebp
004ee171 c20c00                   ret       0xc
