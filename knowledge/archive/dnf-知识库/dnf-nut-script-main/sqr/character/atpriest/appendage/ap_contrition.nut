function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_Contrition")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_Contrition")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_Contrition")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_Contrition")
}


function sq_AddEffect(appendage)
{
	if(!appendage) {
		return;
	}
}

function drawAppend_appendage_Contrition(appendage, isOver, x, y, isFlip)
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
	
	if(isOver) 
	{
 		local ani = appendage.getVar().GetAnimationMap("contrition", "character/priest/effect/animation/hammerofcontrition/devil/buff1loop_00.ani");
		sq_AnimationProc(ani);
		ani.setImageRateFromOriginal(1.8, 1.8);
		local yPos = 0.95 * sq_GetObjectHeight(parentObj);
		sq_drawCurrentFrame(ani, x, y - yPos.tointeger(), isFlip);
	}
}

function proc_appendage_Contrition(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = appendage.getParent();
	local obj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	local object = sq_GetCNRDObjectToActiveObject(parentObj);
	if (!object || !obj) {
		appendage.setValid(false);
		return;
	}
	if(!sq_IsValidActiveStatus(object, ACTIVESTATUS_CONFUSE))
	{
		sq_sendSetActiveStatusPacket(object, obj, ACTIVESTATUS_CONFUSE, 100.0, 99, false, 10000, 0);
	}
}


function onStart_appendage_Contrition(appendage)
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



function onEnd_appendage_Contrition(appendage)
{
	if (!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local object = sq_GetCNRDObjectToActiveObject(parentObj);
	if (!object) {
		appendage.setValid(false);
		return;
	}
	if(sq_IsValidActiveStatus(object, ACTIVESTATUS_CONFUSE))
	{
		sq_ReleaseActiveStatus(object, ACTIVESTATUS_CONFUSE);
	}
	appendage.setValid(false);
	return;
}

