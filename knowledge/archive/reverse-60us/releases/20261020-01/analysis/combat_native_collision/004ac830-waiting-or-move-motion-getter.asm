004ac830 8b8140120000             mov       eax, dword ptr [ecx + 0x1240]
004ac836 85c0                     test      eax, eax
004ac838 7511                     jne       0x4ac84b
004ac83a 8b89e0120000             mov       ecx, dword ptr [ecx + 0x12e0]
004ac840 85c9                     test      ecx, ecx
004ac842 7405                     je        0x4ac849
004ac844 e967075800               jmp       0xa2cfb0
004ac849 33c0                     xor       eax, eax
004ac84b c3                       ret       
004ac84c cc                       int3      
004ac84d cc                       int3      
004ac84e cc                       int3      
004ac84f cc                       int3      
004ac850 55                       push      ebp
004ac851 8bec                     mov       ebp, esp
004ac853 53                       push      ebx
004ac854 8b5d14                   mov       ebx, dword ptr [ebp + 0x14]
004ac857 56                       push      esi
004ac858 57                       push      edi
004ac859 8b7d10                   mov       edi, dword ptr [ebp + 0x10]
004ac85c 85ff                     test      edi, edi
004ac85e 8bf1                     mov       esi, ecx
