function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_talismanofoppression")
	appendage.sq_AddFunctionName("proc", "proc_appendage_talismanofoppression")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_talismanofoppression")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_talismanofoppression")
}

function drawAppend_appendage_talismanofoppression(appendage, isOver, x, y, isFlip)
{
	if(!appendage) {
		return;
	}
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	
	if(isOver) 
	{
		local ani = appendage.getVar().GetAnimationMap("talismanofoppression", "character/priest/effect/animation/attalismanofoppression/attalismanofoppression_hold_talisman.ani");
		sq_AnimationProc(ani);
		sq_drawCurrentFrame(ani, x, y - sq_GetObjectHeight(parentObj)/2, isFlip);
	}
}

function onStart_appendage_talismanofoppression(appendage)
{
	if (!appendage) return;
	local UncleBangValue1 = appendage.getParent();
	local UncleBangValue2 = appendage.getSource();
	local UncleBangValue2 = sq_GetCNRDObjectToSQRCharacter(UncleBangValue2);
	if (!UncleBangValue2 || !UncleBangValue1)
	{
		appendage.setValid(false);
		return;
	}
	sq_SetCustomDamageType(UncleBangValue1, true, 1);
	sq_SetGrabable(UncleBangValue1, false);
	UncleBangValue1.setCurrentDirection(sq_GetOppositeDirection(UncleBangValue2.getDirection()));
	if (sq_IsValidActiveStatus(UncleBangValue1, ACTIVESTATUS_STUN))
	{
		UncleBangValue1.setEnableChangeState(false);
		sq_IsSetActiveStatus(UncleBangValue1, ACTIVESTATUS_STUN, 0.0);
		UncleBangValue1.setEnableChangeState(true);
	}
}

function proc_appendage_talismanofoppression(appendage)

{

	if (!appendage) return;

	local UncleBangValue1 = appendage.getParent();

	local UncleBangValue2 = appendage.getSource();

	local UncleBangValue2 = sq_GetCNRDObjectToSQRCharacter(UncleBangValue2);

	if (!UncleBangValue2 || !UncleBangValue1 || UncleBangValue1.isDead())

	{

		appendage.setValid(false);

		return;

	}

	if (UncleBangValue1.isMyControlObject() && !UncleBangValue1.isDead())

	{

		local UncleBangValue4 = sq_GetGlobalIntVector();

		sq_IntVectorClear(UncleBangValue4);

		sq_IntVectorPush(UncleBangValue4, Z_ACCEL_TYPE_CONST);

		UncleBangValue1.addSetStatePacket(STATE_HOLD, UncleBangValue4, STATE_PRIORITY_FORCE, false, "");

		UncleBangValue1.flushSetStatePacket();

	}

}

function onEnd_appendage_talismanofoppression(appendage)

{

	if (!appendage) return;

	local UncleBangValue1 = appendage.getParent();

	local UncleBangValue2 = appendage.getSource();

	local UncleBangValue2 = sq_GetCNRDObjectToSQRCharacter(UncleBangValue2);

	if (!UncleBangValue2 || !UncleBangValue1)

	{

		appendage.setValid(false);

		return;

	}

	sq_SetCustomDamageType(UncleBangValue1, false, 0);

	sq_SetGrabable(UncleBangValue1, true);

	if (UncleBangValue1.isMyControlObject() && UncleBangValue1.getState() == STATE_HOLD)

	{

		appendage.setValid(false);

		sq_AddSetStatePacketActiveObject(UncleBangValue1, STATE_STAND, sq_GetGlobalIntVector(), STATE_PRIORITY_FORCE);

	}
	appendage.sq_DeleteAppendages();

}