
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
 11b42de: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 11b42e1: 8b 1e                        	mov	ebx, dword ptr [esi]
 11b42e3: 0b c2                        	or	eax, edx
 11b42e5: 8b 56 08                     	mov	edx, dword ptr [esi + 0x8]
 11b42e8: 3b da                        	cmp	ebx, edx
 11b42ea: 0f 84 bf 00 00 00            	je	0x11b43af <.text+0x1cf>
 11b42f0: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
 11b42f3: 57                           	push	edi
 11b42f4: 8b 7e 0c                     	mov	edi, dword ptr [esi + 0xc]
 11b42f7: 3b cf                        	cmp	ecx, edi
 11b42f9: 0f 84 af 00 00 00            	je	0x11b43ae <.text+0x1ce>
 11b42ff: 8b 75 0c                     	mov	esi, dword ptr [ebp + 0xc]
 11b4302: 2b d3                        	sub	edx, ebx
 11b4304: 0f 57 c0                     	xorps	xmm0, xmm0
 11b4307: f3 0f 2a c2                  	cvtsi2ss	xmm0, edx
 11b430b: 8b 56 08                     	mov	edx, dword ptr [esi + 0x8]
 11b430e: 2b 16                        	sub	edx, dword ptr [esi]
 11b4310: 0f 57 c9                     	xorps	xmm1, xmm1
 11b4313: f3 0f 2a ca                  	cvtsi2ss	xmm1, edx
 11b4317: 8b 56 0c                     	mov	edx, dword ptr [esi + 0xc]
 11b431a: 2b 56 04                     	sub	edx, dword ptr [esi + 0x4]
 11b431d: 6a 24                        	push	0x24
 11b431f: f3 0f 5e c1                  	divss	xmm0, xmm1
 11b4323: 2b f9                        	sub	edi, ecx
 11b4325: 56                           	push	esi
 11b4326: 83 ec 14                     	sub	esp, 0x14
 11b4329: 0f 57 c9                     	xorps	xmm1, xmm1
 11b432c: f3 0f 2a cf                  	cvtsi2ss	xmm1, edi
 11b4330: 0f 57 d2                     	xorps	xmm2, xmm2
 11b4333: f3 0f 2a d2                  	cvtsi2ss	xmm2, edx
 11b4337: 8b d0                        	mov	edx, eax
 11b4339: 0f b6 f8                     	movzx	edi, al
 11b433c: f3 0f 5e ca                  	divss	xmm1, xmm2
 11b4340: 0f 57 d2                     	xorps	xmm2, xmm2
 11b4343: f3 0f 11 54 24 10            	movss	dword ptr [esp + 0x10], xmm2
 11b4349: f3 0f 11 54 24 0c            	movss	dword ptr [esp + 0xc], xmm2
 11b434f: f3 0f 11 4c 24 08            	movss	dword ptr [esp + 0x8], xmm1
 11b4355: c1 ea 10                     	shr	edx, 0x10
 11b4358: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11b435e: 81 e2 ff 00 00 00            	and	edx, 0xff
 11b4364: c1 e7 10                     	shl	edi, 0x10
 11b4367: 0b d7                        	or	edx, edi
 11b4369: 25 00 ff 00 ff               	and	eax, 0xff00ff00
 11b436e: f3 0f 11 05 4c 58 b5 01      	movss	dword ptr [0x1b5584c], xmm0
 11b4376: f3 0f 10 45 14               	movss	xmm0, dword ptr [ebp + 0x14]
 11b437b: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11b4380: 0b d0                        	or	edx, eax
 11b4382: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 11b4385: 8b 38                        	mov	edi, dword ptr [eax]
 11b4387: 6a 00                        	push	0x0
 11b4389: 52                           	push	edx
 11b438a: 8b 55 fc                     	mov	edx, dword ptr [ebp - 0x4]
 11b438d: 52                           	push	edx
 11b438e: 51                           	push	ecx
 11b438f: 89 0d 40 58 b5 01            	mov	dword ptr [0x1b55840], ecx
 11b4395: 8b c8                        	mov	ecx, eax
 11b4397: 8b 87 ac 00 00 00            	mov	eax, dword ptr [edi + 0xac]
 11b439d: 53                           	push	ebx
 11b439e: f3 0f 11 0d 48 58 b5 01      	movss	dword ptr [0x1b55848], xmm1
 11b43a6: 89 1d 44 58 b5 01            	mov	dword ptr [0x1b55844], ebx
 11b43ac: ff d0                        	call	eax
 11b43ae: 5f                           	pop	edi
 11b43af: 5e                           	pop	esi
 11b43b0: 5b                           	pop	ebx
 11b43b1: 8b e5                        	mov	esp, ebp
 11b43b3: 5d                           	pop	ebp
 11b43b4: c2 14 00                     	ret	0x14
 11b43b7: cc                           	int3
 11b43b8: cc                           	int3
 11b43b9: cc                           	int3
 11b43ba: cc                           	int3
 11b43bb: cc                           	int3
 11b43bc: cc                           	int3
 11b43bd: cc                           	int3
 11b43be: cc                           	int3
 11b43bf: cc                           	int3
 11b43c0: 55                           	push	ebp
 11b43c1: 8b ec                        	mov	ebp, esp
 11b43c3: 8b 55 10                     	mov	edx, dword ptr [ebp + 0x10]
 11b43c6: 85 d2                        	test	edx, edx
 11b43c8: 74 45                        	je	0x11b440f <.text+0x22f>
 11b43ca: 8b 45 1c                     	mov	eax, dword ptr [ebp + 0x1c]
 11b43cd: 56                           	push	esi
 11b43ce: f3 0f 10 45 14               	movss	xmm0, dword ptr [ebp + 0x14]
 11b43d3: 57                           	push	edi
 11b43d4: 6a 09                        	push	0x9
 11b43d6: 6a 00                        	push	0x0
 11b43d8: 50                           	push	eax
 11b43d9: 8b 45 18                     	mov	eax, dword ptr [ebp + 0x18]
 11b43dc: 8b f0                        	mov	esi, eax
 11b43de: 0f b6 f8                     	movzx	edi, al
 11b43e1: c1 ee 10                     	shr	esi, 0x10
 11b43e4: 81 e6 ff 00 00 00            	and	esi, 0xff
 11b43ea: c1 e7 10                     	shl	edi, 0x10
 11b43ed: 25 00 ff 00 ff               	and	eax, 0xff00ff00
 11b43f2: 0b f7                        	or	esi, edi
 11b43f4: 0b f0                        	or	esi, eax
 11b43f6: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b43f9: 56                           	push	esi
 11b43fa: 51                           	push	ecx
 11b43fb: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11b4400: 51                           	push	ecx
 11b4401: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11b4404: 51                           	push	ecx
 11b4405: 50                           	push	eax
 11b4406: 8b ca                        	mov	ecx, edx
 11b4408: e8 23 f7 ff ff               	call	0x11b3b30
 11b440d: 5f                           	pop	edi
 11b440e: 5e                           	pop	esi
 11b440f: 5d                           	pop	ebp
 11b4410: c2 18 00                     	ret	0x18
 11b4413: cc                           	int3
 11b4414: cc                           	int3
 11b4415: cc                           	int3
 11b4416: cc                           	int3
 11b4417: cc                           	int3
 11b4418: cc                           	int3
 11b4419: cc                           	int3
 11b441a: cc                           	int3
 11b441b: cc                           	int3
 11b441c: cc                           	int3
 11b441d: cc                           	int3
 11b441e: cc                           	int3
 11b441f: cc                           	int3
 11b4420: 55                           	push	ebp
 11b4421: 8b ec                        	mov	ebp, esp
 11b4423: 53                           	push	ebx
 11b4424: 56                           	push	esi
 11b4425: 8b 75 10                     	mov	esi, dword ptr [ebp + 0x10]
 11b4428: 8b d9                        	mov	ebx, ecx
 11b442a: 85 f6                        	test	esi, esi
 11b442c: 0f 84 9f 00 00 00            	je	0x11b44d1 <.text+0x2f1>
 11b4432: 0f b7 46 1e                  	movzx	eax, word ptr [esi + 0x1e]
 11b4436: 0f b7 56 1c                  	movzx	edx, word ptr [esi + 0x1c]
 11b443a: 0f 57 c0                     	xorps	xmm0, xmm0
 11b443d: f3 0f 2a c0                  	cvtsi2ss	xmm0, eax
 11b4441: f3 0f 59 45 18               	mulss	xmm0, dword ptr [ebp + 0x18]
 11b4446: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11b4449: 57                           	push	edi
 11b444a: 8b 3d 18 a5 55 01            	mov	edi, dword ptr [0x155a518]
 11b4450: f3 0f 2c c8                  	cvttss2si	ecx, xmm0
 11b4454: 03 c8                        	add	ecx, eax
 11b4456: 51                           	push	ecx
 11b4457: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11b445a: 0f 57 c0                     	xorps	xmm0, xmm0
 11b445d: f3 0f 2a c2                  	cvtsi2ss	xmm0, edx
 11b4461: f3 0f 59 45 14               	mulss	xmm0, dword ptr [ebp + 0x14]
 11b4466: f3 0f 2c d0                  	cvttss2si	edx, xmm0
 11b446a: 03 d1                        	add	edx, ecx
 11b446c: 52                           	push	edx
 11b446d: 50                           	push	eax
 11b446e: 51                           	push	ecx
 11b446f: 68 60 58 b5 01               	push	0x1b55860
 11b4474: ff d7                        	call	edi
 11b4476: 0f b7 46 1e                  	movzx	eax, word ptr [esi + 0x1e]
 11b447a: 0f b7 4e 1c                  	movzx	ecx, word ptr [esi + 0x1c]
 11b447e: 50                           	push	eax
 11b447f: 51                           	push	ecx
 11b4480: 6a 00                        	push	0x0
 11b4482: 6a 00                        	push	0x0
 11b4484: 68 50 58 b5 01               	push	0x1b55850
 11b4489: ff d7                        	call	edi
 11b448b: 8b 55 20                     	mov	edx, dword ptr [ebp + 0x20]
 11b448e: 8b 45 1c                     	mov	eax, dword ptr [ebp + 0x1c]
 11b4491: f3 0f 10 45 24               	movss	xmm0, dword ptr [ebp + 0x24]
 11b4496: 52                           	push	edx
 11b4497: 50                           	push	eax
 11b4498: 8b 45 28                     	mov	eax, dword ptr [ebp + 0x28]
 11b449b: 8b c8                        	mov	ecx, eax
 11b449d: c1 e9 10                     	shr	ecx, 0x10
 11b44a0: 0f b6 d0                     	movzx	edx, al
 11b44a3: 81 e1 ff 00 00 00            	and	ecx, 0xff
 11b44a9: 6a 00                        	push	0x0
 11b44ab: c1 e2 10                     	shl	edx, 0x10
 11b44ae: 0b ca                        	or	ecx, edx
 11b44b0: 25 00 ff 00 ff               	and	eax, 0xff00ff00
 11b44b5: 0b c8                        	or	ecx, eax
 11b44b7: 51                           	push	ecx
 11b44b8: 51                           	push	ecx
 11b44b9: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11b44be: 53                           	push	ebx
 11b44bf: 68 50 58 b5 01               	push	0x1b55850
 11b44c4: 68 60 58 b5 01               	push	0x1b55860
 11b44c9: 8b ce                        	mov	ecx, esi
 11b44cb: e8 60 f6 ff ff               	call	0x11b3b30
 11b44d0: 5f                           	pop	edi
 11b44d1: 5e                           	pop	esi
 11b44d2: 5b                           	pop	ebx
 11b44d3: 5d                           	pop	ebp
 11b44d4: c2 24 00                     	ret	0x24
 11b44d7: cc                           	int3
 11b44d8: cc                           	int3
 11b44d9: cc                           	int3
 11b44da: cc                           	int3
 11b44db: cc                           	int3
 11b44dc: cc                           	int3
 11b44dd: cc                           	int3
 11b44de: cc                           	int3
 11b44df: cc                           	int3
 11b44e0: 55                           	push	ebp
 11b44e1: 8b ec                        	mov	ebp, esp
 11b44e3: 8b d1                        	mov	edx, ecx
 11b44e5: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 11b44e8: 85 c9                        	test	ecx, ecx
 11b44ea: 0f 84 b2 00 00 00            	je	0x11b45a2 <.text+0x3c2>
 11b44f0: f3 0f 10 4d 24               	movss	xmm1, dword ptr [ebp + 0x24]
 11b44f5: f3 0f 10 15 b4 61 56 01      	movss	xmm2, dword ptr [0x15661b4]
 11b44fd: 0f 2e ca                     	ucomiss	xmm1, xmm2
 11b4500: 9f                           	lahf
 11b4501: f6 c4 44                     	test	ah, 0x44
 11b4504: 7a 11                        	jp	0x11b4517 <.text+0x337>
 11b4506: 66 8b 41 1c                  	mov	ax, word ptr [ecx + 0x1c]
 11b450a: 66 d1 e8                     	shr	ax
 11b450d: 0f b7 c0                     	movzx	eax, ax
 11b4510: 0f 57 c9                     	xorps	xmm1, xmm1
 11b4513: f3 0f 2a c8                  	cvtsi2ss	xmm1, eax
 11b4517: f3 0f 10 45 28               	movss	xmm0, dword ptr [ebp + 0x28]
 11b451c: 0f 2e c2                     	ucomiss	xmm0, xmm2
 11b451f: 9f                           	lahf
 11b4520: f6 c4 44                     	test	ah, 0x44
 11b4523: 7a 11                        	jp	0x11b4536 <.text+0x356>
 11b4525: 66 8b 41 1e                  	mov	ax, word ptr [ecx + 0x1e]
 11b4529: 66 d1 e8                     	shr	ax
 11b452c: 0f b7 c0                     	movzx	eax, ax
 11b452f: 0f 57 c0                     	xorps	xmm0, xmm0
 11b4532: f3 0f 2a c0                  	cvtsi2ss	xmm0, eax
 11b4536: 8b 45 20                     	mov	eax, dword ptr [ebp + 0x20]
 11b4539: 53                           	push	ebx
 11b453a: 56                           	push	esi
 11b453b: 57                           	push	edi
 11b453c: 8b 31                        	mov	esi, dword ptr [ecx]
 11b453e: 6a 24                        	push	0x24
 11b4540: 6a 00                        	push	0x0
 11b4542: 83 ec 14                     	sub	esp, 0x14
 11b4545: f3 0f 11 44 24 10            	movss	dword ptr [esp + 0x10], xmm0
 11b454b: f3 0f 10 45 18               	movss	xmm0, dword ptr [ebp + 0x18]
 11b4550: f3 0f 11 4c 24 0c            	movss	dword ptr [esp + 0xc], xmm1
 11b4556: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11b455c: f3 0f 10 45 14               	movss	xmm0, dword ptr [ebp + 0x14]
 11b4561: 8b f8                        	mov	edi, eax
 11b4563: 0f b6 d8                     	movzx	ebx, al
 11b4566: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11b456c: f3 0f 10 45 1c               	movss	xmm0, dword ptr [ebp + 0x1c]
 11b4571: c1 ef 10                     	shr	edi, 0x10
 11b4574: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11b4579: 81 e7 ff 00 00 00            	and	edi, 0xff
 11b457f: c1 e3 10                     	shl	ebx, 0x10
 11b4582: 6a 00                        	push	0x0
 11b4584: 25 00 ff 00 ff               	and	eax, 0xff00ff00
 11b4589: 0b fb                        	or	edi, ebx
 11b458b: 0b f8                        	or	edi, eax
 11b458d: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b4590: 57                           	push	edi
 11b4591: 52                           	push	edx
 11b4592: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11b4595: 52                           	push	edx
 11b4596: 8b 96 ac 00 00 00            	mov	edx, dword ptr [esi + 0xac]
 11b459c: 50                           	push	eax
 11b459d: ff d2                        	call	edx
 11b459f: 5f                           	pop	edi
 11b45a0: 5e                           	pop	esi
 11b45a1: 5b                           	pop	ebx
 11b45a2: 5d                           	pop	ebp
 11b45a3: c2 28 00                     	ret	0x28
 11b45a6: cc                           	int3
 11b45a7: cc                           	int3
 11b45a8: cc                           	int3
 11b45a9: cc                           	int3
 11b45aa: cc                           	int3
 11b45ab: cc                           	int3
 11b45ac: cc                           	int3
 11b45ad: cc                           	int3
 11b45ae: cc                           	int3
 11b45af: cc                           	int3
 11b45b0: 55                           	push	ebp
 11b45b1: 8b ec                        	mov	ebp, esp
 11b45b3: 8b d1                        	mov	edx, ecx
 11b45b5: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 11b45b8: 85 c9                        	test	ecx, ecx
 11b45ba: 0f 84 b6 00 00 00            	je	0x11b4676 <.text+0x496>
 11b45c0: f3 0f 10 4d 28               	movss	xmm1, dword ptr [ebp + 0x28]
 11b45c5: f3 0f 10 15 b4 61 56 01      	movss	xmm2, dword ptr [0x15661b4]
 11b45cd: 0f 2e ca                     	ucomiss	xmm1, xmm2
 11b45d0: 9f                           	lahf
 11b45d1: f6 c4 44                     	test	ah, 0x44
 11b45d4: 7a 11                        	jp	0x11b45e7 <.text+0x407>
 11b45d6: 66 8b 41 1c                  	mov	ax, word ptr [ecx + 0x1c]
 11b45da: 66 d1 e8                     	shr	ax
 11b45dd: 0f b7 c0                     	movzx	eax, ax
 11b45e0: 0f 57 c9                     	xorps	xmm1, xmm1
 11b45e3: f3 0f 2a c8                  	cvtsi2ss	xmm1, eax
 11b45e7: f3 0f 10 45 2c               	movss	xmm0, dword ptr [ebp + 0x2c]
 11b45ec: 0f 2e c2                     	ucomiss	xmm0, xmm2
 11b45ef: 9f                           	lahf
 11b45f0: f6 c4 44                     	test	ah, 0x44
 11b45f3: 7a 11                        	jp	0x11b4606 <.text+0x426>
 11b45f5: 66 8b 41 1e                  	mov	ax, word ptr [ecx + 0x1e]
 11b45f9: 66 d1 e8                     	shr	ax
 11b45fc: 0f b7 c0                     	movzx	eax, ax
 11b45ff: 0f 57 c0                     	xorps	xmm0, xmm0
 11b4602: f3 0f 2a c0                  	cvtsi2ss	xmm0, eax
 11b4606: 8b 45 24                     	mov	eax, dword ptr [ebp + 0x24]
 11b4609: 53                           	push	ebx
 11b460a: 56                           	push	esi
 11b460b: 57                           	push	edi
 11b460c: 8b 31                        	mov	esi, dword ptr [ecx]
 11b460e: 6a 24                        	push	0x24
 11b4610: 6a 00                        	push	0x0
 11b4612: 83 ec 14                     	sub	esp, 0x14
 11b4615: f3 0f 11 44 24 10            	movss	dword ptr [esp + 0x10], xmm0
 11b461b: f3 0f 10 45 1c               	movss	xmm0, dword ptr [ebp + 0x1c]
 11b4620: f3 0f 11 4c 24 0c            	movss	dword ptr [esp + 0xc], xmm1
 11b4626: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11b462c: f3 0f 10 45 18               	movss	xmm0, dword ptr [ebp + 0x18]
 11b4631: 8b f8                        	mov	edi, eax
 11b4633: 0f b6 d8                     	movzx	ebx, al
 11b4636: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11b463c: f3 0f 10 45 20               	movss	xmm0, dword ptr [ebp + 0x20]
 11b4641: c1 ef 10                     	shr	edi, 0x10
 11b4644: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11b4649: 81 e7 ff 00 00 00            	and	edi, 0xff
 11b464f: 6a 00                        	push	0x0
 11b4651: c1 e3 10                     	shl	ebx, 0x10
 11b4654: 25 00 ff 00 ff               	and	eax, 0xff00ff00
 11b4659: 0b fb                        	or	edi, ebx
 11b465b: 0b f8                        	or	edi, eax
 11b465d: 8b 45 14                     	mov	eax, dword ptr [ebp + 0x14]
 11b4660: 57                           	push	edi
 11b4661: 50                           	push	eax
 11b4662: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b4665: 52                           	push	edx
 11b4666: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11b4669: 52                           	push	edx
 11b466a: 8b 96 b0 00 00 00            	mov	edx, dword ptr [esi + 0xb0]
 11b4670: 50                           	push	eax
 11b4671: ff d2                        	call	edx
 11b4673: 5f                           	pop	edi
 11b4674: 5e                           	pop	esi
 11b4675: 5b                           	pop	ebx
 11b4676: 5d                           	pop	ebp
 11b4677: c2 2c 00                     	ret	0x2c
 11b467a: cc                           	int3
 11b467b: cc                           	int3
 11b467c: cc                           	int3
 11b467d: cc                           	int3
 11b467e: cc                           	int3
 11b467f: cc                           	int3
 11b4680: 55                           	push	ebp
 11b4681: 8b ec                        	mov	ebp, esp
 11b4683: 6a ff                        	push	-0x1
 11b4685: 68 38 7c 4c 01               	push	0x14c7c38
 11b468a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11b4690: 50                           	push	eax
 11b4691: 51                           	push	ecx
 11b4692: 56                           	push	esi
 11b4693: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11b4698: 33 c5                        	xor	eax, ebp
 11b469a: 50                           	push	eax
 11b469b: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11b469e: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11b46a4: 8b f1                        	mov	esi, ecx
 11b46a6: 89 75 f0                     	mov	dword ptr [ebp - 0x10], esi
 11b46a9: c7 06 0c 9e 85 01            	mov	dword ptr [esi], 0x1859e0c
 11b46af: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11b46b6: ff 15 b0 9e 85 01            	call	dword ptr [0x1859eb0]
 11b46bc: 8b ce                        	mov	ecx, esi
 11b46be: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 11b46c5: e8 86 7d 01 00               	call	0x11cc450 <.text+0x18270>
 11b46ca: f6 45 08 01                  	test	byte ptr [ebp + 0x8], 0x1
 11b46ce: 74 09                        	je	0x11b46d9 <.text+0x4f9>
 11b46d0: 56                           	push	esi
 11b46d1: e8 ea bc ff ff               	call	0x11b03c0
 11b46d6: 83 c4 04                     	add	esp, 0x4
 11b46d9: 8b c6                        	mov	eax, esi
 11b46db: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11b46de: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11b46e5: 59                           	pop	ecx
 11b46e6: 5e                           	pop	esi
 11b46e7: 8b e5                        	mov	esp, ebp
 11b46e9: 5d                           	pop	ebp
 11b46ea: c2 04 00                     	ret	0x4
 11b46ed: cc                           	int3
 11b46ee: cc                           	int3
 11b46ef: cc                           	int3
 11b46f0: b8 01 00 00 00               	mov	eax, 0x1
 11b46f5: 09 41 44                     	or	dword ptr [ecx + 0x44], eax
 11b46f8: c3                           	ret
 11b46f9: cc                           	int3
 11b46fa: cc                           	int3
 11b46fb: cc                           	int3
 11b46fc: cc                           	int3
 11b46fd: cc                           	int3
 11b46fe: cc                           	int3
 11b46ff: cc                           	int3
 11b4700: 83 61 44 fe                  	and	dword ptr [ecx + 0x44], -0x2
 11b4704: b8 01 00 00 00               	mov	eax, 0x1
 11b4709: c3                           	ret
 11b470a: cc                           	int3
 11b470b: cc                           	int3
 11b470c: cc                           	int3
 11b470d: cc                           	int3
 11b470e: cc                           	int3
 11b470f: cc                           	int3
