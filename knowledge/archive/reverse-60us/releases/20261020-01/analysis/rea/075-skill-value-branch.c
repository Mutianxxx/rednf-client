
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_00550150(float param_1,int param_2,undefined4 param_3,int param_4,int param_5,int param_6)

{
  float fVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  float10 fVar10;
  float10 fVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  
  uVar3 = FUN_00550080(param_1,param_2,param_3,param_4,param_5,param_6,0,0);
  cVar2 = FUN_0043abf0(0xffffffff);
  if ((((cVar2 != '\0') || (cVar2 = FUN_0043a310(), cVar2 != '\0')) &&
      (iVar4 = FUN_00402060(), 1 < iVar4)) &&
     ((iVar4 = FUN_00402060(), iVar4 != 0 && (param_4 != -1)))) {
    iVar4 = FUN_00402060();
    iVar5 = FUN_00402060();
    iVar5 = (param_4 - iVar4) / iVar5 + 1;
    iVar4 = FUN_00402060();
    if (iVar4 <= iVar5) {
      iVar5 = FUN_00402060();
    }
    uVar16 = 0;
    uVar15 = 0;
    uVar14 = 0xc;
    uVar13 = 0xffffffff;
    uVar12 = 0xffffffff;
    uVar3 = FUN_00402060(param_3,0xffffffff,0xffffffff,0xc,0,0);
    iVar4 = FUN_00550080(param_1,uVar3,param_3,uVar12,uVar13,uVar14,uVar15,uVar16);
    iVar6 = FUN_00402060();
    uVar16 = 0;
    uVar15 = 0;
    uVar14 = 0xc;
    uVar13 = 0xffffffff;
    uVar12 = 0xffffffff;
    uVar3 = 0;
    if (iVar6 == 1) {
      iVar6 = FUN_00550080(param_1,2,0,0xffffffff,0xffffffff,0xc,0,0);
      iVar7 = FUN_00550080(param_1,1,0,0xffffffff,0xffffffff,0xc,0,0);
      iVar6 = iVar6 - iVar7;
    }
    else {
      uVar8 = FUN_00402060(0,0xffffffff,0xffffffff,0xc,0,0);
      iVar6 = FUN_00550080(param_1,uVar8,uVar3,uVar12,uVar13,uVar14,uVar15,uVar16);
      iVar7 = FUN_00550080(param_1,1,0,0xffffffff,0xffffffff,0xc,0,0);
      iVar9 = FUN_00402060();
      iVar6 = (iVar6 - iVar7) / (iVar9 + -1);
    }
    iVar4 = FUN_00447ff0((float)iVar4 - (float)(iVar5 - param_2) * (float)iVar6);
    param_1 = (float)iVar4;
    if (param_6 != 0xc) {
      uVar3 = FUN_00402060();
      iVar5 = FUN_00553ba0(uVar3);
      if (param_5 < iVar5) {
        fVar10 = (float10)FUN_00448150(iVar5,param_6,0);
        fVar11 = (float10)FUN_00448150(param_5,param_6,0);
        param_1 = (float)((float10)(float)(fVar10 * (float10)iVar4) / fVar11);
      }
    }
    cVar2 = FUN_0043a310();
    fVar1 = _DAT_00f5e954;
    if (cVar2 != '\0') {
      fVar1 = _DAT_00f5e958;
    }
    uVar3 = FUN_00447ff0(fVar1 * param_1);
    return uVar3;
  }
  return uVar3;
}

