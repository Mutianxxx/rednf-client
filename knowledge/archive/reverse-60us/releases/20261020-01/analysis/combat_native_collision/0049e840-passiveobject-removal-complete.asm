0049e840 55                       push      ebp
0049e841 8bec                     mov       ebp, esp
0049e843 6aff                     push      -1
0049e845 681a6bc500               push      0xc56b1a
0049e84a 64a100000000             mov       eax, dword ptr fs:[0]
0049e850 50                       push      eax
0049e851 64892500000000           mov       dword ptr fs:[0], esp
0049e858 83ec10                   sub       esp, 0x10
0049e85b 8b4508                   mov       eax, dword ptr [ebp + 8]
0049e85e 53                       push      ebx
0049e85f 50                       push      eax
0049e860 8bd9                     mov       ebx, ecx
0049e862 e8b9a8ffff               call      0x499120
0049e867 b90ce6ff00               mov       ecx, 0xffe60c
0049e86c e8ef37f6ff               call      0x402060
0049e871 85c0                     test      eax, eax
0049e873 0f85d3010000             jne       0x49ea4c
0049e879 8b8300010000             mov       eax, dword ptr [ebx + 0x100]
0049e87f 85c0                     test      eax, eax
0049e881 0f84c5010000             je        0x49ea4c
0049e887 8b8814010000             mov       ecx, dword ptr [eax + 0x114]
0049e88d 85c9                     test      ecx, ecx
0049e88f 0f84b7010000             je        0x49ea4c
0049e895 8b0d48280001             mov       ecx, dword ptr [0x1002848]
0049e89b 81c140100000             add       ecx, 0x1040
0049e8a1 e8ba37f6ff               call      0x402060
0049e8a6 83f803                   cmp       eax, 3
0049e8a9 0f859d010000             jne       0x49ea4c
0049e8af 8b8b00010000             mov       ecx, dword ptr [ebx + 0x100]
0049e8b5 8b8114010000             mov       eax, dword ptr [ecx + 0x114]
0049e8bb 56                       push      esi
0049e8bc 8bb0b4000000             mov       esi, dword ptr [eax + 0xb4]
0049e8c2 85f6                     test      esi, esi
0049e8c4 0f8481010000             je        0x49ea4b
0049e8ca 57                       push      edi
0049e8cb 8d7e10                   lea       edi, [esi + 0x10]
0049e8ce 8bcf                     mov       ecx, edi
0049e8d0 e89b250000               call      0x4a0e70
0049e8d5 84c0                     test      al, al
0049e8d7 0f856d010000             jne       0x49ea4a
0049e8dd b9604c0001               mov       ecx, 0x1004c60
0049e8e2 e87937f6ff               call      0x402060
0049e8e7 8bcf                     mov       ecx, edi
0049e8e9 894508                   mov       dword ptr [ebp + 8], eax
0049e8ec e87f510b00               call      0x553a70
0049e8f1 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049e8f4 3bc8                     cmp       ecx, eax
0049e8f6 0f834e010000             jae       0x49ea4a
0049e8fc 8d5508                   lea       edx, [ebp + 8]
0049e8ff 33ff                     xor       edi, edi
0049e901 52                       push      edx
0049e902 8d4de4                   lea       ecx, [ebp - 0x1c]
0049e905 897d08                   mov       dword ptr [ebp + 8], edi
0049e908 e84338f6ff               call      0x402150
0049e90d b9604c0001               mov       ecx, 0x1004c60
0049e912 897dfc                   mov       dword ptr [ebp - 4], edi
0049e915 c6450b00                 mov       byte ptr [ebp + 0xb], 0
0049e919 897df0                   mov       dword ptr [ebp - 0x10], edi
0049e91c e83f37f6ff               call      0x402060
0049e921 8b4e14                   mov       ecx, dword ptr [esi + 0x14]
0049e924 c1e004                   shl       eax, 4
0049e927 03c1                     add       eax, ecx
0049e929 8bc8                     mov       ecx, eax
0049e92b e820ad2700               call      0x719650
0049e930 85c0                     test      eax, eax
0049e932 0f86e7000000             jbe       0x49ea1f
0049e938 eb06                     jmp       0x49e940
0049e93a 8d9b00000000             lea       ebx, [ebx]
0049e940 b9604c0001               mov       ecx, 0x1004c60
0049e945 e81637f6ff               call      0x402060
0049e94a 8b4e14                   mov       ecx, dword ptr [esi + 0x14]
0049e94d c1e004                   shl       eax, 4
0049e950 03c1                     add       eax, ecx
0049e952 8b4004                   mov       eax, dword ptr [eax + 4]
0049e955 833c0700                 cmp       dword ptr [edi + eax], 0
0049e959 7574                     jne       0x49e9cf
0049e95b b9604c0001               mov       ecx, 0x1004c60
0049e960 e8fb36f6ff               call      0x402060
0049e965 8b4e14                   mov       ecx, dword ptr [esi + 0x14]
0049e968 c1e004                   shl       eax, 4
0049e96b 03c1                     add       eax, ecx
0049e96d 8b4004                   mov       eax, dword ptr [eax + 4]
0049e970 8b440704                 mov       eax, dword ptr [edi + eax + 4]
0049e974 3b8368080000             cmp       eax, dword ptr [ebx + 0x868]
0049e97a 7553                     jne       0x49e9cf
0049e97c b9604c0001               mov       ecx, 0x1004c60
0049e981 e8da36f6ff               call      0x402060
0049e986 8b4e14                   mov       ecx, dword ptr [esi + 0x14]
0049e989 c1e004                   shl       eax, 4
0049e98c 03c1                     add       eax, ecx
0049e98e 8b4004                   mov       eax, dword ptr [eax + 4]
0049e991 8b4c0708                 mov       ecx, dword ptr [edi + eax + 8]
0049e995 85c9                     test      ecx, ecx
0049e997 7436                     je        0x49e9cf
0049e999 b9604c0001               mov       ecx, 0x1004c60
0049e99e e8bd36f6ff               call      0x402060
0049e9a3 8b4e14                   mov       ecx, dword ptr [esi + 0x14]
0049e9a6 c1e004                   shl       eax, 4
0049e9a9 03c1                     add       eax, ecx
0049e9ab 8b4004                   mov       eax, dword ptr [eax + 4]
0049e9ae 8b540708                 mov       edx, dword ptr [edi + eax + 8]
0049e9b2 8d440708                 lea       eax, [edi + eax + 8]
0049e9b6 4a                       dec       edx
0049e9b7 8bcb                     mov       ecx, ebx
0049e9b9 8910                     mov       dword ptr [eax], edx
0049e9bb c6450b01                 mov       byte ptr [ebp + 0xb], 1
0049e9bf e8ccd6ffff               call      0x49c090
0049e9c4 84c0                     test      al, al
0049e9c6 7407                     je        0x49e9cf
0049e9c8 8bcb                     mov       ecx, ebx
0049e9ca e891e8ffff               call      0x49d260
0049e9cf b9604c0001               mov       ecx, 0x1004c60
0049e9d4 e88736f6ff               call      0x402060
0049e9d9 8b4e14                   mov       ecx, dword ptr [esi + 0x14]
0049e9dc c1e004                   shl       eax, 4
0049e9df 03c1                     add       eax, ecx
0049e9e1 8b4004                   mov       eax, dword ptr [eax + 4]
0049e9e4 8b4c0708                 mov       ecx, dword ptr [edi + eax + 8]
0049e9e8 8d55ec                   lea       edx, [ebp - 0x14]
0049e9eb 894dec                   mov       dword ptr [ebp - 0x14], ecx
0049e9ee 52                       push      edx
0049e9ef 8d4de4                   lea       ecx, [ebp - 0x1c]
0049e9f2 e81912f7ff               call      0x40fc10
0049e9f7 ff45f0                   inc       dword ptr [ebp - 0x10]
0049e9fa b9604c0001               mov       ecx, 0x1004c60
0049e9ff 83c70c                   add       edi, 0xc
0049ea02 e85936f6ff               call      0x402060
0049ea07 8b4e14                   mov       ecx, dword ptr [esi + 0x14]
0049ea0a c1e004                   shl       eax, 4
0049ea0d 03c1                     add       eax, ecx
0049ea0f 8bc8                     mov       ecx, eax
0049ea11 e83aac2700               call      0x719650
0049ea16 3945f0                   cmp       dword ptr [ebp - 0x10], eax
0049ea19 0f8221ffffff             jb        0x49e940
0049ea1f 8d4de4                   lea       ecx, [ebp - 0x1c]
0049ea22 e83936f6ff               call      0x402060
0049ea27 85c0                     test      eax, eax
0049ea29 7510                     jne       0x49ea3b
0049ea2b 8a450b                   mov       al, byte ptr [ebp + 0xb]
0049ea2e 84c0                     test      al, al
0049ea30 7409                     je        0x49ea3b
0049ea32 6a01                     push      1
0049ea34 8bcb                     mov       ecx, ebx
0049ea36 e8f5280000               call      0x4a1330
0049ea3b 8d4de4                   lea       ecx, [ebp - 0x1c]
0049ea3e c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
0049ea45 e8c635f6ff               call      0x402010
0049ea4a 5f                       pop       edi
0049ea4b 5e                       pop       esi
0049ea4c 8b03                     mov       eax, dword ptr [ebx]
0049ea4e 6a00                     push      0
0049ea50 8bcb                     mov       ecx, ebx
0049ea52 ff90d0020000             call      dword ptr [eax + 0x2d0]
0049ea58 8b13                     mov       edx, dword ptr [ebx]
0049ea5a 6a00                     push      0
0049ea5c 8bcb                     mov       ecx, ebx
0049ea5e ff92d8020000             call      dword ptr [edx + 0x2d8]
0049ea64 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0049ea67 5b                       pop       ebx
0049ea68 64890d00000000           mov       dword ptr fs:[0], ecx
0049ea6f 8be5                     mov       esp, ebp
0049ea71 5d                       pop       ebp
0049ea72 c20400                   ret       4
