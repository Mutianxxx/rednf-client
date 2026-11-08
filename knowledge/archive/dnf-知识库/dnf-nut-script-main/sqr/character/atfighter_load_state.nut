IRDSQRCharacter.pushPassiveObj("js60_qq506807329/share_obj/share_po_atfighter_24375.nut", 24375);
sq_RunScript("js60_qq506807329/share_obj/atfighter/setcustomdata.nut");
sq_RunScript("js60_qq506807329/share_obj/atfighter/setstate.nut");
sq_RunScript("js60_qq506807329/share_obj/atfighter/procappend.nut");
sq_RunScript("js60_qq506807329/share_obj/atfighter/onendcurrentani.nut");
sq_RunScript("js60_qq506807329/share_obj/atfighter/else.nut");

IRDSQRCharacter.pushScriptFiles("character/atfighter/atfighter_header.nut");
IRDSQRCharacter.pushScriptFiles("character/atfighter/atfighter_common.nut");
IRDSQRCharacter.pushScriptFiles("character/atfighter/passive_skill_atfighter.nut");

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/spiralemperorslap/spiralemperorslap.nut", "atfighter_spiralemperorslap", 220, 220);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/moonlighttheearth/moonlighttheearth.nut", "atfighter_moonlighttheearth", 221, 221);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/glancethehost/glancethehost.nut", "atfighter_glancethehost", 222, 222);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/dropfire/dropfire.nut", "atfighter_dropfire", 223, 223);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/atomiccannon/atomiccannon.nut", "atfighter_atomiccannon", 224, 224);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/emperorcombination/emperorcombination.nut", "atfighter_emperorcombination", 225, 225);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/chaindrive/chaindrive.nut", "atfighter_chaindrive", 226, 226);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/ruinrain/ruinrain.nut", "atfighter_ruinrain", 227, 227);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/fireworks/fireworks.nut", "atfighter_fireworks", 228, 228);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/cyclonecrash/cyclonecrash.nut", "atfighter_cyclonecrash", 229, 229);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/chainbrake/chainbrake.nut", "atfighter_chainbrake", 230, 230);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/finalextremestrike/finalextremestrike.nut", "atfighter_finalextremestrike", 231, 231);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "Character/atfighter/atfighter_buff.nut", "atfighter_buff", 17, -1);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "Character/atfighter/flamelegs/flamelegs.nut", "atfighter_flamelegs", 62, -1);

//CNAvenger.pushPassiveObj("character/atfighter/passiveobject/po_atillusionbomb.nut", 24150);



IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/fastdash/fastdash.nut", "", 59, 108);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/fastdash/fastdash.nut", "FastDash", STATE_DASH_BEHIND, 108);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/lieyanfenbu/lieyanfenbuzhuijia.nut", "LieYanFenBuZhuiJia", STATE_LIE_YAN_FEN_BU_ZHUI_JIA, -1);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/randomkick/randomkick.nut", "RandomKick", 49, 82);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/randomkick/whirlwindkick.nut", "WhirlWindKick", 6, 58);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/junkspin/junkspin.nut", "junkspin", 42, 77);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "Character/ATFighter/ATFighter_Throw.nut", "ATFighter_Throw", 13, -1);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "Character/atfighter/ATFighter_Throw.nut", "LightningDragon", 56, 90);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "Character/atfighter/ATFighter_Throw.nut", "SpiralColumnEx", 70, 120);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "Character/atfighter/ATFighter_Throw.nut", "NenFlower", 45, 67);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "Character/atfighter/ATFighter_Throw.nut", "NenSpearEx", 66, 117);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "character/atfighter/nenmaster2nd/spiralgaleforce.nut", "spiralgaleforce", STATE_SPIRALGALEFORCE, SKILL_SPIRALGALEFORCE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "Character/atfighter/thundercannon/thundercannon.nut", "thundercannon", STATE_THUNDERCANNON, SKILL_THUNDERCANNON);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "Character/atfighter/thundersuplex/thundersuplex.nut", "ThunderSuplex", STATE_THUNDERSUPLEX, SKILL_THUNDERSUPLEX);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_FIGHTER, "Character/atfighter/thundertiger/thundertiger.nut", "thundertiger", STATE_THUNDERTIGER, SKILL_THUNDERTIGER);
