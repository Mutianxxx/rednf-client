005c8660 55                       push      ebp
005c8661 8bec                     mov       ebp, esp
005c8663 6aff                     push      -1
005c8665 68443bc600               push      0xc63b44
005c866a 64a100000000             mov       eax, dword ptr fs:[0]
005c8670 50                       push      eax
005c8671 64892500000000           mov       dword ptr fs:[0], esp
005c8678 51                       push      ecx
005c8679 8b450c                   mov       eax, dword ptr [ebp + 0xc]
005c867c 56                       push      esi
005c867d 8bf1                     mov       esi, ecx
005c867f 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005c8682 50                       push      eax
005c8683 51                       push      ecx
005c8684 8bce                     mov       ecx, esi
005c8686 8975f0                   mov       dword ptr [ebp - 0x10], esi
005c8689 e89280ecff               call      0x490720
005c868e 33c0                     xor       eax, eax
005c8690 c706f410cf00             mov       dword ptr [esi], 0xcf10f4
005c8696 8945fc                   mov       dword ptr [ebp - 4], eax
005c8699 898694080000             mov       dword ptr [esi + 0x894], eax
005c869f 898698080000             mov       dword ptr [esi + 0x898], eax
005c86a5 89869c080000             mov       dword ptr [esi + 0x89c], eax
005c86ab 8986a4080000             mov       dword ptr [esi + 0x8a4], eax
005c86b1 8986a8080000             mov       dword ptr [esi + 0x8a8], eax
005c86b7 8986ac080000             mov       dword ptr [esi + 0x8ac], eax
005c86bd 8bce                     mov       ecx, esi
005c86bf c645fc02                 mov       byte ptr [ebp - 4], 2
005c86c3 e868aa0200               call      0x5f3130
005c86c8 8bce                     mov       ecx, esi
005c86ca e8a1b00200               call      0x5f3770
005c86cf 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005c86d2 8bc6                     mov       eax, esi
005c86d4 5e                       pop       esi
005c86d5 64890d00000000           mov       dword ptr fs:[0], ecx
005c86dc 8be5                     mov       esp, ebp
005c86de 5d                       pop       ebp
005c86df c20800                   ret       8
