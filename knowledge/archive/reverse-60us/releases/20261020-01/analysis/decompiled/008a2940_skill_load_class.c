typedef struct st_8a2940_1 {
    char padding_0[12];
    int field_c;
    char padding_10[4];
    unsigned int field_14;
    char padding_18[16];
    unsigned int field_28;
} st_8a2940_1;

typedef struct st_8a2940_2 {
    struct st_8a2940_1 *field_0;
    unsigned int field_4;
    unsigned int field_8;
    unsigned int field_c;
} st_8a2940_2;

typedef struct st_8a2940_0 {
    unsigned int field_0;
} st_8a2940_0;

extern int g_c824f0;
extern unsigned int g_cbb3a0;
extern st_8a2940_0 *g_ff2ebc;
extern st_8a2940_2 g_10bf08c;

void skill_load_class(int a0, int a1, unsigned int idx)
{
    int v11;  // edi
    int v12;  // esi
    int v13;  // ebx
    int v14;  // ecx
    st_8a2940_1 *i;  // edi
    int v16;  // eax
    unsigned int v2;  // [bp-0x30]
    unsigned int v3;  // [bp-0x2c]
    unsigned int v4;  // [bp-0x28]
    unsigned int v5;  // [bp-0x24]
    unsigned int v6;  // [bp-0x14]
    unsigned int v7;  // [bp-0x10]
    unsigned int v8;  // [bp-0x8]
    char v9;  // [bp+0x0]
    st_8a2940_1 *v10;  // [bp+0xc]

    v7 = NtGetCurrentTeb()->Reserved1[0];
    NtGetCurrentTeb()->Reserved1[0] = &v7;
    v6 = sub_bed91d(816, v11, v12, v13, v14, v7, &g_c824f0, -0x1, &v9);
    v8 = 0;
    v6 = (!v6 ? 0 : sub_556170());
    v8 = 0xffffffff;
    if (idx >= 6)
    {
        v5 = 6;
        v4 = idx;
        v3 = "nstl::sarray<struct STScriptFileList,6>::operator`[]'";
        v2 = &g_cbb3a0;
        g_ff2ebc();
    }
    i = *(int *)&(&g_10bf08c.field_0)[3 * idx]->padding_0[0];
    for (v10 = *(int *)&(&g_10bf08c.field_0)[3 * idx]->padding_0[0]; i != (&g_10bf08c.field_0)[3 * idx]; i = v10)
    {
        if ((char)skill_parse_properties(v6, (i->field_28 < 8 ? (struct st_8a2940_1 *)&i->field_14 : i->field_14), idx, 0))
        {
            v16 = sub_a530f0();
            sub_836240(v16, i->field_c);
        }
        sub_bab770();
    }
    if (v6)
    {
        sub_556520();
        sub_bfffdd(v6);
    }
    sub_830160(a0, a1);
    NtGetCurrentTeb()->Reserved1[0] = v7;
    return;
}
