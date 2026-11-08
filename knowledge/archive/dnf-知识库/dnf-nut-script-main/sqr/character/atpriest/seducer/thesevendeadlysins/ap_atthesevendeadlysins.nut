function sq_AddFunctionName(appendage)
{
	//dofile("demoniclancer/cs.nut");
	appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_TheSevenDeadlySins")

}


function onAttackParent_appendage_TheSevenDeadlySins(appendage, realAttacker, damager, boundingBox, isStuck)
{
	if(!appendage) return
	local parentObj = appendage.getParent()
	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj)
	local colObj = sq_GetCNRDObjectToCollisionObject(realAttacker)
	local txobj = colObj.getCollisionObjectIndex()
	local id = colObj.getVar("id").get_vector(0)
	local ChrState = obj.getState();
	local ChrSubState = obj.getSkillSubState();
	if(txobj == 24384 && (id == 3 || id == 4 ))
		return
	atpriestthesevendeadlysins(obj)
}

function atpriestthesevendeadlysins(obj)
{
	local loadSlot = obj.sq_GetSkillLoad(SKILL_THESEVENDEADLYSINS);
	if(!loadSlot) return
	local zuidacishu = obj.sq_GetLevelData(SKILL_THESEVENDEADLYSINS, 0, sq_GetSkillLevel(obj, SKILL_THESEVENDEADLYSINS));
	local gailv = obj.sq_GetLevelData(SKILL_THESEVENDEADLYSINS, 1, sq_GetSkillLevel(obj, SKILL_THESEVENDEADLYSINS));
	local suij = sq_getRandom(0, 1000);
	local ChrState = obj.getState();
	if(suij > gailv)
		return
	local cishu = loadSlot.getRemainLoadNumber()
	if(cishu+1 <= zuidacishu)
		loadSlot.increaseLoadCount(1);
	return
}

function thesevendeadlysins(obj)
{
	local  loadSlot = obj.sq_GetSkillLoad(SKILL_THESEVENDEADLYSINS)
	if(!loadSlot) return
	local cishu = loadSlot.getRemainLoadNumber()
	if(cishu-1 >= 0)
	loadSlot.decreaseLoadCount(obj.sq_GetLevelData(SKILL_THESEVENDEADLYSINS, 0, sq_GetSkillLevel(obj, SKILL_THESEVENDEADLYSINS)))

return
}
