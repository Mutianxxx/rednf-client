0072b47f  6a01                     push       1
0072b481  6a01                     push       1
0072b483  6a01                     push       1
0072b485  6a17                     push       0x17
0072b487  ff9068070000             call       dword ptr [eax + 0x768]
0072b48d  84c0                     test       al, al
0072b48f  0f846d010000             je         0x72b602
0072b495  8b06                     mov        eax, dword ptr [esi]
0072b497  53                       push       ebx
0072b498  6a01                     push       1
0072b49a  8bce                     mov        ecx, esi
0072b49c  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072b49f  ff9034020000             call       dword ptr [eax + 0x234]
0072b4a5  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
0072b4a8  8b55ec                   mov        edx, dword ptr [ebp - 0x14]
0072b4ab  2bc1                     sub        eax, ecx
0072b4ad  50                       push       eax
0072b4ae  8bce                     mov        ecx, esi
0072b4b0  ff92e8030000             call       dword ptr [edx + 0x3e8]
0072b4b6  895db4                   mov        dword ptr [ebp - 0x4c], ebx
0072b4b9  895db8                   mov        dword ptr [ebp - 0x48], ebx
0072b4bc  895dbc                   mov        dword ptr [ebp - 0x44], ebx
0072b4bf  8d45ec                   lea        eax, [ebp - 0x14]
0072b4c2  50                       push       eax
0072b4c3  8d4db0                   lea        ecx, [ebp - 0x50]
0072b4c6  c745fc24000000           mov        dword ptr [ebp - 4], 0x24
0072b4cd  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072b4d0  e84bbccdff               call       0x407120
0072b4d5  8d4dec                   lea        ecx, [ebp - 0x14]
0072b4d8  51                       push       ecx
0072b4d9  8d4db0                   lea        ecx, [ebp - 0x50]
0072b4dc  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072b4df  e83cbccdff               call       0x407120
0072b4e4  8d55ec                   lea        edx, [ebp - 0x14]
0072b4e7  52                       push       edx
0072b4e8  8d4db0                   lea        ecx, [ebp - 0x50]
0072b4eb  c745ec17000000           mov        dword ptr [ebp - 0x14], 0x17
0072b4f2  e829bccdff               call       0x407120
0072b4f7  8b06                     mov        eax, dword ptr [esi]
0072b4f9  6a17                     push       0x17
0072b4fb  8bce                     mov        ecx, esi
0072b4fd  ff904c060000             call       dword ptr [eax + 0x64c]
0072b503  50                       push       eax
0072b504  56                       push       esi
0072b505  8bcf                     mov        ecx, edi
0072b507  e824cfd3ff               call       0x468430
0072b50c  8d4dec                   lea        ecx, [ebp - 0x14]
0072b50f  51                       push       ecx
0072b510  8d4db0                   lea        ecx, [ebp - 0x50]
0072b513  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072b516  e805bccdff               call       0x407120
0072b51b  56                       push       esi
0072b51c  6a02                     push       2
0072b51e  8bcf                     mov        ecx, edi
0072b520  e83b4ae2ff               call       0x54ff60
0072b525  8d55ec                   lea        edx, [ebp - 0x14]
0072b528  52                       push       edx
0072b529  8d4db0                   lea        ecx, [ebp - 0x50]
0072b52c  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072b52f  e8ecbbcdff               call       0x407120
0072b534  8d45ec                   lea        eax, [ebp - 0x14]
0072b537  50                       push       eax
0072b538  8d4db0                   lea        ecx, [ebp - 0x50]
0072b53b  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072b53e  e8ddbbcdff               call       0x407120
0072b543  8d4dec                   lea        ecx, [ebp - 0x14]
0072b546  51                       push       ecx
0072b547  8d4db0                   lea        ecx, [ebp - 0x50]
0072b54a  c745ec04000000           mov        dword ptr [ebp - 0x14], 4
0072b551  e8cabbcdff               call       0x407120
0072b556  8d55ec                   lea        edx, [ebp - 0x14]
0072b559  52                       push       edx
0072b55a  8d4db0                   lea        ecx, [ebp - 0x50]
0072b55d  c745ec04000000           mov        dword ptr [ebp - 0x14], 4
0072b564  e8b7bbcdff               call       0x407120
0072b569  8d45ec                   lea        eax, [ebp - 0x14]
0072b56c  50                       push       eax
0072b56d  8d4db0                   lea        ecx, [ebp - 0x50]
0072b570  c745ece8030000           mov        dword ptr [ebp - 0x14], 0x3e8
0072b577  e8a4bbcdff               call       0x407120
0072b57c  8d4dec                   lea        ecx, [ebp - 0x14]
0072b57f  51                       push       ecx
0072b580  8d4db0                   lea        ecx, [ebp - 0x50]
0072b583  c745ece8030000           mov        dword ptr [ebp - 0x14], 0x3e8
0072b58a  e891bbcdff               call       0x407120
0072b58f  56                       push       esi
0072b590  6a01                     push       1
0072b592  8bcf                     mov        ecx, edi
0072b594  e8c749e2ff               call       0x54ff60
0072b599  99                       cdq        
0072b59a  2bc2                     sub        eax, edx
0072b59c  8d55ec                   lea        edx, [ebp - 0x14]
0072b59f  d1f8                     sar        eax, 1
0072b5a1  52                       push       edx
0072b5a2  8d4db0                   lea        ecx, [ebp - 0x50]
0072b5a5  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072b5a8  e873bbcdff               call       0x407120
0072b5ad  8b06                     mov        eax, dword ptr [esi]
0072b5af  53                       push       ebx
0072b5b0  53                       push       ebx
0072b5b1  6a01                     push       1
0072b5b3  8d4db0                   lea        ecx, [ebp - 0x50]
0072b5b6  51                       push       ecx
0072b5b7  6a0a                     push       0xa
0072b5b9  8bce                     mov        ecx, esi
0072b5bb  ff908c020000             call       dword ptr [eax + 0x28c]