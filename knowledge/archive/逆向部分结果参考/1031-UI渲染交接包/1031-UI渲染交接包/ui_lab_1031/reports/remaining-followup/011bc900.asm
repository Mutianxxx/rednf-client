
<stdin>:	file format elf32-i386

Disassembly of section .text:

011bc900 <.text>:
 11bc900: 55                           	push	ebp
 11bc901: 8b ec                        	mov	ebp, esp
 11bc903: 6a ff                        	push	-0x1
 11bc905: 68 03 7c 4c 01               	push	0x14c7c03
 11bc90a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11bc910: 50                           	push	eax
 11bc911: 83 ec 28                     	sub	esp, 0x28
 11bc914: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11bc919: 33 c5                        	xor	eax, ebp
 11bc91b: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 11bc91e: 56                           	push	esi
 11bc91f: 57                           	push	edi
 11bc920: 50                           	push	eax
 11bc921: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11bc924: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11bc92a: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 11bc92d: 68 ac 00 00 00               	push	0xac
 11bc932: 8b f1                        	mov	esi, ecx
 11bc934: e8 47 3a ff ff               	call	0x11b0380
 11bc939: 83 c4 04                     	add	esp, 0x4
 11bc93c: 89 45 cc                     	mov	dword ptr [ebp - 0x34], eax
 11bc93f: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11bc946: 85 c0                        	test	eax, eax
 11bc948: 74 0d                        	je	0x11bc957 <.text+0x57>
 11bc94a: 8b 4e 08                     	mov	ecx, dword ptr [esi + 0x8]
 11bc94d: 51                           	push	ecx
 11bc94e: 8b c8                        	mov	ecx, eax
 11bc950: e8 cb c2 ff ff               	call	0x11b8c20
 11bc955: eb 02                        	jmp	0x11bc959 <.text+0x59>
 11bc957: 33 c0                        	xor	eax, eax
 11bc959: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 11bc960: 89 45 cc                     	mov	dword ptr [ebp - 0x34], eax
 11bc963: 85 c0                        	test	eax, eax
 11bc965: 75 07                        	jne	0x11bc96e <.text+0x6e>
 11bc967: b8 08 00 00 80               	mov	eax, 0x80000008
 11bc96c: eb 65                        	jmp	0x11bc9d3 <.text+0xd3>
 11bc96e: 57                           	push	edi
 11bc96f: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 11bc972: e8 a9 55 25 ff               	call	0x411f20
 11bc977: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 11bc97a: 52                           	push	edx
 11bc97b: 8d 4e 0c                     	lea	ecx, [esi + 0xc]
 11bc97e: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
 11bc985: e8 b6 3d 2a ff               	call	0x460740
 11bc98a: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
 11bc98e: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 11bc995: 72 0c                        	jb	0x11bc9a3 <.text+0xa3>
 11bc997: 8b 45 d4                     	mov	eax, dword ptr [ebp - 0x2c]
 11bc99a: 50                           	push	eax
 11bc99b: e8 87 91 21 00               	call	0x13d5b27 <.text+0x219227>
 11bc9a0: 83 c4 04                     	add	esp, 0x4
 11bc9a3: 8b 55 d0                     	mov	edx, dword ptr [ebp - 0x30]
 11bc9a6: 33 c9                        	xor	ecx, ecx
 11bc9a8: 33 ff                        	xor	edi, edi
 11bc9aa: 52                           	push	edx
 11bc9ab: c7 45 e8 07 00 00 00         	mov	dword ptr [ebp - 0x18], 0x7
 11bc9b2: 89 7d e4                     	mov	dword ptr [ebp - 0x1c], edi
 11bc9b5: 66 89 4d d4                  	mov	word ptr [ebp - 0x2c], cx
 11bc9b9: e8 69 91 21 00               	call	0x13d5b27 <.text+0x219227>
 11bc9be: 83 c4 04                     	add	esp, 0x4
 11bc9c1: 8d 45 cc                     	lea	eax, [ebp - 0x34]
 11bc9c4: 50                           	push	eax
 11bc9c5: 8d 4e 20                     	lea	ecx, [esi + 0x20]
 11bc9c8: 89 7d d0                     	mov	dword ptr [ebp - 0x30], edi
 11bc9cb: e8 a0 6d 2d ff               	call	0x493770
 11bc9d0: 8d 47 01                     	lea	eax, [edi + 0x1]
 11bc9d3: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11bc9d6: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11bc9dd: 59                           	pop	ecx
 11bc9de: 5f                           	pop	edi
 11bc9df: 5e                           	pop	esi
 11bc9e0: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 11bc9e3: 33 cd                        	xor	ecx, ebp
 11bc9e5: e8 ee a7 21 00               	call	0x13d71d8 <.text+0x21a8d8>
 11bc9ea: 8b e5                        	mov	esp, ebp
 11bc9ec: 5d                           	pop	ebp
 11bc9ed: c2 04 00                     	ret	0x4
