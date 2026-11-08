

function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ap_erjue")
	appendage.sq_AddFunctionName("prepareDraw", "prepareDraw_appendage_ap_erjue")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ap_erjue")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_ap_erjue")
	appendage.sq_AddFunctionName("isEnd", "isEnd_appendage_ap_erjue")
}


function sq_AddEffect(appendage)
{
	if(!appendage)
		return;
//????????ani???
	//appendage.sq_AddEffectBack("character/swordman/effect/animation/terriblekilling/erjue_effect_back.ani")

	//appendage.sq_AddEffectFront("character/swordman/effect/animation/terriblekilling/erjue_effect_front.ani")


}





function proc_appendage_ap_erjue(appendage)
{
	if(!appendage) {
		return;
	}
	
	local obj = appendage.getParent();
	
	if(!obj)
	{
		appendage.setValid(false);
		return;
	}	
	
	local time = appendage.getTimer().Get();
	
	local x = obj.getXPos();
	local y = obj.getYPos();
	local z = obj.getZPos();
	
	local t = appendage.getVar().get_timer_vector(0);
	
	if(!t)
		return;
	
	if(t.isOnEvent(time) == true)
	{
		local particleCreater = appendage.getVar().GetparticleCreaterMap("mm_darkaura", "passiveobject/new_skill/at_mage_summon_nutouwang/particle/buff_effect_radX.ptl", obj);
			
		particleCreater.Restart(0);
		particleCreater.SetPos(x, y, z);
		
		sq_AddParticleObject(obj, particleCreater);
	}
	
	if(t.isEnd() == true)
	{
		appendage.setValid(false);
	}
}


function onStart_appendage_ap_erjue(appendage)
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
	
	local var = appendage.getVar();		
	local elect = sq_AddDrawOnlyAniFromParent(parentObj,"character/swordman/effect/animation/terriblekilling/erjue_effect_front.ani", 0, 0, 1);	
	elect.setCurrentPos(parentObj.getXPos(), parentObj.getYPos()+1, parentObj.getZPos() + parentObj.getObjectHeight()/2);

	local sizeRate = sq_GetUniformVelocity(5,15,parentObj.getObjectHeight() - 100, 150);
	sizeRate = sizeRate.tofloat()/5.0;
	local ani = elect.getCurrentAnimation();
	if(ani)
		ani.resize(sizeRate);
}


function prepareDraw_appendage_ap_erjue(appendage)
{
	if(!appendage) {
		return;
	}
	
	local obj = appendage.getParent();	
}




function onEnd_appendage_ap_erjue(appendage)
{
	if(!appendage) {
		return;
	}
	
	local obj = appendage.getParent();	
	
}


// ??? ?? ??? ???
function isEnd_appendage_ap_erjue(appendage)
{
	
	
	return false;
}