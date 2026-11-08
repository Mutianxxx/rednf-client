//shake 1 100
function checkExecutableSkill_particleline(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_PARTICLELINE);

	if (isUse) {


			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			
			obj.addSetStatePacket(STATE_PARTICLELINE , pIntVec, STATE_PRIORITY_FORCE, false, "");
		return true;
	}

	return false;
}

function checkCommandEnable_particleline(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	return true;
}
//PARTICLELINE

function createDimensionLayEventHorizenC(obj,x,y,z,size)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atdimensionlay/dimensionlay_eventhorizen_laser_b01.ani");
        local sizeRate = size.tofloat()/100.0;
        ani.setImageRateFromOriginal(1.0, sizeRate);

	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createDimensionLayEventHorizenA(obj,x,y,z,size)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atdimensionlay/dimensionlay_eventhorizen_laser_a01.ani");
        local sizeRate = size.tofloat()/100.0;
        ani.setImageRateFromOriginal(1.0, sizeRate);

	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function onSetState_PARTICLELINE(obj, state, datas, isResetTimer)
{
	if(!obj) return;

	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
	obj.sq_StopMove();
    if (state == 0)
    {

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_PARTICLELINE_CASTING );
        obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("atanimation/als_ani/atdimensionlay/dimensionlay_cast_eff02.ani"), 0, 0);
        obj.sq_AddStateLayerAnimation(2, obj.sq_CreateCNRDAnimation("atanimation/als_ani/atdimensionlay/dimensionlay_cast_loopeff.ani"), 0, 0);

		local castTime = sq_GetCastTime(obj, SKILL_PARTICLELINE, sq_GetSkillLevel(obj, SKILL_PARTICLELINE)  );
		local animation = sq_GetCurrentAnimation(obj);
		local startTime = animation.getDelaySum(false);
		local speedRate = startTime.tofloat() / castTime.tofloat();
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);

		sq_StartDrawCastGauge(obj, castTime, true);

    }else if (state == 1)
    {

        if (obj.isMyControlObject())
        {
            sq_SetMyShake(obj, 2, 150);
            local power = obj.sq_GetPowerWithPassive(SKILL_PARTICLELINE, STATE_PARTICLELINE, 0, -1, 1.0);
            local hitC = sq_GetLevelData(obj, SKILL_PARTICLELINE, 1, sq_GetSkillLevel(obj, SKILL_PARTICLELINE) );
            obj.sq_StartWrite();
            obj.sq_WriteDword(power );	// attackBonusRate
            obj.sq_WriteDword(102);	// attackBonusRate
            obj.sq_WriteDword( hitC - 1);	// attackBonusRate

            obj.sq_SendCreatePassiveObjectPacket(24357, 0, obj.sq_GetIntData(SKILL_PARTICLELINE, 2), obj.sq_GetIntData(SKILL_PARTICLELINE, 3), obj.sq_GetIntData(SKILL_PARTICLELINE, 4));
        }
        setBreakSenseEnegry(obj,getBreakSenseEnegry(obj) + obj.sq_GetIntData(SKILL_PARTICLELINE, 0) );
        
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_PARTICLELINE_SHOOT);

        obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("atanimation/als_ani/atdimensionlay/dimensionlay_circle_eff01.ani"), 0, 0);
    }else if (state == 2)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_PARITCLELINE_EVENTHROIZEN_SHOOT );
        removeEventHorizen(obj);

    }else if (state == 3)
    {

        sq_SetMyShake(obj, 2, 150);
//        setBreakSenseEnegry(obj,getBreakSenseEnegry(obj) + obj.sq_GetIntData(SKILL_PARTICLELINE, 1) );
		local power = obj.sq_GetPowerWithPassive(SKILL_PARTICLELINE, STATE_PARTICLELINE, 2, -1, 1.0);
        local xpos = obj.sq_GetIntData(SKILL_PARTICLELINE, 5);
        local ypos = obj.sq_GetIntData(SKILL_PARTICLELINE, 6);
        local zpos = obj.sq_GetIntData(SKILL_PARTICLELINE, 7);

        local size = obj.sq_GetIntData(SKILL_PARTICLELINE, 8);


//createDimensionLayEventHorizenC(obj,x,y,z)
        if (obj.isMyControlObject())
        {
            obj.sq_StartWrite();
            obj.sq_WriteDword(power );	// attackBonusRate
            obj.sq_WriteDword(113);	// attackBonusRate
            obj.sq_WriteDword(size);	// attackBonusRate
            obj.sq_SendCreatePassiveObjectPacket(24357, 0,xpos , ypos, zpos);

    //        local startX = xpos;//- 256;

            createDimensionLayEventHorizenA(obj,xpos , ypos, zpos,size);
            for (local i = 0;i <= 9;i++)
            {
                local startX = xpos;
                startX = startX + 100 * i;
                createDimensionLayEventHorizenC(obj,startX,ypos,zpos,size);
            }
        }
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_PARTICLELINE_SHOOT );
        removeEventHorizen(obj);

        obj.getVar("start").clear_vector();
        obj.getVar("start").push_vector(obj.getXPos() );


    }
}

function getScrollBasisPos_PARTICLELINE(obj)
{

    local state = obj.getSkillSubState();
    local yPos = obj.getYPos();

    local departT = obj.sq_GetIntData(SKILL_PARTICLELINE, 9);
    local returnT = obj.sq_GetIntData(SKILL_PARTICLELINE, 10);
    local maxDistance = obj.sq_GetIntData(SKILL_PARTICLELINE, 11);
    local saveT = obj.sq_GetIntData(SKILL_PARTICLELINE, 12);


    if (state == 3)
    {
        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);



        local destX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), maxDistance);
        if (currentT < departT)
        {
//            local v = sq_GetAccel(obj.getXPos(), destX, currentT, departT, true);
            local v = sq_GetUniformVelocity(obj.getXPos(), destX, currentT, departT );
            obj.sq_SetCameraScrollPosition(v, yPos, 0);
            return true;
        }else if (currentT > saveT - returnT )
        {
            local v = sq_GetAccel( destX , obj.getXPos(), currentT - (saveT - returnT), returnT, true);

            obj.sq_SetCameraScrollPosition(v, yPos, 0);
            return true;
        }else{
            obj.sq_SetCameraScrollPosition(destX, yPos, 0);
            return true;
        }
    }
    return false;
}

//CUSTOM_ANI_PARITCLELINE_EVENTHROIZEN_SHOOT
function onEndCurrentAni_PARTICLELINE(obj)
{
    if (!obj.isMyControlObject())
        return false;
    local state = obj.getSkillSubState();
    if (state == 0)
    {
        if (!isEventHorizen(obj))
        {
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 1);
			
			obj.addSetStatePacket(STATE_PARTICLELINE , pIntVec, STATE_PRIORITY_FORCE, false, "");
        }else{
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 2);
			
			obj.addSetStatePacket(STATE_PARTICLELINE , pIntVec, STATE_PRIORITY_FORCE, false, "");
        }

    }else if (state == 1)
    {
		obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 3);
			
			obj.addSetStatePacket(STATE_PARTICLELINE , pIntVec, STATE_PRIORITY_FORCE, false, "");
    }else if (state == 3)
    {
		obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }
}