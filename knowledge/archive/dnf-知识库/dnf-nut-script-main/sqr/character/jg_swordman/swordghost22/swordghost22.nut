function checkExecutableSkill_SwordGhost22(obj) {
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_22);

	if (isUse) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_22, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}

	return false;
}

function checkCommandEnable_SwordGhost22(obj) {
	if (!obj) return false;
	local state = obj.sq_GetState();

	if (state == STATE_STAND) return true;

	return true;
}

function onSetState_SwordGhost22(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);

	if (substate == 0) {

		obj.sq_SendCreatePassiveObjectPacket(260204, 0, 0, 0, 0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_22_ER_JUE_START);
		obj.sq_SendCreatePassiveObjectPacket(260200, 0, -35, -5, 0);

		local activeObject = getBossTargetSwordMan4(obj);
		if (activeObject && obj.isEnemy(activeObject) && activeObject.isObjectType(OBJECTTYPE_ACTIVE) && activeObject.isInDamagableState(obj)) {
			local id = sq_GetObjectId(activeObject);
			local activeObject_xPos = activeObject.getXPos();
			local activeObject_yPos = activeObject.getYPos();
			local activeObject_zPos = activeObject.getZPos();

			obj.getVar().clear_vector();
			obj.getVar().push_vector(activeObject_xPos);
			obj.getVar().push_vector(activeObject_yPos);
			obj.getVar().push_vector(activeObject_zPos);
			obj.getVar().push_vector(id);

			local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(activeObject, obj, STATE_SWORD_GHOST_22, false, "character/JG_SwordMan/swordghost22/ap_erjue.nut", true);
			masterAppendage.sq_SetValidTime(4000);
			if (masterAppendage) {
				if(sq_IsInScreenCollisionObject(activeObject, true)){
					sq_HoldAndDelayDie(activeObject, obj, true, true, true, 1, 1, ENUM_DIRECTION_NEUTRAL, masterAppendage);
				}
			}
		}else{
			obj.getVar().clear_vector();
			obj.getVar().push_vector(obj.getXPos());
			obj.getVar().push_vector(obj.getYPos());
			obj.getVar().push_vector(obj.getZPos());
		}

	}
	else if (substate == 1) {

		local xPos = obj.getVar().get_vector(0);
		local yPos = obj.getVar().get_vector(1);
		local zPos = obj.getVar().get_vector(2);

		//print("xPos " + xPos);
		//print("yPos " + yPos);
		//print("zPos " + zPos);

		local activeObject = getBossTargetSwordMan4(obj);
		//print("substate_activeObject " + activeObject);
		if (activeObject && obj.isEnemy(activeObject) && activeObject.isObjectType(OBJECTTYPE_ACTIVE)) {
			
			if (!obj.isMovablePos(xPos, yPos)) {
				sq_SetCurrentPos(obj, xPos - 10, yPos, 0);
			}
		}

		obj.sq_SendCreatePassiveObjectPacket(260203, 0, 0, -1, 0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_22_ER_JUE_ATTACK);
	}

}

function onEndCurrentAni_SwordGhost22(obj) {
	local substate = obj.getSkillSubState();
	if (substate == 0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_22, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if (substate == 1) {

		local activeObject = getBossTargetSwordMan4(obj);

		//print("onEnd activeObject " + activeObject);
		if (activeObject != null) {
			//sq_SendCreatePassiveObjectPacketPos(obj, 261166, 0, activeObject.getXPos(), activeObject.getYPos(), activeObject.getZPos());
			CNSquirrelAppendage.sq_RemoveAppendage(activeObject, "character/JG_SwordMan/swordghost22/ap_erjue.nut");
		}

		local direction = sq_GetDirection(obj); //????????????V

		if (direction == ENUM_DIRECTION_LEFT) {
			obj.sq_SetDirection(ENUM_DIRECTION_RIGHT);
			sq_SetCurrentPos(obj, obj.getXPos() + 140, obj.getYPos(), obj.getZPos());
		}
		else if (direction == ENUM_DIRECTION_RIGHT) {
			obj.sq_SetDirection(ENUM_DIRECTION_LEFT);
			sq_SetCurrentPos(obj, obj.getXPos() - 140, obj.getYPos(), obj.getZPos());
		}
		local posX = obj.getXPos();
		local posY = obj.getYPos();
		local posZ = obj.getZPos();
		if (!obj.isMovablePos(posX, posY)) {
			sq_MoveToNearMovablePos(obj, posX, posY, 0, posX, posY, posZ, 200, -1, 3);
		}

		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);

	}

}

function onAttack_SwordGhost22(obj, damager, boundingBox, isStuck) {
	if (!obj) return false;

	obj.sq_setCustomHitEffectFileName("character/swordman/effect/animation/swordghost/hit_effect/hit_0_0.ani");

	local skillLevel = obj.sq_GetSkillLevel(123);

	if (skillLevel > 0) {
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
		sq_EffectLayerAppendage(damager, sq_RGB(255, 255, 255), 150, 300, 150, 500); //???????????????G

		local count1 = obj.getMyPassiveObjectCount(251338); //BUFF???
		local count2 = obj.getMyPassiveObjectCount(250334); //????????BUFF????

		if (count1 <= max_gaugeValue) {
			if (count2 <= 5) {
				local rand = sq_getRandom(-50, 50);
				local objindex = setSwordGhost4State(obj); //??????????????????o?????????????
				sq_SendCreatePassiveObjectPacketPos(obj, objindex, 0, damager.getXPos() + rand, damager.getYPos() + rand, damager.getZPos() + damager.getObjectHeight() / 2);
			}
		}
		//print( "ski_22:buff_count1:" + count1);
	}

}

function onKeyFrameFlag_SwordGhost22(obj, flagIndex) {
	if (!obj) return false;

	//if (flagIndex == 1)
	//{
	//}
	//if (flagIndex == 2)
	//{
	//sq_flashScreen(obj, 400, 2000, 800, 255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);//?????
	//}
	if (flagIndex == 3) {
		//sq_flashScreen(obj, 10, 30, 10, 180, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);//?????

		//obj.sq_SetShake(obj,20,200);//?????

		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_22_ER_JUE_ATTACK1); //????ATK????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_22, -1, 0, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??

	}
	if (flagIndex == 4) {

		//sq_flashScreen(obj, 10, 30, 10, 180, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);//?????

		//obj.sq_SetShake(obj,15,300);//?????

		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_22_ER_JUE_ATTACK2); //????ATK????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_22, -1, 1, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??

	}
	if (flagIndex == 5) {

		//sq_flashScreen(obj, 10, 30, 10, 180, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);//?????

		//obj.sq_SetShake(obj,15,300);//?????

		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_22_ER_JUE_ATTACK3); //????ATK????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_22, -1, 2, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??
	}
	if (flagIndex == 6) {

		//sq_flashScreen(obj, 10, 80, 10, 180, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);//?????

		//obj.sq_SetShake(obj,28,290);//?????

		obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_22_ER_JUE_ATTACK1); //????ATK????

		local gaugeValue_rate = setSwordGhost3State(obj);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_22, -1, 3, 1.0 + gaugeValue_rate.tofloat());
		obj.sq_SetCurrentAttackBonusRate(damage); //??????SKL??????v??
		setSwordGhostEnergy(obj, 0);
	}
	if (flagIndex == 7) {
		obj.sq_SendCreatePassiveObjectPacket(260201, 0, 149, 0, 0);
	}
	if (flagIndex == 8) {

		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
		local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);
		sq_SendCreatePassiveObjectPacketPos(obj, 260202, 0, xPos, yPos + 110, 0);

	}
	return true;
}