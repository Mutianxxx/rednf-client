//shake 1 100
function checkExecutableSkill_particlehop(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_PARTICLEHOP);

	if (isUse) {

        if (obj.sq_GetState() == STATE_DAMAGE || obj.sq_GetState() == STATE_DOWN )
        {
            setBreakSenseEnegry(obj,getBreakSenseEnegry(obj) - obj.sq_GetIntData(SKILL_PARTICLEHOP, 2) * 100 );
        }

		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0); 
		obj.sq_AddSetStatePacket(STATE_PARTICLEHOP , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}

function checkCommandEnable_particlehop(obj)
{
	if (!obj) return false;

	if (obj.sq_GetState() == STATE_DAMAGE || obj.sq_GetState() == STATE_DOWN )
    {
        if (getBreakSenseEnegry(obj) < 100)
        {
            return false;
        }
    }
	return true;
}
//PARTICLEHOP

function onSetState_PARTICLEHOP(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
    obj.sq_SetShake(obj, 1, 100);
	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_PARTILEHOP_BODY);
	obj.sq_SetCurrentAttackInfo(ATTACKINFO_PARTICLEHOP );

	local power = obj.sq_GetPowerWithPassive(SKILL_PARTICLEHOP, STATE_PARTICLEHOP, 0, -1, 1.0);
    local attackInfo = sq_GetCurrentAttackInfo(obj);
    sq_SetCurrentAttackPower(attackInfo, power);
    createParticleAttackEffect(obj,0,0);
//ATTACKINFO_PARTICLEHOP 
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
}

function onEndCurrentAni_PARTICLEHOP(obj)
{
    if (!obj.isMyControlObject())
        return false;
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}


function createParticleAttackEffect(obj,len,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atdimensionleap/attack_05.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), len);
	
	pooledObj.setCurrentPos(posX,obj.getYPos() + 1,obj.getZPos() + obj.getObjectHeight()/2);
	
	pooledObj.setCurrentDirection(obj.getDirection());
	
	sq_AddObject(obj,pooledObj,0,false);	
}


function createParticleMoveEffect(obj,len,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atdimensionleap/moveeffect.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), len);
	
	pooledObj.setCurrentPos(posX,obj.getYPos() + 1,obj.getZPos());
	
	pooledObj.setCurrentDirection(obj.getDirection());
	
	sq_AddObject(obj,pooledObj,0,false);	
}


function onKeyFrameFlag_PARTICLEHOP(obj,flagIndex)
{
	if(!obj)
		return false;
    if (!obj.isMyControlObject())
        return false;
    if (obj.getVar("flag").get_vector(0) == 0)
    {
        obj.getVar("flag").set_vector(0,1);

        local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),-obj.sq_GetIntData(SKILL_PARTICLEHOP, 1) );
        obj.sq_SetfindNearLinearMovablePos(posX ,obj.getYPos(),obj.getXPos(), obj.getYPos(), 10);
        createParticleMoveEffect(obj,1,0);
        setBreakSenseEnegry(obj,getBreakSenseEnegry(obj) + obj.sq_GetIntData(SKILL_PARTICLEHOP, 0) );

    }
}


function onAttack_PARTICLEHOP(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return false;
	local featurelevel = sq_GetSkillLevel(obj, 250);
	if(featurelevel>0){
		if(damager.getState() != STATE_HOLD ) 
		{
			local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_PARTICLEHOP, false, "character/atmage/particlehop/ap_particlehop.nut", true);				 
			if(masterAppendage) 
			{
				sq_HoldAndDelayDie(damager, obj, true, false, false, 200, 200, ENUM_DIRECTION_NEUTRAL , masterAppendage);
				masterAppendage.sq_SetValidTime(1500);
			}

		}
	}else{
		local save = sq_GetIntData(obj, SKILL_PARTICLEHOP, 1, sq_GetSkillLevel(obj, SKILL_PARTICLEHOP) );
		if(damager.getState() != STATE_HOLD && !sq_IsFixture(damager)) 
		{
			local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_PARTICLEHOP, false, "character/atmage/particlehop/ap_particlehop.nut", true);				 
			if(masterAppendage) 
			{
				sq_HoldAndDelayDie(damager, obj, true, false, false, 200, 200, ENUM_DIRECTION_NEUTRAL , masterAppendage);
				masterAppendage.sq_SetValidTime(save);
			}

		}
	}
}

