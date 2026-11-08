
<stdin>:	file format elf32-i386

Disassembly of section .text:

01144e20 <.text>:
 1144e20: 52                           	push	edx
 1144e21: 57                           	push	edi
 1144e22: 50                           	push	eax
 1144e23: 56                           	push	esi
 1144e24: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 1144e2b: e8 60 15 19 00               	call	0x12d6390 <.text+0x191570>
 1144e30: 83 c4 14                     	add	esp, 0x14
 1144e33: c7 83 5c 02 00 00 ff ff ff ff	mov	dword ptr [ebx + 0x25c], 0xffffffff
 1144e3d: 84 c0                        	test	al, al
 1144e3f: 0f 85 f5 f2 ff ff            	jne	0x114413a
 1144e45: 85 f6                        	test	esi, esi
 1144e47: 74 5e                        	je	0x1144ea7 <.text+0x87>
 1144e49: 8b ce                        	mov	ecx, esi
 1144e4b: e8 90 00 7d ff               	call	0x914ee0
 1144e50: eb 4c                        	jmp	0x1144e9e <.text+0x7e>
 1144e52: 6a 60                        	push	0x60
 1144e54: e8 c1 1c 29 00               	call	0x13d6b1a <.text+0x291cfa>
 1144e59: 83 c4 04                     	add	esp, 0x4
 1144e5c: 89 85 b8 fa ff ff            	mov	dword ptr [ebp - 0x548], eax
 1144e62: c7 45 fc 1d 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1d
 1144e69: 85 c0                        	test	eax, eax
 1144e6b: 74 0b                        	je	0x1144e78 <.text+0x58>
 1144e6d: 8b c8                        	mov	ecx, eax
 1144e6f: e8 9c e0 ff ff               	call	0x1142f10
 1144e74: 8b f0                        	mov	esi, eax
 1144e76: eb 02                        	jmp	0x1144e7a <.text+0x5a>
 1144e78: 33 f6                        	xor	esi, esi
 1144e7a: 57                           	push	edi
 1144e7b: 56                           	push	esi
 1144e7c: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 1144e83: e8 78 f9 1c 00               	call	0x1314800 <.text+0x1cf9e0>
 1144e88: 83 c4 08                     	add	esp, 0x8
 1144e8b: 84 c0                        	test	al, al
 1144e8d: 0f 85 a7 f2 ff ff            	jne	0x114413a
 1144e93: 85 f6                        	test	esi, esi
 1144e95: 74 10                        	je	0x1144ea7 <.text+0x87>
 1144e97: 8b ce                        	mov	ecx, esi
 1144e99: e8 d2 e1 ff ff               	call	0x1143070
 1144e9e: 56                           	push	esi
 1144e9f: e8 83 0c 29 00               	call	0x13d5b27 <.text+0x290d07>
 1144ea4: 83 c4 04                     	add	esp, 0x4
 1144ea7: 33 c0                        	xor	eax, eax
 1144ea9: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 1144eac: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 1144eb3: 59                           	pop	ecx
 1144eb4: 5f                           	pop	edi
 1144eb5: 5e                           	pop	esi
 1144eb6: 5b                           	pop	ebx
 1144eb7: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 1144eba: 33 cd                        	xor	ecx, ebp
 1144ebc: e8 17 23 29 00               	call	0x13d71d8 <.text+0x2923b8>
 1144ec1: 8b e5                        	mov	esp, ebp
 1144ec3: 5d                           	pop	ebp
 1144ec4: c2 08 00                     	ret	0x8
 1144ec7: 90                           	nop
 1144ec8: 16                           	push	ss
 1144ec9: 35 14 01 7a 39               	xor	eax, 0x397a0114
 1144ece: 14 01                        	adc	al, 0x1
 1144ed0: 74 3d                        	je	0x1144f0f <.text+0xef>
 1144ed2: 14 01                        	adc	al, 0x1
 1144ed4: ce                           	into
 1144ed5: 3d 14 01 26 3e               	cmp	eax, 0x3e260114
 1144eda: 14 01                        	adc	al, 0x1
 1144edc: 55                           	push	ebp
 1144edd: 41                           	inc	ecx
 1144ede: 14 01                        	adc	al, 0x1
 1144ee0: b2 41                        	mov	dl, 0x41
 1144ee2: 14 01                        	adc	al, 0x1
 1144ee4: 07                           	pop	es
 1144ee5: 42                           	inc	edx
 1144ee6: 14 01                        	adc	al, 0x1
 1144ee8: 0e                           	push	cs
 1144ee9: 44                           	inc	esp
 1144eea: 14 01                        	adc	al, 0x1
 1144eec: 83 44 14 01 db               	add	dword ptr [esp + edx + 0x1], -0x25
 1144ef1: 44                           	inc	esp
 1144ef2: 14 01                        	adc	al, 0x1
 1144ef4: 33 45 14                     	xor	eax, dword ptr [ebp + 0x14]
 1144ef7: 01 8b 45 14 01 e3            	add	dword ptr [ebx - 0x1cfeebbb], ecx
 1144efd: 45                           	inc	ebp
 1144efe: 14 01                        	adc	al, 0x1
 1144f00: 3b 46 14                     	cmp	eax, dword ptr [esi + 0x14]
 1144f03: 01 9f 4a 14 01 1e            	add	dword ptr [edi + 0x1e01144a], ebx
 1144f09: 4b                           	dec	ebx
 1144f0a: 14 01                        	adc	al, 0x1
 1144f0c: 7b 4b                        	jnp	0x1144f59 <.text+0x139>
 1144f0e: 14 01                        	adc	al, 0x1
 1144f10: d2 4b 14                     	ror	byte ptr [ebx + 0x14], cl
 1144f13: 01 2a                        	add	dword ptr [edx], ebp
 1144f15: 4c                           	dec	esp
 1144f16: 14 01                        	adc	al, 0x1
 1144f18: 82 4c 14 01 da               	or	byte ptr [esp + edx + 0x1], -0x26
 1144f1d: 4c                           	dec	esp
 1144f1e: 14 01                        	adc	al, 0x1
 1144f20: df 4d 14                     	fisttp	word ptr [ebp + 0x14]
 1144f23: 01 32                        	add	dword ptr [edx], esi
 1144f25: 4d                           	dec	ebp
 1144f26: 14 01                        	adc	al, 0x1
 1144f28: 8a 4d 14                     	mov	cl, byte ptr [ebp + 0x14]
 1144f2b: 01 52 4e                     	add	dword ptr [edx + 0x4e], edx
 1144f2e: 14 01                        	adc	al, 0x1
 1144f30: a7                           	cmpsd	dword ptr [esi], dword ptr es:[edi]
 1144f31: 4e                           	dec	esi
 1144f32: 14 01                        	adc	al, 0x1
 1144f34: 00 01                        	add	byte ptr [ecx], al
 1144f36: 02 03                        	add	al, byte ptr [ebx]
 1144f38: 04 05                        	add	al, 0x5
 1144f3a: 06                           	push	es
 1144f3b: 07                           	pop	es
 1144f3c: 08 09                        	or	byte ptr [ecx], cl
 1144f3e: 0a 0b                        	or	cl, byte ptr [ebx]
