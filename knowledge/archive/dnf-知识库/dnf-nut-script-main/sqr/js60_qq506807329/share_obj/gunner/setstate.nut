

function setState_po_qq506807329new_gunner_24371(obj, state, datas) {
	if (!obj) return;
	sq_IntVectorClear(sq_GetGlobalIntVector());
	obj.getVar("state").clear_vector();
	obj.getVar("state").push_vector(state);
	local index = obj.getVar("skill").get_vector(0);
	switch (index) {
		case 251:
			local subType = obj.getVar("subType").get_vector(0);
			switch (subType) {
				case 1:
				case 2:
				case 3:
				case 4:
					switch (state) {
						case PASSIVEOBJ_SUB_STATE_0:
							if (obj.isMyControlObject()){
								sq_SetShake(obj, 3, 200);
							}
							local aLZ3A39p1UwcHqh9r = createPooledObjEff_qq506807329(obj, "character/gunner/effect/animation/dangerclose/dangertarget.ani", obj.getVar().get_vector(0), obj.getVar().get_vector(1), 0, ENUM_DRAWLAYER_BOTTOM, obj.getDirection());
							obj.setCustomRotate(true, getTargetObjRadian(obj, aLZ3A39p1UwcHqh9r, 90.0));
							local ani = obj.getVar().GetAnimationMap("dangershell", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose_old/dangershell.ani");
							obj.setCurrentAnimation(ani);
							local attackInfo = sq_GetCustomAttackInfo(obj, 33);
							sq_SetCurrentAttackInfo(obj, attackInfo);
							local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
							sq_SetCurrentAttackBonusRate(currentAttackInfo, obj.getVar().get_vector(3));
							
							obj.getVar("move").setFloat(0, getTargetObjRadian(obj, aLZ3A39p1UwcHqh9r, 0.0));
							obj.getVar("move").clear_vector();
							obj.getVar("move").push_vector(obj.getXPos());
							obj.getVar("move").push_vector(obj.getYPos());
							obj.getVar("move").push_vector(obj.getZPos());
							obj.getVar("move").clear_timer_vector();
							obj.getVar("move").push_timer_vector();
							local UnDSZ0Mnw8CmOe85TvnNZKM = obj.getVar("move").get_timer_vector(0);
							UnDSZ0Mnw8CmOe85TvnNZKM.setParameter(40, -1);
							UnDSZ0Mnw8CmOe85TvnNZKM.resetInstant(0);
							obj.getVar("move").push_timer_vector();
							UnDSZ0Mnw8CmOe85TvnNZKM = obj.getVar("move").get_timer_vector(1);
							UnDSZ0Mnw8CmOe85TvnNZKM.setParameter(120, -1);
							UnDSZ0Mnw8CmOe85TvnNZKM.resetInstant(0);
							break;
						case PASSIVEOBJ_SUB_STATE_1:
							obj.setCustomRotate(false, 0.0);
							local size = obj.getVar().get_vector(7).tofloat() / 100.0;
							local ani = null;
							local attackInfo = null;
							local attackBonus = obj.getVar().get_vector(8);
							switch (subType) {
								case 1:
									ani = obj.getVar().GetAnimationMap("dangerboom_01", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose_old/dangerboom_01.ani");
									attackInfo = sq_GetCustomAttackInfo(obj, 34);
									sq_SetCurrentAttackInfo(obj, attackInfo);
									local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
									sq_SetCurrentAttackBonusRate(currentAttackInfo, attackBonus);
									break;
								case 2:
									ani = obj.getVar().GetAnimationMap("dangerboom_05", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose/dangerboomfire_01.ani");
									attackInfo = sq_GetCustomAttackInfo(obj, 35);
									sq_SetCurrentAttackInfo(obj, attackInfo);
									local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
									sq_SetCurrentAttackBonusRate(currentAttackInfo, attackBonus);
									if (obj.isMyControlObject()) {
										sq_BinaryStartWrite();
										sq_BinaryWriteDword(251);
										sq_BinaryWriteDword(5);
										sq_BinaryWriteDword(obj.getVar().get_vector(4));
										sq_BinaryWriteDword(obj.getVar().get_vector(5));
										sq_BinaryWriteDword(obj.getVar().get_vector(6));
										sq_BinaryWriteDword(obj.getVar().get_vector(7));
										sq_SendCreatePassiveObjectPacket(obj, 24371, 0, 0, 0, 0, obj.getDirection());
									}
									break;
								case 3:
									ani = obj.getVar().GetAnimationMap("dangerboomice_01", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose_old/dangerboomice_01.ani");
									attackInfo = sq_GetCustomAttackInfo(obj, 36);
									sq_SetCurrentAttackInfo(obj, attackInfo);
									local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
									sq_SetCurrentAttackBonusRate(currentAttackInfo, attackBonus);
									sq_SetChangeStatusIntoAttackInfo(currentAttackInfo, 0, ACTIVESTATUS_FREEZE, obj.getVar().get_vector(9), obj.getVar().get_vector(11), obj.getVar().get_vector(10));
									break;
								case 4:
									ani = obj.getVar().GetAnimationMap("dangerboomlight_01", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose_old/dangerboomlight_01.ani");
									attackInfo = sq_GetCustomAttackInfo(obj, 37);
									sq_SetCurrentAttackInfo(obj, attackInfo);
									local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
									sq_SetCurrentAttackBonusRate(currentAttackInfo, attackBonus);
									sq_SetChangeStatusIntoAttackInfoWithEtc(currentAttackInfo, 0, ACTIVESTATUS_LIGHTNING, obj.getVar().get_vector(9), obj.getVar().get_vector(11), obj.getVar().get_vector(10), obj.getVar().get_vector(12), 0);
									break;
							}
							obj.setCurrentAnimation(ani);
							local currentAni = obj.getCurrentAnimation();
							currentAni.setImageRateFromOriginal(size, size);
							currentAni.setAutoLayerWorkAnimationAddSizeRate(size);
							sq_SetAttackBoundingBoxSizeRate(currentAni, size, size, size);
							break;
					}
					break;
				case 5:
					switch (state) {
						case PASSIVEOBJ_SUB_STATE_0:
							sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
							local size = obj.getVar().get_vector(3).tofloat() / 100.0;
							local ani = obj.getVar().GetAnimationMap("dangergroundnew_01", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose_old/dangergroundnew_01.ani");
							obj.setCurrentAnimation(ani);
							
							ani = obj.getCurrentAnimation();
							ani.setImageRateFromOriginal(size, size);
							ani.setAutoLayerWorkAnimationAddSizeRate(size);
							sq_SetAttackBoundingBoxSizeRate(ani, size, size, size);
							
							local attackInfo = sq_GetCustomAttackInfo(obj, 38);
							sq_SetCurrentAttackInfo(obj, attackInfo);
							local currentAttackInfo = sq_GetCurrentAttackInfo(obj);
							sq_SetCurrentAttackBonusRate(currentAttackInfo, obj.getVar().get_vector(0));
							
							obj.getVar("attack").clear_timer_vector();
							obj.getVar("attack").push_timer_vector();
							local UnDSZ0Mnw8CmOe85TvnNZKM = obj.getVar("attack").get_timer_vector(0);
							UnDSZ0Mnw8CmOe85TvnNZKM.setParameter(obj.getVar().get_vector(1), obj.getVar().get_vector(2));
							UnDSZ0Mnw8CmOe85TvnNZKM.resetInstant(0);
							break;
						case PASSIVEOBJ_SUB_STATE_1:
							local size = obj.getVar().get_vector(3) / 100.0;
							local ani = obj.getVar().GetAnimationMap("dangergroundend", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose_old/dangergroundend.ani");
							obj.setCurrentAnimation(ani);
							
							ani = obj.getCurrentAnimation();
							ani.setImageRateFromOriginal(size, size);
							ani.setAutoLayerWorkAnimationAddSizeRate(size);
							break;
					}
					break;
			}
			break;
		case 234:
			if (state == 10) {
				if (obj.isExistTimeEvent(0)) obj.stopTimeEvent(0);
				sq_moveWithParent(obj, obj);
				local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/plasmaboost/plasmaboostlaserend_00.ani");
				obj.setCurrentAnimation(ani);
			}
			break;
		case 232:
			switch (state) {
				case 10:
					local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/msc7/missile_01.ani");
					obj.setCurrentAnimation(ani);
					obj.getVar().clear_obj_vector();
					break;
				case 11:
					obj.sq_RemoveMoveParticle();
					obj.getVar("move").clear_vector();
					obj.getVar("move").push_vector(obj.getXPos());
					obj.getVar("move").push_vector(sq_GetObjectTime(obj));
					break;
				case 12:
					obj.sq_RemoveMoveParticle();

					sq_setCurrentAxisPos(sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/msc7/explosion_bottom.ani", ENUM_DRAWLAYER_BOTTOM, true), 2, 0);
					local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/msc7/explosion_08.ani");
					local AmGI1Q1kUH6f27cw = (obj.getVar().get_vector(0)).tofloat() / 100.0;
					ani.setImageRateFromOriginal(AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw);
					ani.setAutoLayerWorkAnimationAddSizeRate(AmGI1Q1kUH6f27cw);
					sq_SetAttackBoundingBoxSizeRate(ani, AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw);
					obj.setCurrentAnimation(ani);
					sq_SetCurrentAttackInfoFromCustomIndex(obj, 1);
					break;
			}
			break;
		case 233:
			local subType = obj.getVar("subType").get_vector(0);
			switch (subType) {
				case 1:
					switch (state) {
						case 10:
							sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
							local ani = sq_CreateAnimation("", "character/gunner/effect/animation/seismicwave/casting/gunnercursor-dodge_start.ani");
							obj.setCurrentAnimation(ani);
							break;
						case 11:
							obj.setCurrentPos(sq_GetVectorData(datas, 0), sq_GetVectorData(datas, 1), 0);
							local ani = sq_CreateAnimation("", "character/gunner/effect/animation/seismicwave/casting/gunnercursor-dodge_end.ani");
							obj.setCurrentAnimation(ani);
							break;
						case 12:
							sq_setCurrentAxisPos(obj, 2, 1000);
							sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
							local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/seismicwave/drop/drop_seismicwave.ani");
							obj.setCurrentAnimation(ani);
							sq_SetCurrentAttackInfoFromCustomIndex(obj, 2);
							break;
						case 13:
							local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/seismicwave/start/start_seismicwave.ani");
							obj.setCurrentAnimation(ani);
							sq_SetCurrentAttackInfoFromCustomIndex(obj, 3);
							if (obj.isMyControlObject()) {
								sq_SetMyShake(obj, 4, 300);
								sq_flashScreen(obj, 0, 40, 200, 204, sq_RGB(255, 255, 255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
								sq_BinaryStartWrite();
								sq_BinaryWriteDword(233);
								sq_BinaryWriteDword(3);
								sq_BinaryWriteDword(obj.getVar().get_vector(3));
								sq_SendCreatePassiveObjectPacket(obj, 24371, 0, 0, 0, 0, obj.getDirection());
							}
							break;
						case 14:
							obj.getVar().set_vector(4, obj.getVar().get_vector(4) - 1);
							local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/seismicwave/loop/loop_seismicwave.ani");
							ani.setSpeedRate((obj.getVar().get_vector(5)).tofloat());
							obj.setCurrentAnimation(ani);
							if (obj.isMyControlObject()) {
								sq_SetMyShake(obj, 5, 180);
								sq_flashScreen(obj, 0, 0, 120, 153, sq_RGB(0, 0, 0), GRAPHICEFFECT_LINEARDODGE, ENUM_DRAWLAYER_BOTTOM);
								sq_BinaryStartWrite();
								sq_BinaryWriteDword(233);
								sq_BinaryWriteDword(2);
								sq_BinaryWriteDword(obj.getVar().get_vector(3));
								sq_BinaryWriteDword(obj.getVar().get_vector(6));
								sq_BinaryWriteDword(obj.getVar().get_vector(7));
								sq_BinaryWriteDword(obj.getVar().get_vector(8));
								sq_SendCreatePassiveObjectPacket(obj, 24371, 0, 0, 0, 0, obj.getDirection());
							}
							break;
						case 15:
							local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/seismicwave/end/end_exp_dodge.ani");
							obj.setCurrentAnimation(ani);
							sq_SetCurrentAttackInfoFromCustomIndex(obj, 5);
							sq_SetMyShake(obj, 3, 300);
							break;
					}
					break;
			}
			break;
		case 242:
			switch (state) {
				case 10:
					local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/grenadegravity/grenadegravity_grenade_normal.ani");
					obj.setCurrentAnimation(ani);
					break;
				case 11:
					local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/grenadegravity/grenadegravity_grenade_normal.ani");
					local kaSzGNd2aLDWQV4Y = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/grenadegravity/grenadegravity_grenade_dodge.ani");
					ani.addLayerAnimation(-1, kaSzGNd2aLDWQV4Y, true);
					obj.setCurrentAnimation(ani);
					obj.setTimeEvent(0, 50, 1, false);
					break;
				case 12:
					sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
					local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/grenadegravity/01_start/grenadegravity_start_background.ani");
					local AmGI1Q1kUH6f27cw = (obj.getVar().get_vector(2)).tofloat() / 100.0;
					ani.setImageRateFromOriginal(AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw);
					ani.setAutoLayerWorkAnimationAddSizeRate(AmGI1Q1kUH6f27cw);
					obj.setCurrentAnimation(ani);

					CreateAniRate(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/grenadegravity/01_start/grenadegravity_start_front.ani", ENUM_DRAWLAYER_NORMAL, obj.getXPos(), obj.getYPos(), obj.getZPos(), AmGI1Q1kUH6f27cw, false);
					CreateAniRate(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/grenadegravity/01_start/grenadegravity_start_background01.ani", ENUM_DRAWLAYER_NORMAL, obj.getXPos(), obj.getYPos(), obj.getZPos(), AmGI1Q1kUH6f27cw, false);
					break;
				case 13:
					local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/grenadegravity/02_loop/grenadegravity_loop_background.ani");
					local AmGI1Q1kUH6f27cw = (obj.getVar().get_vector(2)).tofloat() / 100.0;
					ani.setImageRateFromOriginal(AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw);
					ani.setAutoLayerWorkAnimationAddSizeRate(AmGI1Q1kUH6f27cw);
					sq_SetAttackBoundingBoxSizeRate(ani, AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw, 1.0);
					obj.setCurrentAnimation(ani);
					sq_SetCurrentAttackInfoFromCustomIndex(obj, 15);
					obj.setTimeEvent(1, obj.getVar().get_vector(1), 0, false);
					obj.setTimeEvent(2, obj.getVar().get_vector(0), 1, false);
					break;
				case 14:
					obj.removeAllTimeEvent();
					sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
					local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/grenadegravity/03_finish/grenadegravity_finish_front.ani");
					local AmGI1Q1kUH6f27cw = (obj.getVar().get_vector(2)).tofloat() / 100.0;
					ani.setImageRateFromOriginal(AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw);
					ani.setAutoLayerWorkAnimationAddSizeRate(AmGI1Q1kUH6f27cw);
					sq_SetAttackBoundingBoxSizeRate(ani, AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw);
					obj.setCurrentAnimation(ani);
					sq_SetCurrentAttackInfoFromCustomIndex(obj, 16);

					CreateAniRate(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/grenadegravity/03_finish/grenadegravity_finish_background.ani", ENUM_DRAWLAYER_BOTTOM, obj.getXPos(), obj.getYPos(), obj.getZPos(), AmGI1Q1kUH6f27cw, false);
					break;
			}
			break;
		case 243:
			local subType = obj.getVar("subType").get_vector(0);
			switch (subType) {
				case 1:
					if (state == 10) {
						if (obj.isMyControlObject()) {
							local ani = sq_CreateAnimation("", "character/gunner/effect/animation/dangerclose/dangerclose.ani");
							obj.setCurrentAnimation(ani);
						}
					} else if (state == 11) {
						obj.setCurrentAnimation(null);
						sq_setCurrentAxisPos(obj, 0, sq_GetVectorData(datas, 0));
						sq_setCurrentAxisPos(obj, 1, sq_GetVectorData(datas, 1));
						sq_SetCurrentDirection(obj, sq_GetVectorData(datas, 2));
						obj.getVar().setInt(0, sq_GetVectorData(datas, 3));
						obj.setTimeEvent(0, obj.getVar().get_vector(2), 0, true);
					}
					break;
				case 2:
					if (state == 10) {
						obj.removeAllTimeEvent();
						sq_SetCustomRotate(obj, 0.0);
						local HObjTePwsiNv20Z4igY5mO = obj.getVar().get_vector(4);
						local path = "";
						switch (HObjTePwsiNv20Z4igY5mO) {
							case 17:
								path = "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose/dangerboom_01.ani";
								break;
							case 18:
								path = "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose/dangerboomfire_01.ani";
								break;
							case 19:
								path = "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose/dangerboomlight_01.ani";
								break;
							case 20:
								path = "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose/dangerboomice_01.ani";
								break;
						}
						local ani = sq_CreateAnimation("", path);
						obj.setCurrentAnimation(ani);

						sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose/dangerground.ani", ENUM_DRAWLAYER_BOTTOM, true);
						sq_SetMyShake(obj, 3, 200);
					}
					break;
			}
			break;
		case 244:
			switch (state) {
				case 10:
					obj.sq_PlaySound("G_38ARG_THROW");
					local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/g-38arg/g-38argthrow.ani");
					obj.setCurrentAnimation(ani);
					obj.setTimeEvent(0, obj.getVar().get_vector(0), 1, false);
					break;
				case 11:
					obj.sq_RemoveMoveParticle();
					local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/g-38arg/g-38argmove.ani");
					obj.setCurrentAnimation(ani);
					obj.getVar().clear_obj_vector();
					obj.setTimeEvent(1, 200, 1, false);
					obj.getVar().setBool(1, false);
					if (obj.isMyControlObject()) {

						local l_fYXYOe38bDkKOX = null;
						local hYIYXjYCWrBWM8jPfInD = 0;

						local aqxQSx_N8drux = obj.getObjectManager();
						for (local qIDlmOSolDW4_633998x5cr4 = 0; qIDlmOSolDW4_633998x5cr4 < aqxQSx_N8drux.getCollisionObjectNumber(); qIDlmOSolDW4_633998x5cr4++) {
							local BUBlLPsc8j1 = aqxQSx_N8drux.getCollisionObject(qIDlmOSolDW4_633998x5cr4);

							if (!BUBlLPsc8j1 ||
								!obj.isEnemy(BUBlLPsc8j1) ||
								!BUBlLPsc8j1.isObjectType(OBJECTTYPE_ACTIVE) ||
								!BUBlLPsc8j1.isInDamagableState(obj) ||
								CNSquirrelAppendage.sq_IsAppendAppendage(BUBlLPsc8j1, "character/gunner/g38arg/ap_g38arg.nut")) continue;
							BUBlLPsc8j1 = sq_GetCNRDObjectToActiveObject(BUBlLPsc8j1);
							if (BUBlLPsc8j1.isDead() || BUBlLPsc8j1.getState == STATE_DIE) continue;
							local dM4lXPPMIxZC5e38_Cc = BUBlLPsc8j1.getHp();
							if (dM4lXPPMIxZC5e38_Cc > hYIYXjYCWrBWM8jPfInD) {
								hYIYXjYCWrBWM8jPfInD = dM4lXPPMIxZC5e38_Cc;
								l_fYXYOe38bDkKOX = BUBlLPsc8j1;
							}
						}
						if (l_fYXYOe38bDkKOX != null) {
							sq_BinaryStartWrite();
							sq_BinaryWriteDword(sq_GetGroup(l_fYXYOe38bDkKOX));
							sq_BinaryWriteDword(sq_GetUniqueId(l_fYXYOe38bDkKOX));
							sq_BinaryWriteWord(
								(obj.getXPos() > l_fYXYOe38bDkKOX.getXPos()) ? ENUM_DIRECTION_LEFT : ENUM_DIRECTION_RIGHT
							);
							sq_SendChangeSkillEffectPacket(obj, 244);
						} else {
							obj.addSetStatePacket(14, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
							obj.flushSetStatePacket();
							return;
						}
					}
					break;
				case 12:
					local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/g-38arg/g-38argnonattack.ani");
					obj.setCurrentAnimation(ani);
					local pDx5klG1fY = sq_GetVectorData(datas, 0);
					if (pDx5klG1fY != 1) return;
					local l_fYXYOe38bDkKOX = sq_GetCNRDObjectToActiveObject(obj.getVar().get_obj_vector(0));
					if (l_fYXYOe38bDkKOX && !l_fYXYOe38bDkKOX.isDead()) {
						obj.setCurrentPos(l_fYXYOe38bDkKOX.getXPos(), l_fYXYOe38bDkKOX.getYPos(), l_fYXYOe38bDkKOX.getZPos() + sq_GetObjectHeight(l_fYXYOe38bDkKOX) / 2);
						sq_moveWithParent(l_fYXYOe38bDkKOX, obj);

						local X4NPA_WZwyDzVf = CNSquirrelAppendage.sq_GetAppendage(l_fYXYOe38bDkKOX, "character/gunner/g38arg/ap_g38arg.nut");
						if (X4NPA_WZwyDzVf)
							CNSquirrelAppendage.sq_RemoveAppendage(l_fYXYOe38bDkKOX, "character/gunner/g38arg/ap_g38arg.nut");
						X4NPA_WZwyDzVf = CNSquirrelAppendage.sq_AppendAppendage(l_fYXYOe38bDkKOX, obj, 244, true, "character/gunner/g38arg/ap_g38arg.nut", true);
						if (X4NPA_WZwyDzVf) {
							X4NPA_WZwyDzVf.getVar().clear_vector();
							local tRGzb0J0g8 = obj.getVar();
							local KfaJE8AgF8bcqnp2qGL = X4NPA_WZwyDzVf.getVar();
							KfaJE8AgF8bcqnp2qGL.push_vector(tRGzb0J0g8.get_vector(1));
							KfaJE8AgF8bcqnp2qGL.push_vector(tRGzb0J0g8.get_vector(2));
							KfaJE8AgF8bcqnp2qGL.push_vector(tRGzb0J0g8.get_vector(3));
							KfaJE8AgF8bcqnp2qGL.push_vector(tRGzb0J0g8.get_vector(4));
							KfaJE8AgF8bcqnp2qGL.push_vector(tRGzb0J0g8.get_vector(5));
							KfaJE8AgF8bcqnp2qGL.push_vector(tRGzb0J0g8.get_vector(6));
						}
					} else if (obj.isMyControlObject()) {
						obj.addSetStatePacket(14, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
						obj.flushSetStatePacket();
						return;
					}
					break;
				case 13:
					local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/g-38arg/g-38argattack.ani");
					obj.setCurrentAnimation(ani);
					ani.setSpeedRate(150.0);
					break;
				case 14:
					obj.sq_RemoveMoveParticle();
					sq_moveWithParent(obj, obj);
					local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/g-38arg/explosion_08.ani");
					obj.setCurrentAnimation(ani);
					sq_SetCurrentAttackInfoFromCustomIndex(obj, 22);
					if (obj.isMyControlObject()) {
						sq_flashScreen(obj, 0, 80, 0, 178, sq_RGB(255, 255, 255), GRAPHICEFFECT_DARK, ENUM_DRAWLAYER_BOTTOM);
						sq_flashScreen(obj, 0, 0, 300, 102, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
					}
					break;
			}
			break;
		case 245:
			local subType = obj.getVar("subType").get_vector(0);
			switch (subType) {
				case 1:
					local ani = null;
					switch (state) {
						case 10:
							ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/supernova/bomb_bomb.ani");

							obj.sq_SetMoveParticle("particle/supernova.ptl", 0.0, 0.0);
							break;
						case 11:
							obj.sq_RemoveMoveParticle();
							ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/supernova/start/explosionstart_hemisphere01.ani");
							sq_SetCurrentAttackInfoFromCustomIndex(obj, 23);
							sq_SetMyShake(obj, 2, 300);
							break;
						case 12:
							ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/supernova/loop/explosionloop_hemisphere01.ani");
							local sQn7xH2iUSJXH_ltPHa = obj.getVar().get_vector(1);
							local XKgObrsApDuHV = obj.getVar().get_vector(2);
							sq_SetCurrentAttackInfoFromCustomIndex(obj, 24);
							obj.setTimeEvent(0, sQn7xH2iUSJXH_ltPHa, 1, false);
							obj.setTimeEvent(1, obj.getVar().get_vector(2), 0, false);
							obj.setTimeEvent(2, sQn7xH2iUSJXH_ltPHa / 3 * 2, 1, false);
							obj.getVar().setInt(0, sQn7xH2iUSJXH_ltPHa / 3);
							break;
						case 13:
							obj.removeAllTimeEvent();
							ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/supernova/end/explosionend_hemisphere01.ani");
							sq_SetMyShake(obj, 7, 200);
							sq_SetMyShake(obj, 8, 300);
							if (obj.isMyControlObject()) {

								sq_BinaryStartWrite();
								sq_BinaryWriteDword(245);
								sq_BinaryWriteDword(2);
								sq_BinaryWriteDword(obj.getVar().get_vector(0));
								sq_SendCreatePassiveObjectPacket(obj, 24371, 0, 0, 0, 0, obj.getDirection());
							}
							break;
					}
					if (state != 10) {
						local AmGI1Q1kUH6f27cw = (obj.getVar().get_vector(0)).tofloat() / 350.0;
						ani.setImageRateFromOriginal(AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw);
						ani.setAutoLayerWorkAnimationAddSizeRate(AmGI1Q1kUH6f27cw);
						sq_SetAttackBoundingBoxSizeRate(ani, AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw);
					}
					obj.setCurrentAnimation(ani);
					break;
				case 2:
					switch (state) {
						case 10:
							local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/supernova/floorend/floorend_floornormal.ani");
							local AmGI1Q1kUH6f27cw = (obj.getVar().get_vector(0)).tofloat() / 350.0;
							ani.setImageRateFromOriginal(AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw);
							ani.setAutoLayerWorkAnimationAddSizeRate(AmGI1Q1kUH6f27cw);
							obj.setCurrentAnimation(ani);
							break;
					}
					break;
			}
			break;
		case 246:
			local subType = obj.getVar("subType").get_vector(0);
			switch (subType) {
				case 1:
					switch (state) {
						case 10:
							sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
							if (obj.isMyControlObject()) {
								local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/targetloop_00.ani");
								obj.setCurrentAnimation(ani);
							}
							break;
						case 11:
							sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_NORMAL);
							sq_setCurrentAxisPos(obj, 0, sq_GetVectorData(datas, 0));
							sq_setCurrentAxisPos(obj, 1, sq_GetVectorData(datas, 1));
							local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/dimensionrunnerready_body.ani");
							obj.setCurrentAnimation(ani);

							sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/targetend_00.ani", ENUM_DRAWLAYER_BOTTOM, true);
							break;
						case 12:
							local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/dimensionrunnerfire_body.ani");
							obj.setCurrentAnimation(ani);
							local XcyNl7nSpQrUN2ulrKG = sq_GetVectorData(datas, 0);
							switch (XcyNl7nSpQrUN2ulrKG) {
								case 1:

									local n19cWR0u_pUrzTuMFzndkJAz = sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/targetarea.ani", ENUM_DRAWLAYER_BOTTOM, true);
									sq_setCurrentAxisPos(n19cWR0u_pUrzTuMFzndkJAz, 0, sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 120));
									if (obj.isMyControlObject()) {

										sq_BinaryStartWrite();
										sq_BinaryWriteDword(246);
										sq_BinaryWriteDword(3);
										sq_BinaryWriteDword(obj.getVar().get_vector(0));
										sq_SendCreatePassiveObjectPacket(obj, 24371, 0, 120, 0, 0, obj.getDirection());
									}
									break;
								case 2:
									local cxwjTVbbVwKdSfJ7i = sq_GetVectorData(datas, 1);
									local qX0epDoUSplnToUMe8HKs = [19, 58, -27, -56];
									local iInzjR26Pt93Amv = [148, 125, 149, 127];

									local ph8Nqt4fnmUDq = [
										"passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/missilefireglow_a.ani"
										"passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/missilefireglow_b.ani"
										"passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/missilefireglow_c.ani"
										"passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/missilefireglow_d.ani"
									];

									local hkjRDaYKdUTYQthQn7lM = [
										"passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/dimensionrunnerfirea_00.ani"
										"passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/dimensionrunnerfireb_00.ani"
										"passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/dimensionrunnerfirec_00.ani"
										"passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/dimensionrunnerfired_00.ani"
									];
									for (local qIDlmOSolDW4_633998x5cr4 = 0; qIDlmOSolDW4_633998x5cr4 < 4; qIDlmOSolDW4_633998x5cr4++) {
										if (qIDlmOSolDW4_633998x5cr4 == cxwjTVbbVwKdSfJ7i) continue;
										local OJNM0mawAZP2kLIzC = qX0epDoUSplnToUMe8HKs[qIDlmOSolDW4_633998x5cr4];
										local DgPnpIBlpylEfy3Ut = iInzjR26Pt93Amv[qIDlmOSolDW4_633998x5cr4];

										sq_AddDrawOnlyAniFromParent(obj, ph8Nqt4fnmUDq[qIDlmOSolDW4_633998x5cr4], 0, 0, 0);

										sq_AddDrawOnlyAniFromParent(obj, hkjRDaYKdUTYQthQn7lM[qIDlmOSolDW4_633998x5cr4], 0, -1, 0);
										if (obj.isMyControlObject()) {
											sq_BinaryStartWrite();
											sq_BinaryWriteDword(246);
											sq_BinaryWriteDword(2);
											sq_SendCreatePassiveObjectPacket(obj, 24371, 0, OJNM0mawAZP2kLIzC, 0, DgPnpIBlpylEfy3Ut, obj.getDirection());
										}
									}
									obj.getVar().set_vector(1, obj.getVar().get_vector(1) - 1);
									break;
							}
							break;
						case 13:
							local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/dimensionrunnersuicideready_body.ani");
							obj.setCurrentAnimation(ani);
							break;
						case 14:
							obj.getVar("move").clear_vector();
							local wny4A8vzMSRCuM = obj.getVar("move");
							wny4A8vzMSRCuM.push_vector(sq_GetVectorData(datas, 0));
							wny4A8vzMSRCuM.push_vector(sq_GetVectorData(datas, 1));
							local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/dimensionrunnersuicide_body.ani");
							obj.setCurrentAnimation(ani);

							sq_AddDrawOnlyAniFromParent(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/suicidedust_00.ani", 0, -1, 0);
							break;
						case 15:
							local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/suisideexplosiona_body.ani");
							obj.setCurrentAnimation(ani);
							break;
						case 16:
							local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/suisideexplosionb_04.ani");
							local AmGI1Q1kUH6f27cw = (obj.getVar().get_vector(3)).tofloat() / 100.0;
							ani.setImageRateFromOriginal(AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw);
							ani.setAutoLayerWorkAnimationAddSizeRate(AmGI1Q1kUH6f27cw);
							sq_SetAttackBoundingBoxSizeRate(ani, AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw);
							obj.setCurrentAnimation(ani);
							sq_SetCurrentAttackInfoFromCustomIndex(obj, 26);

							local n19cWR0u_pUrzTuMFzndkJAz = sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/suisideexplosionground_00.ani", ENUM_DRAWLAYER_BOTTOM, true);
							local F2GBcsceXLDnsCXDwF = n19cWR0u_pUrzTuMFzndkJAz.getCurrentAnimation();
							if (F2GBcsceXLDnsCXDwF) F2GBcsceXLDnsCXDwF.setImageRateFromOriginal(AmGI1Q1kUH6f27cw, AmGI1Q1kUH6f27cw);

							sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/last/dimensionrunnerfinishhandeff_ground_normal.ani", ENUM_DRAWLAYER_BOTTOM, true);

							sq_AddDrawOnlyAniFromParent(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/last/dimensionrunnerfinishhand.ani", 0, -1, 0);
							sq_SetMyShake(obj, 5, 320);
							break;
					}
					break;
				case 2:
					switch (state) {
						case 10:
							local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/missile_01.ani");
							obj.setCurrentAnimation(ani);
							obj.getVar().clear_vector();
							local tRGzb0J0g8 = obj.getVar();
							tRGzb0J0g8.push_vector(1);
							tRGzb0J0g8.push_vector(obj.getXPos());
							tRGzb0J0g8.push_vector(obj.getZPos());
							tRGzb0J0g8.push_vector(sq_GetVectorData(datas, 0));
							tRGzb0J0g8.push_vector(sq_GetVectorData(datas, 1));
							tRGzb0J0g8.push_vector(sq_GetVectorData(datas, 2));
							obj.setTimeEvent(1, 70, 0, false);
							break;
						case 11:
							obj.removeAllTimeEvent();
							sq_SetCustomRotate(obj, 0.0);
							local ani = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/missileexplosion_04.ani");
							obj.setCurrentAnimation(ani);

							sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dimensionrunner/new/missileexplosionground_00.ani", ENUM_DRAWLAYER_BOTTOM, true);
							sq_SetMyShake(obj, 3, 80);
							local gBcTSrZzrhPlGPMxEPVc = sq_GetCNRDObjectToCollisionObject(obj.getParent());
							gBcTSrZzrhPlGPMxEPVc.getVar("atkcount").set_vector(0, gBcTSrZzrhPlGPMxEPVc.getVar("atkcount").get_vector(0) + 1);
							break;
					}
					break;
			}
			break;
		case 247:
			local subType = obj.getVar("subType").get_vector(0);
			if (subType == 1) {
				switch (state) {
					case 10:
						local u5BOkzD3tFl = obj.getXPos();
						local U1qkv3YhsplKyz1 = obj.getYPos();
						local ZHZfADccJY_6taCQhhgmYE9 = obj.getDirection();
						local GxDGT5lNkLwhX5WKvUEL4mq1 = sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/hellmarch/gate/back/gatestart_dot4.ani", ENUM_DRAWLAYER_NORMAL, false);
						local ZkK5lyyUZWy_IKAr = sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/hellmarch/gate/front/gatestart_dot2.ani", ENUM_DRAWLAYER_NORMAL, false);
						GxDGT5lNkLwhX5WKvUEL4mq1.setCurrentPos(sq_GetDistancePos(u5BOkzD3tFl, ZHZfADccJY_6taCQhhgmYE9, -65), U1qkv3YhsplKyz1 - 110, 0);
						ZkK5lyyUZWy_IKAr.setCurrentPos(sq_GetDistancePos(u5BOkzD3tFl, ZHZfADccJY_6taCQhhgmYE9, -75), U1qkv3YhsplKyz1 + 70, 0);
						local Pf8cUaGn2N = sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/hellmarch/gate/back/gatestart_dot4.ani", ENUM_DRAWLAYER_NORMAL, false);
						local hVraSgFYEL = sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/hellmarch/gate/front/gatestart_dot2.ani", ENUM_DRAWLAYER_NORMAL, false);
						Pf8cUaGn2N.setCurrentPos(sq_GetDistancePos(u5BOkzD3tFl, ZHZfADccJY_6taCQhhgmYE9, 845 + 65), U1qkv3YhsplKyz1 - 110, 0);
						hVraSgFYEL.setCurrentPos(sq_GetDistancePos(u5BOkzD3tFl, ZHZfADccJY_6taCQhhgmYE9, 845 + 75), U1qkv3YhsplKyz1 + 70, 0);
						sq_SetCurrentDirection(Pf8cUaGn2N, sq_GetOppositeDirection(ZHZfADccJY_6taCQhhgmYE9));
						sq_SetCurrentDirection(hVraSgFYEL, sq_GetOppositeDirection(ZHZfADccJY_6taCQhhgmYE9));

						obj.getVar("aniobj").clear_obj_vector();
						local UBP1xdKHHZT2XGXCw72bhiyf = obj.getVar("aniobj");
						UBP1xdKHHZT2XGXCw72bhiyf.push_obj_vector(GxDGT5lNkLwhX5WKvUEL4mq1);
						UBP1xdKHHZT2XGXCw72bhiyf.push_obj_vector(ZkK5lyyUZWy_IKAr);
						UBP1xdKHHZT2XGXCw72bhiyf.push_obj_vector(Pf8cUaGn2N);
						UBP1xdKHHZT2XGXCw72bhiyf.push_obj_vector(hVraSgFYEL);

						sq_setCurrentAxisPos(sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/hellmarch/gate/laser_electric02.ani", ENUM_DRAWLAYER_COVER, true), 1, U1qkv3YhsplKyz1 + 85);
						if (obj.isMyControlObject()) {

							sq_BinaryStartWrite();
							sq_BinaryWriteDword(247);
							sq_BinaryWriteDword(3);
							sq_BinaryWriteDword(obj.getVar().get_vector(1));
							sq_BinaryWriteDword(obj.getVar().get_vector(2));
							sq_SendCreatePassiveObjectPacket(obj, 24371, 0, 0, 0, 0, obj.getDirection());
						}
						obj.setTimeEvent(0, 1040, 1, false);
						obj.setTimeEvent(1, 880, 1, false);
						obj.setTimeEvent(2, 1000, 1, false);
						obj.setTimeEvent(3, 1650, 1, false);
						break;
					case 11:
						local path = [
							"character/gunner/effect/animation/hellmarch/gate/back/gateloop_dot4.ani",
							"character/gunner/effect/animation/hellmarch/gate/front/gateloop_dot2.ani"
						];

						local UBP1xdKHHZT2XGXCw72bhiyf = obj.getVar("aniobj");
						for (local qIDlmOSolDW4_633998x5cr4 = 0; qIDlmOSolDW4_633998x5cr4 < 4; qIDlmOSolDW4_633998x5cr4++) {
							local n19cWR0u_pUrzTuMFzndkJAz = UBP1xdKHHZT2XGXCw72bhiyf.get_obj_vector(qIDlmOSolDW4_633998x5cr4);
							if (n19cWR0u_pUrzTuMFzndkJAz)
								n19cWR0u_pUrzTuMFzndkJAz.setCurrentAnimation(sq_CreateAnimation("", path[qIDlmOSolDW4_633998x5cr4 % 2]));
						}

						local YM6xqd4yNcgtmR = sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/hellmarch/gate/gateground_03.ani", ENUM_DRAWLAYER_BOTTOM, true);
						UBP1xdKHHZT2XGXCw72bhiyf.push_obj_vector(YM6xqd4yNcgtmR);
						break;
					case 12:

						local u5BOkzD3tFl = obj.getXPos();
						local ZHZfADccJY_6taCQhhgmYE9 = obj.getDirection();
						local ngo4oPqVFmI0J = sq_GetDistancePos(u5BOkzD3tFl, ZHZfADccJY_6taCQhhgmYE9, -100);
						local y3WK_JMT7IgPXvSvB461yCMC = sq_GetDistancePos(u5BOkzD3tFl, ZHZfADccJY_6taCQhhgmYE9, 845 + 100);
						local GxDGT5lNkLwhX5WKvUEL4mq1 = sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/leaderred/leader_appear_leftfootmove1.ani", ENUM_DRAWLAYER_NORMAL, false);
						local ZkK5lyyUZWy_IKAr = sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/leaderblue/leader_appear_leftfootmove1.ani", ENUM_DRAWLAYER_NORMAL, false);

						(GxDGT5lNkLwhX5WKvUEL4mq1.getCurrentAnimation()).addLayerAnimation(-1, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/leaderred/leader_leftfootmove.ani"), true);
						(ZkK5lyyUZWy_IKAr.getCurrentAnimation()).addLayerAnimation(-1, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/leaderblue/leader_leftfootmove.ani"), true);
						sq_setCurrentAxisPos(GxDGT5lNkLwhX5WKvUEL4mq1, 0, ngo4oPqVFmI0J);
						sq_setCurrentAxisPos(ZkK5lyyUZWy_IKAr, 0, y3WK_JMT7IgPXvSvB461yCMC);
						sq_SetCurrentDirection(ZkK5lyyUZWy_IKAr, sq_GetOppositeDirection(ZHZfADccJY_6taCQhhgmYE9));
						obj.getVar("aniobj1").clear_obj_vector();
						local V__P61FjTdyimJ5Y = obj.getVar("aniobj1");
						V__P61FjTdyimJ5Y.push_obj_vector(GxDGT5lNkLwhX5WKvUEL4mq1);
						V__P61FjTdyimJ5Y.push_obj_vector(ZkK5lyyUZWy_IKAr);

						obj.getVar("aniobj1").clear_vector();
						obj.getVar("aniobj1").push_vector(ngo4oPqVFmI0J);
						obj.getVar("aniobj1").push_vector(y3WK_JMT7IgPXvSvB461yCMC);

						obj.getVar("clarity").clear_vector();
						obj.getVar("clarity").push_vector(0);

						obj.getVar("direction").clear_vector();
						obj.getVar("direction").push_vector(1);
						obj.getVar("direction").push_vector(1);

						obj.getVar("aniobj2").clear_obj_vector();
						obj.setTimeEvent(4, 100, 1, false);
						obj.getVar().set_vector(0, obj.getVar().get_vector(0) - 1);
						break;
					case 13:

						local u5BOkzD3tFl = obj.getXPos();
						local U1qkv3YhsplKyz1 = obj.getYPos();
						local ZHZfADccJY_6taCQhhgmYE9 = obj.getDirection();
						local GF4jXNllpeZ3muI4AuLqdSm = sq_GetOppositeDirection(ZHZfADccJY_6taCQhhgmYE9);
						local _jq0tXjOU4FfRyQsY4l7f = sq_GetDistancePos(u5BOkzD3tFl, ZHZfADccJY_6taCQhhgmYE9, -100 + 30 * 3);
						local RoIljK3rv0tojz = sq_GetDistancePos(u5BOkzD3tFl, ZHZfADccJY_6taCQhhgmYE9, 845 + 100 - 30 * 3);
						local btjDqgxzakcUvcoolfPKL = U1qkv3YhsplKyz1 - 20 * 3;
						local HxQYlmF9aJ6nrJ = obj.getVar("aniobj1");
						local lrZ5Hf0Cqv = HxQYlmF9aJ6nrJ.get_obj_vector(0);
						local sODVIRC7kVevVVIw6UmN = HxQYlmF9aJ6nrJ.get_obj_vector(1);
						local nu6qKD3BDmh8Aa = obj.getVar("direction").get_vector(0);
						local zh8xR5h68OV = "";
						if (nu6qKD3BDmh8Aa == 1) {
							zh8xR5h68OV = "right";
							obj.getVar("direction").set_vector(0, 2);
						} else if (nu6qKD3BDmh8Aa == 2) {
							zh8xR5h68OV = "left";
							obj.getVar("direction").set_vector(0, 1);
						}
						local ieCyEmkDlYSJ = obj.getVar("direction").get_vector(1);
						if (ieCyEmkDlYSJ >= 5) ieCyEmkDlYSJ = 1;
						local XqYfGfeWEGIb4se29NzXEX = "";
						if (ieCyEmkDlYSJ == 1 || ieCyEmkDlYSJ == 4)
							XqYfGfeWEGIb4se29NzXEX = "1";
						else if (ieCyEmkDlYSJ == 2 || ieCyEmkDlYSJ == 3)
							XqYfGfeWEGIb4se29NzXEX = "2";
						obj.getVar("direction").set_vector(1, ieCyEmkDlYSJ + 1);
						if (lrZ5Hf0Cqv) {
							lrZ5Hf0Cqv.setCurrentAnimation(sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/LeaderRed/leader_appear_" + zh8xR5h68OV + "footmove" + XqYfGfeWEGIb4se29NzXEX + ".ani"));
							lrZ5Hf0Cqv.getCurrentAnimation().addLayerAnimation(-1, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/leaderred/leader_" + zh8xR5h68OV + "footmove.ani"), true);
						}
						if (sODVIRC7kVevVVIw6UmN) {
							sODVIRC7kVevVVIw6UmN.setCurrentAnimation(sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/leaderblue/leader_appear_" + zh8xR5h68OV + "footmove" + XqYfGfeWEGIb4se29NzXEX + ".ani"));
							sODVIRC7kVevVVIw6UmN.getCurrentAnimation().addLayerAnimation(-1, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/leaderblue/leader_" + zh8xR5h68OV + "footmove.ani"), true);
						}

						obj.getVar("aniobj1").clear_vector();
						obj.getVar("aniobj1").push_vector(lrZ5Hf0Cqv.getXPos());
						obj.getVar("aniobj1").push_vector(sODVIRC7kVevVVIw6UmN.getXPos());
						local ZpFQomROYiRDCSAsaAmbf = obj.getVar("aniobj2");
						local SbttPoIoNyNjF = ZpFQomROYiRDCSAsaAmbf.get_obj_vector_size();
						for (local qIDlmOSolDW4_633998x5cr4 = 0; qIDlmOSolDW4_633998x5cr4 < SbttPoIoNyNjF; qIDlmOSolDW4_633998x5cr4++) {
							local hjR892gfTWud4H = ZpFQomROYiRDCSAsaAmbf.get_obj_vector(qIDlmOSolDW4_633998x5cr4);
							if (hjR892gfTWud4H) {
								hjR892gfTWud4H.setCurrentAnimation(sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/soldier/soldier_appear_" + zh8xR5h68OV + "footmove" + XqYfGfeWEGIb4se29NzXEX + ".ani"));

								(hjR892gfTWud4H.getCurrentAnimation()).addLayerAnimation(-1, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/soldier/soldier_" + zh8xR5h68OV + "footmove.ani"), true);
							}
						}

						if (SbttPoIoNyNjF < 6 * 2 * 3)
							for (local qIDlmOSolDW4_633998x5cr4 = 0; qIDlmOSolDW4_633998x5cr4 < 7; qIDlmOSolDW4_633998x5cr4++) {
								if (qIDlmOSolDW4_633998x5cr4 == 3) continue;
								local GxDGT5lNkLwhX5WKvUEL4mq1 = sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/soldier/soldier_appear_" + zh8xR5h68OV + "footmove" + XqYfGfeWEGIb4se29NzXEX + ".ani", ENUM_DRAWLAYER_NORMAL, false);
								local ZkK5lyyUZWy_IKAr = sq_CreateDrawOnlyObject(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/soldier/soldier_appear_" + zh8xR5h68OV + "footmove" + XqYfGfeWEGIb4se29NzXEX + ".ani", ENUM_DRAWLAYER_NORMAL, false);

								GxDGT5lNkLwhX5WKvUEL4mq1.getCurrentAnimation().addLayerAnimation(-1, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/soldier/soldier_" + zh8xR5h68OV + "footmove.ani"), false);
								ZkK5lyyUZWy_IKAr.getCurrentAnimation().addLayerAnimation(-1, sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/soldier/soldier_" + zh8xR5h68OV + "footmove.ani"), false);
								local GiWpcK5x9qO6hkC = btjDqgxzakcUvcoolfPKL + 20 * qIDlmOSolDW4_633998x5cr4;
								GxDGT5lNkLwhX5WKvUEL4mq1.setCurrentPos(sq_GetDistancePos(_jq0tXjOU4FfRyQsY4l7f, ZHZfADccJY_6taCQhhgmYE9, -30 * qIDlmOSolDW4_633998x5cr4), GiWpcK5x9qO6hkC, 0);
								ZkK5lyyUZWy_IKAr.setCurrentPos(sq_GetDistancePos(RoIljK3rv0tojz, ZHZfADccJY_6taCQhhgmYE9, 30 * qIDlmOSolDW4_633998x5cr4), GiWpcK5x9qO6hkC, 0);
								sq_SetCurrentDirection(ZkK5lyyUZWy_IKAr, GF4jXNllpeZ3muI4AuLqdSm);
								sq_moveWithParent(lrZ5Hf0Cqv, GxDGT5lNkLwhX5WKvUEL4mq1);
								sq_moveWithParent(sODVIRC7kVevVVIw6UmN, ZkK5lyyUZWy_IKAr);
								ZpFQomROYiRDCSAsaAmbf.push_obj_vector(GxDGT5lNkLwhX5WKvUEL4mq1);
								ZpFQomROYiRDCSAsaAmbf.push_obj_vector(ZkK5lyyUZWy_IKAr);
							}

						local QwtzGeW50sLex = obj.getVar("clarity");
						local wZe57FmvOANUaQSAF = QwtzGeW50sLex.size_vector();
						for (local qIDlmOSolDW4_633998x5cr4 = 0; qIDlmOSolDW4_633998x5cr4 < wZe57FmvOANUaQSAF; qIDlmOSolDW4_633998x5cr4++) {
							local _T8HCaa8T_xcc8L1subT213 = QwtzGeW50sLex.get_vector(qIDlmOSolDW4_633998x5cr4);
							QwtzGeW50sLex.set_vector(qIDlmOSolDW4_633998x5cr4, _T8HCaa8T_xcc8L1subT213 + obj.getVar().get_vector(6));
						}
						if (wZe57FmvOANUaQSAF < 4)
							QwtzGeW50sLex.push_vector(0);
						obj.setTimeEvent(4, 100, 1, false);
						obj.getVar().set_vector(0, obj.getVar().get_vector(0) - 1);
						break;
					case 14: {
						local path = [
							"character/gunner/effect/animation/hellmarch/gate/back/gateend_dot4.ani",
							"character/gunner/effect/animation/hellmarch/gate/front/gateend_dot2.ani"
						];
						local BHxC0Jzg3GjIUw1E = obj.getVar("aniobj");
						for (local qIDlmOSolDW4_633998x5cr4 = 0; qIDlmOSolDW4_633998x5cr4 < 4; qIDlmOSolDW4_633998x5cr4++) {
							local n19cWR0u_pUrzTuMFzndkJAz = BHxC0Jzg3GjIUw1E.get_obj_vector(qIDlmOSolDW4_633998x5cr4);
							if (n19cWR0u_pUrzTuMFzndkJAz)
								n19cWR0u_pUrzTuMFzndkJAz.setCurrentAnimation(sq_CreateAnimation("", path[qIDlmOSolDW4_633998x5cr4 % 2]));
						}
					}
					local HxQYlmF9aJ6nrJ = obj.getVar("aniobj1");
					local lrZ5Hf0Cqv = HxQYlmF9aJ6nrJ.get_obj_vector(0);
					local sODVIRC7kVevVVIw6UmN = HxQYlmF9aJ6nrJ.get_obj_vector(1);
					if (lrZ5Hf0Cqv)
						lrZ5Hf0Cqv.setCurrentAnimation(sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/leaderred/leader_sir.ani"));
					if (sODVIRC7kVevVVIw6UmN)
						sODVIRC7kVevVVIw6UmN.setCurrentAnimation(sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/leaderblue/leader_sir.ani"));
					local ZpFQomROYiRDCSAsaAmbf = obj.getVar("aniobj2");
					local SbttPoIoNyNjF = ZpFQomROYiRDCSAsaAmbf.get_obj_vector_size();
					for (local qIDlmOSolDW4_633998x5cr4 = 0; qIDlmOSolDW4_633998x5cr4 < SbttPoIoNyNjF; qIDlmOSolDW4_633998x5cr4++) {
						local hjR892gfTWud4H = ZpFQomROYiRDCSAsaAmbf.get_obj_vector(qIDlmOSolDW4_633998x5cr4);
						if (hjR892gfTWud4H)
							hjR892gfTWud4H.setCurrentAnimation(sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/soldier/soldier_sir.ani"));
					}

					local QwtzGeW50sLex = obj.getVar("clarity");
					local wZe57FmvOANUaQSAF = QwtzGeW50sLex.size_vector();
					for (local qIDlmOSolDW4_633998x5cr4 = 0; qIDlmOSolDW4_633998x5cr4 < wZe57FmvOANUaQSAF; qIDlmOSolDW4_633998x5cr4++) {
						local _T8HCaa8T_xcc8L1subT213 = QwtzGeW50sLex.get_vector(qIDlmOSolDW4_633998x5cr4);
						QwtzGeW50sLex.set_vector(qIDlmOSolDW4_633998x5cr4, _T8HCaa8T_xcc8L1subT213 + obj.getVar().get_vector(6));
					}
					break;
					case 15:
						local HxQYlmF9aJ6nrJ = obj.getVar("aniobj1");
						local lrZ5Hf0Cqv = HxQYlmF9aJ6nrJ.get_obj_vector(0);
						local sODVIRC7kVevVVIw6UmN = HxQYlmF9aJ6nrJ.get_obj_vector(1);
						if (lrZ5Hf0Cqv)
							lrZ5Hf0Cqv.setCurrentAnimation(sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/leaderred/leader_readytoexplosion.ani"));
						if (sODVIRC7kVevVVIw6UmN)
							sODVIRC7kVevVVIw6UmN.setCurrentAnimation(sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/leaderblue/leader_readytoexplosion.ani"));
						local ZpFQomROYiRDCSAsaAmbf = obj.getVar("aniobj2");
						local SbttPoIoNyNjF = ZpFQomROYiRDCSAsaAmbf.get_obj_vector_size();
						for (local qIDlmOSolDW4_633998x5cr4 = 0; qIDlmOSolDW4_633998x5cr4 < SbttPoIoNyNjF; qIDlmOSolDW4_633998x5cr4++) {
							local hjR892gfTWud4H = ZpFQomROYiRDCSAsaAmbf.get_obj_vector(qIDlmOSolDW4_633998x5cr4);
							if (hjR892gfTWud4H)
								hjR892gfTWud4H.setCurrentAnimation(sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/soldier/soldier_readytoexplosion.ani"));
						}
						break;
					case 16:
						local ZpFQomROYiRDCSAsaAmbf = obj.getVar("aniobj2");
						local SbttPoIoNyNjF = ZpFQomROYiRDCSAsaAmbf.get_obj_vector_size();
						for (local qIDlmOSolDW4_633998x5cr4 = 0; qIDlmOSolDW4_633998x5cr4 < SbttPoIoNyNjF; qIDlmOSolDW4_633998x5cr4++) {
							local hjR892gfTWud4H = ZpFQomROYiRDCSAsaAmbf.get_obj_vector(qIDlmOSolDW4_633998x5cr4);
							if (hjR892gfTWud4H)
								hjR892gfTWud4H.setCurrentAnimation(sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/bombnew/explosion_04.ani"));
						}

						local HxQYlmF9aJ6nrJ = obj.getVar("aniobj1");
						local lrZ5Hf0Cqv = HxQYlmF9aJ6nrJ.get_obj_vector(0);
						local sODVIRC7kVevVVIw6UmN = HxQYlmF9aJ6nrJ.get_obj_vector(1);
						local JPS8tH2WcCoFlO = sq_GetDirection(lrZ5Hf0Cqv);
						local ScDafhaIWqw_d4ThuzJpy3 = sq_GetDirection(sODVIRC7kVevVVIw6UmN);
						sq_CreateParticle("passiveobject/script_sqr_nut_qq506807329/gunner/particle/hellmarchexplosion.ptl", lrZ5Hf0Cqv, sq_GetDistancePos(0, JPS8tH2WcCoFlO, -100), -60, 120, false, 100, 0, 2);
						sq_CreateParticle("passiveobject/script_sqr_nut_qq506807329/gunner/particle/hellmarchexplosion.ptl", sODVIRC7kVevVVIw6UmN, sq_GetDistancePos(0, ScDafhaIWqw_d4ThuzJpy3, -100), -60, 120, false, 100, 0, 2);
						sq_CreateParticle("passiveobject/script_sqr_nut_qq506807329/gunner/particle/hellmarchexplosion.ptl", lrZ5Hf0Cqv, sq_GetDistancePos(0, JPS8tH2WcCoFlO, -180), 0, 120, false, 100, 0, 2);
						sq_CreateParticle("passiveobject/script_sqr_nut_qq506807329/gunner/particle/hellmarchexplosion.ptl", sODVIRC7kVevVVIw6UmN, sq_GetDistancePos(0, ScDafhaIWqw_d4ThuzJpy3, -180), 0, 120, false, 100, 0, 2);
						sq_CreateParticle("passiveobject/script_sqr_nut_qq506807329/gunner/particle/hellmarchexplosion.ptl", lrZ5Hf0Cqv, sq_GetDistancePos(0, JPS8tH2WcCoFlO, -280), 60, 120, false, 100, 0, 2);
						sq_CreateParticle("passiveobject/script_sqr_nut_qq506807329/gunner/particle/hellmarchexplosion.ptl", sODVIRC7kVevVVIw6UmN, sq_GetDistancePos(0, ScDafhaIWqw_d4ThuzJpy3, -280), 60, 120, false, 100, 0, 2);
						if (obj.isMyControlObject()) {

							sq_BinaryStartWrite();
							sq_BinaryWriteDword(247);
							sq_BinaryWriteDword(2);
							sq_BinaryWriteDword(obj.getVar().get_vector(3));
							sq_BinaryWriteDword(obj.getVar().get_vector(4));
							sq_SendCreatePassiveObjectPacket(obj, 24371, 0, 0, 0, 0, obj.getDirection());
						}
						sq_SetMyShake(obj, 5, 300);
						break;
					case 17:
						local HxQYlmF9aJ6nrJ = obj.getVar("aniobj1");
						local lrZ5Hf0Cqv = HxQYlmF9aJ6nrJ.get_obj_vector(0);
						local sODVIRC7kVevVVIw6UmN = HxQYlmF9aJ6nrJ.get_obj_vector(1);
						if (lrZ5Hf0Cqv)
							lrZ5Hf0Cqv.setCurrentAnimation(sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/bombnew/explosion_04.ani"));
						if (sODVIRC7kVevVVIw6UmN)
							sODVIRC7kVevVVIw6UmN.setCurrentAnimation(sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/gunner/animation/hellmarch/bombnew/explosion_04.ani"));
						sq_SetMyShake(obj, 5, 300);
						break;
				}
			}
			break;
	}
};