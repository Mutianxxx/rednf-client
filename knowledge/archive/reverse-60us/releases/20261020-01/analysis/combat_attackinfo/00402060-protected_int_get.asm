00402060  53                       push       ebx
00402061  8b1ddc012101             mov        ebx, dword ptr [0x12101dc]
00402067  56                       push       esi
00402068  57                       push       edi
00402069  8bf9                     mov        edi, ecx
0040206b  8b07                     mov        eax, dword ptr [edi]
0040206d  8b4f04                   mov        ecx, dword ptr [edi + 4]
00402070  33c3                     xor        eax, ebx
00402072  2bc7                     sub        eax, edi
00402074  3bc1                     cmp        eax, ecx
00402076  7414                     je         0x40208c
00402078  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
0040207e  6a3f                     push       0x3f
00402080  57                       push       edi
00402081  e82a507100               call       0xb170b0
00402086  8b1ddc012101             mov        ebx, dword ptr [0x12101dc]
0040208c  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
00402092  8b4704                   mov        eax, dword ptr [edi + 4]
00402095  8b5144                   mov        edx, dword ptr [ecx + 0x44]
00402098  c1e002                   shl        eax, 2
0040209b  8b3402                   mov        esi, dword ptr [edx + eax]
0040209e  03d0                     add        edx, eax
004020a0  33f2                     xor        esi, edx
004020a2  8b5148                   mov        edx, dword ptr [ecx + 0x48]
004020a5  03c2                     add        eax, edx
004020a7  8b10                     mov        edx, dword ptr [eax]
004020a9  33d0                     xor        edx, eax
004020ab  33f3                     xor        esi, ebx
004020ad  33d3                     xor        edx, ebx
004020af  3bf2                     cmp        esi, edx
004020b1  7408                     je         0x4020bb
004020b3  6a40                     push       0x40
004020b5  57                       push       edi
004020b6  e8f54f7100               call       0xb170b0
004020bb  5f                       pop        edi
004020bc  8bc6                     mov        eax, esi
004020be  5e                       pop        esi
004020bf  5b                       pop        ebx
004020c0  c3                       ret        
004020c1  cc                       int3       
004020c2  cc                       int3       
004020c3  cc                       int3       
004020c4  cc                       int3       
004020c5  cc                       int3       
004020c6  cc                       int3       
004020c7  cc                       int3       
004020c8  cc                       int3       
004020c9  cc                       int3       
004020ca  cc                       int3       
004020cb  cc                       int3       
004020cc  cc                       int3       
004020cd  cc                       int3       
004020ce  cc                       int3       
004020cf  cc                       int3       
004020d0  55                       push       ebp
004020d1  8bec                     mov        ebp, esp
004020d3  83791810                 cmp        dword ptr [ecx + 0x18], 0x10
004020d7  8b4508                   mov        eax, dword ptr [ebp + 8]
004020da  894114                   mov        dword ptr [ecx + 0x14], eax
004020dd  720b                     jb         0x4020ea
004020df  8b4904                   mov        ecx, dword ptr [ecx + 4]
004020e2  c6040100                 mov        byte ptr [ecx + eax], 0
004020e6  5d                       pop        ebp
004020e7  c20400                   ret        4
004020ea  c644010400               mov        byte ptr [ecx + eax + 4], 0
004020ef  5d                       pop        ebp
004020f0  c20400                   ret        4
004020f3  cc                       int3       
004020f4  cc                       int3       
004020f5  cc                       int3       
004020f6  cc                       int3       
004020f7  cc                       int3       
004020f8  cc                       int3       
004020f9  cc                       int3       
004020fa  cc                       int3       
004020fb  cc                       int3       
004020fc  cc                       int3       
004020fd  cc                       int3       
004020fe  cc                       int3       
004020ff  cc                       int3       
00402100  55                       push       ebp
00402101  8bec                     mov        ebp, esp
00402103  8b4508                   mov        eax, dword ptr [ebp + 8]
00402106  50                       push       eax
00402107  e811b87e00               call       0xbed91d
0040210c  83c404                   add        esp, 4
0040210f  5d                       pop        ebp
00402110  c20400                   ret        4
00402113  cc                       int3       
00402114  cc                       int3       
00402115  cc                       int3       
00402116  cc                       int3       
00402117  cc                       int3       
00402118  cc                       int3       
00402119  cc                       int3       
0040211a  cc                       int3       
0040211b  cc                       int3       
0040211c  cc                       int3       
0040211d  cc                       int3       
0040211e  cc                       int3       
0040211f  cc                       int3       
00402120  81c140100000             add        ecx, 0x1040
00402126  e935ffffff               jmp        0x402060
0040212b  cc                       int3       
0040212c  cc                       int3       
0040212d  cc                       int3       
0040212e  cc                       int3       
0040212f  cc                       int3       
00402130  8bc1                     mov        eax, ecx
00402132  33c9                     xor        ecx, ecx
00402134  c7401807000000           mov        dword ptr [eax + 0x18], 7
0040213b  89                       .byte      0x89
0040213c  48                       dec        eax
