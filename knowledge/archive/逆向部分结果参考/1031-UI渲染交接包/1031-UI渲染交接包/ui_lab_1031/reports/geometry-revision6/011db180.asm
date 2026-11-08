
<stdin>:	file format elf32-i386

Disassembly of section .text:

011db180 <.text>:
 11db180: 55                           	push	ebp
 11db181: 8b ec                        	mov	ebp, esp
 11db183: 56                           	push	esi
 11db184: 57                           	push	edi
 11db185: 8b 7d 10                     	mov	edi, dword ptr [ebp + 0x10]
 11db188: 8b f1                        	mov	esi, ecx
 11db18a: 8b cf                        	mov	ecx, edi
 11db18c: e8 ef de 3d ff               	call	0x5b9080
 11db191: 83 f8 07                     	cmp	eax, 0x7
 11db194: 75 56                        	jne	0x11db1ec <.text+0x6c>
 11db196: f3 0f 10 05 b4 61 56 01      	movss	xmm0, dword ptr [0x15661b4]
 11db19e: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11db1a1: 8b 06                        	mov	eax, dword ptr [esi]
 11db1a3: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11db1a6: 8b 80 ac 00 00 00            	mov	eax, dword ptr [eax + 0xac]
 11db1ac: 6a 24                        	push	0x24
 11db1ae: 6a 00                        	push	0x0
 11db1b0: 83 ec 14                     	sub	esp, 0x14
 11db1b3: f3 0f 11 44 24 10            	movss	dword ptr [esp + 0x10], xmm0
 11db1b9: f3 0f 11 44 24 0c            	movss	dword ptr [esp + 0xc], xmm0
 11db1bf: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11db1c7: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11db1cd: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11db1d3: 0f 57 c0                     	xorps	xmm0, xmm0
 11db1d6: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11db1db: 6a 00                        	push	0x0
 11db1dd: 6a ff                        	push	-0x1
 11db1df: 57                           	push	edi
 11db1e0: 51                           	push	ecx
 11db1e1: 52                           	push	edx
 11db1e2: 8b ce                        	mov	ecx, esi
 11db1e4: ff d0                        	call	eax
 11db1e6: 5f                           	pop	edi
 11db1e7: 5e                           	pop	esi
 11db1e8: 5d                           	pop	ebp
 11db1e9: c2 0c 00                     	ret	0xc
 11db1ec: 83 f8 08                     	cmp	eax, 0x8
 11db1ef: 74 0f                        	je	0x11db200 <.text+0x80>
 11db1f1: 83 f8 0e                     	cmp	eax, 0xe
 11db1f4: 74 0a                        	je	0x11db200 <.text+0x80>
 11db1f6: 83 f8 0f                     	cmp	eax, 0xf
 11db1f9: 74 05                        	je	0x11db200 <.text+0x80>
 11db1fb: 83 f8 10                     	cmp	eax, 0x10
 11db1fe: 75 10                        	jne	0x11db210 <.text+0x90>
 11db200: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11db203: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11db206: 57                           	push	edi
 11db207: 51                           	push	ecx
 11db208: 52                           	push	edx
 11db209: 8b ce                        	mov	ecx, esi
 11db20b: e8 d0 fb ff ff               	call	0x11dade0
 11db210: 5f                           	pop	edi
 11db211: 5e                           	pop	esi
 11db212: 5d                           	pop	ebp
 11db213: c2 0c 00                     	ret	0xc
