//STATE 0
//FLAG1 DASH

//STATE 1
//ONSET SHAKE 2 30 
//CREATE HIT EFFECT
//a

//STATE 2
//SET FLAG 1 
//SHAKE 2 60
//CREATE HIT EFFECT
//b

//STATE 3
//SET FLAG 1
//DOWN
//c1
//SET FLAG 2
//CREATE HIT EFFECT

//STATE 4
//SET FLAG 1
//CREATE HIT EFFECT
//c2

//STATE 5
//SET FLAG 1
//SHAKE 3 120
//START END CANCEL
//end

function checkExecutableSkill_windblades(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_WINDBLADES);

	if (isUse) {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_WINDBLADES , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}


function createWindBladesHitEffect(obj, damager)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atwindblades/atwindbladesattacka_hiteffect.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos(),damager.getYPos(),damager.getZPos());
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_moveWithParent(obj, pooledObj);
	sq_AddObject(obj,pooledObj,2,false);	

}

function checkCommandEnable_windblades(obj)
{

	return true;
}

function onSetState_WINDBLADES(obj, state, datas, isResetTimer)
{
    local state = obj.getVar("state").get_vector(0);
	obj.sq_StopMove();
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    if (state == 0)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_WINDBLADES_DASH);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_WINDBLADES_DASH);
        obj.getVar("isDash").clear_vector();
        obj.getVar("isDash").push_vector(0);

        obj.getVar("dama").clear_obj_vector();

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_WINDBLADES , STATE_WINDBLADES, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

    }else if (state == 1)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_WINDBLADES_ATTACK_A);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_WINDBLADES_ATTACK_A);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_WINDBLADES , STATE_WINDBLADES, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

        obj.sq_SetShake(obj, 2, 30);
        local targetObj = obj.getVar("dama").get_obj_vector(0);
        createWindBladesHitEffect(obj, targetObj);

    }else if (state == 2)
    {
		obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_WINDBLADES_ATTACK_B);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_WINDBLADES_ATTACK_B);

        local targetObj = obj.getVar("dama").get_obj_vector(0);
		local dstX = sq_GetDistancePos(targetObj.getXPos(), obj.getDirection(), sq_GetIntData(obj, SKILL_WINDBLADES, 0) );	
        obj.sq_SetfindNearLinearMovablePos(dstX ,targetObj.getYPos(),obj.getXPos() , obj.getYPos(), 10);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_WINDBLADES , STATE_WINDBLADES, 2, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				
    }else if (state == 3)
    {


		obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_WINDBLADES_ATTACK_C01);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_WINDBLADES_ATTACK_C01);

		local ani = obj.sq_GetCurrentAni();
		local delay = ani.getDelaySum(false);

        obj.getVar("dropParameter").clear_vector();
        obj.getVar("dropParameter").push_vector(delay);

        local targetObj = obj.getVar("dama").get_obj_vector(0);
		local dstX = sq_GetDistancePos(targetObj.getXPos(), obj.getDirection(), sq_GetIntData(obj, SKILL_WINDBLADES, 1) );	
        obj.sq_SetfindNearLinearMovablePos(dstX ,targetObj.getYPos(),obj.getXPos() , obj.getYPos(), 10);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_WINDBLADES , STATE_WINDBLADES, 3, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				
    }else if (state == 4)
    {
        sq_setCurrentAxisPos(obj, 2, 0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_WINDBLADES_ATTACK_C02);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_WINDBLADES_ATTACK_C02);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_WINDBLADES , STATE_WINDBLADES, 3, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				


    }else if (state == 5)
    {
        sq_setCurrentAxisPos(obj, 2, 0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_WINDBLADES_ATTACK_D);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_WINDBLADES_ATTACK_D);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_WINDBLADES , STATE_WINDBLADES, 4, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

        obj.getVar("isCancel").clear_vector();
        obj.getVar("isCancel").push_vector(0);

    }

	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
		SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

}


function onProc_WINDBLADES(obj)
{
    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {
        if (obj.getVar("isDash").get_vector(0) == 1)
        {
            
//0                obj.getVar("dashParameter").push_vector( obj.getXPos() );
//1                obj.getVar("dashParameter").push_vector( currentT );
//2                obj.getVar("dashParameter").push_vector( abs( obj.getXPos() - targetObj.getXPos() ) );
//3                obj.getVar("dashParameter").push_vector( targetObj.getYPos() - obj.getYPos() );
//4                obj.getVar("dashParameter").push_vector( obj.getYPos() );


            local dashNeedTime =  sq_GetIntData(obj, SKILL_WINDBLADES, 2);

            local pAni = obj.sq_GetCurrentAni();
            local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
            local currentT = sq_GetCurrentTime(pAni);

            local startX = obj.getVar("dashParameter").get_vector(0);
            local startY = obj.getVar("dashParameter").get_vector(4);

            local startT = obj.getVar("dashParameter").get_vector(1);
            local tarObjX = obj.getVar("dashParameter").get_vector(2);
            local tarObjY = obj.getVar("dashParameter").get_vector(3);

            local dashT = currentT - startT;

            local v = sq_GetAccel(0, tarObjX, dashT,dashNeedTime , true);
            local v2 = sq_GetAccel(0, tarObjY, dashT,dashNeedTime , true);
            if (obj.getDirection() == ENUM_DIRECTION_LEFT)
            {
                v = -v;
            }

            local lastX = startX + v;
            local lastY = startY + v2;
            if(obj.isMovablePos(lastX, lastY) )
            { 
                sq_setCurrentAxisPos(obj, 0, lastX);
                sq_setCurrentAxisPos(obj, 1, lastY);
            }

            
        }
    }else if (state == 1)
    {
        //a
        local targetObj = obj.getVar("dama").get_obj_vector(0);

    }else if (state == 2)
    {
        //b

        local lastX = obj.getXPos();
        local lastY = obj.getYPos();
        local lastZ = 0;

        if(obj.isMovablePos(lastX, lastY) )
        { 
            sq_setCurrentAxisPos(obj, 0, lastX);
            sq_setCurrentAxisPos(obj, 1, lastY);
        }
        sq_setCurrentAxisPos(obj, 2, lastZ);
    }else if (state == 3)
    {
        //c01
        //        obj.getVar("dropParameter").push_vector(delay);

        
        local targetObj = obj.getVar("dama").get_obj_vector(0);
		local dstX = obj.getXPos();
        local lastX = dstX;
        local lastY = obj.getYPos();
        local height = targetObj.getObjectHeight();

        local delay = obj.getVar("dropParameter").get_vector(0);
        local pAni = obj.sq_GetCurrentAni();
        local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
        local currentT = sq_GetCurrentTime(pAni);

        local lastZ = height - sq_GetAccel(0, height, currentT,delay , true);;

        if(obj.isMovablePos(lastX, lastY) )
        { 
            sq_setCurrentAxisPos(obj, 0, lastX);
            sq_setCurrentAxisPos(obj, 1, lastY);
        }
        sq_setCurrentAxisPos(obj, 2, lastZ);


    }else if (state == 4)
    {
        //c02

        local targetObj = obj.getVar("dama").get_obj_vector(0);
        local lastX = obj.getXPos();
        local lastY = obj.getYPos();
        local lastZ = 0;

        if(obj.isMovablePos(lastX, lastY) )
        { 
            sq_setCurrentAxisPos(obj, 0, lastX);
            sq_setCurrentAxisPos(obj, 1, lastY);
        }
        sq_setCurrentAxisPos(obj, 2, lastZ);

    }else if (state == 5)
    {

    }




        if (obj.getVar("isCancel").get_vector(0) == 1)
        {

            local skill = sq_GetSkill(obj, 143);
            
            if(skill) {
                skill.setCommandEnable( true ); 
            }

            skill = sq_GetSkill(obj, 132);
            
            if(skill) {
                skill.setCommandEnable( true ); 
            }


           skill = sq_GetSkill(obj, 139);
            
            if(skill) {
                skill.setCommandEnable( true ); 
            }

           skill = sq_GetSkill(obj, 110);
            
            if(skill) {
                skill.setCommandEnable( true ); 
            }

           skill = sq_GetSkill(obj, 102);
            
            if(skill) {
                skill.setCommandEnable( true ); 
            }

           skill = sq_GetSkill(obj, 135);
            
            if(skill) {
                skill.setCommandEnable( true ); 
            }

           skill = sq_GetSkill(obj, 101);
            
            if(skill) {
                skill.setCommandEnable( true ); 
            }

           skill = sq_GetSkill(obj, 136);
            
            if(skill) {
                skill.setCommandEnable( true ); 
            }


           skill = sq_GetSkill(obj, 138);
            
            if(skill) {
                skill.setCommandEnable( true ); 
            }

           skill = sq_GetSkill(obj, 133);
            
            if(skill) {
                skill.setCommandEnable( true ); 
            }

           skill = sq_GetSkill(obj, 134);
            
            if(skill) {
                skill.setCommandEnable( true ); 
            }

        }
}

function onEndCurrentAni_WINDBLADES(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        if ( obj.getVar("dama").get_obj_vector_size() > 0 )
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            obj.sq_AddSetStatePacket(STATE_WINDBLADES , STATE_PRIORITY_USER, false);
        }else{
            obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
        }
    }else if (state == 1)
    {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(2);
            obj.sq_AddSetStatePacket(STATE_WINDBLADES , STATE_PRIORITY_USER, false);
    }else if (state == 2)
    {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(3);
            obj.sq_AddSetStatePacket(STATE_WINDBLADES , STATE_PRIORITY_USER, false);
    }else if (state == 3)
    {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(4);
            obj.sq_AddSetStatePacket(STATE_WINDBLADES , STATE_PRIORITY_USER, false);
    }else if (state == 4)
    {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(5);
            obj.sq_AddSetStatePacket(STATE_WINDBLADES , STATE_PRIORITY_USER, false);
    }else if (state == 5)
    {
            obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true );
    }
}

function onAttack_WINDBLADES(obj, damager, boundingBox, isStuck)
{
    local state = obj.getVar("state").get_vector(0);
}

function onKeyFrameFlag_WINDBLADES(obj, flagIndex)
{
    local state = obj.getVar("state").get_vector(0);

    if (flagIndex == 1 && obj.getVar("flag").get_vector(0) == 0)
    {
        obj.getVar("flag").set_vector(0,1);
        if (state == 0)
        {
//                obj.sq_SendCreatePassiveObjectPacket(24357, 0, 55, 1, 0);

            local tarDistance = sq_GetIntData(obj, SKILL_WINDBLADES, 3);
            local targetObj = findAngleTarget(obj, tarDistance, 180, 100);
            obj.getVar("isDash").clear_vector();
            obj.getVar("isDash").push_vector(1);
            if (targetObj)
            {
                obj.sq_PlaySound("WIND_BLADES_DASH");
                local pAni = obj.sq_GetCurrentAni();
                local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
                local currentT = sq_GetCurrentTime(pAni);

                obj.getVar("dama").push_obj_vector(targetObj);
                
                obj.getVar("dashParameter").clear_vector();
                obj.getVar("dashParameter").push_vector( obj.getXPos() );
                obj.getVar("dashParameter").push_vector( currentT );
                obj.getVar("dashParameter").push_vector( abs( obj.getXPos() - targetObj.getXPos() ) - 50 );
                obj.getVar("dashParameter").push_vector( targetObj.getYPos() - obj.getYPos() );
                obj.getVar("dashParameter").push_vector( obj.getYPos() );

//                obj.sq_SendCreatePassiveObjectPacket(24357, 0, 55, 1, 0);
            }else{


                obj.sq_PlaySound("WIND_BLADES_DASH");
                local pAni = obj.sq_GetCurrentAni();
                local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
                local currentT = sq_GetCurrentTime(pAni);

                
                obj.getVar("dashParameter").clear_vector();
                obj.getVar("dashParameter").push_vector( obj.getXPos() );
                obj.getVar("dashParameter").push_vector( currentT );
                obj.getVar("dashParameter").push_vector(  sq_GetIntData(obj, SKILL_WINDBLADES, 4) );
                obj.getVar("dashParameter").push_vector( 0 );
                obj.getVar("dashParameter").push_vector( obj.getYPos() );

            }

        }else if (state == 1)
        {


        }else if (state == 2)
        {
            obj.sq_SetShake(obj, 2, 60);
            local targetObj = obj.getVar("dama").get_obj_vector(0);
            createWindBladesHitEffect(obj, targetObj);

        }else if (state == 3)
        {
            sq_setCurrentAxisPos(obj, 2, 0);
        }else if (state == 4)
        {
            local targetObj = obj.getVar("dama").get_obj_vector(0);
            createWindBladesHitEffect(obj, targetObj);
            obj.getVar("isCancel").set_vector(0,1);
        }else if (state == 5)
        {
            obj.sq_SetShake(obj, 3, 120);

        }



    }else if (flagIndex == 2 && obj.getVar("flag").get_vector(1) == 0)
    {
        obj.getVar("flag").set_vector(1,1);
        if (state == 0)
        {
            local targetObj = obj.getVar("dama").get_obj_vector(0);
            sq_SendHitObjectPacket(obj,targetObj ,0,0,0);
        }else if (state == 1)
        {
        }else if (state == 2)
        {
        }else if (state == 3)
        {
            local targetObj = obj.getVar("dama").get_obj_vector(0);
            createWindBladesHitEffect(obj, targetObj);
        }else if (state == 4)
        {
        }else if (state == 5)
        {
        }
    }
}




//STATE 4
//SET FLAG 1
//CREATE HIT EFFECT
//c2




