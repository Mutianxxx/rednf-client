
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_IceCrash")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_IceCrash")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_IceCrash")
}

function sq_AddEffect(appendage)
{
}



function proc_appendage_IceCrash(appendage)
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
				
	local x = sq_GetDistancePos(sourceObj.getXPos(), sourceObj.getDirection(), 155);
	local t = sq_GetShuttleValue(0, 10,sq_GetObjectTime(parentObj),50)-5;
	x = x + (t >= 0 ? 3 : -3);
	local z = sourceObj.getZPos() + 50 - parentObj.getObjectHeight()/2;	
				
	if(z < 0)
		z = 0;
	sq_SetCurrentPos(parentObj, x, sourceObj.getYPos()-1,z);
    gbl_HoldAndDelayEffectSetDownByAppendageLoop(appendage);
}



function onStart_appendage_IceCrash(appendage)
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
}



function onEnd_appendage_IceCrash(appendage)
{
	if(!appendage) {
		return;
	}	
	
	local obj = appendage.getParent();
	local sourceObj = appendage.getSource();
	if(obj && sq_IsMyControlObject(obj) ) {
		local xPos = obj.getXPos();
		local yPos = obj.getYPos();

		// ������ �̵� ������ ��ǥ�� ã�´�
		if (moveDamagerLinerMovablepos(obj, sourceObj.getDirection(), 50) == false)
		{
			// ������ ������ ��ǥ�� ��ã�� ���?�������� ��ġ�� �������� ���?�������� ��ġ�� �̵�
			if (obj.isMovablePos(sourceObj.getXPos(), sourceObj.getYPos()) == true)
			{
				sq_SetCurrentPos(obj, sourceObj.getXPos(), sourceObj.getYPos(), obj.getZPos());
			}
			// �������� ��ġ�� �̻��� ���?�ֺ��� ������ ��ġ ����
			else
			{
				sq_SimpleMoveToNearMovablePos(obj,200);
			}
		}
	}		
}

function moveDamagerLinerMovablepos(damager, dir, movableRange)
{
	local xPos = damager.getXPos();
	local yPos = damager.getYPos();
	local toXPos = xPos

	if (dir == ENUM_DIRECTION_LEFT)
	{
		toXPos = xPos - movableRange;
	}
	else
	{
		toXPos = xPos + movableRange;
	}

	toXPos = damager.sq_findNearLinearMovableXPos(xPos, yPos, toXPos, yPos, 10);
	if (damager.isMovablePos(toXPos, yPos) == true)
	{
		sq_SetCurrentPos(damager, toXPos, yPos, damager.getZPos());
		return true;
	}
	else
	{
		if (dir == ENUM_DIRECTION_LEFT)
		{
			toXPos = xPos + movableRange;
		}
		else
		{
			toXPos = xPos - movableRange;
		}

		toXPos = damager.sq_findNearLinearMovableXPos(xPos, yPos, toXPos, yPos, 10);
		if (damager.isMovablePos(toXPos, yPos) == true)
		{
			sq_SetCurrentPos(damager, toXPos, yPos, damager.getZPos());
			return true;
		}
	}

	return false;
}