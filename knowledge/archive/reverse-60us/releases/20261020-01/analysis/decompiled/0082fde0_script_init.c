typedef struct st_a570d0_1 {
    unsigned int field_0;
} st_a570d0_1;

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

typedef struct st_82fde0_0 {
    unsigned int field_0;
} st_82fde0_0;

extern int g_cabae0;
extern int g_e1383c;
extern unsigned int g_e1385c;
extern int g_e13874;
extern int g_e13894;
extern int g_e138b4;
extern int g_e138d0;
extern char g_f710d8;
extern unsigned short g_1050556[4];
extern int g_1050558;
extern char g_1050760;
extern st_82fde0_0 *g_1050764;
extern st_a570d0_0 g_10511a8;
extern unsigned int g_105122c;

int script_init(void)
{
    int v3;  // eax
    int v4;  // ebx
    unsigned int v6;  // edx
    int v0;  // [bp-0x18]
    char v1;  // [bp+0x0]
    int v2;  // [bp+0x4]

    sub_c008c6(&g_1050558, v2, 260, &v1);
    v3 = sub_bffdcd(&g_1050558);
    if (v3 <= 0)
        return;
    if (g_1050556[v3] != 0x5c && g_1050556[v3] != 0x2f)
        sub_c02242(&g_1050558, "\\", 260);
    g_f710d8 = 1;
    if (!sub_c00667(&g_e138d0, 0, v4))
        g_f710d8 = 1;
    if (!sub_c00667(&g_e138b4, 0))
        g_f710d8 = 0;
    if (!sub_c00667(&g_e13894, 0))
        g_1050760 = 1;
    if (!sub_c00667(&g_e13874, 0))
        g_1050760 = 0;
    g_f710d8 = 1;
    if (pvf_open_archive(&g_10511a8.field_0, v6, &g_e1385c, 0, 1) == 1)
        return;
    if (!g_1050760)
        return;
    g_105122c = 1;
    if (!g_1050764)
    {
        v0 = sub_a92cf0(&g_cabae0, sub_a92cf0(&g_e1383c, 0, 0));
        script_reader_open(v0);
        sub_8b2c10(sub_8b2c60(sub_8b2cb0(v0)));
        return;
    }
    g_1050764();
}
