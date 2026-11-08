0050de00 0c8b                     or        al, 0x8b
0050de02 55                       push      ebp
0050de03 1089088d4508             adc       byte ptr [ecx + 0x8458d08], cl
0050de09 895508                   mov       dword ptr [ebp + 8], edx
0050de0c 8b16                     mov       edx, dword ptr [esi]
0050de0e 50                       push      eax
0050de0f 8bce                     mov       ecx, esi
0050de11 ff5228                   call      dword ptr [edx + 0x28]
0050de14 8bc8                     mov       ecx, eax
0050de16 83c104                   add       ecx, 4
0050de19 e84267efff               call      0x404560
0050de1e 8b06                     mov       eax, dword ptr [esi]
0050de20 8bce                     mov       ecx, esi
0050de22 ff505c                   call      dword ptr [eax + 0x5c]
0050de25 85c0                     test      eax, eax
0050de27 7413                     je        0x50de3c
0050de29 8b16                     mov       edx, dword ptr [esi]
0050de2b 6a00                     push      0
0050de2d 6a00                     push      0
0050de2f 56                       push      esi
0050de30 8bce                     mov       ecx, esi
0050de32 ff525c                   call      dword ptr [edx + 0x5c]
0050de35 8bc8                     mov       ecx, eax
0050de37 e8b4e8ffff               call      0x50c6f0
0050de3c 8b06                     mov       eax, dword ptr [esi]
0050de3e 57                       push      edi
0050de3f 53                       push      ebx
0050de40 8bce                     mov       ecx, esi
0050de42 ff5058                   call      dword ptr [eax + 0x58]
0050de45 8d5514                   lea       edx, [ebp + 0x14]
0050de48 8d4b0c                   lea       ecx, [ebx + 0xc]
0050de4b 52                       push      edx
0050de4c e89f06f8ff               call      0x48e4f0
0050de51 8b06                     mov       eax, dword ptr [esi]
0050de53 8bce                     mov       ecx, esi
0050de55 ff5028                   call      dword ptr [eax + 0x28]
0050de58 83780c07                 cmp       dword ptr [eax + 0xc], 7
0050de5c 747d                     je        0x50dedb
0050de5e 8b16                     mov       edx, dword ptr [esi]
