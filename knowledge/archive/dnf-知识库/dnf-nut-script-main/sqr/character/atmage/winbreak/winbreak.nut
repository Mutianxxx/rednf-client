function checkExecutableSkill_winbreak(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_WINBREAK);

	if (isUse) {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_WINBREAK , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}


function checkCommandEnable_winbreak(obj)
{

	return true;
}

function createPassive_WINDBREAK(obj)
{
    local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atwindblaster/windblaster_blast_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);

	pooledObj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);	
}

function onSetState_WINBREAK(obj, state, datas, isResetTimer)
{	
    if(!obj) return;
    obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {
    
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWWINDBREAK_READY);
    }else if (state == 1){

        obj.sq_SetShake(obj, 5, 240);
        createPassive_WINDBREAK(obj);

        obj.getVar("poss").clear_vector();
        obj.getVar("poss").push_vector( obj.getXPos() );
        obj.getVar("poss").push_vector( -50 );

//        local dstX = sq_GetDistancePos(obj.getXPos() , obj.getDirection(), -50);

//        obj.sq_SetfindNearLinearMovablePos(dstX ,obj.getYPos(),obj.getXPos(), obj.getYPos(), 10);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWWINDBREAK_OUT);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODWINDSKRIKE);
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_WINBREAK , STATE_WINBREAK, 0, 1.0);
        obj.sq_SetCurrentAttackBonusRate(damage);				
        
        local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackeHitStunTime(currentAttackInfo, 0);
        
        obj.getVar("winObj").clear_obj_vector();
  
        local bloodCutObjCount = obj.getMyPassiveObjectCount(24357);			
        for (local i = 0; i < bloodCutObjCount ; ++i) 
        { 
            local bloodCutObj = obj.getMyPassiveObject(24357,i);
                    if (bloodCutObj && bloodCutObj.getVar("id").get_vector(0) == 25)
                    {
                        obj.getVar("winObj").push_obj_vector( bloodCutObj );

                        obj.getVar("pos").clear_vector();
                        obj.getVar("pos").push_vector( bloodCutObj.getXPos() );
                        obj.getVar("pos").push_vector( 250 );
                        obj.getVar("pos").push_vector( 250 );
                        return true;
                    }
        }

    }

	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}



function onProc_WINBREAK(obj)
{

    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {

            local pAni = obj.sq_GetCurrentAni();
            local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);


            local startFrameIndex = 0;
            local endFrameIndex = 2;

            local currentT = sq_GetCurrentTime(pAni);

            if (frmIndex <= startFrameIndex)
            {
                obj.setCurrentPos(obj.getVar("poss").get_vector(0),obj.getYPos(),obj.getZPos() );

            }else if (frmIndex >= startFrameIndex && frmIndex <= endFrameIndex)
            {
                local startX = obj.getVar("poss").get_vector(0);
                local maxD = obj.getVar("poss").get_vector(1);

                currentT = currentT - pAni.getDelaySum(0,startFrameIndex);
                local maxT = pAni.getDelaySum(startFrameIndex,endFrameIndex);
                if (currentT < maxT)
                {
                    local v = sq_GetAccel(0, maxD, currentT,maxT, true);
                    local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);

                    if( obj.isMovablePos(dstX, obj.getYPos() ))
                    {
                        sq_setCurrentAxisPos(obj, 0, dstX);
                    }

                }
            }

        local windObj = obj.getVar("winObj").get_obj_vector(0);
        if (windObj)
        {
            local startX = obj.getVar("pos").get_vector(0);
            local maxD = obj.getVar("pos").get_vector(1);
            local maxT = obj.getVar("pos").get_vector(2);

            local pAni = obj.sq_GetCurrentAni();
            local currentT = sq_GetCurrentTime(pAni);
            local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);


            if (currentT < maxT)
            {

                local v = sq_GetAccel(0, maxD, currentT, maxT, true);
                local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);

                if(obj.isMovablePos(dstX, obj.getYPos() ) )
                {
                    sq_setCurrentAxisPos(windObj, 0, dstX);
                }

            }


        }
    }
}



function onEndCurrentAni_WINBREAK(obj)
{
        if(!obj.isMyControlObject())
            return false;

    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_WINBREAK , STATE_PRIORITY_USER, false);
    }else if (state == 1){

        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
    }
}

