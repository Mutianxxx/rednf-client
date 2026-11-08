function sq_AddFunctionName(appendage) {
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_alteration")
	appendage.sq_AddFunctionName("proc", "proc_appendage_alteration")
	appendage.sq_AddFunctionName("onSetHp", "onSetHp_appendage_alteration")
}

function onStart_appendage_alteration(appendage) {
	if (!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
}

function proc_appendage_alteration(appendage) {
	if (!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	//??�ap??????
	switch (parentObj.getState()) {
	case 15:
		if (appendage.getVar().getInt(0) != 2) {
			appendage.getVar().setInt(0, 2);
			appendage.sq_DeleteEffectFront(); //?�?��?��?ani
			appendage.sq_AddEffectFront("character/gunner/effect/animation/alteration/dash/thunder_001_00.ani"); //?��?
			appendage.sq_AddEffectFront("character/gunner/effect/animation/alteration/dash/thunder_002_00.ani"); //?��?
			appendage.sq_AddEffectFront("character/gunner/effect/animation/alteration/dash/thunder_003_00.ani"); //?��?
		}
		local ani = appendage.sq_GetFrontAnimation(0); //?�?�頨????�ni
		local isEnd = sq_IsEnd(ani);
		if (isEnd) {
			sq_Rewind(ani);
		}
		break;
	default:
		if (appendage.getVar().getInt(0) != 1) {
			appendage.getVar().setInt(0, 1);
			appendage.sq_DeleteEffectFront(); //?�?��?��?ani
			appendage.sq_AddEffectFront("character/gunner/effect/animation/alteration/blood/bloodlightning_00.ani"); //?��?
		}
		local ani = appendage.sq_GetFrontAnimation(0); //?�?�頨????�ni
		local isEnd = sq_IsEnd(ani);
		if (isEnd) {
			sq_Rewind(ani);
		}
		break;
	}
	RemoveActiveStatusBleeding(parentObj); //ap?�駁撖寡情?��???�?�?�?�撅?
	//UpdataProperty_alteration(appendage); //ap?�??�??
	setSkillSoften_Assault(appendage);
}

function onSetHp_appendage_alteration(appendage, hp, attacker) {
	if (!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	//??�?????�笆??
	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if (hp <= 10) {
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_ALTERATION, STATE_ASSAULTATTACK, 1, 1.0);
		sq_BinaryStartWrite();
		sq_BinaryWriteDword(SKILL_ALTERATION); //??????賜楊??
		sq_BinaryWriteDword(1); //????�??�餃?
		sq_BinaryWriteDword(attackBonusRate);
		sq_SendCreatePassiveObjectPacket(obj, PASSIVEOBJ_GUNNER_ASSAULT_ID, 0, 0, 0, 0, obj.getDirection());
	}
	return hp;
}

//ap?�駁撖寡情?��???�?�?�?�撅?
function RemoveActiveStatusBleeding(obj) {
	if (!obj) return;
	obj = sq_GetCNRDObjectToSQRCharacter(obj);
	sq_ReleaseActiveStatus(obj, ACTIVESTATUS_BLEEDING);
}

//ap?�??�??
function UpdataProperty_alteration(appendage) {
	local parentObj = appendage.getParent();
	if (!parentObj) {
		appendage.setValid(false);
		return;
	}
	//??�?????�笆?�∪????�???
	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	local skill_level = obj.sq_GetSkillLevel(SKILL_ALTERATION);
	local chrLevel = obj.sq_GetSkillLevel(174);

	//?踹???�???
	local equipmentPhysicalAttack = obj.sq_GetLevelData(SKILL_ALTERATION, 1, skill_level).tofloat();
	equipmentPhysicalAttack = equipmentPhysicalAttack / 100;
	local phyBonus = sq_GetIntData(obj, SKILL_ALTERATION, 4);
	local physicalAttack = sq_GetIntData(obj, SKILL_ALTERATION, 2) + chrLevel * phyBonus;
	local attackSpeed = obj.sq_GetLevelData(SKILL_ALTERATION, 2, skill_level);
	local moveSpeed = obj.sq_GetLevelData(SKILL_ALTERATION, 3, skill_level);

	//?�曄?�AP?�??�??
	local change_appendage = appendage.sq_getChangeStatus("alteration"); //?�?�敶????�?
	if (!change_appendage) {
		change_appendage = appendage.sq_AddChangeStatus("alteration", obj, obj, 0, 0, false, 0); //?�??�?�芸???�??
	}
	if (change_appendage) {
		change_appendage.clearParameter();
		change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, false, attackSpeed.tofloat());
		change_appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED, false, moveSpeed.tofloat());
		if (obj.getWeaponSubType() == 1) {
			
			change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK, true, equipmentPhysicalAttack);
			change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, false, physicalAttack.tofloat());
		}
	}
}

//???��??�?�? 2=sub
ASSAULTGROWSTATETABLE <- {
	[0] = [STATE_SUPPRESS, 1],
	//?�? : ??�
	[1] = [STATE_AIMSHOOT, 1],
	//????�??
	[2] = [STATE_BASHSTOCK, 1],
	//????�箏??
	[3] = [STATE_BURSTBOMB, 1],
	//?�??�遊??
	[4] = [STATE_BODYBUNKER, 1],
	//?�? : ??��??�??
	[5] = [STATE_TRIPLEGUNSHOT, 3],
	//?�???�撕
	[6] = [STATE_MCPICE, 1],
	//????�??
	[7] = [STATE_SCORCHTACTICS, 3],
	//??�啁�?
	[8] = [STATE_DIRECTFEEDBACK, 3],
	//??�噢???
	[9] = [STATE_DYNAMITEKICK, 1],
	//?�? : ?????�腺
	[10] = [STATE_RAYTHEONCIRT, 0] //????�???
}

//?�????質�?
ASSAULTOVERCLOCKSKILLTABLE <- {
	[0] = [SKILL_SUPPRESS, 0, STATE_SUPPRESS],
	//?�? : ??�
	[1] = [SKILL_BODYBUNKER, 0, STATE_BODYBUNKER],
	//?�? : ??��??�??
	[2] = [SKILL_DYNAMITEKICK, 0, STATE_DYNAMITEKICK],
	//?�? : ?????�腺
	[3] = [SKILL_DEATHFIELD, 0, STATE_DEATHFIELD],
	//?�? : ??????
	[4] = [SKILL_EQUALISMR, 0, STATE_EQUALISMR],
	//?�? : ?��????�-MR
	[5] = [SKILL_BREACHINGDOWN, 0, STATE_BREACHINGDOWN] //?�? : ?箸１???
}

function setSkillSoften_Assault(appendage) {
	local parentObj = appendage.getParent();
	if (!parentObj) {
		appendage.setValid(false);
		return;
	}
	//??�?????�笆??
	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/gunner/assault/at_sowalker/ap_at_sowalker.nut")) return;
	for (local i = 0; i < ASSAULTGROWSTATETABLE.len(); i++) {
		local growState = ASSAULTGROWSTATETABLE[i][0];
		local growSubState = ASSAULTGROWSTATETABLE[i][1];
		local state = obj.getState();
		local subState = obj.getSkillSubState();
		//print(growState == state);
		if (state == growState && subState == growSubState) {
			for (local j = 0; j < ASSAULTOVERCLOCKSKILLTABLE.len(); j++) {
				local skillIndex = ASSAULTOVERCLOCKSKILLTABLE[j][0];
				if (skillIndex == SKILL_BREACHINGDOWN) {
					local distance = obj.sq_GetIntData(SKILL_BREACHINGDOWN, 8);
					local haveAttackSign = getRangeObjectAttackSignBoss(obj, distance, "character/gunner/assault/breachingdown/ap_breachingdown.nut");
					if (!haveAttackSign) {
						continue;
					}
				}
				local skill_level = sq_GetSkillLevel(obj, skillIndex);
				if (skill_level > 0 && !sq_GetSkill(obj, skillIndex).isInCoolTime()) {
					obj.setSkillCommandEnable(skillIndex, true);
					if (obj.sq_IsEnterSkill(skillIndex) != -1) {
						local isUse = obj.sq_IsUseSkill(skillIndex);
						if (isUse) {
							RemoveAllFlash(obj);
							local subState = ASSAULTOVERCLOCKSKILLTABLE[j][1];
							local state = ASSAULTOVERCLOCKSKILLTABLE[j][2];
							obj.sq_IntVectClear();
							obj.sq_IntVectPush(subState);
							obj.sq_AddSetStatePacket(state, STATE_PRIORITY_USER, true);
							obj.flushSetStatePacket();
							continue;
						}
					}
				}
			}
		}
	}
}
