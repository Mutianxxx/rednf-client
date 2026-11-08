
/*
function getCustomHitEffectFileName_po_bloodcut(obj, isAttachOnDamager)
{
    local id = obj.getVar("id").get_vector(0 );
    if (id == 223)
    {
        local var = sq_getRandom(0,4);
        if (var == 0)
            return "passiveobject/zrr_skill/gunblader/animation/hitmanhit/hita.ani";
        else if (var == 1)
            return "passiveobject/zrr_skill/gunblader/animation/hitmanhit/hita.ani";
        else if (var == 2)
            return "passiveobject/zrr_skill/gunblader/animation/hitmanhit/hita.ani";
        else if (var == 3)
            return "passiveobject/zrr_skill/gunblader/animation/hitmanhit/hitd.ani";
    }
}
*/






function procAppendEtc_po_bloodcut(obj)
{
    local id = obj.getVar("id").get_vector(0 );

    if (id == 223 || id == 224)
    {

        local flyT = obj.getVar("pos").get_vector(6);

        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        if (currentT < flyT)
        {
            local startX = obj.getVar("pos").get_vector(0);
            local startY = obj.getVar("pos").get_vector(1);
            local startZ = obj.getVar("pos").get_vector(2);

            local lastX = obj.getVar("pos").get_vector(3);
            local lastY = obj.getVar("pos").get_vector(4);
            local lastZ = obj.getVar("pos").get_vector(5);

            local x = sq_GetUniformVelocity(startX, lastX, currentT , flyT);
            local y = sq_GetUniformVelocity(startY, lastY, currentT , flyT);
            local z = sq_GetUniformVelocity(startZ, lastZ, currentT , flyT);
            if (z >= 0)
                obj.setCurrentPos(x,y,z);
            else
            {
                sq_SendDestroyPacketPassiveObject(obj);
            }
        }else
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 219)
    {
        onProcBellacre_AdventObj(obj);
    }else if (id == 218)
    {

        local startX = obj.getVar("var").get_vector(0);
        local startY = obj.getVar("var").get_vector(1);
        local startZ = obj.getVar("var").get_vector(2);

        local maxD = obj.getVar("var").get_vector(3);
        local minS = obj.getVar("var").get_vector(4);
        local maxS = obj.getVar("var").get_vector(5);
        local maxT = obj.getVar("var").get_vector(6);
        local z = obj.getVar("var").get_vector(7);
        local y = obj.getVar("var").get_vector(9);
        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        if (currentT > maxT)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }else
        {
            local v = sq_GetUniformVelocity(0, maxD, currentT , maxT);
            local vy = sq_GetUniformVelocity(0, y, currentT , maxT);
            local vz = sq_GetUniformVelocity(0, z, currentT , maxT);
            local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
            sq_setCurrentAxisPos(obj, 0, dstX);
            sq_setCurrentAxisPos(obj, 1, startY + vy);
            sq_setCurrentAxisPos(obj, 2, startZ + vz);

            local size = sq_GetUniformVelocity( minS , maxS , currentT , maxT);

            local currentAni = sq_GetCurrentAnimation(obj);

            local sizeRate = size.tofloat()/100.0;
            currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
            currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
            sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);

        }


    }else if (id == 196)
    {
        local state = obj.getVar("state").get_vector(0);
        if (state == 0)
        {
            local fuckObj = obj.getVar("fuckObj").get_obj_vector(0);
            if (fuckObj)
            {
                obj.setCurrentPos(fuckObj.getXPos(),fuckObj.getYPos() + 1,fuckObj.getZPos());

            }else{

                sq_SendDestroyPacketPassiveObject(obj);

            }
        }else if (state == 1)
        {
            local currentAni = sq_GetCurrentAnimation(obj);
            local currentT = sq_GetCurrentTime(currentAni);
            if (currentT > 1000)
            {

                sq_SendDestroyPacketPassiveObject(obj);


            }
        }
    }else if (id == 193)
    {
        onProcMoveGodWindTorndo(obj);
    }else if (id == 189)
    {
        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        if (currentT > 50)
        {
            local object = obj.getVar("dama").get_obj_vector(0);

            if (object)
                sq_SendHitObjectPacketWithNoStuck(obj,object,0,0, object.getObjectHeight()/2 );	

            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 188)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        local mageState = mage.sq_GetState();
        if (!mage || mageState != 43  )
        {
            sq_SendDestroyPacketPassiveObject(obj);	
        }
    }else if (id == 187)
    {

        if (obj.getVar("state").get_vector(0) == 0)
        {

            local currentAni = sq_GetCurrentAnimation(obj);
            local currentT = sq_GetCurrentTime(currentAni);
            local startX = obj.getVar("moveVar").get_vector(0);
            local moveD = obj.getVar("moveVar").get_vector(1);
            local moveT = obj.getVar("moveVar").get_vector(2);

            if (currentT < moveT)
            {
                local v = sq_GetUniformVelocity(0, moveD, currentT , moveT);
                local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
                sq_setCurrentAxisPos(obj, 0, dstX);

            }else{

                obj.getVar("state").set_vector(0,1);
                local ani = obj.getVar().GetAnimationMap("BigJangExplosionBody", 
                "passiveobject/zrr_skill/atswordman/animation/atbigjang/normal_bomb_d.ani"); 
                obj.setCurrentAnimation(ani );

//////////////////////////////////////////////
		local mage = obj.getTopCharacter();
		mage = sq_ObjectToSQRCharacter(mage);
		local sizeRate = mage.sq_GetIntData(SKILL_BIG_JANG,6);
		local imageRate = sizeRate.tofloat() / 100.0;
		ani.setImageRateFromOriginal(imageRate, imageRate);
		ani.setAutoLayerWorkAnimationAddSizeRate(imageRate);
		sq_SetAttackBoundingBoxSizeRate(ani, imageRate, imageRate, imageRate);
//////////////////////////////////////////////

                local attackInfo = sq_GetCustomAttackInfo(obj, 159);
                sq_SetCurrentAttackInfo(obj, attackInfo);
                attackInfo = sq_GetCurrentAttackInfo(obj);
                sq_SetCurrentAttackBonusRate(attackInfo, obj.getVar("etcVar").get_vector(0) );
                sq_SetMyShake(obj, 6, 150);
                sq_flashScreen(obj,0,70,50,51, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

            }
        }else if (obj.getVar("state").get_vector(0) == 1)
        {
            local currentAni = sq_GetCurrentAnimation(obj);
            local currentT = sq_GetCurrentTime(currentAni);
            if (currentT > 700)
                sq_SendDestroyPacketPassiveObject(obj);	
        }

    }else if (id == 185)
    {
        local state = obj.getVar("state").get_vector(0);
        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        if (state == 1)
        {
            if (obj && currentT >= obj.getVar("etcVar").get_vector(1) )
            {
                
                local mage = obj.getTopCharacter();
                mage = sq_ObjectToSQRCharacter(mage);	
                if (mage)
                {
                    local horizenSlashObj = getMulitingBloodCutObjectByID(mage,184);
                    if (horizenSlashObj)
                    {

                        onSetStatePassiveobject_ZweivolTageExHorizenSlash(horizenSlashObj,2);
                        onSetStatePassiveobject_ZweivolTageExVertexSlash(obj,2);
                    }

                }
            }
        }
    }else if (id == 184)
    {
        local state = obj.getVar("state").get_vector(0);
        if (state == 1)
        {
            local currentAni = sq_GetCurrentAnimation(obj);
            local currentT = sq_GetCurrentTime(currentAni);
            if (currentT >= 15000)
                sq_SendDestroyPacketPassiveObject(obj);	
        }
    }else if (id == 183)
    {
        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        if (currentT > 2000)
        {
            local atk = obj.getVar("num").get_vector(0);
            local attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackBonusRate(attackInfo, atk );

            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();

            if (objectsSize <= 0)
            {
                
                sq_SendDestroyPacketPassiveObject(obj);	
                return false;
            }
            
            obj.sq_PlaySound("KEIGA_ATK");
            sq_flashScreen(obj,0,0,160,100, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
            for(local i=0;i<objectsSize;++i)
            {
                local damager = var.get_obj_vector(i);
                if (damager)
                {
                    createGhostStepSlash_SlashEffect(damager);
                    sq_SendHitObjectPacket(obj,damager,0,0, damager.getObjectHeight()/2 );
                }
            }

            sq_SendDestroyPacketPassiveObject(obj);	

        }

    }else if (id == 175)
    {
        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);

        local frmIndex = sq_GetAnimationFrameIndex(currentAni);
        local startFrameIndex = 12;
        local endFrameIndex = 21;

        if (frmIndex >= startFrameIndex && frmIndex <= endFrameIndex)
        {
            local startX = obj.getVar("dis").get_vector(1);
            local maxD = obj.getVar("dis").get_vector(0);

            currentT = currentT - currentAni.getDelaySum(0,startFrameIndex);
            local maxT = currentAni.getDelaySum(startFrameIndex,endFrameIndex);

            if (currentT < maxT)
            {

                local v = sq_GetAccel(0, maxD, currentT,maxT, true);
                local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
                sq_setCurrentAxisPos(obj, 0, dstX);
            }
        }



    }else if (id == 170)
    {

        setCoalBanPassiveobjectMoveEffect(obj);

    }else if (id == 161)
    {
        local state = obj.getVar("state").get_vector(0);
        if (state == 1)
        {
            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	

            local mageState = mage.sq_GetState();

            if (mageState != STATE_AT_SWORDMAN_EXECUTION)
            {
                createExecutionFrontDestroyEffect(obj);
                sq_SendDestroyPacketPassiveObject(obj);	

            }

        }
    }else if (id == 160)
    {

        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        local maxT = obj.getVar("moveInitVar").get_vector(0);
        if (maxT < currentT)
        {

            sq_SendDestroyPacketPassiveObject(obj);	
        }else{
            setSightingShootPooledObjFollowParentObj(obj);
            local startX = obj.getVar("moveInitVar").get_vector(1);
            local startY = obj.getVar("moveInitVar").get_vector(2);
            local startZ = obj.getVar("moveInitVar").get_vector(3);

            local offsetX = obj.getVar("moveVar").get_vector(0);
            local offsetY = obj.getVar("moveVar").get_vector(1);
            local offsetZ = obj.getVar("moveVar").get_vector(2);

            local vx = sq_GetUniformVelocity(startX, offsetX, currentT, maxT);
            local vy = sq_GetUniformVelocity(startY, offsetY, currentT, maxT);
            local vz = sq_GetUniformVelocity(startZ, offsetZ, currentT, maxT);

//            local dstX = sq_GetDistancePos(startX, obj.getDirection(), vx);
            sq_setCurrentAxisPos(obj, 0, vx);
            sq_setCurrentAxisPos(obj, 1, vy);
            sq_setCurrentAxisPos(obj, 2, vz);

        }

    }else if (id ==159)
    {
        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);

        local fristX = obj.getVar("fristPos").get_vector(0);
        local fristY = obj.getVar("fristPos").get_vector(1);
        local fristZ = obj.getVar("fristPos").get_vector(2);

        local lastX = obj.getVar("lastPos").get_vector(0);
        local lastY = obj.getVar("lastPos").get_vector(1);
        local lastZ = obj.getVar("lastPos").get_vector(2);

        local fristT = obj.getVar("currentT").get_vector(0);
        if (currentT - fristT < 100)
        {

            
            local v1 = sq_GetUniformVelocity(fristX, lastX, currentT - fristT, 100);
            local v2 = sq_GetUniformVelocity(fristY, lastY, currentT - fristT, 100);
            local v3 = sq_GetUniformVelocity(fristZ, lastZ, currentT - fristT, 100);

            obj.setCurrentPos(v1,v2,v3);
            obj.getVar("headObj").get_obj_vector(0).setCurrentPos(v1,v2,v3);
        }else{
            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	
            local keyPress = mage.getVar("keyPress").get_vector(0);
            local keyPress2 = mage.getVar("keyPress").get_vector(1);

            obj.getVar("currentT").set_vector(0,currentT);
            obj.getVar("fristPos").set_vector(0,lastX);
            obj.getVar("fristPos").set_vector(1,lastY);
            obj.getVar("fristPos").set_vector(2,lastZ);

            local finalyX = lastX
            local finalyY = lastY;
            local finalyZ = lastZ;

            if (keyPress == 0 )
            {
                finalyX = lastX + 25;
            }else if (keyPress == 1  || keyPress == 2)
            {
                finalyX = lastX - 25;
                obj.getVar("headObj").get_obj_vector(0).setValid(false);
                obj.getVar("headObj").push_obj_vector( createDoubleDragonPassiveobjectHead4(obj) );
            }else if (keyPress == 3  || keyPress == 4)
            {
                finalyX = lastX + 25;
                obj.getVar("headObj").get_obj_vector(0).setValid(false);
                obj.getVar("headObj").push_obj_vector( createDoubleDragonPassiveobjectHead1(obj) );
            }
        
            if (keyPress2 == 1  || keyPress2 == 2)
            {
                finalyY = lastY + 25;
            }else if (keyPress2 == 3  || keyPress2 == 4)
            {
                finalyY = lastY - 25;
                if (finalyX > lastX)
                {
                    obj.getVar("headObj").get_obj_vector(0).setValid(false);
                    obj.getVar("headObj").push_obj_vector( createDoubleDragonPassiveobjectHead2(obj) );

                }else if (finalyX < lastX){
                    obj.getVar("headObj").get_obj_vector(0).setValid(false);
                    obj.getVar("headObj").push_obj_vector( createDoubleDragonPassiveobjectHead3(obj) );
                }
            }

            obj.getVar("lastPos").set_vector(0,finalyX);
            obj.getVar("lastPos").set_vector(1,finalyY);
            obj.getVar("lastPos").set_vector(2,finalyZ);

        }


    }
    if (id == 146)
    {
        local startX = obj.getVar("pos").get_vector(0);
        local maxD = obj.getVar("pos").get_vector(1);
        local maxT = obj.getVar("pos").get_vector(2);

        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        if (currentT <= maxT)
        {
            local vx = sq_GetUniformVelocity(0, maxD, currentT, maxT);
            local dstX = sq_GetDistancePos(startX, obj.getDirection(), vx);
            sq_setCurrentAxisPos(obj, 0, dstX);
        }else{
            sq_SendDestroyPacketPassiveObject(obj);	
        }

    }
    if (id == 140 || id == 141)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        obj.setCurrentPos(mage.getXPos(),mage.getYPos() + 1,mage.getZPos() );
    }
    if (id == 136)
    {
        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        if (currentT <= 1240)
        {
            local startX = obj.getVar("pos").get_vector(0);
            local moveD = obj.getVar("pos").get_vector(1);
            local vx = sq_GetUniformVelocity(0, moveD, currentT, 1240);
            local dstX = sq_GetDistancePos(startX, obj.getDirection(), vx);
            sq_setCurrentAxisPos(obj, 0, dstX);
        }else{
            sq_SendDestroyPacketPassiveObject(obj);	
        }
    }

    if (id == 134)
    {
        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        if (currentT >= 13 * 80 && obj.getVar("effectFlag").get_vector(0) == 0)
        {
            local size = obj.getVar("var").get_vector(3);

            obj.getVar("effectFlag").set_vector(0,1);
            obj.getVar("effect").push_obj_vector( createEpidMicrasaAppearStayEffect(obj, size ) );
            local saveT = obj.getVar("var").get_vector(0);
            obj.setTimeEvent(1,saveT,0,false);

        }
    }
    if (id == 132 || id == 133)
    {
        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        local maxT = obj.getVar("moveInitVar").get_vector(0);
        if (maxT < currentT)
        {
            setSightingShootPooledObjValid(obj);
            sq_SendDestroyPacketPassiveObject(obj);	
        }else{
            setSightingShootPooledObjFollowParentObj(obj);
            local startX = obj.getVar("moveInitVar").get_vector(1);
            local startY = obj.getVar("moveInitVar").get_vector(2);
            local startZ = obj.getVar("moveInitVar").get_vector(3);

            local offsetX = obj.getVar("moveVar").get_vector(0);
            local offsetY = obj.getVar("moveVar").get_vector(1);
            local offsetZ = obj.getVar("moveVar").get_vector(2);

            local vx = sq_GetUniformVelocity(0, offsetX, currentT, maxT);
            local vy = sq_GetUniformVelocity(0, offsetY, currentT, maxT);
            local vz = sq_GetUniformVelocity(0, offsetZ, currentT, maxT);

            local dstX = sq_GetDistancePos(startX, obj.getDirection(), vx);
            sq_setCurrentAxisPos(obj, 0, dstX);
            sq_setCurrentAxisPos(obj, 1, startY + vy);
            sq_setCurrentAxisPos(obj, 2, startZ + vz);

        }
    }
    if (id == 128)
    {
        local startX = obj.getVar("len").get_vector(0);
        local maxD = obj.getVar("len").get_vector(1);
        local maxT = obj.getVar("len").get_vector(2);

        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);

        if (currentT < maxT)
        {
            local v = sq_GetUniformVelocity(0, maxD, currentT, maxT);
            local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
            sq_setCurrentAxisPos(obj, 0, dstX);


        }else{
            sq_SendDestroyPacketPassiveObject(obj);	
        }
    }
    if (id == 126)
    {
        onProcSummonZigArdentEvent(obj);
    }
    if (id == 125)
    {
        local atk = obj.getVar("var").get_vector(0);
        local maxCount = obj.getVar("var").get_vector(1);
        local currCount =  obj.getVar("var").get_vector(2);
        local dist =  obj.getVar("var").get_vector(3);
        local size =  obj.getVar("var").get_vector(4);
        local yPos =  obj.getVar("var").get_vector(5);
        local maxT =  obj.getVar("var").get_vector(6);
        local burnProc =  obj.getVar("var").get_vector(7);
        local burnLevel =  obj.getVar("var").get_vector(8);
        local burnTime =  obj.getVar("var").get_vector(9);
        local atk2 =  obj.getVar("var").get_vector(10);

        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);

        if (currentT >= 10 && obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").set_vector(0,1);


            if (maxCount > currCount)
            {
                if (!obj.isMyControlObject() )
                    return false;

                local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), dist);
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(atk );	// attackBonusRate
                sq_BinaryWriteDword(125);
                sq_BinaryWriteDword(maxCount);
                sq_BinaryWriteDword(currCount + 1);
                sq_BinaryWriteDword(dist);
                sq_BinaryWriteDword(size);
                sq_BinaryWriteDword(yPos);
                sq_BinaryWriteDword(maxT);
                sq_BinaryWriteDword(burnProc);
                sq_BinaryWriteDword(burnLevel);
                sq_BinaryWriteDword(burnTime);
                sq_BinaryWriteDword(atk2);
                sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, posX , obj.getYPos() + yPos, obj.getZPos());
            }

        }else if (currentT >= maxT && obj.getVar("flag").get_vector(1) == 0)
        {
            obj.getVar("flag").set_vector(1,1);
//            sq_SendCreatePassiveObjectPacketPos(obj,20132, 15, obj.getXPos() , obj.getYPos(), obj.getZPos() + 37);
            createIceWaveExExplosionEffect(obj,200);


			sq_createAttackObjectWithPath(obj, "passiveobject/character/swordman/animation/icewaveexiceexplosion.ani",
            "passiveobject/character/swordman/attackinfo/icewaveexiceexplosion.atk",false,atk2,size,0,0,37);		

            local effect = obj.getVar("effectObj").get_obj_vector(0);
            if (effect)
                effect.setValid(false);
            sq_SendDestroyPacketPassiveObject(obj);	

        }
    }

    if (id >= 43 && id <= 48)
    {
        local startX = obj.getVar().get_vector(0);
        local maxD = obj.getVar().get_vector(1);
        local maxT = 200;

        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);

        if (currentT < maxT)
        {
            local v = sq_GetUniformVelocity(0, maxD, currentT, maxT);
            local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
            sq_setCurrentAxisPos(obj, 0, dstX);


        }

    }

    if (id == 119)
    {
        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        local startX = obj.getVar().get_vector(0);
        local maxD = obj.getVar().get_vector(1);
        local maxT = obj.getVar().get_vector(2);

        if (currentT < maxT)
        {
            local v = sq_GetUniformVelocity(0, maxD, currentT, maxT);
            local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
            sq_setCurrentAxisPos(obj, 0, dstX);


        }else{
//            createKallaFireSmokeEffect(obj, 0, 1, 0);
            sq_SendDestroyPacketPassiveObject(obj);	
        }

    }


    if (id == 116)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        if (mage &&  (mage.sq_GetState() == STATE_WING && mage.getVar("state").get_vector(0) == 1)    )
        {
            obj.setCurrentPos(mage.getXPos(),mage.getYPos() + 1,mage.getZPos() );
        }else{
            sq_SendDestroyPacketPassiveObject(obj);	
        }
    }

    if (id == 19 || id == 20)
    {

        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        
        local startX = obj.getVar("len").get_vector(0);
        local maxD = obj.getVar("len").get_vector(1);
        local maxT = obj.getVar("len").get_vector(2);

        if (currentT < maxT)
        {
            local v = sq_GetUniformVelocity(0, maxD, currentT, maxT);
            local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
            sq_setCurrentAxisPos(obj, 0, dstX);


        }else{
            sq_SendDestroyPacketPassiveObject(obj);	
        }
    }
	if (id == 108){
		local isHorizen = obj.getVar("va").get_vector(4);
		if(isHorizen == 1){
			setRangeObjectPosEx(obj, 150, sq_GetDistancePos(0, obj.getDirection(), 0), 0, ENUM_DIRECTION_NEUTRAL, 0, 300, 150, 4);
		}
	}
    if (id == 109)
    {
        local startZ = obj.getVar("posZ").get_vector(0);
        local dropT = obj.getVar("posZ").get_vector(1);
        local waveA = obj.getVar("posZ").get_vector(2);

        local currentAni = sq_GetCurrentAnimation(obj);
        local currentT = sq_GetCurrentTime(currentAni);
        if (currentT < dropT)
        {
            local v = sq_GetUniformVelocity(0, startZ, currentT, dropT);
            sq_setCurrentAxisPos(obj, 2, startZ - v);
        }else{

            sq_BinaryStartWrite();
            sq_BinaryWriteDword(waveA);	// attackBonusRate
            sq_BinaryWriteDword(110);
            sq_BinaryWriteDword(obj.getVar("posZ").get_vector(3));
            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos(), obj.getYPos() + 1, 0);

            sq_SendDestroyPacketPassiveObject(obj);	
        }
    }

    if (id == 107)
    {

        if (obj.getVar("state").get_vector(0) == 0)
        {
            local startX = obj.getVar("state").get_vector(4);
            local dashD =  obj.getVar("state").get_vector(2);
            local dashT = obj.getVar("state").get_vector(3);
            
            local currentAni = sq_GetCurrentAnimation(obj);
            local currentT = sq_GetCurrentTime(currentAni);
            if (currentT < dashT)
            {
                local v = sq_GetUniformVelocity(0, dashD, currentT, dashT);
                local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
                sq_setCurrentAxisPos(obj, 0, dstX);
            }else{
                sq_SendDestroyPacketPassiveObject(obj);	
            }
        }

    }
//        obj.getVar("state").clear_vector();
//        obj.getVar("state").push_vector(0);
//        obj.getVar("state").push_vector(attackBonusRate);
//        obj.getVar("state").push_vector(dashD);
//        obj.getVar("state").push_vector(dashT);
//        obj.getVar("state").push_vector(obj.getXPos() );



    if (id == 78)
    {
        local mage = obj.getTopCharacter();

        if (!mage)
        {
            sq_SendDestroyPacketPassiveObject(obj);	
        }
    }

    if (id == 100)
    {

        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        if (mage.sq_GetState() != STATE_BLOODSONG)
        {
            sq_SendDestroyPacketPassiveObject(obj);	
        }


        local object = obj.getVar("obj").get_obj_vector(0);

        if (object && !sq_IsFixture(object) )
        {
            if (!checkIsHoldAndDelayEffect(object) )
                return false;

            local currentAni = sq_GetCurrentAnimation(obj);
            local currentT = sq_GetCurrentTime(currentAni);


            local height = mage.sq_GetIntData(SKILL_BLOODSONG, 24) + 
            mage.sq_GetIntData(SKILL_BLOODSONG, 25) * obj.getVar("type").get_vector(0) + 
            obj.getVar("hei").get_vector(0);

            if (currentT >= 50)
            {
                object.setCurrentPos(obj.getXPos(),obj.getYPos() - 1,height);
            }else{
                local v = sq_GetUniformVelocity(0, height, currentT, 50);
                object.setCurrentPos(obj.getXPos(),obj.getYPos() - 1,v);
            }
        }


    }


    if (id == 99)
    {


        local object = obj.getVar("target").get_obj_vector(0);
        if (object)
        {
            local currentAni = sq_GetCurrentAnimation(object);

//            currentAni.setEffectLayer(true, GRAPHICEFFECT_LINEARDODGE, true, sq_RGB(255, 100, 100), sq_ALPHA(200), true, false);

        }else{


        }
    }

    if (id == 91)
    {

        local tar = obj.getVar("dama").get_obj_vector(0);
        if ( tar )
        {
            obj.setCurrentPos(tar.getXPos() ,tar.getYPos() + 1,tar.getZPos() + tar.getObjectHeight() / 2 );
        }else{
            sq_SendDestroyPacketPassiveObject(obj);	
        }

    }

    if (id == 87)
    {
        if (obj.getZPos() <= 0)
        {
            sq_SendCreatePassiveObjectPacketPos(obj, 12282, 0,obj.getXPos(), obj.getYPos(),0 );
            sq_SetMyShake(obj,4,80);
            sq_SendDestroyPacketPassiveObject(obj);	

        }else{
            obj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos() - 100);
        }

    }
    if (id == 15)
    {
        if (!obj.isMyControlObject())
            return false;

        local pAni = obj.getCurrentAnimation();
        local frmIndex = sq_GetAnimationFrameIndex(pAni);
        if (frmIndex == 7)
        {
                sq_SetMyShake(obj,1,140);
        }else if (frmIndex == 9)
        {
                sq_SetMyShake(obj,2,80);
        }else if (frmIndex == 10)
        {
            sq_flashScreen(obj,80,20,360,153, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            sq_SetMyShake(obj,4,80);
        }else if (frmIndex == 11)
        {
                sq_SetMyShake(obj,10,240);
        }

    }


    if (id == 51)
    {
        local pAni = obj.getCurrentAnimation();
        local frmIndex = sq_GetAnimationFrameIndex(pAni);
        if (frmIndex == 8)
        {
            if (obj.getVar("id2").get_vector(0) == 1)
                sq_flashScreen(obj,0,0,400,255, sq_RGB(139,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
        }else if (frmIndex == 10)
        {
            //obj.getVar("dama").push_obj_vector(damager);

            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();
            for(local i=0;i<objectsSize;++i)
            {
                local damager = var.get_obj_vector(i);
                if(damager)
                {
                    CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/blood45/ap_blood45.nut");		
                }
            }

        }
    }

    if (id == 81)
    {

        local mage = obj.getVar("followObj").get_obj_vector(0);
//        local mage = obj.getTopCharacter();
//        mage = sq_ObjectToSQRCharacter(mage);	

        if (!mage)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
        local state = obj.getVar("state").get_vector(0);

        if (state == 0)
        {
            local startX = obj.getVar("startPos").get_vector(0);
            local startY = obj.getVar("startPos").get_vector(1);
            local maxT = obj.getVar("startPos").get_vector(2);
            local delT = obj.getVar("startPos").get_vector(3);
            local chrX = sq_GetDistancePos(mage.getXPos(), mage.getDirection(), obj.getVar("startPos").get_vector(4) ); //mage.getXPos();
            local chrY = mage.getYPos();

            local pAni = obj.getCurrentAnimation();
            local currentT = sq_GetCurrentTime(pAni);

            if (currentT < maxT)
            {
                local v1 = sq_GetAccel(startX, chrX, currentT, maxT, true);
                local v2 = sq_GetAccel(startY, chrY, currentT, maxT, true);
        
                obj.setCurrentPos(v1,v2,0);
            }else if(currentT > delT){

                sq_SendDestroyPacketPassiveObject(obj);	
            }else{
//                obj.setCurrentPos(chrX,chrY,0);
            }
        }



    }
    if (id == 80)
    {
//        obj.getVar("mov").push_vector(0);
//        obj.getVar("mov").push_vector(dist);
//        obj.getVar("mov").push_vector(maxTime);
//        obj.getVar("mov").push_vector(obj.getXPos() );

        local startX = obj.getVar("mov").get_vector(3 );
        local dist = obj.getVar("mov").get_vector(1);
        local maxT = obj.getVar("mov").get_vector(2);

        local pAni = obj.getCurrentAnimation();
        local currentT = sq_GetCurrentTime(pAni);

        if (currentT < maxT)
        {
            local v1 = sq_GetUniformVelocity(0, dist, currentT, maxT);
            local posX = sq_GetDistancePos(startX, obj.getDirection(), v1);
            obj.setCurrentPos(posX,obj.getYPos(),0);

        }else{
            sq_SendDestroyPacketPassiveObject(obj);	
        }


//        local currDist = obj.getVar("mov").get_vector(0);
//        if (currDist <= obj.getVar("mov").get_vector(1) )
//        {
//            local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 10);
//            obj.setCurrentPos(posX,obj.getYPos(),0);
//            obj.getVar("mov").set_vector(0,currDist + 10);
//        }else{
//            sq_SendDestroyPacketPassiveObject(obj);	
//        }

    }


    if (id == 0)
    {
        local pAni = obj.getCurrentAnimation();
        local frmIndex = sq_GetAnimationFrameIndex(pAni);

        if (frmIndex == 7)
        {
            sq_SetMyShake(obj,10,300);
            sq_flashScreen(obj,0,80,240,127, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        }
    }

    if (id == 52)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	

        local state = mage.getVar("state").get_vector(0);
        local state2 = mage.sq_GetState();
        if (!mage || state == 2 || state2 == STATE_STAND)
        {
            sq_SendDestroyPacketPassiveObject(obj);	
        }

    }

    if (id == 39)
    {
        if (obj.getZPos() - 5 > 50)
        {
            obj.setCurrentPos(obj.getXPos(), obj.getYPos(),obj.getZPos() - 5);
        }else {

            local attackBonusRate = obj.getVar("atk").get_vector(0);
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(attackBonusRate);	// attackBonusRate
            sq_BinaryWriteDword(40);
            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos(), obj.getYPos() + 1, 50);
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }

    if (id == 35)
    {


        local pAni = obj.getCurrentAnimation();
        local currentT = sq_GetCurrentTime(pAni);

        local startX = obj.getVar("tar").get_vector(2);
        local startY = obj.getVar("tar").get_vector(3);
        local startZ = obj.getVar("tar").get_vector(4);

        local lastX = obj.getVar("tar").get_vector(0);
        local lastY = obj.getVar("tar").get_vector(1);

        if (currentT < 100)
        {   
            local x = sq_GetUniformVelocity(startX,lastX,currentT,100);
            local y = sq_GetUniformVelocity(startY,lastY,currentT,100);
            local z = sq_GetUniformVelocity(startZ,0,currentT,100);
            obj.setCurrentPos(x,y,z);
        }else{

            local id = obj.getVar().get_vector(1);
            local angle = obj.getVar().get_vector(0).tofloat() / 1000.0;

            createVajraDropFloorEffect(obj,lastX,lastY,id,angle,obj.getVar().get_vector(3) );
            createVajraDropEffect(obj,lastX,lastY);

            if (obj.isMyControlObject() )
            {



                sq_BinaryStartWrite();
                sq_BinaryWriteDword( obj.getVar().get_vector(2) );	// attackBonusRate
                sq_BinaryWriteDword(36);	// attackBonusRate
                sq_SendCreatePassiveObjectPacketPos(obj,24357, 0,lastX, lastY, 0);
            }
            sq_SendDestroyPacketPassiveObject(obj);

        }

    }


    if (id == 38)
    {
        local state = obj.getVar("state").get_vector(0);

        local pAni = obj.getCurrentAnimation();
        local currentT = sq_GetCurrentTime(pAni);

        if (state == ENUM_PASSIVEOBJECT_LIGHTING_GOD_STATE_DROP)
        {
            local delay = pAni.getDelaySum(false);
            if (currentT > delay)
            {

//                local ani = obj.getCustomAnimation(50);
                local ani = obj.getVar().GetAnimationMap("5", 
                        "passiveobject/zrr_skill/newswordman/animation/lightninggod/lightning_create/2/god/2_god.ani"); 
                obj.setCurrentAnimation(ani);
                local attackInfo = sq_GetCustomAttackInfo(obj, 23);
                sq_SetCurrentAttackInfo(obj, attackInfo);
                attackInfo = sq_GetCurrentAttackInfo(obj);
                sq_SetCurrentAttackPower(attackInfo, obj.getVar("atk").get_vector(1) );
                obj.getVar("state").set_vector(0,ENUM_PASSIVEOBJECT_LIGHTING_GOD_STATE_ROAR);
                obj.setTimeEvent(0,obj.getVar().get_vector(2),0,false);
                obj.getVar("effctObj").clear_obj_vector();
                createLightingGodBodyFloorEffect_2(obj);

                obj.getVar("flag").clear_vector();
                obj.getVar("flag").push_vector(0);
                obj.getVar("flag").push_vector(0);
                obj.getVar("flag").push_vector(0);
                obj.getVar("flag").push_vector(0);
                sq_SetMyShake(obj,5,150);
                sq_flashScreen(obj,80,200,150,127, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

                sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, 6,obj.getVar("var").get_vector(0),
                                                obj.getVar("var").get_vector(1), obj.getVar("var").get_vector(2) ,
                                                obj.getVar("var").get_vector(3) );

            }
        }else if (state == ENUM_PASSIVEOBJECT_LIGHTING_GOD_STATE_ROAR)
        {
            onProc_Lighting_God_DropSword(obj);
            local maxT = obj.getVar().get_vector(0);
            if (currentT > maxT)
            {
                setVliadEffectLightingGodPassiveObject(obj);
//                local ani = obj.getCustomAnimation(51);
                local ani = obj.getVar().GetAnimationMap("6", 
                        "passiveobject/zrr_skill/newswordman/animation/lightninggod/lightning_create/3/god/3_god.ani"); 
                obj.setCurrentAnimation(ani);
                local attackInfo = sq_GetCustomAttackInfo(obj, 23);
                sq_SetCurrentAttackInfo(obj, attackInfo);
                attackInfo = sq_GetCurrentAttackInfo(obj);
                sq_SetCurrentAttackPower(attackInfo, obj.getVar("atk").get_vector(1) );
                obj.getVar("state").set_vector(0,EUNM_PASSIVEOBJECT_LIGHTING_GOD_STATE_TOGETHER);

                sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, 6,obj.getVar("var").get_vector(0),
                                                obj.getVar("var").get_vector(1), obj.getVar("var").get_vector(2) ,
                                                obj.getVar("var").get_vector(3) );

                obj.getVar("flag").clear_vector();
                obj.getVar("flag").push_vector(0);
                obj.getVar("flag").push_vector(0);
                obj.getVar("flag").push_vector(0);
                obj.getVar("flag").push_vector(0);
                sq_flashScreen(obj,80,3000,150,127, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
                createLightingGodBodyFloorEffect_3(obj);
            }
        }else if (state == EUNM_PASSIVEOBJECT_LIGHTING_GOD_STATE_TOGETHER)
        {
            onProc_Lighting_God_DropSword(obj);
            local delay = pAni.getDelaySum(false);
            if (currentT > delay)
            {

//                local ani = obj.getCustomAnimation(52);
                local ani = obj.getVar().GetAnimationMap("7", 
                        "passiveobject/zrr_skill/newswordman/animation/lightninggod/lightning_create/4/god/4_god.ani"); 
                obj.setCurrentAnimation(ani);
                local attackInfo = sq_GetCustomAttackInfo(obj, 24);
                sq_SetCurrentAttackInfo(obj, attackInfo);
                attackInfo = sq_GetCurrentAttackInfo(obj);
                sq_SetCurrentAttackPower(attackInfo, obj.getVar("atk").get_vector(1) );
                obj.getVar("state").set_vector(0,ENUM_PASSIVEOBJECT_LIGHTING_GOD_STATE_READ_SWROD);

                obj.getVar("effctObj").clear_obj_vector();
                createLightingGodBodyFloorEffect_4(obj);
                setVliadEffectLightingGodPassiveObjectBall(obj);
                obj.setTimeEvent(0,obj.getVar().get_vector(2),0,false);

                sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, 6,obj.getVar("var").get_vector(0),
                                                obj.getVar("var").get_vector(1), obj.getVar("var").get_vector(2) ,
                                                obj.getVar("var").get_vector(3) );

            }
        }else if (state == ENUM_PASSIVEOBJECT_LIGHTING_GOD_STATE_READ_SWROD)
        {
            local maxT = obj.getVar().get_vector(1);
            if (currentT > maxT)
            {
                
                setVliadEffectLightingGodPassiveObject(obj);
//                local ani = obj.getCustomAnimation(53);
                local ani = obj.getVar().GetAnimationMap("8", 
                        "passiveobject/zrr_skill/newswordman/animation/lightninggod/lightning_create/5/god/god_god_normal.ani"); 
                obj.setCurrentAnimation(ani);
                local attackInfo = sq_GetCustomAttackInfo(obj, 24);
                sq_SetCurrentAttackInfo(obj, attackInfo);
                attackInfo = sq_GetCurrentAttackInfo(obj);
                sq_SetCurrentAttackPower(attackInfo, obj.getVar("atk").get_vector(2) );
                obj.getVar("state").set_vector(0,EUNM_PASSIVEOBJECT_LIGHTING_GOD_STATE_DROP_SWORD);
                createLightingGodBodyFloorEffect_5(obj);
                obj.getVar("flag").clear_vector();
                obj.getVar("flag").push_vector(0);
                obj.getVar("flag").push_vector(0);
                obj.getVar("flag").push_vector(0);
                obj.getVar("flag").push_vector(0);

                sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, 6,obj.getVar("var").get_vector(0),
                                                obj.getVar("var").get_vector(1), obj.getVar("var").get_vector(2) ,
                                                obj.getVar("var").get_vector(3) );

            }
        }else if (state == EUNM_PASSIVEOBJECT_LIGHTING_GOD_STATE_DROP_SWORD)
        {

            if (currentT > 80 && obj.getVar("flag").get_vector(0) == 0)
            {
                obj.getVar("flag").set_vector(0,1);
                sq_SetMyShake(obj,8,200);
                sq_flashScreen(obj,80,200,150,150, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            }

            local delay = pAni.getDelaySum(false);
            if (currentT > delay)
            {

//                local ani = obj.getCustomAnimation(54);
                local ani = obj.getVar().GetAnimationMap("9", 
                        "passiveobject/zrr_skill/newswordman/animation/lightninggod/lightning_exp/exp/exp_exp_normal_04.ani"); 
                obj.setCurrentAnimation(ani);
                local attackInfo = sq_GetCustomAttackInfo(obj, 25);
                sq_SetCurrentAttackInfo(obj, attackInfo);
                attackInfo = sq_GetCurrentAttackInfo(obj);
                sq_SetCurrentAttackPower(attackInfo, obj.getVar("atk").get_vector(3) );
                obj.getVar("state").set_vector(0,EUNM_PASSIVEOBJECT_LIGHTING_GOD_STATE_EXPLOSION);
                createLightingGodBodyFloorEffect_explosion(obj);
                sq_SetMyShake(obj,8,200);

                sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, 6,obj.getVar("var").get_vector(0),
                                                obj.getVar("var").get_vector(1), obj.getVar("var").get_vector(2) ,
                                                obj.getVar("var").get_vector(3) );

            }
        }else if (state == EUNM_PASSIVEOBJECT_LIGHTING_GOD_STATE_EXPLOSION)
        {
            local delay = pAni.getDelaySum(false);
            if (currentT > delay)
            {
                sq_SendDestroyPacketPassiveObject(obj);
            }
        }
    }

    if (id == 34)
    {

        local target1 = obj.getVar("tar").get_obj_vector(0);
        local target2 = obj.getVar("tar").get_obj_vector(1);

        obj.setCurrentPos(target1.getXPos(),target1.getYPos() + 1 , target1.getObjectHeight() /2 );

        if (target1.getXPos() > target2.getXPos())
        {
            obj.setCurrentDirection(ENUM_DIRECTION_LEFT);
        }else{
            obj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
        }


        local distance = sq_GetDistance( target1.getXPos(), target1.getYPos() - target1.getZPos(), target2.getXPos(), target2.getYPos() - target2.getZPos(), true);

        local disX = abs( target1.getXPos() - target2.getXPos() );
        local disY = target1.getYPos() - target2.getYPos() + target1.getZPos() - target2.getZPos() + target1.getObjectHeight() /2 +target2.getObjectHeight() /2 ;
        local angle = sq_Atan2( disY.tofloat(), disX.tofloat());

        local rateX = disX.tofloat() / 264;
        local rateY =  1.0;
        local pAni = obj.getCurrentAnimation();

        pAni.setImageRate(rateX, rateY);
        sq_SetfRotateAngle(pAni, angle);		
    }



    if (id == 26)
    {


//        local pAni = obj.getCurrentAnimation();
//        local currentT = sq_GetCurrentTime(pAni);

        local mage = obj.getTopCharacter();
        if (!mage)
            return false;


        mage = sq_ObjectToSQRCharacter(mage);	

        local pAni = mage.getCurrentAnimation();
        local currentT = sq_GetCurrentTime(pAni);

        local speed = 2500 - sq_GetUniformVelocity(0,750,currentT,obj.getVar("d").get_vector(0));
        local judge = sq_GetUniformVelocity(0, 360*2, currentT,speed) + obj.getVar("c").get_vector(0) ;

        if (currentT < 250)
        {   
            judge = obj.getVar("c").get_vector(0);
        }else{
            currentT = currentT - 250;
        }


        obj.getVar("a").set_vector(2,judge % 360);

        local chrx = obj.getVar("a").get_vector(0);
        local chry = obj.getVar("a").get_vector(1);
        local angle = obj.getVar("a").get_vector(2);
        local len = obj.getVar("a").get_vector(3);

        angle = angle.tofloat();

		local posX = len * sq_CosTable(angle.tointeger());
		local posY = len * sq_SinTable(angle.tointeger()) * 0.29;

        local currentAni = sq_GetCurrentAnimation(obj);

        if (obj.getXPos() > chrx)
        {
            obj.setCurrentDirection(ENUM_DIRECTION_RIGHT);
        }else{
            obj.setCurrentDirection(ENUM_DIRECTION_LEFT);
        }

        local size = posY.tofloat() / (len.tofloat()* 0.29);
    
        local sizeRate = 1.40 + size * 0.30;

        currentAni.setImageRateFromOriginal(sizeRate, 1.0);
//        currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

        obj.setCurrentPos(chrx + posX.tointeger(),chry+posY.tointeger(),0);

        obj.getVar("size").clear_vector();
        obj.getVar("size").push_vector(sizeRate.tointeger() );


    }


    if (id == 25)
    {


    }
    if (id == 24)
    {
        local objX = obj.getXPos();
        local objY = obj.getYPos();
        local objZ = obj.getZPos();
//        obj.getVar("len").clear_vector();
//        obj.getVar("len").push_vector( obj.getXPos() );
//        obj.getVar("len").push_vector(dist);
//        obj.getVar("len").push_vector(200);
//        local judge = 

        local pAni = obj.getCurrentAnimation();
        local currentT = sq_GetCurrentTime(pAni);
        
        local startX = obj.getVar("len").get_vector(0);
        local maxD = obj.getVar("len").get_vector(1);
        local maxT = obj.getVar("len").get_vector(2);

        

        if (currentT <= maxT)
        {
            if (obj.getVar("state").get_vector(0) == 0)
            {
                local v = sq_GetUniformVelocity(0,maxD,currentT,maxT);
                local posX = sq_GetDistancePos(startX, obj.getDirection(),v);
                obj.setCurrentPos(posX,obj.getYPos(),obj.getZPos() );
            }
        }else{

            sq_SetMyShake(obj,3,720);
//            local ani = obj.getCustomAnimation(35);
            local ani = obj.getVar().GetAnimationMap("10", 
            "passiveobject/zrr_skill/atmage/animation/atspiralpress/atspiralpressfinish_00.ani"); 
            obj.setCurrentAnimation(ani);
            obj.getVar("state").set_vector(0,1);

        }

    }

    if (id == 18)
    {
        local objX = obj.getXPos();
        local objY = obj.getYPos();
        local objZ = obj.getZPos();

        for (local i = 0;i < obj.getVar("effectObj").get_obj_vector_size();i++)
        {
            local pooledObj = obj.getVar("effectObj").get_obj_vector(i);
            if (pooledObj)
                pooledObj.setCurrentPos(objX,objY,objZ);
        }

        local state = obj.getVar("state").get_vector(0);
        if (state == 0)
        {

            local mage = obj.getTopCharacter();
            mage = sq_ObjectToSQRCharacter(mage);	

            if (mage)
            {
                if (mage.getState() != STATE_STORMQUAKE)
                    obj.getVar("state").set_vector(0,1);
            }else{

                obj.getVar("state").set_vector(0,1);

            }


        }

    }


    if (id == 17)
    {
        local objX = obj.getXPos();
        local objY = obj.getYPos();
        local objZ = obj.getZPos();

        if (objZ > 0)
        {
            obj.setCurrentPos(objX,objY,objZ - 10);
        }else{

            if (obj.getVar("flag").get_vector(0) == 1)
                return false;

            obj.getVar("flag").set_vector(0,1);

            local attackBonusRate = obj.getVar("at").get_vector(0);

            local attackInfo = sq_GetCustomAttackInfo(obj, 5);
            sq_SetCurrentAttackInfo(obj, attackInfo);

//            local ani = obj.getCustomAnimation(25);
            local ani = obj.getVar().GetAnimationMap("11", 
            "passiveobject/zrr_skill/gunner/animation/lightexplosion.ani"); 
            obj.setCurrentAnimation(ani);

            local size = obj.getVar("value").get_vector(0);

            local gdProc = obj.getVar("value").get_vector(1);
            local gdLevel = obj.getVar("value").get_vector(2);
            local gdTime = obj.getVar("value").get_vector(3);
            local gdRate = obj.getVar("value").get_vector(4);

            local currentAni = sq_GetCurrentAnimation(obj);

            local sizeRate = size.tofloat()/100.0;
            currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
            currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
            sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);

            local attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

            sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, ACTIVESTATUS_LIGHTNING, gdProc, gdLevel, gdTime,gdRate);

            obj.resetHitObjectList();



            return true;



        }



    }

    if (id == 14)
    {
        local damager = obj.getVar("dama").get_obj_vector(0);
        if (damager)
        {
//            damager.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos() - damager.getObjectHeight()/2);
        }else{

            sq_SendDestroyPacketPassiveObject(obj);
        }
    }


    if (id == 9)
    {
        local damager = obj.getVar("dama").get_obj_vector(0);
        if (damager)
        {

            obj.setCurrentPos(damager.getXPos(),damager.getYPos(),damager.getZPos() + damager.getObjectHeight()/2);
            obj.setCurrentDirection(damager.getDirection());
        }

    }

    if (id == 1)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	

        local state = mage.getVar("state").get_vector(0);
        if (state == 2)
        {
            sq_SendDestroyPacketPassiveObject(obj);	
        }

    }
    if (id >= 5 && id <= 7)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	

        local state = mage.getVar("state").get_vector(0);
        if (state == 2)
        {
            sq_SendDestroyPacketPassiveObject(obj);	
        }
    }

    if (id == 3)
    {

        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	

        if (!mage)
        {
            setBloodValue(mage,obj.getVar("blood2").get_vector(0) );
            sq_SendDestroyPacketPassiveObject(obj);	
        }

        local chrX = mage.getXPos();
        local chrY = mage.getYPos();
        local chrZ = mage.getZPos();


        local objX = obj.getXPos();
        local objY = obj.getYPos();
        local objZ = obj.getZPos() - (obj.getObjectHeight() * 2) / 3;


        if (obj.getVar("speed").get_vector(0) < 0)
        {

            local moveSpeed = - 10;
            local speedX = moveSpeed + obj.getVar("speed").get_vector(0);
            if (obj.getVar("y").get_vector(0)< 0 )
            {
                local speedY = obj.getVar("y").get_vector(0) + obj.getVar("speed").get_vector(0);
            }else{
                local speedY = obj.getVar("y").get_vector(0) + obj.getVar("speed").get_vector(0);
            }
            local speedZ = 3;

            if (chrX < objX ) speedX = - speedX;
            if (abs(chrX - objX) <= moveSpeed * 2) speedX = 0;

            obj.setCurrentPos(objX + speedX,objY + speedY,obj.getZPos() + speedZ);

        }else{

            local moveSpeed = - 10;
            local speedX = moveSpeed + obj.getVar("speed").get_vector(0);
            local speedY = obj.getVar("speed").get_vector(0);
            local speedZ = 1;

            if (chrX < objX ) speedX = - speedX;
            if (chrY < objY) speedY = - speedY;
            if (chrZ < objZ) speedZ = - speedZ;
        
            if (abs(chrX - objX) <= -moveSpeed * 2) speedX = 0;
            if (abs(chrY - objY) <= -moveSpeed * 2) speedY = 0;
            if (abs(chrZ - objZ) <= 2 ) speedZ = 0;
        
            obj.setCurrentPos(objX + speedX,objY + speedY,obj.getZPos() + speedZ);

        }


        if (abs(chrX - objX) < 40 && abs(chrY - objY) < 40 )
        {
            sq_SendCreatePassiveObjectPacketPos(obj,12160, 0, chrX,chrY,chrZ);
            sq_SendDestroyPacketPassiveObject(obj);	
            setBloodValue(mage,obj.getVar("blood2").get_vector(0) );

        }

    }


    if (id == 4)
    {

        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();

        if (true)
        {

            for(local i=0;i < objectsSize;++i)
            {
                local damager = var.get_obj_vector(i);

                local dvalue = 1;
                if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT) dvalue = -1;

                local objX = obj.getXPos();
                local objY = obj.getYPos();
                local objZ = obj.getZPos();


                if (obj.getVar("4state").get_vector(0) == 0)
                {
                            sq_SetCustomRotate(damager,sq_ToRadian(-20.0) );
                    damager.setCurrentPos(objX + 224 * dvalue,objY + 1,34 + objZ - damager.getObjectHeight()/2);
                }else{

                    local pAni = sq_GetCurrentAnimation(obj);
                    local frmIndex = sq_GetAnimationFrameIndex(pAni);

                    if (obj.getVar("4state").get_vector(0) == 1)
                    {

                        local x = 0;
                        local z = 0;
                        local xz = 0;

                        if (frmIndex == 0)
                        {
                            x = 178;
                            z = 36;
                            xz = - 20;

                        }else if(frmIndex == 1)
                        {
                            x = 171;
                            z = 43;
                            xz = 10;

                        }else if (frmIndex == 2)
                        {
                            x = 180;
                            z = 44;
                            xz = 14;
                        }else if (frmIndex == 3)
                        {
                            x = 216;
                            z = 52;
                            xz = 30;
                        }else if (frmIndex == 4)
                        {
                            x = 256;
                            z = 60;
                            xz = 40;
                        }else if (frmIndex == 5)
                        {
                            x = 255;
                            z = 69;
                            xz = 20;
                        }else if (frmIndex == 6)
                        {
                            x = 223;
                            z = 36;
                            xz = 20;
                        }else if (frmIndex == 7)
                        {
                            x = 252;
                            z = 68;
                            xz = 10;
                        }else if (frmIndex == 8)
                        {
                            x = 180;
                            z = 33;
                            xz = -20;
                        }else if (frmIndex == 9)
                        {
                            x = 180;
                            z = 34;
                            xz = 10;
                        }else if (frmIndex == 10)
                        {
                            x = 183;
                            z = 38;
                            xz = 14;
                        }else if (frmIndex == 11)
                        {
                            x = 222;
                            z = 45;
                            xz = 30;
                        }else if (frmIndex == 12)
                        {

                            x = 258;
                            z = 61;
                            xz = 40;
                        }else if (frmIndex == 13)
                        {
                            x = 257;
                            z = 64;
                            xz = 20;

                        }else if (frmIndex == 14)
                        {
                            x = 256;
                            z = 66;
                            xz = 10;

                        }else if (frmIndex == 15)
                        {
                            x = 234;
                            z = 40;
                            xz = -10;
                        }

                        z = (z.tofloat() / 1.25).tointeger();
                        if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/bloodsong/ap_bloodsong.nut") )
                        {
                            sq_SetCustomRotate(damager,sq_ToRadian(-xz.tofloat() ) );
                            damager.setCurrentPos(objX + x * dvalue,objY - 1,z + objZ - damager.getObjectHeight()/2);
                            
                        }else{
                            sq_SetCustomRotate(damager,0.0);
                        }

                    }else{
                        sq_SetCustomRotate(damager,0.0);

                        local x = 0;
                        local z = 0;
                        local xz = 0;

                        if (frmIndex == 0)
                        {
                            x = 105;
                            z = 169;
                            xz = -40;
                        }else if (frmIndex == 1 )
                        {
                            x = -169;
                            z = 374;
                            xz = -80;
                        }else if (frmIndex == 2 )
                        {
                            x = -191;
                            z = 384;
                            xz = -120;
                        }else if (frmIndex == 3 )
                        {
                            x = -192;
                            z = 381;
                            xz = -130;
                        }else if (frmIndex == 4 )
                        {
                            x = -106;
                            z = 343;
                            xz = -190;
                        }else if (frmIndex == 5 )
                        {
                            x = 189;
                            z = 264;
                            xz = -200;
                        }else if (frmIndex == 6 )
                        {
                            x = 292;
                            z = 62;
                            xz = -200;
                        }

                        x = (x.tofloat() / 1.25).tointeger();
                        z = (z.tofloat() / 1.25).tointeger();


                        if (frmIndex <= 6)
                        {
                            damager.setCurrentPos(objX + x * dvalue,objY - 1,25 + z + objZ);
                            sq_SetCustomRotate(damager,sq_ToRadian(-xz.tofloat() ) );
                        }else{
                            damager.setCurrentPos(damager.getXPos(),damager.getYPos(),damager.getZPos());
                            sq_SetCustomRotate(damager,0.0);
                        }


                    }

                }


            }
        }
    }



}