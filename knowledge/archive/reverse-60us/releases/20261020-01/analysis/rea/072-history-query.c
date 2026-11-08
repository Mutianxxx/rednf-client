
uint FUN_004ece50(int *param_1)

{
  int *piVar1;
  uint in_EAX;
  int *piVar2;
  uint uVar3;
  int *in_ECX;
  int *local_8;
  
  piVar1 = param_1;
  if (param_1 == (int *)0x0) {
    return in_EAX & 0xffffff00;
  }
  local_8 = in_ECX;
  piVar2 = (int *)(**(code **)(*in_ECX + 0x1c8))();
  if (piVar2 != in_ECX) {
    piVar2 = (int *)(**(code **)(*in_ECX + 0x1c8))();
    uVar3 = (**(code **)(*piVar2 + 0x1a8))(piVar1);
    return uVar3;
  }
  param_1 = (int *)(**(code **)(*piVar1 + 0x1c8))();
  FUN_00a64ce0(&local_8,&param_1);
  return (uint)(local_8 != (int *)in_ECX[0x108]);
}

