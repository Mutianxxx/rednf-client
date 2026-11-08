typedef struct st_8b2950_0 {
    char padding_0[4];
    unsigned int field_4;
} st_8b2950_0;

int script_reader_open(st_8b2950_0 *a0)
{
    if (a0->field_4)
        return _INSERT(a0->field_4, 0, 1);
    return text_reader_open();
}
