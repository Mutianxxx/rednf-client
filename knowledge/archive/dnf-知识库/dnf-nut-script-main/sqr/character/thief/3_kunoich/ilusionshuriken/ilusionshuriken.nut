//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function checkCommandEnable_ilusionshuriken(obj)
{
	return true;
}



function checkExecutableSkill_ilusionshuriken(obj)
{
	if(!obj) return false;
	
	local state = obj.sq_GetState();
	if(state == 3||state == 4||state == 5||state == 9||state == 16||state == 40) 
		return false;
	if(obj.sq_IsUseSkill(SKILL_ILUSIONSHURIKEN))
	{
		local now_z = obj.getZPos();
		if(state == 6 || state == 7 || now_z>40)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_AddSetStatePacket(STATE_ILUSIONSHURIKEN, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}else{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_ILUSIONSHURIKEN, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}
		
	}
	
	return false;
}



function onSetState_ilusionshuriken(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	switch(subState)
	{
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_ILUSIONSHURIKEN1);
			obj.sq_PlaySound("R_TF_GHOSTKUNAI");
		break;
		case 1:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_ILUSIONSHURIKEN2);
			obj.sq_ZStop();
			obj.sq_PlaySound("R_TF_GHOSTKUNAI");
		break;
	}
}



function onEndCurrentAni_ilusionshuriken(obj)
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
			obj.sq_IntVectPush(1);
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
	}
}



function onAfterSetState_ilusionshuriken(obj, state, datas, isResetTimer)
{
	if(!obj) return;

	local subState = obj.getSkillSubState();
	local skill_level = sq_GetSkillLevel(obj, SKILL_ILUSIONSHURIKEN);
	local ilusionCount = sq_GetLevelData(obj, SKILL_ILUSIONSHURIKEN, 1, skill_level);
	switch(subState)
	{
		case 0:
			if(obj.isMyControlObject())
			{
				obj.sq_StartWrite();
				obj.sq_WriteDword(4);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
				als_ani(obj, "character/thief/animation/ilusionshuriken_shadow1.ani", 80, 50, 0, 0, 100, 0, 1, 1.0);
				als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_boom.ani", 80, 51, 0, 0, 100, 0, 2, 1.0);
				als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_glow.ani", 80, 51, 0, 0, 100, 0, 2, 1.0);
				als_ani(obj, "character/thief/animation/ilusionshuriken_shadow1.ani", 120, -50, 0, 0, 100, 0, 1, 1.0);
				als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_boom.ani", 120, -49, 0, 0, 100, 0, 2, 1.0);
				als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_glow.ani", 120, -49, 0, 0, 100, 0, 2, 1.0);
				if(ilusionCount >= 3)
				{
					als_ani(obj, "character/thief/animation/ilusionshuriken_shadow1.ani", -30, 80, 0, 0, 100, 0, 1, 1.0);
					als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_boom.ani", -30, 81, 0, 0, 100, 0, 2, 1.0);
					als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_glow.ani", -30, 81, 0, 0, 100, 0, 2, 1.0);
				}
				if(ilusionCount >= 4)
				{
					als_ani(obj, "character/thief/animation/ilusionshuriken_shadow1.ani", 20, -80, 0, 0, 100, 0, 1, 1.0);
					als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_boom.ani", 20, -79, 0, 0, 100, 0, 2, 1.0);
					als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_glow.ani", 20, -79, 0, 0, 100, 0, 2, 1.0);
				}
			}
		break;
		case 1:
			if(obj.isMyControlObject())
			{
				obj.sq_StartWrite();
				obj.sq_WriteDword(5);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
				als_ani(obj, "character/thief/animation/ilusionshuriken_shadow2.ani", -70, 30, 0, 0, 100, 0, 1, 1.0);
				als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_boom.ani", -70, -29, 0, 0, 100, 0, 2, 1.0);
				als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_glow.ani", -70, -29, 0, 0, 100, 0, 2, 1.0);
				als_ani(obj, "character/thief/animation/ilusionshuriken_shadow2.ani", -70, -30, 0, 0, 100, 0, 1, 1.0);
				als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_boom.ani", -70, -49, 0, 0, 100, 0, 2, 1.0);
				als_ani(obj, "character/thief/effect/animation/illusionshuriken/groundatk/ilusion_groundatkstart_a_glow.ani", -70, -49, 0, 0, 100, 0, 2, 1.0);
			}
		break;
	}
}



function onProcCon_ilusionshuriken(obj)
{
	if(!obj) return;

	local subState = obj.getSkillSubState();
	switch(subState)
	{
		case 0:
			sq_SetKeyxEnable(obj, E_JUMP_COMMAND, true);
			if(sq_IsEnterCommand(obj, E_JUMP_COMMAND))
			{
				obj.sq_IntVectClear();
				obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
				remove_ani(obj);
			}
		break;
		case 1:
			sq_SetKeyxEnable(obj, E_JUMP_COMMAND, true);
			if(sq_IsEnterCommand(obj, E_JUMP_COMMAND))
			{
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(1);
				obj.sq_IntVectPush(0);
				obj.sq_IntVectPush(0);
				obj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_IGNORE_FORCE, true);
				remove_ani(obj);
			}
		break;
	}
}