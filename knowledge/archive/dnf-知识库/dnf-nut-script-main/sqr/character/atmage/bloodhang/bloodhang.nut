function checkExecutableSkill_bloodhang(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_BLOODHANG);
	if (isUseSkill) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);	// subState????
		obj.sq_AddSetStatePacket(STATE_BLOODHANG, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_bloodhang(obj)
{
	if(!obj)
		return false;
	local state = obj.sq_GetState();
		
    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_BLOODHANG, 0)))
        return false;
	return true;
}


function setCharacterFristAnimation_Fatality(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_BLOODHANG );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/bloodhang/light0.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atfatality/floor/fatality_startground_whirl2.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atfatality/floor/fatality_attackground_whirl2.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atfatality/fatality_attackbg_bg.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atfatality/fatality_attackhit_hitdodge.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atfatality/fatality_finishhit_bigblood.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atfatality/floor/fatality_finishcloud_cloud1.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atfatality/floor/fatality_finishground_tormentd_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atfatality/hands/fatality_grabstart_hand1.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atfatality/hands/fatality_grabend_hand1.ani");

        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/bloodhang/fatality_start_body.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/bloodhang/fatality_attack_body.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/bloodhang/fatality_attackfail_body.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/bloodhang/fatality_finish_body.ani");



    }
}


function createWave_BLOODHANG(obj,len,z)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/bloodhang/light0.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), len);
	
	pooledObj.setCurrentPos(posX,obj.getYPos() + 1,obj.getZPos() + z + 10);
	
	pooledObj.setCurrentDirection(obj.getDirection());
	
	sq_AddObject(obj,pooledObj,0,false);	
}



function createFatality_StartFloorGround(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfatality/floor/fatality_startground_whirl2.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 150);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}

function createFatality_AttackFloorGround(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfatality/floor/fatality_attackground_whirl2.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 150);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}

function createFatality_AttackBg(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfatality/fatality_attackbg_bg.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);

    local objectManager = obj.getObjectManager();
    local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
    local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);

	pooledObj.setCurrentPos(xPos  ,yPos - 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}

function createFatality_AttackHitEffect(obj,damager)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfatality/fatality_attackhit_hitdodge.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createFatality_FinishHitEffect(obj,damager)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfatality/fatality_finishhit_bigblood.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(damager.getXPos(), damager.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,damager.getYPos() + 1,damager.getZPos() + damager.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}

function createFatality_FinishCloud(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfatality/floor/fatality_finishcloud_cloud1.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 2,0 );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}

function createFatality_FinishWhirl(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfatality/floor/fatality_finishground_tormentd_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 150);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,0 );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}

function createFatality_FinishBg(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfatality/fatality_finishbg_bg.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);

    local objectManager = obj.getObjectManager();
    local xPos = objectManager.getFieldXPos(400, ENUM_DRAWLAYER_NORMAL);
    local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);

	pooledObj.setCurrentPos(xPos  ,yPos - 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}

function createFatality_FinishBg2(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfatality/fatality_finish_screenblue.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);

    local objectManager = obj.getObjectManager();
    local xPos = objectManager.getFieldXPos(400, ENUM_DRAWLAYER_NORMAL);
    local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);

	pooledObj.setCurrentPos(xPos  ,yPos - 2,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}

function createFatality_BloodHangStart(obj,x,y,z)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfatality/hands/fatality_grabstart_hand1.ani");
	ani.setSpeedRate(200.0);				

	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + y,z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createFatality_BloodHangEnd(obj,x,y,z)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfatality/hands/fatality_grabend_hand1.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + y,z);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function findAllMonster_BLOODHANG(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
	local objectManager = obj.getObjectManager();

	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) )
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);

            local objX = sq_GetDistancePos(obj.getXPos() , obj.getDirection(),obj.getVar("posX").get_vector(0) );
            local objY = obj.getYPos();

            local distance = sq_Abs( activeObj.getXPos() - objX );
            distance = distance * distance;
            distance += sq_Abs( activeObj.getYPos() - objY ) * sq_Abs( activeObj.getYPos() - objY );
            if ( !sq_IsFixture(activeObj) && distance <= obj.sq_GetIntData(SKILL_BLOODHANG, 6) * obj.sq_GetIntData(SKILL_BLOODHANG, 6) )
            {
                obj.getVar("dama").push_obj_vector(activeObj);

                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(activeObj, obj, SKILL_BLOODHANG, false, "character/atmage/bloodhang/ap_hang_pull.nut", true);				 


                masterAppendage.getVar("pos2").clear_vector();
                masterAppendage.getVar("pos2").push_vector(objX);
                masterAppendage.getVar("pos2").push_vector(objY);

            }
		}
	}

}

//CUSTOM_ANI_ATFATALITY_ATTACK_FAIL


function onEndState_BLOODHANG(obj, new_state)
{
    if (new_state != STATE_BLOODHANG)
    {
        setVliadEffectAtFatailtyPassiveobject(obj);
    }
}

function getScrollBasisPos_BLOODHANG(obj)
{
    if (!obj || isEventHorizen(obj) )
        return false;

	if (obj.sq_GetSkillSubState(obj) == 0) 
    {
	}else if (obj.sq_GetSkillSubState(obj) == 1) 
    {
        local startX = obj.getVar("pos").get_vector( 0 );
        local startY = obj.getVar("pos").get_vector( 1 );

	}else if (obj.sq_GetSkillSubState(obj) == 2) 
    {

	}else if (obj.sq_GetSkillSubState(obj) == 3)
    {

    }

}


function onSetState_BLOODHANG(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	obj.sq_StopMove();


	local subState = obj.sq_GetVectorData(datas, 0);	// subState
	obj.sq_SetSkillSubState(obj, subState);
	local xiDistance = obj.sq_GetIntData(SKILL_BLOODHANG, 4);
	if (subState == 0)
	{
        if ( obj.isMyControlObject() )
            createFatality_StartFloorGround(obj);


        obj.getVar("floorObj").clear_obj_vector();
        obj.getVar("posX").clear_vector();
        obj.getVar("posX").push_vector(xiDistance);
        setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOODHANG, 0) );

        obj.getVar("dama").clear_obj_vector();
        obj.getVar("dama2").clear_obj_vector();
        findAllMonster_BLOODHANG(obj);
        obj.setTimeEvent(0,obj.sq_GetIntData(SKILL_BLOODHANG, 1),0,false);		
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODHANG_0);
        obj.getVar("pos").clear_vector();
        obj.getVar("pos").push_vector( obj.getXPos() );
        obj.getVar("pos").push_vector( obj.getYPos() );




	}
	else if (subState == 1)
	{
        if (obj.isMyControlObject())
        {
            setVliadEffectAtFatailtyPassiveobject(obj);
            createFatality_BloodHangStart(obj,xiDistance,1,0);
            createFatality_AttackFloorGround(obj);
            createFatality_AttackBg(obj);
        }


		sq_flashScreen(obj,0,1000,1000,150, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODHANG_1);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWBLOOD45_MOVE );

        local xyProc = 100;//sq_GetLevelData(obj, SKILL_BLOODHANG, 1, sq_GetSkillLevel(obj, SKILL_BLOODHANG) );
        local xyLevel = 100;//sq_GetLevelData(obj, SKILL_BLOODHANG, 2, sq_GetSkillLevel(obj, SKILL_BLOODHANG) );
        local xyTime =  obj.sq_GetIntData(SKILL_BLOODHANG, 3);
        //sq_GetLevelData(obj, SKILL_BLOODHANG, 3, sq_GetSkillLevel(obj, SKILL_BLOODHANG) );

        local attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, ACTIVESTATUS_STUN, xyProc, xyLevel, xyTime);
        obj.getVar().clear_vector();
        obj.getVar().push_vector(0);
        
	}else if (subState == 2)
    {
        if (obj.isMyControlObject())
        {
            createFatality_FinishCloud(obj);
            createFatality_FinishWhirl(obj);
            createFatality_BloodHangEnd(obj,xiDistance,1,0);
            createFatality_FinishBg(obj);
        }

//        obj.sq_SendCreatePassiveObjectPacket(12279, 0, xiDistance, 1, 50);
        local len = obj.sq_GetIntData(SKILL_BLOODHANG, 4);
        local damager = obj.getVar("dama").get_obj_vector(0);

        local objectManager = obj.getObjectManager();
        local xPos = objectManager.getFieldXPos(400, ENUM_DRAWLAYER_NORMAL);
        local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);
        local height = obj.sq_GetIntData(SKILL_BLOODHANG, 5);

//		sq_setFullScreenEffect(obj,"passiveobject/zrr_skill/atmage/animation/atfatality/fatality_finishscreen_red.ani");	

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODHANG_2);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODHANGLAST);
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODHANG , STATE_BLOODHANG, 0, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);				

        obj.sq_SetShake(obj, 10, 500);
        sq_flashScreen(obj,0,0,160,255, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
        setBloodValue(obj,obj.sq_GetIntData(SKILL_BLOODHANG, 2));
        obj.getVar().clear_vector();
        obj.getVar().push_vector(0);
    }else if (subState == 3)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATFATALITY_ATTACK_FAIL);
    }
//	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
//			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);
}


function setVliadEffectAtFatailtyPassiveobject(obj)
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


// onEndCurrentAni
function onEndCurrentAni_BLOODHANG(obj)
{
	if (!obj) return;
	
	
	if(!obj.isMyControlObject()) {
		return;
	}
	if (obj.sq_GetSkillSubState(obj) == 0) 
    {
	}else if (obj.sq_GetSkillSubState(obj) == 1) 
    {
        if (obj.getVar("dama2").get_obj_vector_size() > 0)
        {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(2);	// subState????
            obj.sq_AddSetStatePacket(STATE_BLOODHANG, STATE_PRIORITY_USER, true);
        }else{
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(3);	// subState????
            obj.sq_AddSetStatePacket(STATE_BLOODHANG, STATE_PRIORITY_USER, true);

     
        }
	}else if (obj.sq_GetSkillSubState(obj) == 2) 
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}else if (obj.sq_GetSkillSubState(obj) == 3)
    {
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}

function onTimeEvent_BLOODHANG(obj, timeEventIndex, timeEventCount)
{
	if(!obj.isMyControlObject()) {
		return;
	}
	if (obj.sq_GetSkillSubState(obj) == 0) 
    {
        if (timeEventIndex == 0)
        {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(1);	// subState????
            obj.sq_AddSetStatePacket(STATE_BLOODHANG, STATE_PRIORITY_USER, true);
        }
	}
}

function onProc_BLOODHANG(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
    if (obj.sq_GetSkillSubState(obj) == 0)
    {
        local isPress = sq_IsKeyDown(OPTION_HOTKEY_JUMP, ENUM_SUBKEY_TYPE_ALL)
        if (isPress)
        {

            obj.sq_IntVectClear();
            obj.sq_IntVectPush(1);	// subState????
            obj.sq_AddSetStatePacket(STATE_BLOODHANG, STATE_PRIORITY_USER, true);

        }


    }else if (obj.sq_GetSkillSubState(obj) == 1){
    }
}

function onAttack_BLOODHANG(obj, damager, boundingBox, isStuck)
{

    if (obj.sq_GetSkillSubState(obj) == 1)   
    {
        obj.sq_SetShake(obj, 7, 150);
        obj.getVar("dama2").push_obj_vector(damager);
        createFatality_AttackHitEffect(obj,damager);
        if (obj.getVar().get_vector(0) == 0)
        {
            obj.getVar().set_vector(0,1);
            if (obj.isMyControlObject())
            {
                sq_setFullScreenEffect(obj,"passiveobject/zrr_skill/atmage/animation/atfatality/fatality_attackscreen_red.ani");	
            }
        }

    }else if (obj.sq_GetSkillSubState(obj) == 2)
    {
        if (obj.isMyControlObject())
        {
            CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/bloodhang/ap_hang_pull.nut");		
            if (obj.getVar().get_vector(0) == 0)
            {
                obj.getVar().set_vector(0,1);
                createFatality_FinishHitEffect(obj,damager);
                createFatality_FinishBg2(obj);
                createWave_BLOODHANG(obj,150,damager.getZPos() + damager.getObjectHeight()/2 );
                sq_setFullScreenEffect(obj,"passiveobject/zrr_skill/atmage/animation/atfatality/fatality_finish_screenred.ani");	

            }
        }
    }
}
