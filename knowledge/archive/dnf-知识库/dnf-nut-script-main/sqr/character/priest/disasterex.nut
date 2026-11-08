
S_DISASTER_0 <- 0
S_DISASTER_1 <- 1
S_DISASTER_2 <- 2
S_DISASTER_3 <- 3
S_DISASTER_4 <- 4

SD_I_DAMAGE_INC <- 0
SD_I_AWAKENING_INC <- 1
SD_I_TARGET_TIME <- 2
SD_I_TARGET_MOV_X <- 3
SD_I_TARGET_MOV_Y <- 4
SD_I_TARGET_SUCK_LEN <- 5
SD_I_TARGET_SUCK_VEL <- 6

function checkExecutableSkill_DisasterEx(obj) {
	if (!obj) return false;
	local b_useskill = obj.sq_IsUseSkill(134);
	if (b_useskill) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_IntVectPush(obj.getDirection());
		obj.sq_addSetStatePacket(74, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
};

function checkCommandEnable_DisasterEx(obj) {
	if (!obj) return false;

	local state = obj.sq_GetSTATE();

	if (state == STATE_ATTACK) {
		return obj.sq_IsCommandEnable(134);
	}

	return true;
};

function onSetState_DisasterEx(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local sq_var = obj.getVar();
	local substate = obj.sq_getVectorData(datas, 0);
	local direction = obj.sq_getVectorData(datas, 1);
	obj.setSkillSubState(substate);
	obj.sq_stopMove();

	sq_var.clear_vector();
	sq_var.push_vector(0);
	sq_var.push_vector(0);
	sq_var.push_vector(0);

	local posX = obj.getXPos();
	local posY = obj.getYPos();
	local posZ = obj.getZPos();

	obj.sq_setCurrentAttackInfo(95);

	local attack_rate = 1.0;

	if (isAvengerAwakenning(obj)) {
		local inc = obj.sq_getIntData(134, 0);
		local inc_rate = inc.tofloat() / 100.0;
		attack_rate += inc_rate;
	}

	obj.stopSound(7575);
	obj.sq_setAttackPowerWithPassive(134, state, -1, 0, attack_rate);

	if (substate == 0) {
		if (isAvengerAwakenning(obj)) {
			local ani = obj.getVar().GetAnimationMap("Disaster1", "Character/Priest/Animation/disasterEx/Disaster1.ani");
			obj.setCurrentAnimation(ani);
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 119, false, "Appendage/Character/ap_avenger_awakening.nut", false);
			if (appendage) {
				local skill_level = obj.sq_getSkillLevel(119);
				local time = sq_GetLevelData(obj, 119, 0, skill_level);
				local awakening_inc_t = obj.sq_getIntData(134, 1);
				appendage.sq_var.set_vector(0, time + awakening_inc_t);
				appendage.sq_SetValidTime(time + awakening_inc_t);
			}
		}
		else {
			obj.sq_setCurrentAnimation(117);
		}
		local pAni = obj.sq_getCurrentAni();
		obj.sq_setStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); 
	}
	else if (substate == 1) {
		obj.sq_setShake(obj, 3, 160);

		if (isAvengerAwakenning(obj)) {

			local ani = obj.getVar().GetAnimationMap("Disaster2", "Character/Priest/Animation/disasterEx/Disaster2.ani");
			obj.setCurrentAnimation(ani);
		}
		else {
			obj.sq_setCurrentAnimation(118);
		}

		local pA = obj.sq_getCurrentAni();

		local iX = posX;
		local iY = posY;

		local vX = obj.sq_getIntData(134, 3);
		local vY = obj.sq_getIntData(134, 4);
		obj.sq_addAttractAimPointMark(iX, iY, vX, vY);

		local range = obj.sq_getIntData(134, 5);
		local suck_vel = obj.sq_getIntData(134, 6);
		obj.sq_setAttractAimInfo(suck_vel, suck_vel, range / 2, 180);

	}
	else if (substate == 2) {

		obj.sq_setCurrentAttackInfo(95);

		if (isAvengerAwakenning(obj)) {

			local ani = obj.getVar().GetAnimationMap("Disaster3", "Character/Priest/Animation/disasterEx/Disaster3.ani");
			obj.setCurrentAnimation(ani);
		}
		else {
			local ani = obj.getVar().GetAnimationMap("Disaster3", "Character/priest/animation/disaster3.ani");
			obj.setCurrentAnimation(ani);
		}
		obj.sq_PlaySound("DISASTER_CIRCLE_LOOP", 7575);
	}
	else if (substate == 3) {

		if (isAvengerAwakenning(obj)) {

			local ani = obj.getVar().GetAnimationMap("Disaster4", "Character/Priest/Animation/disasterEx/Disaster4.ani");
			obj.setCurrentAnimation(ani);
		}
		else {
			local ani = obj.getVar().GetAnimationMap("Disaster4", "Character/priest/animation/Disaster4.ani");
			obj.setCurrentAnimation(ani);
		}
	}
	else if (substate == 4) {
		if (isAvengerAwakenning(obj)) {

			local ani = obj.getVar().GetAnimationMap("Disaster5", "Character/Priest/Animation/disasterEx/Disaster5.ani");
			obj.setCurrentAnimation(ani);
		}
		else {
			obj.sq_setCurrentAnimation(121);
		}
	}
};

function onProc_DisasterEx(obj) {
	if (!obj) return;

	local substate = obj.getSkillSubState();

	local posX = obj.getXPos();
	local posY = obj.getYPos();
	local posZ = obj.getZPos();

	local sq_var = obj.getVar();
	local pAni = obj.sq_getCurrentAni();
	local frmIndex = obj.sq_ani_GetCurrentFrameIndex(pAni);
	local currentT = sq_GetCurrentTime(pAni);

	if (substate == 1) {
		if (frmIndex >= 0) {
			local flag = sq_var.get_vector(0);
			if (!flag) {
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 134, true, "Appendage/Character/ap_avenger_effect.nut", true);
				sq_var.set_vector(0, 1);
			}
		}

	}
	else if (substate == 2) {
		local stateTimer = obj.sq_getStateTimer();

		local time = obj.sq_getIntData(134, 2);

		if (stateTimer > (time - 750)) {
			local flag = sq_var.get_vector(1);
			if (!flag) {
				local iX = obj.getXPos();
				local iY = obj.getYPos();
				local iPX = obj.sq_getAttractAimPosX(iX, iY, false);
				local iPY = obj.sq_getAttractAimPosY(iX, iY, false) + 2;

				sq_MoveToNearMovablePos(obj, iPX, iPY, 0, iX, iY, posZ, 200, -1, 3);
				obj.sq_removeAttractAimPointMark();
				sq_var.set_vector(1, 1);
			}
		}

		if (stateTimer > time) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(3);
			obj.sq_IntVectPush(obj.getDirection());
			obj.sq_addSetStatePacket(74, STATE_PRIORITY_IGNORE_FORCE, true);
		}

	}
	else if (substate == 3) {
		if (frmIndex >= 5) {
			local flag = sq_var.get_vector(0);
			if (!flag) {

				local attack_rate = 1.0;
				if (isAvengerAwakenning(obj)) {
					local inc = obj.sq_getIntData(134, 0);
					local inc_rate = inc.tofloat() / 100.0;
					attack_rate += inc_rate;
				}

				local bonus_rate = obj.sq_getBonusRateWithPassive(134, 74, 1, attack_rate);

				obj.sq_binaryData_startWrite();
				obj.sq_binaryData_writeDword(bonus_rate);
				obj.sq_p00_sendCreatePassiveObjectPacket(24109, 0, 0, 0, 0);

				if (isAvengerAwakenning(obj)) {

					local particleCreater = sq_var.GetparticleCreaterMap("GuillotineSub6", "Character/Priest/Effect/Particle/DisasterStonsSmall.ptl", obj);
					particleCreater.Restart(0);

					particleCreater.SetPos(posX, posY, posZ);
					sq_AddParticleObject(obj, particleCreater);

					obj.sq_PlaySound("PR_DGUARDIAN_DISASTER");
				}
				else {
					obj.sq_PlaySound("PR_DISASTER");
				}

				local fScreen = sq_flashScreen(obj, 0, 320, 320, 200, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				obj.sq_setShake(obj, 6, 320);
				obj.sq_removeAttractAimPointMark();
				sq_var.set_vector(0, 1);
			}
		}

	}

	if (substate == 4) {
		if (frmIndex >= 4) {
			local flag = sq_var.get_vector(0);
			if (!flag) {
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 134, true, "Appendage/Character/ap_avenger_effect.nut", true);
				sq_var.set_vector(0, 1);
			}
		}
	}

};

function onProcCon_DisasterEx(obj) {
	if (!obj) return;
	local pAni = obj.sq_getCurrentAni();
	local bEnd = obj.sq_ani_IsEnd(pAni);
	local frmIndex = obj.sq_ani_GetCurrentFrameIndex(pAni);
	local sq_var = obj.getVar();

	local subState = obj.getSkillSubState();

	if (bEnd) {
		if (subState == 0) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_IntVectPush(obj.getDirection());
			obj.sq_addSetStatePacket(74, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		else if (subState == 1) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(2);
			obj.sq_IntVectPush(obj.getDirection());
			obj.sq_addSetStatePacket(74, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		else if (subState == 3) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(4);
			obj.sq_IntVectPush(obj.getDirection());
			obj.sq_addSetStatePacket(74, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		else if (subState == 4) {
			obj.sq_addSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		}
	}
};

function onEndState_DisasterEx(obj, new_state) {
	if (!obj) return;
	if (new_state != 74) {
		obj.sq_removeAttractAimPointMark();
	}
	obj.stopSound(7575);
};


function getScrollBasisPos_DisasterEx(obj) {
	if (!obj) return;

	local substate = obj.getSkillSubState();
	if (substate == 2 || substate == 1) {
		local iX = obj.getXPos();
		local iY = obj.getYPos();
		local iPX = obj.sq_getAttractAimPosX(iX, iY, false);
		local iPY = obj.sq_getAttractAimPosY(iX, iY, false);
		obj.sq_SetCameraScrollPosition(iPX, iPY, 0);
		return true;
	}

	return false;
};