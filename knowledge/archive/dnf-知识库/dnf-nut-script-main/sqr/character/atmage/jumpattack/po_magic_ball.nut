VAR_IS_ELEMENTAL_RAIN_PASSIVE_OBJECT	<- 0;


function setCustomData_po_ATMagicBallLightJumpMultiShot(obj, receiveData)
{
	setCustomData_po_ATMagicBallLightJump(obj, receiveData);
}

function setCustomData_po_ATMagicBallDarkJumpMultiShot(obj, receiveData)
{
	setCustomData_po_ATMagicBallDarkJump(obj, receiveData);
}

function setCustomData_po_ATMagicBallWaterJumpMultiShot(obj, receiveData)
{
	setCustomData_po_ATMagicBallWaterJump(obj, receiveData);
}

function setCustomData_po_ATMagicBallFireJumpMultiShot(obj, receiveData)
{
	setCustomData_po_ATMagicBallFireJump(obj, receiveData);
}

function setCustomData_po_ATMagicBallNoneJumpMultiShot(obj, receiveData)
{
	setNoneBallJumpMultiShot(obj, receiveData);
}






// ???? - ???
function setCustomData_po_ATMagicBallLightJump(obj, receiveData)
{
	if(!obj)
		return;
		
	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();
	if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ???? ?? ???, ???? ?????? ???? ????? ??.
		
		// ??? ??
		local attackBonusRate = receiveData.readDword();
		local attackInfo = sq_GetCurrentAttackInfo(obj);
		//sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		//sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	}
	
	
	if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ???? ???? ??? ????
		local flag = receiveData.readDword();
		local var = obj.getVar();
		
		var.setInt(VAR_IS_ELEMENTAL_RAIN_PASSIVE_OBJECT, flag);
	}
	
	// ???? ???? ??? ????? ???
	local mage = obj.getTopCharacter();
	
	if (!mage)
		return;
	local skill = sq_GetSkill(mage, SKILL_ELEMENTAL_CHANGE);
	local skillLevel = sq_GetSkillLevel(mage, SKILL_ELEMENTAL_CHANGE);
	local attackBonusRate = sq_GetBonusRateWithPassive(mage, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 10, 1.0) ;
	local totalDamage = sq_GetCurrentAttackBonusRate(obj) + attackBonusRate;
	sq_SetCurrentAttackBonusRate(sq_GetCurrentAttackInfo(obj), totalDamage);
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),7);	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	
	local angle = sq_GetIntData(mage, SKILL_ELEMENTAL_RAIN, 5);
	verticalAngle = verticalAngle - angle;
	
	
	// ???? ?? ??? ???
	obj.sq_SetMoveParticle("Particle/ATMagicBallLightMoveJump.ptl", horizonAngle, verticalAngle);
	local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallLight", "PassiveObject/Character/Mage/Particle/ATMagicBallLightTail1.ptl", obj);
	particleCreater.Restart(0);
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallLightTailJump1.ptl");
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallLightTailJump2.ptl");
}

function procAppend_po_ATMagicBallLightJump(obj)
{
	// ???? - ??? (???? ??)
	local var = obj.getVar();
	if (var.getInt(VAR_IS_ELEMENTAL_RAIN_PASSIVE_OBJECT) > 0)
	{
		if (obj.isMyControlObject() && obj.getZPos() <= 16)
		{
			createLightExplosion(obj, null, null, false, 24283);
			sq_SendDestroyPacketPassiveObject(obj);
		}
	}
}



// ???? - ???
function setCustomData_po_ATMagicBallDarkJump(obj, receiveData)
{
	if(!obj)
		return 0;
		
	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();
	local attackBonusRate = 0;
	if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ??? ??
		attackBonusRate = receiveData.readDword();
		local attackInfo = sq_GetCurrentAttackInfo(obj);
		//sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		//sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	}

	local mage = obj.getTopCharacter();
	if (!mage)
		return 0;
		
	// ???? ???? ??? ????? ???
	local angle = sq_GetIntData(mage, SKILL_ELEMENTAL_RAIN, 5);
	verticalAngle = verticalAngle - angle;

	local skill = sq_GetSkill(mage, SKILL_ELEMENTAL_CHANGE);
	local skillLevel = sq_GetSkillLevel(mage, SKILL_ELEMENTAL_CHANGE);
	attackBonusRate = sq_GetBonusRateWithPassive(mage, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 6, 1.0) ;
	local totalDamage = sq_GetCurrentAttackBonusRate(obj) + attackBonusRate;
	sq_SetCurrentAttackBonusRate(sq_GetCurrentAttackInfo(obj), totalDamage);
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),7);	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	
	local changeStatusLevel		= sq_GetLevelData(mage, SKILL_ELEMENTAL_CHANGE, 7, skillLevel);// 7.???? ????
	local changeStatusProb		= sq_GetLevelData(mage, SKILL_ELEMENTAL_CHANGE, 8, skillLevel);// 8.???? ???(0.1%)
	changeStatusProb = changeStatusProb/10;
	local changeStatusDuration	= sq_GetLevelData(mage, SKILL_ELEMENTAL_CHANGE, 9, skillLevel);// 9.???? ????e?
	local attackInfo			= sq_GetCurrentAttackInfo(obj);
	sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, ACTIVESTATUS_CURSE, changeStatusProb, changeStatusLevel, changeStatusDuration);	
	
	// ???? ?? ??? ???
	obj.sq_SetMoveParticle("Particle/ATMagicBallDarkMoveJump.ptl", horizonAngle, verticalAngle);
	local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallDark", "PassiveObject/Character/Mage/Particle/ATMagicBallDarkTail1.ptl", obj);
	particleCreater.Restart(0);
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallDarkTailJump1.ptl");
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallDarkTailJump2.ptl");
	//obj.sq_AddObjectParticleCreater("Particle/ATMagicBallDarkTailJump3.ptl");
}


// ???? - ???
function setCustomData_po_ATMagicBallWaterJump(obj, receiveData)
{
	if(!obj)
		return;
		
	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();
	
	if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ??? ??
		local attackBonusRate = receiveData.readDword();
		local attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	}
	
	if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ???? ???? ??? ????
		local flag = receiveData.readDword();
		local var = obj.getVar();
		
		var.setInt(VAR_IS_ELEMENTAL_RAIN_PASSIVE_OBJECT, flag);
	}
	
	// ???? ???? ??? ????? ???
	local mage = obj.getTopCharacter();
	
	if (!mage)
		return;
	local skill = sq_GetSkill(mage, SKILL_ELEMENTAL_CHANGE);
	local skillLevel = sq_GetSkillLevel(mage, SKILL_ELEMENTAL_CHANGE);
	local attackBonusRate = sq_GetBonusRateWithPassive(mage, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 2, 1.0) ;
	local totalDamage = sq_GetCurrentAttackBonusRate(obj) + attackBonusRate;
	sq_SetCurrentAttackBonusRate(sq_GetCurrentAttackInfo(obj), totalDamage);
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),7);	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	
	
	local angle = sq_GetIntData(mage, SKILL_ELEMENTAL_RAIN, 5);
	verticalAngle = verticalAngle - angle;
	

	// ???? ?? ??? ???
	obj.sq_SetMoveParticle("Particle/ATMagicBallWaterMoveJump.ptl", horizonAngle, verticalAngle);
	local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallWaterTailJump", "PassiveObject/Character/Mage/Particle/ATMagicBallWaterTail1.ptl", obj);
	particleCreater.Restart(0);
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallWaterTailJump1.ptl");
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallWaterTailJump2.ptl");
}


function procAppend_po_ATMagicBallWaterJump(obj)
{
	// ???? - ??? (???? ??)
	local var = obj.getVar();
	if (var.getInt(VAR_IS_ELEMENTAL_RAIN_PASSIVE_OBJECT) > 0)
	{
		if (obj.isMyControlObject() && obj.getZPos() <= 16)
		{
			createWaterExplosion(obj, null, null, false, 24282);
			sq_SendDestroyPacketPassiveObject(obj);
		}
	}
}


// ???? - ???
function setCustomData_po_ATMagicBallFireJump(obj, receiveData)
{
	if(!obj)
		return;

	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();

	if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ??? ??
		local attackBonusRate = receiveData.readDword();
		local attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	}
	
	if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ???? ???? ??? ????
		local flag = receiveData.readDword();
		local var = obj.getVar();
		
		var.setInt(VAR_IS_ELEMENTAL_RAIN_PASSIVE_OBJECT, flag);
	}
	
	// ???? ???? ??? ????? ???
	local mage = obj.getTopCharacter();
	
	if (!mage)
		return;
	local skill = sq_GetSkill(mage, SKILL_ELEMENTAL_CHANGE);
	local skillLevel = sq_GetSkillLevel(mage, SKILL_ELEMENTAL_CHANGE);
	local attackBonusRate = sq_GetBonusRateWithPassive(mage, SKILL_ELEMENTAL_CHANGE, STATE_ELEMENTAL_CHANGE, 1, 1.0) ;
	local totalDamage = sq_GetCurrentAttackBonusRate(obj) + attackBonusRate;
	totalDamage = (totalDamage/2).tointeger();
	sq_SetCurrentAttackBonusRate(sq_GetCurrentAttackInfo(obj), totalDamage);
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),7);	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	
	local angle = sq_GetIntData(mage, SKILL_ELEMENTAL_RAIN, 5);
	verticalAngle = verticalAngle - angle;
	
	// ???? ?? ??? ???
	obj.sq_SetMoveParticle("Particle/ATMagicBallFireMoveJump.ptl", horizonAngle, verticalAngle);
	local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallNoneTail", "PassiveObject/Character/Mage/Particle/ATMagicBallFireTail1.ptl", obj);
	particleCreater.Restart(0);
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallFireTailJump1.ptl");
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallFireTailJump2.ptl");
}


function procAppend_po_ATMagicBallFireJump(obj)
{

	if (obj.isMyControlObject() && obj.getZPos() <= 16)
	{
		createFireExplosion(obj, null, null, false, 24281);
		sq_SendDestroyPacketPassiveObject(obj);
	}

}

function procAppend_po_ATMagicBallFireJumpMultiShot(obj)
{
	if (obj.isMyControlObject() && obj.getZPos() <= 16)
	{
		createFireExplosion(obj, null, null, false, 24281);
		sq_SendDestroyPacketPassiveObject(obj);
	}
}

// ???? - ???
function setCustomData_po_ATMagicBallNoneJump(obj, receiveData)
{
	if(!obj)
		return;
	setNoneBallJump(obj, receiveData);
}

function setNoneBallJump(obj, receiveData)
{
	//print("init ok!\n\r");
	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();
	local parentChr = obj.getTopCharacter();
	local overLevel = sq_GetSkillLevel(parentChr, 146);
	//print(overLevel+"leve\n\r");
	if(overLevel > 0){
		local attackInfo = sq_GetCurrentAttackInfo(obj,1);
		local mage = sq_ObjectToSQRCharacter(parentChr);
		local power = mage.sq_GetPowerWithPassive(174, 174, 0, -1, 0.007)+50;
		local ani = obj.getCustomAnimation(1);
		obj.setCurrentAnimation(ani);
		sq_SetCurrentAttackPower(attackInfo, power);
		//print(power+"\n\r");
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
	
	local mage = obj.getTopCharacter();
	if (!mage) return;
	
	local angle = sq_GetIntData(mage, SKILL_ELEMENTAL_RAIN, 5);
	verticalAngle = verticalAngle - angle;
	
	// ?????? ??? ?????? ??????
	obj.sq_SetMoveParticle("Particle/ATMagicBallNoneMoveJump.ptl", horizonAngle, verticalAngle);
	if(overLevel < 1){
		local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallNoneTail", "PassiveObject/Character/Mage/Particle/ATMagicBallNoneTail.ptl", obj);
		particleCreater.Restart(0);
		obj.sq_AddObjectParticleCreater("Particle/ATMagicBallNoneTailJump.ptl");
	}
	else{
		local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallNoneTail", "PassiveObject/Character/Mage/Particle/atmagicballoversensetail.ptl", obj);
		particleCreater.Restart(0);
		obj.sq_AddObjectParticleCreater("Particle/atmagicballoversensetailjump.ptl");
	}
	
	// ???? ???? ????
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),mage.getState());	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
}


function setNoneBallJumpMultiShot(obj, receiveData)
{
	if(!obj)
		return;
	//print("init ok!\n\r");
	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();
	local parentChr = obj.getTopCharacter();
	local overLevel = sq_GetSkillLevel(parentChr, 146);
	local multiShotLv = sq_GetSkillLevel(parentChr, 25);
	local addMultiShotDamage = sq_GetLevelData(parentChr, 25, 1, multiShotLv)+100;
	//print(overLevel+"leve\n\r");
	if(overLevel > 0){
		local attackInfo = sq_GetCurrentAttackInfo(obj,1);
		local mage = sq_ObjectToSQRCharacter(parentChr);
		local power = mage.sq_GetPowerWithPassive(174, 174, 0, -1, 0.2*addMultiShotDamage/100)+50;
		local ani = obj.getCustomAnimation(1);
		obj.setCurrentAnimation(ani);
		sq_SetCurrentAttackPower(attackInfo, power);
		//print(power+"\n\r");
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
	
	local mage = obj.getTopCharacter();
	if (!mage) return;
	
	local angle = sq_GetIntData(mage, SKILL_ELEMENTAL_RAIN, 5);
	verticalAngle = verticalAngle - angle;
	
	// ?????? ??? ?????? ??????
	obj.sq_SetMoveParticle("Particle/ATMagicBallNoneMoveJump.ptl", horizonAngle, verticalAngle);
	if(overLevel < 1){
		local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallNoneTail", "PassiveObject/Character/Mage/Particle/ATMagicBallNoneTail.ptl", obj);
		particleCreater.Restart(0);
		obj.sq_AddObjectParticleCreater("Particle/ATMagicBallNoneTailJump.ptl");
	}
	else{
		local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallNoneTail", "PassiveObject/Character/Mage/Particle/atmagicballoversensetail.ptl", obj);
		particleCreater.Restart(0);
		obj.sq_AddObjectParticleCreater("Particle/atmagicballoversensetailjump.ptl");
	}
	
	// ???? ???? ????
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),mage.getState());	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
}

// ?? ?? ???(???)? ??.
// ?? ??
function onAttack_po_ATMagicBallFireJumpMultiShot(obj, damager, boundingBox, isStuck)
{	// ?? ??? ???
	createFireExplosion(obj, damager, boundingBox, isStuck, 24281);
	return 0;
}


// ?? ?? ???(???)? ??.
// ?? ??
function onAttack_po_ATMagicBallFireJump(obj, damager, boundingBox, isStuck)
{
	// ?? ???
	createFireExplosion(obj, damager, boundingBox, isStuck, 24214);
	return 0;
}

// ?? ?? ???(???)? ??.
// ?? ??
function onAttack_po_ATMagicBallWaterJumpMultiShot(obj, damager, boundingBox, isStuck)
{
	createWaterExplosion(obj, damager, boundingBox, isStuck, 24282);
	return 0;
}


// ?? ?? ???(???)? ??.
// ?? ??
function onAttack_po_ATMagicBallWaterJump(obj, damager, boundingBox, isStuck)
{
	createWaterExplosion(obj, damager, boundingBox, isStuck, 24215);
	return 0;
}

// ?? ?? ???(???)? ??.
// ?? ??
function onAttack_po_ATMagicBallLightJumpMultiShot(obj, damager, boundingBox, isStuck)
{	// ?? ???
	createLightExplosion(obj, damager, boundingBox, isStuck, 24283);
	return 0;
}

function onAttack_po_ATMagicBallNoneJumpMultiShot(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return 0;
	// ??? ????
	local parentChr = obj.getTopCharacter();
	if (!parentChr)
		return 0;
	local overLevel = sq_GetSkillLevel(parentChr, 146);

	//print(addMultiShotDamage+" multibonus \n\r");
	//print(overLevel+" leve\n\r");
	if(overLevel > 0){
		local mage = sq_ObjectToSQRCharacter(parentChr);
		local enegry = mage.sq_GetIntData(146, 6);
		setBreakSenseEnegry(mage,getBreakSenseEnegry(mage) + enegry);
	}
	return 0;
}

// ?? ?? ???(???)? ??.
// ?? ??
function onAttack_po_ATMagicBallLightJump(obj, damager, boundingBox, isStuck)
{	// ?? ???
	createLightExplosion(obj, damager, boundingBox, isStuck, 24216);
	return 0;
}

function onAttack_po_ATMagicBallNoneJump(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return 0;
	// ??? ????
	local parentChr = obj.getTopCharacter();
	if (!parentChr)
		return 0;
	local overLevel = sq_GetSkillLevel(parentChr, 146);

	//print(addMultiShotDamage+" multibonus \n\r");
	//print(overLevel+" leve\n\r");
	if(overLevel > 0){
		local mage = sq_ObjectToSQRCharacter(parentChr);
		setBreakSenseEnegry(mage,getBreakSenseEnegry(mage) +5 );
	}
	return 0;
}
