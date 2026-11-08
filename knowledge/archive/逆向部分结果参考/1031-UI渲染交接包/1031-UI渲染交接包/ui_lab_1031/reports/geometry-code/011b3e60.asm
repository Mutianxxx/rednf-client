
<stdin>:	file format elf32-i386

Disassembly of section .text:

011b3e60 <.text>:
 11b3e60: 55                           	push	ebp
 11b3e61: 8b ec                        	mov	ebp, esp
 11b3e63: 56                           	push	esi
 11b3e64: 8b f1                        	mov	esi, ecx
 11b3e66: 80 7e 04 00                  	cmp	byte ptr [esi + 0x4], 0x0
 11b3e6a: 74 0a                        	je	0x11b3e76 <.text+0x16>
 11b3e6c: b8 02 00 00 80               	mov	eax, 0x80000002
 11b3e71: 5e                           	pop	esi
 11b3e72: 5d                           	pop	ebp
 11b3e73: c2 0c 00                     	ret	0xc
 11b3e76: 0f bf 4e 22                  	movsx	ecx, word ptr [esi + 0x22]
 11b3e7a: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b3e7d: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11b3e80: 89 46 14                     	mov	dword ptr [esi + 0x14], eax
 11b3e83: 0f bf 46 20                  	movsx	eax, word ptr [esi + 0x20]
 11b3e87: 53                           	push	ebx
 11b3e88: 57                           	push	edi
 11b3e89: 8b 7d 10                     	mov	edi, dword ptr [ebp + 0x10]
 11b3e8c: 66 89 56 1c                  	mov	word ptr [esi + 0x1c], dx
 11b3e90: 66 89 7e 1e                  	mov	word ptr [esi + 0x1e], di
 11b3e94: 03 c2                        	add	eax, edx
 11b3e96: 03 cf                        	add	ecx, edi
 11b3e98: 33 db                        	xor	ebx, ebx
 11b3e9a: 66 89 46 2c                  	mov	word ptr [esi + 0x2c], ax
 11b3e9e: 66 89 4e 2e                  	mov	word ptr [esi + 0x2e], cx
 11b3ea2: 66 89 5e 28                  	mov	word ptr [esi + 0x28], bx
 11b3ea6: 66 89 5e 2a                  	mov	word ptr [esi + 0x2a], bx
 11b3eaa: 8b 16                        	mov	edx, dword ptr [esi]
 11b3eac: 8b 82 bc 00 00 00            	mov	eax, dword ptr [edx + 0xbc]
 11b3eb2: 8b ce                        	mov	ecx, esi
 11b3eb4: ff d0                        	call	eax
 11b3eb6: 5f                           	pop	edi
 11b3eb7: 5b                           	pop	ebx
 11b3eb8: 85 c0                        	test	eax, eax
 11b3eba: 78 11                        	js	0x11b3ecd <.text+0x6d>
 11b3ebc: ff 15 88 a5 55 01            	call	dword ptr [0x155a588]
 11b3ec2: 89 46 54                     	mov	dword ptr [esi + 0x54], eax
 11b3ec5: b8 01 00 00 00               	mov	eax, 0x1
 11b3eca: 88 46 04                     	mov	byte ptr [esi + 0x4], al
 11b3ecd: 5e                           	pop	esi
 11b3ece: 5d                           	pop	ebp
 11b3ecf: c2 0c 00                     	ret	0xc
 11b3ed2: cc                           	int3
 11b3ed3: cc                           	int3
 11b3ed4: cc                           	int3
 11b3ed5: cc                           	int3
 11b3ed6: cc                           	int3
 11b3ed7: cc                           	int3
 11b3ed8: cc                           	int3
 11b3ed9: cc                           	int3
 11b3eda: cc                           	int3
 11b3edb: cc                           	int3
 11b3edc: cc                           	int3
 11b3edd: cc                           	int3
 11b3ede: cc                           	int3
 11b3edf: cc                           	int3
