typedef struct st_8a0ae0_0 {
    char padding_0[12];
    unsigned int field_c;
    char padding_10[4];
    unsigned int field_14;
    char padding_18[16];
    unsigned int field_28;
} st_8a0ae0_0;

typedef struct st_8b2970_0 {
    char padding_0[4];
    unsigned int field_4;
    unsigned int field_8;
    unsigned int field_c;
    float field_10;
    unsigned int field_14;
} st_8b2970_0;

typedef struct st_8a0ae0_1 {
    unsigned int field_0;
} st_8a0ae0_1;

extern unsigned int g_c82404;
extern unsigned int g_cbb3a0;
extern int g_e29070;
extern st_8a0ae0_1 *g_ff2ebc;
extern st_8b2970_0 g_1051228;
extern unsigned short g_10bee76[4];
extern int g_10bee78;
extern char g_10bf088;

char skill_list_init(int a0, int a1)
{
    int v16;  // ebx
    unsigned int *i;  // eax
    unsigned int v18;  // esi
    unsigned int v19;  // edi
    unsigned int v20;  // esi
    unsigned int v21;  // edi
    unsigned int v22;  // eax
    int v23;  // esi
    unsigned int v0;  // [bp-0x58]
    unsigned int v1;  // [bp-0x54]
    unsigned int v2;  // [bp-0x50]
    unsigned int v3;  // [bp-0x4c]
    unsigned int v4;  // [bp-0x48]
    unsigned int v5;  // [bp-0x44]
    char v6;  // [bp-0x3c]
    int v7;  // [bp-0x38], Other Possible Types: unsigned short
    unsigned int v8;  // [bp-0x28]
    unsigned int v9;  // [bp-0x24]
    char v10;  // [bp-0x20]
    st_8a0ae0_0 **v11;  // [bp-0x1c]
    unsigned int *v12;  // [bp-0x14], Other Possible Types: char
    unsigned int v13;  // [bp-0x10]
    unsigned int v14;  // [bp-0xc]
    char v15;  // [bp-0x8], Other Possible Types: unsigned int

    v15 = 0xffffffff;
    v14 = &g_c82404;
    v13 = NtGetCurrentTeb()->Reserved1[0];
    NtGetCurrentTeb()->Reserved1[0] = &v13;
    sub_c008c6(&g_10bee78, a0, 0x100);
    if (g_10bee76[sub_bffdcd(&g_10bee78)] != 0x5c && g_10bee76[sub_bffdcd(&g_10bee78)] != 0x2f)
        sub_c02242(&g_10bee78, "\\", 0x100);
    sub_8339e0(v16);
    v15 = 0;
    if (!(char)sub_831ad0(&v10, &g_10bee78, a1))
    {
        v15 = 0xffffffff;
        sub_832c70(&v12, *v11, v11);
        sub_bfffdd(v11);
        NtGetCurrentTeb()->Reserved1[0] = v13;
        return 0;
    }
    i = *v11;
    v5 = v18;
    v4 = v19;
    v12 = i;
    if (i != v11)
    {
        do
        {
            v20 = i[3];
            if (v20 >= 6)
            {
                v3 = 6;
                v2 = v20;
                v1 = "nstl::sarray<struct STScriptFileList,6>::operator`[]'";
                v0 = &g_cbb3a0;
                g_ff2ebc();
            }
            if (!(char)sub_831ad0(&(&g_10bf088)[12 * v20], &g_10bee78, (i[10] < 8 ? i + 5 : i[5])))
            {
                v15 = 0xffffffff;
                sub_832c70(&v12, *v11, v11);
                sub_bfffdd(v11);
                NtGetCurrentTeb()->Reserved1[0] = v13;
                return 0;
            }
            sub_bab770();
            i = v12;
        } while (i != v11);
    }
    if (!(char)script_open(&g_10bee78, &g_e29070))
    {
        v15 = 0xffffffff;
        sub_832c70(&v12, *v11, v11);
        sub_bfffdd(v11);
        NtGetCurrentTeb()->Reserved1[0] = v13;
        return 0;
    }
    v21 = 0;
    v22 = script_reader_next_type(&g_1051228.padding_0[0]);
    if (v22)
    {
        do
        {
            if (v22 == 2)
            {
                v21 = sub_8b29f0();
            }
            else if (v22 == 6)
            {
                v23 = sub_a92c50(sub_8b2ad0());
                v9 = 7;
                v8 = 0;
                v7 = _INSERT(CONCAT(v7, 0), 0, 0);
                sub_402e80(v23, sub_bffdcd(v23));
                v15 = 1;
                *(unsigned int *)sub_4c9a30(&v6) = v21;
                v15 = 0;
                if (v9 >= 8)
                    sub_bfffdd(v7);
                v9 = 7;
                v8 = 0;
                v7 = 0;
            }
        } while ((v22 = script_reader_next_type(&g_1051228.padding_0[0]), v22));
    }
    v15 = 0xffffffff;
    sub_832c70(&v12, *v11, v11);
    sub_bfffdd(v11);
    NtGetCurrentTeb()->Reserved1[0] = v13;
    return 1;
}
