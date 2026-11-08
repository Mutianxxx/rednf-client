
function setCustomData_po_aaabobj(obj, receiveData)
{
	if(!obj)
		return;
	local id = receiveData.readDword();
	local group = receiveData.readDword();
	local uniqueId = receiveData.readDword();
	local PauseTime = receiveData.readWord();
	local damagerId = receiveData.readWord();
	local damager = sq_GetObject(obj, group, uniqueId);

	obj.getVar("id").clear_vector();
	obj.getVar("id").push_vector(id);

	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);

	obj.getVar("pos").clear_vector();
	obj.getVar("pos").push_vector(x);
	obj.getVar("pos").push_vector(y);
	obj.getVar("pos").push_vector(z);

	local parentChr = obj.getTopCharacter();

	if (id == 48)
	{
		local ani = obj.getCustomAnimation(40);
		obj.setCurrentAnimation(ani);

		local attackInfo = sq_GetCustomAttackInfo(obj, 20);
		sq_SetCurrentAttackInfo(obj, attackInfo);

		ATSwordman_Als_Ani(obj,
		"passiveobject/atwordman/animation/atbloodoctopussword/bloodoctopussword03_13.ani", 0, 1, 0, 0, 100, 0, 1.0);

		ATSwordman_Als_Ani(obj,
		"passiveobject/atwordman/animation/atbloodoctopussword/bloodoctopussword02_00.ani", 0, 50, 0, 0, 100, 0, 1.0);

		ATSwordman_Als_Ani(obj,
		"passiveobject/atwordman/animation/atbloodoctopussword/bloodoctopussword05_11.ani", 0, -88, 0, 0, 100, 0, 1.0);

		obj.setTimeEvent(0, 80, 4,true);
		local level = sq_GetSkillLevel(parentChr, SKILL_BLOODOCTOPUSSWORD);
		local attackBonusRate =  sq_GetLevelData(parentChr, SKILL_BLOODOCTOPUSSWORD, 0, level);
		local pAttack = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(pAttack, attackBonusRate.tointeger());

	}
	if (id == 49)
	{
		local ani = obj.getCustomAnimation(41);
		obj.setCurrentAnimation(ani);

		local attackInfo = sq_GetCustomAttackInfo(obj, 21);
		sq_SetCurrentAttackInfo(obj, attackInfo);

		local level = sq_GetSkillLevel(parentChr, SKILL_BLOODOCTOPUSSWORD);
		local attackBonusRate =  sq_GetLevelData(parentChr, SKILL_BLOODOCTOPUSSWORD, 1, level);
		local pAttack = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(pAttack, attackBonusRate.tointeger());

	}
}


function procAppend_po_aaabobj(obj)
{

	if(!obj) return;

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

	if (id == 0)
	{
		local damager = obj.getVar("damager_Object").get_obj_vector(0);
		local damager_state = damager.getState();	
		sq_SetCurrentDirection(obj, obj.getDirection());
		obj.setCurrentPos
		(damager.getXPos() + 0,
		 damager.getYPos() + 1,
		 damager.getZPos() + damager.getObjectHeight()/2 + 0);
		if (damager && currentT >= 2000)
		{
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(1);
			sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
			sq_SendDestroyPacketPassiveObject(obj);
		}
		else if (damager_state == STATE_DIE || State == STATE_DIE)
		{
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(1);
			sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
			sq_SendDestroyPacketPassiveObject(obj);
		}

	}
	if (id == 2)
	{
		if (State != STATE_AtSwordManB06)
		{
			sq_SendDestroyPacketPassiveObject(obj);
		}
	}
	if (id == 3)
	{
		if (State != STATE_AtSwordManB08)
		{
			sq_SendDestroyPacketPassiveObject(obj);
		}
	}
	if (id == 4)
	{
		if (State != STATE_AtSwordManB08)
		{
			sq_SendDestroyPacketPassiveObject(obj);
		}
	}
	if (id == 6)
	{
			local dash_t = 300;
			MovePro_Skill(obj,parentChr, "204_pos", 0, 1)
	}
	if (id == 8)
	{
		if (currentT >= 1200)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(9);
				sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
	}
	if (id == 11)
	{
			local dash_t = 300;
			MovePro_Skill(obj,parentChr, "205_pos", 0, 1)
	}
	if (id == 15)
	{
			local dash_t = 300;
			MovePro_Skill(obj,parentChr, "206_pos", 0, 1)
	}
	if (id == 20)
	{
			local dash_t = 300;
			MovePro_Skill(obj,parentChr, "207_pos", 0, 1)
	}
	if (id == 25)
	{
			local dash_t = 300;
			MovePro_Skill(obj,parentChr, "208_pos", 0, 1)
	}
	if (id == 29 || id == 30)
	{
		
		local damager = parentChr.getVar("dam_Obj29").get_obj_vector(0);
		local damager_state = damager.getState();	
		sq_SetCurrentDirection(obj, obj.getDirection());
		if (damager)
		{
		obj.setCurrentPos
		(damager.getXPos() + 0,
		 damager.getYPos() + 1,
		 damager.getZPos() + damager.getObjectHeight());
		}
		else 
		{
		obj.setCurrentPos
		(parentChr.getXPos() + 0,
		 parentChr.getYPos() - 1,
		 parentChr.getZPos() + 75);
		}
		if (damager_state == STATE_DIE)
		{
			Cohesion_Skill(obj,31, 24239, x, y, z)
		}
	}
	if (id == 31)
	{
		
		local damager = parentChr.getVar("dam_Obj29").get_obj_vector(0);
		local damager_state = damager.getState();	
		if (damager)
		{
		sq_SetCurrentDirection(obj, obj.getDirection());
		obj.setCurrentPos
		(damager.getXPos() + 0,
		 damager.getYPos() + 1,
		 damager.getZPos() + damager.getObjectHeight());
		}
		else 
		{
		obj.setCurrentPos
		(parentChr.getXPos() + 0,
		 parentChr.getYPos() - 1,
		 parentChr.getZPos() + 75);
		}
	}
	if (id == 32 || id == 33 || id == 34)
	{

		local srcX = obj.getVar("pos").get_vector(0);
		local v = sq_GetUniformVelocity(0, 800, currentT, 320);
		local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);
		sq_setCurrentAxisPos(obj, 0, dstX);

		if (currentT >= 350)
		{
			sq_SendDestroyPacketPassiveObject(obj);
		}

	}
	if (id == 37)
	{
		if (currentT >= 2000)
		{
			Cohesion_Skill(obj,38, 24239, x, y, z)
		}
	}
}

function onTimeEvent_po_aaabobj(obj, timeEventIndex, timeEventCount)
{
	if(!obj)
		return false;

	if(timeEventIndex == 0)
	{
		//sq_SendDestroyPacketPassiveObject(obj);
		obj.resetHitObjectList();
	}

}


function onAttack_po_aaabobj(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return false;
	local id = obj.getVar("id").get_vector(0);
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);


}


function onEndCurrentAni_po_aaabobj(obj)
{
	if(!obj)
		return;

	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);

	local id = obj.getVar("id").get_vector(0);
	local parentChr = obj.getTopCharacter();

		 if(id == 999)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(21);
				sq_BinaryWriteDword(0);
				sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 5)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(6);
				sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 6)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(8);
				sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 7)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(8);
				sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 8)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(9);
				sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 10)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(11);
				sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 11)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(12);
				sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 12)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(13);
				sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 14)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(15);
				sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 15)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(16);
				sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 16)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(17);
				sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 17)
		{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(18);
				sq_SendCreatePassiveObjectPacketPos(obj, 24239, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 19)
		{
				Cohesion_Skill(obj,20, 24239, x, y, z)
		}
		 if(id == 20)
		{
				Cohesion_Skill(obj,21, 24239, x, y, z)
		}
		 if(id == 21)
		{
				Cohesion_Skill(obj,22, 24239, x, y, z)
		}
		 if(id == 22)
		{
				Cohesion_Skill(obj,23, 24239, x, y, z)
		}
		 if(id == 23)
		{
			sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 24)
		{
				Cohesion_Skill(obj,25, 24239, x, y, z)
		}
		 if(id == 25)
		{
				Cohesion_Skill(obj,26, 24239, x, y, z)
		}
		 if(id == 26)
		{
					Cohesion_Skill(obj,27, 24239, x, y, z)
		}
		 if(id == 27)
		{
			local HitCount = parentChr.getVar("208_HitCount").getInt(0);
			local MaxHitCount = 4;
			print(" End_HitCount:" + HitCount);
			if(HitCount >= MaxHitCount)
			{
					Cohesion_Skill(obj,28, 24239, x, y, z)
			}
			else 
			{
					Cohesion_Skill(obj,27, 24239, x, y, z)
			}
		}
		 if(id == 28)
		{
			sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 29)
		{
					Cohesion_Skill(obj,30, 24239, x, y, z)
		}
		 if(id == 30)
		{

		}
		 if(id == 31)
		{
			parentChr.getVar("dam_Obj29").clear_obj_vector();
			sq_SendDestroyPacketPassiveObject(obj);
		}
		 if(id == 36)
		{
					Cohesion_Skill(obj,37, 24239, x, y, z)
		}
		 if(id == 37)
		{
					Cohesion_Skill(obj,38, 24239, x, y, z)
		}
		 if(id == 38)
		{
			sq_SendDestroyPacketPassiveObject(obj);
		}
		else 
		{
			sq_SendDestroyPacketPassiveObject(obj);
		}


}



function onKeyFrameFlag_po_aaabobj(obj,flagIndex)
{
	if(!obj)
		return false;

	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	local parentObj = obj.getParent();
	local id = obj.getVar("id").get_vector(0);
	local parentChr = obj.getTopCharacter();

	 if(id == 8)
	{
		if (flagIndex == 1)
		{
			obj.resetHitObjectList();
		}
	}
	 if(id == 21)
	{
		if (flagIndex == 1)
		{

			local mux = 180;
			local tux = 55;
			if (obj.getDirection() == 0)
			{
					mux = -180;
					tux = -55;
			}

			for (local i = 0; i < 3 ; i++)
			{
				sq_SendCreatePassiveObjectPacketPos(parentObj, 260021, 0, x + mux + tux * i, y + 1, 0);
			}
		}
	}
	 if(id == 27)
	{
		if (flagIndex == 1)
		{
			obj.resetHitObjectList();
		}
	}
	 if(id == 30)
	{
		if (flagIndex == 1)
		{
			obj.resetHitObjectList();
			local HitCount = parentChr.getVar("29_HitCount").getInt(0);
			local MaxHitCount = sq_GetIntData(parentChr, SKILL_AtSwordManB11, 8, SKILL_AtSwordManB11);
			parentChr.getVar("29_HitCount").setInt(0, HitCount + 1);
			print(" End_HitCount:" + HitCount);
			if(HitCount >= MaxHitCount)
			{
					Cohesion_Skill(obj,31, 24239, x, y, z)
			}
		}
	}
	 if(id == 31)
	{
		if (flagIndex == 1)
		{
				obj.sq_setShake(obj,3,300);	
				sq_flashScreen(obj, 30, 25, 30, 200, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		}
	}

	 if(id == 44)
	{
		if (flagIndex == 1)
		{
				obj.sq_setShake(obj,6,250);	
				sq_flashScreen(obj, 30, 25, 30, 200, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		}
	}
	return true;
}


function Cohesion_Skill(obj,CohesionId, objid, x, y, z)
{
	if(!obj)
		return false;

				sq_BinaryStartWrite();
				sq_BinaryWriteDword(CohesionId);
				sq_SendCreatePassiveObjectPacketPos(obj, objid, 0, x, y, z);
				sq_SendDestroyPacketPassiveObject(obj);
}


function MoveObj_Skill(obj,parentChr, das, Atk_target, name_target, name)
{
	if(!obj)
		return false;

					parentChr.getVar(name_target).clear_obj_vector();
					parentChr.getVar(name_target).push_obj_vector(Atk_target);
					local xPos = obj.getXPos();
					local yPos = obj.getYPos();
					parentChr.getVar(name).clear_vector();
					parentChr.getVar(name).push_vector(xPos);
					parentChr.getVar(name).push_vector(yPos);
					local disX = sq_Abs(Atk_target.getXPos() - xPos);
					local disY = Atk_target.getYPos() - yPos;
					disX = disX + das;
					if(disX <= 0)
					disX = 0;
					parentChr.getVar(name).push_vector(disX);
					parentChr.getVar(name).push_vector(disY);
}


function MovePro_Skill(obj,parentChr, name, Xmove, Ymove)
{
	if(!obj)
		return false;

			local srcX = parentChr.getVar(name).get_vector(0);
			local srcY = parentChr.getVar(name).get_vector(1);
			local dis_x_len = parentChr.getVar(name).get_vector(2);
			local dis_y_len = parentChr.getVar(name).get_vector(3);
			local pAni = obj.getCurrentAnimation();
			local delay = 0;
			if(pAni)
			delay = pAni.getDelaySum(false);
			local currentT = sq_GetCurrentTime(pAni);
			local v = sq_GetAccel(0, dis_x_len, currentT, delay, true);
			local my = sq_GetUniformVelocity(0, dis_y_len, currentT, delay);
			local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);
			local dstY = srcY + my;
			if(Xmove == 0)
			sq_setCurrentAxisPos(obj, 0, dstX);
			if(Ymove == 1)
			sq_setCurrentAxisPos(obj, 1, dstY + 2);

}


