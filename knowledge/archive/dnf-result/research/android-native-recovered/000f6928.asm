000f6928: 70b5	push	{r4, r5, r6, lr}
000f692a: 0b68	ldr	r3, [r1]
000f692c: 104a	ldr	r2, [pc, #0x40]
000f692e: 041c	adds	r4, r0, #0
000f6930: 0d1c	adds	r5, r1, #0
000f6932: 0020	movs	r0, #0
000f6934: 9342	cmp	r3, r2
000f6936: 0ad8	bhi	#0xf694e
000f6938: 6269	ldr	r2, [r4, #0x14]
000f693a: d107	lsls	r1, r2, #0x1f
000f693c: 08d4	bmi	#0xf6950
000f693e: a269	ldr	r2, [r4, #0x18]
000f6940: 9342	cmp	r3, r2
000f6942: 0bd0	beq	#0xf695c
000f6944: 201c	adds	r0, r4, #0
000f6946: 291c	adds	r1, r5, #0
000f6948: 0122	movs	r2, #1
000f694a: fff7d1fd	bl	#0xf64f0
000f694e: 70bd	pop	{r4, r5, r6, pc}
000f6950: 201c	adds	r0, r4, #0
000f6952: 291c	adds	r1, r5, #0
000f6954: 0122	movs	r2, #1
000f6956: fff701fd	bl	#0xf635c
000f695a: f8e7	b	#0xf694e
000f695c: 201c	adds	r0, r4, #0
000f695e: fff7b3fc	bl	#0xf62c8
000f6962: e069	ldr	r0, [r4, #0x1c]
000f6964: 0028	cmp	r0, #0
000f6966: f2d0	beq	#0xf694e
000f6968: a369	ldr	r3, [r4, #0x18]
000f696a: 2b60	str	r3, [r5]
000f696c: efe7	b	#0xf694e
000f696e: c046	mov	r8, r8
000f6970: feff	.byte	0xfe, 0xff
000f6972: 0000	movs	r0, r0
