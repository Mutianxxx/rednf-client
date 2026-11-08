function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_revive_hold")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_revive_hold")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_revive_hold")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_revive_hold")
}


function drawAppend_appendage_revive_hold(appendage, isOver, x, y, isFlip) {
	if (!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	local anif = appendage.getVar().GetAnimationMap("helpui", "character/priest/effect/animation/atrevive/helpui/help_up_00.ani");
	if (anif && isOver) {
		sq_AnimationProc(anif);
		sq_drawCurrentFrame(anif, x, y, isFlip);
	}
}

function proc_appendage_revive_hold(appendage)
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
	local currTime = appendage.getTimer().Get();
	local recHp = appendage.getVar("revive").get_vector(0);
	local maxTime = appendage.getVar("revive").get_vector(1);
	local reviveOn = appendage.getVar("revive").get_vector(2);
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(parentObj);
	sqrChr.setEnableDamageBox(0);
	sqrChr.setHp(1, null, true);
	sq_SetCustomRotate(sqrChr, 1.57);
	if(reviveOn > 0)
	{
		sq_AddDrawOnlyAniFromParent(sqrChr,"character/priest/effect/animation/atrevive/usereffect_01.ani", 0, 1, 0);
		local subHp = recHp * sqrChr.getHpMax() / 1000;
		subHp = subHp.tointeger();
		sqrChr.setHp(subHp, null, true);
		sqrChr.setEnableDamageBox(1);
		sq_SetCustomRotate(sqrChr, 0.0);
		appendage.setValid(false);
	}
	if(sq_IsMyCharacter(sqrChr) && sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
	{
		sqrChr.setEnableDamageBox(1);
		local oldAppend = sqrChr.GetSquirrelAppendage("character/atpriest/revive/ap_revive.nut");
		if(oldAppend)
		{
			oldAppend.setValid(false);
		}
		sqrChr.setHp(0, null, true);
		sq_SetCustomRotate(sqrChr, 0.0);
		appendage.setValid(false);
	}
	if (currTime - appendage.getVar("monsterTime").getInt(0) > maxTime)
	{
		appendage.getVar("monsterTime").setInt(0,currTime);
		sqrChr.setEnableDamageBox(1);
		local oldAppend = sqrChr.GetSquirrelAppendage("character/atpriest/revive/ap_revive.nut");
		if(oldAppend)
		{
			oldAppend.setValid(false);
		}
		sqrChr.setHp(0, null, true);
		sq_SetCustomRotate(sqrChr, 0.0);
		appendage.setValid(false);
	}
}


function onStart_appendage_revive_hold(appendage)
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
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	parentObj.setEnableDamageBox(0);
	local currTime = appendage.getTimer().Get();
	appendage.getVar("monsterTime").setInt(0,currTime);
	local recHp = appendage.getVar("revive").get_vector(0);
	local maxTime = appendage.getVar("revive").get_vector(1);
	local reviveOn = appendage.getVar("revive").get_vector(2);
}



function onEnd_appendage_revive_hold(appendage)
{
	if (!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	parentObj.setEnableDamageBox(1);
	sq_SetCustomRotate(parentObj, 0.0);
	appendage.sq_DeleteAppendages();
	return;
}
