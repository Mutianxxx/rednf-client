004dc8b0  8b865c150000             mov        eax, dword ptr [esi + 0x155c]
004dc8b6  8b1ddc012101             mov        ebx, dword ptr [0x12101dc]
004dc8bc  8b8e60150000             mov        ecx, dword ptr [esi + 0x1560]
004dc8c2  8dbe5c150000             lea        edi, [esi + 0x155c]
004dc8c8  33c3                     xor        eax, ebx
004dc8ca  2bc7                     sub        eax, edi
004dc8cc  3bc1                     cmp        eax, ecx
004dc8ce  740e                     je         0x4dc8de
004dc8d0  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004dc8d6  6a3f                     push       0x3f
004dc8d8  57                       push       edi
004dc8d9  e8d2a76300               call       0xb170b0
004dc8de  8b15d8012101             mov        edx, dword ptr [0x12101d8]
004dc8e4  8b4a44                   mov        ecx, dword ptr [edx + 0x44]
004dc8e7  8b4704                   mov        eax, dword ptr [edi + 4]
004dc8ea  c1e002                   shl        eax, 2
004dc8ed  8d1c08                   lea        ebx, [eax + ecx]
004dc8f0  331c08                   xor        ebx, dword ptr [eax + ecx]
004dc8f3  331ddc012101             xor        ebx, dword ptr [0x12101dc]
004dc8f9  8b4a48                   mov        ecx, dword ptr [edx + 0x48]
004dc8fc  8d1408                   lea        edx, [eax + ecx]
004dc8ff  331408                   xor        edx, dword ptr [eax + ecx]
004dc902  3315dc012101             xor        edx, dword ptr [0x12101dc]
004dc908  3bda                     cmp        ebx, edx
004dc90a  740e                     je         0x4dc91a
004dc90c  8b0dd8012101             mov        ecx, dword ptr [0x12101d8]
004dc912  6a40                     push       0x40
004dc914  57                       push       edi
004dc915  e896a76300               call       0xb170b0
004dc91a  83fb0e                   cmp        ebx, 0xe
004dc91d  bf08000000               mov        edi, 8
004dc922  0f87070b0000             ja         0x4dd42f
004dc928  0fb68334e34d00           movzx      eax, byte ptr [ebx + 0x4de334]
004dc92f  ff248514e34d00           jmp        dword ptr [eax*4 + 0x4de314]