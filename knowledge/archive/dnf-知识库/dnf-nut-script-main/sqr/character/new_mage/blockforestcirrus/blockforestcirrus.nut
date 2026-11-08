function checkExecutableSkill_blockforestcirrus(obj)  
{
	if (getBobyNumber(obj) >= 1)
	{
		local isUseSkill = obj.sq_IsUseSkill(SKILL_BLOCKFORESTCIRRUS);
		if (isUseSkill) 
		{
			obj.sq_AddSetStatePacket(STATE_BLOCKFORESTCIRRUS, STATE_PRIORITY_USER, true);
			return true;
		}
	}
	else
	{
		playNoDollSound(obj);
	}
	return false;
}

function createentranceBlockForestCirrus(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/newmage/animation/blackthorntree/blackthorntree_house_entrance_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 12,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createentranceLightBlockForestCirrus(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/newmage/animation/blackthorntree/blackthorntree_house_entrancelight_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 15,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function checkCommandEnable_blockforestcirrus(obj)
{

	return (isOpenBobyBox(obj) );
}



function onKeyFrameFlag_BLOCKFORESTCIRRUS(obj,flagIndex)
{
	if (flagIndex == 1 &&  obj.getVar("flag").get_vector(0) == 0 )
	{
		obj.getVar("flag").set_vector(0,1);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_BLOCKFORESTCIRRUS , STATE_BLOCKFORESTCIRRUS, 0, 1.0);
		local level = sq_GetSkillLevel(obj, SKILL_BLOCKFORESTCIRRUS);		
		local count = sq_GetLevelData(obj, SKILL_BLOCKFORESTCIRRUS, 1, level);

		sq_BinaryStartWrite();
		sq_BinaryWriteDword(4);
		sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOCKFORESTCIRRUS, 0));
		sq_BinaryWriteDword(damage);
		sq_BinaryWriteDword(count);
		sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOCKFORESTCIRRUS, 1));
		sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_BLOCKFORESTCIRRUS, 2));
		obj.sq_SendCreatePassiveObjectPacket(24346, 0, 78, 1, 56);
		setBobyNumber(obj,getBobyNumber(obj) - 1);
	}
}

function onSetState_BLOCKFORESTCIRRUS(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
	
	if (!isDollState(obj))
	{
		obj.sq_SetCurrentAnimation( CUSTOM_ANI_BLOCKFORESTCIRRUS_BOBY );
	}else{
		local ani = obj.getVar().GetAnimationMap("blockforest", "character/mage/animation/zrr_ani/mad_destinypuppetstart.ani"); 
		obj.setCurrentAnimation(ani);
	}
    
	obj.getVar("flag").clear_vector();
	obj.getVar("flag").push_vector(0);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onEndCurrentAni_BLOCKFORESTCIRRUS(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}