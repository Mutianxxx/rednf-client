0049cf70 56                       push      esi
0049cf71 8bf1                     mov       esi, ecx
0049cf73 e858ceffff               call      0x499dd0
0049cf78 8a86f4010000             mov       al, byte ptr [esi + 0x1f4]
0049cf7e 84c0                     test      al, al
0049cf80 740b                     je        0x49cf8d
0049cf82 8b06                     mov       eax, dword ptr [esi]
0049cf84 8bce                     mov       ecx, esi
0049cf86 5e                       pop       esi
0049cf87 ffa068030000             jmp       dword ptr [eax + 0x368]
0049cf8d 5e                       pop       esi
0049cf8e c3                       ret       
0049cf8f cc                       int3      
0049cf90 55                       push      ebp
0049cf91 8bec                     mov       ebp, esp
0049cf93 53                       push      ebx
0049cf94 56                       push      esi
0049cf95 8bd9                     mov       ebx, ecx
0049cf97 8b8314080000             mov       eax, dword ptr [ebx + 0x814]
0049cf9d 57                       push      edi
0049cf9e 50                       push      eax
0049cf9f e8e2427600               call      0xc01286
0049cfa4 8b750c                   mov       esi, dword ptr [ebp + 0xc]
0049cfa7 56                       push      esi
0049cfa8 c7831408000000000000     mov       dword ptr [ebx + 0x814], 0
0049cfb2 e80a0a7500               call      0xbed9c1
0049cfb7 8bce                     mov       ecx, esi
0049cfb9 8b7508                   mov       esi, dword ptr [ebp + 8]
0049cfbc 8bd1                     mov       edx, ecx
0049cfbe c1e902                   shr       ecx, 2
0049cfc1 898314080000             mov       dword ptr [ebx + 0x814], eax
0049cfc7 8bf8                     mov       edi, eax
0049cfc9 f3a5                     rep movsd dword ptr es:[edi], dword ptr [esi]
0049cfcb 83c408                   add       esp, 8
0049cfce 8bca                     mov       ecx, edx
0049cfd0 83e103                   and       ecx, 3
0049cfd3 f3a4                     rep movsb byte ptr es:[edi], byte ptr [esi]
0049cfd5 5f                       pop       edi
0049cfd6 8bc2                     mov       eax, edx
0049cfd8 5e                       pop       esi
0049cfd9 898310080000             mov       dword ptr [ebx + 0x810], eax
0049cfdf 5b                       pop       ebx
0049cfe0 5d                       pop       ebp
0049cfe1 c20800                   ret       8
0049cfe4 cc                       int3      
0049cfe5 cc                       int3      
0049cfe6 cc                       int3      
0049cfe7 cc                       int3      
0049cfe8 cc                       int3      
0049cfe9 cc                       int3      
0049cfea cc                       int3      
0049cfeb cc                       int3      
0049cfec cc                       int3      
0049cfed cc                       int3      
0049cfee cc                       int3      
0049cfef cc                       int3      
