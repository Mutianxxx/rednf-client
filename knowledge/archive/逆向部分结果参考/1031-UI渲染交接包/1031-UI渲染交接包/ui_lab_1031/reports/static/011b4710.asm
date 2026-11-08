
<stdin>:	file format elf32-i386

Disassembly of section .text:

011b4710 <.text>:
 11b4710: 55                           	push	ebp
 11b4711: 8b ec                        	mov	ebp, esp
 11b4713: 51                           	push	ecx
 11b4714: 33 d2                        	xor	edx, edx
 11b4716: 89 55 fc                     	mov	dword ptr [ebp - 0x4], edx
 11b4719: 8d 45 08                     	lea	eax, [ebp + 0x8]
 11b471c: 39 55 08                     	cmp	dword ptr [ebp + 0x8], edx
 11b471f: 7f 03                        	jg	0x11b4724 <.text+0x14>
 11b4721: 8d 45 fc                     	lea	eax, [ebp - 0x4]
 11b4724: 66 8b 00                     	mov	ax, word ptr [eax]
 11b4727: 66 89 41 28                  	mov	word ptr [ecx + 0x28], ax
 11b472b: 89 55 08                     	mov	dword ptr [ebp + 0x8], edx
 11b472e: 8d 45 0c                     	lea	eax, [ebp + 0xc]
 11b4731: 39 55 0c                     	cmp	dword ptr [ebp + 0xc], edx
 11b4734: 7f 03                        	jg	0x11b4739 <.text+0x29>
 11b4736: 8d 45 08                     	lea	eax, [ebp + 0x8]
 11b4739: 66 8b 00                     	mov	ax, word ptr [eax]
 11b473c: 66 89 41 2a                  	mov	word ptr [ecx + 0x2a], ax
 11b4740: 89 55 08                     	mov	dword ptr [ebp + 0x8], edx
 11b4743: 8d 45 10                     	lea	eax, [ebp + 0x10]
 11b4746: 39 55 10                     	cmp	dword ptr [ebp + 0x10], edx
 11b4749: 7f 03                        	jg	0x11b474e <.text+0x3e>
 11b474b: 8d 45 08                     	lea	eax, [ebp + 0x8]
 11b474e: 66 8b 00                     	mov	ax, word ptr [eax]
 11b4751: 66 89 41 2c                  	mov	word ptr [ecx + 0x2c], ax
 11b4755: 89 55 08                     	mov	dword ptr [ebp + 0x8], edx
 11b4758: 39 55 14                     	cmp	dword ptr [ebp + 0x14], edx
 11b475b: 7e 10                        	jle	0x11b476d <.text+0x5d>
 11b475d: 8d 45 14                     	lea	eax, [ebp + 0x14]
 11b4760: 66 8b 10                     	mov	dx, word ptr [eax]
 11b4763: 66 89 51 2e                  	mov	word ptr [ecx + 0x2e], dx
 11b4767: 8b e5                        	mov	esp, ebp
 11b4769: 5d                           	pop	ebp
 11b476a: c2 10 00                     	ret	0x10
 11b476d: 8d 45 08                     	lea	eax, [ebp + 0x8]
 11b4770: 66 8b 00                     	mov	ax, word ptr [eax]
 11b4773: 66 89 41 2e                  	mov	word ptr [ecx + 0x2e], ax
 11b4777: 8b e5                        	mov	esp, ebp
 11b4779: 5d                           	pop	ebp
 11b477a: c2 10 00                     	ret	0x10
 11b477d: cc                           	int3
 11b477e: cc                           	int3
 11b477f: cc                           	int3
 11b4780: 8b 41 44                     	mov	eax, dword ptr [ecx + 0x44]
 11b4783: 83 e0 01                     	and	eax, 0x1
 11b4786: c3                           	ret
 11b4787: cc                           	int3
 11b4788: cc                           	int3
 11b4789: cc                           	int3
 11b478a: cc                           	int3
 11b478b: cc                           	int3
 11b478c: cc                           	int3
 11b478d: cc                           	int3
 11b478e: cc                           	int3
 11b478f: cc                           	int3
 11b4790: 53                           	push	ebx
 11b4791: 33 db                        	xor	ebx, ebx
 11b4793: 56                           	push	esi
 11b4794: 8b f1                        	mov	esi, ecx
 11b4796: 33 d2                        	xor	edx, edx
 11b4798: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11b479b: 89 5e 48                     	mov	dword ptr [esi + 0x48], ebx
 11b479e: 83 66 44 fe                  	and	dword ptr [esi + 0x44], -0x2
 11b47a2: 89 56 20                     	mov	dword ptr [esi + 0x20], edx
 11b47a5: 33 c0                        	xor	eax, eax
 11b47a7: 33 c9                        	xor	ecx, ecx
 11b47a9: 89 46 1c                     	mov	dword ptr [esi + 0x1c], eax
 11b47ac: 89 4e 24                     	mov	dword ptr [esi + 0x24], ecx
 11b47af: c7 46 18 00 00 01 00         	mov	dword ptr [esi + 0x18], 0x10000
 11b47b6: 89 5e 4c                     	mov	dword ptr [esi + 0x4c], ebx
 11b47b9: 66 0f ef c0                  	pxor	xmm0, xmm0
 11b47bd: 66 0f d6 46 28               	movq	qword ptr [esi + 0x28], xmm0
 11b47c2: 8a 56 58                     	mov	dl, byte ptr [esi + 0x58]
 11b47c5: 80 e2 f2                     	and	dl, -0xe
 11b47c8: 89 5e 50                     	mov	dword ptr [esi + 0x50], ebx
 11b47cb: 80 ca 02                     	or	dl, 0x2
 11b47ce: 88 5e 50                     	mov	byte ptr [esi + 0x50], bl
 11b47d1: 81 4e 50 00 03 00 00         	or	dword ptr [esi + 0x50], 0x300
 11b47d8: 88 56 58                     	mov	byte ptr [esi + 0x58], dl
 11b47db: ff 15 88 a5 55 01            	call	dword ptr [0x155a588]
 11b47e1: 89 46 54                     	mov	dword ptr [esi + 0x54], eax
 11b47e4: 8a 46 58                     	mov	al, byte ptr [esi + 0x58]
 11b47e7: 24 f0                        	and	al, -0x10
 11b47e9: 0c 10                        	or	al, 0x10
 11b47eb: 88 5e 40                     	mov	byte ptr [esi + 0x40], bl
 11b47ee: 88 46 58                     	mov	byte ptr [esi + 0x58], al
 11b47f1: 5e                           	pop	esi
 11b47f2: 5b                           	pop	ebx
 11b47f3: c3                           	ret
 11b47f4: cc                           	int3
 11b47f5: cc                           	int3
 11b47f6: cc                           	int3
 11b47f7: cc                           	int3
 11b47f8: cc                           	int3
 11b47f9: cc                           	int3
 11b47fa: cc                           	int3
 11b47fb: cc                           	int3
 11b47fc: cc                           	int3
 11b47fd: cc                           	int3
 11b47fe: cc                           	int3
 11b47ff: cc                           	int3
 11b4800: 55                           	push	ebp
 11b4801: 8b ec                        	mov	ebp, esp
 11b4803: 56                           	push	esi
 11b4804: 8b f1                        	mov	esi, ecx
 11b4806: e8 35 7c 01 00               	call	0x11cc440 <.text+0x17d30>
 11b480b: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b480e: c7 06 0c 9e 85 01            	mov	dword ptr [esi], 0x1859e0c
 11b4814: 89 46 08                     	mov	dword ptr [esi + 0x8], eax
 11b4817: 8b ce                        	mov	ecx, esi
 11b4819: c7 46 44 00 00 00 00         	mov	dword ptr [esi + 0x44], 0x0
 11b4820: e8 6b ff ff ff               	call	0x11b4790 <.text+0x80>
 11b4825: 8b c6                        	mov	eax, esi
 11b4827: 5e                           	pop	esi
 11b4828: 5d                           	pop	ebp
 11b4829: c2 04 00                     	ret	0x4
 11b482c: cc                           	int3
 11b482d: cc                           	int3
 11b482e: cc                           	int3
 11b482f: cc                           	int3
