
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c2cf0 <.text>:
 11c2cf0: e8 9b fe ff ff               	call	0x11c2b90
 11c2cf5: c6 41 04 00                  	mov	byte ptr [ecx + 0x4], 0x0
 11c2cf9: b8 01 00 00 00               	mov	eax, 0x1
 11c2cfe: c3                           	ret
 11c2cff: cc                           	int3
 11c2d00: 56                           	push	esi
 11c2d01: 8b f1                        	mov	esi, ecx
 11c2d03: e8 48 b5 ff ff               	call	0x11be250
 11c2d08: 84 c0                        	test	al, al
 11c2d0a: 0f 84 95 00 00 00            	je	0x11c2da5 <.text+0xb5>
 11c2d10: 83 be c8 02 00 00 00         	cmp	dword ptr [esi + 0x2c8], 0x0
 11c2d17: 0f 84 88 00 00 00            	je	0x11c2da5 <.text+0xb5>
 11c2d1d: 6a 00                        	push	0x0
 11c2d1f: 6a 02                        	push	0x2
 11c2d21: e8 3a 07 ff ff               	call	0x11b3460
 11c2d26: f3 0f 10 05 50 22 56 01      	movss	xmm0, dword ptr [0x1562250]
 11c2d2e: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c2d34: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c2d39: 68 90 01 00 00               	push	0x190
 11c2d3e: ff 15 88 a5 55 01            	call	dword ptr [0x155a588]
 11c2d44: 50                           	push	eax
 11c2d45: 68 82 00 00 00               	push	0x82
 11c2d4a: 68 ff 00 00 00               	push	0xff
 11c2d4f: e8 0c 6c ff ff               	call	0x11b9960
 11c2d54: 0f 57 c0                     	xorps	xmm0, xmm0
 11c2d57: 8b 8e c8 02 00 00            	mov	ecx, dword ptr [esi + 0x2c8]
 11c2d5d: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 11c2d60: 0f b6 c0                     	movzx	eax, al
 11c2d63: 83 c4 10                     	add	esp, 0x10
 11c2d66: c1 e0 18                     	shl	eax, 0x18
 11c2d69: 0d ff ff ff 00               	or	eax, 0xffffff
 11c2d6e: 50                           	push	eax
 11c2d6f: 8b 46 14                     	mov	eax, dword ptr [esi + 0x14]
 11c2d72: 83 ec 0c                     	sub	esp, 0xc
 11c2d75: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11c2d7b: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11c2d83: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c2d89: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c2d8e: 51                           	push	ecx
 11c2d8f: 52                           	push	edx
 11c2d90: 50                           	push	eax
 11c2d91: 8b ce                        	mov	ecx, esi
 11c2d93: e8 78 b6 ff ff               	call	0x11be410
 11c2d98: 8b c8                        	mov	ecx, eax
 11c2d9a: e8 41 14 ff ff               	call	0x11b41e0
 11c2d9f: 5e                           	pop	esi
 11c2da0: e9 cb 07 ff ff               	jmp	0x11b3570
 11c2da5: 5e                           	pop	esi
 11c2da6: c3                           	ret
 11c2da7: cc                           	int3
 11c2da8: cc                           	int3
 11c2da9: cc                           	int3
 11c2daa: cc                           	int3
 11c2dab: cc                           	int3
 11c2dac: cc                           	int3
 11c2dad: cc                           	int3
 11c2dae: cc                           	int3
 11c2daf: cc                           	int3
 11c2db0: 55                           	push	ebp
 11c2db1: 8b ec                        	mov	ebp, esp
 11c2db3: 83 ec 0c                     	sub	esp, 0xc
 11c2db6: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11c2db9: 53                           	push	ebx
 11c2dba: 8d 04 40                     	lea	eax, [eax + 2*eax]
 11c2dbd: 56                           	push	esi
 11c2dbe: 03 c0                        	add	eax, eax
 11c2dc0: 8b 9c 00 50 22 a4 01         	mov	ebx, dword ptr [eax + eax + 0x1a42250]
 11c2dc7: 8b 94 00 58 22 a4 01         	mov	edx, dword ptr [eax + eax + 0x1a42258]
 11c2dce: 03 c0                        	add	eax, eax
 11c2dd0: 8b f1                        	mov	esi, ecx
 11c2dd2: 8b 88 54 22 a4 01            	mov	ecx, dword ptr [eax + 0x1a42254]
 11c2dd8: 57                           	push	edi
 11c2dd9: 89 4d f8                     	mov	dword ptr [ebp - 0x8], ecx
 11c2ddc: 8b 8e 50 03 00 00            	mov	ecx, dword ptr [esi + 0x350]
 11c2de2: 53                           	push	ebx
 11c2de3: 89 55 f4                     	mov	dword ptr [ebp - 0xc], edx
 11c2de6: e8 e5 1d ff ff               	call	0x11b4bd0
 11c2deb: 8b c8                        	mov	ecx, eax
 11c2ded: e8 ce 0f ff ff               	call	0x11b3dc0
 11c2df2: 8b be 4c 03 00 00            	mov	edi, dword ptr [esi + 0x34c]
 11c2df8: 2b 3d e8 64 b5 01            	sub	edi, dword ptr [0x1b564e8]
 11c2dfe: 8b 8e 50 03 00 00            	mov	ecx, dword ptr [esi + 0x350]
 11c2e04: 0f 57 c0                     	xorps	xmm0, xmm0
 11c2e07: f3 0f 2a c7                  	cvtsi2ss	xmm0, edi
 11c2e0b: f3 0f 59 05 84 21 56 01      	mulss	xmm0, dword ptr [0x1562184]
 11c2e13: 53                           	push	ebx
 11c2e14: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
 11c2e17: f3 0f 11 45 fc               	movss	dword ptr [ebp - 0x4], xmm0
 11c2e1c: e8 af 1d ff ff               	call	0x11b4bd0
 11c2e21: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11c2e24: 50                           	push	eax
 11c2e25: 8b 46 18                     	mov	eax, dword ptr [esi + 0x18]
 11c2e28: 50                           	push	eax
 11c2e29: 51                           	push	ecx
 11c2e2a: 8b ce                        	mov	ecx, esi
 11c2e2c: e8 df b5 ff ff               	call	0x11be410
 11c2e31: 8b c8                        	mov	ecx, eax
 11c2e33: e8 18 0b ff ff               	call	0x11b3950
 11c2e38: f3 0f 10 05 50 22 56 01      	movss	xmm0, dword ptr [0x1562250]
 11c2e40: 8b 55 f8                     	mov	edx, dword ptr [ebp - 0x8]
 11c2e43: 8b 8e 50 03 00 00            	mov	ecx, dword ptr [esi + 0x350]
 11c2e49: 83 ec 08                     	sub	esp, 0x8
 11c2e4c: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c2e52: 0f 57 c0                     	xorps	xmm0, xmm0
 11c2e55: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c2e5a: 6a ff                        	push	-0x1
 11c2e5c: 83 ec 0c                     	sub	esp, 0xc
 11c2e5f: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11c2e65: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11c2e6d: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c2e73: f3 0f 10 45 fc               	movss	xmm0, dword ptr [ebp - 0x4]
 11c2e78: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c2e7d: 52                           	push	edx
 11c2e7e: e8 4d 1d ff ff               	call	0x11b4bd0
 11c2e83: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11c2e86: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 11c2e89: 50                           	push	eax
 11c2e8a: 8b 46 18                     	mov	eax, dword ptr [esi + 0x18]
 11c2e8d: 03 cb                        	add	ecx, ebx
 11c2e8f: 50                           	push	eax
 11c2e90: 51                           	push	ecx
 11c2e91: 8b ce                        	mov	ecx, esi
 11c2e93: e8 78 b5 ff ff               	call	0x11be410
 11c2e98: 8b c8                        	mov	ecx, eax
 11c2e9a: e8 41 13 ff ff               	call	0x11b41e0
 11c2e9f: 8b 55 f4                     	mov	edx, dword ptr [ebp - 0xc]
 11c2ea2: 8b 8e 50 03 00 00            	mov	ecx, dword ptr [esi + 0x350]
 11c2ea8: 52                           	push	edx
 11c2ea9: e8 22 1d ff ff               	call	0x11b4bd0
 11c2eae: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11c2eb1: 50                           	push	eax
 11c2eb2: 8b 46 18                     	mov	eax, dword ptr [esi + 0x18]
 11c2eb5: 03 cf                        	add	ecx, edi
 11c2eb7: 03 cb                        	add	ecx, ebx
 11c2eb9: 50                           	push	eax
 11c2eba: 51                           	push	ecx
 11c2ebb: 8b ce                        	mov	ecx, esi
 11c2ebd: e8 4e b5 ff ff               	call	0x11be410
 11c2ec2: 8b c8                        	mov	ecx, eax
 11c2ec4: e8 87 0a ff ff               	call	0x11b3950
 11c2ec9: 8b ce                        	mov	ecx, esi
 11c2ecb: e8 80 b3 ff ff               	call	0x11be250
 11c2ed0: 84 c0                        	test	al, al
 11c2ed2: 0f 84 65 01 00 00            	je	0x11c303d <.text+0x34d>
 11c2ed8: 68 90 01 00 00               	push	0x190
 11c2edd: ff 15 88 a5 55 01            	call	dword ptr [0x155a588]
 11c2ee3: 50                           	push	eax
 11c2ee4: 68 82 00 00 00               	push	0x82
 11c2ee9: 68 ff 00 00 00               	push	0xff
 11c2eee: e8 6d 6a ff ff               	call	0x11b9960
 11c2ef3: 0f b6 d8                     	movzx	ebx, al
 11c2ef6: 6a 00                        	push	0x0
 11c2ef8: c1 e3 18                     	shl	ebx, 0x18
 11c2efb: 6a 02                        	push	0x2
 11c2efd: 81 cb ff ff ff 00            	or	ebx, 0xffffff
 11c2f03: e8 58 05 ff ff               	call	0x11b3460
 11c2f08: f3 0f 10 05 50 22 56 01      	movss	xmm0, dword ptr [0x1562250]
 11c2f10: 8b 8e 50 03 00 00            	mov	ecx, dword ptr [esi + 0x350]
 11c2f16: f3 0f 11 44 24 14            	movss	dword ptr [esp + 0x14], xmm0
 11c2f1c: 83 c4 10                     	add	esp, 0x10
 11c2f1f: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c2f24: 0f 57 c0                     	xorps	xmm0, xmm0
 11c2f27: 53                           	push	ebx
 11c2f28: 83 ec 0c                     	sub	esp, 0xc
 11c2f2b: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11c2f31: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11c2f39: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c2f3f: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c2f44: 68 c2 00 00 00               	push	0xc2
 11c2f49: e8 82 1c ff ff               	call	0x11b4bd0
 11c2f4e: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 11c2f51: 50                           	push	eax
 11c2f52: 8b 46 14                     	mov	eax, dword ptr [esi + 0x14]
 11c2f55: 83 ea 06                     	sub	edx, 0x6
 11c2f58: 52                           	push	edx
 11c2f59: 83 e8 06                     	sub	eax, 0x6
 11c2f5c: 50                           	push	eax
 11c2f5d: 8b ce                        	mov	ecx, esi
 11c2f5f: e8 ac b4 ff ff               	call	0x11be410
 11c2f64: 8b c8                        	mov	ecx, eax
 11c2f66: e8 75 12 ff ff               	call	0x11b41e0
 11c2f6b: f3 0f 10 05 50 22 56 01      	movss	xmm0, dword ptr [0x1562250]
 11c2f73: 8b 8e 50 03 00 00            	mov	ecx, dword ptr [esi + 0x350]
 11c2f79: 83 ec 08                     	sub	esp, 0x8
 11c2f7c: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c2f82: 0f 57 c0                     	xorps	xmm0, xmm0
 11c2f85: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c2f8a: 53                           	push	ebx
 11c2f8b: 83 ec 0c                     	sub	esp, 0xc
 11c2f8e: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11c2f94: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11c2f9c: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c2fa2: f3 0f 10 45 fc               	movss	xmm0, dword ptr [ebp - 0x4]
 11c2fa7: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c2fac: 68 c3 00 00 00               	push	0xc3
 11c2fb1: e8 1a 1c ff ff               	call	0x11b4bd0
 11c2fb6: 8b 4e 18                     	mov	ecx, dword ptr [esi + 0x18]
 11c2fb9: 8b 56 14                     	mov	edx, dword ptr [esi + 0x14]
 11c2fbc: 03 55 08                     	add	edx, dword ptr [ebp + 0x8]
 11c2fbf: 50                           	push	eax
 11c2fc0: 83 e9 06                     	sub	ecx, 0x6
 11c2fc3: 51                           	push	ecx
 11c2fc4: 52                           	push	edx
 11c2fc5: 8b ce                        	mov	ecx, esi
 11c2fc7: e8 44 b4 ff ff               	call	0x11be410
 11c2fcc: 8b c8                        	mov	ecx, eax
 11c2fce: e8 0d 12 ff ff               	call	0x11b41e0
 11c2fd3: f3 0f 10 05 50 22 56 01      	movss	xmm0, dword ptr [0x1562250]
 11c2fdb: 8b 8e 50 03 00 00            	mov	ecx, dword ptr [esi + 0x350]
 11c2fe1: 83 ec 08                     	sub	esp, 0x8
 11c2fe4: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c2fea: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c2fef: 0f 57 c0                     	xorps	xmm0, xmm0
 11c2ff2: 53                           	push	ebx
 11c2ff3: 83 ec 0c                     	sub	esp, 0xc
 11c2ff6: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11c2ffc: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11c3004: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c300a: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c300f: 68 c4 00 00 00               	push	0xc4
 11c3014: e8 b7 1b ff ff               	call	0x11b4bd0
 11c3019: 50                           	push	eax
 11c301a: 8b 46 18                     	mov	eax, dword ptr [esi + 0x18]
 11c301d: 83 e8 06                     	sub	eax, 0x6
 11c3020: 50                           	push	eax
 11c3021: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11c3024: 03 cf                        	add	ecx, edi
 11c3026: 03 4d 08                     	add	ecx, dword ptr [ebp + 0x8]
 11c3029: 51                           	push	ecx
 11c302a: 8b ce                        	mov	ecx, esi
 11c302c: e8 df b3 ff ff               	call	0x11be410
 11c3031: 8b c8                        	mov	ecx, eax
 11c3033: e8 a8 11 ff ff               	call	0x11b41e0
 11c3038: e8 33 05 ff ff               	call	0x11b3570
 11c303d: 5f                           	pop	edi
 11c303e: 5e                           	pop	esi
 11c303f: 5b                           	pop	ebx
 11c3040: 8b e5                        	mov	esp, ebp
 11c3042: 5d                           	pop	ebp
 11c3043: c2 04 00                     	ret	0x4
 11c3046: cc                           	int3
 11c3047: cc                           	int3
 11c3048: cc                           	int3
 11c3049: cc                           	int3
 11c304a: cc                           	int3
 11c304b: cc                           	int3
 11c304c: cc                           	int3
 11c304d: cc                           	int3
 11c304e: cc                           	int3
 11c304f: cc                           	int3
 11c3050: 55                           	push	ebp
 11c3051: 8b ec                        	mov	ebp, esp
 11c3053: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11c3056: 89 81 5c 03 00 00            	mov	dword ptr [ecx + 0x35c], eax
 11c305c: 89 81 60 03 00 00            	mov	dword ptr [ecx + 0x360], eax
 11c3062: 89 81 64 03 00 00            	mov	dword ptr [ecx + 0x364], eax
 11c3068: 89 81 68 03 00 00            	mov	dword ptr [ecx + 0x368], eax
 11c306e: 5d                           	pop	ebp
 11c306f: c2 04 00                     	ret	0x4
 11c3072: cc                           	int3
 11c3073: cc                           	int3
 11c3074: cc                           	int3
 11c3075: cc                           	int3
 11c3076: cc                           	int3
 11c3077: cc                           	int3
 11c3078: cc                           	int3
 11c3079: cc                           	int3
 11c307a: cc                           	int3
 11c307b: cc                           	int3
 11c307c: cc                           	int3
 11c307d: cc                           	int3
 11c307e: cc                           	int3
 11c307f: cc                           	int3
 11c3080: 55                           	push	ebp
 11c3081: 8b ec                        	mov	ebp, esp
 11c3083: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11c3086: 83 f8 03                     	cmp	eax, 0x3
 11c3089: 77 0a                        	ja	0x11c3095 <.text+0x3a5>
 11c308b: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11c308e: 89 94 81 5c 03 00 00         	mov	dword ptr [ecx + 4*eax + 0x35c], edx
 11c3095: 5d                           	pop	ebp
 11c3096: c2 08 00                     	ret	0x8
 11c3099: cc                           	int3
 11c309a: cc                           	int3
 11c309b: cc                           	int3
 11c309c: cc                           	int3
 11c309d: cc                           	int3
 11c309e: cc                           	int3
 11c309f: cc                           	int3
 11c30a0: 55                           	push	ebp
 11c30a1: 8b ec                        	mov	ebp, esp
 11c30a3: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 11c30a6: 83 f8 03                     	cmp	eax, 0x3
 11c30a9: 77 14                        	ja	0x11c30bf <.text+0x3cf>
 11c30ab: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11c30ae: 89 94 81 6c 03 00 00         	mov	dword ptr [ecx + 4*eax + 0x36c], edx
 11c30b5: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11c30b8: 89 94 81 7c 03 00 00         	mov	dword ptr [ecx + 4*eax + 0x37c], edx
 11c30bf: 5d                           	pop	ebp
 11c30c0: c2 0c 00                     	ret	0xc
 11c30c3: cc                           	int3
 11c30c4: cc                           	int3
 11c30c5: cc                           	int3
 11c30c6: cc                           	int3
 11c30c7: cc                           	int3
 11c30c8: cc                           	int3
 11c30c9: cc                           	int3
 11c30ca: cc                           	int3
 11c30cb: cc                           	int3
 11c30cc: cc                           	int3
 11c30cd: cc                           	int3
 11c30ce: cc                           	int3
 11c30cf: cc                           	int3
 11c30d0: 55                           	push	ebp
 11c30d1: 8b ec                        	mov	ebp, esp
 11c30d3: f3 0f 10 45 08               	movss	xmm0, dword ptr [ebp + 0x8]
 11c30d8: f3 0f 11 81 8c 03 00 00      	movss	dword ptr [ecx + 0x38c], xmm0
 11c30e0: f3 0f 10 45 0c               	movss	xmm0, dword ptr [ebp + 0xc]
 11c30e5: f3 0f 11 81 90 03 00 00      	movss	dword ptr [ecx + 0x390], xmm0
 11c30ed: 5d                           	pop	ebp
 11c30ee: c2                           	<unknown>
 11c30ef: 08                           	<unknown>
