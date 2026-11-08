004eb300 52                       push      edx
004eb301 57                       push      edi
004eb302 e8f9edffff               call      0x4ea100
004eb307 8b4df8                   mov       ecx, dword ptr [ebp - 8]
004eb30a 8b55fc                   mov       edx, dword ptr [ebp - 4]
004eb30d 83c428                   add       esp, 0x28
004eb310 894e04                   mov       dword ptr [esi + 4], ecx
004eb313 8a4d2b                   mov       cl, byte ptr [ebp + 0x2b]
004eb316 891e                     mov       dword ptr [esi], ebx
004eb318 895608                   mov       dword ptr [esi + 8], edx
004eb31b 5b                       pop       ebx
004eb31c 884e58                   mov       byte ptr [esi + 0x58], cl
004eb31f 5e                       pop       esi
004eb320 5f                       pop       edi
004eb321 8be5                     mov       esp, ebp
004eb323 5d                       pop       ebp
004eb324 c23800                   ret       0x38
004eb327 8b553c                   mov       edx, dword ptr [ebp + 0x3c]
004eb32a 8b4d38                   mov       ecx, dword ptr [ebp + 0x38]
004eb32d 52                       push      edx
004eb32e 8b5534                   mov       edx, dword ptr [ebp + 0x34]
004eb331 51                       push      ecx
004eb332 8b4d30                   mov       ecx, dword ptr [ebp + 0x30]
004eb335 52                       push      edx
004eb336 8b552c                   mov       edx, dword ptr [ebp + 0x2c]
004eb339 51                       push      ecx
004eb33a 8b4d18                   mov       ecx, dword ptr [ebp + 0x18]
004eb33d 52                       push      edx
004eb33e 8b5514                   mov       edx, dword ptr [ebp + 0x14]
004eb341 50                       push      eax
004eb342 8b451c                   mov       eax, dword ptr [ebp + 0x1c]
004eb345 50                       push      eax
004eb346 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004eb349 51                       push      ecx
004eb34a 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004eb34d 52                       push      edx
004eb34e 8b5508                   mov       edx, dword ptr [ebp + 8]
004eb351 50                       push      eax
004eb352 51                       push      ecx
004eb353 52                       push      edx
004eb354 e847ebffff               call      0x4e9ea0
004eb359 83c430                   add       esp, 0x30
004eb35c 5e                       pop       esi
004eb35d 5f                       pop       edi
004eb35e 8be5                     mov       esp, ebp
004eb360 5d                       pop       ebp
004eb361 c23800                   ret       0x38
004eb364 b8ffff0000               mov       eax, 0xffff
004eb369 5f                       pop       edi
004eb36a 8be5                     mov       esp, ebp
004eb36c 5d                       pop       ebp
004eb36d c23800                   ret       0x38
004eb370 55                       push      ebp
004eb371 8bec                     mov       ebp, esp
004eb373 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004eb376 56                       push      esi
004eb377 57                       push      edi
004eb378 8b7d08                   mov       edi, dword ptr [ebp + 8]
004eb37b 8b17                     mov       edx, dword ptr [edi]
004eb37d 8bf1                     mov       esi, ecx
004eb37f 50                       push      eax
004eb380 8bcf                     mov       ecx, edi
004eb382 ff92f4000000             call      dword ptr [edx + 0xf4]
004eb388 50                       push      eax
004eb389 8b06                     mov       eax, dword ptr [esi]
004eb38b 57                       push      edi
004eb38c 8bce                     mov       ecx, esi
004eb38e ff90f4000000             call      dword ptr [eax + 0xf4]
004eb394 50                       push      eax
004eb395 56                       push      esi
004eb396 e875e7ffff               call      0x4e9b10
004eb39b 83c414                   add       esp, 0x14
004eb39e 5f                       pop       edi
004eb39f 5e                       pop       esi
004eb3a0 5d                       pop       ebp
004eb3a1 c20800                   ret       8
004eb3a4 cc                       int3      
004eb3a5 cc                       int3      
004eb3a6 cc                       int3      
004eb3a7 cc                       int3      
004eb3a8 cc                       int3      
004eb3a9 cc                       int3      
004eb3aa cc                       int3      
004eb3ab cc                       int3      
004eb3ac cc                       int3      
004eb3ad cc                       int3      
004eb3ae cc                       int3      
004eb3af cc                       int3      
004eb3b0 55                       push      ebp
004eb3b1 8bec                     mov       ebp, esp
004eb3b3 51                       push      ecx
004eb3b4 53                       push      ebx
004eb3b5 56                       push      esi
004eb3b6 57                       push      edi
004eb3b7 8b7d08                   mov       edi, dword ptr [ebp + 8]
004eb3ba 8bf1                     mov       esi, ecx
004eb3bc 8b06                     mov       eax, dword ptr [esi]
004eb3be 57                       push      edi
004eb3bf 8d4dfc                   lea       ecx, [ebp - 4]
004eb3c2 51                       push      ecx
004eb3c3 8bce                     mov       ecx, esi
004eb3c5 c745fc64000000           mov       dword ptr [ebp - 4], 0x64
004eb3cc ff9010030000             call      dword ptr [eax + 0x310]
004eb3d2 8b5d10                   mov       ebx, dword ptr [ebp + 0x10]
004eb3d5 84db                     test      bl, bl
004eb3d7 0f8594010000             jne       0x4eb571
004eb3dd 83f802                   cmp       eax, 2
004eb3e0 0f84d7010000             je        0x4eb5bd
004eb3e6 8d8ebc040000             lea       ecx, [esi + 0x4bc]
004eb3ec e86f6cf1ff               call      0x402060
004eb3f1 85c0                     test      eax, eax
004eb3f3 740d                     je        0x4eb402
004eb3f5 8d8ec4040000             lea       ecx, [esi + 0x4c4]
004eb3fb e8606cf1ff               call      0x402060
004eb400 eb07                     jmp       0x4eb409
004eb402 8bce                     mov       ecx, esi
004eb404 e8d7ebfaff               call      0x499fe0
004eb409 83f802                   cmp       eax, 2
004eb40c 7453                     je        0x4eb461
004eb40e 8b17                     mov       edx, dword ptr [edi]
004eb410 8bcf                     mov       ecx, edi
004eb412 ff929c010000             call      dword ptr [edx + 0x19c]
004eb418 8bc8                     mov       ecx, eax
004eb41a 81c180010000             add       ecx, 0x180
004eb420 e83b6cf1ff               call      0x402060
004eb425 8bd8                     mov       ebx, eax
004eb427 8a8640020000             mov       al, byte ptr [esi + 0x240]
004eb42d 84c0                     test      al, al
004eb42f 7430                     je        0x4eb461
004eb431 85db                     test      ebx, ebx
004eb433 7e2c                     jle       0x4eb461
004eb435 8b86b0010000             mov       eax, dword ptr [esi + 0x1b0]
004eb43b 85c0                     test      eax, eax
004eb43d 7413                     je        0x4eb452
004eb43f 83f801                   cmp       eax, 1
004eb442 751d                     jne       0x4eb461
004eb444 8b06                     mov       eax, dword ptr [esi]
004eb446 8bce                     mov       ecx, esi
004eb448 ff9030010000             call      dword ptr [eax + 0x130]
004eb44e 3bc3                     cmp       eax, ebx
