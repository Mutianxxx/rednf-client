0049d7d0 55                       push      ebp
0049d7d1 8bec                     mov       ebp, esp
0049d7d3 83ec10                   sub       esp, 0x10
0049d7d6 53                       push      ebx
0049d7d7 56                       push      esi
0049d7d8 57                       push      edi
0049d7d9 8b7d08                   mov       edi, dword ptr [ebp + 8]
0049d7dc 8bc7                     mov       eax, edi
0049d7de 83e800                   sub       eax, 0
0049d7e1 8bf1                     mov       esi, ecx
0049d7e3 0f84c1000000             je        0x49d8aa
0049d7e9 48                       dec       eax
0049d7ea 0f85df000000             jne       0x49d8cf
0049d7f0 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049d7f3 8b4004                   mov       eax, dword ptr [eax + 4]
0049d7f6 8b4808                   mov       ecx, dword ptr [eax + 8]
0049d7f9 8b500c                   mov       edx, dword ptr [eax + 0xc]
0049d7fc 8b18                     mov       ebx, dword ptr [eax]
0049d7fe 8b7804                   mov       edi, dword ptr [eax + 4]
0049d801 894d0c                   mov       dword ptr [ebp + 0xc], ecx
0049d804 8b4810                   mov       ecx, dword ptr [eax + 0x10]
0049d807 8955f0                   mov       dword ptr [ebp - 0x10], edx
0049d80a 8b5014                   mov       edx, dword ptr [eax + 0x14]
0049d80d 8b4018                   mov       eax, dword ptr [eax + 0x18]
0049d810 894d08                   mov       dword ptr [ebp + 8], ecx
0049d813 8955f4                   mov       dword ptr [ebp - 0xc], edx
0049d816 8b16                     mov       edx, dword ptr [esi]
0049d818 8bce                     mov       ecx, esi
0049d81a 8945f8                   mov       dword ptr [ebp - 8], eax
0049d81d ff923c030000             call      dword ptr [edx + 0x33c]
0049d823 8b00                     mov       eax, dword ptr [eax]
0049d825 8b16                     mov       edx, dword ptr [esi]
0049d827 8bce                     mov       ecx, esi
0049d829 8945fc                   mov       dword ptr [ebp - 4], eax
0049d82c ff923c030000             call      dword ptr [edx + 0x33c]
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
0049d8a1 5f                       pop       edi
0049d8a2 5e                       pop       esi
0049d8a3 5b                       pop       ebx
0049d8a4 8be5                     mov       esp, ebp
0049d8a6 5d                       pop       ebp
0049d8a7 c21000                   ret       0x10
0049d8aa 8b864c010000             mov       eax, dword ptr [esi + 0x14c]
0049d8b0 85c0                     test      eax, eax
0049d8b2 741b                     je        0x49d8cf
0049d8b4 8b16                     mov       edx, dword ptr [esi]
0049d8b6 8bce                     mov       ecx, esi
0049d8b8 8bd8                     mov       ebx, eax
0049d8ba ff9204010000             call      dword ptr [edx + 0x104]
0049d8c0 3bc3                     cmp       eax, ebx
0049d8c2 740b                     je        0x49d8cf
0049d8c4 8b06                     mov       eax, dword ptr [esi]
0049d8c6 53                       push      ebx
0049d8c7 8bce                     mov       ecx, esi
0049d8c9 ff9000010000             call      dword ptr [eax + 0x100]
0049d8cf 8b16                     mov       edx, dword ptr [esi]
0049d8d1 8bce                     mov       ecx, esi
0049d8d3 ff924c030000             call      dword ptr [edx + 0x34c]
0049d8d9 3bf8                     cmp       edi, eax
0049d8db 7c65                     jl        0x49d942
0049d8dd 8b1e                     mov       ebx, dword ptr [esi]
0049d8df 8bce                     mov       ecx, esi
0049d8e1 ff934c030000             call      dword ptr [ebx + 0x34c]
0049d8e7 8bcf                     mov       ecx, edi
0049d8e9 2bc8                     sub       ecx, eax
0049d8eb 51                       push      ecx
0049d8ec 8bce                     mov       ecx, esi
0049d8ee ff9350030000             call      dword ptr [ebx + 0x350]
0049d8f4 85c0                     test      eax, eax
0049d8f6 742f                     je        0x49d927
0049d8f8 8b1e                     mov       ebx, dword ptr [esi]
0049d8fa 8bce                     mov       ecx, esi
0049d8fc ff934c030000             call      dword ptr [ebx + 0x34c]
0049d902 8bd7                     mov       edx, edi
0049d904 2bd0                     sub       edx, eax
0049d906 52                       push      edx
0049d907 8bce                     mov       ecx, esi
0049d909 ff9350030000             call      dword ptr [ebx + 0x350]
0049d90f 50                       push      eax
0049d910 8bce                     mov       ecx, esi
0049d912 ff9300010000             call      dword ptr [ebx + 0x100]
0049d918 89bee8070000             mov       dword ptr [esi + 0x7e8], edi
0049d91e 5f                       pop       edi
0049d91f 5e                       pop       esi
0049d920 5b                       pop       ebx
0049d921 8be5                     mov       esp, ebp
0049d923 5d                       pop       ebp
0049d924 c21000                   ret       0x10
0049d927 57                       push      edi
0049d928 8d8e08020000             lea       ecx, [esi + 0x208]
0049d92e e8bd575b00               call      0xa530f0
0049d933 50                       push      eax
0049d934 68e8ebcc00               push      0xccebe8
0049d939 ff15bc2eff00             call      dword ptr [0xff2ebc]
0049d93f 83c40c                   add       esp, 0xc
0049d942 89bee8070000             mov       dword ptr [esi + 0x7e8], edi
0049d948 5f                       pop       edi
0049d949 5e                       pop       esi
0049d94a 5b                       pop       ebx
0049d94b 8be5                     mov       esp, ebp
0049d94d 5d                       pop       ebp
0049d94e c21000                   ret       0x10
