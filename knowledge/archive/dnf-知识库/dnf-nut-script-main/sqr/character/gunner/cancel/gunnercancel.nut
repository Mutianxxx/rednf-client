function onProc_gunnercancel(obj)
{
	if (!obj) return false;
	if (isAtSOWalkerOnBody(obj)) return false;
	obj.setSkillCommandEnable(40, true);
	obj.setSkillCommandEnable(53, true);
	obj.setSkillCommandEnable(76, true);
	obj.setSkillCommandEnable(77, true);
	obj.setSkillCommandEnable(51, true);
	if(sq_GetSkillLevel(obj, SKILL_HEADSHOTMASTERY)>0)
	{
		obj.setSkillCommandEnable(5 ,true);
		obj.setSkillCommandEnable(20 ,true);
		obj.setSkillCommandEnable(47 ,true);
	}
}

function onProcCon_gunnercancel(obj)
{
	if (!obj) 
		return false;
	if(obj.getCurrentSkillIndex()<0){
		if(sq_GetSkillLevel(obj,5)>0&&sq_GetSkillLevel(obj,129)>0)
		{
			local inShot = obj.getVar("inShot").get_vector(0);
			local atkend = obj.getVar("atkpup").get_vector(0);
			//local substate1 = obj.getVar("powerup").get_vector(1);
			if(atkend == 1){
				obj.getVar("atkpup").clear_vector();
				obj.getVar("atkpup").push_vector(0);
				if(!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/gunner/headshotmastery/ap_headshotmastery.nut")){
					local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_HEADSHOTMASTERY, false, "character/gunner/headshotmastery/ap_headshotmastery.nut", true);
				}
				obj.sq_IntVectClear();
				obj.sq_AddSetStatePacket(0, STATE_PRIORITY_USER, true);
				return true;
			}
			if(inShot == 1){
				local pObj = obj.getMyPassiveObject(22254, 0);
				if(!pObj)
					return false;
				local X = obj.getXPos();
				local Y = obj.getYPos();
				local posX = pObj.getXPos();
				local posY = pObj.getYPos();
				local distanceX = sq_Abs(posX - X);
				local distanceY = sq_Abs(posY - Y);
				//print("X:"+distanceX+" Y:"+distanceY+"\n\r");
				if(distanceX < 201 && distanceY < 20)
				{
					obj.sq_IntVectClear();
					obj.sq_AddSetStatePacket(0, STATE_PRIORITY_USER, true);
					if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/gunner/headshotmastery/ap_headshotmastery.nut")){
						CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/gunner/headshotmastery/ap_headshotmastery.nut");
					}
					//print("in\n\r");
					return true;
				}
			}
			
		}
	}
	return false;
}


function onAfterSetState_gunnercancel(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate0 = obj.sq_GetVectorData(datas, 0);
	local substate1 = obj.sq_GetVectorData(datas, 1);
	obj.getVar("powerup").clear_vector();
	obj.getVar("powerup").push_vector( substate0 );
	obj.getVar("powerup").push_vector( substate1 );
}

function onEndState_gunnercancel(obj, new_state)
{
	if(!obj) return;
	obj.getVar("inShot").clear_vector();
	obj.getVar("inShot").push_vector(0);
}

function startSkillCoolTime_gunnercancel(obj, skillIndex, skillLevel, currentCoolTime)
{

	local newCoolTime	= currentCoolTime;
	local level = sq_GetSkillLevel(obj, SKILL_HEADSHOTMASTERY);
	if(level < 1)
		return currentCoolTime;
	if(skillIndex == 5 && skillLevel > 0)
	{
		
		local decRate	= 1.0 - sq_GetLevelData(obj, SKILL_HEADSHOTMASTERY, 3, level)/1000.0;
		newCoolTime	= currentCoolTime * decRate;
	}
	if(skillIndex == 20 && skillLevel > 0)
	{
		local decRate	= 1.0 - sq_GetLevelData(obj, SKILL_HEADSHOTMASTERY, 4, level)/1000.0;
		newCoolTime	= currentCoolTime * decRate;
	}
	if(newCoolTime < 0)
	{
		newCoolTime = 0;
	}
	newCoolTime = newCoolTime.tointeger();
	return newCoolTime;	
}