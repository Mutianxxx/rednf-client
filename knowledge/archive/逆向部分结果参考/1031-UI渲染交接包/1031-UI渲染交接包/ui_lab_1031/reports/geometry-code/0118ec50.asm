
<stdin>:	file format elf32-i386

Disassembly of section .text:

0118ec50 <.text>:
 118ec50: 3b 87 c4 04 00 00            	cmp	eax, dword ptr [edi + 0x4c4]
 118ec56: 0f 85 46 02 00 00            	jne	0x118eea2 <.text+0x252>
 118ec5c: e8 af 77 57 ff               	call	0x706410
 118ec61: 8b c8                        	mov	ecx, eax
 118ec63: e8 08 d8 5c ff               	call	0x75c470
 118ec68: 83 f8 01                     	cmp	eax, 0x1
 118ec6b: 75 4a                        	jne	0x118ecb7 <.text+0x67>
 118ec6d: 8b 8f c4 04 00 00            	mov	ecx, dword ptr [edi + 0x4c4]
 118ec73: e8 68 e3 79 ff               	call	0x92cfe0
 118ec78: 84 c0                        	test	al, al
 118ec7a: 74 3b                        	je	0x118ecb7 <.text+0x67>
 118ec7c: 80 bf c9 04 00 00 00         	cmp	byte ptr [edi + 0x4c9], 0x0
 118ec83: 74 32                        	je	0x118ecb7 <.text+0x67>
 118ec85: 8b 8f cc 04 00 00            	mov	ecx, dword ptr [edi + 0x4cc]
 118ec8b: 85 c9                        	test	ecx, ecx
 118ec8d: 74 28                        	je	0x118ecb7 <.text+0x67>
 118ec8f: 83 bf c4 04 00 00 00         	cmp	dword ptr [edi + 0x4c4], 0x0
 118ec96: 74 1f                        	je	0x118ecb7 <.text+0x67>
 118ec98: e8 23 d8 f0 ff               	call	0x109c4c0
 118ec9d: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 118eca3: 6a 01                        	push	0x1
 118eca5: 6a 00                        	push	0x0
 118eca7: 6a 01                        	push	0x1
 118eca9: 6a 01                        	push	0x1
 118ecab: 51                           	push	ecx
 118ecac: 8b 8f cc 04 00 00            	mov	ecx, dword ptr [edi + 0x4cc]
 118ecb2: e8 c9 78 f0 ff               	call	0x1096580
 118ecb7: 8b 8f c4 04 00 00            	mov	ecx, dword ptr [edi + 0x4c4]
 118ecbd: e8 1e e3 79 ff               	call	0x92cfe0
 118ecc2: 84 c0                        	test	al, al
 118ecc4: 0f 84 d8 01 00 00            	je	0x118eea2 <.text+0x252>
 118ecca: 8b 0d e4 cd a4 01            	mov	ecx, dword ptr [0x1a4cde4]
 118ecd0: 6a 00                        	push	0x0
 118ecd2: 68 0c b6 9d 01               	push	0x19db60c
 118ecd7: 68 dc a7 9d 01               	push	0x19da7dc
 118ecdc: 6a 00                        	push	0x0
 118ecde: 6a 00                        	push	0x0
 118ece0: e8 fb c7 3a ff               	call	0x53b4e0
 118ece5: 50                           	push	eax
 118ece6: e8 f4 89 24 00               	call	0x13d76df <.text+0x248a8f>
 118eceb: 8b f0                        	mov	esi, eax
 118eced: 83 c4 14                     	add	esp, 0x14
 118ecf0: 85 f6                        	test	esi, esi
 118ecf2: 0f 84 aa 01 00 00            	je	0x118eea2 <.text+0x252>
 118ecf8: 8b ce                        	mov	ecx, esi
 118ecfa: e8 91 be fb ff               	call	0x114ab90
 118ecff: 85 c0                        	test	eax, eax
 118ed01: 0f 84 9b 01 00 00            	je	0x118eea2 <.text+0x252>
 118ed07: 8b ce                        	mov	ecx, esi
 118ed09: e8 82 be fb ff               	call	0x114ab90
 118ed0e: 8b 58 08                     	mov	ebx, dword ptr [eax + 0x8]
 118ed11: 2b 58 04                     	sub	ebx, dword ptr [eax + 0x4]
 118ed14: c1 fb 02                     	sar	ebx, 0x2
 118ed17: 85 db                        	test	ebx, ebx
 118ed19: 0f 8e 83 01 00 00            	jle	0x118eea2 <.text+0x252>
 118ed1f: 8b 8f c4 04 00 00            	mov	ecx, dword ptr [edi + 0x4c4]
 118ed25: e8 36 12 2a ff               	call	0x42ff60
 118ed2a: 8b 8f c4 04 00 00            	mov	ecx, dword ptr [edi + 0x4c4]
 118ed30: 8d 70 fc                     	lea	esi, [eax - 0x4]
 118ed33: e8 28 12 2a ff               	call	0x42ff60
 118ed38: 8b 15 e4 64 b5 01            	mov	edx, dword ptr [0x1b564e4]
 118ed3e: 8d 78 06                     	lea	edi, [eax + 0x6]
 118ed41: 8b 02                        	mov	eax, dword ptr [edx]
 118ed43: 6a 65                        	push	0x65
 118ed45: 68 10 d3 84 01               	push	0x184d310
 118ed4a: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
 118ed4d: e8 9e 11 01 00               	call	0x119fef0 <.text+0x112a0>
 118ed52: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 118ed55: 8b 0d e4 64 b5 01            	mov	ecx, dword ptr [0x1b564e4]
 118ed5b: 83 c4 04                     	add	esp, 0x4
 118ed5e: 50                           	push	eax
 118ed5f: 8b                           	<unknown>
