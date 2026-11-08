
<stdin>:	file format elf32-i386

Disassembly of section .text:

011bf8e0 <.text>:
 11bf8e0: 3b 4b 34                     	cmp	ecx, dword ptr [ebx + 0x34]
 11bf8e3: 0f 84 82 00 00 00            	je	0x11bf96b <.text+0x8b>
 11bf8e9: 8b 56 34                     	mov	edx, dword ptr [esi + 0x34]
 11bf8ec: 89 15 08 25 a4 01            	mov	dword ptr [0x1a42508], edx
 11bf8f2: 8b 43 34                     	mov	eax, dword ptr [ebx + 0x34]
 11bf8f5: a3 04 25 a4 01               	mov	dword ptr [0x1a42504], eax
 11bf8fa: 8b f3                        	mov	esi, ebx
 11bf8fc: 57                           	push	edi
 11bf8fd: 8d 49 00                     	lea	ecx, [ecx]
 11bf900: 8b 7e 5c                     	mov	edi, dword ptr [esi + 0x5c]
 11bf903: 85 ff                        	test	edi, edi
 11bf905: 74 1d                        	je	0x11bf924 <.text+0x44>
 11bf907: 83 7e 08 02                  	cmp	dword ptr [esi + 0x8], 0x2
 11bf90b: 75 10                        	jne	0x11bf91d <.text+0x3d>
 11bf90d: 56                           	push	esi
 11bf90e: 8b cf                        	mov	ecx, edi
 11bf910: e8 db fe ff ff               	call	0x11bf7f0
 11bf915: 56                           	push	esi
 11bf916: 8b cf                        	mov	ecx, edi
 11bf918: e8 13 fa ff ff               	call	0x11bf330
 11bf91d: 8b 76 5c                     	mov	esi, dword ptr [esi + 0x5c]
 11bf920: 85 f6                        	test	esi, esi
 11bf922: 75 dc                        	jne	0x11bf900 <.text+0x20>
 11bf924: 83 7b 08 09                  	cmp	dword ptr [ebx + 0x8], 0x9
 11bf928: 5f                           	pop	edi
 11bf929: 75 2d                        	jne	0x11bf958 <.text+0x78>
 11bf92b: 8b 4b 34                     	mov	ecx, dword ptr [ebx + 0x34]
 11bf92e: 8b 45 fc                     	mov	eax, dword ptr [ebp - 0x4]
 11bf931: 89 0d 0c 25 a4 01            	mov	dword ptr [0x1a4250c], ecx
 11bf937: 8b 48 60                     	mov	ecx, dword ptr [eax + 0x60]
 11bf93a: 85 c9                        	test	ecx, ecx
 11bf93c: 74 0e                        	je	0x11bf94c <.text+0x6c>
 11bf93e: 8b 11                        	mov	edx, dword ptr [ecx]
 11bf940: 6a 00                        	push	0x0
 11bf942: 6a 00                        	push	0x0
 11bf944: 6a 16                        	push	0x16
 11bf946: 50                           	push	eax
 11bf947: 8b 42 04                     	mov	eax, dword ptr [edx + 0x4]
 11bf94a: ff d0                        	call	eax
 11bf94c: e8 3f 59 02 00               	call	0x11e5290 <.text+0x259b0>
 11bf951: e8 5a 5e 02 00               	call	0x11e57b0 <.text+0x25ed0>
 11bf956: eb 13                        	jmp	0x11bf96b <.text+0x8b>
 11bf958: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11bf95b: 83 79 08 0c                  	cmp	dword ptr [ecx + 0x8], 0xc
 11bf95f: 74 0a                        	je	0x11bf96b <.text+0x8b>
 11bf961: c7 05 18 25 a4 01 ff ff ff ff	mov	dword ptr [0x1a42518], 0xffffffff
 11bf96b: 8b 53 34                     	mov	edx, dword ptr [ebx + 0x34]
 11bf96e: 89 15 f0 24 a4 01            	mov	dword ptr [0x1a424f0], edx
 11bf974: 8b 4b 60                     	mov	ecx, dword ptr [ebx + 0x60]
 11bf977: 85 c9                        	test	ecx, ecx
 11bf979: 74 0e                        	je	0x11bf989 <.text+0xa9>
 11bf97b: 8b 01                        	mov	eax, dword ptr [ecx]
 11bf97d: 8b 50 04                     	mov	edx, dword ptr [eax + 0x4]
 11bf980: 6a 00                        	push	0x0
 11bf982: 6a 00                        	push	0x0
 11bf984: 6a 08                        	push	0x8
 11bf986: 53                           	push	ebx
 11bf987: ff d2                        	call	edx
 11bf989: a1 04 25 a4 01               	mov	eax, dword ptr [0x1a42504]
 11bf98e: 5e                           	pop	esi
 11bf98f: 5b                           	pop	ebx
 11bf990: 8b e5                        	mov	esp, ebp
 11bf992: 5d                           	pop	ebp
 11bf993: c2                           	<unknown>
