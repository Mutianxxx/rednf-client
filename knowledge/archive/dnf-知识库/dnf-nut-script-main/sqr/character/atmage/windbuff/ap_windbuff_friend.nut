function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_WINDBUFF_FRIEND")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_WINDBUFF_FRIEND")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_WINDBUFF_FRIEND")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_WINDBUFF_FRIEND")
}


function sq_AddEffect(appendage)
{
	if(!appendage) {
		return;
	}
	//appendage.sq_AddEffectFront("character/mage/atanimation/als_ani/atwindiness/windiness_shield_loop.ani");
}

function drawAppend_appendage_WINDBUFF_FRIEND(appendage, isOver, x, y, isFlip)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!parentObj) {
		//appendage.setValid(false);
		return;
	}	
	local ani = appendage.getVar().GetAnimationMap("windbufff", "character/mage/atanimation/als_ani/atwindiness/windiness_shield_loop.ani");
	if(ani&&isOver) 
	{
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y, isFlip);
	}
}

function proc_appendage_WINDBUFF_FRIEND(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!parentObj) {
		//appendage.setValid(false);
		return;
	}	
}


function onStart_appendage_WINDBUFF_FRIEND(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!parentObj) {
		//appendage.setValid(false);
		return;
	}	

}



function onEnd_appendage_WINDBUFF_FRIEND(appendage)
{
	if (!appendage) {
		return;
	}	
		
	local parentObj = appendage.getParent();	
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);		
	if (!parentObj) {
		appendage.setValid(false);
		return;
	}	
}

