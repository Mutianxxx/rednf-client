
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c48e0 <.text>:
 11c48e0: 55                           	push	ebp
 11c48e1: 8b ec                        	mov	ebp, esp
 11c48e3: 6a ff                        	push	-0x1
 11c48e5: 68 70 f7 4a 01               	push	0x14af770
 11c48ea: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11c48f0: 50                           	push	eax
 11c48f1: 83 ec 14                     	sub	esp, 0x14
 11c48f4: 53                           	push	ebx
 11c48f5: 56                           	push	esi
 11c48f6: 57                           	push	edi
 11c48f7: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11c48fc: 33 c5                        	xor	eax, ebp
 11c48fe: 50                           	push	eax
 11c48ff: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11c4902: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11c4908: 8b f9                        	mov	edi, ecx
 11c490a: 68 8c 8c 8c ff               	push	0xff8c8c8c
 11c490f: 68 ff ff b8 ff               	push	0xffb8ffff
 11c4914: 68 ff ff b8 ff               	push	0xffb8ffff
 11c4919: 68 dd c5 93 ff               	push	0xff93c5dd
 11c491e: 83 ec 20                     	sub	esp, 0x20
 11c4921: 8b f4                        	mov	esi, esp
 11c4923: 33 db                        	xor	ebx, ebx
 11c4925: 89 65 f0                     	mov	dword ptr [ebp - 0x10], esp
 11c4928: 6a 08                        	push	0x8
 11c492a: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 11c492d: 89 75 ec                     	mov	dword ptr [ebp - 0x14], esi
 11c4930: 89 1e                        	mov	dword ptr [esi], ebx
 11c4932: e8 e3 21 21 00               	call	0x13d6b1a <.text+0x21223a>
 11c4937: 83 c4 04                     	add	esp, 0x4
 11c493a: 3b c3                        	cmp	eax, ebx
 11c493c: 0f 84 80 00 00 00            	je	0x11c49c2 <.text+0xe2>
 11c4942: 89 06                        	mov	dword ptr [esi], eax
 11c4944: 33 c9                        	xor	ecx, ecx
 11c4946: 33 d2                        	xor	edx, edx
 11c4948: 89 08                        	mov	dword ptr [eax], ecx
 11c494a: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c494d: 8b 06                        	mov	eax, dword ptr [esi]
 11c494f: 89 30                        	mov	dword ptr [eax], esi
 11c4951: 6a ff                        	push	-0x1
 11c4953: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c495a: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c495d: 53                           	push	ebx
 11c495e: 8d 55 08                     	lea	edx, [ebp + 0x8]
 11c4961: 66 89 4e 04                  	mov	word ptr [esi + 0x4], cx
 11c4965: 52                           	push	edx
 11c4966: 8b ce                        	mov	ecx, esi
 11c4968: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 11c496c: e8 bf 09 24 ff               	call	0x405330
 11c4971: 8b 07                        	mov	eax, dword ptr [edi]
 11c4973: 8b 90 b4 00 00 00            	mov	edx, dword ptr [eax + 0xb4]
 11c4979: 8b cf                        	mov	ecx, edi
 11c497b: 88 5d fc                     	mov	byte ptr [ebp - 0x4], bl
 11c497e: ff d2                        	call	edx
 11c4980: 83 7d 20 08                  	cmp	dword ptr [ebp + 0x20], 0x8
 11c4984: 72 0c                        	jb	0x11c4992 <.text+0xb2>
 11c4986: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11c4989: 50                           	push	eax
 11c498a: e8 98 11 21 00               	call	0x13d5b27 <.text+0x211247>
 11c498f: 83 c4 04                     	add	esp, 0x4
 11c4992: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11c4995: 33 c9                        	xor	ecx, ecx
 11c4997: 52                           	push	edx
 11c4998: c7 45 20 07 00 00 00         	mov	dword ptr [ebp + 0x20], 0x7
 11c499f: 89 5d 1c                     	mov	dword ptr [ebp + 0x1c], ebx
 11c49a2: 66 89 4d 0c                  	mov	word ptr [ebp + 0xc], cx
 11c49a6: e8 7c 11 21 00               	call	0x13d5b27 <.text+0x211247>
 11c49ab: 83 c4 04                     	add	esp, 0x4
 11c49ae: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11c49b1: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11c49b8: 59                           	pop	ecx
 11c49b9: 5f                           	pop	edi
 11c49ba: 5e                           	pop	esi
 11c49bb: 5b                           	pop	ebx
 11c49bc: 8b e5                        	mov	esp, ebp
 11c49be: 5d                           	pop	ebp
 11c49bf: c2 20 00                     	ret	0x20
 11c49c2: 8d 45 f0                     	lea	eax, [ebp - 0x10]
 11c49c5: 50                           	push	eax
 11c49c6: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
 11c49c9: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
 11c49cc: e8 f9 1a 21 00               	call	0x13d64ca <.text+0x211bea>
 11c49d1: 68 90 0f 91 01               	push	0x1910f90
 11c49d6: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
 11c49d9: 51                           	push	ecx
 11c49da: c7 45 e0 84 20 56 01         	mov	dword ptr [ebp - 0x20], 0x1562084
 11c49e1: e8 b4 21 21 00               	call	0x13d6b9a <.text+0x2122ba>
 11c49e6: cc                           	int3
 11c49e7: cc                           	int3
 11c49e8: cc                           	int3
 11c49e9: cc                           	int3
 11c49ea: cc                           	int3
 11c49eb: cc                           	int3
 11c49ec: cc                           	int3
 11c49ed: cc                           	int3
 11c49ee: cc                           	int3
 11c49ef: cc                           	int3
