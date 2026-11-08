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
