function checkExecutableSkill_bloodsong(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_BLOODSONG);
	if (isUseSkill) {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
        obj.sq_AddSetStatePacket(STATE_BLOODSONG, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_bloodsong(obj)
{
	if(!obj)
		return false;

    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_BLOODSONG,3)))
    return false;

		return true;
}


function onEndState_BLOODSONG(obj, state)
{
	sq_EndDrawCastGauge(obj);
}


function onSetState_BLOODSONG(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	obj.sq_StopMove();
	
	
	local subState = obj.getVar("state").get_vector(0);
	
	if (subState == 0)
	{
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);
        
        setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOODSONG,3));
        sq_flashScreen(obj,0,0,2000,150, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSONG_READ);

	}
	else if (subState == 1)
	{

            sq_flashScreen(obj,100,100,obj.sq_GetIntData(SKILL_BLOODSONG,5)/2,100, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);

        local objectManager = obj.getObjectManager();

        if (!objectManager)
            return;

        local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
        local yPos = objectManager.getFieldYPos(300, 0, ENUM_DRAWLAYER_NORMAL);

        obj.sq_SetfindNearLinearMovablePos(xPos,yPos,obj.getXPos(), obj.getYPos(), 10);

        obj.getVar("dama").clear_obj_vector();
        
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);


        obj.getVar("attackHeight").clear_vector();
        obj.getVar("attackHeight").push_vector(obj.sq_GetIntData(SKILL_BLOODSONG,1));

        obj.getVar("attackTime").clear_vector();
        obj.getVar("attackTime").push_vector(obj.sq_GetIntData(SKILL_BLOODSONG,0));


        obj.setTimeEvent(0, obj.sq_GetIntData(SKILL_BLOODSONG,0), 0, false);
        obj.setTimeEvent(1, obj.sq_GetIntData(SKILL_BLOODSONG,5), 0, false);

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSONG_ATTACK);

        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODSCREAM_ATTACK);

        obj.sq_StartWrite();
        obj.sq_WriteDword(0);	// attackBonusRate
        obj.sq_SendCreatePassiveObjectPacket(24341, 0, 0, 0, 0);
        obj.sq_StartWrite();
        obj.sq_WriteDword(1);	// attackBonusRate
        obj.sq_SendCreatePassiveObjectPacket(24341, 0, 0, -60 , 0);

        obj.sq_SendCreatePassiveObjectPacket(12309, 0, 100, 50, 0);
        obj.sq_SendCreatePassiveObjectPacket(12310, 0, -100, -30, 0);

        obj.sq_SendCreatePassiveObjectPacket(12112, 0, -300, -200, 0);
        obj.sq_SendCreatePassiveObjectPacket(12113, 0, 120, -130, 0);
        obj.sq_SendCreatePassiveObjectPacket(12114, 0, -234, 56, 0);
        obj.sq_SendCreatePassiveObjectPacket(12115, 0, 128, 109, 0);


        obj.sq_SendCreatePassiveObjectPacket(12112, 1, -400, -189, 0);
        obj.sq_SendCreatePassiveObjectPacket(12113, 1, -230, -130, 0);
        obj.sq_SendCreatePassiveObjectPacket(12114, 1, 234, 132, 0);
        obj.sq_SendCreatePassiveObjectPacket(12115, 1, 128, 156, 0);

        obj.sq_SendCreatePassiveObjectPacket(12112, 1, -300, -200, 0);
        obj.sq_SendCreatePassiveObjectPacket(12113, 1, 170, -130, 0);

        obj.sq_SendCreatePassiveObjectPacket(12112, 0, -67, -189, 0);
        obj.sq_SendCreatePassiveObjectPacket(12113, 0, 86, -130, 0);

        obj.sq_SendCreatePassiveObjectPacket(12112, 1, 8, -156, 0);
        obj.sq_SendCreatePassiveObjectPacket(12113, 1, 156, -109, 0);

        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSONG , STATE_BLOODSONG, 0, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);				


	}
    else if (subState == 2)
    {

//        sq_setFullScreenEffect(obj,"character/mage/atanimation/als_ani/bloodsong/yue_0.ani");

        obj.sq_SetShake(obj, 20, 100);

        sq_flashScreen(obj,0,0,150,150, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_COVER);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSONG_READ);


        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODSONGLAST);

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODSONG_LAST);

        local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSONG , STATE_BLOODSONG, 1, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);				

    }

}

function onTimeEvent_BLOODSONG(obj, timeEventIndex, timeEventCount)
{
    local state = obj.getVar("state").get_vector(0);
	if (state == 1) 
    {
        if (timeEventIndex == 0)
        {
            local currFlag = obj.getVar("flag").get_vector(0);
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(currFlag+1);

            local currentHeight = obj.getVar("attackHeight").get_vector(0);
            obj.getVar("attackHeight").clear_vector();
            obj.getVar("attackHeight").push_vector(currentHeight + 1);
            obj.resetHitObjectList();

            local currentAT = obj.getVar("attackTime").get_vector(0);
            if (currentAT > obj.sq_GetIntData(SKILL_BLOODSONG,6))
            {

                obj.setTimeEvent(0, currentAT - obj.sq_GetIntData(SKILL_BLOODSONG,2), 0, false);

                obj.getVar("attackTime").clear_vector();
                obj.getVar("attackTime").push_vector(currentAT - obj.sq_GetIntData(SKILL_BLOODSONG,2) );

            }else{

                obj.setTimeEvent(0, obj.sq_GetIntData(SKILL_BLOODSONG,6), 0, false);

            }
        }

        if (timeEventIndex == 1)
        {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
        obj.sq_AddSetStatePacket(STATE_BLOODSONG, STATE_PRIORITY_USER, true);

        }


    }
}


// onEndCurrentAni
function onEndCurrentAni_BLOODSONG(obj)
{
	if (!obj) return;
	
	local state = obj.getVar("state").get_vector(0);
	if (state == 0) 
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
        obj.sq_AddSetStatePacket(STATE_BLOODSONG, STATE_PRIORITY_USER, true);
	}
	else if (state == 1) 
    {
//        obj.getVar("state").clear_vector();
//        obj.getVar("state").push_vector(2);
//        obj.sq_AddSetStatePacket(STATE_BLOODSONG, STATE_PRIORITY_USER, true);
	}
    else if (state == 2) obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}


function onProc_BLOODSONG(obj)
{
    local state = obj.getVar("state").get_vector(0);

    if (state == 1) 
    {
        local isPress = sq_IsKeyDown(OPTION_HOTKEY_JUMP, ENUM_SUBKEY_TYPE_ALL)
        if (isPress)
        {

            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(2);
            obj.sq_AddSetStatePacket(STATE_BLOODSONG, STATE_PRIORITY_USER, true);

        }

        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),1000);

        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();

        for(local i=0;i<objectsSize;++i)
        {
            local damager = var.get_obj_vector(i);
            sq_EffectLayerAppendage(damager,sq_RGB(0,0,0),255,0,800,0);	

            damager.setCurrentPos(damager.getXPos(),damager.getYPos(),obj.getVar("attackHeight").get_vector(0));
        }
    }
    if (state == 2) 
    {
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),0);
        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();

        for(local i=0;i<objectsSize;++i)
        {
            local damager = var.get_obj_vector(i);
            sq_SetCustomRotate(damager,0.0 );
        }
    }


}



function onAttack_BLOODSONG(obj, damager, boundingBox, isStuck)
{
    if (!obj) return;

    if (sq_IsFixture(damager)) return false;

    local state = obj.getVar("state").get_vector(0);

    if (state == 1) 
    {
        local damaX = damager.getXPos();
        local damaY = damager.getYPos();
        local damaZ = damager.getZPos();

        obj.sq_SetShake(obj, 5, 100);

        local pAni = obj.sq_GetCurrentAni();

        local NowFrame = obj.sq_GetCurrentFrameIndex(pAni);

        if (obj.getVar("flag").get_vector(0) == 0)
        {
            if (sq_GetDirection(damager) == ENUM_DIRECTION_RIGHT)
            {
                sq_SendCreatePassiveObjectPacketPos(obj,12111, 0, damager.getXPos(), damager.getYPos() - 1,damaZ  + 75 );
            }else{
                sq_SendCreatePassiveObjectPacketPos(obj,12111, 0, damager.getXPos(), damager.getYPos() - 1,damaZ  + 75 );
            }
        }

        local passiveId = 12027 + (obj.getVar("flag").get_vector(0) / 2) % 6;

//        obj.sq_PlaySound("SKELETON_DIE_01");

        if  (passiveId == 12027)
        {
            obj.sq_PlaySound("BLOODSONG0");
            obj.sq_PlaySound("BLOODSONG00");
        }

        if  (passiveId == 12028)
        {
            obj.sq_PlaySound("BLOODSONG1");
            obj.sq_PlaySound("BLOODSONG01");
        }

        if  (passiveId == 12029)
        {
            obj.sq_PlaySound("BLOODSONG2");
            obj.sq_PlaySound("BLOODSONG02");
        }

        if  (passiveId == 12030)
        {
            obj.sq_PlaySound("BLOODSONG3");
            obj.sq_PlaySound("BLOODSONG00");
        }

        if  (passiveId == 12031)
        {
            obj.sq_PlaySound("BLOODSONG0");
            obj.sq_PlaySound("BLOODSONG00");
        }

        if  (passiveId == 12032)
        {
            obj.sq_PlaySound("BLOODSONG1");
            obj.sq_PlaySound("BLOODSONG01");
        }

        if  (passiveId == 12333)
        {
            obj.sq_PlaySound("BLOODSONG2");
            obj.sq_PlaySound("BLOODSONG02");
        }

        if (!CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/bloodsong/ap_bloodsong.nut"))
        {
            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODSONG, false, "character/atmage/bloodsong/ap_bloodsong.nut", true);				 
            if(masterAppendage) 
            {
                sq_HoldAndDelayDie(damager, obj, false, true, true, 0, 0, ENUM_DIRECTION_DOWN , masterAppendage);
            }
        }

        if (!sq_IsFixture(damager))
        {
            obj.getVar("dama").clear_vector();
            obj.getVar("dama").push_obj_vector(damager);
        }

        sq_SendCreatePassiveObjectPacketPos(obj,12333, 0, damager.getXPos(), damager.getYPos() - 2, damaZ + damager.getObjectHeight()/2 - 30);


        if (sq_GetDirection(damager) == ENUM_DIRECTION_RIGHT)
        {
            sq_SendCreatePassiveObjectPacketPos(obj,passiveId, sq_getRandom(0,1).tointeger(), damaX + sq_getRandom(-60 , 60).tointeger()  , damaY - 1 , damaZ - obj.sq_GetIntData(SKILL_BLOODSONG,1) + 75 );
        }else{
            sq_SendCreatePassiveObjectPacketPos(obj,passiveId, sq_getRandom(0,1).tointeger(), damaX + sq_getRandom(-60 , 60).tointeger() , damaY - 1 , damaZ - obj.sq_GetIntData(SKILL_BLOODSONG,1) + 75 );
        }

    }

    if (state == 2) 
    {

        if(damager)
        {
            CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/bloodsong/ap_bloodsong.nut");		
        }

        sq_SendCreatePassiveObjectPacketPos(obj,12159, 0, damager.getXPos(), damager.getYPos() + 1, damager.getZPos() + damager.getObjectHeight()/2);

		sq_BinaryStartWrite();
		sq_BinaryWriteDword(0);	// attackBonusRate
        sq_BinaryWriteDword(3);
        sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOODSONG,4) );

		sq_SendCreatePassiveObjectPacketPos(obj,24357, 0,damager.getXPos(), damager.getYPos() + 1, damager.getZPos() + damager.getObjectHeight()/2 );


    }

}



function onKeyFrameFlag_BLOODSONG(obj, flagIndex)
{


    local state = obj.getVar("state").get_vector(0);

    if (state == 0 && obj.getVar("flag").get_vector(0) == 0)
    {
        if (flagIndex == 1)
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);

        }   



    }


}