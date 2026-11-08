
<stdin>:	file format elf32-i386

Disassembly of section .text:

01225150 <.text>:
 1225150: 55                           	push	ebp
 1225151: 8b ec                        	mov	ebp, esp
 1225153: 53                           	push	ebx
 1225154: 56                           	push	esi
 1225155: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 122515a: 32 db                        	xor	bl, bl
 122515c: e8 4f 03 f8 ff               	call	0x11a54b0
 1225161: 83 e8 07                     	sub	eax, 0x7
 1225164: 74 60                        	je	0x12251c6 <.text+0x76>
 1225166: 83 e8 02                     	sub	eax, 0x2
 1225169: 0f 85 90 00 00 00            	jne	0x12251ff <.text+0xaf>
 122516f: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1225174: e8 07 05 f8 ff               	call	0x11a5680
 1225179: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 122517e: 8b f0                        	mov	esi, eax
 1225180: e8 2b 03 f8 ff               	call	0x11a54b0
 1225185: 83 f8 0a                     	cmp	eax, 0xa
 1225188: 75 75                        	jne	0x12251ff <.text+0xaf>
 122518a: 6a 00                        	push	0x0
 122518c: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1225191: e8 8a 05 f8 ff               	call	0x11a5720
 1225196: 50                           	push	eax
 1225197: 56                           	push	esi
 1225198: b9 68 d4 d2 01               	mov	ecx, 0x1d2d468
 122519d: e8 2e 47 0a 00               	call	0x12c98d0 <.text+0xa4780>
 12251a2: 8b c8                        	mov	ecx, eax
 12251a4: 8d 71 02                     	lea	esi, [ecx + 0x2]
 12251a7: 66 8b 11                     	mov	dx, word ptr [ecx]
 12251aa: 83 c1 02                     	add	ecx, 0x2
 12251ad: 66 85 d2                     	test	dx, dx
 12251b0: 75 f5                        	jne	0x12251a7 <.text+0x57>
 12251b2: 2b ce                        	sub	ecx, esi
 12251b4: d1 f9                        	sar	ecx
 12251b6: 51                           	push	ecx
 12251b7: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 12251ba: 50                           	push	eax
 12251bb: e8 70 ae 1e ff               	call	0x410030
 12251c0: 5e                           	pop	esi
 12251c1: b0 01                        	mov	al, 0x1
 12251c3: 5b                           	pop	ebx
 12251c4: 5d                           	pop	ebp
 12251c5: c3                           	ret
 12251c6: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 12251cb: e8 90 04 f8 ff               	call	0x11a5660
 12251d0: 50                           	push	eax
 12251d1: e8 aa ad f7 ff               	call	0x119ff80
 12251d6: 8b c8                        	mov	ecx, eax
 12251d8: 83 c4 04                     	add	esp, 0x4
 12251db: 8d 71 02                     	lea	esi, [ecx + 0x2]
 12251de: 8b ff                        	mov	edi, edi
 12251e0: 66 8b 11                     	mov	dx, word ptr [ecx]
 12251e3: 83 c1 02                     	add	ecx, 0x2
 12251e6: 66 85 d2                     	test	dx, dx
 12251e9: 75 f5                        	jne	0x12251e0 <.text+0x90>
 12251eb: 2b ce                        	sub	ecx, esi
 12251ed: d1 f9                        	sar	ecx
 12251ef: 51                           	push	ecx
 12251f0: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 12251f3: 50                           	push	eax
 12251f4: e8 37 ae 1e ff               	call	0x410030
 12251f9: 5e                           	pop	esi
 12251fa: b0 01                        	mov	al, 0x1
 12251fc: 5b                           	pop	ebx
 12251fd: 5d                           	pop	ebp
 12251fe: c3                           	ret
 12251ff: 5e                           	pop	esi
 1225200: 8a c3                        	mov	al, bl
 1225202: 5b                           	pop	ebx
 1225203: 5d                           	pop	ebp
 1225204: c3                           	ret
