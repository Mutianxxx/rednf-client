
void FUN_004edd10(int *param_1)

{
  int *piVar1;
  char cVar2;
  int *in_ECX;
  int *local_8;
  
  piVar1 = param_1;
  local_8 = in_ECX;
  FUN_0049bc20(param_1);
  cVar2 = (**(code **)(*piVar1 + 0x2c))(1);
  if (cVar2 != '\0') {
    FUN_004eca20(piVar1);
  }
  FUN_00a64ce0(&local_8,&param_1);
  if (local_8 != (int *)in_ECX[0x108]) {
    FUN_00564580(&local_8,local_8);
  }
  FUN_00a64ce0(&local_8,&param_1);
  if (local_8 != (int *)in_ECX[0x11e]) {
    FUN_00564580(&param_1,local_8);
  }
  if ((int *)in_ECX[0x116] == piVar1) {
    in_ECX[0x116] = 0;
  }
  if ((int *)in_ECX[0x138] == piVar1) {
    in_ECX[0x138] = 0;
  }
  if ((int *)in_ECX[0x13b] == piVar1) {
    in_ECX[0x13b] = 0;
  }
  if (piVar1 == in_ECX) {
    FUN_0044aaa0();
    if ((void *)in_ECX[0x135] != (void *)0x0) {
      _free((void *)in_ECX[0x135]);
    }
    in_ECX[0x135] = 0;
    in_ECX[0x136] = 0;
    in_ECX[0x137] = 0;
    FUN_004389b0();
    FUN_004389b0();
    in_ECX[0x116] = 0;
  }
  return;
}

