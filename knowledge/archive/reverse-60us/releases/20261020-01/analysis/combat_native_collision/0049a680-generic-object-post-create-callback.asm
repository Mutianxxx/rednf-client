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
