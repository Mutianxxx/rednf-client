004cd7f0  8b8110150000             mov        eax, dword ptr [ecx + 0x1510]
004cd7f6  85c0                     test       eax, eax
004cd7f8  7414                     je         0x4cd80e
004cd7fa  8bc8                     mov        ecx, eax
004cd7fc  8b01                     mov        eax, dword ptr [ecx]
004cd7fe  ff90e0000000             call       dword ptr [eax + 0xe0]
004cd804  8bc8                     mov        ecx, eax
004cd806  83c104                   add        ecx, 4
004cd809  e95248f3ff               jmp        0x402060
004cd80e  83c8ff                   or         eax, 0xffffffff
004cd811  c3                       ret        
004cd812  cc                       int3       
004cd813  cc                       int3       
004cd814  cc                       int3       
004cd815  cc                       int3       
004cd816  cc                       int3       
004cd817  cc                       int3       
004cd818  cc                       int3       
004cd819  cc                       int3       
004cd81a  cc                       int3       
004cd81b  cc                       int3       
004cd81c  cc                       int3       
004cd81d  cc                       int3       
004cd81e  cc                       int3       
004cd81f  cc                       int3       
004cd820  55                       push       ebp
004cd821  8bec                     mov        ebp, esp
004cd823  83ec0c                   sub        esp, 0xc
004cd826  53                       push       ebx
004cd827  56                       push       esi
004cd828  8b750c                   mov        esi, dword ptr [ebp + 0xc]
004cd82b  8b06                     mov        eax, dword ptr [esi]
004cd82d  57                       push       edi
004cd82e  8bce                     mov        ecx, esi
004cd830  ff9094010000             call       dword ptr [eax + 0x194]
004cd836  8bc8                     mov        ecx, eax
004cd838  83c108                   add        ecx, 8
004cd83b  e82048f3ff               call       0x402060
