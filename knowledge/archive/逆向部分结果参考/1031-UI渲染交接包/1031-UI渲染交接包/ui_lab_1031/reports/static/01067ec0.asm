
<stdin>:	file format elf32-i386

Disassembly of section .text:

01067ec0 <.text>:
 1067ec0: 55                           	push	ebp
 1067ec1: 8b ec                        	mov	ebp, esp
 1067ec3: 53                           	push	ebx
 1067ec4: 56                           	push	esi
 1067ec5: 57                           	push	edi
 1067ec6: 8b f9                        	mov	edi, ecx
 1067ec8: 83 7f 24 00                  	cmp	dword ptr [edi + 0x24], 0x0
 1067ecc: 0f 84 8d 00 00 00            	je	0x1067f5f <.text+0x9f>
 1067ed2: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 1067ed5: 8b c6                        	mov	eax, esi
 1067ed7: 8d 50 02                     	lea	edx, [eax + 0x2]
 1067eda: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
 1067ee0: 66 8b 08                     	mov	cx, word ptr [eax]
 1067ee3: 83 c0 02                     	add	eax, 0x2
 1067ee6: 66 85 c9                     	test	cx, cx
 1067ee9: 75 f5                        	jne	0x1067ee0 <.text+0x20>
 1067eeb: 2b c2                        	sub	eax, edx
 1067eed: d1 f8                        	sar	eax
 1067eef: 74 6e                        	je	0x1067f5f <.text+0x9f>
 1067ef1: 56                           	push	esi
 1067ef2: 68 78 21 56 01               	push	0x1562178
 1067ef7: e8 f4 7f 13 00               	call	0x119fef0 <.text+0x138030>
 1067efc: 83 c4 04                     	add	esp, 0x4
 1067eff: 50                           	push	eax
 1067f00: e8 1b b7 1b 00               	call	0x1223620 <.text+0x1bb760>
 1067f05: 83 c4 08                     	add	esp, 0x8
 1067f08: 84 c0                        	test	al, al
 1067f0a: 74 53                        	je	0x1067f5f <.text+0x9f>
 1067f0c: 83 7f 18 00                  	cmp	dword ptr [edi + 0x18], 0x0
 1067f10: 75 1e                        	jne	0x1067f30 <.text+0x70>
 1067f12: 8b c6                        	mov	eax, esi
 1067f14: 8d 50 02                     	lea	edx, [eax + 0x2]
 1067f17: 66 8b 08                     	mov	cx, word ptr [eax]
 1067f1a: 83 c0 02                     	add	eax, 0x2
 1067f1d: 66 85 c9                     	test	cx, cx
 1067f20: 75 f5                        	jne	0x1067f17 <.text+0x57>
 1067f22: 2b c2                        	sub	eax, edx
 1067f24: d1 f8                        	sar	eax
 1067f26: 50                           	push	eax
 1067f27: 56                           	push	esi
 1067f28: 8d 4f 04                     	lea	ecx, [edi + 0x4]
 1067f2b: e8 00 81 3a ff               	call	0x410030
 1067f30: 8b 5d 0c                     	mov	ebx, dword ptr [ebp + 0xc]
 1067f33: 84 db                        	test	bl, bl
 1067f35: 75 07                        	jne	0x1067f3e <.text+0x7e>
 1067f37: 8b cf                        	mov	ecx, edi
 1067f39: e8 32 ca ff ff               	call	0x1064970
 1067f3e: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 1067f41: 50                           	push	eax
 1067f42: 53                           	push	ebx
 1067f43: 83 ec 20                     	sub	esp, 0x20
 1067f46: 8b cc                        	mov	ecx, esp
 1067f48: 89 65 08                     	mov	dword ptr [ebp + 0x8], esp
 1067f4b: 56                           	push	esi
 1067f4c: e8 cf 9f 3a ff               	call	0x411f20
 1067f51: 8b cf                        	mov	ecx, edi
 1067f53: e8 c8 cd ff ff               	call	0x1064d20
 1067f58: 5f                           	pop	edi
 1067f59: 5e                           	pop	esi
 1067f5a: 5b                           	pop	ebx
 1067f5b: 5d                           	pop	ebp
 1067f5c: c2 0c 00                     	ret	0xc
 1067f5f: 5f                           	pop	edi
 1067f60: 5e                           	pop	esi
 1067f61: 32 c0                        	xor	al, al
 1067f63: 5b                           	pop	ebx
 1067f64: 5d                           	pop	ebp
 1067f65: c2 0c 00                     	ret	0xc
 1067f68: cc                           	int3
 1067f69: cc                           	int3
 1067f6a: cc                           	int3
 1067f6b: cc                           	int3
 1067f6c: cc                           	int3
 1067f6d: cc                           	int3
 1067f6e: cc                           	int3
 1067f6f: cc                           	int3
