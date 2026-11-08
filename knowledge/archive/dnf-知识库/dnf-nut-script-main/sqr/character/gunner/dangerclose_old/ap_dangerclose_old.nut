
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_gunner_dangerclose_old")
	appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_gunner_dangerclose_old")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_gunner_dangerclose_old")
}

function drawAppend_appendage_gunner_dangerclose_old(appendage, isOver, x, y, isFlip)
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
 	local ani = appendage.getVar().GetAnimationMap("dangerold", "character/gunner/effect/animation/dangerclose/dangerbuff.ani");
	if(ani&&isOver) 
	{
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y, isFlip);
	}
}

function onStart_appendage_gunner_dangerclose_old(appendage)
{
	 if(!appendage) return;
	 local realAttacker = appendage.getParent();
	 if(!realAttacker) 
	 {
		 appendage.setValid(false);
		 return;
	 }
	 appendage.getVar("jsqq506807329_20230930").clear_ct_vector(); 
	 appendage.getVar("jsqq506807329_20230930").push_ct_vector(); 
	 local damager = appendage.getVar("jsqq506807329_20230930").get_ct_vector(0); 
	 damager.Reset(); 
	 damager.Start(10000,0);
} 

function onAttackParent_appendage_gunner_dangerclose_old(appendage, realAttacker, damager, boundingBox, isStuck) {
	if (!appendage || isStuck || !damager) return;
	local obj = sq_GetCNRDObjectToSQRCharacter(appendage.getParent());
	if (!obj) {
		appendage.setValid(false);
		return;
	}
	if (!realAttacker) {
		return;
	}
	if (realAttacker.isObjectType(OBJECTTYPE_PASSIVE)){
		realAttacker = sq_GetCNRDObjectToCollisionObject(realAttacker);
		if(realAttacker.getCollisionObjectIndex() == 24371){
			if (realAttacker.getVar("skill").get_vector(0) == SKILL_DANGERCLOSE) return;
		}
	}
	local currentAttackInfo = sq_GetCurrentAttackInfo(realAttacker);
	if (!currentAttackInfo || !obj.isMyControlObject()) return;
	local skill_level = sq_GetSkillLevel(obj, SKILL_DANGERCLOSE);
	local fzFdWCV44Pq3 = obj.sq_GetIntData(SKILL_DANGERCLOSE, 0);
	local timer = appendage.getVar("jsqq506807329_20230930").get_ct_vector(0);
	if (timer.Get() >= fzFdWCV44Pq3) {
		local lbN5aI5H0uG = obj.sq_GetLevelData(SKILL_DANGERCLOSE, 0, skill_level);
		if (sq_getRandom(0, 1000) <= lbN5aI5H0uG) {
			timer.Reset();
			timer.Start(10000, 0);
			if (currentAttackInfo.isValidElement(ENUM_ELEMENT_FIRE)) {
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(SKILL_DANGERCLOSE);
				sq_BinaryWriteDword(2);
				sq_BinaryWriteDword(damager.getXPos());
				sq_BinaryWriteDword(damager.getYPos());
				sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_DANGERCLOSE, 1));
				sq_BinaryWriteDword(obj.sq_GetBonusRateWithPassive(SKILL_DANGERCLOSE, STATE_DANGERCLOSE, 2, 1.0));
				sq_BinaryWriteDword(obj.sq_GetBonusRateWithPassive(SKILL_DANGERCLOSE, STATE_DANGERCLOSE, 4, 1.0));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 5, skill_level));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 6, skill_level));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 7, skill_level));
				sq_BinaryWriteDword(obj.sq_GetBonusRateWithPassive(SKILL_DANGERCLOSE, STATE_DANGERCLOSE, 3, 1.0));
				sq_SendCreatePassiveObjectPacketPos(obj, 24371, 0, sq_GetDistancePos(obj.getXPos(), obj.getDirection(), -350), obj.getYPos(), 800);
			} else if (currentAttackInfo.isValidElement(ENUM_ELEMENT_WATER) || realAttacker.getCollisionObjectIndex() == 22221) {
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(SKILL_DANGERCLOSE);
				sq_BinaryWriteDword(3);
				sq_BinaryWriteDword(damager.getXPos());
				sq_BinaryWriteDword(damager.getYPos());
				sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_DANGERCLOSE, 1));
				sq_BinaryWriteDword(obj.sq_GetBonusRateWithPassive(SKILL_DANGERCLOSE, STATE_DANGERCLOSE, 2, 1.0));
				sq_BinaryWriteDword(obj.sq_GetBonusRateWithPassive(SKILL_DANGERCLOSE, STATE_DANGERCLOSE, 4, 1.0));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 5, skill_level));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 6, skill_level));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 7, skill_level));
				sq_BinaryWriteDword(obj.sq_GetBonusRateWithPassive(SKILL_DANGERCLOSE, STATE_DANGERCLOSE, 13, 1.0));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 14, skill_level));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 15, skill_level));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 16, skill_level));
				sq_SendCreatePassiveObjectPacketPos(obj, 24371, 0, sq_GetDistancePos(obj.getXPos(), obj.getDirection(), -350), obj.getYPos(), 800);
			} else if (currentAttackInfo.isValidElement(ENUM_ELEMENT_LIGHT) || realAttacker.getCollisionObjectIndex() == 22220) {
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(SKILL_DANGERCLOSE);
				sq_BinaryWriteDword(4);
				sq_BinaryWriteDword(damager.getXPos());
				sq_BinaryWriteDword(damager.getYPos());
				sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_DANGERCLOSE, 1));
				sq_BinaryWriteDword(obj.sq_GetBonusRateWithPassive(SKILL_DANGERCLOSE, STATE_DANGERCLOSE, 2, 1.0));
				sq_BinaryWriteDword(obj.sq_GetBonusRateWithPassive(SKILL_DANGERCLOSE, STATE_DANGERCLOSE, 4, 1.0));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 5, skill_level));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 6, skill_level));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 7, skill_level));
				sq_BinaryWriteDword(obj.sq_GetBonusRateWithPassive(SKILL_DANGERCLOSE, STATE_DANGERCLOSE, 8, 1.0));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 9, skill_level));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 10, skill_level));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 11, skill_level));
				sq_BinaryWriteDword(obj.sq_GetPowerWithPassive(SKILL_DANGERCLOSE, -1, 12, -1, 1.0));
				sq_SendCreatePassiveObjectPacketPos(obj, 24371, 0, sq_GetDistancePos(obj.getXPos(), obj.getDirection(), -350), obj.getYPos(), 800);
			} else {
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(SKILL_DANGERCLOSE);
				sq_BinaryWriteDword(1);
				sq_BinaryWriteDword(damager.getXPos());
				sq_BinaryWriteDword(damager.getYPos());
				sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_DANGERCLOSE, 1));
				sq_BinaryWriteDword(obj.sq_GetBonusRateWithPassive(SKILL_DANGERCLOSE, STATE_DANGERCLOSE, 2, 1.0));
				sq_BinaryWriteDword(obj.sq_GetBonusRateWithPassive(SKILL_DANGERCLOSE, STATE_DANGERCLOSE, 4, 1.0));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 5, skill_level));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 6, skill_level));
				sq_BinaryWriteDword(obj.sq_GetLevelData(SKILL_DANGERCLOSE, 7, skill_level));
				sq_BinaryWriteDword(obj.sq_GetBonusRateWithPassive(SKILL_DANGERCLOSE, STATE_DANGERCLOSE, 17, 1.0));
				sq_SendCreatePassiveObjectPacketPos(obj, 24371, 0, sq_GetDistancePos(obj.getXPos(), obj.getDirection(), -350), obj.getYPos(), 800);
			}
		}
	}
}

