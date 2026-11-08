
function setCustomData_po_atswordman_3rd(obj, receiveData)
{
	if(!obj)
		return;

	local id = receiveData.readDword();
	local time = receiveData.readWord();
	local ATTK = receiveData.readWord();
	local chr = obj.getTopCharacter();

	obj.getVar("state").clear_vector();
	obj.getVar("state").push_vector(0);

	obj.getVar("id").clear_vector();
	obj.getVar("id").push_vector(id);

	if (id == 1)
	{
		local ani = obj.getCustomAnimation(0);
		obj.setCurrentAnimation(ani);

		local attackInfo = sq_GetCustomAttackInfo(obj, 0);
		sq_SetCurrentAttackInfo(obj, attackInfo);

		local level = sq_GetSkillLevel(chr, SKILL_QUIETUSREDEMPTION);
		local LevelData0 = sq_GetLevelData(chr, SKILL_QUIETUSREDEMPTION, 0, level);
		local pAttack = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(pAttack, LevelData0);
	}

	if (id == 2)
	{
		local ani = obj.getCustomAnimation(1);
		obj.setCurrentAnimation(ani);

		local attackInfo = sq_GetCustomAttackInfo(obj, 1);
		sq_SetCurrentAttackInfo(obj, attackInfo);

		local level = sq_GetSkillLevel(chr, SKILL_QUIETUSREDEMPTION);
		local LevelData0 = sq_GetLevelData(chr, SKILL_QUIETUSREDEMPTION, 1, level);
		local pAttack = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(pAttack, LevelData0);
	}
	if (id == 3)
	{
		local ani = obj.getCustomAnimation(2);
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 2);
		sq_SetCurrentAttackInfo(obj, attackInfo);
		local atk = sq_GetCurrentAttackInfo(obj);
		local power = sq_GetPowerWithPassive(chr, SKILL_TESTAMENT, STATE_TESTAMENT, 0, -1,1.0);
		sq_SetCurrentAttackPower(atk, power);
	}
	if (id == 4)
	{
		local ani = obj.getCustomAnimation(3);
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 2);
		sq_SetCurrentAttackInfo(obj, attackInfo);
		local atk = sq_GetCurrentAttackInfo(obj);
		local power = sq_GetPowerWithPassive(chr, SKILL_TESTAMENT, STATE_TESTAMENT, 1, -1,1.0);
		sq_SetCurrentAttackPower(atk, power);
	}
	if (id == 5)
	{
		local ani = obj.getCustomAnimation(3);
		obj.setCurrentAnimation(ani);
		local attackInfo = sq_GetCustomAttackInfo(obj, 2);
		sq_SetCurrentAttackInfo(obj, attackInfo);
		local atk = sq_GetCurrentAttackInfo(obj);
		local power = sq_GetPowerWithPassive(chr, SKILL_TESTAMENT, STATE_TESTAMENT, 3, -1,1.0);
		sq_SetCurrentAttackPower(atk, power);
	}
	if (id == 6)
	{
		local ani = obj.getCustomAnimation(4);
		obj.setCurrentAnimation(ani);

		local attackInfo = sq_GetCustomAttackInfo(obj, 3);
		sq_SetCurrentAttackInfo(obj, attackInfo);

		local level = sq_GetSkillLevel(chr, SKILL_LACERTHORNS);
		local LevelData0 = sq_GetLevelData(chr, SKILL_LACERTHORNS, 0, level);
		local pAttack = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(pAttack, LevelData0);
	}
	if (id == 7)
	{
		local ani = obj.getCustomAnimation(4);
		obj.setCurrentAnimation(ani);
	}
	if (id == 8)
	{
		local ani = obj.getCustomAnimation(6);
		obj.setCurrentAnimation(ani);
		obj.setTimeEvent(2, 200, 4,true);
		ATSwordman_Als_Ani(obj,"character/swordman/effect/animation/3rd/atgonewiththepetal/attackb_03.ani", 50, 0, 0, 0, 100, 0, 1.0);
		ATSwordman_Als_Ani(obj,"character/swordman/effect/animation/3rd/atgonewiththepetal/attacka.ani", 50, 0, 0, 0, 100, 0, 1.0);
		local attackInfo = sq_GetCustomAttackInfo(obj, 6);
		sq_SetCurrentAttackInfo(obj, attackInfo);
		local level = sq_GetSkillLevel(parentChr, SKILL_GONEWITHTHEPETAL);
		local attackBonusRate =  sq_GetLevelData(parentChr, SKILL_GONEWITHTHEPETAL, 1, level);
		local pAttack = sq_GetCurrentAttackInfo(obj);
		sq_SetCurrentAttackBonusRate(pAttack, attackBonusRate.tointeger());
	}

}

function onAttack_po_atswordman_3rd(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return false;
	local id = obj.getVar("id").get_vector(0);
	local parentChr = obj.getTopCharacter();
	local pAni = obj.getCurrentAnimation();
	local currentT = sq_GetCurrentTime(pAni);
	if(id == 7)
	{
		local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, parentChr, STATE_LACERTHORNS, false, 
		"character/atswordman_3rd/lacerthorns/ap_lacerthorns_enemy.nut", true);
	}
	if(id == 8)
	{
		local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, parentChr, STATE_LACERTHORNS, false, 
		"character/atswordman_3rd/gonewiththepetal/ap_gonewiththepetal_enemy.nut", true);
	}
}

/*
function procAppend_po_aaacobj(obj)
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
	if (id == 8)
	{
		local damager = obj.getVar("damager_Object").get_obj_vector(0);
		local damager_state = damager.getState();
		sq_SetCurrentDirection(obj, obj.getDirection());
		obj.setCurrentPos(damager.getXPos() + 0, damager.getYPos() + 1, 0);
		if (currentT >= 1200)
		{
			ATSwordman_3rd_Skill(obj, 9, 24391, x, y, z);
		}
		else if (damager_state == STATE_DIE || State == STATE_DIE)
		{
			sq_SendDestroyPacketPassiveObject(obj);
		}
	}
}

function ATSwordman_3rd_Skill(obj,CohesionId, objid, x, y, z)
{
	if(!obj)
		return false;
	sq_BinaryStartWrite();
	sq_BinaryWriteDword(CohesionId);
	sq_SendCreatePassiveObjectPacketPos(obj, objid, 0, x, y, z);
	sq_SendDestroyPacketPassiveObject(obj);
}
*/