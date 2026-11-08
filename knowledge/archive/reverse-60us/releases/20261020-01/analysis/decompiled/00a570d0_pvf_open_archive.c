typedef struct st_a570d0_0 {
    int field_0;
    char padding_4[4];
    unsigned int field_8;
    int field_c;
    char padding_10[4];
    struct st_a570d0_1 *field_14;
    char padding_18[100];
    char field_7c;
} st_a570d0_0;

typedef struct st_a570d0_1 {
    unsigned int field_0;
} st_a570d0_1;

typedef struct st_a55fa0_1 {
    unsigned int field_0;
    unsigned int field_4;
} st_a55fa0_1;

extern unsigned int g_c8fbc5;
extern int g_e136a0;
extern int g_e4a4ec;
extern int g_e4ab48;
extern int g_e4ac2c;
extern int g_e4ac4c;
extern int g_e4ac74;
extern int g_ff8e80;

unsigned int pvf_open_archive(st_a570d0_0 *a0, unsigned int a1, unsigned int a2, int a3, int a4)
{
    unsigned int v12;  // esi
    unsigned int v13;  // eax
    int v22;  // ebx
    unsigned int *j;  // edi
    int v14;  // ecx
    int v15;  // edx
    unsigned int v16;  // eax
    int v17;  // edi
    int v18;  // ebx
    int v19;  // edi
    char *v20;  // ecx
    unsigned int *iter;  // ebx
    unsigned int v0;  // [bp-0x3c]
    char v1;  // [bp-0x38]
    char *v2;  // [bp-0x34]
    unsigned int v3;  // [bp-0x24]
    unsigned int v4;  // [bp-0x20]
    st_a55fa0_1 *v5;  // [bp-0x1c], Other Possible Types: unsigned int
    char v6;  // [bp-0x18], Other Possible Types: int
    char v7;  // [bp-0x14], Other Possible Types: int
    unsigned int v8;  // [bp-0x10]
    unsigned int v9;  // [bp-0xc]
    unsigned int v10;  // [bp-0x8]
    st_a55fa0_1 *v11;  // [bp+0x8]

    v10 = 0xffffffff;
    v9 = &g_c8fbc5;
    v8 = NtGetCurrentTeb()->Reserved1[0];
    NtGetCurrentTeb()->Reserved1[0] = &v8;
    v0 = v12;
    if (a0->field_7c)
    {
        v13 = sub_a56870(a2, a3, a4);
        NtGetCurrentTeb()->Reserved1[0] = v8;
        return v13;
    }
    v4 = 7;
    v3 = 0;
    *(unsigned short *)&v2 = 0;
    v10 = 0;
    if (a0->field_14)
    {
        v14 = *(int *)&a0->padding_18[0] - (char *)a0->field_14;
        v15 = ((unsigned int)(-2004318071 * v14) >> 32) + v14 >> 5;
        v16 = (unsigned int)(v15) >> 31;
        v5 = v16 + v15;
        if (v16 + v15)
        {
            sub_c022ef(&g_ff8e80, &g_e4ac2c);
            sub_c022ef(&g_ff8e80, &g_e4a4ec, L"C:\\Work\\USA\\DNF_SRC\\RDAR\\Library\\PackSVN\\Pack.cpp", 1015, &g_e4ac74);
            if (v4 >= 8)
                sub_bfffdd(v2);
            NtGetCurrentTeb()->Reserved1[0] = v8;
            return 1;
        }
    }
    v19 = sub_c01d29(a2, &g_e136a0, v17, v18);
    if (!v19)
    {
        sub_c022ef(&g_ff8e80, &g_e4ac4c, a2);
        sub_c022ef(&g_ff8e80, &g_e4a4ec, L"C:\\Work\\USA\\DNF_SRC\\RDAR\\Library\\PackSVN\\Pack.cpp", 0x3fe, &g_e4ac74);
        if (v4 >= 8)
            sub_bfffdd(v2);
        NtGetCurrentTeb()->Reserved1[0] = v8;
        return 1;
    }
    else
    {
        sub_a55af0(&v1);
        if (a3)
        {
            v20 = v2;
            if (v4 < 8)
                v20 = &v2;
            if (sub_c00deb(v20, a3))
            {
                if (v4 < 8)
                    v2 = &v2;
                sub_c022ef(&g_ff8e80, &g_e4ab48, v2);
                sub_c022ef(&g_ff8e80, &g_e4a4ec, L"C:\\Work\\USA\\DNF_SRC\\RDAR\\Library\\PackSVN\\Pack.cpp", 0x404, &g_e4ac74);
                sub_b8e070();
                NtGetCurrentTeb()->Reserved1[0] = v8;
                return 1;
            }
        }
        sub_c02436(a0->padding_4, 4, 1, v19);
        sub_c02436(&a2, 4, 1, v19);
        sub_c02436(&v6, 4, 1, v19);
        sub_c02436(&v7, 4, 1, v19);
        v5 = sub_bed9c1(a2);
        sub_c02436(v5, a2, 1, v19);
        a0->field_8 = sub_c025e4(v19);
        a0->field_0 = v19;
        if (!pvf_decrypt_verify(v6, v5, a2))
        {
            sub_c01286(v5);
            sub_b8e070();
            NtGetCurrentTeb()->Reserved1[0] = v8;
            return 1;
        }
        a3 = v5;
        sub_a59b70(v7);
        iter = a0->field_14;
        if (a0->field_14 != *(int *)&a0->padding_18[0])
        {
            do
            {
                *iter = a3->field_0;
                v11 = &a3->field_4;
                pvf_read_tree_entry(iter + 1, &v11, &v11);
                iter += 15;
                a3 = v11;
            } while (iter != *(int *)&a0->padding_18[0]);
        }
        sub_c01286(v5);
        if (!a4)
        {
            sub_c026b4(v19, 0, 2);
            a3 = sub_c025e4(v19);
            sub_c026b4(v19, 0, 0);
            v22 = sub_bed9c1(a3);
            sub_c02436(v22, a3, 1, v19);
            j = a0->field_14;
            if (a0->field_14 != *(int *)&a0->padding_18[0])
            {
                do
                {
                    sub_a55010(v22, a0);
                    j += 15;
                } while (j != *(int *)&a0->padding_18[0]);
            }
            sub_c01286(v22);
        }
        a0->field_c = a4;
        if (v4 >= 8)
            sub_bfffdd(v2);
        NtGetCurrentTeb()->Reserved1[0] = v8;
        return 0;
    }
}
