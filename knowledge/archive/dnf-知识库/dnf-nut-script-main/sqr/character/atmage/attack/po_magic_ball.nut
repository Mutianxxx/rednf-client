function setCustomData_po_ATMagicBallLightMultiShot(obj, receiveData)
{
	setCustomData_po_ATMagicBallLight(obj, receiveData);
}

function setCustomData_po_ATMagicBallDarkMultiShot(obj, receiveData)
{
	setCustomData_po_ATMagicBallDark(obj, receiveData);
}

function setCustomData_po_ATMagicBallWaterMultiShot(obj, receiveData)
{
	setCustomData_po_ATMagicBallWater(obj, receiveData);
}

function setCustomData_po_ATMagicBallFireMultiShot(obj, receiveData)
{
	setCustomData_po_ATMagicBallFire(obj, receiveData);
}

function setCustomData_po_ATMagicBallNoneMultiShot(obj, receiveData)
{
	setNoneBallMultiShot(obj, receiveData);
}


function setNoneBallMultiShot(obj, receiveData)
{
	if(!obj)
		return;
	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();
	local parentChr = obj.getTopCharacter();
	local overLevel = sq_GetSkillLevel(parentChr, 146);
	local multiShotLv = sq_GetSkillLevel(parentChr, 25);
	local addMultiShotDamage = sq_GetLevelData(parentChr, 25, 1, multiShotLv)+100;
	if(overLevel > 0){
		local attackInfo = sq_GetCurrentAttackInfo(obj,1);
		local mage = sq_ObjectToSQRCharacter(parentChr);
		local power = mage.sq_GetPowerWithPassive(174, 174, 0, -1, 0.2*addMultiShotDamage/100)+50;
		local ani = obj.getCustomAnimation(1);
		obj.setCurrentAnimation(ani);
		sq_SetCurrentAttackPower(attackInfo, power);
		sq_SetCurrentAttackInfo(obj,attackInfo);
	}
	else if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ????? ????
		local attackBonusRate = receiveData.readDword();
		local attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	}
	
	// ?????? ??? ?????? ??????
	obj.sq_SetMoveParticle("Particle/ATMagicBallNoneMove.ptl", horizonAngle, verticalAngle);
	if(overLevel < 1){
		local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallNoneTail", "PassiveObject/Character/Mage/Particle/ATMagicBallNoneTail.ptl", obj);
		particleCreater.Restart(0);
		obj.sq_AddObjectParticleCreater("Particle/ATMagicBallNoneTail.ptl");
	}
	else{
		local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallNoneTail", "PassiveObject/Character/Mage/Particle/atmagicballoversensetail.ptl", obj);
		particleCreater.Restart(0);
		obj.sq_AddObjectParticleCreater("Particle/atmagicballoversensetail.ptl");
	}
	obj.sq_SetObjectParticlePos(0, -1, 0);
	
	local mage = obj.getTopCharacter();
	if (!mage)
		return;
	
	// ???? ???? ????
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),mage.getState());	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
}


// ??????ü - ????
function setCustomData_po_ATMagicBallLight(obj, receiveData)
{
	if(!obj)
		return;
		
	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();	
	if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ????? ????
		local attackBonusRate = receiveData.readDword();
		local attackInfo = sq_GetCurrentAttackInfo(obj);		
		//sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		//sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	}
	
	local mage = obj.getTopCharacter();
	if (!mage)
		return;
	local skill = sq_GetSkill(mage, SKILL_ELEMENTAL_CHANGE);
	local skillLevel = sq_GetSkillLevel(mage, SKILL_ELEMENTAL_CHANGE);
	local attackBonusRate = sq_GetBonusRateWithPassive(mage, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 10, 1.0) ;
	local totalDamage = sq_GetCurrentAttackBonusRate(obj) + attackBonusRate;
	sq_SetCurrentAttackBonusRate(sq_GetCurrentAttackInfo(obj), totalDamage);
	
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	
	// ?????? ??? ?????? ??????
	obj.sq_SetMoveParticle("Particle/ATMagicBallLightMove.ptl", horizonAngle, verticalAngle);
	local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallLight", "PassiveObject/Character/Mage/Particle/ATMagicBallLightTail1.ptl", obj);
	particleCreater.Restart(0);
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallLightTail1.ptl");
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallLightTail2.ptl");
	obj.sq_SetObjectParticlePos(0, -1, 0);
	

}


// ??????ü - ????
function setCustomData_po_ATMagicBallDark(obj, receiveData)
{
	if(!obj)
		return;

	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();	
	local attackBonusRate = 0;
//	if (sq_BinaryGetReadSize() < receiveData.getSize())
//	{
		// ????? ????
//		attackBonusRate = receiveData.readDword();
//		local attackInfo = sq_GetCurrentAttackInfo(obj);
//		sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
//		sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
//	}
	
	local mage = obj.getTopCharacter();
	if (!mage)
		return;
	local skill = sq_GetSkill(mage, SKILL_ELEMENTAL_CHANGE);
	local skillLevel = sq_GetSkillLevel(mage, SKILL_ELEMENTAL_CHANGE);
	//attackBonusRate = sq_GetAttackBonusRate(skill, 6, 1.0);
	attackBonusRate = sq_GetBonusRateWithPassive(mage, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 6, 1.0) ;
	local totalDamage = sq_GetCurrentAttackBonusRate(obj) + attackBonusRate;
	sq_SetCurrentAttackBonusRate(sq_GetCurrentAttackInfo(obj), totalDamage);

	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	
	// ?????? ??? ?????? ??????? ??????? ????????? ??ü?? ??? ??????.
	local changeStatusLevel		= sq_GetLevelData(mage, SKILL_ELEMENTAL_CHANGE, 7, skillLevel);// 7.???? ????
	local changeStatusProb		= sq_GetLevelData(mage, SKILL_ELEMENTAL_CHANGE, 8, skillLevel);// 8.???? ???(0.1%)
	changeStatusProb = changeStatusProb/10;
	local changeStatusDuration	= sq_GetLevelData(mage, SKILL_ELEMENTAL_CHANGE, 9, skillLevel);// 9.???? ????e?
	local attackInfo			= sq_GetCurrentAttackInfo(obj);
	sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, ACTIVESTATUS_CURSE, changeStatusProb, changeStatusLevel, changeStatusDuration);	


	// ?????? ??? ?????? ??????
	obj.sq_SetMoveParticle("Particle/ATMagicBallDarkMove.ptl", horizonAngle, verticalAngle);
	local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallDark", "PassiveObject/Character/Mage/Particle/ATMagicBallDarkTail1.ptl", obj);
	particleCreater.Restart(0);
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallDarkTail1.ptl");
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallDarkTail2.ptl");
	obj.sq_SetObjectParticlePos(0, -1, 0);
	

}


// ??????ü - ?????
function setCustomData_po_ATMagicBallWater(obj, receiveData)
{
	if(!obj)
		return;
	
	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();	
	if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ????? ????
		local attackBonusRate = receiveData.readDword();
		local attackInfo = sq_GetCurrentAttackInfo(obj);
		//sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		//sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	}
	
	local mage = obj.getTopCharacter();
	if (!mage)
		return;
	local skill = sq_GetSkill(mage, SKILL_ELEMENTAL_CHANGE);
	local skillLevel = sq_GetSkillLevel(mage, SKILL_ELEMENTAL_CHANGE);
	local attackBonusRate = sq_GetBonusRateWithPassive(mage, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 2, 1.0) ;
	local totalDamage = sq_GetCurrentAttackBonusRate(obj) + attackBonusRate;
	sq_SetCurrentAttackBonusRate(sq_GetCurrentAttackInfo(obj), totalDamage);
	
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	
	// ?????? ??? ?????? ??????

	obj.sq_SetMoveParticle("Particle/ATMagicBallWaterMove.ptl", horizonAngle, verticalAngle);
	local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallWaterTail", "PassiveObject/Character/Mage/Particle/ATMagicBallWaterTail1.ptl", obj);
	particleCreater.Restart(0);
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallWaterTail1.ptl");
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallWaterTail2.ptl");
	obj.sq_SetObjectParticlePos(0, -1, 0);
	

}


// ??????ü - ????
function setCustomData_po_ATMagicBallFire(obj, receiveData)
{
	if(!obj)
		return;
	
	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();
	if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ????? ????
		local attackBonusRate = receiveData.readDword();
		local attackInfo = sq_GetCurrentAttackInfo(obj);
		//sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		//sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	}
	
	local mage = obj.getTopCharacter();
	if (!mage)
		return;
	local skill = sq_GetSkill(mage, SKILL_ELEMENTAL_CHANGE);
	local skillLevel = sq_GetSkillLevel(mage, SKILL_ELEMENTAL_CHANGE);
	local attackBonusRate = sq_GetBonusRateWithPassive(mage, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 1, 1.0) ;
	local totalDamage = sq_GetCurrentAttackBonusRate(obj) + attackBonusRate;
	totalDamage = (totalDamage/2).tointeger();
	sq_SetCurrentAttackBonusRate(sq_GetCurrentAttackInfo(obj), totalDamage);
	
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));

	obj.sq_SetMoveParticle("Particle/ATMagicBallFireMove.ptl", horizonAngle, verticalAngle);
	local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallFireTail", "PassiveObject/Character/Mage/Particle/ATMagicBallFireTail1.ptl", obj);
	particleCreater.Restart(0);
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallFireTail1.ptl");
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallFireTail2.ptl");
	obj.sq_SetObjectParticlePos(0, -1, 0);
	

}

function setCustomData_po_ATMagicBallNone(obj, receiveData)
{
	if(!obj)
		return;
	setNoneBall(obj, receiveData);
}

function setNoneBall(obj, receiveData)
{
	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();
	local parentChr = obj.getTopCharacter();
	local overLevel = sq_GetSkillLevel(parentChr, 146);
	if(overLevel > 0){
		local attackInfo = sq_GetCurrentAttackInfo(obj,1);
		local mage = sq_ObjectToSQRCharacter(parentChr);
		local power = mage.sq_GetPowerWithPassive(174, 174, 0, -1, 0.007)+50;
		local ani = obj.getCustomAnimation(1);
		obj.setCurrentAnimation(ani);
		sq_SetCurrentAttackPower(attackInfo, power);
		sq_SetCurrentAttackInfo(obj,attackInfo);
	}
	else if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ????? ????
		local attackBonusRate = receiveData.readDword();
		local attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	}
	
	// ?????? ??? ?????? ??????
	obj.sq_SetMoveParticle("Particle/ATMagicBallNoneMove.ptl", horizonAngle, verticalAngle);
	if(overLevel < 1){
		local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallNoneTail", "PassiveObject/Character/Mage/Particle/ATMagicBallNoneTail.ptl", obj);
		particleCreater.Restart(0);
		obj.sq_AddObjectParticleCreater("Particle/ATMagicBallNoneTail.ptl");
	}
	else{
		local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallNoneTail", "PassiveObject/Character/Mage/Particle/atmagicballoversensetail.ptl", obj);
		particleCreater.Restart(0);
		obj.sq_AddObjectParticleCreater("Particle/atmagicballoversensetail.ptl");
	}
	obj.sq_SetObjectParticlePos(0, -1, 0);
	
	local mage = obj.getTopCharacter();
	if (!mage)
		return;
	
	// ???? ???? ????
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),mage.getState());	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
}


function onAttack_po_ATMagicBallFireMultiShot(obj, damager, boundingBox, isStuck)
{	// ???? ?????? ????
	createFireExplosion(obj, damager, boundingBox, isStuck, 24281);
	return 0;
}

function onAttack_po_ATMagicBallFire(obj, damager, boundingBox, isStuck)
{	// ??? ????
	
	createFireExplosion(obj, damager, boundingBox, isStuck, 24214);
	return 0;
}

function onAttack_po_ATMagicBallWaterMultiShot(obj, damager, boundingBox, isStuck)
{	// ???? ?????? ????
	createWaterExplosion(obj, damager, boundingBox, isStuck, 24282);
	return 0;
}

function onAttack_po_ATMagicBallWater(obj, damager, boundingBox, isStuck)
{
	// ??? ?????
	
	createWaterExplosion(obj, damager, boundingBox, isStuck, 24215);
	return 0;
}

function onAttack_po_ATMagicBallDark(obj, damager, boundingBox, isStuck)
{	// ??? ????
	if (!obj)
		return 0;

	return 0;
}


function onAttack_po_ATMagicBallLight(obj, damager, boundingBox, isStuck)
{
	
	createLightExplosion(obj, damager, boundingBox, isStuck, 24216);
	return 0;
}

function onAttack_po_ATMagicBallNone(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return 0;
	// ??? ????
	local parentChr = obj.getTopCharacter();
	if (!parentChr)
		return 0;
	local overLevel = sq_GetSkillLevel(parentChr, 146);
	if(overLevel > 0){
		local mage = sq_ObjectToSQRCharacter(parentChr);
		local enegry = mage.sq_GetIntData(146, 6);
		setBreakSenseEnegry(mage,getBreakSenseEnegry(mage) + enegry);
	}
	return 0;
}

// ???? ???? ??????(????)?? ????.
// ???? ????
function onAttack_po_ATMagicBallLightMultiShot(obj, damager, boundingBox, isStuck)
{
	createLightExplosion(obj, damager, boundingBox, isStuck, 24283);
	return 0;
}


function onAttack_po_ATMagicBallNoneMultiShot(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return 0;
	// ??? ????
	local parentChr = obj.getTopCharacter();
	if (!parentChr)
		return 0;
	local overLevel = sq_GetSkillLevel(parentChr, 146);
	if(overLevel > 0){
		local mage = sq_ObjectToSQRCharacter(parentChr);
		local enegry = parentChr.sq_GetIntData(146, 6);
		setBreakSenseEnegry(mage,getBreakSenseEnegry(mage) + enegry);
	}
	return 0;
}

function procAppend_po_ATMagicBallNone(obj)
{
}

function createFireExplosion(obj, damager, boundingBox, isStuck, passiveObjectIndex)
{
	if (!obj)
		return 0;
	local y = 0;
	if(!damager){
		y = obj.getYPos() + 1;
	}else{
		y = damager.getYPos() + 1;
	}

	local x = 0;
	local z = 0;
	if(!boundingBox){
		x = obj.getXPos();
		z = 1;
	}else{
		x = sq_GetCenterXPos(boundingBox);
		z = sq_GetCenterZPos(boundingBox);
	}

	local mage = obj.getTopCharacter();
	
	if (!mage)
		return 0;
	
	if (obj.isMyControlObject())
	{
		local var = obj.getVar();
		local bonusRate = 1.0;
		if (var.getInt(VAR_IS_ELEMENTAL_RAIN_PASSIVE_OBJECT) > 0)
		{
			local rate = sq_GetIntData(mage, SKILL_ELEMENTAL_RAIN, 3);
			bonusRate = rate.tofloat() / 100.0;
		}

		local skill = sq_GetSkill(mage, SKILL_ELEMENTAL_CHANGE);
		local skillLevel = sq_GetSkillLevel(mage, SKILL_ELEMENTAL_CHANGE);
		local attackBonusRate = sq_GetBonusRateWithPassive(mage, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 1, bonusRate);
		local sizeRate = sq_GetIntData(mage, SKILL_ELEMENTAL_CHANGE, 0);
		local totalDamage = sq_GetCurrentAttackBonusRate(obj) + attackBonusRate;
		totalDamage = (totalDamage/2).tointeger();
		
		sq_BinaryStartWrite();
		sq_BinaryWriteWord(sizeRate*2);
		sq_BinaryWriteWord(totalDamage);
		sq_SendCreatePassiveObjectPacketPos(mage, passiveObjectIndex, 0, x, y, z);

	}
}

function createWaterExplosion(obj, damager, boundingBox, isStuck, passiveObjectIndex)
{
	if (!obj)
		return 0;
		
	local y = 0;
	if(!damager){
		y = obj.getYPos() + 1;
	}else{
		y = damager.getYPos() + 1;
	}

	local x = 0;
	local z = 0;
	if(!boundingBox){
		x = obj.getXPos();
		z = 1;
	}else{
		x = sq_GetCenterXPos(boundingBox);
		z = sq_GetCenterZPos(boundingBox);
	}

	local mage = obj.getTopCharacter();
	if (!mage)
		return 0;

	if (obj.isMyControlObject())
	{
		local var = obj.getVar();
		local bonusRate = 1.0;
		if (var.getInt(VAR_IS_ELEMENTAL_RAIN_PASSIVE_OBJECT) > 0)
		{
			local rate = sq_GetIntData(mage, SKILL_ELEMENTAL_RAIN, 3);
			bonusRate = rate.tofloat() / 100.0;
		}
		
		local skill = sq_GetSkill(mage, SKILL_ELEMENTAL_CHANGE);
		local skillLevel = sq_GetSkillLevel(mage, SKILL_ELEMENTAL_CHANGE);
		local attackBonusRate = sq_GetBonusRateWithPassive(mage, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 2, bonusRate);
		local sizeRate = sq_GetIntData(mage, SKILL_ELEMENTAL_CHANGE, 1);
				
		local totalDamage = sq_GetCurrentAttackBonusRate(obj) + attackBonusRate;
		totalDamage = (totalDamage/2).tointeger();
		local power = sq_GetLevelData(mage, SKILL_ELEMENTAL_CHANGE, 3, skillLevel);
		local prob = sq_GetLevelData(mage, SKILL_ELEMENTAL_CHANGE, 4, skillLevel);
		local validTime = sq_GetLevelData(mage, SKILL_ELEMENTAL_CHANGE, 5, skillLevel);
		
		sq_BinaryStartWrite();
		sq_BinaryWriteWord(sizeRate);
		sq_BinaryWriteWord(totalDamage);
		sq_BinaryWriteByte(ACTIVESTATUS_FREEZE);
		prob = prob / 10.0;
		sq_BinaryWriteFloat(prob.tofloat());
		sq_BinaryWriteFloat(power.tofloat());
		sq_BinaryWriteDword(validTime);
		sq_SendCreatePassiveObjectPacketPos(mage, passiveObjectIndex, 0, x, y, z);
	}
}

function createLightExplosion(obj, damager, boundingBox, isStuck, passiveObjectIndex)
{
		
	if (!obj)
		return 0;
		
	local y = 0;
	if(!damager){
		y = obj.getYPos() + 1;
	}else{
		y = damager.getYPos() + 1;
	}

	local x = 0;
	local z = 0;
	if(!boundingBox){
		x = obj.getXPos();
		z = 1;
	}else{
		x = sq_GetCenterXPos(boundingBox);
		z = sq_GetCenterZPos(boundingBox);
	}

	local mage = obj.getTopCharacter();
	if (!mage)
		return 0;

	if (obj.isMyControlObject())
	{
		local var = obj.getVar();
		local bonusRate = 1.0;
		if (var.getInt(VAR_IS_ELEMENTAL_RAIN_PASSIVE_OBJECT) > 0)
		{
			local rate = sq_GetIntData(mage, SKILL_ELEMENTAL_RAIN, 3);
			bonusRate = rate.tofloat() / 100.0;
		}
		
		local skill = sq_GetSkill(mage, SKILL_ELEMENTAL_CHANGE);
		local skillLevel = sq_GetSkillLevel(mage, SKILL_ELEMENTAL_CHANGE);
		local attackBonusRate = sq_GetBonusRateWithPassive(mage, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 10, bonusRate);
		local sizeRate = sq_GetIntData(mage, SKILL_ELEMENTAL_CHANGE, 2);
		
		local power = sq_GetLevelData(mage, SKILL_ELEMENTAL_CHANGE, 11, skillLevel);
		local prob = sq_GetLevelData(mage, SKILL_ELEMENTAL_CHANGE, 12, skillLevel);
		local validTime = sq_GetLevelData(mage, SKILL_ELEMENTAL_CHANGE, 13, skillLevel);
		mage = sq_ObjectToSQRCharacter(mage);
		local damage = mage.sq_GetPowerWithPassive(SKILL_ELEMENTAL_CHANGE, SKILL_ELEMENTAL_CHANGE, 14, -1, 0.5);
		
		local totalDamage = sq_GetCurrentAttackBonusRate(obj) + attackBonusRate;
		totalDamage = (totalDamage/2).tointeger();
		
		sq_BinaryStartWrite();
		sq_BinaryWriteWord(sizeRate);
		sq_BinaryWriteWord(totalDamage);
		sq_BinaryWriteByte(ACTIVESTATUS_LIGHTNING);
		prob = prob / 10.0;
		sq_BinaryWriteFloat(prob.tofloat());
		sq_BinaryWriteFloat(power.tofloat());
		sq_BinaryWriteDword(validTime);
		sq_BinaryWriteDword(damage.tointeger());
		sq_SendCreatePassiveObjectPacketPos(mage, passiveObjectIndex, 0, x, y, z);
	}
}


