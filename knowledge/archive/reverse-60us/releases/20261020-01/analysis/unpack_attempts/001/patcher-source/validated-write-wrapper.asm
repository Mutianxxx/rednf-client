00407186 55                       push ebp
00407187 89e5                     mov ebp, esp
00407189 53                       push ebx
0040718A 57                       push edi
0040718B 56                       push esi
0040718C 83ec48                   sub esp, 0x48
0040718F 8b5d14                   mov ebx, dword ptr [ebp + 0x14]
00407192 8b7d0c                   mov edi, dword ptr [ebp + 0xc]
00407195 66be1000                 mov si, 0x10
00407199 39df                     cmp edi, ebx
0040719B 89d8                     mov eax, ebx
0040719D 0f47c7                   cmova eax, edi
004071A0 83f841                   cmp eax, 0x41
004071A3 7356                     jae 0x4071fb
004071A5 894df0                   mov dword ptr [ebp - 0x10], ecx
004071A8 8955ec                   mov dword ptr [ebp - 0x14], edx
004071AB 50                       push eax
004071AC 8d45ac                   lea eax, [ebp - 0x54]
004071AF 50                       push eax
004071B0 e8c9020000               call 0x40747e
004071B5 59                       pop ecx
004071B6 5a                       pop edx
004071B7 6685c0                   test ax, ax
004071BA 753d                     jne 0x4071f9
004071BC 8d4dac                   lea ecx, [ebp - 0x54]
004071BF 89da                     mov edx, ebx
004071C1 53                       push ebx
004071C2 ff7510                   push dword ptr [ebp + 0x10]
004071C5 e86e000000               call 0x407238
004071CA 59                       pop ecx
004071CB 5a                       pop edx
004071CC a801                     test al, 1
004071CE 7404                     je 0x4071d4
004071D0 31f6                     xor esi, esi
004071D2 eb27                     jmp 0x4071fb
004071D4 8d4dac                   lea ecx, [ebp - 0x54]
004071D7 89fa                     mov edx, edi
004071D9 57                       push edi
004071DA ff7508                   push dword ptr [ebp + 8]
004071DD e856000000               call 0x407238
004071E2 59                       pop ecx
004071E3 5a                       pop edx
004071E4 a801                     test al, 1
004071E6 7413                     je 0x4071fb
004071E8 8b4df0                   mov ecx, dword ptr [ebp - 0x10]
004071EB 8b55ec                   mov edx, dword ptr [ebp - 0x14]
004071EE 53                       push ebx
004071EF ff7510                   push dword ptr [ebp + 0x10]
004071F2 e80e000000               call 0x407205
004071F7 59                       pop ecx
004071F8 5a                       pop edx
004071F9 89c6                     mov esi, eax
004071FB 89f0                     mov eax, esi
004071FD 83c448                   add esp, 0x48
00407200 5e                       pop esi
00407201 5f                       pop edi
00407202 5b                       pop ebx
00407203 5d                       pop ebp
00407204 c3                       ret 
