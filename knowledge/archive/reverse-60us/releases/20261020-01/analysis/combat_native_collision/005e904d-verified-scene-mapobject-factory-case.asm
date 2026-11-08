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
