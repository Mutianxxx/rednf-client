//FLAG 1 MAD JUMP
//STATE -- BLACK COVER
//MAD FLAG 1 `StartBlackCoverMadJump`	5	0	15


function checkExecutableSkill_dollforest(obj)  
{

    if (true )
    {
        local isUseSkill = obj.sq_IsUseSkill(SKILL_DOLLFOREST);
        if (isUseSkill) 
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(0);
            obj.sq_AddSetStatePacket(STATE_DOLLFOREST, STATE_PRIORITY_USER, true);
            return true;
        }
        return false;
    }
}


function checkCommandEnable_dollforest(obj)
{

	return true;
}

function onSetState_DOLLFOREST(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
    local objectManager = obj.getObjectManager();
    local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
    local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_COVER);
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    obj.getVar("flag").push_vector(0);
    if (state == 0)
    {
        if (!isDollState(obj))
        {
            obj.sq_SetCurrentAnimation(CUSTOM_DOLLFOREST_READY);
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(0);
        }else{
            local ani = obj.getVar().GetAnimationMap("dollforest", "passiveobject/zrr_skill/newmage/animation/dot/woodsofpuppetjump_body.ani"); 
            obj.setCurrentAnimation(ani);
            obj.sq_SendCreatePassiveObjectPacket(12301, 0, 0, 2, 0);
            sq_flashScreen(obj,400,500,200,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
        }
    }else if (state == 1)
    {
        obj.getVar("isBreak").clear_vector();
        obj.getVar("isBreak").push_vector(0);
        //?????????? 400 300 ???a?????

        sq_SendCreatePassiveObjectPacketPos(obj,12293, 0, xPos, yPos + 1, 0 );
        sq_SendCreatePassiveObjectPacketPos(obj,12286, 0, xPos, yPos, 0 );
        sq_SendCreatePassiveObjectPacketPos(obj,12287, 0, xPos, yPos, 0 );
        sq_SendCreatePassiveObjectPacketPos(obj,12300, 0, xPos, yPos, 0 );


		sq_BinaryStartWrite();
		sq_BinaryWriteDword(0);	// attackBonusRate
        sq_BinaryWriteDword(9);

        sq_SendCreatePassiveObjectPacketPos(obj,24366, 0, xPos - 1, yPos, 0 );
        //????ani???b????W
        obj.sq_SetCurrentAnimation(CUSTOM_DOLLFOREST_WAIT);
        sq_flashScreen(obj,0,5000,200,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
    }else if (state == 2)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_DOLLFOREST_ATTACKBOX);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_DOLLFOREST_FIRE);
        sq_SendCreatePassiveObjectPacketPos(obj,12294, 0, xPos, yPos - 1, 0 );
        sq_SendCreatePassiveObjectPacketPos(obj,12296, 0, xPos, yPos, 0 );
        sq_SendCreatePassiveObjectPacketPos(obj,12398, 0, xPos, yPos + 1, 0 );
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_DOLLFOREST , STATE_DOLLFOREST, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				
        local hitCount = obj.sq_GetIntData(SKILL_DOLLFOREST, 0);
        obj.setTimeEvent(0,1120 / hitCount,0,false);		
    }else if (state == 3)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_DOLLFOREST_FINISH);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_DOLLFOREST_ONEHAND);
        sq_SendCreatePassiveObjectPacketPos(obj,12295, 0, xPos, yPos - 1, 0 );
        sq_SendCreatePassiveObjectPacketPos(obj,12397, 0, xPos, yPos, 0 );
        sq_SendCreatePassiveObjectPacketPos(obj,12299, 0, xPos, yPos + 1, 0 );
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_DOLLFOREST , STATE_DOLLFOREST, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

    }
}
function onTimeEvent_DOLLFOREST(obj, timeEventIndex, timeEventCount)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 2)
    {
        if (timeEventIndex == 0)
        {
			obj.resetHitObjectList();

        }
    }
}

function onProc_DOLLFOREST(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state != 0)
    {
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),1000);
    }
}
function sendDotDollForestMadJump(obj)
{
    local dot = getDotObj(obj);
    {

        dot.getVar("state").clear_vector();
        dot.getVar("state").push_vector(9);
        local pIntVec = sq_GetGlobalIntVector();
        dot.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
    }

}

function onKeyFrameFlag_DOLLFOREST(obj,flagIndex)
{

    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        if (!isDollState(obj))
        {
            if (flagIndex == 1 && obj.getVar("flag").get_vector(0) == 0)
            {
                obj.getVar("flag").clear_vector();
                obj.getVar("flag").push_vector(1);
                sendDotDollForestMadJump(obj);

                obj.sq_SendCreatePassiveObjectPacket(12301, 0, 0, 2, 0);
                sq_flashScreen(obj,400,500,200,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
                //?i?D???n???D?F
            }
        }else{


        }
    }else if (state == 2)
    {
        if (obj.getVar("flag").get_vector(flagIndex) == 0)
        {
            obj.getVar("flag").set_vector(flagIndex,1);
            obj.sq_SetShake(obj, 2, 1440);

        }
    }else if (state == 3)
    {
        if (obj.getVar("flag").get_vector(flagIndex) == 0)
        {
            obj.getVar("flag").set_vector(flagIndex,1);
            if (flagIndex == 0)
            {
                obj.sq_SetShake(obj, 5, 120);
            }else if (flagIndex == 1)
            {
                obj.resetHitObjectList();
                obj.sq_SetCurrentAttackInfo(ATTACKINFO_DOLLFOREST_TWOHAND);
                local damage = obj.sq_GetBonusRateWithPassive(SKILL_DOLLFOREST , STATE_DOLLFOREST, 2, 1.0);
                obj.sq_SetCurrentAttackBonusRate(damage);				
                obj.sq_SetShake(obj, 5, 120);
            }else if (flagIndex == 2)
            {
                obj.resetHitObjectList();
                obj.sq_SetCurrentAttackInfo(ATTACKINFO_DOLLFOREST_ONEHAND);
                local damage = obj.sq_GetBonusRateWithPassive(SKILL_DOLLFOREST , STATE_DOLLFOREST, 3, 1.0);
                obj.sq_SetCurrentAttackBonusRate(damage);				
                obj.sq_SetShake(obj, 10, 240);

            }else if (flagIndex == 3)
            {
                obj.getVar("isBreak").clear_vector();
                obj.getVar("isBreak").push_vector(1);
                sq_flashScreen(obj,400,240,1000,255, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
                local objectManager = obj.getObjectManager();
                local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
                local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);
                sq_SendCreatePassiveObjectPacketPos(obj,12303, 0, xPos, yPos + 1, 0 );
            }
        }
    }

}


function onEndCurrentAni_DOLLFOREST(obj)
{
	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
            obj.getVar("state").set_vector(0,1);
            obj.sq_AddSetStatePacket(STATE_DOLLFOREST, STATE_PRIORITY_USER, true);
    }else if (state == 1)
    {
            obj.getVar("state").set_vector(0,2);
            obj.sq_AddSetStatePacket(STATE_DOLLFOREST, STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {
            obj.getVar("state").set_vector(0,3);
            obj.sq_AddSetStatePacket(STATE_DOLLFOREST, STATE_PRIORITY_USER, true);
    }else if (state == 3)
    {
            obj.setCurrentPos(obj.getXPos(),obj.getYPos(),0);
            if (!isDollState(obj))
            {
                sendDotDollStand(obj);
            }
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}


