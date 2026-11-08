
/* WARNING: Removing unreachable block (ram,0x00add43a) */
/* WARNING: Removing unreachable block (ram,0x00add464) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00add3d0(int param_1,int param_2,int param_3,undefined4 param_4,int param_5,float param_6,
                 float param_7,float param_8,float param_9,float param_10,undefined4 param_11)

{
  float fVar1;
  float fVar2;
  char cVar3;
  DWORD DVar4;
  undefined2 extraout_var;
  undefined4 uVar5;
  int in_ECX;
  float local_64;
  float local_60;
  float local_54;
  float local_50;
  float local_34;
  float local_30;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  cVar3 = FUN_00adcf90();
  if (cVar3 != '\0') {
    DVar4 = timeGetTime();
    *(DWORD *)(in_ECX + 0x54) = DVar4;
    FUN_00b09fb0(4);
    thunk_FUN_00c3551a(&local_64,-param_6);
    if (param_6 == _DAT_00e9d7a4) {
      if (param_9 == _DAT_00cc46cc) {
        param_9 = (float)(*(uint *)(in_ECX + 0x14) >> 1);
      }
      if (param_10 == _DAT_00cc46cc) {
        param_10 = (float)(*(uint *)(in_ECX + 0x18) >> 1);
      }
    }
    local_64 = local_64 * param_7;
    local_60 = local_60 * param_8;
    local_54 = local_54 * param_7;
    local_50 = local_50 * param_8;
    fVar1 = (float)*(int *)(in_ECX + 0x1c) - param_9;
    fVar2 = (float)*(int *)(in_ECX + 0x20) - param_10;
    local_34 = (float)param_1 + param_9 + fVar1 * local_64 + local_54 * fVar2;
    local_30 = (float)param_2 + param_10 + fVar1 * local_60 + fVar2 * local_50;
    if (param_5 == 0) {
      if ((param_7 != _DAT_00cc1f58) ||
         (uVar5 = CONCAT22(extraout_var,
                           (ushort)(param_8 < _DAT_00cc1f58) << 8 |
                           (ushort)(NAN(param_8) || NAN(_DAT_00cc1f58)) << 10 |
                           (ushort)(param_8 == _DAT_00cc1f58) << 0xe), param_8 != _DAT_00cc1f58)) {
        uVar5 = 1;
      }
      FUN_00b08d30(*(undefined4 *)(in_ECX + 0x68),param_11,param_3 + 0x30,&local_64,param_4,uVar5);
      FUN_00b09ff0(4,0);
      return;
    }
    if (*(char *)(DAT_010db8e0 + 0x50338) == '\0') {
      FUN_00adcac0(*(undefined4 *)(DAT_010db8e0 + 0x1c),param_3);
      if (DAT_00ff2661 != '\0') {
        FUN_00b08710();
      }
      local_1c = (float)*(int *)(in_ECX + 0x1c);
      local_18 = (float)*(int *)(in_ECX + 0x20);
      local_c = param_9;
      local_8 = param_10;
      local_10 = param_8;
      local_14 = param_7;
      local_24 = (float)param_1;
      local_20 = (float)param_2;
      FUN_00aff9c0(&local_24,&local_1c,param_3 + 0x30,*(undefined4 *)(in_ECX + 0x68),in_ECX,
                   &local_14,&local_c,param_6,param_4,&local_64,param_5);
    }
    FUN_00b09ff0(4,0);
  }
  return;
}

