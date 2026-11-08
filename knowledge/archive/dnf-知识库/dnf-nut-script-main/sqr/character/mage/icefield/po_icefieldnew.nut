function setCustomData_po_icefieldnew(obj, receiveData) {
	if (!obj) return;
	local areaSizeRate = receiveData.readFloat();
	local lifeTime = receiveData.readDword();
	local iceRainCount = receiveData.readDword();
	local iceRate = receiveData.readDword();
	local iceLevel = receiveData.readDword();
	local iceTime = receiveData.readDword();
	obj.getVar("icefieldnew").setFloat(0, areaSizeRate);
	obj.getVar("icefieldnew").setInt(1, lifeTime);
	obj.getVar("icefieldnew").setInt(2, iceRainCount);
	
	local parentChr = obj.getTopCharacter();
	parentChr = sq_ObjectToSQRCharacter(parentChr);
	
	if (!parentChr) return;
	
	local attackInfo = sq_GetCustomAttackInfo(obj, 0); //ÊÇßä£»÷åüù
	local ani = obj.getCurrentAnimation();
	ani.setImageRateFromOriginal(areaSizeRate, areaSizeRate);
	sq_SetAttackBoundingBoxSizeRate(ani, areaSizeRate, areaSizeRate, areaSizeRate);

	sq_SetCurrentAttackInfo(obj, attackInfo); //ÊÇßä£»÷åüù
	local pAttack = sq_GetCurrentAttackInfo(obj);
	local level = sq_GetSkillLevel(parentChr, 59);
	local attackBonusLow = sq_GetLevelData(parentChr, 59, 0, level);
	local attackBonus = sq_GetLevelData(parentChr, 59, 1, level);
	local attackBonusEx = sq_GetSkillLevel(parentChr, 158);
	local attackBonusDec = 1 - sq_GetLevelData(parentChr, 167, 3, sq_GetSkillLevel(parentChr, 167))/1200.0;
	if(attackBonusDec < 0)
	{
		attackBonusDec = 0;
	}
	local chargepre = lifeTime / 1000;
	local attackBonusRate = (attackBonus - attackBonusLow) * chargepre * attackBonusDec + attackBonusLow * attackBonusDec;
	local MasteryLevel = sq_GetSkillLevel(parentChr, 62);
	local attackBonusMastery = sq_GetLevelData(parentChr, 62, 1, MasteryLevel);
	if (attackBonusMastery > 0) {
		attackBonusRate = attackBonusRate * attackBonusMastery / 100 + attackBonusRate;
	}
	sq_SetCurrentAttackBonusRate(pAttack, attackBonusRate.tointeger());
	local attackInfo = sq_GetCurrentAttackInfo(obj, 0);
	if (!attackInfo) return;
	sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, ACTIVESTATUS_FREEZE, iceRate, iceLevel, iceTime);
	obj.setTimeEvent(0, (5600 / iceRainCount).tointeger(), 500, false);
}


function onTimeEvent_po_icefieldnew(obj, timeEventIndex, timeEventCount) {
	if (!obj) return false;
	if (timeEventIndex == 0) {
		local iceRainCount = obj.getVar("icefieldnew").getInt(2);
		if (timeEventCount < iceRainCount) {
			local attackInfo = sq_GetCurrentAttackInfo(obj, 0);
			sq_SetCurrentAttackInfo(obj, attackInfo);
		} else {
			local icefield = obj.getMyPassiveObject(23027, 0);
			sq_SendDestroyPacketPassiveObject(obj);
			if(icefield){
				sq_SendDestroyPacketPassiveObject(icefield);
			}
		}
	}
	return false;
}