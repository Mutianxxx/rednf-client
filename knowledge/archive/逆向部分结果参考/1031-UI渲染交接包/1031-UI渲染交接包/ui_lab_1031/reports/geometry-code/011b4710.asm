
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
 11b479e: 83 66                        	<unknown>
