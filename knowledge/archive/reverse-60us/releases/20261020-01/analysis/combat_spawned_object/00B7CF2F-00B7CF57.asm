00b7cf2f  55                       push       ebp
00b7cf30  57                       push       edi
00b7cf31  8d442438                 lea        eax, [esp + 0x38]
00b7cf35  68f8b8ca00               push       0xcab8f8
00b7cf3a  50                       push       eax
00b7cf3b  e8cd3f0800               call       0xc00f0d
00b7cf40  8b842454040000           mov        eax, dword ptr [esp + 0x454]
00b7cf47  8b16                     mov        edx, dword ptr [esi]
00b7cf49  83c410                   add        esp, 0x10
00b7cf4c  50                       push       eax
00b7cf4d  8d4c2434                 lea        ecx, [esp + 0x34]
00b7cf51  51                       push       ecx
00b7cf52  8bce                     mov        ecx, esi
00b7cf54  ff5208                   call       dword ptr [edx + 8]