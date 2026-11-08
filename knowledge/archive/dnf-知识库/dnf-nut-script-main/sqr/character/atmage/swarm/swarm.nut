//shake 1 30

function checkExecutableSkill_swarm(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWARM);

	if (isUse) {

			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			
			obj.addSetStatePacket(STATE_SWARM , pIntVec, STATE_PRIORITY_FORCE, false, "");


		return true;
	}

	return false;
}

function checkCommandEnable_swarm(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_SWARM);		
    local useHp = sq_GetLevelData(obj, SKILL_SWARM, 0, level);
    if (obj.getHp() < useHp )
        return false;

	return true;




}
//SWARM
function createSwarmOutEffect(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atswarm/swarmout_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createSwarmGateDisappear(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atswarm/endgate_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function onSetState_SWARM(obj, state, datas, isResetTimer)
{

	obj.sq_StopMove();
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);

    if (state == 0)
    {


		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWARM_CASTING );

		local castTime = sq_GetCastTime(obj, SKILL_SWARM, sq_GetSkillLevel(obj, SKILL_SWARM)  );
		local animation = sq_GetCurrentAnimation(obj);
		local startTime = animation.getDelaySum(false);
		local speedRate = startTime.tofloat() / castTime.tofloat();
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);

		sq_StartDrawCastGauge(obj, castTime, true);
    }else if (state == 1)
    {


        if(obj.isMyControlObject())
        {
            local level = sq_GetSkillLevel(obj, SKILL_SWARM);		
            local useHp = sq_GetLevelData(obj, SKILL_SWARM, 0, level);
            obj.setHp( obj.getHp() - useHp, null, true);
            local power = obj.sq_GetPowerWithPassive(SKILL_SWARM, STATE_SWARM, 1, -1, 1.0);
            obj.sq_StartWrite();
            obj.sq_WriteDword( power);	// attackBonusRate
            obj.sq_WriteDword(20);
            obj.sq_WriteDword( obj.sq_GetIntData(SKILL_SWARM, 0) );//maxS
            obj.sq_WriteDword(obj.sq_GetIntData(SKILL_SWARM, 1) / obj.sq_GetIntData(SKILL_SWARM, 0) );//summT
            obj.sq_WriteDword(obj.sq_GetIntData(SKILL_SWARM, 2) );//dashD
            obj.sq_WriteDword(obj.sq_GetIntData(SKILL_SWARM, 3) );//dashT

            obj.sq_SendCreatePassiveObjectPacket(24364, 0, obj.sq_GetIntData(SKILL_SWARM, 4), obj.sq_GetIntData(SKILL_SWARM, 5), obj.sq_GetIntData(SKILL_SWARM, 6));
            sq_SetMyShake(obj, 4, 200);
        }
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWARM_START);


    }else if (state == 2)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWARM_END);
    }
}
function onProc_SWARM(obj)
{
    
}

function onEndCurrentAni_SWARM(obj)
{
    if(!obj.isMyControlObject())
        return false;
    local state = obj.getSkillSubState();
    if (state == 0)
    {
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 1);
			
			obj.addSetStatePacket(STATE_SWARM , pIntVec, STATE_PRIORITY_FORCE, false, "");
    }else if (state == 1)
    {
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 2);
			
			obj.addSetStatePacket(STATE_SWARM , pIntVec, STATE_PRIORITY_FORCE, false, "");
    }else if (state == 2)
    {
		obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }

}