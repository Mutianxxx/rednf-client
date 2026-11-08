function checkExecutableSkill_stormquake(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_STORMQUAKE);

	if (isUse) {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_STORMQUAKE);
		obj.sq_AddSetStatePacket(STATE_STORMQUAKE , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}




function checkCommandEnable_stormquake(obj)
{
	

	return true;
}

function onSetState_STORMQUAKE(obj, state, datas, isResetTimer)
{

	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
    if (state == 0)
    {
        local distance = obj.sq_GetIntData(SKILL_STORMQUAKE, 0);
        obj.getVar("dis").clear_vector();
        obj.getVar("dis").push_vector(distance);
        obj.getVar("isEnd").clear_vector();
        obj.getVar("isEnd").push_vector(0);

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_STORMQUAKE_CASTING);

    }else if (state == 1){
    createStormQuakeLoopShootEffect(obj,0,1,0);
    createStormQuakeLoopShootDustEffect(obj,0,1,0);


		obj.sq_SetCurrentAnimation(CUSTOM_ANI_STORMQUAKE_SHOOTING);

    }
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

}
function onKeyFrameFlag_STORMQUAKE(obj,flagIndex)
{
    if(!obj.isMyControlObject())
        return false;
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        if (flagIndex == 2)
        {
            if (obj.getVar("flag").get_vector(0) == 0)
            {
                obj.getVar("flag").clear_vector();
                obj.getVar("flag").push_vector(1);
                local damage0 = obj.sq_GetBonusRateWithPassive(SKILL_STORMQUAKE , STATE_STORMQUAKE, 0, 1.0);
                local damage1 = obj.sq_GetBonusRateWithPassive(SKILL_STORMQUAKE , STATE_STORMQUAKE, 1, 1.0);
                local level = sq_GetSkillLevel(obj, SKILL_STORMQUAKE);		
                local atkTime = sq_GetLevelData(obj, SKILL_STORMQUAKE, 2, level);
        
                local distance = obj.getVar("dis").get_vector(0);
		   local size = obj.sq_GetIntData(SKILL_STORMQUAKE,2);
		   
                sq_flashScreen(obj,0,40,120,150, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
                obj.sq_SetShake(obj, 5, 40);

                obj.sq_StartWrite();
                obj.sq_WriteDword(damage0);	// attackBonusRate
                obj.sq_WriteDword(18);
                obj.sq_WriteDword(atkTime);
                obj.sq_WriteDword(distance);
                obj.sq_WriteDword(damage1);
                obj.sq_WriteDword(size);

                obj.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);
            }

        }

    }else if (state == 1){
            if (flagIndex == 2)
            {
                if (obj.getVar("flag").get_vector(0) == 0)
                {

                    local iceCoreObj = obj.getMyPassiveObject(24357,0);
                    if(iceCoreObj )//&& iceCoreObj.getVar("id").get_vector(0) == 18 )
                    {
                        
                        iceCoreObj.getVar("state").set_vector(0,1);
                    }

                }
            }

    }

}
function onProc_STORMQUAKE(obj)
{
	if(!obj.isMyControlObject())
		return false;
	local state = obj.getVar("state").get_vector(0);
	if (state == 0)
	{
		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

		if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && rightPress) obj.getVar("dis").set_vector(0,obj.sq_GetIntData(SKILL_STORMQUAKE, 1));
		if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && leftPress) obj.getVar("dis").set_vector(0,obj.sq_GetIntData(SKILL_STORMQUAKE, 1));


		local pAni = obj.sq_GetCurrentAni();
		local currentT = sq_GetCurrentTime(pAni);
    

		if(obj.isDownSkillLastKey())
		{
			if(currentT > 740){

				obj.getVar("state").clear_vector();
				obj.getVar("state").push_vector(1);
				obj.sq_AddSetStatePacket(STATE_STORMQUAKE , STATE_PRIORITY_USER, false);
        		}

		}else{
			if(obj.getVar("isEnd").get_vector(0) == 1){
				obj.getVar("state").clear_vector();
				obj.getVar("state").push_vector(1);
				obj.sq_AddSetStatePacket(STATE_STORMQUAKE , STATE_PRIORITY_USER, false);
			}
		}

	}

}



function onEndCurrentAni_STORMQUAKE(obj)
{
    if(!obj.isMyControlObject())
        return false;
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.getVar("isEnd").clear_vector();
        obj.getVar("isEnd").push_vector(1);
//        obj.getVar("state").clear_vector();
//        obj.getVar("state").push_vector(1);
//        obj.sq_AddSetStatePacket(STATE_STORMQUAKE , STATE_PRIORITY_USER, false);
    }else{
		obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }

}


function setValidStormQuakePooledObject(obj)
{
    for (local i = 0;i < obj.getVar("effectObj").get_obj_vector_size();i++)
    {
        local pooledObj = obj.getVar("effectObj").get_obj_vector(i);
        if (pooledObj)
            pooledObj.setValid(false);
    }

}


function createStormQuakeLoopFloorEffect(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atstormquake/stormquake_b_windfloor_loop11.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector(pooledObj);
}




function createStormQuakeLoopShootEffect(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atstormquake/stormquake_d_shot02.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}


function createStormQuakeLoopShootDustEffect(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atstormquake/stormquake_move_wind01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}



function createStormQuakeLoopShootAEffect(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atstormquake/cloud_move_bigcloud01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}



function createStormQuakeLoopShootABackEffect(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atstormquake/stormquake_a_back_pang01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}



function createStormQuakeLoopBigCloud01Effect(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atstormquake/cloud_c_bigcloud01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}



function createStormQuakeLoopBigCloud01BackEffect(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atstormquake/stormquake_a_back_pang01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}



function createStormQuakeLoopCastingEffect(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atstormquake/stormquake_a_cast.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}

