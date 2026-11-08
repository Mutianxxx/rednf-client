004cf680  55                       push       ebp
004cf681  8bec                     mov        ebp, esp
004cf683  83ec18                   sub        esp, 0x18
004cf686  53                       push       ebx
004cf687  56                       push       esi
004cf688  8b7508                   mov        esi, dword ptr [ebp + 8]
004cf68b  8b8678010000             mov        eax, dword ptr [esi + 0x178]
004cf691  57                       push       edi
004cf692  8bf9                     mov        edi, ecx
004cf694  8a8e7c010000             mov        cl, byte ptr [esi + 0x17c]
004cf69a  884d0b                   mov        byte ptr [ebp + 0xb], cl
004cf69d  8d8e80010000             lea        ecx, [esi + 0x180]
004cf6a3  8945f0                   mov        dword ptr [ebp - 0x10], eax
004cf6a6  894dfc                   mov        dword ptr [ebp - 4], ecx
004cf6a9  e8b229f3ff               call       0x402060
004cf6ae  8d9e88010000             lea        ebx, [esi + 0x188]
004cf6b4  8bcb                     mov        ecx, ebx
004cf6b6  8945ec                   mov        dword ptr [ebp - 0x14], eax
004cf6b9  e8f23cf6ff               call       0x4333b0
004cf6be  d95de8                   fstp       dword ptr [ebp - 0x18]
004cf6c1  83be7801000005           cmp        dword ptr [esi + 0x178], 5
004cf6c8  7520                     jne        0x4cf6ea
004cf6ca  8b17                     mov        edx, dword ptr [edi]
004cf6cc  8bcf                     mov        ecx, edi
004cf6ce  ff9298060000             call       dword ptr [edx + 0x698]
004cf6d4  898678010000             mov        dword ptr [esi + 0x178], eax
004cf6da  8b07                     mov        eax, dword ptr [edi]
004cf6dc  8bcf                     mov        ecx, edi
004cf6de  ff909c060000             call       dword ptr [eax + 0x69c]
004cf6e4  88867c010000             mov        byte ptr [esi + 0x17c], al
004cf6ea  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004cf6ed  e86e29f3ff               call       0x402060
004cf6f2  83f8ff                   cmp        eax, -1
004cf6f5  7546                     jne        0x4cf73d
004cf6f7  8b17                     mov        edx, dword ptr [edi]
004cf6f9  8bcf                     mov        ecx, edi
004cf6fb  ff92a0060000             call       dword ptr [edx + 0x6a0]
004cf701  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004cf704  8b5104                   mov        edx, dword ptr [ecx + 4]
004cf707  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004cf70d  8b4944                   mov        ecx, dword ptr [ecx + 0x44]
004cf710  8d0c91                   lea        ecx, [ecx + edx*4]
004cf713  8bd1                     mov        edx, ecx
004cf715  3315dc012101             xor        edx, dword ptr [0x12101dc]
004cf71b  33d0                     xor        edx, eax
004cf71d  8911                     mov        dword ptr [ecx], edx
004cf71f  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
004cf722  8b5104                   mov        edx, dword ptr [ecx + 4]
004cf725  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004cf72b  8b4948                   mov        ecx, dword ptr [ecx + 0x48]
004cf72e  8d0c91                   lea        ecx, [ecx + edx*4]
004cf731  8bd1                     mov        edx, ecx
004cf733  3315dc012101             xor        edx, dword ptr [0x12101dc]
004cf739  33d0                     xor        edx, eax
004cf73b  8911                     mov        dword ptr [ecx], edx
004cf73d  8bcb                     mov        ecx, ebx
004cf73f  e86c3cf6ff               call       0x4333b0
004cf744  dc25f0b8ca00             fsub       qword ptr [0xcab8f0]
004cf74a  8bcb                     mov        ecx, ebx
004cf74c  d9e1                     fabs       
004cf74e  dd5df4                   fstp       qword ptr [ebp - 0xc]
004cf751  e85a3cf6ff               call       0x4333b0
004cf756  d9e1                     fabs       
004cf758  dc0de8b8ca00             fmul       qword ptr [0xcab8e8]
004cf75e  dc5df4                   fcomp      qword ptr [ebp - 0xc]
004cf761  dfe0                     fnstsw     ax
004cf763  f6c401                   test       ah, 1
004cf766  7548                     jne        0x4cf7b0
004cf768  8b07                     mov        eax, dword ptr [edi]
004cf76a  8bcf                     mov        ecx, edi
004cf76c  ff90a4060000             call       dword ptr [eax + 0x6a4]
004cf772  d95df8                   fstp       dword ptr [ebp - 8]
004cf775  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004cf77b  8b4244                   mov        eax, dword ptr [edx + 0x44]
004cf77e  8b4b04                   mov        ecx, dword ptr [ebx + 4]
004cf781  8d0488                   lea        eax, [eax + ecx*4]
004cf784  8b0ddc012101             mov        ecx, dword ptr [0x12101dc]
004cf78a  8bd0                     mov        edx, eax
004cf78c  33d1                     xor        edx, ecx
004cf78e  8b4df8                   mov        ecx, dword ptr [ebp - 8]
004cf791  33d1                     xor        edx, ecx
004cf793  8910                     mov        dword ptr [eax], edx
004cf795  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004cf79b  8b5248                   mov        edx, dword ptr [edx + 0x48]
004cf79e  8b4304                   mov        eax, dword ptr [ebx + 4]
004cf7a1  8d0482                   lea        eax, [edx + eax*4]
004cf7a4  8bd0                     mov        edx, eax
004cf7a6  3315dc012101             xor        edx, dword ptr [0x12101dc]
004cf7ac  33d1                     xor        edx, ecx
004cf7ae  8910                     mov        dword ptr [eax], edx
004cf7b0  56                       push       esi
004cf7b1  8bcf                     mov        ecx, edi
004cf7b3  e85802feff               call       0x4afa10
004cf7b8  8b45f0                   mov        eax, dword ptr [ebp - 0x10]
004cf7bb  8a4d0b                   mov        cl, byte ptr [ebp + 0xb]
004cf7be  88                       .byte      0x88
004cf7bf  8e                       .byte      0x8e
