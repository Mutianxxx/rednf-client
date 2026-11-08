function checkExecutableSkill_moonlightdance(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_MOONLIGHTDANCE);
	if (isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_MOONLIGHTDANCE, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_moonlightdance(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_moonlightdance(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	local sq_var = obj.getVar();
	obj.setSkillSubState(substate);
	obj.sq_StopMove();

	local x = sq_GetXPos(obj);
	local y = sq_GetYPos(obj);
	local z = sq_GetZPos(obj);
	obj.getVar("pos").clear_vector();
	obj.getVar("pos").push_vector(x);
	obj.getVar("pos").push_vector(y);
	obj.getVar("pos").push_vector(z);

	local isMyControlObject = obj.sq_IsMyControlObject();
	if(substate == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MoonLightDanceReadyA_Body);
		als_ani_Thif(obj,"character/swordman/effect/animation/3rd/atmoonlightdance/start/moonlightdancestartc_06.ani", 0, 2, 0, 0, 100, 0, 1.0);

		local randNum = sq_getRandom(1, 4);
		obj.getVar("randNum").clear_vector();
		obj.getVar("randNum").push_vector(randNum);
	}
	else if(substate == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MoonLightDanceStartA_Body);

		local randNum = obj.getVar("randNum").get_vector(0);
		if(randNum == 1)
		obj.sq_PlaySound("SW_MOON_LIGHT_DANCE_01_1");
		if(randNum == 2)
		obj.sq_PlaySound("SW_MOON_LIGHT_DANCE_01_2");
		if(randNum == 3)
		obj.sq_PlaySound("SW_MOON_LIGHT_DANCE_01_3");
		if(randNum == 4)
		obj.sq_PlaySound("SW_MOON_LIGHT_DANCE_01_4");

		local objectManager = obj.getObjectManager();
		local xPos = objectManager.getFieldXPos(400+CFG_SCREEN_WIDTH_OFFSETX, ENUM_DRAWLAYER_NORMAL);
		local yPos = objectManager.getFieldYPos(450, 0, ENUM_DRAWLAYER_NORMAL);
		obj.sq_SetCurrentPos(obj, xPos, yPos, 0);

		if (isMyControlObject)
		{
			local objectManager = obj.getObjectManager();
			for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
			{
				local object = objectManager.getCollisionObject(i);
				if (object)
				{
					sq_ChangeDrawLayer(object, ENUM_DRAWLAYER_BOTTOM);
				}
			}
			local moonlightdancestarta_00 = "character/swordman/effect/animation/3rd/atmoonlightdance/start/moonlightdancestarta_00.ani";
			ATSwordman_Create(obj,moonlightdancestarta_00,ENUM_DRAWLAYER_NORMAL,0,-1,0,0,100,1,100,"moonlightdancestarta_00");

			//����
			local moonlightdancestarta_body = "character/swordman/atanimation/3rd/moonlightdancestarta_body.ani";
			ATSwordman_Create(obj,moonlightdancestarta_body,ENUM_DRAWLAYER_NORMAL,0,10,0,0,100,1,100,"moonlightdancestarta_body");
		}
	}
	else if(substate == 2)
	{
		local moonlightdancedasha_00 = "character/swordman/effect/animation/3rd/atmoonlightdance/dash/moonlightdancedasha_00.ani";
		ATSwordman_Create(obj,moonlightdancedasha_00,ENUM_DRAWLAYER_BOTTOM,0,0,0,0,100,0,100,"moonlightdancedasha_00");

		//����
		local moonlightdancedasha_body = "character/swordman/atanimation/3rd/moonlightdancedasha_body.ani";
		ATSwordman_Create(obj,moonlightdancedasha_body,ENUM_DRAWLAYER_NORMAL,0,0,0,0,100,0,100,"moonlightdancedasha_body");

		local moonlightdancedashc_01 = "character/swordman/effect/animation/3rd/atmoonlightdance/dash/moonlightdancedashc_01.ani";
		ATSwordman_Create(obj,moonlightdancedashc_01,ENUM_DRAWLAYER_NORMAL,0,1,0,0,100,0,100,"moonlightdancedashc_01");

		local moonlightdancedashd_00 = "character/swordman/effect/animation/3rd/atmoonlightdance/dash/moonlightdancedashd_00.ani";
		ATSwordman_Create(obj,moonlightdancedashd_00,ENUM_DRAWLAYER_NORMAL,0,1,0,0,100,0,100,"moonlightdancedashd_00");

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MoonLightDanceDashA_Body);

		local moonlightdancedasha_body = "character/swordman/atanimation/3rd/moonlightdancedasha_body.ani";
		ATSwordman_Create(obj,moonlightdancedasha_body,ENUM_DRAWLAYER_NORMAL,0,10,0,0,100,1,100,"moonlightdancedasha_body");
	}
	else if(substate == 3)
	{
		local objectManager = obj.getObjectManager();
		for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
		{
			local object = objectManager.getCollisionObject(i);
			if (object)
			{
				sq_ChangeDrawLayer(object, ENUM_DRAWLAYER_NORMAL);
			}
		}
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MoonLightDanceDashD_Body);
	}
	else if(substate == 4)
	{
		local randNum = obj.getVar("randNum").get_vector(0);
		if(randNum == 1)
		obj.sq_PlaySound("SW_MOON_LIGHT_DANCE_02_1");
		if(randNum == 2)
		obj.sq_PlaySound("SW_MOON_LIGHT_DANCE_02_2");
		if(randNum == 3)
		obj.sq_PlaySound("SW_MOON_LIGHT_DANCE_02_3");
		if(randNum == 4)
		obj.sq_PlaySound("SW_MOON_LIGHT_DANCE_02_4");

		local moonlightdanceattacka_00 = "character/swordman/effect/animation/3rd/atmoonlightdance/attack/moonlightdanceattacka_00.ani";
		ATSwordman_Create(obj,moonlightdanceattacka_00,ENUM_DRAWLAYER_NORMAL,0,1,0,0,100,1,100,"moonlightdanceattacka_00");

		local moonlightdanceattacka_body = "character/swordman/atanimation/3rd/moonlightdanceattacka_body.ani";
		ATSwordman_Create(obj,moonlightdanceattacka_body,ENUM_DRAWLAYER_NORMAL,0,2,0,0,100,1,100,"moonlightdanceattacka_body");

		obj.sq_SetCurrentAttackInfo(CUSTOM_ATTACK_MoonLightDance);
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_MOONLIGHTDANCE , -1, 0, 1.0);
		obj.sq_SetCurrentAttackBonusRate(damage);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MoonLightDanceAttackA_Body);
	}
	else if(substate == 5)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_MoonLightDanceDashA1_Body);
	}
}

function onEndCurrentAni_moonlightdance(obj)
{
	local substate = obj.getSkillSubState();
	local sq_var = obj.getVar();
	if(substate == 0)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(1);
		obj.sq_AddSetStatePacket(STATE_MOONLIGHTDANCE, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 1)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(2);
		obj.sq_AddSetStatePacket(STATE_MOONLIGHTDANCE, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 2)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(3);
		obj.sq_AddSetStatePacket(STATE_MOONLIGHTDANCE, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 3)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(4);
		obj.sq_AddSetStatePacket(STATE_MOONLIGHTDANCE, STATE_PRIORITY_IGNORE_FORCE, true);
	}
	else if(substate == 4)
	{
		local posX = obj.getXPos();
		local posY = obj.getYPos();
		local posZ = obj.getZPos();
		if (!obj.isMovablePos(posX, posY))
		{
			sq_MoveToNearMovablePos(obj, posX, posY, 0, posX, posY, posZ, 1000, -1, 3);
		}
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	else if(substate == 5)
	{
	}
}

function onKeyFrameFlag_moonlightdance(obj,flagIndex)
{
	if(!obj)
	return false;
	if (flagIndex == 100)
	{
		obj.sq_SetShake(obj,1,200);
	}
	else if (flagIndex == 101)
	{
		local swordmaster_neo = "sqr/character/atswordman_3rd/moonlightdance/atsword_swordmaster_neo.ani";
		ATSwordman_Create(obj,swordmaster_neo,ENUM_DRAWLAYER_COVER,-460,-480,0,0,100,0,100,"swordmaster_neo");
	}
	else if (flagIndex == 102)
	{
		obj.sq_SetShake(obj,3,300);
	}
	else if (flagIndex == 103)
	{
		obj.sq_SetShake(obj,12,320);
	}
	return true;
}

function onProc_moonlightdance(obj)
{
	local substate = obj.getSkillSubState();
	local pAni = obj.getCurrentAnimation();
	local frmIndex = sq_GetAnimationFrameIndex(pAni);
	local CurrentT = sq_GetCurrentTime(pAni);
	local delay = 0;
	if(pAni)
	delay = pAni.getDelaySum(false);
	if(substate == 3)
	{
		UniformVelocityMapMove_X(obj,"pos",500,delay);
	}
}
