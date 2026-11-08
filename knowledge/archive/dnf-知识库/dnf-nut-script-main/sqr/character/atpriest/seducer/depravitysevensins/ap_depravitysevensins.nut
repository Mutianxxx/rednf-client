
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_DepravitySevenSins")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_DepravitySevenSins")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_DepravitySevenSins")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_DepravitySevenSins")
	appendage.sq_AddFunctionName("onSetHp", "onSetHp_appendage_DepravitySevenSins")
}

function drawAppend_appendage_DepravitySevenSins(appendage, isOver, x, y, isFlip)
{
	if (!appendage) {
		return;
	}
	
	local obj = appendage.getParent();
	
	if (!obj) {
		appendage.setValid(false);
		return;
	}

	local backAni = appendage.getVar().GetAnimationMap("depravityb", "character/priest/seducer/effect/animation/atdepravitysevensins/demonization/depravitysevensins_changeloop_back.ani");
	local frontAni = appendage.getVar().GetAnimationMap("depravityf", "character/priest/seducer/effect/animation/atdepravitysevensins/demonization/depravitysevensins_changeloop_front01.ani");

	if (frontAni && isOver) {
		sq_AnimationProc(frontAni);
		sq_drawCurrentFrame(frontAni, x, y, isFlip);
	}	
	else if (backAni && !isOver) {
		sq_AnimationProc(backAni);
		sq_drawCurrentFrame(backAni, x, y, isFlip);
	}
}

function onSetHp_appendage_DepravitySevenSins(appendage, hp, attacker)
{
	if(!appendage) {
		return hp;
	}
	
	local obj = appendage.getParent();
 	if(!obj) {
		return hp;
	}
	
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	if(!sqrChr){
		return hp;
	}
	if(!sqrChr.isMyControlObject()){
		return hp;
	}
	
	local currentHp = hp;
	local orghp = appendage.getVar("dsevensins").get_vector(1); 
	
	if(attacker)
	{
		local attackInfo = sq_GetCurrentAttackInfo(attacker);
		if(attackInfo)
		{
			if(attackInfo.isIgnoreDieHard_)
				return hp;
		}
	}
		
	if (currentHp <= 0 && appendage.getVar("dsevensins").get_vector(0) == 1) {
		appendage.getVar("dsevensins").set_vector(0, 0);
		return orghp;
	}
	
	return currentHp;
}

function proc_appendage_DepravitySevenSins(appendage)
{
	if(!appendage) {
		return;
	}
	if(!sq_IsInBattle()){
		appendage.setValid(false);
		return;
	}
	local parentObj = appendage.getParent();
	if(!parentObj) {
		appendage.setValid(false);
		return;
	}
	local sqrObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	sq_SetCustomDamageType(sqrObj, true, 1); 
	local ChrState = sqrObj.getState();
	SeducerStateCommandEnable(sqrObj);
	if(appendage.getVar("dsevensins").get_vector(0) == 0){
		appendage.getVar("dsevensins").set_vector(0, 2);
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 2);
		sqrObj.addSetStatePacket(STATE_DEPRAVITYSEVENSINS, pIntVec, STATE_PRIORITY_FORCE, false, "");
		sqrObj.flushSetStatePacket();
	}
	if(ChrState == STATE_DIE) {
		appendage.setValid(false);
		return;
	}
}


function onStart_appendage_DepravitySevenSins(appendage)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
				
	if(!parentObj) {
		appendage.setValid(false);
		return;
	}
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(parentObj);
	 if(!sqrChr)
		return;
	sqrChr.setHp(sqrChr.getHpMax(), null, true);
	sqrChr.sq_SetSoundTagCreatureCommand("PW_CMDPET_DM");
	sqrChr.sq_SetSoundTagLackMp("R_PW_COOLTIME_DM");
	sqrChr.sq_SetSoundTagCoolTime("R_PW_COOLTIME_DM");
	sqrChr.sq_SetSoundTagDie("PW_DIE_DM");
	sqrChr.sq_SetSoundTagBackStepStart("PW_BACK");
	sqrChr.sq_SetSoundTagThrowItem("R_PW_THROW_DM");
}

function onEnd_appendage_DepravitySevenSins(appendage)
{
	if(!appendage) {
		return;
	}
	if(!sq_IsInBattle()){
		appendage.setValid(false);
		return;
	}
	local parentObj = appendage.getParent();
	 if(!parentObj)
	 {
	 	appendage.setValid(false);
	 	return;
	 }
	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	createdemonizationeff02(obj, 0, 0, 0);
	setVliadEffectDepravitySevenSins(obj);
	sq_SetCustomDamageType(obj, false, 1);
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	appendage.setValid(false);
	
	local orghp = appendage.getVar("dsevensins").get_vector(1);
	obj.setHp(orghp, null, true);
	obj.sq_SetSoundTagCreatureCommand("PW_CMDPET_MS");
	obj.sq_SetSoundTagLackMp("R_PW_COOLTIME_MS");
	obj.sq_SetSoundTagCoolTime("R_PW_COOLTIME_MS");
	obj.sq_SetSoundTagDie("PW_DIE_MS");
	obj.sq_SetSoundTagBackStepStart("PW_BACK");
	obj.sq_SetSoundTagThrowItem("R_PW_THROW");
	return;
}
