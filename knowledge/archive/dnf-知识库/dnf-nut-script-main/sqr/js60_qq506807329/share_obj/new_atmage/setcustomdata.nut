 
 
function setCustomData_po_qq506807329new_atmage_24377(obj, reciveData) {
	if (!obj) return;
	local netZD7Dbmq = reciveData.readDword();
	obj.getVar("skill").clear_vector();
	obj.getVar("skill").push_vector(netZD7Dbmq);
	switch (netZD7Dbmq) {
		case 125:
			local power = reciveData.readDword();
			local ani = obj.getVar().GetAnimationMap("nyarlyshoot", "passiveobject/script_sqr_nut_qq506807329/atmage/animation/atnyarly/nyarly_shooting_projectile.ani");
			obj.setCurrentAnimation(ani);
			local attackInfo = sq_GetCustomAttackInfo(obj, 12);
			sq_SetCurrentAttackInfo(obj, attackInfo);
			attackInfo = sq_GetCurrentAttackInfo(obj);
			sq_SetCurrentAttackPower(attackInfo, power);
			break;
		case 243:
			local LNTkxz7Jl_9hzqndfBkD4iSH = reciveData.readDword();
			obj.getVar("subType").clear_vector();
			obj.getVar("subType").push_vector(LNTkxz7Jl_9hzqndfBkD4iSH);
			switch (LNTkxz7Jl_9hzqndfBkD4iSH) {
				case 1:
					sq_ChangeDrawLayer(obj, ENUM_DRAWLAYER_BOTTOM);
					local CN4JYsjoyeLMCgxOV = sq_GetCustomAttackInfo(obj, 0);
					sq_SetCurrentAttackBonusRate(CN4JYsjoyeLMCgxOV, reciveData.readDword());
					sq_SetCurrentAttackInfo(obj, CN4JYsjoyeLMCgxOV);
					obj.getVar().setFloat(0, reciveData.readFloat());
					obj.getVar().clear_vector();
					obj.getVar().push_vector(reciveData.readDword());
					if (obj.isMyControlObject())
						obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, "");
					break;
			}
			break;
		case 244:
			local LNTkxz7Jl_9hzqndfBkD4iSH = reciveData.readDword();
			obj.getVar("subType").clear_vector();
			obj.getVar("subType").push_vector(LNTkxz7Jl_9hzqndfBkD4iSH);
			switch (LNTkxz7Jl_9hzqndfBkD4iSH) {
				case 1:

					sq_SetCurrentAttackBonusRate(sq_GetCustomAttackInfo(obj, 2), reciveData.readDword());
					local TeHNQv2_FTP7tNIglnN38eP = reciveData.readDword() / 100.0;
					local A9yL4uSpZsRY9BGMY = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atconvergencecannon/bigorb_orbd.ani", TeHNQv2_FTP7tNIglnN38eP, false);
					local hgQUvSbfN1qdSfzoikuqVbZj = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atconvergencecannon/projectile_dodge.ani", TeHNQv2_FTP7tNIglnN38eP, false);
					local Ca1tcSMgeXsB0 = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atconvergencecannon/explosion/explosion_dodge.ani", TeHNQv2_FTP7tNIglnN38eP, false);
					obj.addCustomAnimation(A9yL4uSpZsRY9BGMY);
					obj.addCustomAnimation(hgQUvSbfN1qdSfzoikuqVbZj);
					obj.addCustomAnimation(Ca1tcSMgeXsB0);
					local QsIpP8bWywLUfPc0Dc9 = reciveData.readDword();
					local Ijc9lieNnx8diGDH = 150;
					obj.getVar("move").clear_vector();
					obj.getVar("move").push_vector(obj.getXPos());
					obj.getVar("move").push_vector(QsIpP8bWywLUfPc0Dc9);
					obj.getVar("move").push_vector(Ijc9lieNnx8diGDH);

					obj.getVar().clear_timer_vector();
					obj.getVar().push_timer_vector();
					local s9iIo4JfJfuXw = obj.getVar().get_timer_vector(0);
					s9iIo4JfJfuXw.setParameter(Ijc9lieNnx8diGDH / (QsIpP8bWywLUfPc0Dc9 / 65), -1);
					s9iIo4JfJfuXw.resetInstant(0);
					obj.sq_PlaySound("R_DARKSHOT_HIT");
					if (obj.isMyControlObject())
						obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, "");
					break;
			}
			break;
		case 245:
			local LNTkxz7Jl_9hzqndfBkD4iSH = reciveData.readDword();
			obj.getVar("subType").clear_vector();
			obj.getVar("subType").push_vector(LNTkxz7Jl_9hzqndfBkD4iSH);

			switch (LNTkxz7Jl_9hzqndfBkD4iSH) {
				case 1:

					sq_SetCurrentAttackBonusRate(sq_GetCustomAttackInfo(obj, 3), reciveData.readDword());

					sq_SetCurrentAttackBonusRate(sq_GetCustomAttackInfo(obj, 4), reciveData.readDword());
					local TeHNQv2_FTP7tNIglnN38eP = reciveData.readDword() / 100.0;
					obj.getVar("sizeRate").setFloat(0, TeHNQv2_FTP7tNIglnN38eP);
					local A9yL4uSpZsRY9BGMY = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atarmageddonstrike/ascolorball_00.ani", TeHNQv2_FTP7tNIglnN38eP, false);
					local hgQUvSbfN1qdSfzoikuqVbZj = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atarmageddonstrike/asblackball_00.ani", TeHNQv2_FTP7tNIglnN38eP, false);
					obj.addCustomAnimation(A9yL4uSpZsRY9BGMY);
					obj.addCustomAnimation(hgQUvSbfN1qdSfzoikuqVbZj);
					obj.sq_PlaySound("R_DARKSHOT_HIT");
					if (obj.isMyControlObject())
						obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, "");
					break;
				case 2:
					local CN4JYsjoyeLMCgxOV = sq_GetCustomAttackInfo(obj, 5);
					sq_SetCurrentAttackBonusRate(CN4JYsjoyeLMCgxOV, reciveData.readDword());
					sq_SetCurrentAttackInfo(obj, CN4JYsjoyeLMCgxOV);
					local A9yL4uSpZsRY9BGMY = sq_CreateAnimation("", "passiveobject/script_sqr_nut_qq506807329/atmage/animation/atarmageddonstrike/explosion_01.ani");
					obj.setCurrentAnimation(A9yL4uSpZsRY9BGMY);
					break;
			}
			break;
		case 246:
			local LNTkxz7Jl_9hzqndfBkD4iSH = reciveData.readDword();
			obj.getVar("subType").clear_vector();
			obj.getVar("subType").push_vector(LNTkxz7Jl_9hzqndfBkD4iSH);
			switch (LNTkxz7Jl_9hzqndfBkD4iSH) {
				case 1:
					local Xf9WUoK3kgOAY_oA = obj.getTopCharacter();
					if (Xf9WUoK3kgOAY_oA) {

						Xf9WUoK3kgOAY_oA.getVar().clear_obj_vector();
						Xf9WUoK3kgOAY_oA.getVar().push_obj_vector(obj);
					}
					sq_SetCurrentAttackInfoFromCustomIndex(obj, 6);
					local TeHNQv2_FTP7tNIglnN38eP = reciveData.readDword() / 100.0;
					obj.getVar("sizeRate").setFloat(0, TeHNQv2_FTP7tNIglnN38eP);
					local A9yL4uSpZsRY9BGMY = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atshardmagnum/shardmagnumstep1_01iceboom4.ani", TeHNQv2_FTP7tNIglnN38eP, false);
					local hgQUvSbfN1qdSfzoikuqVbZj = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atshardmagnum/shardmagnumstep2_02handglow.ani", TeHNQv2_FTP7tNIglnN38eP, false);
					obj.addCustomAnimation(A9yL4uSpZsRY9BGMY);
					obj.addCustomAnimation(hgQUvSbfN1qdSfzoikuqVbZj);
					setCurrentAnimationFromCutomIndex(obj, 0);
					break;
			}
			break;
		case 247:
			local LNTkxz7Jl_9hzqndfBkD4iSH = reciveData.readDword();
			obj.getVar("subType").clear_vector();
			obj.getVar("subType").push_vector(LNTkxz7Jl_9hzqndfBkD4iSH);
			switch (LNTkxz7Jl_9hzqndfBkD4iSH) {
				case 1:
					local TeHNQv2_FTP7tNIglnN38eP = reciveData.readFloat();
					local DXVjRWliS1ZHpECo = reciveData.readFloat();
					obj.getVar("sizeRate").setFloat(0, TeHNQv2_FTP7tNIglnN38eP);
					local A9yL4uSpZsRY9BGMY = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atoverfreezeextension/atoverfreezeextension_shock_circle_front.ani", TeHNQv2_FTP7tNIglnN38eP, DXVjRWliS1ZHpECo);
					local w9xFqW7mKRsOSAE1gCfDe = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atoverfreezeextension/atoverfreezeextension_shock_circle_back.ani", TeHNQv2_FTP7tNIglnN38eP, DXVjRWliS1ZHpECo);
					A9yL4uSpZsRY9BGMY.addLayerAnimation(-1, w9xFqW7mKRsOSAE1gCfDe, true);
					obj.addCustomAnimation(A9yL4uSpZsRY9BGMY);
					setCurrentAnimationFromCutomIndex(obj, 0);
					sq_SetCurrentAttackInfoFromCustomIndex(obj, 8);
					local CN4JYsjoyeLMCgxOV = sq_GetCurrentAttackInfo(obj);
					sq_SetCurrentAttackBonusRate(CN4JYsjoyeLMCgxOV, reciveData.readDword());
					obj.getVar().clear_vector();
					obj.getVar().push_vector(reciveData.readDword());
					break;
			}
			break;
		case 248:
			local LNTkxz7Jl_9hzqndfBkD4iSH = reciveData.readDword();
			obj.getVar("subType").clear_vector();
			obj.getVar("subType").push_vector(LNTkxz7Jl_9hzqndfBkD4iSH);
			switch (LNTkxz7Jl_9hzqndfBkD4iSH) {
				case 1:
					local A9yL4uSpZsRY9BGMY = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atjudekatheeternal/arrow_shoot.ani", false, false);
					local hgQUvSbfN1qdSfzoikuqVbZj = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atjudekatheeternal/ice/judekatheeternal_first.ani", false, false);
					local Ca1tcSMgeXsB0 = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atjudekatheeternal/ice/judekatheeternal_second.ani", false, false);
					local FOvaeRcF9jb = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atjudekatheeternal/ice/judekatheeternal_third.ani", false, false);
					local HNS9e0qzjNGDo = sq_CreateAnimation_SizeRate_SpeedRate("passiveobject/script_sqr_nut_qq506807329/atmage/animation/atjudekatheeternal/explosion/judekatheeternal_explosion.ani", false, false);
					obj.addCustomAnimation(A9yL4uSpZsRY9BGMY);
					obj.addCustomAnimation(hgQUvSbfN1qdSfzoikuqVbZj);
					obj.addCustomAnimation(Ca1tcSMgeXsB0);
					obj.addCustomAnimation(FOvaeRcF9jb);
					obj.addCustomAnimation(HNS9e0qzjNGDo);

					sq_SetCurrentAttackBonusRate(sq_GetCustomAttackInfo(obj, 9), reciveData.readDword());

					sq_SetCurrentAttackBonusRate(sq_GetCustomAttackInfo(obj, 10), reciveData.readDword());

					sq_SetCurrentAttackBonusRate(sq_GetCustomAttackInfo(obj, 11), reciveData.readDword());
					obj.getVar().setBool(0, false);
					obj.getVar().clear_obj_vector();
					obj.getVar().clear_vector();
					obj.getVar().push_vector(reciveData.readDword());
					if (obj.isMyControlObject())
						obj.addSetStatePacket(10, null, STATE_PRIORITY_AUTO, false, "");
					break;
			}
			break;
	}
};
