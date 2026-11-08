
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_HolyLight")
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_HolyLight")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_HolyLight")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_HolyLight")
	appendage.sq_AddFunctionName("onDamageParent", "onDamageParent_appendage_HolyLight")
}

function drawAppend_appendage_HolyLight(appendage, isOver, x, y, isFlip)
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
		
		local aniA = appendage.getVar().GetAnimationMap("barrieromen", "character/priest/effect/animation/atholylight/barrier/barrierloop_omen.ani");
		local aniB = appendage.getVar().GetAnimationMap("barriertwinkle", "character/priest/effect/animation/atholylight/barrier/particle_twinkle.ani");
		local aniC = appendage.getVar().GetAnimationMap("barrierloop", "character/priest/effect/animation/atholylight/barrier/barrierloop.ani");
		sq_AnimationProc(aniA);
		sq_drawCurrentFrame(aniA, x, y - sq_GetObjectHeight(parentObj)/2, isFlip);
		
		sq_AnimationProc(aniB);
		sq_drawCurrentFrame(aniB, x, y - sq_GetObjectHeight(parentObj)/2, isFlip);
		
		sq_AnimationProc(aniC);
		sq_drawCurrentFrame(aniC, x, y, isFlip);
		
	}
}

function getImmuneTypeDamageRate_appendage_HolyLight(appendage, damageRate, attacker) {
	if (!appendage)
		return damageRate;
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if (!sourceObj || !parentObj) {
		return damageRate;
	}
	if (!sq_IsInBattle())
	{
		appendage.setValid(false);
		return damageRate;
	}
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if(parentObj.isEnemy(attacker)){
		local attackerInfo = sq_GetCurrentAttackInfo(attacker);
		if (attackerInfo) {
			sq_SetAttackInfoHitDelayRateDamager(attackerInfo, 0.0);
			sq_SetCurrentAttackeDamageAct(attackerInfo, DAMAGEACT_NONE);
		}
	}
	
	local decreaseRatePhy = appendage.getVar("holylightbuff").get_vector(0) / 10;
	local decreaseRateMag = appendage.getVar("holylightbuff").get_vector(1) / 10;
	damageRate = damageRate - (decreaseRatePhy + decreaseRateMag)/2;
	if (damageRate < 0) {
		damageRate = 0;
	}
	damageRate = damageRate.tointeger();
	return damageRate;
}

function onDamageParent_appendage_HolyLight(appendage ,attacker, boundingBox, isStuck) 
{
	if(!appendage) {
		appendage.setValid(false);
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	local ani = sq_AddDrawOnlyAniFromParent(parentObj, "character/priest/effect/animation/atholylight/barrier/hiteffect.ani", 0, -60, 0);
	sq_moveWithParent(parentObj, ani);
	
	local attackerInfo = sq_GetCurrentAttackInfo(attacker);
	if (attackerInfo) {
		sq_SetAttackInfoHitDelayRateDamager(attackerInfo, 0.0);
		sq_SetCurrentAttackeDamageAct(attackerInfo, DAMAGEACT_NONE);
	}
}

function onStart_appendage_HolyLight(appendage)
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
	obj = sq_GetCNRDObjectToSQRCharacter(obj);
	obj.sq_PlaySound("HOLYLIGHT_LOOP",8889);
	local ani = sq_AddDrawOnlyAniFromParent(parentObj, "character/priest/effect/animation/atholylight/barrier/barrierstart.ani", 0, -60, 0);
}

function onEnd_appendage_HolyLight(appendage)
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
	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	obj.stopSound(8889);
	if (parentObj.isDead()) 
	{
		appendage.setValid(false);
		return;
	}
	local ani = sq_AddDrawOnlyAniFromParent(obj, "character/priest/effect/animation/atholylight/barrier/barrierend_barrierend.ani", 0, -60, 0);
	
	obj.sq_StartWrite();
	obj.sq_WriteDword(62);
	obj.sq_WriteDword(appendage.getVar("holylightbuff").get_vector(2));
	obj.sq_WriteDword(appendage.getVar("holylightbuff").get_vector(3));
	obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 70);
}
