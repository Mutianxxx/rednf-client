004e8840 c20400                   ret       4
004e8843 cc                       int3      
004e8844 cc                       int3      
004e8845 cc                       int3      
004e8846 cc                       int3      
004e8847 cc                       int3      
004e8848 cc                       int3      
004e8849 cc                       int3      
004e884a cc                       int3      
004e884b cc                       int3      
004e884c cc                       int3      
004e884d cc                       int3      
004e884e cc                       int3      
004e884f cc                       int3      
004e8850 c20400                   ret       4
004e8853 cc                       int3      
004e8854 cc                       int3      
004e8855 cc                       int3      
004e8856 cc                       int3      
004e8857 cc                       int3      
004e8858 cc                       int3      
004e8859 cc                       int3      
004e885a cc                       int3      
004e885b cc                       int3      
004e885c cc                       int3      
004e885d cc                       int3      
004e885e cc                       int3      
004e885f cc                       int3      
004e8860 55                       push      ebp
004e8861 8bec                     mov       ebp, esp
004e8863 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e8869 8b01                     mov       eax, dword ptr [ecx]
004e886b 6a02                     push      2
004e886d 6a1a                     push      0x1a
004e886f ff5008                   call      dword ptr [eax + 8]
004e8872 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e8878 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004e887b 8b11                     mov       edx, dword ptr [ecx]
004e887d 50                       push      eax
004e887e ff5224                   call      dword ptr [edx + 0x24]
004e8881 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e8887 8b4510                   mov       eax, dword ptr [ebp + 0x10]
004e888a 8b11                     mov       edx, dword ptr [ecx]
004e888c 50                       push      eax
004e888d ff5224                   call      dword ptr [edx + 0x24]
004e8890 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e8896 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004e8899 8b11                     mov       edx, dword ptr [ecx]
004e889b 50                       push      eax
004e889c ff5220                   call      dword ptr [edx + 0x20]
004e889f 8b451c                   mov       eax, dword ptr [ebp + 0x1c]
004e88a2 8b0d64310001             mov       ecx, dword ptr [0x1003164]
004e88a8 8b11                     mov       edx, dword ptr [ecx]
004e88aa 50                       push      eax
004e88ab 8b4518                   mov       eax, dword ptr [ebp + 0x18]
004e88ae 50                       push      eax
004e88af ff5238                   call      dword ptr [edx + 0x38]
004e88b2 8b4508                   mov       eax, dword ptr [ebp + 8]
004e88b5 8b0d90070c01             mov       ecx, dword ptr [0x10c0790]
004e88bb 8b11                     mov       edx, dword ptr [ecx]
004e88bd 6a03                     push      3
004e88bf 50                       push      eax
004e88c0 8b4520                   mov       eax, dword ptr [ebp + 0x20]
004e88c3 6aff                     push      -1
004e88c5 50                       push      eax
004e88c6 ff5244                   call      dword ptr [edx + 0x44]
004e88c9 5d                       pop       ebp
004e88ca c3                       ret       
004e88cb cc                       int3      
004e88cc cc                       int3      
004e88cd cc                       int3      
004e88ce cc                       int3      
004e88cf cc                       int3      
004e88d0 56                       push      esi
004e88d1 57                       push      edi
004e88d2 8bf9                     mov       edi, ecx
004e88d4 8d4f60                   lea       ecx, [edi + 0x60]
004e88d7 e824e66100               call      0xb06f00
004e88dc 8b0d88310001             mov       ecx, dword ptr [0x1003188]
004e88e2 8bf0                     mov       esi, eax
004e88e4 8b870c050000             mov       eax, dword ptr [edi + 0x50c]
004e88ea 6a07                     push      7
004e88ec 2bf0                     sub       esi, eax
004e88ee e8                       .byte     0xe8
004e88ef 6d                       insd      dword ptr es:[edi], dx
