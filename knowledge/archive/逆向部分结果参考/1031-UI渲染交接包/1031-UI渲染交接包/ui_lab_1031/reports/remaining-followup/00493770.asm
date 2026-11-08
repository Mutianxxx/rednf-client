
<stdin>:	file format elf32-i386

Disassembly of section .text:

00493770 <.text>:
  493770: 55                           	push	ebp
  493771: 8b ec                        	mov	ebp, esp
  493773: e9 3a c1 c5 01               	jmp	0x20ef8b2 <.text+0x1c5c142>
  493778: 08 57 8b                     	or	byte ptr [edi - 0x75], dl
  49377b: 7d 08                        	jge	0x493785 <.text+0x15>
  49377d: 3b f8                        	cmp	edi, eax
  49377f: 73 33                        	jae	0x4937b4 <.text+0x44>
  493781: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  493784: 3b cf                        	cmp	ecx, edi
  493786: 77 2c                        	ja	0x4937b4 <.text+0x44>
  493788: 2b f9                        	sub	edi, ecx
  49378a: c1 ff 02                     	sar	edi, 0x2
  49378d: 3b 46 0c                     	cmp	eax, dword ptr [esi + 0xc]
  493790: 75 09                        	jne	0x49379b <.text+0x2b>
  493792: 6a 01                        	push	0x1
  493794: 8b ce                        	mov	ecx, esi
  493796: e8 65 ed 0c 00               	call	0x562500 <.text+0xced90>
  49379b: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
  49379e: 85 c0                        	test	eax, eax
  4937a0: 74 2b                        	je	0x4937cd <.text+0x5d>
  4937a2: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  4937a5: 8b 14 b9                     	mov	edx, dword ptr [ecx + 4*edi]
  4937a8: 89 10                        	mov	dword ptr [eax], edx
  4937aa: 83 46 08 04                  	add	dword ptr [esi + 0x8], 0x4
  4937ae: 5f                           	pop	edi
  4937af: 5e                           	pop	esi
  4937b0: 5d                           	pop	ebp
  4937b1: c2 04 00                     	ret	0x4
  4937b4: 3b 46 0c                     	cmp	eax, dword ptr [esi + 0xc]
  4937b7: 75 09                        	jne	0x4937c2 <.text+0x52>
  4937b9: 6a 01                        	push	0x1
  4937bb: 8b ce                        	mov	ecx, esi
  4937bd: e8 3e ed 0c 00               	call	0x562500 <.text+0xced90>
  4937c2: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
  4937c5: 85 c0                        	test	eax, eax
  4937c7: 74 04                        	je	0x4937cd <.text+0x5d>
  4937c9: 8b 0f                        	mov	ecx, dword ptr [edi]
  4937cb: 89 08                        	mov	dword ptr [eax], ecx
  4937cd: 83 46 08 04                  	add	dword ptr [esi + 0x8], 0x4
  4937d1: 5f                           	pop	edi
  4937d2: 5e                           	pop	esi
  4937d3: 5d                           	pop	ebp
  4937d4: c2 04 00                     	ret	0x4
