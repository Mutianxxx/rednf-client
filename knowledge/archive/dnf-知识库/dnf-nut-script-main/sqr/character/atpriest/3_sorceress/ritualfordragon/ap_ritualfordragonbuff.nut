function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_RitualForDragonBuff")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_RitualForDragonBuff")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_RitualForDragonBuff")
}


function sq_AddEffect(appendage)
{

}

function proc_appendage_RitualForDragonBuff(appendage)
{
	if(!appendage) {
		return;		
	}
	
	local parentObj = appendage.getParent();
	if(!parentObj) {
		appendage.setValid(false);
		return;
	}
}


function onStart_appendage_RitualForDragonBuff(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	if(!parentObj) {
		appendage.setValid(false);
		return;
	}
}



function onEnd_appendage_RitualForDragonBuff(appendage)
{
	if (!appendage) {
		return;
	}	
		
	local parentObj = appendage.getParent();
	if (!parentObj) {
		appendage.setValid(false);
		return;
	}
}

