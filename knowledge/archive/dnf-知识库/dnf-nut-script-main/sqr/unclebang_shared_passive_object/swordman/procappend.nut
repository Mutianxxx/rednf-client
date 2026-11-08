











function procAppend_po_swordman_shared(obj)
{
	if(!obj) return false;

	local id = obj.getVar("id").get_vector(0);
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	local parentChr = sq_ObjectToSQRCharacter(obj.getTopCharacter());
	local pAni = obj.getCurrentAnimation();
	local currentT = sq_GetCurrentTime(pAni);
	if(!parentChr)
	{
		sq_SendDestroyPacketPassiveObject(obj);
		return false;
	}
	local chrState = parentChr.sq_GetState();

	switch(id)
	{
		case 24:
			obj.setMapFollowParent(parentChr);
			obj.setMapFollowType(1);
		break;
		case 25:
			obj.setMapFollowParent(parentChr);
			obj.setMapFollowType(1);
			if(chrState == STATE_DIE)
			{
				local skill_level = sq_GetSkillLevel(parentChr, 241);
				parentChr.sq_StartWrite();
				parentChr.sq_WriteDword(241);
				parentChr.sq_WriteDword(1);
				parentChr.sq_WriteDword(parentChr.sq_GetBonusRateWithPassive(241, 241, 0, 1.0));
				parentChr.sq_WriteDword(sq_GetLevelData(parentChr, 241, 5, skill_level));
				parentChr.sq_WriteDword(sq_GetLevelData(parentChr, 241, 6, skill_level));
				parentChr.sq_WriteDword(sq_GetLevelData(parentChr, 241, 7, skill_level));
				parentChr.sq_WriteDword(sq_GetLevelData(parentChr, 241, 8, skill_level));
				parentChr.sq_WriteDword(sq_GetLevelData(parentChr, 241, 1, skill_level));
				sq_SendCreatePassiveObjectPacketPos(obj, 24370, 0, sq_GetXPos(obj), sq_GetYPos(obj), sq_GetZPos(obj));
				parentChr.sq_StartWrite();
				parentChr.sq_WriteDword(241);
				parentChr.sq_WriteDword(2);
				parentChr.sq_WriteDword(parentChr.sq_GetBonusRateWithPassive(241, 241, 2, 1.0));
				parentChr.sq_WriteDword(parentChr.sq_GetBonusRateWithPassive(241, 241, 3, 1.0));
				parentChr.sq_WriteDword(parentChr.sq_GetBonusRateWithPassive(241, 241, 4, 1.0));
				parentChr.sq_WriteDword(sq_GetLevelData(parentChr, 241, 9, skill_level));
				parentChr.sq_WriteDword(sq_GetLevelData(parentChr, 241, 10, skill_level));
				parentChr.sq_WriteDword(sq_GetLevelData(parentChr, 241, 11, skill_level));
				parentChr.sq_WriteDword(sq_GetLevelData(parentChr, 241, 12, skill_level));
				sq_SendCreatePassiveObjectPacketPos(obj, 24370, 0, sq_GetXPos(obj), sq_GetYPos(obj), sq_GetZPos(obj));
				sq_SendDestroyPacketPassiveObject(obj);
			}
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10:
					local enemyObj = obj.sq_FindFirstTarget(-1000, 1000, 2000, 200);
					if(enemyObj)
					{
						obj.sendStateOnlyPacket(11);
						obj.flushSetStatePacket();
					}
					ZigAttackWithChr(obj);
				break;
				case 11:
					local enemyXPos = obj.getVar("enemyPos").get_vector(0);
					local enemyYPos = obj.getVar("enemyPos").get_vector(1);

					local enemyObj = obj.sq_FindFirstTarget(-1000, 1000, 2000, 200);
					if(enemyObj)
					{
						local xAccel = sq_GetUniformVelocity(x, sq_GetDistancePos(enemyXPos, obj.getDirection(), -120), currentT, 50000);
						local yAccel = sq_GetUniformVelocity(y, enemyYPos, currentT, 50000);
						sq_setCurrentAxisPos(obj, 0, xAccel);
						sq_setCurrentAxisPos(obj, 1, yAccel);

						local distance = sq_GetDistanceObject(obj, enemyObj, false);
						if(distance >= 50 && distance <= 250)
						{
							obj.sendStateOnlyPacket(sq_getRandom(12, 15));
							obj.flushSetStatePacket();
						}
					}
					if(!enemyObj)
					{
						als_ani(obj, "passiveobject/unclebang_shared_passive_object/swordman/animation/zig/teleport/teleport_disappear_body.ani", 0, 0, 0, 0, 100, 0, 1, 1.0);
						obj.setCurrentPos(parentChr.getXPos(), parentChr.getYPos() - 1, 0);
						obj.setCurrentDirection(parentChr.getDirection());
						obj.sendStateOnlyPacket(10);
						obj.flushSetStatePacket();
					}
					ZigAttackWithChr(obj);
				break;
				case 12:
					ZigAttackWithChr(obj);
				break;
				case 13:
					ZigAttackWithChr(obj);
				break;
				case 14:
					ZigAttackWithChr(obj);
				break;
				case 15:
					local xDistance = obj.getVar("zigMove").get_vector(0);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 300);
					sq_setCurrentAxisPos(obj, 0, xAccel);
					ZigAttackWithChr(obj);
				break;
				case 16:
					ZigAttackWithChr(obj);
				break;
				case 17:
					ZigAttackWithChr(obj);
				break;
				case 18:
					ZigAttackWithChr(obj);
				break;
				case 19:
					ZigAttackWithChr(obj);
				break;
				case 20:
					ZigAttackWithChr(obj);
				break;
				case 21:
					ZigAttackWithChr(obj);
				break;
				case 22:
					ZigAttackWithChr(obj);
				break;
				case 23:
					ZigAttackWithChr(obj);
				break;
				case 24:
					ZigAttackWithChr(obj);
				break;
			}
		break;
		case 26:
			local zAccel = sq_GetUniformVelocity(z, 0, currentT, 50);
			sq_setCurrentAxisPos(obj, 2, zAccel);
		break;
		case 61:
			local state = obj.getVar("state").get_vector(0);
			switch(state)
			{
				case 10:
					local xDistance = obj.getVar("oneslashvsMove").get_vector(0);
					local xAccel = sq_GetUniformVelocity(x, xDistance, currentT, 100);
					sq_setCurrentAxisPos(obj, 0, xAccel);
				break;
			}
		break;
	}
}



