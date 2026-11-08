0049cff0 55                       push      ebp
0049cff1 8bec                     mov       ebp, esp
0049cff3 8b4508                   mov       eax, dword ptr [ebp + 8]
0049cff6 56                       push      esi
0049cff7 8bf1                     mov       esi, ecx
0049cff9 39862c050000             cmp       dword ptr [esi + 0x52c], eax
0049cfff 7423                     je        0x49d024
0049d001 89862c050000             mov       dword ptr [esi + 0x52c], eax
0049d007 8b0d64310001             mov       ecx, dword ptr [0x1003164]
0049d00d 8b01                     mov       eax, dword ptr [ecx]
0049d00f ff9088000000             call      dword ptr [eax + 0x88]
0049d015 8b4850                   mov       ecx, dword ptr [eax + 0x50]
0049d018 85c9                     test      ecx, ecx
0049d01a 7408                     je        0x49d024
0049d01c 6a00                     push      0
0049d01e 56                       push      esi
0049d01f e83c90feff               call      0x486060
0049d024 5e                       pop       esi
0049d025 5d                       pop       ebp
0049d026 c20400                   ret       4
0049d029 cc                       int3      
0049d02a cc                       int3      
0049d02b cc                       int3      
0049d02c cc                       int3      
0049d02d cc                       int3      
0049d02e cc                       int3      
0049d02f cc                       int3      
