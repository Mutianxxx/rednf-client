
<stdin>:	file format elf32-i386

Disassembly of section .text:

004bb940 <.text>:
  4bb940: 55                           	push	ebp
  4bb941: 8b ec                        	mov	ebp, esp
  4bb943: 8a 45 08                     	mov	al, byte ptr [ebp + 0x8]
  4bb946: 88 81 10 0a 00 00            	mov	byte ptr [ecx + 0xa10], al
  4bb94c: 5d                           	pop	ebp
  4bb94d: c2 04 00                     	ret	0x4
  4bb950: 55                           	push	ebp
  4bb951: 8b ec                        	mov	ebp, esp
  4bb953: 6a ff                        	push	-0x1
  4bb955: 68 08 16 41 01               	push	0x1411608
  4bb95a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  4bb960: 50                           	push	eax
  4bb961: 83 ec 1c                     	sub	esp, 0x1c
  4bb964: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  4bb969: 33 c5                        	xor	eax, ebp
  4bb96b: 50                           	push	eax
  4bb96c: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  4bb96f: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  4bb975: 8d 4d d8                     	lea	ecx, [ebp - 0x28]
  4bb978: e8 b3 db d0 00               	call	0x11c9530 <.text+0xd0dbf0>
  4bb97d: 8b 0d 64 65 b5 01            	mov	ecx, dword ptr [0x1b56564]
  4bb983: 33 c0                        	xor	eax, eax
  4bb985: 89 4d e0                     	mov	dword ptr [ebp - 0x20], ecx
  4bb988: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
  4bb98e: 88 45 de                     	mov	byte ptr [ebp - 0x22], al
  4bb991: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
  4bb994: c6 45 d9 01                  	mov	byte ptr [ebp - 0x27], 0x1
  4bb998: 8b 11                        	mov	edx, dword ptr [ecx]
  4bb99a: 8b 52 4c                     	mov	edx, dword ptr [edx + 0x4c]
  4bb99d: 8d 45 d8                     	lea	eax, [ebp - 0x28]
  4bb9a0: 50                           	push	eax
  4bb9a1: ff d2                        	call	edx
  4bb9a3: 8b 55 10                     	mov	edx, dword ptr [ebp + 0x10]
  4bb9a6: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
  4bb9ac: 8b 01                        	mov	eax, dword ptr [ecx]
  4bb9ae: 8b 40 5c                     	mov	eax, dword ptr [eax + 0x5c]
  4bb9b1: 52                           	push	edx
  4bb9b2: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
  4bb9b5: 68 dd c5 93 ff               	push	0xff93c5dd
  4bb9ba: 52                           	push	edx
  4bb9bb: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
  4bb9be: 52                           	push	edx
  4bb9bf: ff d0                        	call	eax
  4bb9c1: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
  4bb9c7: 8b 11                        	mov	edx, dword ptr [ecx]
  4bb9c9: 8b 42 50                     	mov	eax, dword ptr [edx + 0x50]
  4bb9cc: ff d0                        	call	eax
  4bb9ce: 8d 4d d8                     	lea	ecx, [ebp - 0x28]
  4bb9d1: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
  4bb9d8: e8 53 ea c9 00               	call	0x115a430 <.text+0xc9eaf0>
  4bb9dd: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  4bb9e0: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  4bb9e7: 59                           	pop	ecx
  4bb9e8: 8b e5                        	mov	esp, ebp
  4bb9ea: 5d                           	pop	ebp
  4bb9eb: c2 0c 00                     	ret	0xc
  4bb9ee: cc                           	int3
  4bb9ef: cc                           	int3
  4bb9f0: 55                           	push	ebp
  4bb9f1: 8b ec                        	mov	ebp, esp
  4bb9f3: 56                           	push	esi
  4bb9f4: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
  4bb9f7: 8b 06                        	mov	eax, dword ptr [esi]
  4bb9f9: 8b 90 a4 02 00 00            	mov	edx, dword ptr [eax + 0x2a4]
  4bb9ff: 57                           	push	edi
  4bba00: 8b f9                        	mov	edi, ecx
  4bba02: 8b ce                        	mov	ecx, esi
  4bba04: ff d2                        	call	edx
  4bba06: 0f 57 c0                     	xorps	xmm0, xmm0
  4bba09: f3 0f 2a c0                  	cvtsi2ss	xmm0, eax
  4bba0d: 8b 06                        	mov	eax, dword ptr [esi]
  4bba0f: 8b 90 a8 02 00 00            	mov	edx, dword ptr [eax + 0x2a8]
  4bba15: 8b ce                        	mov	ecx, esi
  4bba17: f3 0f 11 45 08               	movss	dword ptr [ebp + 0x8], xmm0
  4bba1c: ff d2                        	call	edx
  4bba1e: f3 0f 10 4d 08               	movss	xmm1, dword ptr [ebp + 0x8]
  4bba23: 0f 57 c0                     	xorps	xmm0, xmm0
  4bba26: f3 0f 2a c0                  	cvtsi2ss	xmm0, eax
  4bba2a: f3 0f 5e c8                  	divss	xmm1, xmm0
  4bba2e: f3 0f 59 0d 38 2e 56 01      	mulss	xmm1, dword ptr [0x1562e38]
  4bba36: f3 0f 10 05 c4 c6 56 01      	movss	xmm0, dword ptr [0x156c6c4]
  4bba3e: 0f 2f c1                     	comiss	xmm0, xmm1
  4bba41: 0f 86 c2 00 00 00            	jbe	0x4bbb09 <.text+0x1c9>
  4bba47: e8 c4 a9 24 00               	call	0x706410 <.text+0x24aad0>
  4bba4c: 8b c8                        	mov	ecx, eax
  4bba4e: e8 2d ee 29 00               	call	0x75a880 <.text+0x29ef40>
  4bba53: 84 c0                        	test	al, al
  4bba55: 0f 84 ae 00 00 00            	je	0x4bbb09 <.text+0x1c9>
  4bba5b: e8 f0 11 4b 00               	call	0x96cc50 <.text+0x4b1310>
