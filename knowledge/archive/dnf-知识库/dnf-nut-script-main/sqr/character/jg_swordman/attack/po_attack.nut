
// setCustomData
function setCustomData_po_wavemarkattack_light_4(obj, receiveData)
{
	if(!obj)
		return;

	local attackBonusRate = receiveData.readDword();// ??????%)	

	local attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
}



function onEndCurrentAni_po_wavemarkattack_light_4(obj)
{
	if(!obj)
		return;
		
	if(obj.isMyControlObject())
	{
		sq_SendDestroyPacketPassiveObject(obj);
	}
}
