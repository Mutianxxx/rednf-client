004936d0 55                       push      ebp
004936d1 8bec                     mov       ebp, esp
004936d3 6aff                     push      -1
004936d5 68b364c500               push      0xc564b3
004936da 64a100000000             mov       eax, dword ptr fs:[0]
004936e0 50                       push      eax
004936e1 64892500000000           mov       dword ptr fs:[0], esp
004936e8 51                       push      ecx
004936e9 53                       push      ebx
004936ea 56                       push      esi
004936eb 8bf1                     mov       esi, ecx
004936ed 33db                     xor       ebx, ebx
004936ef 57                       push      edi
004936f0 8975f0                   mov       dword ptr [ebp - 0x10], esi
004936f3 895e08                   mov       dword ptr [esi + 8], ebx
004936f6 895e0c                   mov       dword ptr [esi + 0xc], ebx
004936f9 895e10                   mov       dword ptr [esi + 0x10], ebx
004936fc 895dfc                   mov       dword ptr [ebp - 4], ebx
004936ff 895e38                   mov       dword ptr [esi + 0x38], ebx
00493702 895e3c                   mov       dword ptr [esi + 0x3c], ebx
00493705 895e40                   mov       dword ptr [esi + 0x40], ebx
00493708 895e44                   mov       dword ptr [esi + 0x44], ebx
0049370b 8d4e48                   lea       ecx, [esi + 0x48]
0049370e c645fc01                 mov       byte ptr [ebp - 4], 1
00493712 e8491cf7ff               call      0x405360
00493717 899e98000000             mov       dword ptr [esi + 0x98], ebx
0049371d 899e9c000000             mov       dword ptr [esi + 0x9c], ebx
00493723 899ea0000000             mov       dword ptr [esi + 0xa0], ebx
00493729 8d8ea8000000             lea       ecx, [esi + 0xa8]
0049372f c645fc03                 mov       byte ptr [ebp - 4], 3
00493733 e8f8acfdff               call      0x46e430
00493738 8dbe7c010000             lea       edi, [esi + 0x17c]
0049373e 8bcf                     mov       ecx, edi
00493740 c645fc04                 mov       byte ptr [ebp - 4], 4
00493744 e897befaff               call      0x43f5e0
00493749 894704                   mov       dword ptr [edi + 4], eax
0049374c 895f08                   mov       dword ptr [edi + 8], ebx
0049374f b807000000               mov       eax, 7
00493754 8986b8010000             mov       dword ptr [esi + 0x1b8], eax
0049375a 899eb4010000             mov       dword ptr [esi + 0x1b4], ebx
00493760 66899ea4010000           mov       word ptr [esi + 0x1a4], bx
00493767 899ec0010000             mov       dword ptr [esi + 0x1c0], ebx
0049376d 899ec4010000             mov       dword ptr [esi + 0x1c4], ebx
00493773 899ec8010000             mov       dword ptr [esi + 0x1c8], ebx
00493779 8dbecc010000             lea       edi, [esi + 0x1cc]
0049377f 8bcf                     mov       ecx, edi
00493781 8845fc                   mov       byte ptr [ebp - 4], al
00493784 e8077b0900               call      0x52b290
00493789 894704                   mov       dword ptr [edi + 4], eax
0049378c c6402d01                 mov       byte ptr [eax + 0x2d], 1
00493790 8b4704                   mov       eax, dword ptr [edi + 4]
00493793 894004                   mov       dword ptr [eax + 4], eax
00493796 8b4704                   mov       eax, dword ptr [edi + 4]
00493799 8900                     mov       dword ptr [eax], eax
0049379b 8b4704                   mov       eax, dword ptr [edi + 4]
0049379e 894008                   mov       dword ptr [eax + 8], eax
004937a1 895f08                   mov       dword ptr [edi + 8], ebx
004937a4 899edc010000             mov       dword ptr [esi + 0x1dc], ebx
004937aa 899ee0010000             mov       dword ptr [esi + 0x1e0], ebx
004937b0 899ee4010000             mov       dword ptr [esi + 0x1e4], ebx
004937b6 8bce                     mov       ecx, esi
004937b8 c645fc09                 mov       byte ptr [ebp - 4], 9
004937bc 885e18                   mov       byte ptr [esi + 0x18], bl
004937bf e89c435900               call      0xa27b60
004937c4 8b450c                   mov       eax, dword ptr [ebp + 0xc]
004937c7 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004937ca 53                       push      ebx
004937cb 53                       push      ebx
004937cc 53                       push      ebx
004937cd 53                       push      ebx
004937ce 50                       push      eax
004937cf 51                       push      ecx
004937d0 68e0baca00               push      0xcabae0
004937d5 8bce                     mov       ecx, esi
004937d7 e8f4625900               call      0xa29ad0
004937dc 5f                       pop       edi
004937dd 8bc6                     mov       eax, esi
004937df 5e                       pop       esi
004937e0 5b                       pop       ebx
004937e1 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
004937e4 64890d00000000           mov       dword ptr fs:[0], ecx
004937eb 8be5                     mov       esp, ebp
004937ed 5d                       pop       ebp
004937ee c20800                   ret       8
004937f1 cc                       int3      
004937f2 cc                       int3      
004937f3 cc                       int3      
004937f4 cc                       int3      
004937f5 cc                       int3      
004937f6 cc                       int3      
004937f7 cc                       int3      
004937f8 cc                       int3      
004937f9 cc                       int3      
004937fa cc                       int3      
004937fb cc                       int3      
004937fc cc                       int3      
004937fd cc                       int3      
004937fe cc                       int3      
004937ff cc                       int3      
00493800 55                       push      ebp
00493801 8bec                     mov       ebp, esp
00493803 8b4508                   mov       eax, dword ptr [ebp + 8]
00493806 a3b47ef500               mov       dword ptr [0xf57eb4], eax
0049380b 5d                       pop       ebp
0049380c c3                       ret       
0049380d cc                       int3      
0049380e cc                       int3      
0049380f cc                       int3      
