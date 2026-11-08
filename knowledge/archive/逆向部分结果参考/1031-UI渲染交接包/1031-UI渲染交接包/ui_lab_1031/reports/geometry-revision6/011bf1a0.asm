
<stdin>:	file format elf32-i386

Disassembly of section .text:

011bf1a0 <.text>:
 11bf1a0: 55                           	push	ebp
 11bf1a1: 8b ec                        	mov	ebp, esp
 11bf1a3: 6a ff                        	push	-0x1
 11bf1a5: 68 bc 7d 4c 01               	push	0x14c7dbc
 11bf1aa: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11bf1b0: 50                           	push	eax
 11bf1b1: 51                           	push	ecx
 11bf1b2: 53                           	push	ebx
 11bf1b3: 56                           	push	esi
 11bf1b4: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11bf1b9: 33 c5                        	xor	eax, ebp
 11bf1bb: 50                           	push	eax
 11bf1bc: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11bf1bf: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11bf1c5: 8b f1                        	mov	esi, ecx
 11bf1c7: 89 75 f0                     	mov	dword ptr [ebp - 0x10], esi
 11bf1ca: c7 06 14 a6 85 01            	mov	dword ptr [esi], 0x185a614
 11bf1d0: 56                           	push	esi
 11bf1d1: b9 f4 95 b2 01               	mov	ecx, 0x1b295f4
 11bf1d6: c7 45 fc 03 00 00 00         	mov	dword ptr [ebp - 0x4], 0x3
 11bf1dd: e8 9e 16 ff ff               	call	0x11b0880
 11bf1e2: 33 db                        	xor	ebx, ebx
 11bf1e4: 39 35 6c 71 b5 01            	cmp	dword ptr [0x1b5716c], esi
 11bf1ea: 75 06                        	jne	0x11bf1f2 <.text+0x52>
 11bf1ec: 89 1d 6c 71 b5 01            	mov	dword ptr [0x1b5716c], ebx
 11bf1f2: 8b 06                        	mov	eax, dword ptr [esi]
 11bf1f4: 8b 50 1c                     	mov	edx, dword ptr [eax + 0x1c]
 11bf1f7: 8b ce                        	mov	ecx, esi
 11bf1f9: ff d2                        	call	edx
 11bf1fb: 8b 46 74                     	mov	eax, dword ptr [esi + 0x74]
 11bf1fe: 3b c3                        	cmp	eax, ebx
 11bf200: 74 09                        	je	0x11bf20b <.text+0x6b>
 11bf202: 50                           	push	eax
 11bf203: e8 1f 69 21 00               	call	0x13d5b27 <.text+0x216987>
 11bf208: 83 c4 04                     	add	esp, 0x4
 11bf20b: 8b 86 ac 02 00 00            	mov	eax, dword ptr [esi + 0x2ac]
 11bf211: 89 5e 74                     	mov	dword ptr [esi + 0x74], ebx
 11bf214: 3b c3                        	cmp	eax, ebx
 11bf216: 74 09                        	je	0x11bf221 <.text+0x81>
 11bf218: 50                           	push	eax
 11bf219: e8 09 69 21 00               	call	0x13d5b27 <.text+0x216987>
 11bf21e: 83 c4 04                     	add	esp, 0x4
 11bf221: 89 9e ac 02 00 00            	mov	dword ptr [esi + 0x2ac], ebx
 11bf227: 83 be 98 00 00 00 08         	cmp	dword ptr [esi + 0x98], 0x8
 11bf22e: 72 0f                        	jb	0x11bf23f <.text+0x9f>
 11bf230: 8b 86 84 00 00 00            	mov	eax, dword ptr [esi + 0x84]
 11bf236: 50                           	push	eax
 11bf237: e8 eb 68 21 00               	call	0x13d5b27 <.text+0x216987>
 11bf23c: 83 c4 04                     	add	esp, 0x4
 11bf23f: 33 c0                        	xor	eax, eax
 11bf241: c7 86 98 00 00 00 07 00 00 00	mov	dword ptr [esi + 0x98], 0x7
 11bf24b: 89 9e 94 00 00 00            	mov	dword ptr [esi + 0x94], ebx
 11bf251: 66 89 86 84 00 00 00         	mov	word ptr [esi + 0x84], ax
 11bf258: 8b 86 80 00 00 00            	mov	eax, dword ptr [esi + 0x80]
 11bf25e: 50                           	push	eax
 11bf25f: e8 c3 68 21 00               	call	0x13d5b27 <.text+0x216987>
 11bf264: 83 c4 04                     	add	esp, 0x4
 11bf267: 8d 4e 64                     	lea	ecx, [esi + 0x64]
 11bf26a: 89 9e 80 00 00 00            	mov	dword ptr [esi + 0x80], ebx
 11bf270: e8 3b ad 05 00               	call	0x1219fb0 <.text+0x5ae10>
 11bf275: 8d 4e 48                     	lea	ecx, [esi + 0x48]
 11bf278: 88 5d fc                     	mov	byte ptr [ebp - 0x4], bl
 11bf27b: e8 e0 1d 02 00               	call	0x11e1060 <.text+0x21ec0>
 11bf280: 8b ce                        	mov	ecx, esi
 11bf282: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 11bf289: e8 c2 d1 00 00               	call	0x11cc450 <.text+0xd2b0>
 11bf28e: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11bf291: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11bf298: 59                           	pop	ecx
 11bf299: 5e                           	pop	esi
 11bf29a: 5b                           	pop	ebx
 11bf29b: 8b e5                        	mov	esp, ebp
 11bf29d: 5d                           	pop	ebp
 11bf29e: c3                           	ret
