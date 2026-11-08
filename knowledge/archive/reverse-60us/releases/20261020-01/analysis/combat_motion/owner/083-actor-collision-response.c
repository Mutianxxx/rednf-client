
void FUN_004b97b0(int param_1,undefined4 param_2,undefined4 param_3)

{
  int *in_ECX;
  
  FUN_004e8a30(param_1,param_2,param_3);
  if ((((*(char *)((int)in_ECX + 0x1606) != '\0') && (*(char *)((int)in_ECX + 0x1607) != '\0')) &&
      (in_ECX[0x59e] == -1)) && ((param_1 == 0 || (param_1 == 1)))) {
    (**(code **)(*in_ECX + 0x57c))(param_1);
  }
  return;
}

