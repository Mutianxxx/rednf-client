//flag 1 `CreateCurseDoll`	150	0	0
//flag 2 hit one
//flag last hit shake 10 240
//character/mage/animation/ani_als/hex/goblin/hex_goblin_changeexp_00.ani
function checkExecutableSkill_sprlitmagic(obj)  
{
	if (!obj) return false;
	if (getBobyNumber(obj) >= 1)
	{

		local isUseSkill = obj.sq_IsUseSkill(SKILL_SPRLITMAGIC);
		if (isUseSkill) 
		{
			obj.getVar("state").clear_vector();
			obj.getVar("state").push_vector(0);
			obj.sq_AddSetStatePacket(STATE_SPRLITMAGIC , STATE_PRIORITY_USER, true);
			return true;
		}

		//obj.getVar("state").clear_vector();
		//obj.getVar("state").push_vector(2);
		//obj.sq_AddSetStatePacket(STATE_SPRLITMAGIC , STATE_PRIORITY_USER, true);
	}
	else
	{
		playNoDollSound(obj);
	}
}


function checkCommandEnable_sprlitmagic(obj)
{
	if (!obj) return false;
	return isOpenBobyBox(obj);
}

function createFrontSprlitMagicGblinChange(obj,damager)
{
	if (!obj) return;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/hex/goblin/hex_goblin_changeexp_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 2,damager.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFrontSprlitMagicGblinNail1(obj,damager)
{
	if (!obj) return;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/hex_passive/hex_doll1234hit_nail_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + 17);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFrontSprlitMagicGblinNail2(obj,damager)
{
	if (!obj) return;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/hex_passive/hex_doll1234hit_nail_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + 17);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFrontSprlitMagicGblinNail3(obj,damager)
{
	if (!obj) return;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/hex_passive/hex_doll1234hit_nail_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + 37);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFrontSprlitMagicGblinNail4(obj,damager)
{
	if (!obj) return;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/hex_passive/hex_dollhitend_nail_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(damager.getXPos() ,damager.getYPos() + 1,damager.getZPos() + 57);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function createFloorSprlitMagicGround(obj)
{
	if (!obj) return;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/hex/hex_floor_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() - 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}

function onSetState_SPRLITMAGIC(obj, state, datas, isResetTimer)
{
	if (!obj) return;
	local state = obj.getVar("state").get_vector(0);
	obj.sq_StopMove();
	if (state == 0)
	{
		createFloorSprlitMagicGround(obj);
		if (isDollState(obj))
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_DOLL_MAD_SIT);
		}
		else
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPRLITMAGIC_START);
		}
		//obj.sq_SetCurrentAttackInfo(ATTACKINFO_SPRLITMAGIC);
		obj.getVar("dama").clear_obj_vector();
		obj.getVar("hitCount").clear_vector();
		obj.getVar("hitCount").push_vector(4);
		obj.getVar("hitCount").push_vector(1);

	}
	else if (state == 1)
	{

		if (isDollState(obj))
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_DOLL_MAD_THROW2);
		}
		else
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPRLITMAGIC_LOOP);
		}
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_SPRLITMAGIC);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SPRLITMAGIC , STATE_SPRLITMAGIC, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);

	}
	else if (state == 2)
	{

		local var = obj.getVar("dama");  		
		local objectsSize = var.get_obj_vector_size();
		if (objectsSize > 0)
		{
			for(local i=0;i<objectsSize;++i)
			{
				local damager = var.get_obj_vector(i);
				if(damager)
				{
					createFrontSprlitMagicGblinNail4(obj,damager);
				}
			}
		}

		if (isDollState(obj))
		{
			local ani = obj.getVar().GetAnimationMap("sprlitmad", "passiveobject/zrr_skill/newmage/animation/dot/maddefance/maddyguard_body.ani"); 
			obj.setCurrentAnimation(ani);
		}
		else
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SPRLITMAGIC_END);
		}
		obj.sq_SetCurrentAttackInfo(ATTACKINFO_SPRLITMAGIC);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_SPRLITMAGIC , STATE_SPRLITMAGIC, 2, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);				

	}
	obj.getVar("flag").clear_vector();
	obj.getVar("flag").push_vector(0);
}

function onKeyFrameFlag_SPRLITMAGIC(obj,flagIndex)
{
    local state = obj.getVar("state").get_vector(0);
    if (obj.getVar("flag").get_vector(0) == 0)
    {
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(1);

        if (state == 0)
        {
            setBobyNumber(obj,getBobyNumber(obj) - 1);
            findAllMonster_SPRLITMAGIC(obj)


        }else if (state == 1)
        {
            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();
            if (objectsSize > 0)
            {
                for(local i=0;i<objectsSize;++i)
                {
                    local damager = var.get_obj_vector(i);
                    if(damager)
                    {
                        sq_SendHitObjectPacket(obj,damager,0,0,0);
                    }
                }
            }
            obj.sq_SetShake(obj, 4, 150);

        }else if (state == 2)
        {
            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();
            if (objectsSize > 0)
            {
                for(local i=0;i<objectsSize;++i)
                {
                    local damager = var.get_obj_vector(i);
                    if(damager)
                    {

                        CNSquirrelAppendage.sq_RemoveAppendage(damager, "character/new_mage/sprlitmagic/sprlitmagic_gblin1.nut");		
                        sq_SendHitObjectPacket(obj,damager,0,0,0);
                    }
                }
            }
            obj.sq_SetShake(obj, 10, 240);
        }
    }
}
function sendOneHit_SPRLITMAGIC(obj)
{


}

function findAllMonster_SPRLITMAGIC(obj)
{

	local objectManager = obj.getObjectManager();

	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);
		if (object && obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_ACTIVE) )
		{
			local activeObj = sq_GetCNRDObjectToActiveObject(object);
            
            obj.getVar("dama").push_obj_vector(activeObj);

            if (!CNSquirrelAppendage.sq_IsAppendAppendage(activeObj, "character/new_mage/sprlitmagic/sprlitmagic_gblin1.nut"))
            {
                local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(activeObj, obj, SKILL_SPRLITMAGIC, false, "character/new_mage/sprlitmagic/sprlitmagic_gblin1.nut", true);				 
                  sq_HoldAndDelayDie(activeObj, obj, true, true, true, 0, 0, ENUM_DIRECTION_DOWN , masterAppendage);

                createFrontSprlitMagicGblinChange(obj,activeObj);
            }

		}
	}

}
function onEndCurrentAni_SPRLITMAGIC(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        if (obj.getVar("dama").get_obj_vector_size() > 0)
        {
            obj.getVar("state").set_vector(0,1);
            obj.sq_AddSetStatePacket(STATE_SPRLITMAGIC , STATE_PRIORITY_USER, true);

            local var = obj.getVar("dama");  		
            local objectsSize = var.get_obj_vector_size();
            if (objectsSize > 0)
            {
                for(local i=0;i<objectsSize;++i)
                {
                    local damager = var.get_obj_vector(i);
                    if(damager)
                    {
                        local currHit = sq_getRandom(0,4).tointeger();
                        if (currHit == 0)
                        {
                            createFrontSprlitMagicGblinNail1(obj,damager);
                        }else if (currHit == 1)
                        {
                            createFrontSprlitMagicGblinNail2(obj,damager);
                        }else if (currHit == 2)
                        {
                            createFrontSprlitMagicGblinNail3(obj,damager);
                        }
                    }
                }
            }

        }else{
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
        }
    }else if (state == 1)
    {
        local currHit = obj.getVar("hitCount").get_vector(1);
        local maxHit = obj.getVar("hitCount").get_vector(0);
        if (currHit < maxHit)
        {
            obj.getVar("hitCount").set_vector(1,currHit + 1);
        }else{
            obj.getVar("state").set_vector(0,2);
        }
        obj.sq_AddSetStatePacket(STATE_SPRLITMAGIC , STATE_PRIORITY_USER, true);
    }else if (state == 2)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}