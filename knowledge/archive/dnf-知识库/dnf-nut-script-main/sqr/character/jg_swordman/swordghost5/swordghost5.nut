function checkExecutableSkill_SwordGhost5(obj) {
	if (!obj) return false;
	local count = obj.getMyPassiveObjectCount(260149);
	local count_D = obj.getMyPassiveObjectCount(260150);

	if (count == 0) {
		local b_useskill = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_5);

		if (b_useskill) {
			setSwordGhostEnergyDec(obj, 1);
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_5, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}
	}

	else if (count > 0 && count_D == 0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_5, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost5(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();

	if (state == STATE_STAND) return true;

	return true;
}

function onSetState_SwordGhost5(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);

	if (substate == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_5_HE_JI_ONE_ATTACK_B);
		obj.sq_SendCreatePassiveObjectPacket(260149, 0, 45, 1, 0);
		obj.sq_SendCreatePassiveObjectPacket(261153, 0, 0, 1, 0);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_5_HE_JI_ONE_ATTACK2); //????ATK????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_5, -1, 0, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??
	}
	else if (substate == 1) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_5_HE_JI_ONE_ATTACK_B);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_5_HE_JI_ONE_ATTACK2); //????ATK????

		obj.sq_SendCreatePassiveObjectPacket(261153, 0, 0, 1, 0);

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_5, -1, 0, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??

	}
	else if (substate == 2) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_5_HE_JI_ONE_END);
	}
	else if (substate == 3) {

		local direction = sq_GetDirection(obj); //????????????V

		if (direction == ENUM_DIRECTION_LEFT) {
			obj.sq_SetDirection(ENUM_DIRECTION_RIGHT);
		}
		else if (direction == ENUM_DIRECTION_RIGHT) {
			obj.sq_SetDirection(ENUM_DIRECTION_LEFT);
		}
		obj.sq_SendCreatePassiveObjectPacket(262168, 0, 40, 1, 0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_5_HE_JI_ONE_ATTACK_B);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_5_HE_JI_ONE_ATTACK2); //????ATK????
		obj.sq_SendCreatePassiveObjectPacket(261153, 0, 0, 1, 0);
		local gaugeValue_rate = setSwordGhost3State(obj);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_5, -1, 0, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??
	}
	else if (substate == 4) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_5_HE_JI_ONE_END);
	}
}

function onKeyFrameFlag_SwordGhost5(obj, flagIndex) {
	if (!obj) return false;

	if (flagIndex == 120) {
		obj.sq_SetStaticMoveInfo(0, 5500, 100, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
		obj.sq_SendCreatePassiveObjectPacket(260150, 0, 0, 1, 0);
	}
	if (flagIndex == 121) {
		obj.sq_SetStaticMoveInfo(0, 0, 0, false);
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 10.0, 10.0); //????????????t?????
		obj.sq_SendCreatePassiveObjectPacket(261152, 0, -50, 1, 0);

		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_5_HE_JI_ONE_ATTACK3); //????ATK????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_5, -1, 1, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??

	}
	//if (flagIndex == 1)
	//{
	//obj.sq_SetShake(obj,3,80);//?????
	//}
	//if (flagIndex == 2)
	//{
	//obj.sq_SetShake(obj,8,160);//?????
	//sq_flashScreen(obj, 80, 30, 50, 130, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);//?????
	//}

	return true;
}

function onEndCurrentAni_SwordGhost5(obj) {
	local substate = obj.getSkillSubState();

	if (substate == 0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_5, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 1) {

		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_5, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 2) {
		local count1 = obj.getMyPassiveObjectCount(251338); //BUFF???
		local Attak_Ex = obj.sq_GetIntData(SKILL_SWORD_GHOST_4, 5); //???????????????
		//print( "Attak_Ex:" + Attak_Ex);
		if (count1 >= Attak_Ex) {
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(3);
			obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_5, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		if (count1 < Attak_Ex) {
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		}
	}
	else if (substate == 3) {

		obj.sq_IntVectClear();
		obj.sq_IntVectPush(4);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_5, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 4) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}

}

function onAttack_SwordGhost5(obj, damager, boundingBox, isStuck) {
	if (!obj) return false;

	sq_EffectLayerAppendage(damager, sq_RGB(255, 255, 255), 150, 0, 0, 240); //???????????????G

	local skillLevel = obj.sq_GetSkillLevel(123); //

	if (skillLevel > 0) {
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);

		local count1 = obj.getMyPassiveObjectCount(251338); //BUFF???
		local count2 = obj.getMyPassiveObjectCount(250334); //????????BUFF????

		if (count1 <= max_gaugeValue) {
			if (count2 <= 5) {
				local rand = sq_getRandom(-50, 50);
				local objindex = setSwordGhost4State(obj); //??????????????????o?????????????
				sq_SendCreatePassiveObjectPacketPos(obj, objindex, 0, damager.getXPos() + rand, damager.getYPos() + rand, damager.getZPos() + damager.getObjectHeight() / 2);
			}
		}
		//print( "ski_5:buff_count1:" + count1);
	}

}

function onProc_SwordGhost5(obj) {
	if (!obj) return;
	setSwordGhost28Effect(obj);
}