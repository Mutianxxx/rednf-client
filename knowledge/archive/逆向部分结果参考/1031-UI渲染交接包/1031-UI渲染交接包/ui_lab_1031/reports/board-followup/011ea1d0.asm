
<stdin>:	file format elf32-i386

Disassembly of section .text:

011ea1d0 <.text>:
 11ea1d0: 55                           	push	ebp
 11ea1d1: 8b ec                        	mov	ebp, esp
 11ea1d3: 51                           	push	ecx
 11ea1d4: 53                           	push	ebx
 11ea1d5: 56                           	push	esi
 11ea1d6: 57                           	push	edi
 11ea1d7: 8b f1                        	mov	esi, ecx
 11ea1d9: e8 22 36 24 ff               	call	0x42d800
 11ea1de: 8b ce                        	mov	ecx, esi
 11ea1e0: 8b f8                        	mov	edi, eax
 11ea1e2: e8 69 5d 03 00               	call	0x121ff50 <.text+0x35d80>
 11ea1e7: 8b ce                        	mov	ecx, esi
 11ea1e9: 8b d8                        	mov	ebx, eax
 11ea1eb: e8 10 41 fd ff               	call	0x11be300
 11ea1f0: 8b ce                        	mov	ecx, esi
 11ea1f2: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 11ea1f5: e8 66 5d 24 ff               	call	0x42ff60
 11ea1fa: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11ea200: 8b 51 24                     	mov	edx, dword ptr [ecx + 0x24]
 11ea203: 83 ea 00                     	sub	edx, 0x0
 11ea206: 74 16                        	je	0x11ea21e <.text+0x4e>
 11ea208: 4a                           	dec	edx
 11ea209: 75 1f                        	jne	0x11ea22a <.text+0x5a>
 11ea20b: 8b 55 fc                     	mov	edx, dword ptr [ebp - 0x4]
 11ea20e: 57                           	push	edi
 11ea20f: 53                           	push	ebx
 11ea210: 52                           	push	edx
 11ea211: 50                           	push	eax
 11ea212: e8 19 fa ff ff               	call	0x11e9c30
 11ea217: 5f                           	pop	edi
 11ea218: 5e                           	pop	esi
 11ea219: 5b                           	pop	ebx
 11ea21a: 8b e5                        	mov	esp, ebp
 11ea21c: 5d                           	pop	ebp
 11ea21d: c3                           	ret
 11ea21e: 8b 55 fc                     	mov	edx, dword ptr [ebp - 0x4]
 11ea221: 57                           	push	edi
 11ea222: 53                           	push	ebx
 11ea223: 52                           	push	edx
 11ea224: 50                           	push	eax
 11ea225: e8 f6 fb ff ff               	call	0x11e9e20
 11ea22a: 5f                           	pop	edi
 11ea22b: 5e                           	pop	esi
 11ea22c: 5b                           	pop	ebx
 11ea22d: 8b e5                        	mov	esp, ebp
 11ea22f: 5d                           	pop	ebp
 11ea230: c3                           	ret
