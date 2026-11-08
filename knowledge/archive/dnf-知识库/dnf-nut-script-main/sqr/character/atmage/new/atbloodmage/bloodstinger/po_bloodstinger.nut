
// setCustomData
function setCustomData_po_ATBloodStinger(obj, receiveData)
{
	if(!obj)
		return;

	local attackBonusRate = receiveData.readDword();
	local attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

	local ani1 = sq_CreateAnimation("","passiveobject/character/mage/Animation/ATBloodStinger/ATBloodStingeBack_07.ani");
	local ani2 = sq_CreateAnimation("","passiveobject/character/mage/Animation/ATBloodStinger/ATBloodStingeBottom_01.ani");

}

function onEndCurrentAni_po_ATBloodStinger(obj)
{
	if(!obj)
		return;
		
	if(obj.isMyControlObject())
	{
		sq_SendDestroyPacketPassiveObject(obj);
		deleteAllApObj_ATBloodStinger(obj);
	}
}

function onAttack_po_ATBloodStinger(obj, damager, boundingBox, isStuck)
{
	if (!obj||!damager) return 0;

	if (!damager || !damager.isObjectType(OBJECTTYPE_ACTIVE) || CNSquirrelAppendage.sq_IsAppendAppendage(damager, "Character/atmage/new/atbloodmage/bloodstinger/ap_bloodstinger.nut")) return;

	if (sq_IsGrabable(obj, damager) && !sq_IsFixture(damager))//判斷對象可以被抓去且不是固定狀態
	{
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BLOODSTINGER, false, "Character/atmage/new/atbloodmage/bloodstinger/ap_bloodstinger.nut", true);

		sq_MoveToAppendage(damager, obj, obj, 300, 0, 0, 0, true, appendage);
	}
	obj.getVar().push_obj_vector(damager);//加入
}

function deleteAllApObj_ATBloodStinger(obj)
{
    local count = obj.getVar().get_obj_vector_size();
    for (local i = 0; i < count; i++)
    {
        local object = obj.getVar().get_obj_vector(i);
        if (object)
        {
            local dieHardAppendage = CNSquirrelAppendage.sq_GetAppendage(object, "Character/atmage/new/atbloodmage/bloodstinger/ap_bloodstinger.nut");
            if (dieHardAppendage)
            {
                dieHardAppendage.setValid(false);
            }
            sq_SimpleMoveToNearMovablePos(obj, 200);
        }
    }
    obj.getVar().clear_obj_vector();
}