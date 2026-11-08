
/* WARNING: Type propagation algorithm not settling */

void FUN_0040f141(void)

{
  char *pcVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int in_EDX;
  undefined1 *puVar7;
  undefined1 local_128 [4];
  undefined2 uStack_124;
  char acStack_122 [2];
  undefined2 uStack_120;
  char local_11e [2];
  undefined2 uStack_11c;
  char acStack_11a [4];
  char acStack_116 [205];
  undefined2 local_49;
  char acStack_47 [7];
  char local_40 [4];
  char local_3c [4];
  undefined1 *local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  local_1c = in_EDX + 0x404;
  local_128._0_2_ = 0x5ff;
  local_14 = 2;
  local_18 = in_EDX;
  FUN_004076ed(local_1c);
  iVar6 = local_14;
  iVar4 = local_14 + 8;
  local_20 = local_14;
  *(undefined4 *)(local_128 + local_14) = 0x840fc985;
  FUN_00408722(iVar4);
  for (iVar4 = -4; iVar4 != 0; iVar4 = iVar4 + 1) {
    *(undefined1 *)((int)&uStack_120 + iVar4 + iVar6) = *(undefined1 *)((int)&local_38 + iVar4);
  }
  for (iVar4 = 0; iVar5 = local_20, iVar4 != 10; iVar4 = iVar4 + 1) {
    *(undefined1 *)((int)&uStack_120 + iVar6 + iVar4) = (&DAT_0043773e)[iVar4];
  }
  local_34 = (int)&uStack_120 + iVar6;
  acStack_116[iVar6] = 'u';
  iVar5 = iVar5 + 0x14;
  for (iVar4 = -6; iVar4 != 0; iVar4 = iVar4 + 1) {
    local_128[iVar5] = (&DAT_0043774e)[iVar4];
    iVar5 = iVar5 + 1;
  }
  iVar4 = local_18 + 0x400;
  local_14 = iVar5;
  FUN_0040f6ac(0x402060);
  local_30 = iVar4;
  local_128[local_14] = 0xa3;
  local_14 = local_14 + 1;
  FUN_004076ed(iVar4);
  iVar4 = local_14;
  for (iVar6 = 0; iVar6 != 5; iVar6 = iVar6 + 1) {
    local_128[iVar4] = (&DAT_0043774e)[iVar6];
    iVar4 = iVar4 + 1;
  }
  *(undefined2 *)(local_128 + iVar4) = 0x870f;
  FUN_00408722(iVar4 + 6);
  for (iVar6 = -4; iVar5 = local_18, iVar6 != 0; iVar6 = iVar6 + 1) {
    acStack_122[iVar6 + iVar4] = local_3c[iVar6];
  }
  (acStack_122 + iVar4)[0] = -0x2f;
  (acStack_122 + iVar4)[1] = -0x20;
  *(undefined1 *)((int)&uStack_120 + iVar4) = 5;
  local_14 = iVar4 + 9;
  FUN_004076ed(iVar5 + 0x420);
  *(undefined4 *)(local_128 + local_14) = 0x28bd08b;
  *(undefined2 *)((int)&uStack_124 + local_14) = 0xc085;
  acStack_122[local_14] = 't';
  iVar4 = local_14 + 8;
  *(undefined2 *)((int)&uStack_120 + local_14) = 0xd8b;
  local_2c = local_14;
  local_14 = local_14 + 10;
  local_28 = iVar4;
  FUN_004076ed(local_1c);
  iVar6 = local_14;
  iVar4 = local_14 + 2;
  *(undefined2 *)(local_128 + local_14) = 0xc82b;
  local_24 = iVar6;
  for (iVar6 = 0; iVar6 != 6; iVar6 = iVar6 + 1) {
    local_128[iVar4] = (&DAT_00437753)[iVar6];
    iVar4 = iVar4 + 1;
  }
  *(undefined2 *)(local_128 + iVar4) = 0x820f;
  FUN_00408722(iVar4 + 6);
  iVar5 = local_24;
  for (iVar6 = -4; iVar6 != 0; iVar6 = iVar6 + 1) {
    acStack_116[iVar6 + iVar5 + -4] = local_40[iVar6];
  }
  acStack_122[local_2c + 1] = ((char)iVar4 + '\x06') - (char)local_28;
  acStack_122[iVar4] = -0x5f;
  local_14 = iVar4 + 7;
  FUN_004076ed(local_1c);
  *(undefined4 *)(local_128 + local_14) = 0x5ff0289;
  local_14 = local_14 + 4;
  FUN_004076ed(local_18 + 0x408);
  *(undefined2 *)(local_128 + local_14) = 0xd8b;
  local_14 = local_14 + 2;
  FUN_004076ed(0x10d4280);
  *(undefined2 *)(local_128 + local_14) = 0x2a6a;
  local_14 = local_14 + 2;
  FUN_0040f6ac(0xa5e2f0);
  *(undefined2 *)(local_128 + local_14) = 0xd8b;
  local_14 = local_14 + 2;
  FUN_004076ed(0x10d4280);
  *(undefined2 *)(local_128 + local_14) = 0x26a;
  local_128[local_14 + 2] = 0x68;
  local_14 = local_14 + 3;
  FUN_004076ed(local_30);
  FUN_0040f6ac(0xa5e3d0);
  FUN_0040f6ac(0xa5f4a0);
  cVar2 = (char)local_20;
  cVar3 = (char)local_14;
  local_128[local_14] = 0xeb;
  local_128[local_14 + 1] = -0x23 - cVar3;
  *(char *)(local_34 + 0xb) = (cVar3 - cVar2) + -0x12;
  for (iVar4 = 0; iVar4 != 10; iVar4 = iVar4 + 1) {
    local_128[iVar4 + local_14 + 2] = (&DAT_00437759)[iVar4];
  }
  *(undefined1 *)((int)&uStack_11c + local_14) = 0x75;
  *(char *)((int)&uStack_11c + local_14 + 1) = -cVar3 + -0x2f;
  pcVar1 = acStack_116 + local_14 + -4;
  pcVar1[0] = -0x75;
  pcVar1[1] = '\x11';
  pcVar1[2] = -0x7b;
  pcVar1[3] = -0x2e;
  acStack_116[local_14] = 't';
  acStack_116[local_14 + 1] = -cVar3 + -0x35;
  (acStack_116 + local_14 + 2)[0] = -0x7f;
  (acStack_116 + local_14 + 2)[1] = -6;
  local_14 = local_14 + 0x16;
  FUN_004076ed(0x400000);
  local_128[local_14] = 0x72;
  local_128[local_14 + 1] = -0x23 - (char)local_14;
  *(undefined2 *)(local_128 + local_14 + 2) = 0xfa81;
  local_14 = local_14 + 4;
  FUN_004076ed(0x1410000);
  local_128[local_14] = 0x73;
  local_128[local_14 + 1] = -0x23 - (char)local_14;
  for (iVar4 = 0; iVar4 != 6; iVar4 = iVar4 + 1) {
    local_128[iVar4 + local_14 + 2] = (&DAT_00437763)[iVar4];
  }
  *(undefined2 *)((int)&uStack_120 + local_14) = 0xd285;
  local_11e[local_14] = 't';
  local_11e[local_14 + 1] = -0x2d - (char)local_14;
  *(undefined2 *)((int)&uStack_11c + local_14) = 0xfa81;
  local_14 = local_14 + 0xe;
  FUN_004076ed(0x400000);
  local_128[local_14] = 0x72;
  local_128[local_14 + 1] = -0x23 - (char)local_14;
  *(undefined2 *)(local_128 + local_14 + 2) = 0xfa81;
  local_14 = local_14 + 4;
  FUN_004076ed(0x1410000);
  local_128[local_14] = 0x73;
  local_128[local_14 + 1] = -0x23 - (char)local_14;
  *(undefined4 *)(local_128 + local_14 + 2) = 0x8b006a51;
  acStack_122[local_14] = '\x01';
  iVar6 = local_14 + 10;
  for (iVar4 = -3; iVar4 != 0; iVar4 = iVar4 + 1) {
    acStack_116[iVar6 + -0x15] = (&DAT_0043776c)[iVar4];
    iVar6 = iVar6 + 1;
  }
  (acStack_116 + iVar6 + -0x15)[0] = 'Y';
  (acStack_116 + iVar6 + -0x15)[1] = -0x3a;
  acStack_116[iVar6 + -0x13] = -0x7f;
  local_14 = iVar6;
  FUN_004076ed(0x184);
  local_128[local_14] = 0;
  local_49 = 0x1b0;
  for (iVar4 = -3; iVar4 != 0; iVar4 = iVar4 + 1) {
    acStack_47[iVar4 + 3] = (&DAT_00437770)[iVar4];
  }
  puVar7 = local_128;
  for (iVar4 = 0xe4; iVar4 != 0; iVar4 = iVar4 + -1) {
    *local_38 = *puVar7;
    puVar7 = puVar7 + 1;
    local_38 = local_38 + 1;
  }
  return;
}

