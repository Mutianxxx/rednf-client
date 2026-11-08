
<stdin>:	file format elf32-i386

Disassembly of section .text:

011bc290 <.text>:
 11bc290: 55                           	push	ebp
 11bc291: 8b ec                        	mov	ebp, esp
 11bc293: 6a ff                        	push	-0x1
 11bc295: 68 09 7b 4c 01               	push	0x14c7b09
 11bc29a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11bc2a0: 50                           	push	eax
 11bc2a1: 83 ec 34                     	sub	esp, 0x34
 11bc2a4: 53                           	push	ebx
 11bc2a5: 56                           	push	esi
 11bc2a6: 57                           	push	edi
 11bc2a7: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11bc2ac: 33 c5                        	xor	eax, ebp
 11bc2ae: 50                           	push	eax
 11bc2af: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11bc2b2: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11bc2b8: 8b f1                        	mov	esi, ecx
 11bc2ba: 89 75 e8                     	mov	dword ptr [ebp - 0x18], esi
 11bc2bd: e8 7e 01 01 00               	call	0x11cc440 <.text+0x101b0>
 11bc2c2: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11bc2c5: 33 db                        	xor	ebx, ebx
 11bc2c7: c7 06 44 a5 85 01            	mov	dword ptr [esi], 0x185a544
 11bc2cd: 89 46 08                     	mov	dword ptr [esi + 0x8], eax
 11bc2d0: 8d 7e 0c                     	lea	edi, [esi + 0xc]
 11bc2d3: 6a 08                        	push	0x8
 11bc2d5: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 11bc2d8: 89 1f                        	mov	dword ptr [edi], ebx
 11bc2da: e8 3b a8 21 00               	call	0x13d6b1a <.text+0x21a88a>
 11bc2df: 83 c4 04                     	add	esp, 0x4
 11bc2e2: 3b c3                        	cmp	eax, ebx
 11bc2e4: 0f 84 60 03 00 00            	je	0x11bc64a <.text+0x3ba>
 11bc2ea: 89 07                        	mov	dword ptr [edi], eax
 11bc2ec: 89 58 04                     	mov	dword ptr [eax + 0x4], ebx
 11bc2ef: 33 c9                        	xor	ecx, ecx
 11bc2f1: 89 08                        	mov	dword ptr [eax], ecx
 11bc2f3: 8b 0f                        	mov	ecx, dword ptr [edi]
 11bc2f5: 89 39                        	mov	dword ptr [ecx], edi
 11bc2f7: 89 5f 04                     	mov	dword ptr [edi + 0x4], ebx
 11bc2fa: 89 5f 08                     	mov	dword ptr [edi + 0x8], ebx
 11bc2fd: 89 5f 0c                     	mov	dword ptr [edi + 0xc], ebx
 11bc300: 8d 7e 20                     	lea	edi, [esi + 0x20]
 11bc303: 6a 08                        	push	0x8
 11bc305: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 11bc309: 89 1f                        	mov	dword ptr [edi], ebx
 11bc30b: e8 0a a8 21 00               	call	0x13d6b1a <.text+0x21a88a>
 11bc310: 83 c4 04                     	add	esp, 0x4
 11bc313: 3b c3                        	cmp	eax, ebx
 11bc315: 0f 84 0b 03 00 00            	je	0x11bc626 <.text+0x396>
 11bc31b: 89 07                        	mov	dword ptr [edi], eax
 11bc31d: 89 58 04                     	mov	dword ptr [eax + 0x4], ebx
 11bc320: 33 c9                        	xor	ecx, ecx
 11bc322: 89 08                        	mov	dword ptr [eax], ecx
 11bc324: 8b 17                        	mov	edx, dword ptr [edi]
 11bc326: 89 3a                        	mov	dword ptr [edx], edi
 11bc328: 89 5f 04                     	mov	dword ptr [edi + 0x4], ebx
 11bc32b: 89 5f 08                     	mov	dword ptr [edi + 0x8], ebx
 11bc32e: 89 5f 0c                     	mov	dword ptr [edi + 0xc], ebx
