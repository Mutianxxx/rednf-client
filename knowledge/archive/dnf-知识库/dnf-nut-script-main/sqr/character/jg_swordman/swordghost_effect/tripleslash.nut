function onAfterSetState_tripleslash_swordman(obj, state, datas, isResetTimer)
{
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	local ghostSword = obj.sq_GetSkillLevel(123);
	obj.getVar().clear_vector();
	obj.getVar().push_vector(subState);

	switch(subState)
	{
		case 0:
			if(ghostSword > 0)
			{
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(0);
				obj.sq_AddSetStatePacket(STATE_TRIPLESLASH_BLADESPIRIT, STATE_PRIORITY_IGNORE_FORCE, true);
			}
		break;
	}
}



function onSetState_tripleslashbs(obj, state, datas, isResetTimer)
{
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();
	//print("in:"+subState+"\n\r");
	switch(subState)
	{
		case 0:
			obj.getVar("slashcount").setInt(0, 0);
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_TRIPLESLASH_BLADESPIRIT1);
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_TRIPLESLASH_BLADESPIRIT1);
			local damage = obj.sq_GetBonusRateWithPassive(8, -1, 0, 1.0);
			obj.sq_SetCurrentAttackBonusRate(damage);
			local damageBonus = obj.sq_GetPowerWithPassive(8, -1, 3, -1, 1.0);
			obj.sq_SetCurrentAttackPower(damageBonus);
		break;
		case 1:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_TRIPLESLASH_BLADESPIRIT2);
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_TRIPLESLASH_BLADESPIRIT2);
			local damage = obj.sq_GetBonusRateWithPassive(8, -1, 0, 1.0);
			obj.sq_SetCurrentAttackBonusRate(damage);
			local damageBonus = obj.sq_GetPowerWithPassive(8, -1, 3, -1, 1.0);
			obj.sq_SetCurrentAttackPower(damageBonus);
		break;
		case 2:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_TRIPLESLASH_BLADESPIRIT3);
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_INFO_TRIPLESLASH_BLADESPIRIT3);
			local damage = obj.sq_GetBonusRateWithPassive(8, -1, 1, 1.0);
			obj.sq_SetCurrentAttackBonusRate(damage);
			local damageBonus = obj.sq_GetPowerWithPassive(8, -1, 4, -1, 1.0);
			obj.sq_SetCurrentAttackPower(damageBonus);
		break;
	}
	//print("out:ok!\n\r");
	if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL))
	{
		obj.sq_SetDirection(ENUM_DIRECTION_LEFT);
	}
	if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL))
	{
		obj.sq_SetDirection(ENUM_DIRECTION_RIGHT);
	}

	local Cot = obj.getVar("slashcount").getInt(0);
	obj.getVar("slashcount").setInt(0, Cot + 1);
	local xDistance = sq_GetDistancePos(sq_GetXPos(obj), obj.getDirection(), 200);
	//print("setxDistance:"+xDistance+"\n\r");
	obj.getVar("slashmove").clear_vector();
	obj.getVar("slashmove").push_vector(xDistance);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}



function onEndCurrentAni_tripleslashbs(obj)
{
	if(!obj) return;

	if(!obj.isMyControlObject())
	{
		return;
	}

	local subState = obj.getSkillSubState();
	switch(subState)
	{
		case 0:
			obj.sq_IntVectClear();
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
		case 1:
			obj.sq_IntVectClear();
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
		case 2:
			obj.sq_IntVectClear();
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
	}
}



function onProcCon_tripleslashbs(obj)
{
	if(!obj) return;

	local subState = obj.getSkillSubState();
	local pAni = obj.getCurrentAnimation();
	local frmIndex = pAni.GetCurrentFrameIndex();
	local Cot = obj.getVar("slashcount").getInt(0);
	local level = sq_GetSkillLevel(obj, 8);
	local Count = 3;

	if(subState <= 2 && Cot < Count)
	{
		obj.setSkillCommandEnable(8, true);
		if(frmIndex >= 3)
		{
			local tripleSlash = obj.sq_IsEnterSkill(8);
			local tripleSlash1 = sq_IsKeyDown(OPTION_HOTKEY_SKILL, ENUM_SUBKEY_TYPE_ALL);

			if(tripleSlash != -1)
			{
				local substateV = subState + 1;
				if(substateV > 2)
				substateV = 0;
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(substateV);
				obj.sq_AddSetStatePacket(STATE_TRIPLESLASH_BLADESPIRIT, STATE_PRIORITY_IGNORE_FORCE, true);
			}
		}
	}
	else if(subState >= 3)
	{
		obj.sq_IntVectClear();
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(frmIndex >= 3)
	{
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
		obj.sq_SetStaticMoveInfo(0, 0, 0, false);
	}
}



function onProc_tripleslashbs(obj)
{
	if(!obj) return;

	local subState = obj.getSkillSubState();
	local pAni = obj.getCurrentAnimation();
	local currentT = sq_GetCurrentTime(pAni);
	switch(subState)
	{
		case 0:
			local xDistance = obj.getVar("slashmove").get_vector(0);
			//print("getxDistance0:"+xDistance+"\n\r");
			local xAccel = sq_GetUniformVelocity(sq_GetXPos(obj), xDistance, currentT, 200);
			sq_MoveToNearMovablePos(obj, xAccel, sq_GetYPos(obj), 0, sq_GetXPos(obj), sq_GetYPos(obj), sq_GetZPos(obj), 20, -1, 3);
		break;
		case 1:
			local xDistance = obj.getVar("slashmove").get_vector(0);
			//print("getxDistance1:"+xDistance+"\n\r");
			local xAccel = sq_GetUniformVelocity(sq_GetXPos(obj), xDistance, currentT, 200);
			sq_MoveToNearMovablePos(obj, xAccel, sq_GetYPos(obj), 0, sq_GetXPos(obj), sq_GetYPos(obj), sq_GetZPos(obj), 20, -1, 3);
		break;
		case 2:
			local xDistance = obj.getVar("slashmove").get_vector(0);
			//print("getxDistance2:"+xDistance+"\n\r");
			local xAccel = sq_GetUniformVelocity(sq_GetXPos(obj), xDistance, currentT, 200);
			sq_MoveToNearMovablePos(obj, xAccel, sq_GetYPos(obj), 0, sq_GetXPos(obj), sq_GetYPos(obj), sq_GetZPos(obj), 20, -1, 3);
		break;
	}
	setSwordGhost28Effect(obj);
}



function onEndState_tripleslashbs(obj, newState)
{
	if(!obj) return;

	if(newState != STATE_TRIPLESLASH_BLADESPIRIT)
	{
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
		obj.sq_SetStaticMoveInfo(0, 0, 0, false);
		obj.startSkillCoolTime(8, 1, -1);
	}
}
