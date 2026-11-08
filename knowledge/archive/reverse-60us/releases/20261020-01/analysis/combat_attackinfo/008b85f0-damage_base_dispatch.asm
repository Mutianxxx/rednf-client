008b85f0  55                       push       ebp
008b85f1  8bec                     mov        ebp, esp
008b85f3  8b4508                   mov        eax, dword ptr [ebp + 8]
008b85f6  8b8891010000             mov        ecx, dword ptr [eax + 0x191]
008b85fc  8bd1                     mov        edx, ecx
008b85fe  83e221                   and        edx, 0x21
008b8601  80fa21                   cmp        dl, 0x21
008b8604  752e                     jne        0x8b8634
008b8606  8a888d010000             mov        cl, byte ptr [eax + 0x18d]
008b860c  84c9                     test       cl, cl
008b860e  7415                     je         0x8b8625
008b8610  8a888e010000             mov        cl, byte ptr [eax + 0x18e]
008b8616  84c9                     test       cl, cl
008b8618  740b                     je         0x8b8625
008b861a  50                       push       eax
008b861b  e840ffffff               call       0x8b8560
008b8620  83c404                   add        esp, 4
008b8623  5d                       pop        ebp
008b8624  c3                       ret        
008b8625  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
008b8628  51                       push       ecx
008b8629  50                       push       eax
008b862a  e891f3ffff               call       0x8b79c0
008b862f  83c408                   add        esp, 8
008b8632  5d                       pop        ebp
008b8633  c3                       ret        
008b8634  81e181000000             and        ecx, 0x81
008b863a  80f981                   cmp        cl, 0x81
008b863d  74db                     je         0x8b861a
008b863f  8b550c                   mov        edx, dword ptr [ebp + 0xc]
008b8642  52                       push       edx
008b8643  50                       push       eax
008b8644  e877f3ffff               call       0x8b79c0
008b8649  83c408                   add        esp, 8
008b864c  5d                       pop        ebp
008b864d  c3                       ret        
