function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BLOODFIRE")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BLOODFIRE")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BLOODFIRE")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_BLOODFIRE")
}


function sq_AddEffect(appendage)
{
	if(!appendage) {
		return;
	}
	//appendage.sq_AddEffectFront("sqr/character/atmage/bloodfire/bloodfire.ani");
}

function drawAppend_appendage_BLOODFIRE(appendage, isOver, x, y, isFlip)
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
 		local ani = appendage.getVar().GetAnimationMap("bloodfire", "sqr/character/atmage/bloodfire/bloodfire.ani");
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y - sq_GetObjectHeight(parentObj)*3/10, isFlip);
	}
}

function proc_appendage_BLOODFIRE(appendage)
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


function onStart_appendage_BLOODFIRE(appendage)
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



function onEnd_appendage_BLOODFIRE(appendage)
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

