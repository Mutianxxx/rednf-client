//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////

function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_firehide");
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_firehide");
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_firehide");
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_firehide")
}

function sq_AddEffect(appendage)
{
	if(!appendage) {
		return;
	}
	//appendage.sq_AddEffectFront("character/thief/effect/animation/firehide/firehide_fire.ani");
}

function drawAppend_appendage_firehide(appendage, isOver, x, y, isFlip)
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
	

 	local anif = appendage.getVar().GetAnimationMap("firehidef", "character/thief/effect/animation/firehide/firehide_fire_front_01.ani");
 	local anib = appendage.getVar().GetAnimationMap("firehideb", "character/thief/effect/animation/firehide/firehide_fire_back_01.ani");

	if (anif && isOver) {		
		sq_AnimationProc(anif);
		sq_drawCurrentFrame(anif, x, y - sq_GetObjectHeight(parentObj)*2/5, isFlip);
	}	
	else if (anib && !isOver) {
		sq_AnimationProc(anib);
		sq_drawCurrentFrame(anib, x, y - sq_GetObjectHeight(parentObj)*2/5, isFlip);
	}
}

function proc_appendage_firehide(appendage)
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

        //front.setCurrentPos(parentObj.getXPos(),parentObj.getYPos() + 1,parentObj.getZPos() + parentObj.getObjectHeight()/2);
        //back.setCurrentPos(parentObj.getXPos(),parentObj.getYPos() - 1,parentObj.getZPos() + parentObj.getObjectHeight()/2);
}

function onStart_appendage_firehide(appendage)
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



function onEnd_appendage_firehide(appendage)
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

