0049b9f0 55                       push      ebp
0049b9f1 8bec                     mov       ebp, esp
0049b9f3 51                       push      ecx
0049b9f4 53                       push      ebx
0049b9f5 56                       push      esi
0049b9f6 57                       push      edi
0049b9f7 8bf1                     mov       esi, ecx
0049b9f9 8b06                     mov       eax, dword ptr [esi]
0049b9fb 33db                     xor       ebx, ebx
0049b9fd 53                       push      ebx
0049b9fe ff5060                   call      dword ptr [eax + 0x60]
0049ba01 8b0d1c600101             mov       ecx, dword ptr [0x101601c]
0049ba07 8b01                     mov       eax, dword ptr [ecx]
0049ba09 3bc1                     cmp       eax, ecx
0049ba0b 8945fc                   mov       dword ptr [ebp - 4], eax
0049ba0e 743c                     je        0x49ba4c
0049ba10 8b780c                   mov       edi, dword ptr [eax + 0xc]
0049ba13 3bfb                     cmp       edi, ebx
0049ba15 7422                     je        0x49ba39
0049ba17 397758                   cmp       dword ptr [edi + 0x58], esi
0049ba1a 751d                     jne       0x49ba39
0049ba1c 8b0dd4f10401             mov       ecx, dword ptr [0x104f1d4]
0049ba22 51                       push      ecx
0049ba23 8bcf                     mov       ecx, edi
0049ba25 e8d6c60900               call      0x538100
0049ba2a 3bc6                     cmp       eax, esi
0049ba2c 8bcf                     mov       ecx, edi
0049ba2e 7403                     je        0x49ba33
0049ba30 50                       push      eax
0049ba31 eb01                     jmp       0x49ba34
0049ba33 53                       push      ebx
0049ba34 e8f7c40900               call      0x537f30
0049ba39 8d4dfc                   lea       ecx, [ebp - 4]
0049ba3c e87f78f9ff               call      0x4332c0
0049ba41 8b45fc                   mov       eax, dword ptr [ebp - 4]
0049ba44 3b051c600101             cmp       eax, dword ptr [0x101601c]
0049ba4a 75c4                     jne       0x49ba10
0049ba4c 8b3dcca02301             mov       edi, dword ptr [0x123a0cc]
0049ba52 3bfb                     cmp       edi, ebx
0049ba54 740f                     je        0x49ba65
0049ba56 8b16                     mov       edx, dword ptr [esi]
0049ba58 8bce                     mov       ecx, esi
0049ba5a ff5244                   call      dword ptr [edx + 0x44]
0049ba5d 50                       push      eax
0049ba5e 8bcf                     mov       ecx, edi
0049ba60 e8ab276f00               call      0xb8e210
0049ba65 8b8e00010000             mov       ecx, dword ptr [esi + 0x100]
0049ba6b 3bcb                     cmp       ecx, ebx
0049ba6d 7408                     je        0x49ba77
0049ba6f 53                       push      ebx
0049ba70 53                       push      ebx
0049ba71 56                       push      esi
0049ba72 e8790c0700               call      0x50c6f0
0049ba77 8bbef8000000             mov       edi, dword ptr [esi + 0xf8]
0049ba7d 3bfb                     cmp       edi, ebx
0049ba7f 7410                     je        0x49ba91
0049ba81 8bcf                     mov       ecx, edi
0049ba83 e8d8060000               call      0x49c160
0049ba88 57                       push      edi
0049ba89 e8c264f6ff               call      0x401f50
0049ba8e 83c404                   add       esp, 4
0049ba91 8bbe18010000             mov       edi, dword ptr [esi + 0x118]
0049ba97 3bfb                     cmp       edi, ebx
0049ba99 899ef8000000             mov       dword ptr [esi + 0xf8], ebx
0049ba9f 7410                     je        0x49bab1
0049baa1 8bcf                     mov       ecx, edi
0049baa3 e828cff6ff               call      0x4089d0
0049baa8 57                       push      edi
0049baa9 e8a264f6ff               call      0x401f50
0049baae 83c404                   add       esp, 4
0049bab1 899e18010000             mov       dword ptr [esi + 0x118], ebx
0049bab7 eb07                     jmp       0x49bac0
0049bab9 8da42400000000           lea       esp, [esp]
0049bac0 8b8e20010000             mov       ecx, dword ptr [esi + 0x120]
0049bac6 33ff                     xor       edi, edi
0049bac8 3bcf                     cmp       ecx, edi
0049baca 7447                     je        0x49bb13
0049bacc 8b8624010000             mov       eax, dword ptr [esi + 0x124]
0049bad2 2bc1                     sub       eax, ecx
0049bad4 c1f802                   sar       eax, 2
0049bad7 3bd8                     cmp       ebx, eax
0049bad9 7338                     jae       0x49bb13
0049badb 8d3c9d00000000           lea       edi, [ebx*4]
0049bae2 8bc1                     mov       eax, ecx
0049bae4 03c7                     add       eax, edi
0049bae6 8b00                     mov       eax, dword ptr [eax]
0049bae8 85c0                     test      eax, eax
0049baea 8945fc                   mov       dword ptr [ebp - 4], eax
0049baed 7413                     je        0x49bb02
0049baef 8bc8                     mov       ecx, eax
0049baf1 e8dacef6ff               call      0x4089d0
0049baf6 8b45fc                   mov       eax, dword ptr [ebp - 4]
0049baf9 50                       push      eax
0049bafa e85164f6ff               call      0x401f50
0049baff 83c404                   add       esp, 4
0049bb02 8b8620010000             mov       eax, dword ptr [esi + 0x120]
0049bb08 03c7                     add       eax, edi
0049bb0a c70000000000             mov       dword ptr [eax], 0
0049bb10 43                       inc       ebx
0049bb11 ebad                     jmp       0x49bac0
0049bb13 8b8620010000             mov       eax, dword ptr [esi + 0x120]
0049bb19 3bc7                     cmp       eax, edi
0049bb1b 7409                     je        0x49bb26
0049bb1d 50                       push      eax
0049bb1e e8ba447600               call      0xbfffdd
0049bb23 83c404                   add       esp, 4
0049bb26 89be20010000             mov       dword ptr [esi + 0x120], edi
0049bb2c 89be24010000             mov       dword ptr [esi + 0x124], edi
0049bb32 89be28010000             mov       dword ptr [esi + 0x128], edi
0049bb38 8b8e4c010000             mov       ecx, dword ptr [esi + 0x14c]
0049bb3e 3bcf                     cmp       ecx, edi
0049bb40 7406                     je        0x49bb48
0049bb42 8b11                     mov       edx, dword ptr [ecx]
0049bb44 6a01                     push      1
0049bb46 ff12                     call      dword ptr [edx]
0049bb48 8b8e50010000             mov       ecx, dword ptr [esi + 0x150]
0049bb4e 3bcf                     cmp       ecx, edi
0049bb50 89be4c010000             mov       dword ptr [esi + 0x14c], edi
0049bb56 7406                     je        0x49bb5e
0049bb58 8b01                     mov       eax, dword ptr [ecx]
0049bb5a 6a01                     push      1
0049bb5c ff10                     call      dword ptr [eax]
0049bb5e 89be50010000             mov       dword ptr [esi + 0x150], edi
0049bb64 33db                     xor       ebx, ebx
0049bb66 8b8e5c010000             mov       ecx, dword ptr [esi + 0x15c]
0049bb6c 3bcf                     cmp       ecx, edi
0049bb6e 743b                     je        0x49bbab
0049bb70 8b8660010000             mov       eax, dword ptr [esi + 0x160]
0049bb76 2bc1                     sub       eax, ecx
0049bb78 c1f802                   sar       eax, 2
0049bb7b 3bd8                     cmp       ebx, eax
0049bb7d 732c                     jae       0x49bbab
0049bb7f 8d3c9d00000000           lea       edi, [ebx*4]
0049bb86 8bc1                     mov       eax, ecx
0049bb88 03c7                     add       eax, edi
0049bb8a 8b00                     mov       eax, dword ptr [eax]
0049bb8c 85c0                     test      eax, eax
0049bb8e 7408                     je        0x49bb98
0049bb90 8b10                     mov       edx, dword ptr [eax]
0049bb92 6a01                     push      1
0049bb94 8bc8                     mov       ecx, eax
0049bb96 ff12                     call      dword ptr [edx]
0049bb98 8b865c010000             mov       eax, dword ptr [esi + 0x15c]
0049bb9e 03c7                     add       eax, edi
0049bba0 43                       inc       ebx
0049bba1 c70000000000             mov       dword ptr [eax], 0
0049bba7 33ff                     xor       edi, edi
0049bba9 ebbb                     jmp       0x49bb66
0049bbab 8b                       .byte     0x8b
0049bbac 865c0100                 xchg      byte ptr [ecx + eax], bl
