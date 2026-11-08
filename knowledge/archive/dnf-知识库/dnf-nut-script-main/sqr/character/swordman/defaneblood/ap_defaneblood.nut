
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_defaneblood")
	appendage.sq_AddFunctionName("onDamageParent", "onDamageParent_appendage_defaneblood")	
	//appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_defaneblood")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_defaneblood")
	appendage.sq_AddFunctionName("onSetHp", "onSetHp_appendage_defaneblood")
}

function sq_AddEffect(appendage)
{
	if(!appendage) {
		return;
	}
}


function drawAppend_appendage_defaneblood(appendage, isOver, x, y, isFlip)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	
	
 	local ani = appendage.getVar().GetAnimationMap("defaneblood", "character/swordman/animation/berserk/berserk.ani");
	if(ani&&isOver) 
	{
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y, isFlip);
	}
}

/*function getImmuneTypeDamageRate_appendage_defaneblood(appendage, damageRate, attacker)
{

	local parentObj = appendage.getParent();	
	parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if(!parentObj.isMyControlObject()){
		appendage.setValid(false);
		return;
	}
    	local hp = appendage.getVar("hpMax").get_vector(0);

   	local subHp = hp * parentObj.getHpMax() / 100;

	if (parentObj.getHp() -  damageRate <= 1){
		parentObj.setHp(10, null, true);
		return 0;
	}
	if (subHp >= parentObj.getHp()){
		appendage.getVar("hpMax").setBool(0,true);
		subHp = subHp.tointeger();
		parentObj.setHp(subHp, null, true);
		return 0;
	}else{
		appendage.getVar("hpMax").setBool(0,false);
		if (parentObj.getHp() -  damageRate <= 1){
			subHp = subHp.tointeger();
			parentObj.setHp(subHp, null, true);
			return 0;
		}

	}
	return damageRate;
//    if (damageRate > 0 && hp - damageRate >= 0)
//    {
//        appendage.getVar("hpMax").set_vector(0,hp - damageRate);
//        damageRate = 0;
//    }
//        return damageRate;
}*/


function onDamageParent_appendage_defaneblood(appendage ,attacker, boundingBox, isStuck) 
{
	local parentObj = appendage.getParent();	
	
	if (!parentObj) {
		appendage.setValid(false);
		return;
	}
	 if(appendage.getVar("hpMax").getBool(0)){
 		createFrontDefaneBlood(parentObj);
		//parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
		//local hp = appendage.getVar("hpMax").get_vector(0);
		//local subHp = hp * parentObj.getHpMax() / 100;
		//subHp = subHp.tointeger();
		//parentObj.setHp(subHp, null, true);
 	}
}

function proc_appendage_defaneblood(appendage)
{
	if(!appendage) {
		return;		
	}
	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	local value0 = 0;
	local value1 = 0;
	if(appendage.getVar("hpMax").getBool(0)){
		value0 = 1000;
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_LIGHTNING);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_STONE);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_POISON);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_BURN);
		sq_ReleaseActiveStatus(sqrChr, ACTIVESTATUS_BLEEDING);
	}
	local change_appendage = appendage.sq_getChangeStatus("defaneblood");
	if(!change_appendage)
	{
		change_appendage = appendage.sq_AddChangeStatus("defaneblood",obj, obj, 0, 0, true, 0);
	}
	if(change_appendage){
		change_appendage.clearParameter();
		change_appendage.addParameter(CHANGE_STATUS_TYPE_ACTIVESTATUS_TOLERANCE_ALL, false, value0.tofloat());
		change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_DEFENSE, false, value1.tofloat());
	}

}

function onSetHp_appendage_defaneblood(appendage, hp, attacker)
{
	if(!appendage)
		return hp;
	
	local obj = appendage.getParent();
	
	if(!obj)
		return hp;
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	if(!sqrChr.isMyControlObject()){
		appendage.setValid(false);
		return;
	}
	local org_hp =hp;
    	local defanehp = appendage.getVar("hpMax").get_vector(0);
   	local subHp = defanehp * sqrChr.getHpMax() / 100;
   	
	if (hp <= subHp)
	{
		if(attacker)
		{
			local attackInfo = sq_GetCurrentAttackInfo(attacker);
			
			if(attackInfo)
			{
				if(attackInfo.isIgnoreDieHard_)
					return hp;
			}
		}

		local isRelayTimeOut = sq_isSendTimeOutPacket(); 

		if (isRelayTimeOut)
			return hp;
		
		if(!sqrChr)
			return hp;
		
		if(!sq_IsInBattle())
		{ 
			return hp;
		}
		appendage.getVar("hpMax").setBool(0,true);
		org_hp = subHp.tointeger(); 
	}else{
		appendage.getVar("hpMax").setBool(0,false);
	}
	return org_hp;
}