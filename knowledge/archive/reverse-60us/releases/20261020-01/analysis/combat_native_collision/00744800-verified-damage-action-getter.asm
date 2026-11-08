00744800 55                       push      ebp
00744801 8bec                     mov       ebp, esp
00744803 8b4508                   mov       eax, dword ptr [ebp + 8]
00744806 83f802                   cmp       eax, 2
00744809 7d0b                     jge       0x744816
0074480b 8b8481ec120000           mov       eax, dword ptr [ecx + eax*4 + 0x12ec]
00744812 5d                       pop       ebp
00744813 c20400                   ret       4
00744816 33c0                     xor       eax, eax
00744818 5d                       pop       ebp
00744819 c20400                   ret       4
