000f2844: f0b5	push	{r4, r5, r6, r7, lr}
000f2846: 5f46	mov	r7, fp
000f2848: 5646	mov	r6, sl
000f284a: 4d46	mov	r5, sb
000f284c: 4446	mov	r4, r8
000f284e: f0b4	push	{r4, r5, r6, r7}
000f2850: 87b0	sub	sp, #0x1c
000f2852: 071c	adds	r7, r0, #0
000f2854: 1098	ldr	r0, [sp, #0x40]
000f2856: 9046	mov	r8, r2
000f2858: 9a46	mov	sl, r3
000f285a: 0022	movs	r2, #0
000f285c: 4346	mov	r3, r8
000f285e: 0e1c	adds	r6, r1, #0
000f2860: 8146	mov	sb, r0
000f2862: 9346	mov	fp, r2
000f2864: 002b	cmp	r3, #0
000f2866: 5edb	blt	#0xf2926
000f2868: 4b46	mov	r3, sb
000f286a: 002b	cmp	r3, #0
000f286c: 03d0	beq	#0xf2876
000f286e: 0123	movs	r3, #1
000f2870: 5b42	rsbs	r3, r3, #0
000f2872: 4846	mov	r0, sb
000f2874: 0360	str	r3, [r0]
000f2876: bb68	ldr	r3, [r7, #8]
000f2878: 3d68	ldr	r5, [r7]
000f287a: 191c	adds	r1, r3, #0
000f287c: 002d	cmp	r5, #0
000f287e: 00d1	bne	#0xf2882
000f2880: 74e0	b	#0xf296c
000f2882: 1a1c	adds	r2, r3, #0
000f2884: 9c46	mov	ip, r3
000f2886: 0024	movs	r4, #0
000f2888: 4346	mov	r3, r8
000f288a: 03e0	b	#0xf2894
000f288c: 0134	adds	r4, #1
000f288e: ac42	cmp	r4, r5
000f2890: 24d0	beq	#0xf28dc
000f2892: 0c32	adds	r2, #0xc
000f2894: 1068	ldr	r0, [r2]
000f2896: b042	cmp	r0, r6
000f2898: f8d1	bne	#0xf288c
000f289a: 5068	ldr	r0, [r2, #4]
000f289c: 9842	cmp	r0, r3
000f289e: f5d1	bne	#0xf288c
000f28a0: 9846	mov	r8, r3
000f28a2: 6346	mov	r3, ip
000f28a4: a542	cmp	r5, r4
000f28a6: 1bd9	bls	#0xf28e0
000f28a8: fb68	ldr	r3, [r7, #0xc]
000f28aa: 002b	cmp	r3, #0
000f28ac: 31d0	beq	#0xf2912
000f28ae: 7a69	ldr	r2, [r7, #0x14]
000f28b0: 013b	subs	r3, #1
000f28b2: 1b01	lsls	r3, r3, #4
000f28b4: d318	adds	r3, r2, r3
000f28b6: 0593	str	r3, [sp, #0x14]
000f28b8: 181c	adds	r0, r3, #0
000f28ba: 211c	adds	r1, r4, #0
000f28bc: 5246	mov	r2, sl
000f28be: fff7a1ff	bl	#0xf2804
000f28c2: 0028	cmp	r0, #0
000f28c4: 03d1	bne	#0xf28ce
000f28c6: 4b46	mov	r3, sb
000f28c8: 002b	cmp	r3, #0
000f28ca: 00d0	beq	#0xf28ce
000f28cc: 1c60	str	r4, [r3]
000f28ce: 07b0	add	sp, #0x1c
000f28d0: 3cbc	pop	{r2, r3, r4, r5}
000f28d2: 9046	mov	r8, r2
000f28d4: 9946	mov	sb, r3
000f28d6: a246	mov	sl, r4
000f28d8: ab46	mov	fp, r5
000f28da: f0bd	pop	{r4, r5, r6, r7, pc}
000f28dc: 9846	mov	r8, r3
000f28de: 6346	mov	r3, ip
000f28e0: 6a1c	adds	r2, r5, #1
000f28e2: 0292	str	r2, [sp, #8]
000f28e4: 7a68	ldr	r2, [r7, #4]
000f28e6: 0298	ldr	r0, [sp, #8]
000f28e8: 9042	cmp	r0, r2
000f28ea: 04d3	blo	#0xf28f6
000f28ec: 0021	movs	r1, #0
000f28ee: 0591	str	r1, [sp, #0x14]
000f28f0: 191c	adds	r1, r3, #0
000f28f2: 9042	cmp	r0, r2
000f28f4: 25d8	bhi	#0xf2942
000f28f6: 6b00	lsls	r3, r5, #1
000f28f8: 5d19	adds	r5, r3, r5
000f28fa: 029b	ldr	r3, [sp, #8]
000f28fc: ad00	lsls	r5, r5, #2
000f28fe: 4919	adds	r1, r1, r5
000f2900: 4046	mov	r0, r8
000f2902: 5a46	mov	r2, fp
000f2904: 3b60	str	r3, [r7]
000f2906: 0e60	str	r6, [r1]
000f2908: 4860	str	r0, [r1, #4]
000f290a: 8a60	str	r2, [r1, #8]
000f290c: fb68	ldr	r3, [r7, #0xc]
000f290e: 002b	cmp	r3, #0
000f2910: cdd1	bne	#0xf28ae
000f2912: 381c	adds	r0, r7, #0
000f2914: 0c30	adds	r0, #0xc
000f2916: 5146	mov	r1, sl
000f2918: 05aa	add	r2, sp, #0x14
000f291a: fff7edfe	bl	#0xf26f8
000f291e: 059b	ldr	r3, [sp, #0x14]
000f2920: 0028	cmp	r0, #0
000f2922: d4d1	bne	#0xf28ce
000f2924: c8e7	b	#0xf28b8
000f2926: 4046	mov	r0, r8
000f2928: 1530	adds	r0, #0x15
000f292a: 04d0	beq	#0xf2936
000f292c: 0122	movs	r2, #1
000f292e: 0023	movs	r3, #0
000f2930: 9346	mov	fp, r2
000f2932: 9846	mov	r8, r3
000f2934: 98e7	b	#0xf2868
000f2936: 0320	movs	r0, #3
000f2938: 0022	movs	r2, #0
000f293a: 153e	subs	r6, #0x15
000f293c: 8346	mov	fp, r0
000f293e: 9046	mov	r8, r2
000f2940: 92e7	b	#0xf2868
000f2942: 291c	adds	r1, r5, #0
000f2944: 0720	movs	r0, #7
000f2946: 0831	adds	r1, #8
000f2948: 8143	bics	r1, r0
000f294a: 0391	str	r1, [sp, #0xc]
000f294c: 0093	str	r3, [sp]
000f294e: 05ab	add	r3, sp, #0x14
000f2950: 0193	str	r3, [sp, #4]
000f2952: 0c21	movs	r1, #0xc
000f2954: 5046	mov	r0, sl
000f2956: 039b	ldr	r3, [sp, #0xc]
000f2958: f6f7b6fc	bl	#0xe92c8
000f295c: b860	str	r0, [r7, #8]
000f295e: 011c	adds	r1, r0, #0
000f2960: 0598	ldr	r0, [sp, #0x14]
000f2962: 0028	cmp	r0, #0
000f2964: b3d1	bne	#0xf28ce
000f2966: 039a	ldr	r2, [sp, #0xc]
000f2968: 7a60	str	r2, [r7, #4]
000f296a: c4e7	b	#0xf28f6
000f296c: 0024	movs	r4, #0
000f296e: b7e7	b	#0xf28e0
