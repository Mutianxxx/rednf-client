
<stdin>:	file format elf32-i386

Disassembly of section .text:

011bead0 <.text>:
 11bead0: 55                           	push	ebp
 11bead1: 8b ec                        	mov	ebp, esp
 11bead3: 83 ec 0c                     	sub	esp, 0xc
 11bead6: 80 7d 10 00                  	cmp	byte ptr [ebp + 0x10], 0x0
 11beada: 56                           	push	esi
 11beadb: 75 15                        	jne	0x11beaf2 <.text+0x22>
 11beadd: 8b 71 5c                     	mov	esi, dword ptr [ecx + 0x5c]
 11beae0: 85 f6                        	test	esi, esi
 11beae2: 74 0e                        	je	0x11beaf2 <.text+0x22>
 11beae4: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11beae7: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11beaea: 03 56 14                     	add	edx, dword ptr [esi + 0x14]
 11beaed: 03 46 18                     	add	eax, dword ptr [esi + 0x18]
 11beaf0: eb 06                        	jmp	0x11beaf8 <.text+0x28>
 11beaf2: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11beaf5: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11beaf8: 83 79 1c 00                  	cmp	dword ptr [ecx + 0x1c], 0x0
 11beafc: 75 0c                        	jne	0x11beb0a <.text+0x3a>
 11beafe: 83 79 20 00                  	cmp	dword ptr [ecx + 0x20], 0x0
 11beb02: 75 06                        	jne	0x11beb0a <.text+0x3a>
 11beb04: 89 51 78                     	mov	dword ptr [ecx + 0x78], edx
 11beb07: 89 41 7c                     	mov	dword ptr [ecx + 0x7c], eax
 11beb0a: 83 79 6c 00                  	cmp	dword ptr [ecx + 0x6c], 0x0
 11beb0e: 8b 71 14                     	mov	esi, dword ptr [ecx + 0x14]
 11beb11: 89 71 1c                     	mov	dword ptr [ecx + 0x1c], esi
 11beb14: 8b 71 18                     	mov	esi, dword ptr [ecx + 0x18]
 11beb17: 89 71 20                     	mov	dword ptr [ecx + 0x20], esi
 11beb1a: 89 51 14                     	mov	dword ptr [ecx + 0x14], edx
 11beb1d: 89 41 18                     	mov	dword ptr [ecx + 0x18], eax
 11beb20: 0f 84 88 00 00 00            	je	0x11bebae <.text+0xde>
 11beb26: 2b 51 1c                     	sub	edx, dword ptr [ecx + 0x1c]
 11beb29: 53                           	push	ebx
 11beb2a: 2b c6                        	sub	eax, esi
 11beb2c: 89 45 10                     	mov	dword ptr [ebp + 0x10], eax
 11beb2f: 57                           	push	edi
 11beb30: 8d 59 64                     	lea	ebx, [ecx + 0x64]
 11beb33: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11beb36: 50                           	push	eax
 11beb37: 8b cb                        	mov	ecx, ebx
 11beb39: 89 55 0c                     	mov	dword ptr [ebp + 0xc], edx
 11beb3c: e8 cf eb 15 00               	call	0x131d710 <.text+0x15ec40>
 11beb41: 8b 75 f4                     	mov	esi, dword ptr [ebp - 0xc]
 11beb44: 8b 7d fc                     	mov	edi, dword ptr [ebp - 0x4]
 11beb47: 8d 4d f4                     	lea	ecx, [ebp - 0xc]
 11beb4a: 51                           	push	ecx
 11beb4b: 8b cb                        	mov	ecx, ebx
 11beb4d: e8 1e 76 fb ff               	call	0x1176170
 11beb52: 85 f6                        	test	esi, esi
 11beb54: 74 51                        	je	0x11beba7 <.text+0xd7>
 11beb56: 8b 16                        	mov	edx, dword ptr [esi]
 11beb58: 85 d2                        	test	edx, edx
 11beb5a: 74 4b                        	je	0x11beba7 <.text+0xd7>
 11beb5c: 8b 08                        	mov	ecx, dword ptr [eax]
 11beb5e: 85 c9                        	test	ecx, ecx
 11beb60: 74 02                        	je	0x11beb64 <.text+0x94>
 11beb62: 8b 09                        	mov	ecx, dword ptr [ecx]
 11beb64: 3b d1                        	cmp	edx, ecx
 11beb66: 75 3f                        	jne	0x11beba7 <.text+0xd7>
 11beb68: 3b 78 08                     	cmp	edi, dword ptr [eax + 0x8]
 11beb6b: 74 3f                        	je	0x11bebac <.text+0xdc>
 11beb6d: 8b c2                        	mov	eax, edx
 11beb6f: 85 c0                        	test	eax, eax
 11beb71: 74 34                        	je	0x11beba7 <.text+0xd7>
 11beb73: 85 ff                        	test	edi, edi
 11beb75: 74 30                        	je	0x11beba7 <.text+0xd7>
 11beb77: 3b 78 04                     	cmp	edi, dword ptr [eax + 0x4]
 11beb7a: 74 2b                        	je	0x11beba7 <.text+0xd7>
 11beb7c: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
 11beb7f: 85 c9                        	test	ecx, ecx
 11beb81: 74 15                        	je	0x11beb98 <.text+0xc8>
 11beb83: 8b 51 18                     	mov	edx, dword ptr [ecx + 0x18]
 11beb86: 03 55 10                     	add	edx, dword ptr [ebp + 0x10]
 11beb89: 8b 41 14                     	mov	eax, dword ptr [ecx + 0x14]
 11beb8c: 03 45 0c                     	add	eax, dword ptr [ebp + 0xc]
 11beb8f: 6a 01                        	push	0x1
 11beb91: 52                           	push	edx
 11beb92: 50                           	push	eax
 11beb93: e8 38 ff ff ff               	call	0x11bead0 <.text>
 11beb98: 8b 06                        	mov	eax, dword ptr [esi]
 11beb9a: 85 c0                        	test	eax, eax
 11beb9c: 74 09                        	je	0x11beba7 <.text+0xd7>
 11beb9e: 3b 78 04                     	cmp	edi, dword ptr [eax + 0x4]
 11beba1: 74 04                        	je	0x11beba7 <.text+0xd7>
 11beba3: 8b 3f                        	mov	edi, dword ptr [edi]
 11beba5: eb a0                        	jmp	0x11beb47 <.text+0x77>
 11beba7: e8 fb 81 21 00               	call	0x13d6da7 <.text+0x2182d7>
 11bebac: 5f                           	pop	edi
 11bebad: 5b                           	pop	ebx
 11bebae: 5e                           	pop	esi
 11bebaf: 8b e5                        	mov	esp, ebp
 11bebb1: 5d                           	pop	ebp
 11bebb2: c2 0c 00                     	ret	0xc
