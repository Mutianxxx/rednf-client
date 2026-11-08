
void FUN_005f5b40(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  int *in_ECX;
  
  FUN_0049d0e0(param_1,param_2,param_3,param_4,param_5);
  iVar1 = (**(code **)(*in_ECX + 0x234))();
  if ((iVar1 < 1) && (in_ECX[0x21f] < in_ECX[0x221])) {
    in_ECX[0x21f] = in_ECX[0x21f] + 1;
    (**(code **)(*in_ECX + 0x388))();
    iVar1 = *in_ECX;
    uVar2 = (**(code **)(iVar1 + 0x238))();
    (**(code **)(iVar1 + 0x35c))(uVar2);
  }
  else {
    iVar1 = in_ECX[0x48];
    if ((iVar1 != 0) && ((1 < (uint)(in_ECX[0x49] - iVar1 >> 2) && (*(int *)(iVar1 + 4) != 0)))) {
      in_ECX[0x24f] = 1;
      FUN_00a27360();
      (**(code **)(*in_ECX + 0xf0))(*(undefined4 *)(in_ECX[0x48] + 4));
    }
  }
  if ((in_ECX[0x221] <= in_ECX[0x21f]) && ((char)in_ECX[0x222] == '\x01')) {
    (**(code **)(*in_ECX + 0x38c))(param_1);
  }
  return;
}

