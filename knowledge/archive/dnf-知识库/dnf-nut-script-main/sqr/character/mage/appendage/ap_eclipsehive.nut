function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_eclipsehive")
	appendage.sq_AddFunctionName("proc", "proc_appendage_eclipsehive")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_eclipsehive")
}



function onStart_appendage_eclipsehive(appendage)
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

function proc_appendage_eclipsehive(appendage)
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

	local skill_level = sq_GetSkillLevel(parentObj, 170);
	local soften_number = sq_GetLevelData(parentObj, 170, 1, skill_level);
	local cooltime = sq_GetLevelData(parentObj, 170, 2, skill_level);
	cooltime = cooltime.tointeger();
	soften_number = soften_number.tointeger();
	
	local loadSlot = parentObj.sq_GetSkillLoad(170);
	if(!loadSlot){
		parentObj.sq_AddSkillLoad(170, 68, soften_number, cooltime);
		loadSlot = parentObj.sq_GetSkillLoad(170);
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
		if (remain_number > 0){
			local iEnterHodor = parentObj.sq_IsEnterSkill(25);
			local iEnterBabyDragon = parentObj.sq_IsEnterSkill(80);
			local iEnterSandor = parentObj.sq_IsEnterSkill(44);
			local iEnterSDH = parentObj.sq_IsEnterSkill(76);
			local iEnterSLH = parentObj.sq_IsEnterSkill(77);
			local iEnterSWH = parentObj.sq_IsEnterSkill(78);
			local iEnterSFH = parentObj.sq_IsEnterSkill(79);
			local iEnterLuis = parentObj.sq_IsEnterSkill(46);
			local iEnterEcheverra = parentObj.sq_IsEnterSkill(47);
			local iEnterSandorEx = parentObj.sq_IsEnterSkill(118);
			local send = 0;
			if(iEnterHodor != -1){
				send = sendState_EclipseHive(parentObj, 25);
			}
			else if(iEnterBabyDragon != -1){
				send = sendState_EclipseHive(parentObj, 80);
			}
			else if(iEnterSandor != -1){
				send = sendState_EclipseHive(parentObj, 44);
			}
			else if(iEnterSDH != -1){
				send = sendState_EclipseHive(parentObj, 76);
			}
			else if(iEnterSLH != -1){
				send = sendState_EclipseHive(parentObj, 77);
			}
			else if(iEnterSWH != -1){
				send = sendState_EclipseHive(parentObj, 78);
			}
			else if(iEnterSFH != -1){
				send = sendState_EclipseHive(parentObj, 79);
			}
			else if(iEnterLuis != -1){
				send = sendState_EclipseHive(parentObj, 46);
			}
			else if(iEnterEcheverra != -1){
				send = sendState_EclipseHive(parentObj, 47);
			}
			else if(iEnterSandorEx != -1){
				send = sendState_EclipseHive(parentObj, 118);
			}
			else{
				return;
			}
			if(send){
				loadSlot.decreaseLoadCount(1);
				loadSlot.setStartCool();
			}
		}
		else{
			local iEnterHodor = parentObj.sq_IsEnterSkill(25);
			local iEnterBabyDragon = parentObj.sq_IsEnterSkill(80);
			local iEnterSandor = parentObj.sq_IsEnterSkill(44);
			local iEnterSDH = parentObj.sq_IsEnterSkill(76);
			local iEnterSLH = parentObj.sq_IsEnterSkill(77);
			local iEnterSWH = parentObj.sq_IsEnterSkill(78);
			local iEnterSFH = parentObj.sq_IsEnterSkill(79);
			local iEnterLuis = parentObj.sq_IsEnterSkill(46);
			local iEnterEcheverra = parentObj.sq_IsEnterSkill(47);
			local iEnterSandorEx = parentObj.sq_IsEnterSkill(118);
			if(	iEnterHodor != -1 || 
				iEnterBabyDragon != -1 ||
				iEnterSandor != -1 ||
				iEnterSDH != -1 ||
				iEnterSLH != -1 ||
				iEnterSWH != -1 ||
				iEnterSFH != -1 ||
				iEnterLuis != -1 ||
				iEnterEcheverra != -1 ||
				iEnterSandorEx != -1){
			 		parentObj.startCantUseSkillWarning();
 					if (parentObj.isMessage())
 						sq_AddMessage(414);
 					parentObj.sq_PlaySound("WZ_NOMANA");
			}
		}
	}
}

//WZ_MASSTELEPORT

function onEnd_appendage_eclipsehive(appendage)
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
	if(parentObj && parentObj.isObjectType(OBJECTTYPE_CHARACTER)){
		local loadSlot = parentObj.sq_GetSkillLoad(170);
		if(loadSlot)
			parentObj.sq_RemoveSkillLoad(170);
	}
}

