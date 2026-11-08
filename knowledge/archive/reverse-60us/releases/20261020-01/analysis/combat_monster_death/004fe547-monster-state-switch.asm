004fe547 8b4508                   mov       eax, dword ptr [ebp + 8]
004fe54a 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
004fe54d 83c0fd                   add       eax, -3
004fe550 83f80a                   cmp       eax, 0xa
004fe553 0f8735060000             ja        0x4feb8e
004fe559 0fb68880ef4f00           movzx     ecx, byte ptr [eax + 0x4fef80]
004fe560 ff248d68ef4f00           jmp       dword ptr [ecx*4 + 0x4fef68]
