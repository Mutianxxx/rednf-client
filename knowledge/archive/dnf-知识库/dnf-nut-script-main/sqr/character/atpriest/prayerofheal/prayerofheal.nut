function checkExecutableSkill_PrayerOfHeal(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_PRAYER_OF_HEAL);
	if (isUse)
	{
		obj.sq_AddSetStatePacket(STATE_PRAYER_OF_HEAL, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_PrayerOfHeal(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND || state == STATE_DASH){
		return true;
	}
	else{
		return false;
	}
}

function onSetState_PrayerOfHeal(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
		SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	obj.sq_PlaySound("R_PW_PRAYERHEAL");
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_PRAYER_OFHEAL_BODY);

	createPrayerOfHealEffect(obj);
	addPrayerOfHealBuff(obj);
}

function createPrayerOfHealEffect(obj)
{
	local groundrange_00 = "character/priest/effect/animation/atprayerofheal/groundrange_00.ani";
	ATPriest_Create(obj,groundrange_00,ENUM_DRAWLAYER_BOTTOM, 0, 0, 0, 0, sq_GetIntData(obj, SKILL_PRAYER_OF_HEAL, 0)/2,0,100,"groundrange_00");
}

function onEndCurrentAni_PrayerOfHeal(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function addPrayerOfHealBuff(obj)
{
	local objectManager = obj.getObjectManager();
	local skill_level = sq_GetSkillLevel(obj, SKILL_PRAYER_OF_HEAL);
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if(!object || !object.isObjectType(OBJECTTYPE_ACTIVE)){
			continue;
		}
		object = sq_GetCNRDObjectToActiveObject(object);
		if (object && !obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) && 
			isDistanceOfTarget(obj,object,sq_GetIntData(obj, SKILL_PRAYER_OF_HEAL, 0)))
		{
				local Skill = obj.sq_GetSkillLevel(SKILL_PRAYER_OF_HEAL);
				local recoverypercentage = obj.sq_GetLevelData(SKILL_PRAYER_OF_HEAL, 1, Skill);
				if(obj.sq_GetSkillLevel(SKILL_CRUSADE) > 0){
					recoverypercentage = recoverypercentage * sq_GetIntData(obj, SKILL_PRAYER_OF_HEAL, 2)/100;
				}
				local recoveryBonus = obj.getHpMax().tofloat();
				recoveryBonus = recoveryBonus/10000 + 1.0;
				recoverypercentage = recoveryBonus * recoverypercentage;
				recoverypercentage = recoverypercentage.tointeger();
				object.setHp(object.getHp() + recoverypercentage, null, true);
		}
	}
}
