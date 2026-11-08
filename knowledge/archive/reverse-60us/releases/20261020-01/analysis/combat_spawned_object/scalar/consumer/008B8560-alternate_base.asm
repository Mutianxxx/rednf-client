008b8560  55                       push       ebp
008b8561  8bec                     mov        ebp, esp
008b8563  56                       push       esi
008b8564  8b7508                   mov        esi, dword ptr [ebp + 8]
008b8567  8a868d010000             mov        al, byte ptr [esi + 0x18d]
008b856d  84c0                     test       al, al
008b856f  7509                     jne        0x8b857a
008b8571  d905a4d7e900             fld        dword ptr [0xe9d7a4]
008b8577  5e                       pop        esi
008b8578  5d                       pop        ebp
008b8579  c3                       ret        
008b857a  dd8682010000             fld        qword ptr [esi + 0x182]
008b8580  e8bf8f3400               call       0xc01544
008b8585  0fbe8e8f010000           movsx      ecx, byte ptr [esi + 0x18f]
008b858c  50                       push       eax
008b858d  0fbe8690010000           movsx      eax, byte ptr [esi + 0x190]
008b8594  50                       push       eax
008b8595  51                       push       ecx
008b8596  e825feffff               call       0x8b83c0
008b859b  83c40c                   add        esp, 0xc
008b859e  d80e                     fmul       dword ptr [esi]
008b85a0  d84e2b                   fmul       dword ptr [esi + 0x2b]
008b85a3  5e                       pop        esi
008b85a4  5d                       pop        ebp
008b85a5  c3                       ret        