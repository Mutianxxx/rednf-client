0072bfa1  6a01                     push       1
0072bfa3  6a01                     push       1
0072bfa5  6a01                     push       1
0072bfa7  6a1e                     push       0x1e
0072bfa9  8bce                     mov        ecx, esi
0072bfab  ff9068070000             call       dword ptr [eax + 0x768]
0072bfb1  84c0                     test       al, al
0072bfb3  0f8418010000             je         0x72c0d1
0072bfb9  899d40ffffff             mov        dword ptr [ebp - 0xc0], ebx
0072bfbf  899d44ffffff             mov        dword ptr [ebp - 0xbc], ebx
0072bfc5  899d48ffffff             mov        dword ptr [ebp - 0xb8], ebx
0072bfcb  8d4dec                   lea        ecx, [ebp - 0x14]
0072bfce  51                       push       ecx
0072bfcf  8d8d3cffffff             lea        ecx, [ebp - 0xc4]
0072bfd5  c745fc2a000000           mov        dword ptr [ebp - 4], 0x2a
0072bfdc  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072bfdf  e83cb1cdff               call       0x407120
0072bfe4  8d55ec                   lea        edx, [ebp - 0x14]
0072bfe7  52                       push       edx
0072bfe8  8d8d3cffffff             lea        ecx, [ebp - 0xc4]
0072bfee  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072bff1  e82ab1cdff               call       0x407120
0072bff6  8d45ec                   lea        eax, [ebp - 0x14]
0072bff9  50                       push       eax
0072bffa  8d8d3cffffff             lea        ecx, [ebp - 0xc4]
0072c000  c745ec1e000000           mov        dword ptr [ebp - 0x14], 0x1e
0072c007  e814b1cdff               call       0x407120
0072c00c  8b16                     mov        edx, dword ptr [esi]
0072c00e  6a1e                     push       0x1e
0072c010  8bce                     mov        ecx, esi
0072c012  ff924c060000             call       dword ptr [edx + 0x64c]
0072c018  50                       push       eax
0072c019  8b06                     mov        eax, dword ptr [esi]
0072c01b  56                       push       esi
0072c01c  6a1e                     push       0x1e
0072c01e  8bce                     mov        ecx, esi
0072c020  ff907c060000             call       dword ptr [eax + 0x67c]
0072c026  8bc8                     mov        ecx, eax
0072c028  e803c4d3ff               call       0x468430
0072c02d  8d4dec                   lea        ecx, [ebp - 0x14]
0072c030  51                       push       ecx
0072c031  8d8d3cffffff             lea        ecx, [ebp - 0xc4]
0072c037  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072c03a  e8e1b0cdff               call       0x407120
0072c03f  8b16                     mov        edx, dword ptr [esi]
0072c041  56                       push       esi
0072c042  53                       push       ebx
0072c043  6a1e                     push       0x1e
0072c045  8bce                     mov        ecx, esi
0072c047  ff927c060000             call       dword ptr [edx + 0x67c]
0072c04d  8bc8                     mov        ecx, eax
0072c04f  e80c3fe2ff               call       0x54ff60
0072c054  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072c057  8d45ec                   lea        eax, [ebp - 0x14]
0072c05a  50                       push       eax
0072c05b  8d8d3cffffff             lea        ecx, [ebp - 0xc4]
0072c061  e8bab0cdff               call       0x407120
0072c066  8d4dec                   lea        ecx, [ebp - 0x14]
0072c069  51                       push       ecx
0072c06a  8d8d3cffffff             lea        ecx, [ebp - 0xc4]
0072c070  c745ec01000000           mov        dword ptr [ebp - 0x14], 1
0072c077  e8a4b0cdff               call       0x407120
0072c07c  8d55ec                   lea        edx, [ebp - 0x14]
0072c07f  52                       push       edx
0072c080  8d8d3cffffff             lea        ecx, [ebp - 0xc4]
0072c086  c745ec04000000           mov        dword ptr [ebp - 0x14], 4
0072c08d  e88eb0cdff               call       0x407120
0072c092  8d45ec                   lea        eax, [ebp - 0x14]
0072c095  50                       push       eax
0072c096  8d8d3cffffff             lea        ecx, [ebp - 0xc4]
0072c09c  c745ec04000000           mov        dword ptr [ebp - 0x14], 4
0072c0a3  e878b0cdff               call       0x407120
0072c0a8  8b16                     mov        edx, dword ptr [esi]
0072c0aa  53                       push       ebx
0072c0ab  53                       push       ebx
0072c0ac  6a01                     push       1
0072c0ae  8d853cffffff             lea        eax, [ebp - 0xc4]
0072c0b4  50                       push       eax
0072c0b5  6a0a                     push       0xa
0072c0b7  8bce                     mov        ecx, esi
0072c0b9  ff928c020000             call       dword ptr [edx + 0x28c]