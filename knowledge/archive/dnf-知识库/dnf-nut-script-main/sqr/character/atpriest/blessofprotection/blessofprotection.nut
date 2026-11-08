
function checkExecutableSkill_BlessOfProtection(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_BLESS_OF_PROTECTION);
	if (isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_BLESS_OF_PROTECTION, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_BlessOfProtection(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_BlessOfProtection(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
		SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	if(substate == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLESS_OF_PROTECTION_CAST_BODY);

		local MagicalAttack = INTELLIGENCE_VALUE;
		sq_BinaryStartWrite();
		sq_BinaryWriteWord(0);
		sq_BinaryWriteDword(MagicalAttack);
		sq_SendChangeSkillEffectPacket(obj, SKILL_BLESS_OF_COURAGE);
		
		sq_StartDrawCastGauge(obj, sq_GetCastTime(obj, SKILL_BLESS_OF_PROTECTION, sq_GetSkillLevel(obj, SKILL_BLESS_OF_PROTECTION)), true);
	}
	if(substate == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLESS_OF_PROTECTION_START_BODY);
		addBlessOfProtectionBuff(obj);
	}
}

function onEndState_BlessOfProtection(obj, newState) {
	if(!obj)
		return false;
	if(newState != STATE_BLESS_OF_PROTECTION)
		sq_EndDrawCastGauge(obj);
}

function AriaOfCourage_start_back(obj)
{
	local start_back_1 = "character/priest/effect/animation/atblessofprotection/start_back_1.ani";
	ATPriest_Create(obj,start_back_1,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,0,100,"start_back_1");
}

function AriaOfCourage_start_front(obj)
{
	local start_front = "character/priest/effect/animation/atblessofprotection/start_front_4.ani";
	ATPriest_Create(obj,start_front,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,0,100,"start_front");
}

function AriaOfCourage_start_floor(obj)
{
	local start_floor = "character/priest/effect/animation/atblessofprotection/start_floor.ani";
	ATPriest_Create(obj,start_floor,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,0,100,"start_floor");
}

function onKeyFrameFlag_BlessOfProtection(obj,flagIndex)
{
	if(!obj)
		return false;
	if (flagIndex == 0)
	{
		obj.sq_PlaySound("BLESSPROTECTION_CAST");
	}
	return true;
}

function onEndCurrentAni_BlessOfProtection(obj)
{
	local substate = obj.getSkillSubState();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_BLESS_OF_PROTECTION, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	if(substate == 1)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onChangeSkillEffect_BlessOfCourage(obj, skillIndex, reciveData)
{
	if(!obj) return;
	local readWord = reciveData.readWord();
	if(readWord == 0)
	{
		local MagicalAttack = reciveData.readDword();
		obj.getVar().clear_vector();
		obj.getVar().push_vector(MagicalAttack);
	}
}

function addBlessOfProtectionBuff(obj)
{
	if(!obj) return;
	
	local phyValueBonus = obj.getHpMax().tofloat();
	phyValueBonus = phyValueBonus/100000 + 1.0;
	
	local magValueBonus = obj.getMpMax().tofloat();
	magValueBonus = magValueBonus/100000 + 1.0;
	
	local skill_level = sq_GetSkillLevel(obj, SKILL_BLESS_OF_PROTECTION);
	local Time = sq_GetLevelData(obj, SKILL_BLESS_OF_PROTECTION, 0, skill_level) + isStudyZealOfFaith(obj);
	local value0 = sq_GetLevelData(obj, SKILL_BLESS_OF_PROTECTION, 6, skill_level).tofloat();
	local fValue0 = value0 * phyValueBonus;
	local value1 = sq_GetLevelData(obj, SKILL_BLESS_OF_PROTECTION, 7, skill_level).tofloat();
	local fValue1 = value1 * magValueBonus;
	local value2 = sq_GetLevelData(obj, SKILL_BLESS_OF_PROTECTION, 2, skill_level).tofloat();
	local fValue2= value2 * phyValueBonus;
	local value3 = sq_GetLevelData(obj, SKILL_BLESS_OF_PROTECTION, 3, skill_level).tofloat();
	local fValue3 = value3 * magValueBonus;
	local value4 = sq_GetLevelData(obj, SKILL_BLESS_OF_PROTECTION, 4, skill_level).tofloat();
	local fValue4 = value4 * phyValueBonus;
	local value5 = sq_GetLevelData(obj, SKILL_BLESS_OF_PROTECTION, 5, skill_level).tofloat();
	local fValue5 = value5 * magValueBonus;
	
	local value6 = sq_GetIntData(obj, SKILL_BLESS_OF_PROTECTION, 1);
	
	local objectManager = obj.getObjectManager();
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if(!object || !object.isObjectType(OBJECTTYPE_ACTIVE)){
			continue;
		}
		if (!obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_CHARACTER) && isDistanceOfTarget(obj,object,sq_GetIntData(obj, SKILL_BLESS_OF_PROTECTION, 0)))
		{
			object = sq_GetCNRDObjectToActiveObject(object);
			CNSquirrelAppendage.sq_RemoveAppendage(object, "character/atpriest/blessofprotection/ap_blessofprotection.nut");
			AriaOfCourage_start_back(object);
			AriaOfCourage_start_front(object);
			AriaOfCourage_start_floor(object);
			
			local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(object, object, SKILL_BLESS_OF_PROTECTION, false, "character/atpriest/blessofprotection/ap_blessofprotection.nut", false);
			
			masterAppendage.sq_SetValidTime(Time);
			masterAppendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_BLESS_OF_PROTECTION, skill_level);
			masterAppendage.getVar("protection").clear_vector();
			masterAppendage.getVar("protection").push_vector(value6);
			CNSquirrelAppendage.sq_AppendAppendageID(masterAppendage, object, object, SKILL_BLESS_OF_PROTECTION, true);
			masterAppendage.setBuffIconImage(127);
			local change_appendage = masterAppendage.sq_getChangeStatus("blessofprotection");
			if(!change_appendage)
			{
				change_appendage = masterAppendage.sq_AddChangeStatusAppendageID(object, object, 0, 37, false, 0, APID_COMMON);
			}
			if(change_appendage)
			{
				change_appendage.clearParameter();
				if(isSameObject(obj, object))
				{
					change_appendage.addParameter(CHANGE_STATUS_TYPE_HP_MAX, false, value0);
					change_appendage.addParameter(CHANGE_STATUS_TYPE_MP_MAX, false, value1);
					change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_DEFENSE, false, value2);
					change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_DEFENSE, false, value3);
					change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_DEFENSE, false, value4);
					change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_DEFENSE, false, value5);
				}
				else
				{
					change_appendage.addParameter(CHANGE_STATUS_TYPE_HP_MAX, false, fValue0);
					change_appendage.addParameter(CHANGE_STATUS_TYPE_MP_MAX, false, fValue1);
					change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_DEFENSE, false, fValue2);
					change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_DEFENSE, false, fValue3);
					change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_DEFENSE, false, fValue4);
					change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_DEFENSE, false, fValue5);
				}
			}
		}
	}
}

