
<stdin>:	file format elf32-i386

Disassembly of section .text:

011e99a0 <.text>:
 11e99a0: 55                           	push	ebp
 11e99a1: 8b ec                        	mov	ebp, esp
 11e99a3: 56                           	push	esi
 11e99a4: 8b f1                        	mov	esi, ecx
 11e99a6: 8b 86 b8 02 00 00            	mov	eax, dword ptr [esi + 0x2b8]
 11e99ac: 83 38 00                     	cmp	dword ptr [eax], 0x0
 11e99af: 0f 84 d6 00 00 00            	je	0x11e9a8b <.text+0xeb>
 11e99b5: 83 78 04 00                  	cmp	dword ptr [eax + 0x4], 0x0
 11e99b9: 0f 84 cc 00 00 00            	je	0x11e9a8b <.text+0xeb>
 11e99bf: 83 78 08 00                  	cmp	dword ptr [eax + 0x8], 0x0
 11e99c3: 0f 84 c2 00 00 00            	je	0x11e9a8b <.text+0xeb>
 11e99c9: 83 78 0c 00                  	cmp	dword ptr [eax + 0xc], 0x0
 11e99cd: 0f 84 b8 00 00 00            	je	0x11e9a8b <.text+0xeb>
 11e99d3: 83 78 10 00                  	cmp	dword ptr [eax + 0x10], 0x0
 11e99d7: 0f 84 ae 00 00 00            	je	0x11e9a8b <.text+0xeb>
 11e99dd: 83 78 14 00                  	cmp	dword ptr [eax + 0x14], 0x0
 11e99e1: 0f 84 a4 00 00 00            	je	0x11e9a8b <.text+0xeb>
 11e99e7: 83 78 18 00                  	cmp	dword ptr [eax + 0x18], 0x0
 11e99eb: 0f 84 9a 00 00 00            	je	0x11e9a8b <.text+0xeb>
 11e99f1: 83 78 1c 00                  	cmp	dword ptr [eax + 0x1c], 0x0
 11e99f5: 0f 84 90 00 00 00            	je	0x11e9a8b <.text+0xeb>
 11e99fb: 83 78 20 00                  	cmp	dword ptr [eax + 0x20], 0x0
 11e99ff: 0f 84 86 00 00 00            	je	0x11e9a8b <.text+0xeb>
 11e9a05: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11e9a08: 53                           	push	ebx
 11e9a09: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 11e9a0c: 89 58 28                     	mov	dword ptr [eax + 0x28], ebx
 11e9a0f: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11e9a15: 89 51 2c                     	mov	dword ptr [ecx + 0x2c], edx
 11e9a18: 8b 86 b8 02 00 00            	mov	eax, dword ptr [esi + 0x2b8]
 11e9a1e: 8b 48 10                     	mov	ecx, dword ptr [eax + 0x10]
 11e9a21: 57                           	push	edi
 11e9a22: e8 59 a3 fc ff               	call	0x11b3d80
 11e9a27: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11e9a2d: 8b 49 14                     	mov	ecx, dword ptr [ecx + 0x14]
 11e9a30: 8b f8                        	mov	edi, eax
 11e9a32: 0f af fb                     	imul	edi, ebx
 11e9a35: e8 46 a3 fc ff               	call	0x11b3d80
 11e9a3a: 8b 96 b8 02 00 00            	mov	edx, dword ptr [esi + 0x2b8]
 11e9a40: 8b 4a 0c                     	mov	ecx, dword ptr [edx + 0xc]
 11e9a43: 03 f8                        	add	edi, eax
 11e9a45: e8 36 a3 fc ff               	call	0x11b3d80
 11e9a4a: 03 f8                        	add	edi, eax
 11e9a4c: 8b 86 b8 02 00 00            	mov	eax, dword ptr [esi + 0x2b8]
 11e9a52: 8b 48 10                     	mov	ecx, dword ptr [eax + 0x10]
 11e9a55: e8 36 a3 fc ff               	call	0x11b3d90
 11e9a5a: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11e9a60: 8b 49 1c                     	mov	ecx, dword ptr [ecx + 0x1c]
 11e9a63: 8b d8                        	mov	ebx, eax
 11e9a65: 0f af 5d 0c                  	imul	ebx, dword ptr [ebp + 0xc]
 11e9a69: e8 22 a3 fc ff               	call	0x11b3d90
 11e9a6e: 8b 96 b8 02 00 00            	mov	edx, dword ptr [esi + 0x2b8]
 11e9a74: 8b 4a 04                     	mov	ecx, dword ptr [edx + 0x4]
 11e9a77: 03 d8                        	add	ebx, eax
 11e9a79: e8 12 a3 fc ff               	call	0x11b3d90
 11e9a7e: 03 c3                        	add	eax, ebx
 11e9a80: 50                           	push	eax
 11e9a81: 57                           	push	edi
 11e9a82: 8b ce                        	mov	ecx, esi
 11e9a84: e8 e7 48 fd ff               	call	0x11be370
 11e9a89: 5f                           	pop	edi
 11e9a8a: 5b                           	pop	ebx
 11e9a8b: 5e                           	pop	esi
 11e9a8c: 5d                           	pop	ebp
 11e9a8d: c2 08 00                     	ret	0x8
