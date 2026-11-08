function checkExecutableSkill_SwordGhost28(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_28);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_28 , STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_SwordGhost28(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	

	if (state == STATE_STAND)
		return true;

	return true;
}

function onProc_SwordGhost28(obj)//????????????????????????
{

}


function onSetState_SwordGhost28(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_28_GHOST_REN_1);
	obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_28_GHOST_REN_1);	//????ATK????
	local gaugeValue_rate = setSwordGhost3State(obj);
	local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_28 , -1, 0, 1.0 + gaugeValue_rate.tofloat());
	obj.sq_SetCurrentAttackBonusRate(damage);				//??????SKL??????v??	

}

function onKeyFrameFlag_SwordGhost28(obj,flagIndex)
{
	if(!obj)
		return false;

		if (flagIndex == 4)
        {
		//obj.sq_PlaySound("SM_MOONSPIRITSLASH_VS_01");
		//obj.sq_SetShake(obj,3,100);//?????
	//sq_flashScreen(obj, 0, 30, 60, 170, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);//?????
		obj.sq_AddStateLayerAnimation(-4,obj.sq_CreateCNRDAnimation("effect/animation/ghost_ren_atk1/ghost_ren_atk1_effect_dust.ani"), 107, -50);
		obj.sq_AddStateLayerAnimation(2,obj.sq_CreateCNRDAnimation("effect/animation/ghost_ren_atk1/ghost_ren_atk1_L_a.ani"), 20, 34);
		obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/ghost_ren_atk1/ghost_ren_atk1_L_b.ani"), 20, 34);
		obj.sq_AddStateLayerAnimation(1,obj.sq_CreateCNRDAnimation("effect/animation/ghost_ren_atk1/ghost_ren_atk1_n_a.ani"), 20, 34);
		obj.sq_AddStateLayerAnimation(-3,obj.sq_CreateCNRDAnimation("effect/animation/ghost_ren_atk1/ghost_ren_atk1_n_b.ani"), 20, 34);
			obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/ghost_ren_atk1/ghost_ren_atk1_effect_sub_0.ani"), 131, -10);
			obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/ghost_ren_atk1/ghost_ren_atk1_effect_sub_1.ani"), 290, -80);
			obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/ghost_ren_atk1/ghost_ren_atk1_effect_sub_2.ani"), 230, -140);
		return true;
        }
		if (flagIndex == 5)
        {
			obj.sq_AddStateLayerAnimation(-1,obj.sq_CreateCNRDAnimation("effect/animation/ghost_ren_atk1/ghost_ren_atk1_effect.ani"), 20, 34);
			obj.sq_SendCreatePassiveObjectPacket(262173, 0, 176, 13, 0);
		return true;
        }
		if (flagIndex == 0)
        {
			obj.sq_AddStateLayerAnimation(0,obj.sq_CreateCNRDAnimation("effect/animation/ghost_ren_atk1/ghost_ren_atk1_effect_c.ani"), 0, 0);
			//obj.sq_AddStateLayerAnimation(0,obj.sq_CreateCNRDAnimation("effect/animation/ghost_ren_atk1/ghost_ren_atk1_effect_b.ani"), 67, -15);
obj.sq_AddStateLayerAnimation(0,obj.sq_CreateCNRDAnimation("effect/animation/ghost_ren_atk1/sword_ghost_7_gsb_start02.ani"), 0, 0);
		return true;
        }
}




function onEndCurrentAni_SwordGhost28(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}
