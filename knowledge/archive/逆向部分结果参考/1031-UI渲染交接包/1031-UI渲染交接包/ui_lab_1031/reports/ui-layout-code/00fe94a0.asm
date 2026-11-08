
<stdin>:	file format elf32-i386

Disassembly of section .text:

00fe94a0 <.text>:
  fe94a0: f8                           	clc
  fe94a1: 04 75                        	add	al, 0x75
  fe94a3: 05 8d 70 01 eb               	add	eax, 0xeb01708d
  fe94a8: 3f                           	aas
  fe94a9: 83 f8 05                     	cmp	eax, 0x5
  fe94ac: 75 04                        	jne	0xfe94b2 <.text+0x12>
  fe94ae: 8b f0                        	mov	esi, eax
  fe94b0: eb 36                        	jmp	0xfe94e8 <.text+0x48>
  fe94b2: 83 f8 06                     	cmp	eax, 0x6
  fe94b5: 74 2c                        	je	0xfe94e3 <.text+0x43>
  fe94b7: 83 f8 07                     	cmp	eax, 0x7
  fe94ba: 75 04                        	jne	0xfe94c0 <.text+0x20>
  fe94bc: 8b f0                        	mov	esi, eax
  fe94be: eb 28                        	jmp	0xfe94e8 <.text+0x48>
  fe94c0: 83 f8 08                     	cmp	eax, 0x8
  fe94c3: 75 05                        	jne	0xfe94ca <.text+0x2a>
  fe94c5: 8d 70 fc                     	lea	esi, [eax - 0x4]
  fe94c8: eb 1e                        	jmp	0xfe94e8 <.text+0x48>
  fe94ca: 83 f8 09                     	cmp	eax, 0x9
  fe94cd: 75 05                        	jne	0xfe94d4 <.text+0x34>
  fe94cf: 8d 70 fb                     	lea	esi, [eax - 0x5]
  fe94d2: eb 14                        	jmp	0xfe94e8 <.text+0x48>
  fe94d4: 83 f8 0a                     	cmp	eax, 0xa
  fe94d7: 75 05                        	jne	0xfe94de <.text+0x3e>
  fe94d9: 8d 70 fe                     	lea	esi, [eax - 0x2]
  fe94dc: eb 0a                        	jmp	0xfe94e8 <.text+0x48>
  fe94de: 83 f8 0b                     	cmp	eax, 0xb
  fe94e1: 75 05                        	jne	0xfe94e8 <.text+0x48>
  fe94e3: be 06 00 00 00               	mov	esi, 0x6
  fe94e8: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
  fe94eb: 6a 00                        	push	0x0
  fe94ed: 68 5c e6 a3 01               	push	0x1a3e65c
  fe94f2: 68 88 96 9d 01               	push	0x19d9688
  fe94f7: 6a 00                        	push	0x0
  fe94f9: 50                           	push	eax
  fe94fa: e8 81 ed 07 00               	call	0x1068280 <.text+0x7ede0>
  fe94ff: 50                           	push	eax
  fe9500: e8 da e1 3e 00               	call	0x13d76df <.text+0x3ee23f>
  fe9505: 83 c4 14                     	add	esp, 0x14
  fe9508: 85 c0                        	test	eax, eax
  fe950a: 74 08                        	je	0xfe9514 <.text+0x74>
  fe950c: 56                           	push	esi
  fe950d: 8b c8                        	mov	ecx, eax
  fe950f: e8 2c 97 01 00               	call	0x1002c40 <.text+0x197a0>
  fe9514: 5e                           	pop	esi
  fe9515: 5d                           	pop	ebp
  fe9516: c2 08 00                     	ret	0x8
  fe9519: cc                           	int3
  fe951a: cc                           	int3
  fe951b: cc                           	int3
  fe951c: cc                           	int3
  fe951d: cc                           	int3
  fe951e: cc                           	int3
  fe951f: cc                           	int3
  fe9520: 55                           	push	ebp
  fe9521: 8b ec                        	mov	ebp, esp
  fe9523: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
  fe9526: 56                           	push	esi
  fe9527: 33 f6                        	xor	esi, esi
  fe9529: 33 c0                        	xor	eax, eax
  fe952b: 85 d2                        	test	edx, edx
  fe952d: 75 27                        	jne	0xfe9556 <.text+0xb6>
  fe952f: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
  fe9532: 83 fa 18                     	cmp	edx, 0x18
  fe9535: 75 07                        	jne	0xfe953e <.text+0x9e>
  fe9537: b8 ce 00 00 00               	mov	eax, 0xce
  fe953c: eb 20                        	jmp	0xfe955e <.text+0xbe>
  fe953e: 83 fa 19                     	cmp	edx, 0x19
  fe9541: 75 07                        	jne	0xfe954a <.text+0xaa>
  fe9543: b8 32 01 00 00               	mov	eax, 0x132
  fe9548: eb 14                        	jmp	0xfe955e <.text+0xbe>
  fe954a: 83 fa 1a                     	cmp	edx, 0x1a
  fe954d: 75 0f                        	jne	0xfe955e <.text+0xbe>
  fe954f: b8 96 01 00 00               	mov	eax, 0x196
  fe9554: eb 08                        	jmp	0xfe955e <.text+0xbe>
  fe9556: 83 fa 01                     	cmp	edx, 0x1
  fe9559: 75 03                        	jne	0xfe955e <.text+0xbe>
  fe955b: 8d 42 0b                     	lea	eax, [edx + 0xb]
  fe955e: 6a 00                        	push	0x0
