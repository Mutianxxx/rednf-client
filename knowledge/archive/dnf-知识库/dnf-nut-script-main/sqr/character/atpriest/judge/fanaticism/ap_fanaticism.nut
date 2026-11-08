function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_Fanaticism")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_Fanaticism")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_Fanaticism")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_Fanaticism")
}


function sq_AddEffect(appendage)
{
	if(!appendage) {
		return;
	}
}

function drawAppend_appendage_Fanaticism(appendage, isOver, x, y, isFlip)
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
	
	if(!isOver) 
	{
 		local ani = appendage.getVar().GetAnimationMap("fanaticism", "character/priest/effect/animation/atfanaticism/fanaticismbuff.ani");
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y, isFlip);
	}
}

function proc_appendage_Fanaticism(appendage)
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


function onStart_appendage_Fanaticism(appendage)
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



function onEnd_appendage_Fanaticism(appendage)
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

