function checkExecutableSkill_FlowerOfPurification(obj) {
	if (!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_FLOWEROFPURIFICATION);

	if (isUse) {
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.addSetStatePacket(STATE_FLOWEROFPURIFICATION, pIntVec, STATE_PRIORITY_FORCE, false, "");
	}
}

function checkCommandEnable_FlowerOfPurification(obj) {

	return true;
}



function onSetState_FlowerOfPurification(obj, state, datas, isResetTimer) {
	if (!obj) return;
	obj.sq_StopMove();
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
	switch (state) {
		case 0:
			obj.getVar("damaFlowerOfPurification").clear_obj_vector();
			obj.getVar("FlowerOfPurificationobj").clear_obj_vector();
			sq_StartDrawCastGauge(obj, sq_GetCastTime(obj, SKILL_FLOWEROFPURIFICATION, sq_GetSkillLevel(obj, SKILL_FLOWEROFPURIFICATION)), true);
			local ani = obj.getVar().GetAnimationMap("Seducer176", "Character/Priest/Seducer/ATAnimation/delightflower_castbody.ani");
			obj.setCurrentAnimation(ani);
			
			setFlowerOfPurificationattack(obj)
			obj.sq_PlaySound("PW_DSEVENSINS_DM_01");
			if (obj.isMyControlObject()) {
				creatdepravitysevensins(obj, 380, 400,
					"character/priest/seducer/effect/animation/atdepravitysevensins/delightflower_castblack.ani", ENUM_DRAWLAYER_BOTTOM)
				creatdepravitysevensins(obj, 400, 400,
					"character/priest/seducer/effect/animation/atdepravitysevensins/delightflower_castback02.ani", ENUM_DRAWLAYER_BOTTOM)
			}

			local tar = obj.getVar("damaFlowerOfPurification").get_obj_vector(0);
			if (tar) {
				obj.sq_StartWrite();
				obj.sq_WriteDword(9);
				obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(SKILL_FLOWEROFPURIFICATION, -1, 0, 1.0));
				sq_SendCreatePassiveObjectPacketPos(obj, 24384, 0, tar.getXPos(), tar.getYPos() + 1, tar.getZPos() + tar.getObjectHeight() / 2);
			}

			obj.getVar("guanjian").clear_vector();
			obj.getVar("guanjian").push_vector(0);
			
			local skillLevel = obj.sq_GetSkillLevel(SKILL_DEPRAVITYSEVENSINS);
			local buff = sq_GetLevelData(obj, SKILL_DEPRAVITYSEVENSINS, 3, skillLevel);
			local time = obj.sq_GetIntData(SKILL_DEPRAVITYSEVENSINS, 0);
			if(buff > 0)
			{
				local coolbonus  = buff.tofloat();
				coolbonus  = coolbonus / 100;
				
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_FLOWEROFPURIFICATION, false, "character/atpriest/seducer/flowerofpurification/ap_flowerofpurificationbuff.nut", true);
				appendage.sq_SetValidTime(time);
				appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_FLOWEROFPURIFICATION, skillLevel);
				CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_FLOWEROFPURIFICATION, true);
				local change_appendage = appendage.sq_getChangeStatus("dsevensinsc");
				if(!change_appendage)
				{
					change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, 0, false, 0, APID_COMMON);
				}
				if(change_appendage) 
				{
					change_appendage.clearParameter();
					change_appendage.addParameter(CHANGE_STATUS_TYPE_COOLTIME_DECLINE, false, -coolbonus);
				}
			}
			
			break;

	}
	//obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
	//SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function setFlowerOfPurificationattack(obj) {
	local dist = sq_GetIntData(obj, SKILL_FLOWEROFPURIFICATION, 5);
	local tar = getFlowerOfPurification(obj, dist);

	if (tar)
		obj.getVar("damaFlowerOfPurification").push_obj_vector(tar);


}

function getFlowerOfPurification(obj,var) {
	local objectManager = obj.getObjectManager();
	if (objectManager) {
		for (local i = 0; i < objectManager.getCollisionObjectNumber(); i += 1) {
			local object = objectManager.getCollisionObject(i);
			if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE)) {
				local activeObj = sq_GetCNRDObjectToActiveObject(object);
				local curDistance = abs(obj.getXPos() - activeObj.getXPos()) * abs(obj.getXPos() - activeObj.getXPos()) +
					abs(obj.getYPos() - activeObj.getYPos()) * abs(obj.getYPos() - activeObj.getYPos());
				if (curDistance <= var * var)
					return activeObj;
			}
		}
	}
	return null;
}


function onProc_FlowerOfPurification(obj) {
	if (!obj) return;

	local state = obj.getSkillSubState(); //��������������SUB����
	local pAni = obj.sq_GetCurrentAni();
	local currentT = sq_GetCurrentTime(pAni);
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);

	switch (state) {
		case 0:
			if (frmIndex == 10 && obj.getVar("guanjian").get_vector(0) == 0) {
				if (obj.isMyControlObject()) {
					creatdepravitysevensins(obj, 400, 0,
						"character/priest/seducer/effect/animation/atdepravitysevensins/background/delightflower_bg_start_river.ani", ENUM_DRAWLAYER_BOTTOM)
				}
				obj.getVar("guanjian").clear_vector();
				obj.getVar("guanjian").push_vector(1);
			} else if (frmIndex == 19 && obj.getVar("guanjian").get_vector(0) == 1) {
				obj.sq_StartWrite();
				obj.sq_WriteDword(8);
				obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(SKILL_FLOWEROFPURIFICATION, -1, 1, 1.0));
				obj.sq_WriteDword(100);
				obj.sq_SendCreatePassiveObjectPacket(24384, 0, 0, 0, 0);
				if (obj.isMyControlObject()) {
					creatdepravitysevensins(obj, 400, 0,
						"character/priest/seducer/effect/animation/atdepravitysevensins/background/delightflower_bg_loop_river.ani", ENUM_DRAWLAYER_BOTTOM)
				}
				obj.getVar("guanjian").clear_vector();
				obj.getVar("guanjian").push_vector(0);
			}

			break;

	}
}


function onEndState_FlowerOfPurification(obj, new_state) {
	if (!obj) return;
	if (new_state != STATE_FLOWEROFPURIFICATION) {
		sq_EndDrawCastGauge(obj);
		setVliadEffectatdepravitysevensins(obj);
		local sq_var = obj.getVar("damaFlowerOfP");
		local objectsSize = sq_var.get_obj_vector_size();
		for (local i = 0; i < objectsSize; ++i) {
			local damager = sq_var.get_obj_vector(i);
			if (CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atpriest/seducer/flowerofpurification/ap_flowerofpurification.nut")) {
				CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atpriest/seducer/flowerofpurification/ap_flowerofpurification.nut");
			}
		}
	}
}


function creatdepravitysevensins(obj, x, y, img, ENUM) {
	local ani = sq_CreateAnimation("", img);

	local pooledObj = sq_CreatePooledObject(ani, true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM);
	local objectManager = obj.getObjectManager();
	local xPos = objectManager.getFieldXPos(x+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
	local yPos = objectManager.getFieldYPos(y, 0, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(xPos, yPos, 0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj, pooledObj, 0, false);
	obj.getVar("FlowerOfPurificationobj").push_obj_vector(pooledObj);
}

function setVliadEffectatdepravitysevensins(obj) {
	local var = obj.getVar("FlowerOfPurificationobj");
	local objectsSize = var.get_obj_vector_size();
	for (local i = 0; i < objectsSize; ++i) {
		local effectObj =
			var.get_obj_vector(i);
		if (effectObj) {
			effectObj.setValid(false);
		}
	}
}