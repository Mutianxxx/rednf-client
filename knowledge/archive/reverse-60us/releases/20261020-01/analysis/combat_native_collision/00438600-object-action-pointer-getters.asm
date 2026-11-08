00438600 fc                       cld       
00438601 ff8d8e180500             dec       dword ptr [ebp + 0x5188e]
00438607 00c6                     add       dh, al
00438609 45                       inc       ebp
0043860a fc                       cld       
0043860b 0de87fbbfc               or        eax, 0xfcbb7fe8
00438610 ff8bcec645fc             dec       dword ptr [ebx - 0x3ba3932]
00438616 0e                       push      cs
00438617 e8b4480b00               call      0x4eced0
0043861c 8bce                     mov       ecx, esi
0043861e e86df70a00               call      0x4e7d90
00438623 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00438626 5f                       pop       edi
00438627 8bc6                     mov       eax, esi
00438629 5e                       pop       esi
0043862a 64890d00000000           mov       dword ptr fs:[0], ecx
00438631 8be5                     mov       esp, ebp
00438633 5d                       pop       ebp
00438634 c3                       ret       
00438635 cc                       int3      
00438636 cc                       int3      
00438637 cc                       int3      
00438638 cc                       int3      
00438639 cc                       int3      
0043863a cc                       int3      
0043863b cc                       int3      
0043863c cc                       int3      
0043863d cc                       int3      
0043863e cc                       int3      
0043863f cc                       int3      
00438640 8d8104020000             lea       eax, [ecx + 0x204]
00438646 c3                       ret       
00438647 cc                       int3      
00438648 cc                       int3      
00438649 cc                       int3      
0043864a cc                       int3      
0043864b cc                       int3      
0043864c cc                       int3      
0043864d cc                       int3      
0043864e cc                       int3      
0043864f cc                       int3      
00438650 8d8160020000             lea       eax, [ecx + 0x260]
00438656 c3                       ret       
00438657 cc                       int3      
00438658 cc                       int3      
00438659 cc                       int3      
0043865a cc                       int3      
0043865b cc                       int3      
0043865c cc                       int3      
0043865d cc                       int3      
0043865e cc                       int3      
0043865f cc                       int3      
00438660 8d8118040000             lea       eax, [ecx + 0x418]
00438666 c3                       ret       
00438667 cc                       int3      
00438668 cc                       int3      
00438669 cc                       int3      
0043866a cc                       int3      
0043866b cc                       int3      
0043866c cc                       int3      
0043866d cc                       int3      
0043866e cc                       int3      
0043866f cc                       int3      
00438670 8b01                     mov       eax, dword ptr [ecx]
00438672 6a11                     push      0x11
00438674 ff502c                   call      dword ptr [eax + 0x2c]
00438677 c3                       ret       
00438678 cc                       int3      
00438679 cc                       int3      
0043867a cc                       int3      
0043867b cc                       int3      
0043867c cc                       int3      
0043867d cc                       int3      
0043867e cc                       int3      
0043867f cc                       int3      
00438680 55                       push      ebp
00438681 8bec                     mov       ebp, esp
00438683 8b4508                   mov       eax, dword ptr [ebp + 8]
00438686 898198040000             mov       dword ptr [ecx + 0x498], eax
0043868c 5d                       pop       ebp
0043868d c20400                   ret       4
00438690 8b8198040000             mov       eax, dword ptr [ecx + 0x498]
00438696 c3                       ret       
00438697 cc                       int3      
00438698 cc                       int3      
00438699 cc                       int3      
0043869a cc                       int3      
0043869b cc                       int3      
0043869c cc                       int3      
0043869d cc                       int3      
0043869e cc                       int3      
0043869f cc                       int3      
004386a0 d905a4d7e900             fld       dword ptr [0xe9d7a4]
004386a6 c3                       ret       
004386a7 cc                       int3      
004386a8 cc                       int3      
004386a9 cc                       int3      
004386aa cc                       int3      
004386ab cc                       int3      
004386ac cc                       int3      
004386ad cc                       int3      
004386ae cc                       int3      
004386af cc                       int3      
004386b0 55                       push      ebp
004386b1 8bec                     mov       ebp, esp
004386b3 8b4d08                   mov       ecx, dword ptr [ebp + 8]
004386b6 33c0                     xor       eax, eax
004386b8 85c9                     test      ecx, ecx
004386ba 0f9dc0                   setge     al
004386bd 5d                       pop       ebp
004386be c20400                   ret       4
004386c1 cc                       int3      
004386c2 cc                       int3      
004386c3 cc                       int3      
004386c4 cc                       int3      
004386c5 cc                       int3      
004386c6 cc                       int3      
004386c7 cc                       int3      
004386c8 cc                       int3      
004386c9 cc                       int3      
004386ca cc                       int3      
004386cb cc                       int3      
004386cc cc                       int3      
004386cd cc                       int3      
004386ce cc                       int3      
004386cf cc                       int3      
004386d0 8b811c020000             mov       eax, dword ptr [ecx + 0x21c]
004386d6 c3                       ret       
004386d7 cc                       int3      
004386d8 cc                       int3      
004386d9 cc                       int3      
004386da cc                       int3      
004386db cc                       int3      
004386dc cc                       int3      
004386dd cc                       int3      
004386de cc                       int3      
004386df cc                       int3      
004386e0 83c8ff                   or        eax, 0xffffffff
004386e3 c3                       ret       
004386e4 cc                       int3      
004386e5 cc                       int3      
004386e6 cc                       int3      
004386e7 cc                       int3      
004386e8 cc                       int3      
004386e9 cc                       int3      
004386ea cc                       int3      
004386eb cc                       int3      
004386ec cc                       int3      
004386ed cc                       int3      
004386ee cc                       int3      
004386ef cc                       int3      
004386f0 55                       push      ebp
004386f1 8bec                     mov       ebp, esp
004386f3 8a4508                   mov       al, byte ptr [ebp + 8]
004386f6 88819c040000             mov       byte ptr [ecx + 0x49c], al
004386fc 5d                       pop       ebp
004386fd c20400                   ret       4
00438700 8b81a0040000             mov       eax, dword ptr [ecx + 0x4a0]
00438706 c3                       ret       
00438707 cc                       int3      
00438708 cc                       int3      
00438709 cc                       int3      
0043870a cc                       int3      
0043870b cc                       int3      
0043870c cc                       int3      
0043870d cc                       int3      
0043870e cc                       int3      
0043870f cc                       int3      
00438710 c781a0040000ffffffff     mov       dword ptr [ecx + 0x4a0], 0xffffffff
0043871a c3                       ret       
0043871b cc                       int3      
0043871c cc                       int3      
0043871d cc                       int3      
0043871e cc                       int3      
0043871f cc                       int3      
