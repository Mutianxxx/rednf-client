0040747E 55                       push ebp
0040747F 89e5                     mov ebp, esp
00407481 6a00                     push 0
00407483 ff750c                   push dword ptr [ebp + 0xc]
00407486 ff7508                   push dword ptr [ebp + 8]
00407489 52                       push edx
0040748A 51                       push ecx
0040748B e884d60200               call 0x434b14
00407490 31c9                     xor ecx, ecx
00407492 85c0                     test eax, eax
00407494 6a11                     push 0x11
00407496 58                       pop eax
00407497 0f45c1                   cmovne eax, ecx
0040749A 5d                       pop ebp
0040749B c3                       ret 
