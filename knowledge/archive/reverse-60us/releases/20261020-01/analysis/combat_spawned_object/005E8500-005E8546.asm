005e8500  55                       push       ebp
005e8501  8bec                     mov        ebp, esp
005e8503  64a100000000             mov        eax, dword ptr fs:[0]
005e8509  6aff                     push       -1
005e850b  68c774c600               push       0xc674c7
005e8510  50                       push       eax
005e8511  64892500000000           mov        dword ptr fs:[0], esp
005e8518  56                       push       esi
005e8519  8b7508                   mov        esi, dword ptr [ebp + 8]
005e851c  81feee590000             cmp        esi, 0x59ee
005e8522  0f8f0f440000             jg         0x5ec937
005e8528  0f84cb430000             je         0x5ec8f9
005e852e  81fe32110000             cmp        esi, 0x1132
005e8534  0f8fcb1a0000             jg         0x5ea005
005e853a  81fe30110000             cmp        esi, 0x1130
005e8540  0f8d3a1b0000             jge        0x5ea080