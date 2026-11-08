//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////


function onAfterSetState_attack_thief(obj, state, datas, isResetTimer)
{
	onAfterSetState_attack_thief_3(obj, state, datas, isResetTimer);
	onAfterSetState_attack_thief_4(obj, state, datas, isResetTimer);

}


function onAfterSetState_attack_thief_3(obj, state, datas, isResetTimer)
{
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.getVar("subState").clear_vector();
	obj.getVar("subState").push_vector(subState);
	local equipchakraweapon = obj.sq_GetSkillLevel(SKILL_EQUIPCHAKRAWEAPON);
	local kusanagi = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut");
	if(equipchakraweapon > 0  && (obj.getWeaponSubType()==5 || kusanagi == true))
	{
		switch(subState)
		{
			case 0:
				if(kusanagi == true)
				{
					if(obj.isMyControlObject())
					{
						obj.sq_StartWrite();
						obj.sq_WriteDword(61);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 70, 0, 70);
						obj.sq_StartWrite();
						obj.sq_WriteDword(61);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 70, 20, 70);
						obj.sq_StartWrite();
						obj.sq_WriteDword(61);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 70, -20, 70);
					}
					obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
				}
				else
				{
					als_ani(obj, "character/thief/effect/animation/chakraweapon/chakraweaponatk01_eff_a.ani", 30, 0, 0, 0, 100, 1, 1, 1.0);
					if(obj.isMyControlObject())
					{
						obj.sq_StartWrite();
						obj.sq_WriteDword(0);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 90, 0, 60);
					}
					local shurikenimprove = sq_GetSkillLevel(obj, SKILL_SHURIKENIMPROVE);
					local randomNum = sq_getRandom(0, 100);
					local prob = sq_GetLevelData(obj, SKILL_SHURIKENIMPROVE, 2, shurikenimprove);
					local isTrue;
					if(randomNum <= prob)
					{
						isTrue = true;
					}
					else if(randomNum > prob)
					{
						isTrue = false;
					}
					if(obj.isMyControlObject() && isTrue)
					{
						obj.sq_StartWrite();
						obj.sq_WriteDword(0);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 70, 0, 45);
					}
				}
			break;
			case 1:
				if(kusanagi == true)
				{
					if(obj.isMyControlObject())
					{
						obj.sq_StartWrite();
						obj.sq_WriteDword(61);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 70, 0, 70);
						obj.sq_StartWrite();
						obj.sq_WriteDword(61);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 70, 20, 70);
						obj.sq_StartWrite();
						obj.sq_WriteDword(61);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 70, -20, 70);
					}
					obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
				}
				else
				{
					als_ani(obj, "character/thief/effect/animation/chakraweapon/chakraweaponatk02_eff_a.ani", -20, 0, 0, 0, 100, 1, 1, 1.0);
					if(obj.isMyControlObject())
					{
						obj.sq_StartWrite();
						obj.sq_WriteDword(0);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 90, 0, 60);
					}
					local shurikenimprove = sq_GetSkillLevel(obj, SKILL_SHURIKENIMPROVE);
					local randomNum = sq_getRandom(0, 100);
					local prob = sq_GetLevelData(obj, SKILL_SHURIKENIMPROVE, 2, shurikenimprove);
					local isTrue;
					if(randomNum <= prob)
					{
						isTrue = true;
					}
					else if(randomNum > prob)
					{
						isTrue = false;
					}
					if(obj.isMyControlObject() && isTrue)
					{
						obj.sq_StartWrite();
						obj.sq_WriteDword(0);
						obj.sq_SendCreatePassiveObjectPacket(24356, 0, 70, 0, 45);
					}
				}
			break;
			case 2:
				als_ani(obj, "character/thief/effect/animation/chakraweapon/chakraweaponatk03a_eff_a.ani", -40, 0, 0, 0, 100, 1, 1, 1.0);
				if(obj.isMyControlObject())
				{
					obj.sq_StartWrite();
					obj.sq_WriteDword(0);
					obj.sq_SendCreatePassiveObjectPacket(24356, 0, 90, 0, 60);
				}
				local shurikenimprove = sq_GetSkillLevel(obj, SKILL_SHURIKENIMPROVE);
				local randomNum = sq_getRandom(0, 100);
				local prob = sq_GetLevelData(obj, SKILL_SHURIKENIMPROVE, 2, shurikenimprove);
				local isTrue;
				if(randomNum <= prob)
				{
					isTrue = true;
				}
				else if(randomNum > prob)
				{
					isTrue = false;
				}
				if(obj.isMyControlObject() && isTrue)
				{
					obj.sq_StartWrite();
					obj.sq_WriteDword(0);
					obj.sq_SendCreatePassiveObjectPacket(24356, 0, 70, 0, 45);
				}
			break;
			case 3:
				als_ani(obj, "character/thief/effect/animation/chakraweapon/chakraweaponatk03b_eff_a.ani", 40, 0, 0, 0, 100, 1, 1, 1.0);
				if(obj.isMyControlObject())
				{
					obj.sq_StartWrite();
					obj.sq_WriteDword(0);
					obj.sq_SendCreatePassiveObjectPacket(24356, 0, 90, 0, 50);
				}
				local shurikenimprove = sq_GetSkillLevel(obj, SKILL_SHURIKENIMPROVE);
				local randomNum = sq_getRandom(0, 100);
				local prob = sq_GetLevelData(obj, SKILL_SHURIKENIMPROVE, 2, shurikenimprove);
				local isTrue;
				if(randomNum <= prob)
				{
					isTrue = true;
				}
				else if(randomNum > prob)
				{
					isTrue = false;
				}
				if(obj.isMyControlObject() && isTrue)
				{
					obj.sq_StartWrite();
					obj.sq_WriteDword(0);
					obj.sq_SendCreatePassiveObjectPacket(24356, 0, 70, 0, 65);
				}
			break;
		}
	}
}



function onProcCon_attack_thief(obj)
{
	if(!obj) return;

	local subState = obj.getVar("subState").get_vector(0);
	local equipchakraweapon = obj.sq_GetSkillLevel(SKILL_EQUIPCHAKRAWEAPON);
	local kusanagi = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut");
	if(subState <= 3 && equipchakraweapon > 0  && (obj.getWeaponSubType()==5 || kusanagi == true))
	{
		if(obj.getDirection() == ENUM_DIRECTION_LEFT)
		{
			sq_SetKeyxEnable(obj, E_ATTACK_COMMAND, true);
			if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && sq_IsEnterCommand(obj, E_ATTACK_COMMAND))
			{
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(0);
				obj.sq_AddSetStatePacket(STATE_CHAKRAWEPAON_STEP, STATE_PRIORITY_IGNORE_FORCE, true);
			}
		}
		if(obj.getDirection() == ENUM_DIRECTION_RIGHT)
		{
			sq_SetKeyxEnable(obj, E_ATTACK_COMMAND, true);
			if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && sq_IsEnterCommand(obj, E_ATTACK_COMMAND))
			{
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(0);
				obj.sq_AddSetStatePacket(STATE_CHAKRAWEPAON_STEP, STATE_PRIORITY_IGNORE_FORCE, true);
			}
		}
	}
	return true;
}



function onSetState_chakraweapon_backstep(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();

	switch(subState)
	{
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_CHAKRAWEAPON_BACKSTEP);
			obj.sq_SetStaticSpeedInfo(0, 0, 0, (1000 * 1.0).tointeger(), 0.0, 0.0);
		break;
	}
}



function onEndCurrentAni_chakraweapon_backstep(obj)
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
	}
}



function onKeyFrameFlag_chakraweapon_backstep(obj, flagIndex)
{
	if(!obj) return false;

	local subState = obj.getSkillSubState();
	local kusanagi = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut");
	switch(subState)
	{
		case 0:
			switch(flagIndex)
			{
				case 10002:
					if(kusanagi == true)
					{
						if(obj.isMyControlObject())
						{
							obj.sq_StartWrite();
							obj.sq_WriteDword(61);
							obj.sq_SendCreatePassiveObjectPacket(24356, 0, 100, 0, 40);
						}
					}
					else
					{
						als_ani(obj, "character/thief/effect/animation/chakraweapon/chakraweaponatk03b_eff_a.ani", 40, 0, 20, 0, 100, 1, 1, 1.0);
						if(obj.isMyControlObject())
						{
							obj.sq_StartWrite();
							obj.sq_WriteDword(0);
							obj.sq_SendCreatePassiveObjectPacket(24356, 0, 90, 0, 60);
						}
					}
				break;
			}
		break;
	}
	return true;
}



function onProc_chakraweapon_backstep(obj)
{
	if(!obj) return;

	local subState = obj.getSkillSubState();
	local pAni = obj.getCurrentAnimation();
	switch(subState)
	{
		case 0:
			if(obj.getDirection() == ENUM_DIRECTION_LEFT)
			{
				if(obj.sq_IsKeyFrameFlag(pAni, 10001))
				{
					sq_SetVelocity(obj, 0, 600.0);
					sq_SetVelocity(obj, 2, 300.0);
				}
				if(obj.sq_IsKeyFrameFlag(pAni, 10003))
				{
					sq_SetVelocity(obj, 0, 200.0);
				}
			}
			if(obj.getDirection() == ENUM_DIRECTION_RIGHT)
			{
				if(obj.sq_IsKeyFrameFlag(pAni, 10001))
				{
					sq_SetVelocity(obj, 0, -600.0);
					sq_SetVelocity(obj, 2, 300.0);
				}
				if(obj.sq_IsKeyFrameFlag(pAni, 10003))
				{
					sq_SetVelocity(obj, 0, -200.0);
				}
			}
		break;
	}
	return true;
}






function onSetState_attack_thief(obj, state, datas, isResetTimer)
{	

    local attackIndex = obj.getAttackIndex();
    if (isAssassin(obj))
    {
        obj.getVar("isBack").clear_vector();
        obj.getVar("isBack").push_vector(0);
    }

}

function onAfterAttack_attack_thief(obj, damager, boundingBox, isStuck)
{
	local attackIndex = obj.getAttackIndex();
	if (isAssassin(obj) && attackIndex == 3)
	{
		local monObj = sq_GetCNRDObjectToActiveObject(damager);
		monObj.setDirection(obj.getDirection());
		local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_ASSASSIN, false, "character/new_thief/appendage/ap_attack_thief.nut", true);
		if(masterAppendage)
		{
			masterAppendage.getAppendageInfo().setValidTime(1000);
		}
	}
}

function onAttack_attack_thief(obj, damager, boundingBox, isStuck)
{
	local attackIndex = obj.getAttackIndex();
	if (isAssassin(obj) && isEnemyBack(obj,damager) && attackIndex == 3)
	{
		local damage = sq_GetCurrentAttackBonusRate(obj);
		sendOneHitAllMonsterShaowAreaObj(obj,damage);
	}
}

/*function onEndState_ThiefAttack(obj,new_state)
{
    local attackIndex = obj.getAttackIndex();
    if (attackIndex == 25 && new_state != STATE_ATTACK)
    {
        local pAni = sq_GetCurrentAnimation(obj);
        if(pAni)
            pAni.setFrameDelay(1,80,true);

    }
}*/

function onAfterSetState_attack_thief_4(obj, state, datas, isResetTimer)
{

    local attackIndex = obj.getAttackIndex();
    if (attackIndex == 25)
    {
        local pAni = sq_GetCurrentAnimation(obj);
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);

        if(pAni)
            pAni.setFrameDelay(1,9999,true);

    }
}

/*function onProc_ThiefAttack(obj)
{

    local atk = obj.getAttackIndex();
    if (atk == 25)
    {
        local oobj = getBellacreObject(obj);
        if (!oobj)
        {
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
        }else
        {
            local pAni = sq_GetCurrentAnimation(oobj);
            local frmIndex = sq_GetAnimationFrameIndex(pAni);
            if (frmIndex >= 21)
            {
                obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
            
            }else
			{
				if (frmIndex >= 4 && obj.getVar("flag").get_vector(0) == 0)
				{
					obj.sq_SetShake(obj, 4, 160);
					obj.getVar("flag").set_vector(0,1);
				}else if (frmIndex >= 16 && obj.getVar("flag").get_vector(1) == 0)
				{
					obj.sq_SetShake(obj, 7, 400);
					sq_flashScreen(obj,0,120,320,255, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
					obj.getVar("flag").set_vector(1,1);
				}
			
			}
            
        }
    }
}*/



