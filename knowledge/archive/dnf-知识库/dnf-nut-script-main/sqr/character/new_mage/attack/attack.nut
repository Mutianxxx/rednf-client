function onAfterSetState_ATTACKMAGE(obj, state, datas, isResetTimer) {
	if (!obj) return false;
	local animation = null;
	local attackIndex = obj.getAttackIndex();
	if (obj.sq_GetState() == STATE_ATTACK && isZFAwakeing(obj)) {
		switch (attackIndex) {
		case 0:
			animation = obj.getVar().GetAnimationMap("atk1", "character/mage/animation/ani_als/avatar_job/attack1.ani");
			break;
		case 1:
			animation = obj.getVar().GetAnimationMap("atk2", "character/mage/animation/ani_als/avatar_job/attack2.ani");
			break;
		case 2:
			animation = obj.getVar().GetAnimationMap("atk3", "character/mage/animation/ani_als/avatar_job/attack3.ani");
			break;
		}
	}
	else if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut") == true) {
		switch (attackIndex) {
		case 0:
			animation = setCurrentAnimation_avatar_eff(obj, "BattleMageAttack1", true);
			break;
		case 1:
			animation = setCurrentAnimation_avatar_eff(obj, "BattleMageAttack2", true);
			break;
		case 2:
			animation = setCurrentAnimation_avatar_eff(obj, "BattleMageAttack3", true);
			break;
		}

	}
	if (animation != null) obj.setCurrentAnimation(ani);

}