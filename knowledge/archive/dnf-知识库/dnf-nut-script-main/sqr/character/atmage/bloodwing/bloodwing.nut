function checkExecutableSkill_wing(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_WING);

	if (isUse) {

			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			
			obj.addSetStatePacket(STATE_WING , pIntVec, STATE_PRIORITY_FORCE, false, "");
	}

	return false;
}




function setCharacterFristAnimation_BloodWing(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_WING );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/als_ani/atbloodwing/pass/bloodwingmove_01.ani");

        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/new_bloodwing/bloodwingawakeend_04.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/new_bloodwing/bloodwingawakemove_04.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/new_bloodwing/bloodwingawakestart01_05.ani");

    }
}

function checkCommandEnable_wing(obj)
{
    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_WING, 2)))
        return false;
	return true;
}

function createNEWWING(obj,xz)
{

	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atbloodwing/pass/bloodwingmove_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	
	pooledObj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());

    sq_SetCustomRotate(pooledObj, xz);	
	sq_moveWithParent(obj, pooledObj);
	
	sq_AddObject(obj,pooledObj,0,false);	
}


function onAttack_WING(obj, damager, boundingBox, isStuck)
{
    setCustomHitEffectBloodMageCut(obj,damager,0);
    local state = obj.getSkillSubState();
    if (state == 1)
    {
        if (damager.isObjectType(OBJECTTYPE_ACTIVE))
        {
            obj.getVar("dama").push_obj_vector(damager);
        }
    }
}


function onSetState_WING(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	obj.sq_StopMove();

	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);


    if(state == 0)
    {
        obj.getVar("isFly").clear_vector();
        if (obj.getZPos() > 0) 
        {   
            obj.getVar("isFly").push_vector(1);
        }else{
            obj.getVar("isFly").push_vector(0);
        }


        setBloodValue(obj,-obj.sq_GetIntData(SKILL_WING, 2));
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOODWING_READY);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);

    }else if(state == 1)
    {
        local isfly = obj.getVar("isFly").get_vector(0);//0 in floor  1 on sky

        obj.getVar("dama").clear_obj_vector();
        obj.getVar("isEnd").clear_vector();
        obj.getVar("isEnd").push_vector(0);

        local ani = obj.sq_GetCurrentAni();
		local delay = ani.getDelaySum(false);
        local xz = obj.sq_GetIntData(SKILL_WING, 1); // 0

        if (isfly == 1)
            xz = obj.sq_GetIntData(SKILL_WING, 4);// -78

        sq_SetCustomRotate(obj, xz.tofloat() / 100.0 );	


        obj.getVar("len").clear_vector();
        obj.getVar("len").push_vector( obj.sq_GetIntData(SKILL_WING, 0) );

        obj.getVar("posX").clear_vector();
        obj.getVar("posX").push_vector(obj.getXPos());
        obj.getVar("posX").push_vector( obj.sq_GetIntData(SKILL_WING, 7) / 2 );
        obj.getVar("posX").push_vector(obj.getZPos());


        obj.setTimeEvent(0,(obj.sq_GetIntData(SKILL_WING, 7)/ 2) / obj.sq_GetIntData(SKILL_WING, 5),0,false);		


        createNEWWING(obj,xz.tofloat() / 100.0 );

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOODWING_DASH);

		local pAni = obj.sq_GetCurrentAni();
		pAni.setSpeedRate(200.0);

        obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWBLOODWING_DASH);
        local damage = obj.sq_GetBonusRateWithPassive(SKILL_WING , STATE_WING, 0, 1.0); 
        obj.sq_SetCurrentAttackBonusRate(damage);

        if ( obj.isMyControlObject() )
        {
            local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_WING , STATE_WING, 1, 1.0); 
            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
            obj.sq_WriteDword(116);	// attackBonusRate
            obj.sq_WriteDword( obj.sq_GetIntData(SKILL_WING, 7) / obj.sq_GetIntData(SKILL_WING, 6) );
            obj.sq_WriteDword(xz);	// attackBonusRate
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);
        }

    }else if(state == 2)
    {
        sq_SetCustomRotate(obj, 0.0);	
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOODWING_END);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT,1.0, 1.0);
    }

}


function onTimeEvent_WING(obj, timeEventIndex, timeEventCount)
{
    local state = obj.getSkillSubState();
    if (state == 1)
    {

			obj.resetHitObjectList();
    }
}

function onProc_WING(obj)
{

    local state = obj.getSkillSubState();
    
    if (state == 1)
    {

        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);
        local delayT = obj.getVar("posX").get_vector(1);
        local len = obj.getVar("len").get_vector(0);

        if (currentT < delayT)
        {



            local v = sq_GetAccel(0, len, currentT, delayT, true);
            local v2 = sq_GetAccel(obj.getVar("posX").get_vector(2), 0, currentT, delayT, true);
            local srcX = obj.getVar("posX").get_vector(0);
            
            local dstX = sq_GetDistancePos(srcX, obj.getDirection(),v);
             
            if(obj.isMovablePos(dstX, obj.getYPos() ))
            {
                sq_setCurrentAxisPos(obj, 0, dstX);
                sq_setCurrentAxisPos(obj, 2, v2);
            }


            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();

            if (objectsSize > 0)
            {

                for(local i=0;i<objectsSize;++i)
                {
                    local damager = var.get_obj_vector(i);
                    local dstX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), obj.sq_GetIntData(SKILL_WING, 3) );
                    damager.setCurrentPos(dstX,damager.getYPos(),damager.getZPos() );
                }

            }




        }else{

			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 2);
			
			obj.addSetStatePacket(STATE_WING , pIntVec, STATE_PRIORITY_FORCE, false, "");


        }

    }
}

function onEndCurrentAni_WING(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
    local state = obj.getSkillSubState();
    if (state == 0)
    {
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 1);
			
			obj.addSetStatePacket(STATE_WING , pIntVec, STATE_PRIORITY_FORCE, false, "");
    }else if (state == 1)
    {


    }else if (state == 2)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
    }

}
