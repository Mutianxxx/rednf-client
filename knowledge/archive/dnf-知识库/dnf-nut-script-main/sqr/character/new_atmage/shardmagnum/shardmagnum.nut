
 
function checkExecutableSkill_atmage_shardmagnum(obj)
{
 	if(!obj) return false; 
 	local gMENAd0ViZvuhrYLdIpS5s = obj.sq_IsUseSkill(246); 
	if(gMENAd0ViZvuhrYLdIpS5s) 
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0); 
		obj.sq_AddSetStatePacket(246, STATE_PRIORITY_USER, true); 
		return true; 
	}
 	return false; 
}

 
function checkCommandEnable_atmage_shardmagnum(obj)
{
	if(!obj) return false; 
	return true; 
/*	local gMENAd0ViZvuhrYLdIpS5s = obj.sq_GetState(); 
	if(gMENAd0ViZvuhrYLdIpS5s == STATE_STAND) 
		return true; 
	if(gMENAd0ViZvuhrYLdIpS5s == STATE_ATTACK) 
	{
		return obj.sq_IsCommandEnable(246); 
	}
	return true; */
} ;

 
function onSetState_atmage_shardmagnum(obj, gMENAd0ViZvuhrYLdIpS5s, fwOCOeFq9yr, Y70fQ_GxyKDyR67)
{
	if(!obj) return; 

	obj.sq_StopMove(); 
	local Ol8AVXsF1kpPcOd1w = obj.sq_GetVectorData(fwOCOeFq9yr, 0); 
	obj.setSkillSubState(Ol8AVXsF1kpPcOd1w); 
	switch(Ol8AVXsF1kpPcOd1w)
	{
		case 0:
			obj.getVar().clear_obj_vector(); 
			obj.sq_SetCurrentAnimation(104);
			obj.sq_SetCurrentAttackInfo(22);
			local rSdaPSiLJjhzoE5ovO6zjU = obj.sq_GetBonusRateWithPassive(246, 246, 0, 1.0); 
			obj.sq_SetCurrentAttackBonusRate(rSdaPSiLJjhzoE5ovO6zjU); 
		break;
	}
	local sd9I5MbxS3D2f7aPfz43C = obj.sq_GetDelaySum(); 
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); 
	local R8ITeeYCPkf_9Nm = obj.sq_GetDelaySum(); 
	obj.getVar("speedRate").setFloat(0, sd9I5MbxS3D2f7aPfz43C.tofloat() / R8ITeeYCPkf_9Nm.tofloat()); 
	obj.getVar("speedRate").setFloat(1, R8ITeeYCPkf_9Nm.tofloat() / sd9I5MbxS3D2f7aPfz43C.tofloat()); 
	obj.getVar("dama").clear_obj_vector();
} ;


function onAttack_atmage_shardmagnum(obj, damager, boundingBox, isStuck)
{
        obj.getVar("dama").push_obj_vector(damager);
}



function onKeyFrameFlag_atmage_shardmagnum(obj, hRuY8re0Cr)
{
	if(!obj) return false;
	local substate = obj.getSkillSubState(); 
	switch(substate)
	{
	case 0:
	switch(hRuY8re0Cr)
	{
		case 1:
			sq_myFlashScreen_qq506807329(obj, 0, 0, 200, 102, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM, false); 
			sq_mySetShake_qq506807329(obj, 5, 50, false); 
 
			if(obj.sq_IsMyControlObject())
			{
				obj.sq_StartWrite();
				obj.sq_WriteDword(246); 
				obj.sq_WriteDword(1); 
				obj.sq_WriteDword(obj.sq_GetIntData(246, 1)); 
				obj.sq_SendCreatePassiveObjectPacket(24379, 0, 85, 0, 0);
			}
			break;
		case 2:
			sq_myFlashScreen_qq506807329(obj, 0, 80, 100, 178, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM, false); 
			sq_mySetShake_qq506807329(obj, 10, 200, false); 
 
			local wBYSXC9udAMy6OrtL1JZVmY = sq_GetCNRDObjectToCollisionObject(obj.getVar().get_obj_vector(0)); 
			if(wBYSXC9udAMy6OrtL1JZVmY)
			{
				if(wBYSXC9udAMy6OrtL1JZVmY.isMyControlObject())
				{
					local vAw11S_w7iMNnY384qt9bnGq = sq_GetSkillLevel(obj, 246); 
					local zTT7r_ziIs = sq_GetGlobalIntVector(); 
					sq_IntVectorClear(zTT7r_ziIs); 
					sq_IntVectorPush(zTT7r_ziIs, obj.sq_GetBonusRateWithPassive(246, 246, 1, 1.0)); 
					sq_IntVectorPush(zTT7r_ziIs, obj.sq_GetLevelData(246, 2, vAw11S_w7iMNnY384qt9bnGq)); 
					sq_IntVectorPush(zTT7r_ziIs, obj.sq_GetLevelData(246, 3, vAw11S_w7iMNnY384qt9bnGq)); 
					sq_IntVectorPush(zTT7r_ziIs, obj.sq_GetLevelData(246, 4, vAw11S_w7iMNnY384qt9bnGq)); 
					sq_IntVectorPush(zTT7r_ziIs, obj.sq_GetIntData(246, 0)); 
					sq_IntVectorPush(zTT7r_ziIs, sq_GetGroup(obj)); 
					sq_IntVectorPush(zTT7r_ziIs, sq_GetUniqueId(obj)); 
					wBYSXC9udAMy6OrtL1JZVmY.addSetStatePacket(10, zTT7r_ziIs, STATE_PRIORITY_AUTO, false, ""); 
				}
			}
			break;
	}
	break;
 	}
 	return true;
} ;

 
function onEndCurrentAni_atmage_shardmagnum(obj)
{
	if(!obj) return;
	if(!obj.sq_IsMyControlObject()) return;
	local substate = obj.getSkillSubState(); 
	switch(substate)
	{
		case 0:
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
		break;
	}
} ;


function onEndState_atmage_shardmagnum(obj, new_state)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();
	local damager = obj.getVar("dama").get_obj_vector(0);
	local atk = obj.sq_GetBonusRateWithPassive(246 , 246, 1, 1.0);

	if (damager)
	{
		sendIcecraft(obj,damager,atk);

	}
	return true;

}
