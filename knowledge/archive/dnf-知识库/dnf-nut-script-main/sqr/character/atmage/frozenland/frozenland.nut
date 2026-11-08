
SUB_STATE_FROZENLAND_0	<- 0
SUB_STATE_FROZENLAND_1	<- 1
SUB_STATE_FROZENLAND_2	<- 2
SUB_STATE_FROZENLAND_3	<- 3
SUB_STATE_FROZENLAND_4	<- 4
SUB_STATE_FROZENLAND_CASTING	<- 5

function createShockWaveAnimation(obj, x, y, z)
{
	local ani = sq_CreateAnimation("", "passiveobject/character/mage/animation/atblizzardstorm/column/columnbottomwave_01.ani");
	
	local shockWaveObj = sq_CreatePooledObject(ani,true);
	shockWaveObj = sq_SetEnumDrawLayer(shockWaveObj, ENUM_DRAWLAYER_BOTTOM);
	
	if(shockWaveObj)
	{
		shockWaveObj.setCurrentPos(x,y,z);
		sq_AddObject(obj, shockWaveObj, OBJECTTYPE_DRAWONLY, false);
	}
}

function setCharacterFristAnimation_FrozenLand(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_FROZENLAND );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/frozenland1.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/frozenland2.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/frozenland3.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/frozenlandcasting.ani");

        createFristAnimationPooledObject(obj,
        "passiveobject/character/mage/animation/atblizzardstorm/column/column_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/character/mage/animation/atblizzardstorm/column/startcolumn_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/character/mage/animation/atblizzardstorm/end/endstorm_04.ani");

        createFristAnimationPooledObject(obj,
        "passiveobject/character/mage/animation/atblizzardstorm/magiccircle/circleend_03.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/character/mage/animation/atblizzardstorm/magiccircle/circleloop_01.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/character/mage/animation/atblizzardstorm/magiccircle/circlestart_04.ani");

    }
}

function checkExecutableSkill_FrozenLand(obj)
{

	if(!obj) return false;

	local b_useskill = obj.sq_IsUseSkill(SKILL_FROZENLAND);

	if(b_useskill) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(SUB_STATE_FROZENLAND_CASTING); // substate????
		obj.sq_AddSetStatePacket(STATE_FROZENLAND, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}	
	
	return false;

}

function checkCommandEnable_FrozenLand(obj)
{
	if(!obj) return false;
	return true;
}

function onSetState_FrozenLand(obj, state, datas, isResetTimer)
{

	if(!obj) return;

	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();

	obj.getVar().clear_vector();
	obj.getVar().push_vector(0);
	obj.getVar().push_vector(0);
	obj.getVar().push_vector(0);
	obj.getVar().push_vector(0);
	obj.getVar().push_vector(0);
	obj.getVar("speed").clear_vector();
	obj.getVar("speed").push_vector(100);
	obj.getVar("state").clear_ct_vector();
	obj.getVar("state").push_ct_vector();	
	
	
	if(substate == SUB_STATE_FROZENLAND_CASTING)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_FROZENLAND_CASTING);
		
		local skillLevel = sq_GetSkillLevel(obj, SKILL_FROZENLAND);
		local castTime = sq_GetCastTime(obj, SKILL_FROZENLAND, skillLevel);
		local animation = sq_GetCurrentAnimation(obj);
		local startTime = sq_GetFrameStartTime(animation, 16);
		local speedRate = startTime.tofloat() / castTime.tofloat();
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);

		sq_StartDrawCastGauge(obj, startTime, true);
		obj.sq_PlaySound("MW_SLASHWATER");
	}
	else if(substate == SUB_STATE_FROZENLAND_0) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_FROZENLAND1);
		
	}
	else if(substate == SUB_STATE_FROZENLAND_1) {
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_FROZENLAND2);
	}
	else if(substate == SUB_STATE_FROZENLAND_2) {
		local t = obj.getVar("state").get_ct_vector(0);
		t.Reset();
		t.Start(10000,0);
		//obj.sq_SetCurrentAnimation(CUSTOM_ANI_FROZENLAND3);
	}
	else if(substate == SUB_STATE_FROZENLAND_3)
	{
		//print(" obj.sq_SetCurrentAnimation(CUSTOM_ANI_FROZENLAND3);");
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_FROZENLAND3);
	}
	else if(substate == SUB_STATE_FROZENLAND_4) {
		// SUB_STATE_FROZENLAND_4 ????????? ???
	}
	
}

function prepareDraw_FrozenLand(obj)
{

	if(!obj) return;
	
}

function onProc_FrozenLand(obj) {

	if (!obj) return;

	local substate = obj.getSkillSubState();
	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	local currentT = sq_GetCurrentTime(pAni);
	if (substate != SUB_STATE_FROZENLAND_CASTING) {
		obj.setSkillCommandEnable(SKILL_FROZENLAND, true);
		local iEnterSkill = obj.sq_IsEnterSkill(SKILL_FROZENLAND);
		if (sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL) || iEnterSkill != -1)
			obj.getVar("speed").set_vector(0, obj.sq_GetIntData(SKILL_FROZENLAND, 6));
	}
	if (substate == SUB_STATE_FROZENLAND_0) {
		// SUB_STATE_FROZENLAND_0 ????????? ???
	} else if (substate == SUB_STATE_FROZENLAND_1) {
		// SUB_STATE_FROZENLAND_1 ????????? ???
	} else if (substate == SUB_STATE_FROZENLAND_2) {
		// SUB_STATE_FROZENLAND_2 ????????? ???
		local t = obj.getVar("state").get_ct_vector(0);
		local currentT = 0;
		currentT = t.Get();
		if (currentT > 240) {
			if (!obj.getVar().get_vector(1)) {
				//obj.sq_SetCurrentAnimation(CUSTOM_ANI_FROZENLAND3);
				if (obj.isMyControlObject()) {
					obj.sq_IntVectClear();
					obj.sq_IntVectPush(SUB_STATE_FROZENLAND_3); // substate????
					obj.sq_AddSetStatePacket(STATE_FROZENLAND, STATE_PRIORITY_IGNORE_FORCE, true);
				}
				obj.getVar().set_vector(1, 1);
			}
		}
	} else if (substate == SUB_STATE_FROZENLAND_3) {
		// SUB_STATE_FROZENLAND_3 ????????? ???
	} else if (substate == SUB_STATE_FROZENLAND_4) {
		// SUB_STATE_FROZENLAND_4 ????????? ???
	}
}

function onProcCon_FrozenLand(obj)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	
	if(substate == SUB_STATE_FROZENLAND_0) {
		if(frmIndex >= 4) {	
			if(obj.getVar().get_vector(0) == 0) 
			{			
				if(obj.isMyControlObject())
				{
					local radiusRate = obj.sq_GetIntData(SKILL_FROZENLAND, 0);
					local stopSpinNum = obj.sq_GetIntData(SKILL_FROZENLAND, 2); 
					local spinTime = obj.sq_GetIntData(SKILL_FROZENLAND, 3); 
					
					sq_BinaryStartWrite();
					sq_BinaryWriteDword(radiusRate); 
					sq_BinaryWriteDword(stopSpinNum); 
					sq_BinaryWriteDword(spinTime); 
					
					local multiHitTerm = obj.sq_GetIntData(SKILL_FROZENLAND, 1); 
					local multiHitAttackRate = obj.sq_GetBonusRateWithPassive(SKILL_FROZENLAND, STATE_FROZENLAND, 0, 1.0); 
					local expAttackRate = obj.sq_GetBonusRateWithPassive(SKILL_FROZENLAND, STATE_FROZENLAND, 1, 1.0); 
					 obj.sq_GetLevelData(SKILL_FROZENLAND, 1, obj.sq_GetSkillLevel(SKILL_FROZENLAND));

					
					local skillLevel = obj.sq_GetSkillLevel(SKILL_FROZENLAND);
					local frozenRate = obj.sq_GetLevelData(SKILL_FROZENLAND, 2, skillLevel); 
					local frozenLevel = obj.sq_GetLevelData(SKILL_FROZENLAND, 3, skillLevel); 
					local frozenTime = obj.sq_GetLevelData(SKILL_FROZENLAND, 4, skillLevel); 
					
					sq_BinaryWriteDword(multiHitTerm); 
					sq_BinaryWriteDword(multiHitAttackRate); 
					sq_BinaryWriteDword(expAttackRate); 
					sq_BinaryWriteDword(frozenRate); 
					sq_BinaryWriteDword(frozenLevel); 
					sq_BinaryWriteDword(frozenTime); 
					
					local spinAddTime = obj.sq_GetIntData(SKILL_FROZENLAND, 4); 
					sq_BinaryWriteDword(spinAddTime); 
					
					
					sq_BinaryWriteDword( obj.sq_GetIntData(SKILL_FROZENLAND, 5) ); 
					sq_BinaryWriteDword( obj.sq_GetIntData(SKILL_FROZENLAND, 7) );
					obj.sq_SendCreatePassiveObjectPacket(24247, 0, 10, -1, 0); 
				}

				obj.getVar().set_vector(0, 1);
			}
		}
	}
	else if(substate == SUB_STATE_FROZENLAND_1) {
		
		local magicCirclePassiveObj = obj.sq_GetPassiveObject(24247); // po_ATFrozenLandMagicCircle
		local stateChange = true;
		
		if(magicCirclePassiveObj)
		{			
			local magicCirclePassiveState = magicCirclePassiveObj.getState();
			
			if(magicCirclePassiveState == S_PO_FROZENLAND_MC_3)
			{
				stateChange = true;
			}
			else
			{
				stateChange = false;
			}
		}
		
		if(stateChange)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(SUB_STATE_FROZENLAND_2); // substate????
			obj.sq_AddSetStatePacket(STATE_FROZENLAND, STATE_PRIORITY_IGNORE_FORCE, true);
		}
		
	}
	else if(substate == SUB_STATE_FROZENLAND_2) {
		// SUB_STATE_FROZENLAND_2 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_3) {
		// SUB_STATE_FROZENLAND_3 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_4) {
		// SUB_STATE_FROZENLAND_4 ????????? ???
	}
	

}

function onEndCurrentAni_FrozenLand(obj)
{

	if(!obj) return;

	if(!obj.isMyControlObject()) {
		return;
	}
	
	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_FROZENLAND_CASTING)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(SUB_STATE_FROZENLAND_0); // substate????
		obj.sq_AddSetStatePacket(STATE_FROZENLAND, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == SUB_STATE_FROZENLAND_0) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(SUB_STATE_FROZENLAND_1); // substate????
		obj.sq_AddSetStatePacket(STATE_FROZENLAND, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == SUB_STATE_FROZENLAND_1) {
	}
	else if(substate == SUB_STATE_FROZENLAND_2) {
	}
	else if(substate == SUB_STATE_FROZENLAND_3) {
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	else if(substate == SUB_STATE_FROZENLAND_4) {
		// SUB_STATE_FROZENLAND_4 ????????? ???
	}
	

}

function onKeyFrameFlag_FrozenLand(obj, flagIndex)
{

	if(!obj) return false;

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_FROZENLAND_0) {
		// SUB_STATE_FROZENLAND_0 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_1) {
		// SUB_STATE_FROZENLAND_1 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_2) {
		// SUB_STATE_FROZENLAND_2 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_3) {
		// SUB_STATE_FROZENLAND_3 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_4) {
		// SUB_STATE_FROZENLAND_4 ????????? ???
	}
	

	return false;

}

function onEndState_FrozenLand(obj, new_state)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_FROZENLAND_0) {
		// SUB_STATE_FROZENLAND_0 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_1) {
		// SUB_STATE_FROZENLAND_1 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_2) {
		// SUB_STATE_FROZENLAND_2 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_3) {
		// SUB_STATE_FROZENLAND_3 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_4) {
		// SUB_STATE_FROZENLAND_4 ????????? ???
	}
	
	// ??????? ???? ??? ?????????? ????? ?????? ????
	sq_EndDrawCastGauge(obj);
	
	

}

function onAfterSetState_FrozenLand(obj, state, datas, isResetTimer)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

	if(substate == SUB_STATE_FROZENLAND_0) {
		// SUB_STATE_FROZENLAND_0 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_1) {
		// SUB_STATE_FROZENLAND_1 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_2) {
		// SUB_STATE_FROZENLAND_2 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_3) {
		// SUB_STATE_FROZENLAND_3 ????????? ???
	}
	else if(substate == SUB_STATE_FROZENLAND_4) {
		// SUB_STATE_FROZENLAND_4 ????????? ???
	}
	

}

function findFrozenLandPoleAttration(obj)
{
	obj.getVar("dama").clear_obj_vector();
	local objectManager = obj.getObjectManager();


    local mage = obj.getTopCharacter();
    mage = sq_ObjectToSQRCharacter(mage);	

    local chrX = mage.getXPos();

	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) )
		{
            
			local activeObj = sq_GetCNRDObjectToActiveObject(object);

            if (!CNSquirrelAppendage.sq_IsAppendAppendage(activeObj, "character/atmage/frozenland/ap_frozenland.nut") )
            {
                local objX = obj.getXPos();
                local objY = obj.getYPos();

                local dd = 300;

                local distance = sq_Abs( activeObj.getXPos() - objX );
                distance = distance * distance;
                distance += sq_Abs( activeObj.getYPos() - objY ) * sq_Abs( activeObj.getYPos() - objY );

                if ( !sq_IsFixture(activeObj) && distance <= dd * dd )
                {

                    if (activeObj.getXPos() > chrX && objX > chrX)
                    {
                        obj.getVar("dama").push_obj_vector(activeObj);
                        local appendage = CNSquirrelAppendage.sq_AppendAppendage(activeObj, obj, SKILL_FROZENLAND, true,
                        "character/atmage/frozenland/ap_frozenland.nut", false);
                    }else if (activeObj.getXPos() < chrX && objX < chrX)
                    {
                        obj.getVar("dama").push_obj_vector(activeObj);
                        local appendage = CNSquirrelAppendage.sq_AppendAppendage(activeObj, obj, SKILL_FROZENLAND, true,
                        "character/atmage/frozenland/ap_frozenland.nut", false);
                    }
                }
            }
		}
	}

}


function setFrozenLandPoleAttractionEffect(obj)
{


            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();


            for(local i=0;i<objectsSize;++i)
            {
                
                local damager = var.get_obj_vector(i);
                if (true)
                {
                    local objX = obj.getXPos();
                    local objY = obj.getYPos();
                    local damaX = damager.getXPos();
                    local damaY = damager.getYPos();
                    local damaZ = damager.getZPos();
                    local x_move = 2;
                    local y_move = 1;
                    if (objX < damaX) x_move = - x_move;
                    if (objY < damaY) y_move = - y_move;

                    local lastX = damaX + x_move;
                    local lastY = damaY + y_move;

                    if (sq_Abs(damaX - objX) < 5 * x_move ) lastX = obj.getXPos();
                    if (sq_Abs(damaY - objY) < 5 * y_move ) lastY = obj.getYPos();
                    damager.setCurrentPos(lastX,lastY,damaZ);
                }

            }

}