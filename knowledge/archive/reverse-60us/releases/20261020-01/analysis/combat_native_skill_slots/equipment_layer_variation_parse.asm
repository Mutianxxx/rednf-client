00866600  8d45ac                   lea        eax, [ebp - 0x54]
00866603  68fcebe100               push       0xe1ebfc
00866608  50                       push       eax
00866609  e8c2e1b9ff               call       0x4047d0
0086660e  83c408                   add        esp, 8
00866611  84c0                     test       al, al
00866613  7443                     je         0x866658
00866615  8a45f3                   mov        al, byte ptr [ebp - 0xd]
00866618  84c0                     test       al, al
0086661a  53                       push       ebx
0086661b  741c                     je         0x866639
0086661d  e8ae91fcff               call       0x82f7d0
00866622  8d4d88                   lea        ecx, [ebp - 0x78]
00866625  51                       push       ecx
00866626  898560ffffff             mov        dword ptr [ebp - 0xa0], eax
0086662c  e8dfa0fcff               call       0x830710
00866631  83c408                   add        esp, 8
00866634  e97f1b0000               jmp        0x8681b8
00866639  e89291fcff               call       0x82f7d0
0086663e  8d956cffffff             lea        edx, [ebp - 0x94]
00866644  52                       push       edx
00866645  89855cffffff             mov        dword ptr [ebp - 0xa4], eax
0086664b  e8c0a0fcff               call       0x830710
00866650  83c408                   add        esp, 8
00866653  e9601b0000               jmp        0x8681b8
00866658  8d45ac                   lea        eax, [ebp - 0x54]
0086665b  68ecebe100               push       0xe1ebec
00866660  50                       push       eax
00866661  e86ae1b9ff               call       0x4047d0
00866666  83c408                   add        esp, 8
00866669  84c0                     test       al, al
0086666b  0f84c4000000             je         0x866735
00866671  8a45f3                   mov        al, byte ptr [ebp - 0xd]
00866674  84c0                     test       al, al
00866676  7460                     je         0x8666d8
00866678  399d58feffff             cmp        dword ptr [ebp - 0x1a8], ebx
0086667e  741c                     je         0x86669c
00866680  8b55a4                   mov        edx, dword ptr [ebp - 0x5c]
00866683  8d8d58feffff             lea        ecx, [ebp - 0x1a8]
00866689  51                       push       ecx
0086668a  52                       push       edx
0086668b  8bcf                     mov        ecx, edi
0086668d  e8deab0000               call       0x871270
00866692  8bc8                     mov        ecx, eax
00866694  83c118                   add        ecx, 0x18
00866697  e864910000               call       0x86f800
0086669c  8d8d58feffff             lea        ecx, [ebp - 0x1a8]
008666a2  e829550000               call       0x86bbd0
008666a7  8bb560ffffff             mov        esi, dword ptr [ebp - 0xa0]
008666ad  3bf3                     cmp        esi, ebx
008666af  53                       push       ebx
008666b0  7413                     je         0x8666c5
008666b2  e81991fcff               call       0x82f7d0
008666b7  83c404                   add        esp, 4
008666ba  89b558feffff             mov        dword ptr [ebp - 0x1a8], esi
008666c0  e9f31a0000               jmp        0x8681b8
008666c5  e80691fcff               call       0x82f7d0
008666ca  83c404                   add        esp, 4
008666cd  898558feffff             mov        dword ptr [ebp - 0x1a8], eax
008666d3  e9e01a0000               jmp        0x8681b8
008666d8  399dd8feffff             cmp        dword ptr [ebp - 0x128], ebx
008666de  7419                     je         0x8666f9
008666e0  8b4da4                   mov        ecx, dword ptr [ebp - 0x5c]
008666e3  8d85d8feffff             lea        eax, [ebp - 0x128]
008666e9  50                       push       eax
008666ea  51                       push       ecx
008666eb  8bcf                     mov        ecx, edi
008666ed  e87eab0000               call       0x871270
008666f2  8bc8                     mov        ecx, eax
008666f4  e807910000               call       0x86f800
008666f9  8d8dd8feffff             lea        ecx, [ebp - 0x128]
008666ff  e8cc540000               call       0x86bbd0
00866704  8bb55cffffff             mov        esi, dword ptr [ebp - 0xa4]
0086670a  3bf3                     cmp        esi, ebx
0086670c  53                       push       ebx
0086670d  7413                     je         0x866722
0086670f  e8bc90fcff               call       0x82f7d0
00866714  83c404                   add        esp, 4
00866717  89b5d8feffff             mov        dword ptr [ebp - 0x128], esi
0086671d  e9961a0000               jmp        0x8681b8
00866722  e8a990fcff               call       0x82f7d0
00866727  83c404                   add        esp, 4
0086672a  8985d8feffff             mov        dword ptr [ebp - 0x128], eax
00866730  e9831a0000               jmp        0x8681b8
