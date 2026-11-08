0049d832 8938                     mov       dword ptr [eax], edi
0049d834 8b45fc                   mov       eax, dword ptr [ebp - 4]
0049d837 3bc7                     cmp       eax, edi
0049d839 7e16                     jle       0x49d851
0049d83b 8b0dd4f10401             mov       ecx, dword ptr [0x104f1d4]
0049d841 8b9658040000             mov       edx, dword ptr [esi + 0x458]
0049d847 33c0                     xor       eax, eax
0049d849 3bca                     cmp       ecx, edx
0049d84b 0f94c0                   sete      al
0049d84e 50                       push      eax
0049d84f eb04                     jmp       0x49d855
0049d851 7d20                     jge       0x49d873
0049d853 6a04                     push      4
0049d855 8b5508                   mov       edx, dword ptr [ebp + 8]
0049d858 8b06                     mov       eax, dword ptr [esi]
0049d85a 53                       push      ebx
0049d85b 8bce                     mov       ecx, esi
0049d85d 52                       push      edx
0049d85e ff9098000000             call      dword ptr [eax + 0x98]
0049d864 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049d867 40                       inc       eax
0049d868 50                       push      eax
0049d869 51                       push      ecx
0049d86a 56                       push      esi
0049d86b e810b1ffff               call      0x498980
0049d870 83c418                   add       esp, 0x18
0049d873 8b55f8                   mov       edx, dword ptr [ebp - 8]
0049d876 8b45f4                   mov       eax, dword ptr [ebp - 0xc]
0049d879 52                       push      edx
0049d87a 8b16                     mov       edx, dword ptr [esi]
0049d87c 50                       push      eax
0049d87d 8bce                     mov       ecx, esi
0049d87f ff525c                   call      dword ptr [edx + 0x5c]
0049d882 8bc8                     mov       ecx, eax
0049d884 e897df0600               call      0x50b820
0049d889 8b4d08                   mov       ecx, dword ptr [ebp + 8]
0049d88c 8b16                     mov       edx, dword ptr [esi]
0049d88e 51                       push      ecx
0049d88f 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
0049d892 51                       push      ecx
0049d893 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
0049d896 51                       push      ecx
0049d897 53                       push      ebx
0049d898 50                       push      eax
0049d899 8bce                     mov       ecx, esi
0049d89b ff9248030000             call      dword ptr [edx + 0x348]
