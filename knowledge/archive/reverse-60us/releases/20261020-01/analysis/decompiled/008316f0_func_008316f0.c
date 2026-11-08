typedef struct st_8316f0_0 {
    char padding_0[36];
    struct st_8316f0_1 *field_24;
} st_8316f0_0;

typedef struct st_8316f0_2 {
    struct st_8316f0_2 *field_0;
} st_8316f0_2;

typedef struct st_8316f0_1 {
    unsigned int field_0;
} st_8316f0_1;

extern unsigned int g_c7d994;
extern int g_cab8f8;
extern int g_cb56f0;
extern int g_e136a0;
extern char g_f710d8;

int func_008316f0(st_8316f0_0 **a0, unsigned int a1, int a2, int a3, int a4, int a5)
{
    unsigned int v21;  // ebx
    unsigned int v22;  // esi
    char *v31;  // edi
    int v32;  // esi
    unsigned int v33;  // 4101
    int v34;  // esi
    st_8316f0_2 **v35;  // eax
    int v37;  // esi
    st_8316f0_2 **v38;  // eax
    int v40;  // esi
    unsigned int v23;  // edi
    int v24;  // eax
    char *v25;  // edi
    unsigned int v26;  // ecx
    unsigned int v27;  // cc_op
    unsigned int v28;  // cc_dep1
    unsigned int v29;  // cc_dep2
    int v30;  // esi
    unsigned int v0;  // [bp-0x364]
    int v1;  // [bp-0x360]
    unsigned int v2;  // [bp-0x35c]
    char *v3;  // [bp-0x358]
    int v4;  // [bp-0x354], Other Possible Types: unsigned int
    int v5;  // [bp-0x350]
    unsigned int v6;  // [bp-0x34c]
    char *v7;  // [bp-0x348]
    unsigned int v8;  // [bp-0x344]
    unsigned int v9;  // [bp-0x340]
    unsigned int v10;  // [bp-0x33c]
    char v11;  // [bp-0x338]
    char v12;  // [bp-0x130]
    char v13;  // [bp-0x30]
    st_8316f0_2 **v14;  // [bp-0x2c]
    unsigned int v15;  // [bp-0x1c]
    unsigned int v16;  // [bp-0x18]
    char v17;  // [bp-0x14], Other Possible Types: int
    unsigned int v18;  // [bp-0x10]
    unsigned int v19;  // [bp-0xc]
    unsigned int v20;  // [bp-0x8]

    v20 = 0xffffffff;
    v19 = &g_c7d994;
    v18 = NtGetCurrentTeb()->Reserved1[0];
    NtGetCurrentTeb()->Reserved1[0] = &v18;
    v10 = v21;
    v9 = v22;
    v8 = v23;
    v16 = 7;
    v15 = 0;
    *(unsigned short *)&v14 = 0;
    v20 = 0;
    v24 = a3;
    if (g_f710d8)
    {
        v25 = "../DebugConfig.txt";
        v26 = 19;
        v27 = 15;
        v28 = 0;
        v29 = 0;
        v30 = v24;
        do
        {
            v31 = v25;
            v32 = v30;
            if (!v26)
                break;
            v26 -= 1;
            v27 = 4;
            v28 = *(char *)v32;
            v29 = *v31;
            v25 = v31 + 1;
            v30 = v32 + 1;
        } while (*(char *)v32 == *v31);
        v33 = _ccall(4, v27, v28, v29, 0);
        if (v33 & 1)
            goto LABEL_831833;
        v34 = a2;
        if ((char)sub_831410(sub_a92c50(v34, sub_a92c50(v24, &v13))) == 1)
        {
            v35 = v14;
            if (v16 < 8)
                v35 = &v14;
            sub_c0227f(&v11, 260, &g_cb56f0, v35);
        }
        else
        {
            sub_c0227f(&v11, 260, &g_cab8f8, sub_a92c50(v34, sub_a92c50(a3)));
        }
        if (sub_a56180(&v11, a4, a5, &v17) != 1)
            goto LABEL_831a9c;
        v2 = sub_a92cf0(&v11);
        v1 = "DNFLex::ReadStream";
        v0 = "%s - Pack::PackSet::get failed. file='%s'";
    }
    else
    {
LABEL_831833:
        v37 = a2;
        if ((char)sub_831180(sub_a92c50(v37, sub_a92c50(v24, &v13))))
        {
            v38 = v14;
            if (v16 < 8)
                v38 = &v14;
            sub_c0227f(&v11, 260, &g_cb56f0, v38);
        }
        else
        {
            sub_82f6c0(&v11, &g_cab8f8, sub_a92c50(v37, sub_a92c50(a3)));
        }
        v40 = sub_c01d29(&v11, &g_e136a0);
        if (!v40)
        {
            v6 = sub_a92cf0(&v11);
            v5 = "DNFLex::ReadStream";
            v4 = "%s - fopen failed. file='%s'";
        }
        else
        {
            if (sub_c026b4(v40, 0, 2))
            {
                v6 = sub_a92cf0(&v11);
                v5 = "DNFLex::ReadStream";
                v4 = "%s - fseek failed. file='%s'";
            }
            else
            {
                v17 = sub_c025e4(v40);
                if (sub_c026b4(v40, 0, 0))
                {
                    sub_c026fd(&v12, 0x100, "%s - fseek failed. file='%s'", "DNFLex::ReadStream", sub_a92cf0(&v11));
                    v7 = &v12;
                    *a0->field_24();
                }
                if ((unsigned int)v17 > (unsigned int)a5)
                {
                    v6 = sub_a92cf0(&v11, v17);
                    v5 = "DNFLex::ReadStream";
                    v4 = "%s - file is too big. file='%s', size=%d";
                }
                else
                {
                    if (sub_c02436(a4, v17, 1, v40) != 1)
                    {
                        sub_c026fd(&v12, 0x100, "%s - fread failed. file='%s'", "DNFLex::ReadStream", sub_a92cf0(&v11));
                        v7 = &v12;
                        *a0->field_24();
                    }
                    else if (sub_c01c7c(v40))
                    {
                        sub_c026fd(&v12, 0x100, "%s - fclose failed. file='%s'", "DNFLex::ReadStream", sub_a92cf0(&v11));
                        v7 = &v12;
                        *a0->field_24();
                    }
LABEL_831a9c:
                    if (v16 >= 8)
                        sub_bfffdd(v14);
                    NtGetCurrentTeb()->Reserved1[0] = v18;
                    return v17;
                }
            }
            sub_c026fd(&v12, 0x100);
            v7 = &v12;
            *a0->field_24();
        }
    }
    sub_c026fd(&v12, 0x100);
    v3 = &v12;
    *a0->field_24();
}
