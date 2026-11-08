 
function getMyMonsterObject_Character_jsqq506807329(obj, index, append) {
	if (!obj)
		return null;
	local objMan = obj.getObjectManager();
	for (local i = 0; i < objMan.getCollisionObjectNumber(); i++) {
		local object = objMan.getCollisionObject(i);
		if (object && object.isObjectType(OBJECTTYPE_MONSTER) && !obj.isEnemy(object) && object.getCollisionObjectIndex() == index) {
			local monObj = sq_GetCNRDObjectToActiveObject(object);
			if (monObj && !monObj.isDead()) {
				local appendage = CNSquirrelAppendage.sq_GetAppendage(monObj, append);
				if (!appendage)
					continue;
				if (isSameObject(obj, appendage.getVar("sqrChr").get_obj_vector(0)))
					return monObj;
			}
		}
	}
	return null;
}

function getMyControlMonsterObject_Character(obj, index, num) {
	if (!obj)
		return null;
	local objMan = obj.getObjectManager();
	for (local i = 0; i < objMan.getCollisionObjectNumber(); i++) {
		local object = objMan.getCollisionObject(i);
		if (object && object.isObjectType(OBJECTTYPE_MONSTER) && !obj.isEnemy(object) && object.getCollisionObjectIndex() == index) {
			local monObj = sq_GetCNRDObjectToActiveObject(object);
			if (monObj && !monObj.isDead() && monObj.isMyControlObject()) {
				if(num > 1){
					num = num - 1;
				}
				else{
					return monObj;
				}
			}
		}
	}
	return null;
}