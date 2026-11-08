//2019 6 19
//?B?? ?q??s


function checkExecutableSkill_bloodsong(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_BLOODSONG);
	if (isUseSkill) {
        obj.sq_AddSetStatePacket(STATE_BLOODSONG, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function onEndCurrentAni_BLOODSONG(obj)
{
    obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function checkCommandEnable_bloodsong(obj)
{
	if(!obj)
    if (judgeSubBloodValue(obj, getBloodValue_BloodSong(obj) )) 
    {
        return false;
    }
	return true;
}

function getBloodValue_BloodSong(obj)
{
    if (obj.sq_GetSkillLevel(SKILL_BLOODSONG) >= 3)
    {
        local addBlood = 100 + obj.sq_GetIntData(SKILL_BLOODSONG, 13);
        return (obj.sq_GetIntData(SKILL_BLOODSONG, 8) * addBlood) / 100;
    }
    return obj.sq_GetIntData(SKILL_BLOODSONG, 8);
}

function onSetState_BLOODSONG(obj, state, datas, isResetTimer)
{
    local speed = obj.sq_GetIntData(SKILL_BLOODSONG, 10);
    setBloodValue(obj, -getBloodValue_BloodSong(obj) );
    obj.getVar("speed").clear_vector();
    obj.getVar("speed").push_vector(speed);
    local objectManager = obj.getObjectManager();
    sq_flashScreen(obj,1200 / (obj.getVar("speed").get_vector(0) / 100),0,1900 / (obj.getVar("speed").get_vector(0) / 100),230, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);


    obj.getVar("dama").clear_obj_vector();
    obj.getVar("attackHeight").clear_vector();
    obj.getVar("attackHeight").push_vector(obj.sq_GetIntData(SKILL_BLOODSONG,2));


    obj.getVar("count").clear_vector();
    obj.getVar("count").push_vector(0);

    obj.getVar("isUp").clear_vector();
    obj.getVar("isUp").push_vector(0);

	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOODSONG_BODY);
    obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWBLOODSONG_SPEAR);

    local currentAni = sq_GetCurrentAnimation(obj);
	currentAni.setSpeedRate(obj.getVar("speed").get_vector(0).tofloat() );				


    local xPos = objectManager.getFieldXPos(obj.sq_GetIntData(SKILL_BLOODSONG,0)+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
    local yPos = objectManager.getFieldYPos(obj.sq_GetIntData(SKILL_BLOODSONG,1), 0, ENUM_DRAWLAYER_NORMAL);


    obj.sq_StartWrite();
    obj.sq_WriteDword(10);	// attackBonusRate
    sq_SendCreatePassiveObjectPacketPos(obj,24341, 0, xPos, yPos, 0 );

    sq_SendCreatePassiveObjectPacketPos(obj,12321, 0, xPos, yPos, 0 );
    sq_SendCreatePassiveObjectPacketPos(obj,12322, 0, xPos, yPos, 0 );

    obj.sq_StartWrite();
    obj.sq_WriteDword(0);	// attackBonusRate
    obj.sq_WriteDword(52);	// attackBonusRate
    sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, xPos, yPos, 0 );

    obj.getVar("state").clear_vector();
    obj.getVar("state").push_vector(1);

    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);

    obj.getVar("spear").clear_vector();
    obj.getVar("spear").push_vector(0);

    local rate = 100;
    if (obj.sq_GetSkillLevel(SKILL_BLOODSONG) >= 9)
    {
        rate = rate + obj.sq_GetIntData(SKILL_BLOODSONG,15);
    }
    local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSONG , STATE_BLOODSONG, 0, rate.tofloat() / 100.0 );
    obj.sq_SetCurrentAttackBonusRate(damage);				

}

function sendLastDamagePassiveObject_BLOODSONG(obj)
{
        local var = obj.getVar("dama");  		
        for(local i = 0;i<var.get_obj_vector_size();++i)
        {
            local damager = var.get_obj_vector(i);
            sq_SendCreatePassiveObjectPacketPos(obj,12372, 0,  damager.getXPos(),  damager.getYPos(),  damager.getZPos() );
        }

}

function passSpeedAdd_BLOODSONG(obj)
{
    local speed = obj.getVar("speed").get_vector(0);
    local speedRate = speed.tofloat();
    local iceCoreObj = null;
    local currentAnip = null;
    iceCoreObj = obj.getMyPassiveObject(24341,0);
    if(iceCoreObj)
    {
        currentAnip = sq_GetCurrentAnimation(iceCoreObj);
        currentAnip.setSpeedRate(speedRate);				
    }
    iceCoreObj = obj.getMyPassiveObject(12321,0);
    if(iceCoreObj)
    {
        currentAnip = sq_GetCurrentAnimation(iceCoreObj);
        currentAnip.setSpeedRate(speedRate);				
    }
    iceCoreObj = obj.getMyPassiveObject(12322,0);
    if(iceCoreObj)
    {
        currentAnip = sq_GetCurrentAnimation(iceCoreObj);
        currentAnip.setSpeedRate(speedRate);				
    }
    iceCoreObj = obj.getMyPassiveObject(24357,0);
    if(iceCoreObj)
    {
        currentAnip = sq_GetCurrentAnimation(iceCoreObj);
        currentAnip.setSpeedRate(speedRate);				
    }

}

function sendOneDamage_BLOODSONG(obj)
{
        local var = obj.getVar("dama");  		

        if ( var.get_obj_vector_size() > 0 )
        {

            local currC = obj.getVar("count").get_vector(0);
            local curr = obj.getVar("attackHeight").get_vector(0);
            obj.getVar("attackHeight").set_vector(0,obj.sq_GetIntData(SKILL_BLOODSONG,3) + curr);
            if ( obj.getVar("spear").get_vector(0) == 0)
            {
                obj.sq_SetShake(obj, 7, 100);
            }else{
                obj.sq_SetShake(obj, 6, 100);
            }
            obj.getVar("count").set_vector(0,currC + 1);

            local audioValue = sq_getRandom(0,4);

            if  (audioValue > 1)
            {
//                obj.sq_PlaySound("BLOODSONG0");
                obj.sq_PlaySound("BLOODSONG00");
            }else if  (audioValue > 2){
//                obj.sq_PlaySound("BLOODSONG1");
                obj.sq_PlaySound("BLOODSONG01");
            }else if  (audioValue > 3){
//                obj.sq_PlaySound("BLOODSONG2");
                obj.sq_PlaySound("BLOODSONG02");
            }else{
//                obj.sq_PlaySound("BLOODSONG3");
                obj.sq_PlaySound("BLOODSONG00");
            }




            for(local i = 0;i<var.get_obj_vector_size();++i)
            {
                local damager = var.get_obj_vector(i);
                sq_SendHitObjectPacket(obj,damager,0,0,0);
                spearHitEffect1(obj,damager);
                spearHitEffect2(obj,damager);
            }


            local rate = obj.sq_GetIntData(SKILL_BLOODSONG,9);
            if (obj.sq_GetSkillLevel(SKILL_BLOODSONG) >= 6)
            {
                rate = (rate * (100 + obj.sq_GetIntData(SKILL_BLOODSONG,14) )  ) / 100;
            }
            setBloodValue(obj, rate );
    }
}

function spearHitEffect1(obj,damager)
{
    local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/tepes_blood1.ani");
    local speed = obj.getVar("speed").get_vector(0);
    local speedRate = speed.tofloat();
    ani.setSpeedRate( speedRate );

    local sizeRate = 100.0;

    if ( !sq_IsFixture(damager) )
    {
        sizeRate = damager.getObjectHeight();
        sizeRate = sizeRate.tofloat()/100.0;
    }
	ani.resize(sizeRate);
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() - 3,damager.getZPos() );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function spearHitEffect2(obj,damager)
{
    local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/tepes_blood2.ani");
    local speed = obj.getVar("speed").get_vector(0);
    local speedRate = speed.tofloat();
    ani.setSpeedRate( speedRate );
    local sizeRate = 100.0;

    if ( !sq_IsFixture(damager) )
    {
        sizeRate = damager.getObjectHeight();
        sizeRate = sizeRate.tofloat()/100.0;
    }


	ani.resize(sizeRate);
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() - 2,damager.getZPos() );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createSpear_BLOODSONG(obj,damager,value1,value2)
{
    local hei = 1000;
    if ( !sq_IsFixture(damager) )
    {
        hei = damager.getObjectHeight();
    }
    local ani = null;
    local rand = sq_getRandom(value1,value2).tointeger();
    if (hei < obj.sq_GetIntData(SKILL_BLOODSONG,4) )
    {
        if (rand == 0)
        {
            ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/spearc_1_j.ani");
        }else if(rand == 1)
        {
            ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/spearc_2_j.ani");
        }else if (rand == 2)
        {
            ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/spearc_3_j.ani");
        }else{
            ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/spearc_4_j.ani");
        }
    }else if (hei < obj.sq_GetIntData(SKILL_BLOODSONG,5))
    {
        if (rand == 0)
        {
            ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/spearb_1_j.ani");
        }else if(rand == 1)
        {
            ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/spearb_2_j.ani");
        }else if (rand == 2)
        {
            ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/spearb_3_j.ani");
        }else{
            ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/spearb_4_j.ani");
        }
    }else{
        if (rand == 0)
        {
            ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/speara_1_j.ani");
        }else if(rand == 1)
        {
            ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/speara_2_j.ani");
        }else if (rand == 2)
        {
            ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/speara_3_j.ani");
        }else{
            ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/speara_4_j.ani");
        }
    }

    local speed = obj.getVar("speed").get_vector(0) * 100 / 115;
    ani.setSpeedRate( speed.tofloat() );
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 2,damager.getZPos() );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}

function onKeyFrameFlag_BLOODSONG(obj,flagIndex)
{
    if (flagIndex == 1 && obj.getVar("flag").get_vector(0) == 0)
    {

        sq_flashScreen(obj,0,80,0,153, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
        obj.sq_SetShake(obj, 20,240 );

        obj.getVar("flag").set_vector(0,1);
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
        obj.getVar("spear").clear_vector();
        obj.getVar("spear").push_vector(2);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWBLOODSONG_LAST);
        sendLastDamagePassiveObject_BLOODSONG(obj);


        local rate = 100;
        if (obj.sq_GetSkillLevel(SKILL_BLOODSONG) >= 9)
        {
            rate = rate + obj.sq_GetIntData(SKILL_BLOODSONG,16);
        }
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSONG , STATE_BLOODSONG, 1, rate.tofloat() / 100.0 );
        obj.sq_SetCurrentAttackBonusRate(damage);				


        local var = obj.getVar("dama");  		

        if (var.get_obj_vector_size() > 0 )
        {

            for(local i=0;i<var.get_obj_vector_size();++i)
            {
                local damager = var.get_obj_vector(i);

                if(damager)
                {
                    CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/bloodsong/ap_bloodsong.nut");		
                }

            }
        }

    }else if (flagIndex == 2 && obj.getVar("flag").get_vector(1) == 0)
    {

        obj.getVar("flag").set_vector(1,1);
        findAllMonster_BLOODSONG(obj);

        local var = obj.getVar("dama");  		
        for(local i=0;i<var.get_obj_vector_size();++i)
        {
            local damager = var.get_obj_vector(i);

        if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/bloodsong/ap_bloodsong.nut"))
        {
            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODSONG, false, "character/atmage/bloodsong/ap_bloodsong.nut", true);				 
            sq_HoldAndDelayDie(damager, obj, false, true, true, 0, 0, ENUM_DIRECTION_DOWN , masterAppendage);
        }


            //addSpearCommand
            createSpear_BLOODSONG(obj,damager,0,1);
            createSpear_BLOODSONG(obj,damager,2,3);

            sq_SendHitObjectPacket(obj,damager,0,0,0);

            sq_EffectLayerAppendage(damager,sq_RGB(0,0,0),255,0,4000  / (obj.getVar("speed").get_vector(0) / 100),0);	


            obj.sq_timer_.setParameter(100 * obj.sq_GetIntData(SKILL_BLOODSONG,6) / obj.getVar("speed").get_vector(0), 999);
            obj.sq_timer_.resetInstant(0);

            obj.getVar("spear").clear_vector();
            obj.getVar("spear").push_vector(1);

        }

    }else if (flagIndex == 3)
    {

    }else if (flagIndex == 4 && obj.getVar("flag").get_vector(4) == 0 ){
            obj.getVar("flag").set_vector(4,1);
            obj.getVar("isUp").clear_vector();
            obj.getVar("isUp").push_vector(1);
            obj.sq_timer_.setParameter(100 * obj.sq_GetIntData(SKILL_BLOODSONG,7) /  obj.getVar("speed").get_vector(0), 999);
            obj.sq_timer_.resetInstant(0);
    }else if (flagIndex == 300){
//        sq_flashScreen(obj,0 ,200,10,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
    }
}

function onProc_BLOODSONG(obj)
{
    local pAni = obj.sq_GetCurrentAni();
    local currentT = sq_GetCurrentTime(pAni);
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);

    if (frmIndex == 13)
    {
        obj.sq_SetShake(obj, 18,240 );
        //sq_flashScreen(obj,0,0,1000,150, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
    }else if (frmIndex == 19)
    {
        sq_flashScreen(obj,0,160,0,250, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
    }else if (frmIndex == 21)
    {
        sq_flashScreen(obj,0,0,160,250, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
    }
    
    if (obj.sq_timer_.isOnEvent(currentT) == true && obj.getVar("state").get_vector(0) == 1 )
    {
        sendOneDamage_BLOODSONG(obj);
    }
    passSpeedAdd_BLOODSONG(obj);

//    if (obj.getVar("state").get_vector(0) == 3)
//    {
//        local iceCoreObj = obj.getMyPassiveObject(12322,0);
//        if (iceCoreObj)
//        {
//            sq_SendDestroyPacketPassiveObject(iceCoreObj);	
//        }
//    }

}

function findAllMonster_BLOODSONG(obj)
{

	local objectManager = obj.getObjectManager();
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) )
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);
            
            if ( true )
            {
                if (abs( activeObj.getXPos() - obj.getXPos()) <= obj.sq_GetIntData(SKILL_BLOODSONG, 11) && abs( activeObj.getYPos() - obj.getYPos()) <= obj.sq_GetIntData(SKILL_BLOODSONG, 12) )
                {
                    obj.getVar("dama").push_obj_vector(activeObj);


                }
            }
		}
	}

}
