 
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_mage_avatar") 
	appendage.sq_AddFunctionName("proc", "proc_appendage_mage_avatar") 
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_mage_avatar") 
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_mage_avatar") 
}

function drawAppend_appendage_mage_avatar(appendage, isOver, x, y, isFlip) {
	if (!appendage) {
		return;
	}
	if(!sq_IsInBattle()){
		appendage.setValid(false);
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}

	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj);

	local anib2 = appendage.getVar().GetAnimationMap("avatarb2", "character/mage/effect/animation/avatar/avataraurabody_eff_00.ani");
	local anif = appendage.getVar().GetAnimationMap("avatarf", "character/mage/effect/animation/avatar/avatarauralooptop_eff_01.ani");
	local anib = appendage.getVar().GetAnimationMap("avatarb", "character/mage/effect/animation/avatar/avatarauraloopbot_eff_01.ani");
	local anifz = appendage.getVar().GetAnimationMap("avatarfz", "character/mage/effect/animation/avatar/avatarauraendtop_eff_01.ani");
	local anibz = appendage.getVar().GetAnimationMap("avatarbz", "character/mage/effect/animation/avatar/avatarauraendbot_eff_01.ani");

	if (obj.getZPos() > 0) {
		if (isOver) {
			sq_AnimationProc(anifz);
			sq_drawCurrentFrame(anifz, x, y, isFlip);
		} else if (!isOver) {
			sq_AnimationProc(anibz);
			sq_AnimationProc(anib2);
			sq_drawCurrentFrame(anibz, x, y, isFlip);
			sq_drawCurrentFrame(anib2, x, y - 2, isFlip);
		}
	} else {

		if (isOver) {
			sq_AnimationProc(anif);
			sq_drawCurrentFrame(anif, x, y, isFlip);
		} else if (!isOver) {
			sq_AnimationProc(anib);
			sq_AnimationProc(anib2);
			sq_drawCurrentFrame(anib, x, y, isFlip);
			sq_drawCurrentFrame(anib2, x, y - 2, isFlip);
		}
	}
}

function onStart_appendage_mage_avatar(appendage)
{
	if(!appendage)
		return;
	local obj = appendage.getSource(); 
	local parentObj = appendage.getParent(); 
	if(!obj || !parentObj)
	{
		appendage.setValid(false);
		return;
	}
	if(!sq_IsInBattle()){
		appendage.setValid(false);
		return;
	}
	local spectrum = appendage.sq_GetOcularSpectrum("ocularSpectrum"); 
	if(!spectrum) 
	{
		spectrum = appendage.sq_AddOcularSpectrum("ocularSpectrum", obj, obj, 100); 
		sq_SetParameterOcularSpectrum(spectrum, 500, 50, true, sq_RGBA(255, 244, 77, 150), sq_RGBA(255, 244, 77, 0), 2, 2, 2); 
	}
	local obj = sq_GetCNRDObjectToSQRCharacter(obj);
	obj.sq_PlaySound("AVATAR_AURA_LOOP", SOUND_ID_MAGE_AVATAR); 
	appendage.getVar("skill").setBool(0, false); 
}

function proc_appendage_mage_avatar(appendage)
{

	if(!appendage) return;
	
	local parentObj = appendage.getParent();
	
	if(!parentObj)
	{ 
 		appendage.setValid(false); 
 		return;
	}
	if(!sq_IsInBattle()){
		appendage.setValid(false);
		return;
	}
	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj); 
	if(!obj || obj.isDead())
	{ 
 		appendage.setValid(false); 
 		return;
	}
	
	obj.setSkillCommandEnable(83, false); 
	if(!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar_icon.nut"))
	{
		local ylYw61KQiz = obj.getState(); 
		switch(ylYw61KQiz)
 		{

 			case STATE_STAND:
 			case STATE_ATTACK:
 			case STATE_DASH:
 				if(obj.sq_IsMyControlObject())
 				{
 					obj.sq_IntVectClear();
 					obj.sq_IntVectPush(0);
 					obj.sq_AddSetStatePacket(STATE_MAGE_RETURNTOBM, STATE_PRIORITY_USER, true); 
 					return;
 				}
 			break;
 		}
 	}
	sq_SetCustomDamageType(obj, true, 1); 
}

function onEnd_appendage_mage_avatar(appendage)
{
	if(!appendage)
		return;
	local obj = appendage.getParent(); 
	if(!obj)
	{ 
		appendage.setValid(false); 
		return;
	}
	local spectrum = appendage.sq_GetOcularSpectrum("ocularSpectrum"); 
	if(spectrum) 
		spectrum.endCreateSpectrum(); 
	if(!sq_IsInBattle()){
		appendage.setValid(false);
		return;
	}
	obj.stopSound(SOUND_ID_MAGE_AVATAR); 
	sq_SetCustomDamageType(obj, false, 0);
	appendage.setValid(false);
	return;
}
