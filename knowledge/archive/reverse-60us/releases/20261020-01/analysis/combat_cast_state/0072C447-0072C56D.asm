0072c447  6a01                     push       1
0072c449  6a01                     push       1
0072c44b  6a01                     push       1
0072c44d  6a2c                     push       0x2c
0072c44f  8bce                     mov        ecx, esi
0072c451  ff9068070000             call       dword ptr [eax + 0x768]
0072c457  84c0                     test       al, al
0072c459  0f8420010000             je         0x72c57f
0072c45f  8b16                     mov        edx, dword ptr [esi]
0072c461  6a2c                     push       0x2c
0072c463  8bce                     mov        ecx, esi
0072c465  ff927c060000             call       dword ptr [edx + 0x67c]
0072c46b  8bf8                     mov        edi, eax
0072c46d  899d50ffffff             mov        dword ptr [ebp - 0xb0], ebx
0072c473  899d54ffffff             mov        dword ptr [ebp - 0xac], ebx
0072c479  899d58ffffff             mov        dword ptr [ebp - 0xa8], ebx
0072c47f  8d45ec                   lea        eax, [ebp - 0x14]
0072c482  50                       push       eax
0072c483  8d8d4cffffff             lea        ecx, [ebp - 0xb4]
0072c489  c745fc2d000000           mov        dword ptr [ebp - 4], 0x2d
0072c490  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072c493  e888accdff               call       0x407120
0072c498  8d4dec                   lea        ecx, [ebp - 0x14]
0072c49b  51                       push       ecx
0072c49c  8d8d4cffffff             lea        ecx, [ebp - 0xb4]
0072c4a2  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072c4a5  e876accdff               call       0x407120
0072c4aa  8d55ec                   lea        edx, [ebp - 0x14]
0072c4ad  52                       push       edx
0072c4ae  8d8d4cffffff             lea        ecx, [ebp - 0xb4]
0072c4b4  c745ec2c000000           mov        dword ptr [ebp - 0x14], 0x2c
0072c4bb  e860accdff               call       0x407120
0072c4c0  8b06                     mov        eax, dword ptr [esi]
0072c4c2  6a2c                     push       0x2c
0072c4c4  8bce                     mov        ecx, esi
0072c4c6  ff904c060000             call       dword ptr [eax + 0x64c]
0072c4cc  50                       push       eax
0072c4cd  56                       push       esi
0072c4ce  8bcf                     mov        ecx, edi
0072c4d0  e85bbfd3ff               call       0x468430
0072c4d5  8d4dec                   lea        ecx, [ebp - 0x14]
0072c4d8  51                       push       ecx
0072c4d9  8d8d4cffffff             lea        ecx, [ebp - 0xb4]
0072c4df  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072c4e2  e839accdff               call       0x407120
0072c4e7  8b16                     mov        edx, dword ptr [esi]
0072c4e9  53                       push       ebx
0072c4ea  53                       push       ebx
0072c4eb  6a0c                     push       0xc
0072c4ed  6aff                     push       -1
0072c4ef  6aff                     push       -1
0072c4f1  56                       push       esi
0072c4f2  6a2c                     push       0x2c
0072c4f4  8bce                     mov        ecx, esi
0072c4f6  ff924c060000             call       dword ptr [edx + 0x64c]
0072c4fc  50                       push       eax
0072c4fd  6a01                     push       1
0072c4ff  8bcf                     mov        ecx, edi
0072c501  e87a3be2ff               call       0x550080
0072c506  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072c509  8d45ec                   lea        eax, [ebp - 0x14]
0072c50c  50                       push       eax
0072c50d  8d8d4cffffff             lea        ecx, [ebp - 0xb4]
0072c513  e808accdff               call       0x407120
0072c518  8d4dec                   lea        ecx, [ebp - 0x14]
0072c51b  51                       push       ecx
0072c51c  8d8d4cffffff             lea        ecx, [ebp - 0xb4]
0072c522  c745ec01000000           mov        dword ptr [ebp - 0x14], 1
0072c529  e8f2abcdff               call       0x407120
0072c52e  8d55ec                   lea        edx, [ebp - 0x14]
0072c531  52                       push       edx
0072c532  8d8d4cffffff             lea        ecx, [ebp - 0xb4]
0072c538  c745ec04000000           mov        dword ptr [ebp - 0x14], 4
0072c53f  e8dcabcdff               call       0x407120
0072c544  8d45ec                   lea        eax, [ebp - 0x14]
0072c547  50                       push       eax
0072c548  8d8d4cffffff             lea        ecx, [ebp - 0xb4]
0072c54e  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072c551  e8caabcdff               call       0x407120
0072c556  8b16                     mov        edx, dword ptr [esi]
0072c558  53                       push       ebx
0072c559  53                       push       ebx
0072c55a  6a01                     push       1
0072c55c  8d854cffffff             lea        eax, [ebp - 0xb4]
0072c562  50                       push       eax
0072c563  6a0a                     push       0xa
0072c565  8bce                     mov        ecx, esi
0072c567  ff928c020000             call       dword ptr [edx + 0x28c]