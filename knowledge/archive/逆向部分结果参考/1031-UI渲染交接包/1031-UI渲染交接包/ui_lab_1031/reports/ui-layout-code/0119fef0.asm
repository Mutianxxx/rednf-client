
<stdin>:	file format elf32-i386

Disassembly of section .text:

0119fef0 <.text>:
 119fef0: 55                           	push	ebp
 119fef1: 8b ec                        	mov	ebp, esp
 119fef3: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 119fef6: 66 8b 08                     	mov	cx, word ptr [eax]
 119fef9: ba a1 2c 00 00               	mov	edx, 0x2ca1
 119fefe: 66 3b ca                     	cmp	cx, dx
 119ff01: 75 05                        	jne	0x119ff08 <.text+0x18>
 119ff03: 83 c0 04                     	add	eax, 0x4
 119ff06: 5d                           	pop	ebp
 119ff07: c3                           	ret
 119ff08: 6a 02                        	push	0x2
 119ff0a: 50                           	push	eax
 119ff0b: e8 90 fe ff ff               	call	0x119fda0
 119ff10: 83 c4 08                     	add	esp, 0x8
 119ff13: 5d                           	pop	ebp
 119ff14: c3                           	ret
 119ff15: cc                           	int3
 119ff16: cc                           	int3
 119ff17: cc                           	int3
 119ff18: cc                           	int3
 119ff19: cc                           	int3
 119ff1a: cc                           	int3
 119ff1b: cc                           	int3
 119ff1c: cc                           	int3
 119ff1d: cc                           	int3
 119ff1e: cc                           	int3
 119ff1f: cc                           	int3
 119ff20: a1 0c 8a b0 01               	mov	eax, dword ptr [0x1b08a0c]
 119ff25: c3                           	ret
 119ff26: cc                           	int3
 119ff27: cc                           	int3
 119ff28: cc                           	int3
 119ff29: cc                           	int3
 119ff2a: cc                           	int3
 119ff2b: cc                           	int3
 119ff2c: cc                           	int3
 119ff2d: cc                           	int3
 119ff2e: cc                           	int3
 119ff2f: cc                           	int3
 119ff30: 55                           	push	ebp
 119ff31: 8b ec                        	mov	ebp, esp
 119ff33: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 119ff36: a1 0c 8a b0 01               	mov	eax, dword ptr [0x1b08a0c]
 119ff3b: 89 0d 0c 8a b0 01            	mov	dword ptr [0x1b08a0c], ecx
 119ff41: 5d                           	pop	ebp
 119ff42: c3                           	ret
 119ff43: cc                           	int3
 119ff44: cc                           	int3
 119ff45: cc                           	int3
 119ff46: cc                           	int3
 119ff47: cc                           	int3
 119ff48: cc                           	int3
 119ff49: cc                           	int3
 119ff4a: cc                           	int3
 119ff4b: cc                           	int3
 119ff4c: cc                           	int3
 119ff4d: cc                           	int3
 119ff4e: cc                           	int3
 119ff4f: cc                           	int3
 119ff50: a1 a0 30 da 01               	mov	eax, dword ptr [0x1da30a0]
 119ff55: 64 8b 0d 2c 00 00 00         	mov	ecx, dword ptr fs:[0x2c]
 119ff5c: 8b 04 81                     	mov	eax, dword ptr [ecx + 4*eax]
 119ff5f: 8b 90 18 24 03 00            	mov	edx, dword ptr [eax + 0x32418]
 119ff65: c1 e2 0c                     	shl	edx, 0xc
 119ff68: 8d 84 02 10 04 00 00         	lea	eax, [edx + eax + 0x410]
 119ff6f: c3                           	ret
 119ff70: b8 00 10 00 00               	mov	eax, 0x1000
 119ff75: c3                           	ret
 119ff76: cc                           	int3
 119ff77: cc                           	int3
 119ff78: cc                           	int3
 119ff79: cc                           	int3
 119ff7a: cc                           	int3
 119ff7b: cc                           	int3
 119ff7c: cc                           	int3
 119ff7d: cc                           	int3
 119ff7e: cc                           	int3
 119ff7f: cc                           	int3
 119ff80: 55                           	push	ebp
 119ff81: 8b ec                        	mov	ebp, esp
 119ff83: a1 a0 30 da 01               	mov	eax, dword ptr [0x1da30a0]
 119ff88: 64 8b 0d 2c 00 00 00         	mov	ecx, dword ptr fs:[0x2c]
 119ff8f: 53                           	push	ebx
 119ff90: 56                           	push	esi
 119ff91: 8b 34 81                     	mov	esi, dword ptr [ecx + 4*eax]
 119ff94: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 119ff97: 8b 0d 0c 8a b0 01            	mov	ecx, dword ptr [0x1b08a0c]
 119ff9d: 57                           	push	edi
 119ff9e: 8b be 10 24 03 00            	mov	edi, dword ptr [esi + 0x32410]
 119ffa4: 68 00 10 00 00               	push	0x1000
 119ffa9: 8b d7                        	mov	edx, edi
 119ffab: c1 e2 0d                     	shl	edx, 0xd
 119ffae: 8d 9c 32 10 e4 01 00         	lea	ebx, [edx + esi + 0x1e410]
 119ffb5: 53                           	push	ebx
 119ffb6: 6a ff                        	push	-0x1
 119ffb8: 50                           	push	eax
 119ffb9: 6a 00                        	push	0x0
 119ffbb: 51                           	push	ecx
 119ffbc: ff 15 d4 a1 55 01            	call	dword ptr [0x155a1d4]
 119ffc2: c1 e7 0c                     	shl	edi, 0xc
 119ffc5: 03 c7                        	add	eax, edi
 119ffc7: 33 d2                        	xor	edx, edx
 119ffc9: 66 89 94 46 10 e4 01 00      	mov	word ptr [esi + 2*eax + 0x1e410], dx
 119ffd1: 8b 86 10 24 03 00            	mov	eax, dword ptr [esi + 0x32410]
 119ffd7: 40                           	inc	eax
 119ffd8: 99                           	cdq
 119ffd9: b9 0a 00 00 00               	mov	ecx, 0xa
 119ffde: f7 f9                        	idiv	ecx
 119ffe0: 5f                           	pop	edi
 119ffe1: 8b c3                        	mov	eax, ebx
 119ffe3: 89 96 10 24 03 00            	mov	dword ptr [esi + 0x32410], edx
 119ffe9: 5e                           	pop	esi
 119ffea: 5b                           	pop	ebx
 119ffeb: 5d                           	pop	ebp
 119ffec: c3                           	ret
 119ffed: cc                           	int3
 119ffee: cc                           	int3
 119ffef: cc                           	int3
 119fff0: 55                           	push	ebp
 119fff1: 8b ec                        	mov	ebp, esp
 119fff3: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 119fff6: 5d                           	pop	ebp
 119fff7: c3                           	ret
 119fff8: cc                           	int3
 119fff9: cc                           	int3
 119fffa: cc                           	int3
 119fffb: cc                           	int3
 119fffc: cc                           	int3
 119fffd: cc                           	int3
 119fffe: cc                           	int3
 119ffff: cc                           	int3
 11a0000: 55                           	push	ebp
 11a0001: 8b ec                        	mov	ebp, esp
 11a0003: a1 a0 30 da 01               	mov	eax, dword ptr [0x1da30a0]
 11a0008: 64 8b 0d 2c 00 00 00         	mov	ecx, dword ptr fs:[0x2c]
 11a000f: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11a0012: 53                           	push	ebx
 11a0013: 56                           	push	esi
 11a0014: 8b 34 81                     	mov	esi, dword ptr [ecx + 4*eax]
 11a0017: a1 0c 8a b0 01               	mov	eax, dword ptr [0x1b08a0c]
 11a001c: 57                           	push	edi
 11a001d: 8b be 18 24 03 00            	mov	edi, dword ptr [esi + 0x32418]
 11a0023: 6a 00                        	push	0x0
 11a0025: 6a 00                        	push	0x0
 11a0027: 68 00 10 00 00               	push	0x1000
 11a002c: c1 e7 0c                     	shl	edi, 0xc
 11a002f: 8d 9c 37 10 04 00 00         	lea	ebx, [edi + esi + 0x410]
 11a0036: 53                           	push	ebx
 11a0037: 6a ff                        	push	-0x1
 11a0039: 52                           	push	edx
 11a003a: 6a 00                        	push	0x0
 11a003c: 50                           	push	eax
 11a003d: ff 15 38 a2 55 01            	call	dword ptr [0x155a238]
 11a0043: 03 c7                        	add	eax, edi
 11a0045: c6 84 30 10 04 00 00 00      	mov	byte ptr [eax + esi + 0x410], 0x0
 11a004d: 8b 86 18 24 03 00            	mov	eax, dword ptr [esi + 0x32418]
 11a0053: 40                           	inc	eax
 11a0054: 99                           	cdq
 11a0055: b9 0a 00 00 00               	mov	ecx, 0xa
 11a005a: f7 f9                        	idiv	ecx
 11a005c: 5f                           	pop	edi
 11a005d: 8b c3                        	mov	eax, ebx
 11a005f: 89 96 18 24 03 00            	mov	dword ptr [esi + 0x32418], edx
 11a0065: 5e                           	pop	esi
 11a0066: 5b                           	pop	ebx
 11a0067: 5d                           	pop	ebp
 11a0068: c3                           	ret
 11a0069: cc                           	int3
 11a006a: cc                           	int3
 11a006b: cc                           	int3
 11a006c: cc                           	int3
 11a006d: cc                           	int3
 11a006e: cc                           	int3
 11a006f: cc                           	int3
 11a0070: 55                           	push	ebp
 11a0071: 8b ec                        	mov	ebp, esp
 11a0073: a1 a0 30 da 01               	mov	eax, dword ptr [0x1da30a0]
 11a0078: 64 8b 0d 2c 00 00 00         	mov	ecx, dword ptr fs:[0x2c]
 11a007f: 53                           	push	ebx
 11a0080: 56                           	push	esi
 11a0081: 8b 34 81                     	mov	esi, dword ptr [ecx + 4*eax]
 11a0084: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11a0087: 8b 0d 0c 8a b0 01            	mov	ecx, dword ptr [0x1b08a0c]
 11a008d: 57                           	push	edi
 11a008e: 8b be 14 24 03 00            	mov	edi, dword ptr [esi + 0x32414]
 11a0094: 68 00 10 00 00               	push	0x1000
 11a0099: 8b d7                        	mov	edx, edi
 11a009b: c1 e2 0d                     	shl	edx, 0xd
 11a009e: 8d 9c 32 10 a4 00 00         	lea	ebx, [edx + esi + 0xa410]
 11a00a5: 53                           	push	ebx
 11a00a6: 6a ff                        	push	-0x1
 11a00a8: 50                           	push	eax
 11a00a9: 6a 00                        	push	0x0
 11a00ab: 51                           	push	ecx
 11a00ac: ff 15 d4 a1 55 01            	call	dword ptr [0x155a1d4]
 11a00b2: c1 e7 0c                     	shl	edi, 0xc
 11a00b5: 03 c7                        	add	eax, edi
 11a00b7: 33 d2                        	xor	edx, edx
 11a00b9: 66 89 94 46 10 a4 00 00      	mov	word ptr [esi + 2*eax + 0xa410], dx
 11a00c1: 8b 86 14 24 03 00            	mov	eax, dword ptr [esi + 0x32414]
 11a00c7: 40                           	inc	eax
 11a00c8: 99                           	cdq
 11a00c9: b9 0a 00 00 00               	mov	ecx, 0xa
 11a00ce: f7 f9                        	idiv	ecx
 11a00d0: 5f                           	pop	edi
 11a00d1: 8b c3                        	mov	eax, ebx
 11a00d3: 89 96 14 24 03 00            	mov	dword ptr [esi + 0x32414], edx
 11a00d9: 5e                           	pop	esi
 11a00da: 5b                           	pop	ebx
 11a00db: 5d                           	pop	ebp
 11a00dc: c3                           	ret
 11a00dd: cc                           	int3
 11a00de: cc                           	int3
 11a00df: cc                           	int3
 11a00e0: 55                           	push	ebp
 11a00e1: 8b ec                        	mov	ebp, esp
 11a00e3: 51                           	push	ecx
 11a00e4: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 11a00e7: 53                           	push	ebx
 11a00e8: 8b 5d 0c                     	mov	ebx, dword ptr [ebp + 0xc]
 11a00eb: 56                           	push	esi
 11a00ec: 6a 00                        	push	0x0
 11a00ee: 6a 00                        	push	0x0
 11a00f0: 6a ff                        	push	-0x1
 11a00f2: 53                           	push	ebx
 11a00f3: 6a 00                        	push	0x0
 11a00f5: 50                           	push	eax
 11a00f6: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11a00fd: ff 15 d4 a1 55 01            	call	dword ptr [0x155a1d4]
 11a0103: 8b f0                        	mov	esi, eax
 11a0105: 4e                           	dec	esi
 11a0106: 75 12                        	jne	0x11a011a <.text+0x22a>
 11a0108: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 11a010b: 8b ce                        	mov	ecx, esi
 11a010d: e8 8e 36 00 00               	call	0x11a37a0 <.text+0x38b0>
 11a0112: 8b c6                        	mov	eax, esi
 11a0114: 5e                           	pop	esi
 11a0115: 5b                           	pop	ebx
 11a0116: 8b e5                        	mov	esp, ebp
 11a0118: 5d                           	pop	ebp
 11a0119: c3                           	ret
 11a011a: 57                           	push	edi
 11a011b: 56                           	push	esi
 11a011c: e8 6f 34 00 00               	call	0x11a3590 <.text+0x36a0>
 11a0121: 83 c4 04                     	add	esp, 0x4
 11a0124: 8b f8                        	mov	edi, eax
 11a0126: 46                           	inc	esi
 11a0127: 56                           	push	esi
 11a0128: 8b cf                        	mov	ecx, edi
 11a012a: e8 81 13 38 ff               	call	0x5214b0
 11a012f: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 11a0132: 50                           	push	eax
 11a0133: 6a ff                        	push	-0x1
 11a0135: 53                           	push	ebx
 11a0136: 6a 00                        	push	0x0
 11a0138: 51                           	push	ecx
 11a0139: ff 15 d4 a1 55 01            	call	dword ptr [0x155a1d4]
 11a013f: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 11a0142: 57                           	push	edi
 11a0143: 8b ce                        	mov	ecx, esi
 11a0145: e8 16 36 00 00               	call	0x11a3760 <.text+0x3870>
 11a014a: 5f                           	pop	edi
 11a014b: 8b c6                        	mov	eax, esi
 11a014d: 5e                           	pop	esi
 11a014e: 5b                           	pop	ebx
 11a014f: 8b e5                        	mov	esp, ebp
 11a0151: 5d                           	pop	ebp
 11a0152: c3                           	ret
 11a0153: cc                           	int3
 11a0154: cc                           	int3
 11a0155: cc                           	int3
 11a0156: cc                           	int3
 11a0157: cc                           	int3
 11a0158: cc                           	int3
 11a0159: cc                           	int3
 11a015a: cc                           	int3
 11a015b: cc                           	int3
 11a015c: cc                           	int3
 11a015d: cc                           	int3
 11a015e: cc                           	int3
 11a015f: cc                           	int3
 11a0160: 55                           	push	ebp
 11a0161: 8b ec                        	mov	ebp, esp
 11a0163: 51                           	push	ecx
 11a0164: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11a0167: 56                           	push	esi
 11a0168: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 11a016b: 50                           	push	eax
 11a016c: 8b ce                        	mov	ecx, esi
 11a016e: c7 45                        	<unknown>
