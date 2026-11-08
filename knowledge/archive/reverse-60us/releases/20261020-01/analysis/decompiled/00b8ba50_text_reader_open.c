typedef struct st_b8ba50_0 {
    char padding_0[124];
    unsigned int field_7c;
} st_b8ba50_0;

void text_reader_open(st_b8ba50_0 *a0, unsigned int a1, int a2, int a3, int a4, int a5)
{
    unsigned int v1;  // esi
    unsigned int v0;  // [bp-0x8]

    v0 = v1;
    if (a0->field_7c)
    {
        do
        {
            sub_b8b490(1);
        } while (a0->field_7c);
    }
    sub_b8b5c0(a2, a3, a4, a5); /* do not return */
}
