00407bf0 55                       push      ebp
00407bf1 8bec                     mov       ebp, esp
00407bf3 8b9148010000             mov       edx, dword ptr [ecx + 0x148]
00407bf9 85d2                     test      edx, edx
00407bfb 8b4508                   mov       eax, dword ptr [ebp + 8]
00407bfe 89814c010000             mov       dword ptr [ecx + 0x14c], eax
00407c04 7509                     jne       0x407c0f
00407c06 8b11                     mov       edx, dword ptr [ecx]
00407c08 50                       push      eax
00407c09 ff9200010000             call      dword ptr [edx + 0x100]
00407c0f 5d                       pop       ebp
00407c10 c20400                   ret       4
00407c13 cc                       int3      
00407c14 cc                       int3      
00407c15 cc                       int3      
00407c16 cc                       int3      
00407c17 cc                       int3      
00407c18 cc                       int3      
00407c19 cc                       int3      
00407c1a cc                       int3      
00407c1b cc                       int3      
00407c1c cc                       int3      
00407c1d cc                       int3      
00407c1e cc                       int3      
00407c1f cc                       int3      
00407c20 8b8118010000             mov       eax, dword ptr [ecx + 0x118]
00407c26 c3                       ret       
00407c27 cc                       int3      
00407c28 cc                       int3      
00407c29 cc                       int3      
00407c2a cc                       int3      
00407c2b cc                       int3      
00407c2c cc                       int3      
00407c2d cc                       int3      
00407c2e cc                       int3      
00407c2f cc                       int3      
