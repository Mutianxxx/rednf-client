004ac7c0 55                       push      ebp
004ac7c1 8bec                     mov       ebp, esp
004ac7c3 8b5508                   mov       edx, dword ptr [ebp + 8]
004ac7c6 83fa02                   cmp       edx, 2
004ac7c9 7d1f                     jge       0x4ac7ea
004ac7cb 8b84914c120000           mov       eax, dword ptr [ecx + edx*4 + 0x124c]
004ac7d2 85c0                     test      eax, eax
004ac7d4 7516                     jne       0x4ac7ec
004ac7d6 8b8c91ec120000           mov       ecx, dword ptr [ecx + edx*4 + 0x12ec]
004ac7dd 85c9                     test      ecx, ecx
004ac7df 7409                     je        0x4ac7ea
004ac7e1 e8ca075800               call      0xa2cfb0
004ac7e6 5d                       pop       ebp
004ac7e7 c20400                   ret       4
004ac7ea 33c0                     xor       eax, eax
004ac7ec 5d                       pop       ebp
004ac7ed c20400                   ret       4
004ac7f0 8b8154120000             mov       eax, dword ptr [ecx + 0x1254]
004ac7f6 85c0                     test      eax, eax
004ac7f8 7511                     jne       0x4ac80b
004ac7fa 8b89f4120000             mov       ecx, dword ptr [ecx + 0x12f4]
004ac800 85c9                     test      ecx, ecx
004ac802 7405                     je        0x4ac809
004ac804 e9a7075800               jmp       0xa2cfb0
004ac809 33c0                     xor       eax, eax
004ac80b c3                       ret       
004ac80c cc                       int3      
004ac80d cc                       int3      
004ac80e cc                       int3      
004ac80f cc                       int3      
004ac810 8b8158120000             mov       eax, dword ptr [ecx + 0x1258]
004ac816 85c0                     test      eax, eax
004ac818 7511                     jne       0x4ac82b
004ac81a 8b89f8120000             mov       ecx, dword ptr [ecx + 0x12f8]
004ac820 85c9                     test      ecx, ecx
004ac822 7405                     je        0x4ac829
004ac824 e987075800               jmp       0xa2cfb0
004ac829 33c0                     xor       eax, eax
004ac82b c3                       ret       
004ac82c cc                       int3      
004ac82d cc                       int3      
004ac82e cc                       int3      
004ac82f cc                       int3      
004ac830 8b8140120000             mov       eax, dword ptr [ecx + 0x1240]
004ac836 85c0                     test      eax, eax
004ac838 7511                     jne       0x4ac84b
004ac83a 8b89e0120000             mov       ecx, dword ptr [ecx + 0x12e0]
004ac840 85c9                     test      ecx, ecx
004ac842 7405                     je        0x4ac849
004ac844 e967075800               jmp       0xa2cfb0
004ac849 33c0                     xor       eax, eax
004ac84b c3                       ret       
