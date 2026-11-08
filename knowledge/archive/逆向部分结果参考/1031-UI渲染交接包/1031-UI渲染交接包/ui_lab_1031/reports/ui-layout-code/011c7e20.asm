
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c7e20 <.text>:
 11c7e20: a1 0c 65 b5 01               	mov	eax, dword ptr [0x1b5650c]
 11c7e25: c3                           	ret
 11c7e26: cc                           	int3
 11c7e27: cc                           	int3
 11c7e28: cc                           	int3
 11c7e29: cc                           	int3
 11c7e2a: cc                           	int3
 11c7e2b: cc                           	int3
 11c7e2c: cc                           	int3
 11c7e2d: cc                           	int3
 11c7e2e: cc                           	int3
 11c7e2f: cc                           	int3
 11c7e30: a1 10 65 b5 01               	mov	eax, dword ptr [0x1b56510]
 11c7e35: c3                           	ret
 11c7e36: cc                           	int3
 11c7e37: cc                           	int3
 11c7e38: cc                           	int3
 11c7e39: cc                           	int3
 11c7e3a: cc                           	int3
 11c7e3b: cc                           	int3
 11c7e3c: cc                           	int3
 11c7e3d: cc                           	int3
 11c7e3e: cc                           	int3
 11c7e3f: cc                           	int3
 11c7e40: 55                           	push	ebp
 11c7e41: 8b ec                        	mov	ebp, esp
 11c7e43: 83 ec 08                     	sub	esp, 0x8
 11c7e46: 56                           	push	esi
 11c7e47: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 11c7e4a: 57                           	push	edi
 11c7e4b: 83 fe ff                     	cmp	esi, -0x1
 11c7e4e: 74 2c                        	je	0x11c7e7c <.text+0x5c>
 11c7e50: e8 eb 06 01 00               	call	0x11d8540 <.text+0x10720>
 11c7e55: 8b c8                        	mov	ecx, eax
 11c7e57: e8 54 06 01 00               	call	0x11d84b0 <.text+0x10690>
 11c7e5c: 0f 57 c0                     	xorps	xmm0, xmm0
 11c7e5f: f2                           	repne
