VIOLENTSTROM_START_TIME <- 300
VIOLENTSTROM_LOOP_TIME <- 120

function checkExecutableSkill_jumpattackwin(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_JUMPATTACKWIN);
	if (isUseSkill) {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_JUMPATTACKWIN, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}




function checkCommandEnable_jumpattackwin(obj)
{
    return true;
}

function createFrontJumpAttackWinStart(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atviolentstorm/stormstartback_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFrontJumpAttackWinStart2(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atviolentstorm/stormstart_06.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createViolentStromCircleStart(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atviolentstorm/circlestart_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createViolentStromCircleEnd(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atviolentstorm/circleend_02.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createViolentStromLoopStrom(obj)
{
        local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atviolentstorm/stormloop_01.ani");
        local pooledObj = sq_CreatePooledObject(ani,true);
        pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos());
        pooledObj.setCurrentDirection(obj.getDirection());
        sq_AddObject(obj,pooledObj,2,false);	
        obj.getVar("stromObj").push_obj_vector( pooledObj );
}


function createViolentStromLoopBackStrom(obj)
{
        local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atviolentstorm/stormloopback_00.ani");
        local pooledObj = sq_CreatePooledObject(ani,true);
        pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos());
        pooledObj.setCurrentDirection(obj.getDirection());
        sq_AddObject(obj,pooledObj,2,false);	
        obj.getVar("stromObj").push_obj_vector( pooledObj );
}


function createViolentStromEndBackStrom(obj)
{
        local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atviolentstorm/stormendback_02.ani");
        local pooledObj = sq_CreatePooledObject(ani,true);
        pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() - 1,obj.getZPos());
        pooledObj.setCurrentDirection(obj.getDirection());
        sq_AddObject(obj,pooledObj,2,false);	
}


function createViolentStromEndDustStrom(obj)
{
        local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atviolentstorm/stormenddust_00.ani");
        local pooledObj = sq_CreatePooledObject(ani,true);
        pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos());
        pooledObj.setCurrentDirection(obj.getDirection());
        sq_AddObject(obj,pooledObj,2,false);	
}


function createViolentStromEndFrontStrom(obj)
{
        local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atviolentstorm/stormendfront_04.ani");
        local pooledObj = sq_CreatePooledObject(ani,true);
        pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
        pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 2,obj.getZPos());
        pooledObj.setCurrentDirection(obj.getDirection());
        sq_AddObject(obj,pooledObj,2,false);	
}


function createViolentStromEndBottomStrom(obj)
{
        local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atviolentstorm/stormendbottom_00.ani");
        local pooledObj = sq_CreatePooledObject(ani,true);
        pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
        pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() - 1,obj.getZPos());
        pooledObj.setCurrentDirection(obj.getDirection());
        sq_AddObject(obj,pooledObj,2,false);	
}


function onEndState_JUMPATTACKWIN(obj, new_state)
{

    if (new_state != STATE_JUMPATTACKWIN)
    {

		obj.sq_RemoveAimPointMark();

        local circleObj = obj.getVar("circleLoopObj").get_obj_vector(0);
        if( circleObj )     
        {
            circleObj.setValid(false);
        }

        local stromObj1 = obj.getVar("stromObj").get_obj_vector(0);
        local stromObj2 = obj.getVar("stromObj").get_obj_vector(1);

        if( stromObj1 )     
        {
            stromObj1.setValid(false);
        }

        if( stromObj2 )     
        {
            stromObj2.setValid(false);
        }

    }else{



    }


//    setVliadEffectBloodStreamEsaspistPassiveObject(obj);)
}

function onSetState_JUMPATTACKWIN(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	obj.sq_StopMove();
	
	local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {
        obj.sq_PlaySound("MW_VIOLENTSTORM_01_2");
        obj.sq_PlaySound("VIOLENTSTORM_CAST");
		obj.sq_SetCurrentAnimation(-1);
        createFrontJumpAttackWinStart(obj,0,-1,0);
        createFrontJumpAttackWinStart2(obj,0,1,0);
        obj.getVar().clear_vector();
        obj.getVar().push_vector(0);
        obj.getVar().push_vector(0);
        obj.getVar().push_vector(0);
        obj.getVar().push_vector(0);
        obj.getVar().push_vector(0);
        obj.getVar().push_vector(0);
        obj.getVar().push_vector(0);
        obj.getVar().push_vector(0);
        obj.getVar().push_vector(0);
    }else if (state == 1)
    {
        sq_SetMyShake(obj,4,100);
        createViolentStromCircleStart(obj,0,1,0);
    }else if (state == 2)
    {

        obj.sq_AddAimPointMark(obj.getXPos(), obj.getYPos(), 
        obj.sq_GetIntData(SKILL_JUMPATTACKWIN,0), obj.sq_GetIntData(SKILL_JUMPATTACKWIN,1) );


        obj.getVar("circleLoopObj").clear_obj_vector();

        local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atviolentstorm/circleloop_00.ani");
        local pooledObj = sq_CreatePooledObject(ani,true);
        sq_AddObject(obj,pooledObj,2,false);	
        obj.getVar("circleLoopObj").push_obj_vector( pooledObj );

    }else if (state == 3)
    {


        obj.sq_PlaySound("MW_VIOLENTSTORM_02_2");
        obj.sq_PlaySound("VIOLENTSTORM");

        local posX = obj.getXPos();
        local posY = obj.getYPos();
        local aimPosX = obj.sq_GetAimPosX(posX, posY, false);
        local aimPosY = obj.sq_GetAimPosY(posX, posY, false);
        obj.setCurrentPos(aimPosX,aimPosY,0);

		obj.sq_RemoveAimPointMark();
        obj.setTimeEvent(0,obj.sq_GetIntData(SKILL_JUMPATTACKWIN,2),0,true);


        obj.getVar("stromObj").clear_obj_vector();
        createViolentStromLoopStrom(obj);
        createViolentStromLoopBackStrom(obj);
        sq_SetMyShake(obj,5,obj.sq_GetIntData(SKILL_JUMPATTACKWIN,2) * obj.sq_GetIntData(SKILL_JUMPATTACKWIN,3) );

    }else if (state == 4)
    {


    }
}

function onTimeEvent_JUMPATTACKWIN(obj, timeEventIndex, timeEventCount)
{
                if(!obj.isMyControlObject()) {
                    return;
                }
    local state = obj.getVar("state").get_vector(0);
    if (state == 3)
    {
        if (timeEventIndex == 0 )
        {
            if (timeEventCount <= obj.sq_GetIntData(SKILL_JUMPATTACKWIN,3) )
            {
                local power = obj.sq_GetBonusRateWithPassive(SKILL_JUMPATTACKWIN , STATE_JUMPATTACKWIN, 0, 1.0);
                sq_createAttackObjectWithPath(obj, "character/mage/atanimation/zrr/jumpattackwin/atk.ani",
                "character/mage/atattackinfo/zrr/jumpattackwin.atk",true,power,100,0,0,0);		

            }else{



                local circleObj = obj.getVar("circleLoopObj").get_obj_vector(0);
                if( circleObj )     
                {
                    circleObj.setValid(false);
                }

                local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_JUMPATTACKWIN , STATE_JUMPATTACKWIN, 1, 1.0);
                obj.sq_StartWrite();
                obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
                obj.sq_WriteDword(117);	// attackBonusRate
                obj.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);

                local stromObj1 = obj.getVar("stromObj").get_obj_vector(0);
                local stromObj2 = obj.getVar("stromObj").get_obj_vector(1);

                if( stromObj1 )     
                {
                    stromObj1.setValid(false);
                }

                if( stromObj2 )     
                {
                    stromObj2.setValid(false);
                }

                createViolentStromCircleEnd(obj,0,1,0);
                createViolentStromEndBackStrom(obj);
                createViolentStromEndDustStrom(obj);
                createViolentStromEndFrontStrom(obj);
                createViolentStromEndBottomStrom(obj);

                sq_flashScreen(obj,0,80,0,255, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
                sq_SetMyShake(obj,7,300);

                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(4);
                obj.sq_AddSetStatePacket(STATE_JUMPATTACKWIN, STATE_PRIORITY_USER, true);
            }
        }
    }
}

function onEndCurrentAni_JUMPATTACKWIN(obj)
{
	if (!obj) return;
	local state = obj.getVar("state").get_vector(0);

}


function onProc_JUMPATTACKWIN(obj)
{
	local state = obj.getVar("state").get_vector(0);
	local stateTimer = obj.sq_GetStateTimer();
    if (state == 0)
    {
        if (stateTimer > VIOLENTSTROM_START_TIME && obj.getVar().get_vector(0) == 0)//create start circle
        {
                if(!obj.isMyControlObject()) {
                    return;
                }
            obj.getVar().set_vector(0,1);
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            obj.sq_AddSetStatePacket(STATE_JUMPATTACKWIN, STATE_PRIORITY_USER, true);

        }
    }else if (state == 1)
    {

        if (stateTimer > VIOLENTSTROM_LOOP_TIME && obj.getVar().get_vector(1) == 0 ) // create loop circle
        {
                if(!obj.isMyControlObject()) {
                    return;
                }
            obj.getVar().set_vector(1,1);
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(2);
            obj.sq_AddSetStatePacket(STATE_JUMPATTACKWIN, STATE_PRIORITY_USER, true);
        }



    }else if (state == 2)
    {

        local posX = obj.getXPos();
        local posY = obj.getYPos();
        local aimPosX = obj.sq_GetAimPosX(posX, posY, false);
        local aimPosY = obj.sq_GetAimPosY(posX, posY, false);

        local circleObj = obj.getVar("circleLoopObj").get_obj_vector(0);
        if( circleObj )     
            circleObj.setCurrentPos( aimPosX,aimPosY + 1,0 );

        if (stateTimer > obj.sq_GetIntData(SKILL_JUMPATTACKWIN,4) ) // create loop hit
        {
                if(!obj.isMyControlObject()) {
                    return;
                }
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(3);
            obj.sq_AddSetStatePacket(STATE_JUMPATTACKWIN, STATE_PRIORITY_USER, true);

        }

        local posX = obj.getXPos();
        local posY = obj.getYPos();
        local posZ = obj.getZPos();

		local disX = sq_GetDistancePos(obj.getXPos(), sq_GetDirection(obj), 200);

		if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT)
		{
			if (disX > iPX)
			{
				obj.sq_SetAimPointMarkPosition(disX, aimPosY);
			}
		}

		if (sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT)
		{
			if (disX < iPX)
			{
				obj.sq_SetAimPointMarkPosition(disX, aimPosY);
			}
		}



    }else if (state == 3)
    {

    }else if (state == 4)
    {
        if (stateTimer > obj.sq_GetIntData(SKILL_JUMPATTACKWIN,5) ) // on end 
        {
                if(!obj.isMyControlObject()) {
                    return;
                }
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
        }
    }
}


function getScrollBasisPos_JUMPATTACKWIN(obj)
{
	local state = obj.getVar("state").get_vector(0);
	local stateTimer = obj.sq_GetStateTimer();
    if (state == 2)
    {
        local posX = obj.getXPos();
        local posY = obj.getYPos();
        local aimPosX = obj.sq_GetAimPosX(posX, posY, false);
        local aimPosY = obj.sq_GetAimPosY(posX, posY, false);

        obj.sq_SetCameraScrollPosition(aimPosX, aimPosY, 0);
        return true;

    }
    return false;
}