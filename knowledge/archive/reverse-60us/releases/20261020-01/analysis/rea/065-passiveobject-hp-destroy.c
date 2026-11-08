
void FUN_0049d0e0(void)

{
  int iVar1;
  int *in_ECX;
  
  iVar1 = (**(code **)(*in_ECX + 0x33c))();
  if (*(char *)(iVar1 + 0x34) != '\0') {
    iVar1 = (**(code **)(*in_ECX + 0x238))();
    if (0 < iVar1) {
      iVar1 = (**(code **)(*in_ECX + 0x234))();
      if (iVar1 < 1) {
        (**(code **)(*in_ECX + 0x164))(0);
      }
    }
  }
  return;
}

