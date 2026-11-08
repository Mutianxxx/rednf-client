function sq_AddFunctionName(appendage) {
	appendage.sq_AddFunctionName("proc", "proc_appendage_darkmoon_monster")
	appendage.sq_AddFunctionName("onSetHp", "onSetHp_appendage_darkmoon_monster")
}

function proc_appendage_darkmoon_monster(appendage) {
	if (!appendage) return;
	local obj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local maxhp = 0;
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(sourceObj);
	if(sqrChr){
		local sourceApp = sqrChr.GetSquirrelAppendage("character/mage/darkmoon/ap_darkmoon.nut");
		if (!CNSquirrelAppendage.sq_IsAppendAppendage(sqrChr, "character/mage/darkmoon/ap_darkmoon.nut")){
			appendage.setValid(false);
			return;
		}
		if(sourceApp){
			maxhp = sourceApp.getVar("hpMax").get_vector(0);
		}else{
			appendage.setValid(false);
			return;
		}
	}
	if(maxhp<1)
	{
		appendage.setValid(false);
		return;
	}

	local pObj = sq_GetCNRDObjectToActiveObject(obj);
	if(!pObj.isMyControlObject()){
		appendage.setValid(false);
		return;
	}
	if(pObj)
	{
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_SLOW);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_FREEZE);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_POISON);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_STUN);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_CURSE);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_BLIND);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_LIGHTNING);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_STONE);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_SLEEP);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_BURN);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_WEAPON_BREAK);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_BLEEDING);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_HASTE);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_BLESS);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_ELEMENT);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_CONFUSE);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_HOLD);
		sq_ReleaseActiveStatus(pObj, ACTIVESTATUS_ARMOR_BREAK);
	}
}

function onSetHp_appendage_darkmoon_monster(appendage, hp, attacker)
{
	if(!appendage)
		return hp;
	
	local obj = appendage.getParent();
	if(!obj)
		return hp;
	if(!obj.isMyControlObject()){
		appendage.setValid(false);
		return hp;
	}
	local pObj = sq_GetCNRDObjectToActiveObject(obj);
	if(!pObj)
		return hp;
	
	local org_hp =hp;
	
	local sourceObj = appendage.getSource();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(sourceObj);
    	local maxhp = 0;
	if(!sqrChr)
		return hp;
	local sourceApp = sqrChr.GetSquirrelAppendage("character/mage/darkmoon/ap_darkmoon.nut");
	if(!sourceApp)
		return hp;
	local maxhp = sourceApp.getVar("hpMax").get_vector(0);
    	
	if(attacker)
	{
		local attackInfo = sq_GetCurrentAttackInfo(attacker);
		if(attackInfo)
		{
			if(attackInfo.isIgnoreDieHard_)
				return hp;
		}
	}
	
	local nowHp = pObj.getHp();
	if(maxhp>0 && hp < nowHp){
		local hpDown = nowHp - hp;
		maxhp = maxhp - hpDown;
		if(maxhp>0){
			sourceApp.getVar("hpMax").set_vector(0, maxhp); 
		}
		else	{
			sourceApp.getVar("hpMax").set_vector(0, 0); 
		}
		return nowHp;
	}
	
	return org_hp;
}