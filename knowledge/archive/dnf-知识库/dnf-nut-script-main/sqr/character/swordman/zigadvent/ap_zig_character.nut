//////////////////////////////////////////////////////////////////////////////////////////////////
//									By Uncle Bang
//////////////////////////////////////////////////////////////////////////////////////////////////








function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_zig_character")
	appendage.sq_AddFunctionName("proc", "proc_appendage_zig_character")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_zig_character")
}



function sq_AddEffect(appendage)
{
}



function onStart_appendage_zig_character(appendage)
{
	if(!appendage || !appendage.isValid())
	{
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = sq_ObjectToSQRCharacter(sourceObj);
	if(!sourceObj || !parentObj || parentObj.isDead())
	{
		appendage.setValid(false);
		return;
	}
}



function proc_appendage_zig_character(appendage)
{
	if(!appendage || !appendage.isValid())
	{
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = sq_ObjectToSQRCharacter(sourceObj);
	if(!sourceObj || !parentObj || parentObj.isDead())
	{
		appendage.setValid(false);
		return;
	}
}



function onEnd_appendage_zig_character(appendage)
{
	if(!appendage || !appendage.isValid())
	{
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = sq_ObjectToSQRCharacter(sourceObj);
	if(!sourceObj || !parentObj || parentObj.isDead())
	{
		appendage.setValid(false);
		return;
	}
}

