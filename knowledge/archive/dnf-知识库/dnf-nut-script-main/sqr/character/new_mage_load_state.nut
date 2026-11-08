IRDSQRCharacter.pushScriptFiles("character/new_mage/bloodcut/mage_receivedata.nut");
IRDSQRCharacter.pushScriptFiles("character/new_mage/bloodcut/mage_bloodcut_frameflag.nut");
IRDSQRCharacter.pushScriptFiles("character/new_mage/bloodcut/mage_onattack.nut");
IRDSQRCharacter.pushScriptFiles("character/new_mage/bloodcut/mage_ontimeevent.nut");
IRDSQRCharacter.pushScriptFiles("character/new_mage/bloodcut/mage_procappend.nut");
IRDSQRCharacter.pushScriptFiles("character/new_mage/bloodcut/mage_onendcurrentani.nut");

//character/new_mage/superlolly/superlolly.nut
//character/new_mage/hotlove/hotlove.nut
//character/new_mage/madbigdog/madbigdog.nut
//character/new_mage/tailor/tailor.nut
//CURSEOFDOT
//character/new_mage/curseofdot/curseofdot.nut

//IRDSQRCharacter.pushPassiveObj("character/new_mage/painfugraden/po_painfulgarden.nut", 24366);
//IRDSQRCharacter.pushPassiveObj("character/new_mage/hotlove/po_hotlove.nut", 24364);
//IRDSQRCharacter.pushPassiveObj("character/new_mage/bloodcut/po_mage_bloodcut.nut", 24357);
//character/new_mage/darkshadow/po_darkshadow_floor.nut
IRDSQRCharacter.pushPassiveObj("character/new_mage/bobybox/po_dot.nut", 24332);
IRDSQRCharacter.pushPassiveObj("character/new_mage/po_mage_passiveobject.nut", 24346);
IRDSQRCharacter.pushPassiveObj("character/new_mage/doll/po_doll_screen_cover.nut", 24347);
///character/new_mage/doll/po_doll_screen_cover.nut
IRDSQRCharacter.pushPassiveObj("character/new_mage/superlolly/po_superlolly.nut", 24348);

//IRDSQRCharacter.pushState(3, "character/new_mage/attack/attack.nut", "ATTACKMAGE", STATE_ATTACK, -1);

IRDSQRCharacter.pushState(3, "character/new_mage/keepout/keepout.nut", "KEEPOUT", STATE_KEEPOUT, SKILL_KEEPOUT);

IRDSQRCharacter.pushState(3, "character/new_mage/dashattack/dashattack.nut", "MAGEDASHATTACKNEW", 200, -1);

IRDSQRCharacter.pushState(3, "character/new_mage/attack/zattack.nut", "zmageAttack", 23, -1);

IRDSQRCharacter.pushState(3, "character/new_mage/dashattack/dashattack.nut", "MAGEDASHATTACK", STATE_DASH_ATTACK, -1);

IRDSQRCharacter.pushState(3, "character/new_mage/curseofdot/curseofdot.nut", "CURSEOFDOT", STATE_CURSEOFDOT, SKILL_CURSEOFDOT);

IRDSQRCharacter.pushState(3, "character/new_mage/tailor/tailor.nut", "TAILOR", STATE_TAILOR, SKILL_TAILOR);

IRDSQRCharacter.pushState(3, "character/new_mage/dollforest/dollforest.nut", "DOLLFOREST", STATE_DOLLFOREST, SKILL_DOLLFOREST);

IRDSQRCharacter.pushState(3, "character/new_mage/painfugraden/painfugraden.nut", "PAINFUGRADEN", STATE_PAINFUGRADEN, SKILL_PAINFUGRADEN);

IRDSQRCharacter.pushState(3, "character/new_mage/terribledot/terribledot.nut", "TERRIBLEDOT", STATE_TERRIBLEDOT, SKILL_TERRIBLEDOT);

IRDSQRCharacter.pushState(3, "character/new_mage/madbigdog/madbigdog.nut", "MADBIGDOG", STATE_MADBIGDOG, SKILL_MADBIGDOG);

IRDSQRCharacter.pushState(3, "character/new_mage/sprlitmagic/sprlitmagic.nut", "SPRLITMAGIC", STATE_SPRLITMAGIC, SKILL_SPRLITMAGIC);

IRDSQRCharacter.pushState(3, "character/new_mage/fateslave/fateslave.nut", "FATESLAVE", STATE_FATESLAVE, SKILL_FATESLAVE);

IRDSQRCharacter.pushState(3, "character/new_mage/hotlove/hotlove.nut", "HOTLOVE", STATE_HOTLOVE, SKILL_HOTLOVE);

IRDSQRCharacter.pushState(3, "character/new_mage/sorceressbuff/sorceressbuff.nut", "SORCERESSBUFF", STATE_SORCERESSBUFF, SKILL_SORCERESSBUFF);

IRDSQRCharacter.pushState(3, "character/new_mage/blockforestcirrus/blockforestcirrus.nut", "BLOCKFORESTCIRRUS", STATE_BLOCKFORESTCIRRUS, SKILL_BLOCKFORESTCIRRUS);

IRDSQRCharacter.pushState(3, "character/new_mage/doll/doll.nut", "DOLL", STATE_DOLL, SKILL_DOLL);

IRDSQRCharacter.pushState(3, "character/new_mage/rosecirrus/rosecirrus.nut", "ROSECIRRUS", STATE_ROSECIRRUS, SKILL_ROSECIRRUS);

IRDSQRCharacter.pushState(3, "character/new_mage/cirruscut/cirruscut.nut", "CIRRUSCUT", STATE_CIRRUSCUT, SKILL_CIRRUSCUT);

IRDSQRCharacter.pushState(3, "character/new_mage/cirrusarea/cirrusarea.nut", "CIRRUSAREA", STATE_CIRRUSAREA, SKILL_CIRRUSAREA);

IRDSQRCharacter.pushState(3, "character/new_mage/maddotshoot/maddotshoot.nut", "MADDOTSHOOT", STATE_MADDOTSHOOT, SKILL_MADDOTSHOOT);

IRDSQRCharacter.pushState(3, "character/new_mage/maddefance/maddefance.nut", "MADDEFANCE", STATE_MADDEFANCE, SKILL_MADDEFANCE);

IRDSQRCharacter.pushState(3, "character/new_mage/madbigbreak/madbigbreak.nut", "MADBIGBREAK", STATE_MADBIGBREAK, SKILL_MADBIGBREAK);

IRDSQRCharacter.pushState(3, "character/new_mage/jumpdotquake/jumpdotquake.nut", "JUMPDOTQUAKE", STATE_JUMPDOTQUAKE, SKILL_JUMPDOTQUAKE);

IRDSQRCharacter.pushState(3, "character/new_mage/relive/eternalpossession.nut", "ETERNALPOSSESSION", STATE_RELIVE, SKILL_RELIVE);

IRDSQRCharacter.pushState(3, "character/new_mage/favorite/favorite.nut", "FAVORITE", STATE_FAVORITE, SKILL_FAVORITE);