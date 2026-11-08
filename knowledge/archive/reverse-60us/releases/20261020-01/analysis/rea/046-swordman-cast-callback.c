
void FUN_0071cab0(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int *in_ECX;
  
  cVar1 = FUN_0049c090();
  if (cVar1 != '\0') {
    if (in_ECX[0x90a] == 0) {
      iVar2 = FUN_00402060();
      if ((iVar2 == 0x4a) && (param_1 == -1)) {
        (**(code **)(*in_ECX + 0x28c))(0x29,0,0,0,0);
        return;
      }
    }
    FUN_004d80f0(param_1,param_2);
  }
  return;
}

