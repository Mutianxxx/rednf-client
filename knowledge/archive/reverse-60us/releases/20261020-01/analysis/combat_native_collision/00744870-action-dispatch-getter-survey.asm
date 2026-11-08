00744870 8b81dc120000             mov       eax, dword ptr [ecx + 0x12dc]
00744876 c3                       ret       
00744877 cc                       int3      
00744878 cc                       int3      
00744879 cc                       int3      
0074487a cc                       int3      
0074487b cc                       int3      
0074487c cc                       int3      
0074487d cc                       int3      
0074487e cc                       int3      
0074487f cc                       int3      
00744880 55                       push      ebp
00744881 8bec                     mov       ebp, esp
00744883 8b4508                   mov       eax, dword ptr [ebp + 8]
00744886 8b848194120000           mov       eax, dword ptr [ecx + eax*4 + 0x1294]
0074488d 5d                       pop       ebp
0074488e c20400                   ret       4
00744891 cc                       int3      
00744892 cc                       int3      
00744893 cc                       int3      
00744894 cc                       int3      
00744895 cc                       int3      
00744896 cc                       int3      
00744897 cc                       int3      
00744898 cc                       int3      
00744899 cc                       int3      
0074489a cc                       int3      
0074489b cc                       int3      
0074489c cc                       int3      
0074489d cc                       int3      
0074489e cc                       int3      
0074489f cc                       int3      
007448a0 55                       push      ebp
007448a1 8bec                     mov       ebp, esp
007448a3 8b550c                   mov       edx, dword ptr [ebp + 0xc]
007448a6 8b01                     mov       eax, dword ptr [ecx]
007448a8 52                       push      edx
007448a9 8b5508                   mov       edx, dword ptr [ebp + 8]
007448ac 6a00                     push      0
007448ae 6aff                     push      -1
007448b0 52                       push      edx
007448b1 ff9038040000             call      dword ptr [eax + 0x438]
007448b7 5d                       pop       ebp
007448b8 c20800                   ret       8
007448bb cc                       int3      
007448bc cc                       int3      
007448bd cc                       int3      
007448be cc                       int3      
007448bf cc                       int3      
007448c0 55                       push      ebp
007448c1 8bec                     mov       ebp, esp
007448c3 8b4508                   mov       eax, dword ptr [ebp + 8]
007448c6 53                       push      ebx
007448c7 8b5d0c                   mov       ebx, dword ptr [ebp + 0xc]
007448ca 56                       push      esi
007448cb 53                       push      ebx
007448cc 50                       push      eax
007448cd 8bf1                     mov       esi, ecx
007448cf e83c8edaff               call      0x4ed710
007448d4 84db                     test      bl, bl
007448d6 740c                     je        0x7448e4
007448d8 8b16                     mov       edx, dword ptr [esi]
007448da 6a00                     push      0
007448dc 8bce                     mov       ecx, esi
007448de ff9248030000             call      dword ptr [edx + 0x348]
007448e4 5e                       pop       esi
007448e5 5b                       pop       ebx
007448e6 5d                       pop       ebp
007448e7 c20800                   ret       8
007448ea cc                       int3      
007448eb cc                       int3      
007448ec cc                       int3      
007448ed cc                       int3      
007448ee cc                       int3      
007448ef cc                       int3      
