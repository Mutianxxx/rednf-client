
<stdin>:	file format elf32-i386

Disassembly of section .text:

01223620 <.text>:
 1223620: 55                           	push	ebp
 1223621: 8b ec                        	mov	ebp, esp
 1223623: 56                           	push	esi
 1223624: 8b 75 0c                     	mov	esi, dword ptr [ebp + 0xc]
 1223627: 85 f6                        	test	esi, esi
 1223629: 75 05                        	jne	0x1223630 <.text+0x10>
 122362b: 32 c0                        	xor	al, al
 122362d: 5e                           	pop	esi
 122362e: 5d                           	pop	ebp
 122362f: c3                           	ret
 1223630: a1 b4 72 d2 01               	mov	eax, dword ptr [0x1d272b4]
 1223635: 85 c0                        	test	eax, eax
 1223637: 74 02                        	je	0x122363b <.text+0x1b>
 1223639: ff d0                        	call	eax
 122363b: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 122363e: 6a 00                        	push	0x0
 1223640: 56                           	push	esi
 1223641: 50                           	push	eax
 1223642: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1223647: e8 74 32 f8 ff               	call	0x11a68c0
 122364c: 5e                           	pop	esi
 122364d: 5d                           	pop	ebp
 122364e: c3                           	ret
 122364f: cc                           	int3
 1223650: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1223655: e9 36 1e f8 ff               	jmp	0x11a5490
 122365a: cc                           	int3
 122365b: cc                           	int3
 122365c: cc                           	int3
 122365d: cc                           	int3
 122365e: cc                           	int3
 122365f: cc                           	int3
 1223660: 55                           	push	ebp
 1223661: 8b ec                        	mov	ebp, esp
 1223663: 56                           	push	esi
 1223664: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1223669: 33 f6                        	xor	esi, esi
 122366b: e8 40 1e f8 ff               	call	0x11a54b0
 1223670: 83 f8 02                     	cmp	eax, 0x2
 1223673: 75 17                        	jne	0x122368c <.text+0x6c>
 1223675: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 122367a: e8 41 1f f8 ff               	call	0x11a55c0
 122367f: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 1223682: 85 c9                        	test	ecx, ecx
 1223684: 74 4f                        	je	0x12236d5 <.text+0xb5>
 1223686: c6 01 01                     	mov	byte ptr [ecx], 0x1
 1223689: 5e                           	pop	esi
 122368a: 5d                           	pop	ebp
 122368b: c3                           	ret
 122368c: 83 f8 03                     	cmp	eax, 0x3
 122368f: 75                           	<unknown>
