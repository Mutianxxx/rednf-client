

//	`atanimation/zrr/newblood45/corruption_startdashbodyready.ani`
//	`atanimation/zrr/newblood45/corruption_startdashbody.ani`
//	`atanimation/zrr/newblood45/corruption_startdashbodyhit.ani`
//	`atanimation/zrr/newblood45/corruption_atka_atk_body.ani`
//	`atanimation/zrr/newblood45/corruption_atka_hold_body.ani`
//	`atanimation/zrr/newblood45/corruption_end_body.ani`

//CUSTOM_ANI_NEWBLOOD45_DASHREADY <- 253
//CUSTOM_ANI_NEWBLOOD45_DASH2 <- 254
//CUSTOM_ANI_NEWBLOOD45_DASHHIT <- 255
//CUSTOM_ANI_NEWBLOOD45_HOLD <- 256
//CUSTOM_ANI_NEWBLOOD45_NOHOLD <- 257
//CUSTOM_ANI_NEWBLOOD45_END <- 258
//CUSTOM_ANI_CORRPUTION_CANNETGRAB_BODY <- 338

// 0 -> 1 (onAttack Success) -> 2 (can hold) -> 3 -> 7-> 5
// 0 -> 1 (onAttack Success) -> 2 (cann't hold) -> 4 //delete
// 0 -> 1 (onAttack Success) -> 2 (cann't hold) -> 9 -> 8 
// 0 -> 1 (onAttack Fail) STATE_STAND

function checkExecutableSkill_blood45(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_BLOOD45);
	if (isUseSkill) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0); 
        obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}



function setCharacterFristAnimation_Corruption(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_BLOOD45 );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/als_ani/atcorruption/corruption_smoke.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/als_ani/atcorruption/corruption_startdashadd.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atcorruption/b/corruptionblood_eff_00.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atcorruption/b/corruptionteethawakefrontend_teeth_02.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atcorruption/b/corruptionteethawakefrontloop_teeth_00.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atcorruption/b/corruptionteethawakefrontstart_teeth_00.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atcorruption/c/corruptionteethgrabcannonfrontend_eff_08.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atcorruption/c/corruptionteethgrabcannonfrontloop_eff_08.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atcorruption/c/corruptionteethgrabcannonfrontstart_eff_08.ani");

        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/newblood45/corruption_atka_atk_body.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/newblood45/corruption_end_body.ani");


    }
}



function checkCommandEnable_blood45(obj)
{
	if(!obj)
		return false;
    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_BLOOD45, 7))) 
        return false;
	return true;

}
function createBLOOD45_Smoke(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atcorruption/corruption_smoke.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);	
}

function createBLOOD45_DashShaow(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atcorruption/corruption_startdashadd.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);	
}

function onSetState_BLOOD45(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
    local speed = obj.sq_GetIntData(SKILL_BLOOD45, 10);
    obj.getVar("speed").clear_vector();
    obj.getVar("speed").push_vector(speed);

    if (state == 0)
    {
        setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOOD45, 7));
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOOD45_DASHREADY);

        obj.getVar("v").clear_vector();
        obj.getVar("v").push_vector(0);

    }else if (state == 1)
    {
            obj.sq_SetShake(obj, 1, 30);
//        createBLOOD45_DashShaow(obj);
        local len = obj.sq_GetIntData(SKILL_BLOOD45, 0);
        local leny = 0;
        //obj.sq_GetIntData(SKILL_BLOOD45, 15);
		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);
		local upPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL);
		local downPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL);

		if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && leftPress) len = obj.sq_GetIntData(SKILL_BLOOD45, 1);
		if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && rightPress) len = obj.sq_GetIntData(SKILL_BLOOD45, 1);
		if(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && leftPress) len = obj.sq_GetIntData(SKILL_BLOOD45, 2);
		if(sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && rightPress) len = obj.sq_GetIntData(SKILL_BLOOD45, 2);

        if (upPress) leny = -obj.sq_GetIntData(SKILL_BLOOD45, 15);
        if (downPress) leny = obj.sq_GetIntData(SKILL_BLOOD45, 15);

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOOD45_DASH2);
        obj.sq_SetCurrentAttackInfo( ATTACKINFO_NEWBLOOD45_MOVE );


        local ani = obj.sq_GetCurrentAni();
		local delay = ani.getDelaySum(false);
        obj.getVar("dama").clear_obj_vector();
        obj.getVar("len").clear_vector();
        obj.getVar("len").push_vector( len );
        obj.getVar("len").push_vector( leny );

        obj.getVar("posX").clear_vector();
        obj.getVar("posX").push_vector(obj.getXPos());
        obj.getVar("posX").push_vector(delay);
        obj.getVar("posX").push_vector(obj.getYPos());

    }else if(state == 2)//hit
    {
        obj.getVar("isHold").clear_vector();
        obj.getVar("isHold").push_vector(0);

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOOD45_DASHHIT);


        local damager = obj.getVar("dama").get_obj_vector(0);
        if (!damager)
            return false;

        if ( damager.getState() == STATE_HOLD )
        {
            obj.getVar("isHold").set_vector(0,1);
        }
        obj.sq_SetfindNearLinearMovablePos(damager.getXPos(),damager.getYPos() + 2,obj.getXPos(), obj.getYPos(), 10);

		local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, 
        SKILL_BLOOD45, false, "character/atmage/blood45/ap_blood45.nut", true);				 



    }else if (state == 3)//can hold
    {

        local damager = obj.getVar("dama").get_obj_vector(0);
        local waitT = obj.sq_GetIntData(SKILL_BLOOD45, 3);
        if (obj.isMyControlObject())
        {
        sq_flashScreen(obj,200*100 / speed,(waitT+2000) * 100 / speed,200 * 100 / speed,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        }
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOOD45, STATE_BLOOD45, 0, 1.0);
		obj.sq_StartWrite();
		obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
		obj.sq_WriteDword(49);	// attackBonusRate
		obj.sq_WriteDword(waitT);	// attackBonusRate
		obj.sq_WriteDword(1);	// attackBonusRate
		obj.sq_WriteDword(speed);	// attackBonusRate
        sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, damager.getXPos(), damager.getYPos() + 1, damager.getZPos() +  damager.getObjectHeight()/2 );
        obj.setTimeEvent(1,850 * 100 / speed,0,false);
		obj.sq_SetCurrentAnimation(-1);

    }else if (state == 4) // no can hold
    {
        local damager = obj.getVar("dama").get_obj_vector(0);
        local waitT = obj.sq_GetIntData(SKILL_BLOOD45, 4);

	 obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOOD45_HOLD);
	
	 local level = sq_GetSkillLevel(obj, SKILL_BLOOD45);
        local bloodCount = obj.sq_GetIntData(SKILL_BLOOD45, 14);
        //sq_GetLevelData(obj, SKILL_BLOOD45, 2, level);
	 local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOOD45, STATE_BLOOD45, 1, 1.0);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWBLOODSONG_SPEAR);
        obj.sq_SetCurrentAttackBonusRate(attackBonusRate);				
        for (local a = 1;a < bloodCount;a++)
        {
            sq_SendHitObjectPacket(obj,damager,0,0,0);
        }
	
	
        obj.getVar("v").clear_vector();
        obj.getVar("v").push_vector(waitT);
        obj.getVar("v").push_vector(damager.getXPos() );

    }else if (state == 5)
    {

        setBloodValue(obj,obj.sq_GetIntData(SKILL_BLOOD45, 8));
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOOD45_END);

    }else if (state == 6)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOOD45_HOLD);
        local damager = obj.getVar("dama").get_obj_vector(0);
		obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));

        local posX = sq_GetDistancePos( damager.getXPos() , obj.getDirection(), obj.sq_GetIntData(SKILL_BLOOD45, 5) );
        obj.sq_SetfindNearLinearMovablePos( posX ,obj.getYPos(),obj.getXPos() + 2, obj.getYPos(), 10);


        createBLOOD45_Smoke(obj);
        sq_EffectLayerAppendage(obj,sq_RGB(0,0,0),255,0,400,0);	
    }else if (state == 7)
    {
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOOD45_HOLD);
       local damager = obj.getVar("dama").get_obj_vector(0);
       
       local level = sq_GetSkillLevel(obj, SKILL_BLOOD45);
	local bloodCount = obj.sq_GetIntData(SKILL_BLOOD45, 14);
	//sq_GetLevelData(obj, SKILL_BLOOD45, 2, level);
	local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOOD45, STATE_BLOOD45, 1, 1.0);
	obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWBLOODSONG_SPEAR);
	obj.sq_SetCurrentAttackBonusRate(attackBonusRate);				
	for (local a = 1;a < bloodCount;a++)
	{
		sq_SendHitObjectPacket(obj,damager,0,0,0);
	}
       
	obj.setCurrentDirection(sq_GetOppositeDirection(obj.getDirection()));

	local posX = sq_GetDistancePos( damager.getXPos() , obj.getDirection(), obj.sq_GetIntData(SKILL_BLOOD45, 5) );
	obj.sq_SetfindNearLinearMovablePos( posX ,obj.getYPos(),obj.getXPos() + 2, obj.getYPos(), 10);


    }else if (state == 8)
    {

	obj.sq_SetCurrentAnimation(CUSTOM_ANI_CORRPUTION_CANNETGRAB_BODY);
	local level = sq_GetSkillLevel(obj, SKILL_BLOOD45);
	local bloodCount = obj.sq_GetIntData(SKILL_BLOOD45, 14);
	//sq_GetLevelData(obj, SKILL_BLOOD45, 2, level);
	local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOOD45, STATE_BLOOD45, 2, 1.0);

	local damager = obj.getVar("dama").get_obj_vector(0);
	obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWBLOODSONG_SPEAR);
	obj.sq_SetCurrentAttackBonusRate(attackBonusRate);				
	for (local a = 0;a < bloodCount;a++)
	{
		sq_SendHitObjectPacket(obj,damager,0,0,0);
	}

        local posX = sq_GetDistancePos( damager.getXPos() , obj.getDirection(), obj.sq_GetIntData(SKILL_BLOOD45, 11) );
        obj.sq_SetfindNearLinearMovablePos( posX ,obj.getYPos(),obj.getXPos() + 2, obj.getYPos(), 10);


        local ani = obj.sq_GetCurrentAni();
		local delay = ani.getDelaySum(false);

        local v = obj.getVar("v").get_vector(0);
        local len = obj.getVar("len").get_vector(0);

        obj.getVar("len").clear_vector();
        obj.getVar("len").push_vector(obj.sq_GetIntData(SKILL_BLOOD45, 12) );// len - v);
        obj.getVar("posX").clear_vector();
        obj.getVar("posX").push_vector(obj.getXPos());
        obj.getVar("posX").push_vector(delay);


    }else if (state == 9)
    {

        local damager = obj.getVar("dama").get_obj_vector(0);
        local waitT = obj.sq_GetIntData(SKILL_BLOOD45, 4);
        if (obj.isMyControlObject())
        {
        	sq_flashScreen(obj,200*100 / speed,(waitT+2000) * 100 / speed,200 * 100 / speed,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        }
	 local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOOD45, STATE_BLOOD45, 1, 1.0);
        if (obj.isMyControlObject())
        {
            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
            obj.sq_WriteDword(49);	// attackBonusRate
            obj.sq_WriteDword(waitT);	// attackBonusRate
            obj.sq_WriteDword(0);	// attackBonusRate
            obj.sq_WriteDword(speed);	// attackBonusRate
            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, damager.getXPos(), damager.getYPos() + 1, damager.getZPos() +  damager.getObjectHeight()/2 );
            obj.setTimeEvent(1,(1200 + waitT) * 100 / speed,0,false);
        }
		obj.sq_SetCurrentAnimation(-1);
    }else if (state == 10)
    {

        local damager = obj.getVar("dama").get_obj_vector(0);
        local waitT = obj.sq_GetIntData(SKILL_BLOOD45, 4);
        if (obj.isMyControlObject())
        {
        	sq_flashScreen(obj,200*100 / speed,(waitT+2000) * 100 / speed,200 * 100 / speed,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
        }
	 local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOOD45, STATE_BLOOD45, 1, 1.0);
        if (obj.isMyControlObject())
        {
            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
            obj.sq_WriteDword(49);	// attackBonusRate
            obj.sq_WriteDword(waitT);	// attackBonusRate
            obj.sq_WriteDword(0);	// attackBonusRate
            obj.sq_WriteDword(speed);	// attackBonusRate
            sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, damager.getXPos(), damager.getYPos() + 1, 
            damager.getZPos() +  damager.getObjectHeight()/2 );

            obj.setTimeEvent(1,450 * 100 / speed,0,false);
        }
		obj.sq_SetCurrentAnimation(-1);

    }else if (state == 11)
    {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOOD45_NOHOLD);
    }
//
//
//    local currentAnip = sq_GetCurrentAnimation(obj);
//    currentAnip.setSpeedRate(speed.tofloat() );				
}

function onTimeEvent_BLOOD45(obj, timeEventIndex, timeEventCount)
{
    local state = obj.getSkillSubState();
    if (state == 9)
    {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(8); 
            obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
    }else if (state == 4 )
    {
        if (timeEventIndex == 1)
        {

            obj.sq_IntVectClear();
            obj.sq_IntVectPush(5); 
            obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
        }
    }else if (state == 3)
    {
        if (timeEventIndex == 1)
        {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(7); 
            obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
        }
    }else if (state == 10)
    {
        if (timeEventIndex == 1)
        {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(4); 
            obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
        }
    }

}

function onAttack_BLOOD45(obj, damager, boundingBox, isStuck)
{

    local state = obj.getSkillSubState();
    if (state == 1)
    {
        createBLOOD45_Smoke(obj);
        obj.getVar("dama").push_obj_vector(damager);
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2); 
        obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);

    }
}

function onEndCurrentAni_BLOOD45(obj)
{
    local state = obj.getSkillSubState();
    if (state == 0)
    {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1); 
        obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);

    }else if (state == 1){
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 2){

        local damager = obj.getVar("dama").get_obj_vector(0);
		if(sq_IsGrabable(obj,damager) 
		     && sq_IsHoldable(obj,damager) 
		     && !sq_IsFixture(damager)
             && obj.getVar("isHold").get_vector(0) == 0 ) 
        {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(3); 
            obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
        }else{
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(10); 
            obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
        }
    }else if (state == 3){


		obj.sq_IntVectClear();
		obj.sq_IntVectPush(7); 
        obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);


    }else if (state == 4){
        local speed = obj.getVar("speed").get_vector(0);
        local waitT = obj.getVar("v").get_vector(0);
        obj.setTimeEvent(1,(waitT + 600)*100 / speed,0,false);
    }else if (state == 5){

        sq_SendMessage(obj,OBJECT_MESSAGE_INVINCIBLE,1,0);
        sq_PostDelayedMessage(obj,OBJECT_MESSAGE_INVINCIBLE,0,0,obj.sq_GetIntData(SKILL_BLOOD45, 13) );

        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 6){


		obj.sq_IntVectClear();
		obj.sq_IntVectPush(5); 
        obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
    }else if (state == 7){



		obj.sq_IntVectClear();
		obj.sq_IntVectPush(5); 
        obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
    }else if (state == 8){
        sq_SendMessage(obj,OBJECT_MESSAGE_INVINCIBLE,1,0);
        sq_PostDelayedMessage(obj,OBJECT_MESSAGE_INVINCIBLE,0,0,obj.sq_GetIntData(SKILL_BLOOD45, 13) );

        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 11){
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(5); 
        obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);


    }
}


function onProc_BLOOD45(obj)
{

    local state = obj.getSkillSubState();
	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
    if (state == 0)
    {

    }else if (state == 1)
    {
        if (frmIndex == 0)
        {

        }
        local currentT = sq_GetCurrentTime(pAni);
        local delayT = obj.getVar("posX").get_vector(1);
        local len = obj.getVar("len").get_vector(0);
        local leny = obj.getVar("len").get_vector(1);

		local v = sq_GetAccel(0, len, currentT, delayT, true);
        local v2 = sq_GetAccel(0, leny, currentT, delayT, true);

		local srcX = obj.getVar("posX").get_vector(0);
		local scrY = obj.getVar("posX").get_vector(2);

		local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);
		local dstY = scrY + v2;

		if(obj.isMovablePos(dstX, dstY ))
        {
			sq_setCurrentAxisPos(obj, 0, dstX);
			sq_setCurrentAxisPos(obj, 1, dstY);
        }

        obj.getVar("v").clear_vector();
        obj.getVar("v").push_vector(v);



    }else if (state == 2)
    {




    }else if (state == 4)
    {
        local damaX = obj.getVar("v").get_vector(1);
        local currentT = sq_GetCurrentTime(pAni);
        if (currentT < 300)
        {
            local v = sq_GetAccel(0, -75, currentT, 300, true);
            local dstX = sq_GetDistancePos(damaX, obj.getDirection(), v);
			if(obj.isMovablePos(dstX, obj.getYPos() ) )
				sq_setCurrentAxisPos(obj, 0, dstX);


        }else if (currentT < 1000){

            local dstX = sq_GetDistancePos(damaX, obj.getDirection(), -75);
			if(obj.isMovablePos(dstX, obj.getYPos() ) )
				sq_setCurrentAxisPos(obj, 0, dstX);

        }else{

            obj.sq_IntVectClear();
            obj.sq_IntVectPush(11); 
            obj.sq_AddSetStatePacket(STATE_BLOOD45, STATE_PRIORITY_USER, true);
        }

    }else if (state == 8)
    {
        local currentT = sq_GetCurrentTime(pAni);
        local delayT = obj.getVar("posX").get_vector(1);
        local len = obj.getVar("len").get_vector(0);
    
		local v = sq_GetAccel(0, len, currentT, delayT, true);
		local srcX = obj.getVar("posX").get_vector(0);
		
		local dstX = sq_GetDistancePos(srcX, obj.getDirection(), v);
		 
		if(obj.isMovablePos(dstX, obj.getYPos() ))
			sq_setCurrentAxisPos(obj, 0, dstX);
    }
}
