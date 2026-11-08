
<stdin>:	file format elf32-i386

Disassembly of section .text:

011cc440 <.text>:
 11cc440: 8b c1                        	mov	eax, ecx
 11cc442: c7 00 f4 d5 56 01            	mov	dword ptr [eax], 0x156d5f4
 11cc448: c6 40 04 00                  	mov	byte ptr [eax + 0x4], 0x0
 11cc44c: c3                           	ret
 11cc44d: cc                           	int3
 11cc44e: cc                           	int3
 11cc44f: cc                           	int3
 11cc450: c7 01 f4 d5 56 01            	mov	dword ptr [ecx], 0x156d5f4
 11cc456: c6 41 04 00                  	mov	byte ptr [ecx + 0x4], 0x0
 11cc45a: c3                           	ret
 11cc45b: cc                           	int3
 11cc45c: cc                           	int3
 11cc45d: cc                           	int3
 11cc45e: cc                           	int3
 11cc45f: cc                           	int3
 11cc460: 8a 41 04                     	mov	al, byte ptr [ecx + 0x4]
 11cc463: c3                           	ret
 11cc464: cc                           	int3
 11cc465: cc                           	int3
 11cc466: cc                           	int3
 11cc467: cc                           	int3
 11cc468: cc                           	int3
 11cc469: cc                           	int3
 11cc46a: cc                           	int3
 11cc46b: cc                           	int3
 11cc46c: cc                           	int3
 11cc46d: cc                           	int3
 11cc46e: cc                           	int3
 11cc46f: cc                           	int3
 11cc470: 55                           	push	ebp
 11cc471: 8b ec                        	mov	ebp, esp
 11cc473: 8a 45 08                     	mov	al, byte ptr [ebp + 0x8]
 11cc476: 88 41 04                     	mov	byte ptr [ecx + 0x4], al
 11cc479: 5d                           	pop	ebp
 11cc47a: c2 04 00                     	ret	0x4
 11cc47d: cc                           	int3
 11cc47e: cc                           	int3
 11cc47f: cc                           	int3
 11cc480: 56                           	push	esi
 11cc481: 8b f1                        	mov	esi, ecx
 11cc483: e8 58 0b 76 ff               	call	0x92cfe0
 11cc488: 84 c0                        	test	al, al
 11cc48a: 0f 84 ec 01 00 00            	je	0x11cc67c <.text+0x23c>
 11cc490: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11cc496: 85 c9                        	test	ecx, ecx
 11cc498: 0f 84 de 01 00 00            	je	0x11cc67c <.text+0x23c>
 11cc49e: e8 dd cb 3e ff               	call	0x5b9080
 11cc4a3: 85 c0                        	test	eax, eax
 11cc4a5: 0f 84 d1 01 00 00            	je	0x11cc67c <.text+0x23c>
 11cc4ab: 8b 8e c4 02 00 00            	mov	ecx, dword ptr [esi + 0x2c4]
 11cc4b1: 85 c9                        	test	ecx, ecx
 11cc4b3: 0f 84 c3 01 00 00            	je	0x11cc67c <.text+0x23c>
 11cc4b9: 53                           	push	ebx
 11cc4ba: 57                           	push	edi
 11cc4bb: e8 00 79 fe ff               	call	0x11b3dc0
 11cc4c0: 8b 8e d4 02 00 00            	mov	ecx, dword ptr [esi + 0x2d4]
 11cc4c6: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 11cc4c9: 8b 7e 14                     	mov	edi, dword ptr [esi + 0x14]
 11cc4cc: 6a 00                        	push	0x0
 11cc4ce: 8b d8                        	mov	ebx, eax
 11cc4d0: 8b 86 c0 02 00 00            	mov	eax, dword ptr [esi + 0x2c0]
 11cc4d6: 50                           	push	eax
 11cc4d7: 51                           	push	ecx
 11cc4d8: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11cc4de: 52                           	push	edx
 11cc4df: 57                           	push	edi
 11cc4e0: e8 8b 09 ff ff               	call	0x11bce70
 11cc4e5: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11cc4eb: e8 80 a0 75 ff               	call	0x926570
 11cc4f0: f3 0f 10 05 50 22 56 01      	movss	xmm0, dword ptr [0x1562250]
 11cc4f8: 8b c8                        	mov	ecx, eax
 11cc4fa: 8b 86 c8 02 00 00            	mov	eax, dword ptr [esi + 0x2c8]
 11cc500: 99                           	cdq
 11cc501: 2b c2                        	sub	eax, edx
 11cc503: d1 f8                        	sar	eax
 11cc505: f7 d9                        	neg	ecx
 11cc507: 2b c8                        	sub	ecx, eax
 11cc509: 8b c3                        	mov	eax, ebx
 11cc50b: 99                           	cdq
 11cc50c: 2b c2                        	sub	eax, edx
 11cc50e: 0f b6 96 c0 02 00 00         	movzx	edx, byte ptr [esi + 0x2c0]
 11cc515: 83 ec 08                     	sub	esp, 0x8
 11cc518: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11cc51e: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11cc523: 0f 57 c0                     	xorps	xmm0, xmm0
 11cc526: c1 e2 18                     	shl	edx, 0x18
 11cc529: 81 ca ff ff ff 00            	or	edx, 0xffffff
 11cc52f: 52                           	push	edx
 11cc530: 83 ec 0c                     	sub	esp, 0xc
 11cc533: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11cc539: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11cc541: 8b d8                        	mov	ebx, eax
 11cc543: 8b 86 c4 02 00 00            	mov	eax, dword ptr [esi + 0x2c4]
 11cc549: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11cc54f: 03 f9                        	add	edi, ecx
 11cc551: 8b 4e 18                     	mov	ecx, dword ptr [esi + 0x18]
 11cc554: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11cc559: 50                           	push	eax
 11cc55a: 51                           	push	ecx
 11cc55b: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11cc561: d1 fb                        	sar	ebx
 11cc563: e8 88 33 37 ff               	call	0x53f8f0
 11cc568: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11cc56e: 99                           	cdq
 11cc56f: 2b c2                        	sub	eax, edx
 11cc571: d1 f8                        	sar	eax
 11cc573: 8b d7                        	mov	edx, edi
 11cc575: 2b d0                        	sub	edx, eax
 11cc577: 2b d3                        	sub	edx, ebx
 11cc579: 52                           	push	edx
 11cc57a: e8 01 cb 3e ff               	call	0x5b9080
 11cc57f: 8b                           	<unknown>
