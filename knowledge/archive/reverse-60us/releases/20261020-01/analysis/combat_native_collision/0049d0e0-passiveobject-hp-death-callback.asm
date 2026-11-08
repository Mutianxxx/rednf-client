0049d0e0 56                       push      esi
0049d0e1 8bf1                     mov       esi, ecx
0049d0e3 8b06                     mov       eax, dword ptr [esi]
0049d0e5 ff903c030000             call      dword ptr [eax + 0x33c]
0049d0eb 8a4834                   mov       cl, byte ptr [eax + 0x34]
0049d0ee 84c9                     test      cl, cl
0049d0f0 7428                     je        0x49d11a
0049d0f2 8b16                     mov       edx, dword ptr [esi]
0049d0f4 8bce                     mov       ecx, esi
0049d0f6 ff9238020000             call      dword ptr [edx + 0x238]
0049d0fc 85c0                     test      eax, eax
0049d0fe 7e1a                     jle       0x49d11a
0049d100 8b06                     mov       eax, dword ptr [esi]
0049d102 8bce                     mov       ecx, esi
0049d104 ff9034020000             call      dword ptr [eax + 0x234]
0049d10a 85c0                     test      eax, eax
0049d10c 7f0c                     jg        0x49d11a
0049d10e 8b16                     mov       edx, dword ptr [esi]
0049d110 6a00                     push      0
0049d112 8bce                     mov       ecx, esi
0049d114 ff9264010000             call      dword ptr [edx + 0x164]
0049d11a 5e                       pop       esi
0049d11b c21400                   ret       0x14
0049d11e cc                       int3      
0049d11f cc                       int3      
