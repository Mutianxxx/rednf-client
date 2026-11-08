004bc640 92                       xchg      edx, eax
004bc641 0c01                     or        al, 1
004bc643 0000                     add       byte ptr [eax], al
004bc645 8a4510                   mov       al, byte ptr [ebp + 0x10]
004bc648 84c0                     test      al, al
004bc64a 7418                     je        0x4bc664
004bc64c 8dbe64150000             lea       edi, [esi + 0x1564]
004bc652 8bcf                     mov       ecx, edi
004bc654 e89788f4ff               call      0x404ef0
004bc659 6a00                     push      0
004bc65b 6a00                     push      0
004bc65d 8bcf                     mov       ecx, edi
004bc65f e8fca86400               call      0xb06f60
004bc664 8a4514                   mov       al, byte ptr [ebp + 0x14]
004bc667 84c0                     test      al, al
004bc669 741a                     je        0x4bc685
004bc66b 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
004bc671 85c9                     test      ecx, ecx
004bc673 7410                     je        0x4bc685
004bc675 e8e6ac5600               call      0xa27360
004bc67a 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
004bc680 e80b765600               call      0xa23c90
004bc685 8b0dd8012101             mov       ecx, dword ptr [0x12101d8]
004bc68b 8b5144                   mov       edx, dword ptr [ecx + 0x44]
004bc68e 8b8660150000             mov       eax, dword ptr [esi + 0x1560]
004bc694 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004bc69a 8b5d08                   mov       ebx, dword ptr [ebp + 8]
004bc69d 8d0482                   lea       eax, [edx + eax*4]
004bc6a0 8bc8                     mov       ecx, eax
004bc6a2 33cf                     xor       ecx, edi
004bc6a4 33cb                     xor       ecx, ebx
004bc6a6 8908                     mov       dword ptr [eax], ecx
004bc6a8 a1d8012101               mov       eax, dword ptr [0x12101d8]
004bc6ad 8b9660150000             mov       edx, dword ptr [esi + 0x1560]
004bc6b3 8b4848                   mov       ecx, dword ptr [eax + 0x48]
004bc6b6 8b3ddc012101             mov       edi, dword ptr [0x12101dc]
004bc6bc 8d0491                   lea       eax, [ecx + edx*4]
004bc6bf 8bd0                     mov       edx, eax
004bc6c1 33d7                     xor       edx, edi
004bc6c3 33d3                     xor       edx, ebx
004bc6c5 8910                     mov       dword ptr [eax], edx
004bc6c7 8dbeec140000             lea       edi, [esi + 0x14ec]
004bc6cd c7451417000000           mov       dword ptr [ebp + 0x14], 0x17
004bc6d4 8b07                     mov       eax, dword ptr [edi]
004bc6d6 85c0                     test      eax, eax
004bc6d8 740b                     je        0x4bc6e5
004bc6da 8bc8                     mov       ecx, eax
004bc6dc 8b01                     mov       eax, dword ptr [ecx]
004bc6de 53                       push      ebx
004bc6df ff90cc000000             call      dword ptr [eax + 0xcc]
004bc6e5 8b4514                   mov       eax, dword ptr [ebp + 0x14]
004bc6e8 83c704                   add       edi, 4
004bc6eb 48                       dec       eax
004bc6ec 894514                   mov       dword ptr [ebp + 0x14], eax
004bc6ef 75e3                     jne       0x4bc6d4
004bc6f1 8a8665160000             mov       al, byte ptr [esi + 0x1665]
004bc6f7 84c0                     test      al, al
004bc6f9 0f8484000000             je        0x4bc783
004bc6ff 8dbe5c150000             lea       edi, [esi + 0x155c]
004bc705 8bcf                     mov       ecx, edi
004bc707 e85459f4ff               call      0x402060
004bc70c 83f804                   cmp       eax, 4
004bc70f 7535                     jne       0x4bc746
004bc711 8d8e20170000             lea       ecx, [esi + 0x1720]
004bc717 e84459f4ff               call      0x402060
004bc71c 83f802                   cmp       eax, 2
004bc71f 7525                     jne       0x4bc746
004bc721 8a8666160000             mov       al, byte ptr [esi + 0x1666]
004bc727 84c0                     test      al, al
004bc729 751b                     jne       0x4bc746
004bc72b c7866816000000000000     mov       dword ptr [esi + 0x1668], 0
004bc735 c7866c160000ffffffff     mov       dword ptr [esi + 0x166c], 0xffffffff
004bc73f c6866616000001           mov       byte ptr [esi + 0x1666], 1
004bc746 8bcf                     mov       ecx, edi
004bc748 e81359f4ff               call      0x402060
004bc74d 83f804                   cmp       eax, 4
004bc750 7431                     je        0x4bc783
004bc752 8bcf                     mov       ecx, edi
004bc754 e80759f4ff               call      0x402060
004bc759 83f809                   cmp       eax, 9
004bc75c 7425                     je        0x4bc783
004bc75e 8a8666160000             mov       al, byte ptr [esi + 0x1666]
004bc764 84c0                     test      al, al
004bc766 741b                     je        0x4bc783
004bc768 c7866816000000000000     mov       dword ptr [esi + 0x1668], 0
004bc772 c7866c160000ffffffff     mov       dword ptr [esi + 0x166c], 0xffffffff
004bc77c c6866616000000           mov       byte ptr [esi + 0x1666], 0
004bc783 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004bc786 5f                       pop       edi
004bc787 5e                       pop       esi
004bc788 5b                       pop       ebx
004bc789 64890d00000000           mov       dword ptr fs:[0], ecx
004bc790 8be5                     mov       esp, ebp
004bc792 5d                       pop       ebp
004bc793 c21000                   ret       0x10
004bc796 8bff                     mov       edi, edi
