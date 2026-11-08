




 
function checkExecutableSkill_Ripper(obj)
{
 if(!obj) return false;
 local yBbaFpXtbeG0l = obj.sq_IsUseSkill(117);
 if(yBbaFpXtbeG0l)
 {
		obj.sq_IntVectClear();
 obj.sq_addSetStatePacket(65, STATE_PRIORITY_USER, false);
 return true;
 }
 return false;
} ;

 
function checkCommandEnable_Ripper(obj)
{
	if(!obj) return false;
	return true;
} ;

 
function onIsCheckHitCollision_Ripper(QLC6NDdzsB4Z, WJS5wjsxzAgnpsv29gda0kdJ)
{
 return true;
} ;

function isForceHitCheck_Ripper(Cd7L3cZaZ_FrD1e4gWtsq0MK)
{
 return true;
} ;

function onAttack_Ripper(Cd7L3cZaZ_FrD1e4gWtsq0MK, sTY7IagIy5F3, QpTceXgar4e)
{
 local Ux9tHXfyUKKtewYgvbVh0y = Cd7L3cZaZ_FrD1e4gWtsq0MK.getVar();
 Ux9tHXfyUKKtewYgvbVh0y.setBool(0, true); 
 local BIUH5xL_mzo = Ux9tHXfyUKKtewYgvbVh0y.getBool(1); 
 if(!BIUH5xL_mzo)
 {
 Ux9tHXfyUKKtewYgvbVh0y.push_obj_vector(sTY7IagIy5F3);
 sq_AtrractionForce(Cd7L3cZaZ_FrD1e4gWtsq0MK, sTY7IagIy5F3, false, 270, -1, 2000.0, 1500.0, false); 
 sq_EffectLayerAppendage(sTY7IagIy5F3, sq_RGB(255, 255, 255), 155, 0, 80, 0);
 }
} ;


function onEndState_Ripper(Ae958nz8rExvtCnHv, bQIBhzjEDTM2OoZY8P5wef)
{
 if(!Ae958nz8rExvtCnHv) return;
 local xvUFpBYjiGRPTJSGUYvD = Ae958nz8rExvtCnHv.getVar();
 xvUFpBYjiGRPTJSGUYvD.clear_obj_vector();
 local oqXwTmFJPsU3ZpkPI6U6tI = sq_GetCurrentAnimation(Ae958nz8rExvtCnHv);
 if(oqXwTmFJPsU3ZpkPI6U6tI)
 {
 local tmyHgCjvUWZrs = xvUFpBYjiGRPTJSGUYvD.getFloat(2);
 oqXwTmFJPsU3ZpkPI6U6tI.setAttackBoundingBoxSizeRate(1.0 / tmyHgCjvUWZrs, true);
 }
 Ae958nz8rExvtCnHv.sq_setXScrollStop(0);
} ;


 
function onSetState_Ripper(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local var = obj.getVar();
	obj.sq_stopMove();
	if (isAvengerAwakenning(obj)) {
		local ani = obj.getVar().GetAnimationMap("RipperEx", "character/priest/animation/ripperex.ani");
		obj.setCurrentAnimation(ani);
		obj.sq_PlaySound("PR_DGUARDIAN_RIPPER_READY");
	}
	else{
		obj.sq_setCurrentAnimation(91);
		obj.sq_PlaySound("PR_RIPPER_READY");
	}
	obj.sq_setStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); 
	obj.sq_setCurrentAttackInfo(73);
	obj.sq_setAttackPowerWithPassive(117, state, -1, 0, 1.0);
	var.setBool(0, false);
	var.setBool(1, false);
	var.setFloat(2, 1.0);
	obj.sq_setXScroll(180, 100, obj.sq_getDelaySum()-200, 100);
	
} ;

function onEndCurrentAni_Ripper(TPGpocWFM5f8Gc)
{
 TPGpocWFM5f8Gc.sq_addSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
 TPGpocWFM5f8Gc.sq_setfindNearMovablePos(TPGpocWFM5f8Gc.getXPos(), TPGpocWFM5f8Gc.getYPos(), 50, 1, 5);
} ;

function onKeyFrameFlag_Ripper(obj, flagIndex)
{
	local var = obj.getVar();
	if(flagIndex == 1) 
		obj.sq_setShake(obj, 4, 60);
	else if(flagIndex == 2)
		obj.sq_setShake(obj, 2, 30);
	else if(flagIndex == 3)
	{
		sq_SetMyShake(obj, 3, 60); 
	}
	else if(flagIndex == 4)
		sq_SetMyShake(obj, 2, 30); 
	else if(flagIndex == 6)
	{
		obj.sq_setCurrentAttackInfo(73);
		local RojKJeqBLlZkY = obj.sq_GetSTATE();
		obj.sq_setAttackPowerWithPassive(117, RojKJeqBLlZkY, -1, 0, 1.0);
	}
	else if(flagIndex == 5 && var.getBool(0))
	{
		local RojKJeqBLlZkY = obj.sq_GetSTATE();
		obj.sq_setCurrentAttackInfo(85);
 
 		local A_7Q0qDxQbrDWSCRRO = sq_GetSkillLevel(obj, 165);
 		if(!sq_isPVPMode() && A_7Q0qDxQbrDWSCRRO > 0)
 		{
 			local J41KFgDsq1R6WeoSUh3JcyW = sq_GetLevelData(obj, 117, 2, A_7Q0qDxQbrDWSCRRO);
			J41KFgDsq1R6WeoSUh3JcyW = J41KFgDsq1R6WeoSUh3JcyW * 0.01;
			local Xm83SDnX7hlvU9seyH = sq_GetCurrentAnimation(obj);
			if(Xm83SDnX7hlvU9seyH)
			{
				Xm83SDnX7hlvU9seyH.setAttackBoundingBoxSizeRate(J41KFgDsq1R6WeoSUh3JcyW, true);
				var.setFloat(2, J41KFgDsq1R6WeoSUh3JcyW);
			}
		}
 		obj.sq_setAttackPowerWithPassive(117, RojKJeqBLlZkY, -1, 1, 1.0);
		sq_AddDrawOnlyAniFromParent(obj, "Character/Priest/Effect/Animation/Ripper/etc/33p_1_burst1-handup_normal.ani", 0, 1, 0);
		sq_AddDrawOnlyAniFromParent(obj, "Character/Priest/Effect/Animation/Ripper/etc/33p_burst1-handup_normal.ani", 0, 1, 0);
		local nBjRQp0ttmZgmzzMruO = sq_flashScreen(obj, 80, 80, 0, 255, sq_RGBA(255, 255, 255, 128), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		sq_addFlashScreen(nBjRQp0ttmZgmzzMruO, 0, 0, 400, 255, sq_RGBA(0, 0, 0, 180), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		local czPMeAF5v3LWUR9WlV = var.get_obj_vector_size();
		for(local FAbaay0X3ew8Bvye_r = 0; FAbaay0X3ew8Bvye_r < czPMeAF5v3LWUR9WlV; ++FAbaay0X3ew8Bvye_r)
		{
			local obj = var.get_obj_vector(FAbaay0X3ew8Bvye_r);
			if(obj == null)
				continue;
			sq_EffectLayerAppendage(obj, sq_RGB(0, 0, 0), 255, 0, 160, 160);
		}
	}
	else if(flagIndex == 7 && var.getBool(0))
	{
		var.setBool(1, true);
		sq_SendCreatePassiveObjectPacket(obj, 24102, 0, 267, 1, 83, obj.getDirection());
		if (isAvengerAwakenning(obj)) {
			obj.sq_PlaySound("R_PR_DGUARDIAN_RIPPER");
		}
		else{
			obj.sq_PlaySound("R_PR_RIPPER");
		}
	}
	return true;
} ;



