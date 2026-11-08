
<stdin>:	file format elf32-i386

Disassembly of section .text:

004eaf70 <.text>:
  4eaf70: 55                           	push	ebp
  4eaf71: 8b ec                        	mov	ebp, esp
  4eaf73: 6a ff                        	push	-0x1
  4eaf75: 68 20 35 41 01               	push	0x1413520
  4eaf7a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  4eaf80: 50                           	push	eax
  4eaf81: 83 ec 74                     	sub	esp, 0x74
  4eaf84: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  4eaf89: 33 c5                        	xor	eax, ebp
  4eaf8b: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
  4eaf8e: 53                           	push	ebx
  4eaf8f: 56                           	push	esi
  4eaf90: 57                           	push	edi
  4eaf91: 50                           	push	eax
  4eaf92: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  4eaf95: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  4eaf9b: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
  4eaf9e: 53                           	push	ebx
  4eaf9f: 8d 45 9c                     	lea	eax, [ebp - 0x64]
  4eafa2: 50                           	push	eax
  4eafa3: 8b f1                        	mov	esi, ecx
  4eafa5: e8 06 c9 ff ff               	call	0x4e78b0
  4eafaa: 8d 4d 90                     	lea	ecx, [ebp - 0x70]
  4eafad: 51                           	push	ecx
  4eafae: 8b ce                        	mov	ecx, esi
  4eafb0: e8 db 47 2c 00               	call	0x7af790 <.text+0x2c4820>
  4eafb5: 8b 7d 9c                     	mov	edi, dword ptr [ebp - 0x64]
  4eafb8: 85 ff                        	test	edi, edi
  4eafba: 0f 84 0d 01 00 00            	je	0x4eb0cd <.text+0x15d>
  4eafc0: 8b 17                        	mov	edx, dword ptr [edi]
  4eafc2: 85 d2                        	test	edx, edx
  4eafc4: 0f 84 03 01 00 00            	je	0x4eb0cd <.text+0x15d>
  4eafca: 8b 08                        	mov	ecx, dword ptr [eax]
  4eafcc: 85 c9                        	test	ecx, ecx
  4eafce: 74 02                        	je	0x4eafd2 <.text+0x62>
  4eafd0: 8b 09                        	mov	ecx, dword ptr [ecx]
  4eafd2: 3b d1                        	cmp	edx, ecx
  4eafd4: 0f 85 f3 00 00 00            	jne	0x4eb0cd <.text+0x15d>
  4eafda: 8b 4d a4                     	mov	ecx, dword ptr [ebp - 0x5c]
  4eafdd: 3b 48 08                     	cmp	ecx, dword ptr [eax + 0x8]
  4eafe0: 0f 94 c0                     	sete	al
  4eafe3: 84 c0                        	test	al, al
  4eafe5: 0f 84 cf 00 00 00            	je	0x4eb0ba <.text+0x14a>
  4eafeb: 6a 08                        	push	0x8
  4eafed: c7 45 d0 00 00 00 00         	mov	dword ptr [ebp - 0x30], 0x0
  4eaff4: e8 21 bb ee 00               	call	0x13d6b1a <.text+0xeebbaa>
  4eaff9: 33 c9                        	xor	ecx, ecx
  4eaffb: 83 c4 04                     	add	esp, 0x4
  4eaffe: 3b c1                        	cmp	eax, ecx
  4eb000: 0f 84 cc 00 00 00            	je	0x4eb0d2 <.text+0x162>
  4eb006: 89 45 d0                     	mov	dword ptr [ebp - 0x30], eax
  4eb009: 89 08                        	mov	dword ptr [eax], ecx
  4eb00b: 33 d2                        	xor	edx, edx
  4eb00d: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
  4eb010: 8b 45 d0                     	mov	eax, dword ptr [ebp - 0x30]
  4eb013: 8d 55 d0                     	lea	edx, [ebp - 0x30]
  4eb016: 89 10                        	mov	dword ptr [eax], edx
  4eb018: 33 c0                        	xor	eax, eax
  4eb01a: c7 45 e8 07 00 00 00         	mov	dword ptr [ebp - 0x18], 0x7
  4eb021: 89 45 e4                     	mov	dword ptr [ebp - 0x1c], eax
  4eb024: 66 89 4d d4                  	mov	word ptr [ebp - 0x2c], cx
  4eb028: 52                           	push	edx
  4eb029: 53                           	push	ebx
  4eb02a: 8d 4d ac                     	lea	ecx, [ebp - 0x54]
  4eb02d: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
  4eb030: e8 cb d1 ff ff               	call	0x4e8200
  4eb035: 50                           	push	eax
  4eb036: 8d 45 80                     	lea	eax, [ebp - 0x80]
  4eb039: 50                           	push	eax
  4eb03a: 8b ce                        	mov	ecx, esi
  4eb03c: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
  4eb040: e8 eb e0 ff ff               	call	0x4e9130
  4eb045: 8b 08                        	mov	ecx, dword ptr [eax]
  4eb047: 33 db                        	xor	ebx, ebx
  4eb049: 3b f9                        	cmp	edi, ecx
  4eb04b: 74 08                        	je	0x4eb055 <.text+0xe5>
  4eb04d: 8b 09                        	mov	ecx, dword ptr [ecx]
  4eb04f: 3b cb                        	cmp	ecx, ebx
  4eb051: 74 02                        	je	0x4eb055 <.text+0xe5>
  4eb053: 8b 39                        	mov	edi, dword ptr [ecx]
  4eb055: 83 7d c8 08                  	cmp	dword ptr [ebp - 0x38], 0x8
  4eb059: 8b 48 08                     	mov	ecx, dword ptr [eax + 0x8]
  4eb05c: 89 4d a4                     	mov	dword ptr [ebp - 0x5c], ecx
  4eb05f: 72 0c                        	jb	0x4eb06d <.text+0xfd>
  4eb061: 8b 55 b4                     	mov	edx, dword ptr [ebp - 0x4c]
  4eb064: 52                           	push	edx
  4eb065: e8 bd aa ee 00               	call	0x13d5b27 <.text+0xeeabb7>
  4eb06a: 83 c4 04                     	add	esp, 0x4
  4eb06d: 8b 4d b0                     	mov	ecx, dword ptr [ebp - 0x50]
  4eb070: 33 c0                        	xor	eax, eax
  4eb072: be 07 00 00 00               	mov	esi, 0x7
  4eb077: 51                           	push	ecx
  4eb078: 89 75 c8                     	mov	dword ptr [ebp - 0x38], esi
  4eb07b: 89 5d c4                     	mov	dword ptr [ebp - 0x3c], ebx
  4eb07e: 66 89 45 b4                  	mov	word ptr [ebp - 0x4c], ax
  4eb082: e8 a0 aa ee 00               	call	0x13d5b27 <.text+0xeeabb7>
  4eb087: 83 c4 04                     	add	esp, 0x4
  4eb08a: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
  4eb08e: 89 5d b0                     	mov	dword ptr [ebp - 0x50], ebx
  4eb091: 72 0c                        	jb	0x4eb09f <.text+0x12f>
  4eb093: 8b 55 d4                     	mov	edx, dword ptr [ebp - 0x2c]
  4eb096: 52                           	push	edx
  4eb097: e8 8b aa ee 00               	call	0x13d5b27 <.text+0xeeabb7>
  4eb09c: 83 c4 04                     	add	esp, 0x4
  4eb09f: 8b 4d d0                     	mov	ecx, dword ptr [ebp - 0x30]
  4eb0a2: 33 c0                        	xor	eax, eax
  4eb0a4: 51                           	push	ecx
  4eb0a5: 89 75 e8                     	mov	dword ptr [ebp - 0x18], esi
  4eb0a8: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
  4eb0ab: 66 89 45 d4                  	mov	word ptr [ebp - 0x2c], ax
  4eb0af: e8 73 aa ee 00               	call	0x13d5b27 <.text+0xeeabb7>
  4eb0b4: 8b 4d a4                     	mov	ecx, dword ptr [ebp - 0x5c]
  4eb0b7: 83 c4 04                     	add	esp, 0x4
  4eb0ba: 85 ff                        	test	edi, edi
  4eb0bc: 74 0f                        	je	0x4eb0cd <.text+0x15d>
  4eb0be: 8b 3f                        	mov	edi, dword ptr [edi]
  4eb0c0: 85 ff                        	test	edi, edi
  4eb0c2: 74 09                        	je	0x4eb0cd <.text+0x15d>
  4eb0c4: 85 c9                        	test	ecx, ecx
  4eb0c6: 74 05                        	je	0x4eb0cd <.text+0x15d>
  4eb0c8: 3b 4f 04                     	cmp	ecx, dword ptr [edi + 0x4]
  4eb0cb: 75 29                        	jne	0x4eb0f6 <.text+0x186>
  4eb0cd: e8 d5 bc ee 00               	call	0x13d6da7 <.text+0xeebe37>
  4eb0d2: 8d 55 a8                     	lea	edx, [ebp - 0x58]
  4eb0d5: 89 4d a8                     	mov	dword ptr [ebp - 0x58], ecx
  4eb0d8: 52                           	push	edx
  4eb0d9: 8d 4d 90                     	lea	ecx, [ebp - 0x70]
  4eb0dc: e8 e9 b3 ee 00               	call	0x13d64ca <.text+0xeeb55a>
  4eb0e1: 68 90 0f 91 01               	push	0x1910f90
  4eb0e6: 8d 45 90                     	lea	eax, [ebp - 0x70]
  4eb0e9: 50                           	push	eax
  4eb0ea: c7 45 90 84 20 56 01         	mov	dword ptr [ebp - 0x70], 0x1562084
  4eb0f1: e8 a4 ba ee 00               	call	0x13d6b9a <.text+0xeebc2a>
  4eb0f6: 8d 41 0c                     	lea	eax, [ecx + 0xc]
  4eb0f9: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  4eb0fc: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  4eb103: 59                           	pop	ecx
  4eb104: 5f                           	pop	edi
  4eb105: 5e                           	pop	esi
  4eb106: 5b                           	pop	ebx
  4eb107: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
  4eb10a: 33 cd                        	xor	ecx, ebp
  4eb10c: e8 c7 c0 ee 00               	call	0x13d71d8 <.text+0xeec268>
  4eb111: 8b e5                        	mov	esp, ebp
  4eb113: 5d                           	pop	ebp
  4eb114: c2 04 00                     	ret	0x4
