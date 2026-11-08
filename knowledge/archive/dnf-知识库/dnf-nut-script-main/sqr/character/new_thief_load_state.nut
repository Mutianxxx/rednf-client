
IRDSQRCharacter.pushPassiveObj("js60_qq506807329/share_obj/share_po_new_thief_24378.nut", 24378);
IRDSQRCharacter.pushPassiveObj("character/thief/po_thief_shared.nut", 24356);
IRDSQRCharacter.pushPassiveObj("Character/Thief/Hurricane/po_HurricaneKnife.nut", 24391);
IRDSQRCharacter.pushPassiveObj("character/thief/4_shadow/shaowarea/po_shaowarea.nut", 24239);

sq_RunScript("js60_qq506807329/share_obj/new_thief/setcustomdata.nut");
sq_RunScript("js60_qq506807329/share_obj/new_thief/setstate.nut");
sq_RunScript("js60_qq506807329/share_obj/new_thief/procappend.nut");
sq_RunScript("js60_qq506807329/share_obj/new_thief/onendcurrentani.nut");
sq_RunScript("js60_qq506807329/share_obj/new_thief/else.nut");

IRDSQRCharacter.pushScriptFiles("character/new_thief/new_thief_header.nut");  
IRDSQRCharacter.pushScriptFiles("character/new_thief/new_thief_common.nut");  
IRDSQRCharacter.pushScriptFiles("character/new_thief/passive_skill_thief.nut");  

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/new_thief/exoticrampant/exoticrampant.nut", "thief_exoticrampant", 220, 220);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/new_thief/distribution/distribution.nut", "thief_distribution", 221, 221);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/new_thief/novaremnant/novaremnant.nut", "thief_novaremnant", 222, 222);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/new_thief/executionerslash/executionerslash.nut", "thief_executionerslash", 223, 223);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/new_thief/nicolasblackarachnia/nicolasblackarachnia.nut", "thief_nicolasblackarachnia", 224, 224);

 
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/new_thief/ballacreadvent/ballacreadvent.nut", "thief_ballacreadvent", 225, 225);

IRDSQRCharacter.pushState(6, "Character/new_thief/WuQi/WuQi.nut", "WuQi", STATE_WUQI, SKILL_WUQI);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/new_thief/livingdead/livingdead.nut", "thief_livingdead", STATE_THIEF_LIVINGDEAD, SKILL_THIEF_LIVINGDEAD);


IRDSQRCharacter.pushState(6, "character/thief/rouhua/ShiningCut.nut", "ShiningCut", 22, 3);//??????
IRDSQRCharacter.pushState(6, "character/thief/rouhua/DoublePierce.nut", "DoublePierce", 52, 27);//?????
IRDSQRCharacter.pushState(6, "character/thief/rouhua/VerticalSpiral.nut", "VerticalSpiral", 56, 33);//?????
IRDSQRCharacter.pushState(6, "character/thief/rouhua/SonicAssault.nut", "SonicAssault", 57, 34);//???????
IRDSQRCharacter.pushState(6, "character/thief/rouhua/ChainSaw.nut", "ChainSaw", 34, 41);//????
IRDSQRCharacter.pushState(6, "character/thief/rouhua/LightningArrow.nut", "LightningArrow", 37, 45);//????
IRDSQRCharacter.pushState(6, "character/thief/rouhua/ExcelStrike.nut", "ExcelStrike", 38, 47);//??????
IRDSQRCharacter.pushState(6, "character/thief/rouhua/SilverStream.nut", "SilverStream", 45, 57);//??????


//IRDSQRCharacter.pushState(6, "character/thief/rouhua/Hurricane.nut", "Hurricane", 54, 31);
//IRDSQRCharacter.pushState(6, "character/thief/rouhua/VerticalSpiralEx.nut", "VerticalSpiralEx", 65, 75);
//IRDSQRCharacter.pushState(6, "character/thief/rouhua/ChainSawEx.nut", "ChainSawEx", 66, 76);

IRDSQRCharacter.pushScriptFiles("character/thief/flametogaws.nut");

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "Character/Thief/Hurricane/Hurricane.nut", "Hurricane", 54, 31);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/firehide/firehide.nut", "firehide", STATE_FIREHIDE, SKILL_FIREHIDE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/flameball/flameball.nut", "flameball", STATE_FLAMEBALL, SKILL_FLAMEBALL);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/ilusionshuriken/ilusionshuriken.nut", "ilusionshuriken", STATE_ILUSIONSHURIKEN, SKILL_ILUSIONSHURIKEN);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/woodmove/woodmove.nut", "woodmove", STATE_WOODMOVE, SKILL_WOODMOVE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/flametornado/flametornado.nut", "flametornado", STATE_FLAMETORNADO, SKILL_FLAMETORNADO);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/bigkunai/bigkunai.nut", "bigkunai", STATE_BIGKUNAI, SKILL_BIGKUNAI);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/migawari/migawari.nut", "migawari", STATE_MIGAWARI, SKILL_MIGAWARI);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/skyroads/skyroads.nut", "skyroads", STATE_SKYROADS, SKILL_SKYROADS);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/deitiesrebirth/deitiesrebirth.nut", "deitiesrebirth", STATE_DEITIESREBIRTH, SKILL_DEITIESREBIRTH);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/gasolinefire/gasolinefire.nut", "gasolinefire", STATE_GASOLINEFIRE, SKILL_GASOLINEFIRE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/flameflower/flameflower.nut", "flameflower", STATE_FLAMEFLOWER, SKILL_FLAMEFLOWER);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/doomfield/doomfield.nut", "doomfield", STATE_DOOMFIELD, SKILL_DOOMFIELD);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/flyingswallow/flyingswallow.nut", "flyingswallow", STATE_FLYINGSWALLOW, SKILL_FLYINGSWALLOW);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/yamataorochi/yamataorochi.nut", "yamataorochi", STATE_YAMATAOROCHI, SKILL_YAMATAOROCHI);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/fuumashuriken/fuumashuriken.nut", "fuumashuriken", STATE_FUUMASHURIKEN, SKILL_FUUMASHURIKEN);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/amateras/amateras.nut", "amateras", STATE_AMATERAS, SKILL_AMATERAS);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/swordofkusanagi/swordofkusanagi.nut", "swordofkusanagi", STATE_SWORDOFKUSANAGI, SKILL_SWORDOFKUSANAGI);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/jumpattack/jumpattack.nut", "jumpattack_thief", 7, -1);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_THIEF, "character/thief/3_kunoich/dashattack/dashattack.nut", "dashattack_thief", 15, -1);


IRDSQRCharacter.pushState(6, "character/thief/4_shadow/cutneck/cutneck.nut", "CUTNECK", STATE_CUTNECK, SKILL_CUTNECK );

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/cardioheart/cradioheart.nut", "CARDIOHEART", STATE_CARDIOHEART, SKILL_CARDIOHEART);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/gotohell/gotohell.nut", "GOTOHELL", STATE_GOTOHELL, SKILL_GOTOHELL);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/holdup/holdup.nut", "HOLDUP", STATE_HOLDUP, SKILL_HOLDUP);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/speedslade/speedslade.nut", "SPEEDSLADE", STATE_SPEEDSLADE, SKILL_SPEEDSLADE);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/shaowslash/shaowslash.nut", "SHAOWSLASH", STATE_SHAOWSLASH, SKILL_SHAOWSLASH);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/shaowstay/shaowstay.nut", "SHAOWSTAY", STATE_SHAOWSTAY, SKILL_SHAOWSTAY);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/shaowarea/shaowarea.nut", "SHAOWAREA", STATE_SHAOWAREA, SKILL_SHAOWAREA);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/assassinofcreed/assassinofcreed.nut", "ASSASSINOFCREED", STATE_ASSASSINOFCREED, SKILL_ASSASSINOFCREED);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/bloodshaowslash/bloodshaowslash.nut", "BLOODSHAOWSLASH", STATE_BLOODSHAOWSLASH, SKILL_BLOODSHAOWSLASH);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/assassination/assassination.nut", "ASSASSINATION", STATE_ASSASSINATION, SKILL_ASSASSINATION);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/bloodandshaow/bloodandshaow.nut", "BLOODANDSHAOW", STATE_BLOODANDSHAOW, SKILL_BLOODANDSHAOW);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/sshadow_wipe/shadow_wipe.nut", "SHADOW_WIPE", STATE_SHADOW_WIPE, SKILL_SHADOW_WIPE);

//IRDSQRCharacter.pushState(6, "character/thief/4_shadow/attack/attack.nut", "ThiefAttack", 8, -1);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/eraser/eraser.nut", "Eraser",27 , -1);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/eraser/eraser.nut", "ShaowCut",26 , -1);

IRDSQRCharacter.pushState(6, "character/thief/attack.nut", "attack_thief", 8, -1);
IRDSQRCharacter.pushState(6, "character/thief/attack.nut", "chakraweapon_backstep", STATE_CHAKRAWEPAON_STEP, -1);

IRDSQRCharacter.pushState(6, "character/thief/4_shadow/bloodshadowdance/bloodshadowdance.nut", "bloodshaowdancce", STATE_BLOOD_SHADOW_DANCE , SKILL_BLOOD_SHADOW_DANCE );
IRDSQRCharacter.pushState(6, "character/thief/4_shadow/shadowsoul/shadowsoul.nut", "shaowsoul", STATE_SHADOW_SOUL , SKILL_SHADOW_SOUL );
IRDSQRCharacter.pushState(6, "character/thief/4_shadow/breakheart/breakheart.nut", "breakheart", STATE_BREAK_HEART , SKILL_BREAK_HEART );
IRDSQRCharacter.pushState(6, "character/thief/4_shadow/severshadowslash/severshadowslash.nut", "severshaowslash", STATE_SEVER_SHADOW_SLASH , SKILL_SEVER_SHADOW_SLASH );

