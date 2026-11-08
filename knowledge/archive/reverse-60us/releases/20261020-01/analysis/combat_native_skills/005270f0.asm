005270f0  55                       push       ebp
005270f1  8bec                     mov        ebp, esp
005270f3  8b8148040000             mov        eax, dword ptr [ecx + 0x448]
005270f9  8b914c040000             mov        edx, dword ptr [ecx + 0x44c]
005270ff  81c144040000             add        ecx, 0x444
00527105  2bd0                     sub        edx, eax
00527107  b895204f09               mov        eax, 0x94f2095
0052710c  f7ea                     imul       edx
0052710e  8b4508                   mov        eax, dword ptr [ebp + 8]
00527111  56                       push       esi
00527112  c1fa04                   sar        edx, 4
00527115  8bf2                     mov        esi, edx
00527117  c1ee1f                   shr        esi, 0x1f
0052711a  03f2                     add        esi, edx
0052711c  3bc6                     cmp        eax, esi
0052711e  5e                       pop        esi
0052711f  730a                     jae        0x52712b
00527121  50                       push       eax
00527122  e869ffffff               call       0x527090
00527127  5d                       pop        ebp
00527128  c20400                   ret        4
0052712b  33c0                     xor        eax, eax
0052712d  5d                       pop        ebp
0052712e  c20400                   ret        4
00527131  cc                       int3       
00527132  cc                       int3       
00527133  cc                       int3       
00527134  cc                       int3       
00527135  cc                       int3       
00527136  cc                       int3       
00527137  cc                       int3       
00527138  cc                       int3       
00527139  cc                       int3       
0052713a  cc                       int3       
0052713b  cc                       int3       
0052713c  cc                       int3       
0052713d  cc                       int3       
0052713e  cc                       int3       
0052713f  cc                       int3       
00527140  8b15d8012101             mov        edx, dword ptr [0x12101d8]
00527146  8b5244                   mov        edx, dword ptr [edx + 0x44]
00527149  8b4104                   mov        eax, dword ptr [ecx + 4]
0052714c  8d0482                   lea        eax, [edx + eax*4]
0052714f  56                       push       esi
00527150  8b35dc012101             mov        esi, dword ptr [0x12101dc]
00527156  8bd0                     mov        edx, eax
00527158  33d6                     xor        edx, esi
0052715a  8910                     mov        dword ptr [eax], edx
0052715c  8b15d8012101             mov        edx, dword ptr [0x12101d8]
00527162  8b5248                   mov        edx, dword ptr [edx + 0x48]
00527165  8b4104                   mov        eax, dword ptr [ecx + 4]
00527168  8b35dc012101             mov        esi, dword ptr [0x12101dc]
0052716e  8d0482                   lea        eax, [edx + eax*4]
00527171  8bd0                     mov        edx, eax
00527173  33d6                     xor        edx, esi
00527175  8910                     mov        dword ptr [eax], edx
00527177  688d0e0000               push       0xe8d
0052717c  c6410801                 mov        byte ptr [ecx + 8], 1
00527180  51                       push       ecx
00527181  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
00527187  e874fe5e00               call       0xb17000
0052718c  5e                       pop        esi
0052718d  c3                       ret        
0052718e  cc                       int3       
0052718f  cc                       int3       
00527190  56                       push       esi
00527191  8d7140                   lea        esi, [ecx + 0x40]
00527194  57                       push       edi
00527195  8d4e38                   lea        ecx, [esi + 0x38]
00527198  e8c3aeedff               call       0x402060
0052719d  8bce                     mov        ecx, esi
0052719f  8bf8                     mov        edi, eax
005271a1  e85afd5d00               call       0xb06f00
005271a6  33c9                     xor        ecx, ecx
005271a8  3bc7                     cmp        eax, edi
005271aa  0f9dc1                   setge      cl
005271ad  5f                       pop        edi
005271ae  8ac1                     mov        al, cl
005271b0  5e                       pop        esi
005271b1  c3                       ret        
005271b2  cc                       int3       
005271b3  cc                       int3       
005271b4  cc                       int3       
005271b5  cc                       int3       
005271b6  cc                       int3       
005271b7  cc                       int3       
005271b8  cc                       int3       
005271b9  cc                       int3       
005271ba  cc                       int3       
005271bb  cc                       int3       
005271bc  cc                       int3       
005271bd  cc                       int3       
005271be  cc                       int3       
005271bf  cc                       int3       
005271c0  55                       push       ebp
005271c1  8bec                     mov        ebp, esp
005271c3  51                       push       ecx
005271c4  8b5104                   mov        edx, dword ptr [ecx + 4]
005271c7  8b4204                   mov        eax, dword ptr [edx + 4]
005271ca  53                       push       ebx
005271cb  8a5811                   mov        bl, byte ptr [eax + 0x11]
005271ce  84db                     test       bl, bl
005271d0  56                       push       esi
005271d1  57                       push       edi
005271d2  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
005271d5  751e                     jne        0x5271f5
005271d7  8b37                     mov        esi, dword ptr [edi]
005271d9  8da42400000000           lea        esp, [esp]
005271e0  39700c                   cmp        dword ptr [eax + 0xc], esi
005271e3  7d05                     jge        0x5271ea
005271e5  8b4008                   mov        eax, dword ptr [eax + 8]
005271e8  eb04                     jmp        0x5271ee
005271ea  8bd0                     mov        edx, eax
005271ec  8b00                     mov        eax, dword ptr [eax]
005271ee  8a                       .byte      0x8a
005271ef  58                       pop        eax