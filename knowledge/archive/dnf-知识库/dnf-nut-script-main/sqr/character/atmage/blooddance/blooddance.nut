function checkExecutableSkill_blooddance(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_BLOODDANCE);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_BLOODDANCE , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}


function checkCommandEnable_blooddance(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	return true;
		

}

function setCharacterFristAnimation_Lilroi(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_BLOODDANCE );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atlilroi/lilroi_loop_front_awake.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atlilroi/lilroi_end_front_awake.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atlilroi/lilroi_end_disappear_front.ani");

        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atlilroi/floor/lilroi_end_floor.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atlilroi/floor/lilroi_loop_floor.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atlilroi/floor/lilroi_start_floor.ani");

        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/blooddance/blooddance_ready.ani");

    }
}




function onSetState_BLOODDANCE(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODDANCE_READY);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onEndCurrentAni_BLOODDANCE(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}




function onKeyFrameFlag_BLOODDANCE(obj,flagIndex)
{
	if(!obj)
		return false;

	local isMyControlObject = obj.sq_IsMyControlObject();

	// ????? ??????? ????
	if (isMyControlObject && flagIndex == 1)
	{

		local level = sq_GetSkillLevel(obj, SKILL_BLOODDANCE);		
        local size = obj.sq_GetIntData(SKILL_BLOODDANCE, 3);//sq_GetLevelData(obj, SKILL_BLOODDANCE, 1, level);
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOODDANCE, STATE_BLOODDANCE, 0, 1.0);
		obj.sq_StartWrite();
		obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
		obj.sq_WriteDword(0);					//id
        obj.sq_WriteDword(obj.sq_GetIntData(SKILL_BLOODDANCE, 0));	//attackCount
        obj.sq_WriteDword(obj.sq_GetIntData(SKILL_BLOODDANCE, 1));	//time
        obj.sq_WriteDword(obj.sq_GetIntData(SKILL_BLOODDANCE, 2));	//blood
        obj.sq_WriteDword(size);										//size

		obj.sq_SendCreatePassiveObjectPacket(24364, 0, 100, 1, 0);
        createBloodDanceStartFloorEffect(obj,size);
        obj.sq_SetShake(obj, 5, 100);
	}
	return true;
}



function createBloodDanceLoopFloorEffect(obj,size)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atlilroi/floor/lilroi_loop_floor.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
	sq_moveWithParent(obj, pooledObj);

    local currentAni = sq_GetCurrentAnimation(pooledObj);

    local sizeRate = size.tofloat()/100.0;
    currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
    currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

    obj.getVar("particleObj").push_obj_vector( pooledObj );
}


function createBloodDanceEndFloorEffect(obj,size)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atlilroi/floor/lilroi_end_floor.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

    local currentAni = sq_GetCurrentAnimation(pooledObj);

    local sizeRate = size.tofloat()/100.0;
    currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
    currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

	sq_moveWithParent(obj, pooledObj);
}

function createBloodDanceStartFloorEffect(obj,size)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atlilroi/floor/lilroi_start_floor.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 100);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());

    local currentAni = sq_GetCurrentAnimation(pooledObj);

    local sizeRate = size.tofloat()/100.0;
    currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
    currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

	sq_AddObject(obj,pooledObj,2,false);	
}


function setVliadEffectAtBloodDancePassiveobject(obj)
{
    local var = obj.getVar("particleObj");  		
    local objectsSize = var.get_obj_vector_size();

    for(local i=0;i<objectsSize;++i)
    {
        local effectObj = var.get_obj_vector(i);
        if (effectObj)
        {
//            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos(), obj.getYPos(), 0 );
            effectObj.setValid(false);
        }
    }

}
