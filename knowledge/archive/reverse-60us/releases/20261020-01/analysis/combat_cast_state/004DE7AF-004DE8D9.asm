004de7af  8bcf                     mov        ecx, edi
004de7b1  e8aa38f2ff               call       0x402060
004de7b6  83f801                   cmp        eax, 1
004de7b9  0f8503010000             jne        0x4de8c2
004de7bf  83be2824000002           cmp        dword ptr [esi + 0x2428], 2
004de7c6  8b3e                     mov        edi, dword ptr [esi]
004de7c8  750a                     jne        0x4de7d4
004de7ca  8bce                     mov        ecx, esi
004de7cc  ff976c030000             call       dword ptr [edi + 0x36c]
004de7d2  eb0f                     jmp        0x4de7e3
004de7d4  8b8e44240000             mov        ecx, dword ptr [esi + 0x2444]
004de7da  51                       push       ecx
004de7db  8bce                     mov        ecx, esi
004de7dd  ff97e4050000             call       dword ptr [edi + 0x5e4]
004de7e3  8bce                     mov        ecx, esi
004de7e5  50                       push       eax
004de7e6  ff97f0000000             call       dword ptr [edi + 0xf0]
004de7ec  8b864c240000             mov        eax, dword ptr [esi + 0x244c]
004de7f2  8b8e48240000             mov        ecx, dword ptr [esi + 0x2448]
004de7f8  8b16                     mov        edx, dword ptr [esi]
004de7fa  680000803f               push       0x3f800000
004de7ff  680000803f               push       0x3f800000
004de804  50                       push       eax
004de805  50                       push       eax
004de806  51                       push       ecx
004de807  51                       push       ecx
004de808  8bce                     mov        ecx, esi
004de80a  ff9294040000             call       dword ptr [edx + 0x494]
004de810  8dbe3c240000             lea        edi, [esi + 0x243c]
004de816  8bcf                     mov        ecx, edi
004de818  e84338f2ff               call       0x402060
004de81d  83f8ff                   cmp        eax, -1
004de820  7433                     je         0x4de855
004de822  8d8e20160000             lea        ecx, [esi + 0x1620]
004de828  e83338f2ff               call       0x402060
004de82d  8bcf                     mov        ecx, edi
004de82f  89450c                   mov        dword ptr [ebp + 0xc], eax
004de832  e82938f2ff               call       0x402060
004de837  69c0e8030000             imul       eax, eax, 0x3e8
004de83d  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004de840  99                       cdq        
004de841  f7f9                     idiv       ecx
004de843  8d8e3c240000             lea        ecx, [esi + 0x243c]
004de849  89450c                   mov        dword ptr [ebp + 0xc], eax
004de84c  8d450c                   lea        eax, [ebp + 0xc]
004de84f  50                       push       eax
004de850  e80b5df2ff               call       0x404560
004de855  8d8e50240000             lea        ecx, [esi + 0x2450]
004de85b  e80038f2ff               call       0x402060
004de860  83f8ff                   cmp        eax, -1
004de863  744e                     je         0x4de8b3
004de865  8bcb                     mov        ecx, ebx
004de867  e8247ff8ff               call       0x466790
004de86c  83f801                   cmp        eax, 1
004de86f  7637                     jbe        0x4de8a8
004de871  8b4304                   mov        eax, dword ptr [ebx + 4]
004de874  8b4804                   mov        ecx, dword ptr [eax + 4]
004de877  6a00                     push       0
004de879  688c52f500               push       0xf5528c
004de87e  681009f400               push       0xf40910
004de883  83c004                   add        eax, 4
004de886  6a00                     push       0
004de888  51                       push       ecx
004de889  8b8e00010000             mov        ecx, dword ptr [esi + 0x100]
004de88f  e81cd00200               call       0x50b8b0
004de894  50                       push       eax
004de895  e871247200               call       0xc00d0b
004de89a  83c414                   add        esp, 0x14
004de89d  898658240000             mov        dword ptr [esi + 0x2458], eax
004de8a3  e9b4feffff               jmp        0x4de75c
004de8a8  89b658240000             mov        dword ptr [esi + 0x2458], esi
004de8ae  e9a9feffff               jmp        0x4de75c
004de8b3  c7865824000000000000     mov        dword ptr [esi + 0x2458], 0
004de8bd  e99afeffff               jmp        0x4de75c
004de8c2  8bcf                     mov        ecx, edi
004de8c4  e89737f2ff               call       0x402060
004de8c9  83f802                   cmp        eax, 2
004de8cc  0f858afeffff             jne        0x4de75c
004de8d2  33ff                     xor        edi, edi
004de8d4  89                       .byte      0x89
004de8d5  be                       .byte      0xbe
004de8d6  58                       pop        eax
004de8d7  2400                     and        al, 0