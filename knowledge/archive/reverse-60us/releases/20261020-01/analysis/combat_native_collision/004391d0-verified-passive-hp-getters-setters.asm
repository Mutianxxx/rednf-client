004391d0 55                       push      ebp
004391d1 8bec                     mov       ebp, esp
004391d3 8b4508                   mov       eax, dword ptr [ebp + 8]
004391d6 898124050000             mov       dword ptr [ecx + 0x524], eax
004391dc 5d                       pop       ebp
004391dd c20400                   ret       4
004391e0 8b8124050000             mov       eax, dword ptr [ecx + 0x524]
004391e6 c3                       ret       
004391e7 cc                       int3      
004391e8 cc                       int3      
004391e9 cc                       int3      
004391ea cc                       int3      
004391eb cc                       int3      
004391ec cc                       int3      
004391ed cc                       int3      
004391ee cc                       int3      
004391ef cc                       int3      
004391f0 55                       push      ebp
004391f1 8bec                     mov       ebp, esp
004391f3 8b4508                   mov       eax, dword ptr [ebp + 8]
004391f6 898128050000             mov       dword ptr [ecx + 0x528], eax
004391fc 5d                       pop       ebp
004391fd c20400                   ret       4
00439200 8b8128050000             mov       eax, dword ptr [ecx + 0x528]
00439206 c3                       ret       
