
<stdin>:	file format elf32-i386

Disassembly of section .text:

011b41e0 <.text>:
 11b41e0: 55                           	push	ebp
 11b41e1: 8b ec                        	mov	ebp, esp
 11b41e3: 8b d1                        	mov	edx, ecx
 11b41e5: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 11b41e8: 85 c9                        	test	ecx, ecx
 11b41ea: 0f 84 b2 00 00 00            	je	0x11b42a2 <.text+0xc2>
 11b41f0: f3 0f 10 4d 24               	movss	xmm1, dword ptr [ebp + 0x24]
 11b41f5: f3 0f 10 15 50 22 56 01      	movss	xmm2, dword ptr [0x1562250]
 11b41fd: 0f 2e ca                     	ucomiss	xmm1, xmm2
 11b4200: 9f                           	lahf
 11b4201: f6 c4 44                     	test	ah, 0x44
 11b4204: 7a 11                        	jp	0x11b4217 <.text+0x37>
 11b4206: 66 8b 41 1c                  	mov	ax, word ptr [ecx + 0x1c]
 11b420a: 66 d1 e8                     	shr	ax
 11b420d: 0f b7 c0                     	movzx	eax, ax
 11b4210: 0f 57 c9                     	xorps	xmm1, xmm1
 11b4213: f3 0f 2a c8                  	cvtsi2ss	xmm1, eax
 11b4217: f3 0f 10 45 28               	movss	xmm0, dword ptr [ebp + 0x28]
 11b421c: 0f 2e c2                     	ucomiss	xmm0, xmm2
 11b421f: 9f                           	lahf
 11b4220: f6 c4 44                     	test	ah, 0x44
 11b4223: 7a 11                        	jp	0x11b4236 <.text+0x56>
 11b4225: 66 8b 41 1e                  	mov	ax, word ptr [ecx + 0x1e]
 11b4229: 66 d1 e8                     	shr	ax
 11b422c: 0f b7 c0                     	movzx	eax, ax
 11b422f: 0f 57 c0                     	xorps	xmm0, xmm0
 11b4232: f3 0f 2a c0                  	cvtsi2ss	xmm0, eax
 11b4236: 8b 45 20                     	mov	eax, dword ptr [ebp + 0x20]
 11b4239: 53                           	push	ebx
 11b423a: 56                           	push	esi
 11b423b: 57                           	push	edi
 11b423c: 8b 31                        	mov	esi, dword ptr [ecx]
 11b423e: 6a 24                        	push	0x24
 11b4240: 6a 00                        	push	0x0
 11b4242: 83 ec 14                     	sub	esp, 0x14
 11b4245: f3 0f 11 44 24 10            	movss	dword ptr [esp + 0x10], xmm0
 11b424b: f3 0f 10 45 18               	movss	xmm0, dword ptr [ebp + 0x18]
 11b4250: f3 0f 11 4c 24 0c            	movss	dword ptr [esp + 0xc], xmm1
 11b4256: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11b425c: f3 0f 10 45 14               	movss	xmm0, dword ptr [ebp + 0x14]
 11b4261: 8b f8                        	mov	edi, eax
 11b4263: 0f b6 d8                     	movzx	ebx, al
 11b4266: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11b426c: f3 0f 10 45 1c               	movss	xmm0, dword ptr [ebp + 0x1c]
 11b4271: c1 ef 10                     	shr	edi, 0x10
 11b4274: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11b4279: 81 e7 ff 00 00 00            	and	edi, 0xff
 11b427f: c1 e3 10                     	shl	ebx, 0x10
 11b4282: 6a 00                        	push	0x0
 11b4284: 25 00 ff 00 ff               	and	eax, 0xff00ff00
 11b4289: 0b fb                        	or	edi, ebx
 11b428b: 0b f8                        	or	edi, eax
 11b428d: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b4290: 57                           	push	edi
 11b4291: 52                           	push	edx
 11b4292: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11b4295: 52                           	push	edx
 11b4296: 8b 96 ac 00 00 00            	mov	edx, dword ptr [esi + 0xac]
 11b429c: 50                           	push	eax
 11b429d: ff d2                        	call	edx
 11b429f: 5f                           	pop	edi
 11b42a0: 5e                           	pop	esi
 11b42a1: 5b                           	pop	ebx
 11b42a2: 5d                           	pop	ebp
 11b42a3: c2 24 00                     	ret	0x24
 11b42a6: cc                           	int3
 11b42a7: cc                           	int3
 11b42a8: cc                           	int3
 11b42a9: cc                           	int3
 11b42aa: cc                           	int3
 11b42ab: cc                           	int3
 11b42ac: cc                           	int3
 11b42ad: cc                           	int3
 11b42ae: cc                           	int3
 11b42af: cc                           	int3
 11b42b0: 55                           	push	ebp
 11b42b1: 8b ec                        	mov	ebp, esp
 11b42b3: 51                           	push	ecx
 11b42b4: 83 7d 10 00                  	cmp	dword ptr [ebp + 0x10], 0x0
 11b42b8: 89 4d fc                     	mov	dword ptr [ebp - 0x4], ecx
 11b42bb: 0f 84 f0 00 00 00            	je	0x11b43b1 <.text+0x1d1>
 11b42c1: 8b 55 18                     	mov	edx, dword ptr [ebp + 0x18]
 11b42c4: 8b c2                        	mov	eax, edx
 11b42c6: 0f b6 ca                     	movzx	ecx, dl
 11b42c9: c1 e8 10                     	shr	eax, 0x10
 11b42cc: 25 ff 00 00 00               	and	eax, 0xff
 11b42d1: 53                           	push	ebx
 11b42d2: c1 e1 10                     	shl	ecx, 0x10
 11b42d5: 81 e2 00 ff 00 ff            	and	edx, 0xff00ff00
 11b42db: 0b c1                        	or	eax, ecx
 11b42dd: 56                           	push	esi
 11b42de: 8b 75                        	<unknown>
