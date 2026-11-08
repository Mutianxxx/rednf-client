00408722 55                       push ebp
00408723 89e5                     mov ebp, esp
00408725 53                       push ebx
00408726 56                       push esi
00408727 50                       push eax
00408728 2b5508                   sub edx, dword ptr [ebp + 8]
0040872B 89c8                     mov eax, ecx
0040872D 31c9                     xor ecx, ecx
0040872F 8d75f4                   lea esi, [ebp - 0xc]
00408732 89d3                     mov ebx, edx
00408734 d3eb                     shr ebx, cl
00408736 83c108                   add ecx, 8
00408739 881e                     mov byte ptr [esi], bl
0040873B 46                       inc esi
0040873C 83f920                   cmp ecx, 0x20
0040873F 75f1                     jne 0x408732
00408741 8b4df4                   mov ecx, dword ptr [ebp - 0xc]
00408744 8908                     mov dword ptr [eax], ecx
00408746 83c404                   add esp, 4
00408749 5e                       pop esi
0040874A 5b                       pop ebx
0040874B 5d                       pop ebp
0040874C c3                       ret 
