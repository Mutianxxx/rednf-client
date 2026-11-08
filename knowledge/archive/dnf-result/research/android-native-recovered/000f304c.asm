000f304c: 70b5	push	{r4, r5, r6, lr}
000f304e: 041c	adds	r4, r0, #0
000f3050: 4068	ldr	r0, [r0, #4]
000f3052: 0e1c	adds	r6, r1, #0
000f3054: 0028	cmp	r0, #0
000f3056: 1dd1	bne	#0xf3094
000f3058: e369	ldr	r3, [r4, #0x1c]
000f305a: 2568	ldr	r5, [r4]
000f305c: 002b	cmp	r3, #0
000f305e: 04d0	beq	#0xf306a
000f3060: 626a	ldr	r2, [r4, #0x24]
000f3062: 013b	subs	r3, #1
000f3064: 1b01	lsls	r3, r3, #4
000f3066: d318	adds	r3, r2, r3
000f3068: d960	str	r1, [r3, #0xc]
000f306a: 201c	adds	r0, r4, #0
000f306c: 2830	adds	r0, #0x28
000f306e: 291c	adds	r1, r5, #0
000f3070: fff71aff	bl	#0xf2ea8
000f3074: 0028	cmp	r0, #0
000f3076: 0dd1	bne	#0xf3094
000f3078: 3434	adds	r4, #0x34
000f307a: e368	ldr	r3, [r4, #0xc]
000f307c: 002b	cmp	r3, #0
000f307e: 04d0	beq	#0xf308a
000f3080: 6269	ldr	r2, [r4, #0x14]
000f3082: 013b	subs	r3, #1
000f3084: 1b01	lsls	r3, r3, #4
000f3086: d318	adds	r3, r2, r3
000f3088: de60	str	r6, [r3, #0xc]
000f308a: 201c	adds	r0, r4, #0
000f308c: 1830	adds	r0, #0x18
000f308e: 291c	adds	r1, r5, #0
000f3090: fff70aff	bl	#0xf2ea8
000f3094: 70bd	pop	{r4, r5, r6, pc}
