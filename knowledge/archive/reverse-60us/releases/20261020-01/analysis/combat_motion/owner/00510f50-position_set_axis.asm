00510f50  55                       push       ebp
00510f51  8bec                     mov        ebp, esp
00510f53  8b01                     mov        eax, dword ptr [ecx]
00510f55  85c0                     test       eax, eax
00510f57  c6818c00000001           mov        byte ptr [ecx + 0x8c], 1
00510f5e  7416                     je         0x510f76
00510f60  db450c                   fild       dword ptr [ebp + 0xc]
00510f63  8b5508                   mov        edx, dword ptr [ebp + 8]
00510f66  8bc8                     mov        ecx, eax
00510f68  8b01                     mov        eax, dword ptr [ecx]
00510f6a  51                       push       ecx
00510f6b  d91c24                   fstp       dword ptr [esp]
00510f6e  52                       push       edx
00510f6f  ff5004                   call       dword ptr [eax + 4]
00510f72  5d                       pop        ebp
00510f73  c20800                   ret        8
00510f76  db450c                   fild       dword ptr [ebp + 0xc]
00510f79  8b5508                   mov        edx, dword ptr [ebp + 8]
00510f7c  8b4108                   mov        eax, dword ptr [ecx + 8]
00510f7f  83c108                   add        ecx, 8
00510f82  51                       push       ecx
00510f83  d91c24                   fstp       dword ptr [esp]
00510f86  52                       push       edx
00510f87  ff5004                   call       dword ptr [eax + 4]
00510f8a  5d                       pop        ebp
00510f8b  c20800                   ret        8
