function onKeyFrameFlagEtc_po_mage_bloodcut(obj, flagIndex)
{
    local id = obj.getVar("id").get_vector(0 );
    if (id == 222)
    {
        onFrameKeyFlagBellacreAdvent(obj,3,flagIndex);
        return true;
    }else if (id == 221)
    {
        onFrameKeyFlagBellacreAdvent(obj,2,flagIndex);
        if (flagIndex == 999)
        {
            local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 90);
            sq_BinaryStartWrite();
            sq_BinaryWriteDword( 0 );
            sq_BinaryWriteDword(222 );
            sq_SendCreatePassiveObjectPacketPos(obj, 24357, 0, posX, obj.getYPos(),0);
        }
        return true;
    }else if (id == 220)
    {
        onFrameKeyFlagBellacreAdvent(obj,1,flagIndex);
        return true;
    }
    else if (id == 219)
    {
        onFrameKeyFlagBellacreAdvent(obj,0,flagIndex);
        if (flagIndex == 4000)
        {



        }
        return true;
    }else if (id == 217)
    {
        if (flagIndex == 999)
        {

            local isP = obj.getVar("var").get_vector(0);
            local saveT = obj.getVar("var").get_vector(1);
            local atkT = obj.getVar("var").get_vector(2);
            local pushA = obj.getVar("var").get_vector(3);

            local state = obj.getVar("state").get_vector(0);

            if (state == 0)
            {
                obj.getVar("state").set_vector(0,1);
                local ani = obj.getVar().GetAnimationMap("1", 
                "passiveobject/zrr_skill/newthier/animation/livingdead/attact1start_livingdead.ani"); 
                obj.setCurrentAnimation(ani);

                obj.getVar("magic").clear_obj_vector();
                obj.getVar("magic").push_obj_vector( createliliyaLoopMagicEffect(obj) );

            }else if (state == 1)
            {
                obj.getVar("state").set_vector(0,2);
                local ani = obj.getVar().GetAnimationMap("2", 
                "passiveobject/zrr_skill/newthier/animation/livingdead/attack2start_livingdead.ani"); 
                obj.setCurrentAnimation(ani);
            }else if (state == 2)
            {
                obj.getVar("state").set_vector(0,3);
                local ani = obj.getVar().GetAnimationMap("3", 
                "passiveobject/zrr_skill/newthier/animation/livingdead/attack2loop_livingdead.ani"); 
                obj.setCurrentAnimation(ani);

                obj.setTimeEvent(0,saveT, 0, false );
                obj.setTimeEvent(1,atkT, 0, false );

            }else if (state == 3)
            {

            }else if (state == 4)
            {
                local pooled = obj.getVar("magic").get_obj_vector(0);
                if (pooled)
                    pooled.setValid(false);
                sq_SendDestroyPacketPassiveObject(obj);
            }
        }
    }else if (id == 212)
    {
            sq_flashScreen(obj,0,80,160,102, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        sq_SetMyShake(obj, 3, 240);
            return true;
    }else if (id == 205)
    {
                sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 194)
    {
        sq_SetMyShake(obj, 3, 180);
        return true;
    }else if (id == 187)
    {
        if (flagIndex == 1)
        {
            sq_flashScreen(obj,0,140,70,51, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;

        }
    }else if (id == 185)
    {
        if (flagIndex == 10)
        {
            local state = obj.getVar("state").get_vector(0);
            if (state == 0)
            {
                onSetStatePassiveobject_ZweivolTageExVertexSlash(obj,1);
                return true;
            }else if (state == 2)
            {
                onSetStatePassiveobject_ZweivolTageExVertexSlash(obj,3);
                return true;
            }else if (state == 3)
            {
                onSetStatePassiveobject_ZweivolTageExVertexSlash(obj,4);
                return true;
            }

        }
    }else if (id == 184)
    {
        if (flagIndex == 10)
        {
            local state = obj.getVar("state").get_vector(0);
            if (state == 0)
            {
                onSetStatePassiveobject_ZweivolTageExHorizenSlash(obj, 1 );
                return true;
            }else if (state == 2)
            {
                onSetStatePassiveobject_ZweivolTageExHorizenSlash(obj, 3 );
                return true;
            }else if (state == 3)
            {
                sq_SendDestroyPacketPassiveObject(obj);
                return true;
            }
        }

    }else if (id == 182)
    {
        if (flagIndex == 1)
        {

            local mulitHit = obj.getVar("var").get_vector(0);
            local mulitCount = obj.getVar("var").get_vector(1);

            local attackInfo = sq_GetCustomAttackInfo(obj, 153);
            sq_SetCurrentAttackInfo(obj, attackInfo);
            attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackBonusRate(attackInfo, mulitHit);
            obj.setTimeEvent(0,(53 * 53) / mulitCount, mulitCount , false );
            return true;

        }else if (flagIndex == 2)
        {
            sq_flashScreen(obj,60,60,240,204, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;
        }else if (flagIndex == 3)
        {
            sq_flashScreen(obj,0,0,180,153, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;
        }else if (flagIndex == 4)
        {

            return true;
        }else if (flagIndex == 5)
        {
            sq_flashScreen(obj,0,0,120,153, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;
        }else if (flagIndex == 6)
        {

            return true;
        }else if (flagIndex == 7)
        {
            sq_flashScreen(obj,0,0,120,153, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;
        }else if (flagIndex == 8)
        {
            sq_flashScreen(obj,0,60,180,153, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;
        }else if (flagIndex == 9)
        {
            sq_flashScreen(obj,60,60,300,204, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;
        }else if (flagIndex == 10)
        {

            obj.sq_PlaySound("FATAL_FLOWER_EXP");
            obj.getVar("var").set_vector(3,1);
            local explosion = obj.getVar("var").get_vector(2);

            local attackInfo = sq_GetCustomAttackInfo(obj, 154);
            sq_SetCurrentAttackInfo(obj, attackInfo);
            attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackBonusRate(attackInfo, explosion);
            sq_SetMyShake(obj, 7, 600);
            obj.setTimeEvent(0,1, 1 , false );
            return true;
        }

    }else if (id == 181)
    {
        if (flagIndex == 1)
        {
            sq_SetMyShake(obj, 5, 300);
            sq_flashScreen(obj,0,100,0,102, sq_RGB(211,211,211), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;
        }else if (flagIndex == 2)
        {
            sq_flashScreen(obj,0,200,100,153, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;
        }
    }else if (id == 180)
    {
        if (flagIndex == 1)
        {

            return true;
        }else if (flagIndex == 2)
        {
            sq_SetMyShake(obj, 1, 1000);
            local hitCount = obj.getVar("var").get_vector(1);
            obj.setTimeEvent(0,1000 / hitCount,hitCount,false);
            return true;
        }else if (flagIndex == 3)
        {
            obj.setTimeEvent(0,9999,1,false);
            local attackBonusRate = obj.getVar("var").get_vector(0);
            local attackInfo = sq_GetCustomAttackInfo(obj, 151);
            sq_SetCurrentAttackInfo(obj, attackInfo);
            attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
            sq_SetMyShake(obj, 8, 800);
            sq_flashScreen(obj,300,0,0,153, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            obj.resetHitObjectList();
            return true;
        }
    }else if (id == 175)
    {
        if (flagIndex == 2)
        {
            obj.resetHitObjectList();
            return true;
        }
    }else if (id == 161)
    {
        if (flagIndex == 1)
        {
            local maxNum = obj.getVar("var").get_vector(0);
            local curNum = obj.getVar("var").get_vector(1);

            if (curNum < maxNum && curNum != -1)
            {

                local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 90);
                sq_BinaryStartWrite();
                sq_BinaryWriteDword( 0 );
                sq_BinaryWriteDword(161 );
                sq_BinaryWriteDword( maxNum );
                sq_BinaryWriteDword( curNum + 1 );
                sq_SendCreatePassiveObjectPacketPos(obj, 24357, 0, posX, obj.getYPos(),0);


            }
        }else if (flagIndex == 2)
        {

            local ani = obj.getVar().GetAnimationMap("AtExectionHazeLoopEffect", 
            "passiveobject/zrr_skill/atswordman/animation/atexecution/haze_loop_haze2.ani"); 
            obj.setCurrentAnimation(ani );
            obj.getVar("state").set_vector(0,1);
        }
        return true;
    }

    if (id == 143)
    {
        local state = obj.getVar("state").get_vector(0);
        local objID = obj.getVar("atk").get_vector(1);
        local activeObj = sq_GetObjectByObjectId(obj, objID);

        if (flagIndex == 1)
        {
            sq_SendHitObjectPacket(obj,activeObj,0,0,0);
            return true;
        }else if (flagIndex == 2)
        {
        }else if (flagIndex == 3)
        {
            if (state == 0)
            {
                local ani = obj.getVar().GetAnimationMap("SpritMagicWoodHoldAnimationContinue", 
                "passiveobject/zrr_skill/newmage/animation/hex/hex_doll1234hit_nail_00.ani"); 
                obj.setCurrentAnimation(ani);
                obj.getVar("state").set_vector(0,1);
            }else if (state == 1)
            {
                local ani = obj.getVar().GetAnimationMap("SpritMagicWoodHoldAnimationEnd", 
                "passiveobject/zrr_skill/newmage/animation/hex/hex_dollhitend_nail_00.ani"); 
                obj.setCurrentAnimation(ani);
                obj.getVar("state").set_vector(0,2);
            }else if (state == 2)
            {
                sq_SendDestroyPacketPassiveObject(obj);
            }
            return true;
        }else if (flagIndex == 4)
        {

            return true;
        }else if (flagIndex == 5)
        {
            createSpritMagicHitEndLastTarget(obj);
            CNSquirrelAppendage.sq_RemoveAppendage(activeObj, "character/mage/new_spritmagic/ap_spritmagic.nut");		
            local parObj = obj.getVar("obj").get_obj_vector(0);
            if (parObj)
                parObj.setValid(false);

            local attackBonusRate = obj.getVar("atk").get_vector(2);
            local attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
            sq_SendHitObjectPacket(obj,activeObj,0,0,0);



            return true;
        }else if (flagIndex == 6)
        {

        }




    }


    if (id == 142)
    {

        if (flagIndex == 1)
        {
            local objID = obj.getVar("atk").get_vector(1);

            local activeObj = sq_GetObjectByObjectId(obj, objID);

            if (!CNSquirrelAppendage.sq_IsAppendAppendage(activeObj, "character/mage/new_spritmagic/ap_spritmagic.nut"))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(activeObj, 
                obj, SKILL_SPRLITMAGIC, false, "character/mage/new_spritmagic/ap_spritmagic.nut", true);				 

                sq_HoldAndDelayDie(activeObj, obj, true, false, false, 0, 0, ENUM_DIRECTION_DOWN , masterAppendage);

            }
            return true;

        }else if (flagIndex == 2)
        {
            local objID = obj.getVar("atk").get_vector(1);
            local activeObj = sq_GetObjectByObjectId(obj, objID);
            createSpritMagicChangeEffect(activeObj,getSpritMagicTargetVarByObject(activeObj) );
            return true;
        }else if (flagIndex == 3)
        {
            local objID = obj.getVar("atk").get_vector(1);


            sq_BinaryStartWrite();
            sq_BinaryWriteDword( obj.getVar("atk").get_vector(0) );
            sq_BinaryWriteDword(143 );
            sq_BinaryWriteDword( obj.getVar("atk").get_vector(1) );
            sq_BinaryWriteDword( obj.getVar("atk").get_vector(2) );
            sq_SendCreatePassiveObjectPacketPos(obj, 24357, 0, 0, 0,0);


            return true;
        }
    }
    if (id == 141)
    {
        local hitCount = obj.getVar("var").get_vector(0);
            obj.setTimeEvent(0,360 / hitCount,hitCount,true);
        return true;
    }

    if (id == 140)
    {
        local hitCount = obj.getVar("var").get_vector(0);
            obj.setTimeEvent(0,5 * 72 / hitCount,hitCount,true);
        return true;
    }

    if (id == 37)
    {
        if (flagIndex == 12)
        {
            if (!obj.isMyControlObject() )
                return false;
            sq_SetMyShake(obj, 5, 200);
            sq_flashScreen(obj,0,0,180,178, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;
        }else if (flagIndex == 13)
        {
            if (!obj.isMyControlObject() )
                return false;
            sq_SetMyShake(obj, 7, 300);
            return true;
        }else if (flagIndex == 14)
        {
            obj.resetHitObjectList();
            return true;

        }
    }

    if (id == 138)
    {
        if (!obj.isMyControlObject() )
            return false;

        if (flagIndex == 1)
        {
            sq_flashScreen(obj,0,0,180,178, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;
        }else if (flagIndex == 2)
        {

            setGulttonyAttartionArea(obj);
            obj.setTimeEvent(0,obj.getVar("var").get_vector(1),0,true);
            obj.setTimeEvent(1,10,0,true);
            sq_SetMyShake(obj, 2, 650);
            return true;
        }else if (flagIndex == 3)
        {
            obj.getVar("dama").clear_obj_vector();
            obj.setTimeEvent(0,obj.getVar("var").get_vector(1),1,false);
            obj.setTimeEvent(1,10,1,false);
            return true;
        }else if (flagIndex == 4)
        {
            sq_SetMyShake(obj, 7, 350);
            return true;
        }
    }

    if (id == 135)
    {
        if (flagIndex == 1)
        {
            sq_SetMyShake(obj,5,100);
            return true;
        }
    }
    if (id == 131)
    {
        if (flagIndex == 1)
        {
            sq_flashScreen(obj,0,120,800,204, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            sq_SetMyShake(obj,7,320);
            return true;
        }else if (flagIndex == 999)
        {
            obj.getVar("state").set_vector(0,1);
            local attackBonusRate = obj.getVar("var").get_vector(1);
            local ani = obj.getVar().GetAnimationMap("sestoElementoExplosion", 
                        "passiveobject/zrr_skill/newmage/animation/sestoelemento/explosion_main.ani"); 
            obj.setCurrentAnimation(ani);

            local attackInfo = sq_GetCustomAttackInfo(obj, 111);
            sq_SetCurrentAttackInfo(obj, attackInfo);
            attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
            obj.getVar("dama").clear_obj_vector();
            return true;
        }else if (flagIndex == 1000)
        {
            sq_SendDestroyPacketPassiveObject(obj);
            return true;
        }
    }

    if (id == 130)
    {
        if (flagIndex == 1)
        {
            sq_flashScreen(obj,300,0,300,127, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;
        }else if (flagIndex == 2)
        {
            sq_SetMyShake(obj,8,200);
            return true;
        }else if (flagIndex == 3)
        {
            local pooledObj = obj.getVar("effectFloor2").get_obj_vector(0);
            if (pooledObj)
                pooledObj.setValid(false);
            createCrystalOfOverMindOnEndGroundEffect(obj);
            sq_SendDestroyPacketPassiveObject(obj);
            return true;
        }
    }
    if (id == 129)
    {
        if (flagIndex == 1)
        {
            sq_flashScreen(obj,720,0,200,51, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;
        }else if (flagIndex == 2)
        {
            sq_SetMyShake(obj,8,250);
            return true;
        }
    }

    if (id == 126)
    {
        if (flagIndex == 1000)
        {
            local state = obj.getVar("state").get_vector(0);
            if (state == 0)
            {
                obj.getVar("state").set_vector(0,1);
                onSetPassiveObjectSummonZigState(obj,1);
            }else if (state == 1)
            {
                obj.getVar("state").set_vector(0,2);
                onSetPassiveObjectSummonZigState(obj,2);
            }else if (state == 2)
            {
                onSetPassiveObjectSummonZigState(obj,3);
            }
            return true;
        }else if (flagIndex == 2)
        {
            createSummonZigGrabBoomEffect(obj);
            return true;
        }else if (flagIndex == 10)
        {
//set flag 10 flash 640 80 0 204 0 0 0 bottom
            sq_flashScreen(obj,640,80,0,204, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            return true;
        }
    }


    if (id == 124)
    {
//        obj.getVar("var").clear_vector();
//        obj.getVar("var").push_vector(attackBonusRate);
//        obj.getVar("var").push_vector(Maxcount);
//        obj.getVar("var").push_vector(CurrentCount );
//        obj.getVar("var").push_vector(dist);
//        obj.getVar("var").push_vector(size );

        local atk = obj.getVar("var").get_vector(0);
        local maxCount = obj.getVar("var").get_vector(1);
        local CurrentCount = obj.getVar("var").get_vector(2);
        local dist = obj.getVar("var").get_vector(3);
        local size = obj.getVar("var").get_vector(4);
        local increaseSize = obj.getVar("var").get_vector(5);

        local burnProc = obj.getVar("var").get_vector(6);
        local burnLevel = obj.getVar("var").get_vector(7);
        local burnTime = obj.getVar("var").get_vector(8);
        local burnRate = obj.getVar("var").get_vector(9);

        if (maxCount > CurrentCount)
        {
            if (!obj.isMyControlObject() )
                return false;

            local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), dist);
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(atk );	// attackBonusRate
            sq_BinaryWriteDword(124);
            sq_BinaryWriteDword(maxCount);
            sq_BinaryWriteDword(CurrentCount + 1);
            sq_BinaryWriteDword(dist);
            sq_BinaryWriteDword(size + increaseSize * CurrentCount );
            sq_BinaryWriteDword(increaseSize);
            sq_BinaryWriteDword(burnProc);
            sq_BinaryWriteDword(burnLevel);
            sq_BinaryWriteDword(burnTime);
            sq_BinaryWriteDword(burnRate);
            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, posX , obj.getYPos() , obj.getZPos());
            createFireWaveFlameGroundNormal(obj,size);
            sq_SetMyShake(obj,5,200);
            return true;
        }

    }
    if (id == 122)
    {
        if (flagIndex == 3 )
        {
            sq_SetMyShake(obj,10,400);
            sq_flashScreen(obj,40,80,520,127, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        }
        return true;
    }
    if (id == 121)
    {
        if (flagIndex == 1 )
        {
            sq_SetMyShake(obj,1,1320);

        }else if (flagIndex == 2)
        {
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(obj.getVar().get_vector(0) );	// attackBonusRate
            sq_BinaryWriteDword(122);
            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos() , obj.getYPos() , obj.getZPos());
        }
        return true;
    }

    if (id == 118)
    {
        if (flagIndex == 1)
        {
            createInvisibleBladeSwordCut_Passiveobject_IceSword(obj,0,1,0,100,100,0);
            createInvisibleBladeSwordCut_Passiveobject_Red_Block(obj,0,1,0,100,100,0);
            return true;

        }else if (flagIndex == 2)
        {
            createInvisibleBladeSwordCut_Passiveobject_IceSword_2(obj,0,2,200,200,200,0);
            createInvisibleBladeSwordCut_Passiveobject_IceSword_1(obj,0,2,200,200,200,-39);
            return true;
        }else if (flagIndex == 3)
        {
            createInvisibleBladeSwordCut_Passiveobject_IceSword_3(obj,0,1,-50,100,100,0);
            createInvisibleBladeSwordCut_HitEffect_IceSword(obj,-100,2,200,100,100,0);
            return true;
        }else if (flagIndex == 4)
        {
            createInvisibleBladeSwordCut_Passiveobject_IceSword_1(obj,0,2,129,200,200,-17);
            createInvisibleBladeSwordCut_HitEffect_IceSword_1(obj,200,2,0,100,100,0);
            return true;
        }else if (flagIndex == 5)
        {
            createInvisibleBladeSwordCut_Passiveobject_Red_Line(obj,-75,-1,122,150,150,-104);

            return true;
        }else if (flagIndex == 6)
        {

            createInvisibleBladeSwordCut_Passiveobject_Red_Line(obj,0,-1,122,150,150,17);

            return true;
        }else if (flagIndex == 7)
        {

            createInvisibleBladeSwordCut_Passiveobject_Red_Line(obj,152,-1,122,150,150,-50);
            return true;
        }else if (flagIndex == 8)
        {
            local z = 100;
            local size = 100;

            createInvisibleBladeSwordCut_Passiveobject_Shock_0(obj,0,0,z,size,size,-78);
            createInvisibleBladeSwordCut_Passiveobject_Shock_1(obj,0,0,z,size,size,-157);
            createInvisibleBladeSwordCut_Passiveobject_Shock_2(obj,0,0,z,size,size,-235);
            createInvisibleBladeSwordCut_Passiveobject_Shock_3(obj,0,0,z,size,size,-314);

            createInvisibleBladeSwordCut_Passiveobject_Shock_0(obj,0,0,z,size,size,-392);
            createInvisibleBladeSwordCut_Passiveobject_Shock_1(obj,0,0,z,size,size,-471);
            createInvisibleBladeSwordCut_Passiveobject_Shock_2(obj,0,0,z,size,size,-549);
            createInvisibleBladeSwordCut_Passiveobject_Shock_3(obj,0,0,z,size,size,-628);


            createInvisibleBladeSwordCut_Passiveobject_Shock_0(obj,0,0,z,size,size,78);
            createInvisibleBladeSwordCut_Passiveobject_Shock_1(obj,0,0,z,size,size,157);
            createInvisibleBladeSwordCut_Passiveobject_Shock_2(obj,0,0,z,size,size,235);
            createInvisibleBladeSwordCut_Passiveobject_Shock_3(obj,0,0,z,size,size,314);

            createInvisibleBladeSwordCut_Passiveobject_Shock_0(obj,0,0,z,size,size,392);
            createInvisibleBladeSwordCut_Passiveobject_Shock_1(obj,0,0,z,size,size,471);
            createInvisibleBladeSwordCut_Passiveobject_Shock_2(obj,0,0,z,size,size,549);
            createInvisibleBladeSwordCut_Passiveobject_Shock_3(obj,0,0,z,size,size,628);
            createInvisibleBladeSwordCut_Passiveobject_LastShock(obj,0,1,z,size,size,0);

//            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos() , obj.getYPos() , obj.getZPos());
            return true;
        }else if (flagIndex == 9)
        {
            createInvisibleBladeSwordCut_Passiveobject_LastLightEffect(obj,50,2,100,75,75,104);
            createInvisibleBladeSwordCut_Passiveobject_LastLightEffect(obj,32,2,101,86,76,130);

            createInvisibleBladeSwordCut_Passiveobject_LastLightEffect(obj,-152,2,73,60,62,-52);
            createInvisibleBladeSwordCut_Passiveobject_LastLightEffect(obj,-163,2,72,50,42,-32);
            createInvisibleBladeSwordCut_Passiveobject_LastLightEffect(obj,-178,2,71,75,75,-22);

            createInvisibleBladeSwordCut_Passiveobject_LastLightEffect(obj,-123,2,7,70,72,52);
            createInvisibleBladeSwordCut_Passiveobject_LastLightEffect(obj,-102,2,5,75,70,89);

            createInvisibleBladeSwordCut_Passiveobject_LastLightEffect(obj,102,2,5,75,70,-52);

            createInvisibleBladeSwordCut_Passiveobject_LastLightEffect(obj,112,2,32,75,70,-38);
            createInvisibleBladeSwordCut_Passiveobject_LastLightEffect(obj,122,2,42,75,70,-18);

            createInvisibleBladeSwordCut_HitEffect_IceSword_1(obj,0,3,100,125,125,0);
            return true;

        }else if (flagIndex == 10)
        {

            createInvisibleBladeSwordCut_Passiveobject_Last_Shock_0(obj,0,2,150,200,200,0);
            createInvisibleBladeSwordCut_Passiveobject_LastLightEffect(obj,10,2,250,200,200,-15);



            createInvisibleBladeSwordCut_Passiveobject_LastFireLine(obj,-300,2,44,300,40,104);
            createInvisibleBladeSwordCut_Passiveobject_LastFireLine(obj,-300,2,44,150,150,148);

            return true;
        }

    }

    if (id == 111)
    {
        if(obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").set_vector(0,1);

            createAtgCrowLingmist(obj);
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(0 );	// attackBonusRate
            sq_BinaryWriteDword(112);
            sq_BinaryWriteDword(obj.getVar().get_vector(0));
            sq_BinaryWriteDword(obj.getVar().get_vector(1));
            sq_BinaryWriteDword(obj.getVar().get_vector(2));

            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos() , obj.getYPos() , obj.getZPos());

        }
    }

    if (id == 108)
    {
        if(obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").set_vector(0,1);


            sq_BinaryStartWrite();
            sq_BinaryWriteDword(obj.getVar("va").get_vector(0) );	// attackBonusRate
            sq_BinaryWriteDword(109);
            sq_BinaryWriteDword(obj.getVar("va").get_vector(1));
            sq_BinaryWriteDword(obj.getVar("va").get_vector(2));
            sq_BinaryWriteDword(obj.getVar("va").get_vector(3));
            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos() , obj.getYPos() , obj.getZPos());


        }
    }
    if (id == 103)
    {
        if(flagIndex == 1 && obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").set_vector(0,1);
            obj.resetHitObjectList();
        }else if(flagIndex == 2 && obj.getVar("flag").get_vector(1) == 0)
        {
            obj.getVar("flag").set_vector(1,1);
            obj.resetHitObjectList();
        }
    }
    if (id == 100)
    {
        if (flagIndex != 1000)
        {
            if (obj.getVar("flag").get_vector(flagIndex) == 0)
            {
                obj.getVar("flag").set_vector(flagIndex,1);
                local object = obj.getVar("obj").get_obj_vector(0);

                local mage = obj.getTopCharacter();
                mage = sq_ObjectToSQRCharacter(mage);	

                if (flagIndex == 0)
                {
                    sq_SendHitObjectPacket(obj,object,0,0,object.getObjectHeight()/2 );

                    if (!CNSquirrelAppendage.sq_IsAppendAppendage(object, "character/atmage/bloodsong/ap_bloodsong.nut"))
                    {
                        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(object, mage, SKILL_BLOODSONG, false,
                        "character/atmage/bloodsong/ap_bloodsong.nut", true);				 
                        sq_HoldAndDelayDie(object, obj, false, true, true, 0, 0, ENUM_DIRECTION_DOWN , masterAppendage);
                    }

                    sq_EffectLayerAppendage(object,sq_RGB(0,0,0),255,0,4000,0);	
//                    sq_SetMyShake(obj, 5, 25);
                    createTepesHitEffect1(obj,damager);
                    createTepesHitEffect2(obj,damager);


                }else if (flagIndex == 1)
                {
                    sq_SendHitObjectPacket(obj,object,0,0,object.getObjectHeight()/2 );
                    obj.getVar("hei").set_vector(0,mage.sq_GetIntData(SKILL_BLOODSONG, 18) );
//                    sq_SetMyShake(obj, 4, 25);
                    createTepesHitEffect1(obj,object);
                    createTepesHitEffect2(obj,object);
                }else if (flagIndex == 2)
                {
                    sq_SendHitObjectPacket(obj,object,0,0,object.getObjectHeight()/2 );
                    obj.getVar("hei").set_vector(0,mage.sq_GetIntData(SKILL_BLOODSONG, 19));
//                    sq_SetMyShake(obj, 4, 20);
                    createTepesHitEffect1(obj,object);
                    createTepesHitEffect2(obj,object);
                }else if (flagIndex == 3)
                {
                    sq_SendHitObjectPacket(obj,object,0,0,object.getObjectHeight()/2 );
                    obj.getVar("hei").set_vector(0,mage.sq_GetIntData(SKILL_BLOODSONG, 20));
//                    sq_SetMyShake(obj,4, 20);
                    createTepesHitEffect1(obj,object);
                    createTepesHitEffect2(obj,object);
                }else if (flagIndex == 4)
                {
                    sq_SendHitObjectPacket(obj,object,0,0,object.getObjectHeight()/2 );
                    obj.getVar("hei").set_vector(0,mage.sq_GetIntData(SKILL_BLOODSONG, 21));
//                    sq_SetMyShake(obj, 4, 20);
                    createTepesHitEffect1(obj,object);
                    createTepesHitEffect2(obj,object);

                }else if (flagIndex == 5)
                {
                    sq_SendHitObjectPacket(obj,object,0,0,object.getObjectHeight()/2 );
                    obj.getVar("hei").set_vector(0,mage.sq_GetIntData(SKILL_BLOODSONG, 22));
//                    sq_SetMyShake(obj, 4, 20);
                    createTepesHitEffect1(obj,object);
                    createTepesHitEffect2(obj,object);
                }
            }
        }else{

            if (obj.getVar("flag").get_vector(6) == 0)
            {
                obj.getVar("flag").set_vector(6,1);
                obj.setTimeEvent(1,obj.getVar("time").get_vector(0),0,true);
            }
        }
    }
    if (id == 66 && obj.getVar("flag").get_vector(0) == 0)
    {
//        obj.getVar("value").push_vector(attackBonusRate);
//        obj.getVar("value").push_vector(currNum);
//        obj.getVar("value").push_vector(len);
//        obj.getVar("value").push_vector(maxNum);
//        obj.getVar("value").push_vector(bloodProc);
//        obj.getVar("value").push_vector(bloodleve);
//        obj.getVar("value").push_vector(bloodtime);
//        obj.getVar("value").push_vector(bloodRate);

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(1);

        if (obj.getVar("value").get_vector(1) < obj.getVar("value").get_vector(3) )
        {
            local distX = sq_GetDistancePos(obj.getXPos() , obj.getDirection(), obj.getVar("value").get_vector(2) );
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(obj.getVar("value").get_vector(0) );	// attackBonusRate
            sq_BinaryWriteDword(66);
            sq_BinaryWriteDword(obj.getVar("value").get_vector(1) + 1);	
            sq_BinaryWriteDword(obj.getVar("value").get_vector(2));	
            sq_BinaryWriteDword(obj.getVar("value").get_vector(3));
            sq_BinaryWriteDword(obj.getVar("value").get_vector(4));	
            sq_BinaryWriteDword(obj.getVar("value").get_vector(5));	
            sq_BinaryWriteDword(obj.getVar("value").get_vector(6));		
            sq_BinaryWriteDword(obj.getVar("value").get_vector(7));	
            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, distX , obj.getYPos() , obj.getZPos());
        }





    }

    if (id == 65 && obj.getVar("flag").get_vector(flagIndex) == 0)
    {
        if (flagIndex == 0)
        {
            obj.getVar("flag").set_vector(flagIndex,1);
            obj.resetHitObjectList();
            local attackInfo = sq_GetCustomAttackInfo(obj, 38);
            sq_SetCurrentAttackInfo(obj, attackInfo);
            local atk = obj.getVar("atk2").get_vector(0);
            attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackPower(attackInfo, atk);
        }else if (flagIndex == 1)
        {
            obj.getVar("flag").set_vector(flagIndex,1);
            obj.resetHitObjectList();
        }
    }

    if (id == 59)
    {
        if (flagIndex == 1)
        {
            obj.getVar("isSum").set_vector(0,1);
        }else if (flagIndex == 2){
            obj.getVar("isSum").set_vector(0,0);
        }
    }

    if (id == 33 && flagIndex == 1 && obj.getVar("flag").get_vector(0) == 0 )
    {
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(1);
        obj.setTimeEvent(0,obj.getVar().get_vector(0),0,false);		
        obj.setTimeEvent(1,obj.getVar().get_vector(1),0,true);		

        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();

        if (objectsSize > 0)
        {
            for(local i=0;i<objectsSize;++i)
            {
                local damager = var.get_obj_vector(i);

                if ( !CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/newswordman/highlightwave/ap_highlightwave.nut") )
                {
                    local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_HIGHLIGHTWAVE, false, 
                    "character/newswordman/highlightwave/ap_highlightwave.nut", true);				 

                    if (i + 1 < objectsSize)
                    {
                        local damager2 = var.get_obj_vector(i + 1);
                        if (damager2)
                        {

                            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, damager2, SKILL_HIGHLIGHTWAVE, false, 
                            "character/newswordman/highlightwave/ap_highlightwave_line.nut", true);				 

                        }

                    }
                }
            }
        }else{
            sq_SendDestroyPacketPassiveObject(obj);
        }

    }

    if (id == 2 && obj.sq_IsMyControlObject() && flagIndex == 1 )
    {
        sq_SendCreatePassiveObjectPacketPos(obj,12140, 0, obj.getXPos(), obj.getYPos() + 1, obj.getZPos());
        sq_SendCreatePassiveObjectPacketPos(obj,12138, 0, obj.getXPos(), obj.getYPos() + 1, obj.getZPos());

        sq_SetMyShake(obj, 16, 240);
    }

    if (id == 15)
    {
        if (flagIndex == 1 )
        {

            if (obj.getVar("flag").get_vector(0) <= 0)
            {
                local flag = obj.getVar("flag").get_vector(0);
                obj.getVar("flag").clear_vector();
                obj.getVar("flag").push_vector(flag+1);

                local attack = obj.getVar("attackValue").get_vector(0);
                local attackInfo = sq_GetCurrentAttackInfo(obj);
                sq_SetCurrentAttackBonusRate(attackInfo, attack);

                obj.resetHitObjectList();
            }

        }
    }


    if (id == 4)
    {
        if (flagIndex == 1 )
        {
            sq_SetMyShake(obj,3,100);

        }else if (flagIndex == 2)
        {
            sq_SetMyShake(obj,1,30);
            
        }else if (flagIndex == 3)
        {
            sq_SetMyShake(obj,10,500);
            createPhantomBaleFinalyBack(obj,0,-2,0);
        }else if (flagIndex == 4)
        {
            sq_SetMyShake(obj,10,100);
        }else if (flagIndex == 999)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }else if (flagIndex == 998)
        {
            createPhantomBaleFinalySplashBase(obj,0,1,0);
        }

        return true;
    }
    return true;

//                            sq_SetMyShake(obj,5,100);

}