function checkExecutableSkill_superlolly(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_SUPERLOLLY);
	if (isUseSkill) 
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_SUPERLOLLY, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_superlolly(obj)
{

	return true;
}

function onSetState_SUPERLOLLY(obj, state, datas, isResetTimer)
{

	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);

    obj.getVar("pos").clear_vector();
    obj.getVar("pos").push_vector(obj.getZPos());

    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);//frame is end

    obj.getVar("count").clear_vector();
    obj.getVar("count").push_vector(0);


    obj.sq_SetCurrentAnimation(CUSTOM_ANI_SUPERLOLLY_ATTACK);

	obj.sq_SetCurrentAttackInfo(ATTACKINFO_SUPERLLLY);
	local damage = obj.sq_GetBonusRateWithPassive(SKILL_SUPERLOLLY , STATE_SUPERLOLLY, 0, 1.0);
	obj.sq_SetCurrentAttackBonusRate(damage);				

}


function createCircleSkill_SUPERLOLLY(obj)
{
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/superlolly/lollipopcrush/lollipopcrushfloor_floor.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 200);
	
	pooledObj.setCurrentPos(posX,obj.getYPos(),0);
	
	pooledObj.setCurrentDirection(obj.getDirection());
	
	sq_AddObject(obj,pooledObj,0,false);	
}


function onProc_SUPERLOLLY(obj)
{


	local pAni = obj.sq_GetCurrentAni();
	local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);


    if (frmIndex == 11)
    {
        sq_flashScreen(obj,0,0,150,150, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

    }
    if (frmIndex == 16)
    {
        obj.sq_SetShake(obj, 5, 700);
        obj.getVar("flag").set_vector(0,1);
        createCircleSkill_SUPERLOLLY(obj);
    }

    if (obj.getVar("flag").get_vector(0) == 0)
    {
        obj.setCurrentPos(obj.getXPos(),obj.getYPos(),obj.getVar("pos").get_vector(0));
    }

}

function onAttack_SUPERLOLLY(obj, damager, boundingBox, isStuck)
{

    local state = obj.getVar("state").get_vector(0);
    local targetCount = sq_GetLevelData(obj, SKILL_SUPERLOLLY, 1, sq_GetSkillLevel(obj, SKILL_SUPERLOLLY) ) + 1;
    local maxCount = sq_GetLevelData(obj, SKILL_SUPERLOLLY, 11, sq_GetSkillLevel(obj, SKILL_SUPERLOLLY) );
    local currCount = obj.getVar("count").get_vector(0);

    local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_SUPERLOLLY , STATE_SUPERLOLLY, 2, 1.0);

    local smProc = sq_GetLevelData(obj, SKILL_SUPERLOLLY, 3, sq_GetSkillLevel(obj, SKILL_SUPERLOLLY) );
    local smLevel = sq_GetLevelData(obj, SKILL_SUPERLOLLY, 4, sq_GetSkillLevel(obj, SKILL_SUPERLOLLY) );
    local smTime = sq_GetLevelData(obj, SKILL_SUPERLOLLY, 5, sq_GetSkillLevel(obj, SKILL_SUPERLOLLY) );
    local smDown = sq_GetLevelData(obj, SKILL_SUPERLOLLY, 6, sq_GetSkillLevel(obj, SKILL_SUPERLOLLY) );

    local gdProc = sq_GetLevelData(obj, SKILL_SUPERLOLLY, 7, sq_GetSkillLevel(obj, SKILL_SUPERLOLLY) );
    local gdLevel = sq_GetLevelData(obj, SKILL_SUPERLOLLY, 8, sq_GetSkillLevel(obj, SKILL_SUPERLOLLY) );
    local gdTime = sq_GetLevelData(obj, SKILL_SUPERLOLLY, 9, sq_GetSkillLevel(obj, SKILL_SUPERLOLLY) );
    local gdRate = sq_GetLevelData(obj, SKILL_SUPERLOLLY, 10, sq_GetSkillLevel(obj, SKILL_SUPERLOLLY) );




    obj.sq_StartWrite();
    obj.sq_WriteDword(attackBonusRate);
    obj.sq_WriteDword(0);

    sq_SendCreatePassiveObjectPacketPos(obj, 24348, 0,  damager.getXPos(),  damager.getYPos(), damager.getZPos());


    for(local i=0;i<targetCount;++i)
    {
        if (maxCount < currCount + 1)
        {
            return false;
        }else{
            obj.getVar("count").set_vector(0,currCount+1);
        }

        local darkRate = obj.sq_GetIntData(SKILL_SUPERLOLLY, 0);
        obj.sq_StartWrite();
        obj.sq_WriteDword(attackBonusRate);

        if (darkRate <= sq_getRandom(0,100))
        {
            obj.sq_WriteDword(1);

            obj.sq_WriteDword(smProc);
            obj.sq_WriteDword(smLevel);
            obj.sq_WriteDword(smTime);
            obj.sq_WriteDword(smDown);

        }else{
            obj.sq_WriteDword(2);

            obj.sq_WriteDword(gdProc);
            obj.sq_WriteDword(gdLevel);
            obj.sq_WriteDword(gdTime);
            obj.sq_WriteDword(gdRate);
        }
        sq_SendCreatePassiveObjectPacketPos(obj, 24348, 0,  damager.getXPos(),  damager.getYPos(), damager.getZPos());
    }


}

function onEndCurrentAni_SUPERLOLLY(obj)
{

	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);

}

















