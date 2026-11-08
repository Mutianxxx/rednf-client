function checkExecutableSkill_blackhole(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_BLACKHOLE);

	if (isUse) {

			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			
			obj.addSetStatePacket(STATE_BLACKHOLE , pIntVec, STATE_PRIORITY_FORCE, false, "");



		return true;
	}

	return false;
}

function checkCommandEnable_blackhole(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	return true;
}
//BLACKHOLE


function onSetState_BLACKHOLE(obj, state, datas, isResetTimer)
{
	if(!obj) return;


	obj.sq_StopMove();
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);

    if (state == 0)
    {

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOCKHOLE_READY);



        obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("atanimation/als_ani/atdimensionbomb/dimensionbomb_cast_cast.ani"), 0, 0);

		local castTime = sq_GetCastTime(obj, SKILL_BLACKHOLE, sq_GetSkillLevel(obj, SKILL_BLACKHOLE)  );
		local animation = sq_GetCurrentAnimation(obj);
		local startTime = animation.getDelaySum(false);
		local speedRate = startTime.tofloat() / castTime.tofloat();
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);

		sq_StartDrawCastGauge(obj, castTime, true);
		obj.sq_PlaySound("MW_POSITRON");


    }else if (state == 1)
    {


        obj.getVar("effectObj").clear_obj_vector();

        local saveT = sq_GetLevelData(obj, SKILL_BLACKHOLE, 3, sq_GetSkillLevel(obj, SKILL_BLACKHOLE));
        local atkT = sq_GetLevelData(obj, SKILL_BLACKHOLE, 2, sq_GetSkillLevel(obj, SKILL_BLACKHOLE))

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOCKHOLE_LOOP);

        if(!obj.isMyControlObject())
            return false;


        obj.sq_SetShake(obj, 2, saveT);//200);
        sq_flashScreen(obj,0,50,0,127, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		local power = obj.sq_GetPowerWithPassive(SKILL_BLACKHOLE, STATE_BLACKHOLE, 0, -1, 1.0);
		local power2 = obj.sq_GetPowerWithPassive(SKILL_BLACKHOLE, STATE_BLACKHOLE, 1, -1, 1.0);
		obj.sq_StartWrite();
		obj.sq_WriteDword(power );	// attackBonusRate
		obj.sq_WriteDword(104);	// attackBonusRate
		obj.sq_WriteDword(0);	// attackBonusRate
		obj.sq_WriteDword( atkT );	// attackBonusRate
		obj.sq_WriteDword(saveT );	// attackBonusRate
		obj.sq_WriteDword(0 );	// attackBonusRate
		obj.sq_SendCreatePassiveObjectPacket(24357, 0, 45,1, obj.getObjectHeight()/2 + 39 );

		obj.sq_StartWrite();
		obj.sq_WriteDword(power2 );	// attackBonusRate
		obj.sq_WriteDword(104);	// attackBonusRate
		obj.sq_WriteDword(1);	// attackBonusRate
		obj.sq_WriteDword( atkT );	// attackBonusRate
		obj.sq_WriteDword(saveT );	// attackBonusRate
		obj.sq_WriteDword(-270 );	// attackBonusRate
		obj.sq_SendCreatePassiveObjectPacket(24357, 0, 270+208,-125, obj.getObjectHeight()/2);

		obj.sq_StartWrite();
		obj.sq_WriteDword(power2 );	// attackBonusRate
		obj.sq_WriteDword(104);	// attackBonusRate
		obj.sq_WriteDword(2);	// attackBonusRate
		obj.sq_WriteDword( atkT );	// attackBonusRate
		obj.sq_WriteDword(saveT );	// attackBonusRate
		obj.sq_WriteDword(-22 );	// attackBonusRate
		obj.sq_SendCreatePassiveObjectPacket(24357, 0, 322,-20,  obj.getObjectHeight()/2);

        if (!isEventHorizen(obj) )
            setBreakSenseEnegry(obj,getBreakSenseEnegry(obj) + obj.sq_GetIntData(SKILL_BLACKHOLE, 0) );

    }
}

function getScrollBasisPos_BLACKHOLE(obj)
{
    if (!obj || isEventHorizen(obj) )
        return false;


    local state = obj.getSkillSubState();
    local yPos = obj.getYPos();
    if (state == 1)
    {
        local saveT = sq_GetLevelData(obj, SKILL_BLACKHOLE, 3, sq_GetSkillLevel(obj, SKILL_BLACKHOLE));
        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);
        local destX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), obj.sq_GetIntData(SKILL_BLACKHOLE, 2));
        if (currentT < obj.sq_GetIntData(SKILL_BLACKHOLE, 3))
        {
//            local v = sq_GetAccel(obj.getXPos(), destX, currentT, obj.sq_GetIntData(SKILL_BLACKHOLE, 3), true);
            local v = sq_GetUniformVelocity(obj.getXPos(), destX, currentT, obj.sq_GetIntData(SKILL_BLACKHOLE, 3) );
            obj.sq_SetCameraScrollPosition(v, yPos, 0);
            return true;
        }else if (currentT > saveT - obj.sq_GetIntData(SKILL_BLACKHOLE, 4))
        {
            local v = sq_GetAccel( destX , obj.getXPos(), currentT - (saveT - obj.sq_GetIntData(SKILL_BLACKHOLE, 4)), obj.sq_GetIntData(SKILL_BLACKHOLE, 4), true);

            obj.sq_SetCameraScrollPosition(v, yPos, 0);
            return true;
        }else{
            obj.sq_SetCameraScrollPosition(destX, yPos, 0);
            return true;
        }
    }
    return false;
}

function addPartlcAniBlockHole_1(obj,ani,x,y,z)
{

	local ani = sq_CreateAnimation("",ani);
	local pooledObj = sq_CreatePooledObject(ani,true);
    local objectManager = obj.getObjectManager();
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );

}

function addPartlcAniBlockHole_2(obj,ani,x,y,z)
{

	local ani = sq_CreateAnimation("",ani);
	local pooledObj = sq_CreatePooledObject(ani,true);
    local objectManager = obj.getObjectManager();
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y, obj.getZPos() + z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
//    obj.getVar("effectObj").push_obj_vector( pooledObj );

}

function onProc_BLACKHOLE(obj)
{
    local state = obj.getSkillSubState();
    if (state == 0)
    {

    }else if (state == 1)
    {
        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);
        local saveT = sq_GetLevelData(obj, SKILL_BLACKHOLE, 3, sq_GetSkillLevel(obj, SKILL_BLACKHOLE));

        if (isEventHorizen(obj) )
            saveT = obj.sq_GetIntData(SKILL_BLACKHOLE, 5);

        if (currentT > saveT)
        {
            if (isEventHorizen(obj))
                removeEventHorizen(obj);

            obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);



        }
    }
}


function onEndState_BLACKHOLE(obj, new_state)
{
    if (new_state != STATE_BLACKHOLE)
    {
//        setVliadEffectBlockHole(obj);
    }
}

function setVliadEffectBlockHole(obj)
{
    local var = obj.getVar("effectObj");  		
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


function onEndCurrentAni_BLACKHOLE(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
    local state = obj.getSkillSubState();
    if (state == 0)
    {
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 1);
			
			obj.addSetStatePacket(STATE_BLACKHOLE , pIntVec, STATE_PRIORITY_FORCE, false, "");
    }else if (state == 1)
    {
        
        if (isEventHorizen(obj) )
        {
            removeEventHorizen(obj);
            obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
        }
    }
}