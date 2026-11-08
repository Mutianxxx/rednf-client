function checkExecutableSkill_throwattack(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_THROWATTACK);

	if (isUse) {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_THROWATTACK , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}

function checkCommandEnable_throwattack(obj)
{

	return true;
}
//SKILL
function createPassive_ThrowAttackSkill(obj,id,x,y,z)
{
	local ani = NULL;
    local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
    local pooledObj = NULL;
    if (id == 0){
        ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atspiralpress/03_finishhit/02_back/atspiralpress_finish_back_00.ani");

        pooledObj = sq_CreatePooledObject(ani,true);
        pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
    }else if (id == 1){
        ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atspiralpress/03_finishhit/01_front/atspiralpress_finish_front_00.ani");
        pooledObj = sq_CreatePooledObject(ani,true);

    }else if (id == 2){
        ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atspiralpress/04_shoot_dash_body/moveline.ani");
        pooledObj = sq_CreatePooledObject(ani,true);
    }



	pooledObj.setCurrentPos(posX,obj.getYPos()+y,obj.getZPos()+z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,id,false);	
}


function onSetState_THROWATTACKSKILL(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_THROWATTACK_READY0);
        obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
    }else if (state == 1){

        createPassive_ThrowAttackSkill(obj,2,44,1,66);
        obj.sq_SetShake(obj, 5, 120);
        local distance = obj.sq_GetIntData(SKILL_THROWATTACK, 0);
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_THROWATTACK, STATE_THROWATTACK, 0, 1.0);
		obj.sq_StartWrite();
		obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
		obj.sq_WriteDword(24);	// attackBonusRate
		obj.sq_WriteDword(distance);	// attackBonusRate
        obj.sq_SendCreatePassiveObjectPacket(24357, 0, 44, 0, 66);

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_THROWATTACK_READY1);
        obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
    }else if (state == 2){

        obj.getVar("dama").clear_obj_vector();


        local tarX = obj.getVar("state").get_vector(1);
        local tarY = obj.getVar("state").get_vector(2);
        local tarH =66*2;// obj.getVar("state").get_vector(3);

        tarX = sq_GetDistancePos(tarX, obj.getDirection(), -75);

//		local speed = obj.sq_GetIntData(SKILL_THROWATTACK,7);
//		obj.sq_SetStaticMoveInfo(0, speed, speed, false);	
//		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);	


        local savTime = obj.sq_GetIntData(SKILL_THROWATTACK,2);
        local atkTime = obj.sq_GetIntData(SKILL_THROWATTACK,1);


        obj.setTimeEvent(0,savTime,0,false);		
        obj.setTimeEvent(1,atkTime,0,true);		
        obj.sq_SetShake(obj, 3, savTime);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_THROWATTACK_MOVE);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_THROWATTACK_SUCCESS);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_THROWATTACK, STATE_THROWATTACK, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

        obj.sq_SetfindNearLinearMovablePos(tarX ,tarY,obj.getXPos() , obj.getYPos(), 10);
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getVar("h").get_vector(0)/2);

        obj.getVar("h").clear_vector();
        if (tarH < obj.sq_GetIntData(SKILL_THROWATTACK, 5))
        {
            obj.getVar("h").push_vector(obj.sq_GetIntData(SKILL_THROWATTACK, 5) );
        }else{

            obj.getVar("h").push_vector(tarH);
        }

        local dist = obj.sq_GetIntData(SKILL_THROWATTACK,7);

        obj.getVar("len").clear_vector();
        obj.getVar("len").push_vector( obj.getXPos() );
        obj.getVar("len").push_vector( dist );
        obj.getVar("len").push_vector( savTime );
        obj.getVar("len").push_vector( obj.getZPos()  );


    }else if (state == 3){
        createPassive_ThrowAttackSkill(obj,0,0,1,0);
        createPassive_ThrowAttackSkill(obj,1,0,2,0);
        obj.sq_SetShake(obj, 5, 120);
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getVar("h").get_vector(0)/2);
        sq_SetZVelocity(obj,obj.sq_GetIntData(SKILL_THROWATTACK, 3),obj.sq_GetIntData(SKILL_THROWATTACK, 4));

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_THROWATTACK_BACKJUMP);

        obj.sq_SetCurrentAttackInfo(ATTACKINFO_THROWATTACK_SUCCESS);
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getVar("h").get_vector(0)/2);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_THROWATTACK, STATE_THROWATTACK, 2, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				


		local speed = obj.sq_GetIntData(SKILL_THROWATTACK, 6);
		obj.sq_SetStaticMoveInfo(0, speed, speed, false);	
		obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);	

        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();
        for(local i=0;i<objectsSize;++i)
        {
            local damager = var.get_obj_vector(i);
            sq_SendHitObjectPacket(obj,damager,0,0,0);

        }


    }else if(state == 4){
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),0);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_THROWATTACK_LANDING);
    }

}

function onAttack_THROWATTACKSKILL(obj, damager, boundingBox, isStuck)
{

    local state = obj.getVar("state").get_vector(0);
    if(state == 2)
    {
        if ( damager.isObjectType(OBJECTTYPE_ACTIVE))
        {
            obj.getVar("dama").push_obj_vector(damager);

            if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/throwattack/ap_throwattack.nut"))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_THROWATTACK, false, "character/atmage/throwattack/ap_throwattack.nut", true);				 
                sq_HoldAndDelayDie(damager, obj, true, true, true, 0, 0, ENUM_DIRECTION_DOWN , masterAppendage);
            }
        }

    }else if (state == 3)
    {
        if(damager)
        {
            CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/throwattack/ap_throwattack.nut");		
        }
    }
}

function onTimeEvent_THROWATTACKSKILL(obj, timeEventIndex, timeEventCount)
{

    local state = obj.getVar("state").get_vector(0);
    if (state == 2)
    {
        if (timeEventIndex == 0)
        {

            obj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getVar("h").get_vector(0)/2);

            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(3);
            obj.sq_AddSetStatePacket(STATE_THROWATTACK , STATE_PRIORITY_USER, false);
        }else if (timeEventIndex == 1){
            obj.resetHitObjectList();
            obj.sq_SetShake(obj, 3, 100);
        }
    }
}
function onProc_THROWATTACKSKILL(obj)
{
    local state = obj.getVar("state").get_vector(0);
	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);

    if (state == 2)
    {   
        if (frmIndex == 0)
        {
            obj.sq_SetShake(obj, 5, 120);
        }



        local startX = obj.getVar("len").get_vector(0);
        local maxD = obj.getVar("len").get_vector(1);
        local maxT = obj.getVar("len").get_vector(2);
        local startZ = obj.getVar("len").get_vector(3);

        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);

        if ( currentT < maxT )
        {
            local v1 = sq_GetAccel(0, maxD, currentT, maxT,true);
            local posX = sq_GetDistancePos(startX, obj.getDirection(), v1);

            if(obj.isMovablePos(posX, obj.getYPos()))
                obj.setCurrentPos(posX,obj.getYPos(),obj.getVar("h").get_vector(0)/2 );
        }else{

        }

        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();

        if (objectsSize > 0)
        {

            for(local i=0;i<objectsSize;++i)
            {
                local damager = var.get_obj_vector(i);
                local dstX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 50 );
                damager.setCurrentPos(dstX,damager.getYPos(),0);
            }

        }


    }else if (state == 3)
    {
        if (obj.getZPos()<= 0)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(4);
            obj.sq_AddSetStatePacket(STATE_THROWATTACK , STATE_PRIORITY_USER, false);
        }
    }
}
function onEndCurrentAni_THROWATTACKSKILL(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_THROWATTACK , STATE_PRIORITY_USER, false);
    }else if (state == 1){

		obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }else if (state == 4){

		obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }
}