000f41c8: c323	movs	r3, #0xc3
000f41ca: 021c	adds	r2, r0, #0
000f41cc: 5b00	lsls	r3, r3, #1
000f41ce: 0020	movs	r0, #0
000f41d0: 9a42	cmp	r2, r3
000f41d2: 09d8	bhi	#0xf41e8
000f41d4: 054b	ldr	r3, [pc, #0x14]
000f41d6: 5200	lsls	r2, r2, #1
000f41d8: 0548	ldr	r0, [pc, #0x14]
000f41da: 7b44	add	r3, pc
000f41dc: 9b18	adds	r3, r3, r2
000f41de: 3422	movs	r2, #0x34
000f41e0: 9b5e	ldrsh	r3, [r3, r2]
000f41e2: 7844	add	r0, pc
000f41e4: 4030	adds	r0, #0x40
000f41e6: c018	adds	r0, r0, r3
000f41e8: 7047	bx	lr
000f41ea: c046	mov	r8, r8
000f41ec: 1635	adds	r5, #0x16
000f41ee: 0500	movs	r5, r0
000f41f0: 8e24	movs	r4, #0x8e
000f41f2: 0500	movs	r5, r0
