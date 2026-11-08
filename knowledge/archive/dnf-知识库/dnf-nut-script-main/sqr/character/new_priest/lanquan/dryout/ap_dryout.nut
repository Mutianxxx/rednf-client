
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_dryout")
	appendage.sq_AddFunctionName("proc", "proc_appendage_dryout")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_dryout")
//sq_AddMessage(55);
}



function onStart_appendage_dryout(appendage)
{
	if(!appendage) return;
	local parentObj = appendage.getParent();
	if(!parentObj) 
	{
		appendage.setValid(false);
		return;
	}
	
	local CQmQPIrGh947n6Q9D8 = appendage.sq_GetSourceChrTarget();
}



function proc_appendage_dryout(appendage)
{
	if(!appendage) return;
	local parentObj = appendage.getParent();
	if(!parentObj) 
	{
		appendage.setValid(false);
		return;
	}
	local parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);

	local level = sq_GetSkillLevel(parentObj, 87);
	local soften_number = sq_GetIntData(parentObj, 87, 0);
	soften_number = soften_number.tointeger();


	local cooltime = sq_GetIntData(parentObj, 87, 1);
	cooltime = cooltime.tointeger();


	local loadSlot = parentObj.sq_GetSkillLoad(87)
	if(!loadSlot)
	{
		parentObj.sq_AddSkillLoad(87, 78, soften_number, cooltime);
		loadSlot = parentObj.sq_GetSkillLoad(87);

	}
	else
	{
		local remain_number = loadSlot.getRemainLoadNumber();
		if(!loadSlot.isCooling())
		{
			if(remain_number < soften_number)
			{
				loadSlot.increaseLoadCount(1)
				if(loadSlot.getRemainLoadNumber() < soften_number)
					loadSlot.setStartCool();
			}
		}
	}
}



function onEnd_appendage_dryout(appendage)
{
	if(!appendage) return;
	local parentObj = appendage.getParent();
	if(!parentObj)
	{
		appendage.setValid(false);
		return;
	}
	local parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	local loadSlot = parentObj.sq_GetSkillLoad(87);
	if(loadSlot)
		parentObj.sq_RemoveSkillLoad(87);
}

