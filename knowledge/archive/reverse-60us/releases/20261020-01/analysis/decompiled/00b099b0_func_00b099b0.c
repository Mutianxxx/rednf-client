double func_00b099b0(float a0, float a1, int a2, int a3)
{
    if (a2 >= a3)
    {
        return a1;
    }
    else if (a2 <= 0)
    {
        return a0;
    }
    else
    {
        return (a1 - a0) * (double)a2 / (double)a3 + a0;
    }
}
