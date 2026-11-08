00435430  55                       push       ebp
00435431  8bec                     mov        ebp, esp
00435433  83ec14                   sub        esp, 0x14
00435436  53                       push       ebx
00435437  56                       push       esi
00435438  8bf1                     mov        esi, ecx
0043543a  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
00435440  8b5144                   mov        edx, dword ptr [ecx + 0x44]
00435443  8b4604                   mov        eax, dword ptr [esi + 4]
00435446  8d0482                   lea        eax, [edx + eax*4]
00435449  8bd0                     mov        edx, eax
0043544b  c745f000000000           mov        dword ptr [ebp - 0x10], 0
00435452  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
00435455  33d1                     xor        edx, ecx
00435457  57                       push       edi
00435458  3315dc012101             xor        edx, dword ptr [0x12101dc]
0043545e  8910                     mov        dword ptr [eax], edx
00435460  8b15d8012101             mov        edx, dword ptr [0x12101d8]
00435466  8b5248                   mov        edx, dword ptr [edx + 0x48]
00435469  8b4604                   mov        eax, dword ptr [esi + 4]
0043546c  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
00435472  8d0482                   lea        eax, [edx + eax*4]
00435475  8bd0                     mov        edx, eax
00435477  33d1                     xor        edx, ecx
00435479  33d7                     xor        edx, edi
0043547b  8910                     mov        dword ptr [eax], edx
0043547d  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
00435483  8b5144                   mov        edx, dword ptr [ecx + 0x44]
00435486  8b460c                   mov        eax, dword ptr [esi + 0xc]
00435489  8d0482                   lea        eax, [edx + eax*4]
0043548c  8b15dc012101             mov        edx, dword ptr [0x12101dc]
00435492  8bc8                     mov        ecx, eax
00435494  33ca                     xor        ecx, edx
00435496  8908                     mov        dword ptr [eax], ecx
00435498  a1d8012101               mov        eax, dword ptr [0x12101d8]
0043549d  8b4848                   mov        ecx, dword ptr [eax + 0x48]
004354a0  8b560c                   mov        edx, dword ptr [esi + 0xc]
004354a3  8d0491                   lea        eax, [ecx + edx*4]
004354a6  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
004354ac  8bd0                     mov        edx, eax
004354ae  33d1                     xor        edx, ecx
004354b0  8910                     mov        dword ptr [eax], edx
004354b2  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004354b8  8b5144                   mov        edx, dword ptr [ecx + 0x44]
004354bb  8b4614                   mov        eax, dword ptr [esi + 0x14]
004354be  8b1ddc012101             mov        ebx, dword ptr [0x12101dc]
004354c4  8d0482                   lea        eax, [edx + eax*4]
004354c7  8bc8                     mov        ecx, eax
004354c9  33cb                     xor        ecx, ebx
004354cb  8908                     mov        dword ptr [eax], ecx
004354cd  a1d8012101               mov        eax, dword ptr [0x12101d8]
004354d2  8b4848                   mov        ecx, dword ptr [eax + 0x48]
004354d5  8b5614                   mov        edx, dword ptr [esi + 0x14]
004354d8  8b3ddc012101             mov        edi, dword ptr [0x12101dc]
004354de  8d0491                   lea        eax, [ecx + edx*4]
004354e1  8bd0                     mov        edx, eax
004354e3  33d7                     xor        edx, edi
004354e5  8910                     mov        dword ptr [eax], edx
004354e7  c7461800000000           mov        dword ptr [esi + 0x18], 0
004354ee  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004354f4  8b5144                   mov        edx, dword ptr [ecx + 0x44]
004354f7  8b4620                   mov        eax, dword ptr [esi + 0x20]
004354fa  8d0482                   lea        eax, [edx + eax*4]
004354fd  8b15dc012101             mov        edx, dword ptr [0x12101dc]
00435503  8bc8                     mov        ecx, eax
00435505  33ca                     xor        ecx, edx
00435507  8908                     mov        dword ptr [eax], ecx
00435509  a1d8012101               mov        eax, dword ptr [0x12101d8]
0043550e  8b4848                   mov        ecx, dword ptr [eax + 0x48]
00435511  8b5620                   mov        edx, dword ptr [esi + 0x20]
00435514  8d0491                   lea        eax, [ecx + edx*4]
00435517  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
0043551d  8bd0                     mov        edx, eax
0043551f  33d1                     xor        edx, ecx
00435521  8910                     mov        dword ptr [eax], edx
00435523  33c0                     xor        eax, eax
00435525  8d                       .byte      0x8d
00435526  4e                       dec        esi
