typedef struct st_8a0da0_4 {
    struct st_8a0da0_4 *field_0;
} st_8a0da0_4;

typedef struct st_8a0da0_0 {
    unsigned int field_0;
} st_8a0da0_0;

typedef struct st_8a0da0_3 {
    char padding_0[4];
    unsigned int field_4;
    char padding_8[16];
    unsigned int field_18;
    unsigned int field_1c;
    char padding_20[4];
    unsigned int field_24;
    int field_28;
    unsigned int field_2c;
    char padding_30[120];
    unsigned int field_a8;
    unsigned int field_ac;
    char padding_b0[284];
    unsigned int field_1cc;
    int field_1d0;
    unsigned int field_1d4;
    char padding_1d8[164];
    unsigned int field_27c;
    char padding_280[24];
    unsigned int field_298;
    unsigned int field_29c;
    char field_2a0;
    char padding_2a1[19];
    char field_2b4;
    char padding_2b5[3];
    unsigned int field_2b8;
    unsigned int field_2bc;
    unsigned int field_2c0;
    char padding_2c4[20];
    unsigned int field_2d8;
    int field_2dc;
    unsigned int field_2e0;
    char padding_2e4[4];
    unsigned int field_2e8;
    int field_2ec;
    unsigned int field_2f0;
} st_8a0da0_3;

typedef struct st_8a0da0_1 {
    char padding_0[68];
    struct st_8a0da0_0 *field_44;
    unsigned int field_48;
} st_8a0da0_1;

typedef struct st_8b2970_0 {
    char padding_0[4];
    unsigned int field_4;
    unsigned int field_8;
    unsigned int field_c;
    float field_10;
    unsigned int field_14;
} st_8b2970_0;

extern unsigned int g_c824db;
extern unsigned int g_cbb3a0;
extern int g_cc3d74;
extern int g_cc9444;
extern float g_cd5b2c;
extern int g_cda0d0;
extern unsigned int g_e14614;
extern int g_e14e44;
extern int g_e17490;
extern int g_e174a4;
extern int g_e1c8d4;
extern int g_e1c8e8;
extern int g_e1d498;
extern int g_e1d9f0;
extern int g_e1dae8;
extern int g_e1dda4;
extern int g_e1f208;
extern int g_e23d14;
extern int g_e23d28;
extern unsigned int g_e29098;
extern int g_e290e4;
extern int g_e29118;
extern int g_e2913c;
extern int g_e2915c;
extern int g_e2917c;
extern int g_e291b0;
extern int g_e291cc;
extern int g_e291ec;
extern int g_e29210;
extern int g_e2922c;
extern int g_e29248;
extern int g_e29258;
extern int g_e29260;
extern int g_e29274;
extern int g_e29280;
extern int g_e292ac;
extern int g_e292d8;
extern int g_e29304;
extern int g_e29340;
extern int g_e2935c;
extern int g_e29390;
extern int g_e293ac;
extern int g_e293c8;
extern int g_e293e4;
extern int g_e29418;
extern int g_e2944c;
extern int g_e29470;
extern int g_e294b0;
extern int g_e294f0;
extern int g_e29524;
extern int g_e2954c;
extern int g_e29568;
extern int g_e29598;
extern int g_e295c4;
extern int g_e29600;
extern int g_e29630;
extern int g_e29660;
extern int g_e29684;
extern int g_e296a4;
extern int g_e296c4;
extern st_8a0da0_0 *g_ff2ebc;
extern st_8b2970_0 g_1051228;
extern int g_10bee78;
extern char g_10bf07c;
extern st_8a0da0_1 *g_12101d8;
extern unsigned int g_12101dc;

int skill_parse_properties(st_8a0da0_3 *a0, int a1, unsigned int a2, int a3)
{
    int v73;  // eax
    st_8a0da0_3 *v74;  // edi
    unsigned int l;  // ebx
    unsigned int v84;  // ebx
    unsigned int i4;  // ebx
    unsigned int v86;  // ebx
    unsigned int i5;  // ebx
    unsigned int v88;  // ebx
    float count;  // eax
    unsigned int n;  // ebx
    unsigned int v91;  // ebx
    unsigned int i0;  // ebx
    int v75;  // edi
    unsigned int v93;  // ebx
    float count1;  // eax
    unsigned int v95;  // esi
    double count2;  // mm7
    double v97;  // mm7
    unsigned int i1;  // ebx
    unsigned int v99;  // ebx
    float v100;  // eax
    unsigned int i2;  // ebx
    int v76;  // esi
    unsigned int v103;  // ebx
    float v104;  // eax
    int v105;  // esi
    unsigned int v106;  // eax
    unsigned short v109;  // ax
    float v110;  // eax
    float v112;  // eax
    int v77;  // ebx
    unsigned int v113;  // eax
    unsigned int v114;  // eax
    unsigned int i3;  // eax
    float v116;  // eax
    float v117;  // eax
    st_8a0da0_1 *v118;  // ecx
    st_8a0da0_3 *v119;  // ebx
    st_8a0da0_3 *iter;  // edi
    unsigned int v121;  // eax
    unsigned int *v122;  // esi
    unsigned int v78;  // eax
    unsigned int *v123;  // eax
    unsigned int v124;  // eax
    unsigned int *v125;  // edx
    int v126;  // esi
    unsigned int *v127;  // eax
    st_8a0da0_3 *v128;  // esi
    unsigned int v129;  // eax
    int v130;  // edi
    unsigned int *v131;  // eax
    unsigned int v132;  // edx
    unsigned int v79;  // eax
    unsigned int v133;  // eax
    st_8a0da0_3 *v134;  // edx
    st_8a0da0_3 *v135;  // esi
    unsigned int v136;  // eax
    int v137;  // edi
    unsigned int *v138;  // eax
    unsigned int v139;  // edx
    unsigned int v140;  // eax
    st_8a0da0_3 *v141;  // esi
    unsigned int v142;  // eax
    unsigned int k;  // eax
    int v143;  // edi
    unsigned int *v144;  // eax
    unsigned int v145;  // edx
    unsigned int v146;  // eax
    st_8a0da0_3 *v147;  // esi
    unsigned int v148;  // eax
    unsigned int *v149;  // edx
    int v150;  // edi
    unsigned int *v151;  // eax
    unsigned int v152;  // edx
    float v81;  // eax
    unsigned int v153;  // eax
    unsigned int v154;  // esi
    unsigned int *v155;  // ecx
    unsigned int *v156;  // eax
    unsigned int v157;  // eax
    st_8a0da0_3 *v158;  // edx
    unsigned int *v159;  // ecx
    unsigned int *v160;  // ecx
    unsigned int v161;  // eax
    int v162;  // eax
    unsigned int v82;  // eax
    unsigned int v0;  // [bp-0x23c]
    unsigned int v1;  // [bp-0x238]
    unsigned int v2;  // [bp-0x234]
    unsigned int v3;  // [bp-0x230]
    unsigned int v4;  // [bp-0x1f4]
    int v5;  // [bp-0x1f0]
    char *v6;  // [bp-0x1ec]
    unsigned int v7;  // [bp-0x1e8]
    char *v8;  // [bp-0x1e4], Other Possible Types: int
    st_8a0da0_4 **v9;  // [bp-0x1e0], Other Possible Types: char *
    char *v10;  // [bp-0x1dc]
    char *v11;  // [bp-0x1d4]
    char v12;  // [bp-0x190]
    char v13;  // [bp-0x174]
    unsigned int v14;  // [bp-0x158]
    unsigned int v15;  // [bp-0x154]
    char v16;  // [bp-0x150]
    unsigned int v17;  // [bp-0x12c]
    unsigned int v18;  // [bp-0x128]
    char v19;  // [bp-0x124]
    char v20;  // [bp-0x100]
    char v21;  // [bp-0xfc]
    char v22;  // [bp-0xe4]
    char v23;  // [bp-0xe4]
    unsigned int v24;  // [bp-0xe4]
    unsigned int v25;  // [bp-0xe0]
    char v26;  // [bp-0xdc]
    char v27;  // [bp-0xd4]
    char v28;  // [bp-0xcc]
    char v29;  // [bp-0xc4]
    char v30;  // [bp-0xbc]
    char v31;  // [bp-0xb4]
    char v32;  // [bp-0xac]
    char v33;  // [bp-0xa4]
    char v34;  // [bp-0xa4]
    unsigned int v35;  // [bp-0xa4]
    unsigned int v36;  // [bp-0xa0]
    char v37;  // [bp-0x9c]
    char v38;  // [bp-0x94]
    char v39;  // [bp-0x8c]
    char v40;  // [bp-0x84]
    char v41;  // [bp-0x7c]
    int v42;  // [bp-0x78], Other Possible Types: unsigned short
    unsigned int v43;  // [bp-0x68]
    unsigned int v44;  // [bp-0x64]
    char v45;  // [bp-0x60]
    int v46;  // [bp-0x5c]
    int v47;  // [bp-0x58]
    unsigned int v48;  // [bp-0x54]
    unsigned int v49;  // [bp-0x50]
    unsigned int v50;  // [bp-0x4c]
    int v51;  // [bp-0x48], Other Possible Types: unsigned int
    char v52;  // [bp-0x44]
    char v53;  // [bp-0x40], Other Possible Types: int
    char v54;  // [bp-0x3c]
    st_8a0da0_4 **v55;  // [bp-0x38]
    int v56;  // [bp-0x28]
    unsigned int v57;  // [bp-0x24]
    st_8a0da0_3 *v58;  // [bp-0x20], Other Possible Types: unsigned int
    unsigned int v59;  // [bp-0x20]
    float v60;  // [bp-0x1c]
    float m;  // [bp-0x1c]
    unsigned int i;  // [bp-0x1c], Other Possible Types: int
    unsigned int v63;  // [bp-0x1c]
    float v64;  // [bp-0x18]
    unsigned int v65;  // [bp-0x18]
    unsigned int v66;  // [bp-0x18]
    float v67;  // [bp-0x18]
    unsigned int v68;  // [bp-0x18]
    char j;  // [bp-0x11]
    unsigned int v70;  // [bp-0x10]
    unsigned int v71;  // [bp-0xc]
    unsigned int v72;  // [bp-0x8], Other Possible Types: char

    v72 = 0xffffffff;
    v71 = &g_c824db;
    v70 = NtGetCurrentTeb()->Reserved1[0];
    NtGetCurrentTeb()->Reserved1[0] = &v70;
    v73 = script_open(&g_10bee78, a1);
    if (!(char)v73)
    {
        NtGetCurrentTeb()->Reserved1[0] = v70;
        return v73;
    }
    v74 = a0;
    sub_554d70(v75, v76, v77);
    v57 = 7;
    v56 = 0;
    *(unsigned short *)&v55 = 0;
    v72 = 0;
    v44 = 7;
    v43 = 0;
    *(unsigned short *)&v42 = 0;
    v72 = 1;
    j = 0;
    if ((char)sub_8307e0(&v54, 1))
    {
        do
        {
            sub_82ffe0(&v54);
            *(unsigned int *)&m = (unsigned int)v60;
            *(unsigned int *)&v67 = (unsigned int)v64;
            if (!(char)sub_8a0380(v74, &v54, a3))
                continue;
            if (!sub_403ff0(0, v56, &g_e174a4, sub_bffdcd(&g_e174a4)))
            {
                sub_8304e0(v74->padding_8);
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if (!sub_403ff0(0, v56, &g_e1dda4, sub_bffdcd(&g_e1dda4)))
            {
                sub_8304e0(&v74->padding_8[4]);
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if (!sub_403ff0(0, v56, &g_e17490, sub_bffdcd(&g_e17490)))
            {
                sub_8304e0(&v74->padding_8[8]);
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e1f208))
            {
                sub_8304e0(&v74->padding_8[12]);
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e296c4))
            {
                v78 = script_read_int(&j);
                if (!j)
                    break;
                sub_8a31a0();
                v72 = 2;
                v17 = v78;
                v18 = script_read_int(NULL);
                sub_8304e0(&v19);
                v79 = script_read_int(&j);
                if (j)
                {
                    v34 = v33;
                    do
                    {
                        v35 = v79;
                        v36 = script_read_int(NULL);
                        sub_407170(&v35);
                        v60 = script_read_float(NULL);
                        sub_85bc60(&v60);
                        v79 = script_read_int(&j);
                        v34 = v35;
                    } while (j);
                }
                k = v74->field_27c;
                if (v74->field_27c != *(int *)&v74->padding_280[0])
                {
                    do
                    {
                        if (*(int *)(k + 4) >= (int)v17 && *(int *)k <= (int)v18)
                            k = *(int *)sub_8a3780(&v20, k);
                        else
                            k += 44;
                    } while (k != *(int *)&v74->padding_280[0]);
                }
                v9 = &v17;
                sub_8a3850(v9);
                v72 = 1;
                sub_4e39b0(v9);
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e296a4))
            {
                *(unsigned int *)&m = script_read_int(NULL);
                sub_404560(&m);
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e29684))
            {
                sub_434a80();
                v81 = __int_as_float(script_read_int(&j));
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                if (j)
                {
                    do
                    {
                        m = v81;
                        sub_402150(&m);
                        v10 = &v26;
                        v72 = 3;
                        sub_46d0b0(v10);
                        v72 = 1;
                        sub_402010(v10);
                        v81 = __int_as_float(script_read_int(&j));
                        v60 = m;
                        *(unsigned int *)&v67 = (unsigned int)v64;
                    } while (j);
                }
            }
            else if ((char)sub_4047d0(&v54, &g_e29660))
            {
                *(unsigned int *)&m = script_read_int(NULL);
                sub_404560(&m);
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e29630))
            {
                *(unsigned int *)&m = script_read_int(NULL);
                sub_404560(&m);
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e29600))
            {
                *(unsigned int *)&m = script_read_int(NULL);
                sub_404560(&m);
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e295c4))
            {
                *(unsigned int *)&m = script_read_int(NULL);
                sub_404560(&m);
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e29598))
            {
                sub_434a80();
                sub_434a80();
                v82 = script_read_int(&j);
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                if (j)
                {
                    do
                    {
                        i = v82;
                        sub_402150(&i);
                        v8 = &v31;
                        v72 = 4;
                        sub_46d0b0(v8);
                        v72 = 1;
                        sub_402010(v8);
                        *(unsigned int *)&m = script_read_int(NULL);
                        sub_402150(&m);
                        v6 = &v32;
                        v72 = 5;
                        sub_46d0b0(v6);
                        v72 = 1;
                        sub_402010(v6);
                        v82 = script_read_int(&j);
                        *(unsigned int *)&v67 = (unsigned int)v64;
                    } while (j);
                }
            }
            else if ((char)sub_4047d0(&v54, &g_e29568))
            {
                v74->field_2b4 = -(0 < script_read_int(NULL) - 1) + 1;
                v74->field_2b8 = script_read_int(NULL);
                v74->field_2bc = script_read_int(NULL);
                v74->field_2c0 = script_read_int(NULL);
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e14e44))
            {
                sub_830710(&v41);
                if ((char)sub_4047d0(&v41, &g_e23d28))
                {
                    m = 0;
                    sub_404560(&m);
                    *(unsigned int *)&v67 = (unsigned int)v64;
                }
                else
                {
                    *(unsigned int *)&m = (unsigned int)v60;
                    *(unsigned int *)&v67 = (unsigned int)v64;
                    if ((char)sub_4047d0(&v41, &g_e23d14))
                    {
                        m = 1e-45;
                        sub_404560(&m);
                        *(unsigned int *)&v67 = (unsigned int)v64;
                    }
                }
            }
            else if ((char)sub_4047d0(&v54, &g_e2954c))
            {
                *(unsigned int *)&m = script_read_int(NULL);
                sub_404560(&m);
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e29524))
            {
                l = 5;
                do
                {
                    v84 = l;
                    *(unsigned int *)&m = script_read_int(NULL);
                    sub_404560(&m);
                    l = v84 - 1;
                    *(unsigned int *)&v67 = (unsigned int)v64;
                } while (l);
            }
            else if ((char)sub_4047d0(&v54, &g_e294f0))
            {
                v58 = &v74->padding_b0[32];
                m = 7e-45;
                do
                {
                    v60 = m;
                    i4 = 2;
                    do
                    {
                        v86 = i4;
                        *(unsigned int *)&v67 = script_read_int(NULL);
                        sub_404560(&v67);
                        i4 = v86 - 1;
                    } while (i4);
                    v58 = v58->padding_20;
                    *(unsigned int *)&m = *(unsigned int *)&v60 - 1;
                } while (*(unsigned int *)&m);
            }
            else if ((char)sub_4047d0(&v54, &g_e294b0))
            {
                v58 = &v74->padding_b0[48];
                m = 7e-45;
                do
                {
                    v60 = m;
                    i5 = 2;
                    do
                    {
                        v88 = i5;
                        *(unsigned int *)&v67 = script_read_int(NULL);
                        sub_404560(&v67);
                        i5 = v88 - 1;
                    } while (i5);
                    v58 = v58->padding_20;
                    *(unsigned int *)&m = *(unsigned int *)&v60 - 1;
                } while (*(unsigned int *)&m);
            }
            else if ((char)sub_4047d0(&v54, &g_e29470))
            {
                sub_434a80();
                count = __int_as_float(script_read_int(&j));
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                if (j)
                {
                    do
                    {
                        v67 = count;
                        sub_402150(&v67);
                        v10 = &v37;
                        v72 = 6;
                        sub_46d0b0(v10);
                        v72 = 1;
                        sub_402010(v10);
                        count = __int_as_float(script_read_int(&j));
                        *(unsigned int *)&m = (unsigned int)v60;
                    } while (j);
                }
            }
            else if ((char)sub_4047d0(&v54, &g_e2944c))
            {
                n = 2;
                do
                {
                    v91 = n;
                    *(unsigned int *)&v67 = script_read_int(NULL);
                    sub_404560(&v67);
                    n = v91 - 1;
                    v64 = v67;
                    *(unsigned int *)&m = (unsigned int)v60;
                } while (n);
            }
            else if ((char)sub_4047d0(&v54, &g_cc9444))
            {
                *(unsigned int *)&v67 = script_read_int(NULL);
                sub_404560(&v67);
                *(unsigned int *)&m = (unsigned int)v60;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e29418))
            {
                i0 = 5;
                do
                {
                    v93 = i0;
                    *(unsigned int *)&v67 = script_read_int(NULL);
                    sub_404560(&v67);
                    i0 = v93 - 1;
                    v64 = v67;
                    *(unsigned int *)&m = (unsigned int)v60;
                } while (i0);
            }
            else if ((char)sub_4047d0(&v54, &g_e293e4))
            {
                sub_434a80();
                count1 = __int_as_float(script_read_int(&j));
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                if (j)
                {
                    do
                    {
                        v67 = count1;
                        sub_402150(&v67);
                        v10 = &v30;
                        v72 = 7;
                        sub_46d0b0(v10);
                        v72 = 1;
                        sub_402010(v10);
                        count1 = __int_as_float(script_read_int(&j));
                        v64 = v67;
                        *(unsigned int *)&m = (unsigned int)v60;
                    } while (j);
                }
            }
            else if ((char)sub_4047d0(&v54, &g_e293c8))
            {
                v95 = a2;
                m = 3e-45;
                do
                {
                    v60 = m;
                    if (v95 != 1 && v95 != 2 && v95 != 4 && v95 != 3 && v95 && v95 != 5)
                    {
                        count2 = script_read_float(NULL);
                        v97 = count2 * g_cd5b2c;
                        v11 = &v64;
                    }
                    else
                    {
                        v97 = script_read_float(NULL);
                        v11 = &v64;
                    }
                    v64 = (float)v97;
                    sub_404560(v11);
                    *(unsigned int *)&m = *(unsigned int *)&v60 - 1;
                    *(unsigned int *)&v67 = (unsigned int)v64;
                } while (*(unsigned int *)&m);
            }
            else if ((char)sub_4047d0(&v54, &g_e293ac))
            {
                i1 = 2;
                do
                {
                    v99 = i1;
                    v67 = script_read_float(NULL);
                    sub_404560(&v67);
                    i1 = v99 - 1;
                    *(unsigned int *)&m = (unsigned int)v60;
                } while (i1);
            }
            else if ((char)sub_4047d0(&v54, &g_e1d498))
            {
                sub_8a2c40();
                v72 = 8;
                sub_4e40b0();
                v58 = script_read_int(&j);
                sub_404560(&v58);
                if (j)
                {
                    do
                    {
                        v65 = script_read_int(NULL);
                        sub_404560(&v65);
                        *(unsigned int *)&v64 = script_read_int(NULL);
                        sub_404560(&v64);
                        sub_8a3240(&v21);
                        v59 = script_read_int(&j);
                        sub_404560(&v59);
                        v58 = v59;
                    } while (j);
                }
                v72 = 1;
                sub_4e2630();
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e29390))
            {
                sub_434a80();
                v100 = __int_as_float(script_read_int(&j));
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                if (j)
                {
                    do
                    {
                        v67 = v100;
                        sub_402150(&v67);
                        v10 = &v40;
                        v72 = 9;
                        sub_46d0b0(v10);
                        v72 = 1;
                        sub_402010(v10);
                        v100 = __int_as_float(script_read_int(&j));
                        v64 = v67;
                        *(unsigned int *)&m = (unsigned int)v60;
                    } while (j);
                }
            }
            else if ((char)sub_4047d0(&v54, &g_e2935c))
            {
                *(unsigned int *)&v67 = script_read_int(NULL);
                sub_404560(&v67);
                *(unsigned int *)&m = (unsigned int)v60;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e1dae8))
            {
                i2 = 2;
                do
                {
                    v103 = i2;
                    *(unsigned int *)&v67 = script_read_int(NULL);
                    sub_404560(&v67);
                    i2 = v103 - 1;
                    v64 = v67;
                    *(unsigned int *)&m = (unsigned int)v60;
                } while (i2);
            }
            else if ((char)sub_4047d0(&v54, &g_e29340))
            {
                *(unsigned int *)&v67 = script_read_int(NULL);
                sub_404560(&v67);
                *(unsigned int *)&m = (unsigned int)v60;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e29304))
            {
                sub_434a80();
                v104 = __int_as_float(script_read_int(&j));
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                if (j)
                {
                    do
                    {
                        v67 = v104;
                        sub_402150(&v67);
                        v10 = &v28;
                        v72 = 10;
                        sub_46d0b0(v10);
                        v72 = 1;
                        sub_402010(v10);
                        v104 = __int_as_float(script_read_int(&j));
                        v64 = v67;
                        *(unsigned int *)&m = (unsigned int)v60;
                    } while (j);
                }
            }
            else if ((char)sub_4047d0(&v54, &g_e292d8))
            {
                *(unsigned int *)&v67 = script_read_int(NULL);
                sub_404560(&v67);
                *(unsigned int *)&m = (unsigned int)v60;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e292ac))
            {
                sub_830710(&v41);
                if ((char)sub_4047d0(&v41, &g_cc3d74))
                {
                    v67 = 0;
                    sub_404560(&v67);
                    *(unsigned int *)&m = (unsigned int)v60;
                }
                else
                {
                    if ((char)sub_4047d0(&v41, &g_e1c8e8))
                    {
                        v67 = 1e-45;
                        sub_404560(&v67);
                        *(unsigned int *)&m = (unsigned int)v60;
                    }
                    else
                    {
                        *(unsigned int *)&m = (unsigned int)v60;
                        *(unsigned int *)&v67 = (unsigned int)v64;
                        if ((char)sub_4047d0(&v41, &g_e1c8d4))
                        {
                            v67 = 3e-45;
                            sub_404560(&v67);
                            *(unsigned int *)&m = (unsigned int)v60;
                        }
                    }
                }
            }
            else if ((char)sub_4047d0(&v54, &g_e1d9f0))
            {
                sub_8304e0(&v74->padding_1d8[56]);
                v68 = script_read_int(NULL);
                sub_404560(&v68);
                sub_8304e0(&v74->padding_1d8[60]);
                *(unsigned int *)&v67 = script_read_int(NULL);
                sub_404560(&v67);
                *(unsigned int *)&m = (unsigned int)v60;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e29280))
            {
                sub_8304e0(&v74->padding_1d8[124]);
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_cda0d0))
            {
                v105 = 0;
                v46 = 0;
                v47 = 0;
                v48 = 0;
                v49 = 0;
                v50 = 300;
                v72 = 11;
                sub_554440();
                v106 = script_reader_next_type(&g_1051228.padding_0[0]);
                if (v106)
                {
                    do
                    {
                        if (v106 == 5)
                            break;
                        if (v106 == 6)
                        {
                            sub_4035f0(sub_a92c50(sub_8b2ad0()));
                            v9 = &v12;
                            v8 = &v51;
                            v72 = 12;
                            sub_4c8190(v8, v9);
                            v72 = 11;
                            sub_b8e070(v8, v9);
                            if (v51 == *(int *)&g_10bf07c)
                                continue;
                            sub_a47130(v51 + 40);
                        }
                        else
                        {
                            if (v106 == 2)
                            {
                                v49 = sub_8b29f0();
                                continue;
                            }
                            else
                            {
                                if (v106 == 7)
                                {
                                    sub_4035f0(sub_a92c50(sub_8b2af0()));
                                    v72 = 13;
                                    if ((char)sub_4047d0(&v13, &g_e29274))
                                    {
                                        *(unsigned int *)&v74->padding_1d8[112] = 0;
                                        v72 = 11;
                                        sub_b8e070();
                                        goto LABEL_8a1d95;
                                    }
                                    else
                                    {
                                        if ((char)sub_4047d0(&v13, &g_e29260))
                                        {
                                            *(unsigned int *)&v74->padding_1d8[112] = 1;
                                            v72 = 11;
                                            sub_b8e070();
                                            goto LABEL_8a1d95;
                                        }
                                        else
                                        {
                                            if ((char)sub_4047d0(&v13, &g_e29258))
                                            {
                                                *(unsigned int *)&v74->padding_1d8[112] = 2;
                                                v72 = 11;
                                                sub_b8e070();
                                                goto LABEL_8a1d95;
                                            }
                                            else
                                            {
                                                if ((char)sub_4047d0(&v13, &g_e29248))
                                                    *(unsigned int *)&v74->padding_1d8[112] = 3;
                                                v72 = 11;
                                                sub_b8e070();
                                                goto LABEL_8a1d95;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    if (v106 != 8)
                                        continue;
                                    v109 = *(char *)sub_8b2b10();
                                    if (v109 == 38)
                                    {
                                        if (v47 != v105)
                                            sub_5c5500(&v45);
                                    }
                                    else
                                    {
                                        if (v109 == 33)
                                        {
                                            v50 = 150;
                                        }
                                        else
                                        {
                                            if (v109 == 44)
                                            {
                                                v50 = 300;
                                            }
                                            else
                                            {
                                                if (v109 == 126)
                                                    v50 = 1000;
                                            }
                                        }
                                        if (v47 != v105)
                                            sub_4e5630(&v45);
                                    }
                                    sub_4e2e90();
                                }
                            }
                        }
                        v105 = v46;
LABEL_8a1d95:
                    } while ((v106 = script_reader_next_type(&g_1051228.padding_0[0]), v106));
                    if (v47 != v105)
                        sub_4e5630(&v45);
                }
                v72 = 1;
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                if (v105)
                {
                    sub_c00109(v105);
                    *(unsigned int *)&m = (unsigned int)v60;
                    *(unsigned int *)&v67 = (unsigned int)v64;
                }
            }
            else if ((char)sub_4047d0(&v54, &g_e2922c))
            {
                sub_434a80();
                v110 = __int_as_float(script_read_int(&j));
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                if (j)
                {
                    do
                    {
                        v67 = v110;
                        sub_402150(&v67);
                        v10 = &v27;
                        v72 = 14;
                        sub_46d0b0(v10);
                        v72 = 1;
                        sub_402010(v10);
                        v110 = __int_as_float(script_read_int(&j));
                        *(unsigned int *)&m = (unsigned int)v60;
                    } while (j);
                }
            }
            else if ((char)sub_4047d0(&v54, &g_e29210))
            {
                sub_48f950();
                sub_557b70(script_read_int(NULL));
                v112 = __int_as_float(script_read_int(&j));
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                if (j)
                {
                    do
                    {
                        v67 = v112;
                        sub_402150(&v67);
                        v72 = 15;
                        v9 = &v29;
                        sub_46d0b0(v9);
                        v72 = 1;
                        sub_402010(v9);
                        v112 = __int_as_float(script_read_int(&j));
                        v64 = v67;
                    } while (j);
                    v74 = a0;
                    *(unsigned int *)&m = (unsigned int)v60;
                }
            }
            else if ((char)sub_4047d0(&v54, &g_e291ec))
            {
                v113 = script_read_int(&j);
                if (!j)
                    break;
                sub_8a31a0();
                v72 = 16;
                v14 = v113;
                v15 = script_read_int(NULL);
                sub_8304e0(&v16);
                v114 = script_read_int(&j);
                v23 = v22;
                if (j)
                {
                    do
                    {
                        v24 = v114;
                        v25 = script_read_int(NULL);
                        sub_407170(&v24);
                        v64 = script_read_float(NULL);
                        sub_85bc60(&v64);
                        v114 = script_read_int(&j);
                        v23 = v24;
                    } while (j);
                }
                i3 = v74->field_27c;
                if (v74->field_27c != *(int *)&v74->padding_280[0])
                {
                    do
                    {
                        if (*(int *)(i3 + 4) >= (int)v14 && *(int *)i3 <= (int)v15)
                            i3 = *(int *)sub_8a3780(&v53, i3);
                        else
                            i3 += 44;
                    } while (i3 != *(int *)&v74->padding_280[0]);
                }
                v9 = &v14;
                sub_8a3850(v9);
                v72 = 1;
                sub_4e39b0(v9);
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                continue;
            }
            else if ((char)sub_4047d0(&v54, &g_e291cc))
            {
                v74->field_298 = script_read_int(NULL);
                v74->field_29c = script_read_int(NULL);
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
            }
            else if ((char)sub_4047d0(&v54, &g_e291b0))
            {
                v74->field_2a0 = script_read_int(NULL) != 0;
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
            }
            else if ((char)sub_4047d0(&v54, &g_e2917c))
            {
                sub_403f00();
                v72 = 0x11;
                if ((char)sub_8304e0(&v52))
                {
                    do
                    {
                        sub_403be0(&v52);
                    } while ((char)sub_8304e0(&v52));
                }
                v72 = 1;
                sub_a53450();
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
            }
            else if ((char)sub_4047d0(&v54, &g_e2915c))
            {
                sub_434a80();
                v116 = __int_as_float(script_read_int(&j));
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                if (j)
                {
                    do
                    {
                        v67 = v116;
                        sub_402150(&v67);
                        v10 = &v39;
                        v72 = 18;
                        sub_46d0b0(v10);
                        v72 = 1;
                        sub_402010(v10);
                        v116 = __int_as_float(script_read_int(&j));
                        v64 = v67;
                        *(unsigned int *)&m = (unsigned int)v60;
                    } while (j);
                }
            }
            else if ((char)sub_4047d0(&v54, &g_e2913c))
            {
                sub_434a80();
                v117 = __int_as_float(script_read_int(&j));
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                if (j)
                {
                    do
                    {
                        v67 = v117;
                        sub_402150(&v67);
                        v10 = &v38;
                        v72 = 19;
                        sub_46d0b0(v10);
                        v72 = 1;
                        sub_402010(v10);
                        v117 = __int_as_float(script_read_int(&j));
                        *(unsigned int *)&m = (unsigned int)v60;
                    } while (j);
                }
            }
            else if ((char)sub_4047d0(&v54, &g_e29118))
            {
                v65 = script_read_int(NULL);
                sub_404560(&v65);
                *(unsigned int *)&v67 = script_read_int(NULL);
                sub_404560(&v67);
                *(unsigned int *)&m = (unsigned int)v60;
            }
            else if ((char)sub_4047d0(&v54, &g_e290e4))
            {
                v66 = script_read_int(NULL);
                sub_404560(&v66);
                *(unsigned int *)&v67 = script_read_int(NULL);
                sub_404560(&v67);
                *(unsigned int *)&m = (unsigned int)v60;
            }
            else
            {
                *(unsigned int *)&m = (unsigned int)v60;
                *(unsigned int *)&v67 = (unsigned int)v64;
                if (!(char)sub_830120(&v54))
                {
                    if (v57 < 8)
                        v55 = &v55;
                    v9 = v55;
                    v8 = a1;
                    v7 = &g_e14614;
                    g_ff2ebc();
                }
            }
        } while ((v64 = v67, v60 = m, (char)sub_8307e0(&v54, 1)));
    }
    v118 = g_12101d8;
    v119 = &a0->field_18;
    iter = &a0->field_ac;
    i = 5;
    do
    {
        v63 = i;
        if ((*(int *)(&iter->padding_0[0] - 4) ^ g_12101dc) - (char *)iter + 4 != iter->padding_0)
        {
            sub_b170b0((char *)iter - 4, 63);
            v118 = g_12101d8;
        }
        v121 = (unsigned int)(iter->padding_0 * 4);
        v122 = (char *)v118->field_44 + v121;
        v123 = v121 + v118->field_48;
        v51 = *v122 ^ g_12101dc ^ v122;
        if (v51 != (*v123 ^ g_12101dc ^ v123))
        {
            sub_b170b0((char *)iter - 4, 64);
            v118 = g_12101d8;
        }
        if ((v119->padding_0 ^ g_12101dc) - (char *)v119 != v119->field_4)
        {
            sub_b170b0(v119, 63);
            v118 = g_12101d8;
        }
        v124 = v119->field_4 * 4;
        v125 = (char *)v118->field_44 + v124;
        v126 = g_12101dc ^ v125 ^ *v125;
        v127 = v124 + v118->field_48;
        if (v126 != (*v127 ^ g_12101dc ^ v127))
        {
            sub_b170b0(v119, 64);
            v118 = g_12101d8;
        }
        if (v51 > v126)
        {
            v5 = a1;
            v4 = &g_e29098;
            g_ff2ebc();
        }
        iter = iter->padding_8;
        i = v63 - 1;
    } while (i);
    v128 = a0->padding_20;
    while (1)
    {
        i = (!v128->field_4 ? 0 : (int)(*(int *)&v128->padding_8[0] - v128->field_4) >> 3);
        if ((v119->padding_0 ^ g_12101dc) - (char *)v119 != v119->field_4)
        {
            sub_b170b0(v119, 63);
            v118 = g_12101d8;
        }
        v129 = v119->field_4 * 4;
        v130 = *(int *)((char *)v118->field_44 + v129) ^ g_12101dc ^ (char *)v118->field_44 + v129;
        v131 = v129 + v118->field_48;
        if (v130 != (*v131 ^ g_12101dc ^ v131))
        {
            sub_b170b0(v119, 64);
            v118 = g_12101d8;
        }
        if ((unsigned int)i >= (unsigned int)v130)
            break;
        v132 = v128->field_4;
        v133 = a0->field_28 - 8;
        if (v132 && (!v132 ? 0 : (int)(*(int *)&v128->padding_8[0] - v132) >> 3) < (int)(*(int *)&v128->padding_8[4] - v132) >> 3)
        {
            sub_4692f0(*(int *)&v128->padding_8[0], 1, v133, v128, v53);
            *(unsigned int *)&v128->padding_8[0] = *(int *)&v128->padding_8[0] + 8;
            v118 = g_12101d8;
        }
        else
        {
            sub_46a6d0(*(int *)&v128->padding_8[0], 1, v133);
            v118 = g_12101d8;
        }
    }
    v134 = a0;
    v135 = &v134->padding_2c4[16];
    if (v134->field_2d8 && (int)(*(int *)&v135->padding_8[0] - v134->field_2d8) >> 3)
    {
        while (1)
        {
            i = (!v135->field_4 ? 0 : (int)(*(int *)&v135->padding_8[0] - v135->field_4) >> 3);
            if ((v119->padding_0 ^ g_12101dc) - (char *)v119 != v119->field_4)
            {
                sub_b170b0(v119, 63);
                v118 = g_12101d8;
            }
            v136 = v119->field_4 * 4;
            v137 = *(int *)((char *)v118->field_44 + v136) ^ g_12101dc ^ (char *)v118->field_44 + v136;
            v138 = v136 + v118->field_48;
            if (v137 != (g_12101dc ^ v138 ^ *v138))
            {
                sub_b170b0(v119, 64);
                v118 = g_12101d8;
            }
            if ((unsigned int)i >= (unsigned int)v137)
                break;
            v139 = v135->field_4;
            v140 = a0->field_2dc - 8;
            if (v139 && (!v139 ? 0 : (int)(*(int *)&v135->padding_8[0] - v139) >> 3) < (int)(*(int *)&v135->padding_8[4] - v139) >> 3)
            {
                sub_4692f0(*(int *)&v135->padding_8[0], 1, v140, v135, v53);
                *(unsigned int *)&v135->padding_8[0] = *(int *)&v135->padding_8[0] + 8;
                v118 = g_12101d8;
            }
            else
            {
                sub_46a6d0(*(int *)&v135->padding_8[0], 1, v140);
                v118 = g_12101d8;
            }
        }
        v134 = a0;
    }
    v141 = v134->padding_2e4;
    if (v134->field_2e8 && (int)(*(int *)&v141->padding_8[0] - v134->field_2e8) >> 3)
    {
        while (1)
        {
            i = (!v141->field_4 ? 0 : (int)(*(int *)&v141->padding_8[0] - v141->field_4) >> 3);
            if ((v119->padding_0 ^ g_12101dc) - (char *)v119 != v119->field_4)
            {
                sub_b170b0(v119, 63);
                v118 = g_12101d8;
            }
            v142 = v119->field_4 * 4;
            v143 = *(int *)((char *)v118->field_44 + v142) ^ g_12101dc ^ (char *)v118->field_44 + v142;
            v144 = v142 + v118->field_48;
            if (v143 != (*v144 ^ g_12101dc ^ v144))
            {
                sub_b170b0(v119, 64);
                v118 = g_12101d8;
            }
            if ((unsigned int)i >= (unsigned int)v143)
                break;
            v145 = v141->field_4;
            v146 = a0->field_2ec - 8;
            if (v145 && (!v145 ? 0 : (int)(*(int *)&v141->padding_8[0] - v145) >> 3) < (int)(*(int *)&v141->padding_8[4] - v145) >> 3)
            {
                sub_4692f0(*(int *)&v141->padding_8[0], 1, v146, v141, v53);
                *(unsigned int *)&v141->padding_8[0] = *(int *)&v141->padding_8[0] + 8;
                v118 = g_12101d8;
            }
            else
            {
                sub_46a6d0(*(int *)&v141->padding_8[0], 1, v146);
                v118 = g_12101d8;
            }
        }
        v134 = a0;
    }
    v147 = &v134->padding_b0[280];
    if (v134->field_1cc && (int)(*(int *)&v147->padding_8[0] - v134->field_1cc) >> 3)
    {
        while (1)
        {
            i = (!v147->field_4 ? 0 : (int)(*(int *)&v147->padding_8[0] - v147->field_4) >> 3);
            if ((v119->padding_0 ^ g_12101dc) - (char *)v119 != v119->field_4)
            {
                sub_b170b0(v119, 63);
                v118 = g_12101d8;
            }
            v148 = v119->field_4 * 4;
            v149 = (char *)v118->field_44 + v148;
            v150 = g_12101dc ^ v149 ^ *v149;
            v151 = v148 + v118->field_48;
            if (v150 != (g_12101dc ^ v151 ^ *v151))
            {
                sub_b170b0(v119, 64);
                v118 = g_12101d8;
            }
            if ((unsigned int)i >= (unsigned int)v150)
                break;
            v152 = v147->field_4;
            v153 = a0->field_1d0 - 8;
            if (v152 && (!v152 ? 0 : (int)(*(int *)&v147->padding_8[0] - v152) >> 3) < (int)(*(int *)&v147->padding_8[4] - v152) >> 3)
            {
                sub_4692f0(*(int *)&v147->padding_8[0], 1, v153, v147, v53);
                *(unsigned int *)&v147->padding_8[0] = *(int *)&v147->padding_8[0] + 8;
                v118 = g_12101d8;
            }
            else
            {
                sub_46a6d0(*(int *)&v147->padding_8[0], 1, v153);
                v118 = g_12101d8;
            }
        }
        v134 = a0;
    }
    v154 = a2;
    if (v154 == 6)
    {
        v155 = &v118->field_44[v134->field_4];
        *v155 = ~g_12101dc ^ v155;
        v156 = g_12101d8->field_48 + v134->field_4 * 4;
        *v156 = ~g_12101dc ^ v156;
    }
    else if (v154 >= 6)
    {
        v3 = 6;
        v2 = v154;
        v1 = "nstl::sarray<struct STScriptFileList,6>::operator`[]'";
        v0 = &g_cbb3a0;
        g_ff2ebc();
    }
    else
    {
        v157 = sub_573fb0(a1);
        v158 = a0;
        v159 = &g_12101d8->field_44[v158->field_4];
        *v159 = g_12101dc ^ v157 ^ v159;
        v160 = g_12101d8->field_48 + v158->field_4 * 4;
        *v160 = g_12101dc ^ v157 ^ v160;
    }
    if (v44 >= 8)
        sub_bfffdd(v42);
    v161 = 0;
    v43 = 0;
    v42 = 0;
    v44 = 7;
    if (v57 >= 8)
        v161 = sub_bfffdd(v55);
    v162 = _INSERT(v161, 0, 1);
    NtGetCurrentTeb()->Reserved1[0] = v70;
    return v162;
}
