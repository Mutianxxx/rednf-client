
function enableNewWalkShoot(obj)
{
	if (obj.sq_GetSkillLevel(64) > 0)
    {
		local isAppendApd = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atgunner/walkshoot/ap_walkshoot.nut");
		local state = obj.getState();
		if(state == 0 || state == 1)
			obj.setSkillCommandEnable(15,true);
		if(isAppendApd)
			obj.setSkillCommandEnable(15,false);
		local skillLevel = sq_GetSkillLevel(obj, 15);
		local time = sq_GetLevelData(obj, 15, 2, skillLevel);
		local isUseWalkShoot = obj.sq_IsEnterSkill(15);
		if(isUseWalkShoot != -1 && !isAppendApd)
		{
			local skill = sq_GetSkill(obj, 15);
			local isWalkShootCool = skill.isInCoolTime();
			local isUse = obj.sq_IsUseSkill(15);
			if(!isWalkShootCool && isUse)
			{
				obj.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, false);
				skill.resetCurrentCoolTime();
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 15, false, "character/atgunner/walkshoot/ap_walkshoot.nut", false);
				appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj),15,skillLevel);
				appendage.sq_SetValidTime(time);
				CNSquirrelAppendage.sq_Append(appendage, obj, obj);
			}
		}
		if(!isAppendApd) return;
		if(state == 8)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(49, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		local ani = obj.sq_GetCurrentAni();
		local isFlag = obj.sq_IsKeyFrameFlag(ani, 10001);
		if(isFlag)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(49, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		local attackBonus = obj.sq_GetBonusRateWithPassive(15, 49, 0, 1.0);
		local count = obj.getMyPassiveObjectCount(22275);
		for(local i=0;i<count;++i) 
		{
			local bullet = obj.getMyPassiveObject(22275,i);
			if(!bullet) continue;
			local attackInfo = sq_GetCurrentAttackInfo(bullet);
			sq_SetCurrentAttackBonusRate(attackInfo, attackBonus);
		}
	}
}

