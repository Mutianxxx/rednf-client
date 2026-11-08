
void FUN_004ede20(int *param_1)

{
  int *piVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int *in_ECX;
  
  piVar1 = param_1;
  if (param_1 != (int *)0x0) {
    piVar2 = (int *)(**(code **)(*in_ECX + 0x1c8))();
    if (piVar2 != in_ECX) {
      piVar2 = (int *)(**(code **)(*in_ECX + 0x1c8))();
      (**(code **)(*piVar2 + 0x1a4))(piVar1);
      return;
    }
    param_1 = (int *)(**(code **)(*piVar1 + 0x1c8))();
    puVar3 = (undefined4 *)FUN_004eecf0(&param_1);
    uVar4 = (**(code **)(*piVar1 + 0x1c8))();
    *puVar3 = uVar4;
    piVar2 = (int *)(**(code **)(*piVar1 + 0x1c8))();
    if (piVar1 != piVar2) {
      param_1 = piVar1;
      puVar3 = (undefined4 *)FUN_004eecf0(&param_1);
      *puVar3 = piVar1;
    }
  }
  return;
}

