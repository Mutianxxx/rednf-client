
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_DOLL")
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_DOLL")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_DOLL")
	appendage.sq_AddFunctionName("onVaildTimeEnd", "onVaildTimeEnd_appendage_DOLL")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_DOLL")
	appendage.sq_AddFunctionName("onSetHp", "onSetHp_appendage_DOLL")
}


function onSetHp_appendage_DOLL(appendage, hp, attacker)
{
	if(!appendage)
		return hp;
	
	local obj = appendage.getParent();
	
	if(!obj)
		return hp;
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	if (hp <= 0)
	{
		if (getBobyNumber(sqrChr) >= 1){
			sqrChr.sq_AddSetStatePacket(STATE_DOWN, STATE_PRIORITY_IGNORE_FORCE, true);
			local maxHp = sqrChr.getHpMax();
			hp = maxHp.tointeger();
			//sqrChr.setHp(maxHp.tointeger(),null, true);
			setBobyNumber(sqrChr,getBobyNumber(sqrChr) - 1 );
		}else{
			playNoDollSound(sqrChr);
			appendage.setValid(false);
			return hp;
		}
	}
	return hp;
}

//function onStart_appendage_DOLL(appendage)
//{
	//appendage.sq_DeleteEffectFront();
	//appendage.sq_DeleteEffectBack();
	//appendage.sq_AddEffectFront("passiveobject/zrr_skill/newmage/animation/marionette/spotlight_00.ani");
	//appendage.sq_AddEffectBack("passiveobject/zrr_skill/newmage/animation/marionette/spotlightground_00.ani");
	//appendage.sq_AddEffectBack("character/mage/animation/ani_als/marionette/buff02_00.ani");
	//appendage.sq_AddEffectBack("character/mage/animation/ani_als/marionette/connectwirea_00.ani");

//}

function drawAppend_appendage_DOLL(appendage, isOver, x, y, isFlip) {
	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		//appendage.setValid(false);
		return;
	}

	local anif = appendage.getVar().GetAnimationMap("spotlightf", "passiveobject/zrr_skill/newmage/animation/marionette/spotlight_00.ani");
	local anib = appendage.getVar().GetAnimationMap("spotlightg", "passiveobject/zrr_skill/newmage/animation/marionette/spotlightground_00.ani");

	if (anif && isOver) {
		sq_AnimationProc(anif);
		sq_drawCurrentFrame(anif, x, y, isFlip);
	}
	else if (anib && !isOver) {
		sq_AnimationProc(anib);
		sq_drawCurrentFrame(anib, x, y, isFlip);
	}
}

function sq_AddEffect(appendage)
{

}

function getImmuneTypeDamageRate_appendage_DOLL(appendage, damageRate, attacker)
{
	local obj = appendage.getParent();

	if (obj.getHp() - damageRate <= 0 )
	{
		return 0;
	}
	else
	{
		return damageRate / 2;
	}
}

function proc_appendage_DOLL(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	if(!obj) 
	{
		//appendage.setValid(false);
		return;
	}

	local obj = sq_GetCNRDObjectToSQRCharacter(obj);
	
	obj.setSkillCommandEnable(92 ,false);
	obj.setSkillCommandEnable(14 ,false);
	obj.setSkillCommandEnable(17 ,false);
	obj.setSkillCommandEnable(16 ,false);
	obj.setSkillCommandEnable(15 ,false);
	obj.setSkillCommandEnable(18 ,false);
	obj.setSkillCommandEnable(11 ,false);
	obj.setSkillCommandEnable(65 ,false);
	obj.setSkillCommandEnable(80 ,false);
	obj.setSkillCommandEnable(25 ,false);
	
	obj.setSkillCommandEnable(4 ,false);
	obj.setSkillCommandEnable(28 ,false);
	obj.setSkillCommandEnable(20 ,false);
	obj.setSkillCommandEnable(43 ,false);
	obj.setSkillCommandEnable(57 ,false);
}



function onStart_appendage_DOLL(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	if(!obj) 
	{
		appendage.setValid(false);
		return;
	}
	obj = sq_GetCNRDObjectToSQRCharacter(obj);
	obj.sq_SetSoundTagCreatureCommand("WZ_CMDPET_EN");
	obj.sq_SetSoundTagLackMp("WZ_NOMANA_EN_MN");
	obj.sq_SetSoundTagCoolTime("WZ_COOLTIME_EN_MN");
	obj.sq_SetSoundTagDie("WZ_DIE_EN_MN");
}

function onEnd_appendage_DOLL(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	if(!obj) 
	{
		appendage.setValid(false);
		return;
	}
	if(!sq_IsInBattle()){
		appendage.setValid(false);
		return;
	}
	local pChr = sq_GetCNRDObjectToSQRCharacter(obj);
	pChr.sq_SetSoundTagCreatureCommand("WZ_CMDPET_EN");
	pChr.sq_SetSoundTagLackMp("WZ_NOMANA_EN");
	pChr.sq_SetSoundTagCoolTime("R_WZ_COOLTIME_EN");
	pChr.sq_SetSoundTagDie("R_WZ_DIE_EN");
	if (isDollState(pChr) ){
		appendage.setValid(false);
	}
	local jt = pChr.getMyPassiveObject(24347,0);
	if (jt)
	{
		jt.getVar("break").set_vector(0,1);
	}
}

function onVaildTimeEnd_appendage_DOLL(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	if(!obj)
	{
		appendage.setValid(false);
		return;
	}
	
	local pChr = sq_GetCNRDObjectToSQRCharacter(obj);
	 if (isDollState(pChr) ){
	 	appendage.setValid(false);
	 }
	 if(pChr.getHp() > 0){
		pChr.getVar("state").clear_vector();
		pChr.getVar("state").push_vector(3);
		pChr.sq_AddSetStatePacket(STATE_DOLL, STATE_PRIORITY_USER, true);
	}
}