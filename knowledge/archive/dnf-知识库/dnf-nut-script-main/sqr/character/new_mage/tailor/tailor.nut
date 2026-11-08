function checkExecutableSkill_tailor(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_TAILOR);
	if (isUseSkill) 
	{
		if (isDollState(obj)){
			local level = sq_GetSkillLevel(obj, SKILL_TAILOR);		
			local top1Hp = sq_GetLevelData(obj, SKILL_TAILOR, 0, level);
			local etcHp = sq_GetLevelData(obj, SKILL_TAILOR, 2, level);
			createFrontTailorDotCasting(obj);
			addTailorHealBuff(obj,0);
			obj.setHp( obj.getHp() + top1Hp + 2*etcHp , null, true);
			createFrontTailorCotton(obj);
			obj.sq_PlaySound("SEWING_03");
		}else{
			obj.getVar("state").clear_vector();
			obj.getVar("state").push_vector(0);
			obj.sq_AddSetStatePacket(STATE_TAILOR, STATE_PRIORITY_USER, true);
			return true;
		}
	}
	return false;
}

function createFrontTailorCotton(obj)
{
	if (!obj) return false;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/sewing/sewing2cotton_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 2,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createFrontTailorCasting(obj)
{
	if (!obj) return false;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/sewing/sewingcasting_02.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFrontTailorDotCasting(obj)
{
	if (!obj) return false;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/sewing/sewing2_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function checkCommandEnable_tailor(obj)
{
	if (!obj) return false;
	return true;
}

function onKeyFrameFlag_TAILOR(obj,flagIndex)
{
	if (!obj) return false;
	if (obj.getVar("flag").get_vector(flagIndex) == 0)
	{
		if (!obj) return false;
		local level = sq_GetSkillLevel(obj, SKILL_TAILOR);		
		local top1Hp = sq_GetLevelData(obj, SKILL_TAILOR, 0, level);
		local etcHp = sq_GetLevelData(obj, SKILL_TAILOR, 2, level);
		obj.getVar("flag").set_vector(flagIndex,1);


		if (flagIndex == 1)
		{
			obj.setHp( obj.getHp() + top1Hp , null, true);
			addTailorHealBuff(obj,1);
			createFrontTailorCotton(obj);
            
		}else{
			addTailorHealBuff(obj,2);
			obj.setHp( obj.getHp() + etcHp , null, true);
		}
	}
}

function onSetState_TAILOR(obj, state, datas, isResetTimer)
{
	if (!obj) return false;
	obj.sq_StopMove();
	local state = obj.getVar("state").get_vector(0);
	if (state == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_TAILOR_CASTING);
	} 
	else if (state == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_TAILOR_LOOP);
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		createFrontTailorCasting(obj);
	}
}

function onProc_TAILOR(obj)
{
	if (!obj) return false;
    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {
        local isPress = sq_IsKeyDown(OPTION_HOTKEY_JUMP, ENUM_SUBKEY_TYPE_ALL)
        if (isPress)
        {
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
        }
    }
}

function onEndCurrentAni_TAILOR(obj)
{
	if (!obj) return false;
	local state = obj.getVar("state").get_vector(0);
	if (state == 0)
	{
		obj.getVar("state").set_vector(0,1);
		obj.sq_AddSetStatePacket(STATE_TAILOR, STATE_PRIORITY_USER, true);

	}else if (state == 1)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	

}

function addTailorHealBuff(obj,flag)
{
	if (!obj) return false;
	local objectManager = obj.getObjectManager();
	local skill_level = sq_GetSkillLevel(obj, SKILL_TAILOR);
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		object = sq_GetCNRDObjectToActiveObject(object);
		if (object && !obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) && !object.isDead() &&
		isDistanceOfTarget(obj,object,sq_GetIntData(obj, SKILL_TAILOR, 0)))
		{
				local Skill = obj.sq_GetSkillLevel(SKILL_TAILOR);
				local recoverypercentage0 = obj.sq_GetLevelData(SKILL_TAILOR, 0, Skill);
				local recoverypercentage1 = obj.sq_GetLevelData(SKILL_TAILOR, 2, Skill);
				if (isFavoriteing(object) )
				{
					recoverypercentage0 = recoverypercentage0 * 1.2;
					recoverypercentage1 = recoverypercentage1 * 1.2;
				}
				local HpMax = 0;
				if(flag==1){
					HpMax = recoverypercentage0;
				}
				else if(flag==2){
					HpMax = recoverypercentage1;
				}else{
					HpMax = recoverypercentage0 + 2*recoverypercentage1;
				}
				object.setHp(object.getHp() + HpMax.tointeger(), null, true);
		}
	}
}