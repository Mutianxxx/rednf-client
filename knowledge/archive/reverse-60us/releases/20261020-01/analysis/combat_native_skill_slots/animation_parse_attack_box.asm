00a294aa  53                       push       ebx
00a294ab  e82063e0ff               call       0x82f7d0
00a294b0  89450c                   mov        dword ptr [ebp + 0xc], eax
00a294b3  db450c                   fild       dword ptr [ebp + 0xc]
00a294b6  83c404                   add        esp, 4
00a294b9  8d550c                   lea        edx, [ebp + 0xc]
00a294bc  52                       push       edx
00a294bd  d95d0c                   fstp       dword ptr [ebp + 0xc]
00a294c0  8d8d44ffffff             lea        ecx, [ebp - 0xbc]
00a294c6  e895b09dff               call       0x404560
00a294cb  53                       push       ebx
00a294cc  e8ff62e0ff               call       0x82f7d0
00a294d1  89450c                   mov        dword ptr [ebp + 0xc], eax
00a294d4  db450c                   fild       dword ptr [ebp + 0xc]
00a294d7  83c404                   add        esp, 4
00a294da  8d450c                   lea        eax, [ebp + 0xc]
00a294dd  50                       push       eax
00a294de  d95d0c                   fstp       dword ptr [ebp + 0xc]
00a294e1  8d8d4cffffff             lea        ecx, [ebp - 0xb4]
00a294e7  e874b09dff               call       0x404560
00a294ec  53                       push       ebx
00a294ed  e8de62e0ff               call       0x82f7d0
00a294f2  89450c                   mov        dword ptr [ebp + 0xc], eax
00a294f5  db450c                   fild       dword ptr [ebp + 0xc]
00a294f8  83c404                   add        esp, 4
00a294fb  8d4d0c                   lea        ecx, [ebp + 0xc]
00a294fe  51                       push       ecx
00a294ff  d95d0c                   fstp       dword ptr [ebp + 0xc]
00a29502  8d8d54ffffff             lea        ecx, [ebp - 0xac]
00a29508  e853b09dff               call       0x404560
00a2950d  53                       push       ebx
00a2950e  e8bd62e0ff               call       0x82f7d0
00a29513  89450c                   mov        dword ptr [ebp + 0xc], eax
00a29516  db450c                   fild       dword ptr [ebp + 0xc]
00a29519  83c404                   add        esp, 4
00a2951c  8d550c                   lea        edx, [ebp + 0xc]
00a2951f  52                       push       edx
00a29520  d95d0c                   fstp       dword ptr [ebp + 0xc]
00a29523  8d8d5cffffff             lea        ecx, [ebp - 0xa4]
00a29529  e832b09dff               call       0x404560
00a2952e  53                       push       ebx
00a2952f  e89c62e0ff               call       0x82f7d0
00a29534  89450c                   mov        dword ptr [ebp + 0xc], eax
00a29537  db450c                   fild       dword ptr [ebp + 0xc]
00a2953a  83c404                   add        esp, 4
00a2953d  8d450c                   lea        eax, [ebp + 0xc]
00a29540  50                       push       eax
00a29541  d95d0c                   fstp       dword ptr [ebp + 0xc]
00a29544  8d8d64ffffff             lea        ecx, [ebp - 0x9c]
00a2954a  e811b09dff               call       0x404560
00a2954f  53                       push       ebx
00a29550  e87b62e0ff               call       0x82f7d0
00a29555  89450c                   mov        dword ptr [ebp + 0xc], eax
00a29558  db450c                   fild       dword ptr [ebp + 0xc]
00a2955b  83c404                   add        esp, 4
00a2955e  8d4d0c                   lea        ecx, [ebp + 0xc]
00a29561  51                       push       ecx
00a29562  d95d0c                   fstp       dword ptr [ebp + 0xc]
00a29565  8d8d6cffffff             lea        ecx, [ebp - 0x94]
00a2956b  e8f0af9dff               call       0x404560
00a29570  3bf3                     cmp        esi, ebx
00a29572  0f8412f9ffff             je         0xa28e8a
00a29578  8d9544ffffff             lea        edx, [ebp - 0xbc]
00a2957e  52                       push       edx
00a2957f  8d4e38                   lea        ecx, [esi + 0x38]
00a29582  e83937c3ff               call       0x65ccc0
00a29587  e9fef8ffff               jmp        0xa28e8a
