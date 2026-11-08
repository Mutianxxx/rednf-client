004f4440 55                       push      ebp
004f4441 8bec                     mov       ebp, esp
004f4443 53                       push      ebx
004f4444 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004f4447 56                       push      esi
004f4448 57                       push      edi
004f4449 8bf1                     mov       esi, ecx
004f444b 33ff                     xor       edi, edi
004f444d 8d4900                   lea       ecx, [ecx]
004f4450 8b8608230000             mov       eax, dword ptr [esi + 0x2308]
004f4456 85c0                     test      eax, eax
004f4458 7432                     je        0x4f448c
004f445a 8b8e0c230000             mov       ecx, dword ptr [esi + 0x230c]
004f4460 2bc8                     sub       ecx, eax
004f4462 b8398ee338               mov       eax, 0x38e38e39
004f4467 f7e9                     imul      ecx
004f4469 c1fa03                   sar       edx, 3
004f446c 8bc2                     mov       eax, edx
004f446e c1e81f                   shr       eax, 0x1f
004f4471 03c2                     add       eax, edx
004f4473 3bf8                     cmp       edi, eax
004f4475 7315                     jae       0x4f448c
004f4477 8b8648230000             mov       eax, dword ptr [esi + 0x2348]
004f447d 8b0cb8                   mov       ecx, dword ptr [eax + edi*4]
004f4480 8d04b8                   lea       eax, [eax + edi*4]
004f4483 53                       push      ebx
004f4484 e8d7a42500               call      0x74e960
004f4489 47                       inc       edi
004f448a ebc4                     jmp       0x4f4450
004f448c 53                       push      ebx
004f448d 8bce                     mov       ecx, esi
004f448f e83cdcfbff               call      0x4b20d0
004f4494 3bde                     cmp       ebx, esi
004f4496 7537                     jne       0x4f44cf
004f4498 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004f449e 81c140100000             add       ecx, 0x1040
004f44a4 e8b7dbf0ff               call      0x402060
004f44a9 83f803                   cmp       eax, 3
004f44ac 7416                     je        0x4f44c4
004f44ae 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004f44b4 81c140100000             add       ecx, 0x1040
004f44ba e8a1dbf0ff               call      0x402060
004f44bf 83f80a                   cmp       eax, 0xa
004f44c2 750b                     jne       0x4f44cf
004f44c4 8b16                     mov       edx, dword ptr [esi]
004f44c6 8bce                     mov       ecx, esi
004f44c8 ff524c                   call      dword ptr [edx + 0x4c]
004f44cb c6404c00                 mov       byte ptr [eax + 0x4c], 0
004f44cf 8b86801b0000             mov       eax, dword ptr [esi + 0x1b80]
004f44d5 33ff                     xor       edi, edi
004f44d7 3bc3                     cmp       eax, ebx
004f44d9 7506                     jne       0x4f44e1
004f44db 89be801b0000             mov       dword ptr [esi + 0x1b80], edi
004f44e1 399e7c1b0000             cmp       dword ptr [esi + 0x1b7c], ebx
004f44e7 7506                     jne       0x4f44ef
004f44e9 89be7c1b0000             mov       dword ptr [esi + 0x1b7c], edi
004f44ef 399e841b0000             cmp       dword ptr [esi + 0x1b84], ebx
004f44f5 7506                     jne       0x4f44fd
004f44f7 89be841b0000             mov       dword ptr [esi + 0x1b84], edi
004f44fd 399ef0040000             cmp       dword ptr [esi + 0x4f0], ebx
004f4503 750b                     jne       0x4f4510
004f4505 8b06                     mov       eax, dword ptr [esi]
004f4507 57                       push      edi
004f4508 8bce                     mov       ecx, esi
004f450a ff9028030000             call      dword ptr [eax + 0x328]
004f4510 399e84200000             cmp       dword ptr [esi + 0x2084], ebx
004f4516 7537                     jne       0x4f454f
004f4518 8b13                     mov       edx, dword ptr [ebx]
004f451a 6811020000               push      0x211
004f451f 8bcb                     mov       ecx, ebx
004f4521 ff522c                   call      dword ptr [edx + 0x2c]
004f4524 84c0                     test      al, al
004f4526 741c                     je        0x4f4544
004f4528 8b03                     mov       eax, dword ptr [ebx]
004f452a 8b3e                     mov       edi, dword ptr [esi]
004f452c 8bcb                     mov       ecx, ebx
004f452e ff9058030000             call      dword ptr [eax + 0x358]
004f4534 50                       push      eax
004f4535 8bce                     mov       ecx, esi
004f4537 ff9754030000             call      dword ptr [edi + 0x354]
004f453d 5f                       pop       edi
004f453e 5e                       pop       esi
004f453f 5b                       pop       ebx
004f4540 5d                       pop       ebp
004f4541 c20400                   ret       4
004f4544 8b16                     mov       edx, dword ptr [esi]
004f4546 57                       push      edi
004f4547 8bce                     mov       ecx, esi
004f4549 ff9254030000             call      dword ptr [edx + 0x354]
004f454f 5f                       pop       edi
004f4550 5e                       pop       esi
004f4551 5b                       pop       ebx
004f4552 5d                       pop       ebp
004f4553 c20400                   ret       4
