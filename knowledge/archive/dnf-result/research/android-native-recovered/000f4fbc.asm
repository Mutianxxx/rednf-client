000f4fbc: 70b5	push	{r4, r5, r6, lr}
000f4fbe: 0c1c	adds	r4, r1, #0
000f4fc0: 1d1c	adds	r5, r3, #0
000f4fc2: 896c	ldr	r1, [r1, #0x48]
000f4fc4: 8369	ldr	r3, [r0, #0x18]
000f4fc6: 0620	movs	r0, #6
000f4fc8: 9942	cmp	r1, r3
000f4fca: 00d0	beq	#0xf4fce
000f4fcc: 70bd	pop	{r4, r5, r6, pc}
000f4fce: 002a	cmp	r2, #0
000f4fd0: 04d0	beq	#0xf4fdc
000f4fd2: 201c	adds	r0, r4, #0
000f4fd4: 6c30	adds	r0, #0x6c
000f4fd6: 111c	adds	r1, r2, #0
000f4fd8: f2f7f2f9	bl	#0xe73c0
000f4fdc: 0020	movs	r0, #0
000f4fde: 002d	cmp	r5, #0
000f4fe0: f4d0	beq	#0xf4fcc
000f4fe2: 201c	adds	r0, r4, #0
000f4fe4: 6c30	adds	r0, #0x6c
000f4fe6: 2968	ldr	r1, [r5]
000f4fe8: 6a68	ldr	r2, [r5, #4]
000f4fea: f2f771f9	bl	#0xe72d0
000f4fee: 0020	movs	r0, #0
000f4ff0: ece7	b	#0xf4fcc
