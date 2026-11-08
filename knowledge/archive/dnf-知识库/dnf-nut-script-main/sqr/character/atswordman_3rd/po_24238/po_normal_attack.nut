State_0 <- 100
State_1 <- 101
State_2 <- 102
State_3 <- 103
State_4 <- 104
State_5 <- 105
function setCustomData_po_aaaaobj(obj, receiveData)
{
	if(!obj)
		return;
	local id = receiveData.readDword();
	local group = receiveData.readDword();
	local iddam = receiveData.readDword();
	local PauseTime = receiveData.readWord();

	local damager = sq_GetObject(obj, group, iddam);

	obj.getVar("damager_Object").clear_obj_vector();
	obj.getVar("damager_Object").push_obj_vector(damager);

	obj.getVar("id").clear_vector();
	obj.getVar("id").push_vector(id);

	obj.getVar("state").clear_vector();
	obj.getVar("state").push_vector(0);

	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);

	obj.getVar("pos").clear_vector();
	obj.getVar("pos").push_vector(x);
	obj.getVar("pos").push_vector(y);
	obj.getVar("pos").push_vector(z);

	local parentChr = obj.getTopCharacter();

	if (id == 53)
	{
		local ani = obj.getCustomAnimation(82);
		obj.setCurrentAnimation(ani);

		ATSwordman_Als_Ani(obj,"passiveobject/atwordman/animation/atfusionblade/atfusionbladeexplosionbottom_00.ani",
		 0, -1, 0, 0, 100, 0, 1.0);

		local attackInfo = sq_GetCustomAttackInfo(obj, 53);
		sq_SetCurrentAttackInfo(obj, attackInfo);

		local level = sq_GetSkillLevel(parentChr, SKILL_ATFUSIONBLADE);
		local attackBonusRate =  sq_GetLevelData(parentChr, SKILL_ATFUSIONBLADE, 2, level);
		local pAttack = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(pAttack, attackBonusRate);
	}
	if (id == 54)
	{
		local ani = obj.getCustomAnimation(84);
		obj.setCurrentAnimation(ani);
		local angle = -20;
		local rotate = angle.tointeger() * 0.017453;
		obj.setCustomRotate(true,rotate);
	}
	if (id == 55)
	{
		local ani = obj.getCustomAnimation(85);
		obj.setCurrentAnimation(ani);
		local angle = -20;
		local rotate = angle.tointeger() * 0.017453;
		obj.setCustomRotate(true,rotate);

		local attackInfo = sq_GetCustomAttackInfo(obj, 54);
		sq_SetCurrentAttackInfo(obj, attackInfo);

		local level = sq_GetSkillLevel(parentChr, SKILL_ATFUSIONBLADE);
		local attackBonusRate =  sq_GetLevelData(parentChr, SKILL_ATFUSIONBLADE, 1, level);
		local pAttack = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(pAttack, attackBonusRate);

	}
	if (id == 56)
	{
		local ani = obj.getCustomAnimation(86);
		obj.setCurrentAnimation(ani);
		local angle = -20;
		local rotate = angle.tointeger() * 0.017453;
		obj.setCustomRotate(true,rotate);
	}
	if (id == 57)
	{
		local ani = obj.getCustomAnimation(87);
		obj.setCurrentAnimation(ani);
		local angle = -8;
		local rotate = angle.tointeger() * 0.017453;
		obj.setCustomRotate(true,rotate);
	}

	if (id == 58)
	{
		local ani = obj.getCustomAnimation(88);
		obj.setCurrentAnimation(ani);
		local angle = -8;
		local rotate = angle.tointeger() * 0.017453;
		obj.setCustomRotate(true,rotate);

		local attackInfo = sq_GetCustomAttackInfo(obj, 54);
		sq_SetCurrentAttackInfo(obj, attackInfo);

		local level = sq_GetSkillLevel(parentChr, SKILL_ATFUSIONBLADE);
		local attackBonusRate =  sq_GetLevelData(parentChr, SKILL_ATFUSIONBLADE, 1, level);
		local pAttack = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(pAttack, attackBonusRate);
	}
	if (id == 59)
	{
		local ani = obj.getCustomAnimation(89);
		obj.setCurrentAnimation(ani);
		local angle = -8;
		local rotate = angle.tointeger() * 0.017453;
		obj.setCustomRotate(true,rotate);
	}
	if (id == 60)
	{
		local ani = obj.getCustomAnimation(90);
		obj.setCurrentAnimation(ani);
		local angle = 0;
		local rotate = angle.tointeger() * 0.017453;
		obj.setCustomRotate(true,rotate);
	}
	if (id == 61)
	{
		local ani = obj.getCustomAnimation(91);
		obj.setCurrentAnimation(ani);
		local angle = 0;
		local rotate = angle.tointeger() * 0.017453;
		obj.setCustomRotate(true,rotate);

		local attackInfo = sq_GetCustomAttackInfo(obj, 54);
		sq_SetCurrentAttackInfo(obj, attackInfo);

		local level = sq_GetSkillLevel(parentChr, SKILL_ATFUSIONBLADE);
		local attackBonusRate =  sq_GetLevelData(parentChr, SKILL_ATFUSIONBLADE, 1, level);
		local pAttack = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(pAttack, attackBonusRate);
	}
	if (id == 62)
	{
			local ani = obj.getCustomAnimation(92);
			obj.setCurrentAnimation(ani);
			local angle = 0;
			local rotate = angle.tointeger() * 0.017453;
			obj.setCustomRotate(true,rotate);
	}
	if (id == 63)
	{
			local ani = obj.getCustomAnimation(93);
			obj.setCurrentAnimation(ani);
			local angle = 12;
			local rotate = angle.tointeger() * 0.017453;
			obj.setCustomRotate(true,rotate);
	}
	if (id == 64)
	{
		local ani = obj.getCustomAnimation(94);
		obj.setCurrentAnimation(ani);
		local angle = 12;
		local rotate = angle.tointeger() * 0.017453;
		obj.setCustomRotate(true,rotate);

		local attackInfo = sq_GetCustomAttackInfo(obj, 54);
		sq_SetCurrentAttackInfo(obj, attackInfo);

		local level = sq_GetSkillLevel(parentChr, SKILL_ATFUSIONBLADE);
		local attackBonusRate =  sq_GetLevelData(parentChr, SKILL_ATFUSIONBLADE, 1, level);
		local pAttack = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(pAttack, attackBonusRate);
	}
	if (id == 65)
	{
			local ani = obj.getCustomAnimation(95);
			obj.setCurrentAnimation(ani);
			local angle = 12;
			local rotate = angle.tointeger() * 0.017453;
			obj.setCustomRotate(true,rotate);
	}

	if (id == 66)
	{
		local ani = obj.getCustomAnimation(45);
		obj.setCurrentAnimation(ani);

		local attackInfo = sq_GetCustomAttackInfo(obj, 33);
		sq_SetCurrentAttackInfo(obj, attackInfo);

		local level = sq_GetSkillLevel(parentChr, SKILL_AtSwordMan20);
		local attackBonusRate =  sq_GetLevelData(parentChr, SKILL_AtSwordMan20, 0, level);
		local pAttack = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(pAttack, attackBonusRate / 4);

		local sizeRate = sq_GetIntData(parentChr, SKILL_AtSwordMan20, 9, level);
		local imageRate = sizeRate.tofloat() / 100.0;
		local currentAni = obj.getCurrentAnimation();

		currentAni.Proc();
		currentAni.setImageRateFromOriginal(imageRate, imageRate);
		currentAni.setAutoLayerWorkAnimationAddSizeRate(imageRate);
		sq_SetAttackBoundingBoxSizeRate(currentAni, imageRate, imageRate, imageRate);
	}
}


function setState_po_aaaaobj(obj, state, datas)
{

	local passiveState = state;

	obj.getVar("state").set_vector(0, passiveState);

	local id = obj.getVar("id").get_vector(0);

	local parentChr = obj.getTopCharacter();

    if (state == State_0)
    {
    }
    if (state == State_1)
    {
		 if(id == 7)
		{
			local ani = obj.getCustomAnimation(8);
			obj.setCurrentAnimation(ani);
		}
	}
    if (state == State_2)
    {
		 if(id == 7)
		{
			local ani = obj.getCustomAnimation(9);
			obj.setCurrentAnimation(ani);
		}
	}
}



function procAppend_po_aaaaobj(obj)
{

	if(!obj) return;

	local state = obj.getVar("state").get_vector(0);
	local passiveState = state;


	local pAni = obj.getCurrentAnimation();
	local frmIndex = sq_GetAnimationFrameIndex(pAni);
	local currentT = sq_GetCurrentTime(pAni);
	local objX = sq_GetXPos(obj);
	local objY = sq_GetYPos(obj);
	local parentObj = obj.getParent();
	local id = obj.getVar("id").get_vector(0);
	local parentChr = obj.getTopCharacter();
	local State = parentChr.getVar("state").get_vector(0);
	local State_Sub0 = parentChr.getVar("substate").get_vector(0);
	local chr_pAni = parentChr.getCurrentAnimation();
	local chr_frmIndex = sq_GetAnimationFrameIndex(chr_pAni);

	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);

	local parentChr = obj.getTopCharacter();
	if (parentChr == STATE_DIE)
	{
		sq_SendDestroyPacketPassiveObject(obj);
	}

	if (id == 55)
	{

		local srcX = obj.getVar("pos").get_vector(0);
		local srcY = obj.getVar("pos").get_vector(1);
		local v = sq_GetUniformVelocity(0, 350, currentT, 150);

		local vx = sq_GetUniformVelocity(srcY, srcY + 90, currentT, 150);
		local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);
		sq_setCurrentAxisPos(obj, 0, dstX);
		sq_setCurrentAxisPos(obj, 1, vx);
		print(" vx:" + vx);
	}
	if (id == 58)
	{

		local srcX = obj.getVar("pos").get_vector(0);
		local srcY = obj.getVar("pos").get_vector(1);
		local v = sq_GetUniformVelocity(0, 350, currentT, 100);

		local vx = sq_GetUniformVelocity(srcY, srcY + 45, currentT, 100);
		local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);
		sq_setCurrentAxisPos(obj, 0, dstX);
		sq_setCurrentAxisPos(obj, 1, vx);
		print(" vx:" + vx);
	}
	if (id == 61)
	{

		local srcX = obj.getVar("pos").get_vector(0);
		local srcY = obj.getVar("pos").get_vector(1);
		local v = sq_GetUniformVelocity(0, 350, currentT, 100);

		local vx = sq_GetUniformVelocity(srcY, srcY + 0, currentT, 100);
		local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);
		sq_setCurrentAxisPos(obj, 0, dstX);
		sq_setCurrentAxisPos(obj, 1, vx);
		print(" vx:" + vx);
	}
	if (id == 64)
	{

		local srcX = obj.getVar("pos").get_vector(0);
		local srcY = obj.getVar("pos").get_vector(1);
		local v = sq_GetUniformVelocity(0, 350, currentT, 150);

		local vx = sq_GetUniformVelocity(srcY, srcY - 60, currentT, 150);
		local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);
		sq_setCurrentAxisPos(obj, 0, dstX);
		sq_setCurrentAxisPos(obj, 1, vx);
		print(" vx:" + vx);
	}
	if (id == 66)
	{
		local srcX = obj.getVar("pos").get_vector(0);
		local v = sq_GetUniformVelocity(0, 400, currentT, 500);
		local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);
		sq_setCurrentAxisPos(obj, 0, dstX);
	}

}

function onTimeEvent_po_aaaaobj(obj, timeEventIndex, timeEventCount)
{
	if(!obj)
		return false;

	if(timeEventIndex == 0)
	{
		obj.resetHitObjectList();
	}
	if(timeEventIndex == 1)
	{
		local damager = obj.getVar("damager_Object").get_obj_vector(0);
		local z = damager.getObjectHeight()/2;
		sq_SendHitObjectPacket(obj,damager, 0, 0, z);
	}
	if(timeEventIndex == 2)
	{
		sq_SendDestroyPacketPassiveObject(obj);
	}
	if(timeEventIndex == 3)
	{
		obj.sq_setShake(obj,1,80);	
		obj.resetHitObjectList();
	}
	if(timeEventIndex == 4)
	{
		obj.sq_setShake(obj,1,80);	
		obj.resetHitObjectList();
	}
}


function onAttack_po_aaaaobj(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return false;
	local id = obj.getVar("id").get_vector(0);
	local state = obj.getVar("state").get_vector(0);
	local passiveState = state;
	local parentChr = obj.getTopCharacter();
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);

}


function onEndCurrentAni_po_aaaaobj(obj)
{
	if(!obj)
		return;

	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);

	local id = obj.getVar("id").get_vector(0);
	local state = obj.getVar("state").get_vector(0);
	local passiveState = state;
	local parentChr = obj.getTopCharacter();

		if (id == 54)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(55);
				sq_BinaryWriteDword(0);
				sq_SendCreatePassiveObjectPacketPos(obj, 24238, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		if (id == 55)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(56);
				sq_BinaryWriteDword(0);
				sq_SendCreatePassiveObjectPacketPos(obj, 24238, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		if (id == 57)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(58);
				sq_BinaryWriteDword(0);
				sq_SendCreatePassiveObjectPacketPos(obj, 24238, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		if (id == 58)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(59);
				sq_BinaryWriteDword(0);
				sq_SendCreatePassiveObjectPacketPos(obj, 24238, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		if (id == 60)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(61);
				sq_BinaryWriteDword(0);
				sq_SendCreatePassiveObjectPacketPos(obj, 24238, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		if (id == 61)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(62);
				sq_BinaryWriteDword(0);
				sq_SendCreatePassiveObjectPacketPos(obj, 24238, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		if (id == 63)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(64);
				sq_BinaryWriteDword(0);
				sq_SendCreatePassiveObjectPacketPos(obj, 24238, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		if (id == 64)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(65);
				sq_BinaryWriteDword(0);
				sq_SendCreatePassiveObjectPacketPos(obj, 24238, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
}



function onKeyFrameFlag_po_aaaaobj(obj,flagIndex)
{
	if(!obj)
		return false;

	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);

	local id = obj.getVar("id").get_vector(0);
	local state = obj.getVar("state").get_vector(0);
	local passiveState = state;
	local parentChr = obj.getTopCharacter();

	return true;
}






