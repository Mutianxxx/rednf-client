004bdd40 55                       push       ebp
004bdd41 8bec                     mov        ebp, esp
004bdd43 51                       push       ecx
004bdd44 56                       push       esi
004bdd45 8bf1                     mov        esi, ecx
004bdd47 8d8e18020000             lea        ecx, [esi + 0x218]
004bdd4d e80e43f4ff               call       0x402060
004bdd52 8945fc                   mov        dword ptr [ebp - 4], eax
004bdd55 db45fc                   fild       dword ptr [ebp - 4]
004bdd58 8d8e20020000             lea        ecx, [esi + 0x220]
004bdd5e d95dfc                   fstp       dword ptr [ebp - 4]
004bdd61 e84a56f7ff               call       0x4333b0
004bdd66 d84dfc                   fmul       dword ptr [ebp - 4]
004bdd69 e8d6377400               call       0xc01544
004bdd6e 5e                       pop        esi
004bdd6f 8be5                     mov        esp, ebp
004bdd71 5d                       pop        ebp
004bdd72 c3                       ret        
