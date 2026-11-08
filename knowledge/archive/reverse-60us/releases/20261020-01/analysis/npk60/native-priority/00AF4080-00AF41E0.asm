00af4080  46                       inc        esi
00af4081  08895e20c746             or         byte ptr [ecx + 0x46c7205e], cl
00af4087  2401                     and        al, 1
00af4089  0000                     add        byte ptr [eax], al
00af408b  00895e2833c9             add        byte ptr [ecx - 0x36ccd7a2], cl
00af4091  894e0c                   mov        dword ptr [esi + 0xc], ecx
00af4094  894e10                   mov        dword ptr [esi + 0x10], ecx
00af4097  894e14                   mov        dword ptr [esi + 0x14], ecx
00af409a  894e18                   mov        dword ptr [esi + 0x18], ecx
00af409d  894e1c                   mov        dword ptr [esi + 0x1c], ecx
00af40a0  c7464807000000           mov        dword ptr [esi + 0x48], 7
00af40a7  895e44                   mov        dword ptr [esi + 0x44], ebx
00af40aa  895dfc                   mov        dword ptr [ebp - 4], ebx
00af40ad  66895e34                 mov        word ptr [esi + 0x34], bx
00af40b1  885e4c                   mov        byte ptr [esi + 0x4c], bl
00af40b4  895e54                   mov        dword ptr [esi + 0x54], ebx
00af40b7  895e58                   mov        dword ptr [esi + 0x58], ebx
00af40ba  895e5c                   mov        dword ptr [esi + 0x5c], ebx
00af40bd  8d7e60                   lea        edi, [esi + 0x60]
00af40c0  8bcf                     mov        ecx, edi
00af40c2  c645fc02                 mov        byte ptr [ebp - 4], 2
00af40c6  e86564ffff               call       0xaea530
00af40cb  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00af40ce  894704                   mov        dword ptr [edi + 4], eax
00af40d1  895f08                   mov        dword ptr [edi + 8], ebx
00af40d4  c7466c01000000           mov        dword ptr [esi + 0x6c], 1
00af40db  895e74                   mov        dword ptr [esi + 0x74], ebx
00af40de  895e78                   mov        dword ptr [esi + 0x78], ebx
00af40e1  895e7c                   mov        dword ptr [esi + 0x7c], ebx
00af40e4  899e80000000             mov        dword ptr [esi + 0x80], ebx
00af40ea  899e84000000             mov        dword ptr [esi + 0x84], ebx
00af40f0  899e8c000000             mov        dword ptr [esi + 0x8c], ebx
00af40f6  5f                       pop        edi
00af40f7  c6460401                 mov        byte ptr [esi + 4], 1
00af40fb  8bc6                     mov        eax, esi
00af40fd  5e                       pop        esi
00af40fe  5b                       pop        ebx
00af40ff  64890d00000000           mov        dword ptr fs:[0], ecx
00af4106  8be5                     mov        esp, ebp
00af4108  5d                       pop        ebp
00af4109  c20400                   ret        4
00af410c  cc                       int3       
00af410d  cc                       int3       
00af410e  cc                       int3       
00af410f  cc                       int3       
00af4110  53                       push       ebx
00af4111  56                       push       esi
00af4112  8bf1                     mov        esi, ecx
00af4114  33db                     xor        ebx, ebx
00af4116  57                       push       edi
00af4117  8d4e70                   lea        ecx, [esi + 0x70]
00af411a  c70668bae600             mov        dword ptr [esi], 0xe6ba68
00af4120  895e08                   mov        dword ptr [esi + 8], ebx
00af4123  e8d8240000               call       0xaf6600
00af4128  8d7e60                   lea        edi, [esi + 0x60]
00af412b  8bcf                     mov        ecx, edi
00af412d  e8fecbc5ff               call       0x750d30
00af4132  8b4704                   mov        eax, dword ptr [edi + 4]
00af4135  50                       push       eax
00af4136  e8a2be1000               call       0xbfffdd
00af413b  895f04                   mov        dword ptr [edi + 4], ebx
00af413e  8b4654                   mov        eax, dword ptr [esi + 0x54]
00af4141  83c404                   add        esp, 4
00af4144  3bc3                     cmp        eax, ebx
00af4146  740b                     je         0xaf4153
00af4148  8bc8                     mov        ecx, eax
00af414a  51                       push       ecx
00af414b  e8b9bf1000               call       0xc00109
00af4150  83c404                   add        esp, 4
00af4153  837e4808                 cmp        dword ptr [esi + 0x48], 8
00af4157  720c                     jb         0xaf4165
00af4159  8b5634                   mov        edx, dword ptr [esi + 0x34]
00af415c  52                       push       edx
00af415d  e87bbe1000               call       0xbfffdd
00af4162  83c404                   add        esp, 4
00af4165  895e44                   mov        dword ptr [esi + 0x44], ebx
00af4168  c7464807000000           mov        dword ptr [esi + 0x48], 7
00af416f  66895e34                 mov        word ptr [esi + 0x34], bx
00af4173  5f                       pop        edi
00af4174  885e04                   mov        byte ptr [esi + 4], bl
00af4177  c706d4b8ca00             mov        dword ptr [esi], 0xcab8d4
00af417d  5e                       pop        esi
00af417e  5b                       pop        ebx
00af417f  c3                       ret        
00af4180  55                       push       ebp
00af4181  8bec                     mov        ebp, esp
00af4183  83ec10                   sub        esp, 0x10
00af4186  56                       push       esi
00af4187  8b7178                   mov        esi, dword ptr [ecx + 0x78]
00af418a  57                       push       edi
00af418b  8d7970                   lea        edi, [ecx + 0x70]
00af418e  2b7704                   sub        esi, dword ptr [edi + 4]
00af4191  8d45f0                   lea        eax, [ebp - 0x10]
00af4194  50                       push       eax
00af4195  8bcf                     mov        ecx, edi
00af4197  c1fe04                   sar        esi, 4
00af419a  c745f400000000           mov        dword ptr [ebp - 0xc], 0
00af41a1  c745f800000000           mov        dword ptr [ebp - 8], 0
00af41a8  c745fc00000000           mov        dword ptr [ebp - 4], 0
00af41af  e88c240000               call       0xaf6640
00af41b4  8b4708                   mov        eax, dword ptr [edi + 8]
00af41b7  2b4704                   sub        eax, dword ptr [edi + 4]
00af41ba  c1f804                   sar        eax, 4
00af41bd  3bf0                     cmp        esi, eax
00af41bf  7226                     jb         0xaf41e7
00af41c1  50                       push       eax
00af41c2  56                       push       esi
00af41c3  6868a9e600               push       0xe6a968
00af41c8  68a0b3cb00               push       0xcbb3a0
00af41cd  ff15bc2eff00             call       dword ptr [0xff2ebc]
00af41d3  83c410                   add        esp, 0x10
00af41d6  6a00                     push       0
00af41d8  6a00                     push       0
00af41da  6a00                     push       0
00af41dc  68                       .byte      0x68
00af41dd  8c00                     mov        word ptr [eax], es
00af41df  00                       .byte      0x00