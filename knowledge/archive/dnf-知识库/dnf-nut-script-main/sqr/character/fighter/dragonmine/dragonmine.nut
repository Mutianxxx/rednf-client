



 
function checkExecutableSkill_fighter_dragonmine(yqf_5DIzoyF8CzbPt1)
{
 if(!yqf_5DIzoyF8CzbPt1) return false; 
 local qkYSIn5dj9D_EEkEgzNIq = yqf_5DIzoyF8CzbPt1.sq_IsUseSkill(234); 
 if(qkYSIn5dj9D_EEkEgzNIq) 
 {
 yqf_5DIzoyF8CzbPt1.sq_IntVectClear();
 yqf_5DIzoyF8CzbPt1.sq_IntVectPush(0); 
 yqf_5DIzoyF8CzbPt1.sq_AddSetStatePacket(234, STATE_PRIORITY_USER, true); 
 return true; 
 }
 return false; 
} ;

 
function checkCommandEnable_fighter_dragonmine(obj)
{
	if(!obj) return false; 
	return true; 
} ;

 
function onSetState_fighter_dragonmine(obj, bW_7e_9eMYmtoBT_Y, KIbeIkkOUZlNja, HmMWoaYjmtJY5bdLl2O4sM)
{
 if(!obj) return; 
 obj.sq_StopMove(); 
 obj.sq_ZStop(); 
 local VmIxpiA1ttgvd = obj.sq_GetVectorData(KIbeIkkOUZlNja, 0); 
 obj.setSkillSubState(VmIxpiA1ttgvd); 
 switch(VmIxpiA1ttgvd)
 {
 case 0: 
 obj.sq_SetCurrentAnimation(125);
 obj.getVar().clear_vector(); 
 local cfBquNMKFswa10CPucF = obj.getVar(); 
 local zpos = 140 - obj.getZPos();
 if(zpos < 0)
 {
 	zpos = 0;
 }
 cfBquNMKFswa10CPucF.push_vector(obj.getXPos());
 cfBquNMKFswa10CPucF.push_vector(obj.getZPos());
 cfBquNMKFswa10CPucF.push_vector(200);
 cfBquNMKFswa10CPucF.push_vector(zpos);

 sq_CreateDrawOnlyObject(obj, "character/fighter/effect/animation/dragonmine/start_dragonmine_dust.ani", ENUM_DRAWLAYER_BOTTOM, true); 
 break;
 case 1: 
 obj.sq_SetCurrentAnimation(126);
 if(obj.sq_IsMyControlObject())
 {
 local r2EJs9JrEjI1_e3 = sq_flashScreen(obj, 200, 99990, 0, 180, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 obj.getVar("flashobj").clear_obj_vector(); 
 obj.getVar("flashobj").push_obj_vector(r2EJs9JrEjI1_e3); 
 }
 break;
 case 2: 
 obj.sq_SetCurrentAnimation(129);
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(obj.getZPos()); 
 break;
 case 3: 
 obj.sq_SetCurrentAnimation(127);
 obj.sq_SetCurrentAttackInfo(71);
 obj.sq_SetCurrentAttackBonusRate(obj.sq_GetBonusRateWithPassive(234, 234, 0, 1.0)); 
 local GC41u3Dso_uP6cNXO2Ed = obj.sq_GetDelaySum(); 
 obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); 
 local yH77DydYqaHByNsjD4_iu = obj.sq_GetDelaySum(); 
 local lX766zGpNWICT6BXxG = GC41u3Dso_uP6cNXO2Ed.tofloat() / yH77DydYqaHByNsjD4_iu.tofloat() * 100.0; 
 CreateAniRate(obj, "character/fighter/effect/animation/dragonmine/impact_dragonmine_bottom.ani", ENUM_DRAWLAYER_BOTTOM, obj.getXPos(), obj.getYPos(), obj.getZPos(), false, lX766zGpNWICT6BXxG); 
 if(obj.sq_IsMyControlObject())
 {
 sq_SetMyShake(obj, 10, 300); 
 sq_flashScreen(obj, 50, 50, 50, 180, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 }
 break;
 case 4: 
 obj.sq_SetCurrentAnimation(128);
 if(obj.sq_IsMyControlObject())
 {
 sq_SetMyShake(obj, 10, 300); 
 obj.sq_StartWrite();
 obj.sq_WriteDword(234); 
 obj.sq_WriteDword(2); 
 obj.sq_WriteDword(obj.sq_GetBonusRateWithPassive(234, 234, 1, 1.0)); 
 obj.sq_WriteDword(obj.sq_GetLevelData(234, 2, sq_GetSkillLevel(obj, 234))); 
 obj.sq_SendCreatePassiveObjectPacket(24373, 0, 0, 0, 0);
 }
 break;
 }
 obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0); 
} ;

function onEndState_fighter_dragonmine(cqtMfksNWDg4, TEHZnGdyfyGd2M)
{
 if(!cqtMfksNWDg4) return;
 if(TEHZnGdyfyGd2M != 234) 
 {
 RemoveAllFlash(cqtMfksNWDg4); 
 local e6x0BCTkKXx = cqtMfksNWDg4.getSkillSubState(); 
 if(e6x0BCTkKXx == 4 && sq_IsEnd(cqtMfksNWDg4.getCurrentAnimation())) 
 sq_flashScreen(cqtMfksNWDg4, 0, 0, 200, 180, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM); 
 }
} ;

function onKeyFrameFlag_fighter_dragonmine(tdTesEfBcnZ4RDWnG, _xw5JfTGXbV0IkscsISRQKmr)
{
 if(!tdTesEfBcnZ4RDWnG) return false;
 local dYkkESS9Z7js0vu = tdTesEfBcnZ4RDWnG.getSkillSubState(); 
 if(dYkkESS9Z7js0vu == 4)
 {
 if(_xw5JfTGXbV0IkscsISRQKmr == 1) 
 {
 if(tdTesEfBcnZ4RDWnG.sq_IsMyControlObject())
 {
 
 local ROK0xKlP8kCGqh9VNP = sq_GetSkillLevel(tdTesEfBcnZ4RDWnG, 234); 
 tdTesEfBcnZ4RDWnG.sq_StartWrite();
 tdTesEfBcnZ4RDWnG.sq_WriteDword(234); 
 tdTesEfBcnZ4RDWnG.sq_WriteDword(1); 
 tdTesEfBcnZ4RDWnG.sq_WriteDword(tdTesEfBcnZ4RDWnG.sq_GetLevelData(234, 3, ROK0xKlP8kCGqh9VNP)); 
 tdTesEfBcnZ4RDWnG.sq_WriteDword(tdTesEfBcnZ4RDWnG.sq_GetLevelData(234, 5, ROK0xKlP8kCGqh9VNP)); 
 tdTesEfBcnZ4RDWnG.sq_WriteDword(tdTesEfBcnZ4RDWnG.sq_GetBonusRateWithPassive(234, 234, 4, 1.0)); 
 tdTesEfBcnZ4RDWnG.sq_WriteDword(tdTesEfBcnZ4RDWnG.sq_GetLevelData(234, 6, ROK0xKlP8kCGqh9VNP)); 
 tdTesEfBcnZ4RDWnG.sq_WriteDword(tdTesEfBcnZ4RDWnG.sq_GetLevelData(234, 7, ROK0xKlP8kCGqh9VNP)); 
 tdTesEfBcnZ4RDWnG.sq_WriteDword(tdTesEfBcnZ4RDWnG.sq_GetLevelData(234, 8, ROK0xKlP8kCGqh9VNP)); 
 tdTesEfBcnZ4RDWnG.sq_WriteDword(tdTesEfBcnZ4RDWnG.sq_GetLevelData(234, 9, ROK0xKlP8kCGqh9VNP)); 
 tdTesEfBcnZ4RDWnG.sq_WriteDword(tdTesEfBcnZ4RDWnG.sq_GetLevelData(234, 10, ROK0xKlP8kCGqh9VNP)); 
 tdTesEfBcnZ4RDWnG.sq_SendCreatePassiveObjectPacket(24373, 0, 0, 0, 0);
 }
 }
 }
 return true;
} ;

 
function onProc_fighter_dragonmine(Hb3jaDhVgsf4BMWiPjeE6Fh)
{
 if(!Hb3jaDhVgsf4BMWiPjeE6Fh) return;
 local BnHBHCCLS52BYfY80fqUSZIq = Hb3jaDhVgsf4BMWiPjeE6Fh.getSkillSubState(); 
 switch(BnHBHCCLS52BYfY80fqUSZIq)
 {
 case 0: 
 local UfvgED077xFNl6xjcpLBYEs = Hb3jaDhVgsf4BMWiPjeE6Fh.getCurrentAnimation(); 
 local rEARAw3LT4enhx8p1HbXL = sq_GetCurrentTime(UfvgED077xFNl6xjcpLBYEs); 
 local RuUyymHtr00S = UfvgED077xFNl6xjcpLBYEs.getDelaySum(false); 
 local q2ffVjCagXB11w = Hb3jaDhVgsf4BMWiPjeE6Fh.getVar(); 
 local VJ5zLZ3zBxBx3hKebR = q2ffVjCagXB11w.get_vector(0); 
 if(VJ5zLZ3zBxBx3hKebR != 0)
 {
 local uuTkWzMKqdAr = sq_GetDistancePos(VJ5zLZ3zBxBx3hKebR,
 Hb3jaDhVgsf4BMWiPjeE6Fh.getDirection(),
 sq_GetUniformVelocity(0, q2ffVjCagXB11w.get_vector(2), rEARAw3LT4enhx8p1HbXL, RuUyymHtr00S)); 
 if(Hb3jaDhVgsf4BMWiPjeE6Fh.isMovablePos(uuTkWzMKqdAr, Hb3jaDhVgsf4BMWiPjeE6Fh.getYPos())) 
 sq_setCurrentAxisPos(Hb3jaDhVgsf4BMWiPjeE6Fh, 0, uuTkWzMKqdAr); 
 else
 q2ffVjCagXB11w.set_vector(0, 0); 
 }
 local xuagVnZkBmkZM = q2ffVjCagXB11w.get_vector(1) + sq_GetUniformVelocity(0, q2ffVjCagXB11w.get_vector(3), rEARAw3LT4enhx8p1HbXL, RuUyymHtr00S);
 sq_setCurrentAxisPos(Hb3jaDhVgsf4BMWiPjeE6Fh, 2, xuagVnZkBmkZM); 
 break;
 case 2: 
 local UfvgED077xFNl6xjcpLBYEs = Hb3jaDhVgsf4BMWiPjeE6Fh.getCurrentAnimation(); 
 local rEARAw3LT4enhx8p1HbXL = sq_GetCurrentTime(UfvgED077xFNl6xjcpLBYEs); 
 local RuUyymHtr00S = UfvgED077xFNl6xjcpLBYEs.getDelaySum(false); 
 local xuagVnZkBmkZM = sq_GetUniformVelocity(Hb3jaDhVgsf4BMWiPjeE6Fh.getVar().get_vector(0), 0, rEARAw3LT4enhx8p1HbXL, RuUyymHtr00S);
 sq_setCurrentAxisPos(Hb3jaDhVgsf4BMWiPjeE6Fh, 2, xuagVnZkBmkZM); 
 break;
 }
} ;

 
function onEndCurrentAni_fighter_dragonmine(Tg5ThJMAPN4fhLB1)
{
 if(!Tg5ThJMAPN4fhLB1) return;
 if(!Tg5ThJMAPN4fhLB1.sq_IsMyControlObject())return;
 local AgLRPJnqNVVUuoDVc4LIjsr = Tg5ThJMAPN4fhLB1.getSkillSubState(); 
 if(AgLRPJnqNVVUuoDVc4LIjsr != 4)
 {
 Tg5ThJMAPN4fhLB1.sq_IntVectClear();
 Tg5ThJMAPN4fhLB1.sq_IntVectPush(AgLRPJnqNVVUuoDVc4LIjsr + 1); 
 Tg5ThJMAPN4fhLB1.sq_AddSetStatePacket(234, STATE_PRIORITY_USER, true); 
 }
 else
 Tg5ThJMAPN4fhLB1.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false); 
} ;

