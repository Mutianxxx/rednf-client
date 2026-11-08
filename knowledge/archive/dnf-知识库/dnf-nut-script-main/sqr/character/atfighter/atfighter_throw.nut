
function onAfterSetState_ATFighter_Throw(obj, state, datas, isResetTimer) {
	local SkillIndex = obj.getThrowIndex();
	switch (SkillIndex) {
	case 16:
		local append = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
		local appendage = CNSquirrelAppendage.sq_IsAppendAppendage(obj, append);
		if (!appendage || obj.getThrowState() != 1) return;
		local skillLevel = sq_GetSkillLevel(obj, SKILL_SPIRALGALEFORCE);
		local levelDataA = obj.sq_GetLevelData(SKILL_SPIRALGALEFORCE, 1, skillLevel) / 1000.0;
		local levelDataB = obj.getMyPassiveObjectCount(21085);
		local levelDataC = obj.sq_GetLevelData(40, 5, sq_GetSkillLevel(obj, 40)) / 100.0 * levelDataB;
		local skill_level = sq_GetSkillLevel(obj, 16);
		obj.sq_StartWrite();
		obj.sq_WriteDword(16);
		obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(16, -1, 0, levelDataA + levelDataC));
		obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(16, -1, 0, 1.0)); //
		obj.sq_WriteDword(obj.sq_GetLevelData(16, 1, skill_level)); //
		obj.sq_WriteDword(obj.sq_GetLevelData(16, 2, skill_level)); //
		obj.sq_WriteDword(obj.sq_GetLevelData(16, 5, skill_level)); //
		//obj.sq_WriteDword(obj.sq_GetLevelData(16, 6, skill_level)); //
		obj.sq_WriteDword(obj.sq_GetPowerWithPassive(16, -1, 6, -1,1.0)); 
		obj.sq_WriteDword(obj.sq_GetLevelData(16, 4, skill_level)); //
		obj.sq_WriteDword(obj.sq_GetLevelData(16, 3, skill_level)); //
		obj.sq_WriteDword(obj.sq_GetIntData(16, 0)); //
		obj.sq_SendCreatePassiveObjectPacket(24375, 0, 80, 1, 80);
		break;
	case 15:
		local append = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
		local appendage = CNSquirrelAppendage.sq_IsAppendAppendage(obj, append);
		if (!appendage || obj.getThrowState() != 1) return;
		local skillLevel = sq_GetSkillLevel(obj, SKILL_SPIRALGALEFORCE);
		local levelDataA = obj.sq_GetLevelData(SKILL_SPIRALGALEFORCE, 1, skillLevel) / 1000.0;
		obj.sq_StartWrite();
		obj.sq_WriteDword(15);
		obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(15, -1, 3, levelDataA));
		obj.sq_SendCreatePassiveObjectPacket(24375, 0, 0, 1, 70);
		break;
	}
}

function onCreateObject_ATFighter_Throw(obj, createObject) {
	if (!obj) return false;

	if (createObject.isObjectType(OBJECTTYPE_PASSIVE)) {
		local createObject = sq_GetCNRDObjectToCollisionObject(createObject);
		local objectIndex = createObject.getCollisionObjectIndex();
		if (objectIndex == 21055) {
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut")) {
				obj.setTimeEvent(0, 500, 1, false);
				createObject.sendDestroyPacket(true);
			}
		}
	}
}

function onTimeEvent_ATFighter_Throw(obj, timeEventIndex, timeEventCount) {
	if (!obj) return false;
	obj.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, false);
}

function onAttack_NenSpearEx(obj, damager, boundingBox, isStuck) {
	
	if (!obj || isStuck) return false;
	
	local append = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
	local appendage = CNSquirrelAppendage.sq_IsAppendAppendage(obj, append);
	if (!appendage) return;
	local skill_level = sq_GetSkillLevel(obj, SKILL_SPIRALGALEFORCE);
	local levelDataA = obj.sq_GetLevelData(SKILL_SPIRALGALEFORCE, 1, skill_level) / 1000.0;
	local damagerXPos = damager.getXPos();
	local damagerYPos = damager.getYPos();
	local damagerZPos = sq_GetCenterZPos(boundingBox);
	obj.sq_StartWrite();
	obj.sq_WriteDword(117);
	obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(117, -1, 0, levelDataA) + obj.sq_GetBonusRateWithPassive(117, -1, 5, levelDataA));
	obj.sq_WriteBool(sq_IsGrabable(damager, obj));
	sq_SendCreatePassiveObjectPacketPos(obj, 24375, 0, damagerXPos, damagerYPos + 1, damagerZPos);
	
}

function onAfterSetState_NenFlower(obj, state, datas, isResetTimer) {
	obj.setSkillSubState(obj.sq_GetVectorData(datas, 0));
	local append = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
	local appendage = CNSquirrelAppendage.sq_IsAppendAppendage(obj, append);
	if (!appendage) return;
	if (obj.sq_GetVectorData(datas, 0) == 0) {
		if (obj.getVar("SpiralInhaleEnergy").size_vector() == 0) obj.getVar("SpiralInhaleEnergy").push_vector(0);
		local spiralInhaleEnergy = obj.getVar("SpiralInhaleEnergy").get_vector(0);
		if (spiralInhaleEnergy >= 200) obj.getVar("SpiralInhaleEnergy").set_vector(0, spiralInhaleEnergy - 200);
		else CNSquirrelAppendage.sq_RemoveAppendage(obj, append);
	}
}

function onKeyFrameFlag_NenFlower(obj, flagIndex) {
	
	if (!obj) return false;
	local append = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
	local appendage = CNSquirrelAppendage.sq_IsAppendAppendage(obj, append);
	if (!appendage) return;
	if (flagIndex == 1) {
		local skill_level = sq_GetSkillLevel(obj, SKILL_SPIRALGALEFORCE);
		local levelDataA = obj.sq_GetLevelData(SKILL_SPIRALGALEFORCE, 1, skill_level) / 1000.0;
		local atkRateA = obj.sq_GetBonusRateWithPassive(67, -1, 0, levelDataA);
		local atkRateB = obj.sq_GetBonusRateWithPassive(67, -1, 1, levelDataA);
		local atkRateC = obj.sq_GetBonusRateWithPassive(67, -1, 3, levelDataA);
		local levelDataB = obj.sq_GetLevelData(67, 7, sq_GetSkillLevel(obj, 67));
		obj.sq_StartWrite();
		obj.sq_WriteDword(67);
		obj.sq_WriteDword(atkRateA);
		obj.sq_WriteDword(atkRateB);
		obj.sq_WriteDword(atkRateC);
		obj.sq_WriteDword(levelDataB);
		obj.sq_SendCreatePassiveObjectPacket(24375, 0, 0, 1, 100);
	}
	
	return true;
}

function onAfterSetState_LightningDragon(obj, state, datas, isResetTimer) {
	local append = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
	local appendage = CNSquirrelAppendage.sq_IsAppendAppendage(obj, append);
	if (!appendage) return;

	if (obj.getVar("SpiralInhaleEnergy").size_vector() == 0) obj.getVar("SpiralInhaleEnergy").push_vector(0);
	local spiralInhaleEnergy = obj.getVar("SpiralInhaleEnergy").get_vector(0);
	if (spiralInhaleEnergy >= 200) obj.getVar("SpiralInhaleEnergy").set_vector(0, spiralInhaleEnergy - 200);
	else CNSquirrelAppendage.sq_RemoveAppendage(obj, append);
}

function onKeyFrameFlag_LightningDragon(obj, flagIndex) {
	
	if (!obj) return false;
	local append = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
	local appendage = CNSquirrelAppendage.sq_IsAppendAppendage(obj, append);
	if (!appendage) return;
	if (flagIndex == 2) {
		local skill_level = sq_GetSkillLevel(obj, SKILL_SPIRALGALEFORCE);
		local levelDataA = obj.sq_GetLevelData(SKILL_SPIRALGALEFORCE, 1, skill_level) / 1000.0;
		local atkRate = obj.sq_GetBonusRateWithPassive(90, -1, 0, levelDataA) * obj.sq_GetIntData(90, 0);
		obj.sq_StartWrite();
		obj.sq_WriteDword(90);
		obj.sq_WriteDword(atkRate);
		obj.sq_SendCreatePassiveObjectPacket(24375, 0, 300, 1, 70);
		
		return true;
	}
	return false;
}

function onCreateObject_SpiralColumnEx(obj, createObject) {
	local append = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
	local appendage = CNSquirrelAppendage.sq_IsAppendAppendage(obj, append);
	if (!appendage) return;
	if (createObject.isObjectType(OBJECTTYPE_PASSIVE)) {
		local createObject = sq_GetCNRDObjectToCollisionObject(createObject);
		if (createObject) {
			local objectIndex = createObject.getCollisionObjectIndex();
			if (objectIndex == 21067) {
				local uniqueId = sq_GetUniqueId(createObject);
				local objectGroup = sq_GetGroup(createObject);
				obj.getVar("SpiralColumnEx").setInt(0, uniqueId);
				obj.getVar("SpiralColumnEx").setInt(1, objectGroup);
			}
		}
	}
}

function onEndCurrentAni_SpiralColumnEx(obj) {
	
	local append = "character/atfighter/nenmaster2nd/ap_spiralgaleforce.nut";
	local appendage = CNSquirrelAppendage.sq_IsAppendAppendage(obj, append);
	if (!appendage) return;

	local skill_level = sq_GetSkillLevel(obj, SKILL_SPIRALGALEFORCE);
	local levelDataA = obj.sq_GetLevelData(SKILL_SPIRALGALEFORCE, 1, skill_level) / 1000.0;
	local intDataA = obj.getVar("SpiralColumnEx").getInt(0);
	local intDataB = obj.getVar("SpiralColumnEx").getInt(1);
	local spiralColumnObject = sq_GetObject(obj, intDataB, intDataA);
	if (spiralColumnObject) {
		local x = spiralColumnObject.getXPos();
		local y = spiralColumnObject.getYPos();
		obj.sq_StartWrite();
		obj.sq_WriteDword(120);
		obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(120, -1, 0, levelDataA) * obj.sq_GetIntData(120, 3));
		sq_SendCreatePassiveObjectPacketPos(obj, 24375, 0, x, y + 1, 0);
	}
	
}
