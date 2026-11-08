function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_FlowerOfPurificationBuff")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_FlowerOfPurificationBuff")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_FlowerOfPurificationBuff")
}


function sq_AddEffect(appendage)
{

}

function proc_appendage_FlowerOfPurificationBuff(appendage)
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


function onStart_appendage_FlowerOfPurificationBuff(appendage)
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



function onEnd_appendage_FlowerOfPurificationBuff(appendage)
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

