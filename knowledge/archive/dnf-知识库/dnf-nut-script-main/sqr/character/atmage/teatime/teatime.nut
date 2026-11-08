function checkExecutableSkill_teatime(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_TEATIME);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_TEATIME , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}

function checkCommandEnable_teatime(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();


	return getNyarly(obj);

	return false;
}


function createTeaCupSummonAni(obj)
{
	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atteatime/teatime_teacupsummon.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}



function onSetState_TEATIME(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	obj.sq_StopMove();
	obj.sq_PlaySound("MW_TEA_TIME");
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_TEATIME_BODY);
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);



}

function onEndCurrentAni_TEATIME(obj)
{
    if(!obj.isMyControlObject())
        return false;
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function onKeyFrameFlag_TEATIME(obj,flagIndex)
{
	if(!obj)
		return false;
    if(!obj.isMyControlObject())
        return false;
    if ( obj.getVar("flag").get_vector(0) == 0)
    {
        obj.getVar("flag").set_vector(0,1);


        local job = getNyarly(obj);
        if(job)
        {
            createFrontTeportWomanControl(job);
            local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), -50);
            job.setCurrentPos(posX,obj.getYPos() -1 ,0);
            job.getVar("state").clear_vector();
            job.getVar("state").push_vector(9);
            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            job.addSetStatePacket(19, pIntVec, STATE_PRIORITY_AUTO, false, "");
            createFrontTeportWomanControl(job);

            local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_TEATIME, true,
             "character/atmage/teatime/ap_teatime.nut", false);


            local skill_level = sq_GetSkillLevel(obj, SKILL_TEATIME);
            appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_TEATIME, skill_level);
            
            CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_TEATIME, true);


        }


    }
}


