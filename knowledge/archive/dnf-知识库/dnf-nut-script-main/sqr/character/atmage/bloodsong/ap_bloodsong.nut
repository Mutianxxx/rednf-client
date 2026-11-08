
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BLOODSONG")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BLOODSONG")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BLOODSONG")
}

function sq_AddEffect(appendage)
{
}



function onEnd_appendage_BLOODSONG(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

}


function proc_appendage_BLOODSONG(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
    parentObj = sq_GetCNRDObjectToActiveObject(parentObj);
				
	if(!sourceObj || !parentObj || sourceObj.getState() != STATE_BLOODSONG) 
    {
		appendage.setValid(false);
		return;
	}
    local currentAni = sq_GetCurrentAnimation(parentObj);
    currentAni.setEffectLayer(true, GRAPHICEFFECT_NONE, true, sq_RGB(0, 0, 0), sq_ALPHA(255), true, false);

	sourceObj = sq_GetCNRDObjectToSQRCharacter(sourceObj);

    local currentAni2 = sq_GetCurrentAnimation(sourceObj);
	local frmIndex = sourceObj.sq_GetCurrentFrameIndex(currentAni2);
    if (frmIndex >= 20)
    {
		appendage.setValid(false);
		return;
    }

}



function onStart_appendage_BLOODSONG(appendage)
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

