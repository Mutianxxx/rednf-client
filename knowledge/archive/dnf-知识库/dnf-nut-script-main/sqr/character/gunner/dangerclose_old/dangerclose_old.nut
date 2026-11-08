
function checkExecutableSkill_gunner_dangerclose_old(obj)
{
	 if(!obj) return false; 
	 local ou9SclULg0Y5_sbkl0QPm = obj.sq_IsUseSkill(SKILL_DANGERCLOSE); 
	 if(ou9SclULg0Y5_sbkl0QPm) 
	 {
		obj.sq_AddSetStatePacket(STATE_DANGERCLOSE, STATE_PRIORITY_USER, false); 
	 return true; 
	 }
 return false; 
}

function checkCommandEnable_gunner_dangerclose_old(obj)
{
	if(!obj) return false; 
	return true; 
} 

function onSetState_gunner_dangerclose_old(obj, ou9SclULg0Y5_sbkl0QPm, MqglufOhkEu7yaykrwRpr, RpFy1fIv4b)
{
	 if(!obj) return; 
	 obj.sq_StopMove(); 
	 obj.sq_SetCurrentAnimation(CUSTOM_ANI_GUNNER_DANGERCLOSE); 
	 
	 obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	 
	 local coMf2eoq_Q3JL = sq_GetCurrentAnimation(obj);
	 local sw1Gh5ubCE4 = coMf2eoq_Q3JL.getDelaySum(0, 2);
	 sq_StartDrawCastGauge(obj, sw1Gh5ubCE4, true);
} 

function onEnterFrame_gunner_dangerclose_old(obj, ou9SclULg0Y5_sbkl0QPm)
{
	 if (!obj) return;
	 switch (ou9SclULg0Y5_sbkl0QPm) 
	 {
		 case 3: 
		 if(obj.sq_IsMyControlObject())
		 {
			 sq_BinaryStartWrite();
			 sq_BinaryWriteDword(1);
			 sq_SendChangeSkillEffectPacket(obj, SKILL_DANGERCLOSE); 
		 }
		 break;
	 }
} 

function onEndState_gunner_dangerclose_old(obj, ou9SclULg0Y5_sbkl0QPm)
{
	 if (!obj) return;
	 sq_EndDrawCastGauge(obj);
}  

function onChangeSkillEffect_gunner_dangerclose_old(obj, skillIndex, MqglufOhkEu7yaykrwRpr)
{
	 if(!obj || skillIndex != SKILL_DANGERCLOSE) return;
	 local RpFy1fIv4b = MqglufOhkEu7yaykrwRpr.readDword();
	 switch (RpFy1fIv4b) 
	 {
		 case 1:
		 if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/gunner/dangerclose_old/ap_dangerclose_old.nut"))
		 CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/gunner/dangerclose_old/ap_dangerclose_old.nut");
		 local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_DANGERCLOSE, false, "character/gunner/dangerclose_old/ap_dangerclose_old.nut", false);
		 local sw1Gh5ubCE4 = sq_GetSkillLevel(obj, SKILL_DANGERCLOSE);
		 local qsaOCbPXK1u4qMa8txcz = obj.sq_GetLevelData(SKILL_DANGERCLOSE, 1, sw1Gh5ubCE4); 
		 appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj),SKILL_DANGERCLOSE,sw1Gh5ubCE4); 
		 appendage.sq_SetValidTime(qsaOCbPXK1u4qMa8txcz);
		 CNSquirrelAppendage.sq_Append(appendage, obj, obj, true);
		 appendage.setBuffIconImage(71);
		 break;
	 }
} 

function onEndCurrentAni_gunner_dangerclose_old(obj)
{
	 if(!obj) return;
	 if(obj.sq_IsMyControlObject())
	 obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
} 



function getTargetObjRadian(SigNj9U9_BkIjYP1Q_g,HTlZnqtSnccc3,X7X6ReD2nSDD1TDb) 
{
 if(!SigNj9U9_BkIjYP1Q_g || !HTlZnqtSnccc3) return 0.0;
 local wVTK3HchyVCWclVR1 = sq_GetScreenXPos(SigNj9U9_BkIjYP1Q_g); 
 local U8xfrlS6I7F8WM0_zQhmH = sq_GetScreenYPos(SigNj9U9_BkIjYP1Q_g); 
 local cIfiKk3pJ90L9h = sq_GetScreenXPos(HTlZnqtSnccc3); 
 local OPe5B8gR7a = sq_GetScreenYPos(HTlZnqtSnccc3); 
 local YcMdrlBaAF_VEp3foR8PJWBG = sq_Atan2((OPe5B8gR7a - U8xfrlS6I7F8WM0_zQhmH).tofloat(),(cIfiKk3pJ90L9h - wVTK3HchyVCWclVR1).tofloat()); 
 return SigNj9U9_BkIjYP1Q_g.getDirection() == ENUM_DIRECTION_RIGHT ? sq_ToRadian((sq_ToDegree(-YcMdrlBaAF_VEp3foR8PJWBG) + X7X6ReD2nSDD1TDb)%360.0) : sq_ToRadian((sq_ToDegree(YcMdrlBaAF_VEp3foR8PJWBG) + 180.0 + X7X6ReD2nSDD1TDb)%360.0); 
}