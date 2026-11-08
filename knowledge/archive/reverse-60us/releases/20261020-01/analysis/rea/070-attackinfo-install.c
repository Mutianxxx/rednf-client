
void FUN_004edcd0(int param_1)

{
  int *in_ECX;
  
  if (param_1 == 0) {
    FUN_00435430();
    (**(code **)(*in_ECX + 0x1a0))();
    return;
  }
  FUN_004a27e0(param_1);
  (**(code **)(*in_ECX + 0x1a0))();
  return;
}

