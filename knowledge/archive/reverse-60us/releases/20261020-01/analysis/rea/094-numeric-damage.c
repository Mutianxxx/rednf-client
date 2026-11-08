
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_008b8650(float param_1,int *param_2,float param_3)

{
  float fVar1;
  int iVar2;
  char cVar3;
  undefined4 uVar4;
  float *pfVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  uint *puVar9;
  int iVar10;
  uint uVar11;
  float10 fVar12;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  undefined4 uVar13;
  undefined4 local_c;
  float local_8;
  
  uVar4 = param_3;
  iVar2 = (int)param_1;
  local_c = *(undefined4 *)((int)param_1 + 0x1b0);
  fVar12 = (float10)FUN_008b85f0(param_1,param_3);
  param_1 = (float)fVar12;
  if ((*(char *)(iVar2 + 0x1b4) != '\x04') &&
     (cVar3 = FUN_008b7970(iVar2,(int)*(char *)(iVar2 + 0x1b4)), cVar3 != '\0')) {
    param_1 = param_1 * _DAT_00e2f360;
  }
  if ((((byte)*(undefined4 *)(iVar2 + 0x199) & 0x11) == 0x11) &&
     ((((*(char *)(iVar2 + 10) != '\0' || (*(char *)(iVar2 + 0xb) != '\0')) ||
       (*(char *)(iVar2 + 0xc) != '\0')) || (*(char *)(iVar2 + 0xd) != '\0')))) {
    local_8 = -1.0;
    iVar10 = 0;
    piVar7 = (int *)(iVar2 + 0x77);
    do {
      if (*(char *)(iVar2 + 10 + iVar10) != '\0') {
        iVar8 = *piVar7;
        fVar12 = (float10)FUN_004333b0();
        fVar12 = (fVar12 - (float10)iVar8 * (float10)*(float *)(iVar2 + 0x87)) *
                 (float10)_DAT_00cc10ac * (float10)param_1;
        if ((float10)local_8 < fVar12) {
          local_8 = (float)fVar12;
        }
      }
      iVar10 = iVar10 + 1;
      piVar7 = piVar7 + 1;
    } while (iVar10 < 4);
    param_1 = local_8;
    uVar4 = param_3;
  }
  cVar3 = *(char *)(iVar2 + 5);
  param_3 = 0.0;
  if (cVar3 == '\0') {
    fVar12 = (float10)FUN_004333b0();
    param_3 = (float)fVar12;
    iVar10 = FUN_008b7bf0(iVar2,*(char *)(iVar2 + 4) != '\0');
    fVar12 = (float10)FUN_004333b0();
    fVar12 = fVar12 * (float10)iVar10 + (float10)param_3;
LAB_008b87a7:
    param_3 = (float)fVar12;
  }
  else {
    if (cVar3 == '\x01') {
      FUN_004333b0();
      param_3 = (float)extraout_ST0;
      iVar10 = FUN_008b7bf0(iVar2,*(char *)(iVar2 + 4) != '\0');
      fVar12 = (float10)FUN_004333b0();
      fVar12 = fVar12 * (float10)iVar10 + (float10)param_3;
      goto LAB_008b87a7;
    }
    if (cVar3 == '\x02') {
      fVar12 = (float10)param_1 * (float10)_DAT_00e2f35c;
      goto LAB_008b87a7;
    }
  }
  iVar10 = FUN_00402060();
  if (iVar10 != 0) {
    param_3 = 0.0;
  }
  iVar10 = FUN_008ae160(&local_c,999);
  fVar12 = (float10)FUN_008adcb0(-param_3,param_3,iVar10 % 1000);
  piVar7 = param_2;
  param_1 = (float)(fVar12 + (float10)param_1);
  if (((((byte)*(undefined4 *)(iVar2 + 0x199) & 0x11) == 0x11) && (*(char *)(iVar2 + 5) != '\x02'))
     && (*(char *)(iVar2 + 0xe) == '\0')) {
    param_3 = 0.0;
    local_8 = 0.0;
    FUN_008b7c90(&param_3,&local_8,iVar2,param_2);
    param_1 = ((_DAT_00cc1f58 - param_3) - local_8 * *(float *)(iVar2 + 0x5f)) * param_1;
    if (*(char *)(iVar2 + 5) == '\0') {
      param_3 = *(float *)(iVar2 + 0xa3);
      if (*(char *)(iVar2 + 0x18a) != '\x04') {
        fVar12 = (float10)FUN_00448c10(piVar7,4);
        param_3 = (float)(fVar12 * (float10)param_3);
      }
    }
    else {
      if (*(char *)(iVar2 + 5) != '\x01') goto LAB_008b88bf;
      param_3 = *(float *)(iVar2 + 0xa7);
      if (*(char *)(iVar2 + 0x18a) != '\x04') {
        fVar12 = (float10)FUN_00448c10(piVar7,6);
        param_3 = (float)(fVar12 * (float10)param_3);
      }
    }
    fVar12 = (float10)FUN_004333b0();
    param_1 = (float)((float10)param_1 - (float10)param_3 / fVar12);
  }
LAB_008b88bf:
  if (*(char *)(iVar2 + 5) == '\0') {
    param_3 = *(float *)(iVar2 + 0x3f);
    if (*(char *)(iVar2 + 0x18a) != '\x04') {
      fVar12 = (float10)FUN_00448c10(uVar4,3);
      param_3 = (float)(fVar12 * (float10)param_3);
    }
LAB_008b892c:
    fVar12 = (float10)FUN_004333b0();
    param_1 = (float)((float10)param_3 / fVar12 + (float10)param_1);
  }
  else if (*(char *)(iVar2 + 5) == '\x01') {
    param_3 = *(float *)(iVar2 + 0x43);
    if (*(char *)(iVar2 + 0x18a) != '\x04') {
      fVar12 = (float10)FUN_00448c10(uVar4,5);
      param_3 = (float)(fVar12 * (float10)param_3);
    }
    if ((*(char *)(iVar2 + 0x1c1) == '\0') || (*(int *)(iVar2 + 0x1c2) != 0xb3b2))
    goto LAB_008b892c;
  }
  if (*(char *)(iVar2 + 5) == '\0') {
    fVar1 = *(float *)(iVar2 + 0xf);
    if (*(char *)(iVar2 + 4) != '\0') {
      fVar1 = (float)*(int *)(iVar2 + 99) * *(float *)(iVar2 + 0xab) + fVar1;
    }
    param_3 = (*(float *)(iVar2 + 0x37) * _DAT_00cc10ac + _DAT_00cc1f58) *
              (*(float *)(iVar2 + 6) * _DAT_00cc10ac + _DAT_00cc1f58) * fVar1;
    fVar12 = (float10)FUN_00448c10(uVar4,7);
    param_1 = (float)(fVar12 * (float10)param_3 + (float10)param_1);
    if ((((byte)*(undefined4 *)(iVar2 + 0x199) & 0x11) == 0x11) && (*(char *)(iVar2 + 0xe) == '\0'))
    {
      uVar13 = 8;
      param_3 = (float)*(int *)(iVar2 + 0xaf) * *(float *)(iVar2 + 0x5f) +
                (float)*(int *)(iVar2 + 0xb7);
LAB_008b8a42:
      fVar12 = (float10)FUN_00448c10(piVar7,uVar13);
      param_1 = (float)((float10)param_1 - fVar12 * (float10)param_3);
    }
  }
  else {
    if (*(char *)(iVar2 + 5) != '\x01') goto LAB_008b8a62;
    fVar1 = *(float *)(iVar2 + 0xf);
    if (*(char *)(iVar2 + 4) != '\0') {
      fVar1 = (float)*(int *)(iVar2 + 0x67) * *(float *)(iVar2 + 0xab) + fVar1;
    }
    param_3 = (*(float *)(iVar2 + 0x3b) * _DAT_00cc10ac + _DAT_00cc1f58) *
              (*(float *)(iVar2 + 6) * _DAT_00cc10ac + _DAT_00cc1f58) * fVar1;
    fVar12 = (float10)FUN_00448c10(uVar4,9);
    param_1 = (float)(fVar12 * (float10)param_3 + (float10)param_1);
    if ((((byte)*(undefined4 *)(iVar2 + 0x199) & 0x11) == 0x11) && (*(char *)(iVar2 + 0xe) == '\0'))
    {
      uVar13 = 10;
      param_3 = (float)*(int *)(iVar2 + 0xb3) * *(float *)(iVar2 + 0x5f) +
                (float)*(int *)(iVar2 + 0xbb);
      goto LAB_008b8a42;
    }
  }
  (**(code **)(*piVar7 + 800))(uVar4);
LAB_008b8a62:
  if (param_1 < _DAT_00e9d7a4) {
    param_1 = 0.0;
  }
  cVar3 = FUN_008b7ab0(iVar2,&param_1,&local_c);
  fVar12 = (float10)param_1;
  *(char *)(iVar2 + 0x1a5) = cVar3;
  if (*(char *)(iVar2 + 0x1a6) != '\0') {
    uVar4 = FUN_00c01544();
    *(undefined4 *)(iVar2 + 0x1a7) = uVar4;
    fVar12 = extraout_ST0_00;
  }
  iVar10 = DAT_01002848;
  fVar12 = fVar12 * (float10)*(float *)(iVar2 + 0x1b) * (float10)_DAT_00cc10ac *
           (float10)*(int *)(iVar2 + 0x1ac) * (float10)_DAT_00cc10ac;
  if (*(char *)(iVar2 + 0xc3) != '\0') {
    fVar12 = fVar12 * (float10)*(float *)(iVar2 + 0x1f) * (float10)_DAT_00cc10ac;
  }
  if (*(char *)(iVar2 + 0xc4) != '\0') {
    fVar12 = fVar12 * (float10)*(float *)(iVar2 + 0x23) * (float10)_DAT_00cc10ac;
  }
  if (*(char *)(iVar2 + 0xc5) != '\0') {
    fVar12 = fVar12 * (float10)*(float *)(iVar2 + 0x27) * (float10)_DAT_00cc10ac;
  }
  if ((*(uint *)(iVar2 + 0x195) & 0x111) == 0x111) {
    fVar12 = fVar12 * (float10)*(float *)(iVar2 + 0x6b);
  }
  param_1 = (float)fVar12;
  if (fVar12 < (float10)_DAT_00cc1f58) {
    fVar12 = (float10)_DAT_00cc1f58;
    param_1 = _DAT_00cc1f58;
  }
  if ((*(uint *)(iVar2 + 0x19d) & 0x111) == 0x111) {
    iVar8 = 2;
    pfVar5 = (float *)((uint)(cVar3 != '\0') * 0x5c + 0xca + iVar2);
    do {
      iVar8 = iVar8 + -1;
      fVar12 = fVar12 * (float10)pfVar5[-1] * (float10)*pfVar5 * (float10)pfVar5[1] *
               (float10)pfVar5[2] * (float10)pfVar5[3] * (float10)pfVar5[4] * (float10)pfVar5[5] *
               (float10)pfVar5[6];
      pfVar5 = pfVar5 + 8;
    } while (iVar8 != 0);
    pfVar5 = (float *)((uint)(*(char *)(iVar2 + 0x1a5) != '\0') * 0x5c + 0x106 + iVar2);
    iVar8 = 7;
    do {
      fVar12 = fVar12 * (float10)*pfVar5;
      pfVar5 = pfVar5 + 1;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    param_1 = (float)fVar12;
  }
  if ((((byte)*(uint *)(iVar2 + 0x195) & 0x11) == 0x11) && (*(int *)(iVar2 + 0x73) != 0x3f800000)) {
    param_1 = (float)(fVar12 * (float10)*(float *)(iVar2 + 0x73));
  }
  iVar8 = DAT_01002848 + 0x1040;
  if ((*(uint *)(DAT_01002848 + 0x1040) ^ DAT_012101dc) - iVar8 != *(int *)(DAT_01002848 + 0x1044))
  {
    FUN_00b170b0(iVar8,0x3f);
  }
  iVar10 = *(int *)(iVar10 + 0x1044) * 4;
  puVar9 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar10);
  uVar11 = (uint)puVar9 ^ DAT_012101dc ^ *puVar9;
  puVar9 = (uint *)(iVar10 + *(int *)(DAT_012101d8 + 0x48));
  if (uVar11 != ((uint)puVar9 ^ DAT_012101dc ^ *puVar9)) {
    FUN_00b170b0(iVar8,0x40);
  }
  piVar7 = param_2;
  if ((uVar11 == 4) && (cVar3 = (**(code **)(*param_2 + 0x2c))(0x11), cVar3 != '\0')) {
    piVar6 = (int *)FUN_00c00d0b(piVar7,0,&PTR_PTR_00f4287c,&PTR_PTR_00f5526c,0);
    if ((piVar6 != (int *)0x0) &&
       ((iVar10 = (**(code **)(*piVar6 + 0x230))(), iVar10 == 4 &&
        (iVar10 = (**(code **)(*piVar6 + 0x9c))(), 0 < iVar10)))) {
      fVar12 = (float10)FUN_004333b0();
      param_1 = (float)(((float10)_DAT_00cc1f58 - fVar12) * (float10)param_1);
    }
    cVar3 = (**(code **)(*piVar7 + 0x2c))(0x111);
    if (cVar3 != '\0') {
      piVar7 = (int *)FUN_00c00d0b(piVar7,0,&PTR_PTR_00f4287c,&PTR_PTR_00f5528c,0);
      iVar10 = (**(code **)(*piVar7 + 0x234))();
      iVar8 = (**(code **)(*piVar7 + 0x238))();
      param_3 = (float)((iVar10 * 100) / iVar8);
      fVar12 = (float10)FUN_004333b0();
      if ((fVar12 < (float10)param_3) ||
         (fVar12 = (float10)FUN_004333b0(), (float10)param_3 <= fVar12)) {
        fVar12 = (float10)FUN_004333b0();
        if ((fVar12 < (float10)param_3) ||
           (fVar12 = (float10)FUN_004333b0(), (float10)param_3 <= fVar12)) {
          fVar12 = (float10)FUN_004333b0();
          if ((fVar12 < (float10)param_3) ||
             (fVar12 = (float10)FUN_004333b0(), (float10)param_3 <= fVar12)) {
            fVar12 = (float10)FUN_004333b0();
            if ((fVar12 < (float10)param_3) ||
               (fVar12 = (float10)FUN_004333b0(), (float10)param_3 <= fVar12)) {
              fVar12 = (float10)FUN_004333b0();
              if (((float10)param_3 <= fVar12) && (_DAT_00e9d7a4 < param_3)) {
                FUN_004333b0();
              }
            }
            else {
              FUN_004333b0();
            }
          }
          else {
            FUN_004333b0();
          }
        }
        else {
          FUN_004333b0();
        }
      }
      else {
        FUN_004333b0();
      }
    }
  }
  if ((*(char *)(iVar2 + 0x1b6) != '\0') && ((*(uint *)(iVar2 + 0x195) & 0x111) == 0x111)) {
    param_3 = (float)FUN_00c01544();
  }
  uVar4 = FUN_00c01544();
  *(undefined4 *)(iVar2 + 0x1bd) = uVar4;
  return;
}

