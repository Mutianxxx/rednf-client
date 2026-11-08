
<stdin>:	file format elf32-i386

Disassembly of section .text:

0111f360 <.text>:
 111f360: 55                           	push	ebp
 111f361: 8b ec                        	mov	ebp, esp
 111f363: 83 ec 30                     	sub	esp, 0x30
 111f366: 53                           	push	ebx
 111f367: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 111f36a: 56                           	push	esi
 111f36b: 57                           	push	edi
 111f36c: 53                           	push	ebx
 111f36d: 8d 45 f0                     	lea	eax, [ebp - 0x10]
 111f370: 50                           	push	eax
 111f371: 8b f9                        	mov	edi, ecx
 111f373: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 111f37a: e8 71 13 2f ff               	call	0x4106f0
 111f37f: 8d 4d d8                     	lea	ecx, [ebp - 0x28]
 111f382: 51                           	push	ecx
 111f383: 8b cf                        	mov	ecx, edi
 111f385: e8 b6 4f 6a ff               	call	0x7c4340
 111f38a: 8b 75 f0                     	mov	esi, dword ptr [ebp - 0x10]
 111f38d: 85 f6                        	test	esi, esi
 111f38f: 0f 84 ae 00 00 00            	je	0x111f443 <.text+0xe3>
 111f395: 8b 16                        	mov	edx, dword ptr [esi]
 111f397: 85 d2                        	test	edx, edx
 111f399: 0f 84 a4 00 00 00            	je	0x111f443 <.text+0xe3>
 111f39f: 8b 08                        	mov	ecx, dword ptr [eax]
 111f3a1: 85 c9                        	test	ecx, ecx
 111f3a3: 74 02                        	je	0x111f3a7 <.text+0x47>
 111f3a5: 8b 09                        	mov	ecx, dword ptr [ecx]
 111f3a7: 3b d1                        	cmp	edx, ecx
 111f3a9: 0f 85 94 00 00 00            	jne	0x111f443 <.text+0xe3>
 111f3af: 8b 55 f8                     	mov	edx, dword ptr [ebp - 0x8]
 111f3b2: 3b 50 08                     	cmp	edx, dword ptr [eax + 0x8]
 111f3b5: 0f 94 c0                     	sete	al
 111f3b8: 84 c0                        	test	al, al
 111f3ba: 75 07                        	jne	0x111f3c3 <.text+0x63>
 111f3bc: 8b 03                        	mov	eax, dword ptr [ebx]
 111f3be: 3b 42 0c                     	cmp	eax, dword ptr [edx + 0xc]
 111f3c1: 7d 6d                        	jge	0x111f430 <.text+0xd0>
 111f3c3: 8b 0b                        	mov	ecx, dword ptr [ebx]
 111f3c5: 83 c8 ff                     	or	eax, -0x1
 111f3c8: 89 45 d0                     	mov	dword ptr [ebp - 0x30], eax
 111f3cb: 89 45 d4                     	mov	dword ptr [ebp - 0x2c], eax
 111f3ce: f3 0f 7e 45 d0               	movq	xmm0, qword ptr [ebp - 0x30]
 111f3d3: 89 45 d8                     	mov	dword ptr [ebp - 0x28], eax
 111f3d6: 89 45 dc                     	mov	dword ptr [ebp - 0x24], eax
 111f3d9: 89 45 f8                     	mov	dword ptr [ebp - 0x8], eax
 111f3dc: 8d 45 e4                     	lea	eax, [ebp - 0x1c]
 111f3df: 50                           	push	eax
 111f3e0: 83 ec 0c                     	sub	esp, 0xc
 111f3e3: 8b c4                        	mov	eax, esp
 111f3e5: 66 0f d6 45 e8               	movq	qword ptr [ebp - 0x18], xmm0
 111f3ea: f3 0f 7e 45 d8               	movq	xmm0, qword ptr [ebp - 0x28]
 111f3ef: 89 4d e4                     	mov	dword ptr [ebp - 0x1c], ecx
 111f3f2: c7 00 00 00 00 00            	mov	dword ptr [eax], 0x0
 111f3f8: c7 40 04 00 00 00 00         	mov	dword ptr [eax + 0x4], 0x0
 111f3ff: 8b 0e                        	mov	ecx, dword ptr [esi]
 111f401: 66 0f d6 45 f0               	movq	qword ptr [ebp - 0x10], xmm0
 111f406: 89 65 08                     	mov	dword ptr [ebp + 0x8], esp
 111f409: 85 c9                        	test	ecx, ecx
 111f40b: 74 04                        	je	0x111f411 <.text+0xb1>
 111f40d: 8b 09                        	mov	ecx, dword ptr [ecx]
 111f40f: 89                           	<unknown>
