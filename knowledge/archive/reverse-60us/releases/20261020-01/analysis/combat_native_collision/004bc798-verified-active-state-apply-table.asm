004bc798 ebad                     jmp       0x4bc747
004bc79a 4b                       dec       ebx
004bc79b 0016                     add       byte ptr [esi], dl
004bc79d af                       scasd     eax, dword ptr es:[edi]
004bc79e 4b                       dec       ebx
004bc79f 00ee                     add       dh, ch
004bc7a1 af                       scasd     eax, dword ptr es:[edi]
004bc7a2 4b                       dec       ebx
004bc7a3 0091b04b0049             add       byte ptr [ecx + 0x49004bb0], dl
004bc7a9 b24b                     mov       dl, 0x4b
004bc7ab 0076b9                   add       byte ptr [esi - 0x47], dh
004bc7ae 4b                       dec       ebx
004bc7af 00cc                     add       ah, cl
004bc7b1 ba4b003ac2               mov       edx, 0xc23a004b
004bc7b6 4b                       dec       ebx
004bc7b7 00b1c24b00fd             add       byte ptr [ecx - 0x2ffb43e], dh
004bc7bd c3                       ret       
004bc7be 4b                       dec       ebx
004bc7bf 00                       .byte     0x00
