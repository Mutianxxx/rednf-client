
// setCustomData
function setCustomData_po_xuejian_add(obj, receiveData)
{
	if(!obj)
		return;

	local attackBonusRate = receiveData.readDword();
	local sizeRate = receiveData.readWord();	// ????

	local attackInfo = sq_GetCurrentAttackInfo(obj);
	sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);

		local animation = sq_GetCurrentAnimation(obj);//????ANI??
		if (!animation) return;
		local size = sizeRate.tofloat() / 100.0;//?????
		animation.setImageRateFromOriginal(size, size);//?????????
		animation.setAutoLayerWorkAnimationAddSizeRate(size);//??????????
		sq_SetAttackBoundingBoxSizeRate(animation, size, size, size);//?????????

}



function onEndCurrentAni_po_xuejian_add(obj)
{
	if(!obj)
		return;
		
	if(obj.isMyControlObject())
	{
		sq_SendDestroyPacketPassiveObject(obj);
	}
}
