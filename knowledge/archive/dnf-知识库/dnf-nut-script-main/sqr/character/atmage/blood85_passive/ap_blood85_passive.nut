function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BLOOD85_PASSIVE")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BLOOD85_PASSIVE")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BLOOD85_PASSIVE")
}


function sq_AddEffect(appendage)
{
}

function proc_appendage_BLOOD85_PASSIVE(appendage)
{
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();	

	
}


function onStart_appendage_BLOOD85_PASSIVE(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();	

}



function onEnd_appendage_BLOOD85_PASSIVE(appendage)
{
	if(!appendage) {
		return;
	}
	
	local obj = appendage.getParent();
}

