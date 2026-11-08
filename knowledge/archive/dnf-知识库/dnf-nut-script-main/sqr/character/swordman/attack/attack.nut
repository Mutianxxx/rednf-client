



function onAfterSetState_swordman_attack(JM8H4uzkC2sc8UKfL7, CSDeDFugOHJaOjHj1gt, ZDQLDKNcdcrwAH_F2Dd, KLSE5PT5pu)
{
 if(!JM8H4uzkC2sc8UKfL7) return;
 local _RxS8qXkVJS2rEYWZj2fu1 = JM8H4uzkC2sc8UKfL7.sq_GetVectorData(ZDQLDKNcdcrwAH_F2Dd, 0); 
 local K_0MF3eLe5Urn = JM8H4uzkC2sc8UKfL7.sq_GetVectorData(ZDQLDKNcdcrwAH_F2Dd, 1); 
 JM8H4uzkC2sc8UKfL7.getVar().clear_vector(); 
 JM8H4uzkC2sc8UKfL7.getVar().push_vector(_RxS8qXkVJS2rEYWZj2fu1); 
 JM8H4uzkC2sc8UKfL7.getVar().push_vector(K_0MF3eLe5Urn); 
 switch(_RxS8qXkVJS2rEYWZj2fu1)
 {
 case 0:
 break;
 case 1:
 break;
 case 2:
 break;
 }
 wavemark_qq506807329_swordman_attack(JM8H4uzkC2sc8UKfL7, CSDeDFugOHJaOjHj1gt, ZDQLDKNcdcrwAH_F2Dd, KLSE5PT5pu); 
 weaponcombo_qq506807329_swordman_attack(JM8H4uzkC2sc8UKfL7, CSDeDFugOHJaOjHj1gt, ZDQLDKNcdcrwAH_F2Dd, KLSE5PT5pu); 
} ;

function onKeyFrameFlag_swordman_attack(obj, flagIndex)
{
	if(!obj) return false;
	local skillLevel = obj.sq_GetSkillLevel(123);
	local J9fVqmU33AHxBBTZ0BX = obj.getVar().get_vector(0); 
	local y91o8g5Ha1 = obj.getVar().get_vector(1); 
	local type = sq_getGrowType(obj);//??????????????

	switch (type)
	{
		case 0://??????/???

		if (skillLevel > 0)
		{
			if (flagIndex == 120)
			{
				local gaugeValue_rate = setSwordGhost3State(obj);
				obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_NONE_ATTACK1);
				//local damage = obj.sq_GetBonusRateWithPassive(174 , -1, 0, 0.2 + gaugeValue_rate.tofloat());
				//obj.sq_SetCurrentAttackBonusRate(damage);
				local attackInfo = sq_GetCurrentAttackInfo(obj);
				sq_SetCurrentAttackBonusRate(attackInfo, getSwordGhost3BasicAttackBonus(obj));
				sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
				obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);
				sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
			}
			if (flagIndex == 121)
			{
				local gaugeValue_rate = setSwordGhost3State(obj);
				obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_NONE_ATTACK2);
				//local damage = obj.sq_GetBonusRateWithPassive(174 , -1, 0, 0.3 + gaugeValue_rate.tofloat());
				//obj.sq_SetCurrentAttackBonusRate(damage);
				local attackInfo = sq_GetCurrentAttackInfo(obj);
				sq_SetCurrentAttackBonusRate(attackInfo, getSwordGhost3BasicAttackBonus(obj));
				sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
				obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);
				sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
			}
			if (flagIndex == 122)
			{
				local gaugeValue_rate = setSwordGhost3State(obj);
				obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_NONE_ATTACK3);
				//local damage = obj.sq_GetBonusRateWithPassive(174 , -1, 0, 0.4 + gaugeValue_rate.tofloat());
				//obj.sq_SetCurrentAttackBonusRate(damage);
				local attackInfo = sq_GetCurrentAttackInfo(obj);
				sq_SetCurrentAttackBonusRate(attackInfo, getSwordGhost3BasicAttackBonus(obj));
				sq_SetCurrentAttackInfo(obj,sq_GetCurrentAttackInfo(obj));
				obj.applyBasicAttackUp(sq_GetCurrentAttackInfo(obj),8);
				sq_SetCurrentAttackInfo(obj, sq_GetCurrentAttackInfo(obj));
			}
			
			if (flagIndex == 123)
			{	//???????????????? ?????????????????
				//if (sq_IsKeyDown(4, ENUM_SUBKEY_TYPE_ALL))
				//{
					obj.sq_IntVectClear();
					obj.sq_IntVectPush(0);
					obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_1, STATE_PRIORITY_USER, true);
				//}
			}
					local isAppendApd_buff_attack = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/JG_SwordMan/swordghost13/ap_buff.nut");
					if(isAppendApd_buff_attack)
					{
						if (flagIndex == 124)
						{
							obj.sq_PlaySound("SM_HELLSLASH_VS_02_2");
							obj.sq_SendCreatePassiveObjectPacket(260207, 0, 0, 0, 0);
							obj.sq_SetShake(obj,2,30);
							obj.sq_AddStateLayerAnimation(2,obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/buff_attack4.ani"), 5, 0);
						}
						if (flagIndex == 125)
						{
							obj.sq_PlaySound("SM_ONESLASH_VS_01");
							obj.sq_SendCreatePassiveObjectPacket(260208, 0, 0, 0, 0);
							obj.sq_SetShake(obj,2,30);
							obj.sq_AddStateLayerAnimation(2,obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/buff_attack2.ani"), -50, 0);
							obj.sq_AddStateLayerAnimation(3,obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/buff_attack2_sub.ani"), -50, 0);
							obj.sq_AddStateLayerAnimation(5,obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/buff_attack2_attack_sub.ani"), -130, 45);
						}
						if (flagIndex == 126)
						{
							obj.sq_PlaySound("SM_HELLSLASH_VS_02_1");
							obj.sq_SendCreatePassiveObjectPacket(260209, 0, 0, 0, 0);
							obj.sq_SetShake(obj,3,30);
						obj.sq_AddStateLayerAnimation(2,obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/buff_attack1.ani"), -5, 0);
						obj.sq_AddStateLayerAnimation(3,obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/buff_attack1_sub.ani"), -5, 0);
						obj.sq_AddStateLayerAnimation(3,obj.sq_CreateCNRDAnimation("effect/animation/bladespirit/buff_attack1_attack_sub.ani"), -65, -3);
						}
					}
		}
	break;

//??????
	case 1://????
	break;
	case 2://????
	break;
	case 3://????
	break;
//??????

	case 4://?????
	switch(y91o8g5Ha1)
	{
		case 67: 
		switch(flagIndex)
		{
			case 100: 
			case 101:
			obj.resetHitObjectList(); 
			break;
			case 1:
			if(J9fVqmU33AHxBBTZ0BX == 3) 
			sq_CreateDrawOnlyObject(obj, "character/swordman/effect/animation/weaponcombo/reslash_blunt03_dust01.ani", ENUM_DRAWLAYER_NORMAL, true); 
			break;
		}
	break;
	}
		break;
	default:
		break;
}
 return true;
} ;

 
function wavemark_qq506807329_swordman_attack(slsWw__ol53HVwr, obhXkplykqIKXfiAF34l, J9fVqmU33AHxBBTZ0BX, y91o8g5Ha1)
{
 if(!slsWw__ol53HVwr) return;
 if(!CNSquirrelAppendage.sq_IsAppendAppendage(slsWw__ol53HVwr, "character/swordman/appendage/ap_wavemark.nut"))return; 
 local uD4df2NuADegjZfNkTLF7qk = slsWw__ol53HVwr.sq_GetVectorData(J9fVqmU33AHxBBTZ0BX, 0); 
 if(slsWw__ol53HVwr.sq_IsMyControlObject())
 {
 local O84FFxLA2LOOZQuJ2 = slsWw__ol53HVwr.sq_GetBonusRateWithPassive(47, 8, 3 + uD4df2NuADegjZfNkTLF7qk, 1.0); 
 sq_BinaryStartWrite();
 sq_BinaryWriteDword(47); 
 sq_BinaryWriteBool(
 (sq_GetSkillLevel(slsWw__ol53HVwr, 92) > 0)
 ? true 
 : false 
 ); 
 sq_BinaryWriteDword(uD4df2NuADegjZfNkTLF7qk); 
 sq_BinaryWriteDword(O84FFxLA2LOOZQuJ2); 
 sq_SendCreatePassiveObjectPacket(slsWw__ol53HVwr, 24370, 0, 0, 0, 0, slsWw__ol53HVwr.getDirection());
 }
} ;

 
function weaponcombo_qq506807329_swordman_attack(obj, wHPCEiFicq, OSOvntYfaf78, _fWG9u8efXEB5ynSz)
{
 if(!obj) return;
 local xfRERcXbPBR = obj.sq_GetVectorData(OSOvntYfaf78, 0); 
 local ICUtVtUM7t = obj.sq_GetVectorData(OSOvntYfaf78, 1); 
 switch(ICUtVtUM7t)
 {
 case 67: 
 obj.sq_SetCurrentAttackBonusRate(sq_GetCurrentAttackBonusRate(obj) + obj.sq_GetBonusRateWithPassive(67, 8, 0, 1.0)); 
 local weapon = obj.getWeaponSubType(); 
 switch(weapon)
 {
	case 2: 
	switch(xfRERcXbPBR)
	{
		case 2: 
			obj.sq_SetCurrentAnimation(37);
			sq_Rewind(obj.sq_GetCurrentAni()); 
			obj.sq_SetCurrentAttackInfo(36); 
		break;
		case 3: 
			obj.sq_SetCurrentAnimation(170);
			sq_Rewind(obj.sq_GetCurrentAni()); 
			obj.sq_SetCurrentAttackInfo(100); 
		break;
 	}
 	break;
	case 3: 
		if(xfRERcXbPBR == 0 && obj.sq_IsMyControlObject())
		{
			sq_BinaryStartWrite();
			sq_BinaryWriteDword(67); 
			sq_BinaryWriteDword(1); 
			sq_BinaryWriteDword(sq_GetCurrentAttackBonusRate(obj)); 
			sq_SendCreatePassiveObjectPacket(obj, 24370, 0, 100, 0, 0, obj.getDirection());
		}
	break;
	case 0: 
	switch(xfRERcXbPBR)
	{
		case 0:
			local ani = obj.sq_GetAttackAni(1); 
			sq_Rewind(ani); 
			obj.setCurrentAnimation(ani); 
			obj.sq_AddStateLayerAnimation(1, sq_CreateAnimation("", "character/swordman/effect/animation/weaponcombo/short_new_01.ani"), 0, 0); 
			if(obj.sq_IsMyControlObject())
			{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(67); 
				sq_BinaryWriteDword(3); 
				sq_BinaryWriteDword(sq_GetCurrentAttackBonusRate(obj)); 
				sq_SendCreatePassiveObjectPacket(obj, 24370, 0, 0, 0, 0, obj.getDirection());
			}
		break;
		case 1:
			local ani = obj.sq_GetAttackAni(0); 
			sq_Rewind(ani); 
			obj.setCurrentAnimation(ani); 
			obj.sq_AddStateLayerAnimation(1, sq_CreateAnimation("", "character/swordman/effect/animation/weaponcombo/short_new_02.ani"), 40, 0); 
			if(obj.sq_IsMyControlObject())
			{
				sq_BinaryStartWrite();
				sq_BinaryWriteDword(67); 
				sq_BinaryWriteDword(3); 
				sq_BinaryWriteDword(sq_GetCurrentAttackBonusRate(obj)); 
				sq_SendCreatePassiveObjectPacket(obj, 24370, 0, 0, 0, 0, obj.getDirection());
			}
 		break;
		case 2:
			local ani = obj.sq_GetAttackAni(1); 
			sq_Rewind(ani); 
 			obj.setCurrentAnimation(ani); 
 			obj.sq_AddStateLayerAnimation(1, sq_CreateAnimation("", "character/swordman/effect/animation/weaponcombo/short_new_03.ani"), 0, 0); 
 			if(obj.sq_IsMyControlObject())
 			{
 				sq_BinaryStartWrite();
 				sq_BinaryWriteDword(67); 
				sq_BinaryWriteDword(2); 
				sq_BinaryWriteDword(sq_GetCurrentAttackBonusRate(obj)); 
 				sq_SendCreatePassiveObjectPacket(obj, 24370, 0, 0, 0, 0, obj.getDirection());
 			}
 		break;
	}
	break;
	case 1: 
		switch(xfRERcXbPBR)
		{
			case 0:
				obj.sq_AddStateLayerAnimation(1, sq_CreateAnimation("", "character/swordman/effect/animation/weaponcombo/ura_katana_eff.ani"), 0, 0); 
			break;
			case 1:
 				obj.sq_AddStateLayerAnimation(1, sq_CreateAnimation("", "character/swordman/effect/animation/weaponcombo/katana_new1_under_effect.ani"), 0, 0);
 				obj.sq_AddStateLayerAnimation(1, sq_CreateAnimation("", "character/swordman/effect/animation/weaponcombo/katana_new1_upper_effect.ani"), 0, 0);
			break;
			case 2:
				obj.sq_AddStateLayerAnimation(1, sq_CreateAnimation("", "character/swordman/effect/animation/weaponcombo/ura_katana_eff.ani"), 0, 0); 
			break;
			case 3:
				obj.sq_AddStateLayerAnimation(1, sq_CreateAnimation("", "character/swordman/effect/animation/weaponcombo/katana_new2_under_effect.ani"), 0, 0);
 				obj.sq_AddStateLayerAnimation(1, sq_CreateAnimation("", "character/swordman/effect/animation/weaponcombo/katana_new2_upper_effect.ani"), 0, 0);
			break;
 		}
 	break;
 }
 break;
 }
} ;
