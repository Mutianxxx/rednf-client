005e85f6 684c090000               push      0x94c
005e85fb e850b6e1ff               call      0x403c50
005e8600 83c404                   add       esp, 4
005e8603 894508                   mov       dword ptr [ebp + 8], eax
005e8606 85c0                     test      eax, eax
005e8608 c745fc08000000           mov       dword ptr [ebp - 4], 8
005e860f 7422                     je        0x5e8633
005e8611 8b550c                   mov       edx, dword ptr [ebp + 0xc]
005e8614 52                       push      edx
005e8615 56                       push      esi
005e8616 8bc8                     mov       ecx, eax
005e8618 e8a3eaffff               call      0x5e70c0
005e861d c680d907000001           mov       byte ptr [eax + 0x7d9], 1
005e8624 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005e8627 64890d00000000           mov       dword ptr fs:[0], ecx
005e862e 5e                       pop       esi
005e862f 8be5                     mov       esp, ebp
005e8631 5d                       pop       ebp
005e8632 c3                       ret       
005e8633 33c0                     xor       eax, eax
005e8635 c680d907000001           mov       byte ptr [eax + 0x7d9], 1
005e863c 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005e863f 64890d00000000           mov       dword ptr fs:[0], ecx
005e8646 5e                       pop       esi
005e8647 8be5                     mov       esp, ebp
005e8649 5d                       pop       ebp
005e864a c3                       ret       
005e864b 6854090000               push      0x954
005e8650 e8fbb5e1ff               call      0x403c50
005e8655 83c404                   add       esp, 4
005e8658 894508                   mov       dword ptr [ebp + 8], eax
005e865b 85c0                     test      eax, eax
005e865d c745fc1c000000           mov       dword ptr [ebp - 4], 0x1c
005e8664 0f84868f0000             je        0x5f15f0
005e866a 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
005e866d 51                       push      ecx
005e866e 56                       push      esi
005e866f 8bc8                     mov       ecx, eax
005e8671 e84aecffff               call      0x5e72c0
005e8676 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005e8679 64890d00000000           mov       dword ptr fs:[0], ecx
005e8680 5e                       pop       esi
005e8681 8be5                     mov       esp, ebp
005e8683 5d                       pop       ebp
005e8684 c3                       ret       
005e8685 68b0080000               push      0x8b0
005e868a e8c1b5e1ff               call      0x403c50
005e868f 83c404                   add       esp, 4
005e8692 894508                   mov       dword ptr [ebp + 8], eax
005e8695 85c0                     test      eax, eax
005e8697 c745fc01000000           mov       dword ptr [ebp - 4], 1
005e869e 0f844c8f0000             je        0x5f15f0
005e86a4 8b550c                   mov       edx, dword ptr [ebp + 0xc]
005e86a7 52                       push      edx
005e86a8 56                       push      esi
005e86a9 8bc8                     mov       ecx, eax
005e86ab e8b0fffdff               call      0x5c8660
005e86b0 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005e86b3 64890d00000000           mov       dword ptr fs:[0], ecx
005e86ba 5e                       pop       esi
005e86bb 8be5                     mov       esp, ebp
005e86bd 5d                       pop       ebp
005e86be c3                       ret       
