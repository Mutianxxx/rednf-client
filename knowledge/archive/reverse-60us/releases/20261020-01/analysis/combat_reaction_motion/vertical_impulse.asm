004b98f0 55                       push       ebp
004b98f1 8bec                     mov        ebp, esp
004b98f3 8b4508                   mov        eax, dword ptr [ebp + 8]
004b98f6 69c0a00f0000             imul       eax, eax, 0xfa0
004b98fc 894508                   mov        dword ptr [ebp + 8], eax
004b98ff 8b450c                   mov        eax, dword ptr [ebp + 0xc]
004b9902 6bc064                   imul       eax, eax, 0x64
004b9905 db4508                   fild       dword ptr [ebp + 8]
004b9908 99                       cdq        
004b9909 f77d10                   idiv       dword ptr [ebp + 0x10]
004b990c 2d10270000               sub        eax, 0x2710
004b9911 894508                   mov        dword ptr [ebp + 8], eax
004b9914 db4508                   fild       dword ptr [ebp + 8]
004b9917 d80d3814cd00             fmul       dword ptr [0xcd1438]
004b991d d8053414cd00             fadd       dword ptr [0xcd1434]
004b9923 def9                     fdivp      st(1)
004b9925 5d                       pop        ebp
004b9926 c3                       ret        
