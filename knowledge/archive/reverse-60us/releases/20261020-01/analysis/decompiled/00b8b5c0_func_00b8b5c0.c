typedef struct st_b8b5c0_3 {
    struct st_b8b5c0_0 *field_0;
    char padding_4[8];
    unsigned int field_c;
    char padding_10[112];
    unsigned int field_80;
} st_b8b5c0_3;

typedef struct st_b8b5c0_0 {
    char padding_0[24];
    struct st_b8b5c0_1 *field_18;
    char padding_1c[8];
    struct st_b8b5c0_1 *field_24;
} st_b8b5c0_0;

typedef struct st_b8b5c0_1 {
    unsigned int field_0;
} st_b8b5c0_1;

extern unsigned int g_c9a1a3;
extern unsigned int g_ff9138;

void func_00b8b5c0(st_b8b5c0_3 *a0, unsigned int a1, char *a2, char *a3, int a4, int a5)
{
    unsigned int v22;  // ebx
    unsigned int v23;  // esi
    char *v32;  // eax
    unsigned int v34;  // edx
    st_b8b5c0_3 *v35;  // edi
    unsigned int v37;  // eax
    unsigned int v24;  // edi
    char *v25;  // eax
    char *v26;  // eax
    char *v27;  // eax
    char *v28;  // eax
    char *v29;  // eax
    char *v30;  // eax
    char *v31;  // eax
    unsigned int v0;  // [bp-0x98]
    unsigned int v1;  // [bp-0x94]
    st_b8b5c0_3 *v2;  // [bp-0x88]
    unsigned int v3;  // [bp-0x70]
    unsigned int v4;  // [bp-0x6c]
    unsigned int v5;  // [bp-0x68]
    unsigned int v6;  // [bp-0x64]
    char v7;  // [bp-0x60]
    char v8;  // [bp-0x5c]
    unsigned int v9;  // [bp-0x4c]
    unsigned int v10;  // [bp-0x48]
    char v11;  // [bp-0x40]
    unsigned int v12;  // [bp-0x30]
    unsigned int v13;  // [bp-0x2c]
    unsigned int v14;  // [bp-0x28]
    int v15;  // [bp-0x24]
    int v16;  // [bp-0x1c]
    char v17;  // [bp-0x18]
    unsigned int v18;  // [bp-0x14]
    unsigned int v19;  // [bp-0x10]
    unsigned int v20;  // [bp-0xc]
    char v21;  // [bp-0x8], Other Possible Types: unsigned int

    v21 = 0xffffffff;
    v20 = &g_c9a1a3;
    v19 = NtGetCurrentTeb()->Reserved1[0];
    NtGetCurrentTeb()->Reserved1[0] = &v19;
    v5 = v22;
    v18 = g_ff9138;
    v4 = v23;
    v3 = v24;
    v10 = 15;
    v9 = 0;
    v8 = 0;
    v13 = 15;
    v12 = 0;
    v11 = 0;
    v25 = a2;
    v21 = 0;
    v26 = v25;
    do
    {
        v27 = v26;
        v28 = v27 + 1;
        v26 = v28;
    } while (*v27);
    sub_4032b0(v25, v28 - (v25 + 1));
    v29 = a3;
    v30 = v29;
    do
    {
        v31 = v30;
        v32 = v31 + 1;
        v30 = v32;
    } while (*v31);
    sub_4032b0(a3, v32 - (v29 + 1));
    if (!a4)
    {
        v16 = sub_b8bc10();
        v17 = 0;
        v15 = func_008316f0(a0, v34, a2, a3, v16, 0x200000);
        if (!v15)
        {
            sub_b8bb50(v16);
            v35 = a0 + 1;
            sub_c02ddc(v35, "%s - DNFLex::ReadStream failed.", "DNFLex::PushInputStream");
            v2 = v35;
            a0->field_0->field_24();
        }
    }
    else
    {
        v16 = a4;
        v15 = a5;
        v17 = 1;
    }
    v6 = sub_bed91d(144);
    v21 = 1;
    v14 = (!v6 ? 0 : sub_a58140(v16, v15, 1));
    v21 = 0;
    if (*(int *)&a0->padding_10[108])
    {
        v37 = a0->field_80 + *(int *)&a0->padding_10[108] - 1;
        *(unsigned int *)((v37 & 0xff) * 76 + *(int *)(*(int *)&a0->padding_10[104] + (v37 >> 8) * 4) + 64) = a0->field_c;
    }
    sub_b8b3b0(&v7);
    v1 = 0;
    v0 = v14;
    a0->field_0->field_18();
}
