function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BlessOfAngel")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BlessOfAngel")
	appendage.sq_AddFunctionName("proc", "proc_appendage_BlessOfAngel")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_BlessOfAngel")
	appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_BlessOfAngel")
}

function drawAppend_appendage_BlessOfAngel(appendage, isOver, x, y, isFlip)
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
 		local ani = appendage.getVar().GetAnimationMap("blessofangel", "character/priest/effect/animation/atblessofangel/blessofangel_phase2loop_angelbodyloopdodge.ani");
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y - sq_GetObjectHeight(parentObj)*3/2, isFlip);
	}
}

function onStart_appendage_BlessOfAngel(appendage)
{
	if(!appendage) return
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if(!sourceObj || !parentObj) 
    {
		appendage.setValid(false);
		return;
	}
	local obj = appendage.getParent();
	obj = sq_GetCNRDObjectToActiveObject(obj);
	obj.sq_PlaySound("BLESSANGEL_GET");
	sq_AddDrawOnlyAniFromParent(obj,"character/priest/effect/animation/atblessofangel/blessofangel_phase2starteffect_shock.ani", 0, 1, 150);
	sq_AddDrawOnlyAniFromParent(obj,"character/priest/effect/animation/atblessofangel/blessofangel_phase2start_wingoutglow.ani", 0, -1, 150);
}

function onEnd_appendage_BlessOfAngel(appendage)
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
	if (!sq_IsInBattle())
	{
		appendage.setValid(false);
		return;
	}
	if (parentObj.isDead()) 
	{
		appendage.setValid(false);
		return;
	}
	local obj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	local PosX = sq_GetXPos(parentObj);
	local PosY = sq_GetYPos(parentObj);
	local PosZ = sq_GetZPos(parentObj);
	local ani = sq_AddDrawOnlyAniFromParent(parentObj, "character/priest/effect/animation/atblessofangel/blessofangel_phase2end_endeffect.ani", 0, -60, 0);
	sq_BinaryStartWrite();
	sq_BinaryWriteDword(63);
	sq_BinaryWriteDword(appendage.getVar("blessofangelbuff").get_vector(0));
	sq_BinaryWriteDword(appendage.getVar("blessofangelbuff").get_vector(1));
	sq_SendCreatePassiveObjectPacketPos(obj, 24240, 0, PosX, PosY, PosZ);
	appendage.setValid(false);
	return;
}

function proc_appendage_BlessOfAngel(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	if (!sq_IsInBattle())
	{
		appendage.setValid(false);
		return;
	}
	local pObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if (!pObj) {
		appendage.setValid(false);
		return;
	}
	local pState = pObj.sq_GetState();
	if(pState < 21)
	{
		appendage.getVar("pskill").clear_vector();
		appendage.getVar("pskill").push_vector(0);
	}
}

function onAttackParent_appendage_BlessOfAngel(appendage, realAttacker, damager, boundingBox, isStuck) {

	if (!appendage) return;
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	local obj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	local pObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	local maxNum = obj.sq_GetIntData(SKILL_BLESS_OF_ANGEL, 3);
	local nowNum = obj.getVar("BlessOfAngel").get_vector(0);
	local pState = pObj.sq_GetState();
	if(pState == STATE_STAND || pState == STATE_SIT || pState == STATE_SIT_FOREVER || pState == STATE_DAMAGE || pState == STATE_DOWN || pState == STATE_DIE || pState == STATE_JUMP || pState == STATE_JUMP_ATTACK || pState == STATE_ATTACK || pState == STATE_HOLD || pState == STATE_DASH || pState == STATE_DASH_ATTACK || pState == STATE_GET_ITEM)
	{
		return;
	}
	else{
		local lastSkillIndex = appendage.getVar("pskill").get_vector(0);
		if(lastSkillIndex < 1)
		{
			appendage.getVar("pskill").set_vector(0, pObj.getCurrentSkillIndex());
		}
		if(lastSkillIndex != pObj.getCurrentSkillIndex())
		{
			if (nowNum < maxNum) {
				obj.getVar("BlessOfAngel").set_vector(0, nowNum + 1);
			}
		}
	}
}

