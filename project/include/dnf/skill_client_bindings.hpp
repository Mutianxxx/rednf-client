// 技能 -> 身体动作链 / 特效链的静态绑定表。
//
// 每条绑定：skill_id -> 按释放顺序排列的身体 .ani 链，以及
//             由技能脚本登记的特效 .ani 链。
// 以 CHR 名（character/<class>/<class>.chr）和 PVF 技能 id 为键。
#pragma once

#include <cstddef>

namespace dnf::client_bindings {

struct ClientSkillBinding {
    int skillId;
    const char *const *motions; // PVF paths, release order, deduped
    size_t motionCount;
    const char *const *effects;
    size_t effectCount;
    const char *evidence;
};

struct ClientJobBindings {
    const char *job; // CHR file stem, e.g. "swordman", "atfighter"
    const ClientSkillBinding *skills;
    size_t count;
};

static const char *const k_motions_swordman_1[] = {
    "character/swordman/animation/waveeyeattack3.ani",
    "character/swordman/animation/guard.ani",
    "character/swordman/animation/wave.ani",
};
static const ClientSkillBinding k_skill_swordman_1 = {
    1, k_motions_swordman_1, 3, nullptr, 0, 
    "1031 client state table: states 8,17,19,24; basis eligibility pair"};
static const char *const k_motions_swordman_2[] = {
    "character/swordman/animation/guard.ani",
    "character/swordman/animation/reflectguard.ani",
};
static const char *const k_effects_swordman_2[] = {
    "character/swordman/effect/animation/reflectguard/charge.ani",
    "character/swordman/effect/animation/reflectguard/slash.ani",
};
static const ClientSkillBinding k_skill_swordman_2 = {
    2, k_motions_swordman_2, 2, k_effects_swordman_2, 2, 
    "1031 client state table: states 19,38; basis eligibility pair"};
static const char *const k_motions_swordman_3[] = {
    "character/swordman/animation/guard.ani",
    "character/swordman/animation/hitback.ani",
};
static const ClientSkillBinding k_skill_swordman_3 = {
    3, k_motions_swordman_3, 2, nullptr, 0, 
    "1031 client state table: states 17,19,59; basis eligibility pair"};
static const char *const k_motions_swordman_5[] = {
    "character/swordman/animation/hardattack.ani",
    "character/swordman/animation/hardattackchargeafter.ani",
};
static const char *const k_effects_swordman_5[] = {
    "character/swordman/effect/animation/hardattack1.ani",
    "character/swordman/effect/animation/hardattack2.ani",
};
static const ClientSkillBinding k_skill_swordman_5 = {
    5, k_motions_swordman_5, 2, k_effects_swordman_5, 2, 
    "1031 client state table: states 20; basis motion name"};
static const char *const k_motions_swordman_6[] = {
    "character/swordman/animation/hardattack.ani",
    "character/swordman/animation/hardattackchargeafter.ani",
};
static const ClientSkillBinding k_skill_swordman_6 = {
    6, k_motions_swordman_6, 2, nullptr, 0, 
    "1031 client state table: states 20; basis motion name"};
static const char *const k_motions_swordman_7[] = {
    "character/swordman/animation/hitback.ani",
};
static const ClientSkillBinding k_skill_swordman_7 = {
    7, k_motions_swordman_7, 1, nullptr, 0, 
    "1031 client state table: states 21; basis eligibility pair"};
static const char *const k_motions_swordman_11[] = {
    "character/swordman/animation/dashattackmultihit.ani",
};
static const ClientSkillBinding k_skill_swordman_11 = {
    11, k_motions_swordman_11, 1, nullptr, 0, 
    "1031 client state table: states 29; basis eligibility pair"};
static const char *const k_motions_swordman_14[] = {
    "character/swordman/animation/waveeyeattack3.ani",
};
static const ClientSkillBinding k_skill_swordman_14 = {
    14, k_motions_swordman_14, 1, nullptr, 0, 
    "1031 client state table: states 8,13,23,25; basis eligibility pair"};
static const char *const k_motions_swordman_15[] = {
    "character/swordman/animation/chargecrashdash.ani",
    "character/swordman/animation/chargecrashupper.ani",
    "character/swordman/animation/chargecrashfinish.ani",
};
static const ClientSkillBinding k_skill_swordman_15 = {
    15, k_motions_swordman_15, 3, nullptr, 0, 
    "1031 client state table: states 37; basis eligibility pair"};
static const char *const k_motions_swordman_17[] = {
    "character/swordman/animation/jumpattackmultislash1.ani",
};
static const char *const k_effects_swordman_17[] = {
    "character/swordman/effect/animation/jumpattackmulti/jumpchainattackslash1_katana_under.ani",
    "character/swordman/effect/animation/jumpattackmulti/jumpchainattackslash1_katana_upper.ani",
    "character/swordman/effect/animation/jumpattackmulti/jumpchainattackslash2_katana_under.ani",
    "character/swordman/effect/animation/jumpattackmulti/jumpchainattackslash2_katana_upper.ani",
    "character/swordman/effect/animation/jumpattackmulti/jumpchainattackslash1_under_effect.ani",
    "character/swordman/effect/animation/jumpattackmulti/jumpchainattackslash2_under_effect.ani",
    "character/swordman/effect/animation/jumpattackmulti/jumpchainattackslash1_upper_effect.ani",
    "character/swordman/effect/animation/jumpattackmulti/jumpchainattackslash2_upper_effect.ani",
    "character/swordman/effect/animation/jumpattackmulti/jumpchainattacknormal_upper_effect.ani",
};
static const ClientSkillBinding k_skill_swordman_17 = {
    17, k_motions_swordman_17, 1, k_effects_swordman_17, 9, 
    "1031 client state table: states 69; basis motion name"};
static const char *const k_motions_swordman_20[] = {
    "character/swordman/animation/wave.ani",
};
static const char *const k_effects_swordman_20[] = {
    "character/swordman/effect/animation/normalwaveslash.ani",
};
static const ClientSkillBinding k_skill_swordman_20 = {
    20, k_motions_swordman_20, 1, k_effects_swordman_20, 1, 
    "1031 client state table: states 24; basis eligibility pair"};
static const char *const k_motions_swordman_27[] = {
    "character/swordman/animation/rapidmoveslashready1.ani",
    "character/swordman/animation/rapidmoveslashmove1.ani",
    "character/swordman/animation/guard.ani",
    "character/swordman/animation/rapidmoveslashmove2.ani",
};
static const ClientSkillBinding k_skill_swordman_27 = {
    27, k_motions_swordman_27, 4, nullptr, 0, 
    "1031 client state table: states 39; basis eligibility pair"};
static const char *const k_motions_swordman_46[] = {
    "character/swordman/animation/upperslashafter.ani",
};
static const char *const k_effects_swordman_46[] = {
    "character/swordman/effect/animation/upperslash1.ani",
    "character/swordman/effect/animation/upperslash2.ani",
};
static const ClientSkillBinding k_skill_swordman_46 = {
    46, k_motions_swordman_46, 1, k_effects_swordman_46, 2, 
    "1031 client state table: states 30; basis eligibility pair"};
static const char *const k_motions_swordman_51[] = {
    "character/swordman/animation/hardattack.ani",
};
static const ClientSkillBinding k_skill_swordman_51 = {
    51, k_motions_swordman_51, 1, nullptr, 0, 
    "1031 client state table: states 27; basis eligibility pair"};
static const char *const k_motions_swordman_57[] = {
    "character/swordman/animation/shockwaveareacast.ani",
    "character/swordman/animation/shockwaveareasmash.ani",
};
static const char *const k_effects_swordman_57[] = {
    "character/swordman/effect/animation/shockwavearea/cast.ani",
    "character/swordman/effect/animation/shockwavearea/smash.ani",
    "character/swordman/effect/animation/shockwavearea/area.ani",
};
static const ClientSkillBinding k_skill_swordman_57 = {
    57, k_motions_swordman_57, 2, k_effects_swordman_57, 3, 
    "1031 client state table: states 31; basis eligibility pair"};
static const char *const k_motions_swordman_58[] = {
    "character/swordman/animation/vaneslashtry.ani",
};
static const char *const k_effects_swordman_58[] = {
    "character/swordman/effect/animation/vaneslash/upper.ani",
    "character/swordman/effect/animation/vaneslash/dust.ani",
    "character/swordman/effect/animation/vaneslash/smash.ani",
};
static const ClientSkillBinding k_skill_swordman_58 = {
    58, k_motions_swordman_58, 1, k_effects_swordman_58, 3, 
    "1031 client state table: states 32; basis motion name"};
static const char *const k_motions_swordman_60[] = {
    "character/swordman/animation/ghoststepslashready.ani",
    "character/swordman/animation/ghoststepslashmove.ani",
};
static const char *const k_effects_swordman_60[] = {
    "character/swordman/effect/animation/ghoststepslash/move.ani",
    "character/swordman/effect/animation/ghoststepslash/slash1.ani",
    "character/swordman/effect/animation/ghoststepslash/slash2.ani",
    "character/swordman/effect/animation/ghoststepslash/skull.ani",
};
static const ClientSkillBinding k_skill_swordman_60 = {
    60, k_motions_swordman_60, 2, k_effects_swordman_60, 4, 
    "1031 client state table: states 33; basis eligibility pair"};
static const char *const k_motions_swordman_62[] = {
    "character/swordman/animation/standalonewaveready.ani",
    "character/swordman/animation/standalonewavebasic.ani",
};
static const ClientSkillBinding k_skill_swordman_62 = {
    62, k_motions_swordman_62, 2, nullptr, 0, 
    "1031 client state table: states 34; basis eligibility pair"};
static const char *const k_motions_swordman_64[] = {
    "character/swordman/animation/gorecross.ani",
};
static const char *const k_effects_swordman_64[] = {
    "character/swordman/effect/animation/gorecross/slash1.ani",
    "character/swordman/effect/animation/gorecross/slash2.ani",
    "character/swordman/effect/animation/gorecross/slash3.ani",
    "character/swordman/effect/animation/gorecross/slash4.ani",
};
static const ClientSkillBinding k_skill_swordman_64 = {
    64, k_motions_swordman_64, 1, k_effects_swordman_64, 4, 
    "1031 client state table: states 35; basis eligibility pair"};
static const char *const k_motions_swordman_65[] = {
    "character/swordman/animation/hopsmashready.ani",
    "character/swordman/animation/hopsmash.ani",
};
static const char *const k_effects_swordman_65[] = {
    "character/swordman/effect/animation/hopsmash/sword.ani",
    "character/swordman/effect/animation/hopsmash/smash.ani",
};
static const ClientSkillBinding k_skill_swordman_65 = {
    65, k_motions_swordman_65, 2, k_effects_swordman_65, 2, 
    "1031 client state table: states 36; basis motion name"};
static const char *const k_motions_swordman_68[] = {
    "character/swordman/animation/chargecrashdash.ani",
    "character/swordman/animation/chargecrashupper.ani",
    "character/swordman/animation/chargecrashfinish.ani",
};
static const char *const k_effects_swordman_68[] = {
    "character/swordman/effect/animation/chargecrash/dash.ani",
    "character/swordman/effect/animation/chargecrash/up-slash.ani",
    "character/swordman/effect/animation/chargecrash/charge.ani",
    "character/swordman/effect/animation/chargecrash/down-slash.ani",
    "character/swordman/effect/animation/chargecrash/dustdash.ani",
    "character/swordman/effect/animation/chargecrash/dustdashlast.ani",
};
static const ClientSkillBinding k_skill_swordman_68 = {
    68, k_motions_swordman_68, 3, k_effects_swordman_68, 6, 
    "1031 client state table: states 37; basis motion name"};
static const char *const k_motions_swordman_72[] = {
    "character/swordman/animation/rapidmoveslashready1.ani",
    "character/swordman/animation/rapidmoveslashmove1.ani",
    "character/swordman/animation/guard.ani",
    "character/swordman/animation/rapidmoveslashmove2.ani",
};
static const char *const k_effects_swordman_72[] = {
    "character/swordman/effect/animation/rapidmoveslash/move1.ani",
    "character/swordman/effect/animation/rapidmoveslash/move2.ani",
    "character/swordman/effect/animation/rapidmoveslash/slash1.ani",
    "character/swordman/effect/animation/rapidmoveslash/slash2.ani",
};
static const ClientSkillBinding k_skill_swordman_72 = {
    72, k_motions_swordman_72, 4, k_effects_swordman_72, 4, 
    "1031 client state table: states 39; basis eligibility pair"};
static const char *const k_motions_swordman_73[] = {
    "character/swordman/animation/illusionslash1.ani",
    "character/swordman/animation/illusionslashfinal.ani",
};
static const char *const k_effects_swordman_73[] = {
    "character/swordman/effect/animation/illusionslash/upper.ani",
    "character/swordman/effect/animation/illusionslash/smash.ani",
};
static const ClientSkillBinding k_skill_swordman_73 = {
    73, k_motions_swordman_73, 2, k_effects_swordman_73, 2, 
    "1031 client state table: states 40; basis eligibility pair"};
static const char *const k_motions_swordman_77[] = {
    "character/swordman/animation/moonlightslash1.ani",
    "character/swordman/animation/moonlightslash2.ani",
    "character/swordman/animation/moonlightslashfull.ani",
};
static const char *const k_effects_swordman_77[] = {
    "character/swordman/effect/animation/moonlightslash1.ani",
    "character/swordman/effect/animation/moonlightslash2.ani",
    "character/swordman/effect/animation/moonlightslashfull.ani",
};
static const ClientSkillBinding k_skill_swordman_77 = {
    77, k_motions_swordman_77, 3, k_effects_swordman_77, 3, 
    "1031 client state table: states 42; basis eligibility pair"};
static const char *const k_motions_swordman_79[] = {
    "character/swordman/animation/bloodyraveinhale.ani",
    "character/swordman/animation/bloodyraveslash.ani",
};
static const char *const k_effects_swordman_79[] = {
    "character/swordman/effect/animation/bloodyrave/start1.ani",
    "character/swordman/effect/animation/bloodyrave/start2.ani",
    "character/swordman/effect/animation/bloodyrave/loop1.ani",
    "character/swordman/effect/animation/bloodyrave/loop2.ani",
    "character/swordman/effect/animation/bloodyrave/line1.ani",
    "character/swordman/effect/animation/bloodyrave/line2.ani",
    "character/swordman/effect/animation/bloodyrave/typhoon.ani",
    "character/swordman/effect/animation/bloodyrave/end.ani",
    "character/swordman/effect/animation/bloodyrave/sword1.ani",
    "character/swordman/effect/animation/bloodyrave/sword2.ani",
    "character/swordman/effect/animation/bloodyrave/sword3.ani",
    "character/swordman/effect/animation/bloodyrave/sword4.ani",
    "character/swordman/effect/animation/bloodyrave/(tn)sword2.ani",
    "character/swordman/effect/animation/bloodyrave/(tn)sword4.ani",
    "character/swordman/effect/animation/bloodyrave/hit.ani",
};
static const ClientSkillBinding k_skill_swordman_79 = {
    79, k_motions_swordman_79, 2, k_effects_swordman_79, 15, 
    "1031 client state table: states 43; basis motion name"};
static const char *const k_motions_swordman_81[] = {
    "character/swordman/animation/outragebreakready.ani",
    "character/swordman/animation/outragebreakslash.ani",
};
static const char *const k_effects_swordman_81[] = {
    "character/swordman/effect/animation/outragebreak/sword_ready_ldodge.ani",
    "character/swordman/effect/animation/outragebreak/sword_ready_none.ani",
    "character/swordman/effect/animation/outragebreak/sword_slash_ldodge.ani",
    "character/swordman/effect/animation/outragebreak/sword_slash_none.ani",
    "character/swordman/effect/animation/outragebreak/sword_slash_impact_ldodge.ani",
    "character/swordman/effect/animation/outragebreak/sword_slash_impact_none.ani",
    "character/swordman/effect/animation/outragebreak/sword_slash_stone.ani",
};
static const ClientSkillBinding k_skill_swordman_81 = {
    81, k_motions_swordman_81, 2, k_effects_swordman_81, 7, 
    "1031 client state table: states 45; basis eligibility pair"};
static const char *const k_motions_swordman_82[] = {
    "character/swordman/animation/kallaland.ani",
    "character/swordman/animation/kallaair.ani",
    "character/swordman/animation/kallafinishready.ani",
};
static const char *const k_effects_swordman_82[] = {
    "character/swordman/effect/animation/kalla/finishready",
    "character/swordman/effect/animation/kalla/finish",
};
static const ClientSkillBinding k_skill_swordman_82 = {
    82, k_motions_swordman_82, 3, k_effects_swordman_82, 2, 
    "1031 client state table: states 13,44; basis eligibility pair"};
static const char *const k_motions_swordman_85[] = {
    "character/swordman/animation/hellbenterfinish.ani",
};
static const ClientSkillBinding k_skill_swordman_85 = {
    85, k_motions_swordman_85, 1, nullptr, 0, 
    "1031 client state table: states 46; basis eligibility pair"};
static const char *const k_motions_swordman_86[] = {
    "character/swordman/animation/hundredswordready.ani",
    "character/swordman/animation/guard.ani",
    "character/swordman/animation/hundredswordfinish.ani",
};
static const ClientSkillBinding k_skill_swordman_86 = {
    86, k_motions_swordman_86, 3, nullptr, 0, 
    "1031 client state table: states 47,48,49; basis eligibility pair"};
static const char *const k_motions_swordman_87[] = {
    "character/swordman/animation/blachecast.ani",
    "character/swordman/animation/blachesmash.ani",
};
static const ClientSkillBinding k_skill_swordman_87 = {
    87, k_motions_swordman_87, 2, nullptr, 0, 
    "1031 client state table: states 50; basis eligibility pair"};
static const char *const k_motions_swordman_88[] = {
    "character/swordman/animation/waveeyecast.ani",
    "character/swordman/animation/waveeyestart.ani",
    "character/swordman/animation/waveeyewing.ani",
};
static const ClientSkillBinding k_skill_swordman_88 = {
    88, k_motions_swordman_88, 3, nullptr, 0, 
    "1031 client state table: states 51,53; basis eligibility pair"};
static const char *const k_motions_swordman_102[] = {
    "character/swordman/animation/grab.ani",
};
static const ClientSkillBinding k_skill_swordman_102 = {
    102, k_motions_swordman_102, 1, nullptr, 0, 
    "1031 client state table: states 26; basis eligibility pair"};
static const char *const k_motions_swordman_108[] = {
    "character/swordman/animation/flowmindtwojump.ani",
    "character/swordman/animation/flowmindtwolanding.ani",
};
static const ClientSkillBinding k_skill_swordman_108 = {
    108, k_motions_swordman_108, 2, nullptr, 0, 
    "1031 client state table: states 63; basis eligibility pair"};
static const char *const k_motions_swordman_109[] = {
    "character/swordman/animation/flowmindthreeready.ani",
};
static const ClientSkillBinding k_skill_swordman_109 = {
    109, k_motions_swordman_109, 1, nullptr, 0, 
    "1031 client state table: states 64; basis eligibility pair"};
static const char *const k_motions_swordman_111[] = {
    "character/swordman/animation/ghostsidewind.ani",
};
static const char *const k_effects_swordman_111[] = {
    "character/swordman/effect/animation/ghostsidewind/00_sword_normal.ani",
    "character/swordman/effect/animation/ghostsidewind/01_sword_dodge.ani",
};
static const ClientSkillBinding k_skill_swordman_111 = {
    111, k_motions_swordman_111, 1, k_effects_swordman_111, 2, 
    "1031 client state table: states 65; basis eligibility pair"};
static const char *const k_motions_swordman_112[] = {
    "character/swordman/animation/triplestab.ani",
};
static const ClientSkillBinding k_skill_swordman_112 = {
    112, k_motions_swordman_112, 1, nullptr, 0, 
    "1031 client state table: states 66; basis motion name"};
static const char *const k_motions_swordman_162[] = {
    "character/swordman/animation/dashattackmultihit.ani",
};
static const ClientSkillBinding k_skill_swordman_162 = {
    162, k_motions_swordman_162, 1, nullptr, 0, 
    "1031 client state table: states 29; basis motion name"};

static const char *const k_motions_demonicswordman_1[] = {
    "character/swordman/dsanimation/waveeyeattack3.ani",
    "character/swordman/dsanimation/guard.ani",
    "character/swordman/dsanimation/wave.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_1 = {
    1, k_motions_demonicswordman_1, 3, nullptr, 0, 
    "1031 client state table: states 8,17,19,24; basis eligibility pair"};
static const char *const k_motions_demonicswordman_2[] = {
    "character/swordman/dsanimation/guard.ani",
    "character/swordman/dsanimation/reflectguard.ani",
};
static const char *const k_effects_demonicswordman_2[] = {
    "character/swordman/effect/animation/reflectguard_ds/charge.ani",
    "character/swordman/effect/animation/reflectguard_ds/slash.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_2 = {
    2, k_motions_demonicswordman_2, 2, k_effects_demonicswordman_2, 2, 
    "1031 client state table: states 19,38; basis eligibility pair"};
static const char *const k_motions_demonicswordman_3[] = {
    "character/swordman/dsanimation/guard.ani",
    "character/swordman/dsanimation/hitback.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_3 = {
    3, k_motions_demonicswordman_3, 2, nullptr, 0, 
    "1031 client state table: states 17,19,59; basis eligibility pair"};
static const char *const k_motions_demonicswordman_6[] = {
    "character/swordman/dsanimation/hardattack.ani",
    "character/swordman/dsanimation/hardattackchargeafter.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_6 = {
    6, k_motions_demonicswordman_6, 2, nullptr, 0, 
    "1031 client state table: states 20; basis motion name"};
static const char *const k_motions_demonicswordman_7[] = {
    "character/swordman/dsanimation/hitback.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_7 = {
    7, k_motions_demonicswordman_7, 1, nullptr, 0, 
    "1031 client state table: states 21; basis eligibility pair"};
static const char *const k_motions_demonicswordman_11[] = {
    "character/swordman/dsanimation/dashattackmultihit.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_11 = {
    11, k_motions_demonicswordman_11, 1, nullptr, 0, 
    "1031 client state table: states 29; basis eligibility pair"};
static const char *const k_motions_demonicswordman_14[] = {
    "character/swordman/dsanimation/waveeyeattack3.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_14 = {
    14, k_motions_demonicswordman_14, 1, nullptr, 0, 
    "1031 client state table: states 8,13,23,25; basis eligibility pair"};
static const char *const k_motions_demonicswordman_15[] = {
    "character/swordman/dsanimation/chargecrashdash.ani",
    "character/swordman/dsanimation/chargecrashupper.ani",
    "character/swordman/dsanimation/chargecrashfinish.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_15 = {
    15, k_motions_demonicswordman_15, 3, nullptr, 0, 
    "1031 client state table: states 37; basis eligibility pair"};
static const char *const k_motions_demonicswordman_17[] = {
    "character/swordman/dsanimation/jumpattackmultislash1.ani",
};
static const char *const k_effects_demonicswordman_17[] = {
    "character/swordman/effect/animation/jumpattackmulti_ds/jumpchainattackslash1_katana_under.ani",
    "character/swordman/effect/animation/jumpattackmulti_ds/jumpchainattackslash1_katana_upper.ani",
    "character/swordman/effect/animation/jumpattackmulti_ds/jumpchainattackslash2_katana_under.ani",
    "character/swordman/effect/animation/jumpattackmulti_ds/jumpchainattackslash2_katana_upper.ani",
    "character/swordman/effect/animation/jumpattackmulti_ds/jumpchainattackslash1_under_effect.ani",
    "character/swordman/effect/animation/jumpattackmulti_ds/jumpchainattackslash2_under_effect.ani",
    "character/swordman/effect/animation/jumpattackmulti_ds/jumpchainattackslash1_upper_effect.ani",
    "character/swordman/effect/animation/jumpattackmulti_ds/jumpchainattackslash2_upper_effect.ani",
    "character/swordman/effect/animation/jumpattackmulti_ds/jumpchainattacknormal_upper_effect.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_17 = {
    17, k_motions_demonicswordman_17, 1, k_effects_demonicswordman_17, 9, 
    "1031 client state table: states 69; basis motion name"};
static const char *const k_motions_demonicswordman_20[] = {
    "character/swordman/dsanimation/wave.ani",
};
static const char *const k_effects_demonicswordman_20[] = {
    "character/swordman/effect/animation/normalwaveslash_ds.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_20 = {
    20, k_motions_demonicswordman_20, 1, k_effects_demonicswordman_20, 1, 
    "1031 client state table: states 24; basis eligibility pair"};
static const char *const k_motions_demonicswordman_27[] = {
    "character/swordman/dsanimation/rapidmoveslashready1.ani",
    "character/swordman/dsanimation/rapidmoveslashmove1.ani",
    "character/swordman/dsanimation/guard.ani",
    "character/swordman/dsanimation/rapidmoveslashmove2.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_27 = {
    27, k_motions_demonicswordman_27, 4, nullptr, 0, 
    "1031 client state table: states 39; basis eligibility pair"};
static const char *const k_motions_demonicswordman_46[] = {
    "character/swordman/dsanimation/upperslashafter.ani",
};
static const char *const k_effects_demonicswordman_46[] = {
    "character/swordman/effect/animation/upperslash1_ds.ani",
    "character/swordman/effect/animation/upperslash2_ds.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_46 = {
    46, k_motions_demonicswordman_46, 1, k_effects_demonicswordman_46, 2, 
    "1031 client state table: states 30; basis eligibility pair"};
static const char *const k_motions_demonicswordman_51[] = {
    "character/swordman/dsanimation/hardattack.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_51 = {
    51, k_motions_demonicswordman_51, 1, nullptr, 0, 
    "1031 client state table: states 27; basis eligibility pair"};
static const char *const k_motions_demonicswordman_57[] = {
    "character/swordman/dsanimation/shockwaveareacast.ani",
    "character/swordman/dsanimation/shockwaveareasmash.ani",
};
static const char *const k_effects_demonicswordman_57[] = {
    "character/swordman/effect/animation/shockwavearea_ds/cast.ani",
    "character/swordman/effect/animation/shockwavearea_ds/smash.ani",
    "character/swordman/effect/animation/shockwavearea_ds/area.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_57 = {
    57, k_motions_demonicswordman_57, 2, k_effects_demonicswordman_57, 3, 
    "1031 client state table: states 31; basis eligibility pair"};
static const char *const k_motions_demonicswordman_58[] = {
    "character/swordman/dsanimation/vaneslashtry.ani",
};
static const char *const k_effects_demonicswordman_58[] = {
    "character/swordman/effect/animation/vaneslash_ds/upper.ani",
    "character/swordman/effect/animation/vaneslash_ds/dust.ani",
    "character/swordman/effect/animation/vaneslash_ds/smash.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_58 = {
    58, k_motions_demonicswordman_58, 1, k_effects_demonicswordman_58, 3, 
    "1031 client state table: states 32; basis motion name"};
static const char *const k_motions_demonicswordman_60[] = {
    "character/swordman/dsanimation/ghoststepslashready.ani",
    "character/swordman/dsanimation/ghoststepslashmove.ani",
};
static const char *const k_effects_demonicswordman_60[] = {
    "character/swordman/effect/animation/ghoststepslash_ds/move.ani",
    "character/swordman/effect/animation/ghoststepslash_ds/slash1.ani",
    "character/swordman/effect/animation/ghoststepslash_ds/slash2.ani",
    "character/swordman/effect/animation/ghoststepslash_ds/skull.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_60 = {
    60, k_motions_demonicswordman_60, 2, k_effects_demonicswordman_60, 4, 
    "1031 client state table: states 33; basis eligibility pair"};
static const char *const k_motions_demonicswordman_62[] = {
    "character/swordman/dsanimation/standalonewaveready.ani",
    "character/swordman/dsanimation/standalonewavebasic.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_62 = {
    62, k_motions_demonicswordman_62, 2, nullptr, 0, 
    "1031 client state table: states 34; basis eligibility pair"};
static const char *const k_motions_demonicswordman_64[] = {
    "character/swordman/dsanimation/gorecross.ani",
};
static const char *const k_effects_demonicswordman_64[] = {
    "character/swordman/effect/animation/gorecross_ds/slash1.ani",
    "character/swordman/effect/animation/gorecross_ds/slash2.ani",
    "character/swordman/effect/animation/gorecross_ds/slash3.ani",
    "character/swordman/effect/animation/gorecross_ds/slash4.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_64 = {
    64, k_motions_demonicswordman_64, 1, k_effects_demonicswordman_64, 4, 
    "1031 client state table: states 35; basis eligibility pair"};
static const char *const k_motions_demonicswordman_65[] = {
    "character/swordman/dsanimation/hopsmashready.ani",
    "character/swordman/dsanimation/hopsmash.ani",
};
static const char *const k_effects_demonicswordman_65[] = {
    "character/swordman/effect/animation/hopsmash_ds/sword.ani",
    "character/swordman/effect/animation/hopsmash_ds/smash.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_65 = {
    65, k_motions_demonicswordman_65, 2, k_effects_demonicswordman_65, 2, 
    "1031 client state table: states 36; basis motion name"};
static const char *const k_motions_demonicswordman_72[] = {
    "character/swordman/dsanimation/rapidmoveslashready1.ani",
    "character/swordman/dsanimation/rapidmoveslashmove1.ani",
    "character/swordman/dsanimation/guard.ani",
    "character/swordman/dsanimation/rapidmoveslashmove2.ani",
};
static const char *const k_effects_demonicswordman_72[] = {
    "character/swordman/effect/animation/rapidmoveslash_ds/move1.ani",
    "character/swordman/effect/animation/rapidmoveslash_ds/move2.ani",
    "character/swordman/effect/animation/rapidmoveslash_ds/slash1.ani",
    "character/swordman/effect/animation/rapidmoveslash_ds/slash2.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_72 = {
    72, k_motions_demonicswordman_72, 4, k_effects_demonicswordman_72, 4, 
    "1031 client state table: states 39; basis eligibility pair"};
static const char *const k_motions_demonicswordman_73[] = {
    "character/swordman/dsanimation/illusionslash1.ani",
    "character/swordman/dsanimation/illusionslashfinal.ani",
};
static const char *const k_effects_demonicswordman_73[] = {
    "character/swordman/effect/animation/illusionslash_ds/upper.ani",
    "character/swordman/effect/animation/illusionslash_ds/smash.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_73 = {
    73, k_motions_demonicswordman_73, 2, k_effects_demonicswordman_73, 2, 
    "1031 client state table: states 40; basis eligibility pair"};
static const char *const k_motions_demonicswordman_77[] = {
    "character/swordman/dsanimation/moonlightslash1.ani",
    "character/swordman/dsanimation/moonlightslash2.ani",
    "character/swordman/dsanimation/moonlightslashfull.ani",
};
static const char *const k_effects_demonicswordman_77[] = {
    "character/swordman/effect/animation/moonlightslash1_ds.ani",
    "character/swordman/effect/animation/moonlightslash2_ds.ani",
    "character/swordman/effect/animation/moonlightslashfull.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_77 = {
    77, k_motions_demonicswordman_77, 3, k_effects_demonicswordman_77, 3, 
    "1031 client state table: states 42; basis eligibility pair"};
static const char *const k_motions_demonicswordman_81[] = {
    "character/swordman/dsanimation/outragebreakready.ani",
    "character/swordman/dsanimation/outragebreakslash.ani",
};
static const char *const k_effects_demonicswordman_81[] = {
    "character/swordman/effect/animation/outragebreak_ds/sword_ready_ldodge.ani",
    "character/swordman/effect/animation/outragebreak_ds/sword_ready_none.ani",
    "character/swordman/effect/animation/outragebreak_ds/sword_slash_ldodge.ani",
    "character/swordman/effect/animation/outragebreak_ds/sword_slash_none.ani",
    "character/swordman/effect/animation/outragebreak_ds/sword_slash_impact_ldodge.ani",
    "character/swordman/effect/animation/outragebreak_ds/sword_slash_impact_none.ani",
    "character/swordman/effect/animation/outragebreak_ds/sword_slash_stone.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_81 = {
    81, k_motions_demonicswordman_81, 2, k_effects_demonicswordman_81, 7, 
    "1031 client state table: states 45; basis eligibility pair"};
static const char *const k_motions_demonicswordman_82[] = {
    "character/swordman/dsanimation/kallaland.ani",
    "character/swordman/dsanimation/kallaair.ani",
    "character/swordman/dsanimation/kallafinishready.ani",
};
static const char *const k_effects_demonicswordman_82[] = {
    "character/swordman/effect/animation/kalla_ds/finishready",
    "character/swordman/effect/animation/kalla_ds/finish",
};
static const ClientSkillBinding k_skill_demonicswordman_82 = {
    82, k_motions_demonicswordman_82, 3, k_effects_demonicswordman_82, 2, 
    "1031 client state table: states 13,44; basis eligibility pair"};
static const char *const k_motions_demonicswordman_85[] = {
    "character/swordman/dsanimation/hellbenterfinish.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_85 = {
    85, k_motions_demonicswordman_85, 1, nullptr, 0, 
    "1031 client state table: states 46; basis eligibility pair"};
static const char *const k_motions_demonicswordman_86[] = {
    "character/swordman/dsanimation/hundredswordready.ani",
    "character/swordman/dsanimation/guard.ani",
    "character/swordman/dsanimation/hundredswordfinish.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_86 = {
    86, k_motions_demonicswordman_86, 3, nullptr, 0, 
    "1031 client state table: states 47,48,49; basis eligibility pair"};
static const char *const k_motions_demonicswordman_87[] = {
    "character/swordman/dsanimation/blachecast.ani",
    "character/swordman/dsanimation/blachesmash.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_87 = {
    87, k_motions_demonicswordman_87, 2, nullptr, 0, 
    "1031 client state table: states 50; basis eligibility pair"};
static const char *const k_motions_demonicswordman_88[] = {
    "character/swordman/dsanimation/waveeyecast.ani",
    "character/swordman/dsanimation/waveeyestart.ani",
    "character/swordman/dsanimation/waveeyewing.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_88 = {
    88, k_motions_demonicswordman_88, 3, nullptr, 0, 
    "1031 client state table: states 51,53; basis eligibility pair"};
static const char *const k_motions_demonicswordman_102[] = {
    "character/swordman/dsanimation/grab.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_102 = {
    102, k_motions_demonicswordman_102, 1, nullptr, 0, 
    "1031 client state table: states 26; basis eligibility pair"};
static const char *const k_motions_demonicswordman_108[] = {
    "character/swordman/dsanimation/flowmindtwojump.ani",
    "character/swordman/dsanimation/flowmindtwolanding.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_108 = {
    108, k_motions_demonicswordman_108, 2, nullptr, 0, 
    "1031 client state table: states 63; basis eligibility pair"};
static const char *const k_motions_demonicswordman_109[] = {
    "character/swordman/dsanimation/flowmindthreeready.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_109 = {
    109, k_motions_demonicswordman_109, 1, nullptr, 0, 
    "1031 client state table: states 64; basis eligibility pair"};
static const char *const k_motions_demonicswordman_111[] = {
    "character/swordman/dsanimation/ghostsidewind.ani",
};
static const char *const k_effects_demonicswordman_111[] = {
    "character/swordman/effect/animation/ghostsidewind_ds/00_sword_normal.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_111 = {
    111, k_motions_demonicswordman_111, 1, k_effects_demonicswordman_111, 1, 
    "1031 client state table: states 65; basis eligibility pair"};
static const char *const k_motions_demonicswordman_112[] = {
    "character/swordman/dsanimation/triplestab.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_112 = {
    112, k_motions_demonicswordman_112, 1, nullptr, 0, 
    "1031 client state table: states 66; basis motion name"};
static const char *const k_motions_demonicswordman_117[] = {
    "character/swordman/dsanimation/darkwave.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_117 = {
    117, k_motions_demonicswordman_117, 1, nullptr, 0, 
    "1031 client state table: states 67; basis motion name"};
static const char *const k_motions_demonicswordman_162[] = {
    "character/swordman/dsanimation/dashattackmultihit.ani",
};
static const ClientSkillBinding k_skill_demonicswordman_162 = {
    162, k_motions_demonicswordman_162, 1, nullptr, 0, 
    "1031 client state table: states 29; basis motion name"};

static const char *const k_motions_fighter_1[] = {
    "character/fighter/animation/damagelowkick.ani",
    "character/fighter/animation/crashlowkick.ani",
    "character/fighter/animation/trysuplexcyclone.ani",
    "character/fighter/animation/shouldercharge.ani",
};
static const ClientSkillBinding k_skill_fighter_1 = {
    1, k_motions_fighter_1, 4, nullptr, 0, 
    "1031 client state table: states 21,22,43,47; basis eligibility pair"};
static const char *const k_motions_fighter_2[] = {
    "character/fighter/animation/crouch.ani",
};
static const ClientSkillBinding k_skill_fighter_2 = {
    2, k_motions_fighter_2, 1, nullptr, 0, 
    "1031 client state table: states 19,20; basis eligibility pair"};
static const char *const k_motions_fighter_4[] = {
    "character/fighter/animation/damagelowkick.ani",
    "character/fighter/animation/crashlowkick.ani",
};
static const ClientSkillBinding k_skill_fighter_4 = {
    4, k_motions_fighter_4, 2, nullptr, 0, 
    "1031 client state table: states 21; basis eligibility pair"};
static const char *const k_motions_fighter_5[] = {
    "character/fighter/animation/liftupper.ani",
};
static const ClientSkillBinding k_skill_fighter_5 = {
    5, k_motions_fighter_5, 1, nullptr, 0, 
    "1031 client state table: states 30; basis eligibility pair"};
static const char *const k_motions_fighter_6[] = {
    "character/fighter/animation/damagelowkick.ani",
    "character/fighter/animation/crashlowkick.ani",
};
static const ClientSkillBinding k_skill_fighter_6 = {
    6, k_motions_fighter_6, 2, nullptr, 0, 
    "1031 client state table: states 21; basis eligibility pair"};
static const char *const k_motions_fighter_9[] = {
    "character/fighter/animation/trysuplexcyclone.ani",
    "character/fighter/animation/backsuplex.ani",
    "character/fighter/animation/crouch.ani",
    "character/fighter/animation/suplex.ani",
};
static const ClientSkillBinding k_skill_fighter_9 = {
    9, k_motions_fighter_9, 4, nullptr, 0, 
    "1031 client state table: states 22,23; basis eligibility pair"};
static const char *const k_motions_fighter_10[] = {
    "character/fighter/animation/backsuplex.ani",
    "character/fighter/animation/crouch.ani",
    "character/fighter/animation/suplex.ani",
};
static const ClientSkillBinding k_skill_fighter_10 = {
    10, k_motions_fighter_10, 3, nullptr, 0, 
    "1031 client state table: states 23; basis eligibility pair"};
static const char *const k_motions_fighter_13[] = {
    "character/fighter/animation/trylegsuplex.ani",
};
static const ClientSkillBinding k_skill_fighter_13 = {
    13, k_motions_fighter_13, 1, nullptr, 0, 
    "1031 client state table: states 63; basis eligibility pair"};
static const char *const k_motions_fighter_14[] = {
    "character/fighter/animation/mounttry.ani",
    "character/fighter/animation/crazymountstart.ani",
    "character/fighter/animation/mount.ani",
    "character/fighter/animation/mountleft.ani",
    "character/fighter/animation/mountright.ani",
    "character/fighter/animation/mountend.ani",
};
static const ClientSkillBinding k_skill_fighter_14 = {
    14, k_motions_fighter_14, 6, nullptr, 0, 
    "1031 client state table: states 26,27; basis eligibility pair"};
static const char *const k_motions_fighter_17[] = {
    "character/fighter/animation/stompfinish.ani",
};
static const ClientSkillBinding k_skill_fighter_17 = {
    17, k_motions_fighter_17, 1, nullptr, 0, 
    "1031 client state table: states 28; basis eligibility pair"};
static const char *const k_motions_fighter_18[] = {
    "character/fighter/animation/trysuplexcyclone.ani",
    "character/fighter/animation/jumpsuplex.ani",
    "character/fighter/animation/jumpsuplexlariat.ani",
};
static const ClientSkillBinding k_skill_fighter_18 = {
    18, k_motions_fighter_18, 3, nullptr, 0, 
    "1031 client state table: states 22,24,25; basis eligibility pair"};
static const char *const k_motions_fighter_19[] = {
    "character/fighter/animation/closepunch.ani",
};
static const ClientSkillBinding k_skill_fighter_19 = {
    19, k_motions_fighter_19, 1, nullptr, 0, 
    "1031 client state table: states 29; basis eligibility pair"};
static const char *const k_motions_fighter_22[] = {
    "character/fighter/animation/backsuplex.ani",
    "character/fighter/animation/crouch.ani",
    "character/fighter/animation/suplex.ani",
};
static const ClientSkillBinding k_skill_fighter_22 = {
    22, k_motions_fighter_22, 3, nullptr, 0, 
    "1031 client state table: states 23; basis motion name"};
static const char *const k_motions_fighter_41[] = {
    "character/fighter/animation/nenflower.ani",
};
static const ClientSkillBinding k_skill_fighter_41 = {
    41, k_motions_fighter_41, 1, nullptr, 0, 
    "1031 client state table: states 49,62; basis eligibility pair"};
static const char *const k_motions_fighter_46[] = {
    "character/fighter/animation/singlekick.ani",
};
static const ClientSkillBinding k_skill_fighter_46 = {
    46, k_motions_fighter_46, 1, nullptr, 0, 
    "1031 client state table: states 44,48; basis eligibility pair"};
static const char *const k_motions_fighter_49[] = {
    "character/fighter/animation/trysuplexcyclone.ani",
    "character/fighter/animation/throwenemyhold.ani",
    "character/fighter/animation/throwenemythrow.ani",
};
static const ClientSkillBinding k_skill_fighter_49 = {
    49, k_motions_fighter_49, 3, nullptr, 0, 
    "1031 client state table: states 22,50; basis eligibility pair"};
static const char *const k_motions_fighter_54[] = {
    "character/fighter/animation/shouldertackle.ani",
};
static const ClientSkillBinding k_skill_fighter_54 = {
    54, k_motions_fighter_54, 1, nullptr, 0, 
    "1031 client state table: states 33; basis eligibility pair"};
static const char *const k_motions_fighter_58[] = {
    "character/fighter/animation/whirlwindkick.ani",
};
static const ClientSkillBinding k_skill_fighter_58 = {
    58, k_motions_fighter_58, 1, nullptr, 0, 
    "1031 client state table: states 34; basis eligibility pair"};
static const char *const k_motions_fighter_60[] = {
    "character/fighter/animation/blockbuster.ani",
};
static const ClientSkillBinding k_skill_fighter_60 = {
    60, k_motions_fighter_60, 1, nullptr, 0, 
    "1031 client state table: states 35; basis eligibility pair"};
static const char *const k_motions_fighter_62[] = {
    "character/fighter/animation/trylegsuplex.ani",
};
static const ClientSkillBinding k_skill_fighter_62 = {
    62, k_motions_fighter_62, 1, nullptr, 0, 
    "1031 client state table: states 36; basis eligibility pair"};
static const char *const k_motions_fighter_63[] = {
    "character/fighter/animation/trysuplexcyclone.ani",
    "character/fighter/animation/typhoonspin.ani",
    "character/fighter/animation/strongestlowkickstamp.ani",
    "character/fighter/animation/strongestlowkickready.ani",
    "character/fighter/animation/strongestlowkick.ani",
};
static const ClientSkillBinding k_skill_fighter_63 = {
    63, k_motions_fighter_63, 5, nullptr, 0, 
    "1031 client state table: states 22,38,61; basis eligibility pair"};
static const char *const k_motions_fighter_64[] = {
    "character/fighter/animation/poisonmist.ani",
    "character/fighter/animation/poisonmistexplosion.ani",
};
static const ClientSkillBinding k_skill_fighter_64 = {
    64, k_motions_fighter_64, 2, nullptr, 0, 
    "1031 client state table: states 40,41; basis eligibility pair"};
static const char *const k_motions_fighter_67[] = {
    "character/fighter/animation/nenflower.ani",
};
static const ClientSkillBinding k_skill_fighter_67 = {
    67, k_motions_fighter_67, 1, nullptr, 0, 
    "1031 client state table: states 45,49; basis eligibility pair"};
static const char *const k_motions_fighter_68[] = {
    "character/fighter/animation/typhoonspin.ani",
    "character/fighter/animation/groundkickcharge.ani",
};
static const ClientSkillBinding k_skill_fighter_68 = {
    68, k_motions_fighter_68, 2, nullptr, 0, 
    "1031 client state table: states 38,42; basis eligibility pair"};
static const char *const k_motions_fighter_71[] = {
    "character/fighter/animation/strongestlowkickstamp.ani",
    "character/fighter/animation/strongestlowkickready.ani",
    "character/fighter/animation/strongestlowkick.ani",
};
static const ClientSkillBinding k_skill_fighter_71 = {
    71, k_motions_fighter_71, 3, nullptr, 0, 
    "1031 client state table: states 61; basis eligibility pair"};
static const char *const k_motions_fighter_74[] = {
    "character/fighter/animation/crazymountstart.ani",
    "character/fighter/animation/mount.ani",
    "character/fighter/animation/mountleft.ani",
    "character/fighter/animation/mountright.ani",
    "character/fighter/animation/mountend.ani",
};
static const ClientSkillBinding k_skill_fighter_74 = {
    74, k_motions_fighter_74, 5, nullptr, 0, 
    "1031 client state table: states 27; basis motion name"};
static const char *const k_motions_fighter_75[] = {
    "character/fighter/animation/dashpunch.ani",
    "character/fighter/animation/crouch.ani",
    "character/fighter/animation/dashpunchex.ani",
};
static const ClientSkillBinding k_skill_fighter_75 = {
    75, k_motions_fighter_75, 3, nullptr, 0, 
    "1031 client state table: states 44,65; basis eligibility pair"};
static const char *const k_motions_fighter_76[] = {
    "character/fighter/animation/poisonmistexplosion.ani",
};
static const ClientSkillBinding k_skill_fighter_76 = {
    76, k_motions_fighter_76, 1, nullptr, 0, 
    "1031 client state table: states 41; basis eligibility pair"};
static const char *const k_motions_fighter_77[] = {
    "character/fighter/animation/groundkickcharge.ani",
};
static const ClientSkillBinding k_skill_fighter_77 = {
    77, k_motions_fighter_77, 1, nullptr, 0, 
    "1031 client state table: states 42,46; basis eligibility pair"};
static const char *const k_motions_fighter_80[] = {
    "character/fighter/animation/shouldercharge.ani",
    "character/fighter/animation/dashpunch.ani",
    "character/fighter/animation/crouch.ani",
    "character/fighter/animation/dashpunchex.ani",
};
static const ClientSkillBinding k_skill_fighter_80 = {
    80, k_motions_fighter_80, 4, nullptr, 0, 
    "1031 client state table: states 47,51,65; basis eligibility pair"};
static const char *const k_motions_fighter_81[] = {
    "character/fighter/animation/singlekick.ani",
    "character/fighter/animation/punchafterreturn.ani",
};
static const ClientSkillBinding k_skill_fighter_81 = {
    81, k_motions_fighter_81, 2, nullptr, 0, 
    "1031 client state table: states 48,52; basis eligibility pair"};
static const char *const k_motions_fighter_82[] = {
    "character/fighter/animation/randomkickready.ani",
    "character/fighter/animation/randomkickstart.ani",
    "character/fighter/animation/randomkickend.ani",
    "character/fighter/animation/randomkickendpunch.ani",
};
static const ClientSkillBinding k_skill_fighter_82 = {
    82, k_motions_fighter_82, 4, nullptr, 0, 
    "1031 client state table: states 53; basis eligibility pair"};
static const char *const k_motions_fighter_83[] = {
    "character/fighter/animation/throwenemyhold.ani",
    "character/fighter/animation/throwenemythrow.ani",
    "character/fighter/animation/risingupperdash.ani",
    "character/fighter/animation/risingupper.ani",
    "character/fighter/animation/risingupperex.ani",
    "character/fighter/animation/risingupperexfinish.ani",
};
static const ClientSkillBinding k_skill_fighter_83 = {
    83, k_motions_fighter_83, 6, nullptr, 0, 
    "1031 client state table: states 50,54; basis eligibility pair"};
static const char *const k_motions_fighter_84[] = {
    "character/fighter/animation/dashpunch.ani",
    "character/fighter/animation/crouch.ani",
    "character/fighter/animation/dashpunchex.ani",
    "character/fighter/animation/dashafterdashcombo1.ani",
    "character/fighter/animation/dashafterdashcombo2.ani",
    "character/fighter/animation/crashlowkick.ani",
    "character/fighter/animation/dashafterdashcombo3.ani",
    "character/fighter/animation/dashafterdashcombo4.ani",
};
static const ClientSkillBinding k_skill_fighter_84 = {
    84, k_motions_fighter_84, 8, nullptr, 0, 
    "1031 client state table: states 51,55; basis eligibility pair"};
static const char *const k_motions_fighter_86[] = {
    "character/fighter/animation/punchafterreturn.ani",
    "character/fighter/animation/earthbreak.ani",
};
static const ClientSkillBinding k_skill_fighter_86 = {
    86, k_motions_fighter_86, 2, nullptr, 0, 
    "1031 client state table: states 52,56; basis eligibility pair"};
static const char *const k_motions_fighter_87[] = {
    "character/fighter/animation/randomkickready.ani",
    "character/fighter/animation/randomkickstart.ani",
    "character/fighter/animation/randomkickend.ani",
    "character/fighter/animation/randomkickendpunch.ani",
    "character/fighter/animation/holduptry.ani",
    "character/fighter/animation/holduphold.ani",
    "character/fighter/animation/holduphit.ani",
};
static const ClientSkillBinding k_skill_fighter_87 = {
    87, k_motions_fighter_87, 7, nullptr, 0, 
    "1031 client state table: states 53,57; basis eligibility pair"};
static const char *const k_motions_fighter_88[] = {
    "character/fighter/animation/risingupperdash.ani",
    "character/fighter/animation/risingupper.ani",
    "character/fighter/animation/risingupperex.ani",
    "character/fighter/animation/risingupperexfinish.ani",
    "character/fighter/animation/wildcannonspikejump.ani",
    "character/fighter/animation/wildcannonspikehit.ani",
    "character/fighter/animation/wildcannonspikeslide.ani",
    "character/fighter/animation/wildcannonspikeexp.ani",
};
static const ClientSkillBinding k_skill_fighter_88 = {
    88, k_motions_fighter_88, 8, nullptr, 0, 
    "1031 client state table: states 54,58; basis eligibility pair"};
static const char *const k_motions_fighter_89[] = {
    "character/fighter/animation/trysuplexcyclone.ani",
    "character/fighter/animation/suplexcycloneturn.ani",
    "character/fighter/animation/suplexcyclonecrash.ani",
    "character/fighter/animation/suplexcyclonefinish.ani",
};
static const ClientSkillBinding k_skill_fighter_89 = {
    89, k_motions_fighter_89, 4, nullptr, 0, 
    "1031 client state table: states 22,59; basis eligibility pair"};
static const char *const k_motions_fighter_90[] = {
    "character/fighter/animation/earthbreak.ani",
    "character/fighter/animation/lightningdragon.ani",
};
static const ClientSkillBinding k_skill_fighter_90 = {
    90, k_motions_fighter_90, 2, nullptr, 0, 
    "1031 client state table: states 56,60; basis eligibility pair"};
static const char *const k_motions_fighter_101[] = {
    "character/fighter/animation/trylegsuplex.ani",
};
static const ClientSkillBinding k_skill_fighter_101 = {
    101, k_motions_fighter_101, 1, nullptr, 0, 
    "1031 client state table: states 63; basis eligibility pair"};
static const char *const k_motions_fighter_102[] = {
    "character/fighter/animation/dashpunch.ani",
    "character/fighter/animation/crouch.ani",
    "character/fighter/animation/dashpunchex.ani",
};
static const ClientSkillBinding k_skill_fighter_102 = {
    102, k_motions_fighter_102, 3, nullptr, 0, 
    "1031 client state table: states 51,65; basis motion name"};
static const char *const k_motions_fighter_103[] = {
    "character/fighter/animation/risingupperexstart.ani",
    "character/fighter/animation/risingupper.ani",
};
static const ClientSkillBinding k_skill_fighter_103 = {
    103, k_motions_fighter_103, 2, nullptr, 0, 
    "1031 client state table: states 66; basis eligibility pair"};
static const char *const k_motions_fighter_104[] = {
    "character/fighter/animation/blockbusterextry.ani",
    "character/fighter/animation/blockbusterexjump.ani",
    "character/fighter/animation/blockbusterexfinish.ani",
};
static const ClientSkillBinding k_skill_fighter_104 = {
    104, k_motions_fighter_104, 3, nullptr, 0, 
    "1031 client state table: states 67; basis eligibility pair"};
static const char *const k_motions_fighter_105[] = {
    "character/fighter/animation/lightningdragon.ani",
    "character/fighter/animation/suplexcycloneturn.ani",
    "character/fighter/animation/suplexcycloneexjump.ani",
    "character/fighter/animation/suplexcycloneexspin.ani",
    "character/fighter/animation/suplexcyclonefinish.ani",
};
static const ClientSkillBinding k_skill_fighter_105 = {
    105, k_motions_fighter_105, 5, nullptr, 0, 
    "1031 client state table: states 60,68; basis eligibility pair"};
static const char *const k_motions_fighter_106[] = {
    "character/fighter/animation/wildcannonspikejump.ani",
    "character/fighter/animation/wildcannonspikehit.ani",
    "character/fighter/animation/wildcannonspikeslide.ani",
    "character/fighter/animation/wildcannonspikeexp.ani",
};
static const ClientSkillBinding k_skill_fighter_106 = {
    106, k_motions_fighter_106, 4, nullptr, 0, 
    "1031 client state table: states 58,69; basis eligibility pair"};
static const char *const k_motions_fighter_108[] = {
    "character/fighter/animation/suplexcycloneturn.ani",
    "character/fighter/animation/suplexcyclonecrash.ani",
    "character/fighter/animation/suplexcyclonefinish.ani",
};
static const ClientSkillBinding k_skill_fighter_108 = {
    108, k_motions_fighter_108, 3, nullptr, 0, 
    "1031 client state table: states 59; basis eligibility pair"};
static const char *const k_motions_fighter_111[] = {
    "character/fighter/animation/dashpunch.ani",
    "character/fighter/animation/crouch.ani",
    "character/fighter/animation/dashpunchex.ani",
};
static const ClientSkillBinding k_skill_fighter_111 = {
    111, k_motions_fighter_111, 3, nullptr, 0, 
    "1031 client state table: states 65; basis eligibility pair"};
static const char *const k_motions_fighter_117[] = {
    "character/fighter/animation/risingupperexstart.ani",
    "character/fighter/animation/risingupper.ani",
};
static const ClientSkillBinding k_skill_fighter_117 = {
    117, k_motions_fighter_117, 2, nullptr, 0, 
    "1031 client state table: states 66; basis eligibility pair"};
static const char *const k_motions_fighter_120[] = {
    "character/fighter/animation/crazymountend.ani",
};
static const ClientSkillBinding k_skill_fighter_120 = {
    120, k_motions_fighter_120, 1, nullptr, 0, 
    "1031 client state table: states 70; basis eligibility pair"};
static const char *const k_motions_fighter_122[] = {
    "character/fighter/animation/blockbusterextry.ani",
    "character/fighter/animation/blockbusterexjump.ani",
    "character/fighter/animation/blockbusterexfinish.ani",
};
static const ClientSkillBinding k_skill_fighter_122 = {
    122, k_motions_fighter_122, 3, nullptr, 0, 
    "1031 client state table: states 67; basis eligibility pair"};
static const char *const k_motions_fighter_123[] = {
    "character/fighter/animation/suplexcycloneturn.ani",
    "character/fighter/animation/suplexcycloneexjump.ani",
    "character/fighter/animation/suplexcycloneexspin.ani",
    "character/fighter/animation/suplexcyclonefinish.ani",
};
static const ClientSkillBinding k_skill_fighter_123 = {
    123, k_motions_fighter_123, 4, nullptr, 0, 
    "1031 client state table: states 68; basis eligibility pair"};
static const char *const k_motions_fighter_135[] = {
    "character/fighter/animation/nenflower.ani",
};
static const ClientSkillBinding k_skill_fighter_135 = {
    135, k_motions_fighter_135, 1, nullptr, 0, 
    "1031 client state table: states 49; basis eligibility pair"};
static const char *const k_motions_fighter_139[] = {
    "character/fighter/animation/risingupperdash.ani",
    "character/fighter/animation/risingupper.ani",
    "character/fighter/animation/risingupperex.ani",
    "character/fighter/animation/risingupperexfinish.ani",
};
static const ClientSkillBinding k_skill_fighter_139 = {
    139, k_motions_fighter_139, 4, nullptr, 0, 
    "1031 client state table: states 54; basis eligibility pair"};

static const char *const k_motions_atfighter_1[] = {
    "character/fighter/atanimation/damagelowkick.ani",
    "character/fighter/atanimation/crashlowkick.ani",
    "character/fighter/atanimation/holduphit.ani",
    "character/fighter/atanimation/flamelegscast.ani",
};
static const ClientSkillBinding k_skill_atfighter_1 = {
    1, k_motions_atfighter_1, 4, nullptr, 0, 
    "1031 client state table: states 21,22,43,47; basis eligibility pair"};
static const char *const k_motions_atfighter_2[] = {
    "character/fighter/atanimation/crouch.ani",
};
static const ClientSkillBinding k_skill_atfighter_2 = {
    2, k_motions_atfighter_2, 1, nullptr, 0, 
    "1031 client state table: states 19,20; basis eligibility pair"};
static const char *const k_motions_atfighter_4[] = {
    "character/fighter/atanimation/damagelowkick.ani",
    "character/fighter/atanimation/crashlowkick.ani",
};
static const ClientSkillBinding k_skill_atfighter_4 = {
    4, k_motions_atfighter_4, 2, nullptr, 0, 
    "1031 client state table: states 21; basis eligibility pair"};
static const char *const k_motions_atfighter_5[] = {
    "character/fighter/atanimation/liftupper.ani",
};
static const ClientSkillBinding k_skill_atfighter_5 = {
    5, k_motions_atfighter_5, 1, nullptr, 0, 
    "1031 client state table: states 30; basis eligibility pair"};
static const char *const k_motions_atfighter_6[] = {
    "character/fighter/atanimation/damagelowkick.ani",
    "character/fighter/atanimation/crashlowkick.ani",
};
static const ClientSkillBinding k_skill_atfighter_6 = {
    6, k_motions_atfighter_6, 2, nullptr, 0, 
    "1031 client state table: states 21; basis eligibility pair"};
static const char *const k_motions_atfighter_9[] = {
    "character/fighter/atanimation/holduphit.ani",
    "character/fighter/atanimation/backsuplex.ani",
    "character/fighter/atanimation/crouch.ani",
    "character/fighter/atanimation/suplex.ani",
};
static const ClientSkillBinding k_skill_atfighter_9 = {
    9, k_motions_atfighter_9, 4, nullptr, 0, 
    "1031 client state table: states 22,23; basis eligibility pair"};
static const char *const k_motions_atfighter_10[] = {
    "character/fighter/atanimation/backsuplex.ani",
    "character/fighter/atanimation/crouch.ani",
    "character/fighter/atanimation/suplex.ani",
};
static const ClientSkillBinding k_skill_atfighter_10 = {
    10, k_motions_atfighter_10, 3, nullptr, 0, 
    "1031 client state table: states 23; basis eligibility pair"};
static const char *const k_motions_atfighter_13[] = {
    "character/fighter/atanimation/blockbusterjump.ani",
};
static const ClientSkillBinding k_skill_atfighter_13 = {
    13, k_motions_atfighter_13, 1, nullptr, 0, 
    "1031 client state table: states 63; basis eligibility pair"};
static const char *const k_motions_atfighter_14[] = {
    "character/fighter/atanimation/mounttry.ani",
    "character/fighter/atanimation/typhoonjump.ani",
    "character/fighter/atanimation/mount.ani",
    "character/fighter/atanimation/mountpunch.ani",
    "character/fighter/",
    "character/fighter/atanimation/venommine.ani",
};
static const ClientSkillBinding k_skill_atfighter_14 = {
    14, k_motions_atfighter_14, 6, nullptr, 0, 
    "1031 client state table: states 26,27; basis eligibility pair"};
static const char *const k_motions_atfighter_17[] = {
    "character/fighter/",
};
static const ClientSkillBinding k_skill_atfighter_17 = {
    17, k_motions_atfighter_17, 1, nullptr, 0, 
    "1031 client state table: states 28; basis eligibility pair"};
static const char *const k_motions_atfighter_18[] = {
    "character/fighter/atanimation/holduphit.ani",
    "character/fighter/atanimation/jumpsuplex.ani",
    "character/fighter/atanimation/jumpsupleximpresskick.ani",
};
static const ClientSkillBinding k_skill_atfighter_18 = {
    18, k_motions_atfighter_18, 3, nullptr, 0, 
    "1031 client state table: states 22,24,25; basis eligibility pair"};
static const char *const k_motions_atfighter_19[] = {
    "character/fighter/atanimation/closepunch.ani",
};
static const ClientSkillBinding k_skill_atfighter_19 = {
    19, k_motions_atfighter_19, 1, nullptr, 0, 
    "1031 client state table: states 29; basis eligibility pair"};
static const char *const k_motions_atfighter_22[] = {
    "character/fighter/atanimation/backsuplex.ani",
    "character/fighter/atanimation/crouch.ani",
    "character/fighter/atanimation/suplex.ani",
};
static const ClientSkillBinding k_skill_atfighter_22 = {
    22, k_motions_atfighter_22, 3, nullptr, 0, 
    "1031 client state table: states 23; basis motion name"};
static const char *const k_motions_atfighter_41[] = {
    "character/fighter/atanimation/junkspinloop.ani",
};
static const ClientSkillBinding k_skill_atfighter_41 = {
    41, k_motions_atfighter_41, 1, nullptr, 0, 
    "1031 client state table: states 49,62; basis eligibility pair"};
static const char *const k_motions_atfighter_46[] = {
    "character/fighter/atanimation/junkspinwait.ani",
};
static const ClientSkillBinding k_skill_atfighter_46 = {
    46, k_motions_atfighter_46, 1, nullptr, 0, 
    "1031 client state table: states 44,48; basis eligibility pair"};
static const char *const k_motions_atfighter_49[] = {
    "character/fighter/atanimation/holduphit.ani",
    "character/fighter/atanimation/mountend.ani",
    "character/fighter/atanimation/shouldercharge.ani",
};
static const ClientSkillBinding k_skill_atfighter_49 = {
    49, k_motions_atfighter_49, 3, nullptr, 0, 
    "1031 client state table: states 22,50; basis eligibility pair"};
static const char *const k_motions_atfighter_54[] = {
    "character/fighter/atanimation/shouldertackle.ani",
};
static const ClientSkillBinding k_skill_atfighter_54 = {
    54, k_motions_atfighter_54, 1, nullptr, 0, 
    "1031 client state table: states 33; basis eligibility pair"};
static const char *const k_motions_atfighter_58[] = {
    "character/fighter/atanimation/whirlwindkick.ani",
};
static const ClientSkillBinding k_skill_atfighter_58 = {
    58, k_motions_atfighter_58, 1, nullptr, 0, 
    "1031 client state table: states 34; basis eligibility pair"};
static const char *const k_motions_atfighter_60[] = {
    "character/fighter/atanimation/blockbusterready.ani",
};
static const ClientSkillBinding k_skill_atfighter_60 = {
    60, k_motions_atfighter_60, 1, nullptr, 0, 
    "1031 client state table: states 35; basis eligibility pair"};
static const char *const k_motions_atfighter_62[] = {
    "character/fighter/atanimation/blockbusterjump.ani",
};
static const ClientSkillBinding k_skill_atfighter_62 = {
    62, k_motions_atfighter_62, 1, nullptr, 0, 
    "1031 client state table: states 36; basis eligibility pair"};
static const char *const k_motions_atfighter_63[] = {
    "character/fighter/atanimation/holduphit.ani",
    "character/fighter/atanimation/typhoonattack2.ani",
    "character/fighter/atanimation/typhoonattack3.ani",
    "character/fighter/atanimation/typhoonattackkickup.ani",
};
static const ClientSkillBinding k_skill_atfighter_63 = {
    63, k_motions_atfighter_63, 4, nullptr, 0, 
    "1031 client state table: states 22,61; basis eligibility pair"};
static const char *const k_motions_atfighter_64[] = {
    "character/fighter/atanimation/typhoongrab.ani",
    "character/fighter/atanimation/typhoonattack1.ani",
};
static const ClientSkillBinding k_skill_atfighter_64 = {
    64, k_motions_atfighter_64, 2, nullptr, 0, 
    "1031 client state table: states 40,41; basis eligibility pair"};
static const char *const k_motions_atfighter_67[] = {
    "character/fighter/atanimation/junkspinloop.ani",
};
static const ClientSkillBinding k_skill_atfighter_67 = {
    67, k_motions_atfighter_67, 1, nullptr, 0, 
    "1031 client state table: states 45,49; basis eligibility pair"};
static const char *const k_motions_atfighter_68[] = {
    "character/fighter/atanimation/legsuplexthrow.ani",
    "character/fighter/",
};
static const ClientSkillBinding k_skill_atfighter_68 = {
    68, k_motions_atfighter_68, 2, nullptr, 0, 
    "1031 client state table: states 38,42; basis eligibility pair"};
static const char *const k_motions_atfighter_71[] = {
    "character/fighter/atanimation/typhoonattack2.ani",
    "character/fighter/atanimation/typhoonattack3.ani",
    "character/fighter/atanimation/typhoonattackkickup.ani",
};
static const ClientSkillBinding k_skill_atfighter_71 = {
    71, k_motions_atfighter_71, 3, nullptr, 0, 
    "1031 client state table: states 61; basis eligibility pair"};
static const char *const k_motions_atfighter_75[] = {
    "character/fighter/atanimation/whitetigerattack3.ani",
    "character/fighter/atanimation/crouch.ani",
    "character/fighter/",
};
static const ClientSkillBinding k_skill_atfighter_75 = {
    75, k_motions_atfighter_75, 3, nullptr, 0, 
    "1031 client state table: states 44,65; basis eligibility pair"};
static const char *const k_motions_atfighter_76[] = {
    "character/fighter/atanimation/typhoonattack1.ani",
};
static const ClientSkillBinding k_skill_atfighter_76 = {
    76, k_motions_atfighter_76, 1, nullptr, 0, 
    "1031 client state table: states 41; basis eligibility pair"};
static const char *const k_motions_atfighter_77[] = {
    "character/fighter/",
};
static const ClientSkillBinding k_skill_atfighter_77 = {
    77, k_motions_atfighter_77, 1, nullptr, 0, 
    "1031 client state table: states 42,46; basis eligibility pair"};
static const char *const k_motions_atfighter_80[] = {
    "character/fighter/atanimation/flamelegscast.ani",
    "character/fighter/atanimation/whitetigerattack3.ani",
    "character/fighter/atanimation/crouch.ani",
    "character/fighter/",
};
static const ClientSkillBinding k_skill_atfighter_80 = {
    80, k_motions_atfighter_80, 4, nullptr, 0, 
    "1031 client state table: states 47,51; basis eligibility pair"};
static const char *const k_motions_atfighter_81[] = {
    "character/fighter/atanimation/junkspinwait.ani",
    "character/fighter/atanimation/whitetigerattack4.ani",
};
static const ClientSkillBinding k_skill_atfighter_81 = {
    81, k_motions_atfighter_81, 2, nullptr, 0, 
    "1031 client state table: states 48,52; basis eligibility pair"};
static const char *const k_motions_atfighter_82[] = {
    "character/fighter/atanimation/whitetigerattack5.ani",
    "character/fighter/atanimation/whitetigerdashattack.ani",
    "character/fighter/atanimation/whitetigerjumpattack.ani",
    "character/fighter/atanimation/dashpunch.ani",
};
static const ClientSkillBinding k_skill_atfighter_82 = {
    82, k_motions_atfighter_82, 4, nullptr, 0, 
    "1031 client state table: states 53; basis eligibility pair"};
static const char *const k_motions_atfighter_83[] = {
    "character/fighter/atanimation/mountend.ani",
    "character/fighter/atanimation/shouldercharge.ani",
    "character/fighter/atanimation/punchafterreturn.ani",
    "character/fighter/atanimation/randomkick1.ani",
    "character/fighter/atanimation/destroyearthskydroponsky.ani",
    "character/fighter/atanimation/destroyearthskydropfinish.ani",
};
static const ClientSkillBinding k_skill_atfighter_83 = {
    83, k_motions_atfighter_83, 6, nullptr, 0, 
    "1031 client state table: states 50,54; basis eligibility pair"};
static const char *const k_motions_atfighter_84[] = {
    "character/fighter/atanimation/whitetigerattack3.ani",
    "character/fighter/atanimation/crouch.ani",
    "character/fighter/",
    "character/fighter/atanimation/randomkick2.ani",
    "character/fighter/atanimation/randomkick3.ani",
    "character/fighter/atanimation/crashlowkick.ani",
    "character/fighter/atanimation/randomkickfinish.ani",
    "character/fighter/atanimation/risingupperdash.ani",
};
static const ClientSkillBinding k_skill_atfighter_84 = {
    84, k_motions_atfighter_84, 8, nullptr, 0, 
    "1031 client state table: states 51,55; basis eligibility pair"};
static const char *const k_motions_atfighter_86[] = {
    "character/fighter/atanimation/whitetigerattack4.ani",
    "character/fighter/atanimation/risingupper.ani",
};
static const ClientSkillBinding k_skill_atfighter_86 = {
    86, k_motions_atfighter_86, 2, nullptr, 0, 
    "1031 client state table: states 52,56; basis eligibility pair"};
static const char *const k_motions_atfighter_87[] = {
    "character/fighter/atanimation/whitetigerattack5.ani",
    "character/fighter/atanimation/whitetigerdashattack.ani",
    "character/fighter/atanimation/whitetigerjumpattack.ani",
    "character/fighter/atanimation/dashpunch.ani",
    "character/fighter/atanimation/dashafterdashcombo1.ani",
    "character/fighter/atanimation/dashafterdashcombo2.ani",
    "character/fighter/",
};
static const ClientSkillBinding k_skill_atfighter_87 = {
    87, k_motions_atfighter_87, 7, nullptr, 0, 
    "1031 client state table: states 53,57; basis eligibility pair"};
static const char *const k_motions_atfighter_88[] = {
    "character/fighter/atanimation/punchafterreturn.ani",
    "character/fighter/atanimation/randomkick1.ani",
    "character/fighter/atanimation/destroyearthskydroponsky.ani",
    "character/fighter/atanimation/destroyearthskydropfinish.ani",
    "character/fighter/",
    "character/fighter/atanimation/earthbreak.ani",
    "character/fighter/atanimation/holduptry.ani",
    "character/fighter/atanimation/holduphold.ani",
};
static const ClientSkillBinding k_skill_atfighter_88 = {
    88, k_motions_atfighter_88, 8, nullptr, 0, 
    "1031 client state table: states 54,58; basis eligibility pair"};
static const char *const k_motions_atfighter_89[] = {
    "character/fighter/atanimation/holduphit.ani",
};
static const ClientSkillBinding k_skill_atfighter_89 = {
    89, k_motions_atfighter_89, 1, nullptr, 0, 
    "1031 client state table: states 22; basis eligibility pair"};
static const char *const k_motions_atfighter_90[] = {
    "character/fighter/atanimation/risingupper.ani",
    "character/fighter/atanimation/throwsanddouble.ani",
};
static const ClientSkillBinding k_skill_atfighter_90 = {
    90, k_motions_atfighter_90, 2, nullptr, 0, 
    "1031 client state table: states 56,60; basis eligibility pair"};
static const char *const k_motions_atfighter_101[] = {
    "character/fighter/atanimation/blockbusterjump.ani",
};
static const ClientSkillBinding k_skill_atfighter_101 = {
    101, k_motions_atfighter_101, 1, nullptr, 0, 
    "1031 client state table: states 63; basis eligibility pair"};
static const char *const k_motions_atfighter_102[] = {
    "character/fighter/atanimation/whitetigerattack3.ani",
    "character/fighter/atanimation/crouch.ani",
    "character/fighter/",
};
static const ClientSkillBinding k_skill_atfighter_102 = {
    102, k_motions_atfighter_102, 3, nullptr, 0, 
    "1031 client state table: states 65; basis eligibility pair"};
static const char *const k_motions_atfighter_103[] = {
    "character/fighter/atanimation/destroyearthskydropstart.ani",
    "character/fighter/atanimation/randomkick1.ani",
};
static const ClientSkillBinding k_skill_atfighter_103 = {
    103, k_motions_atfighter_103, 2, nullptr, 0, 
    "1031 client state table: states 66; basis eligibility pair"};
static const char *const k_motions_atfighter_104[] = {
    "character/fighter/",
};
static const ClientSkillBinding k_skill_atfighter_104 = {
    104, k_motions_atfighter_104, 1, nullptr, 0, 
    "1031 client state table: states 67; basis eligibility pair"};
static const char *const k_motions_atfighter_105[] = {
    "character/fighter/atanimation/throwsanddouble.ani",
    "character/fighter/atanimation/wildcannonspikecharge.ani",
    "character/fighter/",
    "character/fighter/atanimation/throwsand.ani",
};
static const ClientSkillBinding k_skill_atfighter_105 = {
    105, k_motions_atfighter_105, 4, nullptr, 0, 
    "1031 client state table: states 60,68; basis eligibility pair"};
static const char *const k_motions_atfighter_106[] = {
    "character/fighter/",
    "character/fighter/atanimation/earthbreak.ani",
    "character/fighter/atanimation/holduptry.ani",
    "character/fighter/atanimation/holduphold.ani",
};
static const ClientSkillBinding k_skill_atfighter_106 = {
    106, k_motions_atfighter_106, 4, nullptr, 0, 
    "1031 client state table: states 58,69; basis eligibility pair"};
static const char *const k_motions_atfighter_108[] = {
    "character/fighter/atanimation/wildcannonspikecharge.ani",
    "character/fighter/atanimation/wildcannonspikefall.ani",
    "character/fighter/atanimation/throwsand.ani",
};
static const ClientSkillBinding k_skill_atfighter_108 = {
    108, k_motions_atfighter_108, 3, nullptr, 0, 
    "1031 client state table: states 59; basis eligibility pair"};
static const char *const k_motions_atfighter_111[] = {
    "character/fighter/atanimation/whitetigerattack3.ani",
    "character/fighter/atanimation/crouch.ani",
    "character/fighter/",
};
static const ClientSkillBinding k_skill_atfighter_111 = {
    111, k_motions_atfighter_111, 3, nullptr, 0, 
    "1031 client state table: states 65; basis eligibility pair"};
static const char *const k_motions_atfighter_117[] = {
    "character/fighter/atanimation/destroyearthskydropstart.ani",
    "character/fighter/atanimation/randomkick1.ani",
};
static const ClientSkillBinding k_skill_atfighter_117 = {
    117, k_motions_atfighter_117, 2, nullptr, 0, 
    "1031 client state table: states 66; basis eligibility pair"};
static const char *const k_motions_atfighter_120[] = {
    "character/fighter/atanimation/crazymountstart.ani",
};
static const ClientSkillBinding k_skill_atfighter_120 = {
    120, k_motions_atfighter_120, 1, nullptr, 0, 
    "1031 client state table: states 70; basis eligibility pair"};
static const char *const k_motions_atfighter_122[] = {
    "character/fighter/",
};
static const ClientSkillBinding k_skill_atfighter_122 = {
    122, k_motions_atfighter_122, 1, nullptr, 0, 
    "1031 client state table: states 67; basis eligibility pair"};
static const char *const k_motions_atfighter_123[] = {
    "character/fighter/atanimation/wildcannonspikecharge.ani",
    "character/fighter/",
    "character/fighter/atanimation/throwsand.ani",
};
static const ClientSkillBinding k_skill_atfighter_123 = {
    123, k_motions_atfighter_123, 3, nullptr, 0, 
    "1031 client state table: states 68; basis eligibility pair"};
static const char *const k_motions_atfighter_135[] = {
    "character/fighter/atanimation/junkspinloop.ani",
};
static const ClientSkillBinding k_skill_atfighter_135 = {
    135, k_motions_atfighter_135, 1, nullptr, 0, 
    "1031 client state table: states 49; basis eligibility pair"};
static const char *const k_motions_atfighter_139[] = {
    "character/fighter/atanimation/punchafterreturn.ani",
    "character/fighter/atanimation/randomkick1.ani",
    "character/fighter/atanimation/destroyearthskydroponsky.ani",
    "character/fighter/atanimation/destroyearthskydropfinish.ani",
};
static const ClientSkillBinding k_skill_atfighter_139 = {
    139, k_motions_atfighter_139, 4, nullptr, 0, 
    "1031 client state table: states 54; basis eligibility pair"};

static const char *const k_motions_gunner_1[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
    "character/gunner/animation/aerialknee.ani",
    "character/gunner/animation/setrobot.ani",
    "character/gunner/animation/reloadinhand.ani",
};
static const ClientSkillBinding k_skill_gunner_1 = {
    1, k_motions_gunner_1, 6, nullptr, 0, 
    "1031 client state table: states 17,20,26,29,32; basis eligibility pair"};
static const char *const k_motions_gunner_3[] = {
    "character/gunner/animation/windmillroll.ani",
    "character/gunner/animation/treadshoot.ani",
    "character/gunner/",
};
static const ClientSkillBinding k_skill_gunner_3 = {
    3, k_motions_gunner_3, 3, nullptr, 0, 
    "1031 client state table: states 19,22,52; basis eligibility pair"};
static const char *const k_motions_gunner_4[] = {
    "character/gunner/animation/aerialknee.ani",
};
static const ClientSkillBinding k_skill_gunner_4 = {
    4, k_motions_gunner_4, 1, nullptr, 0, 
    "1031 client state table: states 20; basis eligibility pair"};
static const char *const k_motions_gunner_6[] = {
    "character/gunner/animation/trytread.ani",
    "character/gunner/animation/treadshoot.ani",
    "character/gunner/",
};
static const ClientSkillBinding k_skill_gunner_6 = {
    6, k_motions_gunner_6, 3, nullptr, 0, 
    "1031 client state table: states 21,22,53; basis eligibility pair"};
static const char *const k_motions_gunner_7[] = {
    "character/gunner/animation/fastknee.ani",
    "character/gunner/",
};
static const ClientSkillBinding k_skill_gunner_7 = {
    7, k_motions_gunner_7, 2, nullptr, 0, 
    "1031 client state table: states 23,42; basis eligibility pair"};
static const char *const k_motions_gunner_9[] = {
    "character/gunner/animation/randomshoot.ani",
};
static const ClientSkillBinding k_skill_gunner_9 = {
    9, k_motions_gunner_9, 1, nullptr, 0, 
    "1031 client state table: states 24; basis eligibility pair"};
static const char *const k_motions_gunner_10[] = {
    "character/gunner/animation/bulletguard.ani",
};
static const ClientSkillBinding k_skill_gunner_10 = {
    10, k_motions_gunner_10, 1, nullptr, 0, 
    "1031 client state table: states 25; basis eligibility pair"};
static const char *const k_motions_gunner_11[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_11 = {
    11, k_motions_gunner_11, 3, nullptr, 0, 
    "1031 client state table: states 28; basis eligibility pair"};
static const char *const k_motions_gunner_15[] = {
    "character/gunner/animation/walkshootreadystay.ani",
};
static const ClientSkillBinding k_skill_gunner_15 = {
    15, k_motions_gunner_15, 1, nullptr, 0, 
    "1031 client state table: states 27; basis eligibility pair"};
static const char *const k_motions_gunner_20[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_20 = {
    20, k_motions_gunner_20, 3, nullptr, 0, 
    "1031 client state table: states 28; basis eligibility pair"};
static const char *const k_motions_gunner_26[] = {
    "character/gunner/animation/countershootready.ani",
    "character/gunner/animation/countershootshoot.ani",
};
static const ClientSkillBinding k_skill_gunner_26 = {
    26, k_motions_gunner_26, 2, nullptr, 0, 
    "1031 client state table: states 40; basis eligibility pair"};
static const char *const k_motions_gunner_43[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_43 = {
    43, k_motions_gunner_43, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_gunner_47[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_47 = {
    47, k_motions_gunner_47, 3, nullptr, 0, 
    "1031 client state table: states 13,28; basis eligibility pair"};
static const char *const k_motions_gunner_48[] = {
    "character/gunner/animation/crossshoot.ani",
};
static const ClientSkillBinding k_skill_gunner_48 = {
    48, k_motions_gunner_48, 1, nullptr, 0, 
    "1031 client state table: states 31; basis eligibility pair"};
static const char *const k_motions_gunner_50[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_50 = {
    50, k_motions_gunner_50, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_gunner_51[] = {
    "character/gunner/animation/doublegunhawkthrow.ani",
    "character/gunner/animation/doublegunhawkcatch.ani",
};
static const ClientSkillBinding k_skill_gunner_51 = {
    51, k_motions_gunner_51, 2, nullptr, 0, 
    "1031 client state table: states 41; basis eligibility pair"};
static const char *const k_motions_gunner_53[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_53 = {
    53, k_motions_gunner_53, 3, nullptr, 0, 
    "1031 client state table: states 28; basis eligibility pair"};
static const char *const k_motions_gunner_59[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_59 = {
    59, k_motions_gunner_59, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_gunner_64[] = {
    "character/gunner/animation/desperadoready1.ani",
    "character/gunner/animation/desperadoready2.ani",
    "character/gunner/animation/desperadoready3.ani",
    "character/gunner/animation/desperadoaerial.ani",
    "character/gunner/animation/desperadoland.ani",
    "character/gunner/animation/desperadofinish.ani",
};
static const ClientSkillBinding k_skill_gunner_64 = {
    64, k_motions_gunner_64, 6, nullptr, 0, 
    "1031 client state table: states 33; basis eligibility pair"};
static const char *const k_motions_gunner_67[] = {
    "character/gunner/animation/gaebolgpunch.ani",
};
static const ClientSkillBinding k_skill_gunner_67 = {
    67, k_motions_gunner_67, 1, nullptr, 0, 
    "1031 client state table: states 34; basis eligibility pair"};
static const char *const k_motions_gunner_70[] = {
    "character/gunner/animation/desperadoready1.ani",
    "character/gunner/animation/desperadoready2.ani",
    "character/gunner/animation/desperadoready3.ani",
    "character/gunner/animation/desperadoaerial.ani",
    "character/gunner/animation/desperadoland.ani",
    "character/gunner/animation/desperadofinish.ani",
    "character/gunner/animation/blackrose.ani",
};
static const ClientSkillBinding k_skill_gunner_70 = {
    70, k_motions_gunner_70, 7, nullptr, 0, 
    "1031 client state table: states 33,35; basis eligibility pair"};
static const char *const k_motions_gunner_71[] = {
    "character/gunner/animation/extruderready.ani",
    "character/gunner/animation/extrudercharge.ani",
    "character/gunner/animation/extrudershoot.ani",
};
static const ClientSkillBinding k_skill_gunner_71 = {
    71, k_motions_gunner_71, 3, nullptr, 0, 
    "1031 client state table: states 36; basis eligibility pair"};
static const char *const k_motions_gunner_72[] = {
    "character/gunner/animation/multiheadshotready.ani",
    "character/gunner/animation/multiheadshotfinish.ani",
};
static const ClientSkillBinding k_skill_gunner_72 = {
    72, k_motions_gunner_72, 2, nullptr, 0, 
    "1031 client state table: states 37; basis eligibility pair"};
static const char *const k_motions_gunner_73[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_73 = {
    73, k_motions_gunner_73, 3, nullptr, 0, 
    "1031 client state table: states 28; basis eligibility pair"};
static const char *const k_motions_gunner_77[] = {
    "character/gunner/animation/c4remoteready.ani",
};
static const ClientSkillBinding k_skill_gunner_77 = {
    77, k_motions_gunner_77, 1, nullptr, 0, 
    "1031 client state table: states 39; basis motion name"};
static const char *const k_motions_gunner_79[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_79 = {
    79, k_motions_gunner_79, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_gunner_80[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_80 = {
    80, k_motions_gunner_80, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_gunner_81[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_81 = {
    81, k_motions_gunner_81, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_gunner_82[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_82 = {
    82, k_motions_gunner_82, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_gunner_83[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_83 = {
    83, k_motions_gunner_83, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_gunner_96[] = {
    "character/gunner/",
};
static const ClientSkillBinding k_skill_gunner_96 = {
    96, k_motions_gunner_96, 1, nullptr, 0, 
    "1031 client state table: states 43; basis eligibility pair"};
static const char *const k_motions_gunner_97[] = {
    "character/gunner/",
};
static const ClientSkillBinding k_skill_gunner_97 = {
    97, k_motions_gunner_97, 1, nullptr, 0, 
    "1031 client state table: states 6,44; basis eligibility pair"};
static const char *const k_motions_gunner_98[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_98 = {
    98, k_motions_gunner_98, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_gunner_100[] = {
    "character/gunner/",
};
static const ClientSkillBinding k_skill_gunner_100 = {
    100, k_motions_gunner_100, 1, nullptr, 0, 
    "1031 client state table: states 6,45,46,47,48,49 (+3 more); basis eligibility pair"};
static const char *const k_motions_gunner_102[] = {
    "character/gunner/animation/attack1shootup.ani",
    "character/gunner/animation/attack2shootdown.ani",
    "character/gunner/animation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_gunner_102 = {
    102, k_motions_gunner_102, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_gunner_104[] = {
    "character/gunner/animation/multiheadshotready.ani",
    "character/gunner/animation/multiheadshotfinish.ani",
};
static const ClientSkillBinding k_skill_gunner_104 = {
    104, k_motions_gunner_104, 2, nullptr, 0, 
    "1031 client state table: states 58; basis eligibility pair"};
static const char *const k_motions_gunner_109[] = {
    "character/gunner/animation/chargebustercharge.ani",
};
static const ClientSkillBinding k_skill_gunner_109 = {
    109, k_motions_gunner_109, 1, nullptr, 0, 
    "1031 client state table: states 59; basis eligibility pair"};
static const char *const k_motions_gunner_164[] = {
    "character/gunner/animation/countershootready.ani",
    "character/gunner/animation/countershootshoot.ani",
};
static const ClientSkillBinding k_skill_gunner_164 = {
    164, k_motions_gunner_164, 2, nullptr, 0, 
    "1031 client state table: states 40; basis eligibility pair"};

static const char *const k_motions_atgunner_1[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
    "character/gunner/atanimation/aerialknee.ani",
    "character/gunner/atanimation/setrobot.ani",
    "character/gunner/atanimation/reloadinhand.ani",
};
static const ClientSkillBinding k_skill_atgunner_1 = {
    1, k_motions_atgunner_1, 6, nullptr, 0, 
    "1031 client state table: states 17,20,26,29,32; basis eligibility pair"};
static const char *const k_motions_atgunner_3[] = {
    "character/gunner/atanimation/windmillroll.ani",
    "character/gunner/atanimation/treadshoot.ani",
    "character/gunner/atanimation/twingunbladesumersault1.ani",
    "character/gunner/atanimation/twingunbladesumersault2.ani",
};
static const ClientSkillBinding k_skill_atgunner_3 = {
    3, k_motions_atgunner_3, 4, nullptr, 0, 
    "1031 client state table: states 19,22,52; basis eligibility pair"};
static const char *const k_motions_atgunner_4[] = {
    "character/gunner/atanimation/aerialknee.ani",
};
static const ClientSkillBinding k_skill_atgunner_4 = {
    4, k_motions_atgunner_4, 1, nullptr, 0, 
    "1031 client state table: states 20; basis eligibility pair"};
static const char *const k_motions_atgunner_6[] = {
    "character/gunner/atanimation/trytread.ani",
    "character/gunner/atanimation/treadshoot.ani",
    "character/gunner/atanimation/twingunbladethrowgun1.ani",
    "character/gunner/atanimation/twingunbladethrowgun2.ani",
};
static const ClientSkillBinding k_skill_atgunner_6 = {
    6, k_motions_atgunner_6, 4, nullptr, 0, 
    "1031 client state table: states 21,22,53; basis eligibility pair"};
static const char *const k_motions_atgunner_7[] = {
    "character/gunner/atanimation/fastknee.ani",
    "character/gunner/atanimation/grenadeair.ani",
};
static const ClientSkillBinding k_skill_atgunner_7 = {
    7, k_motions_atgunner_7, 2, nullptr, 0, 
    "1031 client state table: states 23,42; basis eligibility pair"};
static const char *const k_motions_atgunner_9[] = {
    "character/gunner/atanimation/randomshoot.ani",
};
static const ClientSkillBinding k_skill_atgunner_9 = {
    9, k_motions_atgunner_9, 1, nullptr, 0, 
    "1031 client state table: states 24; basis eligibility pair"};
static const char *const k_motions_atgunner_10[] = {
    "character/gunner/atanimation/bulletguard.ani",
};
static const ClientSkillBinding k_skill_atgunner_10 = {
    10, k_motions_atgunner_10, 1, nullptr, 0, 
    "1031 client state table: states 25; basis eligibility pair"};
static const char *const k_motions_atgunner_11[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_11 = {
    11, k_motions_atgunner_11, 3, nullptr, 0, 
    "1031 client state table: states 28; basis eligibility pair"};
static const char *const k_motions_atgunner_15[] = {
    "character/gunner/atanimation/walkshootreadystay.ani",
};
static const ClientSkillBinding k_skill_atgunner_15 = {
    15, k_motions_atgunner_15, 1, nullptr, 0, 
    "1031 client state table: states 27; basis eligibility pair"};
static const char *const k_motions_atgunner_20[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_20 = {
    20, k_motions_atgunner_20, 3, nullptr, 0, 
    "1031 client state table: states 28; basis eligibility pair"};
static const char *const k_motions_atgunner_26[] = {
    "character/gunner/atanimation/countershootready.ani",
    "character/gunner/atanimation/countershootshoot.ani",
};
static const ClientSkillBinding k_skill_atgunner_26 = {
    26, k_motions_atgunner_26, 2, nullptr, 0, 
    "1031 client state table: states 40; basis eligibility pair"};
static const char *const k_motions_atgunner_43[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_43 = {
    43, k_motions_atgunner_43, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_atgunner_47[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_47 = {
    47, k_motions_atgunner_47, 3, nullptr, 0, 
    "1031 client state table: states 13,28; basis eligibility pair"};
static const char *const k_motions_atgunner_48[] = {
    "character/gunner/atanimation/crossshoot.ani",
};
static const ClientSkillBinding k_skill_atgunner_48 = {
    48, k_motions_atgunner_48, 1, nullptr, 0, 
    "1031 client state table: states 31; basis eligibility pair"};
static const char *const k_motions_atgunner_50[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_50 = {
    50, k_motions_atgunner_50, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_atgunner_51[] = {
    "character/gunner/atanimation/doublegunhawkthrow.ani",
    "character/gunner/atanimation/doublegunhawkcatch.ani",
};
static const ClientSkillBinding k_skill_atgunner_51 = {
    51, k_motions_atgunner_51, 2, nullptr, 0, 
    "1031 client state table: states 41; basis eligibility pair"};
static const char *const k_motions_atgunner_53[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_53 = {
    53, k_motions_atgunner_53, 3, nullptr, 0, 
    "1031 client state table: states 28; basis eligibility pair"};
static const char *const k_motions_atgunner_59[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_59 = {
    59, k_motions_atgunner_59, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_atgunner_64[] = {
    "character/gunner/",
};
static const ClientSkillBinding k_skill_atgunner_64 = {
    64, k_motions_atgunner_64, 1, nullptr, 0, 
    "1031 client state table: states 33; basis eligibility pair"};
static const char *const k_motions_atgunner_67[] = {
    "character/gunner/",
};
static const ClientSkillBinding k_skill_atgunner_67 = {
    67, k_motions_atgunner_67, 1, nullptr, 0, 
    "1031 client state table: states 34; basis eligibility pair"};
static const char *const k_motions_atgunner_70[] = {
    "character/gunner/",
};
static const ClientSkillBinding k_skill_atgunner_70 = {
    70, k_motions_atgunner_70, 1, nullptr, 0, 
    "1031 client state table: states 33,35; basis eligibility pair"};
static const char *const k_motions_atgunner_71[] = {
    "character/gunner/atanimation/extruderready.ani",
    "character/gunner/atanimation/extrudercharge.ani",
    "character/gunner/atanimation/extrudershoot.ani",
};
static const ClientSkillBinding k_skill_atgunner_71 = {
    71, k_motions_atgunner_71, 3, nullptr, 0, 
    "1031 client state table: states 36; basis eligibility pair"};
static const char *const k_motions_atgunner_72[] = {
    "character/gunner/atanimation/multiheadshotready.ani",
    "character/gunner/atanimation/multiheadshotfinish.ani",
};
static const ClientSkillBinding k_skill_atgunner_72 = {
    72, k_motions_atgunner_72, 2, nullptr, 0, 
    "1031 client state table: states 37; basis eligibility pair"};
static const char *const k_motions_atgunner_73[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_73 = {
    73, k_motions_atgunner_73, 3, nullptr, 0, 
    "1031 client state table: states 28; basis eligibility pair"};
static const char *const k_motions_atgunner_77[] = {
    "character/gunner/atanimation/c4remoteready.ani",
};
static const ClientSkillBinding k_skill_atgunner_77 = {
    77, k_motions_atgunner_77, 1, nullptr, 0, 
    "1031 client state table: states 39; basis motion name"};
static const char *const k_motions_atgunner_79[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_79 = {
    79, k_motions_atgunner_79, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_atgunner_80[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_80 = {
    80, k_motions_atgunner_80, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_atgunner_81[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_81 = {
    81, k_motions_atgunner_81, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_atgunner_82[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_82 = {
    82, k_motions_atgunner_82, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_atgunner_83[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_83 = {
    83, k_motions_atgunner_83, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_atgunner_96[] = {
    "character/gunner/atanimation/g0cast.ani",
    "character/gunner/atanimation/g0lockon.ani",
};
static const ClientSkillBinding k_skill_atgunner_96 = {
    96, k_motions_atgunner_96, 2, nullptr, 0, 
    "1031 client state table: states 43; basis eligibility pair"};
static const char *const k_motions_atgunner_97[] = {
    "character/gunner/atanimation/ancienttriggerready.ani",
    "character/gunner/atanimation/ancienttriggerride.ani",
};
static const ClientSkillBinding k_skill_atgunner_97 = {
    97, k_motions_atgunner_97, 2, nullptr, 0, 
    "1031 client state table: states 6,44; basis eligibility pair"};
static const char *const k_motions_atgunner_98[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_98 = {
    98, k_motions_atgunner_98, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_atgunner_100[] = {
    "character/gunner/atanimation/twingunbladestart.ani",
    "character/gunner/atanimation/twingunbladedashattackknife.ani",
    "character/gunner/atanimation/twingunbladejumpattackknife.ani",
    "character/gunner/atanimation/twingunbladeattackgunreadystay.ani",
    "character/gunner/atanimation/twingunbladeattackgunfinish.ani",
    "character/gunner/atanimation/twingunbladejumpattackgun.ani",
    "character/gunner/atanimation/twingunbladesumersault1.ani",
    "character/gunner/atanimation/twingunbladesumersault2.ani",
    "character/gunner/atanimation/twingunbladethrowgun1.ani",
    "character/gunner/atanimation/twingunbladethrowgun2.ani",
    "character/gunner/atanimation/twingunbladefinishstart.ani",
    "character/gunner/atanimation/twingunbladefinishrapid.ani",
    "character/gunner/atanimation/twingunbladefinishfinal.ani",
};
static const ClientSkillBinding k_skill_atgunner_100 = {
    100, k_motions_atgunner_100, 13, nullptr, 0, 
    "1031 client state table: states 6,45,46,47,48,49 (+4 more); basis eligibility pair"};
static const char *const k_motions_atgunner_102[] = {
    "character/gunner/atanimation/attack1shootup.ani",
    "character/gunner/atanimation/attack2shootdown.ani",
    "character/gunner/atanimation/attack2shootup.ani",
};
static const ClientSkillBinding k_skill_atgunner_102 = {
    102, k_motions_atgunner_102, 3, nullptr, 0, 
    "1031 client state table: states 13; basis eligibility pair"};
static const char *const k_motions_atgunner_104[] = {
    "character/gunner/atanimation/multiheadshotready.ani",
    "character/gunner/atanimation/multiheadshotfinish.ani",
};
static const ClientSkillBinding k_skill_atgunner_104 = {
    104, k_motions_atgunner_104, 2, nullptr, 0, 
    "1031 client state table: states 58; basis eligibility pair"};
static const char *const k_motions_atgunner_109[] = {
    "character/gunner/atanimation/chargebustercharge.ani",
};
static const ClientSkillBinding k_skill_atgunner_109 = {
    109, k_motions_atgunner_109, 1, nullptr, 0, 
    "1031 client state table: states 59; basis eligibility pair"};
static const char *const k_motions_atgunner_164[] = {
    "character/gunner/atanimation/countershootready.ani",
    "character/gunner/atanimation/countershootshoot.ani",
};
static const ClientSkillBinding k_skill_atgunner_164 = {
    164, k_motions_atgunner_164, 2, nullptr, 0, 
    "1031 client state table: states 40; basis eligibility pair"};

static const char *const k_motions_mage_4[] = {
    "character/mage/animation/thrust.ani",
    "character/mage/animation/powderthrust.ani",
};
static const ClientSkillBinding k_skill_mage_4 = {
    4, k_motions_mage_4, 2, nullptr, 0, 
    "1031 client state table: states 22; basis eligibility pair"};
static const char *const k_motions_mage_10[] = {
    "character/mage/animation/chasersexplosion.ani",
    "character/mage/animation/randompiercestriketry.ani",
    "character/mage/animation/randompiercestrikeloopex.ani",
    "character/mage/animation/randompiercestrikechargeex.ani",
    "character/mage/animation/randompiercestrikefinishex.ani",
};
static const ClientSkillBinding k_skill_mage_10 = {
    10, k_motions_mage_10, 5, nullptr, 0, 
    "1031 client state table: states 28,47; basis eligibility pair"};
static const char *const k_motions_mage_12[] = {
    "character/mage/animation/upperswing.ani",
    "character/mage/animation/powderupperswing.ani",
};
static const ClientSkillBinding k_skill_mage_12 = {
    12, k_motions_mage_12, 2, nullptr, 0, 
    "1031 client state table: states 23; basis eligibility pair"};
static const char *const k_motions_mage_13[] = {
    "character/mage/animation/swing.ani",
    "character/mage/animation/swingex.ani",
    "character/mage/animation/whip.ani",
};
static const ClientSkillBinding k_skill_mage_13 = {
    13, k_motions_mage_13, 3, nullptr, 0, 
    "1031 client state table: states 24; basis eligibility pair"};
static const char *const k_motions_mage_14[] = {
    "character/mage/animation/handstrike.ani",
    "character/mage/animation/strengthhandstrike.ani",
    "character/mage/animation/strengthhandstrikereturn.ani",
};
static const ClientSkillBinding k_skill_mage_14 = {
    14, k_motions_mage_14, 3, nullptr, 0, 
    "1031 client state table: states 25; basis eligibility pair"};
static const char *const k_motions_mage_20[] = {
    "character/mage/animation/swing.ani",
    "character/mage/animation/swingex.ani",
    "character/mage/animation/whip.ani",
};
static const ClientSkillBinding k_skill_mage_20 = {
    20, k_motions_mage_20, 3, nullptr, 0, 
    "1031 client state table: states 24; basis eligibility pair"};
static const char *const k_motions_mage_65[] = {
    "character/mage/animation/pokethrowtry.ani",
    "character/mage/animation/pokethrowsmash.ani",
};
static const ClientSkillBinding k_skill_mage_65 = {
    65, k_motions_mage_65, 2, nullptr, 0, 
    "1031 client state table: states 26; basis eligibility pair"};
static const char *const k_motions_mage_66[] = {
    "character/mage/animation/randompiercestriketry.ani",
    "character/mage/animation/randompiercestrikeloop.ani",
    "character/mage/animation/randompiercestrikefinish.ani",
};
static const ClientSkillBinding k_skill_mage_66 = {
    66, k_motions_mage_66, 3, nullptr, 0, 
    "1031 client state table: states 27; basis eligibility pair"};
static const char *const k_motions_mage_68[] = {
    "character/mage/animation/handstrike.ani",
    "character/mage/animation/strengthhandstrike.ani",
    "character/mage/animation/strengthhandstrikereturn.ani",
};
static const ClientSkillBinding k_skill_mage_68 = {
    68, k_motions_mage_68, 3, nullptr, 0, 
    "1031 client state table: states 25; basis eligibility pair"};
static const char *const k_motions_mage_69[] = {
    "character/mage/animation/dragonspear.ani",
};
static const ClientSkillBinding k_skill_mage_69 = {
    69, k_motions_mage_69, 1, nullptr, 0, 
    "1031 client state table: states 29; basis eligibility pair"};
static const char *const k_motions_mage_83[] = {
    "character/mage/animation/changebellatrixcast.ani",
    "character/mage/animation/changebellatrixup.ani",
    "character/mage/animation/returnbellatrix.ani",
};
static const ClientSkillBinding k_skill_mage_83 = {
    83, k_motions_mage_83, 3, nullptr, 0, 
    "1031 client state table: states 31,32,33,34; basis eligibility pair"};
static const char *const k_motions_mage_86[] = {
    "character/mage/animation/broomspinready.ani",
    "character/mage/animation/broomspinattack.ani",
    "character/mage/animation/broomspinexfinishready.ani",
    "character/mage/animation/broomspintumble.ani",
};
static const ClientSkillBinding k_skill_mage_86 = {
    86, k_motions_mage_86, 4, nullptr, 0, 
    "1031 client state table: states 48; basis eligibility pair"};
static const char *const k_motions_mage_92[] = {
    "character/mage/animation/blackmantle.ani",
};
static const ClientSkillBinding k_skill_mage_92 = {
    92, k_motions_mage_92, 1, nullptr, 0, 
    "1031 client state table: states 35; basis eligibility pair"};
static const char *const k_motions_mage_98[] = {
    "character/mage/animation/broomspinready.ani",
    "character/mage/animation/broomspinattack.ani",
    "character/mage/animation/broomspintumble.ani",
};
static const ClientSkillBinding k_skill_mage_98 = {
    98, k_motions_mage_98, 3, nullptr, 0, 
    "1031 client state table: states 37; basis eligibility pair"};
static const char *const k_motions_mage_103[] = {
    "character/mage/animation/antigravitystarter.ani",
};
static const ClientSkillBinding k_skill_mage_103 = {
    103, k_motions_mage_103, 1, nullptr, 0, 
    "1031 client state table: states 39; basis eligibility pair"};
static const char *const k_motions_mage_104[] = {
    "character/mage/animation/megadrillgreat.ani",
    "character/mage/animation/megadrillsuccess.ani",
};
static const ClientSkillBinding k_skill_mage_104 = {
    104, k_motions_mage_104, 2, nullptr, 0, 
    "1031 client state table: states 40; basis motion name"};
static const char *const k_motions_mage_105[] = {
    "character/mage/animation/fluorecollidercast.ani",
    "character/mage/animation/fluorecolliderappear.ani",
};
static const ClientSkillBinding k_skill_mage_105 = {
    105, k_motions_mage_105, 2, nullptr, 0, 
    "1031 client state table: states 41; basis eligibility pair"};
static const char *const k_motions_mage_106[] = {
    "character/mage/animation/heatingfurnacecast.ani",
};
static const ClientSkillBinding k_skill_mage_106 = {
    106, k_motions_mage_106, 1, nullptr, 0, 
    "1031 client state table: states 43; basis eligibility pair"};
static const char *const k_motions_mage_111[] = {
    "character/mage/animation/walloficeex.ani",
    "character/mage/animation/walloficeexfinish.ani",
};
static const ClientSkillBinding k_skill_mage_111 = {
    111, k_motions_mage_111, 2, nullptr, 0, 
    "1031 client state table: states 46; basis eligibility pair"};
static const char *const k_motions_mage_112[] = {
    "character/mage/animation/randompiercestriketry.ani",
    "character/mage/animation/randompiercestrikeloop.ani",
    "character/mage/animation/randompiercestrikefinish.ani",
    "character/mage/animation/randompiercestrikeloopex.ani",
    "character/mage/animation/randompiercestrikechargeex.ani",
    "character/mage/animation/randompiercestrikefinishex.ani",
};
static const ClientSkillBinding k_skill_mage_112 = {
    112, k_motions_mage_112, 6, nullptr, 0, 
    "1031 client state table: states 27,47; basis eligibility pair"};
static const char *const k_motions_mage_114[] = {
    "character/mage/animation/broomspinready.ani",
    "character/mage/animation/broomspinattack.ani",
    "character/mage/animation/broomspintumble.ani",
    "character/mage/animation/broomspinexfinishready.ani",
};
static const ClientSkillBinding k_skill_mage_114 = {
    114, k_motions_mage_114, 4, nullptr, 0, 
    "1031 client state table: states 37,48; basis eligibility pair"};

static const char *const k_motions_priest_1[] = {
    "character/priest/animation/antiairupper.ani",
};
static const ClientSkillBinding k_skill_priest_1 = {
    1, k_motions_priest_1, 1, nullptr, 0, 
    "1031 client state table: states 17; basis eligibility pair"};
static const char *const k_motions_priest_3[] = {
    "character/priest/animation/sway.ani",
};
static const ClientSkillBinding k_skill_priest_3 = {
    3, k_motions_priest_3, 1, nullptr, 0, 
    "1031 client state table: states 19; basis eligibility pair"};
static const char *const k_motions_priest_4[] = {
    "character/priest/animation/hurricanerollhook.ani",
    "character/priest/animation/hurricanerollupper.ani",
};
static const ClientSkillBinding k_skill_priest_4 = {
    4, k_motions_priest_4, 2, nullptr, 0, 
    "1031 client state table: states 34; basis motion name"};
static const char *const k_motions_priest_8[] = {
    "character/priest/animation/smashertrygrab.ani",
    "character/priest/animation/smashersuccessgrab.ani",
    "character/priest/animation/smasherdash.ani",
};
static const ClientSkillBinding k_skill_priest_8 = {
    8, k_motions_priest_8, 3, nullptr, 0, 
    "1031 client state table: states 22; basis eligibility pair"};
static const char *const k_motions_priest_11[] = {
    "character/priest/animation/quakearea.ani",
};
static const ClientSkillBinding k_skill_priest_11 = {
    11, k_motions_priest_11, 1, nullptr, 0, 
    "1031 client state table: states 23; basis motion name"};
static const char *const k_motions_priest_26[] = {
    "character/priest/animation/healwindcast.ani",
    "character/priest/animation/jumppunch.ani",
    "character/priest/animation/healwindblast.ani",
};
static const ClientSkillBinding k_skill_priest_26 = {
    26, k_motions_priest_26, 3, nullptr, 0, 
    "1031 client state table: states 49; basis motion name"};
static const char *const k_motions_priest_27[] = {
    "character/priest/animation/deflectwall.ani",
};
static const ClientSkillBinding k_skill_priest_27 = {
    27, k_motions_priest_27, 1, nullptr, 0, 
    "1031 client state table: states 36; basis motion name"};
static const char *const k_motions_priest_30[] = {
    "character/priest/animation/holycounterpray.ani",
};
static const ClientSkillBinding k_skill_priest_30 = {
    30, k_motions_priest_30, 1, nullptr, 0, 
    "1031 client state table: states 28; basis motion name"};
static const char *const k_motions_priest_31[] = {
    "character/priest/animation/gorgeouscombination.ani",
};
static const ClientSkillBinding k_skill_priest_31 = {
    31, k_motions_priest_31, 1, nullptr, 0, 
    "1031 client state table: states 29; basis motion name"};
static const char *const k_motions_priest_33[] = {
    "character/priest/animation/choppinghammer.ani",
};
static const ClientSkillBinding k_skill_priest_33 = {
    33, k_motions_priest_33, 1, nullptr, 0, 
    "1031 client state table: states 30; basis motion name"};
static const char *const k_motions_priest_37[] = {
    "character/priest/animation/hurricaneofjudgement2.ani",
    "character/priest/animation/hurricaneofjudgement.ani",
};
static const ClientSkillBinding k_skill_priest_37 = {
    37, k_motions_priest_37, 2, nullptr, 0, 
    "1031 client state table: states 31; basis motion name"};
static const char *const k_motions_priest_41[] = {
    "character/priest/animation/homerungrab.ani",
    "character/priest/animation/homerunsmash.ani",
};
static const ClientSkillBinding k_skill_priest_41 = {
    41, k_motions_priest_41, 2, nullptr, 0, 
    "1031 client state table: states 32; basis motion name"};
static const char *const k_motions_priest_43[] = {
    "character/priest/animation/bladeofpurewhite.ani",
};
static const ClientSkillBinding k_skill_priest_43 = {
    43, k_motions_priest_43, 1, nullptr, 0, 
    "1031 client state table: states 33; basis motion name"};
static const char *const k_motions_priest_50[] = {
    "character/priest/animation/throwweaponready.ani",
    "character/priest/animation/throwweaponswing.ani",
    "character/priest/animation/throwweaponthrow.ani",
};
static const ClientSkillBinding k_skill_priest_50 = {
    50, k_motions_priest_50, 3, nullptr, 0, 
    "1031 client state table: states 35; basis motion name"};
static const char *const k_motions_priest_61[] = {
    "character/priest/animation/luckystraight.ani",
};
static const ClientSkillBinding k_skill_priest_61 = {
    61, k_motions_priest_61, 1, nullptr, 0, 
    "1031 client state table: states 26; basis motion name"};
static const char *const k_motions_priest_63[] = {
    "character/priest/animation/secondupper.ani",
};
static const ClientSkillBinding k_skill_priest_63 = {
    63, k_motions_priest_63, 1, nullptr, 0, 
    "1031 client state table: states 27; basis motion name"};
static const char *const k_motions_priest_73[] = {
    "character/priest/animation/spearofvictoryready.ani",
    "character/priest/animation/spearofvictorythrow.ani",
};
static const ClientSkillBinding k_skill_priest_73 = {
    73, k_motions_priest_73, 2, nullptr, 0, 
    "1031 client state table: states 37; basis motion name"};
static const char *const k_motions_priest_74[] = {
    "character/priest/animation/hammerofcontrition.ani",
};
static const ClientSkillBinding k_skill_priest_74 = {
    74, k_motions_priest_74, 1, nullptr, 0, 
    "1031 client state table: states 38; basis motion name"};
static const char *const k_motions_priest_75[] = {
    "character/priest/animation/heavenlycombination.ani",
    "character/priest/animation/heavenlycombinationex.ani",
};
static const ClientSkillBinding k_skill_priest_75 = {
    75, k_motions_priest_75, 2, nullptr, 0, 
    "1031 client state table: states 39,52; basis motion name"};
static const char *const k_motions_priest_76[] = {
    "character/priest/animation/divinecrush.ani",
};
static const ClientSkillBinding k_skill_priest_76 = {
    76, k_motions_priest_76, 1, nullptr, 0, 
    "1031 client state table: states 40; basis motion name"};
static const char *const k_motions_priest_84[] = {
    "character/priest/animation/apocalypse.ani",
};
static const ClientSkillBinding k_skill_priest_84 = {
    84, k_motions_priest_84, 1, nullptr, 0, 
    "1031 client state table: states 44; basis motion name"};
static const char *const k_motions_priest_88[] = {
    "character/priest/animation/atomicsmash.ani",
};
static const ClientSkillBinding k_skill_priest_88 = {
    88, k_motions_priest_88, 1, nullptr, 0, 
    "1031 client state table: states 46; basis motion name"};
static const char *const k_motions_priest_100[] = {
    "character/priest/animation/cuttingdarknesscharge.ani",
};
static const ClientSkillBinding k_skill_priest_100 = {
    100, k_motions_priest_100, 1, nullptr, 0, 
    "1031 client state table: states 50; basis motion name"};
static const char *const k_motions_priest_104[] = {
    "character/priest/animation/heavenlycombination.ani",
    "character/priest/animation/heavenlycombinationex.ani",
};
static const ClientSkillBinding k_skill_priest_104 = {
    104, k_motions_priest_104, 2, nullptr, 0, 
    "1031 client state table: states 39,52; basis motion name"};
static const char *const k_motions_priest_109[] = {
    "character/priest/animation/deflectwall.ani",
};
static const ClientSkillBinding k_skill_priest_109 = {
    109, k_motions_priest_109, 1, nullptr, 0, 
    "1031 client state table: states 54; basis motion name"};

static const ClientSkillBinding k_job_swordman_skills[] = {
    k_skill_swordman_1,
    k_skill_swordman_2,
    k_skill_swordman_3,
    k_skill_swordman_5,
    k_skill_swordman_6,
    k_skill_swordman_7,
    k_skill_swordman_11,
    k_skill_swordman_14,
    k_skill_swordman_15,
    k_skill_swordman_17,
    k_skill_swordman_20,
    k_skill_swordman_27,
    k_skill_swordman_46,
    k_skill_swordman_51,
    k_skill_swordman_57,
    k_skill_swordman_58,
    k_skill_swordman_60,
    k_skill_swordman_62,
    k_skill_swordman_64,
    k_skill_swordman_65,
    k_skill_swordman_68,
    k_skill_swordman_72,
    k_skill_swordman_73,
    k_skill_swordman_77,
    k_skill_swordman_79,
    k_skill_swordman_81,
    k_skill_swordman_82,
    k_skill_swordman_85,
    k_skill_swordman_86,
    k_skill_swordman_87,
    k_skill_swordman_88,
    k_skill_swordman_102,
    k_skill_swordman_108,
    k_skill_swordman_109,
    k_skill_swordman_111,
    k_skill_swordman_112,
    k_skill_swordman_162,
};
static const ClientJobBindings k_job_swordman = {
    "swordman", k_job_swordman_skills, 37};

static const ClientSkillBinding k_job_demonicswordman_skills[] = {
    k_skill_demonicswordman_1,
    k_skill_demonicswordman_2,
    k_skill_demonicswordman_3,
    k_skill_demonicswordman_6,
    k_skill_demonicswordman_7,
    k_skill_demonicswordman_11,
    k_skill_demonicswordman_14,
    k_skill_demonicswordman_15,
    k_skill_demonicswordman_17,
    k_skill_demonicswordman_20,
    k_skill_demonicswordman_27,
    k_skill_demonicswordman_46,
    k_skill_demonicswordman_51,
    k_skill_demonicswordman_57,
    k_skill_demonicswordman_58,
    k_skill_demonicswordman_60,
    k_skill_demonicswordman_62,
    k_skill_demonicswordman_64,
    k_skill_demonicswordman_65,
    k_skill_demonicswordman_72,
    k_skill_demonicswordman_73,
    k_skill_demonicswordman_77,
    k_skill_demonicswordman_81,
    k_skill_demonicswordman_82,
    k_skill_demonicswordman_85,
    k_skill_demonicswordman_86,
    k_skill_demonicswordman_87,
    k_skill_demonicswordman_88,
    k_skill_demonicswordman_102,
    k_skill_demonicswordman_108,
    k_skill_demonicswordman_109,
    k_skill_demonicswordman_111,
    k_skill_demonicswordman_112,
    k_skill_demonicswordman_117,
    k_skill_demonicswordman_162,
};
static const ClientJobBindings k_job_demonicswordman = {
    "demonicswordman", k_job_demonicswordman_skills, 35};

static const ClientSkillBinding k_job_fighter_skills[] = {
    k_skill_fighter_1,
    k_skill_fighter_2,
    k_skill_fighter_4,
    k_skill_fighter_5,
    k_skill_fighter_6,
    k_skill_fighter_9,
    k_skill_fighter_10,
    k_skill_fighter_13,
    k_skill_fighter_14,
    k_skill_fighter_17,
    k_skill_fighter_18,
    k_skill_fighter_19,
    k_skill_fighter_22,
    k_skill_fighter_41,
    k_skill_fighter_46,
    k_skill_fighter_49,
    k_skill_fighter_54,
    k_skill_fighter_58,
    k_skill_fighter_60,
    k_skill_fighter_62,
    k_skill_fighter_63,
    k_skill_fighter_64,
    k_skill_fighter_67,
    k_skill_fighter_68,
    k_skill_fighter_71,
    k_skill_fighter_74,
    k_skill_fighter_75,
    k_skill_fighter_76,
    k_skill_fighter_77,
    k_skill_fighter_80,
    k_skill_fighter_81,
    k_skill_fighter_82,
    k_skill_fighter_83,
    k_skill_fighter_84,
    k_skill_fighter_86,
    k_skill_fighter_87,
    k_skill_fighter_88,
    k_skill_fighter_89,
    k_skill_fighter_90,
    k_skill_fighter_101,
    k_skill_fighter_102,
    k_skill_fighter_103,
    k_skill_fighter_104,
    k_skill_fighter_105,
    k_skill_fighter_106,
    k_skill_fighter_108,
    k_skill_fighter_111,
    k_skill_fighter_117,
    k_skill_fighter_120,
    k_skill_fighter_122,
    k_skill_fighter_123,
    k_skill_fighter_135,
    k_skill_fighter_139,
};
static const ClientJobBindings k_job_fighter = {
    "fighter", k_job_fighter_skills, 53};

static const ClientSkillBinding k_job_atfighter_skills[] = {
    k_skill_atfighter_1,
    k_skill_atfighter_2,
    k_skill_atfighter_4,
    k_skill_atfighter_5,
    k_skill_atfighter_6,
    k_skill_atfighter_9,
    k_skill_atfighter_10,
    k_skill_atfighter_13,
    k_skill_atfighter_14,
    k_skill_atfighter_17,
    k_skill_atfighter_18,
    k_skill_atfighter_19,
    k_skill_atfighter_22,
    k_skill_atfighter_41,
    k_skill_atfighter_46,
    k_skill_atfighter_49,
    k_skill_atfighter_54,
    k_skill_atfighter_58,
    k_skill_atfighter_60,
    k_skill_atfighter_62,
    k_skill_atfighter_63,
    k_skill_atfighter_64,
    k_skill_atfighter_67,
    k_skill_atfighter_68,
    k_skill_atfighter_71,
    k_skill_atfighter_75,
    k_skill_atfighter_76,
    k_skill_atfighter_77,
    k_skill_atfighter_80,
    k_skill_atfighter_81,
    k_skill_atfighter_82,
    k_skill_atfighter_83,
    k_skill_atfighter_84,
    k_skill_atfighter_86,
    k_skill_atfighter_87,
    k_skill_atfighter_88,
    k_skill_atfighter_89,
    k_skill_atfighter_90,
    k_skill_atfighter_101,
    k_skill_atfighter_102,
    k_skill_atfighter_103,
    k_skill_atfighter_104,
    k_skill_atfighter_105,
    k_skill_atfighter_106,
    k_skill_atfighter_108,
    k_skill_atfighter_111,
    k_skill_atfighter_117,
    k_skill_atfighter_120,
    k_skill_atfighter_122,
    k_skill_atfighter_123,
    k_skill_atfighter_135,
    k_skill_atfighter_139,
};
static const ClientJobBindings k_job_atfighter = {
    "atfighter", k_job_atfighter_skills, 52};

static const ClientSkillBinding k_job_gunner_skills[] = {
    k_skill_gunner_1,
    k_skill_gunner_3,
    k_skill_gunner_4,
    k_skill_gunner_6,
    k_skill_gunner_7,
    k_skill_gunner_9,
    k_skill_gunner_10,
    k_skill_gunner_11,
    k_skill_gunner_15,
    k_skill_gunner_20,
    k_skill_gunner_26,
    k_skill_gunner_43,
    k_skill_gunner_47,
    k_skill_gunner_48,
    k_skill_gunner_50,
    k_skill_gunner_51,
    k_skill_gunner_53,
    k_skill_gunner_59,
    k_skill_gunner_64,
    k_skill_gunner_67,
    k_skill_gunner_70,
    k_skill_gunner_71,
    k_skill_gunner_72,
    k_skill_gunner_73,
    k_skill_gunner_77,
    k_skill_gunner_79,
    k_skill_gunner_80,
    k_skill_gunner_81,
    k_skill_gunner_82,
    k_skill_gunner_83,
    k_skill_gunner_96,
    k_skill_gunner_97,
    k_skill_gunner_98,
    k_skill_gunner_100,
    k_skill_gunner_102,
    k_skill_gunner_104,
    k_skill_gunner_109,
    k_skill_gunner_164,
};
static const ClientJobBindings k_job_gunner = {
    "gunner", k_job_gunner_skills, 38};

static const ClientSkillBinding k_job_atgunner_skills[] = {
    k_skill_atgunner_1,
    k_skill_atgunner_3,
    k_skill_atgunner_4,
    k_skill_atgunner_6,
    k_skill_atgunner_7,
    k_skill_atgunner_9,
    k_skill_atgunner_10,
    k_skill_atgunner_11,
    k_skill_atgunner_15,
    k_skill_atgunner_20,
    k_skill_atgunner_26,
    k_skill_atgunner_43,
    k_skill_atgunner_47,
    k_skill_atgunner_48,
    k_skill_atgunner_50,
    k_skill_atgunner_51,
    k_skill_atgunner_53,
    k_skill_atgunner_59,
    k_skill_atgunner_64,
    k_skill_atgunner_67,
    k_skill_atgunner_70,
    k_skill_atgunner_71,
    k_skill_atgunner_72,
    k_skill_atgunner_73,
    k_skill_atgunner_77,
    k_skill_atgunner_79,
    k_skill_atgunner_80,
    k_skill_atgunner_81,
    k_skill_atgunner_82,
    k_skill_atgunner_83,
    k_skill_atgunner_96,
    k_skill_atgunner_97,
    k_skill_atgunner_98,
    k_skill_atgunner_100,
    k_skill_atgunner_102,
    k_skill_atgunner_104,
    k_skill_atgunner_109,
    k_skill_atgunner_164,
};
static const ClientJobBindings k_job_atgunner = {
    "atgunner", k_job_atgunner_skills, 38};

static const ClientSkillBinding k_job_mage_skills[] = {
    k_skill_mage_4,
    k_skill_mage_10,
    k_skill_mage_12,
    k_skill_mage_13,
    k_skill_mage_14,
    k_skill_mage_20,
    k_skill_mage_65,
    k_skill_mage_66,
    k_skill_mage_68,
    k_skill_mage_69,
    k_skill_mage_83,
    k_skill_mage_86,
    k_skill_mage_92,
    k_skill_mage_98,
    k_skill_mage_103,
    k_skill_mage_104,
    k_skill_mage_105,
    k_skill_mage_106,
    k_skill_mage_111,
    k_skill_mage_112,
    k_skill_mage_114,
};
static const ClientJobBindings k_job_mage = {
    "mage", k_job_mage_skills, 21};

static const ClientSkillBinding k_job_priest_skills[] = {
    k_skill_priest_1,
    k_skill_priest_3,
    k_skill_priest_4,
    k_skill_priest_8,
    k_skill_priest_11,
    k_skill_priest_26,
    k_skill_priest_27,
    k_skill_priest_30,
    k_skill_priest_31,
    k_skill_priest_33,
    k_skill_priest_37,
    k_skill_priest_41,
    k_skill_priest_43,
    k_skill_priest_50,
    k_skill_priest_61,
    k_skill_priest_63,
    k_skill_priest_73,
    k_skill_priest_74,
    k_skill_priest_75,
    k_skill_priest_76,
    k_skill_priest_84,
    k_skill_priest_88,
    k_skill_priest_100,
    k_skill_priest_104,
    k_skill_priest_109,
};
static const ClientJobBindings k_job_priest = {
    "priest", k_job_priest_skills, 25};

inline const ClientJobBindings *const *jobs(size_t &count) {
    static const ClientJobBindings *const k_all[] = {
        &k_job_swordman,
        &k_job_demonicswordman,
        &k_job_fighter,
        &k_job_atfighter,
        &k_job_gunner,
        &k_job_atgunner,
        &k_job_mage,
        &k_job_priest,
    };
    count = 8;
    return k_all;
}

// Lookup by CHR stem and PVF skill id; linear scan is fine at this size.
inline const ClientSkillBinding *find(const char *job, int skillId) {
    size_t n = 0;
    const ClientJobBindings *const *all = jobs(n);
    for (size_t i = 0; i < n; ++i) {
        const ClientJobBindings &j = *all[i];
        bool match = true;
        const char *a = j.job, *b = job;
        for (; *a && *b; ++a, ++b)
            if (*a != *b) { match = false; break; }
        if (match && *a == *b)
            for (size_t k = 0; k < j.count; ++k)
                if (j.skills[k].skillId == skillId) return &j.skills[k];
    }
    return nullptr;
}

} // namespace dnf::client_bindings
