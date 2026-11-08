
function checkExecutableSkill_essenceofphlege(obj)
{
	if(!obj)
		return false;

	local isUse = obj.sq_IsUseSkill(SKILL_ESSENCEOFPHLEGE);
	if (isUse)
	{
		obj.sq_AddSetStatePacket(STATE_ESSENCEOFPHLEGE, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_essenceofphlege(obj)
{
	if (!obj)
		return false;
	return true;
}

function onSetState_EssenceOfPhlege(obj, state, datas, isResetTimer)
{
	if(!obj)
		return false;
	
	local substate = obj.getVar().get_vector(0);
	
	local z = obj.getZPos();
	
	if(z>5)
	{
		substate = 1;
	}
	
	obj.setSkillSubState(substate);
	
	obj.getVar("EssenceOfPhlege").clear_vector();
	obj.getVar("EssenceOfPhlege").push_vector(0);
	

	
	local skillLevel = obj.sq_GetSkillLevel(SKILL_POURESSENCE);
	if(skillLevel > 0)
	{
		if(sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_RIGHT 
			|| sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL) && obj.getDirection() == ENUM_DIRECTION_LEFT)
		{
			obj.getVar("EssenceOfPhlege").clear_vector();
			obj.getVar("EssenceOfPhlege").push_vector(1); 
		}
	}
	
	if(substate == 0)
	{
		obj.sq_StopMove();
		obj.sq_SetCurrentAnimation(ANI_EssenceOfPhlege_Body);
		if(isHolyFlame(obj))
		{
			obj.sq_AddStateLayerAnimation(9999, obj.sq_CreateCNRDAnimation("atanimation/holyflameweaponeffect/essenceofphlege_body.ani"), 0, 0);
		}
		obj.sq_PlaySound("PW_ESSENCE_PHLEGE");
		obj.sq_PlaySound("ESSENCE_SPLASH");
	}
	else if(substate == 1)
	{
		//obj.sq_ZStop();
		obj.sq_SetCurrentAnimation(ANI_EssenceOfPhlegeAir_Body);
		if(isHolyFlame(obj))
		{
			obj.sq_AddStateLayerAnimation(9999, obj.sq_CreateCNRDAnimation("atanimation/holyflameweaponeffect/essenceofphlegeair_body.ani"), 0, 0);
		}
		obj.sq_PlaySound("PW_ESSENCE_PHLEGE");
		obj.sq_PlaySound("ESSENCE_SPLASH");
		//obj.sq_SetCurrentAttackInfo(ATK_ViolentAssault);
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}


function onProc_EssenceOfPhlege(obj)
{
	local substate = obj.getSkillSubState();

	if(substate == 0)
	{

	}
	else if(substate == 1)
	{
		local z = obj.getZPos();
		if(z == 0)
		{
			obj.sq_StopMove();
		}
	}
}

function onKeyFrameFlag_EssenceOfPhlege(obj,flagIndex)
{
	if(!obj)
		return false;
	local ani = obj.sq_GetCurrentAni();
	local type = obj.getVar("EssenceOfPhlege").get_vector(0);
	if (flagIndex == 1)
	{
		//sq_AddDrawOnlyAniFromParent(obj,"character/priest/effect/animation/atessenceofphlege/essenceofphlegeair_08.ani", 100, 100, 0);
		if(type == 1)
		{
			obj.sq_StartWrite();
			obj.sq_WriteDword(113);
			obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, obj.getZPos());
		
		}
		else
		{
			obj.sq_StartWrite();
			obj.sq_WriteDword(111);
			obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 95);
		}

	}
	else if (flagIndex == 2)
	{
		//sq_AddDrawOnlyAniFromParent(obj,"character/priest/effect/animation/atessenceofphlege/essenceofphlegeair_08.ani", 100, 100, 0);
		if(type == 1)
		{
			obj.sq_StartWrite();
			obj.sq_WriteDword(113);
			obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, obj.getZPos());
		
		}
		else
		{
			obj.sq_StartWrite();
			obj.sq_WriteDword(111);
			obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 95);
		}
	}
	obj.sq_ClearKeyFrameFlag(ani);
	return true;
}

function onEndCurrentAni_EssenceOfPhlege(obj)
{
	local substate = obj.getSkillSubState();

	if(substate == 0)
	{
		obj.getVar().clear_vector();
		//obj.getVar().push_vector(1);
		//obj.sq_AddSetStatePacket(STATE_ESSENCEOFPHLEGE ,STATE_PRIORITY_USER, true);
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	else if(substate == 1)
	{
		local z = obj.getZPos();
		if(z > 0)
		{
			
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 1);
			sq_IntVectorPush(pIntVec, 0);
			sq_IntVectorPush(pIntVec, 1);
			obj.addSetStatePacket(STATE_JUMP, pIntVec, STATE_PRIORITY_FORCE, false, "");
			obj.flushSetStatePacket();
			
		}
		else
		{
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		}
	}
}
