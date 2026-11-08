



function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_deitiesrebirth")
	appendage.sq_AddFunctionName("proc", "proc_appendage_deitiesrebirth")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_deitiesrebirth")
}



function sq_AddEffect(appendage)
{
	if(!appendage) {
		return;
	}
	//appendage.sq_AddEffectFront("character/thief/effect/animation/deitiesrebirth/cast_03.ani");
}



function onStart_appendage_deitiesrebirth(appendage)
{
	if(!appendage) return;

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if(!sourceObj || !parentObj)
	{
		appendage.setValid(false);
		return;
	}
	local Front = sq_AddDrawOnlyAniFromParent(parentObj, "character/thief/effect/animation/deitiesrebirth/cast_03.ani" ,0,-1,0);
	
	appendage.getVar("obj").clear_obj_vector();
	appendage.getVar("obj").push_obj_vector(  Front );
	appendage.getVar("enterCount").clear_vector();//qing?????
	appendage.getVar("enterCount").push_vector(0);//?????????????
}



function proc_appendage_deitiesrebirth(appendage)
{
	if(!appendage) return;

	local parentObj = appendage.getParent();//?????????
	local sourceObj = appendage.getSource();//?????????
	local parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);//????????wei?????
	if(!sourceObj || !parentObj || parentObj.isDead())//??????????????????????????????
	{
		appendage.setValid(false);//???????ap
		return;
	}
	local currentCount = appendage.getVar("enterCount").get_vector(0);//?????????????????????
	local front = appendage.getVar("obj").get_obj_vector(0);
	if (front)
	{
        	front.setCurrentPos(parentObj.getXPos(),parentObj.getYPos() + 2,parentObj.getZPos() + parentObj.getObjectHeight()/2);
	}
	if(parentObj.sq_IsEnterSkill(SKILL_FLAMEBALL) != -1 && !sq_GetSkill(parentObj, SKILL_FLAMEBALL).isInCoolTime())
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(65);//???? ?? ????????? ????? ????????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_ILUSIONSHURIKEN) != -1 && !sq_GetSkill(parentObj, SKILL_ILUSIONSHURIKEN).isInCoolTime() && sq_GetZPos(parentObj) == 0)
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(66);//?????????????? ????? ????????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_ILUSIONSHURIKEN) != -1 && !sq_GetSkill(parentObj, SKILL_ILUSIONSHURIKEN).isInCoolTime() && sq_GetZPos(parentObj) != 0)
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(67);//?????????????? ????? ????????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_FLAMETORNADO) != -1 && !sq_GetSkill(parentObj, SKILL_FLAMETORNADO).isInCoolTime())
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(68);//???? ?? ju??? ??????????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_BIGKUNAI) != -1 && !sq_GetSkill(parentObj, SKILL_BIGKUNAI).isInCoolTime() && sq_GetZPos(parentObj) == 0)
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(69);//???? ?? ???????? ????? ????????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_BIGKUNAI) != -1 && !sq_GetSkill(parentObj, SKILL_BIGKUNAI).isInCoolTime() && sq_GetZPos(parentObj) != 0)
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(70);//???? ?? ???????? ????? ???????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_MIGAWARI) != -1 && !sq_GetSkill(parentObj, SKILL_MIGAWARI).isInCoolTime())
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(71);//???? : ?????? ??????????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_SKYROADS) != -1 && !sq_GetSkill(parentObj, SKILL_SKYROADS).isInCoolTime() && sq_GetZPos(parentObj) == 0)
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(72);//???? ?? ???? ????? ????????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_SKYROADS) != -1 && !sq_GetSkill(parentObj, SKILL_SKYROADS).isInCoolTime() && sq_GetZPos(parentObj) != 0)
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(73);//???? ?? ???? ????? ???????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_GASOLINEFIRE) != -1 && !sq_GetSkill(parentObj, SKILL_GASOLINEFIRE).isInCoolTime() && sq_GetZPos(parentObj) == 0)
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(74);//???? ?? ??chu?????? ??????????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_GASOLINEFIRE) != -1 && !sq_GetSkill(parentObj, SKILL_GASOLINEFIRE).isInCoolTime() && sq_GetZPos(parentObj) != 0)
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(75);//???? ?? ??chu???????????????
		sq_SendCreatePassiveObjectPacketPos(parentObj, 24356, 0, sq_GetDistancePos(sq_GetXPos(parentObj), parentObj.getDirection(), -180), sq_GetYPos(parentObj), 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_FLAMEFLOWER) != -1 && !sq_GetSkill(parentObj, SKILL_FLAMEFLOWER).isInCoolTime())
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(76);//???? ?? ??????? ??????????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_YAMATAOROCHI) != -1 && !sq_GetSkill(parentObj, SKILL_YAMATAOROCHI).isInCoolTime())
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(77);//???????? ??????????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_FUUMASHURIKEN) != -1 && !sq_GetSkill(parentObj, SKILL_FUUMASHURIKEN).isInCoolTime() && sq_GetZPos(parentObj) == 0)
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(78);//???? ?? ???????? ????? ????????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_FUUMASHURIKEN) != -1 && !sq_GetSkill(parentObj, SKILL_FUUMASHURIKEN).isInCoolTime() && sq_GetZPos(parentObj) != 0)
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(79);//???? ?? ???????? ????? ???????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	else if(parentObj.sq_IsEnterSkill(SKILL_AMATERAS) != -1 && !sq_GetSkill(parentObj, SKILL_AMATERAS).isInCoolTime())
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(80);//??? ??????????????
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.getVar("enterCount").set_vector(0, currentCount + 1);//????????????????????
	}
	if(currentCount >= sq_GetIntData(parentObj, SKILL_DEITIESREBIRTH, 1))//???????????????????????????????
	{
		appendage.setValid(false);//???????ap??????????????
	}
	parentObj.setSkillCommandEnable(SKILL_DEITIESREBIRTH, true);//????????
	if(parentObj.sq_IsEnterSkill(SKILL_DEITIESREBIRTH) != -1)//??????????????
	{
		appendage.setValid(false);
		if(parentObj.sq_GetSkillLevel(123)>0)
		{
			local myobjcount = parentObj.getMyPassiveObjectCount(24356);			
			for (local i = 0; i < myobjcount ; ++i) 
			{ 
				local object = parentObj.getMyPassiveObject(24356,i);
				if (object)
				{
					object.setCurrentPos(parentObj.getXPos(),parentObj.getYPos(),0);
					sq_SetCurrentDirection(object, parentObj.getDirection());
				}
			}

		}
	}
}


function onEnd_appendage_deitiesrebirth(appendage)
{
	if(!appendage) return;

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if(!sourceObj || !parentObj)
	{
		appendage.setValid(false);
		return;
	}
	appendage.setBuffIconImage(123);
	parentObj.sq_PlaySound("TF_SIXROTATION_02");
	local front = appendage.getVar("obj").get_obj_vector(0);
        if (front)
        {
            front.setValid(false);
        }
}

