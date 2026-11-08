//set flag 0 drop shake 
//set flag 1 create SpearPassiveObject
//set flag 2 setLastAtk
//set flag 3 last shake flashScreen
//set flag 4 xishou 
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
    sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
	if(!obj.isMyControlObject()) {
		return;
	}

    obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}





function getBloodValue_BloodSong(obj)
{
    if (obj.sq_GetSkillLevel(SKILL_BLOODSONG) >= 3)
    {
//        local addBlood = 100 + obj.sq_GetIntData(SKILL_BLOODSONG, 13);
//        return (obj.sq_GetIntData(SKILL_BLOODSONG, 8) * addBlood) / 100;
    }
    return obj.sq_GetIntData(SKILL_BLOODSONG, 8);
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

function onTimeEvent_BLOODSONG(obj, timeEventIndex, timeEventCount)
{


//    obj.getVar("len2").clear_vector();
//    obj.getVar("len2").push_vector(0);
//    local len = obj.getVar("spearObj").get_obj_vector_size();
//    if (len > 0)
//    {
//        obj.setTimeEvent(0,200 / len,len,false);
//    }

    local len = obj.getVar("spearObj").get_obj_vector_size();
    
    if(!obj.isMyControlObject())
        return ;

    if (len > 0)
    {

            
            local objID = obj.getVar("len2").get_vector(0);
            local activeObj = obj.getVar("spearObj").get_obj_vector(objID);
            obj.getVar("len2").set_vector(0, objID + 1);

            local id = sq_GetObjectId(activeObj);

            local rate = 100;
            if (obj.sq_GetSkillLevel(SKILL_BLOODSONG) >= 9)
            {
                rate = rate + obj.sq_GetIntData(SKILL_BLOODSONG,16);
            }

            local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSONG , STATE_BLOODSONG, 0, rate.tofloat() / 100.0 );
            sq_BinaryStartWrite();
            sq_BinaryWriteDword(damage);
            sq_BinaryWriteDword(100);
            sq_BinaryWriteDword(id);
            sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODSONG, 26) );
            sq_BinaryWriteDword( obj.getVar("speed").get_vector(0) );
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);

            if (activeObj && !CNSquirrelAppendage.sq_IsAppendAppendage(activeObj,
                "character/atmage/append_bloodmage/ap_bloodsong.nut"))
            {
                local appendage = CNSquirrelAppendage.sq_AppendAppendage(activeObj, obj, SKILL_BLOODSONG, false, 
                "character/atmage/append_bloodmage/ap_bloodsong.nut", true);
                
            }


    }

//        obj.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);
}

function onSetState_BLOODSONG(obj, state, datas, isResetTimer)
{


//	obj.setTimeEvent(0,300,0,false);
    if (obj.isMyControlObject())
    {
        setBloodValue(obj, -getBloodValue_BloodSong(obj) );
        sq_flashScreen(obj,1200,0,1900,230, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
    }
	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOODSONG_BODY);
//    obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWBLOODSONG_SPEAR);



    local objectManager = obj.getObjectManager();
    local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
    local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);


    obj.getVar("centerPos").clear_vector();
    obj.getVar("centerPos").push_vector(xPos);
    obj.getVar("centerPos").push_vector(yPos);

    obj.getVar("effctObj").clear_obj_vector();
    
    obj.getVar("dama").clear_obj_vector();
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);//0
    obj.getVar("flag").push_vector(0);//1
    obj.getVar("flag").push_vector(0);//2
    obj.getVar("flag").push_vector(0);//3
    obj.getVar("flag").push_vector(0);//4
    obj.getVar("flag").push_vector(0);


    local speed = obj.sq_GetIntData(SKILL_BLOODSONG,17);

    obj.getVar("speed").clear_vector();
    obj.getVar("speed").push_vector(speed);

    local currentAni = sq_GetCurrentAnimation(obj);
	currentAni.setSpeedRate(obj.getVar("speed").get_vector(0).tofloat() );				

    createTepesGroundSpear(obj);

    if (obj.isMyControlObject() )
    {

        createTepesFlares(obj);
        createTepesGround(obj);
        createTepesSkyGround(obj);
    }
}

//set flag 0 drop shake 
//set flag 1 create SpearPassiveObject
//set flag 2 setLastAtk
//set flag 3 last shake flashScreen
//set flag 4 xishou 

function onKeyFrameFlag_BLOODSONG(obj,flagIndex)
{
    if (!obj.isMyControlObject() )
    {
        return true;
    }
    if (obj.getVar("flag").get_vector(flagIndex) == 0)
    {

        obj.getVar("flag").set_vector(flagIndex,1);

        if (flagIndex == 0)
        {
            obj.sq_SetShake(obj, 18,240 );
            createSpearTime(obj);

        }else if (flagIndex == 1)
        {

            setAtTepesSpearBeforeHold(obj);
//            createSpearTime(obj);
//            createTepesSpear(obj);
        }else if (flagIndex == 2)
        {
            sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
            obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWBLOODSONG_LAST);
            local rate = 100;
            if (obj.sq_GetSkillLevel(SKILL_BLOODSONG) >= 9)
            {
                rate = rate + obj.sq_GetIntData(SKILL_BLOODSONG,16);
            }
            local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSONG , STATE_BLOODSONG, 1, rate.tofloat() / 100.0 );
            obj.sq_SetCurrentAttackBonusRate(damage);				

        }else if (flagIndex == 3)
        {


            sq_flashScreen(obj,0,80,0,153, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
            obj.sq_SetShake(obj, 20,240 );


        }else if (flagIndex == 4)
        {
            obj.sq_SetShake(obj, 20,240 );
            setVliadEffectTepesPassiveObject(obj);
            sq_flashScreen(obj,0,160,160,250, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        }
    }

}


function setAtTepesSpearBeforeHold(obj)
{

//    obj.getVar("spearObj").clear_obj_vector();

	local objectManager = obj.getObjectManager();
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) && 
            object.isInDamagableState(obj) )
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);

            if (!CNSquirrelAppendage.sq_IsAppendAppendage(activeObj, "character/atmage/bloodsong/ap_tepes.nut"))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(activeObj, 
                obj, SKILL_BLOODSCREAM, false, "character/atmage/bloodsong/ap_tepes.nut", true);				 

            }

        }
    }
}

function createSpearTime(obj)
{

    
    obj.getVar("spearObj").clear_obj_vector();


	local objectManager = obj.getObjectManager();
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) && 
            object.isInDamagableState(obj) )
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);
            obj.getVar("spearObj").push_obj_vector( activeObj );


            if (CNSquirrelAppendage.sq_IsAppendAppendage(activeObj, "character/atmage/bloodsong/ap_tepes.nut"))
            {
                CNSquirrelAppendage.sq_RemoveAppendage(activeObj, "character/atmage/bloodsong/ap_tepes.nut");		    
                
            }

        }
    }

    obj.getVar("len2").clear_vector();
    obj.getVar("len2").push_vector(0);
    local len = obj.getVar("spearObj").get_obj_vector_size();
    if (len > 0)
    {
        obj.setTimeEvent(0, obj.sq_GetIntData(SKILL_BLOODSONG, 29) / len,len,false);

            if (obj)
            {
                local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BLOODSONG, false, 
                "character/atmage/append_bloodmage/ap_bloodsong_character.nut", true);
                
            }

    }

}

function onAttack_BLOODSONG(obj, damager, boundingBox, isStuck)
{
    createTepesHitBoom(obj,damager);
}

function createTepesHitBoom(obj,damager)
{

    local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/tepes_boom.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createTepesHitEffect1(obj,damager)
{

    local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/tepes_blood1.ani");

    local speed = obj.getVar("speed").get_vector(0);
    local speedRate = speed.tofloat();
    ani.setSpeedRate( speedRate );

    local size = 100;
    local sizeRate = size.tofloat() / 200.0;
    ani.setImageRateFromOriginal(sizeRate, sizeRate);
    ani.setAutoLayerWorkAnimationAddSizeRate(sizeRate);
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() - 1,damager.getZPos() + damager.getObjectHeight() / 2);
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createTepesHitEffect2(obj,damager)
{

    local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/tepes_blood2.ani");

    local speed = obj.getVar("speed").get_vector(0);
    local speedRate = speed.tofloat();
    ani.setSpeedRate( speedRate );

    local size = 100;
//    local size = damager.getObjectHeight() / 2;
    local sizeRate = size.tofloat() / 200.0;
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() - 1,damager.getZPos() + damager.getObjectHeight() / 2);
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function setCharacterFristAnimation_Tepes(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_BLOODSONG );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/tepes_boom.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/tepes_blood1.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/tepes_blood2.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/ground_spear1_m.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/tepes_flares_00.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/tepes_sky_bg1_2.ani");

        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/tepes_ground_1.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/tepes_sky_bg1_2.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/speara_1_j.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/speara_2_j.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/speara_3_j.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/speara_4_j.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/spearb_1_j.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/spearb_2_j.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/spearb_3_j.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/spearb_4_j.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/spearc_1_j.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/spearc_2_j.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/spearc_3_j.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/attepes/spearc_4_j.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/newbloodsong/tepes_main_body2.ani");

    }
}

function createTepesGroundSpear(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/ground_spear1_m.ani");
	ani.setSpeedRate(obj.getVar("speed").get_vector(0).tofloat() );
	local pooledObj = sq_CreatePooledObject(ani,true);

//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
    local objectManager = obj.getObjectManager();
    local xPos = objectManager.getFieldXPos(400, ENUM_DRAWLAYER_NORMAL);
    local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(xPos ,yPos,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effctObj").push_obj_vector( pooledObj );
}



function createTepesFlares(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/tepes_flares_00.ani");
	ani.setSpeedRate(obj.getVar("speed").get_vector(0).tofloat() );
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_COVER);
    local objectManager = obj.getObjectManager();
    local xPos = objectManager.getFieldXPos(400, ENUM_DRAWLAYER_NORMAL);
    local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(xPos ,yPos,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effctObj").push_obj_vector( pooledObj );
}

function createTepesSkyGround(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/tepes_sky_bg1_2.ani");
	ani.setSpeedRate(obj.getVar("speed").get_vector(0).tofloat() );
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
    local objectManager = obj.getObjectManager();
    local xPos = objectManager.getFieldXPos(400, ENUM_DRAWLAYER_NORMAL);
    local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL) - 1;
	pooledObj.setCurrentPos(xPos ,yPos,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

    obj.getVar("effctObj").push_obj_vector( pooledObj );

}

function createTepesGround(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/attepes/tepes_ground_1.ani");
	ani.setSpeedRate(obj.getVar("speed").get_vector(0).tofloat() );
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
    local objectManager = obj.getObjectManager();
    local xPos = objectManager.getFieldXPos(400, ENUM_DRAWLAYER_NORMAL);
    local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);
	pooledObj.setCurrentPos(xPos ,yPos,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effctObj").push_obj_vector( pooledObj );
}


function onEndState_BLOODSONG(obj, new_state)
{
    if (new_state != STATE_BLOODSONG)
    {
        sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
        setVliadEffectTepesPassiveObject(obj);
    }
}

function setVliadEffectTepesPassiveObject(obj)
{
    local var = obj.getVar("effctObj");  		
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



function createTepesSpear22(obj)
{

	local objectManager = obj.getObjectManager();
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) )
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);
            
            local id = sq_GetObjectId(activeObj);

            local rate = 100;
            if (obj.sq_GetSkillLevel(SKILL_BLOODSONG) >= 9)
            {
                rate = rate + obj.sq_GetIntData(SKILL_BLOODSONG,16);
            }
            local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSONG , STATE_BLOODSONG, 0, rate.tofloat() / 100.0 );
//            sq_EffectLayerAppendage(activeObj,sq_RGB(0,0,0),255,0,4000,0);	

            sq_BinaryStartWrite();
            sq_BinaryWriteDword(damage);
            sq_BinaryWriteDword(100);
            sq_BinaryWriteDword(id);
            sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODSONG, 26));
            sq_BinaryWriteDword(obj.getVar("speed").get_vector(0) );

            obj.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);

        }
    }
}




function getAtTepesPassiveAnimation(obj,id)
{
    local ani = null;

    if (id == 133)
    {
        ani = obj.getVar().GetAnimationMap("", 
                    "passiveobject/zrr_skill/atmage/animation/attepes/speara_1_j.ani"); 
    }else if (id == 134)
    {
        ani = obj.getVar().GetAnimationMap("", 
                    "passiveobject/zrr_skill/atmage/animation/attepes/speara_2_j.ani"); 
    }else if (id == 135)
    {
        ani = obj.getVar().GetAnimationMap("", 
                    "passiveobject/zrr_skill/atmage/animation/attepes/speara_3_j.ani"); 
    }else if (id == 136)
    {
        ani = obj.getVar().GetAnimationMap("", 
                    "passiveobject/zrr_skill/atmage/animation/attepes/speara_4_j.ani"); 
    }else if (id == 137)
    {
        ani = obj.getVar().GetAnimationMap("", 
                    "passiveobject/zrr_skill/atmage/animation/attepes/spearb_1_j.ani"); 
    }else if (id == 138)
    {
        ani = obj.getVar().GetAnimationMap("", 
                    "passiveobject/zrr_skill/atmage/animation/attepes/spearb_2_j.ani"); 
    }else if (id == 139)
    {
        ani = obj.getVar().GetAnimationMap("", 
                    "passiveobject/zrr_skill/atmage/animation/attepes/spearb_3_j.ani"); 
    }else if (id == 140)
    {
        ani = obj.getVar().GetAnimationMap("", 
                    "passiveobject/zrr_skill/atmage/animation/attepes/spearb_4_j.ani"); 
    }else if (id == 141)
    {
        ani = obj.getVar().GetAnimationMap("", 
                    "passiveobject/zrr_skill/atmage/animation/attepes/spearc_1_j.ani"); 
    }else if (id == 142)
    {
        ani = obj.getVar().GetAnimationMap("", 
                    "passiveobject/zrr_skill/atmage/animation/attepes/spearc_2_j.ani"); 
    }else if (id == 143)
    {
        ani = obj.getVar().GetAnimationMap("", 
                    "passiveobject/zrr_skill/atmage/animation/attepes/spearc_3_j.ani"); 
    }else if (id == 144)
    {
        ani = obj.getVar().GetAnimationMap("", 
                    "passiveobject/zrr_skill/atmage/animation/attepes/spearc_4_j.ani"); 
    }
    return ani;

}

























