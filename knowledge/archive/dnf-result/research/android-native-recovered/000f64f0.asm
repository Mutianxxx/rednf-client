000f64f0: f0b5	push	{r4, r5, r6, r7, lr}
000f64f2: 5f46	mov	r7, fp
000f64f4: 5646	mov	r6, sl
000f64f6: 4d46	mov	r5, sb
000f64f8: 4446	mov	r4, r8
000f64fa: f0b4	push	{r4, r5, r6, r7}
000f64fc: 91b0	sub	sp, #0x44
000f64fe: 0891	str	r1, [sp, #0x20]
000f6500: 0792	str	r2, [sp, #0x1c]
000f6502: 051c	adds	r5, r0, #0
000f6504: 0069	ldr	r0, [r0, #0x10]
000f6506: 0c68	ldr	r4, [r1]
000f6508: 8379	ldrb	r3, [r0, #6]
000f650a: c279	ldrb	r2, [r0, #7]
000f650c: 1b02	lsls	r3, r3, #8
000f650e: 1343	orrs	r3, r2
000f6510: 1b04	lsls	r3, r3, #0x10
000f6512: 1b0c	lsrs	r3, r3, #0x10
000f6514: 0122	movs	r2, #1
000f6516: 9343	bics	r3, r2
000f6518: 9c46	mov	ip, r3
000f651a: 4ad0	beq	#0xf65b2
000f651c: 079b	ldr	r3, [sp, #0x1c]
000f651e: 6146	mov	r1, ip
000f6520: 4908	lsrs	r1, r1, #1
000f6522: 5a1e	subs	r2, r3, #1
000f6524: 9341	sbcs	r3, r2
000f6526: 0691	str	r1, [sp, #0x18]
000f6528: e418	adds	r4, r4, r3
000f652a: 0029	cmp	r1, #0
000f652c: 00d1	bne	#0xf6530
000f652e: 56e1	b	#0xf67de
000f6530: 069b	ldr	r3, [sp, #0x18]
000f6532: 6646	mov	r6, ip
000f6534: 0236	adds	r6, #2
000f6536: 0027	movs	r7, #0
000f6538: 1a1c	adds	r2, r3, #0
000f653a: 031c	adds	r3, r0, #0
000f653c: b046	mov	r8, r6
000f653e: 381c	adds	r0, r7, #0
000f6540: aa46	mov	sl, r5
000f6542: 9946	mov	sb, r3
000f6544: 04e0	b	#0xf6550
000f6546: ac42	cmp	r4, r5
000f6548: 41d9	bls	#0xf65ce
000f654a: 581c	adds	r0, r3, #1
000f654c: 8242	cmp	r2, r0
000f654e: 12d9	bls	#0xf6576
000f6550: 1318	adds	r3, r2, r0
000f6552: 5b08	lsrs	r3, r3, #1
000f6554: df1d	adds	r7, r3, #7
000f6556: 7f00	lsls	r7, r7, #1
000f6558: 4f44	add	r7, sb
000f655a: 3d78	ldrb	r5, [r7]
000f655c: 7978	ldrb	r1, [r7, #1]
000f655e: 4744	add	r7, r8
000f6560: 2d02	lsls	r5, r5, #8
000f6562: 3e78	ldrb	r6, [r7]
000f6564: 0d43	orrs	r5, r1
000f6566: 7978	ldrb	r1, [r7, #1]
000f6568: 3602	lsls	r6, r6, #8
000f656a: 3143	orrs	r1, r6
000f656c: 8c42	cmp	r4, r1
000f656e: ead2	bhs	#0xf6546
000f6570: 1a1c	adds	r2, r3, #0
000f6572: 8242	cmp	r2, r0
000f6574: ecd8	bhi	#0xf6550
000f6576: 291c	adds	r1, r5, #0
000f6578: 5546	mov	r5, sl
000f657a: 0593	str	r3, [sp, #0x14]
000f657c: 8846	mov	r8, r1
000f657e: 0026	movs	r6, #0
000f6580: 079b	ldr	r3, [sp, #0x1c]
000f6582: 002b	cmp	r3, #0
000f6584: 16d0	beq	#0xf65b4
000f6586: a045	cmp	r8, r4
000f6588: 05d2	bhs	#0xf6596
000f658a: 059f	ldr	r7, [sp, #0x14]
000f658c: 0698	ldr	r0, [sp, #0x18]
000f658e: 0137	adds	r7, #1
000f6590: 0597	str	r7, [sp, #0x14]
000f6592: 8742	cmp	r7, r0
000f6594: 0dd0	beq	#0xf65b2
000f6596: 281c	adds	r0, r5, #0
000f6598: 0599	ldr	r1, [sp, #0x14]
000f659a: fff719fe	bl	#0xf61d0
000f659e: 0028	cmp	r0, #0
000f65a0: 10d1	bne	#0xf65c4
000f65a2: ac61	str	r4, [r5, #0x18]
000f65a4: 002e	cmp	r6, #0
000f65a6: 00d1	bne	#0xf65aa
000f65a8: 0ce1	b	#0xf67c4
000f65aa: ee61	str	r6, [r5, #0x1c]
000f65ac: 089a	ldr	r2, [sp, #0x20]
000f65ae: 1460	str	r4, [r2]
000f65b0: 00e0	b	#0xf65b4
000f65b2: 0026	movs	r6, #0
000f65b4: 11b0	add	sp, #0x44
000f65b6: 301c	adds	r0, r6, #0
000f65b8: 3cbc	pop	{r2, r3, r4, r5}
000f65ba: 9046	mov	r8, r2
000f65bc: 9946	mov	sb, r3
000f65be: a246	mov	sl, r4
000f65c0: ab46	mov	fp, r5
000f65c2: f0bd	pop	{r4, r5, r6, r7, pc}
000f65c4: 002e	cmp	r6, #0
000f65c6: f5d0	beq	#0xf65b4
000f65c8: 0899	ldr	r1, [sp, #0x20]
000f65ca: 0c60	str	r4, [r1]
000f65cc: f2e7	b	#0xf65b4
000f65ce: 4646	mov	r6, r8
000f65d0: b846	mov	r8, r7
000f65d2: e044	add	r8, ip
000f65d4: 0d91	str	r1, [sp, #0x34]
000f65d6: 0c93	str	r3, [sp, #0x30]
000f65d8: 4746	mov	r7, r8
000f65da: 3f78	ldrb	r7, [r7]
000f65dc: 3f06	lsls	r7, r7, #0x18
000f65de: 3f16	asrs	r7, r7, #0x18
000f65e0: 4246	mov	r2, r8
000f65e2: 5278	ldrb	r2, [r2, #1]
000f65e4: 3f02	lsls	r7, r7, #8
000f65e6: e044	add	r8, ip
000f65e8: 1743	orrs	r7, r2
000f65ea: 0997	str	r7, [sp, #0x24]
000f65ec: 4746	mov	r7, r8
000f65ee: 0397	str	r7, [sp, #0xc]
000f65f0: 3a78	ldrb	r2, [r7]
000f65f2: 7f78	ldrb	r7, [r7, #1]
000f65f4: 291c	adds	r1, r5, #0
000f65f6: 1202	lsls	r2, r2, #8
000f65f8: 3a43	orrs	r2, r7
000f65fa: 5546	mov	r5, sl
000f65fc: 9246	mov	sl, r2
000f65fe: bb4a	ldr	r2, [pc, #0x2ec]
000f6600: 0d9f	ldr	r7, [sp, #0x34]
000f6602: 4846	mov	r0, sb
000f6604: 9046	mov	r8, r2
000f6606: 4745	cmp	r7, r8
000f6608: 00d1	bne	#0xf660c
000f660a: 9fe0	b	#0xf674c
000f660c: 6f69	ldr	r7, [r5, #0x14]
000f660e: 3a1c	adds	r2, r7, #0
000f6610: 9207	lsls	r2, r2, #0x1e
000f6612: 7cd5	bpl	#0xf670e
000f6614: b54f	ldr	r7, [pc, #0x2d4]
000f6616: ba45	cmp	sl, r7
000f6618: 00d1	bne	#0xf661c
000f661a: dce0	b	#0xf67d6
000f661c: 5a1c	adds	r2, r3, #1
000f661e: 0b92	str	r2, [sp, #0x2c]
000f6620: 0593	str	r3, [sp, #0x14]
000f6622: 002b	cmp	r3, #0
000f6624: 00d1	bne	#0xf6628
000f6626: 58e1	b	#0xf68da
000f6628: 9f1d	adds	r7, r3, #6
000f662a: 7f00	lsls	r7, r7, #1
000f662c: b946	mov	sb, r7
000f662e: 8144	add	sb, r0
000f6630: 4a46	mov	r2, sb
000f6632: 1278	ldrb	r2, [r2]
000f6634: 4f46	mov	r7, sb
000f6636: 7f78	ldrb	r7, [r7, #1]
000f6638: 1202	lsls	r2, r2, #8
000f663a: 3a43	orrs	r2, r7
000f663c: 0a92	str	r2, [sp, #0x28]
000f663e: 0a9f	ldr	r7, [sp, #0x28]
000f6640: 5a1e	subs	r2, r3, #1
000f6642: bc42	cmp	r4, r7
000f6644: 00d9	bls	#0xf6648
000f6646: 45e1	b	#0xf68d4
000f6648: a84f	ldr	r7, [pc, #0x2a0]
000f664a: 0d91	str	r1, [sp, #0x34]
000f664c: 9a46	mov	sl, r3
000f664e: bb46	mov	fp, r7
000f6650: 111c	adds	r1, r2, #0
000f6652: 4f46	mov	r7, sb
000f6654: a046	mov	r8, r4
000f6656: 8146	mov	sb, r0
000f6658: 0e95	str	r5, [sp, #0x38]
000f665a: 6046	mov	r0, ip
000f665c: 0ce0	b	#0xf6678
000f665e: 8f1d	adds	r7, r1, #6
000f6660: 7f00	lsls	r7, r7, #1
000f6662: 4f44	add	r7, sb
000f6664: 3b78	ldrb	r3, [r7]
000f6666: 7d78	ldrb	r5, [r7, #1]
000f6668: 1b02	lsls	r3, r3, #8
000f666a: 2b43	orrs	r3, r5
000f666c: 4d1e	subs	r5, r1, #1
000f666e: 9845	cmp	r8, r3
000f6670: 00d9	bls	#0xf6674
000f6672: 98e0	b	#0xf67a6
000f6674: 291c	adds	r1, r5, #0
000f6676: 0a93	str	r3, [sp, #0x28]
000f6678: ba19	adds	r2, r7, r6
000f667a: 1478	ldrb	r4, [r2]
000f667c: 5378	ldrb	r3, [r2, #1]
000f667e: 1218	adds	r2, r2, r0
000f6680: 2402	lsls	r4, r4, #8
000f6682: 1c43	orrs	r4, r3
000f6684: a446	mov	ip, r4
000f6686: 0024	movs	r4, #0
000f6688: 1457	ldrsb	r4, [r2, r4]
000f668a: 5378	ldrb	r3, [r2, #1]
000f668c: 1218	adds	r2, r2, r0
000f668e: 2402	lsls	r4, r4, #8
000f6690: 1c43	orrs	r4, r3
000f6692: 0994	str	r4, [sp, #0x24]
000f6694: 1478	ldrb	r4, [r2]
000f6696: 5378	ldrb	r3, [r2, #1]
000f6698: 2402	lsls	r4, r4, #8
000f669a: 1c43	orrs	r4, r3
000f669c: 5c45	cmp	r4, fp
000f669e: 00d0	beq	#0xf66a2
000f66a0: 0591	str	r1, [sp, #0x14]
000f66a2: 0029	cmp	r1, #0
000f66a4: dbd1	bne	#0xf665e
000f66a6: 0392	str	r2, [sp, #0xc]
000f66a8: 6246	mov	r2, ip
000f66aa: 0d99	ldr	r1, [sp, #0x34]
000f66ac: 0d92	str	r2, [sp, #0x34]
000f66ae: 0a9a	ldr	r2, [sp, #0x28]
000f66b0: 0e9d	ldr	r5, [sp, #0x38]
000f66b2: 0027	movs	r7, #0
000f66b4: 5346	mov	r3, sl
000f66b6: 8446	mov	ip, r0
000f66b8: a246	mov	sl, r4
000f66ba: 4846	mov	r0, sb
000f66bc: 4446	mov	r4, r8
000f66be: bb46	mov	fp, r7
000f66c0: 9046	mov	r8, r2
000f66c2: 059a	ldr	r2, [sp, #0x14]
000f66c4: 0b9f	ldr	r7, [sp, #0x2c]
000f66c6: ba42	cmp	r2, r7
000f66c8: 00d1	bne	#0xf66cc
000f66ca: 8de0	b	#0xf67e8
000f66cc: 0599	ldr	r1, [sp, #0x14]
000f66ce: 5945	cmp	r1, fp
000f66d0: 23d0	beq	#0xf671a
000f66d2: 0f1c	adds	r7, r1, #0
000f66d4: 0737	adds	r7, #7
000f66d6: 7f00	lsls	r7, r7, #1
000f66d8: c719	adds	r7, r0, r7
000f66da: 3a78	ldrb	r2, [r7]
000f66dc: 7b78	ldrb	r3, [r7, #1]
000f66de: bf19	adds	r7, r7, r6
000f66e0: 1202	lsls	r2, r2, #8
000f66e2: 1a43	orrs	r2, r3
000f66e4: 9046	mov	r8, r2
000f66e6: 3a78	ldrb	r2, [r7]
000f66e8: 7b78	ldrb	r3, [r7, #1]
000f66ea: 6744	add	r7, ip
000f66ec: 1202	lsls	r2, r2, #8
000f66ee: 1a43	orrs	r2, r3
000f66f0: 0d92	str	r2, [sp, #0x34]
000f66f2: 0026	movs	r6, #0
000f66f4: be57	ldrsb	r6, [r7, r6]
000f66f6: 7b78	ldrb	r3, [r7, #1]
000f66f8: 6744	add	r7, ip
000f66fa: 3602	lsls	r6, r6, #8
000f66fc: 1e43	orrs	r6, r3
000f66fe: 0996	str	r6, [sp, #0x24]
000f6700: 0397	str	r7, [sp, #0xc]
000f6702: 3978	ldrb	r1, [r7]
000f6704: 7b78	ldrb	r3, [r7, #1]
000f6706: 0902	lsls	r1, r1, #8
000f6708: 1943	orrs	r1, r3
000f670a: 8a46	mov	sl, r1
000f670c: 05e0	b	#0xf671a
000f670e: 7748	ldr	r0, [pc, #0x1dc]
000f6710: 8245	cmp	sl, r0
000f6712: 00d1	bne	#0xf6716
000f6714: 31e7	b	#0xf657a
000f6716: 0593	str	r3, [sp, #0x14]
000f6718: 8846	mov	r8, r1
000f671a: 5346	mov	r3, sl
000f671c: 002b	cmp	r3, #0
000f671e: 10d0	beq	#0xf6742
000f6720: 0d9e	ldr	r6, [sp, #0x34]
000f6722: 0398	ldr	r0, [sp, #0xc]
000f6724: a31b	subs	r3, r4, r6
000f6726: 5b00	lsls	r3, r3, #1
000f6728: 5344	add	r3, sl
000f672a: c718	adds	r7, r0, r3
000f672c: 3e78	ldrb	r6, [r7]
000f672e: 7b78	ldrb	r3, [r7, #1]
000f6730: 3602	lsls	r6, r6, #8
000f6732: 1e43	orrs	r6, r3
000f6734: 00d1	bne	#0xf6738
000f6736: 23e7	b	#0xf6580
000f6738: 0999	ldr	r1, [sp, #0x24]
000f673a: 7618	adds	r6, r6, r1
000f673c: 3604	lsls	r6, r6, #0x10
000f673e: 360c	lsrs	r6, r6, #0x10
000f6740: 1ee7	b	#0xf6580
000f6742: 099a	ldr	r2, [sp, #0x24]
000f6744: 1619	adds	r6, r2, r4
000f6746: 3604	lsls	r6, r6, #0x10
000f6748: 360c	lsrs	r6, r6, #0x10
000f674a: 19e7	b	#0xf6580
000f674c: 069a	ldr	r2, [sp, #0x18]
000f674e: 9046	mov	r8, r2
000f6750: 0122	movs	r2, #1
000f6752: 5242	rsbs	r2, r2, #0
000f6754: 9044	add	r8, r2
000f6756: 9845	cmp	r8, r3
000f6758: 00d9	bls	#0xf675c
000f675a: 57e7	b	#0xf660c
000f675c: b942	cmp	r1, r7
000f675e: 00d0	beq	#0xf6762
000f6760: 54e7	b	#0xf660c
000f6762: 2f68	ldr	r7, [r5]
000f6764: fa22	movs	r2, #0xfa
000f6766: b946	mov	sb, r7
000f6768: 5700	lsls	r7, r2, #1
000f676a: b846	mov	r8, r7
000f676c: 4a46	mov	r2, sb
000f676e: 4244	add	r2, r8
000f6770: 1268	ldr	r2, [r2]
000f6772: fc27	movs	r7, #0xfc
000f6774: 9346	mov	fp, r2
000f6776: 7a00	lsls	r2, r7, #1
000f6778: 9046	mov	r8, r2
000f677a: 4f46	mov	r7, sb
000f677c: 4744	add	r7, r8
000f677e: 3f68	ldr	r7, [r7]
000f6780: 5246	mov	r2, sl
000f6782: b846	mov	r8, r7
000f6784: 002a	cmp	r2, #0
000f6786: 00d1	bne	#0xf678a
000f6788: 40e7	b	#0xf660c
000f678a: 0227	movs	r7, #2
000f678c: 039a	ldr	r2, [sp, #0xc]
000f678e: c344	add	fp, r8
000f6790: b846	mov	r8, r7
000f6792: d044	add	r8, sl
000f6794: 9044	add	r8, r2
000f6796: c345	cmp	fp, r8
000f6798: 00d3	blo	#0xf679c
000f679a: 37e7	b	#0xf660c
000f679c: 0127	movs	r7, #1
000f679e: 0022	movs	r2, #0
000f67a0: 0997	str	r7, [sp, #0x24]
000f67a2: 9246	mov	sl, r2
000f67a4: 32e7	b	#0xf660c
000f67a6: 0392	str	r2, [sp, #0xc]
000f67a8: 6246	mov	r2, ip
000f67aa: 5346	mov	r3, sl
000f67ac: a246	mov	sl, r4
000f67ae: 4446	mov	r4, r8
000f67b0: 8846	mov	r8, r1
000f67b2: 0d99	ldr	r1, [sp, #0x34]
000f67b4: 0d92	str	r2, [sp, #0x34]
000f67b6: 0a9a	ldr	r2, [sp, #0x28]
000f67b8: 8446	mov	ip, r0
000f67ba: c346	mov	fp, r8
000f67bc: 4846	mov	r0, sb
000f67be: 0e9d	ldr	r5, [sp, #0x38]
000f67c0: 9046	mov	r8, r2
000f67c2: 7ee7	b	#0xf66c2
000f67c4: 281c	adds	r0, r5, #0
000f67c6: fff77ffd	bl	#0xf62c8
000f67ca: ee69	ldr	r6, [r5, #0x1c]
000f67cc: 002e	cmp	r6, #0
000f67ce: 00d1	bne	#0xf67d2
000f67d0: f0e6	b	#0xf65b4
000f67d2: ac69	ldr	r4, [r5, #0x18]
000f67d4: eae6	b	#0xf65ac
000f67d6: 5f1c	adds	r7, r3, #1
000f67d8: 0597	str	r7, [sp, #0x14]
000f67da: 0b97	str	r7, [sp, #0x2c]
000f67dc: 21e7	b	#0xf6622
000f67de: 434a	ldr	r2, [pc, #0x10c]
000f67e0: 0026	movs	r6, #0
000f67e2: 0596	str	r6, [sp, #0x14]
000f67e4: 9046	mov	r8, r2
000f67e6: cbe6	b	#0xf6580
000f67e8: 9b45	cmp	fp, r3
000f67ea: 00d0	beq	#0xf67ee
000f67ec: 8846	mov	r8, r1
000f67ee: 0699	ldr	r1, [sp, #0x18]
000f67f0: 059a	ldr	r2, [sp, #0x14]
000f67f2: 9142	cmp	r1, r2
000f67f4: 75d9	bls	#0xf68e2
000f67f6: 171c	adds	r7, r2, #0
000f67f8: 0737	adds	r7, #7
000f67fa: 7f00	lsls	r7, r7, #1
000f67fc: c719	adds	r7, r0, r7
000f67fe: 7a78	ldrb	r2, [r7, #1]
000f6800: 3978	ldrb	r1, [r7]
000f6802: bf19	adds	r7, r7, r6
000f6804: 0397	str	r7, [sp, #0xc]
000f6806: 9246	mov	sl, r2
000f6808: 3a78	ldrb	r2, [r7]
000f680a: 8946	mov	sb, r1
000f680c: 1102	lsls	r1, r2, #8
000f680e: 7a78	ldrb	r2, [r7, #1]
000f6810: 1143	orrs	r1, r2
000f6812: 0a91	str	r1, [sp, #0x28]
000f6814: 8c42	cmp	r4, r1
000f6816: 64d3	blo	#0xf68e2
000f6818: 4f46	mov	r7, sb
000f681a: 3a02	lsls	r2, r7, #8
000f681c: 5146	mov	r1, sl
000f681e: 1143	orrs	r1, r2
000f6820: 0b91	str	r1, [sp, #0x2c]
000f6822: 0599	ldr	r1, [sp, #0x14]
000f6824: 059f	ldr	r7, [sp, #0x14]
000f6826: 0d96	str	r6, [sp, #0x34]
000f6828: 0831	adds	r1, #8
000f682a: 4900	lsls	r1, r1, #1
000f682c: 7218	adds	r2, r6, r1
000f682e: bb46	mov	fp, r7
000f6830: 6646	mov	r6, ip
000f6832: 8218	adds	r2, r0, r2
000f6834: 4118	adds	r1, r0, r1
000f6836: 0e90	str	r0, [sp, #0x38]
000f6838: 039f	ldr	r7, [sp, #0xc]
000f683a: 5846	mov	r0, fp
000f683c: 0296	str	r6, [sp, #8]
000f683e: a346	mov	fp, r4
000f6840: 0f95	str	r5, [sp, #0x3c]
000f6842: 1ae0	b	#0xf687a
000f6844: 069c	ldr	r4, [sp, #0x18]
000f6846: 431c	adds	r3, r0, #1
000f6848: 9c42	cmp	r4, r3
000f684a: 2bd9	bls	#0xf68a4
000f684c: 0c78	ldrb	r4, [r1]
000f684e: 4e78	ldrb	r6, [r1, #1]
000f6850: 171c	adds	r7, r2, #0
000f6852: a246	mov	sl, r4
000f6854: 1478	ldrb	r4, [r2]
000f6856: b146	mov	sb, r6
000f6858: 5678	ldrb	r6, [r2, #1]
000f685a: 2402	lsls	r4, r4, #8
000f685c: 0232	adds	r2, #2
000f685e: 3443	orrs	r4, r6
000f6860: a446	mov	ip, r4
000f6862: 0231	adds	r1, #2
000f6864: a345	cmp	fp, r4
000f6866: 1dd3	blo	#0xf68a4
000f6868: 5446	mov	r4, sl
000f686a: 2002	lsls	r0, r4, #8
000f686c: 4e46	mov	r6, sb
000f686e: 0643	orrs	r6, r0
000f6870: 6046	mov	r0, ip
000f6872: 0a90	str	r0, [sp, #0x28]
000f6874: 0b96	str	r6, [sp, #0x2c]
000f6876: 181c	adds	r0, r3, #0
000f6878: 2b1c	adds	r3, r5, #0
000f687a: 029c	ldr	r4, [sp, #8]
000f687c: 029e	ldr	r6, [sp, #8]
000f687e: 3f19	adds	r7, r7, r4
000f6880: 0025	movs	r5, #0
000f6882: 7d57	ldrsb	r5, [r7, r5]
000f6884: 7c78	ldrb	r4, [r7, #1]
000f6886: bf19	adds	r7, r7, r6
000f6888: 2d02	lsls	r5, r5, #8
000f688a: 2543	orrs	r5, r4
000f688c: 0995	str	r5, [sp, #0x24]
000f688e: 3d78	ldrb	r5, [r7]
000f6890: 7c78	ldrb	r4, [r7, #1]
000f6892: 164e	ldr	r6, [pc, #0x58]
000f6894: 2d02	lsls	r5, r5, #8
000f6896: 2c43	orrs	r4, r5
000f6898: 0194	str	r4, [sp, #4]
000f689a: 051c	adds	r5, r0, #0
000f689c: b442	cmp	r4, r6
000f689e: d1d1	bne	#0xf6844
000f68a0: 1d1c	adds	r5, r3, #0
000f68a2: cfe7	b	#0xf6844
000f68a4: 0397	str	r7, [sp, #0xc]
000f68a6: 029f	ldr	r7, [sp, #8]
000f68a8: 0595	str	r5, [sp, #0x14]
000f68aa: 019e	ldr	r6, [sp, #4]
000f68ac: bc46	mov	ip, r7
000f68ae: 0b99	ldr	r1, [sp, #0x2c]
000f68b0: 0a9a	ldr	r2, [sp, #0x28]
000f68b2: 059b	ldr	r3, [sp, #0x14]
000f68b4: 0c9f	ldr	r7, [sp, #0x30]
000f68b6: b246	mov	sl, r6
000f68b8: 5c46	mov	r4, fp
000f68ba: 0d9e	ldr	r6, [sp, #0x34]
000f68bc: 8346	mov	fp, r0
000f68be: 0f9d	ldr	r5, [sp, #0x3c]
000f68c0: 0e98	ldr	r0, [sp, #0x38]
000f68c2: 8846	mov	r8, r1
000f68c4: 0d92	str	r2, [sp, #0x34]
000f68c6: bb42	cmp	r3, r7
000f68c8: 00d0	beq	#0xf68cc
000f68ca: ffe6	b	#0xf66cc
000f68cc: 5846	mov	r0, fp
000f68ce: 0590	str	r0, [sp, #0x14]
000f68d0: 0026	movs	r6, #0
000f68d2: 55e6	b	#0xf6580
000f68d4: 9b46	mov	fp, r3
000f68d6: 8846	mov	r8, r1
000f68d8: f3e6	b	#0xf66c2
000f68da: 0022	movs	r2, #0
000f68dc: 8846	mov	r8, r1
000f68de: 9346	mov	fp, r2
000f68e0: efe6	b	#0xf66c2
000f68e2: 059b	ldr	r3, [sp, #0x14]
000f68e4: 0026	movs	r6, #0
000f68e6: 013b	subs	r3, #1
000f68e8: 0593	str	r3, [sp, #0x14]
000f68ea: 49e6	b	#0xf6580
000f68ec: ffff	.byte	0xff, 0xff
000f68ee: 0000	movs	r0, r0
