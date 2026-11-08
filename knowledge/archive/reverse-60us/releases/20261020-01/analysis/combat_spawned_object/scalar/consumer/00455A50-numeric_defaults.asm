00455a50  8bc1                     mov        eax, ecx
00455a52  33c9                     xor        ecx, ecx
00455a54  ba0000803f               mov        edx, 0x3f800000
00455a59  8908                     mov        dword ptr [eax], ecx
00455a5b  884804                   mov        byte ptr [eax + 4], cl
00455a5e  884805                   mov        byte ptr [eax + 5], cl
00455a61  895006                   mov        dword ptr [eax + 6], edx
00455a64  89480a                   mov        dword ptr [eax + 0xa], ecx
00455a67  88480e                   mov        byte ptr [eax + 0xe], cl
00455a6a  89480f                   mov        dword ptr [eax + 0xf], ecx
00455a6d  895013                   mov        dword ptr [eax + 0x13], edx
00455a70  895017                   mov        dword ptr [eax + 0x17], edx
00455a73  89501b                   mov        dword ptr [eax + 0x1b], edx
00455a76  89501f                   mov        dword ptr [eax + 0x1f], edx
00455a79  895023                   mov        dword ptr [eax + 0x23], edx
00455a7c  895027                   mov        dword ptr [eax + 0x27], edx
00455a7f  53                       push       ebx
00455a80  89502b                   mov        dword ptr [eax + 0x2b], edx
00455a83  89482f                   mov        dword ptr [eax + 0x2f], ecx
00455a86  894833                   mov        dword ptr [eax + 0x33], ecx
00455a89  895037                   mov        dword ptr [eax + 0x37], edx
00455a8c  89503b                   mov        dword ptr [eax + 0x3b], edx
00455a8f  89483f                   mov        dword ptr [eax + 0x3f], ecx
00455a92  894843                   mov        dword ptr [eax + 0x43], ecx
00455a95  895047                   mov        dword ptr [eax + 0x47], edx
00455a98  89504b                   mov        dword ptr [eax + 0x4b], edx
00455a9b  89504f                   mov        dword ptr [eax + 0x4f], edx
00455a9e  895053                   mov        dword ptr [eax + 0x53], edx
00455aa1  895057                   mov        dword ptr [eax + 0x57], edx
00455aa4  89505b                   mov        dword ptr [eax + 0x5b], edx
00455aa7  89505f                   mov        dword ptr [eax + 0x5f], edx
00455aaa  894863                   mov        dword ptr [eax + 0x63], ecx
00455aad  894867                   mov        dword ptr [eax + 0x67], ecx
00455ab0  89506b                   mov        dword ptr [eax + 0x6b], edx
00455ab3  89506f                   mov        dword ptr [eax + 0x6f], edx
00455ab6  895073                   mov        dword ptr [eax + 0x73], edx
00455ab9  894877                   mov        dword ptr [eax + 0x77], ecx
00455abc  89487b                   mov        dword ptr [eax + 0x7b], ecx
00455abf  89487f                   mov        dword ptr [eax + 0x7f], ecx
00455ac2  898883000000             mov        dword ptr [eax + 0x83], ecx
00455ac8  56                       push       esi
00455ac9  bb01000000               mov        ebx, 1
00455ace  57                       push       edi
00455acf  899087000000             mov        dword ptr [eax + 0x87], edx
00455ad5  89888b000000             mov        dword ptr [eax + 0x8b], ecx
00455adb  89988f000000             mov        dword ptr [eax + 0x8f], ebx
00455ae1  898893000000             mov        dword ptr [eax + 0x93], ecx
00455ae7  898897000000             mov        dword ptr [eax + 0x97], ecx
00455aed  89989b000000             mov        dword ptr [eax + 0x9b], ebx
00455af3  89889f000000             mov        dword ptr [eax + 0x9f], ecx
00455af9  8988a3000000             mov        dword ptr [eax + 0xa3], ecx
00455aff  8988a7000000             mov        dword ptr [eax + 0xa7], ecx
00455b05  8990ab000000             mov        dword ptr [eax + 0xab], edx
00455b0b  8988af000000             mov        dword ptr [eax + 0xaf], ecx
00455b11  8988b3000000             mov        dword ptr [eax + 0xb3], ecx
00455b17  8988b7000000             mov        dword ptr [eax + 0xb7], ecx
00455b1d  8988bb000000             mov        dword ptr [eax + 0xbb], ecx
00455b23  8988bf000000             mov        dword ptr [eax + 0xbf], ecx
00455b29  8888c3000000             mov        byte ptr [eax + 0xc3], cl
00455b2f  8888c4000000             mov        byte ptr [eax + 0xc4], cl
00455b35  8888c5000000             mov        byte ptr [eax + 0xc5], cl
00455b3b  8db022010000             lea        esi, [eax + 0x122]
00455b41  bf17000000               mov        edi, 0x17
00455b46  8956a4                   mov        dword ptr [esi - 0x5c], edx
00455b49  8916                     mov        dword ptr [esi], edx
00455b4b  83c604                   add        esi, 4
00455b4e  4f                       dec        edi
00455b4f  75f5                     jne        0x455b46
00455b51  dd0560b2cc00             fld        qword ptr [0xccb260]
00455b57  5f                       pop        edi
00455b58  5e                       pop        esi
00455b59  dd9882010000             fstp       qword ptr [eax + 0x182]
00455b5f  88988b010000             mov        byte ptr [eax + 0x18b], bl
00455b65  88988c010000             mov        byte ptr [eax + 0x18c], bl
00455b6b  8998ac010000             mov        dword ptr [eax + 0x1ac], ebx
00455b71  89907e010000             mov        dword ptr [eax + 0x17e], edx
00455b77  88888a010000             mov        byte ptr [eax + 0x18a], cl
00455b7d  88888d010000             mov        byte ptr [eax + 0x18d], cl
00455b83  88888e010000             mov        byte ptr [eax + 0x18e], cl
00455b89  88888f010000             mov        byte ptr [eax + 0x18f], cl
00455b8f  888890010000             mov        byte ptr [eax + 0x190], cl
00455b95  898891010000             mov        dword ptr [eax + 0x191], ecx
00455b9b  898895010000             mov        dword ptr [eax + 0x195], ecx
00455ba1  898899010000             mov        dword ptr [eax + 0x199], ecx
00455ba7  89889d010000             mov        dword ptr [eax + 0x19d], ecx
00455bad  8988a1010000             mov        dword ptr [eax + 0x1a1], ecx
00455bb3  8888a5010000             mov        byte ptr [eax + 0x1a5], cl
00455bb9  8888a6010000             mov        byte ptr [eax + 0x1a6], cl
00455bbf  8988a7010000             mov        dword ptr [eax + 0x1a7], ecx
00455bc5  8888ab010000             mov        byte ptr [eax + 0x1ab], cl
00455bcb  8988b0010000             mov        dword ptr [eax + 0x1b0], ecx
00455bd1  8888b4010000             mov        byte ptr [eax + 0x1b4], cl
00455bd7  8888b5010000             mov        byte ptr [eax + 0x1b5], cl
00455bdd  8888b6010000             mov        byte ptr [eax + 0x1b6], cl
00455be3  8888b7010000             mov        byte ptr [eax + 0x1b7], cl
00455be9  8988b8010000             mov        dword ptr [eax + 0x1b8], ecx
00455bef  8888bc010000             mov        byte ptr [eax + 0x1bc], cl
00455bf5  8988bd010000             mov        dword ptr [eax + 0x1bd], ecx
00455bfb  8888c1010000             mov        byte ptr [eax + 0x1c1], cl
00455c01  8988c2010000             mov        dword ptr [eax + 0x1c2], ecx
00455c07  5b                       pop        ebx
00455c08  c3                       ret        