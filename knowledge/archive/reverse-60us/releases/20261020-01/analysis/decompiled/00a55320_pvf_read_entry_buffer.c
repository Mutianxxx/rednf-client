typedef struct st_a55320_0 {
    char padding_0[8];
    unsigned int field_8;
    char padding_c[112];
    char field_7c;
} st_a55320_0;

typedef struct st_a55170_0 {
    char padding_0[4];
    unsigned int field_4;
    char padding_8[28];
    unsigned int field_24;
    char padding_28[4];
    int field_2c;
    unsigned int field_30;
    void* field_34;
} st_a55170_0;

extern int g_e4a4ec;
extern int g_e4a6a0;
extern int g_e4a778;
extern int g_e4a790;
extern int g_e4a7ac;
extern int g_e4a838;
extern int g_ff8e80;

unsigned int pvf_read_entry_buffer(st_a55170_0 *a0, unsigned int a1, st_a55320_0 *a2, unsigned int a3, void* a4, unsigned int a5, unsigned int *a6)
{
    void* v3;  // edx
    unsigned int v4;  // edi
    void* iter;  // edi
    unsigned int v6;  // ecx
    void* node;  // eax
    unsigned int v8;  // ecx
    unsigned int v9;  // ecx
    int v12;  // eax
    unsigned int v0;  // [bp-0x18]
    int v1;  // [bp-0x14]
    unsigned int v2;  // [bp-0x10]

    if (a2->field_7c)
    {
        v3 = a4;
        return pvf_read_entry_stream(a0, v3, a2, a3, v3, a5, a6);
    }
    v2 = v4;
    iter = a4;
    if (iter && a6)
    {
        *a6 = 0;
        if (!sub_a54d50())
        {
            v1 = &g_e4a838;
            v0 = 548;
        }
        else
        {
            v6 = a0->field_24;
            if (v6 > a5)
            {
                sub_c022ef(&g_ff8e80, &g_e4a7ac);
                sub_c022ef(&g_ff8e80, &g_e4a4ec, L"C:\\Work\\USA\\DNF_SRC\\RDAR\\Library\\PackSVN\\Pack.cpp", 553, &g_e4a838);
                return 1;
            }
            node = a0->field_34;
            if (a0->field_34)
            {
                for (v8 = v6 >> 2; v8; node += 4)
                {
                    v8 -= 1;
                    *(int *)iter = *(int *)node;
                    iter += 4;
                }
                for (v9 = v6 & 3; v9; node += 1)
                {
                    v9 -= 1;
                    *(char *)iter = *(char *)node;
                    iter += 1;
                }
                iter = a4;
            }
            else if (a0->field_4 == 1)
            {
                sub_c022ef(&g_ff8e80, &g_e4a6a0);
                sub_c022ef(&g_ff8e80, &g_e4a4ec, L"C:\\Work\\USA\\DNF_SRC\\RDAR\\Library\\PackSVN\\Pack.cpp", 564, &g_e4a838);
                return 1;
            }
            else if (!a0->field_4)
            {
                if (a0->padding_28)
                {
                    sub_c026b4(sub_a54d50(0, 0));
                    sub_c026b4(sub_a54d50(a0->field_30 + a2->field_8, 0));
                    v12 = sub_a54d50();
                    if (sub_c02436(iter, a0->padding_28, 1, v12) != 1)
                    {
                        sub_c022ef(&g_ff8e80, &g_e4a790);
                        sub_c022ef(&g_ff8e80, &g_e4a4ec, L"C:\\Work\\USA\\DNF_SRC\\RDAR\\Library\\PackSVN\\Pack.cpp", 572, &g_e4a838);
                        return 1;
                    }
                }
                *a6 = a0->field_24;
            }
            if (pvf_decrypt_verify(a0->field_2c, iter, a0->padding_28))
                return 0;
            sub_c022ef(&g_ff8e80, &g_e4a778);
            sub_c022ef(&g_ff8e80, &g_e4a4ec, L"C:\\Work\\USA\\DNF_SRC\\RDAR\\Library\\PackSVN\\Pack.cpp", 581, &g_e4a838);
            return 1;
        }
    }
    else
    {
        v1 = &g_e4a838;
        v0 = 541;
    }
    sub_c022ef(&g_ff8e80, &g_e4a4ec, L"C:\\Work\\USA\\DNF_SRC\\RDAR\\Library\\PackSVN\\Pack.cpp");
    return 1;
}
