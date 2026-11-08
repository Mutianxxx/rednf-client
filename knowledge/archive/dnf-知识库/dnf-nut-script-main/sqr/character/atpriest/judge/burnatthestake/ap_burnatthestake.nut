function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BurnAtThestake")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BurnAtThestake")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BurnAtThestake")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_BurnAtThestake")
}


function sq_AddEffect(appendage)
{
	if(!appendage) {
		return;
	}
}

function drawAppend_appendage_BurnAtThestake(appendage, isOver, x, y, isFlip)
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
		local ani = appendage.getVar().GetAnimationMap("dot", "character/priest/effect/animation/atdot/dot1.ani");
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y - sq_GetObjectHeight(parentObj)/2, isFlip);
	}
}

function proc_appendage_BurnAtThestake(appendage)
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
	
	local obj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	local damager = sq_GetCNRDObjectToActiveObject(parentObj);
	if(!obj || !damager) {
		return;
	}
	
	local time = obj.sq_GetIntData(SKILL_PATROLBOMB, 0);
	local timeMax = obj.sq_GetIntData(SKILL_PATROLBOMB, 2);
	local currTime = appendage.getTimer().Get();
	
	local append = "character/atpriest/judge/essenceofphlege/ap_essenceofphlege.nut";
	if (damager.IsSquirrelAppendage(append))
	{
		local remainder = timeMax - currTime;
		local timeBonus = 0;
		if(remainder > 0)
		{
			timeBonus = remainder.tofloat() / time;
		}
		
		local holyFlameRate = obj.sq_GetIntData(SKILL_PATROLBOMB, 3).tofloat();
		holyFlameRate = timeBonus * holyFlameRate / 100.0;
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BURNATTHESTAKE, -1, 0, holyFlameRate) + obj.sq_GetBonusRateWithPassive(SKILL_BURNATTHESTAKE, -1, 1, holyFlameRate) + obj.sq_GetBonusRateWithPassive(SKILL_BURNATTHESTAKE, -1, 2, holyFlameRate); 
		local attackInfo = sq_getNewAttackInfoPacket();
		attackInfo.useWeapon = true;
		attackInfo.powerRate = attackBonusRate;
		attackInfo.element = ENUM_ELEMENT_NONE;
		attackInfo.eType = ATTACKTYPE_PHYSICAL;

		sq_SendHitObjectPacketByAttackInfo(obj, damager, attackInfo);
		
		local PosX = sq_GetXPos(damager);
		local PosY = sq_GetYPos(damager);
		local PosZ = sq_GetZPos(damager);
		sq_BinaryStartWrite();
		sq_BinaryWriteDword(110);
		sq_BinaryWriteDword(1);
		CNSquirrelAppendage.sq_RemoveAppendage(damager, append);
		sq_SendCreatePassiveObjectPacketPos(obj,24240, 0, PosX, PosY, PosZ);
		appendage.setValid(false);
		return;
	}
	if (currTime - appendage.getVar("monsterTime").getInt(0) > time)
	{
		appendage.getVar("monsterTime").setInt(0,currTime);
		local holyFlameRate = obj.sq_GetIntData(SKILL_PATROLBOMB, 3).tofloat();
		holyFlameRate = holyFlameRate / 100.0;
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BURNATTHESTAKE, -1, 0, holyFlameRate) + obj.sq_GetBonusRateWithPassive(SKILL_BURNATTHESTAKE, -1, 1, holyFlameRate) + obj.sq_GetBonusRateWithPassive(SKILL_BURNATTHESTAKE, -1, 2, holyFlameRate); 
		local attackInfo = sq_getNewAttackInfoPacket();
		attackInfo.useWeapon = true;
		attackInfo.powerRate = attackBonusRate;
		attackInfo.element = ENUM_ELEMENT_NONE;
		attackInfo.eType = ATTACKTYPE_PHYSICAL;
		sq_SendHitObjectPacketByAttackInfo(obj, damager, attackInfo);
	}
	if (currTime > timeMax)
	{
		appendage.getVar("monsterTime").setInt(0,currTime);
		appendage.setValid(false);
	}

}


function onStart_appendage_BurnAtThestake(appendage)
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
	local obj = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	if(!obj) {
		return;
	}
	
	local currTime = appendage.getTimer().Get();
	appendage.getVar("monsterTime").setInt(0,currTime);
	
}



function onEnd_appendage_BurnAtThestake(appendage)
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

