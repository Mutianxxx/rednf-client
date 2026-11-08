005e8560 7f05                     jg        0x5e8567
005e8562 0000                     add       byte ptr [eax], al
005e8564 81fe02030000             cmp       esi, 0x302
005e856a 0f8ddd0a0000             jge       0x5e904d
005e8570 81fe1e010000             cmp       esi, 0x11e
005e8576 0f8f90020000             jg        0x5e880c
005e857c 81fe19010000             cmp       esi, 0x119
005e8582 0f8d9b1b0000             jge       0x5ea123
005e8588 81fefa000000             cmp       esi, 0xfa
005e858e 0f8f2b010000             jg        0x5e86bf
005e8594 81fef1000000             cmp       esi, 0xf1
005e859a 0f8de5000000             jge       0x5e8685
005e85a0 8d46ff                   lea       eax, [esi - 1]
005e85a3 3def000000               cmp       eax, 0xef
005e85a8 0f870b040000             ja        0x5e89b9
005e85ae 0fb68020165f00           movzx     eax, byte ptr [eax + 0x5f1620]
005e85b5 ff248504165f00           jmp       dword ptr [eax*4 + 0x5f1604]
005e85bc 687c080000               push      0x87c
005e85c1 e88ab6e1ff               call      0x403c50
005e85c6 83c404                   add       esp, 4
005e85c9 894508                   mov       dword ptr [ebp + 8], eax
005e85cc 85c0                     test      eax, eax
005e85ce c745fc00000000           mov       dword ptr [ebp - 4], 0
005e85d5 0f8415900000             je        0x5f15f0
005e85db 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
005e85de 51                       push      ecx
005e85df 56                       push      esi
005e85e0 8bc8                     mov       ecx, eax
005e85e2 e8e910feff               call      0x5c96d0
005e85e7 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005e85ea 64890d00000000           mov       dword ptr fs:[0], ecx
005e85f1 5e                       pop       esi
005e85f2 8be5                     mov       esp, ebp
005e85f4 5d                       pop       ebp
005e85f5 c3                       ret       
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
005e86bf 8d86fefeffff             lea       eax, [esi - 0x102]
005e86c5 83f812                   cmp       eax, 0x12
005e86c8 0f87eb020000             ja        0x5e89b9
005e86ce 0fb6803c175f00           movzx     eax, byte ptr [eax + 0x5f173c]
005e86d5 ff248510175f00           jmp       dword ptr [eax*4 + 0x5f1710]
005e86dc 687c080000               push      0x87c
005e86e1 e8                       .byte     0xe8
005e86e2 6ab5                     push      -0x4b
005e86e4 e1                       .byte     0xe1
