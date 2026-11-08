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
005c86e2 cc                       int3      
005c86e3 cc                       int3      
005c86e4 cc                       int3      
005c86e5 cc                       int3      
005c86e6 cc                       int3      
005c86e7 cc                       int3      
005c86e8 cc                       int3      
005c86e9 cc                       int3      
005c86ea cc                       int3      
005c86eb cc                       int3      
005c86ec cc                       int3      
005c86ed cc                       int3      
005c86ee cc                       int3      
005c86ef cc                       int3      
005c86f0 ff8174080000             inc       dword ptr [ecx + 0x874]
005c86f6 c3                       ret       
005c86f7 cc                       int3      
005c86f8 cc                       int3      
005c86f9 cc                       int3      
005c86fa cc                       int3      
005c86fb cc                       int3      
005c86fc cc                       int3      
005c86fd cc                       int3      
005c86fe cc                       int3      
005c86ff cc                       int3      
005c8700 55                       push      ebp
005c8701 8bec                     mov       ebp, esp
005c8703 56                       push      esi
005c8704 8bf1                     mov       esi, ecx
005c8706 e825000000               call      0x5c8730
005c870b f6450801                 test      byte ptr [ebp + 8], 1
005c870f 7409                     je        0x5c871a
005c8711 56                       push      esi
005c8712 e83998e3ff               call      0x401f50
005c8717 83c404                   add       esp, 4
005c871a 8bc6                     mov       eax, esi
005c871c 5e                       pop       esi
005c871d 5d                       pop       ebp
005c871e c20400                   ret       4
005c8721 cc                       int3      
005c8722 cc                       int3      
005c8723 cc                       int3      
005c8724 cc                       int3      
005c8725 cc                       int3      
005c8726 cc                       int3      
005c8727 cc                       int3      
005c8728 cc                       int3      
005c8729 cc                       int3      
005c872a cc                       int3      
005c872b cc                       int3      
005c872c cc                       int3      
005c872d cc                       int3      
005c872e cc                       int3      
005c872f cc                       int3      
005c8730 55                       push      ebp
005c8731 8bec                     mov       ebp, esp
005c8733 6aff                     push      -1
005c8735 68443bc600               push      0xc63b44
005c873a 64a100000000             mov       eax, dword ptr fs:[0]
005c8740 50                       push      eax
005c8741 64892500000000           mov       dword ptr fs:[0], esp
005c8748 51                       push      ecx
005c8749 56                       push      esi
005c874a 8bf1                     mov       esi, ecx
005c874c 57                       push      edi
005c874d 8975f0                   mov       dword ptr [ebp - 0x10], esi
005c8750 c706f410cf00             mov       dword ptr [esi], 0xcf10f4
005c8756 c745fc02000000           mov       dword ptr [ebp - 4], 2
005c875d e81eab0200               call      0x5f3280
005c8762 8b86a4080000             mov       eax, dword ptr [esi + 0x8a4]
005c8768 33ff                     xor       edi, edi
005c876a 3bc7                     cmp       eax, edi
005c876c 7409                     je        0x5c8777
005c876e 50                       push      eax
005c876f e869786300               call      0xbfffdd
005c8774 83c404                   add       esp, 4
005c8777 89bea4080000             mov       dword ptr [esi + 0x8a4], edi
005c877d 89bea8080000             mov       dword ptr [esi + 0x8a8], edi
005c8783 89beac080000             mov       dword ptr [esi + 0x8ac], edi
005c8789 8b8694080000             mov       eax, dword ptr [esi + 0x894]
005c878f 3bc7                     cmp       eax, edi
005c8791 7409                     je        0x5c879c
005c8793 50                       push      eax
005c8794 e844786300               call      0xbfffdd
005c8799 83c404                   add       esp, 4
005c879c 8bce                     mov       ecx, esi
005c879e 89be94080000             mov       dword ptr [esi + 0x894], edi
005c87a4 89be98080000             mov       dword ptr [esi + 0x898], edi
005c87aa 89be9c080000             mov       dword ptr [esi + 0x89c], edi
