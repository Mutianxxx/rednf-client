004fa1d0 55                       push       ebp
004fa1d1 8bec                     mov        ebp, esp
004fa1d3 6aff                     push       -1
004fa1d5 68709cc500               push       0xc59c70
004fa1da 64a100000000             mov        eax, dword ptr fs:[0]
004fa1e0 50                       push       eax
004fa1e1 64892500000000           mov        dword ptr fs:[0], esp
004fa1e8 83ec60                   sub        esp, 0x60
004fa1eb 53                       push       ebx
004fa1ec 56                       push       esi
004fa1ed 57                       push       edi
004fa1ee 8bf1                     mov        esi, ecx
004fa1f0 e96a08ec00               jmp        0x13baa5f
004fa1f5 7ce3                     jl         0x4fa1da
004fa1f7 5e                       pop        esi
004fa1f8 1f                       pop        ds
004fa1f9 e453                     in         al, 0x53
004fa1fb 2e395600                 cmp        dword ptr cs:[esi], edx
004fa1ff f8                       clc        
004fa200 e253                     loop       0x4fa255
004fa202 98                       cwde       
004fa203 d7                       xlatb      
004fa204 99                       cdq        
004fa205 9a56e378bdb3ba           lcall      0xbab3, 0xbd78e356
004fa20c 5b                       pop        ebx
004fa20d 6bccf4                   imul       ecx, esp, -0xc
004fa210 94                       xchg       esp, eax
004fa211 91                       xchg       ecx, eax
004fa212 8e92f8e44ad2             mov        ss, word ptr [edx - 0x2db51b08]
004fa218 03bd1c2a8a86             add        edi, dword ptr [ebp - 0x7975d5e4]
004fa21e e801000084               call       0x844fa224
004fa223 c00f85                   ror        byte ptr [edi], 0x85
004fa226 1306                     adc        eax, dword ptr [esi]
004fa228 0000                     add        byte ptr [eax], al
004fa22a 8b06                     mov        eax, dword ptr [esi]
