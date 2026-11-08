function setCustomData_po_blooddog0(obj, receiveData)
{
	if(!obj)
		return;
	local attackBonusRate0 = receiveData.readDword();// ?????(%)	
    local attackBonusRate1 = receiveData.readDword();// ?????(%)	
    local time0 = receiveData.readDword();
    local time1 = receiveData.readDword();
    local isShort = receiveData.readDword();

    if (isShort == 1)
    {
        local ani = obj.getCustomAnimation(1);
		obj.setCurrentAnimation(ani);
    }

    obj.getVar("dama").clear_obj_vector();

    obj.getVar("values").clear_vector();
    obj.getVar("values").push_vector(attackBonusRate1);
    obj.getVar("values").push_vector(time0);
    obj.getVar("values").push_vector(time1);
    obj.getVar("values").push_vector(attackBonusRate0);

    obj.getVar("state").clear_vector();
    obj.getVar("state").push_vector(0);


	local attackInfo = sq_GetCustomAttackInfo(obj, 0);
	sq_SetCurrentAttackInfo(obj, attackInfo);

    attackInfo = sq_GetCurrentAttackInfo(obj);
    sq_SetCurrentAttackeHitStunTime(attackInfo, 0);

}

function onAttack_po_blooddog0(obj, damager, boundingBox, isStuck)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {

        local mage = obj.getParent();
        mage = sq_ObjectToSQRCharacter(mage);	

        setCustomHitEffectBloodMageCut(obj,damager,0);
        if (mage && damager.getState() != STATE_HOLD && damager.getState() != STATE_DIE)
        {
            obj.getVar("dama").push_obj_vector(damager);
            obj.sq_PlaySound("BLOODDOGHOLD");
            damager = sq_GetCNRDObjectToActiveObject(damager);
		local isApd = CNSquirrelAppendage.sq_IsAppendAppendage(damager, "character/atmage/blooddog/ap_blooddog.nut");
            if (!damager.isDead() && !isApd)
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODDOG, false, 
                "character/atmage/blooddog/ap_blooddog.nut", true);				 

                if(masterAppendage) 
                {
                    masterAppendage.getVar("dog").clear_obj_vector();
                    masterAppendage.getVar("dog").push_obj_vector(obj);
                    masterAppendage.getVar("dog").push_obj_vector(mage);
                }
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, mage, SKILL_BLOODDOG, false, 
                "character/atmage/append_bloodmage/ap_blooddog.nut", true);				 

            }
					 

		local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODDOG, false, "character/atmage/blooddog/ap_blooddog.nut", true);				 
		if(masterAppendage) 
    		{
			sq_HoldAndDelayDie(damager, obj, true,false, false, 200, 200, ENUM_DIRECTION_NEUTRAL , masterAppendage);
    		}

   	 	
            if (!CNSquirrelAppendage.sq_IsAppendAppendage(mage, "character/atmage/append_bloodmage/ap_blooddog_character.nut"))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(mage, mage, SKILL_BLOODDOG, false, 
                "character/atmage/append_bloodmage/ap_blooddog_character.nut", true);				 
            }
        }

    }else if (state == 1)
    {

        setCustomHitEffectBloodMageBlow(obj,damager);


    }

}



function onTimeEvent_po_blooddog0(obj, timeEventIndex, timeEventCount)
{

	if(!obj.isMyControlObject())
		return false;


    if (timeEventIndex == 0) 
    {
        sq_SendCreatePassiveObjectPacketPos(obj,12335, 0, sq_GetXPos(obj),sq_GetYPos(obj) + 1,sq_GetZPos(obj));
        sq_SendDestroyPacketPassiveObject(obj);
    }else if (timeEventIndex == 1)
    {

        obj.sq_PlaySound("BLOODDOGHOLD2");

        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();
        for(local i=0;i<objectsSize;++i)
        {
            local damager = var.get_obj_vector(i);
            sq_SendHitObjectPacket(obj,damager,0,0,0);

        }
        sq_SetMyShake(obj,1,60);

    }
}

function createBackBloodDogHitEffect(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athellberus/awakening/awakeninghita_back_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() +60);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}
function createFrontBloodDogHitEffect(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/athellberus/awakening/awakeninghita_front_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() +60);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function onKeyFrameFlag_po_blooddog0(obj, flagIndex)
{
    if (flagIndex == 1)
    {
        local var = obj.getVar("dama");  		
        local objectsSize = var.get_obj_vector_size();
        if (objectsSize > 0 )
        {
            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);

        	local ani = obj.getCustomAnimation(0);
			obj.setCurrentAnimation(ani);

            local attackBonusRate = obj.getVar("values").get_vector(3);

            local attackInfo = sq_GetCustomAttackInfo(obj, 1);
            sq_SetCurrentAttackInfo(obj, attackInfo);
            attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

            createHellBerus02_Smoke(obj);
            sq_SendCreatePassiveObjectPacketPos(obj,12370, 0, sq_GetXPos(obj),sq_GetYPos(obj) + 1,sq_GetZPos(obj));
            sq_SendCreatePassiveObjectPacketPos(obj,12312, 0, sq_GetXPos(obj),sq_GetYPos(obj) + 1,sq_GetZPos(obj) + 60);
            createBackBloodDogHitEffect(obj);
            createHellBerus01_HitEffectHitB(obj);

            for(local i=0;i<objectsSize;++i)
            {
                local damager = var.get_obj_vector(i);
                sq_SendHitObjectPacket(obj,damager,0,0,0);
            }


            attackBonusRate = obj.getVar("values").get_vector(0);
            attackInfo = sq_GetCustomAttackInfo(obj, 2);
            sq_SetCurrentAttackInfo(obj, attackInfo);
            attackInfo = sq_GetCurrentAttackInfo(obj);
            sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

            obj.setTimeEvent(0, obj.getVar("values").get_vector(1), 1, false);
            obj.setTimeEvent(1,obj.getVar("values").get_vector(2),0, true);

        }

    }else if (flagIndex == 2)
    {
        createHellBerus01_HitEffectFront01(obj);
        createHellBerus01_HitEffectBack01(obj);
    }
    return true;

}

function onEndCurrentAni_po_blooddog0(obj)
{
    sq_SendDestroyPacketPassiveObject(obj);

}


