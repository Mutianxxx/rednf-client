//character/atmage/bloodscream/ap_bloodscream.nut

//2020-10-20

function checkExecutableSkill_bloodscream(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_BLOODSCREAM);
	if (isUseSkill) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0); 
		obj.sq_AddSetStatePacket(STATE_BLOODSCREAM, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function setCharacterFristAnimation_BloodStream(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_BLOODSCREAM );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/start/atbloodstream_starta_back_bodyeff02.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/start/atbloodstream_starta_bodyeff07.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/start/atbloodstream_startb_bg_eff01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/start/atbloodstream_startb_back_bodyeff_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/start/atbloodstream_startb_floor.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/start/atbloodstream_startb_bodyeff_02.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopa_back_bodyeff06.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopa_bg_tunnela01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopa_floor.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopa_front_bgeffa_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopa_tornadoa_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopb_back_bodyeff06.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopb_bg_tunnela01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopb_floor.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopb_front_bgeffa_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/loop/atbloodstream_loopb_tornadoa_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/end/atbloodstream_end_back_bodyeff09.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/end/atbloodstream_end_bg_tunnela01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/end/atbloodstream_end_ciecle_02.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/end/atbloodstream_end_floor.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/end/atbloodstream_end_front_bgeffg11.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/dome/atbloodstream_startb_domea_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/dome/atbloodstream_startb_back_domea_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/dome/atbloodstream_loop_domea_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/dome/atbloodstream_loop_back_domea_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/hita_eff03.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/hita_backeff02.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/hita_eff03.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/hitb_back01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/hitb_front01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atbloodstream/hita_eff03.ani");

        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/cutin/atmage_vampirelord.ani");

    }
}



function checkCommandEnable_bloodscream(obj)
{
	if(!obj)
		return false;
    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_BLOODSCREAM, 3)))
        return false;

	return true;
}




function onEndState_BLOODSCREAM(obj, new_state)
{

    if (new_state != STATE_BLOODSCREAM)
    {
        setVliadEffectBloodStreamPassiveObject(obj);
        setVliadEffectBloodStreamEsaspistPassiveObject(obj);
    }else{
        setVliadEffectBloodStreamPassiveObject(obj);
    }


//    setVliadEffectBloodStreamEsaspistPassiveObject(obj);)
}


function setVliadEffectBloodStreamPassiveObject(obj)
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


function setVliadEffectBloodStreamEsaspistPassiveObject(obj)
{
    local var = obj.getVar("esapistEffectObj_BloodStream");  		
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


function holdAllMonster_BLOODSCREAM(obj)
{
	local objectManager = obj.getObjectManager();

	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) &&
            abs(obj.getXPos() - object.getXPos() ) <= obj.sq_GetIntData(SKILL_BLOODSCREAM, 16) &&
            abs(obj.getYPos() - object.getYPos() ) <= obj.sq_GetIntData(SKILL_BLOODSCREAM, 17) &&
            !sq_IsFixture(damager) && object.isInDamagableState(obj)  )
		{

            if(damager.getState() != STATE_HOLD ) 
            {
                local activeObj = sq_GetCNRDObjectToActiveObject(object);
                
                obj.getVar("dama").push_obj_vector(activeObj);

                if (!CNSquirrelAppendage.sq_IsAppendAppendage(activeObj, "character/atmage/bloodscream/ap_bloodscream.nut"))
                {
                    local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(activeObj, obj, SKILL_BLOODSCREAM, false,
                    "character/atmage/bloodscream/ap_bloodscream.nut", true);				 
                }
            }
		}
	}

}

function onSetState_BLOODSCREAM(obj, state, datas, isResetTimer)
{

	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);

    local speed = 100;
    local speedRate = 100;
    local saveTime = 10000;
    local atkCount = 0;
    local atkTime = 10000;

    if (obj.isMyControlObject())
    {
        speed = obj.sq_GetIntData(SKILL_BLOODSCREAM, 4);
        speedRate = speed.tofloat();
        saveTime = obj.sq_GetIntData(SKILL_BLOODSCREAM, 0);
        atkCount = obj.sq_GetIntData(SKILL_BLOODSCREAM, 1);
        atkTime = (saveTime + (640 + 1300) * 100 / speed ) / atkCount;
    }
	obj.sq_StopMove();

    if (state == 0)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSCREAM_STARTA);

        if (obj.isMyControlObject())
        {
            obj.getVar().clear_vector();
            for (local i = 0;i<= 40;i++)
                obj.getVar().push_vector(0);

            //obj.sq_PlaySound("BLOODDOWN_2");
            obj.getVar("dama").clear_obj_vector();
            obj.getVar("effectObj").clear_obj_vector();

            obj.getVar("esapistEffectObj_BloodStream").clear_obj_vector();
            obj.getVar("objSize").clear_vector();
            obj.getVar("objSize").push_vector( obj.sq_GetIntData(SKILL_BLOODSCREAM, 5) );

            createBloodStreamStartA_Back_Bodyeffect02(obj);
            createBloodStreamStartA_Bodyeffect07(obj);

            obj.getVar("speed").clear_vector();
            obj.getVar("speed").push_vector(speed);
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(0);
            setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOODSCREAM, 2) );
            sq_flashScreen(obj,120 * 100 / obj.getVar("speed").get_vector(0),0,120 * 100 / obj.getVar("speed").get_vector(0),153, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        }





        if (obj.isMyControlObject())
        {

        }


    }else if (state == 1)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSCREAM_STARTB);
        if (obj.isMyControlObject())
        {
            sq_flashScreen(obj,240 * 100 / obj.getVar("speed").get_vector(0),0,0,51, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
            obj.sq_SetShake(obj, 8, 240 * 100 / obj.getVar("speed").get_vector(0));
        }
        local objectManager = obj.getObjectManager();
        local xPos = objectManager.getFieldXPos(400 + CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
        local yPos = objectManager.getFieldYPos(400, 0, ENUM_DRAWLAYER_NORMAL);
        obj.sq_SetfindNearLinearMovablePos(xPos,yPos,obj.getXPos(), obj.getYPos(), 10);

        if (obj.isMyControlObject())
        {
            createBloodStreamStartB_BG_Effect01(obj);
            createBloodStreamStartB_Back_Bodyeffect01(obj);
            createBloodStreamStartB_Floor(obj);
            createBloodStreamStartB_Back_BodyEffect_01(obj);
            createBloodStreamStartDomeB_Back(obj);
        }
        createBloodStreamStartB_Bodyeffect02(obj);
        createBloodStreamStartB_FrontBgEffect(obj);


        createBloodStreamStartDomeB(obj);





    }else if (state == 2)
    {

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSCREAM_LOOPA);
        if (obj.isMyControlObject())
        {
            sq_flashScreen(obj,0,60,240 * 100 / obj.getVar("speed").get_vector(0),
            153, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);

            obj.sq_SetShake(obj, 16, 120 * 100 / obj.getVar("speed").get_vector(0));
            createBloodStreamLoopA_Back_BodyEffect06(obj);
            createBloodStreamLoopA_BG(obj);
            createBloodStreamLoopA_Floor(obj);
            createBloodStreamLoopA_FrontBgeffect01(obj);
            createBloodStreamLoopDomeB_Back(obj);
        }
        createBloodStreamLoopA_Tornadoa_01(obj);
        createBloodStreamLoopDomeB(obj);



		obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODSCREAM_MUISTATTACK);
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSCREAM , STATE_BLOODSCREAM, 0, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);		
		obj.setTimeEvent(1,atkTime,atkCount - 1,false);


    }else if (state == 3)
    {

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSCREAM_LOOPB);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODSCREAM_MUISTATTACK);

        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSCREAM , STATE_BLOODSCREAM, 0, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);		

        if (obj.isMyControlObject())
        {
            obj.setTimeEvent(0,saveTime,1,false);
            obj.sq_SetShake(obj, 2, saveTime);
            createBloodStreamLoopB_Back_Bodyeffect06(obj);
            createBloodStreamLoopB_BG_Tunnela01(obj);
            createBloodStreamLoopB_Floor(obj);
            createBloodStreamLoopB_FrontBgEffectA_01(obj);
        }
        createBloodStreamLoopB_Tornadoa_01(obj);

    }else if (state == 4)
    {
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);


        if (obj.isMyControlObject())
        {
            obj.sq_SetShake(obj, 3, 720 * 100 / obj.getVar("speed").get_vector(0));
            createBloodStreamEnd_Back_BodyEffect09(obj);
            createBloodStreamEnd_Bg_Tunnela01(obj);
            createBloodStreamEnd_Ciecle02(obj);
            createBloodStreamEnd_Floor(obj);
            createBloodStreamEnd_FrontBg_Effect11(obj);
        }

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSCREAM_NEWEND);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODSCREAM_MUISTATTACK);
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSCREAM , STATE_BLOODSCREAM, 0, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);		
    }

    local currentAni = sq_GetCurrentAnimation(obj);
	currentAni.setSpeedRate(speedRate);		

    local attackInfo = sq_GetCurrentAttackInfo(obj);
    sq_SetCurrentAttackeHitStunTime(attackInfo, 0);


		

}


function onKeyFrameFlag_BLOODSCREAM(obj,flagIndex)
{

    if (!obj.isMyControlObject() )
        return false;

    if ( flagIndex == 1)
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);

            sq_flashScreen(obj,0,0,120 * 100 / obj.getVar("speed").get_vector(0),204, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
            obj.sq_SetShake(obj, 6, 60 * 100 / obj.getVar("speed").get_vector(0));
            holdAllMonster_BLOODSCREAM(obj);
        }
    }else if ( flagIndex == 2 )
    {
        if (obj.getVar("flag").get_vector(0) == 0)
        {



            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);
            obj.setTimeEvent(1,10000,1,false);
            setVliadEffectBloodStreamEsaspistPassiveObject(obj);
            obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODSCREAM_EXP);
            local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSCREAM , STATE_BLOODSCREAM, 1, 1.0);
            obj.sq_SetCurrentAttackBonusRate(damage);		
            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();

            if (objectsSize > 0)
            {

                for(local i=0;i<objectsSize;++i)
                {
                    local damager = var.get_obj_vector(i);

                    CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/bloodscream/ap_bloodscream.nut");		
                }
            }
        }
    }else if ( flagIndex == 10 )
    {
    }
    return true;
}


function onTimeEvent_BLOODSCREAM(obj, timeEventIndex, timeEventCount)
{


    local state = obj.getSkillSubState();
    if (state == 2)
    {
        if (timeEventIndex == 0)
        {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(3); 
            obj.sq_AddSetStatePacket(STATE_BLOODSCREAM, STATE_PRIORITY_USER, true);
        }else if (timeEventIndex == 1)
        {
            if (!obj.isMyControlObject() )
                return false;
			obj.resetHitObjectList();


        }
    }else if (state == 3)
    {
        if (timeEventIndex == 0)
        {
            if(!obj.isMyControlObject()) {
                return;
            }
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(4); 
            obj.sq_AddSetStatePacket(STATE_BLOODSCREAM, STATE_PRIORITY_USER, true);
        }else if (timeEventIndex == 1 )
        {
            if (!obj.isMyControlObject() )
                return false;
			obj.resetHitObjectList();


        }
    }else if (state == 4)
    {
        if (timeEventIndex == 1)
        {
            if (!obj.isMyControlObject() )
                return false;
			obj.resetHitObjectList();


        }
    }
}


function onEndCurrentAni_BLOODSCREAM(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
    local state = obj.getSkillSubState();
    if (state == 0 )
    {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1); 
		obj.sq_AddSetStatePacket(STATE_BLOODSCREAM, STATE_PRIORITY_USER, true);
    }else if (state == 1)
    {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2); 
		obj.sq_AddSetStatePacket(STATE_BLOODSCREAM, STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(3); 
		obj.sq_AddSetStatePacket(STATE_BLOODSCREAM, STATE_PRIORITY_USER, true);
    }else if (state == 4)
    {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}


function onProc_BLOODSCREAM(obj)
{
//	return false;
    local state = obj.getSkillSubState();
    local pAni = obj.sq_GetCurrentAni();
    local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
    if (!obj.isMyControlObject() )
        return false;

    if (state == 0)
    {

        if (frmIndex >= 1 && obj.getVar().get_vector(8) == 0)
        {
            obj.getVar().set_vector(8,1);
            sq_flashScreen(obj,60 * 100 / obj.getVar("speed").get_vector(0),0,120 * 100 / obj.getVar("speed").get_vector(0),153, 
            sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
        }

    }else if (state == 1)
    {

        if (frmIndex >= 4 && obj.getVar().get_vector(9) == 0)
        {
            obj.getVar().set_vector(9,1);
            sq_flashScreen(obj,0,0,120 * 100 / obj.getVar("speed").get_vector(0),204, 
            sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
            obj.sq_SetShake(obj, 4, 60 * 100 / obj.getVar("speed").get_vector(0) );
        }else if (frmIndex >= 5 && obj.getVar().get_vector(0) == 0)
        {
            obj.getVar().set_vector(0,1);
            obj.sq_SetShake(obj, 1, 240 * 100 / obj.getVar("speed").get_vector(0));
        }else if (frmIndex >= 9 && obj.getVar().get_vector(1) == 0)
        {
            obj.getVar().set_vector(1,1);
            sq_flashScreen(obj,240 * 100 / obj.getVar("speed").get_vector(0),0,0,153, 
            sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
            obj.sq_SetShake(obj, 4, 240 * 100 / obj.getVar("speed").get_vector(0));
        }


    }else if(state == 2)
    {



        if (frmIndex >= 1 && obj.getVar().get_vector(2) == 0)
        {
            obj.getVar().set_vector(2,1);
            obj.sq_SetShake(obj, 2, 600 * 100 / obj.getVar("speed").get_vector(0));
        }

//        obj.getVar("esapistEffectObj_BloodStream").clear_obj_vector();
//        obj.getVar("objSize").clear_vector();
//        obj.getVar("objSize").push_vector(100);


        local circleObj = obj.getVar("esapistEffectObj_BloodStream").get_obj_vector(0);
        local circleObjBack = obj.getVar("esapistEffectObj_BloodStream").get_obj_vector(1);

        if (circleObj && circleObjBack)
        {
//            		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);

//            local size = obj.getVar("objSize").get_vector(0);

			local delay = pAni.getDelaySum(false);
            local currentT = sq_GetCurrentTime(pAni);
            local v = sq_GetAccel(obj.sq_GetIntData(SKILL_BLOODSCREAM, 8), 
            obj.sq_GetIntData(SKILL_BLOODSCREAM, 9), currentT, delay, true);

            obj.getVar("objSize").set_vector(0,v);

            local circleAni = sq_GetCurrentAnimation(circleObj);
            local circleAni2 = sq_GetCurrentAnimation(circleObjBack);

            local sizeRate = v.tofloat()/100.0;
            circleAni.setImageRateFromOriginal(sizeRate, sizeRate);
            circleAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

            circleAni2.setImageRateFromOriginal(sizeRate, sizeRate);
            circleAni2.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

        }

    }else if (state == 3){


        local circleObj = obj.getVar("esapistEffectObj_BloodStream").get_obj_vector(0);
        local circleObjBack = obj.getVar("esapistEffectObj_BloodStream").get_obj_vector(1);

        if (circleObj && circleObjBack)
        {
//            		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);

//            local size = obj.getVar("objSize").get_vector(0);

            local currentT = sq_GetCurrentTime(pAni);
            local v = sq_GetAccel(obj.sq_GetIntData(SKILL_BLOODSCREAM, 10),
            obj.sq_GetIntData(SKILL_BLOODSCREAM, 11), currentT, obj.sq_GetIntData(SKILL_BLOODSCREAM, 0), true);
            obj.getVar("objSize").set_vector(0,v);

            local circleAni = sq_GetCurrentAnimation(circleObj);
            local circleAni2 = sq_GetCurrentAnimation(circleObjBack);

            local sizeRate = v.tofloat()/100.0;
            circleAni.setImageRateFromOriginal(sizeRate, sizeRate);
            circleAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

            circleAni2.setImageRateFromOriginal(sizeRate, sizeRate);
            circleAni2.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

        }


    }else if (state == 4)
    {
        

        local circleObj = obj.getVar("esapistEffectObj_BloodStream").get_obj_vector(0);
        local circleObjBack = obj.getVar("esapistEffectObj_BloodStream").get_obj_vector(1);

        if (circleObj && circleObjBack)
        {
//            		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);

//            local size = obj.getVar("objSize").get_vector(0);

			local delay = pAni.getDelaySum(false);
            local currentT = sq_GetCurrentTime(pAni);
            local v = sq_GetAccel(obj.sq_GetIntData(SKILL_BLOODSCREAM, 12), obj.sq_GetIntData(SKILL_BLOODSCREAM, 13), currentT, delay, true);
            obj.getVar("objSize").set_vector(0,v);

            local circleAni = sq_GetCurrentAnimation(circleObj);
            local circleAni2 = sq_GetCurrentAnimation(circleObjBack);

            local sizeRate = v.tofloat()/100.0;
            circleAni.setImageRateFromOriginal(sizeRate, sizeRate);
            circleAni.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

            circleAni2.setImageRateFromOriginal(sizeRate, sizeRate);
            circleAni2.setAutoLayerWorkAnimationAddSizeRate(sizeRate);

        }


        if (frmIndex >= 6 && obj.getVar().get_vector(3) == 0)
        {
            obj.getVar().set_vector(3,1);
            obj.sq_SetShake(obj, 8, 600 * 100 / obj.getVar("speed").get_vector(0));
        }else if (frmIndex >= 11 && obj.getVar().get_vector(4) == 0)
        {
            obj.getVar().set_vector(4,1);
            sq_flashScreen(obj,120 * 100 / obj.getVar("speed").get_vector(0),20 * 100 / obj.getVar("speed").get_vector(0),
            340 * 100 / obj.getVar("speed").get_vector(0),255, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);

            obj.sq_SetShake(obj, 16, 120 * 100 / obj.getVar("speed").get_vector(0));

        }else if (frmIndex >= 12 && obj.getVar().get_vector(5) == 0)
        {
            obj.getVar().set_vector(5,1);
            obj.sq_SetShake(obj, 20, 120 * 100 / obj.getVar("speed").get_vector(0));
        }else if (frmIndex >= 13 && obj.getVar().get_vector(6) == 0)
        {
            obj.getVar().set_vector(6,1);
            obj.sq_SetShake(obj, 5, 200 * 100 / obj.getVar("speed").get_vector(0));
        }else if (frmIndex >= 15 && obj.getVar().get_vector(7) == 0)
        {
            obj.getVar().set_vector(7,1);
            obj.sq_SetShake(obj, 1, 200 * 100 / obj.getVar("speed").get_vector(0));
        }



    }
}

function onAttack_BLOODSCREAM(obj, damager, boundingBox, isStuck)
{
    local state = obj.getSkillSubState();
    if (state == 0)
    {
        if(damager)
        {
            obj.getVar("dama").push_obj_vector(damager);
        }
    }else if (state == 1)
    {
    }else if (state == 2)
    {
            setCustomHitEffectBloodMageBlow(obj,damager);
//            createBloodStreamHitEffect_HoldEffect(obj,damager);
//            createBloodStreamHitEffect_HoldEffect2(obj,damager);

            if (obj && !CNSquirrelAppendage.sq_IsAppendAppendage(obj,
                "character/atmage/append_bloodmage/ap_bloodstream_character.nut") )
            {
                local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BLOODSCREAM, false, 
                "character/atmage/append_bloodmage/ap_bloodstream_character.nut", true);
                
            }

            if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/bloodscream/ap_bloodscream.nut"))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj,
                SKILL_BLOODSCREAM, false, "character/atmage/bloodscream/ap_bloodscream.nut", true);				 

            }

    }else if (state == 3)
    {

            if (obj && !CNSquirrelAppendage.sq_IsAppendAppendage(obj,
                "character/atmage/append_bloodmage/ap_bloodstream_character.nut") )
            {
                local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BLOODSCREAM, false, 
                "character/atmage/append_bloodmage/ap_bloodstream_character.nut", true);
                
            }

            if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/bloodscream/ap_bloodscream.nut"))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODSCREAM, false, 
                "character/atmage/bloodscream/ap_bloodscream.nut", true);				 

            }

    }else if (state == 4)
    {


        if (obj.getVar("flag").get_vector(0) == 1)
        {
            if (damager && !CNSquirrelAppendage.sq_IsAppendAppendage(damager,
                "character/atmage/append_bloodmage/ap_bloodstream.nut") )
            {
                local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODSCREAM, false, 
                "character/atmage/append_bloodmage/ap_bloodstream.nut", true);
                
            }

            if (CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/bloodscream/ap_bloodscream.nut"))
            {
                    CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/bloodscream/ap_bloodscream.nut");		
            }
        }
    }
}


function createUIAniWithIDPath(obj,id,path)
{
    obj = sq_GetCNRDObjectToSQRCharacter(obj);
    local sq_var = obj.getVar();
	local ani = sq_var.GetAnimationMap("skillAwakeningID_31", 
        "character/mage/atanimation/cutin/atmage_vampirelord.ani");
    local size = sq_GetAniRealImageSize(ani, obj.getDirection() );
	local rate = 800.0 / size.tofloat();

	if (obj.getDirection() == ENUM_DIRECTION_LEFT)
	{
		ani.setImageRate(-0.74976,1.0);
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani,800, 0, false);
	}else
	{
		ani.setImageRate(0.74976,1.0);
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani,0, 0, false);
	}
    //local ani = sq_var.GetAnimationMap("skillAwakeningID_" + id, path );
    //ani.setCurrentFrameWithChildLayer(0);

}
