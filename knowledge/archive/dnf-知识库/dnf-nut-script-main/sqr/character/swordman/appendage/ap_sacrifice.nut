
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_swordman_sacrifice")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_swordman_sacrifice")
}



function proc_appendage_swordman_sacrifice(appendage)
{
	if(!appendage)
		return;
} 

function drawAppend_appendage_swordman_sacrifice(appendage, isOver, x, y, isFlip)
{
	if(!appendage) {
		return;
	}
	
	local obj = appendage.getParent();
	
	if(!obj) {
		appendage.setValid(false);
		return;
	}
	
	local pAni = sq_GetCurrentAnimation(obj);
	
	if(!pAni) {
		appendage.setValid(false);
		return;
	}
	
	
	local currentT = sq_GetCurrentTime(pAni);
	
	local startT = 30;
	local endT = 160;
	local effectT = 240;
	local effectType = GRAPHICEFFECT_LINEARDODGE;
	local rgb = sq_RGB(155, 0, 0);

	local targetV = endT;
	local al = sq_GetUniformVelocity(startT, targetV, appendage.getTimer().Get(), effectT);
	local alpha = sq_ALPHA(al);
	pAni.setEffectLayer(true, effectType, true, rgb, alpha, true, false);
	
	local size = sq_AniLayerListSize(pAni);
	
	if(size > 0) {
		for(local i=0;i<size;i+=1) {
			local aniL = sq_getAniLayerListObject(pAni, i);
			
			if(aniL) {
				local effect = aniL.GetCurrentFrame().GetGraphicEffect();
				
				if(effect != GRAPHICEFFECT_LINEARDODGE) {
					aniL.setEffectLayer(true, effectType, true, rgb, alpha, true, false);
				}
			}
		}
	}

}