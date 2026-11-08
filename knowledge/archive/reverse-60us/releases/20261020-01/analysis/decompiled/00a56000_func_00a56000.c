typedef struct st_a56000_0 {
    char padding_0[20];
    int field_14;
    struct st_a56000_1 *field_18;
} st_a56000_0;

typedef struct st_a56000_1 {
    char padding_0[16];
    unsigned int field_10;
    char padding_14[40];
    unsigned int field_3c;
} st_a56000_1;

extern int g_a54f40;
extern unsigned int g_c8fb23;
extern char g_e1396c;

st_a56000_1 ** func_00a56000(st_a56000_0 *a0, unsigned int a1, st_a56000_1 **a2, int a3)
{
    int v21;  // edi
    int v22;  // esi
    st_a56000_1 **v31;  // esi
    int v23;  // ebx
    char *v24;  // eax
    unsigned int v25;  // esi
    char *v26;  // eax
    unsigned int *v28;  // ebx
    unsigned int *v29;  // ebx
    unsigned int *v30;  // edi
    int v0;  // [bp-0x2ac]
    char v1;  // [bp-0x298]
    unsigned int v2;  // [bp-0x90]
    unsigned int v3;  // [bp-0x8c]
    int v4;  // [bp-0x80]
    unsigned int v5;  // [bp-0x6c]
    unsigned int v6;  // [bp-0x54]
    unsigned int v7;  // [bp-0x50]
    int v8;  // [bp-0x48]
    unsigned int v9;  // [bp-0x38]
    unsigned int v10;  // [bp-0x34]
    unsigned int v11;  // [bp-0x30]
    unsigned int v12;  // [bp-0x2c]
    unsigned int v13;  // [bp-0x28]
    unsigned int v14;  // [bp-0x24]
    unsigned int v15;  // [bp-0x20]
    unsigned int *v16;  // [bp-0x1c], Other Possible Types: char
    unsigned int *v17;  // [bp-0x18]
    unsigned int v18;  // [bp-0x10]
    unsigned int v19;  // [bp-0xc]
    char v20;  // [bp-0x8], Other Possible Types: unsigned int

    v20 = 0xffffffff;
    v19 = &g_c8fb23;
    v18 = NtGetCurrentTeb()->Reserved1[0];
    NtGetCurrentTeb()->Reserved1[0] = &v18;
    v6 = &g_e1396c;
    v10 = 7;
    v9 = 0;
    *(unsigned short *)&v8 = 0;
    v7 = 0;
    v11 = 0;
    v12 = 0;
    v13 = 0;
    v14 = 0;
    v15 = 0;
    v20 = 0;
    sub_a55bf0(a3, &v1, 260, 0, 0, v21, v22, v23);
    v24 = sub_a92cf0(&v1);
    v25 = 5381;
    if (*v24)
    {
        do
        {
            v26 = v24;
            v25 = v25 * 33 + *v26;
            v24 = v26 + 1;
        } while (*v26);
    }
    v2 = v25;
    sub_a58450(&v6);
    v20 = 1;
    sub_a57fe0(&v16, a0->field_14, a0->field_18, &v2, &g_a54f40, 0);
    v28 = v16;
    v3 = &g_e1396c;
    if (v5 >= 8)
        sub_bfffdd(v4);
    if (v28 != a0->field_18 && *v28 == v25)
    {
        v29 = v28 + 4;
        while (1)
        {
            v30 = v28;
            if (v30 == v17)
            {
LABEL_a56132:
                v31 = a2;
                *v31 = a0->field_18;
                goto LABEL_a5613d;
            }
            if (!sub_c00deb((v29[5] < 8 ? v29 : *v29), &v1))
                break;
            v28 = v30 + 15;
            v29 += 15;
            if (v30[15] != v25)
                goto LABEL_a56132;
        }
        v31 = a2;
        *v31 = v30;
LABEL_a5613d:
        if (v10 < 8)
        {
            NtGetCurrentTeb()->Reserved1[0] = v18;
            return v31;
        }
        v0 = v8;
    }
    else
    {
        v31 = a2;
        *v31 = a0->field_18;
        if (v10 < 8)
        {
            NtGetCurrentTeb()->Reserved1[0] = v18;
            return v31;
        }
        v0 = v8;
    }
    sub_bfffdd(v0);
    NtGetCurrentTeb()->Reserved1[0] = v18;
    return v31;
}
