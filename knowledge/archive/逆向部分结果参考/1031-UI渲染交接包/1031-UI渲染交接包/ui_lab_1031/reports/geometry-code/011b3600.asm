
<stdin>:	file format elf32-i386

Disassembly of section .text:

011b3600 <.text>:
 11b3600: 55                           	push	ebp
 11b3601: 8b ec                        	mov	ebp, esp
 11b3603: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b3606: 66 8b 4d 0c                  	mov	cx, word ptr [ebp + 0xc]
 11b360a: 66 8b 55 10                  	mov	dx, word ptr [ebp + 0x10]
 11b360e: 66 89 08                     	mov	word ptr [eax], cx
 11b3611: 66 8b 4d 14                  	mov	cx, word ptr [ebp + 0x14]
 11b3615: 66 89 50 02                  	mov	word ptr [eax + 0x2], dx
 11b3619: 66 8b 55 18                  	mov	dx, word ptr [ebp + 0x18]
 11b361d: 66 89 48 04                  	mov	word ptr [eax + 0x4], cx
 11b3621: 66 89 50 06                  	mov	word ptr [eax + 0x6], dx
 11b3625: 5d                           	pop	ebp
 11b3626: c3                           	ret
 11b3627: cc                           	int3
 11b3628: cc                           	int3
 11b3629: cc                           	int3
 11b362a: cc                           	int3
 11b362b: cc                           	int3
 11b362c: cc                           	int3
 11b362d: cc                           	int3
 11b362e: cc                           	int3
 11b362f: cc                           	int3
 11b3630: 8b 01                        	mov	eax, dword ptr [ecx]
 11b3632: 8b 90 a4 00 00 00            	mov	edx, dword ptr [eax + 0xa4]
 11b3638: ff e2                        	jmp	edx
 11b363a: cc                           	int3
 11b363b: cc                           	int3
 11b363c: cc                           	int3
 11b363d: cc                           	int3
 11b363e: cc                           	int3
 11b363f: cc                           	int3
 11b3640: 55                           	push	ebp
 11b3641: 8b ec                        	mov	ebp, esp
 11b3643: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 11b3646: 0f bf 08                     	movsx	ecx, word ptr [eax]
 11b3649: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11b364c: 3b d1                        	cmp	edx, ecx
 11b364e: 7d 06                        	jge	0x11b3656 <.text+0x56>
 11b3650: b0 01                        	mov	al, 0x1
 11b3652: 5d                           	pop	ebp
 11b3653: c2 0c 00                     	ret	0xc
 11b3656: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11b3659: 56                           	push	esi
 11b365a: 0f bf 70 02                  	movsx	esi, word ptr [eax + 0x2]
 11b365e: 3b ce                        	cmp	ecx, esi
 11b3660: 7c 08                        	jl	0x11b366a <.text+0x6a>
 11b3662: 0f bf 70 04                  	movsx	esi, word ptr [eax + 0x4]
 11b3666: 3b d6                        	cmp	edx, esi
 11b3668: 7c 07                        	jl	0x11b3671 <.text+0x71>
 11b366a: b0 01                        	mov	al, 0x1
 11b366c: 5e                           	pop	esi
 11b366d: 5d                           	pop	ebp
 11b366e: c2 0c 00                     	ret	0xc
 11b3671: 0f bf 50 06                  	movsx	edx, word ptr [eax + 0x6]
 11b3675: 3b ca                        	cmp	ecx, edx
 11b3677: 0f 9d c0                     	setge	al
 11b367a: 5e                           	pop	esi
 11b367b: 5d                           	pop	ebp
 11b367c: c2 0c 00                     	ret	0xc
 11b367f: cc                           	int3
 11b3680: 8d 41 28                     	lea	eax, [ecx + 0x28]
 11b3683: c3                           	ret
 11b3684: cc                           	int3
 11b3685: cc                           	int3
 11b3686: cc                           	int3
 11b3687: cc                           	int3
 11b3688: cc                           	int3
 11b3689: cc                           	int3
 11b368a: cc                           	int3
 11b368b: cc                           	int3
 11b368c: cc                           	int3
 11b368d: cc                           	int3
 11b368e: cc                           	int3
 11b368f: cc                           	int3
 11b3690: 0f bf 41 28                  	movsx	eax, word ptr [ecx + 0x28]
 11b3694: a3 30 58 b5 01               	mov	dword ptr [0x1b55830], eax
 11b3699: 0f bf 51 2a                  	movsx	edx, word ptr [ecx + 0x2a]
 11b369d: 89 15 34 58 b5 01            	mov	dword ptr [0x1b55834], edx
 11b36a3: 0f bf 41 2c                  	movsx	eax, word ptr [ecx + 0x2c]
 11b36a7: a3 38 58 b5 01               	mov	dword ptr [0x1b55838], eax
 11b36ac: 0f bf 49 2e                  	movsx	ecx, word ptr [ecx + 0x2e]
 11b36b0: 89 0d 3c 58 b5 01            	mov	dword ptr [0x1b5583c], ecx
 11b36b6: b8 30 58 b5 01               	mov	eax, 0x1b55830
 11b36bb: c3                           	ret
 11b36bc: cc                           	int3
 11b36bd: cc                           	int3
 11b36be: cc                           	int3
 11b36bf: cc                           	int3
 11b36c0: 55                           	push	ebp
 11b36c1: 8b ec                        	mov	ebp, esp
 11b36c3: 8b 45 18                     	mov	eax, dword ptr [ebp + 0x18]
 11b36c6: 8b 4d 14                     	mov	ecx, dword ptr [ebp + 0x14]
 11b36c9: 8b 55 10                     	mov	edx, dword ptr [ebp + 0x10]
 11b36cc: 50                           	push	eax
 11b36cd: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11b36d0: 51                           	push	ecx
 11b36d1: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11b36d4: 52                           	push	edx
 11b36d5: 50                           	push	eax
 11b36d6: 51                           	push	ecx
 11b36d7: e8 64 fe 03 00               	call	0x11f3540 <.text+0x3ff40>
 11b36dc: 8b c8                        	mov	ecx, eax
 11b36de: e8                           	<unknown>
 11b36df: dd                           	<unknown>
