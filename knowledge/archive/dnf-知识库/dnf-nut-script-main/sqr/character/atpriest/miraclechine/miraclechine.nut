SUB_STATE_ATMIRACLECHINE_0 <- 0
SUB_STATE_ATMIRACLECHINE_1 <- 1
SUB_STATE_ATMIRACLECHINE_2 <- 2
SUB_STATE_ATMIRACLECHINE_3 <- 3
SUB_STATE_ATMIRACLECHINE_4 <- 4

SKL_MC_SD_0 <- 0
SKL_MC_SD_1 <- 1
SKL_MC_SD_2 <- 2
SKL_MC_SD_3 <- 3
SKL_MC_SD_4 <- 4

SKL_MC_LI_0 <- 0
SKL_MC_LI_1 <- 1
SKL_MC_LI_2 <- 2
SKL_MC_LI_3 <- 3
SKL_MC_LI_4 <- 4

function checkExecutableSkill_miraclechine(obj) {
	if (!obj) return false;
	local b_useskill = obj.sq_IsUseSkill(SKILL_MIRACLE_CHINE);
	if (b_useskill) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(SUB_STATE_ATMIRACLECHINE_0); 
		obj.sq_AddSetStatePacket(STATE_MIRACLE_CHINE, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_miraclechine(obj) {
	if (!obj) return false;
	return true;
}

function onSetState_Miraclechine(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();

	local posX = obj.getXPos();
	local posY = obj.getYPos();
	local posZ = obj.getZPos();

	obj.getVar().clear_vector();
	obj.getVar().push_vector(0);
	local attack_time = obj.sq_GetIntData(SKILL_MIRACLE_CHINE, 0);
	if (substate == SUB_STATE_ATMIRACLECHINE_0) {
		obj.sq_SetCurrentAnimationThrow(2);
		obj.sq_PlaySound("R_PW_MIRACLESHINE");
		sq_AddDrawOnlyAniFromParent(obj, "character/priest/effect/animation/atmiracleshine/miracleshine01_01.ani", 0, 0, 0);
		obj.sq_PlaySound("MIRACLESHINE_CAST");
	} else if (substate == SUB_STATE_ATMIRACLECHINE_2) {
		obj.sq_SetCurrentAnimationShoot(2);
		if (obj.isMyControlObject()) {
			local link_num = obj.sq_GetIntData(SKILL_MIRACLE_CHINE, 10);
			local firstTargetYRange = obj.sq_GetIntData(SKILL_MIRACLE_CHINE, 1);
			//local firstTargetXStartRange = obj.sq_GetIntData(SKILL_MIRACLE_CHINE, 2);
			local firstTargetXStartRange = 0;
			local firstTargetXEndRange = obj.sq_GetIntData(SKILL_MIRACLE_CHINE, 3);
			firstTargetXEndRange = 650;
			local nextTargetRange = obj.sq_GetIntData(SKILL_MIRACLE_CHINE, 1);
			local targetMaxHeight = obj.sq_GetIntData(SKILL_MIRACLE_CHINE, 2)*2;
			local multi_hit_num = obj.sq_GetIntData(SKILL_MIRACLE_CHINE, 9);
			local firstAttackRate = obj.sq_GetPowerWithPassive(SKILL_MIRACLE_CHINE, STATE_MIRACLE_CHINE, 1, -1, 1.0);

			sq_BinaryStartWrite();
			sq_BinaryWriteDword(60);
			sq_BinaryWriteWord(firstTargetYRange);
			sq_BinaryWriteWord(firstTargetXStartRange);
			sq_BinaryWriteWord(firstTargetXEndRange);
			sq_BinaryWriteWord(nextTargetRange);
			sq_BinaryWriteWord(targetMaxHeight);

			sq_BinaryWriteWord(link_num);
			sq_BinaryWriteWord(attack_time);
			sq_BinaryWriteDword(firstAttackRate);
			sq_BinaryWriteWord(multi_hit_num);

			local distanceL = 50;
			local h = 95;
			obj.sq_SendCreatePassiveObjectPacket(24240, 0, distanceL, 0, h);
			sq_AddDrawOnlyAniFromParent(obj, "character/priest/effect/animation/atmiracleshine/castsuccess_05.ani", 0, 0, 0);
			//obj.sq_PlaySound("CHAINLIGHT_ELEC_LOOP", 7576);
		}
	}
	obj.sq_SetSuperArmorUntilTime(obj, attack_time);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onProc_Miraclechine(obj) {

	if (!obj) return;

	local substate = obj.getSkillSubState();

	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	local currentT = sq_GetCurrentTime(pAni);

	if (substate == SUB_STATE_ATMIRACLECHINE_0) {

	} else if (substate == SUB_STATE_ATMIRACLECHINE_2) {

		if (obj.isMyControlObject()) {

			local attack_time = obj.sq_GetIntData(SKILL_MIRACLE_CHINE, 0);
			local passiveobj_cl = null;
			local myPObjCount = obj.getMyPassiveObjectCount(24240);
			if (myPObjCount > 0) {
				for (local i = 0; i < myPObjCount; i++) {
					local myPassiveObj = obj.getMyPassiveObject(24240, i);
					if (!myPassiveObj)
						continue;
					if (myPassiveObj.getVar("id").get_vector(0) == 60) {
						local passiveobj_cl = myPassiveObj;
					}
				}
			}
			if (passiveobj_cl) {
				local flag = passiveobj_cl.getVar("nograb").get_vector(0);
				if (flag) {
					obj.sq_IntVectClear();
					obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
					return;
				} else {
					if (obj.getVar().get_vector(0) == 0) {
						obj.sq_SetShake(obj, 1, attack_time);
						obj.getVar().set_vector(0, 1);
					}
				}
			}
			if (currentT > attack_time) {
				obj.sq_IntVectClear();
				obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
			}
		}
	}

}

function onEndCurrentAni_Miraclechine(obj) {
	if (!obj) return;

	local substate = obj.getSkillSubState();

	if (substate == SUB_STATE_ATMIRACLECHINE_0) {
		if (obj.isMyControlObject()) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(SUB_STATE_ATMIRACLECHINE_2);
			obj.sq_AddSetStatePacket(STATE_MIRACLE_CHINE, STATE_PRIORITY_USER, true);
		}
	} else if (substate == SUB_STATE_ATMIRACLECHINE_2) {
		if (obj.isMyControlObject()) {
			//obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		}
	}
}

function onKeyFrameFlag_Miraclechine(obj, flagIndex) {

	if (!obj) return false;

	local substate = obj.getSkillSubState();

	if (substate == SUB_STATE_ATMIRACLECHINE_0) {

	} else if (substate == SUB_STATE_ATMIRACLECHINE_2) {

	}

	return false;

}

function onEndState_Miraclechine(obj, new_state) {

	if (!obj) return;

	local substate = obj.getSkillSubState();

	if (substate == SUB_STATE_ATMIRACLECHINE_0) {

	} else if (substate == SUB_STATE_ATMIRACLECHINE_2) {

	}
	//obj.stopSound(7576);

}
