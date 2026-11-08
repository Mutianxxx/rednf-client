
<stdin>:	file format elf32-i386

Disassembly of section .text:

10004f30 <.text>:
10004f30: 55                           	push	ebp
10004f31: 8b ec                        	mov	ebp, esp
10004f33: 83 7d 0c 01                  	cmp	dword ptr [ebp + 0xc], 0x1
10004f37: 75 69                        	jne	0x10004fa2 <.text+0x72>
10004f39: 53                           	push	ebx
10004f3a: 56                           	push	esi
10004f3b: 33 db                        	xor	ebx, ebx
10004f3d: 57                           	push	edi
10004f3e: 89 5d 0c                     	mov	dword ptr [ebp + 0xc], ebx
10004f41: e8 3a 23 01 00               	call	0x10017280 <.text+0x12350>
10004f46: 53                           	push	ebx
10004f47: 68 ec 94 01 10               	push	0x100194ec
10004f4c: 53                           	push	ebx
10004f4d: 8b f0                        	mov	esi, eax
10004f4f: ff 75 08                     	push	dword ptr [ebp + 0x8]
10004f52: 8b 7e 08                     	mov	edi, dword ptr [esi + 0x8]
10004f55: e8 12 26 01 00               	call	0x1001756c <.text+0x1263c>
10004f5a: 85 c0                        	test	eax, eax
10004f5c: 75 07                        	jne	0x10004f65 <.text+0x35>
10004f5e: e8 c2 30 01 00               	call	0x10018025 <.text+0x130f5>
10004f63: eb 32                        	jmp	0x10004f97 <.text+0x67>
10004f65: e8 48 25 01 00               	call	0x100174b2 <.text+0x12582>
10004f6a: 8b 58 04                     	mov	ebx, dword ptr [eax + 0x4]
10004f6d: 85 db                        	test	ebx, ebx
10004f6f: 74 14                        	je	0x10004f85 <.text+0x55>
10004f71: 8b 03                        	mov	eax, dword ptr [ebx]
10004f73: 8b cb                        	mov	ecx, ebx
10004f75: ff 50 50                     	call	dword ptr [eax + 0x50]
10004f78: 85 c0                        	test	eax, eax
10004f7a: 75 09                        	jne	0x10004f85 <.text+0x55>
10004f7c: 8b 03                        	mov	eax, dword ptr [ebx]
10004f7e: 8b cb                        	mov	ecx, ebx
10004f80: ff 50 68                     	call	dword ptr [eax + 0x68]
10004f83: eb d9                        	jmp	0x10004f5e <.text+0x2e>
10004f85: ff 75 08                     	push	dword ptr [ebp + 0x8]
10004f88: 89 7e 08                     	mov	dword ptr [esi + 0x8], edi
10004f8b: e8 eb 21 01 00               	call	0x1001717b <.text+0x1224b>
10004f90: c7 45 0c 01 00 00 00         	mov	dword ptr [ebp + 0xc], 0x1
10004f97: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
10004f9a: 89 7e 08                     	mov	dword ptr [esi + 0x8], edi
10004f9d: 5f                           	pop	edi
10004f9e: 5e                           	pop	esi
10004f9f: 5b                           	pop	ebx
10004fa0: eb 53                        	jmp	0x10004ff5 <.text+0xc5>
10004fa2: 83 7d 0c 00                  	cmp	dword ptr [ebp + 0xc], 0x0
10004fa6: 75 30                        	jne	0x10004fd8 <.text+0xa8>
10004fa8: e8 05 25 01 00               	call	0x100174b2 <.text+0x12582>
10004fad: 8b 40 04                     	mov	eax, dword ptr [eax + 0x4]
10004fb0: 85 c0                        	test	eax, eax
10004fb2: 74 07                        	je	0x10004fbb <.text+0x8b>
10004fb4: 8b 10                        	mov	edx, dword ptr [eax]
10004fb6: 8b c8                        	mov	ecx, eax
10004fb8: ff 52 68                     	call	dword ptr [edx + 0x68]
10004fbb: e8 c6 da 00 00               	call	0x10012a86 <.text+0xdb56>
10004fc0: 6a ff                        	push	-0x1
10004fc2: e8 c8 da 00 00               	call	0x10012a8f <.text+0xdb5f>
10004fc7: e8 59 30 01 00               	call	0x10018025 <.text+0x130f5>
10004fcc: 6a 01                        	push	0x1
10004fce: ff 75 08                     	push	dword ptr [ebp + 0x8]
10004fd1: e8 bb 21 01 00               	call	0x10017191 <.text+0x12261>
10004fd6: eb 1a                        	jmp	0x10004ff2 <.text+0xc2>
10004fd8: 83 7d 0c 03                  	cmp	dword ptr [ebp + 0xc], 0x3
10004fdc: 75 14                        	jne	0x10004ff2 <.text+0xc2>
10004fde: e8 a3 da 00 00               	call	0x10012a86 <.text+0xdb56>
10004fe3: 6a ff                        	push	-0x1
10004fe5: e8 a5 da 00 00               	call	0x10012a8f <.text+0xdb5f>
10004fea: ff 75 08                     	push	dword ptr [ebp + 0x8]
10004fed: e8 c2 cf 00 00               	call	0x10011fb4 <.text+0xd084>
10004ff2: 6a 01                        	push	0x1
10004ff4: 58                           	pop	eax
10004ff5: 5d                           	pop	ebp
10004ff6: c2                           	<unknown>
