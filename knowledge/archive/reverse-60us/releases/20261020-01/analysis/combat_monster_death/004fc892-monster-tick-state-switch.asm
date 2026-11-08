004fc892 8d8e5c150000             lea       ecx, [esi + 0x155c]
004fc898 e8c357f0ff               call      0x402060
004fc89d 83f80d                   cmp       eax, 0xd
004fc8a0 0f87c6040000             ja        0x4fcd6c
004fc8a6 0fb68084ce4f00           movzx     eax, byte ptr [eax + 0x4fce84]
004fc8ad ff248568ce4f00           jmp       dword ptr [eax*4 + 0x4fce68]
