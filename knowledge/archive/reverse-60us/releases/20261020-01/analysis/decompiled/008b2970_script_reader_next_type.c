typedef struct st_8b2970_0 {
    char padding_0[4];
    unsigned int field_4;
    unsigned int field_8;
    unsigned int field_c;
    float field_10;
    unsigned int field_14;
} st_8b2970_0;

unsigned int script_reader_next_type(st_8b2970_0 *a0)
{
    int v2;  // esi
    unsigned int v3;  // eax
    int v4;  // edi
    unsigned int v5;  // eax
    double v6;  // mm7
    int v0;  // [bp-0xc]

    if (!a0->field_4)
    {
        v3 = text_reader_next_token(v2);
        a0->field_8 = v3;
        return v3;
    }
    if (a0->field_4 != 1)
        return a0->field_8;
    v5 = sub_8b32a0(v4);
    a0->field_8 = v5;
    if (v5 && v5 != 1)
    {
        if (v5 != 2 && v5 != 3 && v5 != 9)
        {
            v0 = 0;
            if (v5 == 4)
            {
                sub_8b3320(v0);
                a0->field_10 = (float)v6;
            }
            else
            {
                a0->field_14 = sub_8b33f0(v0);
            }
            return a0->field_8;
        }
        a0->field_c = sub_8b32e0(0);
    }
    return a0->field_8;
}
