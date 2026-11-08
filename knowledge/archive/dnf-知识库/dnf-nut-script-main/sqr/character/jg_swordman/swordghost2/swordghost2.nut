function checkExecutableSkill_SwordGhost2(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_2);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_2 , STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_SwordGhost2(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	

	if (state == STATE_STAND)
		return true;

	return true;
}

function onSetState_SwordGhost2(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	obj.sq_StopMove();

	local skill_level = obj.sq_GetSkillLevel(46);

	local upForce = obj.sq_GetLevelData(46, 1, skill_level);
	//local power = obj.sq_GetLevelData(46, 3, skill_level);

	//local attackInfo = sq_GetCurrentAttackInfo(obj);
	//sq_SetCurrentAttackPower(attackInfo, power);
	//sq_SetCurrentAttacknUpForce(attackInfo, upForce);

	obj.sq_SetStaticMoveInfo(0, 55, 100, false);	
	obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);

	if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL))
	{
		obj.sq_SetStaticMoveInfo(0, 140, 100, false);	
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}

	if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL))
	{
		obj.sq_SetStaticMoveInfo(0, 140, 100, false);	
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
	}
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_UP_ATTACK);
	local gaugeValue_rate = setSwordGhost3State(obj);

	obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_NONE_ATTACK4);	//????ATK????
	local damage = obj.sq_GetBonusRateWithPassive(46 , -1, 0, 1+gaugeValue_rate);
	obj.sq_SetCurrentAttackBonusRate(damage);				//??????SKL??????v??	
	sq_SetCurrentAttacknUpForce(sq_GetCurrentAttackInfo(obj),upForce);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);	//????????????t?????

}


function onAttack_SwordGhost2(obj, damager, boundingBox, isStuck)
{
	if (!obj) return false;
	
	local skillLevel = obj.sq_GetSkillLevel(123);//


	if (skillLevel > 0)
	{
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
		sq_EffectLayerAppendage(damager,sq_RGB(255,255,255),150,0,0,240);//???????????????G

		local count1 = obj.getMyPassiveObjectCount(251338);//BUFF???
		local count2 = obj.getMyPassiveObjectCount(250334);//????????BUFF????
		
		if(count1 <= max_gaugeValue)
		{
			if(count2 <= 5)
			{
				local rand = sq_getRandom(-50,50);
				local objindex = setSwordGhost4State(obj);//??????????????????o?????????????
				sq_SendCreatePassiveObjectPacketPos(obj, 250334, 0, damager.getXPos() + rand, damager.getYPos() + rand, damager.getZPos() + damager.getObjectHeight()/2);	
			}
		}
	}

}

function onEndCurrentAni_SwordGhost2(obj)
{

	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);

}

function onProc_SwordGhost2(obj)
{
	if(!obj) return;
}

function onKeyFrameFlag_SwordGhost2(obj,flagIndex)
{
	if(!obj)
		return false;

		if (flagIndex == 1)
{

	local skillLevel = obj.sq_GetSkillLevel(123);
	if (skillLevel > 0)
	{
		obj.sq_AddStateLayerAnimation(2,obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/upper_01.ani"), -26, 0);
		obj.sq_AddStateLayerAnimation(3,obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/upper_03.ani"), -26, 0);
		obj.sq_AddStateLayerAnimation(4,obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/upper_02.ani"), -26, 0);
		obj.sq_AddStateLayerAnimation(1,obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/upper_00.ani"), -26, 0);
	}
}
	return true;
}

function onProc_SwordGhost2(obj)
{
	if(!obj) return;
	setSwordGhost28Effect(obj);
}