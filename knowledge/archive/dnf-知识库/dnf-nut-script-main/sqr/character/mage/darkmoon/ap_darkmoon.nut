 
function sq_AddFunctionName(appendage) {
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_darkmoon")
	appendage.sq_AddFunctionName("proc", "proc_appendage_darkmoon")
	appendage.sq_AddFunctionName("onSetHp", "onSetHp_appendage_darkmoon")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_darkmoon")
}

function sq_AddEffect(appendage)
{
	if(!appendage) {
		return;
	}
}

function onStart_appendage_darkmoon(appendage)
{
	if(!appendage) return;

	local currTime = appendage.getTimer().Get();
	appendage.getVar("actChrTime").setInt(0,currTime);
}

function proc_appendage_darkmoon(appendage) {
	if (!appendage) return;
	local obj = appendage.getParent();
	local maxhp = appendage.getVar("hpMax").get_vector(0);
	if(maxhp<1)
	{
		appendage.setValid(false);
	}
	local currTime = appendage.getTimer().Get();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	if (sqrChr && currTime - appendage.getVar("actChrTime").getInt(0) > 1000)
	{
		appendage.getVar("actChrTime").setInt(0,currTime);
		local objectManager = sqrChr.getObjectManager();
		local skillLevel = sq_GetSkillLevel(sqrChr, 148);
		local time = sq_GetLevelData(sqrChr, 148, 0, skillLevel);
		for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
		{
			local object = objectManager.getCollisionObject(i);

			if (object && !sqrChr.isEnemy(object) && object.isObjectType(OBJECTTYPE_MONSTER) && !isSameObject(sqrChr, object) && object.isMyControlObject())
			{
				try
				{
					object = sq_GetCNRDObjectToActiveObject(object);
				}
				catch(ex)
				{
				}
				local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, sqrChr, 148, false, "character/mage/darkmoon/ap_darkmoon_monster.nut", true);
				appendage.sq_SetValidTime(time);
				appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, ENUM_CHARACTERJOB_MAGE, 148, skillLevel);
				CNSquirrelAppendage.sq_AppendAppendageID(appendage, object, sqrChr, 148, true);
				appendage.setEnableIsBuff(true);
			}
		}
	}
	
	if(sqrChr)
	{
		if(sqrChr.getCurrentSkillIndex() == 49)
		{
			appendage.setValid(false);
		}
		sqrChr.setSkillCommandEnable(148,false);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_SLOW);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_FREEZE);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_POISON);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_STUN);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_CURSE);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_BLIND);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_LIGHTNING);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_STONE);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_SLEEP);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_BURN);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_WEAPON_BREAK);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_BLEEDING);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_HASTE);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_BLESS);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_ELEMENT);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_CONFUSE);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_HOLD);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_ARMOR_BREAK);
	}
}

function onSetHp_appendage_darkmoon(appendage, hp, attacker)
{
	if(!appendage)
		return hp;
	
	local obj = appendage.getParent();
	
	if(!obj)
		return hp;
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	
	if(!sqrChr)
		return hp;
		
	if(!sqrChr.isMyControlObject()){
		appendage.setValid(false);
		return hp;
	}
	
	local org_hp =hp;
    	local maxhp = appendage.getVar("hpMax").get_vector(0);
	if(attacker)
	{
		local attackInfo = sq_GetCurrentAttackInfo(attacker);
		if(attackInfo)
		{
			if(attackInfo.isIgnoreDieHard_)
				return hp;
		}
	}
	
	local nowHp = sqrChr.getHp();
	if(maxhp>0 && hp < nowHp){
		local hpDown = nowHp - hp;
		maxhp = maxhp - hpDown;
		if(maxhp>0){
			appendage.getVar("hpMax").set_vector(0, maxhp); 
		}
		else	{
			appendage.getVar("hpMax").set_vector(0, 0); 
		}
		return nowHp;
	}
	
	return org_hp;
}

function onEnd_appendage_darkmoon(appendage)
{
	if(!appendage) {
		return;
	}
 
	local obj = appendage.getParent();
	if(!obj) {
		return;
	}
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	 if(!sqrChr)
		return;
	sqrChr.setSkillCommandEnable(148,true);
} ;
