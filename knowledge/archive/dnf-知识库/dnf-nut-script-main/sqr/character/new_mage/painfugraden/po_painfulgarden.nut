function setCustomData_po_painfulgarden(obj, receiveData)
{
	if(!obj)
		return;

	local attackBonusRate = receiveData.readDword();// ?????(%)	
    local id = receiveData.readDword();
    if (id == 0)
    {
        local time0 = receiveData.readDword();
        local time1 = receiveData.readDword();
        local size = receiveData.readDword();
        local blood = receiveData.readDword();
        obj.getVar("attackRate").clear_vector();
        obj.getVar("attackRate").push_vector(attackBonusRate);
        obj.getVar("attackRate").push_vector(size);


        obj.getVar("blood").clear_vector();
        obj.getVar("blood").push_vector(blood);

        local ani = obj.getVar().GetAnimationMap("0", 
                    "passiveobject/zrr_skill/atmage/animation/atrumbledog/rumbledog_floor_cast01.ani"); 
		obj.setCurrentAnimation(ani);

		obj.getVar("saveT").clear_vector();
		obj.getVar("saveT").push_vector(time0);
		obj.getVar("saveT").push_vector(time1);

        local currentAni = sq_GetCurrentAnimation(obj);
        local sizeRate = size.tofloat()/100.0;
        currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
        currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
        sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);



    }else if (id == 1)
    {
        local waitTime = receiveData.readDword();
        local sxAttackTime = receiveData.readDword();
        local maxSize = receiveData.readDword();
        local minSize = receiveData.readDword();
        local subSize = receiveData.readDword();
        local blood = receiveData.readDword();

        local attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

//        local ani = obj.getCustomAnimation(11);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/atmage/animation/atsoulsteel/floor/floor_start_blackloop8.ani"); 
		obj.setCurrentAnimation(ani);


        obj.setTimeEvent(1, sxAttackTime, 0, false);//attackTime

        obj.getVar("sizeValue").clear_vector();
        obj.getVar("sizeValue").push_vector(maxSize);
        obj.getVar("sizeValue").push_vector(minSize);
        obj.getVar("sizeValue").push_vector(subSize);
        
        obj.getVar("fristSize").clear_vector();
        obj.getVar("fristSize").push_vector(maxSize);

        obj.getVar("blood").clear_vector();
        obj.getVar("blood").push_vector(0);

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
        obj.getVar("state").push_vector(waitTime);



        local currentAni = sq_GetCurrentAnimation(obj);
        local sizeRate = maxSize.tofloat() / 100.0;
        currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
        currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);


        local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atsoulsteel/awake/soulsteelawake_front_start_up.ani");

                ani.setImageRateFromOriginal(sizeRate, sizeRate);
                ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
        local pooledObj = sq_CreatePooledObject(ani,true);
        pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
        pooledObj.setCurrentDirection(obj.getDirection());
        sq_AddObject(obj,pooledObj,5,false);	

        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackeHitStunTime(attackInfo, 0);

    }else if (id == 2)
    {
//        local ani = obj.getCustomAnimation(15);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/bladephantom/magic_circle_start.ani"); 

		obj.setCurrentAnimation(ani);
        local waitTime = receiveData.readDword();//maxwait
        local summonTime = receiveData.readDword();//summontime
        local ghostNumber = receiveData.readDword();//summonnumber
        local ghostWait = receiveData.readDword();//if ghost is wait ghostwait

        local zdProc = receiveData.readDword();
        local zdLevel = receiveData.readDword();
        local zdTime = receiveData.readDword();
        local zdAttackRate = receiveData.readDword();

        local last = receiveData.readDword();
        local muitAtk = receiveData.readDword();

        local size = receiveData.readDword();

        local currentAni = sq_GetCurrentAnimation(obj);
        local sizeRate = size.tofloat() / 100.0;
        currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
        currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

        obj.getVar("summonVar").clear_vector();
        obj.getVar("summonVar").push_vector( waitTime );
        obj.getVar("summonVar").push_vector( summonTime );
        obj.getVar("summonVar").push_vector( size );

        obj.getVar("ghost75Value").clear_vector();
        obj.getVar("ghost75Value").push_vector(attackBonusRate);//0
        obj.getVar("ghost75Value").push_vector(ghostNumber);//1
        obj.getVar("ghost75Value").push_vector(ghostWait);//2
        obj.getVar("ghost75Value").push_vector(zdProc);//3
        obj.getVar("ghost75Value").push_vector(zdLevel);//4
        obj.getVar("ghost75Value").push_vector(zdTime);//5
        obj.getVar("ghost75Value").push_vector(zdAttackRate);//6
        obj.getVar("ghost75Value").push_vector(last);//7
        obj.getVar("ghost75Value").push_vector(muitAtk);//8
        obj.getVar("ghost75Value").push_vector(size);//9

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);

    }else if (id == 3)
    {
        local savT = receiveData.readDword();
        local maxC = receiveData.readDword();
        local atk2 = receiveData.readDword();

		local bloodProc = receiveData.readDword();
		local bloodleve = receiveData.readDword();
		local bloodtime = receiveData.readDword();
		local bloodRate = receiveData.readDword();

        obj.setTimeEvent(0, savT / maxC, 0, false);

        obj.getVar("max").clear_vector();
        obj.getVar("max").push_vector(maxC);
        obj.getVar("max").push_vector(atk2);

//        local ani = obj.getCustomAnimation(2);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/thornvinehold/area/loopfloor_10.ani"); 

		obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCustomAttackInfo(obj, 0);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);

        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
        sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, ACTIVESTATUS_BLEEDING, bloodProc, bloodleve, bloodtime,bloodRate);

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);

        local ani = sq_CreateAnimation("","passiveobject/zrr_skill/newmage/animation/thornvinehold/area/loopfront_00.ani");
        local pooledObj = sq_CreatePooledObject(ani,true);
        pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
        pooledObj.setCurrentDirection(obj.getDirection());
        sq_AddObject(obj,pooledObj,0,false);	

        obj.getVar("obj").clear_obj_vector();
        obj.getVar("obj").push_obj_vector( pooledObj );


    }else if (id == 4)
    {
//        local ani = obj.getCustomAnimation(4);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/rage/ragestartbottom_01.ani"); 
		obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCustomAttackInfo(obj, 2);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
    }else if (id == 5)
    {
//        local ani = obj.getCustomAnimation(5);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/bloodmarble/bloodmarbleextract_normal.ani"); 
		obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCustomAttackInfo(obj, 3);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
        local savT = receiveData.readDword();
        obj.setTimeEvent(0, savT , 0, true);



    }else if (id == 6)
    {
        local ani = obj.getCustomAnimation(6);

		obj.setCurrentAnimation(ani);
    }else if (id == 7)
    {
        local ani = obj.getCustomAnimation(7);
		obj.setCurrentAnimation(ani);
    }else if (id == 8)
    {
        local savT = receiveData.readDword();
        obj.setTimeEvent(0, savT , 0, false);
//        local ani = obj.getCustomAnimation(8);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/dot/curseofdot/curseofterrorbear/loopfloor_00.ani"); 
		obj.setCurrentAnimation(ani);
    }else if (id == 9)
    {
//        local ani = obj.getCustomAnimation(9);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/woodsofpuppet/woodsofpuppetmadbg_00.ani"); 
		obj.setCurrentAnimation(ani);
    }else if (id == 10)
    {
        local hitC = receiveData.readDword();
        local atk2 = receiveData.readDword();

		local bloodProc = receiveData.readDword();
		local bloodleve = receiveData.readDword();
		local bloodtime = receiveData.readDword();
		local bloodRate = receiveData.readDword();

		local holdProc = receiveData.readDword();
		local holdleve = receiveData.readDword();
		local holdtime = receiveData.readDword();

        obj.setTimeEvent(0, 1160 / hitC, 0, false); // hitTime
//        local ani = obj.getCustomAnimation(10);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/painfulgarden/floor_08.ani"); 

		obj.setCurrentAnimation(ani);
        local attackInfo = sq_GetCustomAttackInfo(obj, 4);//ok
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
        sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, ACTIVESTATUS_BLEEDING, bloodProc, bloodleve, bloodtime,bloodRate);
        sq_SetChangeStatusIntoAttackInfo(attackInfo, 1, ACTIVESTATUS_HOLD, holdProc, holdleve, holdtime);


        obj.getVar("value").clear_vector();
        obj.getVar("value").push_vector(atk2);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
    }else if (id == 11)
    {

        obj.sq_PlaySound("R_SM_TOMBSTONE_SWAMP");
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newswordman/animation/tombstoneswamp/groundloop_00.ani"); 
		obj.setCurrentAnimation(ani);
        local saveT = receiveData.readDword();
        local random = receiveData.readDword();
        local x = receiveData.readDword();
        local y = receiveData.readDword();

        obj.setTimeEvent(0,saveT,0,false);
        obj.setTimeEvent(1,25,0,false);

        createGhostCastleTomeEffectStart(obj, -200, 50, 0);
        createGhostCastleTomeEffectStart(obj, 0, -75, 0);
        createGhostCastleTomeEffectStart(obj, 200, 50, 0);

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);

        obj.getVar("atk").clear_vector();
        obj.getVar("atk").push_vector(attackBonusRate);
        obj.getVar("atk").push_vector(random);
        obj.getVar("atk").push_vector(x);
        obj.getVar("atk").push_vector(y);

        obj.getVar("dama").clear_obj_vector();
        obj.getVar("effect").clear_obj_vector();

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);

        local objectManager = obj.getObjectManager();
        for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
        {
            local object = objectManager.getCollisionObject(i);
            if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) )
            {
                local activeObj = sq_GetCNRDObjectToActiveObject(object);
                
                if ( !sq_IsFixture(activeObj) )
                {
                    obj.getVar("dama").push_obj_vector(activeObj);
                }
            }
        }


    }else if (id == 12)
    {
        local power = receiveData.readDword();

//        local ani = obj.getCustomAnimation(14);
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/gunblader/animation/hopslash/ground_01.ani"); 
		obj.setCurrentAnimation(ani);

        local attackInfo = sq_GetCustomAttackInfo(obj, 6);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, attackBonusRate);
    }else if (id == 13)
    {
    
        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/newmage/animation/elementalcurtain/elementalcurtain_groundcircle.ani"); 
		obj.setCurrentAnimation(ani);

        obj.getVar("effect").clear_obj_vector();
        obj.getVar("effect").push_obj_vector( createElementalCurtainInTheSkyPooledObj(obj) );
        obj.getVar("effect").push_obj_vector( createElementalCurtainInTheSkyBackPooledObj(obj) );
        obj.getVar("effect").push_obj_vector( createElementalCurtainInTheSkyFrontPooledObj(obj) );
//
        local attackInfo = sq_GetCustomAttackInfo(obj, 7);
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

        obj.getVar("atk").clear_vector();
        obj.getVar("atk").push_vector( receiveData.readDword() );
        obj.getVar("atk").push_vector( receiveData.readDword() );

        obj.setTimeEvent(0,receiveData.readDword(),0,false);

        local size = receiveData.readDword();
        obj.getVar("atk").push_vector( size );

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);

    }
    obj.getVar("id").clear_vector();
    obj.getVar("id").push_vector(id);

}
function procAppend_po_painfulgarden(obj)
{
    local id = obj.getVar("id").get_vector(0);
    if (id == 11)
    {

        if (obj.getVar("state").get_vector(0) == 0)
        {

            if (obj.getVar("flag").get_vector(0) == 0)
            {
                local currentAni = sq_GetCurrentAnimation(obj);
                local currentT = sq_GetCurrentTime(currentAni);
                if (currentT >= 720)
                {
                    createGhostCastleTomeEffectLoop(obj, -200, 50, 0);
                    createGhostCastleTomeEffectLoop(obj, 0, -75, 0);
                    createGhostCastleTomeEffectLoop(obj, 200, 50, 0);
                    obj.getVar("flag").set_vector(0,1);
                }
            }
            if (obj.getVar("flag").get_vector(1) == 0)
            {
                local currentAni = sq_GetCurrentAnimation(obj);
                local currentT = sq_GetCurrentTime(currentAni);
                if (currentT >= 180)
                {
                    sq_SetMyShake(obj,10,200);
                    obj.getVar("flag").set_vector(1,1);
                }
            }
        }
    }else if (id == 9)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        if (mage.getVar("isBreak").get_vector(0) == 1)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }
    else if (id == 7)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        if (mage.getVar("state").get_vector(0) != 3)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 6)
    {
        local mage = obj.getTopCharacter();
        mage = sq_ObjectToSQRCharacter(mage);	
        if (mage.getVar("state").get_vector(0) != 2)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 5)
    {
        local swordman = obj.getTopCharacter();
        swordman = sq_ObjectToSQRCharacter(swordman);	
        if (swordman.getVar("state").get_vector(0) == 2)
        {
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }
}

function onEndCurrentAni_po_painfulgarden(obj)
{
    local id = obj.getVar("id").get_vector(0);
    if (id == 1)
    {
        obj.setTimeEvent(2, 1024, 0, true);//subSize
        obj.setTimeEvent(0, obj.getVar("state").get_vector(1) , 1, false);//destroy
        obj.getVar("state").set_vector(0,1);
//        local ani = obj.getCustomAnimation(0);
        local ani = obj.getVar().GetAnimationMap("3", 
                    "passiveobject/zrr_skill/atmage/animation/atsoulsteel/floor/floor_loop_blackloop8.ani"); 
		obj.setCurrentAnimation(ani);

    }else if (id == 2)
    {
        if (obj.getVar("state").get_vector(0) == 0)
        {
//            local ani = obj.getCustomAnimation(1);
            local ani = obj.getVar().GetAnimationMap("3", 
                    "passiveobject/zrr_skill/newswordman/animation/bladephantom/magic_circle_loop.ani"); 
            obj.setCurrentAnimation(ani);

            local size = obj.getVar("summonVar").get_vector(2);
            local currentAni = sq_GetCurrentAnimation(obj);
            local sizeRate = size.tofloat() / 100.0;
            currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
            currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

            obj.setTimeEvent(0, obj.getVar("summonVar").get_vector(0 ) , 1, false);//destroy
            obj.setTimeEvent(1, obj.getVar("summonVar").get_vector(1 ) , 0,true);//summonGhost
            obj.getVar("state").set_vector(0,1);
        }
    }else if (id == 3)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 4)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 10)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 11)
    {
        if (obj.getVar("state").get_vector(0) == 1)
        {
            setVliadEffectGhostCastlePassiveObject(obj);

            createGhostCastleTomeEffectEnd(obj, -200, 50, 0);
            createGhostCastleTomeEffectEnd(obj, 0, -75, 0);
            createGhostCastleTomeEffectEnd(obj, 200, 50, 0);

            sq_BinaryStartWrite();
            sq_BinaryWriteDword( obj.getVar("atk").get_vector(0) );	// attackBonusRate
            sq_BinaryWriteDword(94);	// attackBonusRate
            sq_SendCreatePassiveObjectPacketPos(obj, 24357, 0,obj.getXPos(),obj.getYPos() + 1,0);
            sq_SendDestroyPacketPassiveObject(obj);
        }
    }else if (id == 12)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }
}


function onKeyFrameFlag_po_painfulgarden(obj, flagIndex)
{
    local id = obj.getVar("id").get_vector(0);
    if (id == 10 && obj.getVar("flag").get_vector(0) == 0)
    {
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(1);
        local attackInfo = sq_GetCustomAttackInfo(obj, 5);//ok
        sq_SetCurrentAttackInfo(obj, attackInfo);
        attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackPower(attackInfo, obj.getVar("value").get_vector(0) );
        obj.resetHitObjectList();
        sq_SetMyShake(obj,10,230);
        sq_flashScreen(obj,10,50,10,76, sq_RGB(255,0,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        obj.setTimeEvent(0, 10000, 1, false); 
    }else if (id == 0 && flagIndex == 999)
    {
        local time0 = obj.getVar("saveT").get_vector(0);
        local time1 = obj.getVar("saveT").get_vector(1);
        obj.setTimeEvent(0, time0, 1, false);
        obj.setTimeEvent(1, time1, 0, false);


        local ani = obj.getVar().GetAnimationMap("1", 
                    "passiveobject/zrr_skill/atmage/animation/atrumbledog/rumbledog_floor_loop01.ani"); 
		obj.setCurrentAnimation(ani);

        local size = obj.getVar("attackRate").get_vector(1);

        local currentAni = sq_GetCurrentAnimation(obj);
        local sizeRate = size.tofloat()/100.0;
        currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
        currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
        sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);

        return true;
    }
}

function onAttack_po_painfulgarden(obj,damager, boundingBox, isStuck)
{
    local id = obj.getVar("id").get_vector(0);
    if (id == 13)
    {
        local attackInfo = sq_GetCurrentAttackInfo(obj);
        attackInfo.setElement(sq_getRandom(0,4).tointeger() );
        createElementalCurtainInHitEffect(obj,damager);
    }
    else if (id == 5)
    {
        sq_EffectLayerAppendage(damager,sq_RGB(200,0,0),150,0,150,240);	
        local sword = obj.getTopCharacter();
        sword = sq_ObjectToSQRCharacter(sword);	
        local size = sword.getVar("size").get_vector(0);
        sword.getVar("size").set_vector(0,size + 5);

    }
    else if (id == 3)
    {
        if (obj.getVar("state").get_vector(0) == 0)
        {
            if ( !CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/new_mage/cirrusarea/ap_cirrusarea.nut") )
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_CIRRUSAREA  false, "character/new_mage/cirrusarea/ap_cirrusarea.nut", true);				 
            }
        }else{
            CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/new_mage/cirrusarea/ap_cirrusarea.nut");		
        }
    }else if (id == 1)
    {
            local sword = obj.getTopCharacter();
            sword = sq_ObjectToSQRCharacter(sword);	

            damager = sq_GetCNRDObjectToActiveObject(damager);


            if (!damager.isDead() && 
                !CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/append_bloodmage/ap_bloodin.nut"))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, sword, SKILL_BLOODIN, false, 
                "character/atmage/append_bloodmage/ap_bloodin.nut", true);				 
            }


            if (obj.getVar("flag").get_vector(0)  == 0)
            {
                obj.getVar("flag").clear_vector();
                obj.getVar("flag").push_vector(1);


                if (!CNSquirrelAppendage.sq_IsAppendAppendage(sword, "character/atmage/append_bloodmage/ap_bloodin_character.nut"))
                {
                    local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(sword, sword, SKILL_BLOODIN, false, 
                    "character/atmage/append_bloodmage/ap_bloodin_character.nut", true);				 
                }

            }
                if (damager && damager.isObjectType(OBJECTTYPE_ACTIVE) )
                {
                    local objX = obj.getXPos();
                    local objY = obj.getYPos();
                    local damaX = damager.getXPos();
                    local damaY = damager.getYPos();
                    local damaZ = damager.getZPos();
                    local x_move = 0;
                    local y_move = abs(damaY - objY ) / 5;
                    if (objX < damaX) x_move = - x_move;
                    if (objY < damaY) y_move = - y_move;
                    damager.setCurrentPos(damaX + x_move,damaY + y_move,damaZ);
                }

    }
}

function onTimeEvent_po_painfulgarden(obj, timeEventIndex, timeEventCount)
{

    local id = obj.getVar("id").get_vector(0);
    if (id == 13)
    {
        if (timeEventIndex == 0)
        {
            if (timeEventCount < obj.getVar("atk").get_vector(1))
                obj.resetHitObjectList();
            else
            {
                if (obj.getVar("flag").get_vector(0) == 0)
                {
                    local atk = obj.getVar("atk").get_vector(0);
                    local size = obj.getVar("atk").get_vector(2);
                    sq_BinaryStartWrite();
                    sq_BinaryWriteDword(atk );	// attackBonusRate
                    sq_BinaryWriteDword(129);	// attackBonusRate
                    sq_BinaryWriteDword(size);	// attackBonusRate
                    sq_SendCreatePassiveObjectPacketPos(obj, 24357, 0,obj.getXPos(), obj.getYPos(), obj.getZPos() );
                    obj.setTimeEvent(1, 480, 0,false);
                    obj.getVar("flag").set_vector(0,1);
                }
            }
        }else if (timeEventIndex == 1){
                setElementalCurtainPooledObjSetValid(obj);
                sq_SendDestroyPacketPassiveObject(obj);
        }
    }
    if (id == 11)
    {
        if (timeEventIndex == 0)
        {
//            local ani = obj.getCustomAnimation(13);

            local ani = obj.getVar().GetAnimationMap("3", 
                    "passiveobject/zrr_skill/newswordman/animation/tombstoneswamp/groundend_00.ani"); 

            obj.setCurrentAnimation(ani);
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
        }else{

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
                    local x_move = obj.getVar("atk").get_vector(2);
                    local y_move = obj.getVar("atk").get_vector(3);
                    if (objX < damaX) x_move = - x_move;
                    if (objY < damaY) y_move = - y_move;


                    if(damaZ > 0)
                    {
                        damaZ = damaZ - 5;
                    }else{
                        damaZ = 0;
                    }
                    if (abs(objX - damaX) < 3* x_move && abs(objY - damaY) < 3* y_move )
                    {
                        damager.setCurrentPos(objX,objY,damaZ);
                    }else{
                        damager.setCurrentPos(damaX + x_move,damaY + y_move,damaZ);
                    }
            }
        }
    }else if (id == 10)
    {
        obj.resetHitObjectList();


    }else if (id == 8)
    {
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (id == 5)
    {
        if (timeEventIndex == 0)
        {

                obj.resetHitObjectList();
        }
    }
    else if (id == 3)
    {
        if (timeEventIndex == 0)
        {
            if (timeEventCount > obj.getVar("max").get_vector(0))
            {
                obj.setTimeEvent(0, 1, 1,true);
                local loopObj = obj.getVar("obj").get_obj_vector(0);
                if (loopObj)
                {
                    loopObj.setValid(false);
                }

                local ani = sq_CreateAnimation("","passiveobject/zrr_skill/newmage/animation/thornvinehold/area/endfront_03.ani");
                local pooledObj = sq_CreatePooledObject(ani,true);
                pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
                pooledObj.setCurrentDirection(obj.getDirection());
                sq_AddObject(obj,pooledObj,2,false);	

                obj.getVar("state").clear_vector();
                obj.getVar("state").push_vector(1);
                sq_SetMyShake(obj,2,160);

                local ani = obj.getVar().GetAnimationMap("3", 
                    "passiveobject/zrr_skill/newmage/animation/thornvinehold/area/endfloor_08.ani"); 
                obj.setCurrentAnimation(ani);
                local attackInfo = sq_GetCustomAttackInfo(obj, 1);
                sq_SetCurrentAttackInfo(obj, attackInfo);
                attackInfo = sq_GetCurrentAttackInfo(obj);
                sq_SetCurrentAttackPower(attackInfo, obj.getVar("max").get_vector(1) );
                obj.resetHitObjectList();



            }else{
                if (obj.getVar("state").get_vector(0) == 0)
                {
                    obj.resetHitObjectList();
                }
            }
        }


    }else if (id == 2)
    {

        if (timeEventIndex == 0)//destroy
        {
            obj.getVar("state").set_vector(0,2);
            local size = obj.getVar("ghost75Value").get_vector(9);

            local attackBonusRate2 = obj.getVar("ghost75Value").get_vector(8);

            if (obj.isMyControlObject())
            {
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(attackBonusRate2);	// attackBonusRate
                sq_BinaryWriteDword(2);	// attackBonusRate
                sq_BinaryWriteDword(size);	// attackBonusRate
                sq_SendCreatePassiveObjectPacketPos(obj, 24318, 0,obj.getXPos(), obj.getYPos(), obj.getZPos() + 50);
            }
            obj.setTimeEvent(2,500, 1, false);//destroy
            obj.setTimeEvent(1, 1, 1,true);//summonGhost

        } 

        if (timeEventIndex == 1)//summon 24318
        {
            if (obj.isMyControlObject())
            {
                local attackBonusRate = obj.getVar("ghost75Value").get_vector(0);
                local ghostNumber = obj.getVar("ghost75Value").get_vector(1);
                local ghostWait = obj.getVar("ghost75Value").get_vector(2);

                local zdProc =  obj.getVar("ghost75Value").get_vector(3);
                local zdLevel =  obj.getVar("ghost75Value").get_vector(4);
                local zdTime =  obj.getVar("ghost75Value").get_vector(5);
                local zdAttackRate =  obj.getVar("ghost75Value").get_vector(6);
                local size = obj.getVar("ghost75Value").get_vector(9);
                for (local i = 0; i< ghostNumber;i++)
                {
                    local direction = sq_getRandom(-1,1);
                    sq_BinaryStartWrite();
                    sq_BinaryWriteDword(attackBonusRate);	// attackBonusRate
                    sq_BinaryWriteDword(0);	// attackBonusRate
                    sq_BinaryWriteDword(ghostWait);	// attackBonusRate
                    sq_BinaryWriteDword(direction);	// attackBonusRate

                    sq_BinaryWriteDword(zdProc);
                    sq_BinaryWriteDword(zdLevel);
                    sq_BinaryWriteDword(zdTime);
                    sq_BinaryWriteDword(zdAttackRate);

                    sq_BinaryWriteDword(size);	// attackBonusRate

                    sq_SendCreatePassiveObjectPacketPos(obj, 24318, 0,
                    obj.getXPos() + sq_getRandom(-125 * size / 100 , 125 * size / 100 ).tointeger(), 
                    obj.getYPos() + sq_getRandom(-40 * size / 100  , 40 * size / 100 ).tointeger() , 
                    obj.getZPos() + sq_getRandom(0 , 300).tointeger() );
                }
            }

        }

        if (timeEventIndex == 2)
        {
//passiveobject/zrr_skill/newswordman/animation/bladephantom/magic_circle_end.ani

            if (obj.isMyControlObject())
            {
                local size = obj.getVar("ghost75Value").get_vector(9);
                local attackBonusRate3 = obj.getVar("ghost75Value").get_vector(7);
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(attackBonusRate3);	// attackBonusRate
                sq_BinaryWriteDword(1);	// attackBonusRate
                sq_BinaryWriteDword(size);	// attackBonusRate
                sq_SendCreatePassiveObjectPacketPos(obj, 24318, 0,obj.getXPos(), obj.getYPos(), obj.getZPos() + 50);
            }
            obj.setTimeEvent(3,1500, 1, false);//destroy

        }else if ( timeEventIndex == 3 )
        {

            local ani = sq_CreateAnimation("","passiveobject/zrr_skill/newswordman/animation/bladephantom/magic_circle_end.ani");
            local size = obj.getVar("ghost75Value").get_vector(9);

            local sizeRate = size.tofloat() / 100.0;
            ani.setImageRateFromOriginal(sizeRate, sizeRate);
            ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

            local pooledObj = sq_CreatePooledObject(ani,true);
            pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
            pooledObj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos());
            sq_AddObject(obj,pooledObj,1,false);	


            sq_SendDestroyPacketPassiveObject(obj);
        }

    }

    if (id == 1)
    {
        if (timeEventIndex == 0)
        {
            local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atsoulsteel/awake/soulsteelawake_front_end_sp3.ani");
            local pooledObj = sq_CreatePooledObject(ani,true);
            pooledObj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos());
            sq_AddObject(obj,pooledObj,1,false);	
			createBloodInEndFloorEffect(obj);
            sq_SendDestroyPacketPassiveObject(obj);
        }else if (timeEventIndex == 1)
        {
            obj.resetHitObjectList();


        }else if (timeEventIndex == 2)
        {

            if (obj.getVar("state").get_vector(0) == 1)
            {
                local maxSize = obj.getVar("sizeValue").get_vector(0);
                local minSize = obj.getVar("sizeValue").get_vector(1);
                local subSize = obj.getVar("sizeValue").get_vector(2);
                local fristSize = obj.getVar("fristSize").get_vector(0);

                local currSize = maxSize + subSize - timeEventCount * subSize;
                if (currSize < minSize)
                {
                    currSize = minSize;
                }
                local currentAni = sq_GetCurrentAnimation(obj);
                local sizeRate = currSize.tofloat() / 100.0;
                local fristSizeRate = fristSize.tofloat()/100.0;
                currentAni.setImageRateFromOriginal(sizeRate, sizeRate);
                currentAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

                sq_SetAttackBoundingBoxSizeRate(currentAni, 1.0/(fristSizeRate), 1.0/(fristSizeRate), 1.0/(fristSizeRate) );

                sq_SetAttackBoundingBoxSizeRate(currentAni, sizeRate, sizeRate, sizeRate);


                local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atsoulsteel/awake/soulsteelawake_front_loop_sp3.ani");
                ani.setImageRateFromOriginal(sizeRate, sizeRate);
                ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
                local pooledObj = sq_CreatePooledObject(ani,true);
                pooledObj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos());
                sq_AddObject(obj,pooledObj,0,false);	

                obj.getVar("fristSize").set_vector(0,currSize);
            }
        }

    }

    if (id == 0)
    {
        if(!obj.isMyControlObject())
            return false;

        if (timeEventIndex == 0)
        {


            local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atrumbledog/rumbledog_floor_end01.ani");
            local pooledObj = sq_CreatePooledObject(ani,true);
            pooledObj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos());
            sq_AddObject(obj,pooledObj,0,false);	

            sq_SendDestroyPacketPassiveObject(obj);
        }

        if (timeEventIndex == 1)
        {

            if (!obj.isMyControlObject())
                return false;

            local dvalue = 1;
            if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT) dvalue = -1;
            local dogs_ID = timeEventCount % 6;
            local attackBonusRate = obj.getVar("attackRate").get_vector(0);
            local objX = sq_GetXPos(obj);
            local objY = sq_GetYPos(obj);
            local objZ = sq_GetZPos(obj);

            if (dogs_ID == 1) //right down
            {
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(attackBonusRate);	// attackBonusRate
                sq_BinaryWriteDword(1 * dvalue);
                sq_BinaryWriteDword(1);
                sq_BinaryWriteDword(objX);
                sq_BinaryWriteDword(objY);
                sq_BinaryWriteDword( obj.getVar("attackRate").get_vector(1) );
                sq_BinaryWriteDword( obj.getVar("blood").get_vector(0) );
                sq_SendCreatePassiveObjectPacketPos(obj, 24367, 0, objX, objY, objZ);
            }

            if (dogs_ID == 3)//behind
            {
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(attackBonusRate);	// attackBonusRate
                sq_BinaryWriteDword(1 * dvalue);
                sq_BinaryWriteDword(0);
                sq_BinaryWriteDword(objX);
                sq_BinaryWriteDword(objY);
                sq_BinaryWriteDword( obj.getVar("attackRate").get_vector(1) );
                sq_BinaryWriteDword( obj.getVar("blood").get_vector(0) );
                sq_SendCreatePassiveObjectPacketPos(obj, 24367, 0, objX, objY, objZ);
            }

            if (dogs_ID == 5)//right up
            {
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(attackBonusRate);	// attackBonusRate
                sq_BinaryWriteDword(1 * dvalue);
                sq_BinaryWriteDword(2);
                sq_BinaryWriteDword(objX);
                sq_BinaryWriteDword(objY);
                sq_BinaryWriteDword( obj.getVar("attackRate").get_vector(1) );
                sq_BinaryWriteDword( obj.getVar("blood").get_vector(0) );
                sq_SendCreatePassiveObjectPacketPos(obj, 24367, 0, objX, objY, objZ);
            }


            if (dogs_ID == 0) //left down
            {
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(attackBonusRate);	// attackBonusRate
                sq_BinaryWriteDword(-1 * dvalue);
                sq_BinaryWriteDword(1);
                sq_BinaryWriteDword(objX);
                sq_BinaryWriteDword(objY);
                sq_BinaryWriteDword( obj.getVar("attackRate").get_vector(1) );
                sq_BinaryWriteDword( obj.getVar("blood").get_vector(0) );
                sq_SendCreatePassiveObjectPacketPos(obj, 24367, 0, objX, objY, objZ);
            }

            if (dogs_ID == 4)//back
            {
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(attackBonusRate);	// attackBonusRate
                sq_BinaryWriteDword(-1 * dvalue);
                sq_BinaryWriteDword(0);
                sq_BinaryWriteDword(objX);
                sq_BinaryWriteDword(objY);
                sq_BinaryWriteDword( obj.getVar("attackRate").get_vector(1) );
                sq_BinaryWriteDword( obj.getVar("blood").get_vector(0) );
                sq_SendCreatePassiveObjectPacketPos(obj, 24367, 0, objX, objY, objZ);

            }

            if (dogs_ID == 2)//left up
            {
                sq_BinaryStartWrite();
                sq_BinaryWriteDword(attackBonusRate);	// attackBonusRate
                sq_BinaryWriteDword(-1 * dvalue);
                sq_BinaryWriteDword(2);
                sq_BinaryWriteDword(objX);
                sq_BinaryWriteDword(objY);
                sq_BinaryWriteDword( obj.getVar("attackRate").get_vector(1) );
                sq_BinaryWriteDword( obj.getVar("blood").get_vector(0) );
                sq_SendCreatePassiveObjectPacketPos(obj, 24367, 0, objX, objY, objZ);

            }

        }

    }


}