
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ExtraHeart")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ExtraHeart")
}

function sq_AddEffect(appendage)
{
}


function proc_appendage_ExtraHeart(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

	local currT = appendage.getTimer().Get();

	if(!sourceObj || !parentObj || currT > 2500) 
	{
		appendage.setValid(false);
		return;
	}
	gbl_HoldAndDelayEffectSetByAppendageLoopNoClear(appendage);



}



function onStart_appendage_ExtraHeart(appendage)
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

