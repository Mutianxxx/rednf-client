
void FUN_004f5bc0(undefined4 param_1)

{
  int in_ECX;
  uint uVar1;
  
  FUN_004ac090(param_1);
  for (uVar1 = 0;
      (*(int *)(in_ECX + 0x2308) != 0 &&
      (uVar1 < (uint)((*(int *)(in_ECX + 0x230c) - *(int *)(in_ECX + 0x2308)) / 0x24)));
      uVar1 = uVar1 + 1) {
    FUN_0074da90(param_1);
  }
  return;
}

