//passve SET FLAG 1 SHAKE 

function checkExecutableSkill_atg(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_ATG);

	if (isUse) {

        if (!obj.isMyControlObject() )
            return false;
        local job = getNyarly(obj);
        if(job)
        {

            job.getVar("state").clear_vector();
            job.getVar("state").push_vector(8);
            local pIntVec = sq_GetGlobalIntVector();
            sq_IntVectorClear(pIntVec);
            sq_IntVectorPush(pIntVec, 0);
            job.addSetStatePacket(18, pIntVec, STATE_PRIORITY_AUTO, false, "");
        }
		return true;
	}

	return false;
}


function createAtgEndAni(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atnyarlyatg/g/gend_body.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}


function createAtgCrowLingmist(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atnyarlyatg/word/g_word_crowlingmist.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}



function createAtgFlash(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atnyarlyatg/g/gstart_flash_black.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}

function createAtgFront(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atnyarlyatg/g/gstart_front_1.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() + 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}


function createAtgBack(obj)
{

	local ani = sq_CreateAnimation("","passiveobject/zrr_skill/atmage/animation/atnyarlyatg/g/gstart_back_1.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 0);
	pooledObj.setCurrentPos(posX  ,obj.getYPos() - 1,obj.getZPos());
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}


function checkCommandEnable_atg(obj)
{
	if (!obj) return false;

	return getNyarly(obj);
}

