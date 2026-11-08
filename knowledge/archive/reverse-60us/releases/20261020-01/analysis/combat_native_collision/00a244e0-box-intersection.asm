00a244e0 55                       push      ebp
00a244e1 8bec                     mov       ebp, esp
00a244e3 83ec30                   sub       esp, 0x30
00a244e6 56                       push      esi
00a244e7 57                       push      edi
00a244e8 8b7d08                   mov       edi, dword ptr [ebp + 8]
00a244eb 8d7718                   lea       esi, [edi + 0x18]
00a244ee 8bce                     mov       ecx, esi
00a244f0 8975f8                   mov       dword ptr [ebp - 8], esi
00a244f3 e8b8eea0ff               call      0x4333b0
00a244f8 d9e1                     fabs      
00a244fa 8bce                     mov       ecx, esi
00a244fc dd5dd0                   fstp      qword ptr [ebp - 0x30]
00a244ff e8aceea0ff               call      0x4333b0
00a24504 d9e1                     fabs      
00a24506 dc0de8b8ca00             fmul      qword ptr [0xcab8e8]
00a2450c dc5dd0                   fcomp     qword ptr [ebp - 0x30]
00a2450f dfe0                     fnstsw    ax
00a24511 f6c401                   test      ah, 1
00a24514 0f8426040000             je        0xa24940
00a2451a 8d7720                   lea       esi, [edi + 0x20]
00a2451d 8bce                     mov       ecx, esi
00a2451f 8975f0                   mov       dword ptr [ebp - 0x10], esi
00a24522 e889eea0ff               call      0x4333b0
00a24527 d9e1                     fabs      
00a24529 8bce                     mov       ecx, esi
00a2452b dd5dd0                   fstp      qword ptr [ebp - 0x30]
00a2452e e87deea0ff               call      0x4333b0
00a24533 d9e1                     fabs      
00a24535 dc0de8b8ca00             fmul      qword ptr [0xcab8e8]
00a2453b dc5dd0                   fcomp     qword ptr [ebp - 0x30]
00a2453e dfe0                     fnstsw    ax
00a24540 f6c401                   test      ah, 1
00a24543 0f84f7030000             je        0xa24940
00a24549 8d7728                   lea       esi, [edi + 0x28]
00a2454c 8bce                     mov       ecx, esi
00a2454e 8975e8                   mov       dword ptr [ebp - 0x18], esi
00a24551 e85aeea0ff               call      0x4333b0
00a24556 d9e1                     fabs      
00a24558 8bce                     mov       ecx, esi
00a2455a dd5dd0                   fstp      qword ptr [ebp - 0x30]
00a2455d e84eeea0ff               call      0x4333b0
00a24562 d9e1                     fabs      
00a24564 dc0de8b8ca00             fmul      qword ptr [0xcab8e8]
00a2456a dc5dd0                   fcomp     qword ptr [ebp - 0x30]
00a2456d dfe0                     fnstsw    ax
00a2456f f6c401                   test      ah, 1
00a24572 0f84c8030000             je        0xa24940
00a24578 8b750c                   mov       esi, dword ptr [ebp + 0xc]
00a2457b 53                       push      ebx
00a2457c 8d5e18                   lea       ebx, [esi + 0x18]
00a2457f 8bcb                     mov       ecx, ebx
00a24581 895df4                   mov       dword ptr [ebp - 0xc], ebx
00a24584 e827eea0ff               call      0x4333b0
00a24589 d9e1                     fabs      
00a2458b 8bcb                     mov       ecx, ebx
00a2458d dd5dd0                   fstp      qword ptr [ebp - 0x30]
00a24590 e81beea0ff               call      0x4333b0
00a24595 d9e1                     fabs      
00a24597 dc0de8b8ca00             fmul      qword ptr [0xcab8e8]
00a2459d dc5dd0                   fcomp     qword ptr [ebp - 0x30]
00a245a0 dfe0                     fnstsw    ax
00a245a2 f6c401                   test      ah, 1
00a245a5 747f                     je        0xa24626
00a245a7 8d5e20                   lea       ebx, [esi + 0x20]
00a245aa 8bcb                     mov       ecx, ebx
00a245ac 895dec                   mov       dword ptr [ebp - 0x14], ebx
00a245af e8fceda0ff               call      0x4333b0
00a245b4 d9e1                     fabs      
00a245b6 8bcb                     mov       ecx, ebx
00a245b8 dd5dd0                   fstp      qword ptr [ebp - 0x30]
00a245bb e8f0eda0ff               call      0x4333b0
00a245c0 d9e1                     fabs      
00a245c2 dc0de8b8ca00             fmul      qword ptr [0xcab8e8]
00a245c8 dc5dd0                   fcomp     qword ptr [ebp - 0x30]
00a245cb dfe0                     fnstsw    ax
00a245cd f6c401                   test      ah, 1
00a245d0 7454                     je        0xa24626
00a245d2 8d5e28                   lea       ebx, [esi + 0x28]
00a245d5 8bcb                     mov       ecx, ebx
00a245d7 895de4                   mov       dword ptr [ebp - 0x1c], ebx
00a245da e8d1eda0ff               call      0x4333b0
00a245df d9e1                     fabs      
00a245e1 8bcb                     mov       ecx, ebx
00a245e3 dd5dd0                   fstp      qword ptr [ebp - 0x30]
00a245e6 e8c5eda0ff               call      0x4333b0
00a245eb d9e1                     fabs      
00a245ed dc0de8b8ca00             fmul      qword ptr [0xcab8e8]
00a245f3 dc5dd0                   fcomp     qword ptr [ebp - 0x30]
00a245f6 dfe0                     fnstsw    ax
00a245f8 f6c401                   test      ah, 1
00a245fb 7429                     je        0xa24626
00a245fd 8bcf                     mov       ecx, edi
00a245ff e8aceda0ff               call      0x4333b0
00a24604 d95d08                   fstp      dword ptr [ebp + 8]
00a24607 8b4df8                   mov       ecx, dword ptr [ebp - 8]
00a2460a e8a1eda0ff               call      0x4333b0
00a2460f d84508                   fadd      dword ptr [ebp + 8]
00a24612 8bce                     mov       ecx, esi
00a24614 d95d08                   fstp      dword ptr [ebp + 8]
00a24617 e894eda0ff               call      0x4333b0
00a2461c d85d08                   fcomp     dword ptr [ebp + 8]
00a2461f dfe0                     fnstsw    ax
00a24621 f6c441                   test      ah, 0x41
00a24624 7509                     jne       0xa2462f
00a24626 5b                       pop       ebx
00a24627 5f                       pop       edi
00a24628 32c0                     xor       al, al
00a2462a 5e                       pop       esi
00a2462b 8be5                     mov       esp, ebp
00a2462d 5d                       pop       ebp
00a2462e c3                       ret       
00a2462f 8bce                     mov       ecx, esi
00a24631 e87aeda0ff               call      0x4333b0
00a24636 d95d08                   fstp      dword ptr [ebp + 8]
00a24639 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00a2463c e86feda0ff               call      0x4333b0
00a24641 d84508                   fadd      dword ptr [ebp + 8]
00a24644 8bcf                     mov       ecx, edi
00a24646 d95d08                   fstp      dword ptr [ebp + 8]
00a24649 e862eda0ff               call      0x4333b0
00a2464e d85d08                   fcomp     dword ptr [ebp + 8]
00a24651 dfe0                     fnstsw    ax
00a24653 f6c441                   test      ah, 0x41
00a24656 74ce                     je        0xa24626
00a24658 8d5f08                   lea       ebx, [edi + 8]
00a2465b 8d4608                   lea       eax, [esi + 8]
00a2465e 8bcb                     mov       ecx, ebx
00a24660 895dd8                   mov       dword ptr [ebp - 0x28], ebx
00a24663 894508                   mov       dword ptr [ebp + 8], eax
00a24666 e845eda0ff               call      0x4333b0
00a2466b d95dfc                   fstp      dword ptr [ebp - 4]
00a2466e 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
00a24671 e83aeda0ff               call      0x4333b0
00a24676 d845fc                   fadd      dword ptr [ebp - 4]
00a24679 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00a2467c d95dfc                   fstp      dword ptr [ebp - 4]
00a2467f e82ceda0ff               call      0x4333b0
00a24684 d85dfc                   fcomp     dword ptr [ebp - 4]
00a24687 dfe0                     fnstsw    ax
00a24689 f6c441                   test      ah, 0x41
00a2468c 7498                     je        0xa24626
00a2468e 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00a24691 e81aeda0ff               call      0x4333b0
00a24696 d95dfc                   fstp      dword ptr [ebp - 4]
00a24699 8b4dec                   mov       ecx, dword ptr [ebp - 0x14]
00a2469c e80feda0ff               call      0x4333b0
00a246a1 d845fc                   fadd      dword ptr [ebp - 4]
00a246a4 8bcb                     mov       ecx, ebx
00a246a6 d95dfc                   fstp      dword ptr [ebp - 4]
00a246a9 e802eda0ff               call      0x4333b0
00a246ae d85dfc                   fcomp     dword ptr [ebp - 4]
00a246b1 dfe0                     fnstsw    ax
00a246b3 f6c441                   test      ah, 0x41
00a246b6 0f846affffff             je        0xa24626
00a246bc 8d4e10                   lea       ecx, [esi + 0x10]
00a246bf 8d5f10                   lea       ebx, [edi + 0x10]
00a246c2 894dfc                   mov       dword ptr [ebp - 4], ecx
00a246c5 8bcb                     mov       ecx, ebx
00a246c7 895dd4                   mov       dword ptr [ebp - 0x2c], ebx
00a246ca e8e1eca0ff               call      0x4333b0
00a246cf d95de0                   fstp      dword ptr [ebp - 0x20]
00a246d2 8b4de8                   mov       ecx, dword ptr [ebp - 0x18]
00a246d5 e8d6eca0ff               call      0x4333b0
00a246da d845e0                   fadd      dword ptr [ebp - 0x20]
00a246dd 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
00a246e0 d95de0                   fstp      dword ptr [ebp - 0x20]
00a246e3 e8c8eca0ff               call      0x4333b0
00a246e8 d85de0                   fcomp     dword ptr [ebp - 0x20]
00a246eb dfe0                     fnstsw    ax
00a246ed f6c441                   test      ah, 0x41
00a246f0 0f8430ffffff             je        0xa24626
00a246f6 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
00a246f9 e8b2eca0ff               call      0x4333b0
00a246fe d95de0                   fstp      dword ptr [ebp - 0x20]
00a24701 8b4de4                   mov       ecx, dword ptr [ebp - 0x1c]
00a24704 e8a7eca0ff               call      0x4333b0
00a24709 d845e0                   fadd      dword ptr [ebp - 0x20]
00a2470c 8bcb                     mov       ecx, ebx
00a2470e d95de0                   fstp      dword ptr [ebp - 0x20]
00a24711 e89aeca0ff               call      0x4333b0
00a24716 d85de0                   fcomp     dword ptr [ebp - 0x20]
00a24719 dfe0                     fnstsw    ax
00a2471b f6c441                   test      ah, 0x41
00a2471e 0f8402ffffff             je        0xa24626
00a24724 8b5d10                   mov       ebx, dword ptr [ebp + 0x10]
00a24727 85db                     test      ebx, ebx
00a24729 0f8408020000             je        0xa24937
00a2472f 8bcf                     mov       ecx, edi
00a24731 e87aeca0ff               call      0x4333b0
00a24736 d95de0                   fstp      dword ptr [ebp - 0x20]
00a24739 8bce                     mov       ecx, esi
00a2473b e870eca0ff               call      0x4333b0
00a24740 d85de0                   fcomp     dword ptr [ebp - 0x20]
00a24743 dfe0                     fnstsw    ax
00a24745 f6c405                   test      ah, 5
00a24748 8bc7                     mov       eax, edi
00a2474a 7b02                     jnp       0xa2474e
00a2474c 8bc6                     mov       eax, esi
00a2474e 50                       push      eax
00a2474f 8bcb                     mov       ecx, ebx
00a24751 e85afe9dff               call      0x4045b0
00a24756 8bcf                     mov       ecx, edi
00a24758 e853eca0ff               call      0x4333b0
00a2475d d95de0                   fstp      dword ptr [ebp - 0x20]
00a24760 8b4df8                   mov       ecx, dword ptr [ebp - 8]
00a24763 e848eca0ff               call      0x4333b0
00a24768 d845e0                   fadd      dword ptr [ebp - 0x20]
00a2476b 8bce                     mov       ecx, esi
00a2476d d95ddc                   fstp      dword ptr [ebp - 0x24]
00a24770 e83beca0ff               call      0x4333b0
00a24775 d95de0                   fstp      dword ptr [ebp - 0x20]
00a24778 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00a2477b e830eca0ff               call      0x4333b0
00a24780 d845e0                   fadd      dword ptr [ebp - 0x20]
00a24783 d85ddc                   fcomp     dword ptr [ebp - 0x24]
00a24786 dfe0                     fnstsw    ax
00a24788 f6c441                   test      ah, 0x41
00a2478b 7517                     jne       0xa247a4
00a2478d 8bcf                     mov       ecx, edi
00a2478f e81ceca0ff               call      0x4333b0
00a24794 d95ddc                   fstp      dword ptr [ebp - 0x24]
00a24797 8b4df8                   mov       ecx, dword ptr [ebp - 8]
00a2479a e811eca0ff               call      0x4333b0
00a2479f d845dc                   fadd      dword ptr [ebp - 0x24]
00a247a2 eb15                     jmp       0xa247b9
00a247a4 8bce                     mov       ecx, esi
00a247a6 e805eca0ff               call      0x4333b0
00a247ab d95ddc                   fstp      dword ptr [ebp - 0x24]
00a247ae 8b4df4                   mov       ecx, dword ptr [ebp - 0xc]
00a247b1 e8faeba0ff               call      0x4333b0
00a247b6 d845dc                   fadd      dword ptr [ebp - 0x24]
00a247b9 d95df4                   fstp      dword ptr [ebp - 0xc]
00a247bc 8bcb                     mov       ecx, ebx
00a247be e8edeba0ff               call      0x4333b0
00a247c3 d86df4                   fsubr     dword ptr [ebp - 0xc]
00a247c6 8d55dc                   lea       edx, [ebp - 0x24]
00a247c9 52                       push      edx
00a247ca 8d4b18                   lea       ecx, [ebx + 0x18]
00a247cd d95ddc                   fstp      dword ptr [ebp - 0x24]
00a247d0 e88bfd9dff               call      0x404560
00a247d5 8b7dd8                   mov       edi, dword ptr [ebp - 0x28]
00a247d8 8bcf                     mov       ecx, edi
00a247da e8d1eba0ff               call      0x4333b0
00a247df d95dd8                   fstp      dword ptr [ebp - 0x28]
00a247e2 8b7508                   mov       esi, dword ptr [ebp + 8]
00a247e5 8bce                     mov       ecx, esi
00a247e7 e8c4eba0ff               call      0x4333b0
00a247ec d85dd8                   fcomp     dword ptr [ebp - 0x28]
00a247ef dfe0                     fnstsw    ax
00a247f1 f6c405                   test      ah, 5
00a247f4 8bc7                     mov       eax, edi
00a247f6 7b02                     jnp       0xa247fa
00a247f8 8bc6                     mov       eax, esi
00a247fa 8d7308                   lea       esi, [ebx + 8]
00a247fd 50                       push      eax
00a247fe 8bce                     mov       ecx, esi
00a24800 e8abfd9dff               call      0x4045b0
00a24805 8bcf                     mov       ecx, edi
00a24807 e8a4eba0ff               call      0x4333b0
00a2480c d95dd8                   fstp      dword ptr [ebp - 0x28]
00a2480f 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
00a24812 e899eba0ff               call      0x4333b0
00a24817 d845d8                   fadd      dword ptr [ebp - 0x28]
00a2481a 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00a2481d d95ddc                   fstp      dword ptr [ebp - 0x24]
00a24820 e88beba0ff               call      0x4333b0
00a24825 d95dd8                   fstp      dword ptr [ebp - 0x28]
00a24828 8b4dec                   mov       ecx, dword ptr [ebp - 0x14]
00a2482b e880eba0ff               call      0x4333b0
00a24830 d845d8                   fadd      dword ptr [ebp - 0x28]
00a24833 d85ddc                   fcomp     dword ptr [ebp - 0x24]
00a24836 dfe0                     fnstsw    ax
00a24838 f6c441                   test      ah, 0x41
00a2483b 7517                     jne       0xa24854
00a2483d 8bcf                     mov       ecx, edi
00a2483f e86ceba0ff               call      0x4333b0
00a24844 d95d08                   fstp      dword ptr [ebp + 8]
00a24847 8b4df0                   mov       ecx, dword ptr [ebp - 0x10]
00a2484a e861eba0ff               call      0x4333b0
00a2484f d84508                   fadd      dword ptr [ebp + 8]
00a24852 eb16                     jmp       0xa2486a
00a24854 8b4d08                   mov       ecx, dword ptr [ebp + 8]
00a24857 e854eba0ff               call      0x4333b0
00a2485c d95d08                   fstp      dword ptr [ebp + 8]
00a2485f 8b4dec                   mov       ecx, dword ptr [ebp - 0x14]
00a24862 e849eba0ff               call      0x4333b0
00a24867 d84508                   fadd      dword ptr [ebp + 8]
00a2486a d95d08                   fstp      dword ptr [ebp + 8]
00a2486d 8bce                     mov       ecx, esi
00a2486f e83ceba0ff               call      0x4333b0
00a24874 d86d08                   fsubr     dword ptr [ebp + 8]
00a24877 8d4508                   lea       eax, [ebp + 8]
00a2487a 50                       push      eax
00a2487b 8d4b20                   lea       ecx, [ebx + 0x20]
00a2487e d95d08                   fstp      dword ptr [ebp + 8]
00a24881 e8dafc9dff               call      0x404560
00a24886 8b7dd4                   mov       edi, dword ptr [ebp - 0x2c]
00a24889 8bcf                     mov       ecx, edi
00a2488b e820eba0ff               call      0x4333b0
00a24890 d95d08                   fstp      dword ptr [ebp + 8]
00a24893 8b75fc                   mov       esi, dword ptr [ebp - 4]
00a24896 8bce                     mov       ecx, esi
00a24898 e813eba0ff               call      0x4333b0
00a2489d d85d08                   fcomp     dword ptr [ebp + 8]
00a248a0 dfe0                     fnstsw    ax
00a248a2 f6c405                   test      ah, 5
00a248a5 8bc7                     mov       eax, edi
00a248a7 7b02                     jnp       0xa248ab
00a248a9 8bc6                     mov       eax, esi
00a248ab 8d7310                   lea       esi, [ebx + 0x10]
00a248ae 50                       push      eax
00a248af 8bce                     mov       ecx, esi
00a248b1 e8fafc9dff               call      0x4045b0
00a248b6 8bcf                     mov       ecx, edi
00a248b8 e8f3eaa0ff               call      0x4333b0
00a248bd d95d08                   fstp      dword ptr [ebp + 8]
00a248c0 8b4de8                   mov       ecx, dword ptr [ebp - 0x18]
00a248c3 e8e8eaa0ff               call      0x4333b0
00a248c8 d84508                   fadd      dword ptr [ebp + 8]
00a248cb 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
00a248ce d95dd4                   fstp      dword ptr [ebp - 0x2c]
00a248d1 e8daeaa0ff               call      0x4333b0
00a248d6 d95d08                   fstp      dword ptr [ebp + 8]
00a248d9 8b4de4                   mov       ecx, dword ptr [ebp - 0x1c]
00a248dc e8cfeaa0ff               call      0x4333b0
00a248e1 d84508                   fadd      dword ptr [ebp + 8]
00a248e4 d85dd4                   fcomp     dword ptr [ebp - 0x2c]
00a248e7 dfe0                     fnstsw    ax
00a248e9 f6c441                   test      ah, 0x41
00a248ec 7517                     jne       0xa24905
00a248ee 8bcf                     mov       ecx, edi
00a248f0 e8bbeaa0ff               call      0x4333b0
00a248f5 d95d08                   fstp      dword ptr [ebp + 8]
00a248f8 8b4de8                   mov       ecx, dword ptr [ebp - 0x18]
00a248fb e8b0eaa0ff               call      0x4333b0
00a24900 d84508                   fadd      dword ptr [ebp + 8]
00a24903 eb16                     jmp       0xa2491b
00a24905 8b4dfc                   mov       ecx, dword ptr [ebp - 4]
00a24908 e8a3eaa0ff               call      0x4333b0
00a2490d d95d08                   fstp      dword ptr [ebp + 8]
00a24910 8b4de4                   mov       ecx, dword ptr [ebp - 0x1c]
00a24913 e898eaa0ff               call      0x4333b0
00a24918 d84508                   fadd      dword ptr [ebp + 8]
00a2491b d95d08                   fstp      dword ptr [ebp + 8]
00a2491e 8bce                     mov       ecx, esi
00a24920 e88beaa0ff               call      0x4333b0
00a24925 d86d08                   fsubr     dword ptr [ebp + 8]
00a24928 8d4d08                   lea       ecx, [ebp + 8]
00a2492b 51                       push      ecx
00a2492c 8d4b28                   lea       ecx, [ebx + 0x28]
00a2492f d95d08                   fstp      dword ptr [ebp + 8]
00a24932 e829fc9dff               call      0x404560
00a24937 5b                       pop       ebx
00a24938 5f                       pop       edi
00a24939 b001                     mov       al, 1
00a2493b 5e                       pop       esi
00a2493c 8be5                     mov       esp, ebp
00a2493e 5d                       pop       ebp
00a2493f c3                       ret       
00a24940 5f                       pop       edi
00a24941 32c0                     xor       al, al
00a24943 5e                       pop       esi
00a24944 8be5                     mov       esp, ebp
00a24946 5d                       pop       ebp
00a24947 c3                       ret       
00a24948 cc                       int3      
00a24949 cc                       int3      
00a2494a cc                       int3      
00a2494b cc                       int3      
00a2494c cc                       int3      
00a2494d cc                       int3      
00a2494e cc                       int3      
00a2494f cc                       int3      
00a24950 55                       push      ebp
00a24951 8bec                     mov       ebp, esp
00a24953 83ec14                   sub       esp, 0x14
00a24956 56                       push      esi
00a24957 8bf1                     mov       esi, ecx
00a24959 8a86c8000000             mov       al, byte ptr [esi + 0xc8]
00a2495f 84c0                     test      al, al
00a24961 0f8444020000             je        0xa24bab
00a24967 80be3a01000001           cmp       byte ptr [esi + 0x13a], 1
00a2496e 0f8437020000             je        0xa24bab
00a24974 8b8698000000             mov       eax, dword ptr [esi + 0x98]
00a2497a 85c0                     test      eax, eax
00a2497c 0f8429020000             je        0xa24bab
00a24982 8b8e9c000000             mov       ecx, dword ptr [esi + 0x9c]
00a24988 2bc8                     sub       ecx, eax
00a2498a b843082184               mov       eax, 0x84210843
00a2498f f7e9                     imul      ecx
00a24991 03d1                     add       edx, ecx
00a24993 c1fa06                   sar       edx, 6
00a24996 8bc2                     mov       eax, edx
00a24998 c1e81f                   shr       eax, 0x1f
00a2499b 03c2                     add       eax, edx
00a2499d 8945ec                   mov       dword ptr [ebp - 0x14], eax
00a249a0 0f8405020000             je        0xa24bab
00a249a6 8b8698000000             mov       eax, dword ptr [esi + 0x98]
00a249ac 85c0                     test      eax, eax
00a249ae 741b                     je        0xa249cb
00a249b0 8b8e9c000000             mov       ecx, dword ptr [esi + 0x9c]
00a249b6 2bc8                     sub       ecx, eax
00a249b8 b843082184               mov       eax, 0x84210843
00a249bd f7e9                     imul      ecx
00a249bf 03d1                     add       edx, ecx
00a249c1 c1fa06                   sar       edx, 6
00a249c4 8bc2                     mov       eax, edx
00a249c6 c1e81f                   shr       eax, 0x1f
00a249c9 03c2                     add       eax, edx
00a249cb 53                       push      ebx
00a249cc 8b9e24010000             mov       ebx, dword ptr [esi + 0x124]
00a249d2 48                       dec       eax
00a249d3 3bd8                     cmp       ebx, eax
00a249d5 7519                     jne       0xa249f0
00a249d7 8a8630010000             mov       al, byte ptr [esi + 0x130]
00a249dd 84c0                     test      al, al
00a249df 0f                       .byte     0x0f
