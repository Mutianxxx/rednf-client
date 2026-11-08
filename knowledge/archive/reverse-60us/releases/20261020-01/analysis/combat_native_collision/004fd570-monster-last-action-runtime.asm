004fd570 55                       push      ebp
004fd571 8bec                     mov       ebp, esp
004fd573 83ec10                   sub       esp, 0x10
004fd576 a1385a0101               mov       eax, dword ptr [0x1015a38]
004fd57b 53                       push      ebx
004fd57c 56                       push      esi
004fd57d 33db                     xor       ebx, ebx
004fd57f 3bc3                     cmp       eax, ebx
004fd581 57                       push      edi
004fd582 8bf1                     mov       esi, ecx
004fd584 7515                     jne       0x4fd59b
004fd586 8b0dd8300001             mov       ecx, dword ptr [0x10030d8]
004fd58c 8b01                     mov       eax, dword ptr [ecx]
004fd58e 68245dcd00               push      0xcd5d24
004fd593 ff5010                   call      dword ptr [eax + 0x10]
004fd596 a3385a0101               mov       dword ptr [0x1015a38], eax
004fd59b 391d3c5a0101             cmp       dword ptr [0x1015a3c], ebx
004fd5a1 7515                     jne       0x4fd5b8
004fd5a3 8b0dd8300001             mov       ecx, dword ptr [0x10030d8]
004fd5a9 8b11                     mov       edx, dword ptr [ecx]
004fd5ab 68e85ccd00               push      0xcd5ce8
004fd5b0 ff5210                   call      dword ptr [edx + 0x10]
004fd5b3 a33c5a0101               mov       dword ptr [0x1015a3c], eax
004fd5b8 a1d8012101               mov       eax, dword ptr [0x12101d8]
004fd5bd 8b4844                   mov       ecx, dword ptr [eax + 0x44]
004fd5c0 8b1510520001             mov       edx, dword ptr [0x1005210]
004fd5c6 8d0491                   lea       eax, [ecx + edx*4]
004fd5c9 8b10                     mov       edx, dword ptr [eax]
004fd5cb 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004fd5d1 33d0                     xor       edx, eax
004fd5d3 33d1                     xor       edx, ecx
004fd5d5 42                       inc       edx
004fd5d6 33d0                     xor       edx, eax
004fd5d8 33d1                     xor       edx, ecx
004fd5da 8910                     mov       dword ptr [eax], edx
004fd5dc a1d8012101               mov       eax, dword ptr [0x12101d8]
004fd5e1 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004fd5e4 8b1510520001             mov       edx, dword ptr [0x1005210]
004fd5ea 8d0491                   lea       eax, [ecx + edx*4]
004fd5ed 8b10                     mov       edx, dword ptr [eax]
004fd5ef 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004fd5f5 33d0                     xor       edx, eax
004fd5f7 33d1                     xor       edx, ecx
004fd5f9 42                       inc       edx
004fd5fa 33d0                     xor       edx, eax
004fd5fc 33d1                     xor       edx, ecx
004fd5fe 8910                     mov       dword ptr [eax], edx
004fd600 83c8ff                   or        eax, 0xffffffff
004fd603 8d8e441b0000             lea       ecx, [esi + 0x1b44]
004fd609 c786e400000011020000     mov       dword ptr [esi + 0xe4], 0x211
004fd613 c7869804000064000000     mov       dword ptr [esi + 0x498], 0x64
004fd61d 899eb41d0000             mov       dword ptr [esi + 0x1db4], ebx
004fd623 899ec81d0000             mov       dword ptr [esi + 0x1dc8], ebx
004fd629 899e301a0000             mov       dword ptr [esi + 0x1a30], ebx
004fd62f 8986b81d0000             mov       dword ptr [esi + 0x1db8], eax
004fd635 8986bc1d0000             mov       dword ptr [esi + 0x1dbc], eax
004fd63b 899ee81d0000             mov       dword ptr [esi + 0x1de8], ebx
004fd641 899ee41d0000             mov       dword ptr [esi + 0x1de4], ebx
004fd647 899ee01d0000             mov       dword ptr [esi + 0x1de0], ebx
004fd64d 899edc1d0000             mov       dword ptr [esi + 0x1ddc], ebx
004fd653 899ecc040000             mov       dword ptr [esi + 0x4cc], ebx
004fd659 889e141e0000             mov       byte ptr [esi + 0x1e14], bl
004fd65f 899e181e0000             mov       dword ptr [esi + 0x1e18], ebx
004fd665 899ee4190000             mov       dword ptr [esi + 0x19e4], ebx
004fd66b 889e1c1e0000             mov       byte ptr [esi + 0x1e1c], bl
004fd671 889e1d1e0000             mov       byte ptr [esi + 0x1e1d], bl
004fd677 889ea8240000             mov       byte ptr [esi + 0x24a8], bl
004fd67d 89866c1d0000             mov       dword ptr [esi + 0x1d6c], eax
004fd683 8986701d0000             mov       dword ptr [esi + 0x1d70], eax
004fd689 8b4118                   mov       eax, dword ptr [ecx + 0x18]
004fd68c 83f808                   cmp       eax, 8
004fd68f 7205                     jb        0x4fd696
004fd691 8b5104                   mov       edx, dword ptr [ecx + 4]
004fd694 eb03                     jmp       0x4fd699
004fd696 8d5104                   lea       edx, [ecx + 4]
004fd699 83f808                   cmp       eax, 8
004fd69c 8b7914                   mov       edi, dword ptr [ecx + 0x14]
004fd69f 8d147a                   lea       edx, [edx + edi*2]
004fd6a2 7205                     jb        0x4fd6a9
004fd6a4 8b4104                   mov       eax, dword ptr [ecx + 4]
004fd6a7 eb03                     jmp       0x4fd6ac
004fd6a9 8d4104                   lea       eax, [ecx + 4]
004fd6ac 52                       push      edx
004fd6ad 50                       push      eax
004fd6ae 8d45f4                   lea       eax, [ebp - 0xc]
004fd6b1 50                       push      eax
004fd6b2 e89952f0ff               call      0x402950
004fd6b7 8b86081b0000             mov       eax, dword ptr [esi + 0x1b08]
004fd6bd 83f808                   cmp       eax, 8
004fd6c0 8d8ef01a0000             lea       ecx, [esi + 0x1af0]
004fd6c6 7205                     jb        0x4fd6cd
004fd6c8 8b5104                   mov       edx, dword ptr [ecx + 4]
004fd6cb eb03                     jmp       0x4fd6d0
004fd6cd 8d5104                   lea       edx, [ecx + 4]
004fd6d0 83f808                   cmp       eax, 8
004fd6d3 8b7914                   mov       edi, dword ptr [ecx + 0x14]
004fd6d6 8d147a                   lea       edx, [edx + edi*2]
004fd6d9 7205                     jb        0x4fd6e0
004fd6db 8b4104                   mov       eax, dword ptr [ecx + 4]
004fd6de eb03                     jmp       0x4fd6e3
004fd6e0 8d4104                   lea       eax, [ecx + 4]
004fd6e3 52                       push      edx
004fd6e4 50                       push      eax
004fd6e5 8d55f4                   lea       edx, [ebp - 0xc]
004fd6e8 52                       push      edx
004fd6e9 e86252f0ff               call      0x402950
004fd6ee 8b86541e0000             mov       eax, dword ptr [esi + 0x1e54]
004fd6f4 3bc3                     cmp       eax, ebx
004fd6f6 7409                     je        0x4fd701
004fd6f8 50                       push      eax
004fd6f9 e8df287000               call      0xbfffdd
004fd6fe 83c404                   add       esp, 4
004fd701 8d86681e0000             lea       eax, [esi + 0x1e68]
004fd707 899e541e0000             mov       dword ptr [esi + 0x1e54], ebx
004fd70d 899e581e0000             mov       dword ptr [esi + 0x1e58], ebx
004fd713 899e5c1e0000             mov       dword ptr [esi + 0x1e5c], ebx
004fd719 899e601e0000             mov       dword ptr [esi + 0x1e60], ebx
004fd71f 8945fc                   mov       dword ptr [ebp - 4], eax
004fd722 c745f81e000000           mov       dword ptr [ebp - 8], 0x1e
004fd729 83cfff                   or        edi, 0xffffffff
004fd72c 8d642400                 lea       esp, [esp]
004fd730 8b08                     mov       ecx, dword ptr [eax]
004fd732 3bcb                     cmp       ecx, ebx
004fd734 7431                     je        0x4fd767
004fd736 8b5004                   mov       edx, dword ptr [eax + 4]
004fd739 8bf9                     mov       edi, ecx
004fd73b 3bfa                     cmp       edi, edx
004fd73d 8955f4                   mov       dword ptr [ebp - 0xc], edx
004fd740 7414                     je        0x4fd756
004fd742 8bcf                     mov       ecx, edi
004fd744 e8075d5500               call      0xa53450
004fd749 8b45f4                   mov       eax, dword ptr [ebp - 0xc]
004fd74c 83c704                   add       edi, 4
004fd74f 3bf8                     cmp       edi, eax
004fd751 75ef                     jne       0x4fd742
004fd753 8b45fc                   mov       eax, dword ptr [ebp - 4]
004fd756 8b00                     mov       eax, dword ptr [eax]
004fd758 50                       push      eax
004fd759 e87f287000               call      0xbfffdd
004fd75e 8b45fc                   mov       eax, dword ptr [ebp - 4]
004fd761 83c404                   add       esp, 4
004fd764 83cfff                   or        edi, 0xffffffff
004fd767 8b4df8                   mov       ecx, dword ptr [ebp - 8]
004fd76a 8918                     mov       dword ptr [eax], ebx
004fd76c 895804                   mov       dword ptr [eax + 4], ebx
004fd76f 895808                   mov       dword ptr [eax + 8], ebx
004fd772 83c010                   add       eax, 0x10
004fd775 49                       dec       ecx
004fd776 8945fc                   mov       dword ptr [ebp - 4], eax
004fd779 894df8                   mov       dword ptr [ebp - 8], ecx
004fd77c 75b2                     jne       0x4fd730
004fd77e 89be44200000             mov       dword ptr [esi + 0x2044], edi
004fd784 89be70200000             mov       dword ptr [esi + 0x2070], edi
004fd78a 89be6c200000             mov       dword ptr [esi + 0x206c], edi
004fd790 89be68200000             mov       dword ptr [esi + 0x2068], edi
004fd796 89be64200000             mov       dword ptr [esi + 0x2064], edi
004fd79c 89be60200000             mov       dword ptr [esi + 0x2060], edi
004fd7a2 89be5c200000             mov       dword ptr [esi + 0x205c], edi
004fd7a8 c78648200000e8030000     mov       dword ptr [esi + 0x2048], 0x3e8
004fd7b2 8b8678200000             mov       eax, dword ptr [esi + 0x2078]
004fd7b8 3bc3                     cmp       eax, ebx
004fd7ba 7409                     je        0x4fd7c5
004fd7bc 50                       push      eax
004fd7bd e81b287000               call      0xbfffdd
004fd7c2 83c404                   add       esp, 4
004fd7c5 899e78200000             mov       dword ptr [esi + 0x2078], ebx
004fd7cb 899e7c200000             mov       dword ptr [esi + 0x207c], ebx
004fd7d1 899e80200000             mov       dword ptr [esi + 0x2080], ebx
004fd7d7 899e84200000             mov       dword ptr [esi + 0x2084], ebx
004fd7dd 899e88200000             mov       dword ptr [esi + 0x2088], ebx
004fd7e3 899e8c200000             mov       dword ptr [esi + 0x208c], ebx
004fd7e9 899e90200000             mov       dword ptr [esi + 0x2090], ebx
004fd7ef 899e0c210000             mov       dword ptr [esi + 0x210c], ebx
004fd7f5 899e10210000             mov       dword ptr [esi + 0x2110], ebx
004fd7fb 8bcf                     mov       ecx, edi
004fd7fd 898e50200000             mov       dword ptr [esi + 0x2050], ecx
004fd803 898e54200000             mov       dword ptr [esi + 0x2054], ecx
004fd809 898e58200000             mov       dword ptr [esi + 0x2058], ecx
004fd80f 68e0baca00               push      0xcabae0
004fd814 889e4c200000             mov       byte ptr [esi + 0x204c], bl
004fd81a 89be5c210000             mov       dword ptr [esi + 0x215c], edi
004fd820 89be60210000             mov       dword ptr [esi + 0x2160], edi
004fd826 c6866421000001           mov       byte ptr [esi + 0x2164], 1
004fd82d e89b257000               call      0xbffdcd
004fd832 83c404                   add       esp, 4
004fd835 50                       push      eax
004fd836 68e0baca00               push      0xcabae0
004fd83b 8d8e68210000             lea       ecx, [esi + 0x2168]
004fd841 e83a56f0ff               call      0x402e80
004fd846 899ec4210000             mov       dword ptr [esi + 0x21c4], ebx
004fd84c 899ec8210000             mov       dword ptr [esi + 0x21c8], ebx
004fd852 a1d8012101               mov       eax, dword ptr [0x12101d8]
004fd857 8b4844                   mov       ecx, dword ptr [eax + 0x44]
004fd85a 8b96a0210000             mov       edx, dword ptr [esi + 0x21a0]
004fd860 8d0491                   lea       eax, [ecx + edx*4]
004fd863 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004fd869 8bd0                     mov       edx, eax
004fd86b 33d1                     xor       edx, ecx
004fd86d 8910                     mov       dword ptr [eax], edx
004fd86f 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004fd875 8b5148                   mov       edx, dword ptr [ecx + 0x48]
004fd878 8b86a0210000             mov       eax, dword ptr [esi + 0x21a0]
004fd87e 8d0482                   lea       eax, [edx + eax*4]
004fd881 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004fd887 8bc8                     mov       ecx, eax
004fd889 33ca                     xor       ecx, edx
004fd88b 8908                     mov       dword ptr [eax], ecx
004fd88d a1d8012101               mov       eax, dword ptr [0x12101d8]
004fd892 8b4844                   mov       ecx, dword ptr [eax + 0x44]
004fd895 8b96a8210000             mov       edx, dword ptr [esi + 0x21a8]
004fd89b 8d0491                   lea       eax, [ecx + edx*4]
004fd89e 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004fd8a4 8bd0                     mov       edx, eax
004fd8a6 33d1                     xor       edx, ecx
004fd8a8 8910                     mov       dword ptr [eax], edx
004fd8aa 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004fd8b0 8b5148                   mov       edx, dword ptr [ecx + 0x48]
004fd8b3 8b86a8210000             mov       eax, dword ptr [esi + 0x21a8]
004fd8b9 8d0482                   lea       eax, [edx + eax*4]
004fd8bc 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004fd8c2 8bc8                     mov       ecx, eax
004fd8c4 33ca                     xor       ecx, edx
004fd8c6 8908                     mov       dword ptr [eax], ecx
004fd8c8 89be4c1d0000             mov       dword ptr [esi + 0x1d4c], edi
004fd8ce 889e501d0000             mov       byte ptr [esi + 0x1d50], bl
004fd8d4 c786f41d0000c8000000     mov       dword ptr [esi + 0x1df4], 0xc8
004fd8de a1d8012101               mov       eax, dword ptr [0x12101d8]
004fd8e3 8b4844                   mov       ecx, dword ptr [eax + 0x44]
004fd8e6 8b96e8210000             mov       edx, dword ptr [esi + 0x21e8]
004fd8ec 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004fd8f2 8d0491                   lea       eax, [ecx + edx*4]
004fd8f5 8bd0                     mov       edx, eax
004fd8f7 33d7                     xor       edx, edi
004fd8f9 8910                     mov       dword ptr [eax], edx
004fd8fb 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004fd901 8b5148                   mov       edx, dword ptr [ecx + 0x48]
004fd904 8b86e8210000             mov       eax, dword ptr [esi + 0x21e8]
004fd90a 8d0482                   lea       eax, [edx + eax*4]
004fd90d 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004fd913 8bc8                     mov       ecx, eax
004fd915 33ca                     xor       ecx, edx
004fd917 8908                     mov       dword ptr [eax], ecx
004fd919 899ecc220000             mov       dword ptr [esi + 0x22cc], ebx
004fd91f 899ed0220000             mov       dword ptr [esi + 0x22d0], ebx
004fd925 c786ac240000ffff0000     mov       dword ptr [esi + 0x24ac], 0xffff
004fd92f 8b86d8220000             mov       eax, dword ptr [esi + 0x22d8]
004fd935 3bc3                     cmp       eax, ebx
004fd937 742f                     je        0x4fd968
004fd939 8b8edc220000             mov       ecx, dword ptr [esi + 0x22dc]
004fd93f 8bf8                     mov       edi, eax
004fd941 3bf9                     cmp       edi, ecx
004fd943 894df4                   mov       dword ptr [ebp - 0xc], ecx
004fd946 7411                     je        0x4fd959
004fd948 8bcf                     mov       ecx, edi
004fd94a e81177f4ff               call      0x445060
004fd94f 8b45f4                   mov       eax, dword ptr [ebp - 0xc]
004fd952 83c734                   add       edi, 0x34
004fd955 3bf8                     cmp       edi, eax
004fd957 75ef                     jne       0x4fd948
004fd959 8b96d8220000             mov       edx, dword ptr [esi + 0x22d8]
004fd95f 52                       push      edx
004fd960 e878267000               call      0xbfffdd
004fd965 83c404                   add       esp, 4
004fd968 899ed8220000             mov       dword ptr [esi + 0x22d8], ebx
004fd96e 899edc220000             mov       dword ptr [esi + 0x22dc], ebx
004fd974 899ee0220000             mov       dword ptr [esi + 0x22e0], ebx
004fd97a 8b86e8220000             mov       eax, dword ptr [esi + 0x22e8]
004fd980 3bc3                     cmp       eax, ebx
004fd982 7409                     je        0x4fd98d
004fd984 50                       push      eax
004fd985 e853267000               call      0xbfffdd
004fd98a 83c404                   add       esp, 4
004fd98d 899ee8220000             mov       dword ptr [esi + 0x22e8], ebx
004fd993 899eec220000             mov       dword ptr [esi + 0x22ec], ebx
004fd999 899ef0220000             mov       dword ptr [esi + 0x22f0], ebx
004fd99f 8b86f8220000             mov       eax, dword ptr [esi + 0x22f8]
004fd9a5 3bc3                     cmp       eax, ebx
004fd9a7 7409                     je        0x4fd9b2
004fd9a9 50                       push      eax
004fd9aa e82e267000               call      0xbfffdd
004fd9af 83c404                   add       esp, 4
004fd9b2 899ef8220000             mov       dword ptr [esi + 0x22f8], ebx
004fd9b8 899efc220000             mov       dword ptr [esi + 0x22fc], ebx
004fd9be 899e00230000             mov       dword ptr [esi + 0x2300], ebx
004fd9c4 8b8608230000             mov       eax, dword ptr [esi + 0x2308]
004fd9ca 3bc3                     cmp       eax, ebx
004fd9cc 7409                     je        0x4fd9d7
004fd9ce 50                       push      eax
004fd9cf e809267000               call      0xbfffdd
004fd9d4 83c404                   add       esp, 4
004fd9d7 899e08230000             mov       dword ptr [esi + 0x2308], ebx
004fd9dd 899e0c230000             mov       dword ptr [esi + 0x230c], ebx
004fd9e3 899e10230000             mov       dword ptr [esi + 0x2310], ebx
004fd9e9 889e64230000             mov       byte ptr [esi + 0x2364], bl
004fd9ef 889ef8230000             mov       byte ptr [esi + 0x23f8], bl
004fd9f5 889ef9230000             mov       byte ptr [esi + 0x23f9], bl
004fd9fb 899efc230000             mov       dword ptr [esi + 0x23fc], ebx
004fda01 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004fda07 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004fda0a 8b8684230000             mov       eax, dword ptr [esi + 0x2384]
004fda10 8d0482                   lea       eax, [edx + eax*4]
004fda13 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004fda19 8bc8                     mov       ecx, eax
004fda1b 33ca                     xor       ecx, edx
004fda1d 8908                     mov       dword ptr [eax], ecx
004fda1f a1d8012101               mov       eax, dword ptr [0x12101d8]
004fda24 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004fda27 8b9684230000             mov       edx, dword ptr [esi + 0x2384]
004fda2d 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004fda33 8d0491                   lea       eax, [ecx + edx*4]
004fda36 8bd0                     mov       edx, eax
004fda38 33d7                     xor       edx, edi
004fda3a 8910                     mov       dword ptr [eax], edx
004fda3c 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004fda42 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004fda45 8b868c230000             mov       eax, dword ptr [esi + 0x238c]
004fda4b 8d0482                   lea       eax, [edx + eax*4]
004fda4e 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004fda54 8bc8                     mov       ecx, eax
004fda56 33ca                     xor       ecx, edx
004fda58 8908                     mov       dword ptr [eax], ecx
004fda5a a1d8012101               mov       eax, dword ptr [0x12101d8]
004fda5f 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004fda62 8b968c230000             mov       edx, dword ptr [esi + 0x238c]
004fda68 8d0491                   lea       eax, [ecx + edx*4]
004fda6b 8b0ddc012101             mov       ecx, dword ptr [0x12101dc]
004fda71 8bd0                     mov       edx, eax
004fda73 33d1                     xor       edx, ecx
004fda75 8910                     mov       dword ptr [eax], edx
004fda77 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004fda7d 8b5244                   mov       edx, dword ptr [edx + 0x44]
004fda80 8b86c4230000             mov       eax, dword ptr [esi + 0x23c4]
004fda86 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004fda8c 8d0482                   lea       eax, [edx + eax*4]
004fda8f 8d8ea8230000             lea       ecx, [esi + 0x23a8]
004fda95 8bd0                     mov       edx, eax
004fda97 33d7                     xor       edx, edi
004fda99 8910                     mov       dword ptr [eax], edx
004fda9b 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004fdaa1 8b5248                   mov       edx, dword ptr [edx + 0x48]
004fdaa4 8b411c                   mov       eax, dword ptr [ecx + 0x1c]
004fdaa7 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004fdaad 8d0482                   lea       eax, [edx + eax*4]
004fdab0 8bd0                     mov       edx, eax
004fdab2 33d7                     xor       edx, edi
004fdab4 8910                     mov       dword ptr [eax], edx
004fdab6 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004fdabc 8b5244                   mov       edx, dword ptr [edx + 0x44]
004fdabf 8b4124                   mov       eax, dword ptr [ecx + 0x24]
004fdac2 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004fdac8 8d0482                   lea       eax, [edx + eax*4]
004fdacb 8bd0                     mov       edx, eax
004fdacd 33d7                     xor       edx, edi
004fdacf 8910                     mov       dword ptr [eax], edx
004fdad1 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004fdad7 8b5248                   mov       edx, dword ptr [edx + 0x48]
004fdada 8b4124                   mov       eax, dword ptr [ecx + 0x24]
004fdadd 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004fdae3 8d0482                   lea       eax, [edx + eax*4]
004fdae6 8bd0                     mov       edx, eax
004fdae8 53                       push      ebx
004fdae9 33d7                     xor       edx, edi
004fdaeb 53                       push      ebx
004fdaec 8910                     mov       dword ptr [eax], edx
004fdaee e86d946000               call      0xb06f60
004fdaf3 8b8608240000             mov       eax, dword ptr [esi + 0x2408]
004fdaf9 8bbe00240000             mov       edi, dword ptr [esi + 0x2400]
004fdaff 8d8e00240000             lea       ecx, [esi + 0x2400]
004fdb05 33d2                     xor       edx, edx
004fdb07 8945f4                   mov       dword ptr [ebp - 0xc], eax
004fdb0a 3bfb                     cmp       edi, ebx
004fdb0c 7614                     jbe       0x4fdb22
004fdb0e 897df0                   mov       dword ptr [ebp - 0x10], edi
004fdb11 c1ef05                   shr       edi, 5
004fdb14 8bd0                     mov       edx, eax
004fdb16 8d14ba                   lea       edx, [edx + edi*4]
004fdb19 8955f4                   mov       dword ptr [ebp - 0xc], edx
004fdb1c 8b55f0                   mov       edx, dword ptr [ebp - 0x10]
004fdb1f 83e21f                   and       edx, 0x1f
004fdb22 8b7df4                   mov       edi, dword ptr [ebp - 0xc]
004fdb25 57                       push      edi
004fdb26 52                       push      edx
004fdb27 50                       push      eax
004fdb28 33c0                     xor       eax, eax
004fdb2a 50                       push      eax
004fdb2b 8d45f0                   lea       eax, [ebp - 0x10]
004fdb2e 50                       push      eax
004fdb2f e86ca90000               call      0x5084a0
004fdb34 889eb0240000             mov       byte ptr [esi + 0x24b0], bl
004fdb3a 899eb4240000             mov       dword ptr [esi + 0x24b4], ebx
004fdb40 8b15d8012101             mov       edx, dword ptr [0x12101d8]
004fdb46 8b4244                   mov       eax, dword ptr [edx + 0x44]
004fdb49 8b8ed4240000             mov       ecx, dword ptr [esi + 0x24d4]
004fdb4f 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004fdb55 8d0488                   lea       eax, [eax + ecx*4]
004fdb58 8bc8                     mov       ecx, eax
004fdb5a 33ca                     xor       ecx, edx
004fdb5c 8908                     mov       dword ptr [eax], ecx
004fdb5e a1d8012101               mov       eax, dword ptr [0x12101d8]
004fdb63 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004fdb66 8b96d4240000             mov       edx, dword ptr [esi + 0x24d4]
004fdb6c 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004fdb72 8d0491                   lea       eax, [ecx + edx*4]
004fdb75 8bd0                     mov       edx, eax
004fdb77 33d7                     xor       edx, edi
004fdb79 8910                     mov       dword ptr [eax], edx
004fdb7b 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004fdb81 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004fdb84 8b86dc240000             mov       eax, dword ptr [esi + 0x24dc]
004fdb8a 8d0482                   lea       eax, [edx + eax*4]
004fdb8d 8b15dc012101             mov       edx, dword ptr [0x12101dc]
004fdb93 8bc8                     mov       ecx, eax
004fdb95 33ca                     xor       ecx, edx
004fdb97 8908                     mov       dword ptr [eax], ecx
004fdb99 a1d8012101               mov       eax, dword ptr [0x12101d8]
004fdb9e 8b96dc240000             mov       edx, dword ptr [esi + 0x24dc]
004fdba4 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004fdba7 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004fdbad 8d0491                   lea       eax, [ecx + edx*4]
004fdbb0 8bd0                     mov       edx, eax
004fdbb2 33d7                     xor       edx, edi
004fdbb4 8910                     mov       dword ptr [eax], edx
004fdbb6 b864000000               mov       eax, 0x64
004fdbbb 68e0baca00               push      0xcabae0
