
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004cf680(int param_1)

{
  uint *puVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  int *in_ECX;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  
  uVar3 = *(undefined4 *)(param_1 + 0x178);
  uVar2 = *(undefined1 *)(param_1 + 0x17c);
  uVar5 = FUN_00402060();
  fVar9 = (float10)FUN_004333b0();
  if (*(int *)(param_1 + 0x178) == 5) {
    uVar6 = (**(code **)(*in_ECX + 0x698))();
    *(undefined4 *)(param_1 + 0x178) = uVar6;
    uVar4 = (**(code **)(*in_ECX + 0x69c))();
    *(undefined1 *)(param_1 + 0x17c) = uVar4;
  }
  iVar7 = FUN_00402060();
  if (iVar7 == -1) {
    uVar8 = (**(code **)(*in_ECX + 0x6a0))();
    puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(param_1 + 0x184) * 4);
    *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ uVar8;
    puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(param_1 + 0x184) * 4);
    *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ uVar8;
  }
  fVar10 = (float10)FUN_004333b0();
  fVar12 = (float10)_DAT_00cab8f0;
  fVar11 = (float10)FUN_004333b0();
  if ((float10)(double)ABS(fVar10 - fVar12) <= ABS(fVar11) * (float10)_DAT_00cab8e8) {
    fVar12 = (float10)(**(code **)(*in_ECX + 0x6a4))();
    puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(param_1 + 0x18c) * 4);
    *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ (uint)(float)fVar12;
    puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(param_1 + 0x18c) * 4);
    *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ (uint)(float)fVar12;
  }
  FUN_004afa10(param_1);
  *(undefined1 *)(param_1 + 0x17c) = uVar2;
  *(undefined4 *)(param_1 + 0x178) = uVar3;
  puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(param_1 + 0x184) * 4);
  *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ uVar5;
  puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(param_1 + 0x184) * 4);
  *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ uVar5;
  puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(param_1 + 0x18c) * 4);
  *puVar1 = (uint)puVar1 ^ (uint)(float)fVar9 ^ DAT_012101dc;
  puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(param_1 + 0x18c) * 4);
  *puVar1 = (uint)puVar1 ^ (uint)(float)fVar9 ^ DAT_012101dc;
  iVar7 = FUN_00402060();
  if (0 < iVar7) {
    (**(code **)(*in_ECX + 0x344))(3);
    FUN_004333b0();
    FUN_00402060();
    uVar5 = FUN_00c01544();
    puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0xf9] * 4);
    *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ uVar5;
    puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0xf9] * 4);
    *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ uVar5;
  }
  return;
}

