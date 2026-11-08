function checkExecutableSkill_bloodhold(obj)  
{
	if (!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_BLOODHOLD);
    if (isUse)
    {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0); 
        obj.sq_AddSetStatePacket(STATE_BLOODHOLD, STATE_PRIORITY_USER, true);
    }
    return true;
}

function checkCommandEnable_bloodhold(obj)
{
	if(!obj)
		return false;
    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_BLOODHOLD, 4))) 
        return false;

		
	return true;
}

function createBloodHoldCastingEffect0(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atshikaree/shikaree_cast_eff01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}
function createBloodHoldShootEffect0(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atshikaree/shikaree_shot_effect.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}
function onSetState_BLOODHOLD(obj, state, datas, isResetTimer)
{

	obj.sq_StopMove();
	
    local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
    if (state == 0)
    {
        if (obj.isMyControlObject())
            setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOODHOLD, 4));
        createBloodHoldCastingEffect0(obj);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_SHIKAREE_CASTING);

    }else if (state == 1)
    {
        local dir = 0;
		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);
        
		if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && leftPress) dir = 1;
		if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && rightPress) dir = 1;
        
        obj.getVar("dir").clear_vector();
        obj.getVar("dir").push_vector(dir);

        if (obj.isMyControlObject())
        {
            local attT = getBloodHoldHitTimeByDirVector(obj) / obj.sq_GetIntData(SKILL_BLOODHOLD, 0);
            
            

            local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOODHOLD, STATE_BLOODHOLD, 0, 1.0);
            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
            obj.sq_WriteDword(59);	// attackBonusRate
            obj.sq_WriteDword(dir);	// attackBonusRate
            obj.sq_WriteDword( attT );	// attackBonusRate
            obj.sq_WriteDword( obj.sq_GetIntData(SKILL_BLOODHOLD, 1) );	// attackBonusRate
            obj.sq_WriteDword( obj.sq_GetIntData(SKILL_BLOODHOLD, 2) );	// attackBonusRate

            obj.sq_WriteDword( obj.sq_GetIntData(SKILL_BLOODHOLD, 5) );	// attackBonusRate
            obj.sq_WriteDword( obj.sq_GetIntData(SKILL_BLOODHOLD, 6) );	// attackBonusRate
            obj.sq_WriteDword( obj.sq_GetIntData(SKILL_BLOODHOLD, 7) );	// attackBonusRate
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);
        }
        createBloodHoldShootEffect0(obj);
    	obj.sq_SetCurrentAnimation(CUSTOM_ANI_SHIKAREE_ATTACK);


    }
	local currentAni = sq_GetCurrentAnimation(obj);
	currentAni.setSpeedRate(150.0 );
}

function getBloodHoldHitTimeByDirVector(obj)
{

    if (obj.getVar("dir").get_vector(0) == 0)
    {
        return 900;
    }
    return 960;
}


function createBloodHoldSpearNormalDirection(obj,x,y,z,size)
{
    local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atshikaree/shikaree_thorn_effect01.ani");
    local sizeRate = size.tofloat()/100.0;
    ani.setImageRateFromOriginal(sizeRate, sizeRate);
    ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

	local pooledObj = sq_CreatePooledObject(ani,true);
    local lastY = y + sq_getRandom(-20,20).tointeger() * size / 100;
	pooledObj.setCurrentPos(x, lastY ,z );
	pooledObj.setCurrentDirection(obj.getDirection());
    createBloodHoldThornFloorEffect(obj,x,lastY ,z,size,obj.getDirection() );
	sq_AddObject(obj,pooledObj,2,false);	
    
}


function createBloodHoldSpearOppositeDirection(obj,x,y,z,size)
{
    local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atshikaree/shikaree_thorn_effect01.ani");
    local sizeRate = size.tofloat()/100.0;
    ani.setImageRateFromOriginal(sizeRate, sizeRate);
    ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

	local pooledObj = sq_CreatePooledObject(ani,true);
    local lastY = y + sq_getRandom(-20,20).tointeger() * size / 100;
	pooledObj.setCurrentPos(x,lastY ,z );
	pooledObj.setCurrentDirection( sq_GetOppositeDirection(obj.getDirection() ) );
    createBloodHoldThornFloorEffect(obj,x,lastY ,z,size,sq_GetOppositeDirection(obj.getDirection() )   );
	sq_AddObject(obj,pooledObj,2,false);	
}


function createBloodHoldThornFloorEffect(obj,x,y,z,size,dir)
{
    local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atshikaree/shikaree_thorn_floor.ani");
    local sizeRate = size.tofloat()/100.0;
    ani.setImageRateFromOriginal(sizeRate, sizeRate);
    ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

	local pooledObj = sq_CreatePooledObject(ani,true);
    pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	pooledObj.setCurrentPos(x,y,z );
	pooledObj.setCurrentDirection( dir );
	sq_AddObject(obj,pooledObj,2,false);	

}


function onEndCurrentAni_BLOODHOLD(obj)
{
    local state = obj.getSkillSubState();
    if (state == 0)
    {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1); 
	obj.sq_AddSetStatePacket(STATE_BLOODHOLD, STATE_PRIORITY_USER, true);

    }else if (state == 1)
    {
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}



function setBloodHoldPassiveobjectTargetMoveEffect(obj)
{
            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();


            for(local i=0;i<objectsSize;++i)
            {

                    local damager = var.get_obj_vector(i);
                    local objX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),
                    obj.getVar("value").get_vector(0) * obj.getVar("value").get_vector(3) / 100 );
                    local objY = obj.getYPos();
                    local damaX = damager.getXPos();
                    local damaY = damager.getYPos();
                    local damaZ = damager.getZPos();
                    local x_move = obj.getVar("value").get_vector(1);
                    local y_move = obj.getVar("value").get_vector(2);
                    if (objX < damaX) x_move = - x_move;
                    if (objY < damaY) y_move = - y_move;
                    damager.setCurrentPos(damaX + x_move,damaY + y_move,damaZ);


            }

}
