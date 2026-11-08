
//SHAKE 3 160
function onSetState_BLOODOATH(obj, state, datas, isResetTimer)
{

	obj.sq_StopMove();
    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATDEADHEAD_BODY);


}

function createBloodOathSoabrotEffect(obj)
{

	local ani = sq_CreateAnimation("","character/mage/atanimation/als_ani/atblood/absorbblood02.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos() + 1,obj.getZPos() + obj.getObjectHeight()/2);
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,2,false);	

}


function onEndCurrentAni_BLOODOATH(obj)
{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function onKeyFrameFlag_BLOODOATH(obj,flagIndex)
{
    if (flagIndex == 1)
    {
        obj.setCarryWeapon(false);
    }else if (flagIndex == 2)
    {
		obj.sq_SetShake(obj, 3, 160);

    }
    return true;
}