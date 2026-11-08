function checkExecutableSkill_SwordGhost14(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_14);

	if (isUse) {
		setSwordGhostEnergyDec(obj, 1);
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_14, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost14(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();

	if (state == STATE_STAND) return true;

	return true;
}

function onSetState_SwordGhost14(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);

	if (substate == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_14_NAI_LUO_ATTACK);

		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_14_NAI_LUO_ATTACK); //????ATK????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_14, -1, 2, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	}
	else if (substate == 1) {

}

}

function onEndCurrentAni_SwordGhost14(obj) {
	local substate = obj.getSkillSubState();
	if (substate == 0) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	else if (substate == 1) {

}

}

function onAttack_SwordGhost14(obj, damager, boundingBox, isStuck) {
	if (!obj) return false;

	local skillLevel = obj.sq_GetSkillLevel(123); //

	if (skillLevel > 0) {
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
		sq_EffectLayerAppendage(damager, sq_RGB(255, 255, 255), 150, 0, 0, 240); //???????????????G

		local count1 = obj.getMyPassiveObjectCount(251338); //BUFF???
		local count2 = obj.getMyPassiveObjectCount(250334); //????????BUFF????

		if (count1 <= max_gaugeValue) {
			if (count2 <= 5) {
				local rand = sq_getRandom(-50, 50);
				local objindex = setSwordGhost4State(obj); //??????????????????o?????????????
				sq_SendCreatePassiveObjectPacketPos(obj, 250334, 0, damager.getXPos() + rand, damager.getYPos() + rand, damager.getZPos() + damager.getObjectHeight() / 2);
			}
		}
		//print( "ski_15:buff_count1:" + count1);
	}

}

function onKeyFrameFlag_SwordGhost14(obj, flagIndex) {
	if (!obj) return false;

	if (flagIndex == 1) {
		//obj.sq_SetShake(obj,1,500);//?????
		obj.sq_SendCreatePassiveObjectPacket(260198, 0, -230, 5, 0);
	}
	if (flagIndex == 2) {
		//obj.sq_SetShake(obj,8,100);//?????
		obj.sq_SendCreatePassiveObjectPacket(260199, 0, 200, 1, 0);
		obj.sq_SendCreatePassiveObjectPacket(260197, 0, 288, -1, 0);
	}
	//if (flagIndex == 3)
	//{
	//obj.sq_SetShake(obj,25,204);//?????
	//sq_flashScreen(obj, 0, 0, 400, 153, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_CLOSEBACK);//?????
	//}

	return true;
}

function onProc_SwordGhost14(obj) {
	if (!obj) return;
	setSwordGhost28Effect(obj);
}