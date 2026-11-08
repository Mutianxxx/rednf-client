function setCustomData_po_ATMagicBallLightDownMultiShot(obj, receiveData)
{
	setCustomData_po_ATMagicBallLightDown(obj, receiveData);
}

function setCustomData_po_ATMagicBallDarkDownMultiShot(obj, receiveData)
{
	setCustomData_po_ATMagicBallDarkDown(obj, receiveData);
}

function setCustomData_po_ATMagicBallWaterDownMultiShot(obj, receiveData)
{
	setCustomData_po_ATMagicBallWaterDown(obj, receiveData);
}

function setCustomData_po_ATMagicBallFireDownMultiShot(obj, receiveData)
{
	setCustomData_po_ATMagicBallFireDown(obj, receiveData);
}

function setCustomData_po_ATMagicBallNoneDownMultiShot(obj, receiveData)
{
	setCustomData_po_ATMagicBallNoneDown(obj, receiveData);
}



// ??????ü - ????
function setCustomData_po_ATMagicBallLightDown(obj, receiveData)
{
	if(!obj)
		return;

	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();
	if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ??????? ???? ????, ??????? ?????????? ??????? ???????? ???.
		
		// ????? ????
		local attackBonusRate = receiveData.readDword();
		local attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
		
	}
	
	// ?????? ??? ?????? ??????
	obj.sq_SetMoveParticle("Particle/ATMagicBallLightMoveDown.ptl", horizonAngle, verticalAngle);
	local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallLight", "PassiveObject/Character/Mage/Particle/ATMagicBallLightTail1.ptl", obj);
	particleCreater.Restart(0);
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallLightTailDown1.ptl");
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallLightTailDown2.ptl");
	
	local mage = obj.getTopCharacter();
	if (!mage)
		return;
	
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
}


// ??????ü - ????
function setCustomData_po_ATMagicBallDarkDown(obj, receiveData)
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
		sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	}

	// ?????? ??? ?????? ??????
	obj.sq_SetMoveParticle("Particle/ATMagicBallDarkMoveDown.ptl", horizonAngle, verticalAngle);
	local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallDark", "PassiveObject/Character/Mage/Particle/ATMagicBallDarkTail1.ptl", obj);
	particleCreater.Restart(0);
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallDarkTailDown1.ptl");
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallDarkTailDown2.ptl");
	//obj.sq_AddObjectParticleCreater("Particle/ATMagicBallDarkTailDown3.ptl");
	local mage = obj.getTopCharacter();
	if (!mage)
		return;
	
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
}


// ??????ü - ?????
function setCustomData_po_ATMagicBallWaterDown(obj, receiveData)
{
	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();
	
	if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ????? ????
		local attackBonusRate = receiveData.readDword();
		local attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	}

	// ?????? ??? ?????? ??????
	obj.sq_SetMoveParticle("Particle/ATMagicBallWaterMoveDown.ptl", horizonAngle, verticalAngle);
	local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallWaterTailDown", "PassiveObject/Character/Mage/Particle/ATMagicBallWaterTail1.ptl", obj);
	particleCreater.Restart(0);
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallWaterTailDown1.ptl");
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallWaterTailDown2.ptl");
	
	local mage = obj.getTopCharacter();
	if (!mage)
		return;
	
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
}


// ??????ü - ????
function setCustomData_po_ATMagicBallFireDown(obj, receiveData)
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
		sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
	}
	
	// ?????? ??? ?????? ??????
	obj.sq_SetMoveParticle("Particle/ATMagicBallFireMoveDown.ptl", horizonAngle, verticalAngle);
	local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallNoneTail", "PassiveObject/Character/Mage/Particle/ATMagicBallFireTail1.ptl", obj);
	particleCreater.Restart(0);
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallFireTailDown1.ptl");
	obj.sq_AddObjectParticleCreater("Particle/ATMagicBallFireTailDown2.ptl");
	
	local mage = obj.getTopCharacter();
	if (!mage)
		return;
	
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
}

// ??????ü - ?????
function setCustomData_po_ATMagicBallNoneDown(obj, receiveData)
{
	if(!obj)
		return;
	setNoneBallDownMultiShot(obj, receiveData);
	//local horizonAngle = receiveData.readFloat();
	//local verticalAngle = receiveData.readFloat();

	//if (sq_BinaryGetReadSize() < receiveData.getSize())
	//{
		// ????? ????
	//	local attackBonusRate = receiveData.readDword();
	//	local attackInfo = sq_GetCurrentAttackInfo(obj);
	//	sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);		
	//}
	
	// ?????? ??? ?????? ??????
	//obj.sq_SetMoveParticle("Particle/ATMagicBallNoneMoveDown.ptl", horizonAngle, verticalAngle);
	//local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallNoneTail", "PassiveObject/Character/Mage/Particle/ATMagicBallNoneTail.ptl", obj);
	//particleCreater.Restart(0);
	//obj.sq_AddObjectParticleCreater("Particle/ATMagicBallNoneTailDown.ptl");
	
	//local mage = obj.getTopCharacter();
	//if (!mage)
	//	return;
		
	// ???? ???? ????
	//mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),mage.getState());	
	//sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
}

function setNoneBallDownMultiShot(obj, receiveData)
{
	//print("init ok!\n\r");
	local horizonAngle = receiveData.readFloat();
	local verticalAngle = receiveData.readFloat();
	local parentChr = obj.getTopCharacter();
	local overLevel = sq_GetSkillLevel(parentChr, 146);
	local multiShotLv = sq_GetSkillLevel(parentChr, 25);
	local addMultiShotDamage = sq_GetLevelData(parentChr, 25, 1, multiShotLv)+100;
	//print(addMultiShotDamage+" multibonus \n\r");
	//print(overLevel+" leve\n\r");
	if(overLevel > 0){
		local attackInfo = sq_GetCurrentAttackInfo(obj,1);
		local mage = sq_ObjectToSQRCharacter(parentChr);
		local power = mage.sq_GetPowerWithPassive(174, 174, 0, -1, 0.2*addMultiShotDamage/100)+50;
		local ani = obj.getCustomAnimation(1);
		obj.setCurrentAnimation(ani);
		sq_SetCurrentAttackPower(attackInfo, power);
		//print(power+" \n\r");
		sq_SetCurrentAttackInfo(obj,attackInfo);
	}
	else if (sq_BinaryGetReadSize() < receiveData.getSize())
	{
		// ????? ????
		local attackBonusRate = receiveData.readDword();
		local attackInfo = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
	}
	
	// ?????? ??? ?????? ??????
	obj.sq_SetMoveParticle("Particle/ATMagicBallNoneMoveDown.ptl", horizonAngle, verticalAngle);
	if(overLevel < 1){
		local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallNoneTail", "PassiveObject/Character/Mage/Particle/ATMagicBallNoneTail.ptl", obj);
		particleCreater.Restart(0);
		obj.sq_AddObjectParticleCreater("Particle/ATMagicBallNoneTailDown.ptl");
	}
	else{
		local particleCreater = obj.sq_var.GetparticleCreaterMap("ATMagicBallNoneTail", "PassiveObject/Character/Mage/Particle/atmagicballoversensetail.ptl", obj);
		particleCreater.Restart(0);
		obj.sq_AddObjectParticleCreater("Particle/atmagicballoversensetaildown.ptl");
	}

	local mage = obj.getTopCharacter();
	if (!mage)
		return;
	
	// ???? ???? ????
	mage.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);	
	sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
}

// ???? ???? ??????(????)?? ????.
// ???? ????
function onAttack_po_ATMagicBallFireDownMultiShot(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return 0;
	createFireExplosion(obj, damager, boundingBox, isStuck, 24281);
	return 0;
}


// ???? ??? ??????(????)?? ????.
// ???? ????
function onAttack_po_ATMagicBallFireDown(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return 0;

	createFireExplosion(obj, damager, boundingBox, isStuck, 24214);
	return 0;
}


// ???? ???? ??????(?????)?? ????.
// ???? ????
function onAttack_po_ATMagicBallWaterDownMultiShot(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return 0;
	// ??? ?????
	createWaterExplosion(obj, damager, boundingBox, isStuck, 24282);
	return 0;
}


// ???? ??? ??????(?????)?? ????.
// ???? ????
function onAttack_po_ATMagicBallWaterDown(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return 0;
	// ??? ?????
	createWaterExplosion(obj, damager, boundingBox, isStuck, 24215);
	return 0;
}


// ???? ???? ??????(????)?? ????.
// ???? ????
function onAttack_po_ATMagicBallLightDownMultiShot(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return 0;
	// ??? ????
	createLightExplosion(obj, damager, boundingBox, isStuck, 24283);
	return 0;
}

function onAttack_po_ATMagicBallNoneDownMultiShot(obj, damager, boundingBox, isStuck)
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

// ???? ??? ??????(????)?? ????.
// ???? ????
function onAttack_po_ATMagicBallLightDown(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return 0;
	// ??? ????
	createLightExplosion(obj, damager, boundingBox, isStuck, 24216);
	return 0;
}

function onAttack_po_ATMagicBallNoneDown(obj, damager, boundingBox, isStuck)
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
