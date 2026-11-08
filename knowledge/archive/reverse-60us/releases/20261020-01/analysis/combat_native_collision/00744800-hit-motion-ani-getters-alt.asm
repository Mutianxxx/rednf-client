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
0074481c cc                       int3      
0074481d cc                       int3      
0074481e cc                       int3      
0074481f cc                       int3      
00744820 8b81f4120000             mov       eax, dword ptr [ecx + 0x12f4]
00744826 c3                       ret       
00744827 cc                       int3      
00744828 cc                       int3      
00744829 cc                       int3      
0074482a cc                       int3      
0074482b cc                       int3      
0074482c cc                       int3      
0074482d cc                       int3      
0074482e cc                       int3      
0074482f cc                       int3      
00744830 8b81f8120000             mov       eax, dword ptr [ecx + 0x12f8]
00744836 c3                       ret       
00744837 cc                       int3      
00744838 cc                       int3      
00744839 cc                       int3      
0074483a cc                       int3      
0074483b cc                       int3      
0074483c cc                       int3      
0074483d cc                       int3      
0074483e cc                       int3      
0074483f cc                       int3      
00744840 8b81fc120000             mov       eax, dword ptr [ecx + 0x12fc]
00744846 c3                       ret       
00744847 cc                       int3      
00744848 cc                       int3      
00744849 cc                       int3      
0074484a cc                       int3      
0074484b cc                       int3      
0074484c cc                       int3      
0074484d cc                       int3      
0074484e cc                       int3      
0074484f cc                       int3      
00744850 8b8100130000             mov       eax, dword ptr [ecx + 0x1300]
00744856 c3                       ret       
00744857 cc                       int3      
00744858 cc                       int3      
00744859 cc                       int3      
0074485a cc                       int3      
0074485b cc                       int3      
0074485c cc                       int3      
0074485d cc                       int3      
0074485e cc                       int3      
0074485f cc                       int3      
00744860 8d81e0120000             lea       eax, [ecx + 0x12e0]
00744866 c3                       ret       
00744867 cc                       int3      
00744868 cc                       int3      
00744869 cc                       int3      
0074486a cc                       int3      
0074486b cc                       int3      
0074486c cc                       int3      
0074486d cc                       int3      
0074486e cc                       int3      
0074486f cc                       int3      
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
