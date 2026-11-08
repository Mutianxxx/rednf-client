function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_BloodMageMonsterAppendage_DieEffect")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_BloodMageMonsterAppendage_DieEffect")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_BloodMageMonsterAppendage_DieEffect")
}

function sq_AddEffect(appendage)
{
}

function onEnd_appendage_BloodMageMonsterAppendage_DieEffect(appendage)
{
	local parentObj = appendage.getParent();
	parentObj = sq_GetCNRDObjectToActiveObject(parentObj);
	local sourceObj = appendage.getSource();
	sourceObj = sq_GetCNRDObjectToActiveObject(sourceObj);

		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec,0);
		sq_IntVectorPush(pIntVec,0);
		sq_IntVectorPush(pIntVec,0);
		sq_IntVectorPush(pIntVec,0);
		sq_IntVectorPush(pIntVec,0);
		parentObj.addSetStatePacket(STATE_DIE  , pIntVec, STATE_PRIORITY_FORCE, false, "");
}

function proc_appendage_BloodMageMonsterAppendage_DieEffect(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

	local tar = sq_GetCNRDObjectToActiveObject(parentObj);

    

	if(!sourceObj || !parentObj || tar.isBoss() ) 
    {
		appendage.setValid(false);
		return;
	}




    if (    CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_attack_1.nut") || 
            CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_attack_2.nut") || 
            CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_attack_3.nut") || 
            CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_attack_4.nut") || 
            CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_bloodcastle.nut") || 
            CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_blooddance.nut") || 
            CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_blooddog.nut") || 
            CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_bloodin.nut") || 
            CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_bloodsong.nut") || 
            CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_dash.nut") || 
            CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_jump.nut") || 
            CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_throwbat.nut") || 
            CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_windstrike_upper.nut") ||                       CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_blooddoghold.nut") || 
            CNSquirrelAppendage.sq_IsAppendAppendage(parentObj, "character/atmage/append_bloodmage/ap_bloodstream.nut") )
    {

        local currentT = appendage.getTimer().Get();
        local currentAni = sq_GetCurrentAnimation(parentObj);
        if(!currentAni)
        	return;
        if (currentT < 500)
        {

            currentAni.setEffectLayer(true, GRAPHICEFFECT_NONE, true, sq_RGB(0, 0, 0), sq_ALPHA( 255), true, true);
        }else if (currentT < 1000){
            local v = sq_GetAccel(255, 0, currentT - 500, 500, true);
            currentAni.setEffectLayer(true, GRAPHICEFFECT_NONE, true, sq_RGB(0, 0, 0), sq_ALPHA( v ), true, true);
        }else{
            appendage.setValid(false);
            return;
        }

        parentObj.setCurrentPos(appendage.getVar().get_vector(0),
                                appendage.getVar().get_vector(1),
                                appendage.getVar().get_vector(2) );

    }else{

		appendage.setValid(false);
		return;
    }






}



function onStart_appendage_BloodMageMonsterAppendage_DieEffect(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	parentObj = sq_GetCNRDObjectToActiveObject(parentObj);
	local sourceObj = appendage.getSource();
	sourceObj = sq_GetCNRDObjectToActiveObject(sourceObj);
				
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	

	local tar = sq_GetCNRDObjectToActiveObject(parentObj);

	if(!sourceObj || !parentObj || tar.isBoss() ) 
    {
		appendage.setValid(false);
		return;
	}

    sq_SendMessage(parentObj,OBJECT_MESSAGE_INVINCIBLE,1,0);
    sq_PostDelayedMessage(parentObj,OBJECT_MESSAGE_INVINCIBLE,0,0,50000);

    appendage.getVar().clear_vector(  );
    appendage.getVar().push_vector( parentObj.getXPos() );
    appendage.getVar().push_vector( parentObj.getYPos() );
    appendage.getVar().push_vector( parentObj.getZPos() );
    createDieEffectLastSmoke(sourceObj,parentObj,0,1,0);

//	sqrChr.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);

}

