00553ba0  55                       push       ebp
00553ba1  8bec                     mov        ebp, esp
00553ba3  56                       push       esi
00553ba4  8bf1                     mov        esi, ecx
00553ba6  57                       push       edi
00553ba7  8d4e40                   lea        ecx, [esi + 0x40]
00553baa  e8b1e4eaff               call       0x402060
00553baf  8bf8                     mov        edi, eax
00553bb1  8b4508                   mov        eax, dword ptr [ebp + 8]
00553bb4  48                       dec        eax
00553bb5  8d4e38                   lea        ecx, [esi + 0x38]
00553bb8  0faff8                   imul       edi, eax
00553bbb  e8a0e4eaff               call       0x402060
00553bc0  03c7                     add        eax, edi
00553bc2  5f                       pop        edi
00553bc3  5e                       pop        esi
00553bc4  5d                       pop        ebp
00553bc5  c20400                   ret        4