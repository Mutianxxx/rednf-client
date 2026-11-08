
void FUN_00512390(void)

{
  int iVar1;
  int in_ECX;
  
  if (*(int **)(in_ECX + 0x78) != (int *)0x0) {
    (**(code **)(**(int **)(in_ECX + 0x78) + 4))(0);
  }
  FUN_00404ef0();
  FUN_00b06f60(0,0);
  *(undefined4 *)(in_ECX + 0xe4) = 0;
  iVar1 = *(int *)(in_ECX + 0xfc);
  if (*(int *)(in_ECX + 0xfc) == -1) {
    iVar1 = DAT_00f5be7c;
  }
  *(int *)(in_ECX + 0xe8) = -iVar1;
  *(undefined4 *)(in_ECX + 0xec) = 0;
  *(undefined4 *)(in_ECX + 0xf0) = 0;
  *(undefined4 *)(in_ECX + 0xf4) = 0;
  *(undefined1 *)(in_ECX + 0xf8) = 0;
  FUN_0050fcd0();
  return;
}

