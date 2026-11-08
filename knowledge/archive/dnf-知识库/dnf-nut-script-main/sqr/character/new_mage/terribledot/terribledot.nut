//state 1 flash 10 50 10 7 255 255 255 bottom
//FLAG 1 passive [OFFSET] `attraction aura start`	69	0	46
//FLAG 2 [SHAKE] 3 240 effect 85 0 51
//flag 3 3 280 effect add
function checkExecutableSkill_terribledot(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_TERRIBLEDOT);
	if (isUseSkill) 
    {
        obj.getVar("state").clear_vector();
        if (!isDollState(obj) )
        {
            obj.getVar("state").push_vector(0);
        }else{
            obj.getVar("state").push_vector(2);
        }
        obj.sq_IsEnterSkillLastKeyUnits(SKILL_TERRIBLEDOT);
		obj.sq_AddSetStatePacket(STATE_TERRIBLEDOT, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}
function checkCommandEnable_terribledot(obj)
{

	return true;
}
function sendTerribleDotStorageCapacityFlag(obj)
{
    local dot = getDotObj(obj);
    if(dot)
    {
//        local damage = obj.sq_GetBonusRateWithPassive(SKILL_MADDOTSHOOT , STATE_MADDOTSHOOT, 0, 1.0);
//        local count = obj.sq_GetIntData(SKILL_MADBIGBREAK, 0);
        dot.getVar("state").clear_vector();
        dot.getVar("state").push_vector(8);
        dot.getVar("subState").clear_vector();
        dot.getVar("subState").push_vector(0);
        local pIntVec = sq_GetGlobalIntVector();
        dot.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
    }
}
function sendTerribleDotOutFlag(obj)
{
    local dot = getDotObj(obj);
    if(dot)
    {
        local attackRate= obj.sq_GetPowerWithPassive(SKILL_TERRIBLEDOT , STATE_TERRIBLEDOT, 0, -1, 1.0);
        
        local count = sq_GetLevelData(obj, SKILL_TERRIBLEDOT, 1, sq_GetSkillLevel(obj, SKILL_TERRIBLEDOT) );
        dot.getVar("state").clear_vector();
        dot.getVar("state").push_vector(8);
        dot.getVar("subState").clear_vector();
        dot.getVar("subState").push_vector(1);
        dot.getVar("value").clear_vector();
        dot.getVar("value").push_vector( obj.sq_GetIntData(SKILL_TERRIBLEDOT, 0) );
        dot.getVar("value").push_vector(attackRate);
        dot.getVar("value").push_vector(count );
        local pIntVec = sq_GetGlobalIntVector();
        dot.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
    }
}
function onSetState_TERRIBLEDOT(obj, state, datas, isResetTimer)
{

	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {

        sendTerribleDotStorageCapacityFlag(obj);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_TERRIBLEDOT_READY);
        sq_SetMyShake(obj,3, 240 );
        obj.getVar("dama").clear_obj_vector();
        findRoundNearAllEnemy(obj,400,300);
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

    }else if (state == 1)
    {
        sendTerribleDotOutFlag(obj);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_TERRIBLEDOT_LOOP);
        sq_flashScreen(obj,10,50,10,76, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
    }else if (state == 2)
    {
        findRoundNearAllEnemy(obj,400,300);
        local ani = obj.getVar().GetAnimationMap("terribledot1", "passiveobject/zrr_skill/newmage/animation/dot/terribledot/terribleroarstart_mad.ani"); 
		obj.setCurrentAnimation(ani);
    }else if (state == 3)
    {
        local ani = obj.getVar().GetAnimationMap("terribledot2", "passiveobject/zrr_skill/newmage/animation/dot/terribledot/terribleroarwavestart_mad.ani"); 
		obj.setCurrentAnimation(ani);
    }else if (state == 4)
    {
        local ani = obj.getVar().GetAnimationMap("terribledot3", "passiveobject/zrr_skill/newmage/animation/dot/terribledot/terribleroarwaveroof_madbig.ani"); 
		obj.setCurrentAnimation(ani);

        local count = sq_GetLevelData(obj, SKILL_TERRIBLEDOT, 1, sq_GetSkillLevel(obj, SKILL_TERRIBLEDOT) );
        obj.setTimeEvent(1, obj.sq_GetIntData(SKILL_TERRIBLEDOT, 0) ,0,false);
        sq_SetMyShake(obj,3, obj.sq_GetIntData(SKILL_TERRIBLEDOT, 0) );
        sq_BinaryStartWrite();
        sq_BinaryWriteDword( obj.sq_GetPowerWithPassive(SKILL_TERRIBLEDOT , STATE_TERRIBLEDOT, 0, -1, 1.0) );
        sq_BinaryWriteDword(11);
        sq_BinaryWriteDword( count );
        sq_BinaryWriteDword( obj.sq_GetIntData(SKILL_TERRIBLEDOT, 0) );
        sq_BinaryWriteDword( obj.sq_GetIntData(SKILL_TERRIBLEDOT, 1) );
        sq_SendCreatePassiveObjectPacketPos(obj, 24364, 0, obj.getXPos(), obj.getYPos() + 1, 0);


    }else if (state == 5)
    {
        local ani = obj.getVar().GetAnimationMap("terribledot4", "passiveobject/zrr_skill/newmage/animation/dot/terribledot/terribleroarwaveend_mad.ani"); 
		obj.setCurrentAnimation(ani);
    }
}

function onEndCurrentAni_TERRIBLEDOT(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 3)
    {
        obj.getVar("state").set_vector(0,4);
		obj.sq_AddSetStatePacket(STATE_TERRIBLEDOT, STATE_PRIORITY_USER, true);
    }else if (state == 5)
    {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}

function onKeyFrameFlag_TERRIBLEDOT(obj,flagIndex)
{
    if(flagIndex == 1)
    {

    }else if (flagIndex == 2)
    {

    }
}
function onProc_TERRIBLEDOT(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        if(!obj.isDownSkillLastKey() )
        {
            obj.getVar("state").set_vector(0,1);
            obj.sq_AddSetStatePacket(STATE_TERRIBLEDOT, STATE_PRIORITY_USER, true);
        }

        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();
        local dot = getDotObj(obj);
        for(local i=0;i<objectsSize;++i)
        {
                local damager = var.get_obj_vector(i);
                local objX = dot.getXPos();
                local objY = dot.getYPos();
                local damaX = damager.getXPos();
                local damaY = damager.getYPos();
                local damaZ = damager.getZPos();
                local x_move = 4;
                local y_move = 3;
                if (objX < damaX) x_move = - x_move;
                if (objY < damaY) y_move = - y_move;
                damager.setCurrentPos(damaX + x_move,damaY + y_move,damaZ);

       }
    }else if (state == 2)
    {
        if(!obj.isDownSkillLastKey() )
        {
            obj.getVar("state").set_vector(0,3);
            obj.sq_AddSetStatePacket(STATE_TERRIBLEDOT, STATE_PRIORITY_USER, true);
        }

        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();
        local dot = getDotObj(obj);
        for(local i=0;i<objectsSize;++i)
        {
                local damager = var.get_obj_vector(i);
                local objX = obj.getXPos();
                local objY = obj.getYPos();
                local damaX = damager.getXPos();
                local damaY = damager.getYPos();
                local damaZ = damager.getZPos();
                local x_move = 4;
                local y_move = 3;
                if (objX < damaX) x_move = - x_move;
                if (objY < damaY) y_move = - y_move;
                damager.setCurrentPos(damaX + x_move,damaY + y_move,damaZ);

       }




    }else if (state == 4)
    {
        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);
        if (currentT > obj.sq_GetIntData(SKILL_TERRIBLEDOT, 0) )
        {
            obj.getVar("state").set_vector(0,5);
            obj.sq_AddSetStatePacket(STATE_TERRIBLEDOT, STATE_PRIORITY_USER, true);
        }
    }
}



function findRoundNearAllEnemy(obj,chang,kuan)
{
	local objectManager = obj.getObjectManager();

	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isInDamagableState(obj) && object.isObjectType(OBJECTTYPE_ACTIVE))
        {
            if (chang + kuan < 0 )
            {
                return null;
            }else{
                if (abs(obj.getXPos() - object.getXPos())<= chang && abs(obj.getYPos() - object.getYPos())<= kuan)
                {
//                    obj.getVar("dama").clear_obj_vector();
                    obj.getVar("dama").push_obj_vector(object);
                }

            }

        }
    }
}
