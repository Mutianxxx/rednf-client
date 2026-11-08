typedef struct st_a55fa0_0 {
    char padding_0[36];
    unsigned int field_24;
    unsigned int field_28;
    unsigned int field_2c;
    unsigned int field_30;
} st_a55fa0_0;

typedef struct st_a55fa0_1 {
    unsigned int field_0;
    unsigned int field_4;
} st_a55fa0_1;

unsigned int pvf_read_tree_entry(st_a55fa0_0 *a0, unsigned int a1, st_a55fa0_1 **a2)
{
    unsigned int *v3;  // ecx
    int v0;  // [bp-0xc]
    int v1;  // [bp-0x8]
    char v2;  // [bp+0x0]

    sub_a55b70(&a0->padding_0[8], a2, v0, v1, &v2);
    a0->field_24 = *a2->field_0;
    *a2 = &*a2->field_4;
    a0->field_28 = a0->field_24 + 3 & 0xfffffffc;
    a0->field_2c = *a2->field_0;
    v3 = &*a2->field_4;
    *a2 = v3;
    a0->field_30 = *v3;
    *a2 = &*a2->field_4;
    return 0;
}
