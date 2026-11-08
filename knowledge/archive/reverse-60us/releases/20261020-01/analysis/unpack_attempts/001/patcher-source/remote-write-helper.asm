00407205 55                       push ebp
00407206 89e5                     mov ebp, esp
00407208 53                       push ebx
00407209 57                       push edi
0040720A 56                       push esi
0040720B 8b5d0c                   mov ebx, dword ptr [ebp + 0xc]
0040720E 89d7                     mov edi, edx
00407210 89ce                     mov esi, ecx
00407212 6a00                     push 0
00407214 53                       push ebx
00407215 ff7508                   push dword ptr [ebp + 8]
00407218 52                       push edx
00407219 51                       push ecx
0040721A e82bd90200               call 0x434b4a
0040721F 85c0                     test eax, eax
00407221 740c                     je 0x40722f
00407223 53                       push ebx
00407224 57                       push edi
00407225 56                       push esi
00407226 e8a7d80200               call 0x434ad2
0040722B 31c0                     xor eax, eax
0040722D eb04                     jmp 0x407233
0040722F 66b81000                 mov ax, 0x10
00407233 5e                       pop esi
00407234 5f                       pop edi
00407235 5b                       pop ebx
00407236 5d                       pop ebp
00407237 c3                       ret 
