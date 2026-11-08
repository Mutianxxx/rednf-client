//
function checkExecutableSkill_bloodstay(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_BLOODSTAY);

	if (isUse) {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_BLOODSTAY , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}




function checkCommandEnable_bloodstay(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();

	
	return true;
}

function createBloodStayMoveDust(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atcreeping/creepingdust_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}

function createBloodStayEndSky(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atcreeping/creepingendsky02_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}


function onSetState_BLOODSTAY(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	obj.sq_StopMove();

    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOODSTAY_0);

    }else{


		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

        createBloodStayMoveDust(obj);
        local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),obj.sq_GetIntData(SKILL_BLOODSTAY, 0) );
        obj.sq_SetfindNearLinearMovablePos(posX ,obj.getYPos(),obj.getXPos(), obj.getYPos(), 10);
        createBloodStayEndSky(obj);
        if (!leftPress && !rightPress)
        {
			obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
        }

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOODSTAY_1);

    }

	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
    

}
//zrr

function onEndCurrentAni_BLOODSTAY(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {
        sq_SendMessage(obj,OBJECT_MESSAGE_INVINCIBLE,1,0);
        sq_PostDelayedMessage(obj,OBJECT_MESSAGE_INVINCIBLE,0,0,obj.sq_GetIntData(SKILL_BLOODSTAY, 1) );
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
    }else{
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_BLOODSTAY , STATE_PRIORITY_USER, false);
    }
}



