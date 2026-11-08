function setCustomData_po_HurricaneKnife(obj, receiveData)
{
	local chr = obj.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(chr);
	local skillLevel = sq_GetSkillLevel(sqrChr, 11);

	local attackBonusRate = sqrChr.sq_GetBonusRateWithPassive(11, -1, 0, 1.0);
	
	local bleedingLevel = sq_GetLevelData(sqrChr, 11, 2, skillLevel);// ?X??Lv
	local bleedingTime = sq_GetLevelData(sqrChr, 11, 3, skillLevel);// ?X???????
	local bleedingDamage = sqrChr.sq_GetPowerWithPassive(11, -1, 4, -1, 1.0);
	
	local attackInfo = sq_GetCurrentAttackInfo(obj);

	local count = receiveData.readDword();
	local angle = count.tofloat() * 30.0;
	local radian = sq_ToRadian(angle);

	sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
	attackInfo = sq_GetCurrentAttackInfo(obj, 0);
	if (!attackInfo) return;
	sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, ACTIVESTATUS_BLEEDING, 100, bleedingLevel, bleedingTime, bleedingDamage);
	sq_SetCustomRotate(obj, -radian);
	obj.sq_SetMoveParticle("Particle/HurricaneKnife.ptl", angle, 0.0);
	
}


function onEndCurrentAni_po_HurricaneKnife(obj)
{
	sq_SendDestroyPacketPassiveObject(obj);
}

