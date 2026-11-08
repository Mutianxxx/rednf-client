
<stdin>:	file format elf32-i386

Disassembly of section .text:

01137510 <.text>:
 1137510: 56                           	push	esi
 1137511: 57                           	push	edi
 1137512: 8b f1                        	mov	esi, ecx
 1137514: 68 78 21 56 01               	push	0x1562178
 1137519: c7 06 00 00 00 00            	mov	dword ptr [esi], 0x0
 113751f: e8 cc 89 06 00               	call	0x119fef0 <.text+0x689e0>
 1137524: 8b c8                        	mov	ecx, eax
 1137526: 83 c4 04                     	add	esp, 0x4
 1137529: 8d 79 02                     	lea	edi, [ecx + 0x2]
 113752c: 8d 64 24 00                  	lea	esp, [esp]
 1137530: 66 8b 11                     	mov	dx, word ptr [ecx]
 1137533: 83 c1 02                     	add	ecx, 0x2
 1137536: 66 85 d2                     	test	dx, dx
 1137539: 75 f5                        	jne	0x1137530 <.text+0x20>
 113753b: 2b cf                        	sub	ecx, edi
 113753d: d1 f9                        	sar	ecx
 113753f: 51                           	push	ecx
 1137540: 50                           	push	eax
 1137541: 8d 4e 04                     	lea	ecx, [esi + 0x4]
 1137544: e8 e7 8a 2d ff               	call	0x410030
 1137549: 68 78 21 56 01               	push	0x1562178
 113754e: e8 9d 89 06 00               	call	0x119fef0 <.text+0x689e0>
 1137553: 8b c8                        	mov	ecx, eax
 1137555: 83 c4 04                     	add	esp, 0x4
 1137558: 8d 79 02                     	lea	edi, [ecx + 0x2]
 113755b: eb 03                        	jmp	0x1137560 <.text+0x50>
 113755d: 8d 49 00                     	lea	ecx, [ecx]
 1137560: 66 8b 11                     	mov	dx, word ptr [ecx]
 1137563: 83 c1 02                     	add	ecx, 0x2
 1137566: 66 85 d2                     	test	dx, dx
 1137569: 75 f5                        	jne	0x1137560 <.text+0x50>
 113756b: 2b cf                        	sub	ecx, edi
 113756d: d1 f9                        	sar	ecx
 113756f: 51                           	push	ecx
 1137570: 50                           	push	eax
 1137571: 8d 4e 24                     	lea	ecx, [esi + 0x24]
 1137574: e8 b7 8a 2d ff               	call	0x410030
 1137579: 8d 4e 68                     	lea	ecx, [esi + 0x68]
 113757c: c7 46 64 00 00 00 00         	mov	dword ptr [esi + 0x64], 0x0
 1137583: e8 88 ff 60 ff               	call	0x747510
 1137588: 8d 8e 80 00 00 00            	lea	ecx, [esi + 0x80]
 113758e: c6 46 7c 00                  	mov	byte ptr [esi + 0x7c], 0x0
 1137592: e8 b9 1f 25 00               	call	0x1389550 <.text+0x252040>
 1137597: 8d 8e 94 00 00 00            	lea	ecx, [esi + 0x94]
 113759d: e8 3e 4c 19 00               	call	0x12cc1e0 <.text+0x194cd0>
 11375a2: 8d 8e a8 00 00 00            	lea	ecx, [esi + 0xa8]
 11375a8: e8 a3 1f 25 00               	call	0x1389550 <.text+0x252040>
 11375ad: 5f                           	pop	edi
 11375ae: 8d 8e bc 00 00 00            	lea	ecx, [esi + 0xbc]
 11375b4: 5e                           	pop	esi
 11375b5: e9 26 4c 19 00               	jmp	0x12cc1e0 <.text+0x194cd0>
 11375ba: cc                           	int3
 11375bb: cc                           	int3
 11375bc: cc                           	int3
 11375bd: cc                           	int3
 11375be: cc                           	int3
 11375bf: cc                           	int3
