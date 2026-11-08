// 어벤저 각성상태스킬 가드

// 상수
SUB_STATE_START		<- 0
SUB_STATE_LOOP		<- 1
SUB_STATE_END		<- 2

// state를 세팅하고 처음으로 들어오게 됩니다. 각종 리소스를 세팅합니다. 
function onSetState_AvengerGuard(obj, state, datas, isResetTimer)
{	
 	if(obj == NULL && isAvengerAwakenning(obj) == false)
 		return;

	local sq_var = obj.getVar();
	local substate = obj.sq_getVectorData(datas, 0);
	local direction = obj.sq_getVectorData(datas, 1);
	obj.setSkillSubState(substate);
	obj.sq_stopMove();

	local ani = null;
	if (substate == SUB_STATE_START)
	{
		// 스킨아바타 때문에 외부에서 애니메이션을 가지고 와야 합니다.
		ani = obj.getVar().GetAnimationMap("AVENGER_GUARD_START", "Character/Priest/Animation/AvengerGuard/AvengerGuardStart.ani");
		obj.setCurrentAnimation(ani);

		// 가드 어펜디지
		local appendage = null;
	
		if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "Appendage/Character/ap_avenger_guard.nut"))
		{
			CNSquirrelAppendage.sq_RemoveAppendage(obj, "Appendage/Character/ap_avenger_guard.nut");
		}
		
		obj.sq_PlaySound("DGUARDIAN_BACK_1");
		appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_AVENGER_GUARD, true, "Appendage/Character/ap_avenger_guard.nut", false);
				
		if (appendage) 
		{
			CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, APID_MAGIC_SHIELD, true);
		}
	}
	else if (substate == SUB_STATE_LOOP)
	{
		ani = obj.getVar().GetAnimationMap("AVENGER_GUARD_LOOP", "Character/Priest/Animation/AvengerGuard/AvengerGuardLoop.ani");
		obj.setCurrentAnimation(ani);
	}
	else if (substate == SUB_STATE_END)
	{
		if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "Appendage/Character/ap_avenger_guard.nut"))
			CNSquirrelAppendage.sq_RemoveAppendage(obj, "Appendage/Character/ap_avenger_guard.nut");
		ani = obj.getVar().GetAnimationMap("AVENGER_GUARD_END", "Character/Priest/Animation/AvengerGuard/AvengerGuardEnd.ani");
		obj.setCurrentAnimation(ani);
	}
}

// prepareDraw 함수 입니다..
function prepareDraw_AvengerGuard(obj)
{
	if(!obj) return;
}

function onDamage_AvengerGuard(obj, attacker, boundingBox)
{
	if(!obj) return;

	obj.sq_setShake(obj, 2, 300);
	return;
}

// loop 부분입니다 ismycontrol로 감싸지 않은 연결된 모든 object들이 이곳을 거치게됩니다.
function onProc_AvengerGuard(obj)
{
 	if(obj == NULL && isAvengerAwakenning(obj) == false)
 		return;
}

// loop 부분입니다 ismycontrol 호스트가 본인이 object가 이곳을 들어갑니다. setstate 세팅이나 패시브오브젝트 생성 , 등등 처리합니다.
function onProcCon_AvengerGuard(obj)
{
 	if(obj == NULL && isAvengerAwakenning(obj) == false)
 		return;
	
	local pAni = obj.sq_getCurrentAni();
	local bEnd = obj.sq_ani_IsEnd(pAni);
	local frmIndex = obj.sq_ani_GetCurrentFrameIndex(pAni);
	
	local subState = obj.getSkillSubState();
        
	if(bEnd) 
	{
		if (subState == SUB_STATE_START)
		{
 			obj.sq_IntVectClear();
 			obj.sq_IntVectPush(SUB_STATE_LOOP);
 			obj.sq_IntVectPush(obj.getDirection());
 			obj.sq_addSetStatePacket(STATE_AVENGER_GUARD, STATE_PRIORITY_USER, true);
		}
		else if (subState == SUB_STATE_LOOP)
		{
 			obj.sq_IntVectClear();
			obj.sq_IntVectPush(SUB_STATE_END);
 			obj.sq_IntVectPush(obj.getDirection());
 			obj.sq_addSetStatePacket(STATE_AVENGER_GUARD, STATE_PRIORITY_USER, true);
		}
		else if (subState == SUB_STATE_END)
		{
 			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "Appendage/Character/ap_avenger_guard.nut"))
 				CNSquirrelAppendage.sq_RemoveAppendage(obj, "Appendage/Character/ap_avenger_guard.nut");

			obj.sq_addSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
		}
	}
}

function onAfterSetState_AvengerGuard(obj, state, datas, isResetTimer)
{
 	if(obj == NULL && isAvengerAwakenning(obj) == false)
 		return;
}

function checkExecutableSkill_AvengerGuard(obj)  
{
 	if(obj == NULL && isAvengerAwakenning(obj) == false)
 		return;

	local b_useskill = obj.sq_IsUseSkill(SKILL_AVENGER_GUARD);

	if(b_useskill) 
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(SUB_STATE_START); // substate세팅
		obj.sq_IntVectPush(obj.getDirection()); // substate세팅
		obj.sq_addSetStatePacket(STATE_AVENGER_GUARD, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}	
	
	return false;
}

function checkCommandEnable_AvengerGuard(obj)
{
	// 어벤저 각성 상태에서만 사용 가능한 스킬로 평소엔 false처리합니다.
	return false;
}
