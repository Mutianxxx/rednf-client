
<stdin>:	file format elf32-i386

Disassembly of section .text:

004e7790 <.text>:
  4e7790: 55                           	push	ebp
  4e7791: 8b ec                        	mov	ebp, esp
  4e7793: 83 ec 18                     	sub	esp, 0x18
  4e7796: 53                           	push	ebx
  4e7797: 56                           	push	esi
  4e7798: 57                           	push	edi
  4e7799: 8d 71 04                     	lea	esi, [ecx + 0x4]
  4e779c: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  4e779f: 50                           	push	eax
  4e77a0: 8b ce                        	mov	ecx, esi
  4e77a2: e8 29 97 ce 00               	call	0x11d0ed0 <.text+0xce9740>
  4e77a7: 8d 4d e8                     	lea	ecx, [ebp - 0x18]
  4e77aa: 51                           	push	ecx
  4e77ab: 8b ce                        	mov	ecx, esi
  4e77ad: e8 de 7f 2c 00               	call	0x7af790 <.text+0x2c8000>
  4e77b2: 33 db                        	xor	ebx, ebx
  4e77b4: 8b 7d f4                     	mov	edi, dword ptr [ebp - 0xc]
  4e77b7: 85 ff                        	test	edi, edi
  4e77b9: 0f 84 d7 00 00 00            	je	0x4e7896 <.text+0x106>
  4e77bf: 8b 07                        	mov	eax, dword ptr [edi]
  4e77c1: 85 c0                        	test	eax, eax
  4e77c3: 0f 84 cd 00 00 00            	je	0x4e7896 <.text+0x106>
  4e77c9: 8b 4d e8                     	mov	ecx, dword ptr [ebp - 0x18]
  4e77cc: 85 c9                        	test	ecx, ecx
  4e77ce: 74 02                        	je	0x4e77d2 <.text+0x42>
  4e77d0: 8b 09                        	mov	ecx, dword ptr [ecx]
  4e77d2: 3b c1                        	cmp	eax, ecx
  4e77d4: 0f 85 bc 00 00 00            	jne	0x4e7896 <.text+0x106>
  4e77da: 8b 55 fc                     	mov	edx, dword ptr [ebp - 0x4]
  4e77dd: 3b 55 f0                     	cmp	edx, dword ptr [ebp - 0x10]
  4e77e0: 0f 84 b5 00 00 00            	je	0x4e789b <.text+0x10b>
  4e77e6: 85 c0                        	test	eax, eax
  4e77e8: 0f 84 a8 00 00 00            	je	0x4e7896 <.text+0x106>
  4e77ee: 85 d2                        	test	edx, edx
  4e77f0: 0f 84 a0 00 00 00            	je	0x4e7896 <.text+0x106>
  4e77f6: 3b 50 04                     	cmp	edx, dword ptr [eax + 0x4]
  4e77f9: 0f 84 97 00 00 00            	je	0x4e7896 <.text+0x106>
  4e77ff: 8b 72 0c                     	mov	esi, dword ptr [edx + 0xc]
  4e7802: 85 f6                        	test	esi, esi
  4e7804: 74 7b                        	je	0x4e7881 <.text+0xf1>
  4e7806: 80 7e 08 00                  	cmp	byte ptr [esi + 0x8], 0x0
  4e780a: 74 75                        	je	0x4e7881 <.text+0xf1>
  4e780c: 8b 0e                        	mov	ecx, dword ptr [esi]
  4e780e: 85 c9                        	test	ecx, ecx
  4e7810: 74 6f                        	je	0x4e7881 <.text+0xf1>
  4e7812: b8 ab aa aa 2a               	mov	eax, 0x2aaaaaab
  4e7817: f7 eb                        	imul	ebx
  4e7819: d1 fa                        	sar	edx
  4e781b: 8b c2                        	mov	eax, edx
  4e781d: c1 e8 1f                     	shr	eax, 0x1f
  4e7820: 03 c2                        	add	eax, edx
  4e7822: 8d 14 80                     	lea	edx, [eax + 4*eax]
  4e7825: 8d 04 40                     	lea	eax, [eax + 2*eax]
  4e7828: 03 c0                        	add	eax, eax
  4e782a: 03 d2                        	add	edx, edx
  4e782c: 03 d2                        	add	edx, edx
  4e782e: bf 12 02 00 00               	mov	edi, 0x212
  4e7833: 2b fa                        	sub	edi, edx
  4e7835: 8d 14 00                     	lea	edx, [eax + eax]
  4e7838: 8b c3                        	mov	eax, ebx
  4e783a: 2b c2                        	sub	eax, edx
  4e783c: 8d 44 80 46                  	lea	eax, [eax + 4*eax + 0x46]
  4e7840: 6a 01                        	push	0x1
  4e7842: 03 c0                        	add	eax, eax
  4e7844: 57                           	push	edi
  4e7845: 03 c0                        	add	eax, eax
  4e7847: 50                           	push	eax
  4e7848: e8 83 72 cd 00               	call	0x11bead0 <.text+0xcd7340>
  4e784d: 83 7e 04 00                  	cmp	dword ptr [esi + 0x4], 0x0
  4e7851: 74 27                        	je	0x4e787a <.text+0xea>
  4e7853: 8b 0e                        	mov	ecx, dword ptr [esi]
  4e7855: e8 f6 86 d3 00               	call	0x121ff50 <.text+0xd387c0>
  4e785a: 8b 0e                        	mov	ecx, dword ptr [esi]
  4e785c: 8b f8                        	mov	edi, eax
  4e785e: 6a 01                        	push	0x1
  4e7860: d1 ef                        	shr	edi
  4e7862: e8 99 6a cd 00               	call	0x11be300 <.text+0xcd6b70>
  4e7867: 8b 0e                        	mov	ecx, dword ptr [esi]
  4e7869: 50                           	push	eax
  4e786a: e8 f1 86 f4 ff               	call	0x42ff60
  4e786f: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  4e7872: 03 c7                        	add	eax, edi
  4e7874: 50                           	push	eax
  4e7875: e8 56 72 cd 00               	call	0x11bead0 <.text+0xcd7340>
  4e787a: 8b 7d f4                     	mov	edi, dword ptr [ebp - 0xc]
  4e787d: 8b 55 fc                     	mov	edx, dword ptr [ebp - 0x4]
  4e7880: 43                           	inc	ebx
  4e7881: 8b 07                        	mov	eax, dword ptr [edi]
  4e7883: 85 c0                        	test	eax, eax
  4e7885: 74 0f                        	je	0x4e7896 <.text+0x106>
  4e7887: 3b 50 04                     	cmp	edx, dword ptr [eax + 0x4]
  4e788a: 74 0a                        	je	0x4e7896 <.text+0x106>
  4e788c: 8b 0a                        	mov	ecx, dword ptr [edx]
  4e788e: 89 4d fc                     	mov	dword ptr [ebp - 0x4], ecx
  4e7891: e9 1e ff ff ff               	jmp	0x4e77b4 <.text+0x24>
  4e7896: e8 0c f5 ee 00               	call	0x13d6da7 <.text+0xeef617>
  4e789b: 5f                           	pop	edi
  4e789c: 5e                           	pop	esi
  4e789d: 5b                           	pop	ebx
  4e789e: 8b e5                        	mov	esp, ebp
  4e78a0: 5d                           	pop	ebp
  4e78a1: c3                           	ret
  4e78a2: cc                           	int3
  4e78a3: cc                           	int3
  4e78a4: cc                           	int3
  4e78a5: cc                           	int3
  4e78a6: cc                           	int3
  4e78a7: cc                           	int3
  4e78a8: cc                           	int3
  4e78a9: cc                           	int3
  4e78aa: cc                           	int3
  4e78ab: cc                           	int3
  4e78ac: cc                           	int3
  4e78ad: cc                           	int3
  4e78ae: cc                           	int3
  4e78af: cc                           	int3
  4e78b0: 55                           	push	ebp
  4e78b1: 8b ec                        	mov	ebp, esp
  4e78b3: 83 ec 14                     	sub	esp, 0x14
  4e78b6: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
  4e78b9: 53                           	push	ebx
  4e78ba: 56                           	push	esi
  4e78bb: 8b f1                        	mov	esi, ecx
  4e78bd: 0f b6 08                     	movzx	ecx, byte ptr [eax]
  4e78c0: 57                           	push	edi
  4e78c1: 81 f1 ef be ad de            	xor	ecx, 0xdeadbeef
  4e78c7: 81 e1 ff ff ff 7f            	and	ecx, 0x7fffffff
  4e78cd: 68 1d f3 01 00               	push	0x1f31d
  4e78d2: 51                           	push	ecx
  4e78d3: 89 75 fc                     	mov	dword ptr [ebp - 0x4], esi
  4e78d6: c7 45 f8 00 00 00 00         	mov	dword ptr [ebp - 0x8], 0x0
  4e78dd: e8 e9 13 ef 00               	call	0x13d8ccb <.text+0xef153b>
  4e78e2: 69 d2 a7 41 00 00            	imul	edx, edx, 0x41a7
  4e78e8: 69 c0 14 0b 00 00            	imul	eax, eax, 0xb14
  4e78ee: 83 c4 08                     	add	esp, 0x8
  4e78f1: 2b d0                        	sub	edx, eax
  4e78f3: 79 06                        	jns	0x4e78fb <.text+0x16b>
  4e78f5: 81 c2 ff ff ff 7f            	add	edx, 0x7fffffff
  4e78fb: 8b 46 2c                     	mov	eax, dword ptr [esi + 0x2c]
  4e78fe: 8b d8                        	mov	ebx, eax
  4e7900: 23 da                        	and	ebx, edx
  4e7902: 39 5e 30                     	cmp	dword ptr [esi + 0x30], ebx
  4e7905: 77 09                        	ja	0x4e7910 <.text+0x180>
  4e7907: d1 e8                        	shr	eax
  4e7909: 83 ca ff                     	or	edx, -0x1
  4e790c: 2b d0                        	sub	edx, eax
  4e790e: 03 da                        	add	ebx, edx
  4e7910: 53                           	push	ebx
  4e7911: 8d 45 ec                     	lea	eax, [ebp - 0x14]
  4e7914: 50                           	push	eax
  4e7915: 8b ce                        	mov	ecx, esi
  4e7917: e8 e4 db 04 00               	call	0x535500 <.text+0x4dd70>
  4e791c: 8b 7d ec                     	mov	edi, dword ptr [ebp - 0x14]
  4e791f: 8b                           	<unknown>
