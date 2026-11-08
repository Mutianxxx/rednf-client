function checkExecutableSkill_wingout(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_WINGOUT);
	if (isUseSkill) 
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0); 
		obj.sq_AddSetStatePacket(STATE_WINGOUT, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_wingout(obj)
{
	if(!obj)
		return false;
	if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_WINGOUT, 0)))
		return false;

	return true;
}


function setCharacterFristAnimation_Marauder(obj)
{
    local level = sq_GetSkillLevel(obj, SKILL_NEWBLOODDOGHOLD );		
    if (level > 0)
    {
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/als_ani/atmarauder/floor/floor_black.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/als_ani/atmarauder/end/marauder_finish_front.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/als_ani/atmarauder/end/marauder_finish_back.ani");
        createFristAnimationPooledObject(obj,
        "passiveobject/zrr_skill/atmage/animation/atphantombale/02_attack00/hit/atphantombale_attack00_hit_base.ani");

        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/newbloodwingout/marauder_end_body.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/newbloodwingout/marauder_startland_body.ani");
        createFristAnimationPooledObject(obj,
        "character/mage/atanimation/zrr/newbloodwingout/marauder_startspin_body.ani");
    }
}






function onSetState_Marauder(obj, state, datas, isResetTimer)
{
	if(!obj)
		return;
	obj.sq_StopMove();
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);

	if (state == 0)
	{
		setBloodValue(obj,-obj.sq_GetIntData(SKILL_WINGOUT, 0) );
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOODWINGOUT_READY);
		obj.getVar("objectTime").clear_vector();
		

	}else if (state == 1)
	{

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOODWINGOUT_SPIN);

	}else if (state == 2)
	{
		sq_setCurrentAxisPos(obj, 2, 0 );
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOODWINGOUT_LAND);
		

	}else if (state == 3)
	{
		createMarauderLandFloorEffect(obj,0,1,0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_NEWBLOODWINGOUT_END);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWBLOODWINGOUT_DOWN);
		obj.getVar("var").clear_vector();
		obj.getVar("var").push_vector(0);
		obj.getVar("var").push_vector(0);
		obj.getVar("var").push_vector(0);


		local damage = obj.sq_GetBonusRateWithPassive(SKILL_WINGOUT , STATE_WINGOUT, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

		local ani = obj.sq_GetCurrentAni();
		if(ani)
		{
			ani.setFrameDelay(3, obj.sq_GetIntData(SKILL_WINGOUT, 1) ,true);
			ani.setFrameDelay(6, obj.sq_GetIntData(SKILL_WINGOUT, 2) ,true);
		}
	}

}



function onProc_Marauder(obj)
{
	if(!obj)
		return;
	local state = obj.getSkillSubState();
	
	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	local currentT = sq_GetCurrentTime(pAni);
	
	if (state == 0)
	{
		if (frmIndex >= 1 && obj.getVar("objectTime").size_vector() == 0)
		{
			
			obj.getVar("objectTime").clear_vector();
			obj.getVar("objectTime").push_vector( sq_getCurrentCharacterAppendTime(obj) );
			
			
			local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
			local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

			local upPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL);
			local downPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL);
			
			local offsetX = obj.sq_GetIntData(SKILL_WINGOUT, 3);
			local offsetY = obj.sq_GetIntData(SKILL_WINGOUT, 4);
			
			if ( (sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && leftPress) || 
				(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && rightPress) )
			{
				offsetX = obj.sq_GetIntData(SKILL_WINGOUT, 5);
			}
			
			if ( (sq_GetDirection(obj) == ENUM_DIRECTION_RIGHT && rightPress) || 
				(sq_GetDirection(obj) == ENUM_DIRECTION_LEFT && leftPress) )
			{
				offsetX = obj.sq_GetIntData(SKILL_WINGOUT, 6);
			}
			
			if (upPress)
			{
				offsetY = obj.sq_GetIntData(SKILL_WINGOUT, 7);
			}else if (downPress)
			{
				offsetY = obj.sq_GetIntData(SKILL_WINGOUT, 8);
			}
			
			
			obj.getVar("jumpBasicVar").clear_vector();
			obj.getVar("jumpBasicVar").push_vector(obj.getXPos() );
			obj.getVar("jumpBasicVar").push_vector(obj.getYPos() );
			obj.getVar("jumpBasicVar").push_vector(offsetX);
			obj.getVar("jumpBasicVar").push_vector(offsetY);
			obj.getVar("jumpBasicVar").push_vector( obj.sq_GetIntData(SKILL_WINGOUT, 9) );
			
			
		}
		
		if (sq_IsEnd(pAni) == true)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1); 
			obj.sq_AddSetStatePacket(STATE_WINGOUT, STATE_PRIORITY_USER, true);
		}
	
	}else if (state == 1)
	{

	}else if (state == 2)
	{
	
		if (currentT > obj.sq_GetIntData(SKILL_WINGOUT, 10) )
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(3); 
			obj.sq_AddSetStatePacket(STATE_WINGOUT, STATE_PRIORITY_USER, true);
		}
	
	}else if (state == 3)
	{
	
		if (sq_IsEnd(pAni) == true)
		{ 
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);
		}else 
		{
			if (frmIndex >= 0 && obj.getVar("var").get_vector(0) == 0)
			{
			
				obj.getVar("var").set_vector(0,1);
                sq_flashScreen(obj,0,80,300,204, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
                obj.sq_SetShake(obj, 3 , 300);
			
			}else if (frmIndex >= 7 && obj.getVar("var").get_vector(1) == 0)
			{
			
				obj.getVar("var").set_vector(1,1);
				createMarauderFinishFrontEffect(obj,0,1,0);
				createMarauderFinishBackEffect(obj,0,-1,0);
			
			}else if (frmIndex >= 9 && obj.getVar("var").get_vector(2) == 0)
			{

				obj.getVar("var").set_vector(2,1);
				sq_flashScreen(obj,0,120,500,255, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
                obj.sq_SetShake(obj, 5 , 300);
				
				obj.sq_SetCurrentAttackInfo(ATTACKINFO_NEWBLOODWINGOUT_FINISH);
				local damage = obj.sq_GetBonusRateWithPassive(SKILL_WINGOUT , STATE_WINGOUT, 1, 1.0);
				obj.sq_SetCurrentAttackBonusRate(damage);				
				obj.resetHitObjectList();

				//createMarauderFinishFrontEffect(obj,0,1,0);
				//createMarauderFinishBackEffect(obj,0,-1,0);
			
			}
		}
	}
	
	if (obj.getVar("objectTime").size_vector() > 0)
	{
		local maxJumpT = obj.sq_GetIntData(SKILL_WINGOUT, 11);
		local jumpT = sq_getCurrentCharacterAppendTime(obj) - obj.getVar("objectTime").get_vector(0);
		
		if (jumpT < maxJumpT)
		{
		
			local startX = obj.getVar("jumpBasicVar").get_vector(0);
			local startY = obj.getVar("jumpBasicVar").get_vector(1);
			local moveDX = obj.getVar("jumpBasicVar").get_vector(2);
			local moveDY = obj.getVar("jumpBasicVar").get_vector(3);
			local moveDZ = obj.getVar("jumpBasicVar").get_vector(4);
		
			local offsetX = sq_GetUniformVelocity(0, moveDX, jumpT,maxJumpT);
			local offsetY = sq_GetUniformVelocity(0, moveDY, jumpT,maxJumpT);
			
            local dstX = sq_GetDistancePos(startX, obj.getDirection(), offsetX );
            local dstY = startY + offsetY;
			local dstZ = getQuadraticFunction(obj,jumpT,moveDZ,maxJumpT).tointeger();
			
			sq_setCurrentPosInMoveAble(obj,dstX,dstY,dstZ,false);

		}else
		{
		
			if (state == 0 || state == 1)
			{
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(2); 
				obj.sq_AddSetStatePacket(STATE_WINGOUT, STATE_PRIORITY_USER, true);
			}
		}
	
	}
	
	
}


function onAttack_Marauder(obj, damager, boundingBox, isStuck)
{
	if(!obj)
		return;
	local state = obj.getSkillSubState();
	if (state == 3)
	{

		local pAni = obj.sq_GetCurrentAni();
		local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
		local currentT = sq_GetCurrentTime(pAni);
		if (frmIndex < 9)
		{
			if((sq_IsGrabable(obj,damager) && sq_IsHoldable(obj,damager) && !sq_IsFixture(damager))) 
			{
				CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_WINGOUT, false, "character/atmage/marauder/ap_marauder.nut", true);
			}
		}
		else
		{
		
			CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/marauder/ap_marauder.nut");
		
		}

	}
}


function createMarauderLandFloorEffect(obj,x,y,z)
{
	if(!obj)
		return;
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atmarauder/floor/floor_black.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function createMarauderFinishBackEffect(obj,x,y,z)
{
	if(!obj)
		return;
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atmarauder/end/marauder_finish_back.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	//pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function createMarauderFinishFrontEffect(obj,x,y,z)
{
	if(!obj)
		return;
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atmarauder/end/marauder_finish_front.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	//pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function getQuadraticFunction(obj,x,b,c)
{
  local a = (-b.tofloat() * 4) /( c.tofloat() * c.tofloat());
  return a.tofloat()*(x.tofloat() - c.tofloat() / 2)*(x.tofloat() - c.tofloat() / 2) + b.tofloat();
}
