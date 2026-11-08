007442a0 45                       inc       ebp
007442a1 fc                       cld       
007442a2 09e8                     or        eax, ebp
007442a4 3802                     cmp       byte ptr [edx], al
007442a6 cc                       int3      
007442a7 ff8d8e5c1500             dec       dword ptr [ebp + 0x155c8e]
007442ad 00c6                     add       dh, al
007442af 45                       inc       ebp
007442b0 fc                       cld       
007442b1 0ae8                     or        ch, al
007442b3 2902                     sub       dword ptr [edx], eax
007442b5 cc                       int3      
007442b6 ff8d8e641500             dec       dword ptr [ebp + 0x15648e]
007442bc 00c6                     add       dh, al
007442be 45                       inc       ebp
007442bf fc                       cld       
007442c0 0be8                     or        ebp, eax
007442c2 9a10ccff8d8ea4           lcall     0xa48e, 0x8dffcc10
007442c9 150000c645               adc       eax, 0x45c60000
007442ce fc                       cld       
007442cf 0ce8                     or        al, 0xe8
007442d1 0b02                     or        eax, dword ptr [edx]
007442d3 cc                       int3      
007442d4 ff8d8eac1500             dec       dword ptr [ebp + 0x15ac8e]
007442da 00c6                     add       dh, al
007442dc 45                       inc       ebp
007442dd fc                       cld       
007442de 0de8fc01cc               or        eax, 0xcc01fce8
007442e3 ff8d8eb41500             dec       dword ptr [ebp + 0x15b48e]
007442e9 00c6                     add       dh, al
007442eb 45                       inc       ebp
007442ec fc                       cld       
007442ed 0e                       push      cs
007442ee e89dfecbff               call      0x404190
007442f3 c645fc0f                 mov       byte ptr [ebp - 4], 0xf
007442f7 8d8ebc150000             lea       ecx, [esi + 0x15bc]
007442fd e88efecbff               call      0x404190
00744302 8d8ec4150000             lea       ecx, [esi + 0x15c4]
00744308 c645fc10                 mov       byte ptr [ebp - 4], 0x10
0074430c e8cf01ccff               call      0x4044e0
00744311 8d8ecc150000             lea       ecx, [esi + 0x15cc]
00744317 c645fc11                 mov       byte ptr [ebp - 4], 0x11
0074431b e8c001ccff               call      0x4044e0
00744320 6810204000               push      0x402010
00744325 68e0444000               push      0x4044e0
0074432a 6a02                     push      2
0074432c 6a08                     push      8
0074432e 8d                       .byte     0x8d
0074432f 8e                       .byte     0x8e
