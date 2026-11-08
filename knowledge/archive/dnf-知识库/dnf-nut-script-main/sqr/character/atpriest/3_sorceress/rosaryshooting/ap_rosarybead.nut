

function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart" ,  "onStart_appendage_rosarybead")
	appendage.sq_AddFunctionName("proc" ,  "proc_appendage_rosarybead")
	appendage.sq_AddFunctionName("onEnd" ,  "onEnd_appendage_rosarybead")
}

function onStart_appendage_rosarybead(appendage)
{
	if (!appendage) return;
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if (!sourceObj || !parentObj)
	{
		appendage.setValid(false);
		return;
	}
	local skill_level = sq_GetSkillLevel(parentObj, SKILL_ROSARYSHOOTING);
	
	if(skill_level < 1 || sq_getJob(parentObj) != ENUM_CHARACTERJOB_AT_PRIEST){
		appendage.setValid(false);
		return;
	}
	local count = 6;
	local cooltime = sq_GetLevelData(parentObj, SKILL_ROSARYSHOOTING, 0, skill_level);
	local skillLoad = parentObj.sq_GetSkillLoad(SKILL_ROSARYSHOOTING);
	if (!skillLoad){
		parentObj.sq_AddSkillLoad(SKILL_ROSARYSHOOTING, 113, count, cooltime);
	}
	for (local i = 1; i <= 6; i++)
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(3);
		parentObj.sq_WriteDword(1);
		parentObj.sq_WriteDword(i);
		parentObj.sq_SendCreatePassiveObjectPacket(24338, 0, 0, 0, 0);
	}
}

function proc_appendage_rosarybead(appendage)
{
	if (!appendage) return;
	local Value1 = appendage.getParent();
	local Value2 = appendage.getSource();
	local Value1 = sq_GetCNRDObjectToSQRCharacter(Value1);
	if (!Value2 || !Value1 || Value1.isDead())
	{
		appendage.setValid(false);
		return;
	}
	local Value4 = Value1.sq_GetSkillLoad(234);
	if (Value4)
	{
		local Value5 = 6;
		local Value6 = Value4.getRemainLoadNumber();
		if (Value6 < Value5 && Value1.getVar("rosaryBeadStartCooling").getInt(0) == 1)
		{
			Value4.setStartCool();
			Value1.getVar("rosaryBeadStartCooling").setInt(0, 0);
		}
		if (Value6 < Value5 && !Value4.isCooling())
		{
			Value1.getVar("rosaryBeadStartCooling").setInt(0, 1);
			Value4.increaseLoadCount(1);
		}
	}
}

function onEnd_appendage_rosarybead(appendage)
{
	if(!appendage) return;
	local Value1 =  appendage.getParent();
	if(!Value1)
	{
		appendage.setValid(false);
		return;
	}
	local Value1 =  sq_GetCNRDObjectToSQRCharacter(Value1);
	local Value3 =  Value1.sq_GetSkillLoad(234);
	if(Value3)
		Value1.sq_RemoveSkillLoad(234);
	appendage.sq_DeleteAppendages();
}



