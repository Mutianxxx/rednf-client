
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00511310(undefined4 param_1,int param_2)

{
  int iVar1;
  int in_ECX;
  float10 fVar2;
  float10 fVar3;
  float fVar4;
  
  *(undefined4 *)(in_ECX + 300) = param_1;
  iVar1 = FUN_00c01544();
  fVar2 = (float10)FUN_00b158d0(iVar1);
  fVar3 = (float10)FUN_00b158b0(iVar1);
  FUN_00511040(0,(float)fVar2 * *(float *)(in_ECX + 0x108));
  FUN_00511040(1,(float)DAT_00faf2dc * *(float *)(in_ECX + 0x108) * (float)fVar3 * _DAT_00cc10ac);
  fVar4 = (float)param_2 * *(float *)(in_ECX + 0x10c) * _DAT_00cc11f8 + *(float *)(in_ECX + 0x108);
  *(float *)(in_ECX + 0x108) = fVar4;
  if (fVar4 < _DAT_00e9d7a4) {
    *(undefined4 *)(in_ECX + 0x108) = 0;
  }
  if ((*(char *)(in_ECX + 0x11c) != '\0') && (*(int **)(in_ECX + 0x74) != (int *)0x0)) {
    fVar4 = (float)((iVar1 + 0xb4) % 0x168) * _DAT_00cd6938 * (float)_DAT_00cd6930;
    (**(code **)(**(int **)(in_ECX + 0x74) + 0xf4))(fVar4);
    FUN_00a25880(fVar4);
  }
  return;
}

