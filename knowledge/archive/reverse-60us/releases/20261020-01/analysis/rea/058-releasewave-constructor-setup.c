
void FUN_005c77b0(int param_1)

{
  uint *puVar1;
  undefined4 uVar2;
  int in_ECX;
  
  puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(in_ECX + 0x5e0) * 4);
  *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ (uint)(float)param_1;
  puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(in_ECX + 0x5e0) * 4);
  *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ (uint)(float)param_1;
  uVar2 = FUN_00bffdcd(u_WAVE_CANCLE_00cf08a0);
  FUN_00402e80(u_WAVE_CANCLE_00cf08a0,uVar2);
  return;
}

