004ea4d0  55                       push       ebp
004ea4d1  8bec                     mov        ebp, esp
004ea4d3  83ec10                   sub        esp, 0x10
004ea4d6  57                       push       edi
004ea4d7  8bf9                     mov        edi, ecx
004ea4d9  8b07                     mov        eax, dword ptr [edi]
004ea4db  ff9068010000             call       dword ptr [eax + 0x168]
004ea4e1  84c0                     test       al, al
004ea4e3  0f8529010000             jne        0x4ea612
004ea4e9  8b17                     mov        edx, dword ptr [edi]
004ea4eb  8bcf                     mov        ecx, edi
004ea4ed  ff5264                   call       dword ptr [edx + 0x64]
004ea4f0  84c0                     test       al, al
004ea4f2  0f841a010000             je         0x4ea612
004ea4f8  8bcf                     mov        ecx, edi
004ea4fa  e8911bfbff               call       0x49c090
004ea4ff  84c0                     test       al, al
004ea501  0f840b010000             je         0x4ea612
004ea507  837d2404                 cmp        dword ptr [ebp + 0x24], 4
004ea50b  750d                     jne        0x4ea51a
004ea50d  8b07                     mov        eax, dword ptr [edi]
004ea50f  8bcf                     mov        ecx, edi
004ea511  ff90c0000000             call       dword ptr [eax + 0xc0]
004ea517  894524                   mov        dword ptr [ebp + 0x24], eax
004ea51a  8b17                     mov        edx, dword ptr [edi]
004ea51c  53                       push       ebx
004ea51d  56                       push       esi
004ea51e  8bcf                     mov        ecx, edi
004ea520  ff9294000000             call       dword ptr [edx + 0x94]
004ea526  8bf0                     mov        esi, eax
004ea528  8b07                     mov        eax, dword ptr [edi]
004ea52a  8bcf                     mov        ecx, edi
004ea52c  ff9098000000             call       dword ptr [eax + 0x98]
004ea532  8b17                     mov        edx, dword ptr [edi]
004ea534  8bcf                     mov        ecx, edi
004ea536  8bd8                     mov        ebx, eax
004ea538  ff929c000000             call       dword ptr [edx + 0x9c]
004ea53e  8b5524                   mov        edx, dword ptr [ebp + 0x24]
004ea541  b901000000               mov        ecx, 1
004ea546  3bd1                     cmp        edx, ecx
004ea548  8b5518                   mov        edx, dword ptr [ebp + 0x18]
004ea54b  7504                     jne        0x4ea551
004ea54d  03f2                     add        esi, edx
004ea54f  eb02                     jmp        0x4ea553
004ea551  2bf2                     sub        esi, edx
004ea553  8b551c                   mov        edx, dword ptr [ebp + 0x1c]
004ea556  8975fc                   mov        dword ptr [ebp - 4], esi
004ea559  034520                   add        eax, dword ptr [ebp + 0x20]
004ea55c  8b7510                   mov        esi, dword ptr [ebp + 0x10]
004ea55f  03da                     add        ebx, edx
004ea561  85f6                     test       esi, esi
004ea563  7475                     je         0x4ea5da
004ea565  8b16                     mov        edx, dword ptr [esi]
004ea567  8955f0                   mov        dword ptr [ebp - 0x10], edx
004ea56a  8b5604                   mov        edx, dword ptr [esi + 4]
004ea56d  8955f4                   mov        dword ptr [ebp - 0xc], edx
004ea570  8b5608                   mov        edx, dword ptr [esi + 8]
004ea573  8955f8                   mov        dword ptr [ebp - 8], edx
004ea576  8a5658                   mov        dl, byte ptr [esi + 0x58]
004ea579  88551b                   mov        byte ptr [ebp + 0x1b], dl
004ea57c  8b55fc                   mov        edx, dword ptr [ebp - 4]
004ea57f  8916                     mov        dword ptr [esi], edx
004ea581  394d24                   cmp        dword ptr [ebp + 0x24], ecx
004ea584  8b4d38                   mov        ecx, dword ptr [ebp + 0x38]
004ea587  8b5534                   mov        edx, dword ptr [ebp + 0x34]
004ea58a  51                       push       ecx
004ea58b  8b4d2c                   mov        ecx, dword ptr [ebp + 0x2c]
004ea58e  52                       push       edx
004ea58f  8b5528                   mov        edx, dword ptr [ebp + 0x28]
004ea592  894608                   mov        dword ptr [esi + 8], eax
004ea595  0f95c0                   setne      al
004ea598  884658                   mov        byte ptr [esi + 0x58], al
004ea59b  8b4530                   mov        eax, dword ptr [ebp + 0x30]
004ea59e  50                       push       eax
004ea59f  8b4514                   mov        eax, dword ptr [ebp + 0x14]
004ea5a2  51                       push       ecx
004ea5a3  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004ea5a6  52                       push       edx
004ea5a7  8b5508                   mov        edx, dword ptr [ebp + 8]
004ea5aa  50                       push       eax
004ea5ab  56                       push       esi
004ea5ac  51                       push       ecx
004ea5ad  52                       push       edx
004ea5ae  57                       push       edi
004ea5af  895e04                   mov        dword ptr [esi + 4], ebx
004ea5b2  e849fbffff               call       0x4ea100
004ea5b7  8b4df0                   mov        ecx, dword ptr [ebp - 0x10]
004ea5ba  8b55f4                   mov        edx, dword ptr [ebp - 0xc]
004ea5bd  890e                     mov        dword ptr [esi], ecx
004ea5bf  8b4df8                   mov        ecx, dword ptr [ebp - 8]
004ea5c2  895604                   mov        dword ptr [esi + 4], edx
004ea5c5  8a551b                   mov        dl, byte ptr [ebp + 0x1b]
004ea5c8  83c428                   add        esp, 0x28
004ea5cb  894e08                   mov        dword ptr [esi + 8], ecx
004ea5ce  885658                   mov        byte ptr [esi + 0x58], dl
004ea5d1  5e                       pop        esi
004ea5d2  5b                       pop        ebx
004ea5d3  5f                       pop        edi
004ea5d4  8be5                     mov        esp, ebp
004ea5d6  5d                       pop        ebp
004ea5d7  c23400                   ret        0x34
004ea5da  8b4d38                   mov        ecx, dword ptr [ebp + 0x38]
004ea5dd  8b5534                   mov        edx, dword ptr [ebp + 0x34]
004ea5e0  51                       push       ecx
004ea5e1  8b4d30                   mov        ecx, dword ptr [ebp + 0x30]
004ea5e4  52                       push       edx
004ea5e5  8b552c                   mov        edx, dword ptr [ebp + 0x2c]
004ea5e8  51                       push       ecx
004ea5e9  8b4d28                   mov        ecx, dword ptr [ebp + 0x28]
004ea5ec  52                       push       edx
004ea5ed  8b5524                   mov        edx, dword ptr [ebp + 0x24]
004ea5f0  51                       push       ecx
004ea5f1  8b4d0c                   mov        ecx, dword ptr [ebp + 0xc]
004ea5f4  52                       push       edx
004ea5f5  8b5508                   mov        edx, dword ptr [ebp + 8]
004ea5f8  50                       push       eax
004ea5f9  8b45fc                   mov        eax, dword ptr [ebp - 4]
004ea5fc  53                       push       ebx
004ea5fd  50                       push       eax
004ea5fe  51                       push       ecx
004ea5ff  52                       push       edx
004ea600  57                       push       edi
004ea601  e89af8ffff               call       0x4e9ea0
004ea606  83c430                   add        esp, 0x30
004ea609  5e                       pop        esi
004ea60a  5b                       pop        ebx
004ea60b  5f                       pop        edi
004ea60c  8be5                     mov        esp, ebp
004ea60e  5d                       pop        ebp
004ea60f  c23400                   ret        0x34
004ea612  b8ffff0000               mov        eax, 0xffff
004ea617  5f                       pop        edi
004ea618  8be5                     mov        esp, ebp
004ea61a  5d                       pop        ebp
004ea61b  c23400                   ret        0x34