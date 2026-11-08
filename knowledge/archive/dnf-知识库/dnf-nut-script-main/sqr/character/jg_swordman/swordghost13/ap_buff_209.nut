function sq_AddFunctionName(appendage) {
	appendage.sq_AddFunctionName("proc", "proc_appendage_swordman_209")
	appendage.sq_AddFunctionName("prepareDraw", "prepareDraw_appendage_swordman_209")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_swordman_209")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_swordman_209")
	appendage.sq_AddFunctionName("isEnd", "isEnd_appendage_swordman_209")
}

function sq_AddEffect(appendage) {}

function proc_appendage_swordman_209(appendage) {

	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}
	local obj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	local mystate = obj.sq_GetState();
	if (mystate >= 106 && mystate <= 130) {
		if (mystate == 107) return;
		local skill_level = sq_GetSkillLevel(obj, 123);
		local max_gaugeValue = obj.sq_GetLevelData(123, 0, skill_level);
		//sq_EffectLayerAppendage(damager,sq_RGB(255,255,255),150,300,150,500);//???????????????G

		local count1 = obj.getMyPassiveObjectCount(251338); //BUFF???
		local count2 = obj.getMyPassiveObjectCount(250334); //????????BUFF????

		if (count1 <= max_gaugeValue) {
			if (count2 <= 2) //????????? ???????????
			{
				local rand = sq_getRandom(-50, 50);
				//local objindex = setSwordGhost4State(obj);
				sq_SendCreatePassiveObjectPacketPos(obj, 250334, 0, obj.getXPos() + rand, obj.getYPos() + rand, obj.getZPos() + obj.getObjectHeight() / 2);
			}
		}
		//print( "mystate:" + mystate+"\n");
	}
}

function onStart_appendage_swordman_209(appendage) {
	if (!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();

	if (!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}

}

function prepareDraw_appendage_swordman_209(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();
}

function onEnd_appendage_swordman_209(appendage) {
	if (!appendage) {
		return;
	}

	local obj = appendage.getParent();

}

// ?????? ?????? ????????? ???????
function isEnd_appendage_swordman_209(appendage) {
	return false;
}