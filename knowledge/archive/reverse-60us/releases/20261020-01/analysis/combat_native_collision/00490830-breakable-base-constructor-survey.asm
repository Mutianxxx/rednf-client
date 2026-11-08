00490830 55                       push      ebp
00490831 8bec                     mov       ebp, esp
00490833 6aff                     push      -1
00490835 68745ec500               push      0xc55e74
0049083a 64a100000000             mov       eax, dword ptr fs:[0]
00490840 50                       push      eax
00490841 64892500000000           mov       dword ptr fs:[0], esp
00490848 51                       push      ecx
00490849 8b450c                   mov       eax, dword ptr [ebp + 0xc]
0049084c 56                       push      esi
0049084d 57                       push      edi
0049084e 8bf1                     mov       esi, ecx
00490850 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00490853 50                       push      eax
00490854 51                       push      ecx
00490855 8bce                     mov       ecx, esi
00490857 8975f0                   mov       dword ptr [ebp - 0x10], esi
0049085a e8c1feffff               call      0x490720
0049085f 33ff                     xor       edi, edi
00490861 8d8e8c080000             lea       ecx, [esi + 0x88c]
00490867 897dfc                   mov       dword ptr [ebp - 4], edi
0049086a c7068cc8cc00             mov       dword ptr [esi], 0xccc88c
00490870 e8eb4af7ff               call      0x405360
00490875 89bed4080000             mov       dword ptr [esi + 0x8d4], edi
0049087b 89bed8080000             mov       dword ptr [esi + 0x8d8], edi
00490881 89bedc080000             mov       dword ptr [esi + 0x8dc], edi
00490887 6800d04400               push      0x44d000
0049088c 68003f4000               push      0x403f00
00490891 6a03                     push      3
00490893 6a04                     push      4
00490895 8d96f0080000             lea       edx, [esi + 0x8f0]
0049089b 52                       push      edx
0049089c c645fc02                 mov       byte ptr [ebp - 4], 2
004908a0 e8bfff7600               call      0xc00864
004908a5 89be00090000             mov       dword ptr [esi + 0x900], edi
004908ab 89be04090000             mov       dword ptr [esi + 0x904], edi
004908b1 89be08090000             mov       dword ptr [esi + 0x908], edi
004908b7 89be10090000             mov       dword ptr [esi + 0x910], edi
004908bd 89be14090000             mov       dword ptr [esi + 0x914], edi
004908c3 89be18090000             mov       dword ptr [esi + 0x918], edi
004908c9 89be20090000             mov       dword ptr [esi + 0x920], edi
004908cf 89be24090000             mov       dword ptr [esi + 0x924], edi
004908d5 89be28090000             mov       dword ptr [esi + 0x928], edi
004908db 89be30090000             mov       dword ptr [esi + 0x930], edi
004908e1 89be34090000             mov       dword ptr [esi + 0x934], edi
004908e7 89be38090000             mov       dword ptr [esi + 0x938], edi
004908ed 8bce                     mov       ecx, esi
004908ef c645fc07                 mov       byte ptr [ebp - 4], 7
004908f3 e868591600               call      0x5f6260
004908f8 8bce                     mov       ecx, esi
004908fa e8415d1600               call      0x5f6640
004908ff 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00490902 5f                       pop       edi
00490903 8bc6                     mov       eax, esi
00490905 5e                       pop       esi
00490906 64890d00000000           mov       dword ptr fs:[0], ecx
0049090d 8be5                     mov       esp, ebp
0049090f 5d                       pop       ebp
00490910 c20800                   ret       8
00490913 cc                       int3      
00490914 cc                       int3      
00490915 cc                       int3      
00490916 cc                       int3      
00490917 cc                       int3      
00490918 cc                       int3      
00490919 cc                       int3      
0049091a cc                       int3      
0049091b cc                       int3      
0049091c cc                       int3      
0049091d cc                       int3      
0049091e cc                       int3      
0049091f cc                       int3      
00490920 32c0                     xor       al, al
00490922 c20400                   ret       4
00490925 cc                       int3      
00490926 cc                       int3      
00490927 cc                       int3      
00490928 cc                       int3      
00490929 cc                       int3      
0049092a cc                       int3      
0049092b cc                       int3      
0049092c cc                       int3      
0049092d cc                       int3      
0049092e cc                       int3      
0049092f cc                       int3      
00490930 55                       push      ebp
00490931 8bec                     mov       ebp, esp
00490933 56                       push      esi
00490934 8bf1                     mov       esi, ecx
00490936 e825000000               call      0x490960
0049093b f6450801                 test      byte ptr [ebp + 8], 1
0049093f 7409                     je        0x49094a
00490941 56                       push      esi
00490942 e80916f7ff               call      0x401f50
00490947 83c404                   add       esp, 4
0049094a 8bc6                     mov       eax, esi
0049094c 5e                       pop       esi
0049094d 5d                       pop       ebp
0049094e c20400                   ret       4
00490951 cc                       int3      
00490952 cc                       int3      
00490953 cc                       int3      
00490954 cc                       int3      
00490955 cc                       int3      
00490956 cc                       int3      
00490957 cc                       int3      
00490958 cc                       int3      
00490959 cc                       int3      
0049095a cc                       int3      
0049095b cc                       int3      
0049095c cc                       int3      
0049095d cc                       int3      
0049095e cc                       int3      
0049095f cc                       int3      
