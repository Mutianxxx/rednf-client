00553265  8bcf                     mov        ecx, edi
00553267  e89470f1ff               call       0x46a300
0055326c  8b85fcfeffff             mov        eax, dword ptr [ebp - 0x104]
00553272  33f6                     xor        esi, esi
00553274  3bc6                     cmp        eax, esi
00553276  0f84c3010000             je         0x55343f
0055327c  8b9500ffffff             mov        edx, dword ptr [ebp - 0x100]
00553282  2bd0                     sub        edx, eax
00553284  c1fa04                   sar        edx, 4
00553287  3bd6                     cmp        edx, esi
00553289  0f84b0010000             je         0x55343f
0055328f  83ec10                   sub        esp, 0x10
00553292  8bc4                     mov        eax, esp
00553294  89650c                   mov        dword ptr [ebp + 0xc], esp
00553297  8d8b3c020000             lea        ecx, [ebx + 0x23c]
0055329d  52                       push       edx
0055329e  897004                   mov        dword ptr [eax + 4], esi
005532a1  897008                   mov        dword ptr [eax + 8], esi
005532a4  89700c                   mov        dword ptr [eax + 0xc], esi
005532a7  e8c4380000               call       0x556b70
005532ac  8b95fcfeffff             mov        edx, dword ptr [ebp - 0x104]
005532b2  33c0                     xor        eax, eax
005532b4  89450c                   mov        dword ptr [ebp + 0xc], eax
005532b7  897508                   mov        dword ptr [ebp + 8], esi
005532ba  8d9b00000000             lea        ebx, [ebx]
005532c0  85d2                     test       edx, edx
005532c2  0f8477010000             je         0x55343f
005532c8  8b8d00ffffff             mov        ecx, dword ptr [ebp - 0x100]
005532ce  2bca                     sub        ecx, edx
005532d0  c1f904                   sar        ecx, 4
005532d3  3bc8                     cmp        ecx, eax
005532d5  0f8664010000             jbe        0x55343f
005532db  8b4508                   mov        eax, dword ptr [ebp + 8]
005532de  8b740204                 mov        esi, dword ptr [edx + eax + 4]
005532e2  85f6                     test       esi, esi
005532e4  0f842c010000             je         0x553416
005532ea  8b440208                 mov        eax, dword ptr [edx + eax + 8]
005532ee  2bc6                     sub        eax, esi
005532f0  c1f803                   sar        eax, 3
005532f3  85c0                     test       eax, eax
005532f5  0f841b010000             je         0x553416
005532fb  8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
005532fe  3bcb                     cmp        ecx, ebx
00553300  0f8627010000             jbe        0x55342d
00553306  8b7d08                   mov        edi, dword ptr [ebp + 8]
00553309  8b443a04                 mov        eax, dword ptr [edx + edi + 4]
0055330d  85c0                     test       eax, eax
0055330f  7504                     jne        0x553315
00553311  33f6                     xor        esi, esi
00553313  eb09                     jmp        0x55331e
00553315  8b743a08                 mov        esi, dword ptr [edx + edi + 8]
00553319  2bf0                     sub        esi, eax
0055331b  c1fe03                   sar        esi, 3
0055331e  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
00553321  8b9140020000             mov        edx, dword ptr [ecx + 0x240]
00553327  81c13c020000             add        ecx, 0x23c
0055332d  85d2                     test       edx, edx
0055332f  0f8405010000             je         0x55343a
00553335  8b4108                   mov        eax, dword ptr [ecx + 8]
00553338  2bc2                     sub        eax, edx
0055333a  c1f804                   sar        eax, 4
0055333d  3bc3                     cmp        eax, ebx
0055333f  0f86f5000000             jbe        0x55343a
00553345  83ec08                   sub        esp, 8
00553348  8bcc                     mov        ecx, esp
0055334a  03fa                     add        edi, edx
0055334c  896510                   mov        dword ptr [ebp + 0x10], esp
0055334f  e88c11ebff               call       0x4044e0
00553354  56                       push       esi
00553355  8bcf                     mov        ecx, edi
00553357  e8b40c0000               call       0x554010
0055335c  33ff                     xor        edi, edi
0055335e  8bff                     mov        edi, edi
00553360  8b95fcfeffff             mov        edx, dword ptr [ebp - 0x104]
00553366  85d2                     test       edx, edx
00553368  0f84bf000000             je         0x55342d
0055336e  8bb500ffffff             mov        esi, dword ptr [ebp - 0x100]
00553374  2bf2                     sub        esi, edx
00553376  c1fe04                   sar        esi, 4
00553379  3bf3                     cmp        esi, ebx
0055337b  0f86ac000000             jbe        0x55342d
00553381  8b4d08                   mov        ecx, dword ptr [ebp + 8]
00553384  8b5c1104                 mov        ebx, dword ptr [ecx + edx + 4]
00553388  03ca                     add        ecx, edx
0055338a  85db                     test       ebx, ebx
0055338c  0f8484000000             je         0x553416
00553392  8b4108                   mov        eax, dword ptr [ecx + 8]
00553395  2bc3                     sub        eax, ebx
00553397  c1f803                   sar        eax, 3
0055339a  3bf8                     cmp        edi, eax
0055339c  7378                     jae        0x553416
0055339e  8b5d0c                   mov        ebx, dword ptr [ebp + 0xc]
005533a1  3bf3                     cmp        esi, ebx
005533a3  0f8684000000             jbe        0x55342d
005533a9  8b5104                   mov        edx, dword ptr [ecx + 4]
005533ac  85d2                     test       edx, edx
005533ae  0f84b3feffff             je         0x553267
005533b4  8b4108                   mov        eax, dword ptr [ecx + 8]
005533b7  2bc2                     sub        eax, edx
005533b9  c1f803                   sar        eax, 3
005533bc  3bc7                     cmp        eax, edi
005533be  0f86a3feffff             jbe        0x553267
005533c4  8d34fa                   lea        esi, [edx + edi*8]
005533c7  8b55f0                   mov        edx, dword ptr [ebp - 0x10]
005533ca  8b8240020000             mov        eax, dword ptr [edx + 0x240]
005533d0  81c23c020000             add        edx, 0x23c
005533d6  85c0                     test       eax, eax
005533d8  745e                     je         0x553438
005533da  8b4a08                   mov        ecx, dword ptr [edx + 8]
005533dd  2bc8                     sub        ecx, eax
005533df  c1f904                   sar        ecx, 4
005533e2  3bcb                     cmp        ecx, ebx
005533e4  7652                     jbe        0x553438
005533e6  8b5508                   mov        edx, dword ptr [ebp + 8]
005533e9  8d0c02                   lea        ecx, [edx + eax]
005533ec  8b5104                   mov        edx, dword ptr [ecx + 4]
005533ef  85d2                     test       edx, edx
005533f1  0f8470feffff             je         0x553267
005533f7  8b4108                   mov        eax, dword ptr [ecx + 8]
005533fa  2bc2                     sub        eax, edx
005533fc  c1f803                   sar        eax, 3
005533ff  3bc7                     cmp        eax, edi
00553401  0f8660feffff             jbe        0x553267
00553407  56                       push       esi
00553408  8d0cfa                   lea        ecx, [edx + edi*8]
0055340b  e8a011ebff               call       0x4045b0
00553410  47                       inc        edi
00553411  e94affffff               jmp        0x553360
00553416  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
00553419  8b4508                   mov        eax, dword ptr [ebp + 8]
0055341c  41                       inc        ecx
0055341d  83c010                   add        eax, 0x10
00553420  894508                   mov        dword ptr [ebp + 8], eax
00553423  894d0c                   mov        dword ptr [ebp + 0xc], ecx
00553426  8bc1                     mov        eax, ecx
00553428  e993feffff               jmp        0x5532c0
0055342d  8d8df8feffff             lea        ecx, [ebp - 0x108]
00553433  e8680b0000               call       0x553fa0
00553438  8bca                     mov        ecx, edx
0055343a  e8610b0000               call       0x553fa0
