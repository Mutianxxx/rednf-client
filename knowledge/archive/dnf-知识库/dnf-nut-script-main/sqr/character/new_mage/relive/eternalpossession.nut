//set flag 1 create effect A
//set flag 2 create effect B CreateGroundLight
//set flag 3 shake 8 120
function checkExecutableSkill_eternalpossession(obj)  
{
	if (!obj) return false;
    
	if (getBobyNumber(obj) > 0)
	{
		local isUseSkill = obj.sq_IsUseSkill(SKILL_RELIVE);
		if (isUseSkill) 
		{
			obj.getVar("state").clear_vector();
			obj.getVar("state").push_vector(0);
			obj.sq_AddSetStatePacket(STATE_RELIVE, STATE_PRIORITY_USER, true);
			return true;
		}
	}
	else{
		playNoDollSound(obj);
	}
	return false;
}

function checkCommandEnable_eternalpossession(obj)
{
	return true; 
}

function onKeyFrameFlag_ETERNALPOSSESSION(obj,flagIndex)
{

    if ( flagIndex == 1 )
    {
    }else if ( flagIndex == 2 )
    {
    }else if ( flagIndex == 3 )
    {

        return true;
    }
}


/*function create(obj)
{

	local ani = sq_CreateAnimation("","character/swordman/animation/ani_als/ultimatecrossslash/effect/castback_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,obj.getZPos() + obj.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_moveWithParent(obj, pooledObj);
	sq_AddObject(obj,pooledObj,2,false);	

}*/
function createDeadHeadReLiveStarA_01(obj)
{

	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/eternalpossession/starta_01.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
//	pooledObj = sq_SetEnumDrawLayer(pooledObj, ENUM_DRAWLAYER_BOTTOM);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_moveWithParent(obj, pooledObj);
	sq_AddObject(obj,pooledObj,2,false);	

}

function getNearestDeadCharacterWithDistance(obj,var)
{

	local objectManager = obj.getObjectManager();
	local dist = var  * var;
	local targ = null;
	if (objectManager)
	{
		for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
		{
			local object = objectManager.getCollisionObject(i);
			if (object && !obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_CHARACTER) )
			{
				local activeObj = sq_GetCNRDObjectToActiveObject(object);
                
				if ( !isSameObject(obj, activeObj) )
				{
					if(!isReliveState(activeObj)){
						local curDistance = abs(obj.getXPos() - activeObj.getXPos() ) * abs(obj.getXPos() - activeObj.getXPos() ) + 
						abs(obj.getYPos() - activeObj.getYPos() ) * abs(obj.getYPos() - activeObj.getYPos() );

						if (curDistance <= dist)
                    				{
							dist = curDistance;
							targ = activeObj;
							setBobyNumber(obj,getBobyNumber(obj) - 1);
						}
					}
				}
			}
		}
	}
	return targ;
}


function createReLiveDeadHeadLinkCutWildArea(obj)
{
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/eternalpossession/cutwirea_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() - 1,obj.getZPos()); //+ obj.getObjectHeight()/2 );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_moveWithParent(obj, pooledObj);
	sq_AddObject(obj,pooledObj,2,false);	
}


function createReLiveDeadHeadLinkConnectWildArea(obj)
{
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/eternalpossession/connectwirea_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() - 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_moveWithParent(obj, pooledObj);
	sq_AddObject(obj,pooledObj,2,false);	
}

function onSetState_ETERNALPOSSESSION(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
	local state = obj.getVar("state").get_vector(0);
	if (state == 0)
	{
		local skill_level = sq_GetSkillLevel(obj, SKILL_RELIVE); 
		local castTime = sq_GetCastTime(obj, SKILL_RELIVE, skill_level); 
		sq_StartDrawCastGauge(obj, castTime, true);
		if (!isDollState(obj) )
		{
			obj.sq_SetCurrentAnimation(CUSTON_ANI_RELIVE_START_BODY);
		}else{
			local ani = obj.getVar().GetAnimationMap("FavoriteCasting", "character/mage/animation/zrr_ani/favoritismcasting_mad_body.ani"); 
			obj.setCurrentAnimation(ani);
		}
	}
	else if (state == 1)
	{

		if (!isDollState(obj) )
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_RELIVE_LOOP_BODY);
		}else{
			local ani = obj.getVar().GetAnimationMap("FavoriteCasting", "character/mage/animation/zrr_ani/favoritismcasting_mad_body.ani"); 
			obj.setCurrentAnimation(ani);
		}
	}
	else if (state == 2)
	{

		if (!isDollState(obj) )
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_RELIVE_END_A);
		}
		else{
			local ani = obj.getVar().GetAnimationMap("FavoriteCasting", "character/mage/animation/zrr_ani/favoritismcasting_mad_body.ani"); 
			obj.setCurrentAnimation(ani);
		}

	}
	else if (state == 3)
	{
		local saveObj = obj.getVar("saveObj").get_obj_vector(0);
		if (saveObj)
		{
			createReLiveDeadHeadLinkCutWildArea(saveObj);

            //if(masterAppendage) 
            //{
                //sq_HoldAndDelayDie(saveObj, obj, true, true, true, 200, 200, ENUM_DIRECTION_NEUTRAL , masterAppendage);
                //masterAppendage.sq_SetValidTime(750);
            //}
		}

        	if (!isDollState(obj) )
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_RELIVE_END_B);
		}
		else{
			local ani = obj.getVar().GetAnimationMap("FavoriteCasting","character/mage/animation/zrr_ani/favoritismcasting_mad_body.ani"); 
			obj.setCurrentAnimation(ani);
		}

	}
	else if (state == 4)
	{
		local saveObj = obj.getVar("saveObj").get_obj_vector(0);
		if (saveObj)
		{
			local skill_level = sq_GetSkillLevel(obj, SKILL_RELIVE);
			createReLiveDeadHeadLinkConnectWildArea(saveObj);
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(saveObj, obj, SKILL_RELIVE, false,"character/new_mage/relive/ap_eternalpossession.nut", false);
			local hpmpRate = sq_GetLevelData(obj, SKILL_RELIVE, 0, skill_level);
			local defRate = 0;
			if (isFavoriteing(saveObj))
			{
				defRate = sq_GetLevelData(obj, SKILL_RELIVE, 2, skill_level);
			}
			appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, ENUM_CHARACTERJOB_MAGE, SKILL_RELIVE, skill_level);
			appendage.getVar("relivedata").clear_vector();
			appendage.getVar("relivedata").push_vector(hpmpRate);
			appendage.getVar("relivedata").push_vector(defRate);
			CNSquirrelAppendage.sq_AppendAppendageID(appendage, saveObj, obj, SKILL_RELIVE, false);
			//saveObj = sq_GetCNRDObjectToActiveObject(saveObj);
			//saveObj.setHp( saveObj.getHpMax() * 20 / 100 , null, true);
			//CNSquirrelAppendage.sq_RemoveAppendage(saveObj, "character/new_mage/relive/ap_relive_deadhead.nut");		

		}

		if (!isDollState(obj) )
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_RELIVE_END_C);
		}else{
			local ani = obj.getVar().GetAnimationMap("FavoriteCasting","character/mage/animation/zrr_ani/favoritismcasting_mad_body.ani"); 
			obj.setCurrentAnimation(ani);
		}

	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED , SPEED_TYPE_CAST_SPEED , SPEED_VALUE_DEFAULT , SPEED_VALUE_DEFAULT , 1.0 , 1.0);
}


function onProc_ETERNALPOSSESSION(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {

    }else if (state == 1){

        local pAni = obj.sq_GetCurrentAni();
        local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
        local currentT = sq_GetCurrentTime(pAni);
        local saveObj = getNearestDeadCharacterWithDistance(obj,1000);
        if (saveObj)
        {
            obj.getVar("saveObj").clear_obj_vector();
            obj.getVar("saveObj").push_obj_vector(saveObj);

            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(2);
            obj.sq_AddSetStatePacket(STATE_RELIVE, STATE_PRIORITY_USER, true);

        }
        if (currentT >= 1000)
        {
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
        }
    }
}

function onEndCurrentAni_ETERNALPOSSESSION(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
        obj.sq_AddSetStatePacket(STATE_RELIVE, STATE_PRIORITY_USER, true);
    }else if (state == 1){

        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 2){

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(3);
        obj.sq_AddSetStatePacket(STATE_RELIVE, STATE_PRIORITY_USER, true);
    }else if (state == 3){

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(4);
        obj.sq_AddSetStatePacket(STATE_RELIVE, STATE_PRIORITY_USER, true);
    }else if (state == 4){

        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}