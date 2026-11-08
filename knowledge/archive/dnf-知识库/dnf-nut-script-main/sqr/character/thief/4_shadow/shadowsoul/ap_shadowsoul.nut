
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ShadowSoul")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ShadowSoul")
}
function sq_AddEffect(appendage)
{
}



function proc_appendage_ShadowSoul(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

	if(!sourceObj || !parentObj)
	{
		appendage.setValid(false);
		return;
	}
}



function onStart_appendage_ShadowSoul(appendage)
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

	appendage.getVar("CoolTimeSkill").clear_vector();
	appendage.getVar("CoolTimeSkill").push_vector(-9999);
	appendage.getVar("CoolTimeSkill").push_vector(-9999);
}

