function onAfterSetState_mage_attack(obj, state, datas, isResetTimer) {
	if (!obj) return;
	local index = obj.getAttackIndex();
	if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		local ani = null;
		switch (index) {
		case 0:
			ani = setCurrentAnimation_avatar_eff(obj, "BattleMageAttack1", true);
			break;
		case 1:
			ani = setCurrentAnimation_avatar_eff(obj, "BattleMageAttack2", true);
			break;
		case 2:
			ani = setCurrentAnimation_avatar_eff(obj, "BattleMageAttack3", true);
			break;
		}
		if (ani != null) obj.setCurrentAnimation(ani);
	}
};