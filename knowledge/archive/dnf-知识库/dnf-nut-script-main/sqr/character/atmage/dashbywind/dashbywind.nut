
//FLAG 1 MOVE
function checkExecutableSkill_dashbywind(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_DASHBYWIND);

	if (isUse) {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_DASHBYWIND , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}

function checkCommandEnable_dashbywind(obj)
{

	return true;
}

function onSetState_DASHBYWIND(obj, state, datas, isResetTimer)
{
    local state = obj.getVar("state").get_vector(0);
	obj.sq_StopMove();
    if (state == 0)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_DASHBYWIND_BODY);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
    }else if (state == 1)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_DASHBYWIND_BODY2);

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
    }else if (state == 2)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_DASHBYWIND_BODY3);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
    }
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_DASHBYWIND);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_DASHBYWIND , STATE_DASHBYWIND, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				
}

function onProc_DASHBYWIND(obj)
{
	if(!obj) 
		return;
	local state = obj.getVar("state").get_vector(0);
}

function onProcCon_DASHBYWIND(obj)
{
    if(!obj) 
	  return;
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {

            obj.setSkillCommandEnable(SKILL_DASHBYWIND, true);
            local currentAnimation = sq_GetCurrentAnimation(obj);
            local currentFrameIndex = obj.sq_GetCurrentFrameIndex(currentAnimation);
            if( (obj.sq_IsEnterSkill(SKILL_DASHBYWIND) != -1 || sq_IsKeyDown(OPTION_HOTKEY_SKILL, ENUM_SUBKEY_TYPE_ALL) )  && currentFrameIndex > 1)
            {
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(1);
                obj.sq_AddSetStatePacket(STATE_DASHBYWIND , STATE_PRIORITY_USER, false);
            }
        
    }else if (state == 1)
    {

            obj.setSkillCommandEnable(SKILL_DASHBYWIND, true);
            local currentAnimation = sq_GetCurrentAnimation(obj);
            local currentFrameIndex = obj.sq_GetCurrentFrameIndex(currentAnimation);
            if ( (obj.sq_IsEnterSkill(SKILL_DASHBYWIND) != -1 || sq_IsKeyDown(OPTION_HOTKEY_SKILL, ENUM_SUBKEY_TYPE_ALL) )&& currentFrameIndex > 1)   //|| sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
            {
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(2);
                obj.sq_AddSetStatePacket(STATE_DASHBYWIND , STATE_PRIORITY_USER, false);
            }
        
    }
}


function onEndCurrentAni_DASHBYWIND(obj)
{

    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
		obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }else if (state == 1)
    {
		obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {
		obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
		obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }
}


function onKeyFrameFlag_DASHBYWIND(obj,flagIndex)
{
    local state = obj.getVar("state").get_vector(0);
    if (flagIndex == 2)
    {
        obj.getVar("flag").set_vector(1,1);
    }
    if (obj.getVar("flag").get_vector(0) == 0)
    {
        obj.getVar("flag").set_vector(0,1);
        if (state == 0)
        {

            local dstX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), obj.sq_GetIntData(SKILL_DASHBYWIND, 0) );
            obj.sq_SetfindNearLinearMovablePos(dstX ,obj.getYPos(),obj.getXPos() , obj.getYPos(), 10);
            createStep1_DASHBYWIND(obj);
        }else if (state == 1){

            local dstX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), obj.sq_GetIntData(SKILL_DASHBYWIND, 1) );
            obj.sq_SetfindNearLinearMovablePos(dstX ,obj.getYPos(),obj.getXPos() , obj.getYPos(), 10);
            createStep2_DASHBYWIND(obj);
        }else if (state == 2){

            local dstX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), obj.sq_GetIntData(SKILL_DASHBYWIND, 2) );
            obj.sq_SetfindNearLinearMovablePos(dstX ,obj.getYPos(),obj.getXPos() , obj.getYPos(), 10);
            createStep3_DASHBYWIND(obj);
        }
    }
}


function createStep1_DASHBYWIND(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atsonicmove/sonicmovestep1_smoke.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);	
}


function createStep2_DASHBYWIND(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atsonicmove/sonicmovestep2_winda.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);	
}


function createStep3_DASHBYWIND(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atsonicmove/sonicmovestep3_smoke.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);	
}