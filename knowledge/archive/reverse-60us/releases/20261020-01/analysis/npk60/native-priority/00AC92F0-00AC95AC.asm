00ac92f0  55                       push       ebp
00ac92f1  8bec                     mov        ebp, esp
00ac92f3  83ec08                   sub        esp, 8
00ac92f6  53                       push       ebx
00ac92f7  8b5d10                   mov        ebx, dword ptr [ebp + 0x10]
00ac92fa  56                       push       esi
00ac92fb  57                       push       edi
00ac92fc  8bf1                     mov        esi, ecx
00ac92fe  53                       push       ebx
00ac92ff  8975fc                   mov        dword ptr [ebp - 4], esi
00ac9302  c745f800000000           mov        dword ptr [ebp - 8], 0
00ac9309  e8bf6a1300               call       0xbffdcd
00ac930e  83c404                   add        esp, 4
00ac9311  48                       dec        eax
00ac9312  7810                     js         0xac9324
00ac9314  66833c435c               cmp        word ptr [ebx + eax*2], 0x5c
00ac9319  7506                     jne        0xac9321
00ac931b  66c704432f00             mov        word ptr [ebx + eax*2], 0x2f
00ac9321  48                       dec        eax
00ac9322  79f0                     jns        0xac9314
00ac9324  53                       push       ebx
00ac9325  e8a60f0400               call       0xb0a2d0
00ac932a  8b4604                   mov        eax, dword ptr [esi + 4]
00ac932d  8b30                     mov        esi, dword ptr [eax]
00ac932f  83c404                   add        esp, 4
00ac9332  3bf0                     cmp        esi, eax
00ac9334  7419                     je         0xac934f
00ac9336  53                       push       ebx
00ac9337  8d4e28                   lea        ecx, [esi + 0x28]
00ac933a  e8e1feffff               call       0xac9220
00ac933f  8bf8                     mov        edi, eax
00ac9341  85ff                     test       edi, edi
00ac9343  7542                     jne        0xac9387
00ac9345  8b45fc                   mov        eax, dword ptr [ebp - 4]
00ac9348  8b36                     mov        esi, dword ptr [esi]
00ac934a  3b7004                   cmp        esi, dword ptr [eax + 4]
00ac934d  75e7                     jne        0xac9336
00ac934f  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac9352  33c0                     xor        eax, eax
00ac9354  c7461807000000           mov        dword ptr [esi + 0x18], 7
00ac935b  894614                   mov        dword ptr [esi + 0x14], eax
00ac935e  68e0baca00               push       0xcabae0
00ac9363  66894604                 mov        word ptr [esi + 4], ax
00ac9367  e8616a1300               call       0xbffdcd
00ac936c  83c404                   add        esp, 4
00ac936f  50                       push       eax
00ac9370  68e0baca00               push       0xcabae0
00ac9375  8bce                     mov        ecx, esi
00ac9377  e8049b93ff               call       0x402e80
00ac937c  5f                       pop        edi
00ac937d  8bc6                     mov        eax, esi
00ac937f  5e                       pop        esi
00ac9380  5b                       pop        ebx
00ac9381  8be5                     mov        esp, ebp
00ac9383  5d                       pop        ebp
00ac9384  c20c00                   ret        0xc
00ac9387  8b4608                   mov        eax, dword ptr [esi + 8]
00ac938a  85c0                     test       eax, eax
00ac938c  8b0f                     mov        ecx, dword ptr [edi]
00ac938e  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00ac9391  8d5e08                   lea        ebx, [esi + 8]
00ac9394  890a                     mov        dword ptr [edx], ecx
00ac9396  743a                     je         0xac93d2
00ac9398  8b0f                     mov        ecx, dword ptr [edi]
00ac939a  6a00                     push       0
00ac939c  51                       push       ecx
00ac939d  50                       push       eax
00ac939e  e811931300               call       0xc026b4
00ac93a3  83c40c                   add        esp, 0xc
00ac93a6  33c9                     xor        ecx, ecx
00ac93a8  8d460c                   lea        eax, [esi + 0xc]
00ac93ab  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac93ae  6aff                     push       -1
00ac93b0  894e14                   mov        dword ptr [esi + 0x14], ecx
00ac93b3  51                       push       ecx
00ac93b4  c7461807000000           mov        dword ptr [esi + 0x18], 7
00ac93bb  66894e04                 mov        word ptr [esi + 4], cx
00ac93bf  50                       push       eax
00ac93c0  8bce                     mov        ecx, esi
00ac93c2  e8999993ff               call       0x402d60
00ac93c7  5f                       pop        edi
00ac93c8  8bc6                     mov        eax, esi
00ac93ca  5e                       pop        esi
00ac93cb  5b                       pop        ebx
00ac93cc  8be5                     mov        esp, ebp
00ac93ce  5d                       pop        ebp
00ac93cf  c20c00                   ret        0xc
00ac93d2  85db                     test       ebx, ebx
00ac93d4  0f8475ffffff             je         0xac934f
00ac93da  8b4b1c                   mov        ecx, dword ptr [ebx + 0x1c]
00ac93dd  83f908                   cmp        ecx, 8
00ac93e0  8d4304                   lea        eax, [ebx + 4]
00ac93e3  894510                   mov        dword ptr [ebp + 0x10], eax
00ac93e6  7205                     jb         0xac93ed
00ac93e8  8b4004                   mov        eax, dword ptr [eax + 4]
00ac93eb  eb03                     jmp        0xac93f0
00ac93ed  83c004                   add        eax, 4
00ac93f0  68a036e100               push       0xe136a0
00ac93f5  50                       push       eax
00ac93f6  e82e891300               call       0xc01d29
00ac93fb  8bf0                     mov        esi, eax
00ac93fd  83c408                   add        esp, 8
00ac9400  85f6                     test       esi, esi
00ac9402  0f8447ffffff             je         0xac934f
00ac9408  8b17                     mov        edx, dword ptr [edi]
00ac940a  6a00                     push       0
00ac940c  52                       push       edx
00ac940d  56                       push       esi
00ac940e  e8a1921300               call       0xc026b4
00ac9413  8933                     mov        dword ptr [ebx], esi
00ac9415  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac9418  83c40c                   add        esp, 0xc
00ac941b  33c0                     xor        eax, eax
00ac941d  6aff                     push       -1
00ac941f  894614                   mov        dword ptr [esi + 0x14], eax
00ac9422  c7461807000000           mov        dword ptr [esi + 0x18], 7
00ac9429  50                       push       eax
00ac942a  66894604                 mov        word ptr [esi + 4], ax
00ac942e  8b4510                   mov        eax, dword ptr [ebp + 0x10]
00ac9431  50                       push       eax
00ac9432  8bce                     mov        ecx, esi
00ac9434  e8279993ff               call       0x402d60
00ac9439  5f                       pop        edi
00ac943a  8bc6                     mov        eax, esi
00ac943c  5e                       pop        esi
00ac943d  5b                       pop        ebx
00ac943e  8be5                     mov        esp, ebp
00ac9440  5d                       pop        ebp
00ac9441  c20c00                   ret        0xc
00ac9444  cc                       int3       
00ac9445  cc                       int3       
00ac9446  cc                       int3       
00ac9447  cc                       int3       
00ac9448  cc                       int3       
00ac9449  cc                       int3       
00ac944a  cc                       int3       
00ac944b  cc                       int3       
00ac944c  cc                       int3       
00ac944d  cc                       int3       
00ac944e  cc                       int3       
00ac944f  cc                       int3       
00ac9450  55                       push       ebp
00ac9451  8bec                     mov        ebp, esp
00ac9453  83ec08                   sub        esp, 8
00ac9456  53                       push       ebx
00ac9457  8b5d14                   mov        ebx, dword ptr [ebp + 0x14]
00ac945a  56                       push       esi
00ac945b  57                       push       edi
00ac945c  8bf1                     mov        esi, ecx
00ac945e  53                       push       ebx
00ac945f  8975fc                   mov        dword ptr [ebp - 4], esi
00ac9462  c745f800000000           mov        dword ptr [ebp - 8], 0
00ac9469  e85f691300               call       0xbffdcd
00ac946e  83c404                   add        esp, 4
00ac9471  48                       dec        eax
00ac9472  7810                     js         0xac9484
00ac9474  66833c435c               cmp        word ptr [ebx + eax*2], 0x5c
00ac9479  7506                     jne        0xac9481
00ac947b  66c704432f00             mov        word ptr [ebx + eax*2], 0x2f
00ac9481  48                       dec        eax
00ac9482  79f0                     jns        0xac9474
00ac9484  53                       push       ebx
00ac9485  e8460e0400               call       0xb0a2d0
00ac948a  8b4604                   mov        eax, dword ptr [esi + 4]
00ac948d  8b30                     mov        esi, dword ptr [eax]
00ac948f  83c404                   add        esp, 4
00ac9492  3bf0                     cmp        esi, eax
00ac9494  7419                     je         0xac94af
00ac9496  53                       push       ebx
00ac9497  8d4e28                   lea        ecx, [esi + 0x28]
00ac949a  e881fdffff               call       0xac9220
00ac949f  8bf8                     mov        edi, eax
00ac94a1  85ff                     test       edi, edi
00ac94a3  7542                     jne        0xac94e7
00ac94a5  8b45fc                   mov        eax, dword ptr [ebp - 4]
00ac94a8  8b36                     mov        esi, dword ptr [esi]
00ac94aa  3b7004                   cmp        esi, dword ptr [eax + 4]
00ac94ad  75e7                     jne        0xac9496
00ac94af  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac94b2  33c0                     xor        eax, eax
00ac94b4  c7461807000000           mov        dword ptr [esi + 0x18], 7
00ac94bb  894614                   mov        dword ptr [esi + 0x14], eax
00ac94be  68e0baca00               push       0xcabae0
00ac94c3  66894604                 mov        word ptr [esi + 4], ax
00ac94c7  e801691300               call       0xbffdcd
00ac94cc  83c404                   add        esp, 4
00ac94cf  50                       push       eax
00ac94d0  68e0baca00               push       0xcabae0
00ac94d5  8bce                     mov        ecx, esi
00ac94d7  e8a49993ff               call       0x402e80
00ac94dc  5f                       pop        edi
00ac94dd  8bc6                     mov        eax, esi
00ac94df  5e                       pop        esi
00ac94e0  5b                       pop        ebx
00ac94e1  8be5                     mov        esp, ebp
00ac94e3  5d                       pop        ebp
00ac94e4  c21000                   ret        0x10
00ac94e7  8b0f                     mov        ecx, dword ptr [edi]
00ac94e9  8b4608                   mov        eax, dword ptr [esi + 8]
00ac94ec  85c0                     test       eax, eax
00ac94ee  8b550c                   mov        edx, dword ptr [ebp + 0xc]
00ac94f1  8d5e08                   lea        ebx, [esi + 8]
00ac94f4  890a                     mov        dword ptr [edx], ecx
00ac94f6  8b4f04                   mov        ecx, dword ptr [edi + 4]
00ac94f9  8b5510                   mov        edx, dword ptr [ebp + 0x10]
00ac94fc  890a                     mov        dword ptr [edx], ecx
00ac94fe  743a                     je         0xac953a
00ac9500  8b0f                     mov        ecx, dword ptr [edi]
00ac9502  6a00                     push       0
00ac9504  51                       push       ecx
00ac9505  50                       push       eax
00ac9506  e8a9911300               call       0xc026b4
00ac950b  83c40c                   add        esp, 0xc
00ac950e  33c9                     xor        ecx, ecx
00ac9510  8d460c                   lea        eax, [esi + 0xc]
00ac9513  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac9516  6aff                     push       -1
00ac9518  894e14                   mov        dword ptr [esi + 0x14], ecx
00ac951b  51                       push       ecx
00ac951c  c7461807000000           mov        dword ptr [esi + 0x18], 7
00ac9523  66894e04                 mov        word ptr [esi + 4], cx
00ac9527  50                       push       eax
00ac9528  8bce                     mov        ecx, esi
00ac952a  e8319893ff               call       0x402d60
00ac952f  5f                       pop        edi
00ac9530  8bc6                     mov        eax, esi
00ac9532  5e                       pop        esi
00ac9533  5b                       pop        ebx
00ac9534  8be5                     mov        esp, ebp
00ac9536  5d                       pop        ebp
00ac9537  c21000                   ret        0x10
00ac953a  85db                     test       ebx, ebx
00ac953c  0f846dffffff             je         0xac94af
00ac9542  8b4b1c                   mov        ecx, dword ptr [ebx + 0x1c]
00ac9545  83f908                   cmp        ecx, 8
00ac9548  8d4304                   lea        eax, [ebx + 4]
00ac954b  894514                   mov        dword ptr [ebp + 0x14], eax
00ac954e  7205                     jb         0xac9555
00ac9550  8b4004                   mov        eax, dword ptr [eax + 4]
00ac9553  eb03                     jmp        0xac9558
00ac9555  83c004                   add        eax, 4
00ac9558  68a036e100               push       0xe136a0
00ac955d  50                       push       eax
00ac955e  e8c6871300               call       0xc01d29
00ac9563  8bf0                     mov        esi, eax
00ac9565  83c408                   add        esp, 8
00ac9568  85f6                     test       esi, esi
00ac956a  0f843fffffff             je         0xac94af
00ac9570  8b17                     mov        edx, dword ptr [edi]
00ac9572  6a00                     push       0
00ac9574  52                       push       edx
00ac9575  56                       push       esi
00ac9576  e839911300               call       0xc026b4
00ac957b  8933                     mov        dword ptr [ebx], esi
00ac957d  8b7508                   mov        esi, dword ptr [ebp + 8]
00ac9580  83c40c                   add        esp, 0xc
00ac9583  33c0                     xor        eax, eax
00ac9585  6aff                     push       -1
00ac9587  894614                   mov        dword ptr [esi + 0x14], eax
00ac958a  c7461807000000           mov        dword ptr [esi + 0x18], 7
00ac9591  50                       push       eax
00ac9592  66894604                 mov        word ptr [esi + 4], ax
00ac9596  8b4514                   mov        eax, dword ptr [ebp + 0x14]
00ac9599  50                       push       eax
00ac959a  8bce                     mov        ecx, esi
00ac959c  e8bf9793ff               call       0x402d60
00ac95a1  5f                       pop        edi
00ac95a2  8bc6                     mov        eax, esi
00ac95a4  5e                       pop        esi
00ac95a5  5b                       pop        ebx
00ac95a6  8be5                     mov        esp, ebp
00ac95a8  5d                       pop        ebp
00ac95a9  c21000                   ret        0x10