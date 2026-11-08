00498fd0 c21000                   ret       0x10
00498fd3 cc                       int3      
00498fd4 cc                       int3      
00498fd5 cc                       int3      
00498fd6 cc                       int3      
00498fd7 cc                       int3      
00498fd8 cc                       int3      
00498fd9 cc                       int3      
00498fda cc                       int3      
00498fdb cc                       int3      
00498fdc cc                       int3      
00498fdd cc                       int3      
00498fde cc                       int3      
00498fdf cc                       int3      
00498fe0 c3                       ret       
00498fe1 cc                       int3      
00498fe2 cc                       int3      
00498fe3 cc                       int3      
00498fe4 cc                       int3      
00498fe5 cc                       int3      
00498fe6 cc                       int3      
00498fe7 cc                       int3      
00498fe8 cc                       int3      
00498fe9 cc                       int3      
00498fea cc                       int3      
00498feb cc                       int3      
00498fec cc                       int3      
00498fed cc                       int3      
00498fee cc                       int3      
00498fef cc                       int3      
00498ff0 55                       push      ebp
00498ff1 8bec                     mov       ebp, esp
00498ff3 8b4508                   mov       eax, dword ptr [ebp + 8]
00498ff6 8b89e4000000             mov       ecx, dword ptr [ecx + 0xe4]
00498ffc 23c8                     and       ecx, eax
00498ffe 3bc8                     cmp       ecx, eax
00499000 0f94c0                   sete      al
00499003 5d                       pop       ebp
00499004 c20400                   ret       4
00499007 cc                       int3      
00499008 cc                       int3      
00499009 cc                       int3      
0049900a cc                       int3      
0049900b cc                       int3      
0049900c cc                       int3      
0049900d cc                       int3      
0049900e cc                       int3      
0049900f cc                       int3      
