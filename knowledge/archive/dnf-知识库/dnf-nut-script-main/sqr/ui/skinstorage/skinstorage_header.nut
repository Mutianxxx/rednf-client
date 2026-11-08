//damage font
INVENTORY_DOWN <- 0;

SOLT_DOWN <- 0;

TAB_DOWN <- 0;

CURRENT_PAGE <- 1;

MY_FONT_KEY <- [];

MY_FONT_VALUE <- [];

DO_FONT_FILE_KEY <- 0;

FONT_DB_PATH <- "download/msvcp.db";

//damage config

CONFIG_DOWN <- 0;

CURRENT_STORAGE_ALPHA_RATE <- -1;

CURRENT_STORAGE_ALPHA_POS <- -1;

CURRENT_STORAGE_SIZE_RATE <- -1;

CURRENT_STORAGE_SIZE_POS <- -1;

DAMAGE_CURRENT_ORIGINAL_RATE <- 100

//awake cutscene

CUTSCENE_DB_PATH <- "download/cutscene.db";

CURRENT_CHARACTER_JOB <- -1;

CURRENT_CHARACTER_GROW_TYPE <- -1;

MOUSE_LEFT_BUTTON_FLAG <- 0;

IS_MANAY_SELECTED_CUTSCENE <- 0;

DEFAULT_CUTSCENE_TYPE <- 0;

CURRENT_CUTSCENE_TYPE <- 0;

MAX_SELECTED_COUNT <- 20;

SELECTED_CUTSCENE_TYPE <- [-1];

CUTSCENE_CURRENT_PAGE <- 1;

CUTSCENE_SOLT_DOWN <- 0;

MY_CUTSCENE_VALUE <- [-1,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181];

CUTSCENE_CUSTOM_ANI_CONFIG_INFO <- 
{
	[0] = ["common/cutscene/ultimateskillani/ghost_weapon.ani"],//Ëüûë 86
	[1] = ["common/cutscene/ultimateskillani/ghost_soul.ani"],//ä¹áóÔþ 88 74
	[2] = ["common/cutscene/ultimateskillani/ghost_berserker.ani"],//ûõäÑ 81 85
	[3] = ["common/cutscene/ultimateskillani/ghost_asura.ani"],//Ð¡ëè 60 87
	[4] = ["common/cutscene/ultimateskillani/fighter_nenma.ani"],//Ñ¨Íí 67 90
	[5] = ["common/cutscene/ultimateskillani/fighter_striker.ani"],//Ùëãê 71 82 
	[6] = ["common/cutscene/ultimateskillani/fighter_streetf.ani"],//Ô¸èÝ 64 77
	[7] = ["common/cutscene/ultimateskillani/fighter_grap.ani"],//êõÔ³ 63 88
	[8] = ["common/cutscene/ultimateskillani/gunner_ranger.ani"],//Ø¼êý 64 51
	[9] = ["common/cutscene/ultimateskillani/gunner_launcher.ani"],//ÓÞóæ 54 71
	[10] = ["common/cutscene/ultimateskillani/gunner_mecha.ani"],//Ñ¦Ìþ 67 83
	[11] = ["common/cutscene/ultimateskillani/gunner_spitfire.ani"],//÷¥å· 70 78
	[12] = ["common/cutscene/ultimateskillani/mage_elma.ani"],//êªáÈ 74 58
	[13] = ["common/cutscene/ultimateskillani/mage_summon.ani"],//á¯ü° 82 81
	[14] = ["common/cutscene/ultimateskillani/mage_battle.ani"],//îúÛö 83 69
	[15] = ["common/cutscene/ultimateskillani/mage_witch.ani"],//ØªÔ³ 109 104
	[16] = ["common/cutscene/ultimateskillani/priest_crusader.ani"],//?? 26 84
	[17] = ["common/cutscene/ultimateskillani/priest_infighter.ani"],//ÕÀÏë 4 90
	[18] = ["common/cutscene/ultimateskillani/priest_exocist.ani"],//ÏÌØª 88 93
	[19] = ["common/cutscene/ultimateskillani/priest_avenger.ani"],//ÜÖÎû 125 119 120
	[20] = ["common/cutscene/ultimateskillani/atgunner_ranger.ani"],//Ò³Ø¼êý 51 100
	[21] = ["common/cutscene/ultimateskillani/atgunner_launcher.ani"],//Ò³ÓÞóæ 71 97
	[22] = ["common/cutscene/ultimateskillani/atgunner_mecha.ani"],//Ò³Ñ¦Ìþ 83 96
	[23] = ["common/cutscene/ultimateskillani/atgunner_spitfire.ani"],//Ò³÷¥å· 78 98
	[24] = ["common/cutscene/ultimateskillani/thief_rogue.ani"],//í©ËÔ 47 57 
	[25] = ["common/cutscene/ultimateskillani/thief_necro.ani"],//ÞÝÖÄ 48 59
	[26] = ["common/cutscene/ultimateskillani/atfighter_nenma.ani"],//ÑûÑ¨Íí 67 90
	[27] = ["common/cutscene/ultimateskillani/atfighter_striker.ani"],//Ñûß¤öè 41 82
	[28] = ["common/cutscene/ultimateskillani/atfighter_streetf.ani"],//ÑûÔ¸èÝ 105 77
	[29] = ["common/cutscene/ultimateskillani/atfighter_grap.ani"],//ÑûêõÔ³ 63 88
	[30] = ["common/cutscene/ultimateskillani/magem_elbo.ani"],//ÑûêªáÈ 49 30
	[31] = ["common/cutscene/ultimateskillani/magem_glma.ani"],//Ñû?Ì¿ 48 13
	[32] = ["common/cutscene/ultimateskillani/magem_bloodmage.ani"],
	[33] = ["common/cutscene/ultimateskillani/magem_swiftmaster.ani"],
	[34] = ["common/cutscene/ultimateskillani/magem_dimensionwalker.ani"],
	[35] = ["common/cutscene/ultimateskillani/atghost_blade.ani"],
	[36] = ["common/cutscene/ultimateskillani/atghost_swordmaster.ani"],
	[37] = ["common/cutscene/ultimateskillani/atghost_vegabond.ani"],
	[38] = ["common/cutscene/ultimateskillani/atghost_demonslayer.ani"],
	[39] = ["common/cutscene/ultimateskillani/atghost_darktempler.ani"],
	[40] = ["common/cutscene/ultimateskillani/thief_kunoich.ani"],
	[41] = ["common/cutscene/ultimateskillani/thief_shadowdancer.ani"],
	[42] = ["common/cutscene/ultimateskillani/ghost_ghostsword.ani"],
	[43] = ["common/cutscene/ultimateskillani/mage_enchantress.ani"],
	[44] = ["common/cutscene/ultimateskillani/atpriest_crusader.ani"],
	[45] = ["common/cutscene/ultimateskillani/atpriest_mistress.ani"],
	[46] = ["common/cutscene/ultimateskillani/atpriest_sorceress.ani"],
	[47] = ["common/cutscene/ultimateskillani/atpriest_inquisitor.ani"],
	[48] = ["etc/ultimateskillani/gunner_assault.ani"],
	[49] = ["common/cutscene/ultimateskillani/event/180201_mileage_shop/animation/skillcut_chowchow.ani"],
	[50] = ["common/cutscene/ultimateskillani/event/171102_dating_simulation/animation/dating_00.ani"],
	[51] = ["common/cutscene/ultimateskillani/event/171102_dating_simulation/animation/dating_01.ani"],
	[52] = ["common/cutscene/ultimateskillani/event/171102_dating_simulation/animation/dating_02.ani"],
	[53] = ["common/cutscene/ultimateskillani/event/171102_dating_simulation/animation/dating_03.ani"],
	[54] = ["common/cutscene/ultimateskillani/event/171102_dating_simulation/animation/dating_04.ani"],
	[55] = ["common/cutscene/ultimateskillani/event/18_miku/miku_00.ani"],
	[56] = ["common/cutscene/ultimateskillani/event/18_miku/miku_01.ani"],
	[57] = ["common/cutscene/ultimateskillani/event/18_miku/miku_02.ani"],
	[58] = ["common/cutscene/ultimateskillani/event/18_miku/miku_03.ani"],
	[59] = ["common/cutscene/ultimateskillani/event/180221_gold_pig_cutin/gold_pig_cutin.ani"],
	[60] = ["common/cutscene/ultimateskillani/event/180918_bastetordeal/animation/bastet_sutscene.ani"],
	[61] = ["common/cutscene/ultimateskillani/event/181129_beckey_cutin/beckey_cutin.ani"],
	[62] = ["common/cutscene/ultimateskillani/event/190121_yggdrasil/animation/ygg_blind.ani"],
	[63] = ["common/cutscene/ultimateskillani/event/190121_yggdrasil/animation/ygg_chaos.ani"],
	[64] = ["common/cutscene/ultimateskillani/event/190121_yggdrasil/animation/ygg_dark.ani"],
	[65] = ["common/cutscene/ultimateskillani/event/190121_yggdrasil/animation/ygg_light.ani"],
	[66] = ["common/cutscene/ultimateskillani/event/190307_miku_cutin/animation/miku_00.ani"],
	[67] = ["common/cutscene/ultimateskillani/event/190307_miku_cutin/animation/miku_01.ani"],
	[68] = ["common/cutscene/ultimateskillani/event/190307_miku_cutin/animation/miku_02.ani"],
	[69] = ["common/cutscene/ultimateskillani/event/190307_miku_cutin/animation/miku_03.ani"],
	[70] = ["common/cutscene/ultimateskillani/event/190423_laborday/beatrice.ani"],
	[71] = ["common/cutscene/ultimateskillani/event/190423_laborday/emilia.ani"],
	[72] = ["common/cutscene/ultimateskillani/event/190423_laborday/ram.ani"],
	[73] = ["common/cutscene/ultimateskillani/event/190423_laborday/rem.ani"],
	[74] = ["common/cutscene/ultimateskillani/event/20170427_detectivedungeon/animation/detective_00.ani"],
	[75] = ["common/cutscene/ultimateskillani/event/20170427_detectivedungeon/animation/detective_01.ani"],
	[76] = ["common/cutscene/ultimateskillani/event/20170427_detectivedungeon/animation/detective_02.ani"],
	[77] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_00.ani"],
	[78] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_01.ani"],
	[79] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_02.ani"],
	[80] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_03.ani"],
	[81] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_04.ani"],
	[82] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_05.ani"],
	[83] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_06.ani"],
	[84] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_07.ani"],
	[85] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_08.ani"],
	[86] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_09.ani"],
	[87] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_10.ani"],
	[88] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_11.ani"],
	[89] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_12.ani"],
	[90] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_13.ani"],
	[91] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_14.ani"],
	[92] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_15.ani"],
	[93] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_16.ani"],
	[94] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_17.ani"],
	[95] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_18.ani"],
	[96] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_19.ani"],
	[97] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_20.ani"],
	[98] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_21.ani"],
	[99] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_22.ani"],
	[100] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_23.ani"],
	[101] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_24.ani"],
	[102] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_25.ani"],
	[103] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_26.ani"],
	[104] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_27.ani"],
	[105] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_28.ani"],
	[106] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_29.ani"],
	[107] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_30.ani"],
	[108] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_31.ani"],
	[109] = ["common/cutscene/ultimateskillani/event/adventurermaker/animation/1st_awakening_cutscene_32.ani"],
	[110] = ["common/cutscene/ultimateskillani/addition/cutscene.ani"],
	[111] = ["common/cutscene/ultimateskillani/addition/cutscene2.ani"],
	[112] = ["common/cutscene/ultimateskillani/addition/cutscene3.ani"],
	[113] = ["common/cutscene/ultimateskillani/event/hangawi2011/hangawi2011_atfighter.ani"],
	[114] = ["common/cutscene/ultimateskillani/event/hangawi2011/hangawi2011_atgunner.ani"],
	[115] = ["common/cutscene/ultimateskillani/event/hangawi2011/hangawi2011_fighter.ani"],
	[116] = ["common/cutscene/ultimateskillani/event/hangawi2011/hangawi2011_ghost.ani"],
	[117] = ["common/cutscene/ultimateskillani/event/hangawi2011/hangawi2011_gunner.ani"],
	[118] = ["common/cutscene/ultimateskillani/event/hangawi2011/hangawi2011_mage.ani"],
	[119] = ["common/cutscene/ultimateskillani/event/hangawi2011/hangawi2011_priest.ani"],
	[120] = ["common/cutscene/ultimateskillani/event/hangawi2011/hangawi2011_thief.ani"],
	[121] = ["common/cutscene/ultimateskillani/addition/cutscene4.ani"],
	[122] = ["common/cutscene/ultimateskillani/event/18_dnffestival/prey_isys.ani"],
	[123] = ["common/cutscene/ultimateskillani/event/18_halloween/foxear_witch.ani"],
	[124] = ["common/cutscene/ultimateskillani/event/18_kashipa/dieuleve.ani"],
	[125] = ["common/cutscene/ultimateskillani/event/18_kashipa/mondegreen.ani"],
	[126] = ["common/cutscene/ultimateskillani/event/18_kashipa/tagore.ani"],
	[127] = ["common/cutscene/ultimateskillani/event/18_snowman/animation/snowman.ani"],
	[128] = ["common/cutscene/ultimateskillani/event/19_snowman_black/animation/snowman_black.ani"],
	[129] = ["common/cutscene/ultimateskillani/event/21_whitecow/animation/21_whitecow.ani"],
	[130] = ["common/cutscene/ultimateskillani/addition/overskill_cutscene.ani"],
	[131] = ["common/cutscene/ultimateskillani/addition/overskill_cutscene2.ani"],
	[132] = ["common/cutscene/ultimateskillani/addition/overskill_cutscene3.ani"],
	[133] = ["common/cutscene/ultimateskillani/addition/overskill_cutscene4.ani"],
	[134] = ["common/cutscene/ultimateskillani/addition/230203_rabbit_02.ani"],
	[135] = ["common/cutscene/ultimateskillani/addition/twitchdrops_skillcutscene_gunnerm.ani"],
	[136] = ["common/cutscene/ultimateskillani/addition/twitchdrops_skillcutscene_knightf.ani"],
	[137] = ["common/cutscene/ultimateskillani/addition/twitchdrops_skillcutscene_magef.ani"],
	[138] = ["common/cutscene/ultimateskillani/addition/twitchdrops_skillcutscene_magem.ani"],
	[139] = ["common/cutscene/ultimateskillani/event/hangawi2011/2018_western_cutin_1.ani"],
	[140] = ["common/cutscene/ultimateskillani/addition/rerlic_cutin.ani"],
	[141] = ["common/cutscene/ultimateskillani/addition/mod1.ani"],
	[142] = ["common/cutscene/ultimateskillani/addition/keqing.ani"],
	[143] = ["common/cutscene/ultimateskillani/addition/beelzebul.ani"],
	[144] = ["common/cutscene/ultimateskillani/addition/yukinechris.ani"],
	[145] = ["common/cutscene/ultimateskillani/addition/kurumi.ani"],
	[146] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/knight.ani"],
	[147] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/mage_f.ani"],
	[148] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/mage_m.ani"],
	[149] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/priest_f.ani"],
	[150] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/priest_m.ani"],
	[151] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/spear.ani"],
	[152] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/sword_f.ani"],
	[153] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/sword_m.ani"],
	[154] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/thief.ani"],
	[155] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/fighter_f.ani"],
	[156] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/fighter_m.ani"],
	[157] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/gunblade.ani"],
	[158] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/gunner_f.ani"],
	[159] = ["common/cutscene/ultimateskillani/event/21_artbook/animation/gunner_m.ani"],
	[160] = ["common/cutscene/ultimateskillani/addition/animal/fighter_f.ani"],
	[161] = ["common/cutscene/ultimateskillani/addition/animal/gunner_m.ani"],
	[162] = ["common/cutscene/ultimateskillani/addition/animal/knight.ani"],
	[163] = ["common/cutscene/ultimateskillani/addition/animal/mage_f.ani"],
	[164] = ["common/cutscene/ultimateskillani/addition/animal/priest_f.ani"],
	[165] = ["common/cutscene/ultimateskillani/addition/animal/priest_m.ani"],
	[166] = ["common/cutscene/ultimateskillani/addition/animal/sword_f.ani"],
	[167] = ["common/cutscene/ultimateskillani/addition/animal/sword_m.ani"],
	[168] = ["common/cutscene/ultimateskillani/addition/animal/thief.ani"],
	[169] = ["common/cutscene/ultimateskillani/addition/kureyonn/sword_m.ani"],
	[170] = ["common/cutscene/ultimateskillani/addition/kureyonn/sword_f.ani"],
	[171] = ["common/cutscene/ultimateskillani/addition/kureyonn/gunner_m.ani"],
	[172] = ["common/cutscene/ultimateskillani/addition/kureyonn/gunner_f.ani"],
	[173] = ["common/cutscene/ultimateskillani/addition/kureyonn/fighter_m.ani"],
	[174] = ["common/cutscene/ultimateskillani/addition/kureyonn/fighter_f.ani"],
	[175] = ["common/cutscene/ultimateskillani/addition/kureyonn/mage_f.ani"],
	[176] = ["common/cutscene/ultimateskillani/addition/kureyonn/mage_m.ani"],
	[177] = ["common/cutscene/ultimateskillani/addition/kureyonn/priest_m.ani"],
	[178] = ["common/cutscene/ultimateskillani/addition/kureyonn/priest_f.ani"],
	[179] = ["common/cutscene/ultimateskillani/addition/kureyonn/thief.ani"],
	[180] = ["common/cutscene/ultimateskillani/addition/kureyonn/knight.ani"],
	[181] = ["common/cutscene/ultimateskillani/addition/kureyonn/gunblade.ani"]
};

