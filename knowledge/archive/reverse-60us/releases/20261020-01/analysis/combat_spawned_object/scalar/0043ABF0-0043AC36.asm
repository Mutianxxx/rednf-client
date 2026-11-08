0043abf0  55                       push       ebp
0043abf1  8bec                     mov        ebp, esp
0043abf3  8b4508                   mov        eax, dword ptr [ebp + 8]
0043abf6  83f8ff                   cmp        eax, -1
0043abf9  750b                     jne        0x43ac06
0043abfb  81c140100000             add        ecx, 0x1040
0043ac01  e85a74fcff               call       0x402060
0043ac06  83c0fc                   add        eax, -4
0043ac09  83f805                   cmp        eax, 5
0043ac0c  7714                     ja         0x43ac22
0043ac0e  0fb68030ac4300           movzx      eax, byte ptr [eax + 0x43ac30]
0043ac15  ff248528ac4300           jmp        dword ptr [eax*4 + 0x43ac28]
0043ac1c  b001                     mov        al, 1
0043ac1e  5d                       pop        ebp
0043ac1f  c20400                   ret        4
0043ac22  32c0                     xor        al, al
0043ac24  5d                       pop        ebp
0043ac25  c20400                   ret        4
0043ac28  1cac                     sbb        al, 0xac
0043ac2a  43                       inc        ebx
0043ac2b  0022                     add        byte ptr [edx], ah
0043ac2d  ac                       lodsb      al, byte ptr [esi]
0043ac2e  43                       inc        ebx
0043ac2f  0000                     add        byte ptr [eax], al
0043ac31  0100                     add        dword ptr [eax], eax
0043ac33  0001                     add        byte ptr [ecx], al
0043ac35  00                       .byte      0x00