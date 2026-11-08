typedef struct st_551ad0_2 {
    char padding_0[4];
    unsigned int field_4;
} st_551ad0_2;

typedef struct st_551ad0_0 {
    unsigned int field_0[4];
    unsigned int field_10;
    char padding_14[12];
    unsigned int field_20;
    unsigned int field_24;
    char padding_28[8];
    unsigned int field_30;
    char padding_34[8];
    unsigned int field_3c;
    char padding_40[4];
    unsigned int field_44;
    char padding_48[4];
    unsigned int field_4c;
    unsigned int field_50;
    char padding_54[8];
    unsigned int field_5c;
    unsigned int field_60;
    char padding_64[8];
    unsigned int field_6c;
    char padding_70[4];
    unsigned int field_74;
    char padding_78[4];
    unsigned int field_7c;
    char padding_80[32];
    unsigned int field_a0;
    char padding_a4[40];
    unsigned int field_cc;
    char padding_d0[72];
    unsigned int field_118;
    unsigned int field_11c;
    char padding_120[88];
    unsigned int field_178;
    unsigned int field_17c;
    char padding_180[4];
    unsigned int field_184;
    int field_188;
    unsigned int field_18c;
    char padding_190[116];
    unsigned int field_204;
    unsigned int field_208;
    char padding_20c[52];
    unsigned int field_240;
    unsigned int field_244;
    char padding_248[36];
    unsigned int field_26c;
    unsigned int field_270;
    char field_274;
    char padding_275[19];
    char field_288;
    char padding_289[3];
    unsigned int field_28c;
    unsigned int field_290;
    unsigned int field_294;
    char padding_298[20];
    unsigned int field_2ac;
    unsigned int field_2b0;
    char padding_2b4[8];
    unsigned int field_2bc;
    unsigned int field_2c0;
    char padding_2c4[8];
    unsigned int field_2cc;
    char padding_2d0[4];
    unsigned int field_2d4;
    char padding_2d8[24];
    unsigned int field_2f0;
    unsigned int field_2f4;
    unsigned int field_2f8;
    char padding_2fc[216];
    int field_3d4;
} st_551ad0_0;

typedef struct st_551ad0_7 {
    char field_0;
} st_551ad0_7;

typedef struct st_551ad0_8 {
    char padding_0[16];
    struct st_551ad0_1 *field_10;
} st_551ad0_8;

typedef struct st_551ad0_10 {
    struct st_551ad0_8 *field_0;
} st_551ad0_10;

typedef struct st_551ad0_1 {
    unsigned int field_0;
} st_551ad0_1;

extern unsigned int g_c5d27c;
extern double g_cab8e8;
extern unsigned int g_cdcdd8;
extern st_551ad0_1 *g_ff2ebc;
extern unsigned int g_1002848;
extern st_551ad0_10 *g_10030d8;
extern unsigned int g_12101d8;
extern unsigned int g_12101dc;

void func_00551ad0(st_551ad0_0 *a0, unsigned int a1, int iter, int node, int a4)
{
    st_551ad0_0 *v109;  // ebx
    int v110;  // edi
    unsigned int *v119;  // ecx
    unsigned int *v209;  // ecx
    unsigned int v210;  // esi
    unsigned int *v211;  // esi
    unsigned int *v212;  // ecx
    unsigned int v213;  // edi
    unsigned int *v214;  // edx
    st_551ad0_0 *v215;  // edi
    st_551ad0_0 *iter1;  // esi
    unsigned int *v217;  // ecx
    unsigned int *v218;  // edi
    unsigned int *v120;  // eax
    unsigned int *v219;  // edi
    unsigned int *v220;  // ecx
    unsigned int *v221;  // edx
    unsigned int *v222;  // edx
    unsigned int *v223;  // ecx
    unsigned int *v224;  // edi
    unsigned int *v225;  // edi
    unsigned int *v226;  // ecx
    unsigned int *v227;  // edx
    unsigned int *v228;  // edx
    unsigned int *v121;  // eax
    unsigned int *v229;  // edx
    st_551ad0_0 *v230;  // edi
    st_551ad0_0 *v231;  // edi
    unsigned int *v232;  // edx
    st_551ad0_0 *v233;  // ebx
    unsigned int *v234;  // ecx
    unsigned int *v235;  // edi
    unsigned int *v236;  // edi
    unsigned int *v237;  // ecx
    unsigned int *v238;  // edx
    unsigned int *v122;  // eax
    unsigned int *v239;  // edx
    st_551ad0_0 *v240;  // esi
    st_551ad0_0 *v241;  // esi
    unsigned int *v242;  // edx
    unsigned int *v243;  // edx
    unsigned int idx;  // esi
    unsigned int idx1;  // edx
    int v246;  // esi
    unsigned int v247;  // eax
    st_551ad0_0 *v248;  // esi
    st_551ad0_0 *v123;  // esi
    unsigned int v249;  // edx
    unsigned int idx2;  // eax
    unsigned int index;  // ecx
    float v252;  // esi
    float v253;  // esi
    double v254;  // mm6
    unsigned int v255;  // eax
    float v256;  // esi
    unsigned int v258;  // ecx
    unsigned int *v124;  // ecx
    int m;  // ebx
    int v260;  // eax
    int n;  // ebx
    int v262;  // eax
    int v263;  // esi
    st_551ad0_0 *v264;  // edi
    int i0;  // esi
    int v266;  // edx
    unsigned int v267;  // edx
    int i2;  // eax
    unsigned int *v125;  // edx
    int v269;  // ecx
    int v270;  // ebx
    int v271;  // edi
    int v272;  // esi
    unsigned int *v273;  // ecx
    unsigned int v274;  // edx
    unsigned int v275;  // eax
    unsigned int *v276;  // ecx
    st_551ad0_0 *v277;  // ebx
    int i3;  // edi
    unsigned int *v126;  // ecx
    int v279;  // eax
    st_551ad0_0 *v280;  // ecx
    unsigned int *v127;  // edx
    st_551ad0_0 *v128;  // esi
    int v111;  // esi
    unsigned int *v129;  // ecx
    unsigned int *v130;  // edx
    unsigned int *v131;  // ecx
    unsigned int v132;  // edx
    st_551ad0_0 *v133;  // esi
    unsigned int *v134;  // ecx
    unsigned int v135;  // edx
    unsigned int *v136;  // ecx
    unsigned int v137;  // edx
    st_551ad0_0 *v138;  // esi
    int v112;  // ebx
    unsigned int *v139;  // ecx
    unsigned int v140;  // edx
    unsigned int *v141;  // ecx
    unsigned int v142;  // edx
    int v143;  // esi
    int i;  // edi
    unsigned int v145;  // ecx
    st_551ad0_2 *v146;  // esi
    st_551ad0_2 *v147;  // edx
    unsigned int *v148;  // ecx
    unsigned int *v149;  // eax
    unsigned int *v150;  // ecx
    unsigned int *v151;  // eax
    int v152;  // esi
    int j;  // edi
    unsigned int v154;  // ecx
    st_551ad0_2 *v155;  // esi
    st_551ad0_2 *v156;  // edx
    unsigned int *v157;  // ecx
    unsigned int *v158;  // eax
    int v114;  // esi
    unsigned int *v159;  // ecx
    unsigned int *v160;  // eax
    int v161;  // esi
    int k;  // edi
    unsigned int v163;  // ecx
    st_551ad0_2 *v164;  // esi
    st_551ad0_2 *v165;  // edx
    unsigned int *v166;  // ecx
    unsigned int *v167;  // eax
    unsigned int *v168;  // ecx
    int iter2;  // edi
    unsigned int *v169;  // eax
    int v170;  // esi
    int v171;  // edi
    unsigned int v172;  // ecx
    st_551ad0_2 *v173;  // esi
    st_551ad0_2 *v174;  // edx
    unsigned int *v175;  // ecx
    unsigned int *v176;  // eax
    unsigned int *v177;  // eax
    unsigned int *v178;  // eax
    unsigned int v116;  // ecx
    st_551ad0_0 *v179;  // edi
    unsigned int *v180;  // ecx
    unsigned int *v181;  // edx
    unsigned int *v182;  // ecx
    unsigned int *v183;  // edx
    st_551ad0_0 *v184;  // edi
    unsigned int *v185;  // ecx
    unsigned int *v186;  // edx
    unsigned int *v187;  // ecx
    unsigned int *v188;  // edx
    st_551ad0_2 *v117;  // esi
    st_551ad0_0 *v189;  // edx
    st_551ad0_0 *v190;  // edi
    unsigned int v191;  // ecx
    unsigned int v192;  // eax
    unsigned int *v193;  // ecx
    unsigned int *v194;  // esi
    unsigned int *v195;  // esi
    unsigned int *v196;  // ecx
    unsigned int *v197;  // edx
    unsigned int *v198;  // edx
    st_551ad0_2 *v118;  // edx
    unsigned int *v199;  // ecx
    unsigned int *v200;  // esi
    unsigned int v201;  // esi
    unsigned int *v202;  // ecx
    unsigned int *v203;  // edx
    unsigned int v204;  // edx
    unsigned int v205;  // edx
    st_551ad0_0 *v206;  // esi
    st_551ad0_0 *v207;  // esi
    unsigned int *v208;  // edx
    unsigned int v0;  // [bp-0x4b0]
    unsigned int v1;  // [bp-0x4ac]
    char *v2;  // [bp-0x4a8]
    char *v3;  // [bp-0x4a4], Other Possible Types: float *
    char *v4;  // [bp-0x4a0]
    char *v5;  // [bp-0x498]
    unsigned int v6;  // [bp-0x494]
    char *v7;  // [bp-0x490], Other Possible Types: unsigned int
    unsigned int v8;  // [bp-0x48c]
    unsigned int v9;  // [bp-0x474]
    char *v10;  // [bp-0x470], Other Possible Types: unsigned int
    char *v11;  // [bp-0x468]
    char *v12;  // [bp-0x460]
    char *v13;  // [bp-0x448]
    char *v14;  // [bp-0x43c]
    char v15;  // [bp-0x3d8]
    char v16;  // [bp-0x3cc]
    char v17;  // [bp-0x3c0]
    char v18;  // [bp-0x3b4]
    char v19;  // [bp-0x3a8]
    unsigned int v20;  // [bp-0x390]
    int v21;  // [bp-0x38c]
    char v22;  // [bp-0x374]
    char v23;  // [bp-0x370]
    char v24;  // [bp-0x36c]
    char v25;  // [bp-0x368]
    char v26;  // [bp-0x364]
    char v27;  // [bp-0x360]
    char v28;  // [bp-0x35c]
    unsigned int v29;  // [bp-0x350]
    unsigned int v30;  // [bp-0x34c]
    char v31;  // [bp-0x344]
    unsigned int v32;  // [bp-0x340]
    char v33;  // [bp-0x33c]
    unsigned int v34;  // [bp-0x338]
    char v35;  // [bp-0x334]
    unsigned int v36;  // [bp-0x330]
    char v37;  // [bp-0x32c]
    unsigned int v38;  // [bp-0x328]
    unsigned int v39;  // [bp-0x320]
    unsigned int v40;  // [bp-0x31c]
    unsigned int v41;  // [bp-0x310]
    unsigned int v42;  // [bp-0x30c]
    char v43;  // [bp-0x304]
    unsigned int v44;  // [bp-0x300]
    char v45;  // [bp-0x2fc]
    unsigned int v46;  // [bp-0x2f8]
    char v47;  // [bp-0x2f0]
    char v48;  // [bp-0x2a0]
    char v50;  // [bp-0x204]
    unsigned int v51;  // [bp-0x1f4]
    unsigned int v52;  // [bp-0x1f0]
    unsigned int v53;  // [bp-0x1ec]
    unsigned int v54;  // [bp-0x1e8]
    unsigned int v55;  // [bp-0x1e4]
    unsigned int v56;  // [bp-0x1e0]
    unsigned int v57;  // [bp-0x1dc]
    unsigned int v58;  // [bp-0x1d8]
    char v59;  // [bp-0x1c4]
    char v60;  // [bp-0x1bc]
    char v61;  // [bp-0x1ac]
    char v62;  // [bp-0x19c]
    unsigned int v63;  // [bp-0x180]
    unsigned int v64;  // [bp-0x17c]
    char v65;  // [bp-0x174]
    char v66;  // [bp-0x16c]
    unsigned int v67;  // [bp-0x108]
    unsigned int v68;  // [bp-0x104]
    char v69;  // [bp-0xfc]
    char v70;  // [bp-0xec]
    unsigned int v71;  // [bp-0xdc]
    unsigned int v72;  // [bp-0xd8]
    char v73;  // [bp-0xd4]
    char v74;  // [bp-0xd0]
    char v75;  // [bp-0xc0]
    unsigned int v76;  // [bp-0xbc]
    unsigned int v77;  // [bp-0xb8]
    unsigned int v78;  // [bp-0xb4]
    char v79;  // [bp-0xb0]
    unsigned int v80;  // [bp-0x9c]
    unsigned int v81;  // [bp-0x98]
    unsigned int v82;  // [bp-0x8c]
    unsigned int v83;  // [bp-0x88]
    char v84;  // [bp-0x70]
    unsigned int v85;  // [bp-0x68]
    unsigned int v86;  // [bp-0x64]
    unsigned int v87;  // [bp-0x60]
    char v88;  // [bp-0x5c]
    char v89;  // [bp-0x54]
    char v90;  // [bp-0x4c]
    double v91;  // [bp-0x44], Other Possible Types: unsigned long long
    unsigned int *v92;  // [bp-0x3c]
    char v93;  // [bp-0x38]
    unsigned int l;  // [bp-0x34]
    unsigned int v95;  // [bp-0x34]
    char v96;  // [bp-0x30]
    char *v97;  // [bp-0x2c]
    int v98;  // [bp-0x28]
    st_551ad0_0 *i1;  // [bp-0x24], Other Possible Types: unsigned int
    unsigned int v100;  // [bp-0x24]
    char v101;  // [bp-0x20]
    int v102;  // [bp-0x1c]
    char v103;  // [bp-0x15]
    st_551ad0_0 *v104;  // [bp-0x14]
    unsigned int v105;  // [bp-0x10]
    unsigned int v106;  // [bp-0xc]
    unsigned int v107;  // [bp-0x8], Other Possible Types: char
    unsigned int v108;  // [bp+0x8]

    v107 = 0xffffffff;
    v106 = &g_c5d27c;
    v105 = NtGetCurrentTeb()->Reserved1[0];
    NtGetCurrentTeb()->Reserved1[0] = &v105;
    v109 = a0;
    v104 = v109;
    sub_556170(v110, v111, v112);
    v107 = 0;
    v103 = v109->field_3d4 == 6;
    sub_4e5c40(v110, v111, v112);
    sub_402e80(iter, sub_bffdcd(iter));
    v109->field_3d4 = node;
    if (a4 == 12)
        a4 = (!g_1002848 ? 3 : sub_402060());
    if (!(char)sub_8a0da0(&v22, iter, node, a4))
    {
        v21 = iter;
        v20 = &g_cdcdd8;
        g_ff2ebc();
    }
    sub_4045b0(&v22);
    sub_a53490(&v24);
    sub_a53490(&v25);
    sub_a53490(&v26);
    sub_a53490(&v27);
    sub_4045b0(&v28);
    if (v29)
    {
        v114 = (int)(v30 - v29) >> 3;
        if (v114)
        {
            node = &v19;
            sub_4044e0();
            sub_554010(v114);
            iter2 = 0;
            while (1)
            {
                node = iter2;
                if (!v29 || (int)(v30 - v29) >> 3 <= (unsigned int)iter2)
                    break;
                v116 = *(int *)&v109->padding_28[4];
                v117 = v29 + iter2 * 8;
                if (!v116 || (int)(v109->field_30 - v116) >> 3 <= (unsigned int)iter2)
                    goto LABEL_552175;
                v118 = v116 + iter2 * 8;
                if (v118 != v117)
                {
                    v119 = *(int *)(g_12101d8 + 0x44) + v117->field_4 * 4;
                    v120 = *(int *)(g_12101d8 + 0x44) + v118->field_4 * 4;
                    *v120 = v120 ^ v119 ^ *v119;
                    v121 = *(int *)(g_12101d8 + 72);
                    iter2 = node;
                    v122 = &v121[v118->field_4];
                    *v122 = v122 ^ &v121[v117->field_4] ^ v121[v117->field_4];
                }
                iter2 += 1;
            }
        }
    }
    v123 = &v109->padding_34[4];
    if (v123 != &v31)
    {
        v124 = *(int *)(g_12101d8 + 0x44);
        v125 = v123->field_0[1] * 4;
        *(unsigned int *)(v125 + v124) = v125 + v124 ^ &v124[v32] ^ v124[v32] ^ g_12101dc ^ g_12101dc;
        v126 = *(int *)(g_12101d8 + 72);
        v127 = v123->field_0[1] * 4;
        *(unsigned int *)(v127 + v126) = v127 + v126 ^ &v126[v32] ^ v126[v32] ^ g_12101dc ^ g_12101dc;
    }
    v128 = v109->padding_40;
    if (v128 != &v33)
    {
        v129 = *(int *)(g_12101d8 + 0x44);
        v130 = v128->field_0[1] * 4;
        *(unsigned int *)(v130 + v129) = v130 + v129 ^ &v129[v34] ^ v129[v34] ^ g_12101dc ^ g_12101dc;
        v131 = *(int *)(g_12101d8 + 72);
        v132 = v128->field_0[1] * 4;
        *(unsigned int *)((char *)v131 + v132) = (char *)v131 + v132 ^ &v131[v34] ^ v131[v34] ^ g_12101dc ^ g_12101dc;
    }
    v133 = &v109->padding_2c4[4];
    if (v133 != &v35)
    {
        v134 = *(int *)(g_12101d8 + 0x44);
        v135 = v133->field_0[1] * 4;
        *(unsigned int *)((char *)v134 + v135) = (char *)v134 + v135 ^ &v134[v36] ^ v134[v36] ^ g_12101dc ^ g_12101dc;
        v136 = *(int *)(g_12101d8 + 72);
        v137 = v133->field_0[1] * 4;
        *(unsigned int *)((char *)v136 + v137) = (char *)v136 + v137 ^ &v136[v36] ^ v136[v36] ^ g_12101dc ^ g_12101dc;
    }
    v138 = v109->padding_2d0;
    if (v138 != &v37)
    {
        v139 = *(int *)(g_12101d8 + 0x44);
        v140 = v138->field_0[1] * 4;
        *(unsigned int *)((char *)v139 + v140) = (char *)v139 + v140 ^ &v139[v38] ^ v139[v38] ^ g_12101dc ^ g_12101dc;
        v141 = *(int *)(g_12101d8 + 72);
        v142 = v138->field_0[1] * 4;
        *(unsigned int *)((char *)v141 + v142) = (char *)v141 + v142 ^ &v141[v38] ^ v141[v38] ^ g_12101dc ^ g_12101dc;
    }
    if (v80)
    {
        v143 = (int)(v81 - v80) >> 3;
        if (v143)
        {
            node = &v18;
            sub_4044e0();
            sub_554010(v143);
            for (i = 0; v80 && (int)(v81 - v80) >> 3 > (unsigned int)i; i += 1)
            {
                v145 = v109->field_2ac;
                v146 = v80 + i * 8;
                if (!v145 || (int)(v109->field_2b0 - v145) >> 3 <= (unsigned int)i)
                    goto LABEL_552175;
                v147 = v145 + i * 8;
                if (v147 != v146)
                {
                    v148 = *(int *)(g_12101d8 + 0x44) + v146->field_4 * 4;
                    v149 = *(int *)(g_12101d8 + 0x44) + v147->field_4 * 4;
                    *v149 = *v148 ^ v149 ^ v148;
                    v109 = v104;
                    v150 = *(int *)(g_12101d8 + 72) + v146->field_4 * 4;
                    v151 = *(int *)(g_12101d8 + 72) + v147->field_4 * 4;
                    *v151 = *v150 ^ v151 ^ v150;
                }
            }
        }
    }
    if (v82)
    {
        v152 = (int)(v83 - v82) >> 3;
        if (v152)
        {
            node = &v17;
            sub_4044e0();
            sub_554010(v152);
            for (j = 0; v82 && (int)(v83 - v82) >> 3 > (unsigned int)j; j += 1)
            {
                v154 = v109->field_2bc;
                v155 = v82 + j * 8;
                if (!v154 || (int)(v109->field_2c0 - v154) >> 3 <= (unsigned int)j)
                    goto LABEL_552175;
                v156 = v154 + j * 8;
                if (v156 != v155)
                {
                    v157 = *(int *)(g_12101d8 + 0x44) + v155->field_4 * 4;
                    v158 = *(int *)(g_12101d8 + 0x44) + v156->field_4 * 4;
                    *v158 = *v157 ^ v158 ^ v157;
                    v109 = v104;
                    v159 = *(int *)(g_12101d8 + 72) + v155->field_4 * 4;
                    v160 = *(int *)(g_12101d8 + 72) + v156->field_4 * 4;
                    *v160 = *v159 ^ v160 ^ v159;
                }
            }
        }
    }
    if (v39)
    {
        v161 = (int)(v40 - v39) >> 3;
        if (v161)
        {
            node = &v16;
            sub_4044e0();
            sub_554010(v161);
            for (k = 0; v39 && (int)(v40 - v39) >> 3 > (unsigned int)k; k += 1)
            {
                v163 = v109->field_4c;
                v164 = v39 + k * 8;
                if (!v163 || (int)(v109->field_50 - v163) >> 3 <= (unsigned int)k)
                    goto LABEL_552175;
                v165 = v163 + k * 8;
                if (v165 != v164)
                {
                    v166 = *(int *)(g_12101d8 + 0x44) + v164->field_4 * 4;
                    v167 = *(int *)(g_12101d8 + 0x44) + v165->field_4 * 4;
                    *v167 = *v166 ^ v167 ^ v166;
                    v109 = v104;
                    v168 = *(int *)(g_12101d8 + 72) + v164->field_4 * 4;
                    v169 = *(int *)(g_12101d8 + 72) + v165->field_4 * 4;
                    *v169 = *v168 ^ v169 ^ v168;
                }
            }
        }
    }
    if (v41 && (v170 = (int)(v42 - v41) >> 3, v170))
    {
        node = &v15;
        sub_4044e0();
        sub_554010(v170);
        v171 = 0;
        while (1)
        {
            if (v41 && (int)(v42 - v41) >> 3 > (unsigned int)v171)
                goto LABEL_552111;
            else
                goto LABEL_55217c;
LABEL_552111:
            v172 = v109->field_5c;
            v173 = v41 + v171 * 8;
            if (!v172 || (int)(v109->field_60 - v172) >> 3 <= (unsigned int)v171)
                break;
            v174 = v172 + v171 * 8;
            if (v174 != v173)
            {
                v175 = *(int *)(g_12101d8 + 0x44) + v173->field_4 * 4;
                v176 = *(int *)(g_12101d8 + 0x44) + v174->field_4 * 4;
                *v176 = v176 ^ v175 ^ *v175;
                v177 = *(int *)(g_12101d8 + 72);
                v109 = v104;
                v178 = &v177[v174->field_4];
                *v178 = v178 ^ &v177[v173->field_4] ^ v177[v173->field_4];
            }
            v171 += 1;
        }
LABEL_552175:
        sub_46a300();
    }
LABEL_55217c:
    v179 = &v109->padding_64[4];
    if (v179 != &v43)
    {
        v180 = *(int *)(g_12101d8 + 0x44);
        v181 = v179->field_0[1] * 4;
        *(unsigned int *)(v181 + v180) = v181 + v180 ^ g_12101dc ^ &v180[v44] ^ v180[v44] ^ g_12101dc;
        v182 = *(int *)(g_12101d8 + 72);
        v183 = v109->field_6c * 4;
        *(unsigned int *)(v183 + v182) = v183 + v182 ^ g_12101dc ^ &v182[v44] ^ v182[v44] ^ g_12101dc;
    }
    v184 = v109->padding_70;
    if (v184 != &v45)
    {
        v185 = *(int *)(g_12101d8 + 0x44);
        v186 = v184->field_0[1] * 4;
        *(unsigned int *)(v186 + v185) = v186 + v185 ^ g_12101dc ^ &v185[v46] ^ v185[v46] ^ g_12101dc;
        v187 = *(int *)(g_12101d8 + 72);
        v188 = v109->field_74 * 4;
        *(unsigned int *)(v188 + v187) = v188 + v187 ^ &v187[v46] ^ v187[v46] ^ g_12101dc ^ g_12101dc;
    }
    a4 = &v48 + 16;
    v92 = &v24 - v109;
    v189 = &v47;
    v190 = v109->padding_a4;
    i1 = &v109->field_11c;
    v191 = g_12101d8;
    v97 = &v23 - v109;
    v192 = g_12101dc;
    iter = &v47;
    *(st_551ad0_0 **)((char *)&v91 + 4) = v190;
    l = 5;
    do
    {
        v95 = l;
        if ((char *)v190 - 44 != (char *)v189 - 4)
        {
            v193 = *(int *)(v191 + 0x44);
            v194 = v189->field_0[0] * 4;
            v195 = *(int *)((char *)v190 - 40) * 4;
            *(unsigned int *)(v195 + v193) = v195 + v193 ^ v194 + v193 ^ *(int *)(v194 + v193) ^ v192 ^ v192;
            v196 = *(int *)(g_12101d8 + 72);
            v197 = iter->field_0[0] * 4;
            v198 = *(int *)((char *)v190 - 40) * 4;
            *(unsigned int *)(v198 + v196) = v198 + v196 ^ v197 + v196 ^ *(int *)(v197 + v196) ^ g_12101dc ^ g_12101dc;
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        if ((char *)v190 - 4 != v97 + v190)
        {
            v199 = *(int *)(v191 + 0x44);
            v200 = *(int *)(v92 + v190) * 4;
            v201 = v190->field_0[0] * 4;
            *(unsigned int *)((char *)v199 + v201) = (char *)v199 + v201 ^ v200 + v199 ^ *(int *)(v200 + v199) ^ v192 ^ v192;
            v202 = *(int *)(g_12101d8 + 72);
            v203 = *(int *)(v92 + v190) * 4;
            v204 = v190->field_0[0] * 4;
            *(unsigned int *)((char *)v202 + v204) = (char *)v202 + v204 ^ v203 + v202 ^ *(int *)(v203 + v202) ^ g_12101dc ^ g_12101dc;
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        if ((*(int *)((char *)v190 - 4) ^ v192) - (char *)v190 + 4 != v190->field_0[0])
        {
            sub_b170b0((char *)v190 - 4, 63);
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        v205 = v190->field_0[0] * 4;
        v98 = *(int *)(v191 + 0x44) + v205 ^ *(int *)(*(int *)(v191 + 0x44) + v205) ^ v192;
        if (v98 != (*(int *)(v191 + 72) + v205 ^ *(int *)(*(int *)(v191 + 72) + v205) ^ v192))
        {
            sub_b170b0((char *)v190 - 4, 64);
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        v206 = v104;
        v207 = &v206->field_178;
        node = v207;
        if ((v206->field_178 ^ v192) - (char *)v207 != v206->field_17c)
        {
            sub_b170b0(node, 63);
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        v208 = node->field_0[1] * 4;
        v102 = (char *)v208 + *(int *)(v191 + 0x44) ^ *(int *)((char *)v208 + *(int *)(v191 + 0x44)) ^ v192;
        if (v102 != ((char *)v208 + *(int *)(v191 + 72) ^ *(int *)((char *)v208 + *(int *)(v191 + 72)) ^ v192))
        {
            sub_b170b0(node, 64);
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        if (v98 > v102 && node != (char *)v190 - 4)
        {
            v209 = *(int *)(v191 + 0x44);
            v210 = v190->field_0[0] * 4;
            v211 = node->field_0[1] * 4;
            *(unsigned int *)(v211 + v209) = v211 + v209 ^ (char *)v209 + v210 ^ *(int *)((char *)v209 + v210) ^ v192 ^ v192;
            v212 = *(int *)(g_12101d8 + 72);
            v213 = v190->field_0[0] * 4;
            v214 = node->field_0[1] * 4;
            *(unsigned int *)(v214 + v212) = v214 + v212 ^ (char *)v212 + v213 ^ *(int *)((char *)v212 + v213) ^ g_12101dc ^ g_12101dc;
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        v215 = a4;
        iter1 = i1;
        node = v215;
        i1 = 2;
        do
        {
            v100 = i1;
            if ((char *)iter1 - 84 != (char *)v215 - 20)
            {
                v217 = *(int *)(v191 + 0x44);
                v218 = *(int *)((char *)v215 - 16) * 4;
                v219 = *(int *)((char *)iter1 - 80) * 4;
                *(unsigned int *)(v219 + v217) = v219 + v217 ^ v218 + v217 ^ *(int *)(v218 + v217) ^ v192 ^ v192;
                v220 = *(int *)(g_12101d8 + 72);
                v215 = node;
                v221 = *(int *)((char *)v215 - 16) * 4;
                v222 = *(int *)((char *)iter1 - 80) * 4;
                *(unsigned int *)(v222 + v220) = v222 + v220 ^ v221 + v220 ^ *(int *)(v221 + v220) ^ g_12101dc ^ g_12101dc;
                v192 = g_12101dc;
                v191 = g_12101d8;
            }
            if ((char *)iter1 - 4 != (char *)v215 - 4)
            {
                v223 = *(int *)(v191 + 0x44);
                v224 = v215->field_0[0] * 4;
                v225 = iter1->field_0[0] * 4;
                *(unsigned int *)(v225 + v223) = v225 + v223 ^ v224 + v223 ^ *(int *)(v224 + v223) ^ v192 ^ v192;
                v226 = *(int *)(g_12101d8 + 72);
                v227 = node->field_0[0] * 4;
                v228 = iter1->field_0[0] * 4;
                *(unsigned int *)(v228 + v226) = v228 + v226 ^ v227 + v226 ^ *(int *)(v227 + v226) ^ g_12101dc ^ g_12101dc;
                v192 = g_12101dc;
                v191 = g_12101d8;
            }
            if ((*(int *)((char *)iter1 - 4) ^ v192) - (char *)iter1 + 4 != iter1->field_0[0])
            {
                sub_b170b0((char *)iter1 - 4, 63);
                v192 = g_12101dc;
                v191 = g_12101d8;
            }
            v229 = iter1->field_0[0] * 4;
            v98 = (char *)v229 + *(int *)(v191 + 0x44) ^ *(int *)((char *)v229 + *(int *)(v191 + 0x44)) ^ v192;
            if (v98 != ((char *)v229 + *(int *)(v191 + 72) ^ *(int *)((char *)v229 + *(int *)(v191 + 72)) ^ v192))
            {
                sub_b170b0((char *)iter1 - 4, 64);
                v192 = g_12101dc;
                v191 = g_12101d8;
            }
            v230 = v104;
            v231 = &v230->field_178;
            if ((v230->field_178 ^ v192) - (char *)v231 != v230->field_17c)
            {
                sub_b170b0(v231, 63);
                v192 = g_12101dc;
                v191 = g_12101d8;
            }
            v232 = v231->field_0[1] * 4;
            v102 = (char *)v232 + *(int *)(v191 + 0x44) ^ *(int *)((char *)v232 + *(int *)(v191 + 0x44)) ^ v192;
            if (v102 != ((char *)v232 + *(int *)(v191 + 72) ^ *(int *)((char *)v232 + *(int *)(v191 + 72)) ^ v192))
            {
                sub_b170b0(&v104->field_178, 64);
                v192 = g_12101dc;
                v191 = g_12101d8;
            }
            if (v98 > v102)
            {
                v233 = &v104->field_178;
                if (v233 != (char *)iter1 - 4)
                {
                    v234 = *(int *)(v191 + 0x44);
                    v235 = iter1->field_0[0] * 4;
                    v236 = v233->field_0[1] * 4;
                    *(unsigned int *)(v236 + v234) = v236 + v234 ^ v235 + v234 ^ *(int *)(v235 + v234) ^ v192 ^ v192;
                    v237 = *(int *)(g_12101d8 + 72);
                    v238 = iter1->field_0[0] * 4;
                    v239 = v104->field_17c * 4;
                    *(unsigned int *)(v239 + v237) = v239 + v237 ^ v238 + v237 ^ *(int *)(v238 + v237) ^ g_12101dc ^ g_12101dc;
                    v192 = g_12101dc;
                    v191 = g_12101d8;
                }
            }
            v215 = &node->field_0[2];
            iter1 = &iter1->field_0[2];
            node = v215;
            i1 = v100 - 1;
        } while (i1);
        i1 = iter1;
        v189 = &iter->field_0[2];
        v190 = *(unsigned int *)((void*)&v91 + 4) + 8;
        iter = v189;
        *(st_551ad0_0 **)((char *)&v91 + 4) = v190;
        a4 = &a4->field_20;
        l = v95 - 1;
    } while (l);
    node = 0;
    while (1)
    {
        v240 = v104;
        v241 = &v240->field_20;
        if ((v240->field_20 ^ v192) - (char *)v241 != v240->field_24)
        {
            sub_b170b0(v241, 63);
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        v242 = v241->field_0[1] * 4;
        iter = (char *)v242 + *(int *)(v191 + 0x44) ^ *(int *)((char *)v242 + *(int *)(v191 + 0x44)) ^ v192;
        if (iter != ((char *)v242 + *(int *)(v191 + 72) ^ *(int *)((char *)v242 + *(int *)(v191 + 72)) ^ v192))
        {
            sub_b170b0(v241, 64);
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        v102 = node + 1;
        if (v102 > iter)
            break;
        if ((v241->field_0[0] ^ v192) - (char *)v241 != v241->field_0[1])
        {
            sub_b170b0(v241, 63);
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        v243 = v241->field_0[1] * 4;
        iter = (char *)v243 + *(int *)(v191 + 0x44) ^ *(int *)((char *)v243 + *(int *)(v191 + 0x44)) ^ v192;
        if (iter != ((char *)v243 + *(int *)(v191 + 72) ^ *(int *)((char *)v243 + *(int *)(v191 + 72)) ^ v192))
        {
            sub_b170b0(v241, 64);
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        idx = v54;
        if ((v53 ^ v192) - (char *)&v53 != idx)
        {
            sub_b170b0(&v53, 63);
            idx = v54;
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        a4 = *(int *)(v191 + 0x44) + idx * 4 ^ *(int *)(*(int *)(v191 + 0x44) + idx * 4) ^ v192;
        if (a4 != (*(int *)(v191 + 72) + idx * 4 ^ *(int *)(*(int *)(v191 + 72) + idx * 4) ^ v192))
        {
            sub_b170b0(&v53, 64);
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        idx1 = v52;
        if ((v51 ^ v192) - (char *)&v51 != idx1)
        {
            sub_b170b0(&v51, 63);
            idx1 = v52;
            v192 = g_12101dc;
            v191 = g_12101d8;
        }
        v246 = *(int *)(v191 + 0x44) + idx1 * 4 ^ *(int *)(*(int *)(v191 + 0x44) + idx1 * 4) ^ v192;
        if (v246 != (*(int *)(v191 + 72) + idx1 * 4 ^ *(int *)(*(int *)(v191 + 72) + idx1 * 4) ^ v192))
            sub_b170b0(&v51, 64);
        func_00b099b0(v246, a4, node, iter - 1);
        iter = sub_c01544();
        v12 = &iter;
        sub_402150(v12);
        v247 = v104->field_184;
        v248 = v104->padding_180;
        v107 = 1;
        if (v247 && (!v247 ? 0 : (int)(v248->field_0[2] - v247) >> 3) < (int)(v248->field_0[3] - v247) >> 3)
        {
            sub_4692f0(v248->field_0[2], 1, &v96, v248, node);
            v248->field_0[2] = v248->field_0[2] + 8;
        }
        else
        {
            sub_46a6d0(v248->field_0[2], 1, &v96);
        }
        v10 = &v96;
        v107 = 2;
        sub_b173a0(v10);
        v107 = 0;
        sub_b17a80(v10);
        v249 = g_12101dc;
        idx2 = v56;
        if ((v55 ^ g_12101dc) - (char *)&v55 != idx2)
        {
            sub_b170b0(&v55, 63);
            idx2 = v56;
            v249 = g_12101dc;
        }
        index = g_12101d8;
        v252 = __int_as_float(*(int *)(g_12101d8 + 0x44) + idx2 * 4 ^ *(int *)(*(int *)(g_12101d8 + 0x44) + idx2 * 4) ^ v249);
        if (__float_as_int(v252) != (*(int *)(g_12101d8 + 72) + idx2 * 4 ^ *(int *)(*(int *)(g_12101d8 + 72) + idx2 * 4) ^ v249))
        {
            sub_b170b0(&v55, 64);
            idx2 = v56;
            v249 = g_12101dc;
            index = g_12101d8;
        }
        iter = v252;
        if ((v55 ^ v249) - (char *)&v55 != idx2)
        {
            sub_b170b0(&v55, 63);
            idx2 = v56;
            v249 = g_12101dc;
            index = g_12101d8;
        }
        v253 = __int_as_float(*(int *)(index + 0x44) + idx2 * 4 ^ *(int *)(*(int *)(index + 0x44) + idx2 * 4) ^ v249);
        if (__float_as_int(v253) != (*(int *)(index + 72) + idx2 * 4 ^ *(int *)(*(int *)(index + 72) + idx2 * 4) ^ v249))
        {
            sub_b170b0(&v55, 64);
            v249 = g_12101dc;
            index = g_12101d8;
        }
        a4 = v253;
        v254 = fabs(iter);
        if (fabs(a4) * g_cab8e8 >= v254)
        {
            v255 = v58;
            if ((v57 ^ v249) - (char *)&v57 != v255)
            {
                v5 = &v57;
                sub_b170b0(v5, 63);
                v255 = v58;
                v249 = g_12101dc;
                index = g_12101d8;
            }
            v256 = __int_as_float(*(int *)(index + 0x44) + v255 * 4 ^ *(int *)(*(int *)(index + 0x44) + v255 * 4) ^ v249);
            if (__float_as_int(v256) != (*(int *)(index + 72) + v255 * 4 ^ *(int *)(*(int *)(index + 72) + v255 * 4) ^ v249))
                sub_b170b0(&v57, 64);
            iter = v256;
            v91 = fabs(iter);
            sub_4333b0();
            v254 = fabs(v91) * g_cab8e8;
            if (v254 >= v91)
                goto LABEL_552b68;
        }
        sub_4333b0(node, sub_402060() - 1);
        v1 = v258;
        sub_4333b0((float)v254);
        v0 = v258;
        func_00b099b0((float)v254);
        node = (float)v254;
        v3 = &node;
        sub_44d010(v3);
        v2 = &v93;
        v107 = 3;
        sub_4515e0(v2);
        v107 = 0;
        sub_402010(v2);
LABEL_552b68:
        v192 = g_12101dc;
        node = v102;
        v191 = g_12101d8;
    }
    m = 1;
    if ((int)sub_402060() >= 1)
    {
        do
        {
            v260 = sub_402060();
            node = sub_402060();
            iter = sub_402060();
            func_00b099b0((float)iter, (float)node, m - 1, v260 - 1);
            node = sub_c01544();
            sub_402150(&node);
            v14 = &v101;
            v107 = 4;
            sub_46d0b0(v14);
            v107 = 0;
            sub_402010(v14);
            m += 1;
        } while (m <= (int)sub_402060());
    }
    sub_4045b0(&v59);
    sub_554190(&v60);
    sub_46ba10(&v61);
    sub_4045b0(&v62);
    v13 = &v88;
    sub_4045b0(v13);
    n = 1;
    if ((int)sub_402060(v13) >= 1)
    {
        do
        {
            v262 = sub_402060();
            v108 = sub_402060();
            iter = sub_402060();
            func_00b099b0((float)iter, (float)(int)v108, n - 1, v262 - 1);
            node = sub_c01544();
            sub_402150(&node);
            v12 = &v101;
            v107 = 5;
            sub_46d0b0(v12);
            v107 = 0;
            sub_402010(v12);
            sub_402150(&node);
            v11 = &v96;
            v107 = 6;
            sub_46d0b0(v11);
            v107 = 0;
            sub_402010(v11);
            n += 1;
        } while (n <= (int)sub_402060());
    }
    if (v63)
    {
        v263 = (int)(v64 - v63) >> 3;
        if (v263)
        {
            node = &v12;
            sub_4044e0();
            v264 = &v104->padding_190[112];
            sub_554010(v263);
            for (i0 = 0; v63 && (int)(v64 - v63) >> 3 > (unsigned int)i0; i0 += 1)
            {
                if (v264->field_0[1] && (int)(v264->field_0[2] - v264->field_0[1]) >> 3 > (unsigned int)i0)
                {
                    sub_4045b0(v63 + i0 * 8);
                }
                else
                {
LABEL_553267:
                    sub_46a300();
                    if (v67)
                    {
                        v266 = (int)(v68 - v67) >> 4;
                        if (v266)
                        {
                            node = &v5;
                            v6 = 0;
                            v7 = 0;
                            v8 = 0;
                            sub_556b70(v266);
                            v267 = v67;
                            i2 = 0;
                            node = 0;
                            for (iter = 0; v267 && (v269 = (int)(v68 - v267) >> 4, (unsigned int)v269 > (unsigned int)i2); i2 = node)
                            {
                                if (*(int *)(v267 + iter + 4) && *(int *)(v267 + iter + 8) - *(int *)(v267 + iter + 4) >> 3)
                                {
                                    v270 = node;
                                    if ((unsigned int)v269 <= (unsigned int)v270)
                                    {
LABEL_55342d:
                                        sub_553fa0(); /* do not return */
                                    }
                                    if (v104->field_240 && (int)(v104->field_244 - v104->field_240) >> 4 > (unsigned int)v270)
                                    {
                                        a4 = &v3;
                                        sub_4044e0();
                                        sub_554010((!*(int *)(v267 + iter + 4) ? 0 : *(int *)(v267 + iter + 8) - *(int *)(v267 + iter + 4) >> 3));
                                        v271 = 0;
                                        while (1)
                                        {
                                            v267 = v67;
                                            if (!v267 || !(v272 = (int)(v68 - v267) >> 4, (unsigned int)v272 > (unsigned int)v270))
                                                goto LABEL_55342d;
                                            v273 = iter + v267;
                                            if (!*(int *)(iter + v267 + 4) || (unsigned int)v271 >= (int)(v273[2] - *(int *)(iter + v267 + 4)) >> 3)
                                                goto LABEL_553416;
                                            v270 = node;
                                            if ((unsigned int)v272 <= (unsigned int)v270)
                                                goto LABEL_55342d;
                                            v274 = v273[1];
                                            if (!v274 || (int)(v273[2] - v274) >> 3 <= (unsigned int)v271)
                                                goto LABEL_553267;
                                            v275 = v104->field_240;
                                            if (!v275 || (int)(v104->field_244 - v275) >> 4 <= (unsigned int)v270)
                                                break;
                                            v276 = iter + v275;
                                            if (!v276[1] || (int)(v276[2] - v276[1]) >> 3 <= (unsigned int)v271)
                                                goto LABEL_553267;
                                            sub_4045b0(v274 + v271 * 8);
                                            v271 += 1;
                                        }
                                    }
                                    sub_553fa0(); /* do not return */
                                }
LABEL_553416:
                                iter += 16;
                                node += 1;
                            }
                        }
                    }
                    v277 = v104;
                    sub_4392e0(&v79);
                    sub_5569f0(&v69);
                    sub_5569f0(&v70);
                    v277->field_270 = v72;
                    v277->field_26c = v71;
                    v277->field_28c = v76;
                    v277->field_274 = v73;
                    v277->field_288 = v75;
                    v277->field_290 = v77;
                    v277->field_294 = v78;
                    sub_46ba10(&v74);
                    v7 = &v50;
                    sub_46ba10(v7);
                    i3 = 1;
                    if ((int)sub_402060(v7) >= 1)
                    {
                        do
                        {
                            v279 = sub_402060();
                            v108 = sub_402060();
                            iter = sub_402060();
                            func_00b099b0((float)iter, (float)(int)v108, i3 - 1, v279 - 1);
                            node = sub_c01544();
                            sub_402150(&node);
                            v4 = &v101;
                            v107 = 7;
                            sub_46d0b0(v4);
                            v107 = 0;
                            sub_402010(v4);
                            i3 += 1;
                        } while (i3 <= (int)sub_402060());
                    }
                    sub_4045b0(&v84);
                    v280 = &v104->field_2f0;
                    v280->field_0[0] = v85;
                    v280->field_0[1] = v86;
                    v280->field_0[2] = v87;
                    sub_4045b0(&v89);
                    v3 = &v90;
                    sub_4045b0(v3);
                    v107 = 0xffffffff;
                    sub_556520(v3);
                    NtGetCurrentTeb()->Reserved1[0] = v105;
                    return;
                }
            }
        }
    }
    sub_4045b0(&v65);
    sub_4045b0(&v66);
    node = 2;
    iter = sub_a530f0();
    v10 = sub_402060();
    v9 = iter;
    (*(int *)(*(int *)g_10030d8 + 16))();
}
