
function checkExecutableSkill_swordman_sacrifice(obj) {
	if (!obj) return false;
	local hpMax = obj.getHpMax().tofloat() * 0.05;
	if (obj.getHp() < hpMax) {
		obj.startCantUseSkillWarning();
		if (obj.isMessage()) 
			sq_AddMessage(3599);
		return false;
	}
	local isUsed = obj.sq_IsUseSkill(SKILL_SWORDMAN_SACRIFICE);
	if (isUsed) {
		local newHp = (obj.getHp() - hpMax).tointeger();
		obj.sq_SendSetHpPacket(newHp <= 0 ? 1 : newHp, true, obj);
		local skillLevel = sq_GetSkillLevel(obj, SKILL_SWORDMAN_SACRIFICE);
		local castTime = sq_GetCastTime(obj, SKILL_SWORDMAN_SACRIFICE, skillLevel);
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_IntVectPush(0);
		obj.sq_IntVectPush(SKILL_SWORDMAN_SACRIFICE);
		obj.sq_IntVectPush(castTime);
		obj.sq_IntVectPush(castTime);
		obj.sq_IntVectPush(0);
		obj.sq_IntVectPush(4);
		obj.sq_IntVectPush(4);
		obj.sq_IntVectPush(1000);
		obj.sq_IntVectPush(1000);
		obj.sq_IntVectPush(2000);
		obj.sq_AddSetStatePacket(STATE_THROW, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_swordman_sacrifice(obj) {
	if (!obj) return false;

	local state = obj.sq_GetState();
	if (state == STATE_STAND) 
		return true;
	if (state == STATE_ATTACK) {
		return obj.sq_IsCommandEnable(SKILL_SWORDMAN_SACRIFICE);
	}
	return true;
}

function SetMyAppendage_swordman_sacrifice(obj, datas) {
	if(!obj)
		return;
	local object = null;
	object = sq_GetObjectByObjectId(obj, obj.sq_GetVectorData(datas, 1));
	//print("object : "+object+"\n\r");
	local skillLevel = sq_GetSkillLevel(obj, SKILL_SWORDMAN_SACRIFICE);
	local bvSkillLevel = sq_GetSkillLevel(obj, 63);
	if (skillLevel < 1)
		return;
	
	local time = obj.sq_GetLevelData(SKILL_SWORDMAN_SACRIFICE, 2, skillLevel);
	local phyAtk = obj.sq_GetLevelData(SKILL_SWORDMAN_SACRIFICE, 1, skillLevel);
	local perHp = obj.sq_GetLevelData(SKILL_SWORDMAN_SACRIFICE, 0, skillLevel);
	local atkSpeed = obj.sq_GetLevelData(SKILL_SWORDMAN_SACRIFICE, 3, skillLevel);
	//local phygAtk = obj.sq_GetLevelData(SKILL_SWORDMAN_SACRIFICE, 7, skillLevel);
	local moveSpeed = obj.sq_GetLevelData(SKILL_SWORDMAN_SACRIFICE, 4, skillLevel);
	local phyDef = obj.sq_GetLevelData(SKILL_SWORDMAN_SACRIFICE, 5, skillLevel) / -1;
	local magDef = obj.sq_GetLevelData(SKILL_SWORDMAN_SACRIFICE, 6, skillLevel) / -1;
	
	
	if(!object)
	{
		object = obj;
	}
	local SQRch = sq_GetCNRDObjectToSQRCharacter(object);
	perHp
	if(!SQRch)
		return;
	local newHp = SQRch.getHp() + obj.getHpMax().tofloat() * 0.05 * perHp/100;
	//print("newHp : "+newHp+"\n\r");
	if(isSameObject(obj,SQRch)){
		newHp = SQRch.getHp();
		phyAtk = phyAtk*1.1;
	}
	//print("phyAtk : "+phyAtk+"\n\r");
	if(SQRch)
	{
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(SQRch, obj, SKILL_SWORDMAN_SACRIFICE, false, "character/swordman/appendage/ap_sacrifice.nut", false);
		appendage.sq_SetValidTime(time);
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, ENUM_CHARACTERJOB_SWORDMAN, SKILL_SWORDMAN_SACRIFICE, skillLevel);
		CNSquirrelAppendage.sq_AppendAppendageID(appendage, SQRch, obj, SKILL_SWORDMAN_SACRIFICE, false);
		
		local appendage_status = appendage.sq_getChangeStatus("changeStatus");
		if (!appendage_status) 
			appendage_status = appendage.sq_AddChangeStatusAppendageID(SQRch, obj, 0, CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, false, 0, APID_COMMON);
		if (appendage_status) {
			appendage_status.clearParameter();
			appendage_status.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, false, phyAtk.tofloat());
			//appendage_status.addParameter(CHANGE_STATUS_TYPE_ADDITIONAL_PHYSICAL_GENUINE_ATTACK, true, phygAtk.tofloat());
			if (bvSkillLevel > 0) {
				appendage_status.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, false, atkSpeed.tofloat());
				appendage_status.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED, false, moveSpeed.tofloat());
				appendage_status.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_DEFENSE, true, phyDef.tofloat());
				appendage_status.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_DEFENSE, true, magDef.tofloat());
			}
		}
		//print("1\n\r");
		SQRch.sq_SendSetHpPacket(newHp.tointeger(), true, SQRch);
		//print("out!\n\r");
	}
}

