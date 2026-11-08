00512400  55                       push       ebp
00512401  8bec                     mov        ebp, esp
00512403  8b4508                   mov        eax, dword ptr [ebp + 8]
00512406  894174                   mov        dword ptr [ecx + 0x74], eax
00512409  e882ffffff               call       0x512390
0051240e  5d                       pop        ebp
0051240f  c20400                   ret        4
00512412  cc                       int3       
00512413  cc                       int3       
00512414  cc                       int3       
00512415  cc                       int3       
00512416  cc                       int3       
00512417  cc                       int3       
00512418  cc                       int3       
00512419  cc                       int3       
0051241a  cc                       int3       
0051241b  cc                       int3       
0051241c  cc                       int3       
0051241d  cc                       int3       
0051241e  cc                       int3       
0051241f  cc                       int3       
