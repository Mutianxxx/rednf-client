
<stdin>:	file format elf32-i386

Disassembly of section .text:

013d83e0 <.text>:
 13d83e0: 83 3d ec 46 da 01 00         	cmp	dword ptr [0x1da46ec], 0x0
 13d83e7: 74 2d                        	je	0x13d8416 <.text+0x36>
 13d83e9: 55                           	push	ebp
 13d83ea: 8b ec                        	mov	ebp, esp
 13d83ec: 83 ec 08                     	sub	esp, 0x8
 13d83ef: 83 e4 f8                     	and	esp, -0x8
 13d83f2: dd 1c 24                     	fstp	qword ptr [esp]
 13d83f5: f2 0f 2c 04 24               	cvttsd2si	eax, qword ptr [esp]
 13d83fa: c9                           	leave
 13d83fb: c3                           	ret
 13d83fc: 83 3d ec 46 da 01 00         	cmp	dword ptr [0x1da46ec], 0x0
 13d8403: 74 11                        	je	0x13d8416 <.text+0x36>
 13d8405: 83 ec 04                     	sub	esp, 0x4
 13d8408: d9 3c 24                     	fnstcw	word ptr [esp]
 13d840b: 58                           	pop	eax
 13d840c: 66 83 e0 7f                  	and	ax, 0x7f
 13d8410: 66 83 f8 7f                  	cmp	ax, 0x7f
 13d8414: 74 d3                        	je	0x13d83e9 <.text+0x9>
 13d8416: 55                           	push	ebp
 13d8417: 8b ec                        	mov	ebp, esp
 13d8419: 83 ec 20                     	sub	esp, 0x20
 13d841c: 83 e4 f0                     	and	esp, -0x10
 13d841f: d9 c0                        	fld	st(0)
 13d8421: d9 54 24 18                  	fst	dword ptr [esp + 0x18]
 13d8425: df 7c 24 10                  	fistp	qword ptr [esp + 0x10]
 13d8429: df 6c 24 10                  	fild	qword ptr [esp + 0x10]
 13d842d: 8b 54 24 18                  	mov	edx, dword ptr [esp + 0x18]
 13d8431: 8b 44 24 10                  	mov	eax, dword ptr [esp + 0x10]
 13d8435: 85 c0                        	test	eax, eax
 13d8437: 74 3c                        	je	0x13d8475 <.text+0x95>
 13d8439: de e9                        	fsubp	st(1), st
 13d843b: 85 d2                        	test	edx, edx
 13d843d: 79 1e                        	jns	0x13d845d <.text+0x7d>
 13d843f: d9 1c 24                     	fstp	dword ptr [esp]
 13d8442: 8b 0c 24                     	mov	ecx, dword ptr [esp]
 13d8445: 81 f1 00 00 00 80            	xor	ecx, 0x80000000
 13d844b: 81 c1 ff ff ff 7f            	add	ecx, 0x7fffffff
 13d8451: 83 d0 00                     	adc	eax, 0x0
 13d8454: 8b 54 24 14                  	mov	edx, dword ptr [esp + 0x14]
 13d8458: 83 d2 00                     	adc	edx, 0x0
 13d845b: eb 2c                        	jmp	0x13d8489 <.text+0xa9>
 13d845d: d9 1c 24                     	fstp	dword ptr [esp]
 13d8460: 8b 0c 24                     	mov	ecx, dword ptr [esp]
 13d8463: 81 c1 ff ff ff 7f            	add	ecx, 0x7fffffff
 13d8469: 83 d8 00                     	sbb	eax, 0x0
 13d846c: 8b 54 24 14                  	mov	edx, dword ptr [esp + 0x14]
 13d8470: 83 da 00                     	sbb	edx, 0x0
 13d8473: eb 14                        	jmp	0x13d8489 <.text+0xa9>
 13d8475: 8b 54 24 14                  	mov	edx, dword ptr [esp + 0x14]
 13d8479: f7 c2 ff ff ff 7f            	test	edx, 0x7fffffff
 13d847f: 75 b8                        	jne	0x13d8439 <.text+0x59>
 13d8481: d9 5c 24 18                  	fstp	dword ptr [esp + 0x18]
 13d8485: d9 5c 24 18                  	fstp	dword ptr [esp + 0x18]
 13d8489: c9                           	leave
 13d848a: c3                           	ret
 13d848b: 66 0f c5 c0                  	<unknown>
