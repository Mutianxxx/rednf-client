function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_bigweaponmastery")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_bigweaponmastery")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_bigweaponmastery")
}

function proc_appendage_bigweaponmastery(appendage)
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


function onStart_appendage_bigweaponmastery(appendage)
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
}


function onEnd_appendage_bigweaponmastery(appendage)
{
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
}
