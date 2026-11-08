function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_attack_thief")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_attack_thief")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_attack_thief")
}


function sq_AddEffect(appendage)
{
	if(!appendage) {
		return;
	}
}

function proc_appendage_attack_thief(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	parentObj = sq_GetCNRDObjectToActiveObject(parentObj);
	sourceObj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	
	local currTime = appendage.getTimer().Get();
	parentObj.setDirection(sourceObj.getDirection());
	if (currTime - appendage.getVar("monsterTime").getInt(0) > 1000)
	{
		appendage.getVar("monsterTime").setInt(0,currTime);
		appendage.setValid(false);
	}
}


function onStart_appendage_attack_thief(appendage)
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



function onEnd_appendage_attack_thief(appendage)
{
	if (!appendage) {
		return;
	}	
		
	local parentObj = appendage.getParent();	
	local sourceObj = appendage.getSource();
	sourceObj = sq_GetCNRDObjectToSQRCharacter(sourceObj);		
	if (!sourceObj) {
		appendage.setValid(false);
		return;
	}	
}


