
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ShadowSoulSuperHold")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ShadowSoulSuperHold")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_ShadowSoulSuperHold")
}
function sq_AddEffect(appendage)
{
}


function onEnd_appendage_ShadowSoulSuperHold(appendage)
{

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();


	local line = appendage.getVar("chain").get_obj_vector(0);
	if (line)
	{
		line.setValid(false);
	}
}


function proc_appendage_ShadowSoulSuperHold(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				

	if(!sourceObj || !parentObj )
	{
		appendage.setValid(false);
		return;
	}
	
	local i = 2,j = 2;


	local currT = appendage.getTimer().Get();
	local apdT = appendage.getVar("para").get_vector(0);
	if (apdT > 0)
	{

		if (apdT > currT)
		{
			gbl_HoldAndDelayEffectSetByAppendageLoop(appendage);

			local line = appendage.getVar("chain").get_obj_vector(0);
			
			if (line)
			{
				local lastX = appendage.getVar("para").get_vector(1);
				local lastY = appendage.getVar("para").get_vector(2);
				local lastZ = 0;
		
				local parX = parentObj.getXPos();
				local parY = parentObj.getYPos();
				local parZ = parentObj.getZPos() + parentObj.getObjectHeight() / 2;

				line.setCurrentPos( lastX ,lastY,lastZ);
				sq_setDirectionToPosX(line,parX);
				
				
				
				local angle = getRorateAngleByCurrentPosEX(parentObj,
				lastX,lastY,lastZ,
				parX,parY,parZ,61.8);
						
				local pAni = sq_GetCurrentAnimation(line);

	
				local lenX = 756;
						
				local distance = sq_GetDistance(lastX, 
										lastY - lastZ,
										parX,
										parY - parZ, true);
										
				local screenX = sq_GetScreenXPos(line);
				local screenY = sq_GetScreenYPos(line);

				local screenX2 = sq_GetScreenXPos(parentObj);
				local screenY2 = sq_GetScreenYPos(parentObj);		


				sq_SetfRotateAngle(pAni, angle);

				if (line.getDirection() == 0)
				{
					pAni.setCustomClipArea(true, getMin(screenX,screenX2) - 10, 0, getMax(screenX,screenX2), 600, false);
				}else if (line.getDirection() == 1)
				{
					pAni.setCustomClipArea(true, getMin(screenX,screenX2), 0, getMax(screenX,screenX2) - 10, 600, false);
				}

				pAni.setCustomClipArea(true, getMin(screenX,screenX2), 0, getMax(screenX,screenX2), 600, false);
			}else
			{
				local line = sq_AddDrawOnlyAniFromParent(parentObj,
				"character/thief/animation/zrr/chainreaction/chain_line.ani",0,-1,0);
				appendage.getVar("chain").push_obj_vector(line);
			}


		}else 
		{
			local line = appendage.getVar("chain").get_obj_vector(0);
			if (line)
			{
				line.setValid(false);
			}else
			{
				appendage.setValid(false);
				return;
			}
		}



	}
}





function onStart_appendage_ShadowSoulSuperHold(appendage)
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

	appendage.getVar("chain").clear_obj_vector();




}

