function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_EventHorizen")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_EventHorizen")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_EventHorizen")
}


function sq_AddEffect(appendage)
{

}

function proc_appendage_EventHorizen(appendage)
{

	local obj = appendage.getParent();
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();	
	
}


function onStart_appendage_EventHorizen(appendage)
{
	if(!appendage) {
		return;
	}
	


}



function onEnd_appendage_EventHorizen(appendage)
{
	if(!appendage) {
		return;
	}
	
	local obj = appendage.getParent();
}

