
<stdin>:	file format elf32-i386

Disassembly of section .text:

01117400 <.text>:
 1117400: 9e                           	sahf
 1117401: ec                           	in	al, dx
 1117402: 00 00                        	add	byte ptr [eax], al
 1117404: 00 3b                        	add	byte ptr [ebx], bh
 1117406: fb                           	sti
 1117407: 74 10                        	je	0x1117419 <.text+0x19>
 1117409: 8b cf                        	mov	ecx, edi
 111740b: e8 20 19 f8 ff               	call	0x1098d30
 1117410: 57                           	push	edi
 1117411: e8 aa 8f 09 00               	call	0x11b03c0 <.text+0x98fc0>
 1117416: 83 c4 04                     	add	esp, 0x4
 1117419: 89 9e e8 00 00 00            	mov	dword ptr [esi + 0xe8], ebx
 111741f: 8d be 1c 01 00 00            	lea	edi, [esi + 0x11c]
 1117425: c7 45 fc 02 00 00 00         	mov	dword ptr [ebp - 0x4], 0x2
 111742c: 8d 64 24 00                  	lea	esp, [esp]
 1117430: 8b 0f                        	mov	ecx, dword ptr [edi]
 1117432: 3b cb                        	cmp	ecx, ebx
 1117434: 74 08                        	je	0x111743e <.text+0x3e>
 1117436: 8b 01                        	mov	eax, dword ptr [ecx]
 1117438: 8b 10                        	mov	edx, dword ptr [eax]
 111743a: 6a 01                        	push	0x1
 111743c: ff d2                        	call	edx
 111743e: 89 1f                        	mov	dword ptr [edi], ebx
 1117440: 83 c7 04                     	add	edi, 0x4
 1117443: ff 4d fc                     	dec	dword ptr [ebp - 0x4]
 1117446: 75 e8                        	jne	0x1117430 <.text+0x30>
 1117448: 81 c6 80 02 00 00            	add	esi, 0x280
 111744e: c7 45 fc 07 00 00 00         	mov	dword ptr [ebp - 0x4], 0x7
 1117455: 8b 3e                        	mov	edi, dword ptr [esi]
 1117457: 3b fb                        	cmp	edi, ebx
 1117459: 74 10                        	je	0x111746b <.text+0x6b>
 111745b: 8b cf                        	mov	ecx, edi
 111745d: e8 ce 18 f8 ff               	call	0x1098d30
 1117462: 57                           	push	edi
 1117463: e8 58 8f 09 00               	call	0x11b03c0 <.text+0x98fc0>
 1117468: 83 c4 04                     	add	esp, 0x4
 111746b: 89 1e                        	mov	dword ptr [esi], ebx
 111746d: 83 c6 04                     	add	esi, 0x4
 1117470: ff 4d fc                     	dec	dword ptr [ebp - 0x4]
 1117473: 75 e0                        	jne	0x1117455 <.text+0x55>
 1117475: 5f                           	pop	edi
 1117476: 5e                           	pop	esi
 1117477: 5b                           	pop	ebx
 1117478: 8b e5                        	mov	esp, ebp
 111747a: 5d                           	pop	ebp
 111747b: c3                           	ret
 111747c: cc                           	int3
 111747d: cc                           	int3
 111747e: cc                           	int3
 111747f: cc                           	int3
 1117480: 56                           	push	esi
 1117481: 33 f6                        	xor	esi, esi
 1117483: 8b 0d 28 f7 a6 01            	mov	ecx, dword ptr [0x1a6f728]
 1117489: 56                           	push	esi
 111748a: e8 71 f0 80 ff               	call	0x926500
 111748f: 85 c0                        	test	eax, eax
 1117491: 74 42                        	je	0x11174d5 <.text+0xd5>
 1117493: 8b 0d 28 f7 a6 01            	mov	ecx, dword ptr [0x1a6f728]
 1117499: 56                           	push	esi
 111749a: e8 61 f0 80 ff               	call	0x926500
 111749f: f3 0f 10 80 c8 03 00 00      	movss	xmm0, dword ptr [eax + 0x3c8]
 11174a7: 0f 2e 05 2c bf 5a 01         	ucomiss	xmm0, dword ptr [0x15abf2c]
 11174ae: 9f                           	lahf
 11174af: f6 c4 44                     	test	ah, 0x44
 11174b2: 7b 21                        	jnp	0x11174d5 <.text+0xd5>
 11174b4: 8b 0d 28 f7 a6 01            	mov	ecx, dword ptr [0x1a6f728]
 11174ba: 56                           	push	esi
 11174bb: e8 40 f0 80 ff               	call	0x926500
 11174c0: f3 0f 10 80 c8 03 00 00      	movss	xmm0, dword ptr [eax + 0x3c8]
 11174c8: 0f 2e 05 88 be 5a 01         	ucomiss	xmm0, dword ptr [0x15abe88]
 11174cf: 9f                           	lahf
 11174d0: f6 c4 44                     	test	ah, 0x44
 11174d3: 7a 0a                        	jp	0x11174df <.text+0xdf>
 11174d5: 46                           	inc	esi
 11174d6: 83 fe 04                     	cmp	esi, 0x4
 11174d9: 7c a8                        	jl	0x1117483 <.text+0x83>
 11174db: b0 01                        	mov	al, 0x1
 11174dd: 5e                           	pop	esi
 11174de: c3                           	ret
 11174df: 32 c0                        	xor	al, al
 11174e1: 5e                           	pop	esi
 11174e2: c3                           	ret
 11174e3: cc                           	int3
 11174e4: cc                           	int3
 11174e5: cc                           	int3
 11174e6: cc                           	int3
 11174e7: cc                           	int3
 11174e8: cc                           	int3
 11174e9: cc                           	int3
 11174ea: cc                           	int3
 11174eb: cc                           	int3
 11174ec: cc                           	int3
 11174ed: cc                           	int3
 11174ee: cc                           	int3
 11174ef: cc                           	int3
 11174f0: 55                           	push	ebp
 11174f1: 8b ec                        	mov	ebp, esp
 11174f3: 8a 45 08                     	mov	al, byte ptr [ebp + 0x8]
 11174f6: 56                           	push	esi
 11174f7: 8b f1                        	mov	esi, ecx
 11174f9: 84 c0                        	test	al, al
 11174fb: 74 02                        	je	0x11174ff <.text+0xff>
 11174fd: 32 c0                        	xor	al, al
 11174ff: 88 86 48 03 00 00            	mov	byte ptr [esi + 0x348], al
 1117505: 88 86 49 03 00 00            	mov	byte ptr [esi + 0x349], al
 111750b: 84 c0                        	test	al, al
 111750d: 74 34                        	je	0x1117543 <.text+0x143>
 111750f: a1 50 f7 a6 01               	mov	eax, dword ptr [0x1a6f750]
 1117514: 8b 88 30 43 00 00            	mov	ecx, dword ptr [eax + 0x4330]
 111751a: 6a 00                        	push	0x0
 111751c: e8 0f 13 ef ff               	call	0x1008830
 1117521: 6a 00                        	push	0x0
 1117523: 6a 00                        	push	0x0
 1117525: 68 50 7f 83 01               	push	0x1837f50
 111752a: e8 c1 89 08 00               	call	0x119fef0 <.text+0x88af0>
 111752f: 8b 8e ac 03 00 00            	mov	ecx, dword ptr [esi + 0x3ac]
 1117535: 83 c4 04                     	add	esp, 0x4
 1117538: 50                           	push	eax
 1117539: e8 82 09 f5 ff               	call	0x1067ec0
 111753e: 5e                           	pop	esi
 111753f: 5d                           	pop	ebp
 1117540: c2 04 00                     	ret	0x4
 1117543: 8b 0d 50 f7 a6 01            	mov	ecx, dword ptr [0x1a6f750]
 1117549: 8b 89 30 43 00 00            	mov	ecx, dword ptr [ecx + 0x4330]
 111754f: 68 ff 00 00 00               	push	0xff
 1117554: e8 d7 12 ef ff               	call	0x1008830
 1117559: 8b 8e ac 03 00 00            	mov	ecx, dword ptr [esi + 0x3ac]
 111755f: e8 0c d4 f4 ff               	call	0x1064970
 1117564: 5e                           	pop	esi
 1117565: 5d                           	pop	ebp
 1117566: c2 04 00                     	ret	0x4
 1117569: cc                           	int3
 111756a: cc                           	int3
 111756b: cc                           	int3
 111756c: cc                           	int3
 111756d: cc                           	int3
 111756e: cc                           	int3
 111756f: cc                           	int3
 1117570: 8b 0d 18 f7 a6 01            	mov	ecx, dword ptr [0x1a6f718]
 1117576: 56                           	push	esi
 1117577: e8 84 da 80 ff               	call	0x925000
 111757c: 8b 0d 28 f7 a6 01            	mov	ecx, dword ptr [0x1a6f728]
 1117582: 8b f0                        	mov	esi, eax
 1117584: e8 37 ef 80 ff               	call	0x9264c0
 1117589: 3b c6                        	cmp	eax, esi
 111758b: 0f 94 c0                     	sete	al
 111758e: 5e                           	pop	esi
 111758f: c3                           	ret
 1117590: 56                           	push	esi
 1117591: 8b f1                        	mov	esi, ecx
 1117593: e8 78 ee 5e ff               	call	0x706410
 1117598: 8b c8                        	mov	ecx, eax
 111759a: e8 d1 4e 64 ff               	call	0x75c470
 111759f: 83 f8 02                     	cmp	eax, 0x2
 11175a2: 75 20                        	jne	0x11175c4 <.text+0x1c4>
 11175a4: 8b 86 a0 02 00 00            	mov	eax, dword ptr [esi + 0x2a0]
 11175aa: 83 c0 fd                     	add	eax, -0x3
 11175ad: 83 f8 0d                     	cmp	eax, 0xd
 11175b0: 77 12                        	ja	0x11175c4 <.text+0x1c4>
 11175b2: 0f b6 80 d0 75 11 01         	movzx	eax, byte ptr [eax + 0x11175d0]
 11175b9: ff 24 85 c8 75 11 01         	jmp	dword ptr [4*eax + 0x11175c8]
 11175c0: b0 01                        	mov	al, 0x1
 11175c2: 5e                           	pop	esi
 11175c3: c3                           	ret
 11175c4: 32 c0                        	xor	al, al
 11175c6: 5e                           	pop	esi
 11175c7: c3                           	ret
 11175c8: c0 75 11                     	<unknown>
 11175cb: 01 c4                        	add	esp, eax
 11175cd: 75 11                        	jne	0x11175e0 <.text+0x1e0>
 11175cf: 01 00                        	add	dword ptr [eax], eax
 11175d1: 01 01                        	add	dword ptr [ecx], eax
 11175d3: 01 01                        	add	dword ptr [ecx], eax
 11175d5: 01 01                        	add	dword ptr [ecx], eax
 11175d7: 01 00                        	add	dword ptr [eax], eax
 11175d9: 00 01                        	add	byte ptr [ecx], al
 11175db: 00 01                        	add	byte ptr [ecx], al
 11175dd: 00 cc                        	add	ah, cl
 11175df: cc                           	int3
 11175e0: 56                           	push	esi
 11175e1: 8b f1                        	mov	esi, ecx
 11175e3: e8 28 ee 5e ff               	call	0x706410
 11175e8: 8b 8e a0 02 00 00            	mov	ecx, dword ptr [esi + 0x2a0]
 11175ee: 51                           	push	ecx
 11175ef: 8b c8                        	mov	ecx, eax
 11175f1: e8 1a 2f 64 ff               	call	0x75a510
 11175f6: 5e                           	pop	esi
 11175f7: c3                           	ret
 11175f8: cc                           	int3
 11175f9: cc                           	int3
 11175fa: cc                           	int3
 11175fb: cc                           	int3
 11175fc: cc                           	int3
 11175fd: cc                           	int3
 11175fe: cc                           	int3
 11175ff: cc                           	int3
 1117600: 56                           	push	esi
 1117601: 8b f1                        	mov	esi, ecx
 1117603: e8 08 ee 5e ff               	call	0x706410
 1117608: 8b 8e a0 02 00 00            	mov	ecx, dword ptr [esi + 0x2a0]
 111760e: 51                           	push	ecx
 111760f: 8b c8                        	mov	ecx, eax
 1117611: e8 fa 2e 64 ff               	call	0x75a510
 1117616: 5e                           	pop	esi
 1117617: 85 c0                        	test	eax, eax
 1117619: 74 09                        	je	0x1117624 <.text+0x224>
 111761b: 8b 10                        	mov	edx, dword ptr [eax]
 111761d: 8b c8                        	mov	ecx, eax
 111761f: 8b 42 3c                     	mov	eax, dword ptr [edx + 0x3c]
 1117622: ff e0                        	jmp	eax
 1117624: 33 c0                        	xor	eax, eax
 1117626: c3                           	ret
 1117627: cc                           	int3
 1117628: cc                           	int3
 1117629: cc                           	int3
 111762a: cc                           	int3
 111762b: cc                           	int3
 111762c: cc                           	int3
 111762d: cc                           	int3
 111762e: cc                           	int3
 111762f: cc                           	int3
 1117630: 56                           	push	esi
 1117631: 57                           	push	edi
 1117632: e8 89 07 0b 00               	call	0x11c7dc0 <.text+0xb09c0>
 1117637: 8b f0                        	mov	esi, eax
 1117639: e8 92 07 0b 00               	call	0x11c7dd0 <.text+0xb09d0>
 111763e: 8b d0                        	mov	edx, eax
