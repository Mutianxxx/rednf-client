004fa7ed 4d                       dec       ebp
004fa7ee f4                       hlt       
004fa7ef 64890d00000000           mov       dword ptr fs:[0], ecx
004fa7f6 5f                       pop       edi
004fa7f7 5e                       pop       esi
004fa7f8 5b                       pop       ebx
004fa7f9 8be5                     mov       esp, ebp
004fa7fb 5d                       pop       ebp
004fa7fc c3                       ret       
004fa7fd 8bce                     mov       ecx, esi
004fa7ff e88c18faff               call      0x49c090
004fa804 84c0                     test      al, al
004fa806 7435                     je        0x4fa83d
004fa808 8d8e08020000             lea       ecx, [esi + 0x208]
004fa80e e8dd885500               call      0xa530f0
004fa813 8bf8                     mov       edi, eax
004fa815 8b06                     mov       eax, dword ptr [esi]
004fa817 8bce                     mov       ecx, esi
004fa819 ff5040                   call      dword ptr [eax + 0x40]
004fa81c 50                       push      eax
004fa81d 57                       push      edi
004fa81e 68345bcd00               push      0xcd5b34
004fa823 687cebcc00               push      0xcceb7c
004fa828 ff15bc2eff00             call      dword ptr [0xff2ebc]
004fa82e 8b16                     mov       edx, dword ptr [esi]
004fa830 83c410                   add       esp, 0x10
004fa833 6a00                     push      0
004fa835 8bce                     mov       ecx, esi
004fa837 ff9264010000             call      dword ptr [edx + 0x164]
004fa83d 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004fa840 5f                       pop       edi
004fa841 5e                       pop       esi
004fa842 64890d00000000           mov       dword ptr fs:[0], ecx
004fa849 5b                       pop       ebx
004fa84a 8be5                     mov       esp, ebp
004fa84c 5d                       pop       ebp
004fa84d c3                       ret       
004fa84e cc                       int3      
004fa84f cc                       int3      
004fa850 55                       push      ebp
004fa851 8bec                     mov       ebp, esp
004fa853 83ec08                   sub       esp, 8
004fa856 53                       push      ebx
004fa857 56                       push      esi
004fa858 57                       push      edi
004fa859 8b7d08                   mov       edi, dword ptr [ebp + 8]
004fa85c 83ff1c                   cmp       edi, 0x1c
004fa85f 8bf1                     mov       esi, ecx
004fa861 0f8700020000             ja        0x4faa67
004fa867 0fb68730ab4f00           movzx     eax, byte ptr [edi + 0x4fab30]
004fa86e ff248510ab4f00           jmp       dword ptr [eax*4 + 0x4fab10]
004fa875 8bce                     mov       ecx, esi
004fa877 e81418faff               call      0x49c090
004fa87c 84c0                     test      al, al
004fa87e 7414                     je        0x4fa894
004fa880 8b16                     mov       edx, dword ptr [esi]
004fa882 6a00                     push      0
004fa884 6a00                     push      0
004fa886 6a00                     push      0
004fa888 6a00                     push      0
004fa88a 6a00                     push      0
004fa88c 8bce                     mov       ecx, esi
004fa88e ff928c020000             call      dword ptr [edx + 0x28c]
004fa894 8b06                     mov       eax, dword ptr [esi]
004fa896 8bce                     mov       ecx, esi
004fa898 ff906c060000             call      dword ptr [eax + 0x66c]
004fa89e e9c4010000               jmp       0x4faa67
004fa8a3 8bce                     mov       ecx, esi
004fa8a5 e8e617faff               call      0x49c090
004fa8aa 84c0                     test      al, al
004fa8ac 0f84b5010000             je        0x4faa67
004fa8b2 8b16                     mov       edx, dword ptr [esi]
004fa8b4 6a00                     push      0
004fa8b6 6a00                     push      0
004fa8b8 6a00                     push      0
004fa8ba 6a00                     push      0
004fa8bc 6a00                     push      0
004fa8be 8bce                     mov       ecx, esi
004fa8c0 ff928c020000             call      dword ptr [edx + 0x28c]
004fa8c6 e99c010000               jmp       0x4faa67
004fa8cb 33db                     xor       ebx, ebx
004fa8cd b864000000               mov       eax, 0x64
004fa8d2 899e041d0000             mov       dword ptr [esi + 0x1d04], ebx
004fa8d8 8984beb01b0000           mov       dword ptr [esi + edi*4 + 0x1bb0], eax
004fa8df 8984be281c0000           mov       dword ptr [esi + edi*4 + 0x1c28], eax
004fa8e6 33ff                     xor       edi, edi
004fa8e8 eb06                     jmp       0x4fa8f0
004fa8ea 8d9b00000000             lea       ebx, [ebx]
004fa8f0 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004fa8f6 85c0                     test      eax, eax
004fa8f8 0f8466010000             je        0x4faa64
004fa8fe 8b8e641d0000             mov       ecx, dword ptr [esi + 0x1d64]
004fa904 2bc8                     sub       ecx, eax
004fa906 b8abaaaa2a               mov       eax, 0x2aaaaaab
004fa90b f7e9                     imul      ecx
004fa90d c1fa04                   sar       edx, 4
004fa910 8bc2                     mov       eax, edx
004fa912 c1e81f                   shr       eax, 0x1f
004fa915 03c2                     add       eax, edx
004fa917 3bf8                     cmp       edi, eax
004fa919 0f8345010000             jae       0x4faa64
004fa91f 8b86601d0000             mov       eax, dword ptr [esi + 0x1d60]
004fa925 03c3                     add       eax, ebx
004fa927 680c51cd00               push      0xcd510c
004fa92c 8d                       .byte     0x8d
