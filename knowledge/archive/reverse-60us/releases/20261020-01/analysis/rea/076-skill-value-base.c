
undefined4
FUN_00550080(uint param_1,int param_2,undefined4 param_3,int param_4,int param_5,int param_6,
            undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int in_ECX;
  uint uVar4;
  
  if ((*(int *)(in_ECX + 0x240) == 0) ||
     ((uint)(*(int *)(in_ECX + 0x244) - *(int *)(in_ECX + 0x240) >> 4) <= param_1)) {
    return 0;
  }
  iVar1 = *(int *)(param_1 * 0x10 + 4 + *(int *)(in_ECX + 0x240));
  if (iVar1 == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = *(int *)(param_1 * 0x10 + *(int *)(in_ECX + 0x240) + 8) - iVar1 >> 3;
  }
  if (uVar4 <= param_2 - 1U) {
    return 0;
  }
  uVar2 = FUN_00402060();
  uVar3 = FUN_00402060();
  uVar2 = FUN_0054fc40(param_3,uVar2,param_1,1,uVar3);
  if (param_6 != 0xc) {
    if (param_4 != param_5) {
      FUN_00448150(param_4,param_6,param_7);
      FUN_00448150(param_5,param_6,param_8);
      uVar2 = FUN_00c01544();
    }
  }
  return uVar2;
}

