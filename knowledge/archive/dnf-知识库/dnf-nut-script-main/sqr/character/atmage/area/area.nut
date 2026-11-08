//set flag1 flash 400 2700 400 255 

function checkExecutableSkill_area(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_AREA);
	if (isUseSkill) {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_AREA, STATE_PRIORITY_USER, true);
		return true;
	}
}


function checkCommandEnable_area(obj)
{
	return true;
}

function onSetState_GodWind(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	obj.sq_StopMove();
    
    obj.sq_SetCurrentAnimation(CUSTOM_ANI_GOD_WIND_MAIN_BODY);
    createFrontAreaWindFinishDashEffect(obj,0,-1,0);
}




function onProc_GodWind(obj)
{

    local pAni = obj.sq_GetCurrentAni();
    local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
  
  
    local currentT = sq_GetCurrentTime(pAni);
    local height = 250;
  
  
    local startFrameIndex = 0;
    local endFrameIndex = 7;
    local dropFrameIndex = 54;

    local currentT = sq_GetCurrentTime(pAni);

    if (frmIndex <= startFrameIndex)
    {
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),0 );

    }else if (frmIndex >= startFrameIndex && frmIndex <= endFrameIndex)
    {

        currentT = currentT - pAni.getDelaySum(0,startFrameIndex);
        local maxT = pAni.getDelaySum(startFrameIndex,endFrameIndex);
        if (currentT < maxT)
        {
        local v = sq_GetAccel(0, height, currentT,maxT, true);
        //local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);

        sq_setCurrentAxisPos(obj, 2, v);


        }
    }else if (frmIndex <= dropFrameIndex){
        sq_setCurrentAxisPos(obj, 2, height);
    }else{
        sq_setCurrentAxisPos(obj, 2, 0);
    }

}










function onKeyFrameFlag_GodWind(obj,flagIndex)
{
    if (flagIndex == 1)
    {
        sq_flashScreen(obj,400,2700,400,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.sq_PlaySound("VORTEX_CAST");	
    }else if (flagIndex == 500)
    {
        sq_flashScreen(obj,0,60,0,255, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
        obj.sq_SetShake(obj, 9, 300);
        summonPassive_AREA(obj);
        createFrontAreaWindButtom(obj,0,1,0);
		obj.sq_PlaySound("VORTEX");	
    }else if (flagIndex == 2)
    {
        obj.sq_SetShake(obj, 4, 2140);
    }else if (flagIndex == 2000)
    {
        sq_flashScreen(obj,0,120,0,178, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
        obj.sq_SetShake(obj, 10, 240);

        local rate = 0;
        local skill_level = sq_GetSkillLevel(obj, SKILL_AREA);
        if (skill_level >= 9)
        {
            rate = 10;
        }

        local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_AREA, STATE_AREA, 1, 
        (100+rate).tofloat() / 100.0 );

        obj.sq_StartWrite();
        obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
        obj.sq_WriteDword(115);	// attackBonusRate
        sq_SendCreatePassiveObjectPacketPos(obj,24357,0,obj.getXPos(),obj.getYPos(),0);
        setVliadEffectGodWindPassiveObject(obj);
		obj.sq_PlaySound("VORTEX_EXP");	
    }
    return true;
}




function onEndState_GodWind(obj,new_state)
{
    setVliadEffectGodWindPassiveObject(obj);
}


function onEndCurrentAni_GodWind(obj)
{

	obj.sq_AddSetStatePacket(0, STATE_PRIORITY_USER, true);
}

/*
function ()
{

//obj.getVar("effectObj").

}
*/

function setVliadEffectGodWindPassiveObject(obj)
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




function summonPassive_AREA(obj)
{

    local num = obj.sq_GetIntData(SKILL_AREA, 2);
    local rate = 0;
	local skill_level = sq_GetSkillLevel(obj, SKILL_AREA);
    if (skill_level >= 9)
    {
        rate = 10;
    }
    /*
    for(local i=0;i<num;++i)
    {
        local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_AREA, STATE_AREA, 
        0, (100+rate).tofloat() / 100.0 );

        obj.sq_StartWrite();
        obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
        obj.sq_WriteDword(26);	// attackBonusRate
        obj.sq_WriteDword(0);	// attackBonusRate
        obj.sq_WriteDword(obj.getXPos());
        obj.sq_WriteDword(obj.getYPos());
        obj.sq_WriteDword(i*(360/num));//angle
        obj.sq_WriteDword(obj.sq_GetIntData(SKILL_AREA, 3));
        obj.sq_WriteDword(obj.sq_GetIntData(SKILL_AREA, 4));//len
        obj.sq_WriteDword(obj.sq_GetIntData(SKILL_AREA, 5));//atkT
        obj.sq_WriteDword(obj.sq_GetIntData(SKILL_AREA, 1));
        sq_SendCreatePassiveObjectPacketPos(obj,24357,0,0,0,0);

    }
    */
    local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_AREA, STATE_AREA, 
    0, (100+rate).tofloat() / 100.0 );


    local posX1 = obj.getXPos() - 400;
    local posY1 = obj.getYPos();

    local posX2 = obj.getXPos();
    local posY2 = obj.getYPos() - 152;

    local posX3 = obj.getXPos() + 400;
    local posY3 = obj.getYPos();

    local posX4 = obj.getXPos();
    local posY4 = obj.getYPos() + 202;

    obj.sq_StartWrite();
    obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
    obj.sq_WriteDword(193);	
    obj.sq_WriteDword(posX1);
    obj.sq_WriteDword(posY1);
    obj.sq_WriteDword(posX2);
    obj.sq_WriteDword(posY2);
    obj.sq_WriteDword(posX3);
    obj.sq_WriteDword(posY3);
    obj.sq_WriteDword(posX4);
    obj.sq_WriteDword(posY4);
    sq_SendCreatePassiveObjectPacketPos(obj,24357,0,0,0,0);


    obj.sq_StartWrite();
    obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
    obj.sq_WriteDword(193);	
    obj.sq_WriteDword(posX2);
    obj.sq_WriteDword(posY2);
    obj.sq_WriteDword(posX3);
    obj.sq_WriteDword(posY3);
    obj.sq_WriteDword(posX4);
    obj.sq_WriteDword(posY4);
    obj.sq_WriteDword(posX1);
    obj.sq_WriteDword(posY1);
    sq_SendCreatePassiveObjectPacketPos(obj,24357,0,0,0,0);


    obj.sq_StartWrite();
    obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
    obj.sq_WriteDword(193);	
    obj.sq_WriteDword(posX3);
    obj.sq_WriteDword(posY3);
    obj.sq_WriteDword(posX4);
    obj.sq_WriteDword(posY4);
    obj.sq_WriteDword(posX1);
    obj.sq_WriteDword(posY1);
    obj.sq_WriteDword(posX2);
    obj.sq_WriteDword(posY2);
    sq_SendCreatePassiveObjectPacketPos(obj,24357,0,0,0,0);


    obj.sq_StartWrite();
    obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
    obj.sq_WriteDword(193);	
    obj.sq_WriteDword(posX4);
    obj.sq_WriteDword(posY4);
    obj.sq_WriteDword(posX1);
    obj.sq_WriteDword(posY1);
    obj.sq_WriteDword(posX2);
    obj.sq_WriteDword(posY2);
    obj.sq_WriteDword(posX3);
    obj.sq_WriteDword(posY3);
    sq_SendCreatePassiveObjectPacketPos(obj,24357,0,0,0,0);

//    createFrontAreaWindButtom(obj,0,-1,0);
}



function onProcMoveGodWindTorndo(obj)
{
  local currentAni = sq_GetCurrentAnimation(obj);
  local currentT = sq_GetCurrentTime(currentAni);
  if (currentT > 4000)
    sq_SendDestroyPacketPassiveObject(obj);
  
  if ( obj.getVar("ResetHitTime").size_vector() <= 0  )
  {
      obj.getVar("ResetHitTime").clear_vector();
      obj.getVar("ResetHitTime").push_vector(0);
  }else{
      local encodeT = obj.getVar("ResetHitTime").get_vector(0);
      if (currentT - encodeT > 400)
      {
          obj.resetHitObjectList();
          obj.getVar("ResetHitTime").set_vector(0,currentT);
      }
  
  }
  
  
  if ( obj.getVar("movecircleVar").size_vector() <= 0 )
  {
    obj.getVar("movecircleVar").clear_vector();
    obj.getVar("movecircleVar").push_vector(1);//state
    obj.getVar("movecircleVar").push_vector(350);//spinTime
    obj.getVar("movecircleVar").push_vector(currentT);//encodeTime
    obj.getVar("movecircleVar").push_vector(0);
    
  }else{

      
    local mage = obj.getTopCharacter();
    mage = sq_ObjectToSQRCharacter(mage);	
    local mageState = mage.sq_GetState();
    
    if (!mage)
    {
         createFrontAreaWindFinish(obj,size); 
         sq_SendDestroyPacketPassiveObject(obj);	
    }else{
        
        local posY = obj.getYPos() - mage.getYPos();
        local size = 1.0 + posY.tofloat() / 500.0;
        currentAni.setImageRateFromOriginal(size, size);
        
        local pAni = sq_GetCurrentAnimation(mage);
        local chrFrame = mage.sq_GetCurrentFrameIndex(pAni);
        
        if (mageState != STATE_AREA || chrFrame >= 53)
        {
            createFrontAreaWindFinish(obj,1); 
            sq_SendDestroyPacketPassiveObject(obj);	
        }
    
    }
    if (currentT < 200)
    {
        obj.setCurrentPos(obj.getVar("movePos").get_vector(0),
        obj.getVar("movePos").get_vector(1),0);
        return false;
    }
    else 
      currentT -= 200;
    
    local speed = 150;//sq_GetUniformVelocity(startX, lastX, stateT , spinT);
    if (currentT < 1000)
      speed = sq_GetUniformVelocity(350, 150, currentT , 1000);
    
    if (obj.getVar("movecircleVar").get_vector(0) == 1)
    {
      local stateT = currentT - obj.getVar("movecircleVar").get_vector(2);
      local spinT = obj.getVar("movecircleVar").get_vector(1);
      if (stateT < spinT)
      {
        local startX = obj.getVar("movePos").get_vector(0);
        local startY = obj.getVar("movePos").get_vector(1);
        local lastX = obj.getVar("movePos").get_vector(2);
        local lastY = obj.getVar("movePos").get_vector(3); 
        
        local vx = sq_GetUniformVelocity(startX, lastX, stateT , spinT);
        local vy = sq_GetUniformVelocity(startY, lastY, stateT , spinT);
        obj.setCurrentPos(vx,vy,0);
      }else{
        obj.getVar("movecircleVar").clear_vector();
        obj.getVar("movecircleVar").push_vector(2);//state
        obj.getVar("movecircleVar").push_vector( speed );//spinTime
        obj.getVar("movecircleVar").push_vector(currentT);//encodeTime
        obj.getVar("movecircleVar").push_vector(0);
      
      }
    
    }else if (obj.getVar("movecircleVar").get_vector(0) == 2)
    {
      local stateT = currentT - obj.getVar("movecircleVar").get_vector(2);
      local spinT = obj.getVar("movecircleVar").get_vector(1);
      if (stateT < spinT)
      {
        local startX = obj.getVar("movePos").get_vector(2);
        local startY = obj.getVar("movePos").get_vector(3);
        local lastX = obj.getVar("movePos").get_vector(4);
        local lastY = obj.getVar("movePos").get_vector(5); 
        
        local vx = sq_GetUniformVelocity(startX, lastX, stateT , spinT);
        local vy = sq_GetUniformVelocity(startY, lastY, stateT , spinT);
        obj.setCurrentPos(vx,vy,0);
      }else{
        obj.getVar("movecircleVar").clear_vector();
        obj.getVar("movecircleVar").push_vector(3);//state
        obj.getVar("movecircleVar").push_vector( speed );//spinTime
        obj.getVar("movecircleVar").push_vector(currentT);//encodeTime
        obj.getVar("movecircleVar").push_vector(0);
      
      }
    
    }else if (obj.getVar("movecircleVar").get_vector(0) == 3)
    {
      local stateT = currentT - obj.getVar("movecircleVar").get_vector(2);
      local spinT = obj.getVar("movecircleVar").get_vector(1);
      if (stateT < spinT)
      {
        local startX = obj.getVar("movePos").get_vector(4);
        local startY = obj.getVar("movePos").get_vector(5);
        local lastX = obj.getVar("movePos").get_vector(6);
        local lastY = obj.getVar("movePos").get_vector(7); 
        
        local vx = sq_GetUniformVelocity(startX, lastX, stateT , spinT);
        local vy = sq_GetUniformVelocity(startY, lastY, stateT , spinT);
        obj.setCurrentPos(vx,vy,0);
      }else{
        obj.getVar("movecircleVar").clear_vector();
        obj.getVar("movecircleVar").push_vector(4);//state
        obj.getVar("movecircleVar").push_vector( speed );//spinTime
        obj.getVar("movecircleVar").push_vector(currentT);//encodeTime
        obj.getVar("movecircleVar").push_vector(0);
      
      }
    
    }else if (obj.getVar("movecircleVar").get_vector(0) == 4)
    {
      local stateT = currentT - obj.getVar("movecircleVar").get_vector(2);
      local spinT = obj.getVar("movecircleVar").get_vector(1);
      if (stateT < spinT)
      {
        local startX = obj.getVar("movePos").get_vector(6);
        local startY = obj.getVar("movePos").get_vector(7);
        local lastX = obj.getVar("movePos").get_vector(0);
        local lastY = obj.getVar("movePos").get_vector(1); 
        
        local vx = sq_GetUniformVelocity(startX, lastX, stateT , spinT);
        local vy = sq_GetUniformVelocity(startY, lastY, stateT , spinT);
        obj.setCurrentPos(vx,vy,0);
      }else{
        obj.getVar("movecircleVar").clear_vector();
        obj.getVar("movecircleVar").push_vector(1);//state
        obj.getVar("movecircleVar").push_vector( speed );//spinTime
        obj.getVar("movecircleVar").push_vector(currentT);//encodeTime
        obj.getVar("movecircleVar").push_vector(0);
      
      }
    
    }
  
  
  
  }

}





/////////////////////////////////////////////////////////////////////////



function onSetState_AREA(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
    local hei = obj.sq_GetIntData(SKILL_AREA, 0);
    if (state == 0)
    {
		obj.sq_ZStop();
        sq_flashScreen(obj,400,700 + obj.sq_GetIntData(SKILL_AREA, 1),400,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWAREA_READY);
		local skill_level = -1;//sq_GetSkillLevel(obj, SKILL_AREA);



        if (skill_level >= 3)
        {


            if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atmage/area/ap_area.nut"))
            {

                CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/atmage/area/ap_area.nut");
            }

            local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_AREA, true,
             "character/atmage/area/ap_area.nut", false);

            local change_time = 30000;//sq_GetLevelData(obj, SKILL_BLOODANDSHAOW, 2, sq_GetSkillLevel(obj, SKILL_BLOODANDSHAOW) );
            appendage.sq_SetValidTime(change_time);


            appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_AREA, skill_level);
            
            CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_AREA, true);

			local change_appendage = appendage.sq_getChangeStatus("areaBuff");
            local addValue = 5;
			if(!change_appendage)
            {
				change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, 
				CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, 
				false, addValue, APID_COMMON);

			}
            if (change_appendage)
            {

				change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, false, addValue.tofloat());
            }
        }

    }else if (state == 1){
		obj.sq_ZStop();
        summonPassive_AREA(obj);
        createFrontAreaWindButtom(obj,0,-1,0);
        sq_flashScreen(obj,0,60,0,204, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
        obj.sq_SetShake(obj, 10, 300);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWAREA_STARTSUMMON);

        obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("atanimation/als_ani/atgodwind/atgodwind_start_aura_dodge.ani"), 0, 0);

        
    }else if (state == 2){
		obj.sq_ZStop();
        obj.sq_SetShake(obj, 4, 140 + obj.sq_GetIntData(SKILL_AREA, 1));
        obj.setTimeEvent(0,obj.sq_GetIntData(SKILL_AREA, 1),1,false);		
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWAREA_LOOP);

        obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("atanimation/als_ani/atgodwind/atgodwind_start_aura_dodge.ani"), 0, 0);

    }else if (state == 3){
		obj.sq_ZStop();
        local rate = 0;
        local skill_level = sq_GetSkillLevel(obj, SKILL_AREA);
        if (skill_level >= 9)
        {
            rate = 10;
        }

        local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_AREA, STATE_AREA, 1, (100+rate).tofloat() / 100.0 );

        obj.sq_StartWrite();
        obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
        obj.sq_WriteDword(115);	// attackBonusRate
        sq_SendCreatePassiveObjectPacketPos(obj,24357,0,obj.getXPos(),obj.getYPos(),0);

        sq_flashScreen(obj,0,120,0,178, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
        obj.sq_SetShake(obj, 15, 240);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWAREA_BOOM);

        obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("atanimation/als_ani/atgodwind/atgodwind_start_casting2.ani"), 0, 0);

    }else if (state == 4){

        createFrontAreaWind(obj,0,1,0);
        createFrontAreaWindFinishCircle(obj,0,-1,0);
        createFrontAreaWindFinishDodge(obj,0,-1,0);
        createFrontAreaWindFinishDashEffect(obj,0,1,0);
        createFrontAreaWindFinishBodyEffect(obj,0,1,0);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWAREA_DROP);
    }else if (state == 5){

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWAREA_DOWN);
    }
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
		SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}
function onTimeEvent_AREA(obj, timeEventIndex, timeEventCount)
{
    if (timeEventIndex == 0)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(3);
        obj.sq_AddSetStatePacket(STATE_AREA, STATE_PRIORITY_USER, true);
    }


}

function createFrontAreaWind(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atgodwind/atgodwind_finish_wind5.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createFrontAreaWindFinishCircle(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atgodwind/atgodwind_start_finish_circle.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createFrontAreaWindFinishBodyEffect(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atgodwind/atgodwind_start_body2.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFrontAreaWindFinishDashEffect(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atgodwind/atgodwind_start_dash_eff.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createFrontAreaWindFinishDodge(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atgodwind/atgodwind_start_finish_dodge.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFrontAreaWindFinish(obj,size)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atgodwind/atgodwind_finish_tornado2.ani");
    local sizeRate = size.tofloat();
    ani.setImageRateFromOriginal(sizeRate, sizeRate);
    ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFrontAreaWindButtom(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atgodwind/atgodwind_bottom_bg_eff1.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").clear_obj_vector();
    obj.getVar("effectObj").push_obj_vector(pooledObj);
}


function onEndState_AREA(obj, new_state)
{
    if (new_state != STATE_AREA)
    {
            setVliadEffectAreaPassiveObject(obj);
    }else{

        local state = obj.getVar("state").get_vector(0);
        if (state == 4)
            setVliadEffectAreaPassiveObject(obj);
    }
}


function setVliadEffectAreaPassiveObject(obj)
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


function onProc_AREA(obj)
{

    local state = obj.getVar("state").get_vector(0);
    local hei = obj.sq_GetIntData(SKILL_AREA, 0);
	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);

    if (state == 0)
    {
        if (frmIndex == 1)
        {

        }

    }else if (state == 1)
    {

    }else if (state == 2)
    {

        local currentT = sq_GetCurrentTime(pAni);
        if (currentT < 2000)
        {
            local v = sq_GetAccel(0, hei, currentT, 2000, true);
            sq_setCurrentAxisPos(obj, 2, v);
        }else{
            sq_setCurrentAxisPos(obj, 2, hei);
        }
    }else if (state == 3)
    {

            sq_setCurrentAxisPos(obj, 2, hei);
    }else if (state == 4){

		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_IntVectPush(0);
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_USER, true);

        return true;


        local pAni = obj.sq_GetCurrentAni();
        local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
        local currentT = sq_GetCurrentTime(pAni);
        if (currentT < 100)
        {
            local v = sq_GetAccel(hei, 0, currentT, 100, true);
            sq_setCurrentAxisPos(obj, 2, v);
        }else{

            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(5);
            obj.sq_AddSetStatePacket(STATE_AREA, STATE_PRIORITY_USER, true);

        }

    }

}



function onEndCurrentAni_AREA(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            obj.sq_AddSetStatePacket(STATE_AREA, STATE_PRIORITY_USER, true);
    }else if (state == 1)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
        obj.sq_AddSetStatePacket(STATE_AREA, STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {

    }else if (state == 3)
    {

		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_IntVectPush(0);
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_USER, true);

//        obj.getVar("state").clear_vector();
//        obj.getVar("state").push_vector(4);
//        obj.sq_AddSetStatePacket(STATE_AREA, STATE_PRIORITY_USER, true);
    }else if (state == 4)
    {

    }else if (state == 5)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }

}
