004b9bf0  55                       push       ebp
004b9bf1  8bec                     mov        ebp, esp
004b9bf3  8b4508                   mov        eax, dword ptr [ebp + 8]
004b9bf6  83f801                   cmp        eax, 1
004b9bf9  7515                     jne        0x4b9c10
004b9bfb  8b01                     mov        eax, dword ptr [ecx]
004b9bfd  6a03                     push       3
004b9bff  ff9044030000             call       dword ptr [eax + 0x344]
004b9c05  8bc8                     mov        ecx, eax
004b9c07  e8e4050000               call       0x4ba1f0
004b9c0c  5d                       pop        ebp
004b9c0d  c20400                   ret        4
004b9c10  83f802                   cmp        eax, 2
004b9c13  7515                     jne        0x4b9c2a
004b9c15  8b11                     mov        edx, dword ptr [ecx]
004b9c17  6a03                     push       3
004b9c19  ff9244030000             call       dword ptr [edx + 0x344]
004b9c1f  8bc8                     mov        ecx, eax
004b9c21  e87ab9ffff               call       0x4b55a0
004b9c26  5d                       pop        ebp
004b9c27  c20400                   ret        4
004b9c2a  83f803                   cmp        eax, 3
004b9c2d  750e                     jne        0x4b9c3d
004b9c2f  8b01                     mov        eax, dword ptr [ecx]
004b9c31  6a03                     push       3
004b9c33  ff90a0040000             call       dword ptr [eax + 0x4a0]
004b9c39  5d                       pop        ebp
004b9c3a  c20400                   ret        4
004b9c3d  83f804                   cmp        eax, 4
004b9c40  7515                     jne        0x4b9c57
004b9c42  8b11                     mov        edx, dword ptr [ecx]
004b9c44  6a03                     push       3
004b9c46  ff9244030000             call       dword ptr [edx + 0x344]
004b9c4c  8bc8                     mov        ecx, eax
004b9c4e  e80d060000               call       0x4ba260
004b9c53  5d                       pop        ebp
004b9c54  c20400                   ret        4
004b9c57  b8e8030000               mov        eax, 0x3e8
004b9c5c  5d                       pop        ebp
004b9c5d  c20400                   ret        4
