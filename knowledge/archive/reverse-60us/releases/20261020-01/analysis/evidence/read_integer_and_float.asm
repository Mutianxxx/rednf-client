; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 0082f7d0..0082f8f4 (end exclusive); file offset 0042f7d0
; This is an instruction excerpt, not a recovered original source file.
0082f7d0  55                       push       ebp
0082f7d1  8bec                     mov        ebp, esp
0082f7d3  56                       push       esi
0082f7d4  6a09                     push       9
0082f7d6  e8d5a72d00               call       0xb09fb0
0082f7db  83c404                   add        esp, 4
0082f7de  b928120501               mov        ecx, 0x1051228
0082f7e3  33f6                     xor        esi, esi
0082f7e5  e886310800               call       0x8b2970
0082f7ea  83f802                   cmp        eax, 2
0082f7ed  7527                     jne        0x82f816
0082f7ef  b928120501               mov        ecx, 0x1051228
0082f7f4  e8f7310800               call       0x8b29f0
0082f7f9  8bf0                     mov        esi, eax
0082f7fb  8b4508                   mov        eax, dword ptr [ebp + 8]
0082f7fe  85c0                     test       eax, eax
0082f800  7445                     je         0x82f847
0082f802  6a00                     push       0
0082f804  6a09                     push       9
0082f806  c60001                   mov        byte ptr [eax], 1
0082f809  e8e2a72d00               call       0xb09ff0
0082f80e  83c408                   add        esp, 8
0082f811  8bc6                     mov        eax, esi
0082f813  5e                       pop        esi
0082f814  5d                       pop        ebp
0082f815  c3                       ret        
0082f816  83f803                   cmp        eax, 3
0082f819  750c                     jne        0x82f827
0082f81b  b928120501               mov        ecx, 0x1051228
0082f820  e80b320800               call       0x8b2a30
0082f825  ebd2                     jmp        0x82f7f9
0082f827  83f804                   cmp        eax, 4
0082f82a  7511                     jne        0x82f83d
0082f82c  b928120501               mov        ecx, 0x1051228
0082f831  e83a320800               call       0x8b2a70
0082f836  e8091d3d00               call       0xc01544
0082f83b  ebbc                     jmp        0x82f7f9
0082f83d  8b4508                   mov        eax, dword ptr [ebp + 8]
0082f840  85c0                     test       eax, eax
0082f842  7403                     je         0x82f847
0082f844  c60000                   mov        byte ptr [eax], 0
0082f847  6a00                     push       0
0082f849  6a09                     push       9
0082f84b  e8a0a72d00               call       0xb09ff0
0082f850  83c408                   add        esp, 8
0082f853  8bc6                     mov        eax, esi
0082f855  5e                       pop        esi
0082f856  5d                       pop        ebp
0082f857  c3                       ret        
0082f858  cc                       int3       
0082f859  cc                       int3       
0082f85a  cc                       int3       
0082f85b  cc                       int3       
0082f85c  cc                       int3       
0082f85d  cc                       int3       
0082f85e  cc                       int3       
0082f85f  cc                       int3       
0082f860  55                       push       ebp
0082f861  8bec                     mov        ebp, esp
0082f863  51                       push       ecx
0082f864  6a09                     push       9
0082f866  e845a72d00               call       0xb09fb0
0082f86b  83c404                   add        esp, 4
0082f86e  b928120501               mov        ecx, 0x1051228
0082f873  c745fc00000000           mov        dword ptr [ebp - 4], 0
0082f87a  e8f1300800               call       0x8b2970
0082f87f  83f802                   cmp        eax, 2
0082f882  7530                     jne        0x82f8b4
0082f884  b928120501               mov        ecx, 0x1051228
0082f889  e862310800               call       0x8b29f0
0082f88e  8945fc                   mov        dword ptr [ebp - 4], eax
0082f891  db45fc                   fild       dword ptr [ebp - 4]
0082f894  8b4508                   mov        eax, dword ptr [ebp + 8]
0082f897  d95dfc                   fstp       dword ptr [ebp - 4]
0082f89a  85c0                     test       eax, eax
0082f89c  7448                     je         0x82f8e6
0082f89e  6a00                     push       0
0082f8a0  6a09                     push       9
0082f8a2  c60001                   mov        byte ptr [eax], 1
0082f8a5  e846a72d00               call       0xb09ff0
0082f8aa  d945fc                   fld        dword ptr [ebp - 4]
0082f8ad  83c408                   add        esp, 8
0082f8b0  8be5                     mov        esp, ebp
0082f8b2  5d                       pop        ebp
0082f8b3  c3                       ret        
0082f8b4  83f803                   cmp        eax, 3
0082f8b7  7512                     jne        0x82f8cb
0082f8b9  b928120501               mov        ecx, 0x1051228
0082f8be  e86d310800               call       0x8b2a30
0082f8c3  8945fc                   mov        dword ptr [ebp - 4], eax
0082f8c6  db45fc                   fild       dword ptr [ebp - 4]
0082f8c9  ebc9                     jmp        0x82f894
0082f8cb  83f804                   cmp        eax, 4
0082f8ce  750c                     jne        0x82f8dc
0082f8d0  b928120501               mov        ecx, 0x1051228
0082f8d5  e896310800               call       0x8b2a70
0082f8da  ebb8                     jmp        0x82f894
0082f8dc  8b4508                   mov        eax, dword ptr [ebp + 8]
0082f8df  85c0                     test       eax, eax
0082f8e1  7403                     je         0x82f8e6
0082f8e3  c60000                   mov        byte ptr [eax], 0
0082f8e6  6a00                     push       0
0082f8e8  6a09                     push       9
0082f8ea  e801a72d00               call       0xb09ff0
0082f8ef  d945fc                   fld        dword ptr [ebp - 4]
