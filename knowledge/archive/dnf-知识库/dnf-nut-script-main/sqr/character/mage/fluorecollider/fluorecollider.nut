function onProcCon_mage_MageAntigravitystarter(obj) {
	if (!obj) return;
	sq_SetKeyxEnable(obj, E_JUMP_COMMAND, true);
	if (sq_IsEnterCommand(obj, E_JUMP_COMMAND)) {
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(4);
		obj.sq_IntVectPush(0);
		obj.sq_IntVectPush(0);
		obj.sq_IntVectPush(0);
		obj.sq_IntVectPush(20);
		obj.sq_AddSetStatePacket(4, STATE_PRIORITY_USER, true);
	}
};