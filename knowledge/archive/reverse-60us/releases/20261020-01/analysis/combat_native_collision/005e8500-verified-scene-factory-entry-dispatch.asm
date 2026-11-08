005e8500 55                       push      ebp
005e8501 8bec                     mov       ebp, esp
005e8503 64a100000000             mov       eax, dword ptr fs:[0]
005e8509 6aff                     push      -1
005e850b 68c774c600               push      0xc674c7
005e8510 50                       push      eax
005e8511 64892500000000           mov       dword ptr fs:[0], esp
005e8518 56                       push      esi
005e8519 8b7508                   mov       esi, dword ptr [ebp + 8]
005e851c 81feee590000             cmp       esi, 0x59ee
005e8522 0f8f0f440000             jg        0x5ec937
005e8528 0f84cb430000             je        0x5ec8f9
005e852e 81fe32110000             cmp       esi, 0x1132
005e8534 0f8fcb1a0000             jg        0x5ea005
005e853a 81fe30110000             cmp       esi, 0x1130
005e8540 0f8d3a1b0000             jge       0x5ea080
005e8546 81fe7a030000             cmp       esi, 0x37a
005e854c 0f8fca0a0000             jg        0x5e901c
005e8552 0f84860a0000             je        0x5e8fde
005e8558 81fe0d030000             cmp       esi, 0x30d
005e855e 0f8f7f050000             jg        0x5e8ae3
005e8564 81fe02030000             cmp       esi, 0x302
005e856a 0f8ddd0a0000             jge       0x5e904d
005e8570 81fe1e010000             cmp       esi, 0x11e
005e8576 0f8f90020000             jg        0x5e880c
005e857c 81fe19010000             cmp       esi, 0x119
005e8582 0f8d9b1b0000             jge       0x5ea123
005e8588 81fefa000000             cmp       esi, 0xfa
005e858e 0f8f2b010000             jg        0x5e86bf
005e8594 81fef1000000             cmp       esi, 0xf1
005e859a 0f8de5000000             jge       0x5e8685
005e85a0 8d46ff                   lea       eax, [esi - 1]
005e85a3 3def000000               cmp       eax, 0xef
005e85a8 0f870b040000             ja        0x5e89b9
005e85ae 0fb68020165f00           movzx     eax, byte ptr [eax + 0x5f1620]
005e85b5 ff248504165f00           jmp       dword ptr [eax*4 + 0x5f1604]
