function checkExecutableSkill_win85(obj)
{
	if (!obj)
		return false;
	
	local isUseSkill = obj.sq_IsUseSkill(SKILL_WIN85);
	if (isUseSkill)
	{
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_WIN85, STATE_PRIORITY_IGNORE_FORCE, false);
		return true;
	}	

	return false;

}

function checkCommandEnable_win85(obj)
{

	if(!obj) return false;

    return true;
}

function findAllMonster_WIN85(obj)
{

	local objectManager = obj.getObjectManager();

	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) && object.isInDamagableState(obj))
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);
            
            obj.getVar("dama").push_obj_vector(activeObj);

            if (!CNSquirrelAppendage.sq_IsAppendAppendage(activeObj, "character/atmage/win85/ap_win85.nut"))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(activeObj, obj, SKILL_WIN85, false, "character/atmage/win85/ap_win85.nut", true);				 
                  sq_HoldAndDelayDie(activeObj, obj, true, true, true, 0, 0, ENUM_DIRECTION_DOWN , masterAppendage);
            }

		}
	}

}



function onAttack_WIN85(obj, damager, boundingBox, isStuck)
{

    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {

		if(  sq_IsGrabable(obj,damager)  && !sq_IsFixture(damager) ) 
        {
                local objX = obj.getXPos();
                local objY = obj.getYPos();
                local damaX = damager.getXPos();
                local damaY = damager.getYPos();
                local damaZ = damager.getZPos();
                local x_move = sq_GetIntData(obj, SKILL_WIN85, 0);
                local y_move = sq_GetIntData(obj, SKILL_WIN85, 1);

                if (objX < damaX) x_move = - x_move;
                if (objY < damaY) y_move = - y_move;
                if(damaZ > 0)
                {
                    damaZ = damaZ - sq_GetIntData(obj, SKILL_WIN85, 2);
                }else{
                    damaZ = 0;
                }
                damager.setCurrentPos(damaX + x_move,damaY + y_move,damaZ);
        }
    }
}


function noholdMonster_WIN85(obj)
{
	local objectManager = obj.getObjectManager();

	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) )
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);
            if (CNSquirrelAppendage.sq_IsAppendAppendage(activeObj, "character/atmage/win85/ap_win85.nut"))
            {
                CNSquirrelAppendage.sq_RemoveAppendage(activeObj, "character/atmage/win85/ap_win85.nut");		
            }
        }
    }

}


function onProc_WIN85(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        local z = obj.getVar("pos").get_vector(0);
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),z);

    }else if (state == 1)
    {
        local z = obj.getVar("pos").get_vector(0);
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),z);

    }else if (state == 2)
    {
        local z = obj.getVar("pos").get_vector(0);
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),0);

    }

}



function setVliadEffectFinalTempstPassiveObject(obj)
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


function onEndState_WIN85(obj, new_state)
{
    local state = obj.getVar("state").get_vector(0);



    if (new_state != STATE_WIN85)
    {
        setVliadEffectFinalTempstPassiveObject(obj);
    }else{

        if (state == 1)
        {
            setVliadEffectFinalTempstPassiveObject(obj);
        }else if (state == 2)
        {
            setVliadEffectFinalTempstPassiveObject(obj);
        }else if (state == 3)
        {

        }

    }

//    setVliadEffectBloodStreamEsaspistPassiveObject(obj);)
}

function onSetState_WIN85(obj, state, datas, isResetTimer)
{
    local state = obj.getVar("state").get_vector(0);
    local objectManager = obj.getObjectManager();
    local x = objectManager.getFieldXPos(sq_GetIntData(obj, SKILL_WIN85, 3)+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
    local y = objectManager.getFieldYPos(sq_GetIntData(obj, SKILL_WIN85, 4), 0, ENUM_DRAWLAYER_NORMAL);
    obj.sq_StopMove();
    if (state == 0)
    {


        obj.getVar("effectObj").clear_obj_vector();
        obj.getVar("dama").clear_obj_vector();

        findAllMonster_WIN85(obj);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWWIN85_READY);
        obj.sq_SetShake(obj, 8, 50);
        sq_flashScreen(obj,10,6500,500,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

        obj.getVar("pos").clear_vector();
        obj.getVar("pos").push_vector(obj.getZPos() );
        createFinalTempestStartBG1(obj,x,y);
        createFinalTempestStartMiddle(obj,x,y);
        createFinalTempestStartFront(obj,x,y);
        createFinalTempestTheSky(obj,x,y);

    }else if (state == 1){

        obj.sq_SetShake(obj, 5, 120);

        createFinalTempestLoopBG1(obj,x,y);
        createFinalTempestLoopMiddle(obj,x,y);
        createFinalTempestLoopFront(obj,x,y);

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWWIN85_LOOP);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWWIN85_LOOP);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_WIN85 , STATE_WIN85, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

    }else if (state == 2){
        



        sq_flashScreen(obj,0,150,500,255, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        obj.sq_SetShake(obj, 10, 100);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWWIN85_LAST);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWWIN85_END);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_WIN85 , STATE_WIN85, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

        if (obj.getVar("dama").get_obj_vector_size() > 0 )
        {
            local target = obj.getVar("dama").get_obj_vector(0);
            local tarX = target.getXPos();
            local tarY = target.getYPos();
            local posX = sq_GetDistancePos(tarX, obj.getDirection(), sq_GetIntData(obj, SKILL_WIN85, 5) );
            obj.sq_SetfindNearLinearMovablePos(posX,tarY,obj.getXPos(), obj.getYPos(), 10);
        }
        createFinalTempestEndBG1(obj,x,y);
        createFinalTempestEndMiddle(obj,x,y);
        createFinalTempestEndFront(obj,x,y);
        createFinalTempestFinishTheSky(obj,obj.getXPos(),obj.getYPos() );
        createFinalTempestFinishA01(obj,obj.getXPos(),obj.getYPos() );
    }

        obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}


function onEndCurrentAni_WIN85(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_WIN85, STATE_PRIORITY_IGNORE_FORCE, false);
    }else if (state == 1)
    {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
        obj.sq_AddSetStatePacket(STATE_WIN85, STATE_PRIORITY_IGNORE_FORCE, false);
    }else if (state == 2)
    {

        sq_flashScreen(obj,0,0,400,127, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
    }
}


function onKeyFrameFlag_WIN85(obj, flagIndex)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {
        if (obj.getVar("flag").get_vector(flagIndex) == 0)
        {
            obj.getVar("flag").set_vector(flagIndex,1);
            obj.resetHitObjectList();
            obj.sq_SetShake(obj, 2, 120);
            sq_flashScreen(obj,50,0,50,50, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);


            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();
            for(local i=0;i<objectsSize;++i)
            {
                local damager = var.get_obj_vector(i);

                if(damager)
                {
                    if (flagIndex % 2 == 1)
                    {
                        damager.setCurrentDirection( sq_GetOppositeDirection(obj.getDirection()) );
                    }else{
                        damager.setCurrentDirection( obj.getDirection() );
                    }
                    createFinalTempestHitEffectB(obj,damager);
                }
            }


        }
    }else if (state == 2)
    {
        if (obj.getVar("flag").get_vector(0) == 0 && flagIndex == 1 )
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);

            obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWWIN85_LAST2);
            local damage = obj.sq_GetBonusRateWithPassive(SKILL_WIN85 , STATE_WIN85, 2, 1.0);
            obj.sq_SetCurrentAttackBonusRate(damage);				
            noholdMonster_WIN85(obj);
			obj.resetHitObjectList();
            sq_flashScreen(obj,0,100,0,153, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            obj.sq_SetShake(obj, 6, 250);
        }
    }
}




function createFinalTempestStartBG1(obj,x,y)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfinaltempest/twist_start_bg1.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(x, obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,y - 2,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createFinalTempestStartFront(obj,x,y)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfinaltempest/twist_start_front.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(x, obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,y + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createFinalTempestStartMiddle(obj,x,y)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfinaltempest/twist_start_middle.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(x, obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,y,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}






function createFinalTempestLoopBG1(obj,x,y)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfinaltempest/twist_loop_bg1.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(x, obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,y - 2,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createFinalTempestLoopFront(obj,x,y)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfinaltempest/twist_loop_front.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(x, obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,y + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createFinalTempestLoopMiddle(obj,x,y)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfinaltempest/twist_loop_middle.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(x, obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,y,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}








function createFinalTempestEndBG1(obj,x,y)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfinaltempest/twist_end_bg1.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(x, obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,y - 2,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createFinalTempestEndFront(obj,x,y)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfinaltempest/twist_end_front.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(x, obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,y + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createFinalTempestEndMiddle(obj,x,y)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfinaltempest/twist_end_middle.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(x, obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,y,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}






function createFinalTempestTheSky(obj,x,y)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfinaltempest/finaltempest_steaa_bgeffect_sky01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(x, obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,y,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createFinalTempestFinishTheSky(obj,x,y)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfinaltempest/finaltempest_finish_bgeffect.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(x, obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,y + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}


function createFinalTempestFinishA01(obj,x,y)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfinaltempest/finaltempest_finish_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(x, obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,y + 1,0);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
    obj.getVar("effectObj").push_obj_vector( pooledObj );
}



function createFinalTempestHitEffectB(obj,damager)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atfinaltempest/finaltempest_hiteffectb_hitb.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(damager.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,damager.getYPos() + 2,damager.getZPos() + damager.getObjectHeight() / 2);
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
//    obj.getVar("effectObj").push_obj_vector( pooledObj );
}

