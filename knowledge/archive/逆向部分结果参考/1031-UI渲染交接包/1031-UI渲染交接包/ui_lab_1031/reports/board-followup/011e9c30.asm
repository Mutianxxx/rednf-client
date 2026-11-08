
<stdin>:	file format elf32-i386

Disassembly of section .text:

011e9c30 <.text>:
 11e9c30: 55                           	push	ebp
 11e9c31: 8b ec                        	mov	ebp, esp
 11e9c33: 83 ec 14                     	sub	esp, 0x14
 11e9c36: 56                           	push	esi
 11e9c37: 8b f1                        	mov	esi, ecx
 11e9c39: 83 3e 00                     	cmp	dword ptr [esi], 0x0
 11e9c3c: 0f 84 d1 01 00 00            	je	0x11e9e13 <.text+0x1e3>
 11e9c42: 83 7e 04 00                  	cmp	dword ptr [esi + 0x4], 0x0
 11e9c46: 0f 84 c7 01 00 00            	je	0x11e9e13 <.text+0x1e3>
 11e9c4c: 83 7e 08 00                  	cmp	dword ptr [esi + 0x8], 0x0
 11e9c50: 0f 84 bd 01 00 00            	je	0x11e9e13 <.text+0x1e3>
 11e9c56: 83 7e 0c 00                  	cmp	dword ptr [esi + 0xc], 0x0
 11e9c5a: 0f 84 b3 01 00 00            	je	0x11e9e13 <.text+0x1e3>
 11e9c60: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11e9c63: 85 c9                        	test	ecx, ecx
 11e9c65: 0f 84 a8 01 00 00            	je	0x11e9e13 <.text+0x1e3>
 11e9c6b: 83 7e 14 00                  	cmp	dword ptr [esi + 0x14], 0x0
 11e9c6f: 0f 84 9e 01 00 00            	je	0x11e9e13 <.text+0x1e3>
 11e9c75: 83 7e 18 00                  	cmp	dword ptr [esi + 0x18], 0x0
 11e9c79: 0f 84 94 01 00 00            	je	0x11e9e13 <.text+0x1e3>
 11e9c7f: 83 7e 1c 00                  	cmp	dword ptr [esi + 0x1c], 0x0
 11e9c83: 0f 84 8a 01 00 00            	je	0x11e9e13 <.text+0x1e3>
 11e9c89: 83 7e 20 00                  	cmp	dword ptr [esi + 0x20], 0x0
 11e9c8d: 0f 84 80 01 00 00            	je	0x11e9e13 <.text+0x1e3>
 11e9c93: e8 e8 a0 fc ff               	call	0x11b3d80
 11e9c98: 85 c0                        	test	eax, eax
 11e9c9a: 0f 84 73 01 00 00            	je	0x11e9e13 <.text+0x1e3>
 11e9ca0: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11e9ca3: e8 e8 a0 fc ff               	call	0x11b3d90
 11e9ca8: 85 c0                        	test	eax, eax
 11e9caa: 0f 84 63 01 00 00            	je	0x11e9e13 <.text+0x1e3>
 11e9cb0: 8b 4e 0c                     	mov	ecx, dword ptr [esi + 0xc]
 11e9cb3: 53                           	push	ebx
 11e9cb4: 57                           	push	edi
 11e9cb5: e8 c6 a0 fc ff               	call	0x11b3d80
 11e9cba: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
 11e9cbd: 89 45 f4                     	mov	dword ptr [ebp - 0xc], eax
 11e9cc0: e8 cb a0 fc ff               	call	0x11b3d90
 11e9cc5: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11e9cc8: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 11e9ccb: e8 b0 a0 fc ff               	call	0x11b3d80
 11e9cd0: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11e9cd3: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 11e9cd6: e8 b5 a0 fc ff               	call	0x11b3d90
 11e9cdb: 8b 7d 0c                     	mov	edi, dword ptr [ebp + 0xc]
 11e9cde: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 11e9ce1: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11e9ce7: 89 45 ec                     	mov	dword ptr [ebp - 0x14], eax
 11e9cea: 8b 06                        	mov	eax, dword ptr [esi]
 11e9cec: 50                           	push	eax
 11e9ced: 57                           	push	edi
 11e9cee: 53                           	push	ebx
 11e9cef: 89 5d f8                     	mov	dword ptr [ebp - 0x8], ebx
 11e9cf2: e8 59 9c fc ff               	call	0x11b3950
 11e9cf7: 03 5d f4                     	add	ebx, dword ptr [ebp - 0xc]
 11e9cfa: 83 7e 28 00                  	cmp	dword ptr [esi + 0x28], 0x0
 11e9cfe: 89 5d f4                     	mov	dword ptr [ebp - 0xc], ebx
 11e9d01: c7 45 08 00 00 00 00         	mov	dword ptr [ebp + 0x8], 0x0
 11e9d08: 7e 26                        	jle	0x11e9d30 <.text+0x100>
 11e9d0a: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
 11e9d10: 8b 56 04                     	mov	edx, dword ptr [esi + 0x4]
 11e9d13: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11e9d19: 52                           	push	edx
 11e9d1a: 57                           	push	edi
 11e9d1b: 53                           	push	ebx
 11e9d1c: e8 2f 9c fc ff               	call	0x11b3950
 11e9d21: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11e9d24: 03 5d fc                     	add	ebx, dword ptr [ebp - 0x4]
 11e9d27: 40                           	inc	eax
 11e9d28: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
 11e9d2b: 3b 46 28                     	cmp	eax, dword ptr [esi + 0x28]
 11e9d2e: 7c e0                        	jl	0x11e9d10 <.text+0xe0>
 11e9d30: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
 11e9d33: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11e9d39: 50                           	push	eax
 11e9d3a: 57                           	push	edi
 11e9d3b: 53                           	push	ebx
 11e9d3c: e8 0f 9c fc ff               	call	0x11b3950
 11e9d41: 03 7d f0                     	add	edi, dword ptr [ebp - 0x10]
 11e9d44: 83 7e 2c 00                  	cmp	dword ptr [esi + 0x2c], 0x0
 11e9d48: c7 45 0c 00 00 00 00         	mov	dword ptr [ebp + 0xc], 0x0
 11e9d4f: 7e 64                        	jle	0x11e9db5 <.text+0x185>
 11e9d51: 8b 4e 0c                     	mov	ecx, dword ptr [esi + 0xc]
 11e9d54: 8b 55 f8                     	mov	edx, dword ptr [ebp - 0x8]
 11e9d57: 51                           	push	ecx
 11e9d58: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11e9d5e: 57                           	push	edi
 11e9d5f: 52                           	push	edx
 11e9d60: e8 eb 9b fc ff               	call	0x11b3950
 11e9d65: 83 7e 28 00                  	cmp	dword ptr [esi + 0x28], 0x0
 11e9d69: 8b 5d f4                     	mov	ebx, dword ptr [ebp - 0xc]
 11e9d6c: c7 45 08 00 00 00 00         	mov	dword ptr [ebp + 0x8], 0x0
 11e9d73: 7e 20                        	jle	0x11e9d95 <.text+0x165>
 11e9d75: 8b 46 10                     	mov	eax, dword ptr [esi + 0x10]
 11e9d78: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11e9d7e: 50                           	push	eax
 11e9d7f: 57                           	push	edi
 11e9d80: 53                           	push	ebx
 11e9d81: e8 ca 9b fc ff               	call	0x11b3950
 11e9d86: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11e9d89: 03 5d fc                     	add	ebx, dword ptr [ebp - 0x4]
 11e9d8c: 40                           	inc	eax
 11e9d8d: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
 11e9d90: 3b 46 28                     	cmp	eax, dword ptr [esi + 0x28]
 11e9d93: 7c e0                        	jl	0x11e9d75 <.text+0x145>
 11e9d95: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11e9d98: 51                           	push	ecx
 11e9d99: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11e9d9f: 57                           	push	edi
 11e9da0: 53                           	push	ebx
 11e9da1: e8 aa 9b fc ff               	call	0x11b3950
 11e9da6: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11e9da9: 03 7d ec                     	add	edi, dword ptr [ebp - 0x14]
 11e9dac: 40                           	inc	eax
 11e9dad: 89 45 0c                     	mov	dword ptr [ebp + 0xc], eax
 11e9db0: 3b 46 2c                     	cmp	eax, dword ptr [esi + 0x2c]
 11e9db3: 7c 9c                        	jl	0x11e9d51 <.text+0x121>
 11e9db5: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 11e9db8: 8b 45 f8                     	mov	eax, dword ptr [ebp - 0x8]
 11e9dbb: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11e9dc1: 52                           	push	edx
 11e9dc2: 57                           	push	edi
 11e9dc3: 50                           	push	eax
 11e9dc4: e8 87 9b fc ff               	call	0x11b3950
 11e9dc9: 83 7e 28 00                  	cmp	dword ptr [esi + 0x28], 0x0
 11e9dcd: 8b 5d f4                     	mov	ebx, dword ptr [ebp - 0xc]
 11e9dd0: c7 45 08 00 00 00 00         	mov	dword ptr [ebp + 0x8], 0x0
 11e9dd7: 7e 27                        	jle	0x11e9e00 <.text+0x1d0>
 11e9dd9: 8d a4 24 00 00 00 00         	lea	esp, [esp]
 11e9de0: 8b 4e 1c                     	mov	ecx, dword ptr [esi + 0x1c]
 11e9de3: 51                           	push	ecx
 11e9de4: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11e9dea: 57                           	push	edi
 11e9deb: 53                           	push	ebx
 11e9dec: e8 5f 9b fc ff               	call	0x11b3950
 11e9df1: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11e9df4: 03 5d fc                     	add	ebx, dword ptr [ebp - 0x4]
 11e9df7: 40                           	inc	eax
 11e9df8: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
 11e9dfb: 3b 46 28                     	cmp	eax, dword ptr [esi + 0x28]
 11e9dfe: 7c e0                        	jl	0x11e9de0 <.text+0x1b0>
 11e9e00: 8b 56 20                     	mov	edx, dword ptr [esi + 0x20]
 11e9e03: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11e9e09: 52                           	push	edx
 11e9e0a: 57                           	push	edi
 11e9e0b: 53                           	push	ebx
 11e9e0c: e8 3f 9b fc ff               	call	0x11b3950
 11e9e11: 5f                           	pop	edi
 11e9e12: 5b                           	pop	ebx
 11e9e13: 5e                           	pop	esi
 11e9e14: 8b e5                        	mov	esp, ebp
 11e9e16: 5d                           	pop	ebp
 11e9e17: c2 10 00                     	ret	0x10
