 
function onAfterSetState_newwalkshoot(obj, state, datas, isResetTimer) {
	if(!obj) return;
	obj.getVar("newwalkshoot").clear_obj_vector();
	obj.getVar("flag").clear_vector();
	obj.getVar("flag").push_vector(0);
}

function onCreateObject_newwalkshoot(obj, createObject) {
	if(!obj) return;
	if (sq_GetSkillLevel(obj, 64) < 1 || sq_GetSkill(obj, 64).isSealFunction())
		return;
	if (createObject.isObjectType(OBJECTTYPE_PASSIVE)) {
		local createObject = sq_GetCNRDObjectToCollisionObject(createObject);
		local cuid = createObject.getCollisionObjectIndex();
		if (cuid == 22001) {
			local count = obj.getVar("flag").get_vector(0);
			local countflag = count % 2;
			obj.getVar("flag").set_vector(0, count + 1);
			if(countflag == 1){
				local ani = sq_AddDrawOnlyAniFromParent(obj,"passiveobject/character/gunner/animation/twingunblade/gunshoot.ani", 75, 1, 112);
				newWalkshootAniResizeing(obj,ani);
			}
			else{
				local ani = sq_AddDrawOnlyAniFromParent(obj,"passiveobject/character/gunner/animation/twingunblade/gunshoot.ani", 81, 2, 87);
				newWalkshootAniResizeing(obj,ani);
			}
			obj.getVar("newwalkshoot").push_obj_vector(createObject);
			obj.sq_PlaySound("R_TWINGUN_GUN"); 
		}
	}
}

function onProc_newwalkshoot(obj) {
	if (!obj) return;
	local skillLevel = obj.sq_GetSkillLevel(64);
	if (skillLevel < 1 || sq_GetSkill(obj, 64).isSealFunction())
		return;
	local Count = obj.getMyPassiveObjectCount(22001);
	for (local i = 0; i < Count; ++i) {
		local object = obj.getMyPassiveObject(22001, i);
		local objecttt = obj.getVar("newwalkshoot").is_obj_vector(object);
		if (object && objecttt) {
			local dir = object.getDirection()
			if(dir == ENUM_DIRECTION_RIGHT){
				sq_SetVelocity(object, 0, -800.0);
			}
			else{
				sq_SetVelocity(object, 0, 800.0);
			}
			setCurrentAnimationFromCutomIndex(object, 16);
			local size = sq_GetIntData(obj, 64, 6);
			local imageRate = size.tofloat()/100.0;
			local ani = sq_GetCurrentAnimation(object);
			ani.setImageRateFromOriginal(imageRate, imageRate);
			ani.setAutoLayerWorkAnimationAddSizeRate(imageRate);
			sq_SetAttackBoundingBoxSizeRate(ani, imageRate, imageRate, imageRate);
			
			local attackBonusRate = obj.sq_GetBonusRateWithPassive(15, -1, 0, 1.0);
			local attackInfo = sq_GetCurrentAttackInfo(object);
			sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
			local bleedProb = sq_GetLevelData(obj, 64, 4, skillLevel)/10;
			local bleedLevel = sq_GetLevelData(obj, 64, 5, skillLevel);
			local bleedTime = sq_GetLevelData(obj, 64, 7, skillLevel);
			local bleedPower = obj.sq_GetPowerWithPassive(64, -1, 6, -1, 1.0);
			sq_SetChangeStatusIntoAttackInfo(attackInfo, 0, ACTIVESTATUS_BLEEDING, bleedProb, bleedLevel, bleedTime,bleedPower);
		}
	}
}

function newWalkshootAniResizeing(parentObj, obj){
	if(!parentObj)
		return;
	local size = sq_GetIntData(parentObj, 64, 6);
	size = size.tofloat()/100.0;
	local ani = sq_GetCurrentAnimation(obj);
	if(ani)
		ani.resizeWithChild(size);
}
