00511040  55                       push       ebp
00511041  8bec                     mov        ebp, esp
00511043  83ec08                   sub        esp, 8
00511046  56                       push       esi
00511047  8bf1                     mov        esi, ecx
00511049  8b4e74                   mov        ecx, dword ptr [esi + 0x74]
0051104c  85c9                     test       ecx, ecx
0051104e  7466                     je         0x5110b6
00511050  e83bb0f8ff               call       0x49c090
00511055  84c0                     test       al, al
00511057  745d                     je         0x5110b6
00511059  8b06                     mov        eax, dword ptr [esi]
0051105b  85c0                     test       eax, eax
0051105d  8bc8                     mov        ecx, eax
0051105f  7503                     jne        0x511064
00511061  8d4e08                   lea        ecx, [esi + 8]
00511064  85c0                     test       eax, eax
00511066  53                       push       ebx
00511067  57                       push       edi
00511068  8bf8                     mov        edi, eax
0051106a  7503                     jne        0x51106f
0051106c  8d7e08                   lea        edi, [esi + 8]
0051106f  8b5d08                   mov        ebx, dword ptr [ebp + 8]
00511072  8b01                     mov        eax, dword ptr [ecx]
00511074  53                       push       ebx
00511075  ff5008                   call       dword ptr [eax + 8]
00511078  8b17                     mov        edx, dword ptr [edi]
0051107a  d8650c                   fsub       dword ptr [ebp + 0xc]
0051107d  53                       push       ebx
0051107e  8bcf                     mov        ecx, edi
00511080  d9e1                     fabs       
00511082  dd5df8                   fstp       qword ptr [ebp - 8]
00511085  ff5208                   call       dword ptr [edx + 8]
00511088  d9e1                     fabs       
0051108a  dc0de8b8ca00             fmul       qword ptr [0xcab8e8]
00511090  dc5df8                   fcomp      qword ptr [ebp - 8]
00511093  dfe0                     fnstsw     ax
00511095  f6c401                   test       ah, 1
00511098  741a                     je         0x5110b4
0051109a  8b0e                     mov        ecx, dword ptr [esi]
0051109c  85c9                     test       ecx, ecx
0051109e  7503                     jne        0x5110a3
005110a0  8d4e08                   lea        ecx, [esi + 8]
005110a3  8b550c                   mov        edx, dword ptr [ebp + 0xc]
005110a6  8b01                     mov        eax, dword ptr [ecx]
005110a8  52                       push       edx
005110a9  53                       push       ebx
005110aa  ff500c                   call       dword ptr [eax + 0xc]
005110ad  c686f800000001           mov        byte ptr [esi + 0xf8], 1
005110b4  5f                       pop        edi
005110b5  5b                       pop        ebx
005110b6  5e                       pop        esi
005110b7  8be5                     mov        esp, ebp
005110b9  5d                       pop        ebp
005110ba  c20800                   ret        8
