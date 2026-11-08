function checkExecutableSkill_SwordGhost30(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORD_GHOST_30);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_SWORD_GHOST_30 , STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}

function checkCommandEnable_SwordGhost30(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	

	if (state == STATE_STAND)
		return true;

	return true;
}

function onProc_SwordGhost30(obj)//????????????????????????
{

}


function Body_SwordGhost30_dust(obj, disX, disY, disZ)
{
	//local sizeRate = obj.sq_GetIntData(SKILL_SWORD_GHOST_15, 0);
	//local size = sizeRate.tofloat() / 100.0;//????j?????????
	//ani.setImageRateFromOriginal(size, size);//????j??
	//ani.setAutoLayerWorkAnimationAddSizeRate(size);//???????h
	
	local ani = sq_CreateAnimation("","character/swordman/effect/animation/bladespirit/yasuo_obj_q_hit_07.ani");//????????
	local pooledObj = sq_CreatePooledObject(ani,true);//??????H
	local posX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), disX);//?????????????????????V???????
	pooledObj.setCurrentPos(posX,obj.getYPos() + disY,obj.getZPos() + disZ);//????????????????
	pooledObj.setCurrentDirection(obj.getDirection());//????????????V
	//sq_moveWithParent(obj, pooledObj);//???????????????????
	
	sq_AddObject(obj,pooledObj,2,false);	

}

function onSetState_SwordGhost30(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);	//????????????t?????


		local isAppendApd_flag1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/JG_SwordMan/swordghost30/ap_swordghost30.nut");
		local isAppendApd_flag2 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/JG_SwordMan/swordghost30/ap_swordghost30_2.nut");
		if(isAppendApd_flag2)
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_28_GHOST_REN_2);
			//obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_30_YASUO_ATTACK);	//????ATK????
			obj.sq_SendCreatePassiveObjectPacket(260213, 0, 150, 0, 0);
			//local gaugeValue_rate = setSwordGhost3State(obj);
			//local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_30 , -1, 0, 1.0 + gaugeValue_rate.tofloat());
			//obj.sq_SetCurrentAttackBonusRate(damage);				//??????SKL??????v??	
			CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/JG_SwordMan/swordghost30/ap_swordghost30.nut");
			CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/JG_SwordMan/swordghost30/ap_swordghost30_2.nut");
		}
		else if(!isAppendApd_flag2)
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORD_GHOST_30_YASUO_Q_ATTACK);
			obj.sq_SetCurrentAttackInfo(CUSTOM_ATK_SWORD_GHOST_30_YASUO_ATTACK);	//????ATK????
			local gaugeValue_rate = setSwordGhost3State(obj);
			local damage = obj.sq_GetBonusRateWithPassive(SKILL_SWORD_GHOST_30 , -1, 0, 1.0 + gaugeValue_rate.tofloat());
			obj.sq_SetCurrentAttackBonusRate(damage);				//??????SKL??????v??	
		}
	

}

function onKeyFrameFlag_SwordGhost30(obj,flagIndex)
{
	if(!obj)
		return false;


		if (flagIndex == 1)
        {
	obj.sq_SendCreatePassiveObjectPacket(260215, 0, 113, 0, 57);
	//obj.sq_SetShake(obj,2,100);//?????
	Body_SwordGhost30_dust(obj,45, 0, 0);
		return true;
        }
}


function onAttack_SwordGhost30(obj, damager, boundingBox, isStuck)
{
	if (!obj) return false;

	
		local sq_var = obj.getVar();	
		sq_var.push_obj_vector(damager);
		local objectsSize = sq_var.get_obj_vector_size();
		//print(" id:" + damager);
		//print(" objectsSize:" + objectsSize);
		if(objectsSize <= 1)
	{
		local isAppendApd_flag1 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/JG_SwordMan/swordghost30/ap_swordghost30.nut");
		local isAppendApd_flag2 = CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/JG_SwordMan/swordghost30/ap_swordghost30_2.nut");
		if(!isAppendApd_flag1)
		{
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_SWORD_GHOST_30, false,
		"character/JG_SwordMan/swordghost30/ap_swordghost30.nut", false);
		appendage.sq_SetValidTime(5000);
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_SWORD_GHOST_30, -1);
		CNSquirrelAppendage.sq_Append(appendage, obj, obj);		//??????SKL??????v??	
		}
		else if(isAppendApd_flag1)
		{
		CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/JG_SwordMan/swordghost30/ap_swordghost30.nut");
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_SWORD_GHOST_30, false,
		"character/JG_SwordMan/swordghost30/ap_swordghost30_2.nut", false);
		appendage.sq_SetValidTime(5000);
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_SWORD_GHOST_30, -1);
		CNSquirrelAppendage.sq_Append(appendage, obj, obj);		//??????SKL??????v??	
		}
	}
	
	
}




function onEndCurrentAni_SwordGhost30(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}
