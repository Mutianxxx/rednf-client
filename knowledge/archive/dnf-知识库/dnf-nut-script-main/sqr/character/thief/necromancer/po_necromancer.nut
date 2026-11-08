function setCustomData_po_Necromancer(obj, receiveData)
{
	if(!obj)
		return;

	local id = receiveData.readDword();
	local tarid = receiveData.readDword();
	
	obj.getVar("id").clear_vector();
    obj.getVar("id").push_vector(id);
	
	local thief = obj.getTopCharacter();
	if (!thief)
		return;

	if (id == 0)
    {
		local ani = obj.getVar().GetAnimationMap("0", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/cocoonsmallstart_07.ani");
		obj.setCurrentAnimation(ani);
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
	}
	if (id == 1)
    {
		local ani = obj.getVar().GetAnimationMap("1", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/cocoonsmallloop_00.ani");
		obj.setCurrentAnimation(ani);
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
		
		obj.setTimeEvent(1, 1280, 0, false);
		
		obj.getVar("COU_End").clear_obj_vector();
		createCoconOfUndead_RangeLoopBottom(obj, 0, 0, 0);
		createCoconOfUndead_CoCoonLoopBottom(obj, 0, 0, 0);
	}
	
	if (id == 2)
    {
		local ani = obj.getVar().GetAnimationMap("2", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/cocoonmediumstart_07.ani");
		obj.setCurrentAnimation(ani);
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
		
		obj.getVar("COU_End").clear_obj_vector();
		createCoconOfUndead_RangeLoopBottom(obj, 0, 0, 0);
		createCoconOfUndead_CoCoonLoopBottom(obj, 0, 0, 0);
	}
	if (id == 3)
    {
		local ani = obj.getVar().GetAnimationMap("3", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/cocoonmediumloop_00.ani");
		obj.setCurrentAnimation(ani);
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
		
		obj.setTimeEvent(1, 1280, 0, false);
		
		obj.getVar("COU_End").clear_obj_vector();
		createCoconOfUndead_RangeLoopBottom(obj, 0, 0, 0);
		createCoconOfUndead_CoCoonLoopBottom(obj, 0, 0, 0);
	}
	
	
	if (id == 4)
    {
		local ani = obj.getVar().GetAnimationMap("4", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/cocoonlargestart_07.ani");
		obj.setCurrentAnimation(ani);
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
		
		obj.getVar("COU_End").clear_obj_vector();
		createCoconOfUndead_RangeLoopBottom(obj, 0, 0, 0);
		createCoconOfUndead_CoCoonLoopBottom(obj, 0, 0, 0);
	}
	if (id == 5)
    {
		local ani = obj.getVar().GetAnimationMap("5", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/cocoonlargeloop_00.ani");
		obj.setCurrentAnimation(ani);
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
		
		obj.setTimeEvent(1, 1280, 0, false);
		
		obj.getVar("COU_End").clear_obj_vector();
		createCoconOfUndead_RangeLoopBottom(obj, 0, 0, 0);
		createCoconOfUndead_CoCoonLoopBottom(obj, 0, 0, 0);
	}
	if (id == 6)
    {
		local attackBonusRate = receiveData.readDword();
		
		local ani = obj.getVar().GetAnimationMap("6", "passiveobject/actionobject/new/thief/necromancer/animation/cocoonofundead/cocoonexplosion_09.ani");
		obj.setCurrentAnimation(ani);
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
		
		local attackInfo = sq_GetCustomAttackInfo(obj, 1);
		sq_SetCurrentAttackInfo(obj, attackInfo);
		
		local attackInfo = sq_GetCurrentAttackInfo(obj, attackInfo);
		sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
		
		local skill = sq_GetSkill(thief, SKILL_COCONOFUNDEAD);
		local skillLevel = sq_GetSkillLevel(thief, SKILL_COCONOFUNDEAD);
		attackBonusRate = sq_GetBonusRateWithPassive(thief, SKILL_COCONOFUNDEAD, STATE_COCONOFUNDEAD, 1, 1.0);
		sq_SetCurrentAttackBonusRate(sq_GetCurrentAttackInfo(obj), attackBonusRate);
	}
}	

function onTimeEvent_po_Necromancer(obj, timeEventIndex, timeEventCount)
{
	if (obj.getVar("id").get_vector(0) == 1)
	{	
		if (timeEventIndex == 1)
		{
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(2);
			sq_SendCreatePassiveObjectPacketPos(obj, 24336, 0, obj.getXPos(), obj.getYPos(), obj.getZPos());
			sq_SendDestroyPacketPassiveObject(obj);
			setVliadEffectCoconOfUndeadPassiveobject(obj);
		}
	}
	if (obj.getVar("id").get_vector(0) == 3)
	{	
		if (timeEventIndex == 1)
		{
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(4);
			sq_SendCreatePassiveObjectPacketPos(obj, 24336, 0, obj.getXPos(), obj.getYPos(), obj.getZPos());
			sq_SendDestroyPacketPassiveObject(obj);
			setVliadEffectCoconOfUndeadPassiveobject(obj);
		}
	}
	if (obj.getVar("id").get_vector(0) == 5)
	{	
		if (timeEventIndex == 1)
		{
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(6);
			sq_SendCreatePassiveObjectPacketPos(obj, 24336, 0, obj.getXPos(), obj.getYPos(), obj.getZPos());
			sq_SendDestroyPacketPassiveObject(obj);
			
			setVliadEffectCoconOfUndeadPassiveobject(obj);
		}
	}
}

function onEndCurrentAni_po_Necromancer(obj)
{
	local id = obj.getVar("id").get_vector(0);
	
	if (obj.getVar("id").get_vector(0) == 0)
    {
		setVliadEffectCoconOfUndeadPassiveobject(obj);
		sq_SendDestroyPacketPassiveObject(obj);
	}
	if (obj.getVar("id").get_vector(0) == 2)
    {
		setVliadEffectCoconOfUndeadPassiveobject(obj);
		sq_SendDestroyPacketPassiveObject(obj);
	}
	if (obj.getVar("id").get_vector(0) == 4)
    {
		setVliadEffectCoconOfUndeadPassiveobject(obj);
		sq_SendDestroyPacketPassiveObject(obj);
	}
	if (obj.getVar("id").get_vector(0) == 6)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}
	if (obj.getVar("id").get_vector(0) == 7)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}
	if (obj.getVar("id").get_vector(0) == 8)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}
	if (obj.getVar("id").get_vector(0) == 9)
    {
		sq_SendDestroyPacketPassiveObject(obj);
	}
}

function onKeyFrameFlag_po_Necromancer(obj,flagIndex)
{
	local id = obj.getVar("id").get_vector(0);
	
	if (obj.getVar("id").get_vector(0) == 0)
	{
		if (flagIndex == 0)	
		{
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(1);
			sq_SendCreatePassiveObjectPacketPos(obj, 24336, 0, obj.getXPos(), obj.getYPos(), obj.getZPos());
		}
	}
	if (obj.getVar("id").get_vector(0) == 2)
	{
		if (flagIndex == 0)	
		{
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(3);
			sq_SendCreatePassiveObjectPacketPos(obj, 24336, 0, obj.getXPos(), obj.getYPos(), obj.getZPos());
		}
	}
	if (obj.getVar("id").get_vector(0) == 4)
	{
		if (flagIndex == 0)	
		{
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(5);
			sq_SendCreatePassiveObjectPacketPos(obj, 24336, 0, obj.getXPos(), obj.getYPos(), obj.getZPos());
		}
	}
	return true;
}
