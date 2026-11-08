


function procAppend_po_qq506807329new_gunner_24371(obj) {
	if (!obj) return;
	local index = obj.getVar("skill").get_vector(0);
	switch (index) {
		case 251:
			local subType = obj.getVar("subType").get_vector(0);
			switch (subType) {
				case 1:
				case 2:
				case 3:
				case 4:
					switch (obj.getState()) {
						case PASSIVEOBJ_SUB_STATE_0:
							local currentAnimation = obj.getCurrentAnimation();
							local yzOaHeNhTfK3 = sq_GetCurrentTime(currentAnimation);
							local MwUk3yhOmQOfrQ = obj.getVar().get_vector(2);
							sq_SetCurrentPos(obj,
								sq_GetUniformVelocity(obj.getVar("move").get_vector(0), obj.getVar().get_vector(0), yzOaHeNhTfK3, MwUk3yhOmQOfrQ),
								sq_GetUniformVelocity(obj.getVar("move").get_vector(1), obj.getVar().get_vector(1), yzOaHeNhTfK3, MwUk3yhOmQOfrQ),
								sq_GetUniformVelocity(obj.getVar("move").get_vector(2), 0, yzOaHeNhTfK3, MwUk3yhOmQOfrQ));

							local aBpjnVE457Xw9WhamcPXVFNq = obj.getVar("move").get_timer_vector(0);
							if (aBpjnVE457Xw9WhamcPXVFNq.isOnEvent(yzOaHeNhTfK3) == true) {
								createPooledObjEff_qq506807329(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose_old/missilesmoke" + sq_getRandom(1, 3) + ".ani", obj.getXPos(), obj.getYPos() - 1, obj.getZPos(), ENUM_DRAWLAYER_NORMAL, obj.getDirection());
							}

							aBpjnVE457Xw9WhamcPXVFNq = obj.getVar("move").get_timer_vector(1);
							if (aBpjnVE457Xw9WhamcPXVFNq.isOnEvent(yzOaHeNhTfK3) == true) {
								local GlnX0BEE0eO4kvgd6Q = createPooledObjEff_qq506807329(obj, "passiveobject/script_sqr_nut_qq506807329/gunner/animation/dangerclose_old/dangersmoke.ani", obj.getXPos(), obj.getYPos(), obj.getZPos(), ENUM_DRAWLAYER_NORMAL, obj.getDirection());
								GlnX0BEE0eO4kvgd6Q.setCustomRotate(true, obj.getVar("move").getFloat(0));
							}
							if (yzOaHeNhTfK3 > MwUk3yhOmQOfrQ && obj.isMyControlObject()) {
								obj.addSetStatePacket(PASSIVEOBJ_SUB_STATE_1, null, STATE_PRIORITY_AUTO, false, "");
							}
							break;
						case PASSIVEOBJ_SUB_STATE_1:
							local currentAnimation = obj.getCurrentAnimation();
							if (sq_IsEnd(currentAnimation) && obj.isMyControlObject()) {
								sq_SendDestroyPacketPassiveObject(obj);
							}
							break;
					}
					break;
				case 5:
					switch (obj.getState()) {
						case PASSIVEOBJ_SUB_STATE_0:
							local aBpjnVE457Xw9WhamcPXVFNq = obj.getVar("attack").get_timer_vector(0);
							if (aBpjnVE457Xw9WhamcPXVFNq.isOnEvent(sq_GetObjectTime(obj)) == true) {
								obj.resetHitObjectList();
								return;
							}
							if (aBpjnVE457Xw9WhamcPXVFNq.isEnd() && obj.isMyControlObject()) {
								obj.addSetStatePacket(PASSIVEOBJ_SUB_STATE_1, null, STATE_PRIORITY_AUTO, false, "");
							}
							break;
						case PASSIVEOBJ_SUB_STATE_1:
							local currentAnimation = obj.getCurrentAnimation();
							if (sq_IsEnd(currentAnimation) && obj.isMyControlObject()) {
								sq_SendDestroyPacketPassiveObject(obj);
							}
							break;
					}
					break;
			}
			break;
		case 169:
			procpo_shut(obj);
			break;
		case 232:
			local state = obj.getVar("state").get_vector(0);
			if (state != 12) {
				local myq1z3gSMT2u7aY = obj.getVar("move");
				if (myq1z3gSMT2u7aY.size_vector() <= 0) return;
				local iunIR4RUlbwhjG = obj.getVar();
				local m83oZsgB1qcVB1HFRUxCyQdS = false;

				if (state == 11 && iunIR4RUlbwhjG.get_obj_vector_size() <= 0)
					m83oZsgB1qcVB1HFRUxCyQdS = true;
				local UcmBZMsqUn832FNS = obj.getYPos();
				local Wv79ITTSnABCPX = obj.getDirection();
				local jZuKH09wqDizIPWXv9V2J = sq_GetObjectTime(obj) - myq1z3gSMT2u7aY.get_vector(1);
				local fVKVwayguBRfS9v7Baf = 150;
				local NfjwN1NKjSGLVY = sq_GetDistancePos(myq1z3gSMT2u7aY.get_vector(0),
					Wv79ITTSnABCPX,
					sq_GetUniformVelocity(0, iunIR4RUlbwhjG.get_vector(1), jZuKH09wqDizIPWXv9V2J, fVKVwayguBRfS9v7Baf)
				);
				local l_ZHJBDvaJaMkfgeWUc = sq_GetDistancePos(NfjwN1NKjSGLVY, Wv79ITTSnABCPX, 55);
				for (local XcUMqdgNc8Dk5vw83vnf = 0; XcUMqdgNc8Dk5vw83vnf < iunIR4RUlbwhjG.get_obj_vector_size(); XcUMqdgNc8Dk5vw83vnf++) {
					local Z5sT3vz2meeh = sq_GetCNRDObjectToActiveObject(iunIR4RUlbwhjG.get_obj_vector(XcUMqdgNc8Dk5vw83vnf));

					if (Z5sT3vz2meeh && !Z5sT3vz2meeh.isDead()) {

						if (Z5sT3vz2meeh.isMovablePos(l_ZHJBDvaJaMkfgeWUc, UcmBZMsqUn832FNS)) {
							sq_setCurrentAxisPos(Z5sT3vz2meeh, 0, l_ZHJBDvaJaMkfgeWUc);
							sq_setCurrentAxisPos(Z5sT3vz2meeh, 1, UcmBZMsqUn832FNS);
						} else if (m83oZsgB1qcVB1HFRUxCyQdS == false) {
							m83oZsgB1qcVB1HFRUxCyQdS = true;
							break;
						}
					}
				}
				if (m83oZsgB1qcVB1HFRUxCyQdS == false && jZuKH09wqDizIPWXv9V2J <= fVKVwayguBRfS9v7Baf)
					sq_setCurrentAxisPos(obj, 0, NfjwN1NKjSGLVY);
				else if (obj.isMyControlObject())
					obj.addSetStatePacket(12, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
			}
			break;
		case 233:
			local FJaCTznG1e4ZZVeu8588c1ja = obj.getVar("subType").get_vector(0);
			switch (FJaCTznG1e4ZZVeu8588c1ja) {
				case 1:
					local state = obj.getVar("state").get_vector(0);
					switch (state) {
						case 10:
							local zKXuDqWiDj64izPj_QbTRL = obj.isMyControlObject();
							if (zKXuDqWiDj64izPj_QbTRL) {
								local m83oZsgB1qcVB1HFRUxCyQdS = false;
								local pv4QByYqvJcA = sq_GetCNRDObjectToSQRCharacter(obj.getVar().get_obj_vector(0));
								if (pv4QByYqvJcA &&
									pv4QByYqvJcA.getState() == 233 &&
									pv4QByYqvJcA.getSkillSubState() == 0) {
									local iunIR4RUlbwhjG = obj.getVar();
									local knXC0QgMOmj0575BRjXR5ThL = sq_GetObjectTime(obj);
									local OnFyL6NxDpc1Cm = iunIR4RUlbwhjG.get_vector(0);
									local etGerSKifzU0MgZI80Ed1 = iunIR4RUlbwhjG.get_vector(1);
									local DKzzvpGQVPK8QLJeUnF = 0;
									local vDw5M6ZRd0orAj = 0;
									if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL))
										vDw5M6ZRd0orAj -= etGerSKifzU0MgZI80Ed1;
									else if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL))
										vDw5M6ZRd0orAj += etGerSKifzU0MgZI80Ed1;
									if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL))
										DKzzvpGQVPK8QLJeUnF -= etGerSKifzU0MgZI80Ed1;
									else if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL))
										DKzzvpGQVPK8QLJeUnF += etGerSKifzU0MgZI80Ed1;
									if (DKzzvpGQVPK8QLJeUnF != 0)
										sq_setCurrentAxisPos(obj, 0, obj.getXPos() + DKzzvpGQVPK8QLJeUnF);
									if (vDw5M6ZRd0orAj != 0)
										sq_setCurrentAxisPos(obj, 1, obj.getYPos() + vDw5M6ZRd0orAj);
									if (knXC0QgMOmj0575BRjXR5ThL >= OnFyL6NxDpc1Cm)
										m83oZsgB1qcVB1HFRUxCyQdS = true;
								} else
									m83oZsgB1qcVB1HFRUxCyQdS = true;
								if (m83oZsgB1qcVB1HFRUxCyQdS) {
									if (pv4QByYqvJcA) {

										pv4QByYqvJcA.sq_IntVectClear();
										pv4QByYqvJcA.sq_IntVectPush(1);
										pv4QByYqvJcA.sq_AddSetStatePacket(233, STATE_PRIORITY_USER, true);
									}
									local NAAybzFnB9JG1KVa4 = sq_GetGlobalIntVector();
									sq_IntVectorClear(NAAybzFnB9JG1KVa4);
									sq_IntVectorPush(NAAybzFnB9JG1KVa4, obj.getXPos());
									sq_IntVectorPush(NAAybzFnB9JG1KVa4, obj.getYPos());
									obj.addSetStatePacket(11, NAAybzFnB9JG1KVa4, STATE_PRIORITY_AUTO, false, "");
									return;
								}
							}
							break;
						case 12:
							local FeNYfcjjwrCkRh9fXl = obj.getCurrentAnimation();
							local jZuKH09wqDizIPWXv9V2J = sq_GetCurrentTime(FeNYfcjjwrCkRh9fXl);
							local fVKVwayguBRfS9v7Baf = 200;
							local vGttNjVHE5Oz9b4WAh = sq_GetUniformVelocity(900, 0, jZuKH09wqDizIPWXv9V2J, fVKVwayguBRfS9v7Baf);
							sq_setCurrentAxisPos(obj, 2, vGttNjVHE5Oz9b4WAh);
							if (jZuKH09wqDizIPWXv9V2J >= fVKVwayguBRfS9v7Baf)
								if (obj.isMyControlObject())
									obj.addSetStatePacket(13, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
							break;
						case 13:
						case 14:
							local iunIR4RUlbwhjG = obj.getVar();
							local DJdgIa8hx7 = iunIR4RUlbwhjG.get_vector(9);
							local qYzsRKBGmfu0A8HSQYpw = iunIR4RUlbwhjG.get_vector(10);
							setRangeObjectXPos(obj, DJdgIa8hx7, ENUM_DIRECTION_NEUTRAL, 0, 300, 0, qYzsRKBGmfu0A8HSQYpw);
							break;
					}
			}
			break;
		case 234:
			if (!obj.isMyControlObject()) break;
			local LIVfkmW7yTwIqVrt = obj.getTopCharacter();
			if (obj.getState() != 10)
				if (!LIVfkmW7yTwIqVrt || LIVfkmW7yTwIqVrt.getState() != 234 || obj.sq_GetParentSkillSubState() > 1) {
					obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
				}
			break;
		case 239:
			local dVzx_TzJEyLmn = obj.getVar().get_vector(0);
			if (dVzx_TzJEyLmn == ENUM_DIRECTION_DOWN)
				if (obj.getZPos() <= 0) {

					sq_CreateDrawOnlyObject(obj, "character/gunner/effect/animation/hiteffect/collisionfloor.ani", ENUM_DRAWLAYER_NORMAL, true);
					if (obj.isMyControlObject())
						sq_SendDestroyPacketPassiveObject(obj);
				}
			break;
		case 242:
			local state = obj.getVar("state").get_vector(0);
			if (state == 13) {
				local DMK3znHpPnIX0SC = obj.getVar().get_vector(3);
				local fIy2T7FUCgv22u3eaFrua = obj.getVar().get_vector(4);
				setRangeObjectXPos(obj, DMK3znHpPnIX0SC, ENUM_DIRECTION_NEUTRAL, 0, 100, fIy2T7FUCgv22u3eaFrua, 1);
			} else if (state == 10)
				if (obj.getZPos() <= 0) {
					if (obj.isMyControlObject())
						obj.addSetStatePacket(11, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
				}
			break;
		case 243:
			local FJaCTznG1e4ZZVeu8588c1ja = obj.getVar("subType").get_vector(0);
			local state = obj.getVar("state").get_vector(0);
			switch (FJaCTznG1e4ZZVeu8588c1ja) {
				case 1:
					if (state == 10) {
						if (obj.isMyControlObject()) {
							local pv4QByYqvJcA = sq_GetCNRDObjectToSQRCharacter(obj.getTopCharacter());
							if (pv4QByYqvJcA) {
								if (pv4QByYqvJcA.getState() == 243) {
									local DKzzvpGQVPK8QLJeUnF = 0;
									local vDw5M6ZRd0orAj = 0;
									local etGerSKifzU0MgZI80Ed1 = 4;
									if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL))
										vDw5M6ZRd0orAj -= etGerSKifzU0MgZI80Ed1;
									else if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL))
										vDw5M6ZRd0orAj += etGerSKifzU0MgZI80Ed1;
									if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL))
										DKzzvpGQVPK8QLJeUnF -= etGerSKifzU0MgZI80Ed1;
									else if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL))
										DKzzvpGQVPK8QLJeUnF += etGerSKifzU0MgZI80Ed1;
									if (DKzzvpGQVPK8QLJeUnF != 0) sq_setCurrentAxisPos(obj, 0, obj.getXPos() + DKzzvpGQVPK8QLJeUnF);
									if (vDw5M6ZRd0orAj != 0) sq_setCurrentAxisPos(obj, 1, obj.getYPos() + vDw5M6ZRd0orAj);
								} else {
									local nn2Ouae0RhITU4jSgECR4Gbq = obj.getXPos();
									local UcmBZMsqUn832FNS = obj.getYPos();
									local rL_OWywHLMHnhKW = obj.getVar().get_vector(3);
									local P0Zz0eeL191ixWgvciKD55V = obj.getVar().get_vector(4);
									local rki2a2KJSuG1djsZU7IktXa = sq_ToDegree(
										sq_Atan2(
											sq_Abs(P0Zz0eeL191ixWgvciKD55V - (UcmBZMsqUn832FNS + 1000)).tofloat(),
											sq_Abs(nn2Ouae0RhITU4jSgECR4Gbq - rL_OWywHLMHnhKW).tofloat()
										)
									) + 90.0;
									local NAAybzFnB9JG1KVa4 = sq_GetGlobalIntVector();
									sq_IntVectorClear(NAAybzFnB9JG1KVa4);
									sq_IntVectorPush(NAAybzFnB9JG1KVa4, nn2Ouae0RhITU4jSgECR4Gbq);
									sq_IntVectorPush(NAAybzFnB9JG1KVa4, UcmBZMsqUn832FNS);
									sq_IntVectorPush(NAAybzFnB9JG1KVa4,
										(nn2Ouae0RhITU4jSgECR4Gbq > rL_OWywHLMHnhKW) ? ENUM_DIRECTION_LEFT : ENUM_DIRECTION_RIGHT
									);
									sq_IntVectorPush(NAAybzFnB9JG1KVa4, rki2a2KJSuG1djsZU7IktXa.tointeger());
									obj.addSetStatePacket(11, NAAybzFnB9JG1KVa4, STATE_PRIORITY_AUTO, false, "");
								}
							} else
								sq_SendDestroyPacketPassiveObject(obj);
						}
					}
					break;
				case 2:
					switch (state) {
						case 10:
							break;
						default:
							local jZuKH09wqDizIPWXv9V2J = sq_GetObjectTime(obj);
							local fVKVwayguBRfS9v7Baf = 400;
							local iunIR4RUlbwhjG = obj.getVar();

							local NfjwN1NKjSGLVY = sq_GetUniformVelocity(iunIR4RUlbwhjG.get_vector(0), iunIR4RUlbwhjG.get_vector(2), jZuKH09wqDizIPWXv9V2J, fVKVwayguBRfS9v7Baf);
							local _nGqQ0f7Aa1F1PbUFdVJsC0 = sq_GetUniformVelocity(iunIR4RUlbwhjG.get_vector(1), iunIR4RUlbwhjG.get_vector(3), jZuKH09wqDizIPWXv9V2J, fVKVwayguBRfS9v7Baf);
							local vGttNjVHE5Oz9b4WAh = sq_GetUniformVelocity(1000, 0, jZuKH09wqDizIPWXv9V2J, fVKVwayguBRfS9v7Baf);
							sq_SetCurrentPos(obj, NfjwN1NKjSGLVY, _nGqQ0f7Aa1F1PbUFdVJsC0, vGttNjVHE5Oz9b4WAh);
							if (jZuKH09wqDizIPWXv9V2J >= fVKVwayguBRfS9v7Baf)
								if (obj.isMyControlObject())
									obj.addSetStatePacket(10, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
							break;
					}
					break;
			}
			break;
		case 244:
			local FJaCTznG1e4ZZVeu8588c1ja = obj.getVar("subType").get_vector(0);
			if (FJaCTznG1e4ZZVeu8588c1ja != 1) return;
			local state = obj.getVar("state").get_vector(0);
			switch (state) {
				case 10:
					if (obj.isMyControlObject())
						if (obj.getZPos() <= 0)
							obj.addSetStatePacket(11, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
					break;
				case 11:
					if (obj.isExistTimeEvent(1)) return;
					local zGUWq1s3QfIv = sq_GetCNRDObjectToActiveObject(obj.getVar().get_obj_vector(0));

					if (zGUWq1s3QfIv && !zGUWq1s3QfIv.isDead()) {
						if (obj.getVar().getBool(0) == false) {
							local nn2Ouae0RhITU4jSgECR4Gbq = obj.getXPos();
							local UcmBZMsqUn832FNS = obj.getYPos();
							local jBzcqRF4f1H = zGUWq1s3QfIv.getXPos();
							local xTmqkq1ANq3hf0TkThhvUdX = zGUWq1s3QfIv.getYPos();
							local cMw8X0bFBFE6mqfFpe9 = sq_Abs(nn2Ouae0RhITU4jSgECR4Gbq - jBzcqRF4f1H);
							local X489_skMRpy1 = sq_Abs(UcmBZMsqUn832FNS - xTmqkq1ANq3hf0TkThhvUdX);
							if (cMw8X0bFBFE6mqfFpe9 <= 10 && X489_skMRpy1 <= 10) {
								obj.getVar("move").clear_vector();
								obj.getVar("move").push_vector(sq_GetObjectTime(obj));
								obj.sq_PlaySound("G_38ARG_GRAB");
								obj.getVar().setBool(0, true);
								return;
							} else {

								if (cMw8X0bFBFE6mqfFpe9 > 0) {
									local DKzzvpGQVPK8QLJeUnF = cMw8X0bFBFE6mqfFpe9 / 10 + 1;

									if (nn2Ouae0RhITU4jSgECR4Gbq > jBzcqRF4f1H) DKzzvpGQVPK8QLJeUnF /= -1;
									sq_setCurrentAxisPos(obj, 0, nn2Ouae0RhITU4jSgECR4Gbq + DKzzvpGQVPK8QLJeUnF);
								}

								if (X489_skMRpy1 > 0) {
									local vDw5M6ZRd0orAj = X489_skMRpy1 / 10 + 1;

									if (UcmBZMsqUn832FNS > xTmqkq1ANq3hf0TkThhvUdX) vDw5M6ZRd0orAj /= -1;
									sq_setCurrentAxisPos(obj, 1, UcmBZMsqUn832FNS + vDw5M6ZRd0orAj);
								}
							}
						} else {
							local jZuKH09wqDizIPWXv9V2J = sq_GetObjectTime(obj) - obj.getVar("move").get_vector(0);
							local fVKVwayguBRfS9v7Baf = 200;
							local vGttNjVHE5Oz9b4WAh = sq_GetUniformVelocity(0, zGUWq1s3QfIv.getZPos() + sq_GetObjectHeight(zGUWq1s3QfIv) / 2, jZuKH09wqDizIPWXv9V2J, fVKVwayguBRfS9v7Baf);
							obj.setCurrentPos(zGUWq1s3QfIv.getXPos(), zGUWq1s3QfIv.getYPos() + 1, vGttNjVHE5Oz9b4WAh);
							if (jZuKH09wqDizIPWXv9V2J >= fVKVwayguBRfS9v7Baf) {
								if (obj.isMyControlObject()) {
									local NAAybzFnB9JG1KVa4 = sq_GetGlobalIntVector();
									sq_IntVectorClear(NAAybzFnB9JG1KVa4);
									sq_IntVectorPush(NAAybzFnB9JG1KVa4, 1);
									obj.addSetStatePacket(12, NAAybzFnB9JG1KVa4, STATE_PRIORITY_AUTO, false, "");
								}
							}
						}
					} else {
						if (obj.isMyControlObject())
							obj.addSetStatePacket(11, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
					}
					break;
			}
			break;
		case 245:
			local FJaCTznG1e4ZZVeu8588c1ja = obj.getVar("subType").get_vector(0);
			if (FJaCTznG1e4ZZVeu8588c1ja == 1) {
				local state = obj.getVar("state").get_vector(0);
				if (state == 10) {

					if (obj.isMyControlObject())
						if (obj.getZPos() <= 0)
							obj.addSetStatePacket(11, sq_GetGlobalIntVector(), STATE_PRIORITY_AUTO, false, "");
				}
			}
			break;
		case 246:
			local FJaCTznG1e4ZZVeu8588c1ja = obj.getVar("subType").get_vector(0);
			local state = obj.getVar("state").get_vector(0);
			switch (FJaCTznG1e4ZZVeu8588c1ja) {
				case 1:
					switch (state) {
						case 10:
							if (obj.isMyControlObject()) {
								local pv4QByYqvJcA = sq_GetCNRDObjectToSQRCharacter(obj.getTopCharacter());
								if (pv4QByYqvJcA) {
									if (pv4QByYqvJcA.getState() == 246) {
										local DKzzvpGQVPK8QLJeUnF = 0;
										local vDw5M6ZRd0orAj = 0;
										local etGerSKifzU0MgZI80Ed1 = 4;
										if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_UP, ENUM_SUBKEY_TYPE_ALL))
											vDw5M6ZRd0orAj -= etGerSKifzU0MgZI80Ed1;
										else if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_DOWN, ENUM_SUBKEY_TYPE_ALL))
											vDw5M6ZRd0orAj += etGerSKifzU0MgZI80Ed1;
										if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL))
											DKzzvpGQVPK8QLJeUnF -= etGerSKifzU0MgZI80Ed1;
										else if (sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL))
											DKzzvpGQVPK8QLJeUnF += etGerSKifzU0MgZI80Ed1;
										if (DKzzvpGQVPK8QLJeUnF != 0) sq_setCurrentAxisPos(obj, 0, obj.getXPos() + DKzzvpGQVPK8QLJeUnF);
										if (vDw5M6ZRd0orAj != 0) sq_setCurrentAxisPos(obj, 1, obj.getYPos() + vDw5M6ZRd0orAj);
									} else {
										local NAAybzFnB9JG1KVa4 = sq_GetGlobalIntVector();
										sq_IntVectorClear(NAAybzFnB9JG1KVa4);
										sq_IntVectorPush(NAAybzFnB9JG1KVa4, obj.getXPos());
										sq_IntVectorPush(NAAybzFnB9JG1KVa4, obj.getYPos());
										obj.addSetStatePacket(11, NAAybzFnB9JG1KVa4, STATE_PRIORITY_AUTO, false, "");
									}
								} else
									sq_SendDestroyPacketPassiveObject(obj);
							}
							break;
						case 14:
							local ucFNbdnFzMqiCchx0e = obj.getXPos();
							local uUdvKYdgMiB436DpOP9kCJh = obj.getYPos();
							local kXCg34qgJCzZDMVpwMQc = obj.getVar("move").get_vector(0);
							local V6w8wOSKD0ouYwNSN = obj.getVar("move").get_vector(1);
							local cMw8X0bFBFE6mqfFpe9 = sq_Abs(ucFNbdnFzMqiCchx0e - kXCg34qgJCzZDMVpwMQc);
							local X489_skMRpy1 = sq_Abs(uUdvKYdgMiB436DpOP9kCJh - V6w8wOSKD0ouYwNSN);
							if (cMw8X0bFBFE6mqfFpe9 <= 10 && X489_skMRpy1 <= 10) {

								if (obj.isMyControlObject()) {
									local NAAybzFnB9JG1KVa4 = sq_GetGlobalIntVector();
									sq_IntVectorClear(NAAybzFnB9JG1KVa4);
									obj.addSetStatePacket(15, NAAybzFnB9JG1KVa4, STATE_PRIORITY_AUTO, false, "");
								}
								return;
							} else {

								if (cMw8X0bFBFE6mqfFpe9 > 0) {
									local DKzzvpGQVPK8QLJeUnF = cMw8X0bFBFE6mqfFpe9 / 10 + 1;

									if (ucFNbdnFzMqiCchx0e > kXCg34qgJCzZDMVpwMQc) DKzzvpGQVPK8QLJeUnF /= -1;
									sq_setCurrentAxisPos(obj, 0, ucFNbdnFzMqiCchx0e + DKzzvpGQVPK8QLJeUnF);
								}

								if (X489_skMRpy1 > 0) {
									local vDw5M6ZRd0orAj = X489_skMRpy1 / 10 + 1;

									if (uUdvKYdgMiB436DpOP9kCJh > V6w8wOSKD0ouYwNSN) vDw5M6ZRd0orAj /= -1;
									sq_setCurrentAxisPos(obj, 1, uUdvKYdgMiB436DpOP9kCJh + vDw5M6ZRd0orAj);
								}
							}
							break;
					}
					break;
				case 2:
					switch (state) {
						case 10:
							local iunIR4RUlbwhjG = obj.getVar();
							local jZuKH09wqDizIPWXv9V2J = sq_GetObjectTime(obj);
							local fVKVwayguBRfS9v7Baf = iunIR4RUlbwhjG.get_vector(5);
							local S9GZEmfQvkGm2F6zsYsJ = iunIR4RUlbwhjG.get_vector(0);
							switch (S9GZEmfQvkGm2F6zsYsJ) {
								case 1:
									local qT8tL8fDziot_4J = sq_GetAccel(0, 180, jZuKH09wqDizIPWXv9V2J, fVKVwayguBRfS9v7Baf, false);
									if (qT8tL8fDziot_4J >= 90) {
										iunIR4RUlbwhjG.set_vector(4, obj.getZPos());
										iunIR4RUlbwhjG.set_vector(0, jZuKH09wqDizIPWXv9V2J);
										return;
									}
									local vGttNjVHE5Oz9b4WAh = iunIR4RUlbwhjG.get_vector(2) + iunIR4RUlbwhjG.get_vector(4) * sq_SinTable(qT8tL8fDziot_4J);
									sq_setCurrentAxisPos(obj, 2, vGttNjVHE5Oz9b4WAh.tointeger());
									sq_SetCustomRotate(obj, sq_ToRadian(qT8tL8fDziot_4J.tofloat()) / -1);
									break;
								default:
									local OjjgfIcYTAj_H2qva = jZuKH09wqDizIPWXv9V2J - S9GZEmfQvkGm2F6zsYsJ;
									local DuuPP0VqvY = fVKVwayguBRfS9v7Baf - S9GZEmfQvkGm2F6zsYsJ;
									local AB0HuHKLKRfsnMwVCdlGL = iunIR4RUlbwhjG.get_vector(4) * sq_SinTable(sq_GetUniformVelocity(90, 180, OjjgfIcYTAj_H2qva, DuuPP0VqvY));
									sq_setCurrentAxisPos(obj, 2, AB0HuHKLKRfsnMwVCdlGL.tointeger());
									local rki2a2KJSuG1djsZU7IktXa = sq_GetAccel(90, 165, OjjgfIcYTAj_H2qva, DuuPP0VqvY, true);
									sq_SetCustomRotate(obj, sq_ToRadian(rki2a2KJSuG1djsZU7IktXa.tofloat()) / -1);
									break;
							}
							local NfjwN1NKjSGLVY = sq_GetDistancePos(iunIR4RUlbwhjG.get_vector(1),
								obj.getDirection(),
								sq_GetAccel(0, iunIR4RUlbwhjG.get_vector(3), jZuKH09wqDizIPWXv9V2J, fVKVwayguBRfS9v7Baf, false));
							sq_setCurrentAxisPos(obj, 0, NfjwN1NKjSGLVY);
							if (jZuKH09wqDizIPWXv9V2J >= fVKVwayguBRfS9v7Baf) {
								if (obj.isMyControlObject()) {
									local NAAybzFnB9JG1KVa4 = sq_GetGlobalIntVector();
									sq_IntVectorClear(NAAybzFnB9JG1KVa4);
									obj.addSetStatePacket(11, NAAybzFnB9JG1KVa4, STATE_PRIORITY_AUTO, false, "");
								}
							}
							break;
					}
					break;
			}
			break;
		case 247:
			local FJaCTznG1e4ZZVeu8588c1ja = obj.getVar("subType").get_vector(0);
			if (FJaCTznG1e4ZZVeu8588c1ja == 1) {
				local state = obj.getVar("state").get_vector(0);
				switch (state) {
					case 10:
						local DRc7bP06M25mEbYI3iX = obj.getVar("aniobj");
						local eYkB_jj_F7foWhA = DRc7bP06M25mEbYI3iX.get_obj_vector(0);
						if (eYkB_jj_F7foWhA && sq_IsEnd(eYkB_jj_F7foWhA.getCurrentAnimation())) {
							if (obj.isMyControlObject()) {
								local NAAybzFnB9JG1KVa4 = sq_GetGlobalIntVector();
								sq_IntVectorClear(NAAybzFnB9JG1KVa4);
								obj.addSetStatePacket(11, NAAybzFnB9JG1KVa4, STATE_PRIORITY_AUTO, false, "");
							}
							return;
						}
						break;
					case 12:
						local DRc7bP06M25mEbYI3iX = obj.getVar("aniobj1");
						local eYkB_jj_F7foWhA = DRc7bP06M25mEbYI3iX.get_obj_vector(0);
						local jrNmzX9BrcXLRf = DRc7bP06M25mEbYI3iX.get_obj_vector(1);
						local FeNYfcjjwrCkRh9fXl = eYkB_jj_F7foWhA.getCurrentAnimation();
						local jZuKH09wqDizIPWXv9V2J = sq_GetCurrentTime(FeNYfcjjwrCkRh9fXl);
						local fVKVwayguBRfS9v7Baf = FeNYfcjjwrCkRh9fXl.getDelaySum(0, 0);
						local JQf8wFDwee6jPrRdyuJ = sq_GetAccel(0, obj.getVar().get_vector(5), jZuKH09wqDizIPWXv9V2J, fVKVwayguBRfS9v7Baf, true);
						local XsiVR3QPkqb0OcoV2 = sq_GetDistancePos(DRc7bP06M25mEbYI3iX.get_vector(0), sq_GetDirection(eYkB_jj_F7foWhA), JQf8wFDwee6jPrRdyuJ);
						local ZREeZlxUUHlJ5VGGFlolc8 = sq_GetDistancePos(DRc7bP06M25mEbYI3iX.get_vector(1), sq_GetDirection(jrNmzX9BrcXLRf), JQf8wFDwee6jPrRdyuJ);
						sq_setCurrentAxisPos(eYkB_jj_F7foWhA, 0, XsiVR3QPkqb0OcoV2);
						sq_setCurrentAxisPos(jrNmzX9BrcXLRf, 0, ZREeZlxUUHlJ5VGGFlolc8);

						local eA2U5PtCIpghr = obj.getVar("clarity").get_vector(0);
						local AlJlNfDuE5ErCPJTWfPjmzJ = eA2U5PtCIpghr + sq_GetUniformVelocity(0, obj.getVar().get_vector(6), jZuKH09wqDizIPWXv9V2J, fVKVwayguBRfS9v7Baf);
						local xNlXDvOvQV60l_nDkF8B4 = sq_getAniLayerListObject(FeNYfcjjwrCkRh9fXl, 0);
						local Kv53P0IGorW33_CZc6f5RME = sq_getAniLayerListObject(xNlXDvOvQV60l_nDkF8B4, 0);
						xNlXDvOvQV60l_nDkF8B4.setRGBA(255, 255, 255, AlJlNfDuE5ErCPJTWfPjmzJ);
						Kv53P0IGorW33_CZc6f5RME.setRGBA(255, 255, 255, AlJlNfDuE5ErCPJTWfPjmzJ);
						if (sq_IsEnd(FeNYfcjjwrCkRh9fXl)) {
							if (obj.isMyControlObject()) {
								local NAAybzFnB9JG1KVa4 = sq_GetGlobalIntVector();
								sq_IntVectorClear(NAAybzFnB9JG1KVa4);
								obj.addSetStatePacket(13, NAAybzFnB9JG1KVa4, STATE_PRIORITY_AUTO, false, "");
							}
						}
						break;
					case 13:
						local DRc7bP06M25mEbYI3iX = obj.getVar("aniobj1");
						local eYkB_jj_F7foWhA = DRc7bP06M25mEbYI3iX.get_obj_vector(0);
						local jrNmzX9BrcXLRf = DRc7bP06M25mEbYI3iX.get_obj_vector(1);
						local FeNYfcjjwrCkRh9fXl = eYkB_jj_F7foWhA.getCurrentAnimation();
						local jZuKH09wqDizIPWXv9V2J = sq_GetCurrentTime(FeNYfcjjwrCkRh9fXl);
						local fVKVwayguBRfS9v7Baf = FeNYfcjjwrCkRh9fXl.getDelaySum(0, 0);
						local JQf8wFDwee6jPrRdyuJ = sq_GetAccel(0, obj.getVar().get_vector(5), jZuKH09wqDizIPWXv9V2J, fVKVwayguBRfS9v7Baf, true);
						local XsiVR3QPkqb0OcoV2 = sq_GetDistancePos(DRc7bP06M25mEbYI3iX.get_vector(0), sq_GetDirection(eYkB_jj_F7foWhA), JQf8wFDwee6jPrRdyuJ);
						local ZREeZlxUUHlJ5VGGFlolc8 = sq_GetDistancePos(DRc7bP06M25mEbYI3iX.get_vector(1), sq_GetDirection(jrNmzX9BrcXLRf), JQf8wFDwee6jPrRdyuJ);
						sq_setCurrentAxisPos(eYkB_jj_F7foWhA, 0, XsiVR3QPkqb0OcoV2);
						sq_setCurrentAxisPos(jrNmzX9BrcXLRf, 0, ZREeZlxUUHlJ5VGGFlolc8);


						local QXo755kkADfCrjm7Nt7 = obj.getVar("clarity");
						local eA2U5PtCIpghr = QXo755kkADfCrjm7Nt7.get_vector(0);
						local AlJlNfDuE5ErCPJTWfPjmzJ = eA2U5PtCIpghr + sq_GetUniformVelocity(0, obj.getVar().get_vector(6), jZuKH09wqDizIPWXv9V2J, fVKVwayguBRfS9v7Baf);
						local xO2MRj6kfXm = sq_getAniLayerListObject(eYkB_jj_F7foWhA.getCurrentAnimation(), 0);
						local n2bb_uzOwd4DMJk04tFo = sq_getAniLayerListObject(xO2MRj6kfXm, 0);
						local FIKvzbLNSey4ZHxIvZUqWX1 = sq_getAniLayerListObject(jrNmzX9BrcXLRf.getCurrentAnimation(), 0);
						local f_G_5f86iGOsU0vAWAj = sq_getAniLayerListObject(FIKvzbLNSey4ZHxIvZUqWX1, 0);
						xO2MRj6kfXm.setRGBA(255, 255, 255, AlJlNfDuE5ErCPJTWfPjmzJ);
						n2bb_uzOwd4DMJk04tFo.setRGBA(255, 255, 255, AlJlNfDuE5ErCPJTWfPjmzJ);
						FIKvzbLNSey4ZHxIvZUqWX1.setRGBA(255, 255, 255, AlJlNfDuE5ErCPJTWfPjmzJ);
						f_G_5f86iGOsU0vAWAj.setRGBA(255, 255, 255, AlJlNfDuE5ErCPJTWfPjmzJ);

						local KO51Bpms78oJ = QXo755kkADfCrjm7Nt7.size_vector() - 1;
						local suxAZZg39F5680cfBmLz = obj.getVar("aniobj2");
						for (local JmXD2DGG_8cLUzS20PL17U = 1; JmXD2DGG_8cLUzS20PL17U <= KO51Bpms78oJ; JmXD2DGG_8cLUzS20PL17U++) {
							local qCGp4MqmkfGjOQNJ6Wy9TQy = QXo755kkADfCrjm7Nt7.get_vector(JmXD2DGG_8cLUzS20PL17U);
							local EAaBK_lA7TXLyzAH = (JmXD2DGG_8cLUzS20PL17U - 1) * 12;
							for (local XcUMqdgNc8Dk5vw83vnf = 0; XcUMqdgNc8Dk5vw83vnf < 12; XcUMqdgNc8Dk5vw83vnf++) {
								local V4o3I5QRKja4vDQx = suxAZZg39F5680cfBmLz.get_obj_vector(EAaBK_lA7TXLyzAH + XcUMqdgNc8Dk5vw83vnf);
								local XXNt0ZQglrXOheWLRmGA = sq_getAniLayerListObject(V4o3I5QRKja4vDQx.getCurrentAnimation(), 0);
								local GNp8WkewVXSiTDaSeCwPUtZU = sq_getAniLayerListObject(XXNt0ZQglrXOheWLRmGA, 0);
								XXNt0ZQglrXOheWLRmGA.setRGBA(255, 255, 255, AlJlNfDuE5ErCPJTWfPjmzJ);
								GNp8WkewVXSiTDaSeCwPUtZU.setRGBA(255, 255, 255, AlJlNfDuE5ErCPJTWfPjmzJ);
							}
						}

						if (sq_IsEnd(FeNYfcjjwrCkRh9fXl)) {
							if (obj.isMyControlObject()) {
								local NAAybzFnB9JG1KVa4 = sq_GetGlobalIntVector();
								sq_IntVectorClear(NAAybzFnB9JG1KVa4);
								local yjYR2pb5Rr9el = obj.getVar().get_vector(0);
								if (yjYR2pb5Rr9el > 0)
									obj.addSetStatePacket(13, NAAybzFnB9JG1KVa4, STATE_PRIORITY_AUTO, false, "");
								else
									obj.addSetStatePacket(14, NAAybzFnB9JG1KVa4, STATE_PRIORITY_AUTO, false, "");
							}
						}
						break;
					case 14:
						local eIMnBUg56xAsxOmbcUGz7zn9 = obj.getVar("aniobj");
						local zmK2XitCtxRqZHSZ0aqL = eIMnBUg56xAsxOmbcUGz7zn9.get_obj_vector(0);
						if (zmK2XitCtxRqZHSZ0aqL && sq_IsEnd(zmK2XitCtxRqZHSZ0aqL.getCurrentAnimation())) {

							for (local XcUMqdgNc8Dk5vw83vnf = 0; XcUMqdgNc8Dk5vw83vnf < 4; XcUMqdgNc8Dk5vw83vnf++) {
								local frVfEK3W68fi_nPa = eIMnBUg56xAsxOmbcUGz7zn9.get_obj_vector(XcUMqdgNc8Dk5vw83vnf);
								if (frVfEK3W68fi_nPa)
									frVfEK3W68fi_nPa.setValid(false);
								else
									break;
							}
						}


						local QXo755kkADfCrjm7Nt7 = obj.getVar("clarity");
						local eA2U5PtCIpghr = QXo755kkADfCrjm7Nt7.get_vector(0);
						local AlJlNfDuE5ErCPJTWfPjmzJ = eA2U5PtCIpghr + 1;
						if (AlJlNfDuE5ErCPJTWfPjmzJ < 255) {
							local Ft5wxcEzIGq = obj.getVar("aniobj1");
							local f8K5bOSUo7Oc1 = Ft5wxcEzIGq.get_obj_vector(0);
							local oEhdY73uzLVtw0oKFthg96oV = Ft5wxcEzIGq.get_obj_vector(1);
							local xO2MRj6kfXm = f8K5bOSUo7Oc1.getCurrentAnimation();
							local n2bb_uzOwd4DMJk04tFo = sq_getAniLayerListObject(xO2MRj6kfXm, 0);
							local FIKvzbLNSey4ZHxIvZUqWX1 = oEhdY73uzLVtw0oKFthg96oV.getCurrentAnimation();
							local f_G_5f86iGOsU0vAWAj = sq_getAniLayerListObject(FIKvzbLNSey4ZHxIvZUqWX1, 0);
							xO2MRj6kfXm.setRGBA(255, 255, 255, AlJlNfDuE5ErCPJTWfPjmzJ);
							n2bb_uzOwd4DMJk04tFo.setRGBA(255, 255, 255, AlJlNfDuE5ErCPJTWfPjmzJ);
							FIKvzbLNSey4ZHxIvZUqWX1.setRGBA(255, 255, 255, AlJlNfDuE5ErCPJTWfPjmzJ);
							f_G_5f86iGOsU0vAWAj.setRGBA(255, 255, 255, AlJlNfDuE5ErCPJTWfPjmzJ);
							QXo755kkADfCrjm7Nt7.set_vector(0, AlJlNfDuE5ErCPJTWfPjmzJ);
						}

						local KO51Bpms78oJ = QXo755kkADfCrjm7Nt7.size_vector() - 1;
						local suxAZZg39F5680cfBmLz = obj.getVar("aniobj2");
						for (local JmXD2DGG_8cLUzS20PL17U = 1; JmXD2DGG_8cLUzS20PL17U <= KO51Bpms78oJ; JmXD2DGG_8cLUzS20PL17U++) {
							local qCGp4MqmkfGjOQNJ6Wy9TQy = QXo755kkADfCrjm7Nt7.get_vector(JmXD2DGG_8cLUzS20PL17U);
							local vJOBiTmlp8d = qCGp4MqmkfGjOQNJ6Wy9TQy + 1;
							if (vJOBiTmlp8d >= 255) continue;
							local EAaBK_lA7TXLyzAH = (JmXD2DGG_8cLUzS20PL17U - 1) * 12;
							for (local XcUMqdgNc8Dk5vw83vnf = 0; XcUMqdgNc8Dk5vw83vnf < 12; XcUMqdgNc8Dk5vw83vnf++) {
								local V4o3I5QRKja4vDQx = suxAZZg39F5680cfBmLz.get_obj_vector(EAaBK_lA7TXLyzAH + XcUMqdgNc8Dk5vw83vnf);
								local XXNt0ZQglrXOheWLRmGA = V4o3I5QRKja4vDQx.getCurrentAnimation();
								local GNp8WkewVXSiTDaSeCwPUtZU = sq_getAniLayerListObject(XXNt0ZQglrXOheWLRmGA, 0);
								XXNt0ZQglrXOheWLRmGA.setRGBA(255, 255, 255, vJOBiTmlp8d);
								GNp8WkewVXSiTDaSeCwPUtZU.setRGBA(255, 255, 255, vJOBiTmlp8d);
							}
							QXo755kkADfCrjm7Nt7.set_vector(JmXD2DGG_8cLUzS20PL17U, vJOBiTmlp8d);
						}
						local eYkB_jj_F7foWhA = obj.getVar("aniobj1").get_obj_vector(0);
						if (eYkB_jj_F7foWhA && sq_IsEnd(eYkB_jj_F7foWhA.getCurrentAnimation())) {
							if (obj.isMyControlObject()) {
								local NAAybzFnB9JG1KVa4 = sq_GetGlobalIntVector();
								sq_IntVectorClear(NAAybzFnB9JG1KVa4);
								obj.addSetStatePacket(15, NAAybzFnB9JG1KVa4, STATE_PRIORITY_AUTO, false, "");
							}
							return;
						}
						break;
					case 15:
						local vmKpQo24VTok44Lv24PlzL = obj.getVar("aniobj2");
						local eYkB_jj_F7foWhA = vmKpQo24VTok44Lv24PlzL.get_obj_vector(0);
						if (sq_IsEnd(eYkB_jj_F7foWhA.getCurrentAnimation())) {
							if (obj.isMyControlObject()) {
								local NAAybzFnB9JG1KVa4 = sq_GetGlobalIntVector();
								sq_IntVectorClear(NAAybzFnB9JG1KVa4);
								obj.addSetStatePacket(16, NAAybzFnB9JG1KVa4, STATE_PRIORITY_AUTO, false, "");
							}
							return;
						}
						break;
					case 16:
						local zejBNZiEfpPO8iCtyk9jYaNg = obj.getVar("aniobj1");
						local eYkB_jj_F7foWhA = zejBNZiEfpPO8iCtyk9jYaNg.get_obj_vector(0);
						if (sq_IsEnd(eYkB_jj_F7foWhA.getCurrentAnimation())) {
							if (obj.isMyControlObject()) {
								local NAAybzFnB9JG1KVa4 = sq_GetGlobalIntVector();
								sq_IntVectorClear(NAAybzFnB9JG1KVa4);
								obj.addSetStatePacket(17, NAAybzFnB9JG1KVa4, STATE_PRIORITY_AUTO, false, "");
							}
							return;
						}
						break;
					case 17:
						local zejBNZiEfpPO8iCtyk9jYaNg = obj.getVar("aniobj1");
						local eYkB_jj_F7foWhA = zejBNZiEfpPO8iCtyk9jYaNg.get_obj_vector(0);
						if (eYkB_jj_F7foWhA)
							if (sq_IsEnd(eYkB_jj_F7foWhA.getCurrentAnimation())) {
								if (obj.isMyControlObject())
									sq_SendDestroyPacketPassiveObject(obj);
								return;
							}
						else {
							local jZmM4PUZ0uiiG57CaweUlFL = obj.getVar("aniobj").get_obj_vector(0);
							if (jZmM4PUZ0uiiG57CaweUlFL) {
								local FeNYfcjjwrCkRh9fXl = jZmM4PUZ0uiiG57CaweUlFL.getCurrentAnimation();
								local jZuKH09wqDizIPWXv9V2J = sq_GetCurrentTime(FeNYfcjjwrCkRh9fXl);
								local fVKVwayguBRfS9v7Baf = FeNYfcjjwrCkRh9fXl.getDelaySum(false);
								local JQf8wFDwee6jPrRdyuJ = sq_GetUniformVelocity(255, 50, jZuKH09wqDizIPWXv9V2J, fVKVwayguBRfS9v7Baf);
								FeNYfcjjwrCkRh9fXl.setRGBA(255, 255, 255, JQf8wFDwee6jPrRdyuJ);
								local t5IO_dD6AcApkGWiwBJr = sq_AniLayerListSize(FeNYfcjjwrCkRh9fXl);
								for (local XcUMqdgNc8Dk5vw83vnf = 0; XcUMqdgNc8Dk5vw83vnf < t5IO_dD6AcApkGWiwBJr; XcUMqdgNc8Dk5vw83vnf++) {
									local wP8xLvWGg42gbBv = sq_getAniLayerListObject(FeNYfcjjwrCkRh9fXl, XcUMqdgNc8Dk5vw83vnf);
									wP8xLvWGg42gbBv.setRGBA(255, 255, 255, JQf8wFDwee6jPrRdyuJ);
								}
							}
						}
						break;
				}
			}
			break;
	}
};

