function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_blessofcourage")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_blessofcourage")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_blessofcourage")
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_blessofcourage(appendage)
{
	if(!appendage) {
		return;
	}
	local obj = appendage.getParent();
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
}

function onStart_appendage_blessofcourage(appendage)
{
	if(!appendage)
	{
		return;
	}
	local obj = appendage.getParent();
}

function onEnd_appendage_blessofcourage(appendage)
{
	if(!appendage) {
		return;
	}
	local obj = appendage.getParent();
}

