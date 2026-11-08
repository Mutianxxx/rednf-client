typedef struct st_550f60_0 {
    char padding_0[1712];
    struct st_550f60_1 *field_6b0;
} st_550f60_0;

typedef struct st_550f60_1 {
    unsigned int field_0;
} st_550f60_1;

extern float g_e9d7a4;

double func_00550f60(unsigned int *a0, unsigned int a1, st_550f60_0 **a2, unsigned int a3)
{
    int v5;  // edi
    double v6;  // mm7
    int v7;  // ebx
    unsigned int v0;  // [bp-0x1c]
    int v1;  // [bp-0x18]
    unsigned int *v2;  // [bp-0x8]
    float v3;  // [bp-0x8]
    float v4;  // [bp+0x8]

    v2 = a0;
    if (!a0[101] || !((int)(a0[0x66] - a0[101]) >> 3))
        return g_e9d7a4;
    if (a3 == 0xffffffff)
        a3 = sub_402060();
    sub_4333b0(v5);
    v3 = (float)v6;
    if (!a2)
        return v6;
    v1 = sub_402060(v7);
    sub_553f50(v1);
    v4 = (float)v6;
    if (sub_402060(v1) == 1)
    {
        v0 = 0;
        *a2->field_6b0();
    }
    else if (sub_402060() == 2)
    {
        v0 = 2;
        *a2->field_6b0();
    }
    else
    {
        a3 = sub_54fc40(a2, sub_c01544(0, 3, sub_402060()));
        return v4 * v3;
    }
    return g_e9d7a4;
}
