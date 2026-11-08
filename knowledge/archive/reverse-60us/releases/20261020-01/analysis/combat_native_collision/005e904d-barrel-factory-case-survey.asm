005e904d 684c090000               push      0x94c
005e9052 e8f9abe1ff               call      0x403c50
005e9057 83c404                   add       esp, 4
005e905a 894508                   mov       dword ptr [ebp + 8], eax
005e905d 85c0                     test      eax, eax
005e905f c745fc0a000000           mov       dword ptr [ebp - 4], 0xa
005e9066 0f84c7f5ffff             je        0x5e8633
005e906c 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
005e906f 51                       push      ecx
005e9070 56                       push      esi
005e9071 8bc8                     mov       ecx, eax
005e9073 e8b877eaff               call      0x490830
005e9078 e9b8f5ffff               jmp       0x5e8635
005e907d 684c090000               push      0x94c
005e9082 e8c9abe1ff               call      0x403c50
005e9087 83c404                   add       esp, 4
005e908a 894508                   mov       dword ptr [ebp + 8], eax
005e908d 85c0                     test      eax, eax
005e908f c745fc1a000000           mov       dword ptr [ebp - 4], 0x1a
005e9096 0f8497f5ffff             je        0x5e8633
005e909c 8b550c                   mov       edx, dword ptr [ebp + 0xc]
005e909f 52                       push      edx
005e90a0 56                       push      esi
005e90a1 8bc8                     mov       ecx, eax
005e90a3 e848b2ffff               call      0x5e42f0
005e90a8 e988f5ffff               jmp       0x5e8635
005e90ad 6868090000               push      0x968
005e90b2 e899abe1ff               call      0x403c50
005e90b7 83c404                   add       esp, 4
005e90ba 894508                   mov       dword ptr [ebp + 8], eax
005e90bd 85c0                     test      eax, eax
005e90bf c745fc1b000000           mov       dword ptr [ebp - 4], 0x1b
005e90c6 0f8467f5ffff             je        0x5e8633
005e90cc 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
005e90cf 51                       push      ecx
005e90d0 56                       push      esi
005e90d1 8bc8                     mov       ecx, eax
005e90d3 e89896ffff               call      0x5e2770
005e90d8 e958f5ffff               jmp       0x5e8635
005e90dd 6854090000               push      0x954
005e90e2 e869abe1ff               call      0x403c50
005e90e7 83c404                   add       esp, 4
005e90ea 894508                   mov       dword ptr [ebp + 8], eax
005e90ed 85c0                     test      eax, eax
005e90ef c745fc1f000000           mov       dword ptr [ebp - 4], 0x1f
005e90f6 0f84f4840000             je        0x5f15f0
005e90fc 8d9617fcffff             lea       edx, [esi - 0x3e9]
005e9102 52                       push      edx
005e9103 6a00                     push      0
005e9105 56                       push      esi
005e9106 8bc8                     mov       ecx, eax
005e9108 e8a3e0ffff               call      0x5e71b0
005e910d 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005e9110 64890d00000000           mov       dword ptr fs:[0], ecx
005e9117 5e                       pop       esi
005e9118 8be5                     mov       esp, ebp
005e911a 5d                       pop       ebp
005e911b c3                       ret       
005e911c 68c8080000               push      0x8c8
005e9121 e82aabe1ff               call      0x403c50
005e9126 83c404                   add       esp, 4
005e9129 894508                   mov       dword ptr [ebp + 8], eax
005e912c 85                       .byte     0x85
