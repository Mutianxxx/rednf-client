function checkExecutableSkill_Brionac(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_BRIONAC);
	if (isUse)
	{
		obj.getVar().clear_vector();
		local posX = obj.getXPos();
		local posY = obj.getYPos();
		local posZ = obj.getZPos();
		obj.getVar("Brionac_Pos").clear_vector();
		obj.getVar("Brionac_Pos").push_vector(posX);
		obj.getVar("Brionac_Pos").push_vector(posY);
		obj.getVar("Brionac_Pos").push_vector(posZ);
		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_COVER);
		local yPos = objectManager.getFieldYPos(400, 1, ENUM_DRAWLAYER_COVER);
		obj.sq_SetCurrentPos(obj, xPos, yPos, 0);
		obj.sq_AddSetStatePacket(STATE_BRIONAC, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	return false;
}

function checkCommandEnable_Brionac(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_Brionac(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	obj.sq_StopMove();
	obj.setObjectHeight(2000);
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_BRIONAC_BODY_BODY);
	obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_REPENTENCE_SMASHATK1);
	obj.sq_SendCreatePassiveObjectPacket(242401, 0, 100, 0, 0);
	
	local brionaccutinc_bg05 = "character/priest/effect/animation/atbrionac/cutin/brionaccutinc_bg05.ani";
	ATPriest_Create(obj,brionaccutinc_bg05,ENUM_DRAWLAYER_COVER,0,-150,0,0,140,0,80,"brionaccutinc_bg05");
	local brionaccutina_eff01 = "character/priest/effect/animation/atbrionac/cutin/brionaccutina_eff01.ani";
	ATPriest_Create(obj,brionaccutina_eff01,ENUM_DRAWLAYER_COVER,0,-150,0,0,140,0,90,"brionaccutina_eff01");
	local brionac_new_body = "character/priest/atanimation/brionac_new_body.ani";
	ATPriest_Create(obj,brionac_new_body,ENUM_DRAWLAYER_COVER,-270,-40,0,0,90,0,100,"brionac_new_body");
	local brionacadd_body04 = "character/priest/atanimation/brionacadd_body04.ani";
	ATPriest_Create(obj,brionacadd_body04,ENUM_DRAWLAYER_COVER,15,0,100,0,150,0,100,"brionacadd_body04");
}

function onTimeEvent_Brionac(obj, timeEventIndex, timeEventCount)
{
	if(!obj) return false;
	if(timeEventIndex == 0)
	{
	}
}

function onAttack_Brionac(obj, damager, boundingBox, isStuck)
{
	if(!obj) return false;
	
	if(damager.getState() != STATE_HOLD && sq_IsGrabable(obj,damager) && 
	sq_IsHoldable(obj,damager) && !sq_IsFixture(damager) && damager.isObjectType(OBJECTTYPE_ACTIVE)) 
	{
		local masterAppendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_BRIONAC, false,
		"character/atpriest/brionac/ap_brionac.nut", true);
		masterAppendage.sq_SetValidTime(sq_GetIntData(obj, SKILL_BRIONAC, 0));
		if(masterAppendage)
		{
			sq_HoldAndDelayDie(damager, obj, true, true, true, 1, 1, ENUM_DIRECTION_NEUTRAL , masterAppendage);
		}
	}
}

function onKeyFrameFlag_Brionac(obj,flagIndex)
{
	if(!obj)
		return false;
	if (flagIndex == 0)
	{
		obj.sq_PlaySound("BRUNAQ_CAST");
	}
	if (flagIndex == 1)
	{
		sq_SetShake(obj,5,80);
	}
	if (flagIndex == 2)
	{
		obj.sq_SendCreatePassiveObjectPacket(242402, 0, 0, 0, 0);
		local brionaclanceeff_eff08 = "character/priest/effect/animation/atbrionac/spear/brionaclanceeff_eff08.ani";
		ATPriest_Create(obj,brionaclanceeff_eff08,ENUM_DRAWLAYER_COVER,0,20,0,0,100,0,80,"brionaclanceeff_eff08");
	}
	if (flagIndex == 3)
	{
		obj.sq_StartWrite();
		obj.sq_WriteDword(32);
		obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 0);
	}
	if (flagIndex == 4)
	{
	}
	if (flagIndex == 5)
	{
	}
	if (flagIndex == 6)
	{
		obj.sq_PlaySound("PW_BRUNAQ_AMEN");
	}

	return true;
}

function onEndCurrentAni_Brionac(obj)
{

	obj.setObjectHeight(105);
	local srcX = obj.getVar("Brionac_Pos").get_vector(0);
	local srcY = obj.getVar("Brionac_Pos").get_vector(1);
	local srcZ = obj.getVar("Brionac_Pos").get_vector(2);
	obj.sq_SetCurrentPos(obj, srcX, srcY, srcZ);

	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

