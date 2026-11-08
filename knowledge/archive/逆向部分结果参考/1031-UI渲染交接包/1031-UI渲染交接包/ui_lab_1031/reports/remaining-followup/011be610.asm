
<stdin>:	file format elf32-i386

Disassembly of section .text:

011be610 <.text>:
 11be610: 55                           	push	ebp
 11be611: 8b ec                        	mov	ebp, esp
 11be613: 56                           	push	esi
 11be614: 8b f1                        	mov	esi, ecx
 11be616: 8b 4e 60                     	mov	ecx, dword ptr [esi + 0x60]
 11be619: 85 c9                        	test	ecx, ecx
 11be61b: 74 40                        	je	0x11be65d <.text+0x4d>
 11be61d: 53                           	push	ebx
 11be61e: 8a 5d 08                     	mov	bl, byte ptr [ebp + 0x8]
 11be621: 3a 5e 0c                     	cmp	bl, byte ptr [esi + 0xc]
 11be624: 74 12                        	je	0x11be638 <.text+0x28>
 11be626: 84 db                        	test	bl, bl
 11be628: 75 0e                        	jne	0x11be638 <.text+0x28>
 11be62a: 8b 01                        	mov	eax, dword ptr [ecx]
 11be62c: 8b 50 04                     	mov	edx, dword ptr [eax + 0x4]
 11be62f: 6a 00                        	push	0x0
 11be631: 6a 00                        	push	0x0
 11be633: 6a 11                        	push	0x11
 11be635: 56                           	push	esi
 11be636: ff d2                        	call	edx
 11be638: 80 7e 0c 00                  	cmp	byte ptr [esi + 0xc], 0x0
 11be63c: 75 16                        	jne	0x11be654 <.text+0x44>
 11be63e: 80 fb 01                     	cmp	bl, 0x1
 11be641: 75 11                        	jne	0x11be654 <.text+0x44>
 11be643: 8b 4e 60                     	mov	ecx, dword ptr [esi + 0x60]
 11be646: 8b 01                        	mov	eax, dword ptr [ecx]
 11be648: 8b 50 04                     	mov	edx, dword ptr [eax + 0x4]
 11be64b: 6a 00                        	push	0x0
 11be64d: 6a 00                        	push	0x0
 11be64f: 6a 10                        	push	0x10
 11be651: 56                           	push	esi
 11be652: ff d2                        	call	edx
 11be654: 88 5e 0c                     	mov	byte ptr [esi + 0xc], bl
 11be657: 5b                           	pop	ebx
 11be658: 5e                           	pop	esi
 11be659: 5d                           	pop	ebp
 11be65a: c2 04 00                     	ret	0x4
 11be65d: 8a 45 08                     	mov	al, byte ptr [ebp + 0x8]
 11be660: 88 46 0c                     	mov	byte ptr [esi + 0xc], al
 11be663: 5e                           	pop	esi
 11be664: 5d                           	pop	ebp
 11be665: c2 04 00                     	ret	0x4
