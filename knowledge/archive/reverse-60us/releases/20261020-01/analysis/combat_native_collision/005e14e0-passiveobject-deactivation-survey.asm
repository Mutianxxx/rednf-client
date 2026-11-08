005e14e0 55                       push      ebp
005e14e1 8bec                     mov       ebp, esp
005e14e3 8a4508                   mov       al, byte ptr [ebp + 8]
005e14e6 888184010000             mov       byte ptr [ecx + 0x184], al
005e14ec 5d                       pop       ebp
005e14ed c20400                   ret       4
005e14f0 55                       push      ebp
005e14f1 8bec                     mov       ebp, esp
005e14f3 56                       push      esi
005e14f4 8bf1                     mov       esi, ecx
005e14f6 e825000000               call      0x5e1520
005e14fb f6450801                 test      byte ptr [ebp + 8], 1
005e14ff 74                       .byte     0x74
