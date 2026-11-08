0049a680 55                       push      ebp
0049a681 8bec                     mov       ebp, esp
0049a683 83ec10                   sub       esp, 0x10
0049a686 56                       push      esi
0049a687 8bf1                     mov       esi, ecx
0049a689 8b8600010000             mov       eax, dword ptr [esi + 0x100]
0049a68f 85c0                     test      eax, eax
0049a691 0f840c040000             je        0x49aaa3
0049a697 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
0049a69d 85c9                     test      ecx, ecx
0049a69f 8a86c3010000             mov       al, byte ptr [esi + 0x1c3]
0049a6a5 53                       push      ebx
0049a6a6 8b9ec4010000             mov       ebx, dword ptr [esi + 0x1c4]
0049a6ac 57                       push      edi
0049a6ad 8bbec0010000             mov       edi, dword ptr [esi + 0x1c0]
0049a6b3 8845ff                   mov       byte ptr [ebp - 1], al
0049a6b6 0f849d000000             je        0x49a759
0049a6bc e89fd85800               call      0xa27f60
0049a6c1 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
0049a6c7 8b4978                   mov       ecx, dword ptr [ecx + 0x78]
0049a6ca 85c9                     test      ecx, ecx
0049a6cc 745a                     je        0x49a728
0049a6ce 8b11                     mov       edx, dword ptr [ecx]
0049a6d0 ff5240                   call      dword ptr [edx + 0x40]
0049a6d3 d81dd8b9cc00             fcomp     dword ptr [0xccb9d8]
0049a6d9 dfe0                     fnstsw    ax
0049a6db f6c405                   test      ah, 5
0049a6de 7a48                     jp        0x49a728
0049a6e0 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
0049a6e6 8b4878                   mov       ecx, dword ptr [eax + 0x78]
0049a6e9 8b11                     mov       edx, dword ptr [ecx]
0049a6eb ff5240                   call      dword ptr [edx + 0x40]
0049a6ee 0fb645ff                 movzx     eax, byte ptr [ebp - 1]
0049a6f2 8945f0                   mov       dword ptr [ebp - 0x10], eax
0049a6f5 da4df0                   fimul     dword ptr [ebp - 0x10]
0049a6f8 d80dac10cc00             fmul      dword ptr [0xcc10ac]
0049a6fe e8416e7600               call      0xc01544
0049a703 8b8ec0010000             mov       ecx, dword ptr [esi + 0x1c0]
0049a709 0fb6f8                   movzx     edi, al
0049a70c c1e718                   shl       edi, 0x18
0049a70f 81e1ffffff00             and       ecx, 0xffffff
0049a715 0bf9                     or        edi, ecx
0049a717 81cb000000ff             or        ebx, 0xff000000
0049a71d 84c0                     test      al, al
0049a71f 8845ff                   mov       byte ptr [ebp - 1], al
0049a722 0f8479030000             je        0x49aaa1
0049a728 85db                     test      ebx, ebx
0049a72a 740d                     je        0x49a739
0049a72c 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
0049a732 57                       push      edi
0049a733 53                       push      ebx
0049a734 e897b05800               call      0xa257d0
0049a739 8b16                     mov       edx, dword ptr [esi]
0049a73b 8bce                     mov       ecx, esi
0049a73d ff9244010000             call      dword ptr [edx + 0x144]
0049a743 84c0                     test      al, al
0049a745 7412                     je        0x49a759
0049a747 8b86d4010000             mov       eax, dword ptr [esi + 0x1d4]
0049a74d 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
0049a753 50                       push      eax
0049a754 e827b15800               call      0xa25880
0049a759 8b8648010000             mov       eax, dword ptr [esi + 0x148]
0049a75f 85c0                     test      eax, eax
0049a761 0f8498000000             je        0x49a7ff
0049a767 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
0049a76d 8b4978                   mov       ecx, dword ptr [ecx + 0x78]
0049a770 85c9                     test      ecx, ecx
0049a772 745a                     je        0x49a7ce
0049a774 8b11                     mov       edx, dword ptr [ecx]
0049a776 ff5240                   call      dword ptr [edx + 0x40]
0049a779 d81dd8b9cc00             fcomp     dword ptr [0xccb9d8]
0049a77f dfe0                     fnstsw    ax
0049a781 f6c405                   test      ah, 5
0049a784 7a48                     jp        0x49a7ce
0049a786 8b86f8000000             mov       eax, dword ptr [esi + 0xf8]
0049a78c 8b4878                   mov       ecx, dword ptr [eax + 0x78]
0049a78f 8b11                     mov       edx, dword ptr [ecx]
0049a791 ff5240                   call      dword ptr [edx + 0x40]
0049a794 0fb645ff                 movzx     eax, byte ptr [ebp - 1]
0049a798 8945f0                   mov       dword ptr [ebp - 0x10], eax
0049a79b da4df0                   fimul     dword ptr [ebp - 0x10]
0049a79e d80dac10cc00             fmul      dword ptr [0xcc10ac]
0049a7a4 e89b6d7600               call      0xc01544
0049a7a9 8b8ec0010000             mov       ecx, dword ptr [esi + 0x1c0]
0049a7af 0fb6f8                   movzx     edi, al
0049a7b2 c1e718                   shl       edi, 0x18
0049a7b5 81e1ffffff00             and       ecx, 0xffffff
0049a7bb 0bf9                     or        edi, ecx
0049a7bd 81cb000000ff             or        ebx, 0xff000000
0049a7c3 84c0                     test      al, al
0049a7c5 8845ff                   mov       byte ptr [ebp - 1], al
0049a7c8 0f84d3020000             je        0x49aaa1
0049a7ce 85db                     test      ebx, ebx
0049a7d0 740d                     je        0x49a7df
0049a7d2 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
0049a7d8 57                       push      edi
0049a7d9 53                       push      ebx
0049a7da e8212d5900               call      0xa2d500
0049a7df 8b16                     mov       edx, dword ptr [esi]
0049a7e1 8bce                     mov       ecx, esi
0049a7e3 ff9244010000             call      dword ptr [edx + 0x144]
0049a7e9 84c0                     test      al, al
0049a7eb 7412                     je        0x49a7ff
0049a7ed 8b86d4010000             mov       eax, dword ptr [esi + 0x1d4]
0049a7f3 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
0049a7f9 50                       push      eax
0049a7fa e851275900               call      0xa2cf50
0049a7ff 8b16                     mov       edx, dword ptr [esi]
0049a801 8bbe00010000             mov       edi, dword ptr [esi + 0x100]
0049a807 8bce                     mov       ecx, esi
0049a809 ff5228                   call      dword ptr [edx + 0x28]
0049a80c 8b400c                   mov       eax, dword ptr [eax + 0xc]
0049a80f 8b16                     mov       edx, dword ptr [esi]
0049a811 50                       push      eax
0049a812 8bce                     mov       ecx, esi
0049a814 ff9294000000             call      dword ptr [edx + 0x94]
0049a81a 50                       push      eax
0049a81b 8bcf                     mov       ecx, edi
0049a81d e8de010700               call      0x50aa00
0049a822 8b9e00010000             mov       ebx, dword ptr [esi + 0x100]
0049a828 8bf8                     mov       edi, eax
0049a82a 8b06                     mov       eax, dword ptr [esi]
0049a82c 6a00                     push      0
0049a82e 8bce                     mov       ecx, esi
0049a830 897df4                   mov       dword ptr [ebp - 0xc], edi
0049a833 ff5028                   call      dword ptr [eax + 0x28]
0049a836 8b480c                   mov       ecx, dword ptr [eax + 0xc]
0049a839 8b16                     mov       edx, dword ptr [esi]
0049a83b 51                       push      ecx
0049a83c 8bce                     mov       ecx, esi
0049a83e ff929c000000             call      dword ptr [edx + 0x9c]
0049a844 50                       push      eax
0049a845 8b06                     mov       eax, dword ptr [esi]
0049a847 8bce                     mov       ecx, esi
0049a849 ff9098000000             call      dword ptr [eax + 0x98]
0049a84f 50                       push      eax
0049a850 8bcb                     mov       ecx, ebx
0049a852 e8e9010700               call      0x50aa40
0049a857 8b16                     mov       edx, dword ptr [esi]
0049a859 8bce                     mov       ecx, esi
0049a85b 8bd8                     mov       ebx, eax
0049a85d ff929c000000             call      dword ptr [edx + 0x9c]
0049a863 8945f0                   mov       dword ptr [ebp - 0x10], eax
0049a866 8b06                     mov       eax, dword ptr [esi]
0049a868 8bce                     mov       ecx, esi
0049a86a ff90c0000000             call      dword ptr [eax + 0xc0]
0049a870 8b8ef0010000             mov       ecx, dword ptr [esi + 0x1f0]
0049a876 8b16                     mov       edx, dword ptr [esi]
0049a878 83f801                   cmp       eax, 1
0049a87b 0f9545fb                 setne     byte ptr [ebp - 5]
0049a87f 8b45fb                   mov       eax, dword ptr [ebp - 5]
0049a882 50                       push      eax
0049a883 8b86ec010000             mov       eax, dword ptr [esi + 0x1ec]
0049a889 03cb                     add       ecx, ebx
0049a88b 51                       push      ecx
0049a88c 03c7                     add       eax, edi
0049a88e 50                       push      eax
0049a88f 6a00                     push      0
0049a891 8bce                     mov       ecx, esi
0049a893 ff9284010000             call      dword ptr [edx + 0x184]
0049a899 8b860c010000             mov       eax, dword ptr [esi + 0x10c]
0049a89f 8b38                     mov       edi, dword ptr [eax]
0049a8a1 3bf8                     cmp       edi, eax
0049a8a3 0f84c8000000             je        0x49a971
0049a8a9 8da42400000000           lea       esp, [esp]
0049a8b0 8b4708                   mov       eax, dword ptr [edi + 8]
0049a8b3 85c0                     test      eax, eax
0049a8b5 0f8db6000000             jge       0x49a971
0049a8bb 8a4719                   mov       al, byte ptr [edi + 0x19]
0049a8be 84c0                     test      al, al
0049a8c0 7444                     je        0x49a906
0049a8c2 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049a8c5 e896d65800               call      0xa27f60
0049a8ca 8a45fb                   mov       al, byte ptr [ebp - 5]
0049a8cd 84c0                     test      al, al
0049a8cf 7408                     je        0x49a8d9
0049a8d1 8b45f4                   mov       eax, dword ptr [ebp - 0xc]
0049a8d4 2b4710                   sub       eax, dword ptr [edi + 0x10]
0049a8d7 eb06                     jmp       0x49a8df
0049a8d9 8b4710                   mov       eax, dword ptr [edi + 0x10]
0049a8dc 0345f4                   add       eax, dword ptr [ebp - 0xc]
0049a8df 8a4f18                   mov       cl, byte ptr [edi + 0x18]
0049a8e2 8b55fb                   mov       edx, dword ptr [ebp - 5]
0049a8e5 84c9                     test      cl, cl
0049a8e7 0f95c1                   setne     cl
0049a8ea fec9                     dec       cl
0049a8ec 23ca                     and       ecx, edx
0049a8ee 8b5714                   mov       edx, dword ptr [edi + 0x14]
0049a8f1 51                       push      ecx
0049a8f2 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049a8f5 03d3                     add       edx, ebx
0049a8f7 52                       push      edx
0049a8f8 50                       push      eax
0049a8f9 a12ca90d01               mov       eax, dword ptr [0x10da92c]
0049a8fe 50                       push      eax
0049a8ff e88cc05800               call      0xa26990
0049a904 eb5d                     jmp       0x49a963
0049a906 8a8614010000             mov       al, byte ptr [esi + 0x114]
0049a90c 84c0                     test      al, al
0049a90e 7453                     je        0x49a963
0049a910 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049a913 e848d65800               call      0xa27f60
0049a918 8a45fb                   mov       al, byte ptr [ebp - 5]
0049a91b 84c0                     test      al, al
0049a91d 7408                     je        0x49a927
0049a91f 8b45f4                   mov       eax, dword ptr [ebp - 0xc]
0049a922 2b4710                   sub       eax, dword ptr [edi + 0x10]
0049a925 eb06                     jmp       0x49a92d
0049a927 8b4710                   mov       eax, dword ptr [edi + 0x10]
0049a92a 0345f4                   add       eax, dword ptr [ebp - 0xc]
0049a92d 8a5718                   mov       dl, byte ptr [edi + 0x18]
0049a930 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
0049a933 6a64                     push      0x64
0049a935 84d2                     test      dl, dl
0049a937 689a99993e               push      0x3e99999a
0049a93c 0f95c2                   setne     dl
0049a93f 68cdcccc3e               push      0x3ecccccd
0049a944 51                       push      ecx
0049a945 8b4dfb                   mov       ecx, dword ptr [ebp - 5]
0049a948 feca                     dec       dl
0049a94a 23d1                     and       edx, ecx
0049a94c 8b4f14                   mov       ecx, dword ptr [edi + 0x14]
0049a94f 52                       push      edx
0049a950 8b152ca90d01             mov       edx, dword ptr [0x10da92c]
0049a956 03cb                     add       ecx, ebx
0049a958 51                       push      ecx
0049a959 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049a95c 50                       push      eax
0049a95d 52                       push      edx
0049a95e e89da45800               call      0xa24e00
0049a963 8b3f                     mov       edi, dword ptr [edi]
0049a965 3bbe0c010000             cmp       edi, dword ptr [esi + 0x10c]
0049a96b 0f853fffffff             jne       0x49a8b0
0049a971 8b8e04010000             mov       ecx, dword ptr [esi + 0x104]
0049a977 85c9                     test      ecx, ecx
0049a979 742c                     je        0x49a9a7
0049a97b 8a45ff                   mov       al, byte ptr [ebp - 1]
0049a97e 84c0                     test      al, al
0049a980 7425                     je        0x49a9a7
0049a982 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
0049a985 8b55fb                   mov       edx, dword ptr [ebp - 5]
0049a988 6a64                     push      0x64
0049a98a 689a99993e               push      0x3e99999a
0049a98f 68cdcccc3e               push      0x3ecccccd
0049a994 50                       push      eax
0049a995 8b45f4                   mov       eax, dword ptr [ebp - 0xc]
0049a998 52                       push      edx
0049a999 8b152ca90d01             mov       edx, dword ptr [0x10da92c]
0049a99f 53                       push      ebx
0049a9a0 50                       push      eax
0049a9a1 52                       push      edx
0049a9a2 e859a45800               call      0xa24e00
0049a9a7 8b8e48010000             mov       ecx, dword ptr [esi + 0x148]
0049a9ad 85c9                     test      ecx, ecx
0049a9af 7419                     je        0x49a9ca
0049a9b1 8a45ff                   mov       al, byte ptr [ebp - 1]
0049a9b4 84c0                     test      al, al
0049a9b6 7412                     je        0x49a9ca
0049a9b8 8b45f0                   mov       eax, dword ptr [ebp - 0x10]
0049a9bb 8b55fb                   mov       edx, dword ptr [ebp - 5]
0049a9be 50                       push      eax
0049a9bf 8b45f4                   mov       eax, dword ptr [ebp - 0xc]
0049a9c2 52                       push      edx
0049a9c3 53                       push      ebx
0049a9c4 50                       push      eax
0049a9c5 e8262a5900               call      0xa2d3f0
0049a9ca 3bbe0c010000             cmp       edi, dword ptr [esi + 0x10c]
0049a9d0 0f84b6000000             je        0x49aa8c
0049a9d6 8a4719                   mov       al, byte ptr [edi + 0x19]
0049a9d9 84c0                     test      al, al
0049a9db 7444                     je        0x49aa21
0049a9dd 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049a9e0 e87bd55800               call      0xa27f60
0049a9e5 8a45fb                   mov       al, byte ptr [ebp - 5]
0049a9e8 84c0                     test      al, al
0049a9ea 7408                     je        0x49a9f4
0049a9ec 8b45f4                   mov       eax, dword ptr [ebp - 0xc]
0049a9ef 2b4710                   sub       eax, dword ptr [edi + 0x10]
0049a9f2 eb06                     jmp       0x49a9fa
0049a9f4 8b4710                   mov       eax, dword ptr [edi + 0x10]
0049a9f7 0345f4                   add       eax, dword ptr [ebp - 0xc]
0049a9fa 8a4f18                   mov       cl, byte ptr [edi + 0x18]
0049a9fd 8b55fb                   mov       edx, dword ptr [ebp - 5]
0049aa00 84c9                     test      cl, cl
0049aa02 0f95c1                   setne     cl
0049aa05 fec9                     dec       cl
0049aa07 23ca                     and       ecx, edx
0049aa09 8b5714                   mov       edx, dword ptr [edi + 0x14]
0049aa0c 51                       push      ecx
0049aa0d 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049aa10 03d3                     add       edx, ebx
0049aa12 52                       push      edx
0049aa13 50                       push      eax
0049aa14 a12ca90d01               mov       eax, dword ptr [0x10da92c]
0049aa19 50                       push      eax
0049aa1a e871bf5800               call      0xa26990
0049aa1f eb5d                     jmp       0x49aa7e
0049aa21 8a8614010000             mov       al, byte ptr [esi + 0x114]
0049aa27 84c0                     test      al, al
0049aa29 7453                     je        0x49aa7e
0049aa2b 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049aa2e e82dd55800               call      0xa27f60
0049aa33 8a45fb                   mov       al, byte ptr [ebp - 5]
0049aa36 84c0                     test      al, al
0049aa38 7408                     je        0x49aa42
0049aa3a 8b45f4                   mov       eax, dword ptr [ebp - 0xc]
0049aa3d 2b4710                   sub       eax, dword ptr [edi + 0x10]
0049aa40 eb06                     jmp       0x49aa48
0049aa42 8b4710                   mov       eax, dword ptr [edi + 0x10]
0049aa45 0345f4                   add       eax, dword ptr [ebp - 0xc]
0049aa48 8a5718                   mov       dl, byte ptr [edi + 0x18]
0049aa4b 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
0049aa4e 6a64                     push      0x64
0049aa50 84d2                     test      dl, dl
0049aa52 689a99993e               push      0x3e99999a
0049aa57 0f95c2                   setne     dl
0049aa5a 68cdcccc3e               push      0x3ecccccd
0049aa5f 51                       push      ecx
0049aa60 8b4dfb                   mov       ecx, dword ptr [ebp - 5]
0049aa63 feca                     dec       dl
0049aa65 23d1                     and       edx, ecx
0049aa67 8b4f14                   mov       ecx, dword ptr [edi + 0x14]
0049aa6a 52                       push      edx
0049aa6b 8b152ca90d01             mov       edx, dword ptr [0x10da92c]
0049aa71 03cb                     add       ecx, ebx
0049aa73 51                       push      ecx
0049aa74 8b4f0c                   mov       ecx, dword ptr [edi + 0xc]
0049aa77 50                       push      eax
0049aa78 52                       push      edx
0049aa79 e882a35800               call      0xa24e00
0049aa7e 8b3f                     mov       edi, dword ptr [edi]
0049aa80 3bbe0c010000             cmp       edi, dword ptr [esi + 0x10c]
0049aa86 0f854affffff             jne       0x49a9d6
0049aa8c 8b4dfb                   mov       ecx, dword ptr [ebp - 5]
0049aa8f 8b55f4                   mov       edx, dword ptr [ebp - 0xc]
0049aa92 8b06                     mov       eax, dword ptr [esi]
0049aa94 51                       push      ecx
0049aa95 53                       push      ebx
0049aa96 52                       push      edx
0049aa97 6a01                     push      1
0049aa99 8bce                     mov       ecx, esi
0049aa9b ff9084010000             call      dword ptr [eax + 0x184]
0049aaa1 5f                       pop       edi
0049aaa2 5b                       pop       ebx
0049aaa3 5e                       pop       esi
0049aaa4 8be5                     mov       esp, ebp
0049aaa6 5d                       pop       ebp
0049aaa7 c3                       ret       
0049aaa8 cc                       int3      
0049aaa9 cc                       int3      
0049aaaa cc                       int3      
0049aaab cc                       int3      
0049aaac cc                       int3      
0049aaad cc                       int3      
0049aaae cc                       int3      
0049aaaf cc                       int3      
0049aab0 55                       push      ebp
0049aab1 8bec                     mov       ebp, esp
0049aab3 8b890c010000             mov       ecx, dword ptr [ecx + 0x10c]
0049aab9 8b01                     mov       eax, dword ptr [ecx]
0049aabb 3bc1                     cmp       eax, ecx
0049aabd 740e                     je        0x49aacd
0049aabf 8b5508                   mov       edx, dword ptr [ebp + 8]
0049aac2 39500c                   cmp       dword ptr [eax + 0xc], edx
0049aac5 740c                     je        0x49aad3
0049aac7 8b00                     mov       eax, dword ptr [eax]
0049aac9 3bc1                     cmp       eax, ecx
0049aacb 75f5                     jne       0x49aac2
0049aacd 33c0                     xor       eax, eax
0049aacf 5d                       pop       ebp
0049aad0 c20400                   ret       4
0049aad3 83c008                   add       eax, 8
0049aad6 5d                       pop       ebp
0049aad7 c20400                   ret       4
0049aada cc                       int3      
0049aadb cc                       int3      
0049aadc cc                       int3      
0049aadd cc                       int3      
0049aade cc                       int3      
0049aadf cc                       int3      
0049aae0 55                       push      ebp
0049aae1 8bec                     mov       ebp, esp
0049aae3 53                       push      ebx
0049aae4 8b5d08                   mov       ebx, dword ptr [ebp + 8]
0049aae7 56                       push      esi
0049aae8 57                       push      edi
0049aae9 8bf9                     mov       edi, ecx
0049aaeb 53                       push      ebx
0049aaec 8d4f20                   lea       ecx, [edi + 0x20]
0049aaef 899fe0000000             mov       dword ptr [edi + 0xe0], ebx
0049aaf5 e8e6c56600               call      0xb070e0
0049aafa 53                       push      ebx
0049aafb 8d4f60                   lea       ecx, [edi + 0x60]
0049aafe e8ddc56600               call      0xb070e0
0049ab03 53                       push      ebx
0049ab04 8d8fa0000000             lea       ecx, [edi + 0xa0]
0049ab0a e8d1c56600               call      0xb070e0
0049ab0f 8b8704010000             mov       eax, dword ptr [edi + 0x104]
0049ab15 85c0                     test      eax, eax
0049ab17 7409                     je        0x49ab22
0049ab19 53                       push      ebx
0049ab1a 8d4848                   lea       ecx, [eax + 0x48]
0049ab1d e8bec56600               call      0xb070e0
0049ab22 8b870c010000             mov       eax, dword ptr [edi + 0x10c]
0049ab28 8b30                     mov       esi, dword ptr [eax]
0049ab2a 3bf0                     cmp       esi, eax
0049ab2c 7418                     je        0x49ab46
0049ab2e 8bff                     mov       edi, edi
0049ab30 8b4e0c                   mov       ecx, dword ptr [esi + 0xc]
0049ab33 53                       push      ebx
0049ab34 83c148                   add       ecx, 0x48
0049ab37 e8a4c56600               call      0xb070e0
0049ab3c 8b36                     mov       esi, dword ptr [esi]
0049ab3e 3bb70c010000             cmp       esi, dword ptr [edi + 0x10c]
0049ab44 75ea                     jne       0x49ab30
0049ab46 8b8ff8000000             mov       ecx, dword ptr [edi + 0xf8]
0049ab4c 53                       push      ebx
0049ab4d e8ce630700               call      0x510f20
0049ab52 5f                       pop       edi
0049ab53 5e                       pop       esi
0049ab54 5b                       pop       ebx
0049ab55 5d                       pop       ebp
0049ab56 c20400                   ret       4
0049ab59 cc                       int3      
0049ab5a cc                       int3      
0049ab5b cc                       int3      
0049ab5c cc                       int3      
0049ab5d cc                       int3      
0049ab5e cc                       int3      
0049ab5f cc                       int3      
0049ab60 55                       push      ebp
0049ab61 8bec                     mov       ebp, esp
0049ab63 8b916c010000             mov       edx, dword ptr [ecx + 0x16c]
0049ab69 85d2                     test      edx, edx
0049ab6b 7421                     je        0x49ab8e
0049ab6d 8b8170010000             mov       eax, dword ptr [ecx + 0x170]
0049ab73 2bc2                     sub       eax, edx
0049ab75 8b5508                   mov       edx, dword ptr [ebp + 8]
0049ab78 c1f802                   sar       eax, 2
0049ab7b 3bc2                     cmp       eax, edx
0049ab7d 760f                     jbe       0x49ab8e
0049ab7f 8b816c010000             mov       eax, dword ptr [ecx + 0x16c]
0049ab85 8d0490                   lea       eax, [eax + edx*4]
0049ab88 8b00                     mov       eax, dword ptr [eax]
0049ab8a 5d                       pop       ebp
0049ab8b c20400                   ret       4
0049ab8e 83c8ff                   or        eax, 0xffffffff
0049ab91 5d                       pop       ebp
0049ab92 c20400                   ret       4
0049ab95 cc                       int3      
0049ab96 cc                       int3      
0049ab97 cc                       int3      
0049ab98 cc                       int3      
0049ab99 cc                       int3      
0049ab9a cc                       int3      
0049ab9b cc                       int3      
0049ab9c cc                       int3      
0049ab9d cc                       int3      
0049ab9e cc                       int3      
0049ab9f cc                       int3      
0049aba0 55                       push      ebp
0049aba1 8bec                     mov       ebp, esp
0049aba3 8b5508                   mov       edx, dword ptr [ebp + 8]
0049aba6 85d2                     test      edx, edx
0049aba8 56                       push      esi
0049aba9 8bf1                     mov       esi, ecx
0049abab 7450                     je        0x49abfd
0049abad 8b8e0c010000             mov       ecx, dword ptr [esi + 0x10c]
0049abb3 8b01                     mov       eax, dword ptr [ecx]
0049abb5 3bc1                     cmp       eax, ecx
0049abb7 7444                     je        0x49abfd
0049abb9 8da42400000000           lea       esp, [esp]
0049abc0 39500c                   cmp       dword ptr [eax + 0xc], edx
0049abc3 740b                     je        0x49abd0
0049abc5 8b00                     mov       eax, dword ptr [eax]
0049abc7 3bc1                     cmp       eax, ecx
0049abc9 75f5                     jne       0x49abc0
0049abcb 5e                       pop       esi
0049abcc 5d                       pop       ebp
0049abcd c20400                   ret       4
0049abd0 3b860c010000             cmp       eax, dword ptr [esi + 0x10c]
0049abd6 7425                     je        0x49abfd
0049abd8 8b4804                   mov       ecx, dword ptr [eax + 4]
0049abdb 8b10                     mov       edx, dword ptr [eax]
0049abdd 8911                     mov       dword ptr [ecx], edx
0049abdf 8b08                     mov       ecx, dword ptr [eax]
0049abe1 8b5004                   mov       edx, dword ptr [eax + 4]
0049abe4 50                       push      eax
0049abe5 895104                   mov       dword ptr [ecx + 4], edx
0049abe8 e8f0537600               call      0xbfffdd
0049abed 8b8610010000             mov       eax, dword ptr [esi + 0x110]
0049abf3 83c404                   add       esp, 4
0049abf6 48                       dec       eax
0049abf7 898610010000             mov       dword ptr [esi + 0x110], eax
0049abfd 5e                       pop       esi
0049abfe 5d                       pop       ebp
0049abff c20400                   ret       4
0049ac02 cc                       int3      
0049ac03 cc                       int3      
0049ac04 cc                       int3      
0049ac05 cc                       int3      
0049ac06 cc                       int3      
0049ac07 cc                       int3      
0049ac08 cc                       int3      
0049ac09 cc                       int3      
0049ac0a cc                       int3      
0049ac0b cc                       int3      
0049ac0c cc                       int3      
0049ac0d cc                       int3      
0049ac0e cc                       int3      
0049ac0f cc                       int3      
0049ac10 55                       push      ebp
0049ac11 8bec                     mov       ebp, esp
0049ac13 6aff                     push      -1
0049ac15 68f069c500               push      0xc569f0
0049ac1a 64a100000000             mov       eax, dword ptr fs:[0]
0049ac20 50                       push      eax
0049ac21 64892500000000           mov       dword ptr fs:[0], esp
0049ac28 51                       push      ecx
0049ac29 56                       push      esi
0049ac2a 8bf1                     mov       esi, ecx
0049ac2c 8b868c010000             mov       eax, dword ptr [esi + 0x18c]
0049ac32 85c0                     test      eax, eax
0049ac34 7531                     jne       0x49ac67
0049ac36 68c4010000               push      0x1c4
0049ac3b e8dd2c7500               call      0xbed91d
0049ac40 83c404                   add       esp, 4
0049ac43 8945f0                   mov       dword ptr [ebp - 0x10], eax
0049ac46 85c0                     test      eax, eax
0049ac48 c745fc00000000           mov       dword ptr [ebp - 4], 0
0049ac4f 740e                     je        0x49ac5f
0049ac51 6a00                     push      0
0049ac53 6a78                     push      0x78
0049ac55 56                       push      esi
0049ac56 8bc8                     mov       ecx, eax
0049ac58 e883170000               call      0x49c3e0
0049ac5d eb02                     jmp       0x49ac61
0049ac5f 33c0                     xor       eax, eax
0049ac61 89868c010000             mov       dword ptr [esi + 0x18c], eax
0049ac67 8b868c010000             mov       eax, dword ptr [esi + 0x18c]
0049ac6d 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
0049ac70 5e                       pop       esi
0049ac71 64890d00000000           mov       dword ptr fs:[0], ecx
0049ac78 8be5                     mov       esp, ebp
0049ac7a 5d                       pop       ebp
0049ac7b c3                       ret       
0049ac7c cc                       int3      
0049ac7d cc                       int3      
0049ac7e cc                       int3      
0049ac7f cc                       int3      
0049ac80 55                       push      ebp
0049ac81 8bec                     mov       ebp, esp
0049ac83 83ec50                   sub       esp, 0x50
0049ac86 53                       push      ebx
0049ac87 56                       push      esi
0049ac88 8bd9                     mov       ebx, ecx
0049ac8a 57                       push      edi
0049ac8b 8d4b60                   lea       ecx, [ebx + 0x60]
0049ac8e e86dc26600               call      0xb06f00
0049ac93 8945f8                   mov       dword ptr [ebp - 8], eax
0049ac96 8b4314                   mov       eax, dword ptr [ebx + 0x14]
0049ac99 85c0                     test      eax, eax
0049ac9b 0f848e000000             je        0x49ad2f
0049aca1 8b4318                   mov       eax, dword ptr [ebx + 0x18]
0049aca4 8b7310                   mov       esi, dword ptr [ebx + 0x10]
0049aca7 8b7b10                   mov       edi, dword ptr [ebx + 0x10]
0049acaa 8bc8                     mov       ecx, eax
0049acac 8bd1                     mov       edx, ecx
0049acae c1ea08                   shr       edx, 8
0049acb1 8b1496                   mov       edx, dword ptr [esi + edx*4]
0049acb4 81e1ff000000             and       ecx, 0xff
0049acba 8bf0                     mov       esi, eax
0049acbc 6bc934                   imul      ecx, ecx, 0x34
0049acbf 8b4c0a24                 mov       ecx, dword ptr [edx + ecx + 0x24]
0049acc3 25ff000000               and       eax, 0xff
0049acc8 6bc034                   imul      eax, eax, 0x34
0049accb c1ee08                   shr       esi, 8
0049acce 8b                       .byte     0x8b
0049accf 34                       .byte     0x34
