
//2020-10-26

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


        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/nnofferingatkdwave.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_eff_00.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_eff_01.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_eff_02.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_eff_03.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_eff_04.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_eff_05.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_eff_06.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_eye.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_front_eff_00.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_front_eff_01.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_front_eff_02.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_front_eff_03.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_front_eff_04.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatka_front_eff_05.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkb_eff.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkb_eye.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkceff_eff_00.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkceff_eff_01.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkceff_eff_02.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkceff_eff_03.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkc_eff.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkc_eye.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkd_effsmoke_00.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkd_effsmoke_01.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkd_effsmoke_02.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkd_effsmoke_03.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkd_eff_00.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkd_eff_01.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkd_eff_02.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkd_eff_03.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/offeringatkd_eye.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/surroundinggrabcannonattack.ani");
        createFristAnimationPooledObject(obj,"character/mage/atanimation/als_ani/atoffering/surroundingthrowattack.ani");



	}
}




function onSetState_BLOODHIT(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	obj.sq_StopMove();
	
	
	local subState = obj.sq_GetVectorData(datas, 0);	
	obj.sq_SetSkillSubState(obj, subState);
	
	if (subState == 0)
	{

		//setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOODHIT, 1));
		setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOODHIT, 1));

		obj.getVar("dama").clear_obj_vector();
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);
		obj.getVar("flag").push_vector(0);

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODHIT_NEWHOLD);
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODHIT_NEWGRAB);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODHIT , STATE_BLOODHIT, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

		local currentAni = sq_GetCurrentAnimation(obj);
		currentAni.setSpeedRate( 150.0 );

		obj.getVar("isHoldFlag").clear_vector();
		obj.getVar("isHoldFlag").push_vector(0);

	}
	else if (subState == 1)
	{

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODHIT_NEWDROP);

		obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODHIT_THROW);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODHIT , STATE_BLOODHIT, 1, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

		local currentAni = sq_GetCurrentAnimation(obj);
		currentAni.setSpeedRate( 200.0 );

	}else if (subState == 2)
	{
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODHIT_MISS);

		local pAni = obj.sq_GetCurrentAni();
		local backlight_dodge = obj.sq_GetAutoLayerWorkAnimation(pAni, "Eff");
		if (backlight_dodge)
			backlight_dodge.setImageRateFromOriginal(0.001, 0.001);


		obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODHIT_BREAKHIT);

		local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOODHIT , STATE_BLOODHIT, 2, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				



	}else if (subState == 3)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODHIT_MISS);

		local pAni = obj.sq_GetCurrentAni();
		local backlight_dodge = obj.sq_GetAutoLayerWorkAnimation(pAni, "Eff");
		if (backlight_dodge)
			backlight_dodge.setImageRateFromOriginal(1.0, 1.0);

	}else if (subState == 4)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODHIT_NEWLOOP);
	}

}



function createOfferingBreakEffectSpear(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atoffering/offeringatkceff_eff_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function onProc_BLOODHIT(obj)
{

	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
	local currentT = sq_GetCurrentTime(pAni);
	local state = obj.sq_GetSkillSubState(obj);

	if (state == 0)
	{
		if (frmIndex >= 3)
		{
			if (obj.getVar("flag").get_vector(0) == 0)
			{
				obj.getVar("flag").set_vector(0,1);
				obj.sq_SetShake(obj, 1, 70);
			}else
			{
				setOfferingMonsterPosWithRorate(obj,59,-1,101,-10);
			}
		}
	}else if (state == 1)
	{
		if (frmIndex == 0)
		{
			setOfferingMonsterPosWithRorateNoHeight(obj,36,-1,138,-75);
		}else if (frmIndex == 1)
		{
			setOfferingMonsterPosWithRorateNoHeight(obj,21,-1,148,-90);
		}else if (frmIndex == 2)
		{
			setOfferingMonsterPosWithRorateNoHeight(obj,-3,-1,132,-105);
		}else if (frmIndex == 3)
		{
			setOfferingMonsterPosWithRorateNoHeight(obj,-27,-1,112,-130);
		}else if (frmIndex == 4)
		{
			if (obj.getVar("flag").get_vector(1) == 0)
			{
				obj.getVar("flag").set_vector(1,1);
				sq_flashScreen(obj,0,20,240,204, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
				obj.sq_SetShake(obj, 5, 240);
				setOfferingMonsterPosWithRorateNoHeight(obj,127,-1,23,20);
				//createOfferingThrowFloorEffect(obj,0,-1,0);
			}
		}else if (frmIndex >= 5)
		{
			if (obj.getVar("flag").get_vector(2) == 0)
			{
				obj.getVar("flag").set_vector(2,1);
				ReleaseOfferingMonsterHoldEffect(obj);
			}
			ReleaseOfferingMonsterPosWithRorate(obj);
		}
	
	}else if (state == 2)
	{
		if (frmIndex >= 0 && obj.getVar("flag").get_vector(0) == 0)
		{
			obj.getVar("flag").set_vector(0,1);
			sq_flashScreen(obj,0,40,180,153, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
			obj.sq_SetShake(obj, 5, 180);
			createOfferingBreakEffectSpear(obj,96,1,89);
			setOfferingBreakMonsterHoldEffect(obj);
			
		}
	
	}else if (state == 3)
	{
	
	
	}else if (state == 4)
	{
	
		obj.setSkillCommandEnable(SKILL_BLOODHIT, true);

		local iEnterSkill = obj.sq_IsEnterSkill(SKILL_BLOODHIT);
	
		if (iEnterSkill != -1 || 
			currentT > obj.sq_GetIntData(SKILL_BLOODHIT, 0) || 
			sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL) )
		{
			if (currentT > obj.sq_GetIntData(SKILL_BLOODHIT, 2) )
			{
				obj.sq_IntVectClear();
				obj.sq_IntVectPush(1);	
				obj.sq_AddSetStatePacket(STATE_BLOODHIT, STATE_PRIORITY_USER, true);	
			}
		}else
		{
			if (frmIndex == 1)
			{
				setOfferingMonsterPosWithRorate(obj,60,-1,101,-10);
			}else
			{
				setOfferingMonsterPosWithRorate(obj,59,-1,101,-10);
			}
		}
	
	}
}


function createOfferingThrowFloorEffect(obj,x,y,z)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atoffering/nnofferingatkdwave.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), x);
	pooledObj.setCurrentPos(posX ,obj.getYPos() + y,obj.getZPos() + z );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function setOfferingMonsterPosWithRorate(obj,x,y,z,angle)
{

	local var = obj.getVar("dama");  		
	local objectsSize = var.get_obj_vector_size();
	if (objectsSize > 0)
	{

		for(local i=0;i<objectsSize;++i)
		{
			local damager = var.get_obj_vector(i);
			
			
			if((damager && sq_IsGrabable(obj,damager) 
				&& sq_IsHoldable(obj,damager) 
				&& !sq_IsFixture(damager))) 
			{
			
			
				local disX = x;
				local disY = y;
				local disZ = z;
				local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);

				local v = obj.getZPos() + disZ - damager.getObjectHeight()/2 ;

				local posX = damager.sq_findNearLinearMovableXPos(posX, 
				obj.getYPos(),damager.getXPos(), damager.getYPos(), 10);

				if (v < 0)
				{
					damager.setCurrentPos(posX,obj.getYPos() + disY,damager.getZPos() );
				}else{
					damager.setCurrentPos(posX,obj.getYPos() + disY,v );
				}

				damager.setCurrentDirection(obj.getDirection());
				sq_SetCustomRotate(damager,sq_ToRadian(-angle.tofloat() ) );	
			}
		}
	}


}



function setOfferingMonsterPosWithRorateNoHeight(obj,x,y,z,angle)
{

	local var = obj.getVar("dama");  		
	local objectsSize = var.get_obj_vector_size();
	if (objectsSize > 0)
	{

		for(local i=0;i<objectsSize;++i)
		{
			local damager = var.get_obj_vector(i);

			if((damager && sq_IsGrabable(obj,damager) 
				&& sq_IsHoldable(obj,damager) 
				&& !sq_IsFixture(damager))) 
			{

				local disX = x;
				local disY = y;
				local disZ = z;
				local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);

				local v = obj.getZPos() + disZ;

				local posX = damager.sq_findNearLinearMovableXPos(posX, 
				obj.getYPos(),damager.getXPos(), damager.getYPos(), 10);

				if (v < 0)
				{
					damager.setCurrentPos(posX,obj.getYPos() + disY,damager.getZPos() );
				}else{
					damager.setCurrentPos(posX,obj.getYPos() + disY,v );
				}
				damager.setCurrentDirection(obj.getDirection());
				sq_SetCustomRotate(damager,sq_ToRadian(-angle.tofloat() ) );	
			}
		}
	}


}



function ReleaseOfferingMonsterHoldEffect(obj)
{

	local var = obj.getVar("dama");  		
	local objectsSize = var.get_obj_vector_size();
	if (objectsSize > 0)
	{

		for(local i=0;i<objectsSize;++i)
		{
			local damager = var.get_obj_vector(i);
			if (damager)
				CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/bloodhit/ap_bloodhit.nut");		
		}
	}


}




function setOfferingBreakMonsterHoldEffect(obj)
{

	local var = obj.getVar("dama");  		
	local objectsSize = var.get_obj_vector_size();
	if (objectsSize > 0)
	{

		for(local i=0;i<objectsSize;++i)
		{
			local damager = var.get_obj_vector(i);
			if (damager)
			{
				sq_SendHitObjectPacket(obj,damager,0,0,0);
				CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/atmage/bloodhit/ap_bloodhit.nut");
				local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODHIT, false, 
				"character/atmage/bloodhit/ap_bloodhit2.nut", true);
				if (masterAppendage)
					masterAppendage.sq_SetValidTime(1000);
			}
			
		}
	}


}


function ReleaseOfferingMonsterPosWithRorate(obj)
{

	local var = obj.getVar("dama");  		
	local objectsSize = var.get_obj_vector_size();
	if (objectsSize > 0)
	{

		for(local i=0;i<objectsSize;++i)
		{
			local damager = var.get_obj_vector(i);
			if (damager)
				sq_SetCustomRotate(damager,sq_ToRadian(0.0 ) );	
		}
	}


}





function onAttack_BLOODHIT(obj, damager, boundingBox, isStuck)
{

	local state = obj.sq_GetSkillSubState(obj);
	if (state == 0)
	{
		if (damager.isObjectType(OBJECTTYPE_ACTIVE))
		{
			if (damager.getState() == STATE_HOLD)
			{
				obj.getVar("isHoldFlag").clear_vector();
				obj.getVar("isHoldFlag").push_vector(1);
			}
			obj.getVar("dama").push_obj_vector(damager);	
			local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODHIT, false, 
				"character/atmage/bloodhit/ap_bloodhit.nut", true);	
			if(sq_IsHoldable(obj,damager) && sq_IsGrabable(obj,damager) && !sq_IsFixture(damager))
			{
				if(masterAppendage)
				{
					sq_HoldAndDelayDie(damager, obj, true, false, false, 100, 100, ENUM_DIRECTION_NEUTRAL, masterAppendage);
					local appendageInfo = masterAppendage.getAppendageInfo();
					appendageInfo.setValidTime(obj.sq_GetIntData(SKILL_BLOODHIT, 0));
				}
			}

		}
	}else if (state == 1)
	{
	
	}else if (state == 2)
	{
	
	}else if (state == 3)
	{
	
	}

}


function onEndState_BLOODHIT(obj,new_state)
{
	if (new_state != STATE_BLOODHIT)
	{
		ReleaseOfferingMonsterHoldEffect(obj);
		ReleaseOfferingMonsterPosWithRorate(obj);
	}
}

function onEndCurrentAni_BLOODHIT(obj)
{

	local state = obj.sq_GetSkillSubState(obj);
	if (state == 0)
	{
		if (obj.getVar("dama").get_obj_vector_size() == 0)
		{

			obj.sq_IntVectClear();
			obj.sq_IntVectPush(3);	
			obj.sq_AddSetStatePacket(STATE_BLOODHIT, STATE_PRIORITY_USER, true);	
			return false;

		}else if (obj.getVar("isHoldFlag").get_vector(0) == 1)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(2);	
			obj.sq_AddSetStatePacket(STATE_BLOODHIT, STATE_PRIORITY_USER, true);	
			return ;
		
		}else
		{
		
			local var = obj.getVar("dama");  		
			local objectsSize = var.get_obj_vector_size();
			if (objectsSize > 0)
			{

				for(local i=0;i<objectsSize;++i)
				{
					local damager = var.get_obj_vector(i);

					if(!(sq_IsGrabable(obj,damager) 
						&& sq_IsHoldable(obj,damager) 
						&& !sq_IsFixture(damager))) 
					{
						obj.sq_IntVectClear();
						obj.sq_IntVectPush(2);	
						obj.sq_AddSetStatePacket(STATE_BLOODHIT, STATE_PRIORITY_USER, true);	
						return ;
						
					}
				}
			}
		
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(4);	
			obj.sq_AddSetStatePacket(STATE_BLOODHIT, STATE_PRIORITY_USER, true);	
			return ;
		}
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	else if (state == 1)
	{
	
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	else if (state == 2)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	else if (state == 3)
	{
	
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	else if (state == 4)
	{
	
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}

}




function onKeyFrameFlag_BLOODHIT(obj, flagIndex)
{
}













