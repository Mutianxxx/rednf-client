
uint FUN_004f2a40(void)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int *in_ECX;
  
  cVar1 = (**(code **)(*in_ECX + 0x38))();
  if (cVar1 != '\0') {
    uVar2 = FUN_00bffdcd(&DAT_00cabae0);
    uVar3 = FUN_00403ff0(0,in_ECX[0x6c1],&DAT_00cabae0,uVar2);
    if (uVar3 != 0) {
      return uVar3 & 0xffffff00;
    }
  }
  if ((in_ECX[0x679] == 3) || (in_ECX[0x679] == 8)) {
    iVar4 = FUN_00402060();
    if ((iVar4 != 3) && (iVar4 = FUN_00402060(), iVar4 != 10)) {
      return 0;
    }
    iVar4 = (**(code **)(*in_ECX + 0x378))();
    if ((iVar4 == 0) && (iVar4 = (**(code **)(*in_ECX + 0x3a0))(), iVar4 == 0)) {
      return 0;
    }
    if ((char)in_ECX[0x93f] == '\0') {
      return 1;
    }
  }
  return 0;
}

