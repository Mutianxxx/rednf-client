00745c30  55                       push       ebp
00745c31  8bec                     mov        ebp, esp
00745c33  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00745c36  8b5508                   mov        edx, dword ptr [ebp + 8]
00745c39  56                       push       esi
00745c3a  8bf1                     mov        esi, ecx
00745c3c  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00745c3f  50                       push       eax
00745c40  51                       push       ecx
00745c41  52                       push       edx
00745c42  8bce                     mov        ecx, esi
00745c44  e8d73ed7ff               call       0x4b9b20
00745c49  8b06                     mov        eax, dword ptr [esi]
00745c4b  8bce                     mov        ecx, esi
00745c4d  ff9070070000             call       dword ptr [eax + 0x770]
00745c53  5e                       pop        esi
00745c54  5d                       pop        ebp
00745c55  c20c00                   ret        0xc
00745c58  cc                       int3       
00745c59  cc                       int3       
00745c5a  cc                       int3       
00745c5b  cc                       int3       
00745c5c  cc                       int3       
00745c5d  cc                       int3       
00745c5e  cc                       int3       
00745c5f  cc                       int3       
00745c60  55                       push       ebp
00745c61  8bec                     mov        ebp, esp
00745c63  8a4508                   mov        al, byte ptr [ebp + 8]
00745c66  8881ae230000             mov        byte ptr [ecx + 0x23ae], al
00745c6c  5d                       pop        ebp
00745c6d  c20400                   ret        4
00745c70  8a                       .byte      0x8a
