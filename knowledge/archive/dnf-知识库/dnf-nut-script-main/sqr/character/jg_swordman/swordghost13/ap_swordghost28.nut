
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_swordghost28")
	appendage.sq_AddFunctionName("prepareDraw", "prepareDraw_appendage_swordghost28")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_swordghost28")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_swordghost28")
	appendage.sq_AddFunctionName("isEnd", "isEnd_appendage_swordghost28")
}


function sq_AddEffect(appendage)
{
}




function proc_appendage_swordghost28(appendage)
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


function onStart_appendage_swordghost28(appendage)
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


function prepareDraw_appendage_swordghost28(appendage)
{
	if(!appendage) {
		return;
	}
	
	local obj = appendage.getParent();	
}




function onEnd_appendage_swordghost28(appendage)
{
	if(!appendage) {
		return;
	}
	
	local obj = appendage.getParent();
	
}


// ?????? ?????? ????????? ???????
function isEnd_appendage_swordghost28(appendage)
{	
	return false;
}