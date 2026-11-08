00a293c8  53                       push       ebx
00a293c9  e80264e0ff               call       0x82f7d0
00a293ce  89450c                   mov        dword ptr [ebp + 0xc], eax
00a293d1  db450c                   fild       dword ptr [ebp + 0xc]
00a293d4  83c404                   add        esp, 4
00a293d7  8d4d0c                   lea        ecx, [ebp + 0xc]
00a293da  51                       push       ecx
00a293db  d95d0c                   fstp       dword ptr [ebp + 0xc]
00a293de  8d8d44ffffff             lea        ecx, [ebp - 0xbc]
00a293e4  e877b19dff               call       0x404560
00a293e9  53                       push       ebx
00a293ea  e8e163e0ff               call       0x82f7d0
00a293ef  89450c                   mov        dword ptr [ebp + 0xc], eax
00a293f2  db450c                   fild       dword ptr [ebp + 0xc]
00a293f5  83c404                   add        esp, 4
00a293f8  8d550c                   lea        edx, [ebp + 0xc]
00a293fb  52                       push       edx
00a293fc  d95d0c                   fstp       dword ptr [ebp + 0xc]
00a293ff  8d8d4cffffff             lea        ecx, [ebp - 0xb4]
00a29405  e856b19dff               call       0x404560
00a2940a  53                       push       ebx
00a2940b  e8c063e0ff               call       0x82f7d0
00a29410  89450c                   mov        dword ptr [ebp + 0xc], eax
00a29413  db450c                   fild       dword ptr [ebp + 0xc]
00a29416  83c404                   add        esp, 4
00a29419  8d450c                   lea        eax, [ebp + 0xc]
00a2941c  50                       push       eax
00a2941d  d95d0c                   fstp       dword ptr [ebp + 0xc]
00a29420  8d8d54ffffff             lea        ecx, [ebp - 0xac]
00a29426  e835b19dff               call       0x404560
00a2942b  53                       push       ebx
00a2942c  e89f63e0ff               call       0x82f7d0
00a29431  89450c                   mov        dword ptr [ebp + 0xc], eax
00a29434  db450c                   fild       dword ptr [ebp + 0xc]
00a29437  83c404                   add        esp, 4
00a2943a  8d4d0c                   lea        ecx, [ebp + 0xc]
00a2943d  51                       push       ecx
00a2943e  d95d0c                   fstp       dword ptr [ebp + 0xc]
00a29441  8d8d5cffffff             lea        ecx, [ebp - 0xa4]
00a29447  e814b19dff               call       0x404560
00a2944c  53                       push       ebx
00a2944d  e87e63e0ff               call       0x82f7d0
00a29452  89450c                   mov        dword ptr [ebp + 0xc], eax
00a29455  db450c                   fild       dword ptr [ebp + 0xc]
00a29458  83c404                   add        esp, 4
00a2945b  8d550c                   lea        edx, [ebp + 0xc]
00a2945e  52                       push       edx
00a2945f  d95d0c                   fstp       dword ptr [ebp + 0xc]
00a29462  8d8d64ffffff             lea        ecx, [ebp - 0x9c]
00a29468  e8f3b09dff               call       0x404560
00a2946d  53                       push       ebx
00a2946e  e85d63e0ff               call       0x82f7d0
00a29473  89450c                   mov        dword ptr [ebp + 0xc], eax
00a29476  db450c                   fild       dword ptr [ebp + 0xc]
00a29479  83c404                   add        esp, 4
00a2947c  8d450c                   lea        eax, [ebp + 0xc]
00a2947f  50                       push       eax
00a29480  d95d0c                   fstp       dword ptr [ebp + 0xc]
00a29483  8d8d6cffffff             lea        ecx, [ebp - 0x94]
00a29489  e8d2b09dff               call       0x404560
00a2948e  3bf3                     cmp        esi, ebx
00a29490  0f84f4f9ffff             je         0xa28e8a
00a29496  8d8d44ffffff             lea        ecx, [ebp - 0xbc]
00a2949c  51                       push       ecx
00a2949d  8d4e48                   lea        ecx, [esi + 0x48]
00a294a0  e81b38c3ff               call       0x65ccc0
00a294a5  e9e0f9ffff               jmp        0xa28e8a
