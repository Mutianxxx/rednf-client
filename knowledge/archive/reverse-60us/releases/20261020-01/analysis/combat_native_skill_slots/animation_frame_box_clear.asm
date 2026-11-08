00a27690  55                       push       ebp
00a27691  8bec                     mov        ebp, esp
00a27693  83ec0c                   sub        esp, 0xc
00a27696  53                       push       ebx
00a27697  56                       push       esi
00a27698  8bd9                     mov        ebx, ecx
00a2769a  33c0                     xor        eax, eax
00a2769c  57                       push       edi
00a2769d  895df4                   mov        dword ptr [ebp - 0xc], ebx
00a276a0  8945fc                   mov        dword ptr [ebp - 4], eax
00a276a3  8945f8                   mov        dword ptr [ebp - 8], eax
00a276a6  8b8398000000             mov        eax, dword ptr [ebx + 0x98]
00a276ac  85c0                     test       eax, eax
00a276ae  747a                     je         0xa2772a
00a276b0  8b8b9c000000             mov        ecx, dword ptr [ebx + 0x9c]
00a276b6  2bc8                     sub        ecx, eax
00a276b8  b843082184               mov        eax, 0x84210843
00a276bd  f7e9                     imul       ecx
00a276bf  03d1                     add        edx, ecx
00a276c1  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00a276c4  c1fa06                   sar        edx, 6
00a276c7  8bc2                     mov        eax, edx
00a276c9  c1e81f                   shr        eax, 0x1f
00a276cc  03c2                     add        eax, edx
00a276ce  3bc8                     cmp        ecx, eax
00a276d0  7358                     jae        0xa2772a
00a276d2  8bb398000000             mov        esi, dword ptr [ebx + 0x98]
00a276d8  8b55f8                   mov        edx, dword ptr [ebp - 8]
00a276db  8b7c163c                 mov        edi, dword ptr [esi + edx + 0x3c]
00a276df  03f2                     add        esi, edx
00a276e1  33c0                     xor        eax, eax
00a276e3  3bf8                     cmp        edi, eax
00a276e5  7428                     je         0xa2770f
00a276e7  8b5e40                   mov        ebx, dword ptr [esi + 0x40]
00a276ea  3bfb                     cmp        edi, ebx
00a276ec  7410                     je         0xa276fe
00a276ee  8bff                     mov        edi, edi
00a276f0  8bcf                     mov        ecx, edi
00a276f2  e809cc9dff               call       0x404300
00a276f7  83c730                   add        edi, 0x30
00a276fa  3bfb                     cmp        edi, ebx
00a276fc  75f2                     jne        0xa276f0
00a276fe  8b463c                   mov        eax, dword ptr [esi + 0x3c]
00a27701  50                       push       eax
00a27702  e8d6881d00               call       0xbfffdd
00a27707  8b5df4                   mov        ebx, dword ptr [ebp - 0xc]
00a2770a  83c404                   add        esp, 4
00a2770d  33c0                     xor        eax, eax
00a2770f  8b4dfc                   mov        ecx, dword ptr [ebp - 4]
00a27712  89463c                   mov        dword ptr [esi + 0x3c], eax
00a27715  894640                   mov        dword ptr [esi + 0x40], eax
00a27718  894644                   mov        dword ptr [esi + 0x44], eax
00a2771b  8b45f8                   mov        eax, dword ptr [ebp - 8]
00a2771e  41                       inc        ecx
00a2771f  894dfc                   mov        dword ptr [ebp - 4], ecx
00a27722  83c07c                   add        eax, 0x7c
00a27725  e979ffffff               jmp        0xa276a3
00a2772a  5f                       pop        edi
00a2772b  5e                       pop        esi
00a2772c  5b                       pop        ebx
00a2772d  8be5                     mov        esp, ebp
00a2772f  5d                       pop        ebp
00a27730  c3                       ret        
00a27731  cc                       int3       
00a27732  cc                       int3       
00a27733  cc                       int3       
00a27734  cc                       int3       
00a27735  cc                       int3       
00a27736  cc                       int3       
00a27737  cc                       int3       
00a27738  cc                       int3       
00a27739  cc                       int3       
