0072b64e  6a01                     push       1
0072b650  6a01                     push       1
0072b652  6a01                     push       1
0072b654  6a18                     push       0x18
0072b656  8bce                     mov        ecx, esi
0072b658  ff9268070000             call       dword ptr [edx + 0x768]
0072b65e  84c0                     test       al, al
0072b660  0f8416010000             je         0x72b77c
0072b666  8b06                     mov        eax, dword ptr [esi]
0072b668  6a18                     push       0x18
0072b66a  8bce                     mov        ecx, esi
0072b66c  ff907c060000             call       dword ptr [eax + 0x67c]
0072b672  8bf8                     mov        edi, eax
0072b674  899d60ffffff             mov        dword ptr [ebp - 0xa0], ebx
0072b67a  899d64ffffff             mov        dword ptr [ebp - 0x9c], ebx
0072b680  899d68ffffff             mov        dword ptr [ebp - 0x98], ebx
0072b686  8d4dec                   lea        ecx, [ebp - 0x14]
0072b689  51                       push       ecx
0072b68a  8d8d5cffffff             lea        ecx, [ebp - 0xa4]
0072b690  c745fc25000000           mov        dword ptr [ebp - 4], 0x25
0072b697  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072b69a  e881bacdff               call       0x407120
0072b69f  8d55ec                   lea        edx, [ebp - 0x14]
0072b6a2  52                       push       edx
0072b6a3  8d8d5cffffff             lea        ecx, [ebp - 0xa4]
0072b6a9  895dec                   mov        dword ptr [ebp - 0x14], ebx
0072b6ac  e86fbacdff               call       0x407120
0072b6b1  8d45ec                   lea        eax, [ebp - 0x14]
0072b6b4  50                       push       eax
0072b6b5  8d8d5cffffff             lea        ecx, [ebp - 0xa4]
0072b6bb  c745ec18000000           mov        dword ptr [ebp - 0x14], 0x18
0072b6c2  e859bacdff               call       0x407120
0072b6c7  8b16                     mov        edx, dword ptr [esi]
0072b6c9  53                       push       ebx
0072b6ca  53                       push       ebx
0072b6cb  6a0c                     push       0xc
0072b6cd  6aff                     push       -1
0072b6cf  6aff                     push       -1
0072b6d1  56                       push       esi
0072b6d2  6a18                     push       0x18
0072b6d4  8bce                     mov        ecx, esi
0072b6d6  ff924c060000             call       dword ptr [edx + 0x64c]
0072b6dc  50                       push       eax
0072b6dd  6a01                     push       1
0072b6df  8bcf                     mov        ecx, edi
0072b6e1  e89a49e2ff               call       0x550080
0072b6e6  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072b6e9  8d45ec                   lea        eax, [ebp - 0x14]
0072b6ec  50                       push       eax
0072b6ed  8d8d5cffffff             lea        ecx, [ebp - 0xa4]
0072b6f3  e828bacdff               call       0x407120
0072b6f8  56                       push       esi
0072b6f9  6a03                     push       3
0072b6fb  8bcf                     mov        ecx, edi
0072b6fd  e85e48e2ff               call       0x54ff60
0072b702  8d4dec                   lea        ecx, [ebp - 0x14]
0072b705  51                       push       ecx
0072b706  8d8d5cffffff             lea        ecx, [ebp - 0xa4]
0072b70c  8945ec                   mov        dword ptr [ebp - 0x14], eax
0072b70f  e80cbacdff               call       0x407120
0072b714  8d55ec                   lea        edx, [ebp - 0x14]
0072b717  52                       push       edx
0072b718  8d8d5cffffff             lea        ecx, [ebp - 0xa4]
0072b71e  c745ec01000000           mov        dword ptr [ebp - 0x14], 1
0072b725  e8f6b9cdff               call       0x407120
0072b72a  8d45ec                   lea        eax, [ebp - 0x14]
0072b72d  bf03000000               mov        edi, 3
0072b732  50                       push       eax
0072b733  8d8d5cffffff             lea        ecx, [ebp - 0xa4]
0072b739  897dec                   mov        dword ptr [ebp - 0x14], edi
0072b73c  e8dfb9cdff               call       0x407120
0072b741  8d4dec                   lea        ecx, [ebp - 0x14]
0072b744  51                       push       ecx
0072b745  8d8d5cffffff             lea        ecx, [ebp - 0xa4]
0072b74b  897dec                   mov        dword ptr [ebp - 0x14], edi
0072b74e  e8cdb9cdff               call       0x407120
0072b753  8b16                     mov        edx, dword ptr [esi]
0072b755  53                       push       ebx
0072b756  53                       push       ebx
0072b757  6a01                     push       1
0072b759  8d855cffffff             lea        eax, [ebp - 0xa4]
0072b75f  50                       push       eax
0072b760  6a0a                     push       0xa
0072b762  8bce                     mov        ecx, esi
0072b764  ff928c020000             call       dword ptr [edx + 0x28c]