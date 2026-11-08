004d9040  55                       push       ebp
004d9041  8bec                     mov        ebp, esp
004d9043  6aff                     push       -1
004d9045  680f86c500               push       0xc5860f
004d904a  64a100000000             mov        eax, dword ptr fs:[0]
004d9050  50                       push       eax
004d9051  64892500000000           mov        dword ptr fs:[0], esp
004d9058  81ec30040000             sub        esp, 0x430
004d905e  56                       push       esi
004d905f  8bf1                     mov        esi, ecx
004d9061  c745e800000000           mov        dword ptr [ebp - 0x18], 0
004d9068  e82330fcff               call       0x49c090
004d906d  84c0                     test       al, al
004d906f  0f84f8060000             je         0x4d976d
004d9075  83beb001000002           cmp        dword ptr [esi + 0x1b0], 2
004d907c  0f84eb060000             je         0x4d976d
004d9082  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004d9085  8b06                     mov        eax, dword ptr [esi]
004d9087  53                       push       ebx
004d9088  51                       push       ecx
004d9089  8bce                     mov        ecx, esi
004d908b  ff907c060000             call       dword ptr [eax + 0x67c]
004d9091  8bd8                     mov        ebx, eax
004d9093  85db                     test       ebx, ebx
004d9095  895dec                   mov        dword ptr [ebp - 0x14], ebx
004d9098  7514                     jne        0x4d90ae
004d909a  5b                       pop        ebx
004d909b  32c0                     xor        al, al
004d909d  5e                       pop        esi
004d909e  8b4df4                   mov        ecx, dword ptr [ebp - 0xc]
004d90a1  64890d00000000           mov        dword ptr fs:[0], ecx
004d90a8  8be5                     mov        esp, ebp
004d90aa  5d                       pop        ebp
004d90ab  c21000                   ret        0x10
004d90ae  8d8b1c030000             lea        ecx, [ebx + 0x31c]
004d90b4  e8a78ff2ff               call       0x402060
004d90b9  85c0                     test       eax, eax
004d90bb  8945c4                   mov        dword ptr [ebp - 0x3c], eax
004d90be  c645f301                 mov        byte ptr [ebp - 0xd], 1
004d90c2  74d6                     je         0x4d909a
004d90c4  8b0d48280001             mov        ecx, dword ptr [0x1002848]
004d90ca  e80115f6ff               call       0x43a5d0
004d90cf  84c0                     test       al, al
004d90d1  740b                     je         0x4d90de
004d90d3  8bcb                     mov        ecx, ebx
004d90d5  e8d6990000               call       0x4e2ab0
004d90da  84c0                     test       al, al
004d90dc  75bc                     jne        0x4d909a
004d90de  8b16                     mov        edx, dword ptr [esi]
004d90e0  8bce                     mov        ecx, esi
004d90e2  ff5234                   call       dword ptr [edx + 0x34]
004d90e5  84c0                     test       al, al
004d90e7  7404                     je         0x4d90ed
004d90e9  c6450c00                 mov        byte ptr [ebp + 0xc], 0
004d90ed  57                       push       edi
004d90ee  6aff                     push       -1
004d90f0  56                       push       esi
004d90f1  8bcb                     mov        ecx, ebx
004d90f3  e8c89b0000               call       0x4e2cc0
004d90f8  8bf8                     mov        edi, eax
004d90fa  8b06                     mov        eax, dword ptr [esi]
004d90fc  8bce                     mov        ecx, esi
004d90fe  897ddc                   mov        dword ptr [ebp - 0x24], edi
004d9101  ff5034                   call       dword ptr [eax + 0x34]
004d9104  84c0                     test       al, al
004d9106  7564                     jne        0x4d916c
004d9108  85ff                     test       edi, edi
004d910a  7460                     je         0x4d916c
004d910c  8b4d08                   mov        ecx, dword ptr [ebp + 8]
004d910f  51                       push       ecx
004d9110  8bce                     mov        ecx, esi
004d9112  e8e9a80000               call       0x4e3a00
004d9117  3bc7                     cmp        eax, edi
004d9119  7c51                     jl         0x4d916c
004d911b  8a450c                   mov        al, byte ptr [ebp + 0xc]
004d911e  84c0                     test       al, al
004d9120  7446                     je         0x4d9168
004d9122  8b16                     mov        edx, dword ptr [esi]
004d9124  8bce                     mov        ecx, esi
004d9126  ff5234                   call       dword ptr [edx + 0x34]
004d9129  84c0                     test       al, al
004d912b  7528                     jne        0x4d9155
004d912d  a16c310001               mov        eax, dword ptr [0x100316c]
004d9132  8b7864                   mov        edi, dword ptr [eax + 0x64]
004d9135  6a00                     push       0
004d9137  6a00                     push       0
004d9139  6a10                     push       0x10
004d913b  68e6c89bff               push       0xff9bc8e6
004d9140  680d0e0000               push       0xe0d
004d9145  e8f6805700               call       0xa51240
004d914a  83c404                   add        esp, 4
004d914d  50                       push       eax
004d914e  8bcf                     mov        ecx, edi
004d9150  e8bb354e00               call       0x9bc710
004d9155  6a00                     push       0
004d9157  6a00                     push       0
004d9159  6aff                     push       -1
004d915b  6874c2cc00               push       0xccc274
004d9160  e84be8f6ff               call       0x4479b0
004d9165  83c410                   add        esp, 0x10
004d9168  c645f300                 mov        byte ptr [ebp - 0xd], 0
004d916c  8bcb                     mov        ecx, ebx
004d916e  e84d680700               call       0x54f9c0
004d9173  84c0                     test       al, al
004d9175  745b                     je         0x4d91d2
004d9177  8a450c                   mov        al, byte ptr [ebp + 0xc]
004d917a  84c0                     test       al, al
004d917c  7450                     je         0x4d91ce
004d917e  8b16                     mov        edx, dword ptr [esi]
004d9180  8bce                     mov        ecx, esi
004d9182  ff5234                   call       dword ptr [edx + 0x34]
004d9185  84c0                     test       al, al
004d9187  7528                     jne        0x4d91b1
004d9189  a16c310001               mov        eax, dword ptr [0x100316c]
004d918e  8b7864                   mov        edi, dword ptr [eax + 0x64]
004d9191  6a00                     push       0
004d9193  6a00                     push       0
004d9195  6a10                     push       0x10
004d9197  68e6c89bff               push       0xff9bc8e6
004d919c  6855030000               push       0x355
004d91a1  e89a805700               call       0xa51240
004d91a6  83c404                   add        esp, 4
004d91a9  50                       push       eax
004d91aa  8bcf                     mov        ecx, edi
004d91ac  e85f354e00               call       0x9bc710
004d91b1  6a00                     push       0
004d91b3  6a00                     push       0
004d91b5  6aff                     push       -1
004d91b7  6874c2cc00               push       0xccc274
004d91bc  e8efe7f6ff               call       0x4479b0
004d91c1  8b16                     mov        edx, dword ptr [esi]
004d91c3  83c410                   add        esp, 0x10
004d91c6  8bce                     mov        ecx, esi
004d91c8  ff9268060000             call       dword ptr [edx + 0x668]
004d91ce  c645f300                 mov        byte ptr [ebp - 0xd], 0
004d91d2  8a4510                   mov        al, byte ptr [ebp + 0x10]
004d91d5  84c0                     test       al, al
004d91d7  0f84a9000000             je         0x4d9286
004d91dd  8d8e38120000             lea        ecx, [esi + 0x1238]
004d91e3  e8788ef2ff               call       0x402060
004d91e8  6aff                     push       -1
004d91ea  56                       push       esi
004d91eb  8bcb                     mov        ecx, ebx
004d91ed  8bf8                     mov        edi, eax
004d91ef  e81c7c0700               call       0x550e10
004d91f4  3bf8                     cmp        edi, eax
004d91f6  0f8d8a000000             jge        0x4d9286
004d91fc  8a450c                   mov        al, byte ptr [ebp + 0xc]
004d91ff  84                       .byte      0x84