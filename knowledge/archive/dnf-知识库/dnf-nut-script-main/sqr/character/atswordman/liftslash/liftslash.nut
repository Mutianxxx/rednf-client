

function checkExecutableSkill_Liftslash(obj)
{
	if (!obj) return false
	local state = obj.sq_GetState();
	local movekey = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL)||sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);
	local chainslash = sq_GetSkill ( obj,32 );
	if(state && movekey&&!chainslash.isInCoolTime() && (sq_GetSkillLevel(obj, 32)>0) ){
		return false;
	}
	local CQ7x8Sz5M2HajM6kGDLj = obj.sq_IsUseSkill(86)
	if (CQ7x8Sz5M2HajM6kGDLj)
	{
		CheckUseAddloadDrawsword(obj,143,{[0] = true,[108] = true,[14] = true},0)
		obj.sq_IntVectClear()
		obj.sq_IntVectPush(0)
		obj.sq_AddSetStatePacket(86, STATE_PRIORITY_IGNORE_FORCE, true)
		return true
	}
	return false
}

function checkCommandEnable_Liftslash(obj)
{
	if (!obj) return false;
	if(obj.getZPos() > 10) return false;
	return CheckForceDrawsword(obj,143,{[0] = true,[108] = true,[14] = true})
}

function onSetState_Liftslash(obj, CQ9JLwyjgMrjfPjUg, CQtsQPxJtv566khYTyF, CQBr4NXo5upV1BhQ)
{
	if(!obj) return;
	local CQvYpganUBgG7wgnuv = obj.sq_GetVectorData(CQtsQPxJtv566khYTyF, 0);
	obj.setSkillSubState(CQvYpganUBgG7wgnuv);
	switch(CQvYpganUBgG7wgnuv)
	{
		case 0:
			obj.sq_StopMove();
			obj.sq_SetMoveDirection(obj.getDirection(), ENUM_DIRECTION_NEUTRAL);
			obj.sq_SetStaticMoveInfo(0, 150, 150, false);
			BodyMagicSword(obj, "LiftSlash");
			if(MagicSword_IsAppebd(obj))
				obj.sq_SetCurrentAnimation(218);
			else
			{
				if(sq_GetSkillLevel(obj, 148) > 0)
				{
					BodyCalldaimus(obj, "LiftSlash")
					obj.sq_SetCurrentAnimation(392)
				}
				else
					obj.sq_SetCurrentAnimation(6);
			}
			obj.sq_SetCurrentAttackInfo(5);
			local CQDR3qU1ScSa21RraDNl = obj.sq_GetBonusRateWithPassive(86, -1, 0, getATSwordmanBonus(obj,1.0,86));
			obj.sq_SetCurrentAttackBonusRate(CQDR3qU1ScSa21RraDNl);
			sq_SetCurrentAttacknUpForce(sq_GetCurrentAttackInfo(obj),sq_GetLevelData(obj,86, 2, sq_GetSkillLevel(obj, 86)));
			break;
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}


function onAttack_Liftslash(CQR2psfDTWxrVORqP, CQiKhCCboCLyKjfbFum, CQ1IGfsf9zqUBSde, CQUWbnkVws1TLQdU7b)
{
	if(!CQR2psfDTWxrVORqP) return false;
	local CQHvNE1tHLy9GN9WfDpX = CQR2psfDTWxrVORqP.getSkillSubState();
	switch(CQHvNE1tHLy9GN9WfDpX)
	{
		case 0:
			MagicSword_BasiconAttack(CQR2psfDTWxrVORqP, CQiKhCCboCLyKjfbFum, CQ1IGfsf9zqUBSde, CQUWbnkVws1TLQdU7b);
		break;
	}

}
function onEndCurrentAni_Liftslash(CQjgyZScYT8MXe8Qk)
{
	if(!CQjgyZScYT8MXe8Qk) return;
	local CQE3d8r8IEIJHgzueS6 = CQjgyZScYT8MXe8Qk.getSkillSubState()
	switch(CQE3d8r8IEIJHgzueS6)
	{
		case 0:
			CQjgyZScYT8MXe8Qk.sq_IntVectClear();
			CQjgyZScYT8MXe8Qk.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
	}
}
