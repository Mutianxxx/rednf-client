function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_leavetrace")
	appendage.sq_AddFunctionName("proc", "proc_appendage_leavetrace")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_leavetrace")
}



function onStart_appendage_leavetrace(appendage)
{
	if(!appendage) return;

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if(!sourceObj || !parentObj)
	{
		appendage.setValid(false);
		return;
	}
}

function proc_appendage_leavetrace(appendage)
{
	if(!appendage) return;

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if(!sourceObj || !parentObj || parentObj.isDead())
	{
		appendage.setValid(false);
		return;
	}

	local skill_level = sq_GetSkillLevel(parentObj, SKILL_LEAVETRACE);
	local skill_level1 = sq_GetSkillLevel(parentObj,123);
	//local skill_level_bonus = sq_GetSkillLevel(parentObj, SKILL_WOODMOVE);
	local soften_number = sq_GetLevelData(parentObj, SKILL_LEAVETRACE, 0, skill_level);
	local cooltime = sq_GetLevelData(parentObj, SKILL_LEAVETRACE, 1, skill_level);
	//local cooltime_bonus = sq_GetLevelData(parentObj, SKILL_WOODMOVE, 0, skill_level_bonus).tofloat();
	local cooltime_rate = sq_GetLevelData(parentObj, 123, 0, skill_level1);
	cooltime_rate = cooltime_rate+100;
	if(skill_level1>0){
		//cooltime_bonus = cooltime_bonus + (cooltime*sq_GetLevelData(parentObj, 123, 0, skill_level1))/100
		soften_number = soften_number + sq_GetLevelData(parentObj, 123, 1, skill_level1);
		cooltime = 100*cooltime/cooltime_rate;
	}
	cooltime = cooltime.tointeger();
	soften_number = soften_number.tointeger();
	
	local loadSlot = parentObj.sq_GetSkillLoad(88);
	if(!loadSlot){
		parentObj.sq_AddSkillLoad(88, 66, soften_number, cooltime);
		loadSlot = parentObj.sq_GetSkillLoad(88);
	}
	else
	{
		local remain_number = loadSlot.getRemainLoadNumber();
		if(!loadSlot.isCooling())
		{
			if(remain_number < soften_number)
			{
				loadSlot.increaseLoadCount(1);
				if(loadSlot.getRemainLoadNumber() < soften_number)
					loadSlot.setStartCool();
			}
		}
	}
}



function onEnd_appendage_leavetrace(appendage)
{
	if(!appendage) return;

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if(!sourceObj || !parentObj) 
	{
		appendage.setValid(false);
		return;
	}
	local parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	try
	{
		local loadSlot = parentObj.sq_GetSkillLoad(88);
		if(loadSlot)
			parentObj.sq_RemoveSkillLoad(88);
	}
	catch(ex)
	{
	}
}

