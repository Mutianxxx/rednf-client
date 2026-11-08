
function onAfterSetState_inquisitorjump(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local subState = obj.sq_GetVectorData(datas, 0);
	local type = obj.sq_GetVectorData(datas, 1);
	local high = obj.sq_GetVectorData(datas, 2);
	
	if(type == 1 && subState == 1 && high >20)
	{
		obj.getVar("jumpsteps").clear_vector();
		obj.getVar("jumpsteps").push_vector(1);
	}
	else
	{
		obj.getVar("jumpsteps").clear_vector();
		obj.getVar("jumpsteps").push_vector(0);
	}
}

function onProcCon_inquisitorjump(obj)
{
	if(!obj) return;
	local substatejump = obj.getVar("jumpsteps").get_vector(0);
	if(substatejump == 1 && sq_GetSkillLevel(obj, SKILL_WILLOFINQUISITOR) )
	{
		if( sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL) )
		{
			obj.getVar("jumpsteps").clear_vector();
			obj.getVar("jumpsteps").push_vector(2);
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(7, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		
	}
}

function onEndState_inquisitorjump(obj,new_state)
{
	if(!obj) return;

	obj.getVar("jumpsteps").clear_vector();
	obj.getVar("jumpsteps").push_vector(0);
}

function onKeyFrameFlag_jump_attack(obj, flagIndex)
{
	if(!obj) return false;
	if(isHolyFlame(obj))
	{
		if (flagIndex == 1)
		{
			obj.sq_StartWrite();
			obj.sq_WriteDword(109);
			obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 1, 0);
		}
	}
	return true;
}

function onAfterSetState_jump_attack(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	if(sq_GetSkillLevel(obj, SKILL_CRUSADE) > 0)
	{
		local power = obj.sq_GetPowerWithPassive(174, -1, 2, -1, 0.07);
		power = 45 + power;
		obj.sq_SetCurrentAttackPower(power.tointeger());
	}	
}