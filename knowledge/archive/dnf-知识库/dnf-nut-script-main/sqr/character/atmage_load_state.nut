

//******************************************************************************************
// ï¿??ï¿??ï¿?? ï¿??ï¿??
//******************************************************************************************
IRDSQRCharacter.pushScriptFiles("Character/ATMage/atmage_header.nut");	// ï¿??ï¿??ï¿?? ï¿???ï¿??? ï¿??ï¿??ï¿?? ï¿??ï¿?? ï¿???ï¿?ï¿??ï¿?enumï¿?? ï¿??ï¿??)
IRDSQRCharacter.pushScriptFiles("Character/ATMage/atmage_common.nut"); //  ï¿???ï¿?? stateï¿?? ï¿??ï¿??ï¿??ï¿???ï¿?? ï¿??? ï¿??ï¿??ï¿?? ï¿??ï¿?? ï¿??? ï¿????
//IRDSQRCharacter.pushScriptFiles("Character/ATMage/atmage_throw.nut"); //  state_throwï¿??ï¿?? ?ï¿??ï¿??ï¿??ï¿??Ï´ï¿?ï¿???ï¿????.
IRDSQRCharacter.pushScriptFiles("Character/ATMage/passive_skill_ATMage.nut"); // ï¿??ï¿??ï¿?? ï¿???? ï¿???ï¿?? ?ï¿??ï¿??? ï¿???ï¿????.

IRDSQRCharacter.pushScriptFiles("character/atmage/bloodcut/bloodcut_receivedata.nut");
IRDSQRCharacter.pushScriptFiles("character/atmage/bloodcut/bloodcut_frameflag.nut");
IRDSQRCharacter.pushScriptFiles("character/atmage/bloodcut/bloodcut_onattack.nut");
IRDSQRCharacter.pushScriptFiles("character/atmage/bloodcut/bloodcut_ontimeevent.nut");
IRDSQRCharacter.pushScriptFiles("character/atmage/bloodcut/bloodcut_procappend.nut");
IRDSQRCharacter.pushScriptFiles("character/atmage/bloodcut/bloodcut_onendcurrentani.nut");
IRDSQRCharacter.pushScriptFiles("character/atmage/zrr/atmage_value1.nut");
IRDSQRCharacter.pushScriptFiles("character/atmage/zrr/atmage_value2.nut");

sq_RunScript("js60_qq506807329/js60_506807329_common.nut");

//zrr
//PARTICLESTROM
//MOIRROR
//
IRDSQRCharacter.pushState(8,"character/atmage/bloodhit/offering.nut","BLOODHIT",STATE_BLOODHIT,SKILL_BLOODHIT);
IRDSQRCharacter.pushState(8, "character/atmage/stand/stand.nut", "AtmageStand", 0,-1);
IRDSQRCharacter.pushState(8, "character/atmage/jump/jump.nut", "ATMage_Jump",STATE_JUMP, -1);
IRDSQRCharacter.pushState(8, "character/atmage/particlesmoke/particlesmoke.nut", "",STATE_PARTICLE_SMOKE, SKILL_PARTICLE_SMOKE);
IRDSQRCharacter.pushPassiveObj("monster/po_move/main.nut", 24378);
IRDSQRCharacter.pushPassiveObj("character/atmage/particlevoid/po_particle_void.nut", 24343);
IRDSQRCharacter.pushState(8, "character/atmage/delusion/delusion.nut", "DELUSION",STATE_DELUSION, SKILL_DELUSION);
IRDSQRCharacter.pushState(8, "character/atmage/teatime/teatime.nut", "TEATIME",STATE_TEATIME, SKILL_TEATIME);
IRDSQRCharacter.pushState(8, "character/atmage/atg/atg.nut", "None",STATE_ATG, SKILL_ATG);
IRDSQRCharacter.pushState(8, "character/atmage/timetape/timetape.nut", "TIMETAPE", STATE_TIMETAPE, SKILL_TIMETAPE);
IRDSQRCharacter.pushState(8, "character/atmage/null50/null50.nut", "NULL50", STATE_NULL50, SKILL_NULL50);
IRDSQRCharacter.pushState(8, "character/atmage/summon_woman/summon_woman.nut", "SUMMON_WOMAN", STATE_SUMMON_WOMAN, SKILL_SUMMON_WOMAN);
IRDSQRCharacter.pushPassiveObj("character/atmage/summon_woman/po_nyarly.nut", 24342);
IRDSQRCharacter.pushState(8, "character/atmage/null85/null85.nut", "NULL85", STATE_NULL85, SKILL_NULL85);
IRDSQRCharacter.pushPassiveObj("character/atmage/null85/po_null85_loop_0.nut", 24339);
IRDSQRCharacter.pushState(8, "character/atmage/dropbox/dropbox.nut", "DROPBOX", STATE_DROPBOX, SKILL_DROPBOX);
IRDSQRCharacter.pushState(8, "character/atmage/swarm/swarm.nut", "SWARM", STATE_SWARM, SKILL_SWARM);
IRDSQRCharacter.pushState(8, "character/atmage/eventhorizen/eventhorizen.nut", "None", -1, SKILL_EVENTHORIZEN);
IRDSQRCharacter.pushState(8, "character/atmage/moirror/moirror.nut", "MOIRROR", STATE_MOIRROR, SKILL_MOIRROR);
IRDSQRCharacter.pushState(8, "character/atmage/blockhole/blockhole.nut", "BLACKHOLE", STATE_BLACKHOLE, SKILL_BLACKHOLE);
IRDSQRCharacter.pushState(8, "character/atmage/particlestrom/particlestrom.nut", "PARTICLESTROM", STATE_PARTICLESTROM, SKILL_PARTICLESTROM);
IRDSQRCharacter.pushState(8, "character/atmage/particleline/particleline.nut", "PARTICLELINE", STATE_PARTICLELINE, SKILL_PARTICLELINE);
IRDSQRCharacter.pushState(8, "character/atmage/particlehop/particlehop.nut", "PARTICLEHOP", STATE_PARTICLEHOP, SKILL_PARTICLEHOP);
IRDSQRCharacter.pushState(8, "character/atmage/windblades/windblades.nut", "WINDBLADES", STATE_WINDBLADES, SKILL_WINDBLADES);
IRDSQRCharacter.pushState(8, "character/atmage/dashbywind/dashbywind.nut", "DASHBYWIND", STATE_DASHBYWIND, SKILL_DASHBYWIND);
IRDSQRCharacter.pushState(8, "character/atmage/windbuff/windbuff.nut", "WINDBUFF", STATE_WINDBUFF, SKILL_WINDBUFF);
IRDSQRCharacter.pushState(8, "character/atmage/womandance/womandance.nut", "WOMANDANCE", STATE_WOMANDANCE, SKILL_WOMANDANCE);
IRDSQRCharacter.pushState(8, "character/atmage/womancontrol/womancontrol.nut", "WOMANCONTROL", STATE_WOMANCONTROL, SKILL_WOMANCONTROL);
IRDSQRCharacter.pushState(8, "character/atmage/lostcontrolwind/lostcontrolwind.nut", "LOSTCONTROLWIND", STATE_LOSTCONTROLWIND, SKILL_LOSTCONTROLWIND);
IRDSQRCharacter.pushState(8, "character/atmage/windblow/windblow.nut", "WINDBLOW", STATE_WINDBLOW, SKILL_WINDBLOW);
IRDSQRCharacter.pushState(8, "character/atmage/throwattack/throwattack.nut", "THROWATTACKSKILL", STATE_THROWATTACK, SKILL_THROWATTACK);
IRDSQRCharacter.pushState(8, "character/atmage/raginwind/raginwind.nut", "RAGINWIND", STATE_RAGINWIND, SKILL_RAGINWIND);
IRDSQRCharacter.pushState(8, "character/atmage/secondwindhit/secondwindhit.nut", "SECONDWINDHIT", STATE_SECONDWIDHIT, SKILL_SECONDWIDHIT);
IRDSQRCharacter.pushState(8, "character/atmage/stormquake/stormquake.nut", "STORMQUAKE", STATE_STORMQUAKE, SKILL_STORMQUAKE);
IRDSQRCharacter.pushState(8, "character/atmage/windsword/windsword.nut", "WINDSWORD", STATE_WINDSWORD, SKILL_WINDSWORD);
IRDSQRCharacter.pushState(8, "character/atmage/windcut/windcut.nut", "WINDCUT", STATE_WINDCUT, SKILL_WINDCUT);
IRDSQRCharacter.pushState(8, "character/atmage/throwbat/throwbat.nut", "THROWBAT", STATE_THROWBAT, SKILL_THROWBAT);
IRDSQRCharacter.pushState(8, "character/atmage/bloodwing/bloodwing.nut", "WING", STATE_WING, SKILL_WING);
IRDSQRCharacter.pushState(8, "character/atmage/attack/bloodoath.nut", "BLOODOATH", STATE_BLOODOATH, SKILL_BLOODOATH);
//IRDSQRCharacter.pushPassiveObj("character/atmage/attack/po_spearattack.nut", 24371);
IRDSQRCharacter.pushState(8, "character/atmage/bloodin/bloodin.nut", "BLOODIN", STATE_BLOODIN, SKILL_BLOODIN);
//character/atmage/null85/po_null85_loop_0.nut
IRDSQRCharacter.pushState(8, "character/atmage/newblooddoghold/newblooddoghold.nut", "NBDDH", STATE_NEWBLOODDOGHOLD, SKILL_NEWBLOODDOGHOLD);
IRDSQRCharacter.pushState(8, "character/atmage/win85/win85_2.nut", "WIN85", STATE_WIN85, SKILL_WIN85);
IRDSQRCharacter.pushState(8, "character/atmage/bloodfire/bloodfire.nut", "BLOODFIRE", STATE_BLOODFIRE, SKILL_BLOODFIRE);
IRDSQRCharacter.pushState(8, "character/atmage/jumpattackwin/jumpattackwin2.nut", "JUMPATTACKWIN", STATE_JUMPATTACKWIN, SKILL_JUMPATTACKWIN);
IRDSQRCharacter.pushState(8,"character/atmage/bloodhold/bloodhold.nut","BLOODHOLD",STATE_BLOODHOLD,SKILL_BLOODHOLD);
IRDSQRCharacter.pushState(8,"character/atmage/bloodcastle/bloodcastle.nut","BLOODCASTLE",STATE_BLOODCASTLE,SKILL_BLOODCASTLE);
IRDSQRCharacter.pushPassiveObj("character/atmage/bloodcastle/po_bloodcastle_bloodwater.nut", 24366);
IRDSQRCharacter.pushPassiveObj("character/atmage/bloodcastle/po_bloodcastle_dogs.nut", 24367);
IRDSQRCharacter.pushState(8,"character/atmage/blooddog/blooddog.nut","BLOODDOG",STATE_BLOODDOG,SKILL_BLOODDOG);
IRDSQRCharacter.pushPassiveObj("character/atmage/blooddog/po_blooddog0.nut", 24365);
IRDSQRCharacter.pushState(8, "character/atmage/blooddance/blooddance.nut", "BLOODDANCE", STATE_BLOODDANCE, SKILL_BLOODDANCE);
IRDSQRCharacter.pushPassiveObj("character/atmage/blooddance/po_blooddance.nut", 24364);
IRDSQRCharacter.pushState(8, "character/atmage/bloodscream/bloodscream.nut", "BLOODSCREAM", STATE_BLOODSCREAM, SKILL_BLOODSCREAM);
IRDSQRCharacter.pushScriptFiles("character/atmage/bloodscream/bloodscream_pooledobj.nut");
//IRDSQRCharacter.pushState(8, "character/atmage/bloodscream.nut", "BLOODSCREAM", STATE_BLOODSCREAM, SKILL_BLOODSCREAM);
IRDSQRCharacter.pushState(8, "character/common/burster/burster.nut", "Burster", STATE_BURSTER, SKILL_BURSTER);
IRDSQRCharacter.pushState(8, "character/atmage/ice85/ice85.nut", "JUDEKATHEETERNAL", STATE_JUDEKATHEETERNAL, SKILL_JUDEKATHEETERNAL);
IRDSQRCharacter.pushPassiveObj("character/atmage/ice85/po_ice85_0.nut", 24358);
IRDSQRCharacter.pushPassiveObj("character/atmage/ice85/po_ice85_1.nut", 24359);
IRDSQRCharacter.pushPassiveObj("character/atmage/ice85/po_ice85_2.nut", 24360);
IRDSQRCharacter.pushPassiveObj("character/atmage/ice85/po_ice85_3.nut", 24361);
IRDSQRCharacter.pushPassiveObj("character/atmage/ice85/po_ice85_boom.nut", 24362);
IRDSQRCharacter.pushState(8, "character/atmage/bloodcut/bloodcut.nut", "BLOODCUT", STATE_BLOODCUT, SKILL_BLOODCUT);
IRDSQRCharacter.pushPassiveObj("character/atmage/bloodcut/po_bloodcut.nut", 24357);
IRDSQRCharacter.pushState(8, "character/atmage/blood45/newblood45.nut", "BLOOD45", STATE_BLOOD45, SKILL_BLOOD45);
IRDSQRCharacter.pushState(8, "character/atmage/winbreak/winbreak.nut", "WINBREAK", STATE_WINBREAK, SKILL_WINBREAK);
IRDSQRCharacter.pushState(8, "character/atmage/area/area.nut", "GodWind", STATE_AREA, SKILL_AREA);
IRDSQRCharacter.pushPassiveObj("character/atmage/area/po_area.nut", 24363);
IRDSQRCharacter.pushState(8, "character/atmage/cancel/cancel.nut", "CANCEL", STATE_CANCEL, SKILL_CANCEL);
IRDSQRCharacter.pushState(8, "character/atmage/bloodhang/bloodhang.nut", "BLOODHANG", STATE_BLOODHANG, SKILL_BLOODHANG);
//IRDSQRCharacter.pushState(8, "character/atmage/blooddoghold/blooddoghold.nut", "BLOODDOGHOLD", STATE_BLOODDOGHOLD, SKILL_BLOODDOGHOLD);
IRDSQRCharacter.pushState(8, "character/atmage/blooddown/blooddown.nut", "BLOODDOWN", STATE_BLOODDOWN, SKILL_BLOODDOWN);
IRDSQRCharacter.pushState(8, "character/atmage/bloodsong/newbloodsong2.nut", "BLOODSONG", STATE_BLOODSONG, SKILL_BLOODSONG);
IRDSQRCharacter.pushState(8, "character/atmage/inhang/inhang.nut", "INHANG", STATE_INHANG, SKILL_INHANG);
IRDSQRCharacter.pushState(8, "character/atmage/inwind/inwind.nut", "INWIND", STATE_INWIND, SKILL_INWIND);
//IRDSQRCharacter.pushState(8, "character/atmage/wing.nut", "WING", STATE_WING, SKILL_WING);
//IRDSQRCharacter.pushState(8,"character/atmage/bloodhit/bloodhit.nut","BLOODHIT",STATE_BLOODHIT,SKILL_BLOODHIT);
IRDSQRCharacter.pushState(8,"character/atmage/marauder/marauder.nut","Marauder",STATE_WINGOUT,SKILL_WINGOUT);
IRDSQRCharacter.pushState(8,"character/atmage/bloodstay.nut","BLOODSTAY",STATE_BLOODSTAY,SKILL_BLOODSTAY);

IRDSQRCharacter.pushState(8,"character/atmage/silhouette/silhouette.nut","SILHOUETTE",STATE_SILHOUETTE,SKILL_SILHOUETTE);

IRDSQRCharacter.pushPassiveObj("character/atmage/summon_woman/po_summon_woman.nut", 24341);
//????????
IRDSQRCharacter.pushState(8, "Character/ATMage/New/ATElementalBomber/ConvergenceReact/ConvergenceReact.nut", "ConvergenceReact", STATE_CONVERGENCEREACT, SKILL_CONVERGENCEREACT);
IRDSQRCharacter.pushState(8, "Character/ATMage/New/ATElementalBomber/MicroUniverse/MicroUniverse.nut", "MicroUniverse", STATE_MICROUNIVERSE, SKILL_MICROUNIVERSE);
//?????
IRDSQRCharacter.pushState(8, "Character/ATMage/New/ATGlacialMaster/GlaciesEdge/GlaciesEdge.nut", "GlaciesEdge", STATE_GLACIESEDGE, SKILL_GLACIESEDGE);
IRDSQRCharacter.pushState(8, "Character/ATMage/New/ATGlacialMaster/Nastrond/Nastrond.nut", "Nastrond", STATE_NASTROND, SKILL_NASTROND);
//??????
IRDSQRCharacter.pushState(8, "Character/ATMage/New/atbloodmage/BloodStinger/BloodStinger.nut", "BloodStinger", STATE_BLOODSTINGER, SKILL_BLOODSTINGER);
IRDSQRCharacter.pushState(8, "Character/ATMage/New/atbloodmage/ExtremityPerish/ExtremityPerish.nut", "ExtremityPerish", STATE_EXTREMITYPERISH, SKILL_EXTREMITYPERISH);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/New/atbloodmage/BloodStinger/po_bloodstinger.nut", 24345);
//endzrr

//******************************************************************************************
// ï¿???ï¿??ï¿?? NUTï¿??ï¿?? ï¿???
//******************************************************************************************
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/WindStrike/wind_strike.nut", "WindStrike", STATE_WIND_STRIKE, SKILL_WIND_STRIKE);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/Attack/attack.nut", "Attack", STATE_ATTACK, -1);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/ATMageDashAttack/ATMageDashAttack.nut", "ATMageDashAttack", STATE_DASH_ATTACK, -1);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/JumpAttack/jump_attack.nut", "JumpAttack", STATE_JUMP_ATTACK, -1);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/CrystalAttack/CrystalAttack.nut", "CrystalAttack", STATE_CRYSTALATTACK, SKILL_CRYSTALATTACK);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/ElementalChange/elemental_change.nut", "ElementalChange", STATE_ELEMENTAL_CHANGE, SKILL_ELEMENTAL_CHANGE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/FireRoad/fire_road.nut", "FireRoad", STATE_FIRE_ROAD, SKILL_FIRE_ROAD);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/IceSword/ice_sword.nut", "IceSword", STATE_ICE_SWORD, SKILL_ICE_SWORD);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/DarkChange/dark_change.nut", "DarkChange", STATE_DARK_CHANGE, SKILL_DARK_CHANGE);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/PieceOfIce/piece_of_ice.nut", "PieceOfIce", STATE_PIECE_OF_ICE, SKILL_PIECE_OF_ICE);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/Holonglight/holong_light.nut", "HolongLight", STATE_HOLONG_LIGHT, SKILL_HOLONG_LIGHT);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/IceArea/IceArea.nut", "IceArea", STATE_ICE_AREA, SKILL_ICE_AREA);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/IceCrash/IceCrash.nut", "IceCrash", STATE_ICE_CRASH, SKILL_ICE_CRASH);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/PushOut/PushOut.nut", "PushOut", STATE_PUSH_OUT, SKILL_PUSH_OUT);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/MagicCannon/MagicCannon.nut", "MagicCannon", STATE_MAGIC_CANNON, SKILL_MAGIC_CANNON);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/MagicShield/MagicShield.nut", "MagicShield", STATE_MAGIC_SHIELD, SKILL_MAGIC_SHIELD);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/WaterCannon/WaterCannon.nut", "WaterCannon", STATE_WATER_CANNON, SKILL_WATER_CANNON);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/Resonance/Resonance.nut", "Resonance", STATE_RESONANCE, SKILL_RESONANCE);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/ElementalRain/ElementalRain.nut", "ElementalRain", STATE_ELEMENTAL_RAIN, SKILL_ELEMENTAL_RAIN);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/LightningWall/LightningWall.nut", "LightningWall", STATE_LIGHTNING_WALL, SKILL_LIGHTNING_WALL);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/atmage_throw.nut", "Throw", STATE_THROW, -1);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/atmage_buff.nut", "Buff", STATE_BUFF, -1);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/MultiShot/MultiShot.nut", "MultiShot", STATE_MULTI_SHOT, SKILL_MULTI_SHOT);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/IceOrbEx/IceOrbEx.nut", "IceOrbEx", STATE_ICE_ORB_EX, SKILL_ICE_ORB_EX);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/IceFieldEx/IceFieldEx.nut", "IceFieldEx", STATE_ICE_FIELD_EX, SKILL_ICE_FIELD_EX);


// ï¿??ï¿??ï¿??? ï¿??ï¿??ï¿?? [ï¿??ï¿??ï¿??]
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/ElementalBuster/ElementalBuster.nut",
							"ElementalBuster",
							STATE_ELEMENTAL_BUSTER,
							SKILL_ELEMENTAL_BUSTER);

// ï¿??ï¿??ï¿??? ï¿??ï¿??ï¿?? [ï¿???? ï¿??ï¿??ï¿???]
local path = "Character/ATMage/ElementalBuster/po_ATElementalBusterExpBody.nut";
IRDSQRCharacter.pushPassiveObj(path, 24290);
IRDSQRCharacter.pushPassiveObj(path, 24291);
IRDSQRCharacter.pushPassiveObj(path, 24292);
IRDSQRCharacter.pushPassiveObj(path, 24293);
IRDSQRCharacter.pushPassiveObj(path, 24294);
IRDSQRCharacter.pushPassiveObj(path, 24295);
IRDSQRCharacter.pushPassiveObj(path, 24296);
IRDSQRCharacter.pushPassiveObj(path, 24297);
IRDSQRCharacter.pushPassiveObj(path, 24298);
IRDSQRCharacter.pushPassiveObj(path, 24299);
IRDSQRCharacter.pushPassiveObj(path, 24300);
IRDSQRCharacter.pushPassiveObj(path, 24301);



// ï¿??ï¿???ï¿??ï¿???
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/Concentrate/Concentrate.nut",
							"Concentrate",
							STATE_CONCENTRATE_EX,
							SKILL_CONCENTRATE_EX);
path = "Character/ATMage/Concentrate/po_ATConcentrateExp.nut";
IRDSQRCharacter.pushPassiveObj(path, 24284);	// ï¿??ï¿???ï¿??ï¿???(?ï¿??) ï¿??ï¿?? ï¿??ï¿?? ï¿??ï¿??ï¿???
IRDSQRCharacter.pushPassiveObj(path, 24285);	// ï¿??ï¿???ï¿??ï¿???(?ï¿??) ? ï¿??ï¿?? ï¿??ï¿??ï¿???
IRDSQRCharacter.pushPassiveObj(path, 24286);	// ï¿??ï¿???ï¿??ï¿???(?ï¿??) ï¿???ï¿?? ï¿??ï¿??ï¿???





//******************************************************************************************
// ï¿???ï¿??ï¿?? ï¿???? ï¿??ï¿??ï¿??? NUTï¿??ï¿?? ï¿???
//******************************************************************************************
IRDSQRCharacter.pushPassiveObj("Character/ATMage/CrystalAttack/po_CrystalCore.nut", 24221); 	// 24221	`Character/Mage/CrystalCore.obj`	// ï¿??ï¿??ï¿?? - ?ï¿??ï¿???ï¿??ï¿??

// ï¿??ï¿??
IRDSQRCharacter.pushPassiveObj("Character/ATMage/WindStrike/po_wind_strike.nut", 24201);

// ï¿??ï¿?? ï¿??? (ï¿???)
IRDSQRCharacter.pushPassiveObj("Character/ATMage/Attack/po_magic_ball.nut", 24202);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/Attack/po_magic_ball.nut", 24203);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/Attack/po_magic_ball.nut", 24204);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/Attack/po_magic_ball.nut", 24205);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/Attack/po_magic_ball.nut", 24206);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/JumpAttack/po_magic_ball.nut", 24207);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/JumpAttack/po_magic_ball.nut", 24208);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/JumpAttack/po_magic_ball.nut", 24209);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/JumpAttack/po_magic_ball.nut", 24210);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/JumpAttack/po_magic_ball.nut", 24211);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/MultiShot/po_magic_ball.nut", 24228);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/MultiShot/po_magic_ball.nut", 24229);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/MultiShot/po_magic_ball.nut", 24230);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/MultiShot/po_magic_ball.nut", 24231);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/MultiShot/po_magic_ball.nut", 24232);


// ï¿??ï¿?? ï¿??ï¿??ï¿?? ï¿??ï¿?? ï¿???? ï¿??ï¿??ï¿???
IRDSQRCharacter.pushPassiveObj("Character/ATMage/Attack/po_magic_ball.nut", 24266);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/Attack/po_magic_ball.nut", 24267);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/Attack/po_magic_ball.nut", 24268);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/Attack/po_magic_ball.nut", 24269);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/Attack/po_magic_ball.nut", 24270);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/JumpAttack/po_magic_ball.nut", 24271);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/JumpAttack/po_magic_ball.nut", 24272);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/JumpAttack/po_magic_ball.nut", 24273);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/JumpAttack/po_magic_ball.nut", 24274);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/JumpAttack/po_magic_ball.nut", 24275);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/MultiShot/po_magic_ball.nut", 24276);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/MultiShot/po_magic_ball.nut", 24277);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/MultiShot/po_magic_ball.nut", 24278);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/MultiShot/po_magic_ball.nut", 24279);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/MultiShot/po_magic_ball.nut", 24280);


// ï¿??ï¿???Îµï¿?
IRDSQRCharacter.pushPassiveObj("Character/ATMage/FireRoad/po_fire_road.nut", 24212);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/FireRoad/po_fire_road.nut", 24213);

// ï¿??ï¿??ï¿??ï¿??
IRDSQRCharacter.pushPassiveObj("Character/ATMage/PieceOfIce/po_ATPieceOfIce.nut", 24223);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/PieceOfIce/po_ATPieceOfIceCore.nut", 24224);

// ?ï¿???
IRDSQRCharacter.pushPassiveObj("Character/ATMage/HolongLight/po_ATHolongLight.nut", 24222);

// ï¿??ï¿??? ï¿??ï¿??ï¿??
IRDSQRCharacter.pushPassiveObj("Character/ATMage/IceArea/po_IceArea.nut", 24225);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/IceArea/po_IceAreaIceRain.nut", 24226);

// ï¿??ï¿?? ?ï¿??
IRDSQRCharacter.pushPassiveObj("Character/ATMage/MagicCannon/po_MagicCannon.nut", 24227);

// ï¿??ï¿???
IRDSQRCharacter.pushPassiveObj("Character/ATMage/IceChakram/po_ATIceChakramLarge.nut", 24234);


// ?ï¿?? : ï¿??ï¿??? ï¿??ï¿??
IRDSQRCharacter.pushPassiveObj("Character/ATMage/IceOrbEx/po_ATIceOrbEx.nut", 24235); // ï¿??ï¿??ï¿?? : ?ï¿?? ï¿??ï¿??? ï¿??ï¿?? (ï¿???)
IRDSQRCharacter.pushPassiveObj("Character/ATMage/IceOrbEx/po_ATIceOrbExPrickle.nut", 24236); // ï¿??ï¿??ï¿?? : ?ï¿?? ï¿??ï¿??? ï¿??ï¿?? (ï¿??ï¿??)

// ?ï¿?? : ï¿??ï¿??? ï¿???
IRDSQRCharacter.pushPassiveObj("Character/ATMage/IceFieldEx/po_ATIceFieldEx.nut", 24237); // ï¿??ï¿??ï¿?? : ?ï¿?? ï¿??ï¿??? ï¿???

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/ChainLightning/ChainLightning.nut", "ChainLightning", STATE_CHAINLIGHTNING, SKILL_ATCHAINLIGHTNING);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/ChainLightning/po_ATChainLightning.nut", 24241);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/ChainLightning/po_ATChainLightningTarget.nut", 24242);



IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/IceRoad/IceRoad.nut", "IceRoad", STATE_ICEROAD, SKILL_ICEROAD);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/IceRoad/po_ATIceRoad.nut", 24243);


IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/FlameCircle/FlameCircle.nut", "FlameCircle", STATE_FLAMECIRCLE, SKILL_FLAMECIRCLE);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/FlameCircle/po_ATFlameCircle.nut", 24244);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/BlueDragonWill/BlueDragonWill.nut", "BlueDragonWill", STATE_BLUEDRAGONWILL, SKILL_BLUEDRAGONWILL);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/BlueDragonWill/po_ATBlueDragonWillExp.nut", 24245);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/BlueDragonWill/po_ATBlueDragonWillSub.nut", 24246);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/FrozenLand/FrozenLand.nut", "FrozenLand", STATE_FROZENLAND, SKILL_FROZENLAND);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/FrozenLand/po_ATFrozenLandMagicCircle.nut", 24247);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/FrozenLand/po_ATFrozenLandPole.nut", 24248);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/FrozenLand/po_ATFrozenLandExp.nut", 24249);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/BrokenArrow/BrokenArrow.nut", "BrokenArrow", STATE_BROKENARROW, SKILL_BROKENARROW);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/BrokenArrow/po_ATBrokenArrow.nut", 24250);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/Teleport/Teleport.nut", "Teleport", STATE_TELEPORT, SKILL_TELEPORT);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/FallenBlossoms/FallenBlossoms.nut", "FallenBlossoms", STATE_FALLENBLOSSOMS, SKILL_FALLENBLOSSOMS);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/TurnWindmill/TurnWindmill.nut", "TurnWindmill", STATE_TURNWINDMILL, SKILL_TURNWINDMILL);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/TurnWindmill/po_ATTurnWidmill.nut", 24251);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/DarknessMantle/DarknessMantle.nut", "DarknessMantle", STATE_DARKNESSMANTLE, SKILL_DARKNESSMANTLE);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/DarknessMantle/po_ATDarknessMantle.nut", 24252);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/DarknessMantle/po_ATDarknessMantleExp.nut", 24253);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/WaterCannon/po_ATWaterCannon.nut", 24217);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/ManaBurst/ManaBurst.nut", "ManaBurst", STATE_MANABURST, SKILL_MANABURST);


IRDSQRCharacter.pushPassiveObj("Character/ATMage/LightningWall/po_LightningWall.nut", 24218);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/FirePillar/FirePillar.nut", "FirePillar", STATE_FIREPILLAR, SKILL_FIREPILLAR);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/FirePillar/po_ATFirePillar.nut", 24254);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/IceMan/IceMan.nut", "IceMan", STATE_ICEMAN, SKILL_ICEMAN);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/IceMan/po_ATIceManMagicCircle.nut", 24255);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/FirePillar/po_ATFirePillar.nut", 24254);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/ElementalRain/po_ElementalRainBigBall.nut", 24219);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/ElementalRain/po_ElementalRainBigBallExp.nut", 24220);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/ElementalRain/po_ElementalRainCreator.nut", 24233);



IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/DieHard/DieHard.nut", "DieHard", STATE_DIEHARD, SKILL_DIEHARD);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/WaterCannon/po_ATWaterCannonExp.nut", 24256);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/IceChakram/IceChakram.nut", "IceChakram", STATE_ICECHAKRAM, SKILL_ICECHAKRAM);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/IceChakram/po_ATIceChakramSmallMgr.nut", 24257);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/IceChakram/po_ATIceChakramSmallIceRing.nut", 24258);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/TundraSoul/po_ATTundraSoulFrozen.nut", 24259);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_MAGE, "Character/ATMage/ElementalStrikeEx/ElementalStrikeEx.nut", "ElementalStrikeEx", STATE_ELEMENTAL_STRIKE_EX, SKILL_ELEMENTAL_STRIKE_EX);

IRDSQRCharacter.pushPassiveObj("Character/ATMage/ElementalStrikeEx/po_ATElementalStrikeEx.nut", 24310);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/ElementalStrikeEx/po_ATElementalStrikeEx.nut", 24311);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/ElementalStrikeEx/po_ATElementalStrikeEx.nut", 24312);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/ElementalStrikeEx/po_ATElementalStrikeEx.nut", 24313);
IRDSQRCharacter.pushPassiveObj("Character/ATMage/ElementalStrikeEx/po_ATElementalStrikeEx.nut", 24314);

