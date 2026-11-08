function checkExecutableSkill_bloodhit(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_BLOODHIT);
	if (isUseSkill) 
    {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);	
		obj.sq_AddSetStatePacket(STATE_BLOODHIT, STATE_PRIORITY_USER, true);
    }
		return false;
}

function checkCommandEnable_bloodhit(obj)
{
	if(!obj)
		return false;
    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_BLOODHIT, 1))) 
        return false;

		
	return true;
}

function setCharacterFristAnimation_Offering(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_BLOODHIT );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/als_ani/atoffering/offeringatka_front_eff_05.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/als_ani/atoffering/nnofferingatkdwave.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/als_ani/atoffering/offeringatkceff_eff_00.ani");

        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/bloodhit/offeringatka_body.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/bloodhit/offeringatkb_body.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/bloodhit/offeringatkc_body.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/bloodhit/offeringatkd_body.ani");


    }
}


function createFrontBloodHitEffect(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atoffering/offeringatka_front_eff_05.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}
function createFrontBloodHitEffectUpWave(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atoffering/nnofferingatkdwave.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFrontBloodHitEffectState2_Break(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atoffering/offeringatkceff_eff_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createBloodEyeState0(obj)
{

}
function characterRgbUpdate(obj,r,g,b,t0,t1,t2,tm)
{
    pass;
//    sq_EffectLayerAppendage(obj,sq_RGB(r,g,b),t0,t1,t2,tm);	
}


function onSetState_BLOODHIT(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	obj.sq_StopMove();
	
	
	local subState = obj.sq_GetVectorData(datas, 0);	
	obj.sq_SetSkillSubState(obj, subState);
	
	if (subState == 0)
	{
        if (obj.isMyControlObject())
        {
            setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOODHIT, 1));
//            createFrontBloodHitEffect(obj);
        }
        obj.getVar("dama_bloodhit").clear_obj_vector();
        obj.getVar("isEnd").clear_vector();
        obj.getVar("isEnd").push_vector(0);

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODHIT_NEWHOLD);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODHIT_NEWGRAB);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODHIT , STATE_BLOODHIT, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

	}
	else if (subState == 1)
	{
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);

        obj.getVar().clear_vector();
        obj.getVar().push_vector(0);

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODHIT_NEWDROP);

		obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODHIT_THROW);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODHIT , STATE_BLOODHIT, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				
	}else if (subState == 2)
    {
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODHIT_NEWLOOP);

		obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODHIT_BREAKHIT);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODHIT , STATE_BLOODHIT, 2, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				
    }else if (subState == 3)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODHIT_MISS);
    }else if (subState == 4)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODHIT_NEWLOOP);
    }

}


function onProc_BLOODHIT(obj)
{



    local pAni = obj.sq_GetCurrentAni();
    local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
    local currentT = sq_GetCurrentTime(pAni);

    if (obj.sq_GetSkillSubState(obj) == 0)
    {
        local var = obj.getVar("dama_bloodhit");  		
        local objectsSize = var.get_obj_vector_size();


        if (objectsSize > 0)
        {

            for(local i=0;i<objectsSize;++i)
            {
                local damager = var.get_obj_vector(i);

                local dvalue = 1;
                if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT) dvalue = -1;

                if( !sq_IsGrabable(obj,damager) || !sq_IsHoldable(obj,damager) || sq_IsFixture(damager) )
                {

                    obj.sq_IntVectClear();
                    obj.sq_IntVectPush(2);	
                    obj.sq_AddSetStatePacket(STATE_BLOODHIT, STATE_PRIORITY_USER, true);
                    return false;

                }
                if (frmIndex == 3)
                {
                    damager.setCurrentPos(obj.getXPos() + 59 * dvalue,obj.getYPos() - 1,
                    obj.getZPos() + 101 - damager.getObjectHeight()/2);
                    damager.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
                    sq_SetCustomRotate(damager,-0.1 );
                }else if (frmIndex >= 4)
                {
                    damager.setCurrentPos(obj.getXPos() + 60 * dvalue,obj.getYPos() - 1,
                    obj.getZPos() + 96 - damager.getObjectHeight()/2);
                    damager.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
                    sq_SetCustomRotate(damager,-0.12 );
                }
            }

            if (frmIndex == 3)
            {
                obj.sq_SetShake(obj, 1, 70);
            }

            obj.setSkillCommandEnable(SKILL_BLOODHIT, true);

            local iEnterSkill = obj.sq_IsEnterSkill(SKILL_BLOODHIT);

            if (iEnterSkill != -1 || obj.sq_timer_.isOnEvent(currentT) == true || sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
            {
                if(!obj.isMyControlObject()) {
                    return;
                }
                obj.sq_IntVectClear();
                obj.sq_IntVectPush(1);	
                obj.sq_AddSetStatePacket(STATE_BLOODHIT, STATE_PRIORITY_USER, true);
            }

            if (obj.getVar("isEnd").get_vector(0) == 1)
            {
                    if(!obj.isMyControlObject()) {
                        return;
                    }
                obj.sq_IntVectClear();
                obj.sq_IntVectPush(4);	
                obj.sq_AddSetStatePacket(STATE_BLOODHIT, STATE_PRIORITY_USER, true);


            }

        
        }else{

            if (obj.getVar("isEnd").get_vector(0) == 1)
            {
                if(!obj.isMyControlObject()) {
                    return;
                }
                obj.sq_IntVectClear();
                obj.sq_IntVectPush(3);	
                obj.sq_AddSetStatePacket(STATE_BLOODHIT, STATE_PRIORITY_USER, true);


            }

        }


    }else if (obj.sq_GetSkillSubState(obj) == 1)
    {


        if (frmIndex >= 6 && obj.getVar().get_vector(0) == 0)
        {
                obj.getVar().set_vector(0,1);
                sq_flashScreen(obj,0,20,240,204, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
                obj.sq_SetShake(obj, 5, 240);
        }

        local var = obj.getVar("dama_bloodhit");  		
        local objectsSize = var.get_obj_vector_size();

        for(local i=0;i<objectsSize;++i)
        {
            local posX = obj.getXPos();
            local posY = obj.getYPos();
            local posZ = obj.getZPos();


            local damager = var.get_obj_vector(i);

            if (damager)
            {
                local pAni = obj.sq_GetCurrentAni();
                local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);

                local x = 0;
                local y = -1;
                local z = 0;
                local xz = 0;

                if (frmIndex == 0)
                {
                    xz = -75;
                    x = 36;
                    z  = 138;
                }else if (frmIndex == 1)
                {
                    xz = -90;
                    x = 21;
                    z  = 148;
                }else if (frmIndex == 2)
                {
                    xz = -105;
                    x = -3;
                    z  = 132;
                }else if (frmIndex == 3)
                {
                    xz = -130;
                    x = -27;
                    z  = 112;
                }else if (frmIndex == 4)
                {
                    xz = -90;
                    x = 21;
                    z  = 148;
                }else if (frmIndex == 5)
                {
                    xz = 0;
                    x = 150;
                    z  = 12;
                }

                if (frmIndex <= 5)
                {
                    local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(),x );
                    if (xz != 0)
                        sq_SetCustomRotate(damager, (xz + 90).tofloat() / 100.0 );
                    else
                        sq_SetCustomRotate(damager,0.0 );

                    local lastZ = obj.getZPos() + z - damager.getObjectHeight()/2 ;
                    if (lastZ < 0)
                        lastZ = 0


                    posX = damager.sq_findNearLinearMovableXPos(posX, damager.getYPos(),damager.getXPos(), damager.getYPos(), 10);

                    damager.setCurrentPos(posX,obj.getYPos() + y,lastZ );
                }else{
                    sq_SetCustomRotate(damager,0.0 );
                }

            }
            

        }



    }else if  ( obj.sq_GetSkillSubState(obj) == 2)
    {
        if (currentT > 300)
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if  ( obj.sq_GetSkillSubState(obj) == 3)
    {
    }else if  ( obj.sq_GetSkillSubState(obj) == 4)
    {

        local var = obj.getVar("dama_bloodhit");  		
        local objectsSize = var.get_obj_vector_size();

        if (objectsSize > 0)
        {

            for(local i=0;i<objectsSize;++i)
            {
                local damager = var.get_obj_vector(i);
                local dvalue = 1;
                if (sq_GetDirection(obj) == ENUM_DIRECTION_LEFT) dvalue = -1;
                damager.setCurrentPos(obj.getXPos() + 60 * dvalue,obj.getYPos() - 1,
                obj.getZPos() + 96 - damager.getObjectHeight()/2);
				damager.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
                sq_SetCustomRotate(damager,-0.12 );





            }



        	local pAni = obj.sq_GetCurrentAni();
            local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
            local currentT = sq_GetCurrentTime(pAni);

            obj.setSkillCommandEnable(SKILL_BLOODHIT, true);

            local iEnterSkill = obj.sq_IsEnterSkill(SKILL_BLOODHIT);

            if (iEnterSkill != -1 || obj.sq_timer_.isOnEvent(currentT) == true || sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
            {
                if(!obj.isMyControlObject()) {
                    return;
                }
                obj.sq_IntVectClear();
                obj.sq_IntVectPush(1);	
                obj.sq_AddSetStatePacket(STATE_BLOODHIT, STATE_PRIORITY_USER, true);
            }

        }

    }

}





function onEndCurrentAni_BLOODHIT(obj)
{
	if (!obj) return;
	
	
	if(!obj.isMyControlObject()) {
		return;
	}

	if (obj.sq_GetSkillSubState(obj) == 0) 
    {

        obj.getVar("isEnd").clear_vector();
        obj.getVar("isEnd").push_vector(1);


    }

    if (obj.sq_GetSkillSubState(obj) == 1)
    {

        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
    if (obj.sq_GetSkillSubState(obj) == 2)
    {

        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
    if (obj.sq_GetSkillSubState(obj) == 3)
    {

        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }

}


function onAttack_BLOODHIT(obj, damager, boundingBox, isStuck)
{

    if (obj.sq_GetSkillSubState(obj) == 0)
    {
        setCustomHitEffectBloodMageCut(obj,damager,0);
        if ( damager.isObjectType(OBJECTTYPE_ACTIVE))
        {

            obj.getVar("dama_bloodhit").push_obj_vector(damager);

            obj.sq_timer_.setParameter(obj.sq_GetIntData(SKILL_BLOODHIT, 0),-1);
            obj.sq_timer_.resetInstant(0);


		if(!(damager.getState() != STATE_HOLD 
		     && sq_IsGrabable(obj,damager) 
		     && sq_IsHoldable(obj,damager) 
		     && !sq_IsFixture(damager))) 
            {

                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODHIT, false, 
                "character/atmage/bloodhit/ap_bloodhit2.nut", true);				 
                if(masterAppendage) 
                {
                    damager.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));
                    masterAppendage.sq_SetValidTime(2000);
                }
                if(!obj.isMyControlObject()) {
                    return;
                }

                obj.sq_IntVectClear();
                obj.sq_IntVectPush(2);	
                obj.sq_AddSetStatePacket(STATE_BLOODHIT, STATE_PRIORITY_USER, true);
                return false;
            }

            local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODHIT, false, "character/atmage/bloodhit/ap_bloodhit.nut", true);				 



        }


    }else {
        setCustomHitEffectBloodMageBlow(obj,damager);
    }

}






function onKeyFrameFlag_BLOODHIT(obj, flagIndex)
{


    if (obj.sq_GetSkillSubState(obj) == 1)
    {
        if (flagIndex == 1 && obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);
            local var = obj.getVar("dama_bloodhit");  		
            local objectsSize = var.get_obj_vector_size();
            for(local i=0;i<objectsSize;++i)
            {
                local damager = var.get_obj_vector(i);
//                sq_SendHitObjectPacket(obj,damager,0,0,0);
//                obj.sq_SetShake(obj, 10, 100);
                if(damager)
                {
                    CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/bloodhit/ap_bloodhit.nut");		
                }
            }
        }
    }

    if (obj.sq_GetSkillSubState(obj) == 2)
    {
        if (flagIndex == 1 && obj.getVar("flag").get_vector(0) == 0)
        {
            obj.getVar("flag").clear_vector();
            obj.getVar("flag").push_vector(1);

            local var = obj.getVar("dama_bloodhit");  		
            local objectsSize = var.get_obj_vector_size();
            for(local i=0;i<objectsSize;++i)
            {
                local damager = var.get_obj_vector(i);
                sq_SendHitObjectPacket(obj,damager,0,0,0);

                if(damager)
                {
                    CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/bloodhit/ap_bloodhit.nut");		
                }

            }


            sq_flashScreen(obj,0,40,180,153, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
            obj.sq_SetShake(obj, 5, 180);
            createFrontBloodHitEffectState2_Break(obj,66,1,67);

        }

    }



}













