
<stdin>:	file format elf32-i386

Disassembly of section .text:

011e98e0 <.text>:
 11e98e0: 55                           	push	ebp
 11e98e1: 8b ec                        	mov	ebp, esp
 11e98e3: 6a ff                        	push	-0x1
 11e98e5: 68 e8 a2 4c 01               	push	0x14ca2e8
 11e98ea: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11e98f0: 50                           	push	eax
 11e98f1: 51                           	push	ecx
 11e98f2: 56                           	push	esi
 11e98f3: 57                           	push	edi
 11e98f4: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11e98f9: 33 c5                        	xor	eax, ebp
 11e98fb: 50                           	push	eax
 11e98fc: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11e98ff: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11e9905: 8b f9                        	mov	edi, ecx
 11e9907: 89 7d f0                     	mov	dword ptr [ebp - 0x10], edi
 11e990a: e8 71 56 fd ff               	call	0x11bef80
 11e990f: 33 f6                        	xor	esi, esi
 11e9911: 6a 30                        	push	0x30
 11e9913: 89 75 fc                     	mov	dword ptr [ebp - 0x4], esi
 11e9916: c7 07 bc ec 85 01            	mov	dword ptr [edi], 0x185ecbc
 11e991c: e8 f9 d1 1e 00               	call	0x13d6b1a <.text+0x1ed23a>
 11e9921: 83 c4 04                     	add	esp, 0x4
 11e9924: 3b c6                        	cmp	eax, esi
 11e9926: 74 25                        	je	0x11e994d <.text+0x6d>
 11e9928: 89 30                        	mov	dword ptr [eax], esi
 11e992a: 89 70 04                     	mov	dword ptr [eax + 0x4], esi
 11e992d: 89 70 08                     	mov	dword ptr [eax + 0x8], esi
 11e9930: 89 70 0c                     	mov	dword ptr [eax + 0xc], esi
 11e9933: 89 70 10                     	mov	dword ptr [eax + 0x10], esi
 11e9936: 89 70 14                     	mov	dword ptr [eax + 0x14], esi
 11e9939: 89 70 18                     	mov	dword ptr [eax + 0x18], esi
 11e993c: 89 70 1c                     	mov	dword ptr [eax + 0x1c], esi
 11e993f: 89 70 20                     	mov	dword ptr [eax + 0x20], esi
 11e9942: 89 70 24                     	mov	dword ptr [eax + 0x24], esi
 11e9945: 89 70 28                     	mov	dword ptr [eax + 0x28], esi
 11e9948: 89 70 2c                     	mov	dword ptr [eax + 0x2c], esi
 11e994b: eb 02                        	jmp	0x11e994f <.text+0x6f>
 11e994d: 33 c0                        	xor	eax, eax
 11e994f: 89 87 b8 02 00 00            	mov	dword ptr [edi + 0x2b8], eax
 11e9955: c7 47 08 03 00 00 00         	mov	dword ptr [edi + 0x8], 0x3
 11e995c: 8b c7                        	mov	eax, edi
 11e995e: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11e9961: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11e9968: 59                           	pop	ecx
 11e9969: 5f                           	pop	edi
 11e996a: 5e                           	pop	esi
 11e996b: 8b e5                        	mov	esp, ebp
 11e996d: 5d                           	pop	ebp
 11e996e: c3                           	ret
