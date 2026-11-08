007320db  83beec2e000002           cmp        dword ptr [esi + 0x2eec], 2
007320e2  0f858e000000             jne        0x732176
007320e8  8b06                     mov        eax, dword ptr [esi]
007320ea  6a00                     push       0
007320ec  6a00                     push       0
007320ee  6a0c                     push       0xc
007320f0  6aff                     push       -1
007320f2  6aff                     push       -1
007320f4  56                       push       esi
007320f5  6a06                     push       6
007320f7  8bce                     mov        ecx, esi
007320f9  ff904c060000             call       dword ptr [eax + 0x64c]
007320ff  8b16                     mov        edx, dword ptr [esi]
00732101  50                       push       eax
00732102  6a00                     push       0
00732104  6a06                     push       6
00732106  8bce                     mov        ecx, esi
00732108  ff927c060000             call       dword ptr [edx + 0x67c]
0073210e  8bc8                     mov        ecx, eax
00732110  e86bdfe1ff               call       0x550080
00732115  6a01                     push       1
00732117  8bcf                     mov        ecx, edi
00732119  8bd8                     mov        ebx, eax
0073211b  e87095faff               call       0x6db690
00732120  8b00                     mov        eax, dword ptr [eax]
00732122  8986f42e0000             mov        dword ptr [esi + 0x2ef4], eax
00732128  8b8ef02e0000             mov        ecx, dword ptr [esi + 0x2ef0]
0073212e  51                       push       ecx
0073212f  50                       push       eax
00732130  53                       push       ebx
00732131  6a00                     push       0
00732133  e8e81dd4ff               call       0x473f20
00732138  8dbe70020000             lea        edi, [esi + 0x270]
0073213e  83c410                   add        esp, 0x10
00732141  8bcf                     mov        ecx, edi
00732143  8bd8                     mov        ebx, eax
00732145  e816ffccff               call       0x402060
0073214a  8bc8                     mov        ecx, eax
0073214c  83c164                   add        ecx, 0x64
0073214f  83c364                   add        ebx, 0x64
00732152  0fafcb                   imul       ecx, ebx
00732155  b81f85eb51               mov        eax, 0x51eb851f
0073215a  f7e9                     imul       ecx
0073215c  c1fa05                   sar        edx, 5
0073215f  8bc2                     mov        eax, edx
00732161  c1e81f                   shr        eax, 0x1f
00732164  8d4c029c                 lea        ecx, [edx + eax - 0x64]
00732168  8d55f0                   lea        edx, [ebp - 0x10]
0073216b  894df0                   mov        dword ptr [ebp - 0x10], ecx
0073216e  52                       push       edx
0073216f  8bcf                     mov        ecx, edi
00732171  e8ea23cdff               call       0x404560
