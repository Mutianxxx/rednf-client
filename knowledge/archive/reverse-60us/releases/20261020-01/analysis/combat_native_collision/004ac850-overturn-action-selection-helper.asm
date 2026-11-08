004ac850 55                       push      ebp
004ac851 8bec                     mov       ebp, esp
004ac853 53                       push      ebx
004ac854 8b5d14                   mov       ebx, dword ptr [ebp + 0x14]
004ac857 56                       push      esi
004ac858 57                       push      edi
004ac859 8b7d10                   mov       edi, dword ptr [ebp + 0x10]
004ac85c 85ff                     test      edi, edi
004ac85e 8bf1                     mov       esi, ecx
004ac860 7530                     jne       0x4ac892
004ac862 8b06                     mov       eax, dword ptr [esi]
004ac864 ff9090030000             call      dword ptr [eax + 0x390]
004ac86a 85c0                     test      eax, eax
004ac86c 0f844a020000             je        0x4acabc
004ac872 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004ac875 8b5508                   mov       edx, dword ptr [ebp + 8]
004ac878 8b06                     mov       eax, dword ptr [esi]
004ac87a 51                       push      ecx
004ac87b 52                       push      edx
004ac87c 8bce                     mov       ecx, esi
004ac87e ff9090030000             call      dword ptr [eax + 0x390]
004ac884 8bc8                     mov       ecx, eax
004ac886 e8c5975800               call      0xa36050
004ac88b 5f                       pop       edi
004ac88c 5e                       pop       esi
004ac88d 5b                       pop       ebx
004ac88e 5d                       pop       ebp
004ac88f c21000                   ret       0x10
004ac892 83ff01                   cmp       edi, 1
004ac895 7532                     jne       0x4ac8c9
004ac897 8b16                     mov       edx, dword ptr [esi]
004ac899 8bce                     mov       ecx, esi
004ac89b ff9294030000             call      dword ptr [edx + 0x394]
004ac8a1 85c0                     test      eax, eax
004ac8a3 0f8413020000             je        0x4acabc
004ac8a9 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004ac8ac 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004ac8af 8b16                     mov       edx, dword ptr [esi]
004ac8b1 50                       push      eax
004ac8b2 51                       push      ecx
004ac8b3 8bce                     mov       ecx, esi
004ac8b5 ff9294030000             call      dword ptr [edx + 0x394]
004ac8bb 8bc8                     mov       ecx, eax
004ac8bd e88e975800               call      0xa36050
004ac8c2 5f                       pop       edi
004ac8c3 5e                       pop       esi
004ac8c4 5b                       pop       ebx
004ac8c5 5d                       pop       ebp
004ac8c6 c21000                   ret       0x10
004ac8c9 83ff02                   cmp       edi, 2
004ac8cc 7532                     jne       0x4ac900
004ac8ce 8b06                     mov       eax, dword ptr [esi]
004ac8d0 8bce                     mov       ecx, esi
004ac8d2 ff9098030000             call      dword ptr [eax + 0x398]
004ac8d8 85c0                     test      eax, eax
004ac8da 0f84dc010000             je        0x4acabc
004ac8e0 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004ac8e3 8b5508                   mov       edx, dword ptr [ebp + 8]
004ac8e6 8b06                     mov       eax, dword ptr [esi]
004ac8e8 51                       push      ecx
004ac8e9 52                       push      edx
004ac8ea 8bce                     mov       ecx, esi
004ac8ec ff9098030000             call      dword ptr [eax + 0x398]
004ac8f2 8bc8                     mov       ecx, eax
004ac8f4 e857975800               call      0xa36050
004ac8f9 5f                       pop       edi
004ac8fa 5e                       pop       esi
004ac8fb 5b                       pop       ebx
004ac8fc 5d                       pop       ebp
004ac8fd c21000                   ret       0x10
004ac900 83ff03                   cmp       edi, 3
004ac903 7536                     jne       0x4ac93b
004ac905 8b16                     mov       edx, dword ptr [esi]
004ac907 6a00                     push      0
004ac909 8bce                     mov       ecx, esi
004ac90b ff929c030000             call      dword ptr [edx + 0x39c]
004ac911 85c0                     test      eax, eax
004ac913 0f84a3010000             je        0x4acabc
004ac919 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004ac91c 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004ac91f 8b16                     mov       edx, dword ptr [esi]
004ac921 50                       push      eax
004ac922 51                       push      ecx
004ac923 6a00                     push      0
004ac925 8bce                     mov       ecx, esi
004ac927 ff929c030000             call      dword ptr [edx + 0x39c]
004ac92d 8bc8                     mov       ecx, eax
004ac92f e81c975800               call      0xa36050
004ac934 5f                       pop       edi
004ac935 5e                       pop       esi
004ac936 5b                       pop       ebx
004ac937 5d                       pop       ebp
004ac938 c21000                   ret       0x10
004ac93b 83ff04                   cmp       edi, 4
004ac93e 7536                     jne       0x4ac976
004ac940 8b06                     mov       eax, dword ptr [esi]
004ac942 6a01                     push      1
004ac944 8bce                     mov       ecx, esi
004ac946 ff909c030000             call      dword ptr [eax + 0x39c]
004ac94c 85c0                     test      eax, eax
004ac94e 0f8468010000             je        0x4acabc
004ac954 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004ac957 8b5508                   mov       edx, dword ptr [ebp + 8]
004ac95a 8b06                     mov       eax, dword ptr [esi]
004ac95c 51                       push      ecx
004ac95d 52                       push      edx
004ac95e 6a01                     push      1
004ac960 8bce                     mov       ecx, esi
004ac962 ff909c030000             call      dword ptr [eax + 0x39c]
004ac968 8bc8                     mov       ecx, eax
004ac96a e8e1965800               call      0xa36050
004ac96f 5f                       pop       edi
004ac970 5e                       pop       esi
004ac971 5b                       pop       ebx
004ac972 5d                       pop       ebp
004ac973 c21000                   ret       0x10
004ac976 83ff05                   cmp       edi, 5
004ac979 7532                     jne       0x4ac9ad
004ac97b 8b16                     mov       edx, dword ptr [esi]
004ac97d 8bce                     mov       ecx, esi
004ac97f ff92a0030000             call      dword ptr [edx + 0x3a0]
004ac985 85c0                     test      eax, eax
004ac987 0f842f010000             je        0x4acabc
004ac98d 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004ac990 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004ac993 8b16                     mov       edx, dword ptr [esi]
004ac995 50                       push      eax
004ac996 51                       push      ecx
004ac997 8bce                     mov       ecx, esi
004ac999 ff92a0030000             call      dword ptr [edx + 0x3a0]
004ac99f 8bc8                     mov       ecx, eax
004ac9a1 e8aa965800               call      0xa36050
004ac9a6 5f                       pop       edi
004ac9a7 5e                       pop       esi
004ac9a8 5b                       pop       ebx
004ac9a9 5d                       pop       ebp
004ac9aa c21000                   ret       0x10
004ac9ad 83ff06                   cmp       edi, 6
004ac9b0 7532                     jne       0x4ac9e4
004ac9b2 8b06                     mov       eax, dword ptr [esi]
004ac9b4 8bce                     mov       ecx, esi
004ac9b6 ff90a4030000             call      dword ptr [eax + 0x3a4]
004ac9bc 85c0                     test      eax, eax
004ac9be 0f84f8000000             je        0x4acabc
004ac9c4 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004ac9c7 8b5508                   mov       edx, dword ptr [ebp + 8]
004ac9ca 8b06                     mov       eax, dword ptr [esi]
004ac9cc 51                       push      ecx
004ac9cd 52                       push      edx
004ac9ce 8bce                     mov       ecx, esi
004ac9d0 ff90a4030000             call      dword ptr [eax + 0x3a4]
004ac9d6 8bc8                     mov       ecx, eax
004ac9d8 e873965800               call      0xa36050
004ac9dd 5f                       pop       edi
004ac9de 5e                       pop       esi
004ac9df 5b                       pop       ebx
004ac9e0 5d                       pop       ebp
004ac9e1 c21000                   ret       0x10
004ac9e4 83ff07                   cmp       edi, 7
004ac9e7 7532                     jne       0x4aca1b
004ac9e9 8b16                     mov       edx, dword ptr [esi]
004ac9eb 8bce                     mov       ecx, esi
004ac9ed ff92a8030000             call      dword ptr [edx + 0x3a8]
004ac9f3 85c0                     test      eax, eax
004ac9f5 0f84c1000000             je        0x4acabc
004ac9fb 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004ac9fe 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004aca01 8b16                     mov       edx, dword ptr [esi]
004aca03 50                       push      eax
004aca04 51                       push      ecx
004aca05 8bce                     mov       ecx, esi
004aca07 ff92a8030000             call      dword ptr [edx + 0x3a8]
004aca0d 8bc8                     mov       ecx, eax
004aca0f e83c965800               call      0xa36050
004aca14 5f                       pop       edi
004aca15 5e                       pop       esi
004aca16 5b                       pop       ebx
004aca17 5d                       pop       ebp
004aca18 c21000                   ret       0x10
004aca1b 83ff08                   cmp       edi, 8
004aca1e 7532                     jne       0x4aca52
004aca20 8b06                     mov       eax, dword ptr [esi]
004aca22 8bce                     mov       ecx, esi
004aca24 ff90ac030000             call      dword ptr [eax + 0x3ac]
004aca2a 85c0                     test      eax, eax
004aca2c 0f848a000000             je        0x4acabc
004aca32 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004aca35 8b5508                   mov       edx, dword ptr [ebp + 8]
004aca38 8b06                     mov       eax, dword ptr [esi]
004aca3a 51                       push      ecx
004aca3b 52                       push      edx
004aca3c 8bce                     mov       ecx, esi
004aca3e ff90ac030000             call      dword ptr [eax + 0x3ac]
004aca44 8bc8                     mov       ecx, eax
004aca46 e805965800               call      0xa36050
004aca4b 5f                       pop       edi
004aca4c 5e                       pop       esi
004aca4d 5b                       pop       ebx
004aca4e 5d                       pop       ebp
004aca4f c21000                   ret       0x10
004aca52 83ff09                   cmp       edi, 9
004aca55 7530                     jne       0x4aca87
004aca57 8b16                     mov       edx, dword ptr [esi]
004aca59 53                       push      ebx
004aca5a 8bce                     mov       ecx, esi
004aca5c ff92b0030000             call      dword ptr [edx + 0x3b0]
004aca62 85c0                     test      eax, eax
004aca64 7456                     je        0x4acabc
004aca66 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004aca69 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004aca6c 8b16                     mov       edx, dword ptr [esi]
004aca6e 50                       push      eax
004aca6f 51                       push      ecx
004aca70 53                       push      ebx
004aca71 8bce                     mov       ecx, esi
004aca73 ff92b0030000             call      dword ptr [edx + 0x3b0]
004aca79 8bc8                     mov       ecx, eax
004aca7b e8d0955800               call      0xa36050
004aca80 5f                       pop       edi
004aca81 5e                       pop       esi
004aca82 5b                       pop       ebx
004aca83 5d                       pop       ebp
004aca84 c21000                   ret       0x10
004aca87 83ff0a                   cmp       edi, 0xa
004aca8a 7530                     jne       0x4acabc
004aca8c 8b06                     mov       eax, dword ptr [esi]
004aca8e 53                       push      ebx
004aca8f 8bce                     mov       ecx, esi
004aca91 ff90b4030000             call      dword ptr [eax + 0x3b4]
004aca97 85c0                     test      eax, eax
004aca99 7421                     je        0x4acabc
004aca9b 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004aca9e 8b5508                   mov       edx, dword ptr [ebp + 8]
004acaa1 8b06                     mov       eax, dword ptr [esi]
004acaa3 51                       push      ecx
004acaa4 52                       push      edx
004acaa5 53                       push      ebx
004acaa6 8bce                     mov       ecx, esi
004acaa8 ff90b4030000             call      dword ptr [eax + 0x3b4]
004acaae 8bc8                     mov       ecx, eax
004acab0 e89b955800               call      0xa36050
004acab5 5f                       pop       edi
004acab6 5e                       pop       esi
004acab7 5b                       pop       ebx
004acab8 5d                       pop       ebp
004acab9 c21000                   ret       0x10
004acabc 8b4d0c                   mov       ecx, dword ptr [ebp + 0xc]
004acabf 8b5508                   mov       edx, dword ptr [ebp + 8]
004acac2 53                       push      ebx
004acac3 57                       push      edi
004acac4 51                       push      ecx
004acac5 52                       push      edx
004acac6 8bce                     mov       ecx, esi
004acac8 e8d3d5feff               call      0x49a0a0
004acacd 5f                       pop       edi
004acace 5e                       pop       esi
004acacf 5b                       pop       ebx
004acad0 5d                       pop       ebp
004acad1 c21000                   ret       0x10
004acad4 cc                       int3      
004acad5 cc                       int3      
004acad6 cc                       int3      
004acad7 cc                       int3      
004acad8 cc                       int3      
004acad9 cc                       int3      
004acada cc                       int3      
004acadb cc                       int3      
004acadc cc                       int3      
004acadd cc                       int3      
004acade cc                       int3      
004acadf cc                       int3      
