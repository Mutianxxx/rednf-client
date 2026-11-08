function setCustomData_po_fluorecollider(obj, receiveData)
{
	if(!obj)
		return;
	local liRate	  = receiveData.readDword();
	local liLevel	  = 90;
	local liTime	  = 1000;	
	local parentChr = obj.getTopCharacter();
	local attackInfo = sq_GetCustomAttackInfo(obj, 0);//קוüש

	sq_SetCurrentAttackInfo(obj, attackInfo);//Êַßה
	local pAttack = sq_GetCurrentAttackInfo(obj);		
	local level = sq_GetSkillLevel(parentChr, 105);
	local attackBonusLow =  sq_GetLevelData(parentChr, 105, 0, level);
	local attackBonus =  sq_GetLevelData(parentChr, 105, 1, level);
	local attackBonusRate = attackBonus;
	sq_SetCurrentAttackBonusRate(pAttack, attackBonusRate.tointeger());
	local attackInfo = sq_GetCurrentAttackInfo(obj, 0);
	if (!attackInfo) return;
		sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, ACTIVESTATUS_LIGHTNING,liRate, liLevel, liTime);		
}

function procAppend_po_fluorecollider(obj)
{

	if(!obj) return;
	if(!obj.isMyControlObject())
	  return;
	if(!obj) return;
	if(!obj.isMyControlObject())return;



}

function onTimeEvent_po_fluorecollider(obj, timeEventIndex, timeEventCount)
{		
	if(!obj)
		return false;
	return false;	
} 

