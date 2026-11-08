0060c650 c3                       ret       
0060c651 cc                       int3      
0060c652 cc                       int3      
0060c653 cc                       int3      
0060c654 cc                       int3      
0060c655 cc                       int3      
0060c656 cc                       int3      
0060c657 cc                       int3      
0060c658 cc                       int3      
0060c659 cc                       int3      
0060c65a cc                       int3      
0060c65b cc                       int3      
0060c65c cc                       int3      
0060c65d cc                       int3      
0060c65e cc                       int3      
0060c65f cc                       int3      
0060c660 e9ebb0feff               jmp       0x5f7750
0060c665 cc                       int3      
0060c666 cc                       int3      
0060c667 cc                       int3      
0060c668 cc                       int3      
0060c669 cc                       int3      
0060c66a cc                       int3      
0060c66b cc                       int3      
0060c66c cc                       int3      
0060c66d cc                       int3      
0060c66e cc                       int3      
0060c66f cc                       int3      
0060c670 55                       push      ebp
0060c671 8bec                     mov       ebp, esp
0060c673 83ec0c                   sub       esp, 0xc
0060c676 8b814c090000             mov       eax, dword ptr [ecx + 0x94c]
0060c67c c745f43333333f           mov       dword ptr [ebp - 0xc], 0x3f333333
0060c683 c745f80000803f           mov       dword ptr [ebp - 8], 0x3f800000
0060c68a c745fc6666a63f           mov       dword ptr [ebp - 4], 0x3fa66666
0060c691 8b4c85f4                 mov       ecx, dword ptr [ebp + eax*4 - 0xc]
0060c695 51                       push      ecx
0060c696 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0060c699 e812d14100               call      0xa297b0
0060c69e 8be5                     mov       esp, ebp
0060c6a0 5d                       pop       ebp
0060c6a1 c20400                   ret       4
0060c6a4 cc                       int3      
0060c6a5 cc                       int3      
0060c6a6 cc                       int3      
0060c6a7 cc                       int3      
0060c6a8 cc                       int3      
0060c6a9 cc                       int3      
0060c6aa cc                       int3      
0060c6ab cc                       int3      
0060c6ac cc                       int3      
0060c6ad cc                       int3      
0060c6ae cc                       int3      
0060c6af cc                       int3      
0060c6b0 55                       push      ebp
0060c6b1 8bec                     mov       ebp, esp
0060c6b3 8b814c090000             mov       eax, dword ptr [ecx + 0x94c]
0060c6b9 83e800                   sub       eax, 0
0060c6bc 53                       push      ebx
0060c6bd 8b5d0c                   mov       ebx, dword ptr [ebp + 0xc]
0060c6c0 56                       push      esi
0060c6c1 8b7508                   mov       esi, dword ptr [ebp + 8]
0060c6c4 57                       push      edi
0060c6c5 742e                     je        0x60c6f5
0060c6c7 48                       dec       eax
0060c6c8 740f                     je        0x60c6d9
0060c6ca 48                       dec       eax
0060c6cb 754d                     jne       0x60c71a
0060c6cd 8b06                     mov       eax, dword ptr [esi]
0060c6cf 8bce                     mov       ecx, esi
0060c6d1 ff9038020000             call      dword ptr [eax + 0x238]
0060c6d7 eb36                     jmp       0x60c70f
0060c6d9 8b16                     mov       edx, dword ptr [esi]
0060c6db 8bce                     mov       ecx, esi
0060c6dd ff9238020000             call      dword ptr [edx + 0x238]
0060c6e3 99                       cdq       
0060c6e4 2bc2                     sub       eax, edx
0060c6e6 d1f8                     sar       eax, 1
0060c6e8 8903                     mov       dword ptr [ebx], eax
0060c6ea 8b4510                   mov       eax, dword ptr [ebp + 0x10]
0060c6ed c700e8030000             mov       dword ptr [eax], 0x3e8
0060c6f3 eb25                     jmp       0x60c71a
0060c6f5 8b16                     mov       edx, dword ptr [esi]
0060c6f7 8bce                     mov       ecx, esi
0060c6f9 ff9238020000             call      dword ptr [edx + 0x238]
0060c6ff 8bc8                     mov       ecx, eax
0060c701 b856555555               mov       eax, 0x55555556
0060c706 f7e9                     imul      ecx
0060c708 8bc2                     mov       eax, edx
0060c70a c1e81f                   shr       eax, 0x1f
0060c70d 03c2                     add       eax, edx
0060c70f 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
0060c712 8903                     mov       dword ptr [ebx], eax
0060c714 c701e8030000             mov       dword ptr [ecx], 0x3e8
0060c71a 8b16                     mov       edx, dword ptr [esi]
0060c71c 8bce                     mov       ecx, esi
0060c71e ff9238020000             call      dword ptr [edx + 0x238]
0060c724 8bf8                     mov       edi, eax
0060c726 8b06                     mov       eax, dword ptr [esi]
0060c728 8bce                     mov       ecx, esi
0060c72a ff9034020000             call      dword ptr [eax + 0x234]
0060c730 2bf8                     sub       edi, eax
0060c732 393b                     cmp       dword ptr [ebx], edi
0060c734 7e02                     jle       0x60c738
0060c736 893b                     mov       dword ptr [ebx], edi
0060c738 5f                       pop       edi
0060c739 5e                       pop       esi
0060c73a 5b                       pop       ebx
0060c73b 5d                       pop       ebp
0060c73c c20c00                   ret       0xc
0060c73f cc                       int3      
0060c740 55                       push      ebp
0060c741 8bec                     mov       ebp, esp
0060c743 8b814c090000             mov       eax, dword ptr [ecx + 0x94c]
0060c749 83e800                   sub       eax, 0
0060c74c 53                       push      ebx
0060c74d 8b5d0c                   mov       ebx, dword ptr [ebp + 0xc]
0060c750 56                       push      esi
0060c751 8b7508                   mov       esi, dword ptr [ebp + 8]
0060c754 57                       push      edi
0060c755 742e                     je        0x60c785
0060c757 48                       dec       eax
0060c758 740f                     je        0x60c769
0060c75a 48                       dec       eax
0060c75b 754d                     jne       0x60c7aa
0060c75d 8b06                     mov       eax, dword ptr [esi]
0060c75f 8bce                     mov       ecx, esi
0060c761 ff90fc030000             call      dword ptr [eax + 0x3fc]
0060c767 eb36                     jmp       0x60c79f
0060c769 8b16                     mov       edx, dword ptr [esi]
0060c76b 8bce                     mov       ecx, esi
0060c76d ff92fc030000             call      dword ptr [edx + 0x3fc]
0060c773 99                       cdq       
0060c774 2bc2                     sub       eax, edx
0060c776 d1f8                     sar       eax, 1
0060c778 8903                     mov       dword ptr [ebx], eax
0060c77a 8b4510                   mov       eax, dword ptr [ebp + 0x10]
0060c77d c700e8030000             mov       dword ptr [eax], 0x3e8
0060c783 eb25                     jmp       0x60c7aa
0060c785 8b16                     mov       edx, dword ptr [esi]
0060c787 8bce                     mov       ecx, esi
0060c789 ff92fc030000             call      dword ptr [edx + 0x3fc]
0060c78f 8bc8                     mov       ecx, eax
0060c791 b856555555               mov       eax, 0x55555556
0060c796 f7e9                     imul      ecx
0060c798 8bc2                     mov       eax, edx
0060c79a c1e81f                   shr       eax, 0x1f
0060c79d 03c2                     add       eax, edx
0060c79f 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
0060c7a2 8903                     mov       dword ptr [ebx], eax
0060c7a4 c701e8030000             mov       dword ptr [ecx], 0x3e8
0060c7aa 8b16                     mov       edx, dword ptr [esi]
0060c7ac 8bce                     mov       ecx, esi
0060c7ae ff92fc030000             call      dword ptr [edx + 0x3fc]
0060c7b4 8bf8                     mov       edi, eax
0060c7b6 8b06                     mov       eax, dword ptr [esi]
0060c7b8 8bce                     mov       ecx, esi
0060c7ba ff90f8030000             call      dword ptr [eax + 0x3f8]
0060c7c0 2bf8                     sub       edi, eax
0060c7c2 393b                     cmp       dword ptr [ebx], edi
0060c7c4 7e02                     jle       0x60c7c8
0060c7c6 893b                     mov       dword ptr [ebx], edi
0060c7c8 5f                       pop       edi
0060c7c9 5e                       pop       esi
0060c7ca 5b                       pop       ebx
0060c7cb 5d                       pop       ebp
0060c7cc c20c00                   ret       0xc
0060c7cf cc                       int3      
