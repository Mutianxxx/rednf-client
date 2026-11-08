unsigned int script_read_int(char *a0)
{
    unsigned int v2;  // esi
    unsigned int v3;  // eax
    int v0;  // [bp-0x8]
    int v1;  // [bp-0x4]

    sub_b09fb0(9, v0, v1);
    v3 = script_reader_next_type(v0, v1);
    if (v3 == 2)
    {
        v2 = sub_8b29f0();
    }
    else if (v3 == 3)
    {
        v2 = sub_8b2a30();
    }
    else if (v3 == 4)
    {
        sub_8b2a70();
        v2 = sub_c01544();
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
        return 0;
    }
    if (a0)
    {
        *a0 = 1;
        sub_b09ff0(9, 0);
    }
    else
    {
        sub_b09ff0(9, 0);
    }
    return v2;
}
