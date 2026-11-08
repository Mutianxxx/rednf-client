00565740 55                       push      ebp
00565741 8bec                     mov       ebp, esp
00565743 53                       push      ebx
00565744 56                       push      esi
00565745 57                       push      edi
00565746 8bd9                     mov       ebx, ecx
00565748 33ff                     xor       edi, edi
0056574a 8d9b00000000             lea       ebx, [ebx]
00565750 8b4b04                   mov       ecx, dword ptr [ebx + 4]
00565753 85c9                     test      ecx, ecx
00565755 7454                     je        0x5657ab
00565757 8b4308                   mov       eax, dword ptr [ebx + 8]
0056575a 2bc1                     sub       eax, ecx
0056575c c1f802                   sar       eax, 2
0056575f 3bf8                     cmp       edi, eax
00565761 7348                     jae       0x5657ab
00565763 8b04b9                   mov       eax, dword ptr [ecx + edi*4]
00565766 8b5508                   mov       edx, dword ptr [ebp + 8]
00565769 395004                   cmp       dword ptr [eax + 4], edx
0056576c 7528                     jne       0x565796
0056576e 6a00                     push      0
00565770 68981ef600               push      0xf61e98
00565775 68f451f500               push      0xf551f4
0056577a 6a00                     push      0
0056577c 50                       push      eax
0056577d e889b56900               call      0xc00d0b
00565782 8bf0                     mov       esi, eax
00565784 83c414                   add       esp, 0x14
00565787 85f6                     test      esi, esi
00565789 740b                     je        0x565796
0056578b 8b16                     mov       edx, dword ptr [esi]
0056578d 8bce                     mov       ecx, esi
0056578f ff5260                   call      dword ptr [edx + 0x60]
00565792 84c0                     test      al, al
00565794 7503                     jne       0x565799
00565796 47                       inc       edi
00565797 ebb7                     jmp       0x565750
00565799 8b06                     mov       eax, dword ptr [esi]
0056579b 6a00                     push      0
0056579d 8bce                     mov       ecx, esi
0056579f ff505c                   call      dword ptr [eax + 0x5c]
005657a2 5f                       pop       edi
005657a3 5e                       pop       esi
005657a4 b001                     mov       al, 1
005657a6 5b                       pop       ebx
005657a7 5d                       pop       ebp
005657a8 c20400                   ret       4
005657ab 5f                       pop       edi
005657ac 5e                       pop       esi
005657ad 32c0                     xor       al, al
005657af 5b                       pop       ebx
005657b0 5d                       pop       ebp
005657b1 c20400                   ret       4
005657b4 cc                       int3      
005657b5 cc                       int3      
005657b6 cc                       int3      
005657b7 cc                       int3      
005657b8 cc                       int3      
005657b9 cc                       int3      
005657ba cc                       int3      
005657bb cc                       int3      
005657bc cc                       int3      
005657bd cc                       int3      
005657be cc                       int3      
005657bf cc                       int3      
005657c0 55                       push      ebp
005657c1 8bec                     mov       ebp, esp
005657c3 53                       push      ebx
005657c4 8bd9                     mov       ebx, ecx
005657c6 8b4304                   mov       eax, dword ptr [ebx + 4]
005657c9 85c0                     test      eax, eax
005657cb 56                       push      esi
005657cc 57                       push      edi
005657cd 7504                     jne       0x5657d3
005657cf 33ff                     xor       edi, edi
005657d1 eb08                     jmp       0x5657db
005657d3 8b7b08                   mov       edi, dword ptr [ebx + 8]
005657d6 2bf8                     sub       edi, eax
005657d8 c1ff02                   sar       edi, 2
005657db 33f6                     xor       esi, esi
005657dd 85ff                     test      edi, edi
005657df 7e1f                     jle       0x565800
005657e1 8b4304                   mov       eax, dword ptr [ebx + 4]
005657e4 8b0cb0                   mov       ecx, dword ptr [eax + esi*4]
005657e7 85c9                     test      ecx, ecx
005657e9 8d04b0                   lea       eax, [eax + esi*4]
005657ec 740d                     je        0x5657fb
005657ee 8bc1                     mov       eax, ecx
005657f0 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005657f3 8b10                     mov       edx, dword ptr [eax]
005657f5 51                       push      ecx
005657f6 8bc8                     mov       ecx, eax
005657f8 ff5240                   call      dword ptr [edx + 0x40]
005657fb 46                       inc       esi
005657fc 3bf7                     cmp       esi, edi
005657fe 7ce1                     jl        0x5657e1
00565800 5f                       pop       edi
00565801 5e                       pop       esi
00565802 5b                       pop       ebx
00565803 5d                       pop       ebp
00565804 c20400                   ret       4
00565807 cc                       int3      
00565808 cc                       int3      
00565809 cc                       int3      
0056580a cc                       int3      
0056580b cc                       int3      
0056580c cc                       int3      
0056580d cc                       int3      
0056580e cc                       int3      
0056580f cc                       int3      
00565810 55                       push      ebp
00565811 8bec                     mov       ebp, esp
00565813 51                       push      ecx
00565814 53                       push      ebx
00565815 56                       push      esi
00565816 8bf1                     mov       esi, ecx
00565818 8b4e04                   mov       ecx, dword ptr [esi + 4]
0056581b 33db                     xor       ebx, ebx
0056581d 3bcb                     cmp       ecx, ebx
0056581f 57                       push      edi
00565820 7505                     jne       0x565827
00565822 895dfc                   mov       dword ptr [ebp - 4], ebx
00565825 eb0b                     jmp       0x565832
00565827 8b4608                   mov       eax, dword ptr [esi + 8]
0056582a 2bc1                     sub       eax, ecx
0056582c c1f802                   sar       eax, 2
0056582f 8945fc                   mov       dword ptr [ebp - 4], eax
00565832 8a4508                   mov       al, byte ptr [ebp + 8]
00565835 84c0                     test      al, al
00565837 7560                     jne       0x565899
00565839 8b45fc                   mov       eax, dword ptr [ebp - 4]
0056583c 48                       dec       eax
0056583d 3bc3                     cmp       eax, ebx
0056583f 894508                   mov       dword ptr [ebp + 8], eax
00565842 0f8c9d000000             jl        0x5658e5
00565848 8b5d10                   mov       ebx, dword ptr [ebp + 0x10]
0056584b eb03                     jmp       0x565850
0056584d 8d4900                   lea       ecx, [ecx]
00565850 8d3c8500000000           lea       edi, [eax*4]
00565857 8b4604                   mov       eax, dword ptr [esi + 4]
0056585a 8b0c38                   mov       ecx, dword ptr [eax + edi]
0056585d 03c7                     add       eax, edi
0056585f 85c9                     test      ecx, ecx
00565861 7424                     je        0x565887
00565863 8bc1                     mov       eax, ecx
00565865 8b10                     mov       edx, dword ptr [eax]
00565867 ff5260                   call      dword ptr [edx + 0x60]
0056586a 84c0                     test      al, al
0056586c 7419                     je        0x565887
0056586e 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
00565871 8b4604                   mov       eax, dword ptr [esi + 4]
00565874 51                       push      ecx
00565875 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
00565878 53                       push      ebx
00565879 03c7                     add       eax, edi
0056587b 8b00                     mov       eax, dword ptr [eax]
0056587d 8b10                     mov       edx, dword ptr [eax]
0056587f 51                       push      ecx
00565880 6a00                     push      0
00565882 8bc8                     mov       ecx, eax
00565884 ff5214                   call      dword ptr [edx + 0x14]
00565887 8b4508                   mov       eax, dword ptr [ebp + 8]
0056588a 48                       dec       eax
0056588b 894508                   mov       dword ptr [ebp + 8], eax
0056588e 79c0                     jns       0x565850
00565890 5f                       pop       edi
00565891 5e                       pop       esi
00565892 5b                       pop       ebx
00565893 8be5                     mov       esp, ebp
00565895 5d                       pop       ebp
00565896 c21000                   ret       0x10
00565899 395dfc                   cmp       dword ptr [ebp - 4], ebx
0056589c 7e47                     jle       0x5658e5
0056589e 8bff                     mov       edi, edi
005658a0 8b5604                   mov       edx, dword ptr [esi + 4]
005658a3 8d3c9d00000000           lea       edi, [ebx*4]
005658aa 8b0c17                   mov       ecx, dword ptr [edi + edx]
005658ad 85c9                     test      ecx, ecx
005658af 8d0417                   lea       eax, [edi + edx]
005658b2 7429                     je        0x5658dd
005658b4 8bc1                     mov       eax, ecx
005658b6 8b10                     mov       edx, dword ptr [eax]
005658b8 ff5260                   call      dword ptr [edx + 0x60]
005658bb 84c0                     test      al, al
005658bd 741e                     je        0x5658dd
005658bf 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
005658c2 8b4604                   mov       eax, dword ptr [esi + 4]
005658c5 51                       push      ecx
005658c6 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
005658c9 51                       push      ecx
005658ca 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
005658cd 51                       push      ecx
005658ce 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005658d1 03c7                     add       eax, edi
005658d3 8b00                     mov       eax, dword ptr [eax]
005658d5 8b10                     mov       edx, dword ptr [eax]
005658d7 51                       push      ecx
005658d8 8bc8                     mov       ecx, eax
005658da ff5214                   call      dword ptr [edx + 0x14]
005658dd 8b45fc                   mov       eax, dword ptr [ebp - 4]
005658e0 43                       inc       ebx
005658e1 3bd8                     cmp       ebx, eax
005658e3 7cbb                     jl        0x5658a0
005658e5 5f                       pop       edi
005658e6 5e                       pop       esi
005658e7 5b                       pop       ebx
005658e8 8be5                     mov       esp, ebp
005658ea 5d                       pop       ebp
005658eb c21000                   ret       0x10
005658ee cc                       int3      
005658ef cc                       int3      
005658f0 55                       push      ebp
005658f1 8bec                     mov       ebp, esp
005658f3 51                       push      ecx
005658f4 53                       push      ebx
005658f5 56                       push      esi
005658f6 8bf1                     mov       esi, ecx
005658f8 8b4e04                   mov       ecx, dword ptr [esi + 4]
005658fb 33db                     xor       ebx, ebx
005658fd 3bcb                     cmp       ecx, ebx
005658ff 57                       push      edi
00565900 7505                     jne       0x565907
00565902 895dfc                   mov       dword ptr [ebp - 4], ebx
00565905 eb0b                     jmp       0x565912
00565907 8b4608                   mov       eax, dword ptr [esi + 8]
0056590a 2bc1                     sub       eax, ecx
0056590c c1f802                   sar       eax, 2
0056590f 8945fc                   mov       dword ptr [ebp - 4], eax
00565912 8a4508                   mov       al, byte ptr [ebp + 8]
00565915 84c0                     test      al, al
00565917 7560                     jne       0x565979
00565919 8b45fc                   mov       eax, dword ptr [ebp - 4]
0056591c 48                       dec       eax
0056591d 3bc3                     cmp       eax, ebx
0056591f 894508                   mov       dword ptr [ebp + 8], eax
00565922 0f8c9d000000             jl        0x5659c5
00565928 8b5d10                   mov       ebx, dword ptr [ebp + 0x10]
0056592b eb03                     jmp       0x565930
0056592d 8d4900                   lea       ecx, [ecx]
00565930 8d3c8500000000           lea       edi, [eax*4]
00565937 8b4604                   mov       eax, dword ptr [esi + 4]
0056593a 8b0c38                   mov       ecx, dword ptr [eax + edi]
0056593d 03c7                     add       eax, edi
0056593f 85c9                     test      ecx, ecx
00565941 7424                     je        0x565967
00565943 8bc1                     mov       eax, ecx
00565945 8b10                     mov       edx, dword ptr [eax]
00565947 ff5260                   call      dword ptr [edx + 0x60]
0056594a 84c0                     test      al, al
0056594c 7419                     je        0x565967
0056594e 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
00565951 8b4604                   mov       eax, dword ptr [esi + 4]
00565954 51                       push      ecx
00565955 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
00565958 53                       push      ebx
00565959 03c7                     add       eax, edi
0056595b 8b00                     mov       eax, dword ptr [eax]
0056595d 8b10                     mov       edx, dword ptr [eax]
0056595f 51                       push      ecx
00565960 6a00                     push      0
00565962 8bc8                     mov       ecx, eax
00565964 ff5218                   call      dword ptr [edx + 0x18]
00565967 8b4508                   mov       eax, dword ptr [ebp + 8]
0056596a 48                       dec       eax
0056596b 894508                   mov       dword ptr [ebp + 8], eax
0056596e 79c0                     jns       0x565930
00565970 5f                       pop       edi
00565971 5e                       pop       esi
00565972 5b                       pop       ebx
00565973 8be5                     mov       esp, ebp
00565975 5d                       pop       ebp
00565976 c21000                   ret       0x10
00565979 395dfc                   cmp       dword ptr [ebp - 4], ebx
0056597c 7e47                     jle       0x5659c5
0056597e 8bff                     mov       edi, edi
00565980 8b5604                   mov       edx, dword ptr [esi + 4]
00565983 8d3c9d00000000           lea       edi, [ebx*4]
0056598a 8b0c17                   mov       ecx, dword ptr [edi + edx]
0056598d 85c9                     test      ecx, ecx
0056598f 8d0417                   lea       eax, [edi + edx]
00565992 7429                     je        0x5659bd
00565994 8bc1                     mov       eax, ecx
00565996 8b10                     mov       edx, dword ptr [eax]
00565998 ff5260                   call      dword ptr [edx + 0x60]
0056599b 84c0                     test      al, al
0056599d 741e                     je        0x5659bd
0056599f 8b4d14                   mov       ecx, dword ptr [ebp + 0x14]
005659a2 8b4604                   mov       eax, dword ptr [esi + 4]
005659a5 51                       push      ecx
005659a6 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
005659a9 51                       push      ecx
005659aa 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
005659ad 51                       push      ecx
005659ae 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005659b1 03c7                     add       eax, edi
005659b3 8b00                     mov       eax, dword ptr [eax]
005659b5 8b10                     mov       edx, dword ptr [eax]
005659b7 51                       push      ecx
005659b8 8bc8                     mov       ecx, eax
005659ba ff5218                   call      dword ptr [edx + 0x18]
005659bd 8b45fc                   mov       eax, dword ptr [ebp - 4]
005659c0 43                       inc       ebx
005659c1 3bd8                     cmp       ebx, eax
005659c3 7cbb                     jl        0x565980
005659c5 5f                       pop       edi
005659c6 5e                       pop       esi
005659c7 5b                       pop       ebx
005659c8 8be5                     mov       esp, ebp
005659ca 5d                       pop       ebp
005659cb c21000                   ret       0x10
005659ce cc                       int3      
005659cf cc                       int3      
