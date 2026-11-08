008aebb0  55                       push       ebp
008aebb1  8bec                     mov        ebp, esp
008aebb3  8b4508                   mov        eax, dword ptr [ebp + 8]
008aebb6  c70000000000             mov        dword ptr [eax], 0
008aebbc  c7400400000000           mov        dword ptr [eax + 4], 0
008aebc3  c7400867e6096a           mov        dword ptr [eax + 8], 0x6a09e667
008aebca  c7400c85ae67bb           mov        dword ptr [eax + 0xc], 0xbb67ae85
008aebd1  c7401072f36e3c           mov        dword ptr [eax + 0x10], 0x3c6ef372
008aebd8  c740143af54fa5           mov        dword ptr [eax + 0x14], 0xa54ff53a
008aebdf  c740187f520e51           mov        dword ptr [eax + 0x18], 0x510e527f
008aebe6  c7401c8c68059b           mov        dword ptr [eax + 0x1c], 0x9b05688c
008aebed  c74020abd9831f           mov        dword ptr [eax + 0x20], 0x1f83d9ab
008aebf4  c7402419cde05b           mov        dword ptr [eax + 0x24], 0x5be0cd19
008aebfb  5d                       pop        ebp
008aebfc  c3                       ret        
008aebfd  cc                       int3       
008aebfe  cc                       int3       
008aebff  cc                       int3       
008aec00  55                       push       ebp
008aec01  8bec                     mov        ebp, esp
008aec03  81ec20010000             sub        esp, 0x120
008aec09  8b450c                   mov        eax, dword ptr [ebp + 0xc]
008aec0c  33c9                     xor        ecx, ecx
008aec0e  8a28                     mov        ch, byte ptr [eax]
008aec10  0fb65002                 movzx      edx, byte ptr [eax + 2]
008aec14  53                       push       ebx
008aec15  56                       push       esi
008aec16  57                       push       edi
008aec17  8a4801                   mov        cl, byte ptr [eax + 1]
008aec1a  c1e108                   shl        ecx, 8
008aec1d  0bca                     or         ecx, edx
008aec1f  c1e108                   shl        ecx, 8
008aec22  0fb65003                 movzx      edx, byte ptr [eax + 3]
008aec26  0bca                     or         ecx, edx
008aec28  898de0feffff             mov        dword ptr [ebp - 0x120], ecx
008aec2e  33c9                     xor        ecx, ecx
008aec30  8a6804                   mov        ch, byte ptr [eax + 4]
008aec33  0fb65006                 movzx      edx, byte ptr [eax + 6]
008aec37  8a4805                   mov        cl, byte ptr [eax + 5]
008aec3a  c1e108                   shl        ecx, 8
008aec3d  0bca                     or         ecx, edx
008aec3f  c1e108                   shl        ecx, 8
008aec42  0fb65007                 movzx      edx, byte ptr [eax + 7]
008aec46  0bca                     or         ecx, edx
008aec48  898de4feffff             mov        dword ptr [ebp - 0x11c], ecx
008aec4e  33c9                     xor        ecx, ecx
008aec50  8a6808                   mov        ch, byte ptr [eax + 8]
008aec53  0fb6500a                 movzx      edx, byte ptr [eax + 0xa]
008aec57  8a4809                   mov        cl, byte ptr [eax + 9]
008aec5a  c1e108                   shl        ecx, 8
008aec5d  0bca                     or         ecx, edx
008aec5f  0fb6500b                 movzx      edx, byte ptr [eax + 0xb]
008aec63  c1e108                   shl        ecx, 8
008aec66  0bca                     or         ecx, edx
008aec68  898de8feffff             mov        dword ptr [ebp - 0x118], ecx
008aec6e  33c9                     xor        ecx, ecx
008aec70  8a680c                   mov        ch, byte ptr [eax + 0xc]
008aec73  0fb6500e                 movzx      edx, byte ptr [eax + 0xe]
008aec77  8a480d                   mov        cl, byte ptr [eax + 0xd]
008aec7a  c1e108                   shl        ecx, 8
008aec7d  0bca                     or         ecx, edx
008aec7f  0fb6500f                 movzx      edx, byte ptr [eax + 0xf]
008aec83  c1e108                   shl        ecx, 8
008aec86  0bca                     or         ecx, edx
008aec88  898decfeffff             mov        dword ptr [ebp - 0x114], ecx
008aec8e  33c9                     xor        ecx, ecx
008aec90  8a6810                   mov        ch, byte ptr [eax + 0x10]
008aec93  0fb65012                 movzx      edx, byte ptr [eax + 0x12]
008aec97  8a4811                   mov        cl, byte ptr [eax + 0x11]
008aec9a  c1e108                   shl        ecx, 8
008aec9d  0bca                     or         ecx, edx
008aec9f  0fb65013                 movzx      edx, byte ptr [eax + 0x13]
008aeca3  c1e108                   shl        ecx, 8
008aeca6  0bca                     or         ecx, edx
008aeca8  898df0feffff             mov        dword ptr [ebp - 0x110], ecx
008aecae  33c9                     xor        ecx, ecx
008aecb0  8a6814                   mov        ch, byte ptr [eax + 0x14]
008aecb3  0fb65016                 movzx      edx, byte ptr [eax + 0x16]
008aecb7  8a4815                   mov        cl, byte ptr [eax + 0x15]
008aecba  c1e108                   shl        ecx, 8
008aecbd  0bca                     or         ecx, edx
008aecbf  0fb65017                 movzx      edx, byte ptr [eax + 0x17]
008aecc3  c1e108                   shl        ecx, 8
008aecc6  0bca                     or         ecx, edx
008aecc8  0fb6501a                 movzx      edx, byte ptr [eax + 0x1a]
008aeccc  898df4feffff             mov        dword ptr [ebp - 0x10c], ecx
008aecd2  33c9                     xor        ecx, ecx
008aecd4  8a6818                   mov        ch, byte ptr [eax + 0x18]
008aecd7  8a4819                   mov        cl, byte ptr [eax + 0x19]
008aecda  c1e108                   shl        ecx, 8
008aecdd  0bca                     or         ecx, edx
008aecdf  0fb6501b                 movzx      edx, byte ptr [eax + 0x1b]
008aece3  c1e108                   shl        ecx, 8
008aece6  0bca                     or         ecx, edx
008aece8  0fb6501e                 movzx      edx, byte ptr [eax + 0x1e]
008aecec  898df8feffff             mov        dword ptr [ebp - 0x108], ecx
008aecf2  33c9                     xor        ecx, ecx
008aecf4  8a681c                   mov        ch, byte ptr [eax + 0x1c]
008aecf7  8a481d                   mov        cl, byte ptr [eax + 0x1d]
008aecfa  c1e108                   shl        ecx, 8
008aecfd  0bca                     or         ecx, edx
008aecff  c1e108                   shl        ecx, 8
008aed02  0fb6501f                 movzx      edx, byte ptr [eax + 0x1f]
008aed06  0bca                     or         ecx, edx
008aed08  898dfcfeffff             mov        dword ptr [ebp - 0x104], ecx
008aed0e  33c9                     xor        ecx, ecx
008aed10  8a6820                   mov        ch, byte ptr [eax + 0x20]
008aed13  0fb65022                 movzx      edx, byte ptr [eax + 0x22]
008aed17  8a4821                   mov        cl, byte ptr [eax + 0x21]
008aed1a  c1e108                   shl        ecx, 8
008aed1d  0bca                     or         ecx, edx
008aed1f  c1e108                   shl        ecx, 8
008aed22  0fb65023                 movzx      edx, byte ptr [eax + 0x23]
008aed26  0bca                     or         ecx, edx
008aed28  898d00ffffff             mov        dword ptr [ebp - 0x100], ecx
008aed2e  33c9                     xor        ecx, ecx
008aed30  8a6824                   mov        ch, byte ptr [eax + 0x24]
008aed33  0fb65026                 movzx      edx, byte ptr [eax + 0x26]
008aed37  8a4825                   mov        cl, byte ptr [eax + 0x25]
008aed3a  c1e108                   shl        ecx, 8
008aed3d  0bca                     or         ecx, edx
008aed3f  c1e108                   shl        ecx, 8
008aed42  0fb65027                 movzx      edx, byte ptr [eax + 0x27]
008aed46  0bca                     or         ecx, edx
008aed48  898d04ffffff             mov        dword ptr [ebp - 0xfc], ecx
008aed4e  33c9                     xor        ecx, ecx
008aed50  8a6828                   mov        ch, byte ptr [eax + 0x28]
008aed53  0fb6502a                 movzx      edx, byte ptr [eax + 0x2a]
008aed57  8a4829                   mov        cl, byte ptr [eax + 0x29]
008aed5a  c1e108                   shl        ecx, 8
008aed5d  0bca                     or         ecx, edx
008aed5f  0fb6502b                 movzx      edx, byte ptr [eax + 0x2b]
008aed63  c1e108                   shl        ecx, 8
008aed66  0bca                     or         ecx, edx
008aed68  898d08ffffff             mov        dword ptr [ebp - 0xf8], ecx
008aed6e  33c9                     xor        ecx, ecx
008aed70  8a682c                   mov        ch, byte ptr [eax + 0x2c]
008aed73  0fb6502e                 movzx      edx, byte ptr [eax + 0x2e]
008aed77  8a482d                   mov        cl, byte ptr [eax + 0x2d]
008aed7a  c1e108                   shl        ecx, 8
008aed7d  0bca                     or         ecx, edx
008aed7f  0fb6502f                 movzx      edx, byte ptr [eax + 0x2f]
008aed83  c1e108                   shl        ecx, 8
008aed86  0bca                     or         ecx, edx
008aed88  898d0cffffff             mov        dword ptr [ebp - 0xf4], ecx
008aed8e  33c9                     xor        ecx, ecx
008aed90  8a6830                   mov        ch, byte ptr [eax + 0x30]
008aed93  0fb65032                 movzx      edx, byte ptr [eax + 0x32]
008aed97  8a4831                   mov        cl, byte ptr [eax + 0x31]
008aed9a  c1e108                   shl        ecx, 8
008aed9d  0bca                     or         ecx, edx
008aed9f  0fb65033                 movzx      edx, byte ptr [eax + 0x33]
008aeda3  c1e108                   shl        ecx, 8
008aeda6  0bca                     or         ecx, edx
008aeda8  898d10ffffff             mov        dword ptr [ebp - 0xf0], ecx
008aedae  33c9                     xor        ecx, ecx