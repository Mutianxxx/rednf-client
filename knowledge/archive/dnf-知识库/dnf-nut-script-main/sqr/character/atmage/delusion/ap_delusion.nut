function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_Delusion")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_Delusion")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_Delusion")
}

function sq_AddEffect(appendage)
{

}

function drawAppend_appendage_Delusion(appendage, isOver, x, y, isFlip)
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
	
 	local ani = appendage.getVar().GetAnimationMap("delusion", "character/mage/atanimation/als_ani/atdelusion/delusion_body.ani");
	if(ani&&isOver) 
	{
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y, isFlip);
	}
}

function proc_appendage_Delusion(appendage)
{
	if(!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj) 
    	{
		appendage.setValid(false);
		return;
	}
}


function onStart_appendage_Delusion(appendage)
{
	if(!appendage) {
		return;
	}
	
}


