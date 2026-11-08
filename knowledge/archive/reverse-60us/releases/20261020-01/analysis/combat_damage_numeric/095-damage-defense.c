
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_008b7c90(float *param_1,float *param_2,float param_3,undefined4 param_4)

{
  char *pcVar1;
  float fVar2;
  char cVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar5 = (int)param_3;
  cVar3 = *(char *)((int)param_3 + 0x18a);
  if (cVar3 == '\x04') {
    iVar6 = 0x32;
  }
  else if (cVar3 == '\x06') {
    iVar6 = (int)*(short *)(DAT_010da440 + 2 +
                           *(int *)(*(int *)(DAT_01002848 + 0x1060) + 0x74) * 0x14);
  }
  else if (cVar3 == '\a') {
    iVar6 = (int)*(short *)(DAT_010da128 + 2 +
                           *(int *)(*(int *)(DAT_01002848 + 0x1064) + 0x80) * 0x14);
  }
  else {
    iVar6 = (int)*(char *)((int)param_3 + 0x18b);
  }
  pcVar1 = (char *)((int)param_3 + 5);
  param_3 = 0.0;
  local_8 = 0.0;
  local_c = 0.0;
  if (*pcVar1 == '\0') {
    param_3 = (float)*(int *)(iVar5 + 0x8b) *
              ((float)*(int *)(iVar5 + 0x8f) * _DAT_00cc10ac + _DAT_00cc1f58);
    fVar7 = (float10)FUN_004333b0();
    local_8 = *(float *)(iVar5 + 0x93);
  }
  else {
    if (*pcVar1 != '\x01') goto LAB_008b7d90;
    param_3 = (float)*(int *)(iVar5 + 0x97) *
              ((float)*(int *)(iVar5 + 0x9b) * _DAT_00cc10ac + _DAT_00cc1f58);
    fVar7 = (float10)FUN_004333b0();
    local_8 = *(float *)(iVar5 + 0x9f);
  }
  local_c = (float)fVar7;
  local_8 = local_8 * _DAT_00cc10ac;
LAB_008b7d90:
  fVar7 = (float10)FUN_00448c10(param_4,1);
  fVar2 = (float)(fVar7 * (float10)param_3);
  if (*(char *)(iVar5 + 0x1bc) != '\0') {
    local_c = local_c + local_c;
  }
  fVar4 = local_c * (float)iVar6 + fVar2;
  if (fVar4 <= _DAT_00cc1f58) {
    fVar4 = _DAT_00cc1f58;
  }
  *param_1 = fVar2 / fVar4;
  if (fVar2 < _DAT_00e9d7a4) {
    if (iVar6 < 10) {
      *param_1 = fVar2 * _DAT_00d5a848;
      *param_2 = local_8;
      return;
    }
    *param_2 = local_8;
    return;
  }
  *param_2 = local_8;
  return;
}

