//END SET FLAG 1 
//[OFFSET]
//`explosion`	56	0	3

//FINISH GRAB SET FLAG 1 
//[OFFSET]
//`grab pos`	-39	0	44
//SET FLAG 2 
//[OFFSET]
//`grab pos`	-6	0	59

//JUMP FINISH GRAB SETSTATE SHAKE 1 100
// SET FLAG 1 
//[OFFSET]
//`grab pos`	-39	0	44
//SET FLAG 2 
//[OFFSET]
//`grab pos`	-6	0	59

//TOROLLING  ONSETSTATE SHAKE 1 60

//boom
//flash 0 30 80 102 0 0 0 bottom

//CUSTOM_ANI_GOTOHELL_STANDREADYGRAB_BODY <- 128      //`animation/zrr/gotohell/gotohell_casting_body.ani`
//CUSTOM_ANI_GOTOHELL_STANDREADYJUMP_BODY <- 129      //`animation/zrr/gotohell/gotohell_grabjump_body.ani`
//CUSTOM_ANI_GOTOHELL_STANDJUMP_BODY <- 130           //`animation/zrr/gotohell/gotohell_attack_body.ani`
//CUSTOM_ANI_GOTOHELL_STANDFINISHGRAB_BODY <- 131     //`animation/zrr/gotohell/gotohell_finishgrab_body.ani`
//CUSTOM_ANI_GOTOHELL_STANDFALL_BODY <- 132           //`animation/zrr/gotohell/gotohell_end_body1.ani`
//CUSTOM_ANI_GOTOHELL_JUMPTOROLLING_BODY <- 133       //`animation/zrr/gotohell/gotohell_stand_readytorolling_body.ani`
//CUSTOM_ANI_GOTOHELL_JUMPGRABROLLING_BODY <- 134     //`animation/zrr/gotohell/gotohell_jumpgrabrolling_body.ani`
//CUSTOM_ANI_GOTOHELL_JUMPFINISHGRAB_BODY <- 135      //`animation/zrr/gotohell/gotohell_jumpfinishgrab_body.ani`
//CUSTOM_ANI_GOTOHELL_JUMPGRABFAIL_BODY <- 136        //`animation/zrr/gotohell/gotohell_jumpgrabfail.ani`
//ATTACKINFO_GOTOHELL_TRY <- 52

function onSetState_GOTOHELL(obj, state, datas, isResetTimer)
{	
    local state = obj.getVar("state").get_vector(0);

    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);

    if (state == 0)
    {
        obj.sq_StopMove();
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_GOTOHELL_STANDREADYGRAB_BODY);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_GOTOHELL_TRY);
        obj.getVar("dama").clear_obj_vector();
        obj.getVar("isBack").clear_vector();
        obj.getVar("isBack").push_vector(0);

    }else if (state == 1)
    {
        obj.sq_StopMove();
        obj.getVar("len2").clear_vector();
        obj.getVar("len2").push_vector( obj.getXPos() );
        obj.getVar("len2").push_vector( obj.getYPos() );

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_GOTOHELL_STANDREADYJUMP_BODY);
    }else if (state == 2)
    {
        obj.sq_StopMove();
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_GOTOHELL_STANDJUMP_BODY );
//        sq_SetZVelocity(obj,600,-2000);

		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);
		local upPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL);
		local downPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL);
//obj.sq_GetIntData(SKILL_GOTOHELL,0)
        local lenX = obj.sq_GetIntData(SKILL_GOTOHELL,0);
        local lenY = 0;
        local lenZ = obj.sq_GetIntData(SKILL_GOTOHELL,1);


		if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && leftPress) lenX = obj.sq_GetIntData(SKILL_GOTOHELL,2);
		if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && rightPress) lenX = obj.sq_GetIntData(SKILL_GOTOHELL,3);

		if(upPress) lenY = obj.sq_GetIntData(SKILL_GOTOHELL,4);
		if(downPress) lenY = obj.sq_GetIntData(SKILL_GOTOHELL,5);

        obj.getVar("len").clear_vector();
        obj.getVar("len").push_vector(lenX);
        obj.getVar("len").push_vector(lenY);
        obj.getVar("len").push_vector(lenZ);
        obj.getVar("len").push_vector(obj.getXPos() );
        obj.getVar("len").push_vector(obj.getYPos() );
        obj.getVar("len").push_vector(obj.getZPos() );


		local ani = obj.sq_GetCurrentAni();
		local delay = ani.getDelaySum(false);
        local time = obj.sq_GetIntData(SKILL_GOTOHELL,6);

        obj.getVar("time").clear_vector();
        obj.getVar("time").push_vector(delay);
        obj.getVar("time").push_vector(time);

        obj.getVar("xz").clear_vector();
        obj.getVar("xz").push_vector(0);

    }else if (state == 3)
    {
        obj.sq_StopMove();
        sq_setCurrentAxisPos(obj, 2, 0);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_GOTOHELL_STANDFINISHGRAB_BODY );

        if (obj.getVar("dama").get_obj_vector_size() > 0)
        {
            local damager = obj.getVar("dama").get_obj_vector(0);
            sq_SetCustomRotate(damager, 0.00);	
        }
    }else if (state == 4)
    {
        obj.sq_StopMove();
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_GOTOHELL_STANDFALL_BODY );

       if (obj.getVar("dama").get_obj_vector_size() > 0)
        {
            local damager = obj.getVar("dama").get_obj_vector(0);

            local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),56);
            local posY = obj.getYPos() - 1;
            local posZ = obj.getZPos() + 3;
            damager.setCurrentPos(posX,posY,posZ);

        }


        local isBack = obj.getVar("isBack").get_vector(0);

        local attackRate = 100;
        local size = 100;

        if (isBack == 0)
        {
            attackRate = attackRate + obj.sq_GetIntData(SKILL_GOTOHELL,7);
            size = size + obj.sq_GetIntData(SKILL_GOTOHELL,8);
        }else{
            attackRate = attackRate + obj.sq_GetIntData(SKILL_GOTOHELL,9);
            size = size + obj.sq_GetIntData(SKILL_GOTOHELL,10);
        }

        local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_GOTOHELL, STATE_GOTOHELL, 0, attackRate.tofloat() / 100.0 );
        obj.sq_StartWrite();
        obj.sq_WriteDword(attackBonusRate);
        obj.sq_WriteDword(95);
        obj.sq_WriteDword(size);
        obj.sq_SendCreatePassiveObjectPacket(24357, 0, 56, 1, 3);
        obj.sq_SetShake(obj, 5, 200);
        sq_flashScreen(obj,0,30,80,102, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
    }else if (state == 5)
    {
        obj.sq_StopMove();
        obj.sq_SetShake(obj, 1, 60);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_GOTOHELL_JUMPTOROLLING_BODY );



    }else if (state == 6)
    {
        obj.sq_StopMove();
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_GOTOHELL_JUMPGRABROLLING_BODY );
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_GOTOHELL_TRY);
        obj.getVar("dama").clear_obj_vector();
        obj.getVar("isBack").clear_vector();
        obj.getVar("isBack").push_vector(0);
        sq_SetZVelocity(obj,obj.sq_GetIntData(SKILL_GOTOHELL,11),obj.sq_GetIntData(SKILL_GOTOHELL,12));



//CUSTOM_ANI_GOTOHELL_JUMPGRABROLLING_BODY
    }else if (state == 7)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_GOTOHELL_JUMPGRABFAIL_BODY );
    }
    obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onProc_GOTOHELL(obj)
{
    local state = obj.getVar("state").get_vector(0);



    if (state == 1)
    {
//        obj.getVar("len2").clear_vector();
//        obj.getVar("len2").push_vector( obj.getXPos() );
//        obj.getVar("len2").push_vector( obj.getYPos() );


        if (obj.getVar("dama").get_obj_vector_size() > 0)
        {
            local damager = obj.getVar("dama").get_obj_vector(0);

            local startX = obj.getVar("len2").get_vector(0);
            local startY = obj.getVar("len2").get_vector(1);

            local pAni = obj.sq_GetCurrentAni();
            local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
            local currentT = sq_GetCurrentTime(pAni);
			local delayT = pAni.getDelaySum(false);

            local v1 = sq_GetAccel(obj.getXPos(), damager.getXPos(), currentT, delayT, true);
            local v2 = sq_GetAccel(obj.getYPos(), damager.getYPos(), currentT, delayT, true);
            local v3 = sq_GetAccel(0, damager.getObjectHeight() / 2, currentT, delayT, true);

            obj.setCurrentPos(v1,v2,v3);

        }


    }else if (state == 2)
    {


        local pAni = obj.sq_GetCurrentAni();
        local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
        local currentT = sq_GetCurrentTime(pAni);

        if (obj.getVar("dama").get_obj_vector_size() > 0)
        {
            local damager = obj.getVar("dama").get_obj_vector(0);
            damager.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos() + damager.getObjectHeight() / 2 );

            local xz = obj.getVar("xz").get_vector(0);
            sq_SetCustomRotate(damager, xz.tofloat() / 100.0);	
            
            obj.getVar("xz").set_vector(0,(xz + 60) % 360);
        }

//        obj.getVar("len").clear_vector();
//        obj.getVar("len").push_vector(lenX);0
//        obj.getVar("len").push_vector(lenY);1
//        obj.getVar("len").push_vector(lenZ);2
//        obj.getVar("len").push_vector(obj.getXPos() );3
//        obj.getVar("len").push_vector(obj.getYPos() );4
//        obj.getVar("len").push_vector(obj.getZPos() );5

//        obj.getVar("time").clear_vector();
//        obj.getVar("time").push_vector(delay);
//        obj.getVar("time").push_vector(time);

        local startX = obj.getVar("len").get_vector(3);
        local startY = obj.getVar("len").get_vector(4);
        local startZ = obj.getVar("len").get_vector(5);

        local lenX = obj.getVar("len").get_vector(0);
        local lenY = obj.getVar("len").get_vector(1);
        local lenZ = obj.getVar("len").get_vector(2);

        local delayT = obj.getVar("time").get_vector(0);
        local rolliT = obj.getVar("time").get_vector(1);



        
        if (currentT > rolliT)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(3);
            obj.sq_AddSetStatePacket(STATE_GOTOHELL, STATE_PRIORITY_USER, true);
        }else{
            local v = sq_GetAccel(0, lenX, currentT, rolliT, true);
            local v2 = sq_GetAccel(0, lenY, currentT, rolliT, true);

            local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
            local dstY = startY + v2;

            if(obj.isMovablePos(dstX, obj.getYPos() ) )
            {
                sq_setCurrentAxisPos(obj, 0, dstX);
            }

            if(obj.isMovablePos(obj.getXPos(), dstY ) )
            {
                sq_setCurrentAxisPos(obj, 1, dstY);
            }
    
            sq_setCurrentAxisPos(obj, 2, getQuadraticFunction(obj,v,lenZ,lenX).tointeger() );





        }

    }else if (state == 3)
    {
        if (obj.getVar("dama").get_obj_vector_size() > 0)
        {
            local damager = obj.getVar("dama").get_obj_vector(0);

            local pAni = obj.sq_GetCurrentAni();
            local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
            local currentT = sq_GetCurrentTime(pAni);

            if (frmIndex % 2 == 0)
            {
                local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),-39);
                local posY = obj.getYPos() - 1;
                local posZ = obj.getZPos() + 44;
                damager.setCurrentPos(posX,posY,posZ);
            }else{
                local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),-6);
                local posY = obj.getYPos() - 1;
                local posZ = obj.getZPos() + 59;
                damager.setCurrentPos(posX,posY,posZ);
            }

//FINISH GRAB SET FLAG 1 
//[OFFSET]
//`grab pos`	-39	0	44
//SET FLAG 2 
//[OFFSET]
//`grab pos`	-6	0	59

        }

    }else if (state == 4)
    {


    }else if (state == 5)
    {
        if (obj.getVar("dama").get_obj_vector_size() > 0)
        {
            local damager = obj.getVar("dama").get_obj_vector(0);

            obj.setCurrentPos(damager.getXPos(),damager.getYPos(),damager.getObjectHeight() / 2 );
        }
    }else if (state == 6)
    {

        if (obj.getVar("dama").get_obj_vector_size() > 0)
        {
            local damager = obj.getVar("dama").get_obj_vector(0);

            local pAni = obj.sq_GetCurrentAni();
            local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
            local currentT = sq_GetCurrentTime(pAni);

            if (frmIndex % 2 == 0)
            {
                local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),-39);
                local posY = obj.getYPos() - 1;
                local posZ = obj.getZPos() + 44;
                damager.setCurrentPos(posX,posY,posZ);
            }else{
                local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),-6);
                local posY = obj.getYPos() - 1;
                local posZ = obj.getZPos() + 59;
                damager.setCurrentPos(posX,posY,posZ);
            }

//FINISH GRAB SET FLAG 1 
//[OFFSET]
//`grab pos`	-39	0	44
//SET FLAG 2 
//[OFFSET]
//`grab pos`	-6	0	59

        }



        local z = obj.getZPos();
        local x = 0;
        local y = 0;
        local move = 3;
		if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL)) x = - move;
		if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL)) x = move;
		if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL)) y = - move;
		if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL)) y = move;

        obj.sq_SetfindNearLinearMovablePos(obj.getXPos() + x,obj.getYPos() + y,obj.getXPos(), obj.getYPos(), 10);

        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),z);

        if (obj.getZPos() <= 0)
        {
            if (obj.getVar("dama").get_obj_vector_size() <= 0)
            {
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(7);
                obj.sq_AddSetStatePacket(STATE_GOTOHELL, STATE_PRIORITY_USER, true);
            }else{
                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(3);
                obj.sq_AddSetStatePacket(STATE_GOTOHELL, STATE_PRIORITY_USER, true);
            }
        }
    }
}

function onEndCurrentAni_GOTOHELL(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 1)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(5);
		obj.sq_AddSetStatePacket(STATE_GOTOHELL, STATE_PRIORITY_USER, true);
    }else if (state == 3)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(4);
		obj.sq_AddSetStatePacket(STATE_GOTOHELL, STATE_PRIORITY_USER, true);
    }else if (state == 4)
    {
        local isBack = obj.getVar("isBack").get_vector(0);
        if (isBack == 1)
        {   
            local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_GOTOHELL, STATE_GOTOHELL, 0, 1.0 );
            sendOneHitAllMonsterShaowAreaObj(obj,attackBonusRate);
        }
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 5)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_GOTOHELL, STATE_PRIORITY_USER, true);
    }else if (state == 7)
    {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}

function onAttack_GOTOHELL(obj, damager, boundingBox, isStuck)
{
    
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        if(!sq_IsFixture(damager)) 
        {
            if (obj.getVar("dama").get_obj_vector_size() <= 0)
            {
            
                obj.getVar("dama").push_obj_vector(damager);

                if (isEnemyBack(obj,damager) )
                {
                    obj.getVar("isBack").clear_vector();
                    obj.getVar("isBack").push_vector(1);
                }

            }
            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_GOTOHELL, false, "character/thief/4_shadow/gotohell/ap_gotohell.nut", true);				 

            if(masterAppendage) 
            {
                sq_HoldAndDelayDie(damager, obj, true, false, false, 0, 0, ENUM_DIRECTION_NEUTRAL , masterAppendage);
            }


            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            obj.sq_AddSetStatePacket(STATE_GOTOHELL, STATE_PRIORITY_USER, true);
        }
    }else if (state == 6)
    {
		if(!sq_IsFixture(damager)) 
        {
            if (obj.getVar("dama").get_obj_vector_size() <= 0)
            {
            
                obj.getVar("dama").push_obj_vector(damager);

                if (isEnemyBack(obj,damager) )
                {
                    obj.getVar("isBack").clear_vector();
                    obj.getVar("isBack").push_vector(1);
                }

            }
            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_GOTOHELL, false, 
            "character/thief/4_shadow/gotohell/ap_gotohell.nut", true);				 


        }
    }
}

function checkExecutableSkill_gotohell(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_GOTOHELL);
	if (isUseSkill) 
    {
        if (obj.getZPos() <= 0)
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(0);
        }else{
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(6);
        }
		obj.sq_AddSetStatePacket(STATE_GOTOHELL, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_gotohell(obj)  
{

	return true;
}