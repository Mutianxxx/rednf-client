function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_talismanoflightning")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_talismanoflightning")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_talismanoflightning")
}

function proc_appendage_talismanoflightning(appendage)
{
	if(!appendage)
	{
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	
	local currTime = appendage.getTimer().Get();
	local time = currTime - appendage.getVar("monsterTime").getInt(0);
	local obj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	local damager = sq_GetCNRDObjectToActiveObject(parentObj);
	local xPos = sq_GetZPos(damager);
	local yPos = sq_GetZPos(damager);
	local zPos = sq_GetZPos(damager);
	local targetId = sq_GetObjectId(damager);
	if (time > 200 && sq_GetZPos(damager) < 11)
	{
		appendage.getVar("monsterTime").setInt(0,currTime);
		
		sq_BinaryStartWrite();
		sq_BinaryWriteDword(201);
		sq_BinaryWriteDword(targetId);
		sq_SendCreatePassiveObjectPacketPos(obj,24240, 0, xPos, yPos, zPos);
		appendage.setValid(false);
	}
}

function onStart_appendage_talismanoflightning(appendage)
{
	if(!appendage)
	{
		return;
	}
	local parentObj = appendage.getParent();
	if(!parentObj) 
	{
		appendage.setValid(false);
		return;
	}
	local currTime = appendage.getTimer().Get();
	appendage.getVar("monsterTime").setInt(0,currTime);
}


function onEnd_appendage_talismanoflightning(appendage)
{
	if(!appendage)
	{
		return;
	}
	appendage.sq_DeleteAppendages();
	return;
}


