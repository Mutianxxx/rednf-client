004fa1d0 55                       push      ebp
004fa1d1 8bec                     mov       ebp, esp
004fa1d3 6aff                     push      -1
004fa1d5 68709cc500               push      0xc59c70
004fa1da 64a100000000             mov       eax, dword ptr fs:[0]
004fa1e0 50                       push      eax
004fa1e1 64892500000000           mov       dword ptr fs:[0], esp
004fa1e8 83ec60                   sub       esp, 0x60
004fa1eb 53                       push      ebx
004fa1ec 56                       push      esi
004fa1ed 57                       push      edi
004fa1ee 8bf1                     mov       esi, ecx
004fa1f0 e96a08ec00               jmp       0x13baa5f
