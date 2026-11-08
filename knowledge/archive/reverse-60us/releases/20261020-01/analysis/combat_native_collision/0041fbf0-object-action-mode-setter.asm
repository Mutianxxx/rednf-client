0041fbf0 55                       push      ebp
0041fbf1 8bec                     mov       ebp, esp
0041fbf3 8a4508                   mov       al, byte ptr [ebp + 8]
0041fbf6 888194010000             mov       byte ptr [ecx + 0x194], al
0041fbfc 5d                       pop       ebp
0041fbfd c20400                   ret       4
0041fc00 55                       push      ebp
0041fc01 8bec                     mov       ebp, esp
0041fc03 8b8120020000             mov       eax, dword ptr [ecx + 0x220]
0041fc09 8a5508                   mov       dl, byte ptr [ebp + 8]
0041fc0c 885011                   mov       byte ptr [eax + 0x11], dl
0041fc0f 8b                       .byte     0x8b
