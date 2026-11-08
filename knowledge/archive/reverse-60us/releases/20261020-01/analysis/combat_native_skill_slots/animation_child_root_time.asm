004caa00  8bc1                     mov        eax, ecx
004caa02  8b8888010000             mov        ecx, dword ptr [eax + 0x188]
004caa08  85c9                     test       ecx, ecx
004caa0a  7405                     je         0x4caa11
004caa0c  e9efffffff               jmp        0x4caa00
004caa11  8b808c000000             mov        eax, dword ptr [eax + 0x8c]
004caa17  c3                       ret        
