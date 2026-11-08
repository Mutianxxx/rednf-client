005e14e0 55                       push      ebp
005e14e1 8bec                     mov       ebp, esp
005e14e3 8a4508                   mov       al, byte ptr [ebp + 8]
005e14e6 888184010000             mov       byte ptr [ecx + 0x184], al
005e14ec 5d                       pop       ebp
005e14ed c20400                   ret       4
