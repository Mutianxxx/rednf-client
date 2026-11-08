
<stdin>:	file format elf32-i386

Disassembly of section .text:

010124f0 <.text>:
 10124f0: c4 14 89                     	les	edx, [ecx + 4*ecx]
 10124f3: 45                           	inc	ebp
 10124f4: f0                           	lock
 10124f5: 85 c0                        	test	eax, eax
 10124f7: 0f 84 90 00 00 00            	je	0x101258d <.text+0x9d>
 10124fd: e8 0e 3f 6f ff               	call	0x706410
 1012502: 8b c8                        	mov	ecx, eax
 1012504: e8 17 83 74 ff               	call	0x75a820
 1012509: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 101250c: e8 4f da 41 ff               	call	0x42ff60
 1012511: 8b 9e a0 01 00 00            	mov	ebx, dword ptr [esi + 0x1a0]
 1012517: 2b 9e 9c 01 00 00            	sub	ebx, dword ptr [esi + 0x19c]
 101251d: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 1012520: 89 45 ec                     	mov	dword ptr [ebp - 0x14], eax
 1012523: c1 fb 02                     	sar	ebx, 0x2
 1012526: e8 d5 bd 1a 00               	call	0x11be300 <.text+0x1abe10>
 101252b: 8b 8e 30 01 00 00            	mov	ecx, dword ptr [esi + 0x130]
 1012531: 43                           	inc	ebx
 1012532: 6b db 15                     	imul	ebx, ebx, 0x15
 1012535: 03 c3                        	add	eax, ebx
 1012537: 6a 01                        	push	0x1
 1012539: 50                           	push	eax
 101253a: 8b 45 ec                     	mov	eax, dword ptr [ebp - 0x14]
 101253d: 50                           	push	eax
 101253e: e8 8d c5 1a 00               	call	0x11bead0 <.text+0x1ac5e0>
 1012543: 8b 8e 30 01 00 00            	mov	ecx, dword ptr [esi + 0x130]
 1012549: 8b 11                        	mov	edx, dword ptr [ecx]
 101254b: 8b 42 10                     	mov	eax, dword ptr [edx + 0x10]
 101254e: 6a 01                        	push	0x1
 1012550: ff d0                        	call	eax
 1012552: 8d 4d ec                     	lea	ecx, [ebp - 0x14]
 1012555: 51                           	push	ecx
 1012556: 8d 8e 98 01 00 00            	lea	ecx, [esi + 0x198]
 101255c: c7 45 ec 31 00 00 00         	mov	dword ptr [ebp - 0x14], 0x31
 1012563: e8 08 12 48 ff               	call	0x493770
 1012568: 8b 0d 18 f7 a6 01            	mov	ecx, dword ptr [0x1a6f718]
 101256e: e8 8d 2a 91 ff               	call	0x925000
 1012573: 83 b8 c8 02 00 00 00         	cmp	dword ptr [eax + 0x2c8], 0x0
 101257a: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 101257d: 75 04                        	jne	0x1012583 <.text+0x93>
 101257f: 6a 01                        	push	0x1
 1012581: eb 02                        	jmp	0x1012585 <.text+0x95>
 1012583: 6a 02                        	push	0x2
 1012585: e8 b6 06 ff ff               	call	0x1002c40
 101258a: 8b 5d f4                     	mov	ebx, dword ptr [ebp - 0xc]
 101258d: 83 fb 02                     	cmp	ebx, 0x2
 1012590: 74 09                        	je	0x101259b <.text+0xab>
 1012592: 83 fb 04                     	cmp	ebx, 0x4
 1012595: 0f 85 f3 00 00 00            	jne	0x101268e <.text+0x19e>
 101259b: 8b 0d 18 f7 a6 01            	mov	ecx, dword ptr [0x1a6f718]
 10125a1: e8 5a 2a 91 ff               	call	0x925000
 10125a6: 83 b8 c8 02 00 00 01         	cmp	dword ptr [eax + 0x2c8], 0x1
 10125ad: 74 18                        	je	0x10125c7 <.text+0xd7>
 10125af: 8b 0d 18 f7 a6 01            	mov	ecx, dword ptr [0x1a6f718]
 10125b5: e8 46 2a 91 ff               	call	0x925000
 10125ba: 83 b8 c8 02 00 00 03         	cmp	dword ptr [eax + 0x2c8], 0x3
 10125c1: 0f 85 c7 00 00 00            	jne	0x101268e <.text+0x19e>
 10125c7: 8b 96 34 01 00 00            	mov	edx, dword ptr [esi + 0x134]
 10125cd: 6a 00                        	push	0x0
 10125cf: 68 5c e6 a3 01               	push	0x1a3e65c
 10125d4: 68 78 99 9d 01               	push	0x19d9978
 10125d9: 6a 00                        	push	0x0
 10125db: 52                           	push	edx
 10125dc: e8 fe 50 3c 00               	call	0x13d76df <.text+0x3c51ef>
 10125e1: 83 c4 14                     	add	esp, 0x14
 10125e4: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 10125e7: 85 c0                        	test	eax, eax
 10125e9: 0f 84 9f 00 00 00            	je	0x101268e <.text+0x19e>
 10125ef: e8 1c 3e 6f ff               	call	0x706410
 10125f4: 8b c8                        	mov	ecx, eax
 10125f6: e8 25 82 74 ff               	call	0x75a820
 10125fb: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 10125fe: e8 5d d9 41 ff               	call	0x42ff60
 1012603: 8b 9e a0 01 00 00            	mov	ebx, dword ptr [esi + 0x1a0]
 1012609: 2b 9e 9c 01 00 00            	sub	ebx, dword ptr [esi + 0x19c]
 101260f: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 1012612: 89 45 ec                     	mov	dword ptr [ebp - 0x14], eax
 1012615: c1 fb 02                     	sar	ebx, 0x2
 1012618: e8 e3 bc 1a 00               	call	0x11be300 <.text+0x1abe10>
 101261d: 8b 8e 34 01 00 00            	mov	ecx, dword ptr [esi + 0x134]
 1012623: 43                           	inc	ebx
 1012624: 6b db 15                     	imul	ebx, ebx, 0x15
 1012627: 03 c3                        	add	eax, ebx
 1012629: 6a 01                        	push	0x1
 101262b: 50                           	push	eax
 101262c: 8b 45 ec                     	mov	eax, dword ptr [ebp - 0x14]
 101262f: 50                           	push	eax
 1012630: e8 9b c4 1a 00               	call	0x11bead0 <.text+0x1ac5e0>
 1012635: 8b 8e 34 01 00 00            	mov	ecx, dword ptr [esi + 0x134]
 101263b: 8b 11                        	mov	edx, dword ptr [ecx]
 101263d: 8b 42 10                     	mov	eax, dword ptr [edx + 0x10]
 1012640: 6a 01                        	push	0x1
 1012642: ff d0                        	call	eax
 1012644: 8d 4d ec                     	lea	ecx, [ebp - 0x14]
 1012647: 51                           	push	ecx
 1012648: 8d 8e 98 01 00 00            	lea	ecx, [esi + 0x198]
 101264e: c7 45 ec 32 00 00 00         	mov	dword ptr [ebp - 0x14], 0x32
 1012655: e8 16 11 48 ff               	call	0x493770
 101265a: 8d 55 ec                     	lea	edx, [ebp - 0x14]
 101265d: 52                           	push	edx
 101265e: 68 18 7a ac 01               	push	0x1ac7a18
 1012663: b9 10 7a ac 01               	mov	ecx, 0x1ac7a10
 1012668: e8 73 e7 18 00               	call	0x11a0de0 <.text+0x18e8f0>
 101266d: 8b 45 ec                     	mov	eax, dword ptr [ebp - 0x14]
 1012670: 50                           	push	eax
 1012671: e8 aa 52 92 ff               	call	0x937920
 1012676: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 1012679: 83 c4 04                     	add	esp, 0x4
 101267c: 84 c0                        	test	al, al
 101267e: 74 04                        	je	0x1012684 <.text+0x194>
 1012680: 6a 02                        	push	0x2
 1012682: eb 02                        	jmp	0x1012686 <.text+0x196>
 1012684: 6a 01                        	push	0x1
 1012686: e8 b5 05 ff ff               	call	0x1002c40
 101268b: 8b 5d f4                     	mov	ebx, dword ptr [ebp - 0xc]
 101268e: 83 fb 03                     	cmp	ebx, 0x3
 1012691: 74 09                        	je	0x101269c <.text+0x1ac>
 1012693: 83 fb 05                     	cmp	ebx, 0x5
 1012696: 0f 85 f0 00 00 00            	jne	0x101278c <.text+0x29c>
 101269c: 8b 0d 18 f7 a6 01            	mov	ecx, dword ptr [0x1a6f718]
 10126a2: e8 59 29 91 ff               	call	0x925000
 10126a7: 83 b8 c8 02 00 00 02         	cmp	dword ptr [eax + 0x2c8], 0x2
 10126ae: 74 18                        	je	0x10126c8 <.text+0x1d8>
 10126b0: 8b 0d 18 f7 a6 01            	mov	ecx, dword ptr [0x1a6f718]
 10126b6: e8 45 29 91 ff               	call	0x925000
 10126bb: 83 b8 c8 02 00 00 04         	cmp	dword ptr [eax + 0x2c8], 0x4
 10126c2: 0f 85 c4 00 00 00            	jne	0x101278c <.text+0x29c>
 10126c8: 8b 8e 34 01 00 00            	mov	ecx, dword ptr [esi + 0x134]
 10126ce: 6a 00                        	push	0x0
 10126d0: 68 5c e6 a3 01               	push	0x1a3e65c
 10126d5: 68 78 99 9d 01               	push	0x19d9978
 10126da: 6a 00                        	push	0x0
 10126dc: 51                           	push	ecx
 10126dd: e8 fd 4f 3c 00               	call	0x13d76df <.text+0x3c51ef>
 10126e2: 83 c4 14                     	add	esp, 0x14
 10126e5: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 10126e8: 85 c0                        	test	eax, eax
 10126ea: 0f 84 9c 00 00 00            	je	0x101278c <.text+0x29c>
 10126f0: e8 1b 3d 6f ff               	call	0x706410
 10126f5: 8b c8                        	mov	ecx, eax
 10126f7: e8 24 81 74 ff               	call	0x75a820
 10126fc: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 10126ff: e8 5c d8 41 ff               	call	0x42ff60
 1012704: 8b 9e a0 01 00 00            	mov	ebx, dword ptr [esi + 0x1a0]
 101270a: 2b 9e 9c 01 00 00            	sub	ebx, dword ptr [esi + 0x19c]
 1012710: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 1012713: 89 45 ec                     	mov	dword ptr [ebp - 0x14], eax
 1012716: c1 fb 02                     	sar	ebx, 0x2
 1012719: e8 e2 bb 1a 00               	call	0x11be300 <.text+0x1abe10>
 101271e: 8b 55 ec                     	mov	edx, dword ptr [ebp - 0x14]
 1012721: 8b 8e 34 01 00 00            	mov	ecx, dword ptr [esi + 0x134]
 1012727: 43                           	inc	ebx
 1012728: 6b db 15                     	imul	ebx, ebx, 0x15
 101272b: 6a 01                        	push	0x1
 101272d: 03 c3                        	add	eax, ebx
 101272f: 50                           	push	eax
 1012730: 52                           	push	edx
 1012731: e8 9a c3 1a 00               	call	0x11bead0 <.text+0x1ac5e0>
 1012736: 8b 8e 34 01 00 00            	mov	ecx, dword ptr [esi + 0x134]
 101273c: 8b 01                        	mov	eax, dword ptr [ecx]
 101273e: 8b 50 10                     	mov	edx, dword ptr [eax + 0x10]
 1012741: 6a 01                        	push	0x1
 1012743: ff d2                        	call	edx
 1012745: 8d 45 ec                     	lea	eax, [ebp - 0x14]
 1012748: 50                           	push	eax
 1012749: 8d 8e 98 01 00 00            	lea	ecx, [esi + 0x198]
 101274f: c7 45 ec 32 00 00 00         	mov	dword ptr [ebp - 0x14], 0x32
 1012756: e8 15 10 48 ff               	call	0x493770
 101275b: 8d 4d ec                     	lea	ecx, [ebp - 0x14]
 101275e: 51                           	push	ecx
 101275f: 68 18 7a ac 01               	push	0x1ac7a18
 1012764: b9 10 7a ac 01               	mov	ecx, 0x1ac7a10
 1012769: e8 72 e6 18 00               	call	0x11a0de0 <.text+0x18e8f0>
 101276e: 8b 55 ec                     	mov	edx, dword ptr [ebp - 0x14]
 1012771: 52                           	push	edx
 1012772: e8 a9 51 92 ff               	call	0x937920
 1012777: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 101277a: 83 c4 04                     	add	esp, 0x4
 101277d: 84 c0                        	test	al, al
 101277f: 74 04                        	je	0x1012785 <.text+0x295>
 1012781: 6a 02                        	push	0x2
 1012783: eb 02                        	jmp	0x1012787 <.text+0x297>
 1012785: 6a 01                        	push	0x1
 1012787: e8 b4 04 ff ff               	call	0x1002c40
 101278c: 8b 4d f8                     	mov	ecx, dword ptr [ebp - 0x8]
 101278f: 6a 09                        	push	0x9
 1012791: e8 ba c4 70 ff               	call	0x71ec50
 1012796: 84 c0                        	test	al, al
 1012798: 74 6b                        	je	0x1012805 <.text+0x315>
 101279a: e8 71 3c 6f ff               	call	0x706410
 101279f: 8b c8                        	mov	ecx, eax
 10127a1: e8 7a 80 74 ff               	call	0x75a820
 10127a6: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 10127a9: e8 b2 d7 41 ff               	call	0x42ff60
 10127ae: 8b 9e a0 01 00 00            	mov	ebx, dword ptr [esi + 0x1a0]
 10127b4: 2b 9e 9c 01 00 00            	sub	ebx, dword ptr [esi + 0x19c]
 10127ba: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 10127bd: 89 45 ec                     	mov	dword ptr [ebp - 0x14], eax
 10127c0: c1 fb 02                     	sar	ebx, 0x2
 10127c3: e8 38 bb 1a 00               	call	0x11be300 <.text+0x1abe10>
 10127c8: 8b 8e 38 01 00 00            	mov	ecx, dword ptr [esi + 0x138]
 10127ce: 43                           	inc	ebx
 10127cf: 6b db 15                     	imul	ebx, ebx, 0x15
 10127d2: 03 c3                        	add	eax, ebx
 10127d4: 6a 01                        	push	0x1
 10127d6: 50                           	push	eax
 10127d7: 8b 45 ec                     	mov	eax, dword ptr [ebp - 0x14]
 10127da: 50                           	push	eax
 10127db: e8 f0 c2 1a 00               	call	0x11bead0 <.text+0x1ac5e0>
 10127e0: 8b 8e 38 01 00 00            	mov	ecx, dword ptr [esi + 0x138]
 10127e6: 8b 11                        	mov	edx, dword ptr [ecx]
 10127e8: 8b 42 10                     	mov	eax, dword ptr [edx + 0x10]
 10127eb: 6a 01                        	push	0x1
 10127ed: ff d0                        	call	eax
 10127ef: 8d 4d ec                     	lea	ecx, [ebp - 0x14]
 10127f2: 51                           	push	ecx
 10127f3: 8d 8e 98 01 00 00            	lea	ecx, [esi + 0x198]
 10127f9: c7 45 ec 33 00 00 00         	mov	dword ptr [ebp - 0x14], 0x33
 1012800: e8 6b 0f 48 ff               	call	0x493770
 1012805: 8b 4d f8                     	mov	ecx, dword ptr [ebp - 0x8]
 1012808: 6a 0e                        	push	0xe
 101280a: e8 41 c4 70 ff               	call	0x71ec50
 101280f: 84 c0                        	test	al, al
 1012811: 0f 84 4a 01 00 00            	je	0x1012961 <.text+0x471>
 1012817: e8 f4 3b 6f ff               	call	0x706410
 101281c: 80 b8 a0 00 0b 00 00         	cmp	byte ptr [eax + 0xb00a0], 0x0
 1012823: 0f 84 cd 00 00 00            	je	0x10128f6 <.text+0x406>
 1012829: e8 e2 3b 6f ff               	call	0x706410
 101282e: 8b c8                        	mov	ecx, eax
 1012830: e8 eb 7f 74 ff               	call	0x75a820
 1012835: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 1012838: e8 23 d7 41 ff               	call	0x42ff60
 101283d: 8b 9e a0 01 00 00            	mov	ebx, dword ptr [esi + 0x1a0]
 1012843: 2b 9e 9c 01 00 00            	sub	ebx, dword ptr [esi + 0x19c]
 1012849: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 101284c: 89 45 ec                     	mov	dword ptr [ebp - 0x14], eax
 101284f: c1 fb 02                     	sar	ebx, 0x2
 1012852: e8 a9 ba 1a 00               	call	0x11be300 <.text+0x1abe10>
 1012857: 8b 55 ec                     	mov	edx, dword ptr [ebp - 0x14]
 101285a: 8b 8e 44 01 00 00            	mov	ecx, dword ptr [esi + 0x144]
 1012860: 43                           	inc	ebx
 1012861: 6b db 15                     	imul	ebx, ebx, 0x15
 1012864: 6a 01                        	push	0x1
 1012866: 03 c3                        	add	eax, ebx
 1012868: 50                           	push	eax
 1012869: 52                           	push	edx
 101286a: e8 61 c2 1a 00               	call	0x11bead0 <.text+0x1ac5e0>
 101286f: 8b                           	<unknown>
