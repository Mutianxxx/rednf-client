
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_Favorite")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_Favorite")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_Favorite")
}



function sq_AddEffect(appendage)
{
}

function drawAppend_appendage_Favorite(appendage, isOver, x, y, isFlip) {
	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}

	local anif = appendage.getVar().GetAnimationMap("favoritef", "character/mage/animation/ani_als/favoritism/favoritism_s_heart_00.ani");

	if (anif && isOver) {
		sq_AnimationProc(anif);
		sq_drawCurrentFrame(anif, x, y, isFlip);
	}
}

function proc_appendage_Favorite(appendage)
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
	local obj = appendage.getParent();
	local sqrObj = sq_GetCNRDObjectToSQRCharacter(obj);
}

function onStart_appendage_Favorite(appendage)
{

}

