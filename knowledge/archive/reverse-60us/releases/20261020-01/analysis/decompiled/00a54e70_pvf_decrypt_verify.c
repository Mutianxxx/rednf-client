extern unsigned int g_10d427c;
extern unsigned int g_10d4288[4];

int pvf_decrypt_verify(void)
{
    unsigned int v5;  // eax
    unsigned int v6;  // ebx
    unsigned int v15;  // eax
    int v7;  // esi
    unsigned int v8;  // ecx
    unsigned int v9;  // esi
    void* iter;  // ecx
    void* v11;  // edi
    unsigned int v12;  // eax
    unsigned int v13;  // eax
    unsigned int v14;  // eax
    int v0;  // [bp-0x8]
    char v1;  // [bp+0x0]
    void* v3;  // [bp+0x8]
    unsigned int v4;  // [bp+0xc]

    v6 = v5;
    if ((char)v4 & 3)
        return;
    sub_a5fc30(v7, v0, &v1);
    v9 = ~v8;
    if (g_10d427c)
        v6 ^= g_10d427c;
    iter = v3;
    v11 = iter + (v4 >> 2) * 4;
    if (iter == v11)
        return;
    do
    {
        v12 = __ROL__(*(int *)iter ^ v6, 26);
        *(unsigned int *)iter = v12;
        iter += 4;
        v13 = v9 >> 8 ^ g_10d4288[((char)v12 ^ v9) & 0xff];
        v14 = v13 >> 8 ^ g_10d4288[(*((char *)iter - 3) ^ v13) & 0xff];
        v15 = v14 >> 8 ^ g_10d4288[(*((char *)iter - 2) ^ v14) & 0xff];
        v9 = v15 >> 8 ^ g_10d4288[(*((char *)iter - 1) ^ v15) & 0xff];
    } while (iter != v11);
    return;
}
