
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00a23d60(int param_1,int param_2,int param_3,char param_4,int *param_5)

{
  int *piVar1;
  int iVar2;
  int in_ECX;
  float fVar3;
  
  if ((param_5 != (int *)0x0) && (*param_5 != 0)) {
    if (param_1 == DAT_010da92c) {
      FUN_00401020(param_5[10],param_5[0xb],param_5);
      _DAT_010d3cd8 = -param_5[3];
      _DAT_010d3cd4 = -param_5[2];
      if (*(int *)(in_ECX + 0x30) == 1) {
        iVar2 = *param_5;
        _DAT_010d3cd4 = (*(uint *)(iVar2 + 0x14) >> 1) + *(int *)(iVar2 + 0x1c);
        _DAT_010d3cd8 = (*(uint *)(iVar2 + 0x18) >> 1) + *(int *)(iVar2 + 0x20);
      }
      piVar1 = param_5 + 4;
      if (param_4 == '\0') {
        fVar3 = (float)(*piVar1 - (int)piVar1 ^ DAT_010d3efc);
      }
      else {
        fVar3 = -(float)(*piVar1 - (int)piVar1 ^ DAT_010d3efc);
      }
      FUN_005383d0(param_5[2] + param_2,param_5[3] + param_3,*param_5,fVar3,
                   param_5[5] - (int)(param_5 + 5) ^ DAT_010d3efc,param_5[6],param_5[7],
                   (float)_DAT_010d3cd4,(float)_DAT_010d3cd8,param_5[0x16]);
      FUN_004010b0(param_5[10],param_5);
      return;
    }
    if (param_5[10] == 0) {
      FUN_00b0ded0(param_5[2] + param_2,param_5[3] + param_3,*param_5);
    }
  }
  return;
}

