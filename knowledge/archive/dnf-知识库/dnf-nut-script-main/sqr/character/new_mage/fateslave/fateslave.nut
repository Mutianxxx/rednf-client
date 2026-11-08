//boom shake 3 200

function checkExecutableSkill_fateslave(obj)  
{
	if (!obj) return false;
	local bobyNumber = obj.sq_GetIntData(SKILL_FATESLAVE, 3);
	if(bobyNumber < 1){
		bobyNumber = 1;
	}
	if (getBobyNumber(obj) >= bobyNumber)
	{
		local isUseSkill = obj.sq_IsUseSkill(SKILL_FATESLAVE);
		if (isUseSkill) 
		{
			obj.sq_AddSetStatePacket(STATE_FATESLAVE, STATE_PRIORITY_USER, true);
			return true;
		}
	}
	else
	{
		playNoDollSound(obj);
	}
	return false;
}


function setCharacterFristAnimation_FateSlave(obj)
{
	local level = sq_GetSkillLevel(obj, SKILL_FATESLAVE );		
	if (level > 0)
	{
		createFristAnimationPooledObject(obj,"character/mage/animation/ani_als/destinypuppet/destinypuppetstartfront_03.ani");
		createFristAnimationPooledObject(obj,"character/mage/animation/ani_als/destinypuppet/startfloor_00.ani");
		createFristAnimationPooledObject(obj,"passiveobject/zrr_skill/newmage/animation/destinypuppet/startfront_01.ani");
		createFristAnimationPooledObject(obj,"passiveobject/zrr_skill/newmage/animation/destinypuppet/explosion_11.ani");
		createFristAnimationPooledObject(obj,"passiveobject/zrr_skill/newmage/animation/destinypuppet/loop_00.ani");
		createFristAnimationPooledObject(obj,"passiveobject/zrr_skill/newmage/animation/destinypuppet/loopend_12.ani");
		createFristAnimationPooledObject(obj,"passiveobject/zrr_skill/newmage/animation/destinypuppet/run_zombie.ani");
		createFristAnimationPooledObject(obj,"passiveobject/zrr_skill/newmage/animation/destinypuppet/startfront_04.ani");
		createFristAnimationPooledObject(obj,"passiveobject/zrr_skill/newmage/animation/destinypuppet/success_zombie.ani");
	}
}



function createFateSlaveFrontEffect(obj)
{
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/destinypuppet/destinypuppetstartfront_03.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}
function createFateSlaveFloorEffect(obj)
{
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/destinypuppet/startfloor_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() - 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFateSlaveBobyStartEffect(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/newmage/animation/destinypuppet/startfront_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function onKeyFrameFlag_FATESLAVE(obj,flagIndex)
{
	if (flagIndex == 1 &&  obj.getVar("flag").get_vector(0) == 0 )
	{
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(1);
		launchFateSlaveDoll(obj);
	}
}

function checkCommandEnable_fateslave(obj)
{
	return (isOpenBobyBox(obj) );
}
//SET FLAG 42 1 60

function onSetState_FATESLAVE(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
	if (!isDollState(obj))
	{
		obj.sq_SetCurrentAnimation(CUSTOM_FATESLAVE_BOBY);
	}
	else
	{
		obj.sq_PlaySound("WZ_DESTINYPUPPET_MN");
		local ani = obj.getVar().GetAnimationMap("fateSlave", "character/mage/animation/zrr_ani/mad_destinypuppetstart.ani"); 
		obj.setCurrentAnimation(ani);
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED , SPEED_TYPE_CAST_SPEED , SPEED_VALUE_DEFAULT , SPEED_VALUE_DEFAULT , 1.0 , 1.0);
	obj.getVar("flag").clear_vector();
	obj.getVar("flag").push_vector(0);
//	launchFateSlaveDoll(obj);
	createFateSlaveFrontEffect(obj);
	createFateSlaveFloorEffect(obj);

//	setBobyNumber(obj,getBobyNumber(obj) - 1 );
}

function launchFateSlaveDoll(obj)
{
	local objectManager = obj.getObjectManager();
	obj.getVar("count").clear_vector();
	obj.getVar("count").push_vector(0);
	local bobyNumber = obj.sq_GetIntData(SKILL_FATESLAVE, 3);
	if(bobyNumber < 1){
		bobyNumber = 1;
	}
	setBobyNumber(obj,getBobyNumber(obj) - bobyNumber);//obj.sq_GetIntData(SKILL_FATESLAVE, 0) );
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && object.isObjectType(OBJECTTYPE_ACTIVE) )
		{
			local count = obj.getVar("count").get_vector(0);
			if (obj.isEnemy(object) && object.getZPos() <= 0 && count < 5 && isDistanceOfTarget(obj,object,obj.sq_GetIntData(SKILL_FATESLAVE, 1) ) )
			{
				obj.getVar("count").set_vector(0,1 + count);
				local id = sq_GetObjectId(object);
				createFateSlaveBobyStartEffect(obj);
				local attackBonusRate = obj.sq_GetPowerWithPassive(SKILL_FATESLAVE, STATE_FATESLAVE, 1,-1, 1.0);
				obj.sq_StartWrite();
				obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
				obj.sq_WriteDword(15);
				obj.sq_WriteDword(id);
				obj.sq_WriteDword( obj.sq_GetIntData(SKILL_FATESLAVE, 2) );
				obj.sq_SendCreatePassiveObjectPacket(24364, 0, 0, 1, 0);
			}
			else
			{
				if (!obj.isEnemy(object))
				{

//					local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, obj, SKILL_FATESLAVE, false, "character/mage/fateslave/ap_fateslave_friend.nut", true);


				}
			}
		}
	}
}

function onEndCurrentAni_FATESLAVE(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}
