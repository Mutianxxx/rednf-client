
function setCustomData_po_mage_bloodcut(obj, receiveData)
{
	if(!obj)
		return;
    setCustomDataEtc_po_mage_bloodcut(obj, receiveData);


}


function onKeyFrameFlag_po_mage_bloodcut(obj, flagIndex)
{

	if (!obj)
		return 0;

    return onKeyFrameFlagEtc_po_mage_bloodcut(obj, flagIndex);


}

function onAttack_po_mage_bloodcut(obj,damager, boundingBox, isStuck)
{

	if (!obj)
		return 0;
    onAttackEtc_po_mage_bloodcut(obj,damager, boundingBox, isStuck);
}




function onTimeEvent_po_mage_bloodcut(obj, timeEventIndex, timeEventCount)
{
	if (!obj)
		return 0;
    onTimeEventEtc_po_mage_bloodcut(obj, timeEventIndex, timeEventCount);
}





function procAppend_po_mage_bloodcut(obj)
{
//
	if (!obj)
		return 0;
    procAppendEtc_po_mage_bloodcut(obj);


}



function onEndCurrentAni_po_mage_bloodcut(obj)
{

	if (!obj)
		return 0;
    onEndCurrentAniEtc_po_mage_bloodcut(obj);


}