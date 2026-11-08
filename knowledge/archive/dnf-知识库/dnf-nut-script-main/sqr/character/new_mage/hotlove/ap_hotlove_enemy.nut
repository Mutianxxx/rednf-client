
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_HOTLOVE_ENEMY")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_HOTLOVE_ENEMY")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_HOTLOVE_ENEMY")
}



function sq_AddEffect(appendage)
{
	//appendage.sq_AddEffectFront("character/mage/animation/ani_als/hotlove/hotlove_enemyattack_00.ani");
	//appendage.sq_AddEffectFront("character/mage/animation/ani_als/hotlove/hotlove_09.ani");
}

function drawAppend_appendage_HOTLOVE_ENEMY(appendage, isOver, x, y, isFlip) {
	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}

	local anifa = appendage.getVar().GetAnimationMap("hotlovefea", "character/mage/animation/ani_als/hotlove/hotlove_enemyattack_00.ani");
	local anifb = appendage.getVar().GetAnimationMap("hotlovefeb", "character/mage/animation/ani_als/hotlove/hotlove_09.ani");

	if (anifa && isOver) {
		sq_AnimationProc(anifa);
		sq_AnimationProc(anifb);
		sq_drawCurrentFrame(anifa, x, y, isFlip);
		sq_drawCurrentFrame(anifb, x, y, isFlip);
	}

}

function proc_appendage_HOTLOVE_ENEMY(appendage)
{
	if(!appendage) {
		return;		
	}


}



function onStart_appendage_HOTLOVE_ENEMY(appendage)
{
}

