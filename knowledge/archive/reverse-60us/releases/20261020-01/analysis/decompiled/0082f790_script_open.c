typedef struct st_82f790_0 {
    unsigned int field_0;
} st_82f790_0;

extern st_82f790_0 *g_1050764;

int script_open(int a0, int a1)
{
    if (!g_1050764)
        return script_reader_open(sub_a92cf0(a0, sub_a92cf0(a1, 0, 0)));
    g_1050764();
}
