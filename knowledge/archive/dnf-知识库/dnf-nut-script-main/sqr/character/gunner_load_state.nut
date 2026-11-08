

IRDSQRCharacter.pushScriptFiles("character/gunner/gunner_header.nut");  

IRDSQRCharacter.pushPassiveObj("character/gunner/po_mytestgunner.nut", 24368);
IRDSQRCharacter.pushPassiveObj("character/gunner/hs_1/po_gunner_hs1.nut", 24238);
IRDSQRCharacter.pushPassiveObj("js60_qq506807329/share_obj/share_po_gunner_24371.nut", 24371);
sq_RunScript("js60_qq506807329/share_obj/gunner/setcustomdata.nut");
sq_RunScript("js60_qq506807329/share_obj/gunner/setstate.nut");
sq_RunScript("js60_qq506807329/share_obj/gunner/procappend.nut");
sq_RunScript("js60_qq506807329/share_obj/gunner/onendcurrentani.nut");
sq_RunScript("js60_qq506807329/share_obj/gunner/else.nut");

 PASSIVEOBJ_GUNNER_ASSAULT_ID <- 24380 //ùêÑÑOBJøºûÜ
IRDSQRCharacter.pushPassiveObj("passiveobject/new/gunner/gunner_po_assault.nut", PASSIVEOBJ_GUNNER_ASSAULT_ID);
sq_RunScript("passiveobject/new/gunner/else.nut");
sq_RunScript("passiveobject/new/gunner/onendcurrentani.nut");
sq_RunScript("passiveobject/new/gunner/procappend.nut");
sq_RunScript("passiveobject/new/gunner/setcustomdata.nut");
sq_RunScript("passiveobject/new/gunner/setstate.nut");

IRDSQRCharacter.pushScriptFiles("character/gunner/gunner_common.nut");  
IRDSQRCharacter.pushScriptFiles("Character/gunner/passive_skill_gunner.nut"); 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/gunner_buff.nut", "gunner_buff", 17, -1);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/windmill/stylishbackstepheadshot.nut", "step_headshot", 169, -1);//ý¨Ô¯øïÔé
 
 
 IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/cancel/gunnercancel.nut", "gunnercancel", STATE_ATTACK, -1);
 IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/jump/gunner_jump.nut", "gunner_jump", STATE_JUMP, -1);
 IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/jumpattack/gunner_jumpattack.nut", "gunner_jumpattack", STATE_JUMP_ATTACK, -1);
 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/msc7/msc7.nut", "gunner_msc7", 232, 232);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/seismicwave/seismicwave.nut", "gunner_seismicwave", 233, 233);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/plasmaboost/plasmaboost.nut", "gunner_plasmaboost", 234, 234);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/bursterbeamnew/bursterbeamnew.nut", "gunner_bursterbeamnew", 235, 235);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/deadlyapproach/deadlyapproach.nut", "gunner_deadlyapproach", 236, 236);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/wipeout/wipeout.nut", "gunner_wipeout", 237, 237);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/suppressingfire/suppressingfire.nut", "gunner_suppressingfire", 238, 238);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/fastdraw/fastdraw.nut", "gunner_fastdraw", 239, 239);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER ,  "character/gunner/seventhflow/seventhflow.nut" ,  "seventhflow" ,  STATE_SEVENTHFLOW ,  SKILL_SEVENTHFLOW);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/pistolcarbine/pistolcarbine.nut", "gunner_pistolcarbine", 241, 241);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/gravitygrenade/gravitygrenade.nut", "gunner_gravitygrenade", 242, 242);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/dangerclose/dangerclose.nut", "gunner_dangerclose", 243, 243);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/g38arg/g38arg.nut", "gunner_g38arg", 244, 244);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/supernova/supernova.nut", "gunner_supernova", 245, 245);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/dimensionrunner/dimensionrunner.nut", "gunner_dimensionrunner", 246, 246);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/hellmarch/hellmarch.nut", "gunner_hellmarch", 247, 247);


IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/windmill/windmill.nut", "gunner_windmill", 19, -1);
 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/punisher/punisher1.nut", "gunner_punisher1", 21, -1); 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/punisher/punisher2.nut", "gunner_punisher2", 22, -1); 
 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/aerialknee/aerialknee.nut", "gunner_aerialknee", 20, -1);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/heavyweaponalteration/heavyweaponalteration.nut", "LaserRifle", 26, 39);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/overcharge/overcharge.nut", "overcharge", 252, 252);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/dangerclose_old/dangerclose_old.nut", "gunner_dangerclose_old", STATE_DANGERCLOSE, SKILL_DANGERCLOSE);

IRDSQRCharacter.pushState(2, "character/gunner/hs_1/changqing_751675335_hs1.nut", "RobotRX78", 130, 27);
IRDSQRCharacter.pushState(2, "character/gunner/hs_1/changqing_751675335_hs1.nut", "RobotEz8", 129, 28);
IRDSQRCharacter.pushState(2, "character/gunner/hs_1/changqing_751675335_hs1.nut", "RobotExs", 128, 29);
IRDSQRCharacter.pushState(2, "character/gunner/hs_1/changqing_751675335_hs1.nut", "RobotTempester", 163, 63);
//IRDSQRCharacter.pushState(2, "character/gunner/hs_1/changqing_751675335_hs1.nut", "SparrowFactory", 183, 83);
IRDSQRCharacter.pushState(2, "character/gunner/hs_1/changqing_751675335_hs1.nut", "RobotEz8Ex", 29, 105);
IRDSQRCharacter.pushState(2, "character/gunner/hs_1/changqing_751675335_hs1.nut", "RobotExsEx", 106, 106);
IRDSQRCharacter.pushState(2, "character/gunner/alphasupport/alphasupport.nut", "AlphaSupporta", 26, -1);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "character/gunner/TripleTap/TripleTap.nut", "TripleTap", STATE_TRIPLETAB, SKILL_TRIPLETAB);

//õ±Þº : äâð²
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/suppress/suppress.nut", "Suppress", STATE_SUPPRESS, SKILL_SUPPRESS);
//?ñÞÞÒÌª
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/aimshoot/aimshoot.nut", "AimShoot", STATE_AIMSHOOT, SKILL_AIMSHOOT);
//óæöõ?Ìª
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/bashstock/bashstock.nut", "BashStock", STATE_BASHSTOCK, SKILL_BASHSTOCK);
//óæöõ?Ìª
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/BurstBomb/BurstBomb.nut", "BurstBomb", STATE_BURSTBOMB, SKILL_BURSTBOMB);
//õ±Þº : ñìâêÜÁêÛ
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/BodyBunker/BodyBunker.nut", "BodyBunker", STATE_BODYBUNKER, SKILL_BODYBUNKER);
//í¸Õôâ¢Öô
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/NeodymiumFusee/NeodymiumFusee.nut", "NeodymiumFusee", STATE_NEODYMIUMFUSEE, SKILL_NEODYMIUMFUSEE);
//í¸Õôâ¢Öô
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/TripleGunshot/TripleGunshot.nut", "TripleGunshot", STATE_TRIPLEGUNSHOT, SKILL_TRIPLEGUNSHOT);
//øïÖ®Þ«?
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/McPice/McPice.nut", "McPice", STATE_MCPICE, SKILL_MCPICE);
//õ±Þº : Ñ¦ÌþõøÓÕ
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/BreachingDown/BreachingDown.nut", "BreachingDown", STATE_BREACHINGDOWN, SKILL_BREACHINGDOWN);
//îúÕÔÎÞíÈ
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/ScorchTactics/ScorchTactics.nut", "ScorchTactics", STATE_SCORCHTACTICS, SKILL_SCORCHTACTICS);
//ÖôÓ¹á·ÞÒ
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/DirectFeedback/DirectFeedback.nut", "DirectFeedback", STATE_DIRECTFEEDBACK, SKILL_DIRECTFEEDBACK);
//õ±Þº : ï³×µàì?
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/DynamiteKick/DynamiteKick.nut", "DynamiteKick", STATE_DYNAMITEKICK, SKILL_DYNAMITEKICK);
//ÜÂ×¤ÎÞÌª
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/FortressBlitz/FortressBlitz.nut", "FortressBlitz", STATE_FORTRESSBLITZ, SKILL_FORTRESSBLITZ);
//æúãêÍôàò?
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/RaytheonCIRT/RaytheonCIRT.nut", "RaytheonCIRT", STATE_RAYTHEONCIRT, SKILL_RAYTHEONCIRT);
//õ±Þº : îïÖÅæ´ÍôÌª
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/DeathField/DeathField.nut", "DeathField", STATE_DEATHFIELD, SKILL_DEATHFIELD);
//õ±Þº : ì¥Ð¥××ÞÙ-MR
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/EqualisMR/EqualisMR.nut", "EqualisMR", STATE_EQUALISMR, SKILL_EQUALISMR);
//AT-SO ÜÆú¼íº
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/AT_SOWalker/AT_SOWalker.nut", "AT_SOWalker", STATE_AT_SOWALKER, SKILL_AT_SOWALKER);
//ùêÑÑËÇíû
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/AssaultAttack/AssaultAttack.nut", "AssaultAttack", STATE_ASSAULTATTACK, -1);
//ãýíôÏÌÔÑ
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_GUNNER, "Character/gunner/assault/Activation/Activation.nut", "Activation", STATE_ACTIVATION, SKILL_ACTIVATION);
