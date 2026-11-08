
<stdin>:	file format elf32-i386

Disassembly of section .text:

0106ae80 <.text>:
 106ae80: 55                           	push	ebp
 106ae81: 8b ec                        	mov	ebp, esp
 106ae83: 6a ff                        	push	-0x1
 106ae85: 68 0b a3 46 01               	push	0x146a30b
 106ae8a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 106ae90: 50                           	push	eax
 106ae91: 51                           	push	ecx
 106ae92: 53                           	push	ebx
 106ae93: 56                           	push	esi
 106ae94: 57                           	push	edi
 106ae95: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 106ae9a: 33 c5                        	xor	eax, ebp
 106ae9c: 50                           	push	eax
 106ae9d: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 106aea0: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 106aea6: 8b f1                        	mov	esi, ecx
 106aea8: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 106aeab: 8b 46 6c                     	mov	eax, dword ptr [esi + 0x6c]
 106aeae: 2b c1                        	sub	eax, ecx
 106aeb0: c1 f8 02                     	sar	eax, 0x2
 106aeb3: 83 f8 04                     	cmp	eax, 0x4
 106aeb6: 73 16                        	jae	0x106aece <.text+0x4e>
 106aeb8: 33 c0                        	xor	eax, eax
 106aeba: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 106aebd: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 106aec4: 59                           	pop	ecx
 106aec5: 5f                           	pop	edi
 106aec6: 5e                           	pop	esi
 106aec7: 5b                           	pop	ebx
 106aec8: 8b e5                        	mov	esp, ebp
 106aeca: 5d                           	pop	ebp
 106aecb: c2 04 00                     	ret	0x4
 106aece: 33 ff                        	xor	edi, edi
 106aed0: 3b c7                        	cmp	eax, edi
 106aed2: 77 05                        	ja	0x106aed9 <.text+0x59>
 106aed4: e8 ce be 36 00               	call	0x13d6da7 <.text+0x36bf27>
 106aed9: 83 39 02                     	cmp	dword ptr [ecx], 0x2
 106aedc: 7d da                        	jge	0x106aeb8 <.text+0x38>
 106aede: 68 bc 02 00 00               	push	0x2bc
 106aee3: e8 98 54 14 00               	call	0x11b0380 <.text+0x145500>
 106aee8: 83 c4 04                     	add	esp, 0x4
 106aeeb: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 106aeee: 89 7d fc                     	mov	dword ptr [ebp - 0x4], edi
 106aef1: 3b c7                        	cmp	eax, edi
 106aef3: 74 23                        	je	0x106af18 <.text+0x98>
 106aef5: 8b 56 68                     	mov	edx, dword ptr [esi + 0x68]
 106aef8: 8b 4e 6c                     	mov	ecx, dword ptr [esi + 0x6c]
 106aefb: 2b ca                        	sub	ecx, edx
 106aefd: c1 f9 02                     	sar	ecx, 0x2
 106af00: 85 c9                        	test	ecx, ecx
 106af02: 75 05                        	jne	0x106af09 <.text+0x89>
 106af04: e8 9e be 36 00               	call	0x13d6da7 <.text+0x36bf27>
 106af09: 8b 12                        	mov	edx, dword ptr [edx]
 106af0b: 52                           	push	edx
 106af0c: 8b c8                        	mov	ecx, eax
 106af0e: e8 7d 2f 19 00               	call	0x11fde90 <.text+0x193010>
 106af13: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 106af16: eb 03                        	jmp	0x106af1b <.text+0x9b>
 106af18: 89 7d f0                     	mov	dword ptr [ebp - 0x10], edi
 106af1b: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 106af1e: 8b 46 6c                     	mov	eax, dword ptr [esi + 0x6c]
 106af21: 2b c1                        	sub	eax, ecx
 106af23: c1 f8 02                     	sar	eax, 0x2
 106af26: 33 db                        	xor	ebx, ebx
 106af28: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 106af2f: 3b c7                        	cmp	eax, edi
 106af31: 77 05                        	ja	0x106af38 <.text+0xb8>
 106af33: e8 6f be 36 00               	call	0x13d6da7 <.text+0x36bf27>
 106af38: 8b 11                        	mov	edx, dword ptr [ecx]
 106af3a: 2b d3                        	sub	edx, ebx
 106af3c: 74 56                        	je	0x106af94 <.text+0x114>
 106af3e: 4a                           	dec	edx
 106af3f: 0f 85 92 00 00 00            	jne	0x106afd7 <.text+0x157>
 106af45: a1 e4 64 b5 01               	mov	eax, dword ptr [0x1b564e4]
 106af4a: 8b 38                        	mov	edi, dword ptr [eax]
 106af4c: 68 e5 00 00 00               	push	0xe5
 106af51: 68 d8 50 56 01               	push	0x15650d8
 106af56: e8 95 4f 13 00               	call	0x119fef0 <.text+0x135070>
 106af5b: 8b 0d e4 64 b5 01            	mov	ecx, dword ptr [0x1b564e4]
 106af61: 8b 57 10                     	mov	edx, dword ptr [edi + 0x10]
 106af64: 83 c4 04                     	add	esp, 0x4
 106af67: 50                           	push	eax
 106af68: ff d2                        	call	edx
 106af6a: 8b c8                        	mov	ecx, eax
 106af6c: e8 5f 9c 14 00               	call	0x11b4bd0 <.text+0x149d50>
 106af71: 8b c8                        	mov	ecx, eax
 106af73: e8 08 8e 14 00               	call	0x11b3d80 <.text+0x148f00>
 106af78: 8b 4e 6c                     	mov	ecx, dword ptr [esi + 0x6c]
 106af7b: 8b f8                        	mov	edi, eax
 106af7d: 8b 46 68                     	mov	eax, dword ptr [esi + 0x68]
 106af80: 2b c8                        	sub	ecx, eax
 106af82: c1 f9 02                     	sar	ecx, 0x2
 106af85: 83 f9 01                     	cmp	ecx, 0x1
 106af88: 77 05                        	ja	0x106af8f <.text+0x10f>
 106af8a: e8 18 be 36 00               	call	0x13d6da7 <.text+0x36bf27>
 106af8f: 8b 58 04                     	mov	ebx, dword ptr [eax + 0x4]
 106af92: eb 43                        	jmp	0x106afd7 <.text+0x157>
 106af94: 83 f8 01                     	cmp	eax, 0x1
 106af97: 77 05                        	ja	0x106af9e <.text+0x11e>
 106af99: e8 09 be 36 00               	call	0x13d6da7 <.text+0x36bf27>
 106af9e: 8b 15 e4 64 b5 01            	mov	edx, dword ptr [0x1b564e4]
 106afa4: 8b 79 04                     	mov	edi, dword ptr [ecx + 0x4]
 106afa7: 8b 1a                        	mov	ebx, dword ptr [edx]
 106afa9: 68 e5 00 00 00               	push	0xe5
 106afae: 68 d8 50 56 01               	push	0x15650d8
 106afb3: e8 38 4f 13 00               	call	0x119fef0 <.text+0x135070>
 106afb8: 8b 0d e4 64 b5 01            	mov	ecx, dword ptr [0x1b564e4]
 106afbe: 83 c4 04                     	add	esp, 0x4
 106afc1: 50                           	push	eax
 106afc2: 8b 43 10                     	mov	eax, dword ptr [ebx + 0x10]
 106afc5: ff d0                        	call	eax
 106afc7: 8b c8                        	mov	ecx, eax
 106afc9: e8 02 9c 14 00               	call	0x11b4bd0 <.text+0x149d50>
 106afce: 8b c8                        	mov	ecx, eax
 106afd0: e8 bb 8d 14 00               	call	0x11b3d90 <.text+0x148f10>
 106afd5: 8b d8                        	mov	ebx, eax
 106afd7: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 106afda: e8 21 33 15 00               	call	0x11be300 <.text+0x153480>
 106afdf: 03 46 4c                     	add	eax, dword ptr [esi + 0x4c]
 106afe2: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 106afe5: 50                           	push	eax
 106afe6: e8 75 4f 3c ff               	call	0x42ff60
 106afeb: 03 46 48                     	add	eax, dword ptr [esi + 0x48]
 106afee: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 106aff1: 50                           	push	eax
 106aff2: e8 a9 29 19 00               	call	0x11fd9a0 <.text+0x192b20>
 106aff7: 53                           	push	ebx
 106aff8: 57                           	push	edi
 106aff9: 8b 7d f0                     	mov	edi, dword ptr [ebp - 0x10]
 106affc: 8b cf                        	mov	ecx, edi
 106affe: e8 3d 2a 19 00               	call	0x11fda40 <.text+0x192bc0>
 106b003: 8b 46 68                     	mov	eax, dword ptr [esi + 0x68]
 106b006: 8b 4e 6c                     	mov	ecx, dword ptr [esi + 0x6c]
 106b009: 2b c8                        	sub	ecx, eax
 106b00b: c1 f9 02                     	sar	ecx, 0x2
 106b00e: 83 f9 02                     	cmp	ecx, 0x2
 106b011: 77 05                        	ja	0x106b018 <.text+0x198>
 106b013: e8 8f bd 36 00               	call	0x13d6da7 <.text+0x36bf27>
 106b018: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
 106b01b: 52                           	push	edx
 106b01c: 8b cf                        	mov	ecx, edi
 106b01e: e8 6d 2a 19 00               	call	0x11fda90 <.text+0x192c10>
 106b023: 8b 46 68                     	mov	eax, dword ptr [esi + 0x68]
 106b026: 8b 4e 6c                     	mov	ecx, dword ptr [esi + 0x6c]
 106b029: 2b c8                        	sub	ecx, eax
 106b02b: c1 f9 02                     	sar	ecx, 0x2
 106b02e: 83 f9 03                     	cmp	ecx, 0x3
 106b031: 77 05                        	ja	0x106b038 <.text+0x1b8>
 106b033: e8 6f bd 36 00               	call	0x13d6da7 <.text+0x36bf27>
 106b038: 8b 50 0c                     	mov	edx, dword ptr [eax + 0xc]
 106b03b: 52                           	push	edx
 106b03c: 8b cf                        	mov	ecx, edi
 106b03e: e8 dd 2e 19 00               	call	0x11fdf20 <.text+0x1930a0>
 106b043: 8b c7                        	mov	eax, edi
 106b045: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 106b048: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 106b04f: 59                           	pop	ecx
 106b050: 5f                           	pop	edi
 106b051: 5e                           	pop	esi
 106b052: 5b                           	pop	ebx
 106b053: 8b e5                        	mov	esp, ebp
 106b055: 5d                           	pop	ebp
 106b056: c2 04 00                     	ret	0x4
 106b059: cc                           	int3
 106b05a: cc                           	int3
 106b05b: cc                           	int3
 106b05c: cc                           	int3
 106b05d: cc                           	int3
 106b05e: cc                           	int3
 106b05f: cc                           	int3
 106b060: 55                           	push	ebp
 106b061: 8b ec                        	mov	ebp, esp
 106b063: 6a ff                        	push	-0x1
 106b065: 68 0b a3 46 01               	push	0x146a30b
 106b06a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 106b070: 50                           	push	eax
 106b071: 51                           	push	ecx
 106b072: 53                           	push	ebx
 106b073: 56                           	push	esi
 106b074: 57                           	push	edi
 106b075: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 106b07a: 33 c5                        	xor	eax, ebp
 106b07c: 50                           	push	eax
 106b07d: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 106b080: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 106b086: 8b f1                        	mov	esi, ecx
 106b088: 8b 46 58                     	mov	eax, dword ptr [esi + 0x58]
 106b08b: 2b 46 54                     	sub	eax, dword ptr [esi + 0x54]
 106b08e: c1 f8 05                     	sar	eax, 0x5
 106b091: 83 f8 01                     	cmp	eax, 0x1
 106b094: 73 16                        	jae	0x106b0ac <.text+0x22c>
 106b096: 33 c0                        	xor	eax, eax
 106b098: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 106b09b: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 106b0a2: 59                           	pop	ecx
 106b0a3: 5f                           	pop	edi
 106b0a4: 5e                           	pop	esi
 106b0a5: 5b                           	pop	ebx
 106b0a6: 8b e5                        	mov	esp, ebp
 106b0a8: 5d                           	pop	ebp
 106b0a9: c2 04 00                     	ret	0x4
 106b0ac: 8b 4e 6c                     	mov	ecx, dword ptr [esi + 0x6c]
 106b0af: 2b 4e 68                     	sub	ecx, dword ptr [esi + 0x68]
 106b0b2: c1 f9 02                     	sar	ecx, 0x2
 106b0b5: 83 f9 01                     	cmp	ecx, 0x1
 106b0b8: 72 dc                        	jb	0x106b096 <.text+0x216>
 106b0ba: 68 bc 02 00 00               	push	0x2bc
 106b0bf: e8 bc 52 14 00               	call	0x11b0380 <.text+0x145500>
 106b0c4: 83 c4 04                     	add	esp, 0x4
 106b0c7: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 106b0ca: 33 c9                        	xor	ecx, ecx
 106b0cc: 89 4d fc                     	mov	dword ptr [ebp - 0x4], ecx
 106b0cf: 3b c1                        	cmp	eax, ecx
 106b0d1: 74 0e                        	je	0x106b0e1 <.text+0x261>
 106b0d3: 8b c8                        	mov	ecx, eax
 106b0d5: e8 96 24 19 00               	call	0x11fd570 <.text+0x1926f0>
 106b0da: 8b d8                        	mov	ebx, eax
 106b0dc: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
 106b0df: eb 05                        	jmp	0x106b0e6 <.text+0x266>
 106b0e1: 89 4d f0                     	mov	dword ptr [ebp - 0x10], ecx
 106b0e4: 8b d9                        	mov	ebx, ecx
 106b0e6: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 106b0e9: 8b 3b                        	mov	edi, dword ptr [ebx]
 106b0eb: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 106b0f2: e8 09 32 15 00               	call	0x11be300 <.text+0x153480>
 106b0f7: 03 46 4c                     	add	eax, dword ptr [esi + 0x4c]
 106b0fa: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 106b0fd: 50                           	push	eax
 106b0fe: e8 5d 4e 3c ff               	call	0x42ff60
 106b103: 03 46 48                     	add	eax, dword ptr [esi + 0x48]
 106b106: 8b 97 9c 00 00 00            	mov	edx, dword ptr [edi + 0x9c]
 106b10c: 50                           	push	eax
 106b10d: 8b cb                        	mov	ecx, ebx
 106b10f: ff d2                        	call	edx
 106b111: 8b 46 68                     	mov	eax, dword ptr [esi + 0x68]
 106b114: 8b 4e 6c                     	mov	ecx, dword ptr [esi + 0x6c]
 106b117: 2b c8                        	sub	ecx, eax
 106b119: c1 f9 02                     	sar	ecx, 0x2
 106b11c: 85 c9                        	test	ecx, ecx
 106b11e: 75 05                        	jne	0x106b125 <.text+0x2a5>
 106b120: e8 82 bc 36 00               	call	0x13d6da7 <.text+0x36bf27>
 106b125: 8b 10                        	mov	edx, dword ptr [eax]
 106b127: 52                           	push	edx
 106b128: 8b cb                        	mov	ecx, ebx
 106b12a: e8 81 21 19 00               	call	0x11fd2b0 <.text+0x192430>
 106b12f: 8b 4e 54                     	mov	ecx, dword ptr [esi + 0x54]
 106b132: 8b 46 58                     	mov	eax, dword ptr [esi + 0x58]
 106b135: 2b c1                        	sub	eax, ecx
 106b137: c1 f8 05                     	sar	eax, 0x5
 106b13a: 33 ff                        	xor	edi, edi
 106b13c: 85 c0                        	test	eax, eax
 106b13e: 74 36                        	je	0x106b176 <.text+0x2f6>
 106b140: 33 db                        	xor	ebx, ebx
 106b142: 3b f8                        	cmp	edi, eax
 106b144: 73 da                        	jae	0x106b120 <.text+0x2a0>
 106b146: 83 7c 0b 18 08               	cmp	dword ptr [ebx + ecx + 0x18], 0x8
 106b14b: 72 06                        	jb	0x106b153 <.text+0x2d3>
 106b14d: 8b 4c 0b 04                  	mov	ecx, dword ptr [ebx + ecx + 0x4]
 106b151: eb 04                        	jmp	0x106b157 <.text+0x2d7>
 106b153: 8d 4c 0b 04                  	lea	ecx, [ebx + ecx + 0x4]
 106b157: 51                           	push	ecx
 106b158: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 106b15b: e8 b0 25 19 00               	call	0x11fd710 <.text+0x192890>
 106b160: 8b 4e 54                     	mov	ecx, dword ptr [esi + 0x54]
 106b163: 8b 46 58                     	mov	eax, dword ptr [esi + 0x58]
 106b166: 2b c1                        	sub	eax, ecx
 106b168: 47                           	inc	edi
 106b169: c1 f8 05                     	sar	eax, 0x5
 106b16c: 83 c3 20                     	add	ebx, 0x20
 106b16f: 3b f8                        	cmp	edi, eax
 106b171: 72 d3                        	jb	0x106b146 <.text+0x2c6>
 106b173: 8b 5d f0                     	mov	ebx, dword ptr [ebp - 0x10]
 106b176: 8b 46 68                     	mov	eax, dword ptr [esi + 0x68]
 106b179: 8b 76 6c                     	mov	esi, dword ptr [esi + 0x6c]
 106b17c: 2b f0                        	sub	esi, eax
 106b17e: c1 fe 02                     	sar	esi, 0x2
 106b181: 83 fe 01                     	cmp	esi, 0x1
 106b184: 76 0b                        	jbe	0x106b191 <.text+0x311>
 106b186: 8b 40 04                     	mov	eax, dword ptr [eax + 0x4]
 106b189: 50                           	push	eax
 106b18a: 8b cb                        	mov	ecx, ebx
 106b18c: e8 4f 21 19 00               	call	0x11fd2e0 <.text+0x192460>
 106b191: 8b c3                        	mov	eax, ebx
 106b193: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 106b196: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 106b19d: 59                           	pop	ecx
 106b19e: 5f                           	pop	edi
 106b19f: 5e                           	pop	esi
 106b1a0: 5b                           	pop	ebx
 106b1a1: 8b e5                        	mov	esp, ebp
 106b1a3: 5d                           	pop	ebp
 106b1a4: c2 04 00                     	ret	0x4
 106b1a7: cc                           	int3
 106b1a8: cc                           	int3
 106b1a9: cc                           	int3
 106b1aa: cc                           	int3
 106b1ab: cc                           	int3
 106b1ac: cc                           	int3
 106b1ad: cc                           	int3
 106b1ae: cc                           	int3
 106b1af: cc                           	int3
 106b1b0: 55                           	push	ebp
 106b1b1: 8b ec                        	mov	ebp, esp
 106b1b3: 6a ff                        	push	-0x1
 106b1b5: 68 0b a3 46 01               	push	0x146a30b
 106b1ba: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 106b1c0: 50                           	push	eax
 106b1c1: 51                           	push	ecx
 106b1c2: 53                           	push	ebx
 106b1c3: 56                           	push	esi
 106b1c4: 57                           	push	edi
 106b1c5: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 106b1ca: 33 c5                        	xor	eax, ebp
 106b1cc: 50                           	push	eax
 106b1cd: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 106b1d0: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 106b1d6: 8b f1                        	mov	esi, ecx
 106b1d8: 33 ff                        	xor	edi, edi
 106b1da: 39 7e 78                     	cmp	dword ptr [esi + 0x78], edi
 106b1dd: 75 16                        	jne	0x106b1f5 <.text+0x375>
 106b1df: 33 c0                        	xor	eax, eax
 106b1e1: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 106b1e4: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 106b1eb: 59                           	pop	ecx
 106b1ec: 5f                           	pop	edi
 106b1ed: 5e                           	pop	esi
 106b1ee: 5b                           	pop	ebx
 106b1ef: 8b e5                        	mov	esp, ebp
 106b1f1: 5d                           	pop	ebp
 106b1f2: c2 04 00                     	ret	0x4
 106b1f5: 8b 46 58                     	mov	eax, dword ptr [esi + 0x58]
 106b1f8: 2b 46 54                     	sub	eax, dword ptr [esi + 0x54]
 106b1fb: 83 e0 e0                     	and	eax, -0x20
 106b1fe: 83 f8 40                     	cmp	eax, 0x40
 106b201: 75 dc                        	jne	0x106b1df <.text+0x35f>
 106b203: 68 bc 02 00 00               	push	0x2bc
 106b208: e8 73 51 14 00               	call	0x11b0380 <.text+0x145500>
 106b20d: 83 c4 04                     	add	esp, 0x4
 106b210: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 106b213: 89 7d fc                     	mov	dword ptr [ebp - 0x4], edi
 106b216: 3b c7                        	cmp	eax, edi
 106b218: 74 09                        	je	0x106b223 <.text+0x3a3>
 106b21a: 8b c8                        	mov	ecx, eax
 106b21c: e8 df 68 16 00               	call	0x11d1b00 <.text+0x166c80>
 106b221: 8b f8                        	mov	edi, eax
 106b223: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 106b226: 6a 01                        	push	0x1
 106b228: 8b cb                        	mov	ecx, ebx
 106b22a: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 106b231: e8 ca 30 15 00               	call	0x11be300 <.text+0x153480>
 106b236: 03 46 4c                     	add	eax, dword ptr [esi + 0x4c]
 106b239: 8b cb                        	mov	ecx, ebx
 106b23b: 50                           	push	eax
 106b23c: e8 1f 4d 3c ff               	call	0x42ff60
 106b241: 03 46 48                     	add	eax, dword ptr [esi + 0x48]
 106b244: 8b cf                        	mov	ecx, edi
 106b246: 50                           	push	eax
 106b247: e8 84 38 15 00               	call	0x11bead0 <.text+0x153c50>
 106b24c: 8b 4e 4c                     	mov	ecx, dword ptr [esi + 0x4c]
 106b24f: 8b 56 48                     	mov	edx, dword ptr [esi + 0x48]
 106b252: 51                           	push	ecx
 106b253: 52                           	push	edx
 106b254: 8b cf                        	mov	ecx, edi
 106b256: e8 05 5b 16 00               	call	0x11d0d60 <.text+0x165ee0>
 106b25b: 8b 46 78                     	mov	eax, dword ptr [esi + 0x78]
 106b25e: 50                           	push	eax
 106b25f: 8b cf                        	mov	ecx, edi
 106b261: e8 da 5a 16 00               	call	0x11d0d40 <.text+0x165ec0>
 106b266: 8b 46 54                     	mov	eax, dword ptr [esi + 0x54]
 106b269: 8b 4e 58                     	mov	ecx, dword ptr [esi + 0x58]
 106b26c: 2b c8                        	sub	ecx, eax
 106b26e: c1 f9 05                     	sar	ecx, 0x5
 106b271: 83 f9 01                     	cmp	ecx, 0x1
 106b274: 77 05                        	ja	0x106b27b <.text+0x3fb>
 106b276: e8 2c bb 36 00               	call	0x13d6da7 <.text+0x36bf27>
 106b27b: 83 78 38 08                  	cmp	dword ptr [eax + 0x38], 0x8
 106b27f: 72 05                        	jb	0x106b286 <.text+0x406>
 106b281: 8b 40 24                     	mov	eax, dword ptr [eax + 0x24]
 106b284: eb 03                        	jmp	0x106b289 <.text+0x409>
 106b286: 83 c0 24                     	add	eax, 0x24
 106b289: 50                           	push	eax
 106b28a: 8b cf                        	mov	ecx, edi
 106b28c: e8 3f 5e 16 00               	call	0x11d10d0 <.text+0x166250>
 106b291: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 106b294: 8b 46 6c                     	mov	eax, dword ptr [esi + 0x6c]
 106b297: 2b c1                        	sub	eax, ecx
 106b299: c1 f8 02                     	sar	eax, 0x2
 106b29c: 85 c0                        	test	eax, eax
 106b29e: 74 0a                        	je	0x106b2aa <.text+0x42a>
