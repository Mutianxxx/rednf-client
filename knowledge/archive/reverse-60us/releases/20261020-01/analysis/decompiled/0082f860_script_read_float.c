float script_read_float(char *a0)
{
    int v2;  // ecx
    unsigned int v3;  // eax
    double v4;  // mm7
    float v0;  // [bp-0x8], Other Possible Types: int
    int v1;  // [bp-0x4]

    sub_b09fb0(9, v2, v1);
    v0 = 0;
    v3 = script_reader_next_type(v0, v1);
    if (v3 == 2)
    {
        v0 = sub_8b29f0();
        v4 = (double)v0;
    }
    else if (v3 == 3)
    {
        v0 = sub_8b2a30();
        v4 = (double)v0;
    }
    else if (v3 == 4)
    {
        sub_8b2a70();
    }
    else
    {
        if (a0)
        {
            *a0 = 0;
            sub_b09ff0(9, 0);
        }
        else
        {
            sub_b09ff0(9, 0);
        }
        return v0;
    }
    v0 = (float)v4;
    if (!a0)
    {
        sub_b09ff0(9, 0);
        return v0;
    }
    *a0 = 1;
    sub_b09ff0(9, 0);
    return (float)v4;
}
