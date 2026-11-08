 
function setCustomData_po_darkmoon(obj,receiveData)
{

	if (!obj) return;
 	local anisa = sq_AddDrawOnlyAniFromParent(obj, "character/mage/effect/animation/darkmoon/darkmoon_startamoon.ani", 0, 1, 0);
 	sq_moveWithParent(obj, anisa);
	
	sq_SetCurrentAttackInfoFromCustomIndex(obj, 0);
	local attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, receiveData.readDword());
	local size = receiveData.readDword();
	local blind_prob = receiveData.readDword();
	local blind_level = receiveData.readDword();
	local blind_time = receiveData.readDword();
	local blind_stuck = receiveData.readDword();
	sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, ACTIVESTATUS_BLIND, blind_prob, blind_level, blind_time, 50, blind_stuck);
	//sq_SetCurrentAttackInfo(obj, attackInfo);
	
	local chr = obj.getTopCharacter();
	local sqrChr = sq_ObjectToSQRCharacter(chr);
	local skillLevel = sqrChr.sq_GetSkillLevel(148);
	local time = sq_GetLevelData(sqrChr, 148, 0, skillLevel);
	local hp = sq_GetLevelData(sqrChr, 148, 1, skillLevel);
	obj.setMapFollowParent(sqrChr);
	obj.setMapFollowType(1);
	
	obj.getVar("state").clear_vector();
	obj.getVar("state").push_vector(0);
	obj.getVar("subType").clear_vector();
	obj.getVar("subType").push_vector(time);
	obj.getVar("subType").push_vector(hp);
	obj.getVar("subType").push_vector(size);
	
	if(obj.isMyControlObject())
	{
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);
		obj.addSetStatePacket(0, pIntVec, STATE_PRIORITY_AUTO, false, "");
		//print("\n\rset0 ok!");
	}
	
}

function setState_po_darkmoon(obj,state,datas)
{
	if(!obj) return;
	
	local passiveState = state;
	local orgState = obj.getVar("state").get_vector(0);
	obj.getVar("state").set_vector(0, passiveState);
	//print("\n\rin setState:"+state);
	switch(passiveState)
 	{
 		case 10:
 			if(orgState > passiveState)
 			{
 				local ania = sq_AddDrawOnlyAniFromParent(obj, "passiveobject/character/mage/animation/darkmoon/recovery/darkmoonrecovery2to1_01.ani", 0, 1, 0);
 				sq_moveWithParent(obj, ania);
 			}
 			local ani = obj.getCustomAnimation(0);
			obj.setCurrentAnimation(ani); 
		break;
 		case 11: 
			if(orgState < passiveState)
			{
				local ania = sq_AddDrawOnlyAniFromParent(obj, "passiveobject/character/mage/animation/darkmoon/darkmoon_loop2a_moon.ani", 0, 1, 0);
				sq_moveWithParent(obj, ania);
			}
			else
			{
				local ania = sq_AddDrawOnlyAniFromParent(obj, "passiveobject/character/mage/animation/darkmoon/recovery/darkmoonrecovery3to2_01.ani", 0, 1, 0);
				sq_moveWithParent(obj, ania);
			}
 			local ani = obj.getCustomAnimation(1);
			obj.setCurrentAnimation(ani); 
		break;
 		case 12: 
			if(orgState < passiveState)
			{
			local ania = sq_AddDrawOnlyAniFromParent(obj, "passiveobject/character/mage/animation/darkmoon/darkmoon_loop3a_moon.ani", 0, 1, 0);
			sq_moveWithParent(obj, ania);
			}
			else
			{
				local ania = sq_AddDrawOnlyAniFromParent(obj, "passiveobject/character/mage/animation/darkmoon/recovery/darkmoonrecovery4to3_01.ani", 0, 1, 0);
				sq_moveWithParent(obj, ania);
			}
 			local ani = obj.getCustomAnimation(2);
			obj.setCurrentAnimation(ani); 
		break;
 		case 13: 
			if(orgState < passiveState)
			{
				local ania = sq_AddDrawOnlyAniFromParent(obj, "passiveobject/character/mage/animation/darkmoon/darkmoon_loop4a_moon.ani", 0, 1, 0);
				sq_moveWithParent(obj, ania);
			}
			else
			{
				local ania = sq_AddDrawOnlyAniFromParent(obj, "passiveobject/character/mage/animation/darkmoon/recovery/darkmoonrecovery5to4_01.ani", 0, 1, 0);
				sq_moveWithParent(obj, ania);
			}
 			local ani = obj.getCustomAnimation(3);
			obj.setCurrentAnimation(ani); 
		break;
 		case 14: 
			if(orgState < passiveState)
			{
				local ania = sq_AddDrawOnlyAniFromParent(obj, "passiveobject/character/mage/animation/darkmoon/darkmoon_loop5a_moon.ani", 0, 1, 0);
				sq_moveWithParent(obj, ania);
			}
			else
			{
				local ania = sq_AddDrawOnlyAniFromParent(obj, "passiveobject/character/mage/animation/darkmoon/recovery/darkmoonrecovery6to5_01.ani", 0, 1, 0);
				sq_moveWithParent(obj, ania);
			}
 			local ani = obj.getCustomAnimation(4);
			obj.setCurrentAnimation(ani); 
		break;
 		case 15: 
			local ania = sq_AddDrawOnlyAniFromParent(obj, "passiveobject/character/mage/animation/darkmoon/darkmoon_loop6a_moon.ani", 0, 1, 0);
			sq_moveWithParent(obj, ania);
 			local ani = obj.getCustomAnimation(5);
			obj.setCurrentAnimation(ani); 
		break;
 		case 16: 
 			local ani = obj.getCustomAnimation(6);
 			local size = obj.getVar("subType").get_vector(2);
 			local areaSizeRate = size.tofloat() / 100.0;
			sq_SetAttackBoundingBoxSizeRate(ani, areaSizeRate, areaSizeRate, areaSizeRate);
			obj.setCurrentAnimation(ani); 
		break;
	}
}

function procAppend_po_darkmoon(obj)
{
	if(!obj) return;

	local chr = obj.getTopCharacter();
	
	local passiveState = obj.getVar("state").get_vector(0);
	
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(chr);
	
	if (!CNSquirrelAppendage.sq_IsAppendAppendage(sqrChr, "character/mage/darkmoon/ap_darkmoon.nut")){
	 	if(obj.isMyControlObject() && passiveState != 16){
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
 			obj.addSetStatePacket(16, pIntVec, STATE_PRIORITY_AUTO, false, ""); 
 		}
	}
	else{
		local appendage = sqrChr.GetSquirrelAppendage("character/mage/darkmoon/ap_darkmoon.nut");
		local nowhp = appendage.getVar("hpMax").get_vector(0);
		local maxhp = obj.getVar("subType").get_vector(1);
		
		local hpstate = nowhp.tofloat() / maxhp.tofloat();
		hpstate = hpstate.tofloat();
		if(obj.isMyControlObject()){
			if(hpstate >= 0.83 && passiveState != 10){
				sq_IntVectorClear(sq_GetGlobalIntVector());
				sq_IntVectorPush(sq_GetGlobalIntVector(), 0);
				obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, ""); 
			}
			else if(hpstate < 0.83 && hpstate > 0.67 && passiveState != 11){
				sq_IntVectorClear(sq_GetGlobalIntVector());
				sq_IntVectorPush(sq_GetGlobalIntVector(), 0);
				obj.addSetStatePacket(11, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, ""); 
			}
			else if(hpstate < 0.67 && hpstate > 0.5 && passiveState != 12){
				sq_IntVectorClear(sq_GetGlobalIntVector());
				sq_IntVectorPush(sq_GetGlobalIntVector(), 0);
				obj.addSetStatePacket(12, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, ""); 
			}
			else if(hpstate < 0.5 && hpstate > 0.33 && passiveState != 13){
				sq_IntVectorClear(sq_GetGlobalIntVector());
				sq_IntVectorPush(sq_GetGlobalIntVector(), 0);
				obj.addSetStatePacket(13, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, ""); 
			}
			else if(hpstate < 0.33 && hpstate > 0.17 && passiveState != 14){
				sq_IntVectorClear(sq_GetGlobalIntVector());
				sq_IntVectorPush(sq_GetGlobalIntVector(), 0);
				obj.addSetStatePacket(14, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, ""); 
			}
			else if(hpstate <= 0.17 && passiveState != 15){
				sq_IntVectorClear(sq_GetGlobalIntVector());
				sq_IntVectorPush(sq_GetGlobalIntVector(), 0);
				obj.addSetStatePacket(15, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, ""); 
			}
		}
	}

}

function onChangeSkillEffect_po_darkmoon(obj,skillIndex,receiveData)
{

	if(!obj) return;

}

function onDestroyObject_po_darkmoon(obj,object)
{

	if(!obj) return;

}

function onKeyFrameFlag_po_darkmoon(obj,flagIndex)
{

	if(!obj) return;

}


function onEndCurrentAni_po_darkmoon(obj)
{

	if(!obj) return;
	local passiveState = obj.getVar("state").get_vector(0);
	switch(passiveState)
 	{
 		case 0: 
 			if(obj.isMyControlObject()){
 			 	local pIntVec = sq_GetGlobalIntVector();
				sq_IntVectorClear(pIntVec);
				sq_IntVectorPush(pIntVec, 0);
 				obj.addSetStatePacket(10, pIntVec, STATE_PRIORITY_AUTO, false, ""); 
 			}
		break;
 		case 16: 
			if (obj.isMyControlObject()){
				sq_SendDestroyPacketPassiveObject(obj);
			}
		break;
	}
}
