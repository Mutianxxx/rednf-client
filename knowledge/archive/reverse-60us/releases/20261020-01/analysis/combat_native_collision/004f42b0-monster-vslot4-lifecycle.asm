004f42b0 55                       push      ebp
004f42b1 8bec                     mov       ebp, esp
004f42b3 83ec08                   sub       esp, 8
004f42b6 53                       push      ebx
004f42b7 56                       push      esi
004f42b8 8b7508                   mov       esi, dword ptr [ebp + 8]
004f42bb 8b06                     mov       eax, dword ptr [esi]
004f42bd 83c0fc                   add       eax, -4
004f42c0 83f805                   cmp       eax, 5
004f42c3 57                       push      edi
004f42c4 8bf9                     mov       edi, ecx
004f42c6 7764                     ja        0x4f432c
004f42c8 ff248524444f00           jmp       dword ptr [eax*4 + 0x4f4424]
004f42cf 8b07                     mov       eax, dword ptr [edi]
004f42d1 6a0d                     push      0xd
004f42d3 8bcf                     mov       ecx, edi
004f42d5 ff90f0050000             call      dword ptr [eax + 0x5f0]
004f42db eb4f                     jmp       0x4f432c
004f42dd 8b17                     mov       edx, dword ptr [edi]
004f42df 8bcf                     mov       ecx, edi
004f42e1 ff9230020000             call      dword ptr [edx + 0x230]
004f42e7 83f80b                   cmp       eax, 0xb
004f42ea 7540                     jne       0x4f432c
004f42ec 8b07                     mov       eax, dword ptr [edi]
004f42ee 6a01                     push      1
004f42f0 6a01                     push      1
004f42f2 6a00                     push      0
004f42f4 6a0c                     push      0xc
004f42f6 8bcf                     mov       ecx, edi
004f42f8 ff902c020000             call      dword ptr [eax + 0x22c]
004f42fe 8b17                     mov       edx, dword ptr [edi]
004f4300 6a01                     push      1
004f4302 6a01                     push      1
004f4304 6a00                     push      0
004f4306 6a00                     push      0
004f4308 8bcf                     mov       ecx, edi
004f430a ff922c020000             call      dword ptr [edx + 0x22c]
004f4310 eb1a                     jmp       0x4f432c
004f4312 8b07                     mov       eax, dword ptr [edi]
004f4314 6a10                     push      0x10
004f4316 8bcf                     mov       ecx, edi
004f4318 ff90f0050000             call      dword ptr [eax + 0x5f0]
004f431e eb0c                     jmp       0x4f432c
004f4320 8b17                     mov       edx, dword ptr [edi]
004f4322 6a0d                     push      0xd
004f4324 8bcf                     mov       ecx, edi
004f4326 ff92f0050000             call      dword ptr [edx + 0x5f0]
004f432c 56                       push      esi
004f432d 8bcf                     mov       ecx, edi
004f432f e8dcaffbff               call      0x4af310
004f4334 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f433a 33c0                     xor       eax, eax
004f433c 8945fc                   mov       dword ptr [ebp - 4], eax
004f433f 8945f8                   mov       dword ptr [ebp - 8], eax
004f4342 8b87e8220000             mov       eax, dword ptr [edi + 0x22e8]
004f4348 85c0                     test      eax, eax
004f434a 0f84c8000000             je        0x4f4418
004f4350 8b97ec220000             mov       edx, dword ptr [edi + 0x22ec]
004f4356 2bd0                     sub       edx, eax
004f4358 b867666666               mov       eax, 0x66666667
004f435d f7ea                     imul      edx
004f435f c1fa04                   sar       edx, 4
004f4362 8bc2                     mov       eax, edx
004f4364 c1e81f                   shr       eax, 0x1f
004f4367 03c2                     add       eax, edx
004f4369 3945fc                   cmp       dword ptr [ebp - 4], eax
004f436c 0f83a6000000             jae       0x4f4418
004f4372 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004f4378 8b8728180000             mov       eax, dword ptr [edi + 0x1828]
004f437e 8d9f28180000             lea       ebx, [edi + 0x1828]
004f4384 33c2                     xor       eax, edx
004f4386 8b5304                   mov       edx, dword ptr [ebx + 4]
004f4389 2bc3                     sub       eax, ebx
004f438b 3bc2                     cmp       eax, edx
004f438d 740e                     je        0x4f439d
004f438f 6a3f                     push      0x3f
004f4391 53                       push      ebx
004f4392 e8192d6200               call      0xb170b0
004f4397 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f439d 8b4304                   mov       eax, dword ptr [ebx + 4]
004f43a0 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004f43a3 c1e002                   shl       eax, 2
004f43a6 8b3402                   mov       esi, dword ptr [edx + eax]
004f43a9 03d0                     add       edx, eax
004f43ab 33f2                     xor       esi, edx
004f43ad 3335dc012101             xor       esi, dword ptr [0x12101dc]
004f43b3 8b5148                   mov       edx, dword ptr [ecx + 0x48]
004f43b6 03c2                     add       eax, edx
004f43b8 8b10                     mov       edx, dword ptr [eax]
004f43ba 33d0                     xor       edx, eax
004f43bc 3315dc012101             xor       edx, dword ptr [0x12101dc]
004f43c2 3bf2                     cmp       esi, edx
004f43c4 740e                     je        0x4f43d4
004f43c6 6a40                     push      0x40
004f43c8 53                       push      ebx
004f43c9 e8e22c6200               call      0xb170b0
004f43ce 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f43d4 8b87e8220000             mov       eax, dword ptr [edi + 0x22e8]
004f43da 8b5df8                   mov       ebx, dword ptr [ebp - 8]
004f43dd 8b541804                 mov       edx, dword ptr [eax + ebx + 4]
004f43e1 03c3                     add       eax, ebx
004f43e3 3bf2                     cmp       esi, edx
004f43e5 751f                     jne       0x4f4406
004f43e7 8b8718230000             mov       eax, dword ptr [edi + 0x2318]
004f43ed 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
004f43f0 8b5508                   mov       edx, dword ptr [ebp + 8]
004f43f3 8d0488                   lea       eax, [eax + ecx*4]
004f43f6 8b0a                     mov       ecx, dword ptr [edx]
004f43f8 51                       push      ecx
004f43f9 8b08                     mov       ecx, dword ptr [eax]
004f43fb e8908e2500               call      0x74d290
004f4400 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004f4406 8b55fc                   mov       edx, dword ptr [ebp - 4]
004f4409 8b45f8                   mov       eax, dword ptr [ebp - 8]
004f440c 42                       inc       edx
004f440d 8955fc                   mov       dword ptr [ebp - 4], edx
004f4410 83c028                   add       eax, 0x28
004f4413 e927ffffff               jmp       0x4f433f
004f4418 5f                       pop       edi
004f4419 5e                       pop       esi
004f441a 5b                       pop       ebx
004f441b 8be5                     mov       esp, ebp
004f441d 5d                       pop       ebp
004f441e c20400                   ret       4
004f4421 8d4900                   lea       ecx, [ecx]
004f4424 cf                       iretd     
004f4425 42                       inc       edx
004f4426 4f                       dec       edi
004f4427 00dd                     add       ch, bl
004f4429 42                       inc       edx
004f442a 4f                       dec       edi
004f442b 002c43                   add       byte ptr [ebx + eax*2], ch
004f442e 4f                       dec       edi
004f442f 002c43                   add       byte ptr [ebx + eax*2], ch
004f4432 4f                       dec       edi
004f4433 0012                     add       byte ptr [edx], dl
004f4435 43                       inc       ebx
004f4436 4f                       dec       edi
004f4437 0020                     add       byte ptr [eax], ah
004f4439 43                       inc       ebx
004f443a 4f                       dec       edi
004f443b 00cc                     add       ah, cl
004f443d cc                       int3      
004f443e cc                       int3      
004f443f cc                       int3      
