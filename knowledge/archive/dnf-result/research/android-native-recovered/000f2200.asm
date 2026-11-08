000f2200: f0b5	push	{r4, r5, r6, r7, lr}
000f2202: 5f46	mov	r7, fp
000f2204: 5646	mov	r6, sl
000f2206: 4d46	mov	r5, sb
000f2208: 4446	mov	r4, r8
000f220a: f0b4	push	{r4, r5, r6, r7}
000f220c: 151c	adds	r5, r2, #0
000f220e: cc22	movs	r2, #0xcc
000f2210: 9846	mov	r8, r3
000f2212: 131c	adds	r3, r2, #0
000f2214: 6b43	muls	r3, r5, r3
000f2216: 89b0	sub	sp, #0x24
000f2218: cb18	adds	r3, r1, r3
000f221a: 1a1c	adds	r2, r3, #0
000f221c: cc33	adds	r3, #0xcc
000f221e: 1b68	ldr	r3, [r3]
000f2220: c832	adds	r2, #0xc8
000f2222: 041c	adds	r4, r0, #0
000f2224: 9946	mov	sb, r3
000f2226: 0369	ldr	r3, [r0, #0x10]
000f2228: 0e1c	adds	r6, r1, #0
000f222a: 1768	ldr	r7, [r2]
000f222c: 1807	lsls	r0, r3, #0x1c
000f222e: 06d5	bpl	#0xf223e
000f2230: 09b0	add	sp, #0x24
000f2232: 3cbc	pop	{r2, r3, r4, r5}
000f2234: 9046	mov	r8, r2
000f2236: 9946	mov	sb, r3
000f2238: a246	mov	sl, r4
000f223a: ab46	mov	fp, r5
000f223c: f0bd	pop	{r4, r5, r6, r7, pc}
000f223e: 391c	adds	r1, r7, #0
000f2240: 2068	ldr	r0, [r4]
000f2242: f3f7bffe	bl	#0xe5fc4
000f2246: 391c	adds	r1, r7, #0
000f2248: 8346	mov	fp, r0
000f224a: 6068	ldr	r0, [r4, #4]
000f224c: f3f7bafe	bl	#0xe5fc4
000f2250: cb44	add	fp, sb
000f2252: 8246	mov	sl, r0
000f2254: 002d	cmp	r5, #0
000f2256: 00d1	bne	#0xf225a
000f2258: 89e0	b	#0xf236e
000f225a: 012d	cmp	r5, #1
000f225c: 00d1	bne	#0xf2260
000f225e: 9fe0	b	#0xf23a0
000f2260: 0021	movs	r1, #0
000f2262: e060	str	r0, [r4, #0xc]
000f2264: 0591	str	r1, [sp, #0x14]
000f2266: 0020	movs	r0, #0
000f2268: 0390	str	r0, [sp, #0xc]
000f226a: 0690	str	r0, [sp, #0x18]
000f226c: 6069	ldr	r0, [r4, #0x14]
000f226e: 8146	mov	sb, r0
000f2270: 0028	cmp	r0, #0
000f2272: 1ed0	beq	#0xf22b2
000f2274: 0369	ldr	r3, [r0, #0x10]
000f2276: 1907	lsls	r1, r3, #0x1c
000f2278: 00d4	bmi	#0xf227c
000f227a: 36e1	b	#0xf24ea
000f227c: 4a46	mov	r2, sb
000f227e: 9268	ldr	r2, [r2, #8]
000f2280: 4846	mov	r0, sb
000f2282: 391c	adds	r1, r7, #0
000f2284: 0492	str	r2, [sp, #0x10]
000f2286: c368	ldr	r3, [r0, #0xc]
000f2288: 6268	ldr	r2, [r4, #4]
000f228a: 5b10	asrs	r3, r3, #1
000f228c: 9b46	mov	fp, r3
000f228e: 0368	ldr	r3, [r0]
000f2290: 5210	asrs	r2, r2, #1
000f2292: 4068	ldr	r0, [r0, #4]
000f2294: d21a	subs	r2, r2, r3
000f2296: 2368	ldr	r3, [r4]
000f2298: 4010	asrs	r0, r0, #1
000f229a: d318	adds	r3, r2, r3
000f229c: 181a	subs	r0, r3, r0
000f229e: f3f791fe	bl	#0xe5fc4
000f22a2: 0499	ldr	r1, [sp, #0x10]
000f22a4: 0a1c	adds	r2, r1, #0
000f22a6: 5146	mov	r1, sl
000f22a8: 5a44	add	r2, fp
000f22aa: 4b10	asrs	r3, r1, #1
000f22ac: d31a	subs	r3, r2, r3
000f22ae: 1b18	adds	r3, r3, r0
000f22b0: 9b46	mov	fp, r3
000f22b2: 5a46	mov	r2, fp
000f22b4: 5346	mov	r3, sl
000f22b6: e360	str	r3, [r4, #0xc]
000f22b8: a260	str	r2, [r4, #8]
000f22ba: 7c23	movs	r3, #0x7c
000f22bc: 4046	mov	r0, r8
000f22be: c25c	ldrb	r2, [r0, r3]
000f22c0: 5346	mov	r3, sl
000f22c2: 002a	cmp	r2, #0
000f22c4: 17d0	beq	#0xf22f6
000f22c6: 5146	mov	r1, sl
000f22c8: 4029	cmp	r1, #0x40
000f22ca: 00dc	bgt	#0xf22ce
000f22cc: 21e1	b	#0xf2512
000f22ce: cc22	movs	r2, #0xcc
000f22d0: 131c	adds	r3, r2, #0
000f22d2: 6b43	muls	r3, r5, r3
000f22d4: f618	adds	r6, r6, r3
000f22d6: f368	ldr	r3, [r6, #0xc]
000f22d8: 5646	mov	r6, sl
000f22da: f21a	subs	r2, r6, r3
000f22dc: d017	asrs	r0, r2, #0x1f
000f22de: 1218	adds	r2, r2, r0
000f22e0: 4240	eors	r2, r0
000f22e2: 272a	cmp	r2, #0x27
000f22e4: 00dc	bgt	#0xf22e8
000f22e6: 5ee1	b	#0xf25a6
000f22e8: 5346	mov	r3, sl
000f22ea: bf2b	cmp	r3, #0xbf
000f22ec: 00dc	bgt	#0xf22f0
000f22ee: 6be1	b	#0xf25c8
000f22f0: 2033	adds	r3, #0x20
000f22f2: 3f22	movs	r2, #0x3f
000f22f4: 9343	bics	r3, r2
000f22f6: 5e46	mov	r6, fp
000f22f8: f018	adds	r0, r6, r3
000f22fa: 5a46	mov	r2, fp
000f22fc: 3f21	movs	r1, #0x3f
000f22fe: 2032	adds	r2, #0x20
000f2300: 2030	adds	r0, #0x20
000f2302: 8a43	bics	r2, r1
000f2304: 8843	bics	r0, r1
000f2306: 921b	subs	r2, r2, r6
000f2308: 811b	subs	r1, r0, r6
000f230a: c91a	subs	r1, r1, r3
000f230c: d017	asrs	r0, r2, #0x1f
000f230e: 1518	adds	r5, r2, r0
000f2310: ce17	asrs	r6, r1, #0x1f
000f2312: 4540	eors	r5, r0
000f2314: 8819	adds	r0, r1, r6
000f2316: 7040	eors	r0, r6
000f2318: 8542	cmp	r5, r0
000f231a: 00dd	ble	#0xf231e
000f231c: d8e0	b	#0xf24d0
000f231e: 5a44	add	r2, fp
000f2320: a260	str	r2, [r4, #8]
000f2322: e360	str	r3, [r4, #0xc]
000f2324: 0598	ldr	r0, [sp, #0x14]
000f2326: 0028	cmp	r0, #0
000f2328: 1cd0	beq	#0xf2364
000f232a: e268	ldr	r2, [r4, #0xc]
000f232c: a168	ldr	r1, [r4, #8]
000f232e: 4023	movs	r3, #0x40
000f2330: 3f2a	cmp	r2, #0x3f
000f2332: 03dd	ble	#0xf233c
000f2334: 131c	adds	r3, r2, #0
000f2336: 2033	adds	r3, #0x20
000f2338: 3f22	movs	r2, #0x3f
000f233a: 9343	bics	r3, r2
000f233c: 039a	ldr	r2, [sp, #0xc]
000f233e: 022a	cmp	r2, #2
000f2340: 00d1	bne	#0xf2344
000f2342: e4e0	b	#0xf250e
000f2344: 032a	cmp	r2, #3
000f2346: 0dd0	beq	#0xf2364
000f2348: 012a	cmp	r2, #1
000f234a: 00d1	bne	#0xf234e
000f234c: dae0	b	#0xf2504
000f234e: e360	str	r3, [r4, #0xc]
000f2350: 5e06	lsls	r6, r3, #0x19
000f2352: 00d5	bpl	#0xf2356
000f2354: c3e0	b	#0xf24de
000f2356: 5b10	asrs	r3, r3, #1
000f2358: 2031	adds	r1, #0x20
000f235a: c918	adds	r1, r1, r3
000f235c: 3f22	movs	r2, #0x3f
000f235e: 9143	bics	r1, r2
000f2360: cb1a	subs	r3, r1, r3
000f2362: a360	str	r3, [r4, #8]
000f2364: 2269	ldr	r2, [r4, #0x10]
000f2366: 0823	movs	r3, #8
000f2368: 1343	orrs	r3, r2
000f236a: 2361	str	r3, [r4, #0x10]
000f236c: 60e7	b	#0xf2230
000f236e: 7823	movs	r3, #0x78
000f2370: 4246	mov	r2, r8
000f2372: d35c	ldrb	r3, [r2, r3]
000f2374: 002b	cmp	r3, #0
000f2376: 0ad0	beq	#0xf238e
000f2378: 7a23	movs	r3, #0x7a
000f237a: 4046	mov	r0, r8
000f237c: c35c	ldrb	r3, [r0, r3]
000f237e: 002b	cmp	r3, #0
000f2380: 00d1	bne	#0xf2384
000f2382: a0e0	b	#0xf24c6
000f2384: 5246	mov	r2, sl
000f2386: 0123	movs	r3, #1
000f2388: e260	str	r2, [r4, #0xc]
000f238a: 0593	str	r3, [sp, #0x14]
000f238c: 6be7	b	#0xf2266
000f238e: 5246	mov	r2, sl
000f2390: e260	str	r2, [r4, #0xc]
000f2392: 2269	ldr	r2, [r4, #0x10]
000f2394: 0823	movs	r3, #8
000f2396: 5946	mov	r1, fp
000f2398: 1343	orrs	r3, r2
000f239a: a160	str	r1, [r4, #8]
000f239c: 2361	str	r3, [r4, #0x10]
000f239e: 47e7	b	#0xf2230
000f23a0: 7923	movs	r3, #0x79
000f23a2: 4046	mov	r0, r8
000f23a4: c35c	ldrb	r3, [r0, r3]
000f23a6: 002b	cmp	r3, #0
000f23a8: f1d0	beq	#0xf238e
000f23aa: 7b23	movs	r3, #0x7b
000f23ac: 4146	mov	r1, r8
000f23ae: cb5c	ldrb	r3, [r1, r3]
000f23b0: 002b	cmp	r3, #0
000f23b2: 00d0	beq	#0xf23b6
000f23b4: 8ee0	b	#0xf24d4
000f23b6: 5246	mov	r2, sl
000f23b8: 0023	movs	r3, #0
000f23ba: e260	str	r2, [r4, #0xc]
000f23bc: 0593	str	r3, [sp, #0x14]
000f23be: 8b4b	ldr	r3, [pc, #0x22c]
000f23c0: 2168	ldr	r1, [r4]
000f23c2: 6068	ldr	r0, [r4, #4]
000f23c4: f35c	ldrb	r3, [r6, r3]
000f23c6: 0793	str	r3, [sp, #0x1c]
000f23c8: ce23	movs	r3, #0xce
000f23ca: 5b00	lsls	r3, r3, #1
000f23cc: f258	ldr	r2, [r6, r3]
000f23ce: 002a	cmp	r2, #0
000f23d0: 31d0	beq	#0xf2436
000f23d2: d623	movs	r3, #0xd6
000f23d4: 5b00	lsls	r3, r3, #1
000f23d6: f358	ldr	r3, [r6, r3]
000f23d8: 4018	adds	r0, r0, r1
000f23da: c31a	subs	r3, r0, r3
000f23dc: 9c46	mov	ip, r3
000f23de: 844b	ldr	r3, [pc, #0x210]
000f23e0: f358	ldr	r3, [r6, r3]
000f23e2: 0393	str	r3, [sp, #0xc]
000f23e4: 5b42	rsbs	r3, r3, #0
000f23e6: 0493	str	r3, [sp, #0x10]
000f23e8: 9c45	cmp	ip, r3
000f23ea: 24db	blt	#0xf2436
000f23ec: d023	movs	r3, #0xd0
000f23ee: 5b00	lsls	r3, r3, #1
000f23f0: f318	adds	r3, r6, r3
000f23f2: 0693	str	r3, [sp, #0x18]
000f23f4: d423	movs	r3, #0xd4
000f23f6: 5b00	lsls	r3, r3, #1
000f23f8: f358	ldr	r3, [r6, r3]
000f23fa: 9946	mov	sb, r3
000f23fc: 039b	ldr	r3, [sp, #0xc]
000f23fe: 9944	add	sb, r3
000f2400: 4845	cmp	r0, sb
000f2402: 00dc	bgt	#0xf2406
000f2404: a6e0	b	#0xf2554
000f2406: 8c46	mov	ip, r1
000f2408: 069b	ldr	r3, [sp, #0x18]
000f240a: 011c	adds	r1, r0, #0
000f240c: a146	mov	sb, r4
000f240e: 0195	str	r5, [sp, #4]
000f2410: 0be0	b	#0xf242a
000f2412: 2033	adds	r3, #0x20
000f2414: d868	ldr	r0, [r3, #0xc]
000f2416: 049c	ldr	r4, [sp, #0x10]
000f2418: 081a	subs	r0, r1, r0
000f241a: a042	cmp	r0, r4
000f241c: 08db	blt	#0xf2430
000f241e: 9c68	ldr	r4, [r3, #8]
000f2420: 039d	ldr	r5, [sp, #0xc]
000f2422: 2c19	adds	r4, r5, r4
000f2424: a142	cmp	r1, r4
000f2426: 00dc	bgt	#0xf242a
000f2428: 8fe0	b	#0xf254a
000f242a: 013a	subs	r2, #1
000f242c: 002a	cmp	r2, #0
000f242e: f0d1	bne	#0xf2412
000f2430: 019d	ldr	r5, [sp, #4]
000f2432: 6146	mov	r1, ip
000f2434: 4c46	mov	r4, sb
000f2436: 0020	movs	r0, #0
000f2438: 0390	str	r0, [sp, #0xc]
000f243a: 0690	str	r0, [sp, #0x18]
000f243c: e823	movs	r3, #0xe8
000f243e: 9b00	lsls	r3, r3, #2
000f2440: f258	ldr	r2, [r6, r3]
000f2442: 002a	cmp	r2, #0
000f2444: 31d0	beq	#0xf24aa
000f2446: 131c	adds	r3, r2, #0
000f2448: 1c33	adds	r3, #0x1c
000f244a: 5b01	lsls	r3, r3, #5
000f244c: 9b19	adds	r3, r3, r6
000f244e: d868	ldr	r0, [r3, #0xc]
000f2450: 9c46	mov	ip, r3
000f2452: 674b	ldr	r3, [pc, #0x19c]
000f2454: 401a	subs	r0, r0, r1
000f2456: 0190	str	r0, [sp, #4]
000f2458: f358	ldr	r3, [r6, r3]
000f245a: 9946	mov	sb, r3
000f245c: 5b42	rsbs	r3, r3, #0
000f245e: 0493	str	r3, [sp, #0x10]
000f2460: 9842	cmp	r0, r3
000f2462: 22db	blt	#0xf24aa
000f2464: 5301	lsls	r3, r2, #5
000f2466: f018	adds	r0, r6, r3
000f2468: e123	movs	r3, #0xe1
000f246a: 9b00	lsls	r3, r3, #2
000f246c: c318	adds	r3, r0, r3
000f246e: 0093	str	r3, [sp]
000f2470: 6046	mov	r0, ip
000f2472: 0069	ldr	r0, [r0, #0x10]
000f2474: 031c	adds	r3, r0, #0
000f2476: 4846	mov	r0, sb
000f2478: 1b1a	subs	r3, r3, r0
000f247a: 9c46	mov	ip, r3
000f247c: 6145	cmp	r1, ip
000f247e: 55da	bge	#0xf252c
000f2480: 281c	adds	r0, r5, #0
000f2482: 009b	ldr	r3, [sp]
000f2484: 4d46	mov	r5, sb
000f2486: a446	mov	ip, r4
000f2488: 8146	mov	sb, r0
000f248a: 09e0	b	#0xf24a0
000f248c: 203b	subs	r3, #0x20
000f248e: 9868	ldr	r0, [r3, #8]
000f2490: 049c	ldr	r4, [sp, #0x10]
000f2492: 401a	subs	r0, r0, r1
000f2494: a042	cmp	r0, r4
000f2496: 06db	blt	#0xf24a6
000f2498: dc68	ldr	r4, [r3, #0xc]
000f249a: 641b	subs	r4, r4, r5
000f249c: a142	cmp	r1, r4
000f249e: 41da	bge	#0xf2524
000f24a0: 013a	subs	r2, #1
000f24a2: 002a	cmp	r2, #0
000f24a4: f2d1	bne	#0xf248c
000f24a6: 6446	mov	r4, ip
000f24a8: 4d46	mov	r5, sb
000f24aa: 0023	movs	r3, #0
000f24ac: 0399	ldr	r1, [sp, #0xc]
000f24ae: 0229	cmp	r1, #2
000f24b0: 21d0	beq	#0xf24f6
000f24b2: 0329	cmp	r1, #3
000f24b4: 21d0	beq	#0xf24fa
000f24b6: 0129	cmp	r1, #1
000f24b8: 00d0	beq	#0xf24bc
000f24ba: d7e6	b	#0xf226c
000f24bc: 069a	ldr	r2, [sp, #0x18]
000f24be: 5546	mov	r5, sl
000f24c0: 531b	subs	r3, r2, r5
000f24c2: a360	str	r3, [r4, #8]
000f24c4: 2ee7	b	#0xf2324
000f24c6: 5246	mov	r2, sl
000f24c8: 0023	movs	r3, #0
000f24ca: e260	str	r2, [r4, #0xc]
000f24cc: 0593	str	r3, [sp, #0x14]
000f24ce: cae6	b	#0xf2266
000f24d0: 0a1c	adds	r2, r1, #0
000f24d2: 24e7	b	#0xf231e
000f24d4: 5046	mov	r0, sl
000f24d6: 0121	movs	r1, #1
000f24d8: e060	str	r0, [r4, #0xc]
000f24da: 0591	str	r1, [sp, #0x14]
000f24dc: 6fe7	b	#0xf23be
000f24de: 5b10	asrs	r3, r3, #1
000f24e0: 5918	adds	r1, r3, r1
000f24e2: 3f22	movs	r2, #0x3f
000f24e4: 9143	bics	r1, r2
000f24e6: 2031	adds	r1, #0x20
000f24e8: 3ae7	b	#0xf2360
000f24ea: 311c	adds	r1, r6, #0
000f24ec: 2a1c	adds	r2, r5, #0
000f24ee: 4346	mov	r3, r8
000f24f0: fff786fe	bl	#0xf2200
000f24f4: c2e6	b	#0xf227c
000f24f6: a360	str	r3, [r4, #8]
000f24f8: 14e7	b	#0xf2324
000f24fa: a360	str	r3, [r4, #8]
000f24fc: 069e	ldr	r6, [sp, #0x18]
000f24fe: f31a	subs	r3, r6, r3
000f2500: e360	str	r3, [r4, #0xc]
000f2502: 0fe7	b	#0xf2324
000f2504: 069d	ldr	r5, [sp, #0x18]
000f2506: e360	str	r3, [r4, #0xc]
000f2508: ea1a	subs	r2, r5, r3
000f250a: a260	str	r2, [r4, #8]
000f250c: 2ae7	b	#0xf2364
000f250e: e360	str	r3, [r4, #0xc]
000f2510: 28e7	b	#0xf2364
000f2512: 1f29	cmp	r1, #0x1f
000f2514: 2cdd	ble	#0xf2570
000f2516: 4b10	asrs	r3, r1, #1
000f2518: 5b44	add	r3, fp
000f251a: 3f22	movs	r2, #0x3f
000f251c: 9343	bics	r3, r2
000f251e: 9b46	mov	fp, r3
000f2520: 4023	movs	r3, #0x40
000f2522: e8e6	b	#0xf22f6
000f2524: 0190	str	r0, [sp, #4]
000f2526: 0093	str	r3, [sp]
000f2528: 6446	mov	r4, ip
000f252a: 4d46	mov	r5, sb
000f252c: 0798	ldr	r0, [sp, #0x1c]
000f252e: 0028	cmp	r0, #0
000f2530: 04d1	bne	#0xf253c
000f2532: 304a	ldr	r2, [pc, #0xc0]
000f2534: 0199	ldr	r1, [sp, #4]
000f2536: b258	ldr	r2, [r6, r2]
000f2538: 9142	cmp	r1, r2
000f253a: b6da	bge	#0xf24aa
000f253c: 039b	ldr	r3, [sp, #0xc]
000f253e: 0222	movs	r2, #2
000f2540: 0098	ldr	r0, [sp]
000f2542: 1343	orrs	r3, r2
000f2544: 0393	str	r3, [sp, #0xc]
000f2546: 0369	ldr	r3, [r0, #0x10]
000f2548: b0e7	b	#0xf24ac
000f254a: 019d	ldr	r5, [sp, #4]
000f254c: 6146	mov	r1, ip
000f254e: 0693	str	r3, [sp, #0x18]
000f2550: 8446	mov	ip, r0
000f2552: 4c46	mov	r4, sb
000f2554: 0798	ldr	r0, [sp, #0x1c]
000f2556: 0028	cmp	r0, #0
000f2558: 04d1	bne	#0xf2564
000f255a: 264a	ldr	r2, [pc, #0x98]
000f255c: b258	ldr	r2, [r6, r2]
000f255e: 9445	cmp	ip, r2
000f2560: 00dd	ble	#0xf2564
000f2562: 68e7	b	#0xf2436
000f2564: 069a	ldr	r2, [sp, #0x18]
000f2566: 0123	movs	r3, #1
000f2568: 1269	ldr	r2, [r2, #0x10]
000f256a: 0393	str	r3, [sp, #0xc]
000f256c: 0692	str	r2, [sp, #0x18]
000f256e: 65e7	b	#0xf243c
000f2570: 5246	mov	r2, sl
000f2572: 002a	cmp	r2, #0
000f2574: 21dd	ble	#0xf25ba
000f2576: 5b46	mov	r3, fp
000f2578: 5344	add	r3, sl
000f257a: 181c	adds	r0, r3, #0
000f257c: 3f22	movs	r2, #0x3f
000f257e: 5946	mov	r1, fp
000f2580: 2030	adds	r0, #0x20
000f2582: 9043	bics	r0, r2
000f2584: 2031	adds	r1, #0x20
000f2586: 9143	bics	r1, r2
000f2588: 5d46	mov	r5, fp
000f258a: 021c	adds	r2, r0, #0
000f258c: d31a	subs	r3, r2, r3
000f258e: 481b	subs	r0, r1, r5
000f2590: c617	asrs	r6, r0, #0x1f
000f2592: dd17	asrs	r5, r3, #0x1f
000f2594: 8019	adds	r0, r0, r6
000f2596: 5b19	adds	r3, r3, r5
000f2598: 7040	eors	r0, r6
000f259a: 6b40	eors	r3, r5
000f259c: 9842	cmp	r0, r3
000f259e: 09dd	ble	#0xf25b4
000f25a0: 5346	mov	r3, sl
000f25a2: 9346	mov	fp, r2
000f25a4: a7e6	b	#0xf22f6
000f25a6: 0022	movs	r2, #0
000f25a8: 2f2b	cmp	r3, #0x2f
000f25aa: 00dd	ble	#0xf25ae
000f25ac: 9de6	b	#0xf22ea
000f25ae: 131c	adds	r3, r2, #0
000f25b0: 3633	adds	r3, #0x36
000f25b2: a0e6	b	#0xf22f6
000f25b4: 5346	mov	r3, sl
000f25b6: 8b46	mov	fp, r1
000f25b8: 9de6	b	#0xf22f6
000f25ba: 5b46	mov	r3, fp
000f25bc: 2033	adds	r3, #0x20
000f25be: 3f22	movs	r2, #0x3f
000f25c0: 9343	bics	r3, r2
000f25c2: 9b46	mov	fp, r3
000f25c4: 5346	mov	r3, sl
000f25c6: 96e6	b	#0xf22f6
000f25c8: 3f22	movs	r2, #0x3f
000f25ca: 191c	adds	r1, r3, #0
000f25cc: 1140	ands	r1, r2
000f25ce: 0929	cmp	r1, #9
000f25d0: 00dc	bgt	#0xf25d4
000f25d2: 90e6	b	#0xf22f6
000f25d4: 1d1c	adds	r5, r3, #0
000f25d6: 9543	bics	r5, r2
000f25d8: 2a1c	adds	r2, r5, #0
000f25da: 1f29	cmp	r1, #0x1f
000f25dc: 02dc	bgt	#0xf25e4
000f25de: 2b1c	adds	r3, r5, #0
000f25e0: 0a33	adds	r3, #0xa
000f25e2: 88e6	b	#0xf22f6
000f25e4: 3529	cmp	r1, #0x35
000f25e6: 00dd	ble	#0xf25ea
000f25e8: 85e6	b	#0xf22f6
000f25ea: e0e7	b	#0xf25ae
000f25ec: bc09	lsrs	r4, r7, #6
000f25ee: 0000	movs	r0, r0
000f25f0: b809	lsrs	r0, r7, #6
000f25f2: 0000	movs	r0, r0
000f25f4: b409	lsrs	r4, r6, #6
000f25f6: 0000	movs	r0, r0
