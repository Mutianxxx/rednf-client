
<stdin>:	file format elf32-i386

Disassembly of section .text:

01314420 <.text>:
 1314420: 55                           	push	ebp
 1314421: 8b ec                        	mov	ebp, esp
 1314423: 6a ff                        	push	-0x1
 1314425: 68 62 59 42 01               	push	0x1425962
 131442a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1314430: 50                           	push	eax
 1314431: 51                           	push	ecx
 1314432: 56                           	push	esi
 1314433: 57                           	push	edi
 1314434: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 1314439: 33 c5                        	xor	eax, ebp
 131443b: 50                           	push	eax
 131443c: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 131443f: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 1314445: 8b f9                        	mov	edi, ecx
 1314447: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
 131444a: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 131444d: 3b f1                        	cmp	esi, ecx
 131444f: 73 4e                        	jae	0x131449f <.text+0x7f>
 1314451: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
 1314454: 3b c6                        	cmp	eax, esi
 1314456: 77 47                        	ja	0x131449f <.text+0x7f>
 1314458: 2b f0                        	sub	esi, eax
 131445a: b8 89 88 88 88               	mov	eax, 0x88888889
 131445f: f7 ee                        	imul	esi
 1314461: 03 d6                        	add	edx, esi
 1314463: c1 fa 05                     	sar	edx, 0x5
 1314466: 8b f2                        	mov	esi, edx
 1314468: c1 ee 1f                     	shr	esi, 0x1f
 131446b: 03 f2                        	add	esi, edx
 131446d: 3b 4f 0c                     	cmp	ecx, dword ptr [edi + 0xc]
 1314470: 75 09                        	jne	0x131447b <.text+0x5b>
 1314472: 6a 01                        	push	0x1
 1314474: 8b cf                        	mov	ecx, edi
 1314476: e8 c5 fc ff ff               	call	0x1314140
 131447b: 8b 4f 04                     	mov	ecx, dword ptr [edi + 0x4]
 131447e: 8b c6                        	mov	eax, esi
 1314480: c1 e0 04                     	shl	eax, 0x4
 1314483: 2b c6                        	sub	eax, esi
 1314485: 8d 04 81                     	lea	eax, [ecx + 4*eax]
 1314488: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
 131448b: 89 4d 08                     	mov	dword ptr [ebp + 0x8], ecx
 131448e: 89 4d f0                     	mov	dword ptr [ebp - 0x10], ecx
 1314491: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 1314498: 85 c9                        	test	ecx, ecx
 131449a: 74 2b                        	je	0x13144c7 <.text+0xa7>
 131449c: 50                           	push	eax
 131449d: eb 23                        	jmp	0x13144c2 <.text+0xa2>
 131449f: 3b 4f 0c                     	cmp	ecx, dword ptr [edi + 0xc]
 13144a2: 75 09                        	jne	0x13144ad <.text+0x8d>
 13144a4: 6a 01                        	push	0x1
 13144a6: 8b cf                        	mov	ecx, edi
 13144a8: e8 93 fc ff ff               	call	0x1314140
 13144ad: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
 13144b0: 89 4d 08                     	mov	dword ptr [ebp + 0x8], ecx
 13144b3: 89 4d f0                     	mov	dword ptr [ebp - 0x10], ecx
 13144b6: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
 13144bd: 85 c9                        	test	ecx, ecx
 13144bf: 74 06                        	je	0x13144c7 <.text+0xa7>
 13144c1: 56                           	push	esi
 13144c2: e8 f9 29 e2 ff               	call	0x1136ec0
 13144c7: 83 47 08 3c                  	add	dword ptr [edi + 0x8], 0x3c
 13144cb: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 13144ce: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 13144d5: 59                           	pop	ecx
 13144d6: 5f                           	pop	edi
 13144d7: 5e                           	pop	esi
 13144d8: 8b e5                        	mov	esp, ebp
 13144da: 5d                           	pop	ebp
 13144db: c2 04 00                     	ret	0x4
