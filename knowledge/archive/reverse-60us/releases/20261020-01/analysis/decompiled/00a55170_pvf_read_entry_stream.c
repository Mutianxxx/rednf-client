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
extern int g_e4a7e0;
extern int g_ff8e80;

unsigned int pvf_read_entry_stream(st_a55170_0 *a0, unsigned int a1, unsigned int *a2, unsigned int a3, void* a4, unsigned int a5, unsigned int *a6)
{
    unsigned int v7;  // ebx
    unsigned int v8;  // esi
    unsigned int v9;  // edi
    unsigned int v10;  // edi
    unsigned int v11;  // ecx
    void* node;  // eax
    unsigned int v13;  // ecx
    void* iter;  // edi
    unsigned int v15;  // ecx
    int v16;  // eax
    unsigned int v0;  // [bp-0x30]
    int v1;  // [bp-0x2c]
    unsigned int v2;  // [bp-0x20]
    int v3;  // [bp-0x1c]
    unsigned int v4;  // [bp-0x10]
    unsigned int v5;  // [bp-0xc]
    unsigned int v6;  // [bp-0x8]

    v6 = v7;
    v5 = v8;
    if (a2 && a4 && a6)
    {
        v4 = v9;
        v10 = a2[26];
        *a6 = 0;
        if (!v10)
        {
            sub_c022ef(&g_ff8e80, &g_e4a4ec, L"C:\\Work\\USA\\DNF_SRC\\RDAR\\Library\\PackSVN\\Pack.cpp", 479, &g_e4a7e0);
            return 1;
        }
        v11 = a0->field_24;
        if (v11 > a5)
        {
            sub_c022ef(&g_ff8e80, &g_e4a7ac);
            v3 = &g_e4a7e0;
            v2 = 484;
        }
        else
        {
            node = a0->field_34;
            if (a0->field_34)
            {
                v13 = v11 >> 2;
                for (iter = a4; v13; node += 4)
                {
                    v13 -= 1;
                    *(int *)iter = *(int *)node;
                    iter += 4;
                }
                for (v15 = v11 & 3; v15; node += 1)
                {
                    v15 -= 1;
                    *(char *)iter = *(char *)node;
                    iter += 1;
                }
                goto LABEL_a552a8;
            }
            else if (a0->field_4 == 1)
            {
                sub_c022ef(&g_ff8e80, &g_e4a6a0);
                v3 = &g_e4a7e0;
                v2 = 498;
            }
            else
            {
                if (a0->field_4)
                    goto LABEL_a552a8;
                if (a0->padding_28)
                {
                    sub_a57b30(a2[2] + a0->field_30, 0);
                    v16 = sub_a57ef0(a4, a0->padding_28);
                    if (v16 == a0->padding_28)
                        goto LABEL_a552a3;
                    sub_c022ef(&g_ff8e80, &g_e4a790);
                    v1 = &g_e4a7e0;
                    v0 = 509;
                }
                else
                {
LABEL_a552a3:
                    *a6 = a0->field_24;
LABEL_a552a8:
                    if (pvf_decrypt_verify(a0->field_2c, a4, a0->padding_28))
                        return 0;
                    sub_c022ef(&g_ff8e80, &g_e4a778);
                    v1 = &g_e4a7e0;
                    v0 = 518;
                }
            }
        }
        sub_c022ef(&g_ff8e80, &g_e4a4ec, L"C:\\Work\\USA\\DNF_SRC\\RDAR\\Library\\PackSVN\\Pack.cpp");
        return 1;
    }
    sub_c022ef(&g_ff8e80, &g_e4a4ec, L"C:\\Work\\USA\\DNF_SRC\\RDAR\\Library\\PackSVN\\Pack.cpp", 469, &g_e4a7e0);
    return 1;
}
