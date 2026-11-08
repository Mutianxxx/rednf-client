
void FUN_004b9c60(int param_1,int param_2,undefined4 param_3,undefined4 param_4,uint param_5,
                 uint param_6)

{
  uint *puVar1;
  int *in_ECX;
  
  in_ECX[0x585] = param_2;
  in_ECX[0x584] = param_1;
  puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x58b] * 4);
  *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ param_5;
  puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x58b] * 4);
  *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ param_5;
  puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x58d] * 4);
  *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ param_6;
  puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x58d] * 4);
  *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ param_6;
  if (param_1 != 0) {
    (**(code **)(*in_ECX + 0x584))(param_1);
    FUN_004333b0();
    param_3 = FUN_00c01544();
  }
  if (param_2 != 0) {
    (**(code **)(*in_ECX + 0x584))(param_2);
    FUN_004333b0();
    param_4 = FUN_00c01544();
  }
  (**(code **)(*in_ECX + 0x588))(param_3);
  (**(code **)(*in_ECX + 0x58c))(param_4);
  return;
}

