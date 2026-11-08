
function checkExecutableSkill_BuckShot(obj) {
	if (!obj) return false;
	local used = obj.sq_IsUseSkill(75);
	if (used) {
		obj.getVar("BuckShot_Boss").clear_vector();
		obj.getVar("BuckShot_Named").clear_vector();
		obj.getVar("BuckShot_Mons").clear_vector();
		BuckShot_FindEnermy(obj, sq_GetIntData(obj, 75, 1));
		obj.sq_StartWrite();
		obj.sq_WriteDword(75);
		obj.sq_WriteDword(0);
		obj.sq_WriteDword(sq_GetIntData(obj, 75, 3));
		obj.sq_WriteDword(obj.sq_GetLevelData(75, 0, sq_GetSkillLevel(obj, 75)));
		obj.sq_WriteDword(obj.sq_GetLevelData(75, 1, sq_GetSkillLevel(obj, 75)));
		obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(75, -1, 2, getATSwordmanBonus(obj, 1.0, 75)));
		obj.sq_WriteDword(sq_GetIntData(obj, 75, 13));
		obj.sq_SendCreatePassiveObjectPacket(24381, 0, -80, 0, 75);
	}
	return false;
}

function checkCommandEnable_BuckShot(obj) {
	if (!obj) return false;
	local load = obj.sq_GetSkillLoad(65);
	if (!load) return false;
	local count = load.getRemainLoadNumber();
	if (count < 1) return false;
	return true;
}

function BuckShot_FindEnermy(obj, data) {
	local object = obj.getObjectManager();
	for (local i = 0; i < object.getCollisionObjectNumber(); ++i) {
		local CQoPEZI2cOl3L3unNGXT = object.getCollisionObject(i);
		local CQ2yj8Tps7JZFtuch = sq_GetDistanceObject(obj, CQoPEZI2cOl3L3unNGXT, false);
		if (CQoPEZI2cOl3L3unNGXT && obj.isEnemy(CQoPEZI2cOl3L3unNGXT) && CQ2yj8Tps7JZFtuch <= data && CQoPEZI2cOl3L3unNGXT.isObjectType(OBJECTTYPE_ACTIVE) && CQoPEZI2cOl3L3unNGXT.isInDamagableState(obj) && IsFrontOf(obj, CQoPEZI2cOl3L3unNGXT)) {
			local CQmnGv2UgzUSO5yqlov = CQoPEZI2cOl3L3unNGXT.getZPos() + CQoPEZI2cOl3L3unNGXT.getObjectHeight() / 2;
			local CQJmnoD2tsNopDtb = "passiveobject/changqing_atswordman/Animation/ATBuckShot/BuckshotTarget_Eff_B.ani";
			DarktemplerCreateAniPooledObj(CQoPEZI2cOl3L3unNGXT, CQJmnoD2tsNopDtb, true, true, CQoPEZI2cOl3L3unNGXT.getXPos(), CQoPEZI2cOl3L3unNGXT.getYPos(), CQmnGv2UgzUSO5yqlov, 1.0);
			local CQkTMJtF54WQPztxmU = sq_GetObjectId(CQoPEZI2cOl3L3unNGXT);
			CQoPEZI2cOl3L3unNGXT = sq_GetCNRDObjectToMonster(CQoPEZI2cOl3L3unNGXT);
			if (sq_IsBoss(CQoPEZI2cOl3L3unNGXT)) obj.getVar("BuckShot_Boss").push_vector(CQkTMJtF54WQPztxmU);
			else {
				if (sq_IsNamed(CQoPEZI2cOl3L3unNGXT)) 
					obj.getVar("BuckShot_Named").push_vector(CQkTMJtF54WQPztxmU);
				else 
					obj.getVar("BuckShot_Mons").push_vector(CQkTMJtF54WQPztxmU);
			}
		}
	}
	return;
}