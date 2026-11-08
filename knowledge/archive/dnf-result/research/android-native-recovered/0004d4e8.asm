0004d4e8: f0b5	push	{r4, r5, r6, r7, lr}
0004d4ea: 5f46	mov	r7, fp
0004d4ec: 5646	mov	r6, sl
0004d4ee: 4d46	mov	r5, sb
0004d4f0: 4446	mov	r4, r8
0004d4f2: f0b4	push	{r4, r5, r6, r7}
0004d4f4: 95b0	sub	sp, #0x54
0004d4f6: 0491	str	r1, [sp, #0x10]
0004d4f8: 8b68	ldr	r3, [r1, #8]
0004d4fa: 041c	adds	r4, r0, #0
0004d4fc: 0d68	ldr	r5, [r1]
0004d4fe: 1868	ldr	r0, [r3]
0004d500: df68	ldr	r7, [r3, #0xc]
0004d502: 0023	movs	r3, #0
0004d504: 8446	mov	ip, r0
0004d506: 0948	ldr	r0, [pc, #0x24]
0004d508: 094a	ldr	r2, [pc, #0x24]
0004d50a: 2350	str	r3, [r4, r0]
0004d50c: 094b	ldr	r3, [pc, #0x24]
0004d50e: e250	str	r2, [r4, r3]
0004d510: 002f	cmp	r7, #0
0004d512: 00dc	bgt	#0x4d516
0004d514: 42e2	b	#0x4d99c
0004d516: 0123	movs	r3, #1
0004d518: 5b42	rsbs	r3, r3, #0
0004d51a: 0893	str	r3, [sp, #0x20]
0004d51c: 0899	ldr	r1, [sp, #0x20]
0004d51e: 2a1c	adds	r2, r5, #0
0004d520: 0023	movs	r3, #0
0004d522: 0026	movs	r6, #0
0004d524: 8846	mov	r8, r1
0004d526: a946	mov	sb, r5
0004d528: 17e0	b	#0x4d55a
0004d52a: c046	mov	r8, r8
0004d52c: 5014	asrs	r0, r2, #0x11
0004d52e: 0000	movs	r0, r0
0004d530: 3d02	lsls	r5, r7, #8
0004d532: 0000	movs	r0, r0
0004d534: 5414	asrs	r4, r2, #0x11
0004d536: 0000	movs	r0, r0
0004d538: 2158	ldr	r1, [r4, r0]
0004d53a: 9846	mov	r8, r3
0004d53c: 0432	adds	r2, #4
0004d53e: 4d1c	adds	r5, r1, #1
0004d540: 2550	str	r5, [r4, r0]
0004d542: d64d	ldr	r5, [pc, #0x358]
0004d544: 4919	adds	r1, r1, r5
0004d546: 8900	lsls	r1, r1, #2
0004d548: d54d	ldr	r5, [pc, #0x354]
0004d54a: 6118	adds	r1, r4, r1
0004d54c: 4b60	str	r3, [r1, #4]
0004d54e: e118	adds	r1, r4, r3
0004d550: 4919	adds	r1, r1, r5
0004d552: 0133	adds	r3, #1
0004d554: 0e70	strb	r6, [r1]
0004d556: bb42	cmp	r3, r7
0004d558: 07d0	beq	#0x4d56a
0004d55a: 1188	ldrh	r1, [r2]
0004d55c: 0029	cmp	r1, #0
0004d55e: ebd1	bne	#0x4d538
0004d560: 0133	adds	r3, #1
0004d562: 5180	strh	r1, [r2, #2]
0004d564: 0432	adds	r2, #4
0004d566: bb42	cmp	r3, r7
0004d568: f7d1	bne	#0x4d55a
0004d56a: 4646	mov	r6, r8
0004d56c: 0896	str	r6, [sp, #0x20]
0004d56e: 4d46	mov	r5, sb
0004d570: cc4b	ldr	r3, [pc, #0x330]
0004d572: cd48	ldr	r0, [pc, #0x334]
0004d574: cd4e	ldr	r6, [pc, #0x334]
0004d576: 0021	movs	r1, #0
0004d578: 0122	movs	r2, #1
0004d57a: 8946	mov	sb, r1
0004d57c: 9246	mov	sl, r2
0004d57e: 9846	mov	r8, r3
0004d580: bb46	mov	fp, r7
0004d582: 2258	ldr	r2, [r4, r0]
0004d584: 012a	cmp	r2, #1
0004d586: 22dc	bgt	#0x4d5ce
0004d588: 0132	adds	r2, #1
0004d58a: 2250	str	r2, [r4, r0]
0004d58c: 0899	ldr	r1, [sp, #0x20]
0004d58e: 0129	cmp	r1, #1
0004d590: 00dc	bgt	#0x4d594
0004d592: c5e1	b	#0x4d920
0004d594: 0021	movs	r1, #0
0004d596: 0023	movs	r3, #0
0004d598: c54f	ldr	r7, [pc, #0x314]
0004d59a: d219	adds	r2, r2, r7
0004d59c: 9200	lsls	r2, r2, #2
0004d59e: c04f	ldr	r7, [pc, #0x300]
0004d5a0: a218	adds	r2, r4, r2
0004d5a2: 5360	str	r3, [r2, #4]
0004d5a4: 5246	mov	r2, sl
0004d5a6: e318	adds	r3, r4, r3
0004d5a8: 6a52	strh	r2, [r5, r1]
0004d5aa: db19	adds	r3, r3, r7
0004d5ac: 4a46	mov	r2, sb
0004d5ae: 1a70	strb	r2, [r3]
0004d5b0: a359	ldr	r3, [r4, r6]
0004d5b2: 013b	subs	r3, #1
0004d5b4: a351	str	r3, [r4, r6]
0004d5b6: 6346	mov	r3, ip
0004d5b8: 002b	cmp	r3, #0
0004d5ba: e2d0	beq	#0x4d582
0004d5bc: 4746	mov	r7, r8
0004d5be: 6144	add	r1, ip
0004d5c0: e259	ldr	r2, [r4, r7]
0004d5c2: 4b88	ldrh	r3, [r1, #2]
0004d5c4: d31a	subs	r3, r2, r3
0004d5c6: 2258	ldr	r2, [r4, r0]
0004d5c8: e351	str	r3, [r4, r7]
0004d5ca: 012a	cmp	r2, #1
0004d5cc: dcdd	ble	#0x4d588
0004d5ce: 089e	ldr	r6, [sp, #0x20]
0004d5d0: 0498	ldr	r0, [sp, #0x10]
0004d5d2: b54b	ldr	r3, [pc, #0x2d4]
0004d5d4: 5f46	mov	r7, fp
0004d5d6: 4660	str	r6, [r0, #4]
0004d5d8: e358	ldr	r3, [r4, r3]
0004d5da: de0f	lsrs	r6, r3, #0x1f
0004d5dc: f318	adds	r3, r6, r3
0004d5de: 5e10	asrs	r6, r3, #1
0004d5e0: 002e	cmp	r6, #0
0004d5e2: 07dd	ble	#0x4d5f4
0004d5e4: 321c	adds	r2, r6, #0
0004d5e6: 201c	adds	r0, r4, #0
0004d5e8: 291c	adds	r1, r5, #0
0004d5ea: 013e	subs	r6, #1
0004d5ec: fff7eefe	bl	#0x4d3cc
0004d5f0: 002e	cmp	r6, #0
0004d5f2: f7dc	bgt	#0x4d5e4
0004d5f4: ac4a	ldr	r2, [pc, #0x2b0]
0004d5f6: aa4e	ldr	r6, [pc, #0x2a8]
0004d5f8: b900	lsls	r1, r7, #2
0004d5fa: 4919	adds	r1, r1, r5
0004d5fc: 8a46	mov	sl, r1
0004d5fe: a358	ldr	r3, [r4, r2]
0004d600: b919	adds	r1, r7, r6
0004d602: 0919	adds	r1, r1, r4
0004d604: b626	movs	r6, #0xb6
0004d606: 8946	mov	sb, r1
0004d608: 3601	lsls	r6, r6, #4
0004d60a: 9346	mov	fp, r2
0004d60c: a849	ldr	r1, [pc, #0x2a0]
0004d60e: a059	ldr	r0, [r4, r6]
0004d610: 5a18	adds	r2, r3, r1
0004d612: 9200	lsls	r2, r2, #2
0004d614: a218	adds	r2, r4, r2
0004d616: 5268	ldr	r2, [r2, #4]
0004d618: 013b	subs	r3, #1
0004d61a: 8046	mov	r8, r0
0004d61c: a251	str	r2, [r4, r6]
0004d61e: 5a46	mov	r2, fp
0004d620: a350	str	r3, [r4, r2]
0004d622: 201c	adds	r0, r4, #0
0004d624: 291c	adds	r1, r5, #0
0004d626: 0122	movs	r2, #1
0004d628: fff7d0fe	bl	#0x4d3cc
0004d62c: a148	ldr	r0, [pc, #0x284]
0004d62e: a359	ldr	r3, [r4, r6]
0004d630: 2258	ldr	r2, [r4, r0]
0004d632: a148	ldr	r0, [pc, #0x284]
0004d634: 1118	adds	r1, r2, r0
0004d636: 8900	lsls	r1, r1, #2
0004d638: 6118	adds	r1, r4, r1
0004d63a: 4046	mov	r0, r8
0004d63c: 4860	str	r0, [r1, #4]
0004d63e: 9d48	ldr	r0, [pc, #0x274]
0004d640: 911e	subs	r1, r2, #2
0004d642: 2150	str	r1, [r4, r0]
0004d644: b521	movs	r1, #0xb5
0004d646: 8900	lsls	r1, r1, #2
0004d648: 5218	adds	r2, r2, r1
0004d64a: 9200	lsls	r2, r2, #2
0004d64c: a218	adds	r2, r4, r2
0004d64e: 4046	mov	r0, r8
0004d650: 5360	str	r3, [r2, #4]
0004d652: 8200	lsls	r2, r0, #2
0004d654: aa18	adds	r2, r5, r2
0004d656: 9900	lsls	r1, r3, #2
0004d658: 0692	str	r2, [sp, #0x18]
0004d65a: 6918	adds	r1, r5, r1
0004d65c: 0a88	ldrh	r2, [r1]
0004d65e: e318	adds	r3, r4, r3
0004d660: 9446	mov	ip, r2
0004d662: 069a	ldr	r2, [sp, #0x18]
0004d664: 1088	ldrh	r0, [r2]
0004d666: 8444	add	ip, r0
0004d668: 6246	mov	r2, ip
0004d66a: 5046	mov	r0, sl
0004d66c: 0280	strh	r2, [r0]
0004d66e: 8c48	ldr	r0, [pc, #0x230]
0004d670: 4246	mov	r2, r8
0004d672: 1818	adds	r0, r3, r0
0004d674: 8a4b	ldr	r3, [pc, #0x228]
0004d676: 0590	str	r0, [sp, #0x14]
0004d678: a018	adds	r0, r4, r2
0004d67a: c018	adds	r0, r0, r3
0004d67c: 0078	ldrb	r0, [r0]
0004d67e: 8446	mov	ip, r0
0004d680: 0598	ldr	r0, [sp, #0x14]
0004d682: 0378	ldrb	r3, [r0]
0004d684: 181c	adds	r0, r3, #0
0004d686: 6345	cmp	r3, ip
0004d688: 00d2	bhs	#0x4d68c
0004d68a: 6046	mov	r0, ip
0004d68c: 3b04	lsls	r3, r7, #0x10
0004d68e: 1b0c	lsrs	r3, r3, #0x10
0004d690: 4a46	mov	r2, sb
0004d692: 0130	adds	r0, #1
0004d694: 1070	strb	r0, [r2]
0004d696: 4b80	strh	r3, [r1, #2]
0004d698: 0698	ldr	r0, [sp, #0x18]
0004d69a: b621	movs	r1, #0xb6
0004d69c: 0a01	lsls	r2, r1, #4
0004d69e: 4380	strh	r3, [r0, #2]
0004d6a0: 291c	adds	r1, r5, #0
0004d6a2: a751	str	r7, [r4, r6]
0004d6a4: 201c	adds	r0, r4, #0
0004d6a6: 9046	mov	r8, r2
0004d6a8: 0122	movs	r2, #1
0004d6aa: fff78ffe	bl	#0x4d3cc
0004d6ae: 5846	mov	r0, fp
0004d6b0: 2358	ldr	r3, [r4, r0]
0004d6b2: 0421	movs	r1, #4
0004d6b4: 0122	movs	r2, #1
0004d6b6: 0137	adds	r7, #1
0004d6b8: 8a44	add	sl, r1
0004d6ba: 9144	add	sb, r2
0004d6bc: 012b	cmp	r3, #1
0004d6be: a5dc	bgt	#0x4d60c
0004d6c0: 7c4a	ldr	r2, [pc, #0x1f0]
0004d6c2: 7d48	ldr	r0, [pc, #0x1f4]
0004d6c4: 4646	mov	r6, r8
0004d6c6: a358	ldr	r3, [r4, r2]
0004d6c8: a759	ldr	r7, [r4, r6]
0004d6ca: 591e	subs	r1, r3, #1
0004d6cc: 1b18	adds	r3, r3, r0
0004d6ce: 9b00	lsls	r3, r3, #2
0004d6d0: e318	adds	r3, r4, r3
0004d6d2: a150	str	r1, [r4, r2]
0004d6d4: 5f60	str	r7, [r3, #4]
0004d6d6: 049e	ldr	r6, [sp, #0x10]
0004d6d8: 049a	ldr	r2, [sp, #0x10]
0004d6da: b368	ldr	r3, [r6, #8]
0004d6dc: 1168	ldr	r1, [r2]
0004d6de: 5268	ldr	r2, [r2, #4]
0004d6e0: 1868	ldr	r0, [r3]
0004d6e2: 0590	str	r0, [sp, #0x14]
0004d6e4: 5e68	ldr	r6, [r3, #4]
0004d6e6: 0796	str	r6, [sp, #0x1c]
0004d6e8: 9868	ldr	r0, [r3, #8]
0004d6ea: 0690	str	r0, [sp, #0x18]
0004d6ec: 1b69	ldr	r3, [r3, #0x10]
0004d6ee: 0020	movs	r0, #0
0004d6f0: 8446	mov	ip, r0
0004d6f2: 9846	mov	r8, r3
0004d6f4: 714b	ldr	r3, [pc, #0x1c4]
0004d6f6: 2618	adds	r6, r4, r0
0004d6f8: 0230	adds	r0, #2
0004d6fa: f618	adds	r6, r6, r3
0004d6fc: 6346	mov	r3, ip
0004d6fe: 3380	strh	r3, [r6]
0004d700: 2028	cmp	r0, #0x20
0004d702: f7d1	bne	#0x4d6f4
0004d704: bf00	lsls	r7, r7, #2
0004d706: 0020	movs	r0, #0
0004d708: cf19	adds	r7, r1, r7
0004d70a: 7880	strh	r0, [r7, #2]
0004d70c: 6948	ldr	r0, [pc, #0x1a4]
0004d70e: 4346	mov	r3, r8
0004d710: 2058	ldr	r0, [r4, r0]
0004d712: 0990	str	r0, [sp, #0x24]
0004d714: 0130	adds	r0, #1
0004d716: 0a90	str	r0, [sp, #0x28]
0004d718: 0a9e	ldr	r6, [sp, #0x28]
0004d71a: 8f20	movs	r0, #0x8f
0004d71c: 8000	lsls	r0, r0, #2
0004d71e: 8642	cmp	r6, r0
0004d720: 00dd	ble	#0x4d724
0004d722: 03e1	b	#0x4d92c
0004d724: 099f	ldr	r7, [sp, #0x24]
0004d726: 5d48	ldr	r0, [pc, #0x174]
0004d728: 0391	str	r1, [sp, #0xc]
0004d72a: 9246	mov	sl, r2
0004d72c: 3e18	adds	r6, r7, r0
0004d72e: 5e4f	ldr	r7, [pc, #0x178]
0004d730: b600	lsls	r6, r6, #2
0004d732: a619	adds	r6, r4, r6
0004d734: e019	adds	r0, r4, r7
0004d736: 0027	movs	r7, #0
0004d738: 0497	str	r7, [sp, #0x10]
0004d73a: 5c4f	ldr	r7, [pc, #0x170]
0004d73c: 0436	adds	r6, #4
0004d73e: 8046	mov	r8, r0
0004d740: b946	mov	sb, r7
0004d742: 0293	str	r3, [sp, #8]
0004d744: 0b95	str	r5, [sp, #0x2c]
0004d746: 3568	ldr	r5, [r6]
0004d748: 0398	ldr	r0, [sp, #0xc]
0004d74a: 0399	ldr	r1, [sp, #0xc]
0004d74c: ab00	lsls	r3, r5, #2
0004d74e: c718	adds	r7, r0, r3
0004d750: 7888	ldrh	r0, [r7, #2]
0004d752: 029a	ldr	r2, [sp, #8]
0004d754: 8000	lsls	r0, r0, #2
0004d756: 0818	adds	r0, r1, r0
0004d758: 4088	ldrh	r0, [r0, #2]
0004d75a: 0130	adds	r0, #1
0004d75c: 8242	cmp	r2, r0
0004d75e: 03da	bge	#0x4d768
0004d760: 0498	ldr	r0, [sp, #0x10]
0004d762: 0130	adds	r0, #1
0004d764: 0490	str	r0, [sp, #0x10]
0004d766: 101c	adds	r0, r2, #0
0004d768: 7880	strh	r0, [r7, #2]
0004d76a: aa45	cmp	sl, r5
0004d76c: 28db	blt	#0x4d7c0
0004d76e: 5449	ldr	r1, [pc, #0x150]
0004d770: 0918	adds	r1, r1, r0
0004d772: 4900	lsls	r1, r1, #1
0004d774: 8c46	mov	ip, r1
0004d776: a444	add	ip, r4
0004d778: 6246	mov	r2, ip
0004d77a: 9288	ldrh	r2, [r2, #4]
0004d77c: 0121	movs	r1, #1
0004d77e: 9346	mov	fp, r2
0004d780: 8b44	add	fp, r1
0004d782: 6246	mov	r2, ip
0004d784: 5946	mov	r1, fp
0004d786: 9180	strh	r1, [r2, #4]
0004d788: 0699	ldr	r1, [sp, #0x18]
0004d78a: 0022	movs	r2, #0
0004d78c: 9446	mov	ip, r2
0004d78e: a942	cmp	r1, r5
0004d790: 04dc	bgt	#0x4d79c
0004d792: 6d1a	subs	r5, r5, r1
0004d794: 0799	ldr	r1, [sp, #0x1c]
0004d796: ad00	lsls	r5, r5, #2
0004d798: 6d58	ldr	r5, [r5, r1]
0004d79a: ac46	mov	ip, r5
0004d79c: 3d88	ldrh	r5, [r7]
0004d79e: 4a46	mov	r2, sb
0004d7a0: 6044	add	r0, ip
0004d7a2: a758	ldr	r7, [r4, r2]
0004d7a4: 6843	muls	r0, r5, r0
0004d7a6: c019	adds	r0, r0, r7
0004d7a8: a050	str	r0, [r4, r2]
0004d7aa: 059f	ldr	r7, [sp, #0x14]
0004d7ac: 002f	cmp	r7, #0
0004d7ae: 07d0	beq	#0x4d7c0
0004d7b0: fb18	adds	r3, r7, r3
0004d7b2: 5b88	ldrh	r3, [r3, #2]
0004d7b4: 3b49	ldr	r1, [pc, #0xec]
0004d7b6: 6344	add	r3, ip
0004d7b8: 6058	ldr	r0, [r4, r1]
0004d7ba: 5d43	muls	r5, r3, r5
0004d7bc: 2d18	adds	r5, r5, r0
0004d7be: 6550	str	r5, [r4, r1]
0004d7c0: 0436	adds	r6, #4
0004d7c2: 4645	cmp	r6, r8
0004d7c4: bfd1	bne	#0x4d746
0004d7c6: 0a9e	ldr	r6, [sp, #0x28]
0004d7c8: 0998	ldr	r0, [sp, #0x24]
0004d7ca: 0399	ldr	r1, [sp, #0xc]
0004d7cc: 029b	ldr	r3, [sp, #8]
0004d7ce: 371a	subs	r7, r6, r0
0004d7d0: 0498	ldr	r0, [sp, #0x10]
0004d7d2: 8f26	movs	r6, #0x8f
0004d7d4: b600	lsls	r6, r6, #2
0004d7d6: 5246	mov	r2, sl
0004d7d8: 0b9d	ldr	r5, [sp, #0x2c]
0004d7da: bf19	adds	r7, r7, r6
0004d7dc: 0028	cmp	r0, #0
0004d7de: 00d1	bne	#0x4d7e2
0004d7e0: a4e0	b	#0x4d92c
0004d7e2: 3848	ldr	r0, [pc, #0xe0]
0004d7e4: 5e1e	subs	r6, r3, #1
0004d7e6: b146	mov	sb, r6
0004d7e8: 1e18	adds	r6, r3, r0
0004d7ea: 0130	adds	r0, #1
0004d7ec: c018	adds	r0, r0, r3
0004d7ee: 8446	mov	ip, r0
0004d7f0: 3548	ldr	r0, [pc, #0xd4]
0004d7f2: 7600	lsls	r6, r6, #1
0004d7f4: 3619	adds	r6, r6, r4
0004d7f6: b246	mov	sl, r6
0004d7f8: 1e18	adds	r6, r3, r0
0004d7fa: 7600	lsls	r6, r6, #1
0004d7fc: a619	adds	r6, r4, r6
0004d7fe: 0436	adds	r6, #4
0004d800: b346	mov	fp, r6
0004d802: 6646	mov	r6, ip
0004d804: 7000	lsls	r0, r6, #1
0004d806: 0019	adds	r0, r0, r4
0004d808: 8046	mov	r8, r0
0004d80a: 5846	mov	r0, fp
0004d80c: 8c46	mov	ip, r1
0004d80e: ab46	mov	fp, r5
0004d810: 4146	mov	r1, r8
0004d812: 5546	mov	r5, sl
0004d814: 9046	mov	r8, r2
0004d816: ba46	mov	sl, r7
0004d818: 4a46	mov	r2, sb
0004d81a: 071c	adds	r7, r0, #0
0004d81c: 9946	mov	sb, r3
0004d81e: ab88	ldrh	r3, [r5, #4]
0004d820: 161c	adds	r6, r2, #0
0004d822: 002b	cmp	r3, #0
0004d824: 05d1	bne	#0x4d832
0004d826: 381c	adds	r0, r7, #0
0004d828: 0388	ldrh	r3, [r0]
0004d82a: 013e	subs	r6, #1
0004d82c: 0238	subs	r0, #2
0004d82e: 002b	cmp	r3, #0
0004d830: fad0	beq	#0x4d828
0004d832: 2348	ldr	r0, [pc, #0x8c]
0004d834: 013b	subs	r3, #1
0004d836: 0693	str	r3, [sp, #0x18]
0004d838: 3018	adds	r0, r6, r0
0004d83a: 4000	lsls	r0, r0, #1
0004d83c: 2318	adds	r3, r4, r0
0004d83e: 0593	str	r3, [sp, #0x14]
0004d840: 6846	mov	r0, sp
0004d842: 1823	movs	r3, #0x18
0004d844: 1b5a	ldrh	r3, [r3, r0]
0004d846: 0598	ldr	r0, [sp, #0x14]
0004d848: 8380	strh	r3, [r0, #4]
0004d84a: 2048	ldr	r0, [pc, #0x80]
0004d84c: 3318	adds	r3, r6, r0
0004d84e: 5b00	lsls	r3, r3, #1
0004d850: e318	adds	r3, r4, r3
0004d852: 9888	ldrh	r0, [r3, #4]
0004d854: 0230	adds	r0, #2
0004d856: 9880	strh	r0, [r3, #4]
0004d858: 8b88	ldrh	r3, [r1, #4]
0004d85a: 013b	subs	r3, #1
0004d85c: 8b80	strh	r3, [r1, #4]
0004d85e: 049b	ldr	r3, [sp, #0x10]
0004d860: 023b	subs	r3, #2
0004d862: 0493	str	r3, [sp, #0x10]
0004d864: 002b	cmp	r3, #0
0004d866: dadc	bgt	#0x4d81e
0004d868: 4b46	mov	r3, sb
0004d86a: 5746	mov	r7, sl
0004d86c: 9146	mov	sb, r2
0004d86e: 5d46	mov	r5, fp
0004d870: 4246	mov	r2, r8
0004d872: 8846	mov	r8, r1
0004d874: 002b	cmp	r3, #0
0004d876: 59d0	beq	#0x4d92c
0004d878: 0c4e	ldr	r6, [pc, #0x30]
0004d87a: 4046	mov	r0, r8
0004d87c: 0430	adds	r0, #4
0004d87e: b046	mov	r8, r6
0004d880: 8346	mov	fp, r0
0004d882: e246	mov	sl, ip
0004d884: 0495	str	r5, [sp, #0x10]
0004d886: 5846	mov	r0, fp
0004d888: 0588	ldrh	r5, [r0]
0004d88a: 002d	cmp	r5, #0
0004d88c: 3ed0	beq	#0x4d90c
0004d88e: 0a49	ldr	r1, [pc, #0x28]
0004d890: 0692	str	r2, [sp, #0x18]
0004d892: 7818	adds	r0, r7, r1
0004d894: 8000	lsls	r0, r0, #2
0004d896: 2018	adds	r0, r4, r0
0004d898: 0430	adds	r0, #4
0004d89a: 19e0	b	#0x4d8d0
0004d89c: d702	lsls	r7, r2, #0xb
0004d89e: 0000	movs	r0, r0
0004d8a0: 5814	asrs	r0, r3, #0x11
0004d8a2: 0000	movs	r0, r0
0004d8a4: ac16	asrs	r4, r5, #0x1a
0004d8a6: 0000	movs	r0, r0
0004d8a8: 5014	asrs	r0, r2, #0x11
0004d8aa: 0000	movs	r0, r0
0004d8ac: a816	asrs	r0, r5, #0x1a
0004d8ae: 0000	movs	r0, r0
0004d8b0: d602	lsls	r6, r2, #0xb
0004d8b2: 0000	movs	r0, r0
0004d8b4: 5414	asrs	r4, r2, #0x11
0004d8b6: 0000	movs	r0, r0
0004d8b8: d502	lsls	r5, r2, #0xb
0004d8ba: 0000	movs	r0, r0
0004d8bc: 3c0b	lsrs	r4, r7, #0xc
0004d8be: 0000	movs	r0, r0
0004d8c0: 9c05	lsls	r4, r3, #0x16
0004d8c2: 0000	movs	r0, r0
0004d8c4: 9b05	lsls	r3, r3, #0x16
0004d8c6: 0000	movs	r0, r0
0004d8c8: 9a05	lsls	r2, r3, #0x16
0004d8ca: 0000	movs	r0, r0
0004d8cc: 9d05	lsls	r5, r3, #0x16
0004d8ce: 0000	movs	r0, r0
0004d8d0: 0168	ldr	r1, [r0]
0004d8d2: 069a	ldr	r2, [sp, #0x18]
0004d8d4: 013f	subs	r7, #1
0004d8d6: 8a42	cmp	r2, r1
0004d8d8: 14db	blt	#0x4d904
0004d8da: 8900	lsls	r1, r1, #2
0004d8dc: 5144	add	r1, sl
0004d8de: 4e88	ldrh	r6, [r1, #2]
0004d8e0: 9e42	cmp	r6, r3
0004d8e2: 0ed0	beq	#0x4d902
0004d8e4: 9e1b	subs	r6, r3, r6
0004d8e6: 0596	str	r6, [sp, #0x14]
0004d8e8: 0e88	ldrh	r6, [r1]
0004d8ea: b446	mov	ip, r6
0004d8ec: 059e	ldr	r6, [sp, #0x14]
0004d8ee: 6246	mov	r2, ip
0004d8f0: 7243	muls	r2, r6, r2
0004d8f2: 4646	mov	r6, r8
0004d8f4: 9446	mov	ip, r2
0004d8f6: 4246	mov	r2, r8
0004d8f8: a258	ldr	r2, [r4, r2]
0004d8fa: 9444	add	ip, r2
0004d8fc: 6246	mov	r2, ip
0004d8fe: a251	str	r2, [r4, r6]
0004d900: 4b80	strh	r3, [r1, #2]
0004d902: 013d	subs	r5, #1
0004d904: 0438	subs	r0, #4
0004d906: 002d	cmp	r5, #0
0004d908: e2d1	bne	#0x4d8d0
0004d90a: 069a	ldr	r2, [sp, #0x18]
0004d90c: 0225	movs	r5, #2
0004d90e: 6d42	rsbs	r5, r5, #0
0004d910: 4b46	mov	r3, sb
0004d912: ab44	add	fp, r5
0004d914: 002b	cmp	r3, #0
0004d916: 08d0	beq	#0x4d92a
0004d918: 0126	movs	r6, #1
0004d91a: 7642	rsbs	r6, r6, #0
0004d91c: b144	add	sb, r6
0004d91e: b2e7	b	#0x4d886
0004d920: 089b	ldr	r3, [sp, #0x20]
0004d922: 0133	adds	r3, #1
0004d924: 9900	lsls	r1, r3, #2
0004d926: 0893	str	r3, [sp, #0x20]
0004d928: 36e6	b	#0x4d598
0004d92a: 049d	ldr	r5, [sp, #0x10]
0004d92c: 0023	movs	r3, #0
0004d92e: 0022	movs	r2, #0
0004d930: 0cae	add	r6, sp, #0x30
0004d932: 1c4f	ldr	r7, [pc, #0x70]
0004d934: e118	adds	r1, r4, r3
0004d936: c919	adds	r1, r1, r7
0004d938: 0988	ldrh	r1, [r1]
0004d93a: 5218	adds	r2, r2, r1
0004d93c: 5204	lsls	r2, r2, #0x11
0004d93e: f118	adds	r1, r6, r3
0004d940: 120c	lsrs	r2, r2, #0x10
0004d942: 0233	adds	r3, #2
0004d944: 4a80	strh	r2, [r1, #2]
0004d946: 1e2b	cmp	r3, #0x1e
0004d948: f3d1	bne	#0x4d932
0004d94a: 0898	ldr	r0, [sp, #0x20]
0004d94c: 0130	adds	r0, #1
0004d94e: 1ed0	beq	#0x4d98e
0004d950: 0899	ldr	r1, [sp, #0x20]
0004d952: 0027	movs	r7, #0
0004d954: 0124	movs	r4, #1
0004d956: 8c46	mov	ip, r1
0004d958: 0121	movs	r1, #1
0004d95a: 8c44	add	ip, r1
0004d95c: e246	mov	sl, ip
0004d95e: b446	mov	ip, r6
0004d960: 6b88	ldrh	r3, [r5, #2]
0004d962: 002b	cmp	r3, #0
0004d964: 0fd0	beq	#0x4d986
0004d966: 5900	lsls	r1, r3, #1
0004d968: 6646	mov	r6, ip
0004d96a: 725a	ldrh	r2, [r6, r1]
0004d96c: 501c	adds	r0, r2, #1
0004d96e: 7052	strh	r0, [r6, r1]
0004d970: 0021	movs	r1, #0
0004d972: 101c	adds	r0, r2, #0
0004d974: 2040	ands	r0, r4
0004d976: 0143	orrs	r1, r0
0004d978: 013b	subs	r3, #1
0004d97a: 5208	lsrs	r2, r2, #1
0004d97c: 4900	lsls	r1, r1, #1
0004d97e: 002b	cmp	r3, #0
0004d980: f7d1	bne	#0x4d972
0004d982: 4908	lsrs	r1, r1, #1
0004d984: 2980	strh	r1, [r5]
0004d986: 0137	adds	r7, #1
0004d988: 0435	adds	r5, #4
0004d98a: 5745	cmp	r7, sl
0004d98c: e8d1	bne	#0x4d960
0004d98e: 15b0	add	sp, #0x54
0004d990: 3cbc	pop	{r2, r3, r4, r5}
0004d992: 9046	mov	r8, r2
0004d994: 9946	mov	sb, r3
0004d996: a246	mov	sl, r4
0004d998: ab46	mov	fp, r5
0004d99a: f0bd	pop	{r4, r5, r6, r7, pc}
0004d99c: 0121	movs	r1, #1
0004d99e: 4942	rsbs	r1, r1, #0
0004d9a0: 0891	str	r1, [sp, #0x20]
0004d9a2: e5e5	b	#0x4d570
0004d9a4: 3c0b	lsrs	r4, r7, #0xc
0004d9a6: 0000	movs	r0, r0
