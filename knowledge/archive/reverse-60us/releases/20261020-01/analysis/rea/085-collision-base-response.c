
void FUN_004e8a30(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int in_ECX;
  
  if (*(int **)(in_ECX + 0x148) != (int *)0x0) {
    (**(code **)(**(int **)(in_ECX + 0x148) + 0x1c))(param_1,param_2,param_3);
  }
  if (*(int **)(in_ECX + 0x154) != (int *)0x0) {
    (**(code **)(**(int **)(in_ECX + 0x154) + 0x1c))(param_1,param_2,param_3);
  }
  return;
}

