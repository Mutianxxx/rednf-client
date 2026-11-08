
//frame = 4 shake 4 160
//frame = 16 flash 0 120 320 255 255 255 255 bottom shake 7 400

function checkExecutableSkill_ExecutionerSlash(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_EXECUTIONER_SLASH );
	if (isUseSkill) 
    {
		local lord = getBellacreObject(obj);
		if (!lord)
			return false;
		else
		{

			obj.sq_IntVectClear();
			obj.sq_IntVectPush(25);
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(8, STATE_PRIORITY_IGNORE_FORCE, true);
		    local ani = lord.getCustomAnimation(22);
			sq_Rewind(ani);
            lord.setCurrentAnimation(ani);
			local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_EXECUTIONER_SLASH, STATE_EXECUTIONER_SLASH, 0, 1.0);
			local attackInfo = sq_GetCustomAttackInfo(lord, 14);
            sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate );
            sq_SetCurrentAttackInfo(lord, attackInfo);


		}

		return true;
	}
	return false;
}


function checkCommandEnable_ExecutionerSlash(obj)  
{
	if (getBellacreObject(obj))
		return true;
	return false;
}

