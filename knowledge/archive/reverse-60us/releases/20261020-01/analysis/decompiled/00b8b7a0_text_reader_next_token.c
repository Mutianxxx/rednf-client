typedef struct st_b8b7a0_2 {
    struct st_b8b7a0_0 *field_0;
    char padding_4[120];
    unsigned int field_7c;
} st_b8b7a0_2;

typedef struct st_b8b7a0_0 {
    char padding_0[20];
    struct st_b8b7a0_1 *field_14;
} st_b8b7a0_0;

typedef struct st_b8b7a0_1 {
    unsigned int field_0;
} st_b8b7a0_1;

unsigned int text_reader_next_token(st_b8b7a0_2 *a0)
{
    if (!a0->field_7c)
        return 0;
    a0->field_0->field_14();
}
