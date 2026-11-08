
<stdin>:	file format elf32-i386

Disassembly of section .text:

011b4c66 <.text>:
 11b4c66: 8b d7                        	mov	edx, edi
 11b4c68: 03 d2                        	add	edx, edx
 11b4c6a: 8b 04 d0                     	mov	eax, dword ptr [eax + 8*edx]
 11b4c6d: 85 c0                        	test	eax, eax
 11b4c6f: 75 73                        	jne	0x11b4ce4 <.text+0x7e>
 11b4c71: 68 18 a1 85 01               	push	0x185a118
 11b4c76: e8 75 b2 fe ff               	call	0x119fef0
 11b4c7b: 83 c4 04                     	add	esp, 0x4
 11b4c7e: f6 86 98 00 00 00 04         	test	byte ptr [esi + 0x98], 0x4
 11b4c85: 75 51                        	jne	0x11b4cd8 <.text+0x72>
 11b4c87: 83 7e 48 08                  	cmp	dword ptr [esi + 0x48], 0x8
 11b4c8b: 72 05                        	jb	0x11b4c92 <.text+0x2c>
 11b4c8d: 8b 4e 34                     	mov	ecx, dword ptr [esi + 0x34]
 11b4c90: eb 03                        	jmp	0x11b4c95 <.text+0x2f>
 11b4c92: 8d 4e 34                     	lea	ecx, [esi + 0x34]
 11b4c95: 57                           	push	edi
 11b4c96: 51                           	push	ecx
 11b4c97: 50                           	push	eax
 11b4c98: 68 38 9f 85 01               	push	0x1859f38
 11b4c9d: e8 4e b2 fe ff               	call	0x119fef0
 11b4ca2: 83 c4 04                     	add	esp, 0x4
 11b4ca5: 50                           	push	eax
 11b4ca6: 68 96 09 00 00               	push	0x996
 11b4cab: 68 78 a0 85 01               	push	0x185a078
 11b4cb0: e8 3b b2 fe ff               	call	0x119fef0
 11b4cb5: 83 c4 04                     	add	esp, 0x4
 11b4cb8: 50                           	push	eax
 11b4cb9: 68 e0 9f 85 01               	push	0x1859fe0
 11b4cbe: e8 2d b2 fe ff               	call	0x119fef0
 11b4cc3: 83 c4 04                     	add	esp, 0x4
 11b4cc6: 50                           	push	eax
 11b4cc7: 6a 00                        	push	0x0
 11b4cc9: e8 12 e0 fe ff               	call	0x11a2ce0
 11b4cce: 83 c4 20                     	add	esp, 0x20
 11b4cd1: 83 8e 98 00 00 00 04         	or	dword ptr [esi + 0x98], 0x4
 11b4cd8: e8 f3 5f 00 00               	call	0x11bacd0 <.text+0x606a>
 11b4cdd: 8b c8                        	mov	ecx, eax
 11b4cdf: e8 bc 60 00 00               	call	0x11bada0 <.text+0x613a>
 11b4ce4: 5f                           	pop	edi
 11b4ce5: 5e                           	pop	esi
 11b4ce6: 5d                           	pop	ebp
 11b4ce7: c2 04 00                     	ret	0x4
 11b4cea: cc                           	int3
 11b4ceb: cc                           	int3
 11b4cec: cc                           	int3
 11b4ced: cc                           	int3
 11b4cee: cc                           	int3
 11b4cef: cc                           	int3
 11b4cf0: 55                           	push	ebp
 11b4cf1: 8b ec                        	mov	ebp, esp
 11b4cf3: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11b4cf6: 33 d2                        	xor	edx, edx
 11b4cf8: 83 ec 10                     	sub	esp, 0x10
 11b4cfb: 3b ca                        	cmp	ecx, edx
 11b4cfd: 76 36                        	jbe	0x11b4d35 <.text+0xcf>
 11b4cff: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b4d02: 89 55 f0                     	mov	dword ptr [ebp - 0x10], edx
 11b4d05: 89 55 f4                     	mov	dword ptr [ebp - 0xc], edx
 11b4d08: f3 0f 7e 45 f0               	movq	xmm0, qword ptr [ebp - 0x10]
 11b4d0d: 89 55 f8                     	mov	dword ptr [ebp - 0x8], edx
 11b4d10: 56                           	push	esi
 11b4d11: 8b 35 6c 21 a4 01            	mov	esi, dword ptr [0x1a4216c]
 11b4d17: 89 75 fc                     	mov	dword ptr [ebp - 0x4], esi
 11b4d1a: 3b c2                        	cmp	eax, edx
 11b4d1c: 74 0e                        	je	0x11b4d2c <.text+0xc6>
 11b4d1e: f3 0f 7e 4d f8               	movq	xmm1, qword ptr [ebp - 0x8]
 11b4d23: 66 0f d6                     	<unknown>
