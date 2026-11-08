0072af0c  8bcf                     mov        ecx, edi
0072af0e  e84d71cdff               call       0x402060
0072af13  85c0                     test       eax, eax
0072af15  741c                     je         0x72af33
0072af17  8bcf                     mov        ecx, edi
0072af19  e84271cdff               call       0x402060
0072af1e  83f80b                   cmp        eax, 0xb
0072af21  7410                     je         0x72af33
0072af23  8bcf                     mov        ecx, edi
0072af25  e83671cdff               call       0x402060
0072af2a  83f808                   cmp        eax, 8
0072af2d  0f8595000000             jne        0x72afc8
0072af33  8b16                     mov        edx, dword ptr [esi]
0072af35  53                       push       ebx
0072af36  6a08                     push       8
0072af38  8bce                     mov        ecx, esi
0072af3a  ff923c070000             call       dword ptr [edx + 0x73c]
0072af40  8bc8                     mov        ecx, eax
0072af42  e8f9e1e2ff               call       0x559140
0072af47  83f8ff                   cmp        eax, -1
0072af4a  8945f0                   mov        dword ptr [ebp - 0x10], eax
0072af4d  7479                     je         0x72afc8
0072af4f  8b06                     mov        eax, dword ptr [esi]
0072af51  6a01                     push       1
0072af53  6a01                     push       1
0072af55  6a01                     push       1
0072af57  6a08                     push       8
0072af59  8bce                     mov        ecx, esi
0072af5b  ff9068070000             call       dword ptr [eax + 0x768]
0072af61  84c0                     test       al, al
0072af63  7463                     je         0x72afc8
0072af65  899da8fcffff             mov        dword ptr [ebp - 0x358], ebx
0072af6b  899dacfcffff             mov        dword ptr [ebp - 0x354], ebx
0072af71  899db0fcffff             mov        dword ptr [ebp - 0x350], ebx
0072af77  8d4dec                   lea        ecx, [ebp - 0x14]
0072af7a  51                       push       ecx
0072af7b  8d8da4fcffff             lea        ecx, [ebp - 0x35c]
0072af81  c745fc20000000           mov        dword ptr [ebp - 4], 0x20
0072af88  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072af8b  e890c1cdff               call       0x407120
0072af90  8d55f0                   lea        edx, [ebp - 0x10]
0072af93  52                       push       edx
0072af94  8d8da4fcffff             lea        ecx, [ebp - 0x35c]
0072af9a  e881c1cdff               call       0x407120
0072af9f  8b06                     mov        eax, dword ptr [esi]
0072afa1  53                       push       ebx
0072afa2  53                       push       ebx
0072afa3  6a01                     push       1
0072afa5  8d8da4fcffff             lea        ecx, [ebp - 0x35c]
0072afab  51                       push       ecx
0072afac  6a16                     push       0x16
0072afae  8bce                     mov        ecx, esi
0072afb0  ff                       .byte      0xff
0072afb1  90                       nop        
0072afb2  8c02                     mov        word ptr [edx], es
