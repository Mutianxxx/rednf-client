
D:\game\DNF1031客户端-20260708\combat_ui_1031\reports\code-00818bf0.elf:	file format elf32-i386

Disassembly of section .text:

00818bf0 <.text>:
  818bf0: 55                           	push	ebp
  818bf1: 8b ec                        	mov	ebp, esp
  818bf3: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
  818bf6: 83 fa 02                     	cmp	edx, 0x2
  818bf9: 7d 1f                        	jge	0x818c1a <.text+0x2a>
  818bfb: 8b 84 91 34 2c 00 00         	mov	eax, dword ptr [ecx + 4*edx + 0x2c34]
  818c02: 85 c0                        	test	eax, eax
  818c04: 75 16                        	jne	0x818c1c <.text+0x2c>
  818c06: 8b 8c 91 f0 2c 00 00         	mov	ecx, dword ptr [ecx + 4*edx + 0x2cf0]
  818c0d: 85 c9                        	test	ecx, ecx
  818c0f: 74 09                        	je	0x818c1a <.text+0x2a>
  818c11: e8 9a 9f 88 00               	call	0x10a2bb0 <.text+0x889fc0>
  818c16: 5d                           	pop	ebp
  818c17: c2 04 00                     	ret	0x4
  818c1a: 33 c0                        	xor	eax, eax
  818c1c: 5d                           	pop	ebp
  818c1d: c2 04 00                     	ret	0x4
  818c20: 8b 81 3c 2c 00 00            	mov	eax, dword ptr [ecx + 0x2c3c]
  818c26: 85 c0                        	test	eax, eax
  818c28: 75 11                        	jne	0x818c3b <.text+0x4b>
  818c2a: 8b 89 f8 2c 00 00            	mov	ecx, dword ptr [ecx + 0x2cf8]
  818c30: 85 c9                        	test	ecx, ecx
  818c32: 74 05                        	je	0x818c39 <.text+0x49>
  818c34: e9 77 9f 88 00               	jmp	0x10a2bb0 <.text+0x889fc0>
  818c39: 33 c0                        	xor	eax, eax
  818c3b: c3                           	ret
  818c3c: cc                           	int3
  818c3d: cc                           	int3
  818c3e: cc                           	int3
  818c3f: cc                           	int3
  818c40: 8b 81 40 2c 00 00            	mov	eax, dword ptr [ecx + 0x2c40]
  818c46: 85 c0                        	test	eax, eax
  818c48: 75 11                        	jne	0x818c5b <.text+0x6b>
  818c4a: 8b 89 fc 2c 00 00            	mov	ecx, dword ptr [ecx + 0x2cfc]
  818c50: 85 c9                        	test	ecx, ecx
  818c52: 74 05                        	je	0x818c59 <.text+0x69>
  818c54: e9 57 9f 88 00               	jmp	0x10a2bb0 <.text+0x889fc0>
  818c59: 33 c0                        	xor	eax, eax
  818c5b: c3                           	ret
  818c5c: cc                           	int3
  818c5d: cc                           	int3
  818c5e: cc                           	int3
  818c5f: cc                           	int3
  818c60: 56                           	push	esi
  818c61: 8b f1                        	mov	esi, ecx
  818c63: 8b 86 1c 2c 00 00            	mov	eax, dword ptr [esi + 0x2c1c]
  818c69: 85 c0                        	test	eax, eax
  818c6b: 75 24                        	jne	0x818c91 <.text+0xa1>
  818c6d: 8b 06                        	mov	eax, dword ptr [esi]
  818c6f: 8b 90 a0 04 00 00            	mov	edx, dword ptr [eax + 0x4a0]
