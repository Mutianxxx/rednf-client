
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00a23e90(undefined4 param_1,int param_2,int param_3,char param_4,int *param_5,int param_6,
                 char param_7,undefined4 param_8,undefined4 param_9,float param_10)

{
  int *piVar1;
  int iVar2;
  int in_ECX;
  float fVar3;
  
  if ((param_5 != (int *)0x0) && (*param_5 != 0)) {
    if (param_6 == 6) {
      param_6 = param_5[10];
    }
    if (param_6 != 0) {
      FUN_00401020(param_6,0,0);
    }
    if (param_7 != '\0') {
      FUN_00b084d0(1,param_8);
    }
    _DAT_010d3ce0 = -param_5[3];
    _DAT_010d3cdc = -param_5[2];
    if (*(int *)(in_ECX + 0x30) == 1) {
      iVar2 = *param_5;
      _DAT_010d3cdc = (*(uint *)(iVar2 + 0x14) >> 1) + *(int *)(iVar2 + 0x1c);
      _DAT_010d3ce0 = (*(uint *)(iVar2 + 0x18) >> 1) + *(int *)(iVar2 + 0x20);
    }
    piVar1 = param_5 + 4;
    if (param_4 == '\0') {
      fVar3 = (float)(*piVar1 - (int)piVar1 ^ DAT_010d3efc);
    }
    else {
      fVar3 = -(float)(*piVar1 - (int)piVar1 ^ DAT_010d3efc);
    }
    FUN_005383d0(param_5[2] + param_2,param_5[3] + param_3,*param_5,fVar3,
                 param_5[5] - (int)(param_5 + 5) ^ DAT_010d3efc,param_10 + (float)param_5[6],param_9
                 ,(float)_DAT_010d3cdc,(float)_DAT_010d3ce0,param_5[0x16]);
    if (param_6 != 0) {
      FUN_004010b0(param_6,param_5);
    }
    if (param_7 != '\0') {
      FUN_00b084d0(0,0);
    }
  }
  return;
}

