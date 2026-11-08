function checkExecutableSkill_SwordGhost16(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_16);

	if (isUse) {
		setSwordGhostEnergyDec(obj, 1);
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_16, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost16(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();

	if (state == STATE_STAND) return true;

	return true;
}

function onSetState_SwordGhost16(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	local sq_var = obj.getVar();

	if (substate == 0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_16_HE_JI_YUE_LIN_ATTACK1);

		obj.sq_SendCreatePassiveObjectPacket(260180, 0, -17, -13, 0);

		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_16_HE_JI_YUE_LIN_ATTACK1); //????ATK????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_16, -1, 0, 1.0 + gaugeValue_rate.tofloat());

		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??

		sq_var.setBool(0, false); //??????????????????????????*

		local dark_range = obj.sq_GetIntData(SKILL_SWORD_GHOST_16, 0); //???????????v

		local count3 = obj.getMyPassiveObjectCount(251338);
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
		if (count3 >= max_gaugeValue) {
			count3 = max_gaugeValue; //????????
		}

		dark_range = count3.tofloat() / 300.0 + dark_range.tofloat() / 100.0; //????j?????????
		local ani = sq_GetCurrentAnimation(obj); //????????????????ANI
		//print( "ski_15:AttackBox:" + dark_range);
		if (ani) {
			sq_var.setBool(0, true); //?????????????????????????*
			sq_var.setFloat(1, dark_range); //??????????????????1?????j???????*
			ani.setAttackBoundingBoxSizeRate(dark_range, false); //???????????????j????*
		}

	}
	else if (substate == 1) {

}

}

function onEndState_SwordGhost16(obj, newState) //??????????? ????????????????????????????????*
{
	if (!obj) return;
	local sq_var = obj.getVar();
	//print( "end_SwordGhost16" + sq_var);
	if (newState != STATE_SWORD_GHOST_16) //??????? ???????? STATE_SWORDMAN3
	{
		local isResized = sq_var.getBool(0); //????????????????GetBool??0??

		if (isResized) //isResized ?????
		{
			local ani = sq_GetCurrentAnimation(obj); //????????????????ANI
			if (ani) //ani ?????
			{
				local dark_range = sq_var.getFloat(1);
				ani.setAttackBoundingBoxSizeRate(1.0 / dark_range, false);
			}
		}
	}

}

function onEndCurrentAni_SwordGhost16(obj) {
	local substate = obj.getSkillSubState();
	if (substate == 0) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	else if (substate == 1) {

}

}

function onAttack_SwordGhost16(obj, damager, boundingBox, isStuck) {
	if (!obj) return false;

	local skillLevel = obj.sq_GetSkillLevel(123); //

	if (skillLevel > 0) {
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
		//sq_EffectLayerAppendage(damager,sq_RGB(255,255,255),150,0,0,240);//???????????????G

		local count1 = obj.getMyPassiveObjectCount(251338); //BUFF???
		local count2 = obj.getMyPassiveObjectCount(250334); //????????BUFF????

		if (count1 <= max_gaugeValue) {
			if (count2 <= 5) {
				local rand = sq_getRandom(-50, 50);
				local objindex = setSwordGhost4State(obj); //??????????????????o?????????????
				sq_SendCreatePassiveObjectPacketPos(obj, objindex, 0, damager.getXPos() + rand, damager.getYPos() + rand, damager.getZPos() + damager.getObjectHeight() / 2);
			}
		}
		//print( "ski_15:buff_count1:" + count1);
	}

}

function onKeyFrameFlag_SwordGhost16(obj, flagIndex) {
	if (!obj) return false;

	if (flagIndex == 1) {
		//obj.sq_SetShake(obj,15,100);//?????

		local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_16, 0); //???????????v

		local count2 = obj.getMyPassiveObjectCount(251338);
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
		if (count2 >= max_gaugeValue) {
			count2 = max_gaugeValue; //????????
		}
		local size = count2.tofloat() / 300.0 + sizeRate.tofloat() / 100.0; //????j?????????
		//print( "ski_15:size:" + size);
		local animation = obj.sq_CreateCNRDAnimation("effect/animation/moonspiritslash/moonspiritslashaeffect_00.ani"); //???????
		animation.setImageRateFromOriginal(size, size); //????j??
		animation.setAutoLayerWorkAnimationAddSizeRate(size); //???????h
		obj.sq_AddStateLayerAnimation(1, animation, 0, -1); //?????????
	}

	return true;
}

function onProc_SwordGhost16(obj) {
	if (!obj) return;
	setSwordGhost28Effect(obj);
}