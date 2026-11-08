
 
function setCustomData_po_qq506807329new_priest_24374(obj, receiveData)
{
 if(!obj) return;
 local index = receiveData.readDword(); 
 obj.getVar("skill").clear_vector(); 
 obj.getVar("skill").push_vector(index);
 switch(index) 
 {
 case 45: 
		local ani = obj.getVar().GetAnimationMap("corkscrew45", "character/priest/effect/animation/corkscrewblow/corkscrewblowend_00.ani");
		obj.setCurrentAnimation(ani);
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
		break;
 case 46: 
		local ani = obj.getVar().GetAnimationMap("corkscrew46", "character/priest/effect/animation/corkscrewblow/corkscrewblowend_dusteffect1.ani");
		obj.setCurrentAnimation(ani);
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
		break;
 case 47: 
		local ani = obj.getVar().GetAnimationMap("corkscrew47", "character/priest/effect/animation/corkscrewblow/corkscrewblowend_dusteffect2.ani");
		obj.setCurrentAnimation(ani);
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
		break;
 case 48: 
		local ani = obj.getVar().GetAnimationMap("48", "character/priest/effect/animation/corkscrewblow/hiteffect_body.ani");
		obj.setCurrentAnimation(ani);
		sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
		break;
 case 237: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 switch(FBX7DkQlJpCUw2_mq)
 {
 case 1:
 obj.getVar().clear_vector(); 
 local yCCBbPsrbo13A252ntWLyNbm = obj.getVar(); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 if(obj.isMyControlObject())
 obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, ""); 
 break;
 case 2:
 local Kjd3nOTA21 = obj.getXPos(); 
 local YFhqDmCijFQL = obj.getYPos(); 
 obj.getVar().clear_vector(); 
 local yCCBbPsrbo13A252ntWLyNbm = obj.getVar(); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(Kjd3nOTA21);
 yCCBbPsrbo13A252ntWLyNbm.push_vector(YFhqDmCijFQL);
 yCCBbPsrbo13A252ntWLyNbm.push_vector(sq_GetDistancePos(Kjd3nOTA21, obj.getDirection(), receiveData.readDword())); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(YFhqDmCijFQL + receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 if(obj.isMyControlObject())
 obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, ""); 
 break;
 case 3:
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 1); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/destroyspirittalisman/explosion_explosion_circle_normal.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 break;
 }
 break;
 case 238: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 if(FBX7DkQlJpCUw2_mq == 1)
 {
 sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM); 
 obj.getVar().clear_vector(); 
 local yCCBbPsrbo13A252ntWLyNbm = obj.getVar(); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 obj.getVar().setBool(0, false); 
 if(obj.isMyControlObject())
 obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, ""); 
 }
 break;
 case 240: 
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/dangerousscale/dangerousscaleattackexplosion_00.ani");
 local YnPxxKH_ZPBQ4V = (receiveData.readDword()).tofloat() / 100.0; 
 XDyKOZFgVI1zXLT.setImageRateFromOriginal(YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 XDyKOZFgVI1zXLT.setAutoLayerWorkAnimationAddSizeRate(YnPxxKH_ZPBQ4V); 
 sq_SetAttackBoundingBoxSizeRate(XDyKOZFgVI1zXLT, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 4); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 local Kjd3nOTA21 = obj.getXPos();
 local YFhqDmCijFQL = obj.getYPos();
 local T8mH4uDo5ca9klihczqmOsa4 = obj.getZPos();
 CreateAniRate(obj, "character/priest/effect/animation/dangerousscale/dangerousscaleattackstoneback_00.ani", ENUM_DRAWLAYER_NORMAL, Kjd3nOTA21, YFhqDmCijFQL - 1, T8mH4uDo5ca9klihczqmOsa4, YnPxxKH_ZPBQ4V, false); 
 CreateAniRate(obj, "character/priest/effect/animation/dangerousscale/dangerousscaleattackstonefront_00.ani", ENUM_DRAWLAYER_NORMAL, Kjd3nOTA21, YFhqDmCijFQL, T8mH4uDo5ca9klihczqmOsa4, YnPxxKH_ZPBQ4V, false); 
 CreateAniRate(obj, "character/priest/effect/animation/dangerousscale/dangerousscaleattackdust_00.ani", ENUM_DRAWLAYER_NORMAL, Kjd3nOTA21, YFhqDmCijFQL + 1, T8mH4uDo5ca9klihczqmOsa4, YnPxxKH_ZPBQ4V, false); 
 CreateAniRate(obj, "character/priest/effect/animation/dangerousscale/dangerousscaleattackbottom_00.ani", ENUM_DRAWLAYER_BOTTOM, Kjd3nOTA21, YFhqDmCijFQL, T8mH4uDo5ca9klihczqmOsa4, YnPxxKH_ZPBQ4V, false); 
 break;
 case 241: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 switch(FBX7DkQlJpCUw2_mq)
 {
 case 1:
 local gU7LxqbytHx30wn0zHBDrX3d = (receiveData.readDword()).tofloat(); 
 obj.getVar().setFloat(0, gU7LxqbytHx30wn0zHBDrX3d / 300.0); 
 obj.getVar().setFloat(1, gU7LxqbytHx30wn0zHBDrX3d / 250.0); 
 obj.getVar().clear_vector(); 
 local yCCBbPsrbo13A252ntWLyNbm = obj.getVar(); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 if(obj.isMyControlObject())
 obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, ""); 
 break;
 case 2:
 local cmMMnZKv7HzDgE = receiveData.readFloat(); 
 obj.getVar().setFloat(0, cmMMnZKv7HzDgE); 
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/advanceddragon/advanceddragon_passion/attack_smallfrag.ani");
 XDyKOZFgVI1zXLT.setSpeedRate(cmMMnZKv7HzDgE); 
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 7); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 break;
 }
 break;
 case 242: 
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/nuclearpunch/nuclearpunch_attack_shockbackglow.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 8); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 break;
 case 243: 
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/demolitionpunch/demolitionpunch_c_shockb.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 9); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 break;
 case 245: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 switch(FBX7DkQlJpCUw2_mq)
 {
 case 1:
 local Kb6lUKE40cnlRDxhKLRJWmn = sq_GetCNRDObjectToSQRCharacter(obj.getParent()); 
 if(Kb6lUKE40cnlRDxhKLRJWmn)
 {
 local XDyKOZFgVI1zXLT = sq_GetCustomAni(Kb6lUKE40cnlRDxhKLRJWmn, receiveData.readDword()); 
 sq_Rewind(XDyKOZFgVI1zXLT); 
 XDyKOZFgVI1zXLT.setSpeedRate(150.0); 
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(Kb6lUKE40cnlRDxhKLRJWmn, 109); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 obj.setDirection(receiveData.readDword()); 
 obj.sq_PlaySound("R_WRATH_GOD_HIT"); 
 }
 break;
 case 2:
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(receiveData.readDword()); 
 obj.setDirection(sq_GetOppositeDirection(obj.getDirection())); 
 if(obj.isMyControlObject())
 obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, ""); 
 break;
 case 3:
 local YnPxxKH_ZPBQ4V = 2.0; 
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/wrathofgod/finishatkeff_smoke.ani");
 XDyKOZFgVI1zXLT.setImageRateFromOriginal(YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 XDyKOZFgVI1zXLT.setAutoLayerWorkAnimationAddSizeRate(YnPxxKH_ZPBQ4V); 
 sq_SetAttackBoundingBoxSizeRate(XDyKOZFgVI1zXLT, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 10); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 obj.sq_PlaySound("WRATH_GOD_EXP"); 
 break;
 case 4:
 local Kb6lUKE40cnlRDxhKLRJWmn = sq_GetCNRDObjectToSQRCharacter(obj.getParent()); 
 if(Kb6lUKE40cnlRDxhKLRJWmn)
 {
 local XDyKOZFgVI1zXLT = sq_GetCustomAni(Kb6lUKE40cnlRDxhKLRJWmn, 158); 
 sq_Rewind(XDyKOZFgVI1zXLT); 
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 }
 break;
 }
 break;
 case 248: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 switch(FBX7DkQlJpCUw2_mq)
 {
 case 1:
 local Kb6lUKE40cnlRDxhKLRJWmn = sq_GetCNRDObjectToSQRCharacter(obj.getParent()); 
 if(Kb6lUKE40cnlRDxhKLRJWmn)
 Kb6lUKE40cnlRDxhKLRJWmn.getVar().push_obj_vector(obj); 
 sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM); 
 obj.getVar().clear_vector(); 
 local yCCBbPsrbo13A252ntWLyNbm = obj.getVar(); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 if(obj.isMyControlObject())
 obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, ""); 
 break;
 }
 break;
 case 249: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 switch(FBX7DkQlJpCUw2_mq)
 {
 case 0:
 sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_COVER); 
 obj.getVar().clear_vector(); 
 local yCCBbPsrbo13A252ntWLyNbm = obj.getVar(); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(obj.getYPos()); 
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "character/priest/effect/animation/spearofdestiny/spearofdestiny_bgeff_cloud01.ani"); 
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local w0t2fbe9au3 = sq_CreateDrawOnlyObject(obj, "character/priest/effect/animation/spearofdestiny/spearofdestiny_usereff_glow04.ani", ENUM_DRAWLAYER_COVER, true); 
 obj.getVar("aniobj").clear_obj_vector(); 
 obj.getVar("aniobj").push_obj_vector(w0t2fbe9au3); 
 local kJznxpzJ8H = obj.getParent(); 
 if(kJznxpzJ8H && !kJznxpzJ8H.isMyControlObject()) 
 {
 sq_setCurrentAxisPos(obj, 2, 99999); 
 sq_setCurrentAxisPos(w0t2fbe9au3, 2, 99999); 
 }
 break;
 case 1:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/spearofdestiny/spearofdestiny_dropspear_thunder.ani"); 
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 13); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 obj.getVar().clear_vector(); 
 local yCCBbPsrbo13A252ntWLyNbm = obj.getVar(); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 yCCBbPsrbo13A252ntWLyNbm.push_vector(receiveData.readDword()); 
 break;
 case 2:
 sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM); 
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/spearofdestiny/spearofdestiny_explosion_floor_eff06.ani"); 
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 14); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 break;
 case 3:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/spearofdestiny/spearofdestiny_explosion_back_eff01.ani"); 
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 15); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 sq_SetMyShake(obj, 4, 180); 
 break;
 }
 break;
 case 250: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 switch(FBX7DkQlJpCUw2_mq)
 {
 case 1:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/jupiter/jupiterhammerlightningtower.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 16); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 break;
 case 2:
 local YnPxxKH_ZPBQ4V = 0.5; 
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/jupiter/jupiterhammerupperadd_addeff_a.ani");
 XDyKOZFgVI1zXLT.setImageRateFromOriginal(YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 XDyKOZFgVI1zXLT.setAutoLayerWorkAnimationAddSizeRate(YnPxxKH_ZPBQ4V); 
 sq_SetAttackBoundingBoxSizeRate(XDyKOZFgVI1zXLT, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 17); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 break;
 case 3:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/jupiter/jupiterhammerdashatk_floor_dodge.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local p4wp4yPlGRyJFlLEwQ = receiveData.readDword(); 
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(p4wp4yPlGRyJFlLEwQ); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 18); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, p4wp4yPlGRyJFlLEwQ); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 obj.sq_PlaySound("R_THUNDERHAMMER_ATK_ELEC");
 break;
 case 4:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/jupiter/jupiterhammerupperadd_addeff_a.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 17); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 break;
 case 8:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/chang_qing_skill/priest/animation/divineflash/DivineFlash_Multi_Explosion.ani");
 local dgsydsaudadddds = receiveData.readDword()/100.0;
 XDyKOZFgVI1zXLT.setImageRateFromOriginal(dgsydsaudadddds, dgsydsaudadddds);
 sq_SetAttackBoundingBoxSizeRate(XDyKOZFgVI1zXLT, 1.0, 1.0, 1.0);
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 17); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 break;
 }
 obj.sq_PlaySound("R_THUNDERHAMMER_ATK_ELEC"); 
 break;
 case 251: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 switch(FBX7DkQlJpCUw2_mq)
 {
 case 1:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/divinepunishment/boom_04.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 20); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/priest/animation/divinepunishment/boom_floor_01.ani", ENUM_DRAWLAYER_BOTTOM, true); 
 sq_SetMyShake(obj, 3, 100); 
 break;
 case 2:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/divinepunishment/finish01_09.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 21); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 sq_SetMyShake(obj, 6, 400); 
 break;
 }
 break;
 case 246: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 switch(FBX7DkQlJpCUw2_mq)
 {
 case 1:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/haptism/haptism1front_1.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 22); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 break;
 case 2:
 sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM); 
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/haptism/haptism1floor_1.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 23); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 break;
 case 3:
 sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM); 
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/haptism/haptism2floor_1.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 24); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 sq_SetMyShake(obj, 3, 160); 
 sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/priest/animation/haptism/haptism2front_1.ani", ENUM_DRAWLAYER_NORMAL, true); 
 break;
 }
 break;
 case 135: 
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/devilfist/explosion_08.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 25); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 local YnPxxKH_ZPBQ4V = receiveData.readFloat(); 
 XDyKOZFgVI1zXLT.setImageRateFromOriginal(YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 XDyKOZFgVI1zXLT.setAutoLayerWorkAnimationAddSizeRate(YnPxxKH_ZPBQ4V); 
 sq_SetAttackBoundingBoxSizeRate(XDyKOZFgVI1zXLT, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 break;
 case 136: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 switch(FBX7DkQlJpCUw2_mq)
 {
 case 1:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/darkhowling/dh1_shockwave_normal.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, receiveData.readDword()); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 local GqW9dldQ22 = receiveData.readDword(); 
 sq_SetChangeStatusIntoAttackInfo(wBlSHj6I3y9tynDX3BUk, 0, ACTIVESTATUS_CURSE, receiveData.readDword(), receiveData.readDword(), receiveData.readDword(), GqW9dldQ22, GqW9dldQ22, GqW9dldQ22, GqW9dldQ22); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 local PUQJpw1BLjMiz0 = receiveData.readDword(); 
 if(PUQJpw1BLjMiz0 != 0)
 obj.setTimeEvent(0, XDyKOZFgVI1zXLT.getDelaySum(0, 4) / PUQJpw1BLjMiz0, PUQJpw1BLjMiz0 - 1, false); 
 obj.getVar().clear_obj_vector(); 
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(receiveData.readDword()); 
 sq_SetMyShake(obj, 4, 200); 
 break;
 case 2:
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(receiveData.readDword()); 
 if(obj.isMyControlObject())
 obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, ""); 
 break;
 case 3:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/darkhowling/shock_dodge.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 28); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 local GqW9dldQ22 = receiveData.readDword(); 
 sq_SetChangeStatusIntoAttackInfo(wBlSHj6I3y9tynDX3BUk, 0, ACTIVESTATUS_CURSE, receiveData.readDword(), receiveData.readDword(), receiveData.readDword(), GqW9dldQ22, GqW9dldQ22, GqW9dldQ22, GqW9dldQ22); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 obj.getVar().clear_obj_vector(); 
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(receiveData.readDword()); 
 sq_SetMyShake(obj, 4, 200); 
 sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/priest/animation/darkhowling/circle_normal.ani", ENUM_DRAWLAYER_BOTTOM, true); 
 break;
 }
 break;
 case 137: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 switch(FBX7DkQlJpCUw2_mq)
 {
 case 1:
 local esPvN8WgPY = "passiveobject/script_sqr_nut_qq506807329/priest/animation/doomcrush/doomcrush_boom_finish_20.ani"; 
 if(receiveData.readDword() == 2) 
 esPvN8WgPY = "passiveobject/script_sqr_nut_qq506807329/priest/animation/doomcrush/doomcrush_boom_finish_charge_24.ani"; 
 obj.setCurrentAnimation(sq_CreateAnimation("", esPvN8WgPY)); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 29); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 local p4wp4yPlGRyJFlLEwQ = receiveData.readDword(); 
 if(obj.isMyControlObject())
 {
 sq_BinaryStartWrite();
 sq_BinaryWriteDword(137); 
 sq_BinaryWriteDword(2); 
 sq_BinaryWriteDword(p4wp4yPlGRyJFlLEwQ); 
 sq_SendCreatePassiveObjectPacket(obj, 24374, 0, 0, 0, 0, obj.getDirection());
 }
 obj.getVar().clear_obj_vector(); 
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(receiveData.readDword()); 
 obj.getVar().setBool(0, false); 
 break;
 case 2:
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 30); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 break;
 }
 break;
 case 139: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 switch(FBX7DkQlJpCUw2_mq)
 {
 case 1:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/metamorphosis/change/change_dodge.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 31); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 local YnPxxKH_ZPBQ4V = (receiveData.readDword()).tofloat() / 100.0; 
 XDyKOZFgVI1zXLT.setImageRateFromOriginal(YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 XDyKOZFgVI1zXLT.setAutoLayerWorkAnimationAddSizeRate(YnPxxKH_ZPBQ4V); 
 sq_SetAttackBoundingBoxSizeRate(XDyKOZFgVI1zXLT, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 break;
 case 2:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/metamorphosis/quakearea/quakearea_shock.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 36); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 local YnPxxKH_ZPBQ4V = (receiveData.readDword()).tofloat() / 100.0; 
 XDyKOZFgVI1zXLT.setImageRateFromOriginal(YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 XDyKOZFgVI1zXLT.setAutoLayerWorkAnimationAddSizeRate(YnPxxKH_ZPBQ4V); 
 sq_SetAttackBoundingBoxSizeRate(XDyKOZFgVI1zXLT, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/priest/animation/metamorphosis/quakearea/quakeareaearth.ani", ENUM_DRAWLAYER_BOTTOM, true); 
 sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/priest/animation/metamorphosis/quakearea/quakeareastone.ani", ENUM_DRAWLAYER_BOTTOM, true) 
 break;
 case 3:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/metamorphosis/awakening/awakeningend_dodge.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 37); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 local YnPxxKH_ZPBQ4V = (receiveData.readDword()).tofloat() / 100.0; 
 XDyKOZFgVI1zXLT.setImageRateFromOriginal(YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 XDyKOZFgVI1zXLT.setAutoLayerWorkAnimationAddSizeRate(YnPxxKH_ZPBQ4V); 
 sq_SetAttackBoundingBoxSizeRate(XDyKOZFgVI1zXLT, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V, YnPxxKH_ZPBQ4V); 
 break;
 }
 break;
 case 132: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 switch(FBX7DkQlJpCUw2_mq)
 {
 case 1:
 local Zekm4TMtYJZfOxVrbN = receiveData.readDword(); 
 local XDyKOZFgVI1zXLT = null; 
 switch(Zekm4TMtYJZfOxVrbN)
 {
 case 1:XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/inviteofdevil/devilinvitation_right_04.ani"); break;
 case 2:XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/inviteofdevil/devilinvitation_w_right_03.ani"); break;
 }
 XDyKOZFgVI1zXLT.setSpeedRate(receiveData.readFloat()); 
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 32); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(Zekm4TMtYJZfOxVrbN); 
 break;
 case 2:
 local Zekm4TMtYJZfOxVrbN = receiveData.readDword(); 
 local XDyKOZFgVI1zXLT = null; 
 switch(Zekm4TMtYJZfOxVrbN)
 {
 case 1:XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/inviteofdevil/devilinvitation_left_03.ani"); break;
 case 2:XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/inviteofdevil/devilinvitation_w_left_04.ani"); break;
 }
 XDyKOZFgVI1zXLT.setSpeedRate(receiveData.readFloat()); 
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 32); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 obj.getVar().clear_vector(); 
 obj.getVar().push_vector(Zekm4TMtYJZfOxVrbN); 
 obj.getVar().push_vector(receiveData.readDword()); 
 break;
 case 3:
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/inviteofdevil/devilinvitation_boom_04.ani");
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 33); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 break;
 }
 break;
 case 116: 
 local FBX7DkQlJpCUw2_mq = receiveData.readDword(); 
 obj.getVar("subType").clear_vector(); 
 obj.getVar("subType").push_vector(FBX7DkQlJpCUw2_mq);
 if(FBX7DkQlJpCUw2_mq == 1)
 {
 local kJznxpzJ8H = obj.getParent(); 
 if(kJznxpzJ8H) sq_moveWithParent(kJznxpzJ8H, obj); 
 local XDyKOZFgVI1zXLT = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/priest/animation/hedgehog/thorn_normal.ani");
 XDyKOZFgVI1zXLT.setSpeedRate(receiveData.readFloat()); 
 obj.setCurrentAnimation(XDyKOZFgVI1zXLT); 
 local wBlSHj6I3y9tynDX3BUk = sq_GetCustomAttackInfo(obj, 34); 
 sq_SetCurrentAttackBonusRate(wBlSHj6I3y9tynDX3BUk, receiveData.readDword()); 
 sq_SetCurrentAttackInfo(obj, wBlSHj6I3y9tynDX3BUk); 
 }
 break;
 default: 
 break;
 }
} ;
 
