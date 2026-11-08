008848fe 8d4df0                   lea       ecx, [ebp - 0x10]
00884901 51                       push      ecx
00884902 e8d9bbfaff               call      0x8304e0
00884907 83c404                   add       esp, 4
0088490a 684c36e200               push      0xe2364c
0088490f 8d4df0                   lea       ecx, [ebp - 0x10]
00884912 e8d99eb8ff               call      0x40e7f0
00884917 84c0                     test      al, al
00884919 7408                     je        0x884923
0088491b 897e18                   mov       dword ptr [esi + 0x18], edi
0088491e e9f90f0000               jmp       0x88591c
00884923 681c36e200               push      0xe2361c
00884928 8d4df0                   lea       ecx, [ebp - 0x10]
0088492b e8c09eb8ff               call      0x40e7f0
00884930 84c0                     test      al, al
00884932 740c                     je        0x884940
00884934 c7461801000000           mov       dword ptr [esi + 0x18], 1
0088493b e9dc0f0000               jmp       0x88591c
00884940 680036e200               push      0xe23600
00884945 8d4df0                   lea       ecx, [ebp - 0x10]
00884948 e8a39eb8ff               call      0x40e7f0
0088494d 84c0                     test      al, al
0088494f 740c                     je        0x88495d
00884951 c7461802000000           mov       dword ptr [esi + 0x18], 2
00884958 e9bf0f0000               jmp       0x88591c
