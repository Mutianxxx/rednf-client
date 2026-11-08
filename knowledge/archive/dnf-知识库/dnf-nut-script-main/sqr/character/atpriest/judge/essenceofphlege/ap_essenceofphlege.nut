function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_EssenceOfPhlege")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_EssenceOfPhlege")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_EssenceOfPhlege")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_EssenceOfPhlege")
}


function sq_AddEffect(appendage)
{
	if(!appendage) {
		return;
	}
}

function drawAppend_appendage_EssenceOfPhlege(appendage, isOver, x, y, isFlip)
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
 		local ani = appendage.getVar().GetAnimationMap("essenceofphlege", "character/priest/effect/animation/atessenceofphlege/teardebuff_02.ani");
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y - sq_GetObjectHeight(parentObj)/2, isFlip);
	}
}

function proc_appendage_EssenceOfPhlege(appendage)
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


function onStart_appendage_EssenceOfPhlege(appendage)
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



function onEnd_appendage_EssenceOfPhlege(appendage)
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

