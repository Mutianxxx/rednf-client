008c5440 3bcb                     cmp       ecx, ebx
008c5442 0f84080a0000             je        0x8c5e50
008c5448 0fb7550e                 movzx     edx, word ptr [ebp + 0xe]
008c544c 0fb74512                 movzx     eax, word ptr [ebp + 0x12]
008c5450 53                       push      ebx
008c5451 688c52f500               push      0xf5528c
008c5456 681009f400               push      0xf40910
008c545b 53                       push      ebx
008c545c 52                       push      edx
008c545d 50                       push      eax
008c545e e8bd63c4ff               call      0x50b820
008c5463 50                       push      eax
008c5464 e8a2b83300               call      0xc00d0b
008c5469 83c414                   add       esp, 0x14
008c546c 3bc3                     cmp       eax, ebx
008c546e 0f84dc090000             je        0x8c5e50
008c5474 0fb64d0b                 movzx     ecx, byte ptr [ebp + 0xb]
008c5478 8b10                     mov       edx, dword ptr [eax]
008c547a 51                       push      ecx
008c547b 8bc8                     mov       ecx, eax
008c547d ff9228040000             call      dword ptr [edx + 0x428]
008c5483 3bc3                     cmp       eax, ebx
008c5485 0f84c5090000             je        0x8c5e50
008c548b 8b10                     mov       edx, dword ptr [eax]
008c548d 8bc8                     mov       ecx, eax
008c548f ff925c010000             call      dword ptr [edx + 0x15c]
008c5495 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
008c5498 64890d00000000           mov       dword ptr fs:[0], ecx
008c549f 5f                       pop       edi
008c54a0 5e                       pop       esi
008c54a1 5b                       pop       ebx
008c54a2 8be5                     mov       esp, ebp
008c54a4 5d                       pop       ebp
008c54a5 c20c00                   ret       0xc
008c54a8 8b06                     mov       eax, dword ptr [esi]
008c54aa 8d4d0c                   lea       ecx, [ebp + 0xc]
008c54ad 33db                     xor       ebx, ebx
008c54af 51                       push      ecx
008c54b0 8bce                     mov       ecx, esi
008c54b2 895d0c                   mov       dword ptr [ebp + 0xc], ebx
008c54b5 895d08                   mov       dword ptr [ebp + 8], ebx
008c54b8 ff5054                   call      dword ptr [eax + 0x54]
008c54bb 8b16                     mov       edx, dword ptr [esi]
008c54bd 8d4508                   lea       eax, [ebp + 8]
