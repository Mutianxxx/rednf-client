function onTimeEventEtc_po_bloodcut(obj, timeEventIndex, timeEventCount)
{
	if (!obj)
		return 0;

    local id = obj.getVar("id").get_vector(0 );
    if (id == 217)
    {
        local isP = obj.getVar("var").get_vector(0);
        local saveT = obj.getVar("var").get_vector(1);
        local atkT = obj.getVar("var").get_vector(2);
        local pushA = obj.getVar("var").get_vector(3);

        local state = obj.getVar("state").get_vector(0);

        if (state == 3)
        {
            if (timeEventIndex == 0)
            {
                obj.getVar("state").set_vector(0,4);
                local ani = obj.getVar().GetAnimationMap("4", 
                "passiveobject/zrr_skill/newthier/animation/livingdead/end_livingdead.ani"); 
                obj.setCurrentAnimation(ani);

            }else if (timeEventIndex == 1)
            {



                local maxD = obj.getVar("var").get_vector(4);
                local minS = obj.getVar("var").get_vector(5);
                local maxS = obj.getVar("var").get_vector(6);
                local maxT = obj.getVar("var").get_vector(7);

                local y = obj.getVar("var").get_vector(8);

                sq_BinaryStartWrite();
                sq_BinaryWriteDword( pushA );
                sq_BinaryWriteDword(218);
                sq_BinaryWriteDword(maxD + sq_getRandom(0,50).tointeger() );
                sq_BinaryWriteDword(minS + sq_getRandom(0,5).tointeger());
                sq_BinaryWriteDword(maxS + sq_getRandom(0,5).tointeger());
                sq_BinaryWriteDword(maxT + sq_getRandom(0,25).tointeger());
                sq_BinaryWriteDword(0);
                sq_BinaryWriteDword(isP);
                sq_BinaryWriteDword( sq_getRandom(-y,y ));
                sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos() , obj.getYPos() + 1, 37);

                sq_BinaryStartWrite();
                sq_BinaryWriteDword( pushA );
                sq_BinaryWriteDword(218);
                sq_BinaryWriteDword(maxD + sq_getRandom(0,50).tointeger());
                sq_BinaryWriteDword(minS + sq_getRandom(0,5).tointeger());
                sq_BinaryWriteDword(maxS + sq_getRandom(0,5).tointeger());
                sq_BinaryWriteDword(maxT + sq_getRandom(0,25).tointeger());
                sq_BinaryWriteDword( obj.getVar("var").get_vector(9) );
                sq_BinaryWriteDword(isP);
                sq_BinaryWriteDword( sq_getRandom(-y,y ));
                sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos() , obj.getYPos() + 1, 37);

                sq_BinaryStartWrite();
                sq_BinaryWriteDword( pushA );
                sq_BinaryWriteDword(218);
                sq_BinaryWriteDword(maxD + sq_getRandom(0,50).tointeger());
                sq_BinaryWriteDword(minS + sq_getRandom(0,5).tointeger());
                sq_BinaryWriteDword(maxS + sq_getRandom(0,5).tointeger());
                sq_BinaryWriteDword(maxT + sq_getRandom(0,25).tointeger());
                sq_BinaryWriteDword( -obj.getVar("var").get_vector(9) );
                sq_BinaryWriteDword(isP);
                sq_BinaryWriteDword( sq_getRandom(-y,y ));
                sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos() , obj.getYPos() + 1, 37);


            }
        }

    }else if (id == 211)
    {
        if (timeEventIndex == 0)
        {
            obj.resetHitObjectList();
        }else if (timeEventIndex == 1){

            local flashScreenObj = obj.getVar("flashScreenObj").get_obj_vector(0);
                
            if(flashScreenObj) {
                    local pflashScreen = sq_GetCNRDObjectToFlashScreen(flashScreenObj);
                    if(pflashScreen)
                        pflashScreen.fadeOut();
            }		

            createDragonMineLoopGroundEndEffect(obj);
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 210)
    {
            obj.resetHitObjectList();
    }else if (id == 205)
    {
        if (timeEventIndex == 0)
        {

            local atk = obj.getVar("atkHit").get_vector(0);
            obj.getVar("atkHit").set_vector(0,-9);
            local attackInfo = sq_GetCustomAttackInfo(obj, 173);
            sq_SetCurrentAttackBonusRate(attackInfo, atk );
            sq_SetCurrentAttackInfo(obj, attackInfo);

            local target = obj.getVar("target").get_obj_vector(0);
            if (target)
            {
                obj.setCurrentPos(target.getXPos(),target.getYPos(),target.getZPos() );
                sq_SendHitObjectPacketWithNoStuck(obj,target,0,0,0);
                local ani = obj.getVar().GetAnimationMap("2", 
                            "character/swordman/effect/animation/atfistofexplosion/talisman/atfistofexplosiontalismaneffect_04.ani"); 
                obj.setCurrentAnimation(ani);

            }else{

                sq_SendDestroyPacketPassiveObject(obj);

            }


        }else if (timeEventIndex == 1)
        {

            if (obj.getVar("atkHit").get_vector(0) <= 0)
                return ;

            local target = obj.getVar("target").get_obj_vector(0);
            if (target)
            {

                sq_SendHitObjectPacketWithNoStuck(obj,target,0,0,0);

            }else{

                sq_SendDestroyPacketPassiveObject(obj);

            }
        }

    }else if (id >= 198 && id <= 203)
    {
        obj.resetHitObjectList();
    }else if (id == 196)
    {

        if (timeEventIndex == 0)
        {
            obj.getVar("state").set_vector(0,1);
            local atk = obj.getVar("state").get_vector(1);

            local ani = obj.getVar().GetAnimationMap("2", 
                        "passiveobject/character/swordman/animation/shockwaveareaexplosion.ani"); 
            obj.setCurrentAnimation(ani);

            local attackInfo = sq_GetCustomAttackInfo(obj, 165);
            sq_SetCurrentAttackPower(attackInfo, atk );
            sq_SetCurrentAttackInfo(obj, attackInfo);
            obj.resetHitObjectList();

            local fuckObj = obj.getVar("fuckObj").get_obj_vector(0);
            if (fuckObj)
            {

                CNSquirrelAppendage.sq_RemoveAppendage(fuckObj, "character/newswordman/shockwavearea/ap_shockwavearea_new.nut");

            }

        }else if (timeEventIndex == 1)
        {
            local state = obj.getVar("state").get_vector(0);
            if (state == 0)
            {
                local fuckObj = obj.getVar("fuckObj").get_obj_vector(0);
                
                if (fuckObj)
                {
                    sq_SendHitObjectPacket(obj,fuckObj,0,0, fuckObj.getObjectHeight()/2 );
                }else{
                    sq_SendDestroyPacketPassiveObject(obj);
                }
            }
        }


    }else if (id == 192)
    {
        local fuckObj = obj.getVar("fuckObj").get_obj_vector(0);
        if (fuckObj)
        {

            if (timeEventCount <= obj.getVar("hitCount").get_vector(0))
            {
                
                sq_SendHitObjectPacket(obj,fuckObj,0,0, fuckObj.getObjectHeight()/2 );

            }else{

                sq_SendDestroyPacketPassiveObject(obj);
            }

        }else{

            sq_SendDestroyPacketPassiveObject(obj);
        }


    }else if (id == 188 || id == 191)
    {
        obj.resetHitObjectList();
    }else if (id == 182)
    {
        if (obj.getVar("var").get_vector(3) == 0)
            obj.resetHitObjectList();
    }else if (id == 180)
    {
        local atk = obj.getVar("var").get_vector(2);
        sq_createAttackObjectWithPath(obj, 
        "passiveobject/zrr_skill/atswordman/atoverblowslash/overblowslashneweffect_23_dummy.ani",
        "passiveobject/zrr_skill/atswordman/attackinfo/atoverblowslash.atk",true,atk ,
        100,
		200,1,0);		

    }else if (id == 172)
    {
        local state = obj.getVar("state").get_vector(0);
        if (state == 1)
        {
          local ani = obj.getVar().GetAnimationMap("devilLeftBoom", 
          "passiveobject/zrr_skill/priest/animation/inviteofdevil/devilinvitation_l_boom_02.ani"); 
           if (obj.getVar("isAwake").get_vector(0) == 1)
           {
                ani = obj.getVar().GetAnimationMap("devilLeft_BoomAW", 
               "passiveobject/zrr_skill/priest/animation/inviteofdevil/devilinvitation_w_l_boom_02.ani");
           } 
          obj.setCurrentAnimation(ani );
          obj.getVar("state").set_vector(0,2);
        }
    }
    if (id == 171)
    {
        local state = obj.getVar("state").get_vector(0);
        if (state == 1)
        {
          local ani = obj.getVar().GetAnimationMap("devilRightBoom", 
          "passiveobject/zrr_skill/priest/animation/inviteofdevil/devilinvitation_r_boom_02.ani"); 
           if (obj.getVar("isAwake").get_vector(0) == 1)
           {
                ani = obj.getVar().GetAnimationMap("devilLeft_BoomAW", 
               "passiveobject/zrr_skill/priest/animation/inviteofdevil/devilinvitation_w_r_boom_02.ani");
           } 
          obj.setCurrentAnimation(ani );
          obj.getVar("state").set_vector(0,2);
          local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 135);
          local attackBouns = obj.getVar("attackBouns").get_vector(0);
          sq_BinaryStartWrite();
          sq_BinaryWriteDword(attackBouns );
          sq_BinaryWriteDword(173);
          sq_BinaryWriteDword( obj.getVar("isAwake").get_vector(0) );
          sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, posX , obj.getYPos() - 2, 37);
        }
    }
    if (id == 155)
    {
        obj.resetHitObjectList();
    }
    if (id == 154)
    {
        obj.resetHitObjectList();
    }
    if (id == 147)
    {
        if (timeEventIndex == 0)
        {
            local hitObj = obj.getVar("hitObj").get_obj_vector(0);
            local hitCount = obj.getVar("save").get_vector(0);


            if (hitCount < timeEventCount)
            {
                local objState = obj.getVar("save").get_vector(1);
                local mage = obj.getTopCharacter();
                mage = sq_ObjectToSQRCharacter(mage);	
                if (!mage)
                    return false;

                if (objState == STATE_SPRITGHOSTSLASH)
                {
                    local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_SPRITGHOSTSLASH_ATTACK);
                    local damage = mage.sq_GetBonusRateWithPassive(SKILL_SPRITGHOSTSLASH , STATE_SPRITGHOSTSLASH, 0, 1.0);
                    sq_SetCurrentAttackBonusRate(atk, damage);
                    sq_SetCurrentAttackInfo(obj, atk);
                    sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );
                    sq_SendDestroyPacketPassiveObject(obj);
                }else if (objState == STATE_SOULSLASH)
                {
                    local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_SOULSLASH);
                    local damage = mage.sq_GetBonusRateWithPassive(SKILL_SOULSLASH , STATE_SOULSLASH , 0, 1.0);
                    sq_SetCurrentAttackBonusRate(atk, damage);
                    sq_SetCurrentAttackInfo(obj, atk);
                    sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );
                    sq_SendDestroyPacketPassiveObject(obj);
                }else if (objState == STATE_SLADETOOTHSLASH)
                {
                    local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_BLOODCUTHIT_LAST);
                    local damage = mage.sq_GetBonusRateWithPassive(SKILL_SLADETOOTHSLASH , STATE_SLADETOOTHSLASH, 0, 1.0);
                    sq_SetCurrentAttackBonusRate(atk, damage);
                    sq_SetCurrentAttackInfo(obj, atk);
                    sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );
                    onAttack_SLADETOOTHSLASH(mage, hitObj, -1, -1);
                    sq_SendDestroyPacketPassiveObject(obj);
                }else if (objState == STATE_SPRITSLADETHREESLASH)
                {
                    obj.setTimeEvent(1, 50 ,0,false);		
                    obj.setTimeEvent(0, 50 ,1,false);		
                }else if (objState == STATE_RANDOMSLASH)
                {
                    obj.setTimeEvent(2, 100 ,0,false);		
                    obj.setTimeEvent(0, 50 ,1,false);		
                }else if (objState == STATE_UNLIMITED_SPEED_SLASH)
                {
                    obj.setTimeEvent(4, 30 ,0,false);		
                    obj.setTimeEvent(0, 50 ,1,false);		
                }
                else{
                    sq_SendDestroyPacketPassiveObject(obj);
                }

            }else{
                sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );
            }
        }else if (timeEventIndex == 1)
        {
            local hitObj = obj.getVar("hitObj").get_obj_vector(0);
            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	
            if ( timeEventCount == 1 )
            {
                local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_SPRITSLADETHREESLASH_FIRST );
                local damage = mage.sq_GetBonusRateWithPassive(SKILL_SPRITSLADETHREESLASH, STATE_SPRITSLADETHREESLASH, 0, 1.0);
                sq_SetCurrentAttackBonusRate(atk, damage);
                sq_SetCurrentAttackInfo(obj, atk);
                sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );
            }else if ( timeEventCount == 2 )
            {
                local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_SPRITSLADETHREESLASH_SECOND);
                local damage = mage.sq_GetBonusRateWithPassive(SKILL_SPRITSLADETHREESLASH, STATE_SPRITSLADETHREESLASH, 1, 1.0);
                sq_SetCurrentAttackBonusRate(atk, damage);
                sq_SetCurrentAttackInfo(obj, atk);
                sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );
            }else if ( timeEventCount == 3 )
            {
                local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_SPRITSLADETHREESLASH_THIRD );
                local damage = mage.sq_GetBonusRateWithPassive(SKILL_SPRITSLADETHREESLASH, STATE_SPRITSLADETHREESLASH, 2, 1.0);
                sq_SetCurrentAttackBonusRate(atk, damage);
                sq_SetCurrentAttackInfo(obj, atk);
                sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );

            }else if ( timeEventCount == 4 )
            {
                local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_SPRITSLADETHREESLASH_FOUR );
                local damage = mage.sq_GetBonusRateWithPassive(SKILL_SPRITSLADETHREESLASH, STATE_SPRITSLADETHREESLASH, 2, 1.0);
                sq_SetCurrentAttackBonusRate(atk, damage);
                sq_SetCurrentAttackInfo(obj, atk);
                sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );

            }else if (timeEventCount == 5)
            {
                sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );
                sq_SendDestroyPacketPassiveObject(obj);
            }
            local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackeHitStunTime(currentAttackInfo, 0);
        }else if (timeEventIndex == 2)
        {

            local hitObj = obj.getVar("hitObj").get_obj_vector(0);
            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	
            if ( timeEventCount == 1 )
            {
                local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_RANDOMSLASH_1 );
                local damage = mage.sq_GetBonusRateWithPassive(SKILL_RANDOMSLASH , STATE_RANDOMSLASH , 0, 1.0);
                sq_SetCurrentAttackBonusRate(atk, damage);
                sq_SetCurrentAttackInfo(obj, atk);
                sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );
            }else if ( timeEventCount == 2 )
            {
                local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_RANDOMSLASH_2);
                local damage = mage.sq_GetBonusRateWithPassive(SKILL_RANDOMSLASH , STATE_RANDOMSLASH , 1, 1.0);
                sq_SetCurrentAttackBonusRate(atk, damage);
                sq_SetCurrentAttackInfo(obj, atk);
                sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );
            }else if ( timeEventCount == 3 )
            {
                local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_RANDOMSLASH_3 );
                local damage = mage.sq_GetBonusRateWithPassive(SKILL_RANDOMSLASH , STATE_RANDOMSLASH , 2, 1.0);
                sq_SetCurrentAttackBonusRate(atk, damage);
                sq_SetCurrentAttackInfo(obj, atk);
                sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );

            }else if ( timeEventCount == 4 )
            {
                local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_RANDOMSLASH_4 );
                local damage = mage.sq_GetBonusRateWithPassive(SKILL_RANDOMSLASH , STATE_RANDOMSLASH , 3, 1.0);
                sq_SetCurrentAttackBonusRate(atk, damage);
                sq_SetCurrentAttackInfo(obj, atk);
                sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );
                local hitCount = mage.sq_GetIntData(SKILL_RANDOMSLASH, 2);
                obj.setTimeEvent(3, 100 / hitCount,hitCount,false);		

            }else if (timeEventCount == 5)
            {
                obj.setTimeEvent(3, 50,1,false);		
                local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_RANDOMSLASH_3 );
                local damage = mage.sq_GetBonusRateWithPassive(SKILL_RANDOMSLASH , STATE_RANDOMSLASH ,4, 1.0);
                sq_SetCurrentAttackBonusRate(atk, damage);
                sq_SetCurrentAttackInfo(obj, atk);
                sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );
                sq_SendDestroyPacketPassiveObject(obj);
            }
            local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackeHitStunTime(currentAttackInfo, 0);


        }else if (timeEventIndex == 3)
        {
            obj.resetHitObjectList();


        }else if (timeEventIndex == 4)
        {
            local hitObj = obj.getVar("hitObj").get_obj_vector(0);
            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	
            if (timeEventCount < 5)
            {
                local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_UNLIMITED_SPEEDSLASH_FINISH_HIT );
                local damage = mage.sq_GetBonusRateWithPassive(SKILL_UNLIMITED_SPEED_SLASH, STATE_UNLIMITED_SPEED_SLASH, 4, 1.0);
                sq_SetCurrentAttackBonusRate(atk, damage);
                sq_SetCurrentAttackInfo(obj, atk);
                sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );

            }else{
                local atk = sq_GetCustomAttackInfo(mage,ATTACKINFO_UNLIMITED_SPEEDSLASH_FINISH_HIT );
                local damage = mage.sq_GetBonusRateWithPassive(SKILL_UNLIMITED_SPEED_SLASH, STATE_UNLIMITED_SPEED_SLASH, 5, 1.0);
                sq_SetCurrentAttackBonusRate(atk, damage);
                sq_SetCurrentAttackInfo(obj, atk);
                sq_SendHitObjectPacket(obj,hitObj,0,0, hitObj.getObjectHeight()/2 );
                sq_SendDestroyPacketPassiveObject(obj);
            }
            local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackeHitStunTime(currentAttackInfo, 0);
        }
    }
    if (id == 146)
    {
        obj.resetHitObjectList();
    }
    if (id == 145)
    {
        obj.resetHitObjectList();
    }

    if (id == 140 || id == 141)
    {
        obj.resetHitObjectList();
    }

    if (id == 138)
    {
        if (!obj.isMyControlObject())
            return false;

        if (timeEventIndex == 0)
        {
            createGluttonyMulitHitNoneAnimation(obj);
        }else if (timeEventIndex == 1)
        {

            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();

            for(local i=0;i<objectsSize;++i)
            {

                    local damager = var.get_obj_vector(i);
                    local objX = obj.getXPos();
                    local objY = obj.getYPos() + 1;
                    local damaX = damager.getXPos();
                    local damaY = damager.getYPos();
                    local damaZ = damager.getZPos();
                    local x_move = obj.getVar("var").get_vector(2);
                    local y_move = obj.getVar("var").get_vector(3);
                    if (objX < damaX) x_move = - x_move;
                    if (objY < damaY) y_move = - y_move;
                    damager.setCurrentPos(damaX + x_move,damaY + y_move,damaZ);
                    if (sq_Abs ( objX - damaX) < 2 * obj.getVar("var").get_vector(2) )
                        damager.setCurrentPos(objX,damager.getYPos(),damager.getZPos() );
                    if (sq_Abs ( objY - damaY) < 2 * obj.getVar("var").get_vector(3) )
                        damager.setCurrentPos(damager.getXPos(),obj.getYPos() + 1,damager.getZPos() );
            }

        }
    }

    if (id == 134)
    {
        if (timeEventIndex == 0)
        {
            setEpidMicrasaCreatorHitTarget(obj);
        }else if (timeEventIndex == 1)
        {
            local size = obj.getVar("var").get_vector(3);
            createEpidMicrasaDisAppearEffect(obj,size);
            local areaObj = obj.getVar("effect").get_obj_vector(0);
            if (areaObj)
                areaObj.setValid(false);
            setVliadEffectEpidMicrasaPassiveobject(obj);
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }

    if (id == 131)
    {
        if (timeEventIndex == 0)
        {
            if (timeEventCount < obj.getVar("var").get_vector(0) )
                obj.resetHitObjectList();
        }else if (timeEventIndex == 1)
        {

            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();

            for(local i=0;i<objectsSize;++i)
            {

                    local damager = var.get_obj_vector(i);
                    local objX = obj.getXPos();
                    local objY = obj.getYPos() + 1;
                    local damaX = damager.getXPos();
                    local damaY = damager.getYPos();
                    local damaZ = damager.getZPos();
                    local x_move = obj.getVar("var").get_vector(2);
                    local y_move = obj.getVar("var").get_vector(3);
                    if (objX < damaX) x_move = - x_move;
                    if (objY < damaY) y_move = - y_move;
                    damager.setCurrentPos(damaX + x_move,damaY + y_move,damaZ);
                    if (sq_Abs ( objX - damaX) < 2 * obj.getVar("var").get_vector(2) )
                        damager.setCurrentPos(objX,damager.getYPos(),damager.getZPos() );
                    if (sq_Abs ( objY - damaY) < 2 * obj.getVar("var").get_vector(3) )
                        damager.setCurrentPos(damager.getXPos(),obj.getYPos() + 1,damager.getZPos() );
            }

        }
    }

//
    if (id == 130)
    {

        onTimeEeventNutPoCrystalOfOverMind(obj,timeEventIndex);

    }

    if (id == 128)
    {
            obj.resetHitObjectList();
    }
    if (id == 38)
    {
        local state = obj.getVar("state").get_vector(0);
        if (timeEventIndex == 10)
        {
            if (state != ENUM_PASSIVEOBJECT_LIGHTING_GOD_STATE_DROP && state != EUNM_PASSIVEOBJECT_LIGHTING_GOD_STATE_DROP_SWORD 
                && state != EUNM_PASSIVEOBJECT_LIGHTING_GOD_STATE_EXPLOSION)
            {

                local var = obj.getVar("dama");  		
                local objectsSize = var.get_obj_vector_size();

                for(local i=0;i<objectsSize;++i)
                {

                        local damager = var.get_obj_vector(i);
                        local objX = obj.getXPos();
                        local objY = obj.getYPos();
                        local damaX = damager.getXPos();
                        local damaY = damager.getYPos();
                        local damaZ = damager.getZPos();
                        local x_move = 2;
                        local y_move = 1;

                        if (objX < damaX) x_move = - x_move;
                        if (objY < damaY) y_move = - y_move;
                        if(damaZ > 0)
                        {
                            damaZ = damaZ - 5;
                        }else{
                            damaZ = 0;
                        }
                        damager.setCurrentPos(damaX + x_move,damaY + y_move,damaZ);

                }

            }
        }else{

            if (state == ENUM_PASSIVEOBJECT_LIGHTING_GOD_STATE_ROAR || state == ENUM_PASSIVEOBJECT_LIGHTING_GOD_STATE_READ_SWROD || 
                state == EUNM_PASSIVEOBJECT_LIGHTING_GOD_STATE_TOGETHER )
                obj.resetHitObjectList();
        }
    }
    if (id == 127)
    {
            obj.resetHitObjectList();
    }
    if (id == 121)
    {
            obj.resetHitObjectList();
    }
    if (id == 120)
    {
        if (timeEventIndex == 0)
        {
            setVliadEffectBlachePassiveObject(obj);
            sq_SendDestroyPacketPassiveObject(obj);
        }else if (timeEventIndex == 1)
        {
            obj.getVar().push_obj_vector( createBlacheStartEffect1(obj,200,1,0) );
            obj.getVar().push_obj_vector( createBlacheStartEffect1(obj,-200,1,0) );
            obj.getVar().push_obj_vector( createBlacheStartEffect1(obj,-150,-50,0) );
            obj.getVar().push_obj_vector( createBlacheStartEffect1(obj,-150,50,0) );
            obj.getVar().push_obj_vector( createBlacheStartEffect1(obj,0,-87,0) );
            obj.getVar().push_obj_vector( createBlacheStartEffect1(obj,0,87,0) );
            obj.getVar().push_obj_vector( createBlacheStartEffect1(obj,150,50,0) );
            obj.getVar().push_obj_vector( createBlacheStartEffect1(obj,150,-50,0) );
        }
    }
    if (id == 116)
    {
            obj.resetHitObjectList();
    }

    if (id == 112)
    {
        if (timeEventCount < obj.getVar("value").get_vector(2))
        {
            obj.resetHitObjectList();
        }else{
            createAtgEndAni(obj);
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }

    if (id == 104)
    {
        if ( timeEventIndex == 0 )
        {
            obj.resetHitObjectList();
        }else{
            setVliadEffectBlockHole(obj);
            if (obj.getVar().get_vector(0) == 0)
            {
                addPartlcAniBlockHole_2(obj,"passiveobject/zrr_skill/atmage/animation/atpositron/2crackend_01.ani"
                ,510 - 45,-140, -39);

                addPartlcAniBlockHole_2(obj,"passiveobject/zrr_skill/atmage/animation/atpositron/3crackend_01.ani"
                ,582 - 45,32,-39);

                addPartlcAniBlockHole_2(obj,"passiveobject/zrr_skill/atmage/animation/atpositron/1acrackend_01.ani"
                ,0,1,0);

                addPartlcAniBlockHole_2(obj,"passiveobject/zrr_skill/atmage/animation/atpositron/bcenterend_10.ani"
                ,300 - 45,1,0);
            }


            sq_SendDestroyPacketPassiveObject(obj);
        
        }
    }
    if (id == 102)
    {
            obj.resetHitObjectList();
    }
    if (id == 100)
    {
        local object = obj.getVar("obj").get_obj_vector(0);
        if (object)
        {
            createTepesHitEffect1(obj,object);
            createTepesHitEffect2(obj,object);
            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	


            sq_SendHitObjectPacket(obj,object,0,0, object.getObjectHeight()/2 );
//            sq_SetMyShake(obj, 4, 20);

            obj.getVar("hei").set_vector(0,obj.getVar("hei").get_vector(0) + 
            mage.sq_GetIntData(SKILL_BLOODSONG, 23));

        }
    }
    if (id == 78)
    {
            sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 96)
    {
            sq_SendDestroyPacketPassiveObject(obj);
    }
    if (id == 93)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
        local ani = obj.getCustomAnimation(127);
		obj.setCurrentAnimation(ani);
    }
    if (id == 91)
    {
        local maxC = obj.getVar("v").get_vector(0);
        local tar = obj.getVar("dama").get_obj_vector(0);

        if (timeEventCount >= maxC)
        {
            createSwordBehindSwordEffect5(obj,tar);
            local attackInfo = sq_GetCurrentAttackInfo(obj);
            local attackBonusRate = obj.getVar("v").get_vector(1);
            sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
            sq_SendHitObjectPacket(obj,tar,0,0,0);
            sq_SendDestroyPacketPassiveObject(obj);
        }else{
            sq_SendHitObjectPacket(obj,tar,0,0,0);
            local anilst = (timeEventCount * 100 /maxC );
            if (anilst <= 20)
            {
                if (obj.getVar("flag").get_vector(0) == 0)
                {
                    createSwordBehindSwordEffect1(obj,tar);
                    obj.getVar("flag").set_vector(0,1);
                }
            }else if (anilst <= 40)
            {
                if (obj.getVar("flag").get_vector(1) == 0)
                {
                    createSwordBehindSwordEffect2(obj,tar);
                    obj.getVar("flag").set_vector(1,1);
                }
            }else if (anilst <= 60)
            {
                if (obj.getVar("flag").get_vector(2) == 0)
                {
                    createSwordBehindSwordEffect3(obj,tar);
                    obj.getVar("flag").set_vector(2,1);
                }
            }else if (anilst <= 80)
            {
                if (obj.getVar("flag").get_vector(3) == 0)
                {
                    createSwordBehindSwordEffect4(obj,tar);
                    obj.getVar("flag").set_vector(3,1);
                }
            }




        }
    }

    if (id == 81)
    {
        if ( timeEventIndex == 0 )
        {
            obj.resetHitObjectList();
        }else{
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }
    if (id == 77)
    {
        if ( timeEventIndex == 0 )
        {
            local size = obj.getVar("size").get_vector(0);
            local sizeRate = size.tofloat() / 100.0;

            local currentAni = sq_GetCurrentAnimation(obj);

            currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
            currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
            obj.getVar("size").set_vector(0,5 + size);
        }else{
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }

    if (id == 75)
    {
        obj.resetHitObjectList();
    }
    if (id == 67)
    {
        obj.resetHitObjectList();
    }
    if (id == 62)
    {
        if (timeEventIndex == 0)
        {

                local mage = obj.getTopCharacter();
                mage = sq_ObjectToSQRCharacter(mage);	
                setBloodValue(mage,obj.getVar("blood").get_vector(0) );



        }
    }

    if (id == 59)
    {
        if (timeEventIndex == 1)
        {

            if (obj.getVar("isSum").get_vector(0) == 1)
            {
                local objX = obj.getXPos();
                local objY = obj.getYPos();
                local objZ = obj.getZPos();
                local currJu = obj.getVar("isSum").get_vector(2);
                local size = obj.getVar("value").get_vector(3);

                local currDistance =  35 * currJu *  size / 100 ;
                local posX = 0;
                if (obj.getVar("isSum").get_vector(1) == 0)
                {
                    posX = sq_GetDistancePos(objX, obj.getDirection(), currDistance + 50 *  size / 100 );
                    createBloodHoldSpearNormalDirection(obj,posX,obj.getYPos(),obj.getZPos(),size );
                    
                }else{
                    posX = sq_GetDistancePos(objX, obj.getDirection(), 350 *  size / 100  - currDistance);
                    createBloodHoldSpearOppositeDirection(obj,posX,obj.getYPos(),obj.getZPos(),size );
                }
                obj.getVar("isSum").set_vector(2,currJu + 1);


//        obj.getVar("isSum").push_vector(0);
//        obj.getVar("isSum").push_vector(is);
//        obj.getVar("isSum").push_vector(0);
//        obj.getVar("isSum").push_vector(count);

            }



        }else if (timeEventIndex == 0)
        {
            obj.resetHitObjectList();
        }else if (timeEventIndex == 2)
        {
            setBloodHoldPassiveobjectTargetMoveEffect(obj);

        //    obj.resetHitObjectList();
        }
    }
    if (id == 57)
    {
        if (timeEventIndex == 0)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }

    }

    if (id == 54)
    {
        if (timeEventIndex == 0)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }else if (timeEventIndex == 1)
        {
            obj.resetHitObjectList();
        }
    }
    if (id == 50)
    {
        local atk = obj.getVar("v").get_vector(0);
        local id2 = obj.getVar("v").get_vector(1);
        local speed = obj.getVar("v").get_vector(2);
        sq_BinaryStartWrite();
        sq_BinaryWriteDword(atk);	// attackBonusRate
        sq_BinaryWriteDword(51);	// attackBonusRate
        sq_BinaryWriteDword(id2);	// attackBonusRate
        sq_BinaryWriteDword(speed);	// attackBonusRate
        sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos() , obj.getYPos() + 1, obj.getZPos() );
		sq_SendDestroyPacketPassiveObject(obj);
    }


    if (id == 33)
    {
        local gdProc = obj.getVar("value").get_vector(2);
        local gdLeve = obj.getVar("value").get_vector(3);
        local gdTime = obj.getVar("value").get_vector(4);
        local gdRate = obj.getVar("value").get_vector(5);
        if (timeEventIndex == 0)
        {


            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();


            local attackBonusRate = obj.getVar("value").get_vector(1);
            if (objectsSize >= 2)
                attackBonusRate = obj.getVar().get_vector(2);

            local attackInfo = sq_GetCustomAttackInfo(obj, 100);
            sq_SetCurrentAttackInfo(obj, attackInfo);
            attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
            sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, 6, gdProc, gdLeve, gdTime,gdRate);


            if (objectsSize > 0 )
            {
                if (obj.isMyControlObject())
                {
                    sq_SetMyShake(obj,5,200);
                    sq_flashScreen(obj,60,420,0,191, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
                }
                for(local i=0;i<objectsSize;++i)
                {
                    local damager = var.get_obj_vector(i);
                    sq_SendHitObjectPacket(obj,damager,0,0,damager.getObjectHeight()/2 );
                    createHighLightWaveLastBoomEffect(obj,damager);
                }
            }

            sq_SendDestroyPacketPassiveObject(obj);	
        }else if (timeEventIndex == 1){

            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();

            local attackBonusRate = obj.getVar("value").get_vector(0);
            local attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
            sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, 6, gdProc, gdLeve, gdTime,gdRate);
            if (objectsSize > 0)
            {
                for(local i=0;i<objectsSize;++i)
                {
                    local damager = var.get_obj_vector(i);
                    sq_SendHitObjectPacket(obj,damager,0,0,damager.getObjectHeight()/2 );
                }
            }else{
                sq_SendDestroyPacketPassiveObject(obj);	
            }

        }
    }

    if (id >= 28 && id<= 32 )
    {
        if (timeEventIndex == 0)
        {
            obj.resetHitObjectList();
        }
    }
    if (id == 26)
    {
        if (timeEventIndex == 1){

            obj.resetHitObjectList();
        }else if (timeEventIndex == 2){


            createFrontAreaWindFinish(obj,obj.getVar("size").get_vector(0));
            sq_SendDestroyPacketPassiveObject(obj);	

        }
    }

 if (id == 25)
    {
        if (timeEventIndex == 0)
        {

            sq_SendDestroyPacketPassiveObject(obj);	
        }else if (timeEventIndex == 1){

            obj.resetHitObjectList();
        }else if (timeEventIndex == 2)
        {

            local objX = obj.getXPos();
            local objY = obj.getYPos();
            local objZ = obj.getZPos();

            local currDis = obj.getVar("dis").get_vector(1);
            local dis = obj.getVar("dis").get_vector(0);
            local speed = obj.getVar("speed").get_vector(0);
            if (currDis+speed <= dis)
            {
                obj.getVar("dis").set_vector(1,currDis + speed);
                obj.getVar("speed").set_vector(0,speed + 1);
                local pos = sq_GetDistancePos(obj.getXPos(),obj.getDirection(),speed);
                obj.setCurrentPos(pos,obj.getYPos(),obj.getZPos());

            }
        }
    }


if (id == 22)
    {
        if (timeEventIndex == 0)
        {
            local atk = obj.getVar("atk").get_vector(0);

            sq_BinaryStartWrite();
            sq_BinaryWriteDword(atk);	// attackBonusRate
            sq_BinaryWriteDword(23);	// attackBonusRate
            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos(), obj.getYPos(), obj.getZPos() );
            sq_SetMyShake(obj,10,120);
            sq_SendDestroyPacketPassiveObject(obj);	



        }else if (timeEventIndex == 1){

            obj.resetHitObjectList();
            sq_SetMyShake(obj,2,120);
        }
    }

     if (id == 20)
        {
            if (timeEventIndex == 0)
            {
                obj.resetHitObjectList();
            }else if (timeEventIndex == 1)
            {
                if (timeEventCount %2 == 0)
                {
                    createSecondWindHit_PassiveobjectEffect_B01(obj);
                }else{
                    createSecondWindHit_PassiveobjectEffect_B02(obj);
                }
            }

        }

     if (id == 19)
        {
            if (timeEventIndex == 0)
            {
                obj.resetHitObjectList();
            }else if (timeEventIndex == 1)
            {
                if (timeEventCount %2 == 0)
                {
                    createSecondWindHit_PassiveobjectEffect_A01(obj);
                }else{
                    createSecondWindHit_PassiveobjectEffect_A02(obj);
                }
            }
        }

     if (id == 18)
        {
            local state = obj.getVar("state").get_vector(0);
            if (timeEventIndex == 0)
            {
                if (state == 0 || state == 1)
                    obj.resetHitObjectList();
            }else{

                if (state == 1)
                {

                    local currDis = obj.getVar("dis").get_vector(1);
                    local dis = obj.getVar("dis").get_vector(0);
                    local speed = 20;


                    if (currDis+speed <= dis)
                    {
                        obj.getVar("dis").set_vector(1,currDis + speed);

                        if (obj.getDirection() == ENUM_DIRECTION_LEFT)
                        {
                            obj.setCurrentPos(obj.getXPos() - speed,obj.getYPos(),obj.getZPos());
                        }else{
                            obj.setCurrentPos(obj.getXPos() + speed,obj.getYPos(),obj.getZPos());
                        }


                    }else{



                        obj.getVar("state").set_vector(0,2);

                        createStormQuakeLoopShootAEffect(obj,0,1,0);
                        createStormQuakeLoopShootABackEffect(obj,0,-1,0);
                        createStormQuakeLoopBigCloud01Effect(obj,0,1,0);
                        createStormQuakeLoopBigCloud01BackEffect(obj,0,-1,0);
                        createStormQuakeLoopCastingEffect(obj,0,1,0);


                        setValidStormQuakePooledObject(obj);
                        local damage1 = obj.getVar("state").get_vector(1);

//                        local ani = obj.getCustomAnimation(28);
                        local ani = obj.getVar().GetAnimationMap("3", 
                        "passiveobject/zrr_skill/atmage/animation/atstormquake/stormquake_c_wind_end12.ani"); 
                        obj.setCurrentAnimation(ani);
                        local attackInfo = sq_GetCustomAttackInfo(obj, 7);
                        sq_SetCurrentAttackInfo(obj, attackInfo);

                        attackInfo = sq_GetCurrentAttackInfo(obj);
                        sq_SetCurrentAttackBonusRate(attackInfo, damage1);

                        sq_flashScreen(obj,0,100,240,150, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
                        sq_SetMyShake(obj, 5, 60);

                    }



                }


            }

        }

    if (id == 17)
    {
        if (timeEventIndex == 0)
        {
            obj.getVar("isDrop").clear_vector();
            obj.getVar("isDrop").push_vector(1);
            local height = obj.getVar("height").get_vector(0);

            obj.setCurrentPos(obj.getXPos(),obj.getYPos(),height);

        }
    }
    
    if (id == 14)
    {
        if (timeEventIndex == 0)
        {

            local damager = obj.getVar("dama").get_obj_vector(0);
            sq_SendHitObjectPacket(obj,damager,0,0,0);
            if (obj.isMyControlObject())
            {
                sq_SendCreatePassiveObjectPacketPos(obj,12200, 0, damager.getXPos(), damager.getYPos() + 1,
                damager.getZPos() + damager.getObjectHeight()/2 );
            }
            sq_SendDestroyPacketPassiveObject(obj);	




//                obj.resetHitObjectList();
        }
    }

    if (id == 13)
    {
        if (timeEventIndex == 0)
        {
                obj.resetHitObjectList();
        }
    }


    if (id == 11)
    {
        if (timeEventIndex == 0)
        {
            sq_SendDestroyPacketPassiveObject(obj);	
        }
    }

    if (id == 9)
    {
        if (timeEventIndex == 0)
        {
            if (timeEventCount <= obj.getVar("attackvalue").get_vector(0))
            {
                local damager = obj.getVar("dama").get_obj_vector(0);
                if (damager)
                {
                    sq_SendHitObjectPacket(obj,damager,0,0,damager.getObjectHeight()/2 );
                    obj.sq_PlaySound("GUE_SWORD_01");
                }else{

                    sq_SendDestroyPacketPassiveObject(obj);	

                }
            }else{

                obj.getVar("state").set_vector(0,2);

                local isxz = obj.getVar("xlValue").get_vector(0);

                if (isxz == 0)
                {
                    sq_SendDestroyPacketPassiveObject(obj);	
                }else{
                    local ani = null;
                    obj.sq_PlaySound("GUE_SWORD_BIG");
                    sq_SetMyShake(obj,3,180);

                    sq_flashScreen(obj,0,120,180,102, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

                    if (obj.getVar("weapon").get_vector(0) == 2)
                    {
//                        ani = obj.getCustomAnimation(118);

                          ani = obj.getVar().GetAnimationMap("SwordOfMind_Last", 
                        "passiveobject/zrr_skill/swordman/animation/swordofmind/last_hit.ani"); 

                        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),0);
                    }else{
//                        ani = obj.getCustomAnimation(114);
                          ani = obj.getVar().GetAnimationMap("SwordOfMind_Last2", 
                        "passiveobject/zrr_skill/swordman/animation/swordofmind/last_hit.ani"); 
                    }
                    obj.setCurrentAnimation(ani);

                    local attackLast = obj.getVar("xlValue").get_vector(1);

                    local attackInfo = sq_GetCustomAttackInfo(obj, 96);
                    sq_SetCurrentAttackInfo(obj, attackInfo);

                    local attackInfo = sq_GetCurrentAttackInfo(obj);
                    sq_SetCurrentAttackBonusRate(attackInfo, attackLast);
    
                    local damager = obj.getVar("dama").get_obj_vector(0);

                    sq_SendHitObjectPacket(obj,damager,0,0,damager.getObjectHeight()/2 );

                    obj.setTimeEvent(0,99999,0,false);
                    obj.setTimeEvent(1,2000,0,false);
                }
            }

        }else if (timeEventIndex == 1)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }

    }

    if (id == 3)
    {

        if (timeEventIndex == 0)
        {
        obj.getVar("speed").set_vector(0, obj.getVar("speed").get_vector(0) + 5 );
        }

    }

    if (id == 4)
    {
        if (timeEventIndex == 0 && obj.getVar("4state").get_vector(0) == 1 )
        {
            if (timeEventCount > obj.getVar("aCount").get_vector(0) - 2)
            {


                local ani = obj.getVar().GetAnimationMap("4", 
                    "passiveobject/zrr_skill/atmage/animation/atphantombale/04_finish/last.ani"); 
                obj.setCurrentAnimation(ani);
                createPhantomBaleFinalyFrontBackEffect(obj,0,-3,0);


                local attackBonusRate = obj.getVar("attackBouns2").get_vector(0);

                local attackInfo = sq_GetCustomAttackInfo(obj, 90);
                sq_SetCurrentAttackInfo(obj, attackInfo);

                attackInfo = sq_GetCurrentAttackInfo(obj);
                sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

                obj.resetHitObjectList();

                obj.getVar("4state").clear_vector();
                obj.getVar("4state").push_vector(2);

                local dvalue = 1;
                if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT) dvalue = -1;


            }else{


                obj.resetHitObjectList();

                obj.getVar("aCCount").clear_vector();
                obj.getVar("aCCount").push_vector(timeEventCount);

            }

        }
    }


}















