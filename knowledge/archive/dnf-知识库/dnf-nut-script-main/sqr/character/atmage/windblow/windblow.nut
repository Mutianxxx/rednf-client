function checkExecutableSkill_windblow(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_WINDBLOW);

	if (isUse) {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_WINDBLOW);
		obj.sq_AddSetStatePacket(STATE_WINDBLOW , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}


function createBackWindBlowFloor(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atstormstrikes/stormstrikes_c02_move_floor_eff01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX ,obj.getYPos() - 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createWindBlowLoopBackPooledObject(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atstormstrikes/stormstrikes_c01_stand_back_eff02.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	//pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX ,obj.getYPos() - 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createWindBlowLoopFrontPooledObject(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atstormstrikes/stormstrikes_c01_stand_front_eff02.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	//pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createWindBlowEndBackPooledObject(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atstormstrikes/stormstrikesc02back_03.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	//pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX ,obj.getYPos() - 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createWindBlowEndFrontPooledObject(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atstormstrikes/stormstrikesc02front_05.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	//pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function checkCommandEnable_windblow(obj)
{

	return true;
}

function onSetState_WINDBLOW(obj, state, datas, isResetTimer)
{
    obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.getVar("dama").clear_obj_vector();

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_WINDBLOW_READY);


        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);     

        obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
            SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

    }else if (state == 1){

        xifuMonster_WINDBLOW(obj);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_WINDBLOW_LOOP);

        
    }else if (state == 2){
        createWindBlowLoopBackPooledObject(obj);
        createWindBlowLoopFrontPooledObject(obj);
        createBackWindBlowFloor(obj);
        sq_flashScreen(obj,0,420,400,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        obj.sq_SetShake(obj, 12, 240);
        local distance = obj.sq_GetIntData(SKILL_WINDBLOW, 1);
        local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
        local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

        if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && rightPress) distance = obj.sq_GetIntData(SKILL_WINDBLOW, 2);
        if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && leftPress) distance = obj.sq_GetIntData(SKILL_WINDBLOW, 2);



        obj.sq_SetCurrentAnimation(CUSTOM_ANI_WINDBLOW_LAST);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_WINDBLOW_LAST);

        local damage = obj.sq_GetBonusRateWithPassive(SKILL_WINDBLOW , STATE_WINDBLOW, 0, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);				
        
        obj.getVar().clear_vector();
        obj.getVar().push_vector( obj.getXPos() );
        obj.getVar().push_vector( distance );
        
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0); 

    }
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);
}


function xifuMonster_WINDBLOW(obj)
{
    local state = obj.getVar("state").get_vector(0);

	local objectManager = obj.getObjectManager();
	local object = null;
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isInDamagableState(obj) && object.isObjectType(OBJECTTYPE_ACTIVE) &&
			isInFrontObject(obj, object))
        {
            obj.getVar("dama").push_obj_vector(object);
        }
    }

}

function xifuMonsterIng_WINDBLOW(obj)
{

        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();

        if (objectsSize > 0)
        {

            local objX = sq_GetDistancePos(obj.getXPos() ,obj.getDirection(),obj.sq_GetIntData(SKILL_WINDBLOW, 3) );
            local objY = obj.getYPos();
            local x_move = 3;
            local y_move = 1;

            for(local i=0;i<objectsSize;++i)
            {
                local damager = var.get_obj_vector(i);

                local damaX = damager.getXPos();
                local damaY = damager.getYPos();
                local damaZ = damager.getZPos();

                if (objX < damaX) x_move = - x_move;
                if (objY < damaY) y_move = - y_move;

                damager.setCurrentPos(damaX + x_move,damaY + y_move,damaZ);


            }
        }

}


function onTimeEvent_WINDBLOW(obj, timeEventIndex, timeEventCount)
{

    local state = obj.getVar("state").get_vector(0);

}

function onEndState_WINDBLOW(obj,newState) 
{

    local state = obj.getVar("state").get_vector(0);
    if (state == 2)
    {
      local flashObj = obj.getVar("flashScreenObj").get_obj_vector(0);
      
      if (flashObj)
      {
      
          local pflashScreen = sq_GetCNRDObjectToFlashScreen(flashObj);
          if(pflashScreen)
            pflashScreen.fadeOut();
      
      }
    
    
    }

}


function onProc_WINDBLOW(obj)
{

    local state = obj.getVar("state").get_vector(0);

    local pAni = obj.sq_GetCurrentAni();
    local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
    local currentT = sq_GetCurrentTime(pAni);

    if (state == 0)
    {
        if (frmIndex >= 2 && obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").set_vector(0,1);
         
            local flashObj = sq_flashScreen(obj,720,999999,0,102,
            sq_RGB(0,0,0),   GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            obj.sq_SetShake(obj, 4, 120);

            obj.getVar("flashScreenObj").clear_obj_vector();
            obj.getVar("flashScreenObj").push_obj_vector(flashObj);

        }else if (frmIndex >= 2)
        {
          //xifuMonsterIng_WINDBLOW(obj);
        
        }
    }else if (state == 1){

        if(!obj.isDownSkillLastKey() || currentT > obj.sq_GetIntData(SKILL_WINDBLOW, 0) )
        {

            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(2);
            obj.sq_AddSetStatePacket(STATE_WINDBLOW , STATE_PRIORITY_USER, false);
        }

        xifuMonsterIng_WINDBLOW(obj);

    }else if (state == 1)
    {

    }else if (state == 2)
    {
    
    
            local pAni = obj.sq_GetCurrentAni();
            local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);


            local startFrameIndex = 0;
            local endFrameIndex = 1;

            local currentT = sq_GetCurrentTime(pAni);

            if (frmIndex <= startFrameIndex)
            {
                obj.setCurrentPos(obj.getVar().get_vector(0),obj.getYPos(),obj.getZPos() );

            }else if (frmIndex >= startFrameIndex && frmIndex <= endFrameIndex)
            {
                local startX = obj.getVar().get_vector(0);
                local maxD = obj.getVar().get_vector(1);

                currentT = currentT - pAni.getDelaySum(0,startFrameIndex);
                local maxT = pAni.getDelaySum(startFrameIndex,endFrameIndex);
                if (currentT < maxT)
                {
                    local v = sq_GetAccel(0, maxD, currentT,maxT, true);
                    local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);

                    if( obj.isMovablePos(dstX, obj.getYPos() ))
                    {
                        sq_setCurrentAxisPos(obj, 0, dstX);
                    }

                }
            }else{
                if (obj.getVar("flag").get_vector(0) == 0)
                {
                
                  obj.getVar("flag").set_vector(0,1);
                  //createWindBlowEndBackPooledObject(obj);
                  //createWindBlowEndFrontPooledObject(obj);
                
                }
            }
    }
}

function onEndCurrentAni_WINDBLOW(obj)
{

    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_WINDBLOW , STATE_PRIORITY_USER, false);
    }else if (state == 2){

		obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }

}


function onAttack_WINDBLOW(obj, damager, boundingBox, isStuck)
{
	if (!obj || !damager) return;

    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {

    }else if (state == 1)
    {

    }else if (state == 2)
    {

        local id = sq_GetObjectId(damager);
        local hitCount = obj.sq_GetIntData(SKILL_WINDBLOW, 4);
        local attackBounsRate = obj.sq_GetBonusRateWithPassive(SKILL_WINDBLOW , STATE_WINDBLOW, 1, 1.0);;

        sq_BinaryStartWrite();
        sq_BinaryWriteDword(attackBounsRate);	// attackBonusRate
        sq_BinaryWriteDword(192);	// attackBonusRate
        sq_BinaryWriteDword(id);	// attackBonusRate
        sq_BinaryWriteDword(hitCount);
        obj.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);
    }

}


