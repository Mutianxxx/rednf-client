; Source SHA256: a3177551b8f7373e042865b0e99022e24e6ffd47298299a50dc97fec5254745b
; VA 00b8b5c0..00b8b77c (end exclusive); file offset 0078b5c0
; This is an instruction excerpt, not a recovered original source file.
00b8b5c0  55                       push       ebp
00b8b5c1  8bec                     mov        ebp, esp
00b8b5c3  6aff                     push       -1
00b8b5c5  68a3a1c900               push       0xc9a1a3
00b8b5ca  64a100000000             mov        eax, dword ptr fs:[0]
00b8b5d0  50                       push       eax
00b8b5d1  64892500000000           mov        dword ptr fs:[0], esp
00b8b5d8  83ec54                   sub        esp, 0x54
00b8b5db  a13891ff00               mov        eax, dword ptr [0xff9138]
00b8b5e0  53                       push       ebx
00b8b5e1  33db                     xor        ebx, ebx
00b8b5e3  8945f0                   mov        dword ptr [ebp - 0x10], eax
00b8b5e6  56                       push       esi
00b8b5e7  b80f000000               mov        eax, 0xf
00b8b5ec  57                       push       edi
00b8b5ed  8bf1                     mov        esi, ecx
00b8b5ef  8945bc                   mov        dword ptr [ebp - 0x44], eax
00b8b5f2  895db8                   mov        dword ptr [ebp - 0x48], ebx
00b8b5f5  885da8                   mov        byte ptr [ebp - 0x58], bl
00b8b5f8  8945d8                   mov        dword ptr [ebp - 0x28], eax
00b8b5fb  895dd4                   mov        dword ptr [ebp - 0x2c], ebx
00b8b5fe  885dc4                   mov        byte ptr [ebp - 0x3c], bl
00b8b601  8b5508                   mov        edx, dword ptr [ebp + 8]
00b8b604  8bc2                     mov        eax, edx
00b8b606  895dfc                   mov        dword ptr [ebp - 4], ebx
00b8b609  8d7801                   lea        edi, [eax + 1]
00b8b60c  8d642400                 lea        esp, [esp]
00b8b610  8a08                     mov        cl, byte ptr [eax]
00b8b612  40                       inc        eax
00b8b613  3acb                     cmp        cl, bl
00b8b615  75f9                     jne        0xb8b610
00b8b617  2bc7                     sub        eax, edi
00b8b619  50                       push       eax
00b8b61a  52                       push       edx
00b8b61b  8d4da4                   lea        ecx, [ebp - 0x5c]
00b8b61e  e88d7c87ff               call       0x4032b0
00b8b623  8b7d0c                   mov        edi, dword ptr [ebp + 0xc]
00b8b626  8bc7                     mov        eax, edi
00b8b628  8d5001                   lea        edx, [eax + 1]
00b8b62b  eb03                     jmp        0xb8b630
00b8b62d  8d4900                   lea        ecx, [ecx]
00b8b630  8a08                     mov        cl, byte ptr [eax]
00b8b632  40                       inc        eax
00b8b633  3acb                     cmp        cl, bl
00b8b635  75f9                     jne        0xb8b630
00b8b637  2bc2                     sub        eax, edx
00b8b639  50                       push       eax
00b8b63a  57                       push       edi
00b8b63b  8d4dc0                   lea        ecx, [ebp - 0x40]
00b8b63e  e86d7c87ff               call       0x4032b0
00b8b643  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00b8b646  3bc3                     cmp        eax, ebx
00b8b648  7567                     jne        0xb8b6b1
00b8b64a  b9a8a02301               mov        ecx, 0x123a0a8
00b8b64f  e8bc050000               call       0xb8bc10
00b8b654  6800002000               push       0x200000
00b8b659  50                       push       eax
00b8b65a  8945e8                   mov        dword ptr [ebp - 0x18], eax
00b8b65d  8b4508                   mov        eax, dword ptr [ebp + 8]
00b8b660  57                       push       edi
00b8b661  50                       push       eax
00b8b662  8bce                     mov        ecx, esi
00b8b664  885dec                   mov        byte ptr [ebp - 0x14], bl
00b8b667  e88460caff               call       0x8316f0
00b8b66c  3bc3                     cmp        eax, ebx
00b8b66e  8945e0                   mov        dword ptr [ebp - 0x20], eax
00b8b671  754b                     jne        0xb8b6be
00b8b673  8b4de8                   mov        ecx, dword ptr [ebp - 0x18]
00b8b676  51                       push       ecx
00b8b677  b9a8a02301               mov        ecx, 0x123a0a8
00b8b67c  e8cf040000               call       0xb8bb50
00b8b681  68d09fe700               push       0xe79fd0
00b8b686  8dbe84000000             lea        edi, [esi + 0x84]
00b8b68c  68b09fe700               push       0xe79fb0
00b8b691  57                       push       edi
00b8b692  e845770700               call       0xc02ddc
00b8b697  8b16                     mov        edx, dword ptr [esi]
00b8b699  83c40c                   add        esp, 0xc
00b8b69c  57                       push       edi
00b8b69d  8bce                     mov        ecx, esi
00b8b69f  ff5224                   call       dword ptr [edx + 0x24]
00b8b6a2  8d4da4                   lea        ecx, [ebp - 0x5c]
00b8b6a5  e8f6c60000               call       0xb97da0
00b8b6aa  32c0                     xor        al, al
00b8b6ac  e9c5000000               jmp        0xb8b776
00b8b6b1  8945e8                   mov        dword ptr [ebp - 0x18], eax
00b8b6b4  8b4514                   mov        eax, dword ptr [ebp + 0x14]
00b8b6b7  8945e0                   mov        dword ptr [ebp - 0x20], eax
00b8b6ba  c645ec01                 mov        byte ptr [ebp - 0x14], 1
00b8b6be  6890000000               push       0x90
00b8b6c3  e855220600               call       0xbed91d
00b8b6c8  83c404                   add        esp, 4
00b8b6cb  8945a0                   mov        dword ptr [ebp - 0x60], eax
00b8b6ce  3bc3                     cmp        eax, ebx
00b8b6d0  c645fc01                 mov        byte ptr [ebp - 4], 1
00b8b6d4  7413                     je         0xb8b6e9
00b8b6d6  8b4de0                   mov        ecx, dword ptr [ebp - 0x20]
00b8b6d9  8b55e8                   mov        edx, dword ptr [ebp - 0x18]
00b8b6dc  6a01                     push       1
00b8b6de  51                       push       ecx
00b8b6df  52                       push       edx
00b8b6e0  8bc8                     mov        ecx, eax
00b8b6e2  e859caecff               call       0xa58140
00b8b6e7  eb02                     jmp        0xb8b6eb
00b8b6e9  33c0                     xor        eax, eax
00b8b6eb  8945dc                   mov        dword ptr [ebp - 0x24], eax
00b8b6ee  395e7c                   cmp        dword ptr [esi + 0x7c], ebx
00b8b6f1  885dfc                   mov        byte ptr [ebp - 4], bl
00b8b6f4  7425                     je         0xb8b71b
00b8b6f6  8b567c                   mov        edx, dword ptr [esi + 0x7c]
00b8b6f9  8b8680000000             mov        eax, dword ptr [esi + 0x80]
00b8b6ff  8b7e78                   mov        edi, dword ptr [esi + 0x78]
00b8b702  8b4e0c                   mov        ecx, dword ptr [esi + 0xc]
00b8b705  03c2                     add        eax, edx
00b8b707  48                       dec        eax
00b8b708  8bd0                     mov        edx, eax
00b8b70a  25ff000000               and        eax, 0xff
00b8b70f  6bc04c                   imul       eax, eax, 0x4c
00b8b712  c1ea08                   shr        edx, 8
00b8b715  030497                   add        eax, dword ptr [edi + edx*4]
00b8b718  894840                   mov        dword ptr [eax + 0x40], ecx
00b8b71b  8d45a4                   lea        eax, [ebp - 0x5c]
00b8b71e  50                       push       eax
00b8b71f  8d4e70                   lea        ecx, [esi + 0x70]
00b8b722  e889fcffff               call       0xb8b3b0
00b8b727  8b45dc                   mov        eax, dword ptr [ebp - 0x24]
00b8b72a  8b16                     mov        edx, dword ptr [esi]
00b8b72c  53                       push       ebx
00b8b72d  50                       push       eax
00b8b72e  8bce                     mov        ecx, esi
00b8b730  ff5218                   call       dword ptr [edx + 0x18]
00b8b733  b801000000               mov        eax, 1
00b8b738  89463c                   mov        dword ptr [esi + 0x3c], eax
00b8b73b  89460c                   mov        dword ptr [esi + 0xc], eax
00b8b73e  8b45d8                   mov        eax, dword ptr [ebp - 0x28]
00b8b741  be10000000               mov        esi, 0x10
00b8b746  3bc6                     cmp        eax, esi
00b8b748  720c                     jb         0xb8b756
00b8b74a  8b4dc4                   mov        ecx, dword ptr [ebp - 0x3c]
00b8b74d  51                       push       ecx
00b8b74e  e88a480700               call       0xbfffdd
00b8b753  83c404                   add        esp, 4
00b8b756  3975bc                   cmp        dword ptr [ebp - 0x44], esi
00b8b759  c745d80f000000           mov        dword ptr [ebp - 0x28], 0xf
00b8b760  895dd4                   mov        dword ptr [ebp - 0x2c], ebx
00b8b763  885dc4                   mov        byte ptr [ebp - 0x3c], bl
00b8b766  720c                     jb         0xb8b774
00b8b768  8b55a8                   mov        edx, dword ptr [ebp - 0x58]
00b8b76b  52                       push       edx
00b8b76c  e86c480700               call       0xbfffdd
00b8b771  83c404                   add        esp, 4
00b8b774  b001                     mov        al, 1
00b8b776  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
00b8b779  5f                       pop        edi
00b8b77a  5e                       pop        esi
