function checkExecutableSkill_womancontrol(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_WOMANCONTROL);

	if (isUse) {


        local job = getNyarly(obj);
        if(job)
        {
            createFrontTeportWomanControl(job);
            local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), obj.sq_GetIntData(SKILL_WOMANCONTROL, 0) );
            job.setCurrentPos(posX,obj.getYPos() + obj.sq_GetIntData(SKILL_WOMANCONTROL, 1) ,0);
            job.setCurrentDirection(obj.getDirection());
            job.getVar("state").clear_vector();
            job.getVar("state").push_vector(7);
            job.getVar("subState").clear_vector();
            job.getVar("subState").push_vector(0);
            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            job.addSetStatePacket(17, pIntVec, STATE_PRIORITY_AUTO, false, "");
            createFrontTeportWomanControl(job);
        }
		return true;
	}

	return false;
}

function createFrontTeportWomanControl(obj)
{
	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/monster/nyarly/animation/cheekit/teleport/cheekit_teleport_dodge.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	
}


function checkCommandEnable_womancontrol(obj)
{
	if (!obj) return false;

	return getNyarly(obj);
}

