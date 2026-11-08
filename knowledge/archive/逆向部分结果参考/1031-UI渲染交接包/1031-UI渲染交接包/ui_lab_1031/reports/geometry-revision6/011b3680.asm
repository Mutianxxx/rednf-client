
<stdin>:	file format elf32-i386

Disassembly of section .text:

011b3680 <.text>:
 11b3680: 8d 41 28                     	lea	eax, [ecx + 0x28]
 11b3683: c3                           	ret
 11b3684: cc                           	int3
 11b3685: cc                           	int3
 11b3686: cc                           	int3
 11b3687: cc                           	int3
 11b3688: cc                           	int3
 11b3689: cc                           	int3
 11b368a: cc                           	int3
 11b368b: cc                           	int3
 11b368c: cc                           	int3
 11b368d: cc                           	int3
 11b368e: cc                           	int3
 11b368f: cc                           	int3
 11b3690: 0f bf 41 28                  	movsx	eax, word ptr [ecx + 0x28]
 11b3694: a3 30 58 b5 01               	mov	dword ptr [0x1b55830], eax
 11b3699: 0f bf 51 2a                  	movsx	edx, word ptr [ecx + 0x2a]
 11b369d: 89 15 34 58 b5 01            	mov	dword ptr [0x1b55834], edx
 11b36a3: 0f bf 41 2c                  	movsx	eax, word ptr [ecx + 0x2c]
 11b36a7: a3 38 58 b5 01               	mov	dword ptr [0x1b55838], eax
 11b36ac: 0f bf 49 2e                  	movsx	ecx, word ptr [ecx + 0x2e]
 11b36b0: 89 0d 3c 58 b5 01            	mov	dword ptr [0x1b5583c], ecx
 11b36b6: b8 30 58 b5 01               	mov	eax, 0x1b55830
 11b36bb: c3                           	ret
