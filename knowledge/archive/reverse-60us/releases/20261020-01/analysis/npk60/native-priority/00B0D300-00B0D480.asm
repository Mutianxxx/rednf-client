00b0d300  00805e5dc210             add        byte ptr [eax + 0x10c25d5e], al
00b0d306  008b45088b4d             add        byte ptr [ebx + 0x4d8b0845], cl
00b0d30c  0c8b                     or         al, 0x8b
00b0d30e  55                       push       ebp
00b0d30f  108946108a45             adc        byte ptr [ecx + 0x458a1046], cl
00b0d315  1489                     adc        al, 0x89
00b0d317  4e                       dec        esi
00b0d318  1489                     adc        al, 0x89
00b0d31a  56                       push       esi
00b0d31b  188b168bce88             sbb        byte ptr [ebx - 0x773174ea], cl
00b0d321  46                       inc        esi
00b0d322  0dff523c85               or         eax, 0x853c52ff
00b0d327  c07c08b801               sar        byte ptr [eax + ecx - 0x48], 1
00b0d32c  0000                     add        byte ptr [eax], al
00b0d32e  008846045e5d             add        byte ptr [eax + 0x5d5e0446], cl
00b0d334  c21000                   ret        0x10
00b0d337  cc                       int3       
00b0d338  cc                       int3       
00b0d339  cc                       int3       
00b0d33a  cc                       int3       
00b0d33b  cc                       int3       
00b0d33c  cc                       int3       
00b0d33d  cc                       int3       
00b0d33e  cc                       int3       
00b0d33f  cc                       int3       
00b0d340  56                       push       esi
00b0d341  8bf1                     mov        esi, ecx
00b0d343  8b06                     mov        eax, dword ptr [esi]
00b0d345  ff5040                   call       dword ptr [eax + 0x40]
00b0d348  33c0                     xor        eax, eax
00b0d34a  894610                   mov        dword ptr [esi + 0x10], eax
00b0d34d  894614                   mov        dword ptr [esi + 0x14], eax
00b0d350  894618                   mov        dword ptr [esi + 0x18], eax
00b0d353  89461c                   mov        dword ptr [esi + 0x1c], eax
00b0d356  894620                   mov        dword ptr [esi + 0x20], eax
00b0d359  884604                   mov        byte ptr [esi + 4], al
00b0d35c  5e                       pop        esi
00b0d35d  c3                       ret        
00b0d35e  cc                       int3       
00b0d35f  cc                       int3       
00b0d360  6a00                     push       0
00b0d362  c6410c00                 mov        byte ptr [ecx + 0xc], 0
00b0d366  e835d0fbff               call       0xaca3a0
00b0d36b  6a02                     push       2
00b0d36d  e82ed0fbff               call       0xaca3a0
00b0d372  83c408                   add        esp, 8
00b0d375  c3                       ret        
00b0d376  cc                       int3       
00b0d377  cc                       int3       
00b0d378  cc                       int3       
00b0d379  cc                       int3       
00b0d37a  cc                       int3       
00b0d37b  cc                       int3       
00b0d37c  cc                       int3       
00b0d37d  cc                       int3       
00b0d37e  cc                       int3       
00b0d37f  cc                       int3       
00b0d380  8d4128                   lea        eax, [ecx + 0x28]
00b0d383  c3                       ret        
00b0d384  cc                       int3       
00b0d385  cc                       int3       
00b0d386  cc                       int3       
00b0d387  cc                       int3       
00b0d388  cc                       int3       
00b0d389  cc                       int3       
00b0d38a  cc                       int3       
00b0d38b  cc                       int3       
00b0d38c  cc                       int3       
00b0d38d  cc                       int3       
00b0d38e  cc                       int3       
00b0d38f  cc                       int3       
00b0d390  33c0                     xor        eax, eax
00b0d392  c3                       ret        
00b0d393  cc                       int3       
00b0d394  cc                       int3       
00b0d395  cc                       int3       
00b0d396  cc                       int3       
00b0d397  cc                       int3       
00b0d398  cc                       int3       
00b0d399  cc                       int3       
00b0d39a  cc                       int3       
00b0d39b  cc                       int3       
00b0d39c  cc                       int3       
00b0d39d  cc                       int3       
00b0d39e  cc                       int3       
00b0d39f  cc                       int3       
00b0d3a0  55                       push       ebp
00b0d3a1  8bec                     mov        ebp, esp
00b0d3a3  56                       push       esi
00b0d3a4  57                       push       edi
00b0d3a5  8b7d08                   mov        edi, dword ptr [ebp + 8]
00b0d3a8  c6410c01                 mov        byte ptr [ecx + 0xc], 1
00b0d3ac  837f1808                 cmp        dword ptr [edi + 0x18], 8
00b0d3b0  8d7704                   lea        esi, [edi + 4]
00b0d3b3  7204                     jb         0xb0d3b9
00b0d3b5  8b06                     mov        eax, dword ptr [esi]
00b0d3b7  eb02                     jmp        0xb0d3bb
00b0d3b9  8bc6                     mov        eax, esi
00b0d3bb  6a00                     push       0
00b0d3bd  50                       push       eax
00b0d3be  e8bdcffbff               call       0xaca380
00b0d3c3  8b4718                   mov        eax, dword ptr [edi + 0x18]
00b0d3c6  83c408                   add        esp, 8
00b0d3c9  83f808                   cmp        eax, 8
00b0d3cc  7202                     jb         0xb0d3d0
00b0d3ce  8b36                     mov        esi, dword ptr [esi]
00b0d3d0  6a02                     push       2
00b0d3d2  56                       push       esi
00b0d3d3  e8a8cffbff               call       0xaca380
00b0d3d8  83c408                   add        esp, 8
00b0d3db  5f                       pop        edi
00b0d3dc  b001                     mov        al, 1
00b0d3de  5e                       pop        esi
00b0d3df  5d                       pop        ebp
00b0d3e0  c20400                   ret        4
00b0d3e3  cc                       int3       
00b0d3e4  cc                       int3       
00b0d3e5  cc                       int3       
00b0d3e6  cc                       int3       
00b0d3e7  cc                       int3       
00b0d3e8  cc                       int3       
00b0d3e9  cc                       int3       
00b0d3ea  cc                       int3       
00b0d3eb  cc                       int3       
00b0d3ec  cc                       int3       
00b0d3ed  cc                       int3       
00b0d3ee  cc                       int3       
00b0d3ef  cc                       int3       
00b0d3f0  53                       push       ebx
00b0d3f1  33db                     xor        ebx, ebx
00b0d3f3  56                       push       esi
00b0d3f4  57                       push       edi
00b0d3f5  8bf9                     mov        edi, ecx
00b0d3f7  885f0c                   mov        byte ptr [edi + 0xc], bl
00b0d3fa  885f0d                   mov        byte ptr [edi + 0xd], bl
00b0d3fd  895f10                   mov        dword ptr [edi + 0x10], ebx
00b0d400  895f14                   mov        dword ptr [edi + 0x14], ebx
00b0d403  895f18                   mov        dword ptr [edi + 0x18], ebx
00b0d406  895f1c                   mov        dword ptr [edi + 0x1c], ebx
00b0d409  c74720ff000000           mov        dword ptr [edi + 0x20], 0xff
00b0d410  8b0df4b80d01             mov        ecx, dword ptr [0x10db8f4]
00b0d416  3bcb                     cmp        ecx, ebx
00b0d418  7405                     je         0xb0d41f
00b0d41a  e83198feff               call       0xaf6c50
00b0d41f  8b472c                   mov        eax, dword ptr [edi + 0x2c]
00b0d422  8b4804                   mov        ecx, dword ptr [eax + 4]
00b0d425  8d7728                   lea        esi, [edi + 0x28]
00b0d428  51                       push       ecx
00b0d429  8bce                     mov        ecx, esi
00b0d42b  e800dbfdff               call       0xaeaf30
00b0d430  8b4604                   mov        eax, dword ptr [esi + 4]
00b0d433  894004                   mov        dword ptr [eax + 4], eax
00b0d436  8b4604                   mov        eax, dword ptr [esi + 4]
00b0d439  895e08                   mov        dword ptr [esi + 8], ebx
00b0d43c  8900                     mov        dword ptr [eax], eax
00b0d43e  8b7604                   mov        esi, dword ptr [esi + 4]
00b0d441  897608                   mov        dword ptr [esi + 8], esi
00b0d444  8b0df4b80d01             mov        ecx, dword ptr [0x10db8f4]
00b0d44a  3bcb                     cmp        ecx, ebx
00b0d44c  7405                     je         0xb0d453
00b0d44e  e80d98feff               call       0xaf6c60
00b0d453  8b17                     mov        edx, dword ptr [edi]
00b0d455  8bcf                     mov        ecx, edi
00b0d457  5f                       pop        edi
00b0d458  5e                       pop        esi
00b0d459  5b                       pop        ebx
00b0d45a  ff6238                   jmp        dword ptr [edx + 0x38]
00b0d45d  cc                       int3       
00b0d45e  cc                       int3       
00b0d45f  cc                       int3       
00b0d460  55                       push       ebp
00b0d461  8bec                     mov        ebp, esp
00b0d463  51                       push       ecx
00b0d464  56                       push       esi
00b0d465  8bf1                     mov        esi, ecx
00b0d467  8a4604                   mov        al, byte ptr [esi + 4]
00b0d46a  84c0                     test       al, al
00b0d46c  750a                     jne        0xb0d478
00b0d46e  b801000080               mov        eax, 0x80000001
00b0d473  5e                       pop        esi
00b0d474  8be5                     mov        esp, ebp
00b0d476  5d                       pop        ebp
00b0d477  c3                       ret        
00b0d478  8b0df4b80d01             mov        ecx, dword ptr [0x10db8f4]
00b0d47e  85c9                     test       ecx, ecx