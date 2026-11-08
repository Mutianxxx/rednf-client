004392e0 55                       push      ebp
004392e1 8bec                     mov       ebp, esp
004392e3 51                       push      ecx
004392e4 56                       push      esi
004392e5 57                       push      edi
004392e6 8b7d08                   mov       edi, dword ptr [ebp + 8]
004392e9 8bf1                     mov       esi, ecx
004392eb 3bf7                     cmp       esi, edi
004392ed 0f8467010000             je        0x43945a
004392f3 8b5704                   mov       edx, dword ptr [edi + 4]
004392f6 85d2                     test      edx, edx
004392f8 740f                     je        0x439309
004392fa 8b4f08                   mov       ecx, dword ptr [edi + 8]
004392fd 894dfc                   mov       dword ptr [ebp - 4], ecx
00439300 2bca                     sub       ecx, edx
00439302 c1f902                   sar       ecx, 2
00439305 85c9                     test      ecx, ecx
00439307 7511                     jne       0x43931a
00439309 8bce                     mov       ecx, esi
0043930b e820a3fcff               call      0x403630
00439310 5f                       pop       edi
00439311 8bc6                     mov       eax, esi
00439313 5e                       pop       esi
00439314 8be5                     mov       esp, ebp
00439316 5d                       pop       ebp
00439317 c20400                   ret       4
0043931a 8b4604                   mov       eax, dword ptr [esi + 4]
0043931d 85c0                     test      eax, eax
0043931f 53                       push      ebx
00439320 7504                     jne       0x439326
00439322 33db                     xor       ebx, ebx
00439324 eb08                     jmp       0x43932e
00439326 8b5e08                   mov       ebx, dword ptr [esi + 8]
00439329 2bd8                     sub       ebx, eax
0043932b c1fb02                   sar       ebx, 2
0043932e 3bcb                     cmp       ecx, ebx
00439330 776b                     ja        0x43939d
00439332 8bd8                     mov       ebx, eax
00439334 8b45fc                   mov       eax, dword ptr [ebp - 4]
00439337 8bfa                     mov       edi, edx
00439339 3bf8                     cmp       edi, eax
0043933b 7418                     je        0x439355
0043933d 8d4900                   lea       ecx, [ecx]
00439340 57                       push      edi
00439341 8bcb                     mov       ecx, ebx
00439343 e84880fcff               call      0x401390
00439348 8b45fc                   mov       eax, dword ptr [ebp - 4]
0043934b 83c704                   add       edi, 4
0043934e 83c304                   add       ebx, 4
00439351 3bf8                     cmp       edi, eax
00439353 75eb                     jne       0x439340
00439355 8b4608                   mov       eax, dword ptr [esi + 8]
00439358 50                       push      eax
00439359 53                       push      ebx
0043935a 8bce                     mov       ecx, esi
0043935c e8bfa1fcff               call      0x403520
00439361 8b4508                   mov       eax, dword ptr [ebp + 8]
00439364 8b4804                   mov       ecx, dword ptr [eax + 4]
00439367 85c9                     test      ecx, ecx
00439369 7516                     jne       0x439381
0043936b 8b4e04                   mov       ecx, dword ptr [esi + 4]
0043936e 33c0                     xor       eax, eax
00439370 5b                       pop       ebx
00439371 8d1481                   lea       edx, [ecx + eax*4]
00439374 5f                       pop       edi
00439375 895608                   mov       dword ptr [esi + 8], edx
00439378 8bc6                     mov       eax, esi
0043937a 5e                       pop       esi
0043937b 8be5                     mov       esp, ebp
0043937d 5d                       pop       ebp
0043937e c20400                   ret       4
00439381 8b4008                   mov       eax, dword ptr [eax + 8]
00439384 2bc1                     sub       eax, ecx
00439386 8b4e04                   mov       ecx, dword ptr [esi + 4]
00439389 c1f802                   sar       eax, 2
0043938c 5b                       pop       ebx
0043938d 8d1481                   lea       edx, [ecx + eax*4]
00439390 5f                       pop       edi
00439391 895608                   mov       dword ptr [esi + 8], edx
00439394 8bc6                     mov       eax, esi
00439396 5e                       pop       esi
00439397 8be5                     mov       esp, ebp
00439399 5d                       pop       ebp
0043939a c20400                   ret       4
0043939d 85c0                     test      eax, eax
0043939f 7504                     jne       0x4393a5
004393a1 33d2                     xor       edx, edx
004393a3 eb08                     jmp       0x4393ad
004393a5 8b560c                   mov       edx, dword ptr [esi + 0xc]
004393a8 2bd0                     sub       edx, eax
004393aa c1fa02                   sar       edx, 2
004393ad 3bca                     cmp       ecx, edx
004393af 774b                     ja        0x4393fc
004393b1 85c0                     test      eax, eax
004393b3 7504                     jne       0x4393b9
004393b5 33c9                     xor       ecx, ecx
004393b7 eb08                     jmp       0x4393c1
004393b9 8b4e08                   mov       ecx, dword ptr [esi + 8]
004393bc 2bc8                     sub       ecx, eax
004393be c1                       .byte     0xc1
004393bf f9                       stc       
