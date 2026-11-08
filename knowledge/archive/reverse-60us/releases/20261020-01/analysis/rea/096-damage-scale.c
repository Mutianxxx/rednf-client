
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_008b7ab0(int param_1,float *param_2,undefined4 param_3)

{
  float fVar1;
  byte bVar2;
  float *pfVar3;
  uint in_EAX;
  int iVar4;
  float10 fVar5;
  
  pfVar3 = param_2;
  if (param_2 == (float *)0x0) {
    return in_EAX & 0xffffff00;
  }
  param_2 = (float *)(*(float *)(param_1 + 0x13) + _DAT_00ccb578);
  bVar2 = (byte)*(undefined4 *)(param_1 + 0x195);
  if (*(char *)(param_1 + 0x18e) == '\0') {
    if ((bVar2 & 0x11) == 0x11) {
      if (*(char *)(param_1 + 5) == '\0') {
        param_2 = (float *)((float)param_2 + *(float *)(param_1 + 0x4b));
      }
      else if (*(char *)(param_1 + 5) == '\x01') {
        param_2 = (float *)((float)param_2 + *(float *)(param_1 + 0x4f));
      }
    }
  }
  else if ((bVar2 & 0x81) == 0x81) {
    param_2 = (float *)((float)param_2 + *(float *)(param_1 + 0x5b));
  }
  if ((*(char *)(param_1 + 0x1b5) != '\0') &&
     (param_2 = (float *)((float)param_2 + *(float *)(param_1 + 0x17)), (bVar2 & 0x11) == 0x11)) {
    if (*(char *)(param_1 + 5) == '\0') {
      fVar1 = *(float *)(param_1 + 0x53);
    }
    else {
      if (*(char *)(param_1 + 5) != '\x01') goto LAB_008b7b53;
      fVar1 = *(float *)(param_1 + 0x57);
    }
    param_2 = (float *)((float)param_2 + fVar1);
  }
LAB_008b7b53:
  if (((byte)*(undefined4 *)(param_1 + 0x199) & 0x11) == 0x11) {
    param_2 = (float *)((float)param_2 - *(float *)(param_1 + 0xbf));
  }
  iVar4 = FUN_008ae160(param_3);
  if ((float)param_2 * _DAT_00ccb9d8 <= (float)(iVar4 % 10000)) {
    *(undefined1 *)(param_1 + 0x1a5) = 0;
    return (uint)(*(char *)(param_1 + 0x1a5) != '\0');
  }
  fVar5 = (float10)FUN_004333b0();
  if (((byte)*(undefined4 *)(param_1 + 0x195) & 0x11) == 0x11) {
    fVar5 = fVar5 * (float10)*(float *)(param_1 + 0x6f);
  }
  *pfVar3 = (float)(fVar5 * (float10)*pfVar3);
  *(undefined1 *)(param_1 + 0x1a5) = 1;
  return (uint)(*(char *)(param_1 + 0x1a5) != '\0');
}

