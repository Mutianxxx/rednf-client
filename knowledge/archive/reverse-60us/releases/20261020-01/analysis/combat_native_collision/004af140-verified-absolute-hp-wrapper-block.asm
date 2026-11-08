004af140 55                       push      ebp
004af141 8bec                     mov       ebp, esp
004af143 83ec08                   sub       esp, 8
004af146 56                       push      esi
004af147 8bf1                     mov       esi, ecx
004af149 e842cffeff               call      0x49c090
004af14e 84c0                     test      al, al
004af150 0f84b2010000             je        0x4af308
004af156 8b06                     mov       eax, dword ptr [esi]
004af158 8bce                     mov       ecx, esi
004af15a ff90dc030000             call      dword ptr [eax + 0x3dc]
004af160 84c0                     test      al, al
004af162 0f85a0010000             jne       0x4af308
004af168 8b16                     mov       edx, dword ptr [esi]
004af16a 53                       push      ebx
004af16b 57                       push      edi
004af16c 8bce                     mov       ecx, esi
004af16e ff9234020000             call      dword ptr [edx + 0x234]
004af174 8b7d08                   mov       edi, dword ptr [ebp + 8]
004af177 2bc7                     sub       eax, edi
004af179 85ff                     test      edi, edi
004af17b 894508                   mov       dword ptr [ebp + 8], eax
004af17e 0f8dad000000             jge       0x4af231
004af184 db4508                   fild      dword ptr [ebp + 8]
004af187 8b06                     mov       eax, dword ptr [esi]
004af189 8bce                     mov       ecx, esi
004af18b d95df8                   fstp      dword ptr [ebp - 8]
004af18e ff9038020000             call      dword ptr [eax + 0x238]
004af194 8945fc                   mov       dword ptr [ebp - 4], eax
004af197 db45fc                   fild      dword ptr [ebp - 4]
004af19a d80d64b7cc00             fmul      dword ptr [0xccb764]
004af1a0 d85df8                   fcomp     dword ptr [ebp - 8]
004af1a3 dfe0                     fnstsw    ax
004af1a5 f6c441                   test      ah, 0x41
004af1a8 0f8a83000000             jp        0x4af231
004af1ae 80be7018000001           cmp       byte ptr [esi + 0x1870], 1
004af1b5 757a                     jne       0x4af231
004af1b7 6a01                     push      1
004af1b9 8bce                     mov       ecx, esi
004af1bb e820690000               call      0x4b5ae0
004af1c0 8b5d10                   mov       ebx, dword ptr [ebp + 0x10]
004af1c3 85db                     test      ebx, ebx
004af1c5 746a                     je        0x4af231
004af1c7 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004af1cd 81c140100000             add       ecx, 0x1040
004af1d3 e8882ef5ff               call      0x402060
004af1d8 83f804                   cmp       eax, 4
004af1db 7510                     jne       0x4af1ed
004af1dd 8b16                     mov       edx, dword ptr [esi]
004af1df 6811010000               push      0x111
004af1e4 8bce                     mov       ecx, esi
004af1e6 ff522c                   call      dword ptr [edx + 0x2c]
004af1e9 84c0                     test      al, al
004af1eb 7444                     je        0x4af231
004af1ed 8b03                     mov       eax, dword ptr [ebx]
004af1ef 8bcb                     mov       ecx, ebx
004af1f1 ff90a8020000             call      dword ptr [eax + 0x2a8]
004af1f7 8bd8                     mov       ebx, eax
004af1f9 85db                     test      ebx, ebx
004af1fb 7434                     je        0x4af231
004af1fd 8b13                     mov       edx, dword ptr [ebx]
004af1ff 8bcb                     mov       ecx, ebx
004af201 ff5240                   call      dword ptr [edx + 0x40]
004af204 8b0dd8e5ff00             mov       ecx, dword ptr [0xffe5d8]
004af20a 50                       push      eax
004af20b 6a03                     push      3
004af20d 6a01                     push      1
004af20f e8fcc70600               call      0x51ba10
004af214 3b1dd4f10401             cmp       ebx, dword ptr [0x104f1d4]
004af21a 7515                     jne       0x4af231
004af21c 8b8600010000             mov       eax, dword ptr [esi + 0x100]
004af222 8b8814010000             mov       ecx, dword ptr [eax + 0x114]
004af228 6a00                     push      0
004af22a 6a00                     push      0
004af22c e83fcc0800               call      0x53be70
004af231 8a450c                   mov       al, byte ptr [ebp + 0xc]
004af234 84c0                     test      al, al
004af236 753b                     jne       0x4af273
004af238 85ff                     test      edi, edi
004af23a 7e37                     jle       0x4af273
004af23c 8b16                     mov       edx, dword ptr [esi]
004af23e 8bce                     mov       ecx, esi
004af240 ff9234020000             call      dword ptr [edx + 0x234]
004af246 3bc7                     cmp       eax, edi
004af248 0f84a7000000             je        0x4af2f5
004af24e 8d9ec4150000             lea       ebx, [esi + 0x15c4]
004af254 8bcb                     mov       ecx, ebx
004af256 e8052ef5ff               call      0x402060
004af25b 83f8ff                   cmp       eax, -1
004af25e 0f8591000000             jne       0x4af2f5
004af264 8d4e20                   lea       ecx, [esi + 0x20]
004af267 e8947c6500               call      0xb06f00
004af26c 89450c                   mov       dword ptr [ebp + 0xc], eax
004af26f 8bcb                     mov       ecx, ebx
004af271 eb79                     jmp       0x4af2ec
004af273 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004af279 8b11                     mov       edx, dword ptr [ecx]
004af27b 6a01                     push      1
004af27d 6a0c                     push      0xc
004af27f ff5208                   call      dword ptr [edx + 8]
004af282 a164310001               mov       eax, dword ptr [0x1003164]
004af287 8b16                     mov       edx, dword ptr [esi]
004af289 8b18                     mov       ebx, dword ptr [eax]
004af28b 8bce                     mov       ecx, esi
004af28d ff523c                   call      dword ptr [edx + 0x3c]
004af290 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004af296 50                       push      eax
004af297 ff5324                   call      dword ptr [ebx + 0x24]
004af29a a164310001               mov       eax, dword ptr [0x1003164]
004af29f 8b16                     mov       edx, dword ptr [esi]
004af2a1 8b18                     mov       ebx, dword ptr [eax]
004af2a3 8bce                     mov       ecx, esi
004af2a5 ff5240                   call      dword ptr [edx + 0x40]
004af2a8 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004af2ae 50                       push      eax
004af2af ff5324                   call      dword ptr [ebx + 0x24]
004af2b2 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004af2b8 8b01                     mov       eax, dword ptr [ecx]
004af2ba 57                       push      edi
004af2bb ff502c                   call      dword ptr [eax + 0x2c]
004af2be 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004af2c4 8b4508                   mov       eax, dword ptr [ebp + 8]
004af2c7 8b11                     mov       edx, dword ptr [ecx]
004af2c9 50                       push      eax
004af2ca ff522c                   call      dword ptr [edx + 0x2c]
004af2cd 8b0d90070c01             mov       ecx, dword ptr [0x10c0790]
004af2d3 8b11                     mov       edx, dword ptr [ecx]
004af2d5 6a03                     push      3
004af2d7 56                       push      esi
004af2d8 6aff                     push      -1
004af2da 6a01                     push      1
004af2dc ff5244                   call      dword ptr [edx + 0x44]
004af2df c7450cffffffff           mov       dword ptr [ebp + 0xc], 0xffffffff
004af2e6 8d8ec4150000             lea       ecx, [esi + 0x15c4]
004af2ec 8d450c                   lea       eax, [ebp + 0xc]
004af2ef 50                       push      eax
004af2f0 e86b52f5ff               call      0x404560
004af2f5 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004af2f8 8b16                     mov       edx, dword ptr [esi]
004af2fa 6a00                     push      0
004af2fc 50                       push      eax
004af2fd 57                       push      edi
004af2fe 8bce                     mov       ecx, esi
004af300 ff92ec030000             call      dword ptr [edx + 0x3ec]
004af306 5f                       pop       edi
004af307 5b                       pop       ebx
004af308 5e                       pop       esi
004af309 8be5                     mov       esp, ebp
004af30b 5d                       pop       ebp
004af30c c20c00                   ret       0xc
004af30f cc                       int3      
004af310 55                       push      ebp
004af311 8bec                     mov       ebp, esp
004af313 56                       push      esi
004af314 57                       push      edi
004af315 8b7d08                   mov       edi, dword ptr [ebp + 8]
004af318 8b07                     mov       eax, dword ptr [edi]
004af31a 83f803                   cmp       eax, 3
