

function procAppend_po_qq506807329new_atmage_24377(obj) {
	if (!obj) return;
	local tVkhhJRGalKq = obj.getVar("skill").get_vector(0);
	local RNDKDGb7Xh4tmzwoFrEmqi4B = obj.getVar("subType").get_vector(0);
	local LqMdIv7SpKl = obj.getVar("state").get_vector(0);
	switch (tVkhhJRGalKq) {
		case 125:
			local pAni = obj.getCurrentAnimation();
			local frmIndex = sq_GetAnimationFrameIndex(pAni);
			local currentT = sq_GetCurrentTime(pAni);
			local PosX = sq_GetXPos(obj);
			local v = sq_GetUniformVelocity(0, 100, currentT, 4000);
			local dstX = sq_GetDistancePos(PosX, obj.getDirection(), v);
			sq_setCurrentAxisPos(obj, 0, dstX);
			break;
		case 243:
			switch (RNDKDGb7Xh4tmzwoFrEmqi4B) {
				case 1:
					switch (LqMdIv7SpKl) {
						case 12:
							if (obj.getVar("time").size_vector() <= 0) return;
							local JFlt1wvdwKdlcbytEGuXGD = sq_GetObjectTime(obj) - obj.getVar("time").get_vector(0);
							local OmDrZNzyRAkMj9s96nEZ_GvJ = obj.getVar("time").get_vector(1);
							local gZ9vWm31LHYy = sq_GetUniformVelocity(255, 0, JFlt1wvdwKdlcbytEGuXGD, OmDrZNzyRAkMj9s96nEZ_GvJ);
							setRgba_qq506807329(obj, 255, 255, 255, gZ9vWm31LHYy);
							local OhOWPP3mH4iYqseXBJ2C4W4a = obj.getVar("aniobj").get_obj_vector(0);
							setRgba_qq506807329(OhOWPP3mH4iYqseXBJ2C4W4a, 255, 255, 255, gZ9vWm31LHYy);
							if (JFlt1wvdwKdlcbytEGuXGD >= OmDrZNzyRAkMj9s96nEZ_GvJ && obj.isMyControlObject())
								sq_SendDestroyPacketPassiveObject(obj);
							break;
					}
					break;
			}
			break;
		case 244:
			switch (RNDKDGb7Xh4tmzwoFrEmqi4B) {
				case 1:
					switch (LqMdIv7SpKl) {
						case 10:
							local wqgNmsUX8Cewg4GFQlGLK = obj.getParent();
							if (!wqgNmsUX8Cewg4GFQlGLK) {
								if (obj.isMyControlObject()) {
									obj.addSetStatePacket(11, null, STATE_PRIORITY_AUTO, false, "");
									return;
								}
							} else if (obj.sq_GetParentState() != 244 || obj.sq_GetParentSkillSubState() == 2) {
								if (obj.isMyControlObject())
									obj.addSetStatePacket(11, null, STATE_PRIORITY_AUTO, false, "");
							}
							break;
						case 11:
							local wqgNmsUX8Cewg4GFQlGLK = sq_GetCNRDObjectToSQRCharacter(obj.getParent());
							if (wqgNmsUX8Cewg4GFQlGLK) {
								if (wqgNmsUX8Cewg4GFQlGLK.sq_IsEnterSkill(244) != -1)
									if (obj.isMyControlObject()) {
										obj.addSetStatePacket(12, null, STATE_PRIORITY_AUTO, false, "");
										return;
									}
							}
							if (obj.getVar("move").size_vector() <= 0) return;
							local FWS2k_OmSy7x9 = sq_GetObjectTime(obj);
							local JFlt1wvdwKdlcbytEGuXGD = FWS2k_OmSy7x9 - obj.getVar("move").get_vector(3);
							local OmDrZNzyRAkMj9s96nEZ_GvJ = obj.getVar("move").get_vector(2);
							local eCM5Q7FEfbwHQ7C1f_0cBee = sq_GetDistancePos(obj.getVar("move").get_vector(0),
								obj.getDirection(),
								sq_GetUniformVelocity(0, obj.getVar("move").get_vector(1), JFlt1wvdwKdlcbytEGuXGD, OmDrZNzyRAkMj9s96nEZ_GvJ));
							sq_setCurrentAxisPos(obj, 0, eCM5Q7FEfbwHQ7C1f_0cBee);

							local seOgo9OdGMJZnoU_eWIAC = obj.getVar().get_timer_vector(0);
							if (seOgo9OdGMJZnoU_eWIAC)
								if (seOgo9OdGMJZnoU_eWIAC.isOnEvent(FWS2k_OmSy7x9) == true) {
									local pAvaJgrCBKPrLfjgpt = sq_getRandom(0, 100) > 50 ?
										"character/mage/effect/animation/atconvergencecannon/shot/groundloop01_floor.ani" :
										"character/mage/effect/animation/atconvergencecannon/shot/groundloop02_floor.ani";
									createPooledObjEff_qq506807329(obj, pAvaJgrCBKPrLfjgpt, obj.getXPos(), obj.getYPos(), obj.getZPos(), ENUM_DRAWLAYER_BOTTOM, sq_GetOppositeDirection(obj.getDirection()));
								}
							if (JFlt1wvdwKdlcbytEGuXGD >= OmDrZNzyRAkMj9s96nEZ_GvJ && obj.isMyControlObject())
								obj.addSetStatePacket(12, null, STATE_PRIORITY_AUTO, false, "");
							break;
					}
					break;
			}
			break;
		case 245:
			switch (RNDKDGb7Xh4tmzwoFrEmqi4B) {
				case 1:
					local wqgNmsUX8Cewg4GFQlGLK = obj.getParent();
					if (!wqgNmsUX8Cewg4GFQlGLK) {
						if (obj.isMyControlObject())
							sq_SendDestroyPacketPassiveObject(obj);
					}
					break;
			}
			break;
		case 246:
			switch (RNDKDGb7Xh4tmzwoFrEmqi4B) {
				case 1:
					if (LqMdIv7SpKl != 10) {
						local wqgNmsUX8Cewg4GFQlGLK = obj.getParent();
						if (!wqgNmsUX8Cewg4GFQlGLK) {
							if (obj.isMyControlObject())
								sq_SendDestroyPacketPassiveObject(obj);
						}
					}
					break;
			}
			break;
	}
};
