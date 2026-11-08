
// setCustomData
function setCustomData_po_swordghost15(obj, receiveData)
{
//print("setCustomData_po_swordghost15\n");

	if(!obj)
		return;

	local attackBonusRate = receiveData.readDword();
//print("attackBonusRate="+ attackBonusRate+"\n");
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



function onEndCurrentAni_po_swordghost15(obj)
{
	if(!obj)
		return;
//print("onEndCurrentAni_po_swordghost15\n");		
	if(obj.isMyControlObject())
	{
		sq_SendDestroyPacketPassiveObject(obj);
	}
}
