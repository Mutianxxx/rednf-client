
void FUN_00408722(int param_1)

{
  undefined4 in_EAX;
  byte bVar1;
  undefined4 *in_ECX;
  int iVar2;
  int in_EDX;
  undefined4 *puVar3;
  undefined4 local_10;
  
  iVar2 = 0;
  puVar3 = &local_10;
  local_10 = in_EAX;
  do {
    bVar1 = (byte)iVar2;
    iVar2 = iVar2 + 8;
    *(char *)puVar3 = (char)((uint)(in_EDX - param_1) >> (bVar1 & 0x1f));
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  } while (iVar2 != 0x20);
  *in_ECX = local_10;
  return;
}

