
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005383d0(int param_1,undefined4 param_2,float param_3,float param_4,float param_5,
                 float param_6,undefined4 param_7,float param_8,undefined4 param_9,int param_10)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  int iVar6;
  byte bVar7;
  undefined4 local_c;
  float local_8;
  
  uVar5 = param_9;
  fVar4 = param_8;
  fVar3 = param_3;
  if (param_3 == 0.0) {
    return;
  }
  if (param_10 == 4) {
    fVar1 = param_6 + _DAT_00cdc178;
  }
  else {
    if (param_10 != 5) goto LAB_00538490;
    FUN_005383d0(param_1,param_2,param_3,param_4,param_5,param_6 + _DAT_00cdc174,param_7,param_8,
                 param_9,0);
    FUN_005383d0(param_1,param_2,fVar3,param_4,param_5,param_6 + _DAT_00cdc178,param_7,fVar4,uVar5,0
                );
    fVar1 = param_6 + _DAT_00cdc170;
  }
  FUN_005383d0(param_1,param_2,fVar3,param_4,param_5,fVar1,param_7,fVar4,uVar5,0);
LAB_00538490:
  if (((((*(int *)(DAT_010da92c + 0x30) == 0) && (*(int *)(DAT_010da92c + 0x34) == 0)) &&
       (*(int *)(DAT_010da92c + 0x38) == 0x280)) && (*(int *)(DAT_010da92c + 0x3c) == 0x1e0)) ||
     (local_c = 1, ABS(param_6) <= ABS(param_6) * (float)_DAT_00cab8e8)) {
    local_c = 0;
  }
  iVar6 = FUN_00402060();
  if ((iVar6 == 1) ||
     (param_3 = (float)((uint)param_3 & 0xffffff),
     ABS(param_6) <= ABS(param_6) * (float)_DAT_00cab8e8)) {
    param_3 = (float)CONCAT13(1,param_3._0_3_);
  }
  local_8 = (float)*(int *)((int)fVar3 + 0x14);
  if (*(int *)((int)fVar3 + 0x14) < 0) {
    local_8 = local_8 + _DAT_00cc46cc;
  }
  if ((param_10 == 1) || (param_10 == 3)) {
    local_8 = local_8 + local_8;
  }
  if (ABS(DAT_00f5da14) * (float)_DAT_00cab8e8 < ABS(DAT_00f5da14 - (float)_DAT_00ccb5a0)) {
    FUN_005377b0(&param_1,&param_2,fVar4,uVar5);
    if (param_3._3_1_ == '\x01') {
      fVar1 = (float)*(int *)((int)fVar3 + 0x1c) - param_8;
      fVar2 = fVar1 * DAT_00f5da14 * param_4 + (float)param_1 + param_8;
      param_3 = (fVar1 + local_8) * DAT_00f5da14 * param_4 + (float)param_1 + param_8;
      if (param_4 < _DAT_00e9d7a4) {
        if (_DAT_00cdc16c <= param_3) {
          return;
        }
        bVar7 = fVar2 < _DAT_00e9d7a4 |
                (byte)((ushort)((ushort)(NAN(fVar2) || NAN(_DAT_00e9d7a4)) << 10) >> 8);
      }
      else {
        if (_DAT_00cdc16c <= fVar2) {
          return;
        }
        bVar7 = param_3 < _DAT_00e9d7a4 |
                (byte)((ushort)((ushort)(NAN(param_3) || NAN(_DAT_00e9d7a4)) << 10) >> 8);
      }
      if ((POPCOUNT(bVar7) & 1U) != 0) {
        return;
      }
    }
    if (((param_10 != 0) && (param_10 != 4)) && (param_10 != 5)) {
      FUN_00b0e110(param_1,param_2,fVar3,DAT_00f5da14 * param_4,DAT_00f5da14 * param_5,param_6,
                   param_7,fVar4,uVar5,param_10);
      return;
    }
    FUN_00b0e050(param_1,param_2,fVar3,DAT_00f5da14 * param_4,DAT_00f5da14 * param_5,param_6,param_7
                 ,fVar4,uVar5,local_c);
    return;
  }
  if (param_3._3_1_ == '\x01') {
    fVar1 = (float)*(int *)((int)fVar3 + 0x1c) - param_8;
    fVar2 = fVar1 * param_4 + (float)param_1 + param_8;
    param_3 = (fVar1 + local_8) * param_4 + (float)param_1 + param_8;
    if (param_4 < _DAT_00e9d7a4) {
      if (_DAT_00cdc16c <= param_3) {
        return;
      }
      bVar7 = fVar2 < _DAT_00e9d7a4 |
              (byte)((ushort)((ushort)(NAN(fVar2) || NAN(_DAT_00e9d7a4)) << 10) >> 8);
    }
    else {
      if (_DAT_00cdc16c <= fVar2) {
        return;
      }
      bVar7 = param_3 < _DAT_00e9d7a4 |
              (byte)((ushort)((ushort)(NAN(param_3) || NAN(_DAT_00e9d7a4)) << 10) >> 8);
    }
    if ((POPCOUNT(bVar7) & 1U) != 0) {
      return;
    }
  }
  if (((param_10 != 0) && (param_10 != 4)) && (param_10 != 5)) {
    FUN_00b0e110(param_1,param_2,fVar3,param_4,param_5,param_6,param_7,fVar4,uVar5,param_10);
    return;
  }
  FUN_00b0e050(param_1,param_2,fVar3,param_4,param_5,param_6,param_7,fVar4,uVar5,local_c);
  return;
}

