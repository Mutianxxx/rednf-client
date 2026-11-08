function checkExecutableSkill_gunner_suppressingfire(obj)
{
	if(!obj) return false; 
	local IsUseSkill = obj.sq_IsUseSkill(SKILL_GUNNER_SUPPRESSINGFIRE);
	if (IsUseSkill)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_GUNNER_SUPPRESSINGFIRE, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_gunner_suppressingfire(obj)
{
	if(!obj) return false; 
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
	if (state == STATE_ATTACK)
	{
		return obj.sq_IsCommandEnable(SKILL_GUNNER_SUPPRESSINGFIRE);
	}
	return true;
}

function onSetState_gunner_suppressingfire(obj, state, datas, isResetTimer)
{
	if (!obj) return;
	obj.sq_StopMove();
	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	switch (subState)
	{
	case 0:
		obj.getVar().clear_vector();
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_SUPPRESSINGFIRE_START_BODY);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
		break;
	case 1:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_SUPPRESSINGFIRE_LOOP_BODY);
		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_GUNNER_SUPPRESSINGFIRELOOPATTACK);

		local particleCreater = obj.getVar("gunner_suppressingfire").GetparticleCreaterMap("gunner_suppressingfire", "character/gunner/particle/deadlyapproach.ptl", obj);
		particleCreater.Restart(0);
		particleCreater.SetPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(),0),obj.getYPos(), obj.getZPos());
		sq_AddParticleObject(obj, particleCreater);

		local skill_level = sq_GetSkillLevel(obj, SKILL_GUNNER_SUPPRESSINGFIRE);
		local maxAtkTime = obj.sq_GetLevelData(SKILL_GUNNER_SUPPRESSINGFIRE, 3, skill_level);
		obj.getVar().clear_timer_vector();
		obj.getVar().push_timer_vector();
		local t = obj.getVar().get_timer_vector(0);
		t.setParameter(maxAtkTime, -1);
		t.resetInstant(0);
		local time = obj.sq_GetLevelData(SKILL_GUNNER_SUPPRESSINGFIRE, 2, skill_level);
		local minAtkTime = obj.sq_GetLevelData(SKILL_GUNNER_SUPPRESSINGFIRE, 4, skill_level);
		local maxAniSpeed = 280;
		local minAniSpeed = 100;
		local maxCount = 3;
		local cCount = 0;
        
		obj.getVar().clear_vector();
		local objVar = obj.getVar();
		objVar.push_vector(time);
		objVar.push_vector(maxAtkTime);
		objVar.push_vector(minAtkTime);
		objVar.push_vector(maxAniSpeed);
		objVar.push_vector(minAniSpeed);
		objVar.push_vector(maxCount);
		objVar.push_vector(cCount);

		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_GUNNER_SUPPRESSINGFIRE, false, "character/gunner/suppressingfire/ap_suppressingfire.nut", true);
		//appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_GUNNER_SUPPRESSINGFIRE, -1);
		CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, 238, true);
		break;
	case 2:
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_SUPPRESSINGFIRE_FINISH_BODY);
		sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/atsuppressingfire/03_finish/dust/suppressingfire_finish_dust01.ani", 0, 0, 0);
		sq_AddDrawOnlyAniFromParent(obj, "character/gunner/effect/animation/atsuppressingfire/03_finish/front/suppressingfire_finish_front.ani", 0, 0, 0);
		break;
	}
}

function onProc_gunner_suppressingfire(obj)
{
	if (!obj) return;
	local subState = obj.getSkillSubState();
	if (subState == 1)
	{
		local Count = obj.getMyPassiveObjectCount(22001);
		for(local i=0;i<Count;++i)
		{
			local object = obj.getMyPassiveObject(22001, i);
			local objecttt = obj.getVar("gunner_suppressingfire").is_obj_vector(object);
			if(object && objecttt)
			{
				setCurrentAnimationFromCutomIndex(object, 4);
				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_GUNNER_SUPPRESSINGFIRE, SKILL_GUNNER_SUPPRESSINGFIRE, 0, 1.0);
				local attackInfo = sq_GetCurrentAttackInfo(object);
				sq_SetCurrentAttacknUpForce(attackInfo, 10); 
				sq_SetCurrentAttacknBackForce(attackInfo, 3); 
				sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
			}
		}
		local t = obj.getVar().get_timer_vector(0);
		if (t)
		{
		if (t.isOnEvent(obj.sq_GetStateTimer()) == true)
			{
				local particleCreater = obj.getVar("gunner_suppressingfire").GetparticleCreaterMap("gunner_suppressingfire", "character/gunner/particle/deadlyapproach.ptl", obj);
				particleCreater.Restart(0);
				particleCreater.SetPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(),0),obj.getYPos(), obj.getZPos());
				sq_AddParticleObject(obj, particleCreater);
			}
		}
	}

	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	if (subState == 2 && frmIndex > 4)
	{
		local Count = obj.getMyPassiveObjectCount(22001);
		for(local i=0;i<Count;++i)
		{
			local object = obj.getMyPassiveObject(22001, i);
			local objecttt = obj.getVar("gunner_suppressingfire1").is_obj_vector(object);
			if(object && objecttt)
			{
				setCurrentAnimationFromCutomIndex(object, 5);
				local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_GUNNER_SUPPRESSINGFIRE, SKILL_GUNNER_SUPPRESSINGFIRE, 1, 1.0);
				local attackInfo = sq_GetCurrentAttackInfo(object);
				sq_SetCurrentAttackeDamageAct(attackInfo, 2); 
				sq_SetCurrentAttacknUpForce(attackInfo, 300); 
				sq_SetCurrentAttacknBackForce(attackInfo, 300); 
				sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
			}
		}
	}
}

function onCreateObject_gunner_suppressingfire(obj, createObject)
{
	if(!obj) return;
	local state = obj.sq_GetState();
	local substate = obj.getSkillSubState(); 
	if(state == STATE_GUNNER_SUPPRESSINGFIRE)
	{
		local Object = sq_GetCNRDObjectToCollisionObject(createObject); 
		if(Object && Object.getCollisionObjectIndex() == 22001)
		{
			if (substate == 1)
			{
				obj.getVar("gunner_suppressingfire").push_obj_vector(Object);
			}
			local objecttt = obj.getVar("gunner_suppressingfire").is_obj_vector(Object);
			if (substate == 2 && !objecttt)
			{
				obj.getVar("gunner_suppressingfire1").push_obj_vector(Object);
			}			
		}
	}
}

function onKeyFrameFlag_gunner_suppressingfire(obj, flagIndex)
{
	if(!obj) return false;
	local substate = obj.getSkillSubState(); 
	switch(substate)
	{
		case 2:
		if(flagIndex == 1)
		{
			local particleCreater = obj.getVar("gunner_suppressingfire1").GetparticleCreaterMap("gunner_suppressingfire1", "character/gunner/particle/deadlyapproach.ptl", obj);
			particleCreater.Restart(0);
			particleCreater.SetPos(sq_GetDistancePos(obj.getXPos(), obj.getDirection(),0),obj.getYPos(), obj.getZPos());
			sq_AddParticleObject(obj, particleCreater);
			sq_SetMyShake(obj, 5, 200); 
		}
		break;
	}
	return true;
}

function onProcCon_gunner_suppressingfire(obj)
{
    if (!obj) return;
	local subState = obj.getSkillSubState();
	if (subState == 1)
	{
		local objVar = obj.getVar();
		if (obj.sq_GetStateTimer() >= objVar.get_vector(0))
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(2);
			obj.sq_AddSetStatePacket(STATE_GUNNER_SUPPRESSINGFIRE, STATE_PRIORITY_USER, true);
			return;
		}
		sq_SetKeyxEnable(obj, E_JUMP_COMMAND, true);
		if (sq_IsEnterCommand(obj, E_JUMP_COMMAND))
		{
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
			return;
		}
		sq_SetKeyxEnable(obj, E_ATTACK_COMMAND, true);
		obj.setSkillCommandEnable(SKILL_GUNNER_SUPPRESSINGFIRE, true);
		if (sq_IsEnterCommand(obj, E_ATTACK_COMMAND) || obj.sq_IsEnterSkill(SKILL_GUNNER_SUPPRESSINGFIRE) != -1)
		{
			local cCount = objVar.get_vector(6);
			local maxCount = objVar.get_vector(5);
			if (cCount < maxCount)
			{
				cCount += 1;
				objVar.set_vector(6, cCount);
				local cAtkTime = sq_GetUniformVelocity(objVar.get_vector(1), objVar.get_vector(2), cCount, maxCount);
				local cAniSpeed = sq_GetUniformVelocity(objVar.get_vector(4), objVar.get_vector(3), cCount, maxCount);
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(cAtkTime);
				sq_BinaryWriteDword(cAniSpeed);
				sq_SendChangeSkillEffectPacket(obj, SKILL_GUNNER_SUPPRESSINGFIRE);
			}
		}
	}
}


function onChangeSkillEffect_gunner_suppressingfire(obj, skillIndex, reciveData)
{
    if (!obj)
        return;
    if (skillIndex != SKILL_GUNNER_SUPPRESSINGFIRE)
        return;
    local subState = obj.getSkillSubState();
    if (subState == 1)
    {
        local cAtkTime = reciveData.readDword();
        local cAniSpeed = (reciveData.readDword()).tofloat() / 100.0;
        local t = obj.getVar().get_timer_vector(0);
        if (t)
            t.setEventTerm(cAtkTime);
        obj.sq_SetStaticSpeedInfo(0, 0, SPEED_VALUE_DEFAULT, (SPEED_VALUE_DEFAULT * cAniSpeed).tointeger(), 1.0, 1.0);
    }
}

function onEndState_gunner_suppressingfire(obj, new_state)
{
	local state = obj.sq_GetState();
	local SubState0 = obj.getVar("substate").get_vector(0);
	local SubState1 = obj.getVar("substate").get_vector(1);
	local SubState2 = obj.getVar("substate").get_vector(2);
	if (new_state != SKILL_GUNNER_SUPPRESSINGFIRE)
	{
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/gunner/suppressingfire/ap_suppressingfire.nut");
		removeAni(obj);
	}
}

function onEndCurrentAni_gunner_suppressingfire(obj)
{
    if (!obj)
        return;
    if (!obj.sq_IsMyControlObject())
        return;
    local subState = obj.getSkillSubState();
    if (subState != 2)
    {
        obj.sq_IntVectClear();
        obj.sq_IntVectPush(subState + 1);
        obj.sq_AddSetStatePacket(STATE_GUNNER_SUPPRESSINGFIRE, STATE_PRIORITY_USER, true);
    }
    else
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function onAttack_gunner_suppressingfire(obj, damager, boundingBox, isStuck)
{
    if (!obj)
        return;
    if (isStuck || !damager.isObjectType(OBJECTTYPE_ACTIVE))
        return;
    local subState = obj.getSkillSubState();
/* switch (subState)
    {
    case 1:
        local ani = sq_CreateAnimation("", "character/gunner/effect/animation/hiteffect/updefault.ani");
        ani.setImageRateFromOriginal(-1.0, 1.0);
        ani.addLayerAnimation(1, sq_CreateAnimation("", "character/gunner/effect/animation/atsuppressingfire/suppressingfire_blow001.ani"), true);
        local addZPos = sq_GetCenterZPos(boundingBox);
        local pooledObj = sq_CreatePooledObject(ani, true);
        sq_SetCurrentDirection(pooledObj, obj.getDirection());
        pooledObj.setCurrentPos(damager.getXPos(), damager.getYPos() + 1, damager.getZPos() + addZPos + sq_getRandom(addZPos / 2 / -1, addZPos / 2));
        pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_NORMAL);
        sq_AddObject(obj, pooledObj, OBJECTTYPE_DRAWONLY, false);
        break;
    }*/
}