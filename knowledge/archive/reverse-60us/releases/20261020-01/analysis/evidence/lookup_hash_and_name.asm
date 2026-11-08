; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 00a56000..00a56180 (end exclusive); file offset 00656000
; This is an instruction excerpt, not a recovered original source file.
00a56000  55                       push       ebp
00a56001  8bec                     mov        ebp, esp
00a56003  6aff                     push       -1
00a56005  6823fbc800               push       0xc8fb23
00a5600a  64a100000000             mov        eax, dword ptr fs:[0]
00a56010  50                       push       eax
00a56011  64892500000000           mov        dword ptr fs:[0], esp
00a56018  81ec88020000             sub        esp, 0x288
00a5601e  53                       push       ebx
00a5601f  33db                     xor        ebx, ebx
00a56021  56                       push       esi
00a56022  57                       push       edi
00a56023  8bf9                     mov        edi, ecx
00a56025  897df0                   mov        dword ptr [ebp - 0x10], edi
00a56028  c745b06c39e100           mov        dword ptr [ebp - 0x50], 0xe1396c
00a5602f  c745d007000000           mov        dword ptr [ebp - 0x30], 7
00a56036  895dcc                   mov        dword ptr [ebp - 0x34], ebx
00a56039  66895dbc                 mov        word ptr [ebp - 0x44], bx
00a5603d  895db4                   mov        dword ptr [ebp - 0x4c], ebx
00a56040  895dd4                   mov        dword ptr [ebp - 0x2c], ebx
00a56043  895dd8                   mov        dword ptr [ebp - 0x28], ebx
00a56046  895ddc                   mov        dword ptr [ebp - 0x24], ebx
00a56049  895de0                   mov        dword ptr [ebp - 0x20], ebx
00a5604c  895de4                   mov        dword ptr [ebp - 0x1c], ebx
00a5604f  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00a56052  53                       push       ebx
00a56053  53                       push       ebx
00a56054  6804010000               push       0x104
00a56059  8d856cfdffff             lea        eax, [ebp - 0x294]
00a5605f  50                       push       eax
00a56060  51                       push       ecx
00a56061  895dfc                   mov        dword ptr [ebp - 4], ebx
00a56064  e887fbffff               call       0xa55bf0
00a56069  8d956cfdffff             lea        edx, [ebp - 0x294]
00a5606f  52                       push       edx
00a56070  e87bcc0300               call       0xa92cf0
00a56075  8a08                     mov        cl, byte ptr [eax]
00a56077  83c418                   add        esp, 0x18
00a5607a  3acb                     cmp        cl, bl
00a5607c  be05150000               mov        esi, 0x1505
00a56081  740f                     je         0xa56092
00a56083  8a08                     mov        cl, byte ptr [eax]
00a56085  6bf621                   imul       esi, esi, 0x21
00a56088  0fbed1                   movsx      edx, cl
00a5608b  40                       inc        eax
00a5608c  03f2                     add        esi, edx
00a5608e  3acb                     cmp        cl, bl
00a56090  75f1                     jne        0xa56083
00a56092  8d45b0                   lea        eax, [ebp - 0x50]
00a56095  50                       push       eax
00a56096  8d8d78ffffff             lea        ecx, [ebp - 0x88]
00a5609c  89b574ffffff             mov        dword ptr [ebp - 0x8c], esi
00a560a2  e8a9230000               call       0xa58450
00a560a7  8b4718                   mov        eax, dword ptr [edi + 0x18]
00a560aa  8b4f14                   mov        ecx, dword ptr [edi + 0x14]
00a560ad  53                       push       ebx
00a560ae  68404fa500               push       0xa54f40
00a560b3  8d9574ffffff             lea        edx, [ebp - 0x8c]
00a560b9  52                       push       edx
00a560ba  50                       push       eax
00a560bb  51                       push       ecx
00a560bc  8d45e8                   lea        eax, [ebp - 0x18]
00a560bf  50                       push       eax
00a560c0  c645fc01                 mov        byte ptr [ebp - 4], 1
00a560c4  e8171f0000               call       0xa57fe0
00a560c9  8b4598                   mov        eax, dword ptr [ebp - 0x68]
00a560cc  8b5de8                   mov        ebx, dword ptr [ebp - 0x18]
00a560cf  83c418                   add        esp, 0x18
00a560d2  83f808                   cmp        eax, 8
00a560d5  c78578ffffff6c39e100     mov        dword ptr [ebp - 0x88], 0xe1396c
00a560df  720c                     jb         0xa560ed
00a560e1  8b4d84                   mov        ecx, dword ptr [ebp - 0x7c]
00a560e4  51                       push       ecx
00a560e5  e8f39e1a00               call       0xbfffdd
00a560ea  83c404                   add        esp, 4
00a560ed  8b7f18                   mov        edi, dword ptr [edi + 0x18]
00a560f0  3bdf                     cmp        ebx, edi
00a560f2  745c                     je         0xa56150
00a560f4  3933                     cmp        dword ptr [ebx], esi
00a560f6  7558                     jne        0xa56150
00a560f8  8bfb                     mov        edi, ebx
00a560fa  83c310                   add        ebx, 0x10
00a560fd  8d4900                   lea        ecx, [ecx]
00a56100  3b7dec                   cmp        edi, dword ptr [ebp - 0x14]
00a56103  742d                     je         0xa56132
00a56105  837b1408                 cmp        dword ptr [ebx + 0x14], 8
00a56109  7204                     jb         0xa5610f
00a5610b  8b03                     mov        eax, dword ptr [ebx]
00a5610d  eb02                     jmp        0xa56111
00a5610f  8bc3                     mov        eax, ebx
00a56111  8d956cfdffff             lea        edx, [ebp - 0x294]
00a56117  52                       push       edx
00a56118  50                       push       eax
00a56119  e8cdac1a00               call       0xc00deb
00a5611e  83c408                   add        esp, 8
00a56121  85c0                     test       eax, eax
00a56123  7424                     je         0xa56149
00a56125  8b473c                   mov        eax, dword ptr [edi + 0x3c]
00a56128  83c73c                   add        edi, 0x3c
00a5612b  83c33c                   add        ebx, 0x3c
00a5612e  3bc6                     cmp        eax, esi
00a56130  74ce                     je         0xa56100
00a56132  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
00a56135  8b5118                   mov        edx, dword ptr [ecx + 0x18]
00a56138  8b7508                   mov        esi, dword ptr [ebp + 8]
00a5613b  8916                     mov        dword ptr [esi], edx
00a5613d  837dd008                 cmp        dword ptr [ebp - 0x30], 8
00a56141  7224                     jb         0xa56167
00a56143  8b45bc                   mov        eax, dword ptr [ebp - 0x44]
00a56146  50                       push       eax
00a56147  eb16                     jmp        0xa5615f
00a56149  8b7508                   mov        esi, dword ptr [ebp + 8]
00a5614c  893e                     mov        dword ptr [esi], edi
00a5614e  ebed                     jmp        0xa5613d
00a56150  837dd008                 cmp        dword ptr [ebp - 0x30], 8
00a56154  8b7508                   mov        esi, dword ptr [ebp + 8]
00a56157  893e                     mov        dword ptr [esi], edi
00a56159  720c                     jb         0xa56167
00a5615b  8b4dbc                   mov        ecx, dword ptr [ebp - 0x44]
00a5615e  51                       push       ecx
00a5615f  e8799e1a00               call       0xbfffdd
00a56164  83c404                   add        esp, 4
00a56167  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00a5616a  5f                       pop        edi
00a5616b  8bc6                     mov        eax, esi
00a5616d  5e                       pop        esi
00a5616e  5b                       pop        ebx
00a5616f  64890d00000000           mov        dword ptr fs:[0], ecx
00a56176  8be5                     mov        esp, ebp
00a56178  5d                       pop        ebp
00a56179  c20800                   ret        8
00a5617c  cc                       int3       
00a5617d  cc                       int3       
00a5617e  cc                       int3       
00a5617f  cc                       int3       
