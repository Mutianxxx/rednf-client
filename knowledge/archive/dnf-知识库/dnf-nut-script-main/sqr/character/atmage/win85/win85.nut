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

function spearHitEffect1Win85(obj,damager)
{
    local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atfinaltempest/stepb_hita_03.ani");

	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() - 1,damager.getZPos() );
	pooledObj.setCurrentDirection(damager.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
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
                spearHitEffect1Win85(obj,damager);
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

function onSetState_WIN85(obj, state, datas, isResetTimer)
{
    local state = obj.getVar("state").get_vector(0);
    local objectManager = obj.getObjectManager();
    local xPos = objectManager.getFieldXPos(sq_GetIntData(obj, SKILL_WIN85, 3)+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
    local yPos = objectManager.getFieldYPos(sq_GetIntData(obj, SKILL_WIN85, 4), 0, ENUM_DRAWLAYER_NORMAL);
    obj.sq_StopMove();
    if (state == 0)
    {
        obj.getVar("dama").clear_obj_vector();
        findAllMonster_WIN85(obj);
        sq_SendCreatePassiveObjectPacketPos(obj,12149, 0,xPos, yPos+2, 0);
        sq_SendCreatePassiveObjectPacketPos(obj,12150, 0,xPos, yPos-1, 0);
        sq_SendCreatePassiveObjectPacketPos(obj,12151, 0,xPos, yPos+1, 0);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWWIN85_READY);
        obj.sq_SetShake(obj, 8, 50);
        sq_flashScreen(obj,10,5000,500,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
    }else if (state == 1){

        obj.sq_SetShake(obj, 5, 120);

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);
        obj.getVar("flag").push_vector(0);

        obj.sq_StartWrite();
        obj.sq_WriteDword(7);	// attackBonusRate
        sq_SendCreatePassiveObjectPacketPos(obj,24341, 0,xPos, yPos, 0);
        obj.sq_StartWrite();
        obj.sq_WriteDword(8);	// attackBonusRate
        sq_SendCreatePassiveObjectPacketPos(obj,24341, 0,xPos, yPos, 0);
        obj.sq_StartWrite();
        obj.sq_WriteDword(9);	// attackBonusRate
        sq_SendCreatePassiveObjectPacketPos(obj,24341, 0,xPos, yPos, 0);

		obj.sq_SendCreatePassiveObjectPacket(12155, 0, 0, 1, 0);
		obj.sq_SendCreatePassiveObjectPacket(12156, 0, 0, 1, 0);
		obj.sq_SendCreatePassiveObjectPacket(12157, 0, 0, 1, 0);

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWWIN85_LOOP);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWWIN85_LOOP);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_WIN85 , STATE_WIN85, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

        obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

    }else if (state == 2){
        
        sq_flashScreen(obj,0,150,500,255, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        obj.sq_SetShake(obj, 10, 100);
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWWIN85_LAST);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWWIN85_END);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_WIN85 , STATE_WIN85, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

        obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

        if (obj.getVar("dama").get_obj_vector_size() > 0 )
        {
            local target = obj.getVar("dama").get_obj_vector(0);
            local tarX = target.getXPos();
            local tarY = target.getYPos();
            local posX = sq_GetDistancePos(tarX, obj.getDirection(), sq_GetIntData(obj, SKILL_WIN85, 5) );
            obj.sq_SetfindNearLinearMovablePos(posX,tarY,obj.getXPos(), obj.getYPos(), 10);
        }

    }


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
			obj.resetHitObjectList();
            noholdMonster_WIN85(obj);

            sq_flashScreen(obj,0,100,0,153, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            obj.sq_SetShake(obj, 6, 250);
        }
    }
}