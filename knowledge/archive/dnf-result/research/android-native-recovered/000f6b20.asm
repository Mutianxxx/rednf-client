000f6b20: f0b5	push	{r4, r5, r6, r7, lr}
000f6b22: 4f46	mov	r7, sb
000f6b24: 4646	mov	r6, r8
000f6b26: c0b4	push	{r6, r7}
000f6b28: 274b	ldr	r3, [pc, #0x9c]
000f6b2a: 8846	mov	r8, r1
000f6b2c: 0a68	ldr	r2, [r1]
000f6b2e: 0169	ldr	r1, [r0, #0x10]
000f6b30: 264c	ldr	r4, [pc, #0x98]
000f6b32: 274d	ldr	r5, [pc, #0x9c]
000f6b34: c818	adds	r0, r1, r3
000f6b36: 0b19	adds	r3, r1, r4
000f6b38: 0478	ldrb	r4, [r0]
000f6b3a: 4819	adds	r0, r1, r5
000f6b3c: 0078	ldrb	r0, [r0]
000f6b3e: 2406	lsls	r4, r4, #0x18
000f6b40: 0235	adds	r5, #2
000f6b42: 0004	lsls	r0, r0, #0x10
000f6b44: 0443	orrs	r4, r0
000f6b46: 4819	adds	r0, r1, r5
000f6b48: 0078	ldrb	r0, [r0]
000f6b4a: 0443	orrs	r4, r0
000f6b4c: 2148	ldr	r0, [pc, #0x84]
000f6b4e: 0918	adds	r1, r1, r0
000f6b50: 0978	ldrb	r1, [r1]
000f6b52: 0902	lsls	r1, r1, #8
000f6b54: 0c43	orrs	r4, r1
000f6b56: 2fd0	beq	#0xf6bb8
000f6b58: 0132	adds	r2, #1
000f6b5a: 1878	ldrb	r0, [r3]
000f6b5c: 5978	ldrb	r1, [r3, #1]
000f6b5e: 5d7a	ldrb	r5, [r3, #9]
000f6b60: 0006	lsls	r0, r0, #0x18
000f6b62: 0904	lsls	r1, r1, #0x10
000f6b64: 0843	orrs	r0, r1
000f6b66: d978	ldrb	r1, [r3, #3]
000f6b68: ac46	mov	ip, r5
000f6b6a: 9f7a	ldrb	r7, [r3, #0xa]
000f6b6c: 0843	orrs	r0, r1
000f6b6e: 9978	ldrb	r1, [r3, #2]
000f6b70: 0902	lsls	r1, r1, #8
000f6b72: 0843	orrs	r0, r1
000f6b74: 197a	ldrb	r1, [r3, #8]
000f6b76: 8946	mov	sb, r1
000f6b78: d97a	ldrb	r1, [r3, #0xb]
000f6b7a: 8242	cmp	r2, r0
000f6b7c: 00d2	bhs	#0xf6b80
000f6b7e: 021c	adds	r2, r0, #0
000f6b80: 1e79	ldrb	r6, [r3, #4]
000f6b82: 5d79	ldrb	r5, [r3, #5]
000f6b84: 3606	lsls	r6, r6, #0x18
000f6b86: 2d04	lsls	r5, r5, #0x10
000f6b88: 3543	orrs	r5, r6
000f6b8a: de79	ldrb	r6, [r3, #7]
000f6b8c: 3543	orrs	r5, r6
000f6b8e: 9e79	ldrb	r6, [r3, #6]
000f6b90: 3602	lsls	r6, r6, #8
000f6b92: 3543	orrs	r5, r6
000f6b94: aa42	cmp	r2, r5
000f6b96: 0bd8	bhi	#0xf6bb0
000f6b98: 4d46	mov	r5, sb
000f6b9a: 2e06	lsls	r6, r5, #0x18
000f6b9c: 6546	mov	r5, ip
000f6b9e: 2d04	lsls	r5, r5, #0x10
000f6ba0: 3543	orrs	r5, r6
000f6ba2: 2943	orrs	r1, r5
000f6ba4: 3f02	lsls	r7, r7, #8
000f6ba6: 3943	orrs	r1, r7
000f6ba8: 081a	subs	r0, r1, r0
000f6baa: 8018	adds	r0, r0, r2
000f6bac: 0028	cmp	r0, #0
000f6bae: 05d1	bne	#0xf6bbc
000f6bb0: 013c	subs	r4, #1
000f6bb2: 0c33	adds	r3, #0xc
000f6bb4: 002c	cmp	r4, #0
000f6bb6: d0d1	bne	#0xf6b5a
000f6bb8: 0020	movs	r0, #0
000f6bba: 0022	movs	r2, #0
000f6bbc: 4146	mov	r1, r8
000f6bbe: 0a60	str	r2, [r1]
000f6bc0: 0cbc	pop	{r2, r3}
000f6bc2: 9046	mov	r8, r2
000f6bc4: 9946	mov	sb, r3
000f6bc6: f0bd	pop	{r4, r5, r6, r7, pc}
000f6bc8: 0c20	movs	r0, #0xc
000f6bca: 0000	movs	r0, r0
000f6bcc: 1020	movs	r0, #0x10
000f6bce: 0000	movs	r0, r0
000f6bd0: 0d20	movs	r0, #0xd
000f6bd2: 0000	movs	r0, r0
000f6bd4: 0e20	movs	r0, #0xe
000f6bd6: 0000	movs	r0, r0
