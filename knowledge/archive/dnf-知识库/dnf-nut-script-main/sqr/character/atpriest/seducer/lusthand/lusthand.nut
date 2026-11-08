function checkExecutableSkill_Lusthand(obj) {
	if (!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_LUSTHAND);

	if (isUse) {
		obj.getVar("damaLusthand").clear_obj_vector();
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.addSetStatePacket(STATE_LUSTHAND, pIntVec, STATE_PRIORITY_FORCE, false, "");
	}
}

function checkCommandEnable_Lusthand(obj) {

	return true;
}


function onSetState_Lusthand(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
	obj.sq_StopMove();
	switch (state) {
		case 0:
			if (Seducer(obj)) {
				local ani = obj.getVar().GetAnimationMap("Seducer128", "Character/Priest/Seducer/ATAnimation/lusthandatk01_demon.ani");
				obj.setCurrentAnimation(ani);
			}
			else {
				obj.sq_SetCurrentAnimation(CUSTOM_ANI_LUSTHANDATK01_BODY);
			}

			break;
		case 1:

			obj.sq_SetCurrentAnimation(CUSTOM_ANI_LUSTHANDATK02_BODY);
			obj.getVar().clear_vector();
			obj.getVar().push_vector(obj.getXPos());
			obj.getVar().push_vector(obj.getYPos());
			obj.getVar().push_vector(0);
			break;
		case 2:
			if (Seducer(obj)) {
				local ani = obj.getVar().GetAnimationMap("Seducer129", "Character/Priest/Seducer/ATAnimation/lusthandatk03effa_demon.ani");
				obj.setCurrentAnimation(ani);
				
				obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_LUSTHANDSWINGCUT);
				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_LUSTHAND, -1, 1, 1.0);
				obj.sq_SetCurrentAttackBonusRate(attackBonusRate); 
			}
			else {
				obj.sq_SetCurrentAnimation(CUSTOM_ANI_LUSTHANDATK03BODY_BODY);

				obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_LUSTHANDSWINGCUT);

				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_LUSTHAND, -1, 1, 1.0);
				obj.sq_SetCurrentAttackBonusRate(attackBonusRate); 
			}
			break;
		case 3:

			obj.sq_SetCurrentAnimation(CUSTOM_ANI_LUSTHANDEND_BODY);

			break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}


function onProc_Lusthand(obj) {
	if (!obj) return;

	local state = obj.getSkillSubState(); 
	local pAni = obj.sq_GetCurrentAni();
	local currentT = sq_GetCurrentTime(pAni);
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	switch (state) {

		case 1:
			local tar = obj.getVar("damaLusthand").get_obj_vector(0);
			if (tar) {
				local startFrameIndex = 0;
				local endFrameIndex = 5;
				local currentT = sq_GetCurrentTime(pAni);
				if (frmIndex <= startFrameIndex) {} else if (frmIndex >= startFrameIndex && frmIndex <= endFrameIndex) {
					local startX = obj.getVar().get_vector(0);
					local startY = obj.getVar().get_vector(1);
					currentT = currentT - pAni.getDelaySum(0, startFrameIndex);
					local maxT = pAni.getDelaySum(startFrameIndex, endFrameIndex);

					local lastX = sq_GetDistancePos(tar.getXPos(), obj.getDirection(), tar.getObjectHeight() / 2 - 100);
					local lastY = tar.getYPos() + 1;

					if (currentT < maxT && obj.getVar().get_vector(2) == 0) {
						local v = sq_GetAccel(startX, lastX, currentT, 200, true);
						local v2 = sq_GetAccel(startY, lastY, currentT, 200, true);

						if (obj.isMovablePos(v, v2)) {
							sq_setCurrentAxisPos(obj, 0, v);
							sq_setCurrentAxisPos(obj, 1, v2);
						} else {
							obj.getVar().set_vector(2, 1);
						}

					}
				}
			}
			break;
	}
}

function onAttack_Lusthand(obj, damager, boundingBox, isStuck) {
	if (!obj) return;

	local state = obj.getSkillSubState(); 
	switch (state) {
		case 2:
			createAttackCutExp(obj, damager);
			if (CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atpriest/seducer/lusthand/ap_lusthand.nut")) {
				CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atpriest/seducer/lusthand/ap_lusthand.nut");
			}
			break;
	}
}

function onEndState_Lusthand(obj, new_state) {
	if (new_state != STATE_LUSTHAND) {
		local sq_var = obj.getVar("damaLusthand");

		local objectsSize = sq_var.get_obj_vector_size();

		for (local i = 0; i < objectsSize; ++i) {
			local damager = sq_var.get_obj_vector(i);
			if (CNSquirrelAppendage.sq_IsAppendAppendage(damager,
					"character/atpriest/seducer/lusthand/ap_lusthand.nut"))
				CNSquirrelAppendage.sq_RemoveAppendage(damager,
					"character/atpriest/seducer/lusthand/ap_lusthand.nut");
		}
	}
}


function onEndCurrentAni_Lusthand(obj) {
	if (!obj) return;

	local state = obj.getSkillSubState(); 

	switch (state) {
		case 0:
			if (obj.getVar("damaLusthand").get_obj_vector_size() > 0) {
				local pIntVec = sq_GetGlobalIntVector();
				sq_IntVectorClear(pIntVec);
				sq_IntVectorPush(pIntVec, 1);
				obj.addSetStatePacket(STATE_LUSTHAND, pIntVec, STATE_PRIORITY_FORCE, false, "");
			} else {
				obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
			}

			break;
		case 1:

			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 2);
			obj.addSetStatePacket(STATE_LUSTHAND, pIntVec, STATE_PRIORITY_FORCE, false, "");

			break;
		case 2:
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
			break;
		case 3:
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
			break;
	}

}

function onKeyFrameFlag_Lusthand(obj, flagIndex) //����μ��������
{
	if (!obj) return;


	local state = obj.getSkillSubState(); //����������sub state����

	switch (state) {
		case 0:
			if (flagIndex == 0) {

				//`demonization`0	0	138	
			} else if (flagIndex == 1) {
				if (Seducer(obj)) {
					obj.sq_PlaySound("PW_LUSTHAND_DM_03");
				}

				obj.sq_StartWrite();
				obj.sq_WriteDword(0);
				obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(SKILL_LUSTHAND, -1, 0, 1.0));
				obj.sq_WriteDword(sq_GetIntData(obj, SKILL_LUSTHAND, 0));
				obj.sq_SendCreatePassiveObjectPacket(24384, 0, 103, 0, 81);
				//`CreateClaw`103	0	81
			}

			break;
		case 2:
			if (flagIndex == 0) {
				sq_flashScreen(obj, 10, 50, 60, 76, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
			} else if (flagIndex == 1) {
				obj.sq_SetShake(obj, 2, 100);
			} else if (flagIndex == 2) {
				//`demonization end`-6	0	125	
			}
			break;
	}
	return true;
}