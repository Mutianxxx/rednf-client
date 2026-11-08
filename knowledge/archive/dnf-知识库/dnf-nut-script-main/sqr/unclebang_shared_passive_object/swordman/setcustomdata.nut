











function setCustomData_po_swordman_shared(obj, receiveData)
{
	if(!obj) return;

	local id = receiveData.readDword();
	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	obj.getVar("id").clear_vector();
	obj.getVar("id").push_vector(id);
	local parentChr = sq_ObjectToSQRCharacter(obj.getTopCharacter());
	switch(id)
	{

		case 24:
			local ani = obj.getCustomAnimation(33);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 18);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 13, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);
		break;
		case 25:
			obj.sendStateOnlyPacket(10);
			obj.flushSetStatePacket();
		break;
		case 26:
			local ani = obj.getCustomAnimation(40);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 23);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 18, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);
		break;
		case 27:
			sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
			local ani = obj.getCustomAnimation(46);
			obj.setCurrentAnimation(ani);

			local attackInfo = sq_GetCustomAttackInfo(obj, 21);
			sq_SetCurrentAttackInfo(obj, attackInfo);

			local pAttack = sq_GetCurrentAttackInfo(obj);
			local damage = parentChr.sq_GetBonusRateWithPassive(241, -1, 16, 1.0);
			sq_SetCurrentAttackBonusRate(pAttack, damage);

			obj.setTimeEvent(0, 500, 0, false);
			obj.setTimeEvent(1, 3000, 0, false);
		break;
	}
}