
<stdin>:	file format elf32-i386

Disassembly of section .text:

011bf2a0 <.text>:
 11bf2a0: a1 f4 24 a4 01               	mov	eax, dword ptr [0x1a424f4]
 11bf2a5: 56                           	push	esi
 11bf2a6: 8b f1                        	mov	esi, ecx
 11bf2a8: 3b 46 34                     	cmp	eax, dword ptr [esi + 0x34]
 11bf2ab: 75 72                        	jne	0x11bf31f <.text+0x7f>
 11bf2ad: e8 6e 8b 00 00               	call	0x11c7e20 <.text+0x8b80>
 11bf2b2: 83 f8 01                     	cmp	eax, 0x1
 11bf2b5: 75 68                        	jne	0x11bf31f <.text+0x7f>
 11bf2b7: 8b 0d f4 24 a4 01            	mov	ecx, dword ptr [0x1a424f4]
 11bf2bd: 3b 4e 34                     	cmp	ecx, dword ptr [esi + 0x34]
 11bf2c0: 75 5d                        	jne	0x11bf31f <.text+0x7f>
 11bf2c2: 57                           	push	edi
 11bf2c3: e8 f8 8a 00 00               	call	0x11c7dc0 <.text+0x8b20>
 11bf2c8: 8b f8                        	mov	edi, eax
 11bf2ca: e8 01 8b 00 00               	call	0x11c7dd0 <.text+0x8b30>
 11bf2cf: 85 ff                        	test	edi, edi
 11bf2d1: 78 4b                        	js	0x11bf31e <.text+0x7e>
 11bf2d3: 85 c0                        	test	eax, eax
 11bf2d5: 78 47                        	js	0x11bf31e <.text+0x7e>
 11bf2d7: 83 7e 5c 00                  	cmp	dword ptr [esi + 0x5c], 0x0
 11bf2db: 74 30                        	je	0x11bf30d <.text+0x6d>
 11bf2dd: 80 7e 11 00                  	cmp	byte ptr [esi + 0x11], 0x0
 11bf2e1: 74 2a                        	je	0x11bf30d <.text+0x6d>
 11bf2e3: 8b 4e 5c                     	mov	ecx, dword ptr [esi + 0x5c]
 11bf2e6: 8b 51 18                     	mov	edx, dword ptr [ecx + 0x18]
 11bf2e9: 2b 56 28                     	sub	edx, dword ptr [esi + 0x28]
 11bf2ec: 6a 01                        	push	0x1
 11bf2ee: 2b 56 18                     	sub	edx, dword ptr [esi + 0x18]
 11bf2f1: 03 d0                        	add	edx, eax
 11bf2f3: 8b 41 14                     	mov	eax, dword ptr [ecx + 0x14]
 11bf2f6: 2b 46 24                     	sub	eax, dword ptr [esi + 0x24]
 11bf2f9: 52                           	push	edx
 11bf2fa: 2b 46 14                     	sub	eax, dword ptr [esi + 0x14]
 11bf2fd: 03 c7                        	add	eax, edi
 11bf2ff: 50                           	push	eax
 11bf300: e8 cb f7 ff ff               	call	0x11bead0
 11bf305: 5f                           	pop	edi
 11bf306: b8 01 00 00 00               	mov	eax, 0x1
 11bf30b: 5e                           	pop	esi
 11bf30c: c3                           	ret
 11bf30d: 2b 46 28                     	sub	eax, dword ptr [esi + 0x28]
 11bf310: 2b 7e 24                     	sub	edi, dword ptr [esi + 0x24]
 11bf313: 6a 01                        	push	0x1
 11bf315: 50                           	push	eax
 11bf316: 57                           	push	edi
 11bf317: 8b ce                        	mov	ecx, esi
 11bf319: e8 b2 f7 ff ff               	call	0x11bead0
 11bf31e: 5f                           	pop	edi
 11bf31f: b8 01 00 00 00               	mov	eax, 0x1
 11bf324: 5e                           	pop	esi
 11bf325: c3                           	ret
 11bf326: cc                           	int3
 11bf327: cc                           	int3
 11bf328: cc                           	int3
 11bf329: cc                           	int3
 11bf32a: cc                           	int3
 11bf32b: cc                           	int3
 11bf32c: cc                           	int3
 11bf32d: cc                           	int3
 11bf32e: cc                           	int3
 11bf32f: cc                           	int3
 11bf330: 55                           	push	ebp
 11bf331: 8b ec                        	mov	ebp, esp
 11bf333: 83 ec 1c                     	sub	esp, 0x1c
 11bf336: 83 7d 08 00                  	cmp	dword ptr [ebp + 0x8], 0x0
 11bf33a: 53                           	push	ebx
 11bf33b: 56                           	push	esi
 11bf33c: 57                           	push	edi
 11bf33d: 8b d9                        	mov	ebx, ecx
 11bf33f: 75 0e                        	jne	0x11bf34f <.text+0xaf>
 11bf341: b8 00 00 00 80               	mov	eax, 0x80000000
 11bf346: 5f                           	pop	edi
 11bf347: 5e                           	pop	esi
 11bf348: 5b                           	pop	ebx
 11bf349: 8b e5                        	mov	esp, ebp
 11bf34b: 5d                           	pop	ebp
 11bf34c: c2 04 00                     	ret	0x4
 11bf34f: 8d 45 08                     	lea	eax, [ebp + 0x8]
 11bf352: 50                           	push	eax
 11bf353: 83 ec 0c                     	sub	esp, 0xc
 11bf356: 8b cc                        	mov	ecx, esp
 11bf358: 89 65 fc                     	mov	dword ptr [ebp - 0x4], esp
 11bf35b: 51                           	push	ecx
 11bf35c: 8d 4b 64                     	lea	ecx, [ebx + 0x64]
 11bf35f: e8 0c 6e fb ff               	call	0x1176170
 11bf364: 83 ec 0c                     	sub	esp, 0xc
 11bf367: 8b d4                        	mov	edx, esp
 11bf369: 89 65 fc                     	mov	dword ptr [ebp - 0x4], esp
 11bf36c: 52                           	push	edx
 11bf36d: 8d 4b 64                     	lea	ecx, [ebx + 0x64]
 11bf370: e8 9b e3 15 00               	call	0x131d710 <.text+0x15e470>
 11bf375: 8d 45 f0                     	lea	eax, [ebp - 0x10]
 11bf378: 50                           	push	eax
 11bf379: e8 02 c3 ff ff               	call	0x11bb680
 11bf37e: 83 c4 20                     	add	esp, 0x20
 11bf381: 8d 4d e4                     	lea	ecx, [ebp - 0x1c]
 11bf384: 51                           	push	ecx
 11bf385: 8d 4b 64                     	lea	ecx, [ebx + 0x64]
 11bf388: e8 e3 6d fb ff               	call	0x1176170
 11bf38d: 8b 08                        	mov	ecx, dword ptr [eax]
 11bf38f: 85 c9                        	test	ecx, ecx
 11bf391: 74 74                        	je	0x11bf407 <.text+0x167>
 11bf393: 8b 09                        	mov	ecx, dword ptr [ecx]
 11bf395: 85 c9                        	test	ecx, ecx
 11bf397: 74 6e                        	je	0x11bf407 <.text+0x167>
 11bf399: 8b 55 f0                     	mov	edx, dword ptr [ebp - 0x10]
 11bf39c: 85 d2                        	test	edx, edx
 11bf39e: 74 02                        	je	0x11bf3a2 <.text+0x102>
 11bf3a0: 8b 12                        	mov	edx, dword ptr [edx]
 11bf3a2: 3b ca                        	cmp	ecx, edx
 11bf3a4: 75 61                        	jne	0x11bf407 <.text+0x167>
 11bf3a6: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
 11bf3a9: 3b 55 f8                     	cmp	edx, dword ptr [ebp - 0x8]
 11bf3ac: 75 93                        	jne	0x11bf341 <.text+0xa1>
 11bf3ae: 8d 45                        	<unknown>
