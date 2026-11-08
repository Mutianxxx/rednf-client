//CUSTOM_ANI_SHAOWSTAY <- 137



function checkExecutableSkill_shaowstay(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_SHAOWSTAY);
	if (isUseSkill) 
    {
		obj.sq_AddSetStatePacket(STATE_SHAOWSTAY, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_shaowstay(obj)  
{

	return true;
}



function onSetState_SHAOWSTAY(obj, state, datas, isResetTimer)
{	
    obj.sq_SetCurrentAnimation(CUSTOM_ANI_SHAOWSTAY);
    obj.getVar("len").clear_vector();
    obj.getVar("len").push_vector( obj.getXPos() );
    obj.getVar("len").push_vector( obj.getYPos() );

    local disT = obj.sq_GetIntData(SKILL_SHAOWSTAY, 0);
    local backPos = obj.sq_GetIntData(SKILL_SHAOWSTAY, 1);
    obj.getVar("tar").clear_obj_vector();


	local targetObj = findAngleTarget(obj, disT, 90, 100);
    if (targetObj)
    {

        local tarBackPosX = sq_GetDistancePos(targetObj.getXPos(), targetObj.getDirection(),backPos);

        obj.getVar("len").push_vector( abs(tarBackPosX - obj.getXPos() ) );
        obj.getVar("len").push_vector( targetObj.getYPos() - obj.getYPos() );

        local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(targetObj, obj, SKILL_SHAOWSTAY, false, "character/thief/4_shadow/shaowstay/ap_shaowstay.nut", true);				 

        if(masterAppendage) 
        {

            local holdTime = obj.sq_GetIntData(SKILL_SHAOWSTAY, 2);
            masterAppendage.sq_SetValidTime( holdTime );
        }
        obj.getVar("tar").push_obj_vector(targetObj);
    
    }else{
        obj.getVar("len").push_vector( disT );
        obj.getVar("len").push_vector( 0 );
    }

}

function onEndCurrentAni_SHAOWSTAY(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, true);

    if ( obj.getVar("tar").get_obj_vector_size() > 0 )
    {
        local tar = obj.getVar("tar").get_obj_vector(0);

		obj.setCurrentDirection(tar.getDirection() );
    }
}

function onProc_SHAOWSTAY(obj)
{
    local startX = obj.getVar("len").get_vector(0);
    local startY = obj.getVar("len").get_vector(1);
    local movX = obj.getVar("len").get_vector(2);
    local movY = obj.getVar("len").get_vector(3);

    local ani = obj.sq_GetCurrentAni();
	local delay = ani.getDelaySum(false);
    local currentT = sq_GetCurrentTime(ani);

    local v1 = sq_GetAccel(0, movX, currentT, delay, true);
    local v2 = sq_GetAccel(0, movY, currentT, delay, true);

	local dstX = sq_GetDistancePos(startX, obj.getDirection(),v1);
	local dstY = startY + v2;

	if(obj.isMovablePos(dstX, obj.getYPos() ))
    {
		sq_setCurrentAxisPos(obj, 0, dstX);
    }

	if(obj.isMovablePos(obj.getXPos(), dstY ))
    {
		sq_setCurrentAxisPos(obj, 1, dstY);
    }

}