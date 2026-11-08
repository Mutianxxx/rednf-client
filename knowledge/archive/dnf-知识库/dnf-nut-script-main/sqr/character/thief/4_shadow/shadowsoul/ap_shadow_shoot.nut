
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ShadowSoulShoot")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ShadowSoulShoot")
}
function sq_AddEffect(appendage)
{
}



function proc_appendage_ShadowSoulShoot(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

	if(!sourceObj || !parentObj || sourceObj.getState() != STATE_SHADOW_SOUL)
	{
		appendage.setValid(false);
		return;
	}
	gbl_HoldAndDelayEffectSetByAppendageLoop(appendage);


	local currT = appendage.getTimer().Get();


}



function onStart_appendage_ShadowSoulShoot(appendage)
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

