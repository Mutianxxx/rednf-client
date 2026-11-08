
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ShadowSoulBodyEffect")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ShadowSoulBodyEffect")
	appendage.sq_AddFunctionName("drawAppend", "drawAppend_appendage_ShadowSoulBodyEffect")
}

function sq_AddEffect(appendage)
{
}


function drawAppend_appendage_ShadowSoulBodyEffect(appendage, isOver, x, y, isFlip)
{
	if(!appendage) {
		return;
	}


	local obj = appendage.getParent();	

	if (!obj)
		return ;
	
	if (obj.getState() != 9)
		return ;


	obj = sq_GetCNRDObjectToActiveObject(obj);
	
	obj.setDirection(1);
	
	local pAni = sq_GetCurrentAnimation(obj);
	local centerX = x;
	local centerY = y - obj.getObjectHeight()/2;
	
	local currT = appendage.getTimer().Get();
	
	local rateX = 0;
	local rateY = 0;

	local maxRateX = 45;
	local maxRateY = 35;

	if (currT < 0)
	{
		rateY = 0;
		rateX = 0;
	}else if (currT < 150)
	{
		rateX = 0;
		rateY = sq_GetUniformVelocity(0, maxRateY, currT - 0, 150);
	}
	else
	{
		rateY = maxRateY;
		rateX = 0;
	}
	

	local rgb = sq_RGB(0,0,0);
	local alpha = sq_ALPHA(255);
	
	sq_AnimationProc(pAni);
	sq_DrawSpecificFrameEffect_SIMPLE(pAni, x, y, 0, rgb, alpha, true);
	

	setClipWithLimit(centerX + rateX,centerY + rateY,800,600);
	sq_AnimationProc(pAni);
	sq_drawCurrentFrame(pAni, x + rateX, y + rateY, false);
	releaseClip();
	
	setClipWithLimit(centerX + rateX,0,800,centerY - rateY);
	sq_AnimationProc(pAni);
	sq_drawCurrentFrame(pAni, x + rateX, y - rateY, false);
	releaseClip();


	setClipWithLimit(0,centerY + rateY,centerX - rateX,600);
	sq_AnimationProc(pAni);
	sq_drawCurrentFrame(pAni, x - rateX, y + rateY, false);
	releaseClip();
	
	setClipWithLimit(0,0,centerX - rateX,centerY - rateY);
	sq_AnimationProc(pAni);
	sq_drawCurrentFrame(pAni, x - rateX, y - rateY, false);
	releaseClip();

}


function proc_appendage_ShadowSoulBodyEffect(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

	if(!sourceObj || !parentObj) 
	{
		appendage.setValid(false);
		return;
	}

	local currT = appendage.getTimer().Get();

	if (currT > 1000)
	{
		appendage.setValid(false);
		return;
	}
	gbl_HoldAndDelayEffectSetByAppendageLoopNoClear(appendage);

}



function onStart_appendage_ShadowSoulBodyEffect(appendage)
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

	//sq_ChangeDrawLayer(parentObj, passiveobj.getXPos());
}

