005e70c0 55                       push      ebp
005e70c1 8bec                     mov       ebp, esp
005e70c3 6aff                     push      -1
005e70c5 68583bc600               push      0xc63b58
005e70ca 64a100000000             mov       eax, dword ptr fs:[0]
005e70d0 50                       push      eax
005e70d1 64892500000000           mov       dword ptr fs:[0], esp
005e70d8 51                       push      ecx
005e70d9 8b450c                   mov       eax, dword ptr [ebp + 0xc]
005e70dc 56                       push      esi
005e70dd 8bf1                     mov       esi, ecx
005e70df 8b4d08                   mov       ecx, dword ptr [ebp + 8]
005e70e2 50                       push      eax
005e70e3 51                       push      ecx
005e70e4 8bce                     mov       ecx, esi
005e70e6 8975f0                   mov       dword ptr [ebp - 0x10], esi
005e70e9 e84297eaff               call      0x490830
005e70ee 8bce                     mov       ecx, esi
005e70f0 c745fc00000000           mov       dword ptr [ebp - 4], 0
005e70f7 c7066cd2d400             mov       dword ptr [esi], 0xd4d26c
005e70fd e85ef10000               call      0x5f6260
005e7102 8bce                     mov       ecx, esi
005e7104 e837f50000               call      0x5f6640
005e7109 8bce                     mov       ecx, esi
005e710b e840550200               call      0x60c650
005e7110 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005e7113 8bc6                     mov       eax, esi
005e7115 5e                       pop       esi
005e7116 64890d00000000           mov       dword ptr fs:[0], ecx
005e711d 8be5                     mov       esp, ebp
005e711f 5d                       pop       ebp
005e7120 c20800                   ret       8
005e7123 cc                       int3      
005e7124 cc                       int3      
005e7125 cc                       int3      
005e7126 cc                       int3      
005e7127 cc                       int3      
005e7128 cc                       int3      
005e7129 cc                       int3      
005e712a cc                       int3      
005e712b cc                       int3      
005e712c cc                       int3      
005e712d cc                       int3      
005e712e cc                       int3      
005e712f cc                       int3      
005e7130 55                       push      ebp
005e7131 8bec                     mov       ebp, esp
005e7133 56                       push      esi
005e7134 8bf1                     mov       esi, ecx
005e7136 e825000000               call      0x5e7160
005e713b f6450801                 test      byte ptr [ebp + 8], 1
005e713f 7409                     je        0x5e714a
005e7141 56                       push      esi
005e7142 e809aee1ff               call      0x401f50
005e7147 83c404                   add       esp, 4
005e714a 8bc6                     mov       eax, esi
005e714c 5e                       pop       esi
005e714d 5d                       pop       ebp
005e714e c20400                   ret       4
005e7151 cc                       int3      
005e7152 cc                       int3      
005e7153 cc                       int3      
005e7154 cc                       int3      
005e7155 cc                       int3      
005e7156 cc                       int3      
005e7157 cc                       int3      
005e7158 cc                       int3      
005e7159 cc                       int3      
005e715a cc                       int3      
005e715b cc                       int3      
005e715c cc                       int3      
005e715d cc                       int3      
005e715e cc                       int3      
005e715f cc                       int3      
005e7160 55                       push      ebp
005e7161 8bec                     mov       ebp, esp
005e7163 6aff                     push      -1
005e7165 68583bc600               push      0xc63b58
005e716a 64a100000000             mov       eax, dword ptr fs:[0]
005e7170 50                       push      eax
005e7171 64892500000000           mov       dword ptr fs:[0], esp
005e7178 51                       push      ecx
005e7179 56                       push      esi
005e717a 8bf1                     mov       esi, ecx
005e717c 8975f0                   mov       dword ptr [ebp - 0x10], esi
005e717f c7066cd2d400             mov       dword ptr [esi], 0xd4d26c
005e7185 c745fc00000000           mov       dword ptr [ebp - 4], 0
005e718c e81fe50000               call      0x5f56b0
005e7191 8bce                     mov       ecx, esi
005e7193 c745fcffffffff           mov       dword ptr [ebp - 4], 0xffffffff
005e719a e8c197eaff               call      0x490960
005e719f 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005e71a2 5e                       pop       esi
005e71a3 64890d00000000           mov       dword ptr fs:[0], ecx
005e71aa 8be5                     mov       esp, ebp
005e71ac 5d                       pop       ebp
005e71ad c3                       ret       
005e71ae cc                       int3      
005e71af cc                       int3      
005e71b0 55                       push      ebp
005e71b1 8bec                     mov       ebp, esp
005e71b3 6aff                     push      -1
005e71b5 683659c600               push      0xc65936
005e71ba 64a100000000             mov       eax, dword ptr fs:[0]
005e71c0 50                       push      eax
005e71c1 64892500000000           mov       dword ptr fs:[0], esp
005e71c8 51                       push      ecx
005e71c9 8b4508                   mov       eax, dword ptr [ebp + 8]
005e71cc 56                       push      esi
005e71cd 57                       push      edi
005e71ce 8b7d0c                   mov       edi, dword ptr [ebp + 0xc]
005e71d1 57                       push      edi
005e71d2 8bf1                     mov       esi, ecx
005e71d4 50                       push      eax
005e71d5 8975f0                   mov       dword ptr [ebp - 0x10], esi
005e71d8 e85396eaff               call      0x490830
005e71dd 8d8e4c090000             lea       ecx, [esi + 0x94c]
005e71e3 c70614d6d400             mov       dword ptr [esi], 0xd4d614
005e71e9 68e0baca00               push      0xcabae0
005e71ee c745fc00000000           mov       dword ptr [ebp - 4], 0
005e71f5 c70100000000             mov       dword ptr [ecx], 0
005e71fb e8a0c64600               call      0xa538a0
005e7200 8b4d10                   mov       ecx, dword ptr [ebp + 0x10]
005e7203 51                       push      ecx
005e7204 b001                     mov       al, 1
005e7206 57                       push      edi
005e7207 8bce                     mov       ecx, esi
005e7209 8845fc                   mov       byte ptr [ebp - 4], al
005e720c 888640090000             mov       byte ptr [esi + 0x940], al
005e7212 e849920200               call      0x610460
005e7217 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
005e721a 5f                       pop       edi
005e721b 8bc6                     mov       eax, esi
005e721d 5e                       pop       esi
005e721e 64890d00000000           mov       dword ptr fs:[0], ecx
005e7225 8be5                     mov       esp, ebp
005e7227 5d                       pop       ebp
005e7228 c20c00                   ret       0xc
005e722b cc                       int3      
005e722c cc                       int3      
005e722d cc                       int3      
005e722e cc                       int3      
005e722f cc                       int3      
005e7230 55                       push      ebp
005e7231 8bec                     mov       ebp, esp
005e7233 56                       push      esi
005e7234 8bf1                     mov       esi, ecx
005e7236 e825000000               call      0x5e7260
005e723b f6450801                 test      byte ptr [ebp + 8], 1
005e723f 74                       .byte     0x74
