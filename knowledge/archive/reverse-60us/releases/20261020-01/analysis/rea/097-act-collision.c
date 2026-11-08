
void FUN_00a30d20(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int in_ECX;
  int *piVar7;
  int iVar8;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_38 [4];
  void *local_34;
  int local_30;
  undefined4 local_2c;
  int local_28;
  int *local_24;
  int local_20;
  int local_1c;
  char local_15;
  char local_14;
  char local_13;
  char local_12;
  char local_11;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c8e926;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if ((*(int *)(in_ECX + 0x7c) != 0) && (local_28 = in_ECX, cVar1 = FUN_0049c090(), cVar1 != '\0'))
  {
    local_12 = '\x01';
    local_13 = '\x01';
    local_14 = '\0';
    local_20 = 0;
    if ((*(int *)(in_ECX + 0x90) != 0) &&
       ((local_24 = (int *)((*(int *)(in_ECX + 0x94) - *(int *)(in_ECX + 0x90)) / 0x1c),
        local_24 != (int *)0x0 &&
        (iVar8 = *(int *)(in_ECX + 0x90), iVar8 != *(int *)(in_ECX + 0x94))))) {
LAB_00a30db4:
      if (((*(int *)(iVar8 + 0x14) < 1) || (*(int *)(iVar8 + 0x10) < *(int *)(iVar8 + 0x14))) &&
         ((*(char *)(iVar8 + 0x19) == '\0' && (*(char *)(iVar8 + 0x18) != '\0')))) {
        local_11 = '\0';
        local_15 = '\0';
        local_34 = (void *)0x0;
        local_30 = 0;
        local_2c = 0;
        local_8 = 0;
        local_1c = iVar8;
        FUN_0048e4f0(in_ECX + 0x7c);
        piVar7 = *(int **)(iVar8 + 4);
        local_24 = piVar7 + 9;
LAB_00a30e03:
        if (piVar7 == *(int **)(iVar8 + 8)) goto LAB_00a31191;
        iVar4 = *piVar7;
        if (((((iVar4 == 9) || (iVar4 == 6)) || (iVar4 == 10)) || ((iVar4 == 0xb || (iVar4 == 0xc)))
            ) || ((((iVar4 == 0xd || ((iVar4 == 0xe || (iVar4 == 0xf)))) || (iVar4 == 0x10)) ||
                  (iVar4 == 0x11)))) {
          if (iVar4 != 0x11) goto LAB_00a31191;
          local_11 = '\x01';
        }
        switch(iVar4) {
        case 0:
          if (param_1 == 0) {
            if (local_12 == '\0') {
LAB_00a30f50:
              piVar7 = piVar7 + 0xd;
              local_24 = local_24 + 0xd;
              local_11 = '\0';
              goto LAB_00a30e03;
            }
            local_11 = '\x01';
          }
          else if (param_1 == 1) {
            if (local_13 == '\0') goto LAB_00a30f50;
            local_11 = '\x01';
          }
          else if (param_1 == 2) {
            if (local_14 == '\0') goto LAB_00a30f50;
            local_11 = '\x01';
          }
          else if (local_11 == '\0') break;
          FUN_00533100(0);
          if (((local_34 != (void *)0x0) && (local_30 - (int)local_34 >> 2 != 0)) ||
             (local_15 != '\0')) {
            *(int *)(iVar8 + 0x10) = *(int *)(iVar8 + 0x10) + 1;
            FUN_00a49220(local_20,piVar7,local_38,0);
            piVar7 = piVar7 + 0xd;
            local_24 = local_24 + 0xd;
            goto LAB_00a30e03;
          }
          break;
        case 1:
          cVar1 = FUN_00a48ac0(*(undefined4 *)(*(int *)(in_ECX + 0x20) + 0x124),piVar7,local_38);
          goto code_r0x00a31173;
        default:
          cVar1 = FUN_00a4a380(piVar7,local_38);
code_r0x00a31173:
          if (cVar1 == '\0') goto LAB_00a31191;
          break;
        case 0x19:
          FUN_00a49680(piVar7,local_38);
          piVar7 = piVar7 + 0xd;
          local_24 = local_24 + 0xd;
          goto LAB_00a30e03;
        case 0x1a:
          break;
        case 0x1d:
          if (local_34 == (void *)0x0) {
            iVar4 = 0;
          }
          else {
            iVar4 = local_30 - (int)local_34 >> 2;
          }
          puVar2 = (undefined4 *)FUN_00a3e780(1);
          puVar3 = (undefined4 *)FUN_00a3e780(0);
          cVar1 = FUN_0056f3d0(iVar4,*puVar3,*puVar2);
          iVar8 = local_1c;
          in_ECX = local_28;
          if (cVar1 == '\0') goto LAB_00a31191;
          if (iVar4 == 0) {
            piVar7 = piVar7 + 0xd;
            local_24 = local_24 + 0xd;
            local_15 = '\x01';
            goto LAB_00a30e03;
          }
          break;
        case 0x21:
          if ((local_11 != '\0') &&
             (((FUN_00533100(0), local_34 != (void *)0x0 && (local_30 - (int)local_34 >> 2 != 0)) ||
              (local_15 != '\0')))) {
            *(int *)(iVar8 + 0x10) = *(int *)(iVar8 + 0x10) + 1;
            FUN_00a49220(local_20,piVar7,local_38,0);
            piVar7 = piVar7 + 0xd;
            local_24 = local_24 + 0xd;
            goto LAB_00a30e03;
          }
          break;
        case 0x2f:
          iVar4 = FUN_00533100(0);
          if (iVar4 == 0) {
            piVar7 = piVar7 + 0xd;
            local_24 = local_24 + 0xd;
            local_12 = '\x01';
            local_14 = '\0';
            local_13 = (char)iVar4;
            goto LAB_00a30e03;
          }
          if (iVar4 == 1) {
            piVar7 = piVar7 + 0xd;
            local_24 = local_24 + 0xd;
            local_12 = '\0';
            local_14 = '\0';
            local_13 = (char)iVar4;
            goto LAB_00a30e03;
          }
          if (iVar4 == 2) {
            piVar7 = piVar7 + 0xd;
            local_24 = local_24 + 0xd;
            local_12 = '\0';
            local_13 = '\0';
            local_14 = '\x01';
            goto LAB_00a30e03;
          }
          break;
        case 0x30:
          uVar5 = FUN_00533100(0);
          uVar6 = FUN_00533100(1);
          FUN_00a49fd0(uVar5,uVar6,local_38);
          piVar7 = piVar7 + 0xd;
          local_24 = local_24 + 0xd;
          iVar8 = local_1c;
          goto LAB_00a30e03;
        case 0x31:
          iVar4 = (**(code **)(**(int **)(in_ECX + 0x7c) + 0x108))();
          if (iVar4 == 0) break;
          if (param_1 == 0) {
            if (local_12 == '\0') goto LAB_00a30f50;
            local_11 = '\x01';
          }
          else if (param_1 == 1) {
            if (local_13 == '\0') goto LAB_00a30f50;
            local_11 = '\x01';
          }
          else if (param_1 == 2) {
            if (local_14 == '\0') goto LAB_00a30f50;
            local_11 = '\x01';
          }
          else if (local_11 == '\0') break;
          iVar4 = (**(code **)(**(int **)(in_ECX + 0x7c) + 0x108))();
          if ((iVar4 == 0) ||
             (((FUN_00533100(0), local_34 == (void *)0x0 || (local_30 - (int)local_34 >> 2 == 0)) &&
              (local_15 == '\0')))) break;
          *(int *)(iVar8 + 0x10) = *(int *)(iVar8 + 0x10) + 1;
          FUN_00a49220(local_20,piVar7,local_38,1);
          piVar7 = piVar7 + 0xd;
          local_24 = local_24 + 0xd;
          goto LAB_00a30e03;
        }
        piVar7 = piVar7 + 0xd;
        local_24 = local_24 + 0xd;
        goto LAB_00a30e03;
      }
      goto LAB_00a311b5;
    }
  }
LAB_00a311d1:
  *unaff_FS_OFFSET = local_10;
  return;
LAB_00a31191:
  local_8 = 0xffffffff;
  if (local_34 != (void *)0x0) {
    _free(local_34);
  }
LAB_00a311b5:
  iVar8 = iVar8 + 0x1c;
  local_20 = local_20 + 1;
  if (iVar8 == *(int *)(in_ECX + 0x94)) goto LAB_00a311d1;
  goto LAB_00a30db4;
}

