unsigned int path_hash(unsigned int a0, char *a1)
{
    unsigned int v2;  // eax
    unsigned int v3;  // esi
    char *v4;  // edx
    char *v5;  // edx
    unsigned int v0;  // [bp-0x4]

    v2 = 5381;
    if (!*a1)
        return 5381;
    v0 = v3;
    do
    {
        v4 = a1;
        v5 = v4 + 1;
        v2 = v2 * 33 + *v4;
        a1 = v5;
    } while (*v4);
    return v2;
}
