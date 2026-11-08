function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_NEARBLOW")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_NEARBLOW")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_NEARBLOW")
}


function sq_AddEffect(appendage)
{
	if(!appendage) {
		return;
	}
}

function proc_appendage_NEARBLOW(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	
	local currTime = appendage.getTimer().Get();
	if (currTime - appendage.getVar("monsterTime").getInt(0) > 1000)
	{
		appendage.getVar("monsterTime").setInt(0,currTime);
		appendage.setValid(false);
	}
}


function onStart_appendage_NEARBLOW(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	
	local currTime = appendage.getTimer().Get();
	appendage.getVar("monsterTime").setInt(0,currTime);

}



function onEnd_appendage_NEARBLOW(appendage)
{
	if (!appendage) {
		return;
	}	
		
	local parentObj = appendage.getParent();	
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);		
	if (!parentObj) {
		appendage.setValid(false);
		return;
	}	
}


