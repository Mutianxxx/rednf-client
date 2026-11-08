typedef struct st_550e10_1 {
    char padding_0[1712];
    struct st_550e10_0 *field_6b0;
} st_550e10_1;

typedef struct st_550e10_0 {
    unsigned int field_0;
} st_550e10_0;

extern double g_cdcce8;
extern unsigned int g_cdcd58;
extern st_550e10_0 *g_ff2ebc;

unsigned int func_00550e10(double a0, unsigned int *a1, unsigned int a2, st_550e10_1 **a3, int a4)
{
    int v6;  // eax
    int v7;  // esi
    int v8;  // edi
    int v9;  // ebx
    unsigned int v0;  // [bp-0x24]
    int v1;  // [bp-0x20]
    unsigned int v2;  // [bp-0x1c]
    unsigned int v3;  // [bp-0x18]
    double v4;  // [bp-0x10]
    unsigned int v5;  // [bp-0x8]

    v6 = a4;
    if (v6 == -0x1)
        v6 = sub_402060(v7);
    if ((!a1[97] ? 0 : (int)(a1[98] - a1[97]) >> 3) < (unsigned int)v6)
    {
        if (a1[97])
        {
            v6 = (int)(a1[98] - a1[97]) >> 3;
        }
        else
        {
            v3 = sub_a530f0();
            v2 = &g_cdcd58;
            g_ff2ebc();
        }
    }
    if (v6 <= 0)
    {
        v3 = sub_a530f0();
        v2 = &g_cdcd58;
        g_ff2ebc();
    }
    v5 = sub_402060(v8);
    if (!a3)
        return v5;
    v1 = sub_402060(v9);
    sub_553f50(v1);
    a4 = (float)a0;
    if (sub_402060(v1) == 1)
    {
        v0 = 0;
        *a3->field_6b0();
    }
    else if (sub_402060() == 2)
    {
        v0 = 2;
        *a3->field_6b0();
    }
    else
    {
        if (!sub_402060() || (int)sub_402060() <= 0)
            return sub_54fc40(a3, sub_c01544(0, 3, sub_402060()));
        v4 = a4;
        a4 = sub_402060();
        a4 = (float)(v4 - (double)a4 * g_cdcce8);
        return sub_54fc40(a3, sub_c01544(0, 3, sub_402060()));
    }
}
