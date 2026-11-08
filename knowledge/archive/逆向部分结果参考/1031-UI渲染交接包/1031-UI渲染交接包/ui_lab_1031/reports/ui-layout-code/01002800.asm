
<stdin>:	file format elf32-i386

Disassembly of section .text:

01002800 <.text>:
 1002800: 33 c0                        	xor	eax, eax
 1002802: c7 06 b4 ae 82 01            	mov	dword ptr [esi], 0x182aeb4
 1002808: c7 86 78 01 00 00 a8 ae 82 01	mov	dword ptr [esi + 0x178], 0x182aea8
 1002812: 8d 8e 94 02 00 00            	lea	ecx, [esi + 0x294]
 1002818: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 100281b: 89 86 60 02 00 00            	mov	dword ptr [esi + 0x260], eax
 1002821: 89 86 64 02 00 00            	mov	dword ptr [esi + 0x264], eax
 1002827: 89 86 68 02 00 00            	mov	dword ptr [esi + 0x268], eax
 100282d: 89 86 6c 02 00 00            	mov	dword ptr [esi + 0x26c], eax
 1002833: 89 86 70 02 00 00            	mov	dword ptr [esi + 0x270], eax
 1002839: 89 86 74 02 00 00            	mov	dword ptr [esi + 0x274], eax
 100283f: e8 ec 6c 1c 00               	call	0x11c9530 <.text+0x1c6d30>
 1002844: 8d 8e b0 02 00 00            	lea	ecx, [esi + 0x2b0]
 100284a: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 100284e: e8 dd 6c 1c 00               	call	0x11c9530 <.text+0x1c6d30>
 1002853: 68 70 1f 00 01               	push	0x1001f70
 1002858: 68 90 1e 00 01               	push	0x1001e90
 100285d: 6a 1f                        	push	0x1f
 100285f: 6a 50                        	push	0x50
 1002861: 8d 8e dc 04 00 00            	lea	ecx, [esi + 0x4dc]
 1002867: 51                           	push	ecx
 1002868: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
 100286c: e8 5a 57 3d 00               	call	0x13d7fcb <.text+0x3d57cb>
 1002871: 8b ce                        	mov	ecx, esi
 1002873: c6 45 fc 03                  	mov	byte ptr [ebp - 0x4], 0x3
 1002877: e8 64 ee ff ff               	call	0x10016e0
 100287c: 8b ce                        	mov	ecx, esi
 100287e: e8 ad f7 ff ff               	call	0x1002030
 1002883: 8b c6                        	mov	eax, esi
 1002885: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 1002888: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 100288f: 59                           	pop	ecx
 1002890: 5e                           	pop	esi
 1002891: 8b e5                        	mov	esp, ebp
 1002893: 5d                           	pop	ebp
 1002894: c2 04 00                     	ret	0x4
 1002897: cc                           	int3
 1002898: cc                           	int3
 1002899: cc                           	int3
 100289a: cc                           	int3
 100289b: cc                           	int3
 100289c: cc                           	int3
 100289d: cc                           	int3
 100289e: cc                           	int3
 100289f: cc                           	int3
 10028a0: 55                           	push	ebp
 10028a1: 8b ec                        	mov	ebp, esp
 10028a3: 6a ff                        	push	-0x1
 10028a5: 68 5c 2c 4b 01               	push	0x14b2c5c
 10028aa: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 10028b0: 50                           	push	eax
 10028b1: 51                           	push	ecx
 10028b2: 56                           	push	esi
 10028b3: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 10028b8: 33 c5                        	xor	eax, ebp
 10028ba: 50                           	push	eax
 10028bb: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 10028be: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 10028c4: 8b f1                        	mov	esi, ecx
 10028c6: 89 75 f0                     	mov	dword ptr [ebp - 0x10], esi
 10028c9: c7 06 b4 ae 82 01            	mov	dword ptr [esi], 0x182aeb4
 10028cf: c7 86 78 01 00 00 a8 ae 82 01	mov	dword ptr [esi + 0x178], 0x182aea8
 10028d9: c7 45 fc 03 00 00 00         	mov	dword ptr [ebp - 0x4], 0x3
 10028e0: e8 9b ec ff ff               	call	0x1001580
 10028e5: 68 70 1f 00 01               	push	0x1001f70
 10028ea: 6a 1f                        	push	0x1f
 10028ec: 6a 50                        	push	0x50
 10028ee: 8d 86 dc 04 00 00            	lea	eax, [esi + 0x4dc]
 10028f4: 50                           	push	eax
 10028f5: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
 10028f9: e8 46 53 3d 00               	call	0x13d7c44 <.text+0x3d5444>
 10028fe: 8d 8e b0 02 00 00            	lea	ecx, [esi + 0x2b0]
 1002904: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 1002908: e8 23 7b 15 00               	call	0x115a430 <.text+0x157c30>
 100290d: 8d 8e 94 02 00 00            	lea	ecx, [esi + 0x294]
 1002913: c6 45 fc 00                  	mov	byte ptr [ebp - 0x4], 0x0
 1002917: e8 14 7b 15 00               	call	0x115a430 <.text+0x157c30>
 100291c: 8b ce                        	mov	ecx, esi
 100291e: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 1002925: e8 96 69 06 00               	call	0x10692c0 <.text+0x66ac0>
 100292a: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 100292d: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 1002934: 59                           	pop	ecx
 1002935: 5e                           	pop	esi
 1002936: 8b e5                        	mov	esp, ebp
 1002938: 5d                           	pop	ebp
 1002939: c3                           	ret
 100293a: cc                           	int3
 100293b: cc                           	int3
 100293c: cc                           	int3
 100293d: cc                           	int3
 100293e: cc                           	int3
 100293f: cc                           	int3
 1002940: 55                           	push	ebp
 1002941: 8b ec                        	mov	ebp, esp
 1002943: 56                           	push	esi
 1002944: 8b f1                        	mov	esi, ecx
 1002946: e8 55 ff ff ff               	call	0x10028a0 <.text+0xa0>
 100294b: f6 45 08 01                  	test	byte ptr [ebp + 0x8], 0x1
 100294f: 74 09                        	je	0x100295a <.text+0x15a>
 1002951: 56                           	push	esi
 1002952: e8 69 da 1a 00               	call	0x11b03c0 <.text+0x1adbc0>
 1002957: 83 c4 04                     	add	esp, 0x4
 100295a: 8b c6                        	mov	eax, esi
 100295c: 5e                           	pop	esi
 100295d: 5d                           	pop	ebp
 100295e: c2 04 00                     	ret	0x4
 1002961: cc                           	int3
 1002962: cc                           	int3
 1002963: cc                           	int3
 1002964: cc                           	int3
 1002965: cc                           	int3
 1002966: cc                           	int3
 1002967: cc                           	int3
 1002968: cc                           	int3
 1002969: cc                           	int3
 100296a: cc                           	int3
 100296b: cc                           	int3
 100296c: cc                           	int3
 100296d: cc                           	int3
 100296e: cc                           	int3
 100296f: cc                           	int3
 1002970: 56                           	push	esi
 1002971: 8b f1                        	mov	esi, ecx
 1002973: 8b 86 8c 02 00 00            	mov	eax, dword ptr [esi + 0x28c]
 1002979: 8b 8e 88 02 00 00            	mov	ecx, dword ptr [esi + 0x288]
 100297f: 50                           	push	eax
 1002980: 51                           	push	ecx
 1002981: 8b 0d d0 8c ac 01            	mov	ecx, dword ptr [0x1ac8cd0]
 1002987: e8 44 03 94 ff               	call	0x942cd0
 100298c: 8b 96 8c 02 00 00            	mov	edx, dword ptr [esi + 0x28c]
 1002992: 8b 86 88 02 00 00            	mov	eax, dword ptr [esi + 0x288]
 1002998: 52                           	push	edx
 1002999: 50                           	push	eax
 100299a: 8b ce                        	mov	ecx, esi
 100299c: e8 3f fb ff ff               	call	0x10024e0
 10029a1: 5e                           	pop	esi
 10029a2: c3                           	ret
 10029a3: cc                           	int3
 10029a4: cc                           	int3
 10029a5: cc                           	int3
 10029a6: cc                           	int3
 10029a7: cc                           	int3
 10029a8: cc                           	int3
 10029a9: cc                           	int3
 10029aa: cc                           	int3
 10029ab: cc                           	int3
 10029ac: cc                           	int3
 10029ad: cc                           	int3
 10029ae: cc                           	int3
 10029af: cc                           	int3
 10029b0: 8b 81 8c 02 00 00            	mov	eax, dword ptr [ecx + 0x28c]
 10029b6: 8b 91 88 02 00 00            	mov	edx, dword ptr [ecx + 0x288]
 10029bc: 50                           	push	eax
 10029bd: 52                           	push	edx
 10029be: e8 1d fb ff ff               	call	0x10024e0
 10029c3: c3                           	ret
 10029c4: cc                           	int3
 10029c5: cc                           	int3
 10029c6: cc                           	int3
 10029c7: cc                           	int3
 10029c8: cc                           	int3
 10029c9: cc                           	int3
 10029ca: cc                           	int3
 10029cb: cc                           	int3
 10029cc: cc                           	int3
 10029cd: cc                           	int3
 10029ce: cc                           	int3
 10029cf: cc                           	int3
 10029d0: 55                           	push	ebp
 10029d1: 8b ec                        	mov	ebp, esp
 10029d3: 53                           	push	ebx
 10029d4: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 10029d7: 56                           	push	esi
 10029d8: 57                           	push	edi
 10029d9: 8b f1                        	mov	esi, ecx
 10029db: 83 fb ff                     	cmp	ebx, -0x1
 10029de: 74 06                        	je	0x10029e6 <.text+0x1e6>
 10029e0: 89 9e 88 02 00 00            	mov	dword ptr [esi + 0x288], ebx
 10029e6: 8b 7d 0c                     	mov	edi, dword ptr [ebp + 0xc]
 10029e9: 83 ff ff                     	cmp	edi, -0x1
 10029ec: 74 06                        	je	0x10029f4 <.text+0x1f4>
 10029ee: 89 be 8c 02 00 00            	mov	dword ptr [esi + 0x28c], edi
 10029f4: 8b 86 8c 02 00 00            	mov	eax, dword ptr [esi + 0x28c]
 10029fa: 8b 8e 88 02 00 00            	mov	ecx, dword ptr [esi + 0x288]
 1002a00: 50                           	push	eax
 1002a01: 51                           	push	ecx
 1002a02: 68 a2 56 00 00               	push	0x56a2
 1002a07: e8 54 88 22 00               	call	0x122b260 <.text+0x228a60>
 1002a0c: 83 c4 04                     	add	esp, 0x4
 1002a0f: 50                           	push	eax
 1002a10: 8d 96 cc 02 00 00            	lea	edx, [esi + 0x2cc]
 1002a16: 52                           	push	edx
 1002a17: e8 b4 40 43 ff               	call	0x436ad0
 1002a1c: 8b 86 90 02 00 00            	mov	eax, dword ptr [esi + 0x290]
 1002a22: 83 c4 10                     	add	esp, 0x10
 1002a25: 83 f8 01                     	cmp	eax, 0x1
 1002a28: 0f 9c c1                     	setl	cl
 1002a2b: 88 4d 08                     	mov	byte ptr [ebp + 0x8], cl
 1002a2e: 8b 8e 58 02 00 00            	mov	ecx, dword ptr [esi + 0x258]
 1002a34: 85 c9                        	test	ecx, ecx
 1002a36: 74 11                        	je	0x1002a49 <.text+0x249>
 1002a38: 8b 11                        	mov	edx, dword ptr [ecx]
 1002a3a: 8b 52 18                     	mov	edx, dword ptr [edx + 0x18]
 1002a3d: 83 f8 ff                     	cmp	eax, -0x1
 1002a40: 0f 9f c0                     	setg	al
 1002a43: 0f b6 c0                     	movzx	eax, al
 1002a46: 50                           	push	eax
 1002a47: ff d2                        	call	edx
 1002a49: 8b 8e 5c 02 00 00            	mov	ecx, dword ptr [esi + 0x25c]
 1002a4f: 85 c9                        	test	ecx, ecx
 1002a51: 74 0b                        	je	0x1002a5e <.text+0x25e>
 1002a53: 8b 01                        	mov	eax, dword ptr [ecx]
 1002a55: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 1002a58: 8b 40 18                     	mov	eax, dword ptr [eax + 0x18]
 1002a5b: 52                           	push	edx
 1002a5c: ff d0                        	call	eax
 1002a5e: 8b 8e 80 02 00 00            	mov	ecx, dword ptr [esi + 0x280]
 1002a64: 57                           	push	edi
 1002a65: 53                           	push	ebx
 1002a66: e8 d5 8e 1f 00               	call	0x11fb940 <.text+0x1f9140>
 1002a6b: 8b 0d d0 8c ac 01            	mov	ecx, dword ptr [0x1ac8cd0]
 1002a71: 57                           	push	edi
 1002a72: 53                           	push	ebx
 1002a73: e8 58 02 94 ff               	call	0x942cd0
 1002a78: 57                           	push	edi
 1002a79: 53                           	push	ebx
 1002a7a: 8b ce                        	mov	ecx, esi
 1002a7c: e8 5f fa ff ff               	call	0x10024e0
 1002a81: 5f                           	pop	edi
 1002a82: 5e                           	pop	esi
 1002a83: 5b                           	pop	ebx
 1002a84: 5d                           	pop	ebp
 1002a85: c2 08 00                     	ret	0x8
 1002a88: cc                           	int3
 1002a89: cc                           	int3
 1002a8a: cc                           	int3
 1002a8b: cc                           	int3
 1002a8c: cc                           	int3
 1002a8d: cc                           	int3
 1002a8e: cc                           	int3
 1002a8f: cc                           	int3
 1002a90: 55                           	push	ebp
 1002a91: 8b ec                        	mov	ebp, esp
 1002a93: 56                           	push	esi
 1002a94: 8b f1                        	mov	esi, ecx
 1002a96: 33 c0                        	xor	eax, eax
 1002a98: 89 86 90 02 00 00            	mov	dword ptr [esi + 0x290], eax
 1002a9e: 88 86 8c 0e 00 00            	mov	byte ptr [esi + 0xe8c], al
 1002aa4: 8b 0d d0 8c ac 01            	mov	ecx, dword ptr [0x1ac8cd0]
 1002aaa: e8 c1 27 1d 00               	call	0x11d5270 <.text+0x1d2a70>
 1002aaf: 8b 0d d0 8c ac 01            	mov	ecx, dword ptr [0x1ac8cd0]
 1002ab5: 50                           	push	eax
 1002ab6: e8 d5 1c 1a 00               	call	0x11a4790 <.text+0x1a1f90>
 1002abb: 50                           	push	eax
 1002abc: 8b ce                        	mov	ecx, esi
 1002abe: e8 0d ff ff ff               	call	0x10029d0 <.text+0x1d0>
 1002ac3: 8b 0d d0 8c ac 01            	mov	ecx, dword ptr [0x1ac8cd0]
 1002ac9: e8 62 79 15 00               	call	0x115a430 <.text+0x157c30>
 1002ace: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 1002ad1: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 1002ad4: 50                           	push	eax
 1002ad5: 51                           	push	ecx
 1002ad6: 8b ce                        	mov	ecx, esi
 1002ad8: e8 f3 32 ef ff               	call	0xef5dd0
 1002add: 5e                           	pop	esi
 1002ade: 5d                           	pop	ebp
 1002adf: c2 08 00                     	ret	0x8
 1002ae2: cc                           	int3
 1002ae3: cc                           	int3
 1002ae4: cc                           	int3
 1002ae5: cc                           	int3
 1002ae6: cc                           	int3
 1002ae7: cc                           	int3
 1002ae8: cc                           	int3
 1002ae9: cc                           	int3
 1002aea: cc                           	int3
 1002aeb: cc                           	int3
 1002aec: cc                           	int3
 1002aed: cc                           	int3
 1002aee: cc                           	int3
 1002aef: cc                           	int3
 1002af0: 55                           	push	ebp
 1002af1: 8b ec                        	mov	ebp, esp
 1002af3: 83 ec 08                     	sub	esp, 0x8
 1002af6: 53                           	push	ebx
 1002af7: 56                           	push	esi
 1002af8: 57                           	push	edi
 1002af9: 8b f1                        	mov	esi, ecx
 1002afb: e8 00 7e ef ff               	call	0xefa900
 1002b00: 8b 8e 58 02 00 00            	mov	ecx, dword ptr [esi + 0x258]
 1002b06: 85 c9                        	test	ecx, ecx
 1002b08: 74 32                        	je	0x1002b3c <.text+0x33c>
 1002b0a: e8 b1 b4 1b 00               	call	0x11bdfc0 <.text+0x1bb7c0>
 1002b0f: 84 c0                        	test	al, al
 1002b11: 74 29                        	je	0x1002b3c <.text+0x33c>
 1002b13: 8b 86 8c 02 00 00            	mov	eax, dword ptr [esi + 0x28c]
 1002b19: 8b 8e 88 02 00 00            	mov	ecx, dword ptr [esi + 0x288]
 1002b1f: 83 f8 01                     	cmp	eax, 0x1
 1002b22: 75 08                        	jne	0x1002b2c <.text+0x32c>
 1002b24: 49                           	dec	ecx
 1002b25: b8 0c 00 00 00               	mov	eax, 0xc
 1002b2a: eb 01                        	jmp	0x1002b2d <.text+0x32d>
 1002b2c: 48                           	dec	eax
 1002b2d: ff 8e 90 02 00 00            	dec	dword ptr [esi + 0x290]
 1002b33: 50                           	push	eax
 1002b34: 51                           	push	ecx
 1002b35: 8b ce                        	mov	ecx, esi
 1002b37: e8 94 fe ff ff               	call	0x10029d0 <.text+0x1d0>
 1002b3c: 8b 8e 5c 02 00 00            	mov	ecx, dword ptr [esi + 0x25c]
 1002b42: 85 c9                        	test	ecx, ecx
 1002b44: 74 32                        	je	0x1002b78 <.text+0x378>
 1002b46: e8 75 b4 1b 00               	call	0x11bdfc0 <.text+0x1bb7c0>
 1002b4b: 84 c0                        	test	al, al
 1002b4d: 74 29                        	je	0x1002b78 <.text+0x378>
 1002b4f: 8b 86 8c 02 00 00            	mov	eax, dword ptr [esi + 0x28c]
 1002b55: 8b 8e 88 02 00 00            	mov	ecx, dword ptr [esi + 0x288]
 1002b5b: 83 f8 0c                     	cmp	eax, 0xc
 1002b5e: 75 08                        	jne	0x1002b68 <.text+0x368>
 1002b60: 41                           	inc	ecx
 1002b61: b8 01 00 00 00               	mov	eax, 0x1
 1002b66: eb 01                        	jmp	0x1002b69 <.text+0x369>
 1002b68: 40                           	inc	eax
 1002b69: ff 86 90 02 00 00            	inc	dword ptr [esi + 0x290]
 1002b6f: 50                           	push	eax
 1002b70: 51                           	push	ecx
 1002b71: 8b ce                        	mov	ecx, esi
 1002b73: e8 58 fe ff ff               	call	0x10029d0 <.text+0x1d0>
 1002b78: bb 01 00 00 00               	mov	ebx, 0x1
 1002b7d: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 1002b80: 8d be dc 04 00 00            	lea	edi, [esi + 0x4dc]
 1002b86: c7 45 f8 1f 00 00 00         	mov	dword ptr [ebp - 0x8], 0x1f
 1002b8d: 8d 49 00                     	lea	ecx, [ecx]
 1002b90: 8b 8e 80 02 00 00            	mov	ecx, dword ptr [esi + 0x280]
 1002b96: 53                           	push	ebx
 1002b97: e8 24 8d 1f 00               	call	0x11fb8c0 <.text+0x1f90c0>
 1002b9c: 85 c0                        	test	eax, eax
 1002b9e: 74 69                        	je	0x1002c09 <.text+0x409>
 1002ba0: 83 78 04 ff                  	cmp	dword ptr [eax + 0x4], -0x1
 1002ba4: 74 63                        	je	0x1002c09 <.text+0x409>
 1002ba6: 83 fb 1f                     	cmp	ebx, 0x1f
 1002ba9: 7f 5e                        	jg	0x1002c09 <.text+0x409>
 1002bab: 85 ff                        	test	edi, edi
 1002bad: 74 5a                        	je	0x1002c09 <.text+0x409>
 1002baf: 8b 07                        	mov	eax, dword ptr [edi]
 1002bb1: 8b 0d d0 8c ac 01            	mov	ecx, dword ptr [0x1ac8cd0]
 1002bb7: 50                           	push	eax
 1002bb8: e8 43 f5 93 ff               	call	0x942100
 1002bbd: 8b d8                        	mov	ebx, eax
 1002bbf: 85 db                        	test	ebx, ebx
 1002bc1: 74 46                        	je	0x1002c09 <.text+0x409>
 1002bc3: 8b 8e 84 02 00 00            	mov	ecx, dword ptr [esi + 0x284]
 1002bc9: 85 c9                        	test	ecx, ecx
 1002bcb: 74 10                        	je	0x1002bdd <.text+0x3dd>
 1002bcd: e8 8e d3 42 ff               	call	0x42ff60
 1002bd2: 8b 8e 84 02 00 00            	mov	ecx, dword ptr [esi + 0x284]
 1002bd8: e8 23 b7 1b 00               	call	0x11be300 <.text+0x1bbb00>
 1002bdd: 8b 4f 04                     	mov	ecx, dword ptr [edi + 0x4]
 1002be0: 85 c9                        	test	ecx, ecx
 1002be2: 74 25                        	je	0x1002c09 <.text+0x409>
 1002be4: e8 d7 b3 1b 00               	call	0x11bdfc0 <.text+0x1bb7c0>
 1002be9: 84 c0                        	test	al, al
 1002beb: 74 1c                        	je	0x1002c09 <.text+0x409>
 1002bed: 6a 00                        	push	0x0
 1002bef: 8b cb                        	mov	ecx, ebx
 1002bf1: e8 ea be 6d ff               	call	0x6deae0
 1002bf6: 8b 48 04                     	mov	ecx, dword ptr [eax + 0x4]
 1002bf9: 51                           	push	ecx
 1002bfa: 8b 0d d0 8c ac 01            	mov	ecx, dword ptr [0x1ac8cd0]
 1002c00: 6a ff                        	push	-0x1
 1002c02: 6a 02                        	push	0x2
 1002c04: e8 b7 f7 93 ff               	call	0x9423c0
 1002c09: 8b 5d fc                     	mov	ebx, dword ptr [ebp - 0x4]
 1002c0c: 43                           	inc	ebx
 1002c0d: 83 c7 50                     	add	edi, 0x50
 1002c10: ff 4d f8                     	dec	dword ptr [ebp - 0x8]
 1002c13: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 1002c16: 0f 85 74 ff ff ff            	jne	0x1002b90 <.text+0x390>
 1002c1c: 5f                           	pop	edi
 1002c1d: 5e                           	pop	esi
 1002c1e: 5b                           	pop	ebx
 1002c1f: 8b e5                        	mov	esp, ebp
 1002c21: 5d                           	pop	ebp
 1002c22: c3                           	ret
 1002c23: cc                           	int3
 1002c24: cc                           	int3
 1002c25: cc                           	int3
 1002c26: cc                           	int3
 1002c27: cc                           	int3
 1002c28: cc                           	int3
 1002c29: cc                           	int3
 1002c2a: cc                           	int3
 1002c2b: cc                           	int3
 1002c2c: cc                           	int3
 1002c2d: cc                           	int3
 1002c2e: cc                           	int3
 1002c2f: cc                           	int3
 1002c30: c7 81 d8 03 00 00 00 00 00 00	mov	dword ptr [ecx + 0x3d8], 0x0
 1002c3a: c3                           	ret
 1002c3b: cc                           	int3
 1002c3c: cc                           	int3
 1002c3d: cc                           	int3
 1002c3e: cc                           	int3
 1002c3f: cc                           	int3
 1002c40: 55                           	push	ebp
 1002c41: 8b ec                        	mov	ebp, esp
 1002c43: 51                           	push	ecx
 1002c44: 53                           	push	ebx
 1002c45: 57                           	push	edi
 1002c46: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 1002c49: 8b d9                        	mov	ebx, ecx
 1002c4b: 85 ff                        	test	edi, edi
 1002c4d: 75 0a                        	jne	0x1002c59 <.text+0x459>
 1002c4f: 5f                           	pop	edi
 1002c50: 32 c0                        	xor	al, al
 1002c52: 5b                           	pop	ebx
 1002c53: 8b e5                        	mov	esp, ebp
 1002c55: 5d                           	pop	ebp
 1002c56: c2 04 00                     	ret	0x4
 1002c59: 8b 8b cc 03 00 00            	mov	ecx, dword ptr [ebx + 0x3cc]
 1002c5f: 56                           	push	esi
 1002c60: 8b b3 c8 03 00 00            	mov	esi, dword ptr [ebx + 0x3c8]
 1002c66: 2b ce                        	sub	ecx, esi
 1002c68: b8 93 24 49 92               	mov	eax, 0x92492493
 1002c6d: f7 e9                        	imul	ecx
 1002c6f: 03 d1                        	add	edx, ecx
 1002c71: c1 fa 05                     	sar	edx, 0x5
 1002c74: 8b c2                        	mov	eax, edx
 1002c76: c1 e8 1f                     	shr	eax, 0x1f
 1002c79: 03 c2                        	add	eax, edx
 1002c7b: 3b f8                        	cmp	edi, eax
 1002c7d: 0f 83 87 00 00 00            	jae	0x1002d0a <.text+0x50a>
 1002c83: 8d 0c fd 00 00 00 00         	lea	ecx, [8*edi]
 1002c8a: 2b cf                        	sub	ecx, edi
 1002c8c: 68 78 21 56 01               	push	0x1562178
 1002c91: 8d 34 ce                     	lea	esi, [esi + 8*ecx]
 1002c94: e8 57 d2 19 00               	call	0x119fef0 <.text+0x19d6f0>
 1002c99: 8b c8                        	mov	ecx, eax
 1002c9b: 8d 51 02                     	lea	edx, [ecx + 0x2]
 1002c9e: 83 c4 04                     	add	esp, 0x4
 1002ca1: 8d 7e 18                     	lea	edi, [esi + 0x18]
 1002ca4: 89 55 fc                     	mov	dword ptr [ebp - 0x4], edx
 1002ca7: 66 8b 11                     	mov	dx, word ptr [ecx]
 1002caa: 83 c1 02                     	add	ecx, 0x2
 1002cad: 66 85 d2                     	test	dx, dx
 1002cb0: 75 f5                        	jne	0x1002ca7 <.text+0x4a7>
 1002cb2: 2b 4d fc                     	sub	ecx, dword ptr [ebp - 0x4]
 1002cb5: d1 f9                        	sar	ecx
 1002cb7: 51                           	push	ecx
 1002cb8: 50                           	push	eax
 1002cb9: 8b 47 14                     	mov	eax, dword ptr [edi + 0x14]
 1002cbc: 50                           	push	eax
 1002cbd: 6a 00                        	push	0x0
 1002cbf: 8b cf                        	mov	ecx, edi
 1002cc1: e8 6a ef 3f ff               	call	0x401c30
 1002cc6: 85 c0                        	test	eax, eax
 1002cc8: 74 2c                        	je	0x1002cf6 <.text+0x4f6>
 1002cca: 83 7f 18 08                  	cmp	dword ptr [edi + 0x18], 0x8
 1002cce: 72 13                        	jb	0x1002ce3 <.text+0x4e3>
 1002cd0: 8b 0d e4 64 b5 01            	mov	ecx, dword ptr [0x1b564e4]
 1002cd6: 8b 7f 04                     	mov	edi, dword ptr [edi + 0x4]
 1002cd9: 8b 11                        	mov	edx, dword ptr [ecx]
 1002cdb: 8b 42 10                     	mov	eax, dword ptr [edx + 0x10]
 1002cde: 57                           	push	edi
 1002cdf: ff d0                        	call	eax
 1002ce1: eb 21                        	jmp	0x1002d04 <.text+0x504>
 1002ce3: 8b 0d e4 64 b5 01            	mov	ecx, dword ptr [0x1b564e4]
 1002ce9: 8b 11                        	mov	edx, dword ptr [ecx]
 1002ceb: 8b 42 10                     	mov	eax, dword ptr [edx + 0x10]
 1002cee: 83 c7 04                     	add	edi, 0x4
 1002cf1: 57                           	push	edi
 1002cf2: ff d0                        	call	eax
 1002cf4: eb 0e                        	jmp	0x1002d04 <.text+0x504>
 1002cf6: 8b 0e                        	mov	ecx, dword ptr [esi]
 1002cf8: 51                           	push	ecx
 1002cf9: 8b 0d 70 a8 a6 01            	mov	ecx, dword ptr [0x1a6a870]
 1002cff: e8 ac 84 1b 00               	call	0x11bb1b0 <.text+0x1b89b0>
 1002d04: 8b f8                        	mov	edi, eax
 1002d06: 85 ff                        	test	edi, edi
 1002d08: 75 0b                        	jne	0x1002d15 <.text+0x515>
 1002d0a: 5e                           	pop	esi
 1002d0b: 5f                           	pop	edi
 1002d0c: 32 c0                        	xor	al, al
 1002d0e: 5b                           	pop	ebx
 1002d0f: 8b e5                        	mov	esp, ebp
 1002d11: 5d                           	pop	ebp
 1002d12: c2 04 00                     	ret	0x4
 1002d15: 6a 03                        	push	0x3
 1002d17: 8b cf                        	mov	ecx, edi
 1002d19: e8 22 6b 7b ff               	call	0x7b9840
 1002d1e: 8b 13                        	mov	edx, dword ptr [ebx]
 1002d20: 8b 42 08                     	mov	eax, dword ptr [edx + 0x8]
 1002d23: 8b cb                        	mov	ecx, ebx
 1002d25: ff d0                        	call	eax
 1002d27: 8b 46 14                     	mov	eax, dword ptr [esi + 0x14]
 1002d2a: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 1002d2d: 8b 13                        	mov	edx, dword ptr [ebx]
 1002d2f: 8b 92 b0 00 00 00            	mov	edx, dword ptr [edx + 0xb0]
 1002d35: 50                           	push	eax
 1002d36: 8b 46 0c                     	mov	eax, dword ptr [esi + 0xc]
 1002d39: 51                           	push	ecx
 1002d3a: 8b 4e 08                     	mov	ecx, dword ptr [esi + 0x8]
 1002d3d: 50                           	push	eax
 1002d3e: 8b 46 04                     	mov	eax, dword ptr [esi + 0x4]
 1002d41: 51                           	push	ecx
 1002d42: 50                           	push	eax
 1002d43: 57                           	push	edi
 1002d44: 8b cb                        	mov	ecx, ebx
 1002d46: ff d2                        	call	edx
 1002d48: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 1002d4b: 5e                           	pop	esi
 1002d4c: 89 83 d8 03 00 00            	mov	dword ptr [ebx + 0x3d8], eax
 1002d52: 5f                           	pop	edi
 1002d53: b0 01                        	mov	al, 0x1
 1002d55: 5b                           	pop	ebx
 1002d56: 8b e5                        	mov	esp, ebp
 1002d58: 5d                           	pop	ebp
 1002d59: c2 04 00                     	ret	0x4
 1002d5c: cc                           	int3
 1002d5d: cc                           	int3
 1002d5e: cc                           	int3
 1002d5f: cc                           	int3
 1002d60: 56                           	push	esi
 1002d61: 8b f1                        	mov	esi, ecx
 1002d63: 83 7e 30 08                  	cmp	dword ptr [esi + 0x30], 0x8
 1002d67: 72 0c                        	jb	0x1002d75 <.text+0x575>
 1002d69: 8b 46 1c                     	mov	eax, dword ptr [esi + 0x1c]
 1002d6c: 50                           	push	eax
 1002d6d: e8 b5 2d 3d 00               	call	0x13d5b27 <.text+0x3d3327>
 1002d72: 83 c4 04                     	add	esp, 0x4
 1002d75: 33 c9                        	xor	ecx, ecx
 1002d77: c7 46 30 07 00 00 00         	mov	dword ptr [esi + 0x30], 0x7
 1002d7e: c7 46 2c 00 00 00 00         	mov	dword ptr [esi + 0x2c], 0x0
 1002d85: 66 89 4e 1c                  	mov	word ptr [esi + 0x1c], cx
 1002d89: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 1002d8c: 52                           	push	edx
 1002d8d: e8 95 2d 3d 00               	call	0x13d5b27 <.text+0x3d3327>
 1002d92: 83 c4 04                     	add	esp, 0x4
 1002d95: c7 46 18 00 00 00 00         	mov	dword ptr [esi + 0x18], 0x0
 1002d9c: 5e                           	pop	esi
 1002d9d: c3                           	ret
 1002d9e: cc                           	int3
 1002d9f: cc                           	int3
