004bd649 8b16                     mov       edx, dword ptr [esi]
004bd64b 6811020000               push      0x211
004bd650 8bce                     mov       ecx, esi
004bd652 ff522c                   call      dword ptr [edx + 0x2c]
004bd655 84c0                     test      al, al
004bd657 0f84a3030000             je        0x4bda00
004bd65d 8b06                     mov       eax, dword ptr [esi]
004bd65f 8bce                     mov       ecx, esi
004bd661 ff90a0050000             call      dword ptr [eax + 0x5a0]
004bd667 84c0                     test      al, al
004bd669 0f8591030000             jne       0x4bda00
004bd66f 8b0d48280001             mov       ecx, dword ptr [0x1002848]
004bd675 83b9a819000002           cmp       dword ptr [ecx + 0x19a8], 2
004bd67c 0f847e030000             je        0x4bda00
004bd682 8b8ef8000000             mov       ecx, dword ptr [esi + 0xf8]
004bd688 6a00                     push      0
004bd68a 6a02                     push      2
004bd68c e8af390500               call      0x511040
004bd691 e96a030000               jmp       0x4bda00
