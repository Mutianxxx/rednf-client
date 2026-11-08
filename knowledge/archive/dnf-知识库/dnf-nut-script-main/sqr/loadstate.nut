//dofile("print.f"); //外置打印至根目录print.txt
//tail -f /drives/c/DNF/print.txt
//需要在common setstate里解开相关注释才可以使用
//dofile("_changqing_nut_tools/debug_tool.c"); //长青Debug
//dofile("teststate.f"); //状态打印

sq_RunScript("dnf_enum_header.nut");
sq_RunScript("common.nut");

sq_RunScript("Character/common_load_state.nut");
sq_RunScript("Character/avenger_load_state.nut");
sq_RunScript("Character/atmage_load_state.nut");
//sq_RunScript("Character/CreatorMage_load_state.nut");
sq_RunScript("js60_qq506807329/js60_506807329_common.nut");
sq_RunScript("Character/atgunner_load_state.nut");
sq_RunScript("Character/swordman_load_state.nut");
sq_RunScript("Character/atfighter_load_state.nut");
sq_RunScript("Character/fighter_load_state.nut");
sq_RunScript("Character/priest_load_state.nut");
sq_RunScript("Character/mage_load_state.nut");
sq_RunScript("Character/gunner_load_state.nut");
sq_RunScript("Character/new_atmage_load_state.nut");
sq_RunScript("Character/new_thief_load_state.nut");

//sq_RunScript("Character/demonicswordman_load_state.nut");
sq_RunScript("Character/atswordman_load_state.nut");
sq_RunScript("Character/new_mage_load_state.nut");
//sq_RunScript("Character/atswordman_3rd_load_state.nut");
sq_RunScript("Character/atpriest_load_state.nut");
sq_RunScript("ui/monster_die.nut");
sq_RunScript("apjh/lue.nut");
//sq_RunScript("Character/JG_swordman_load_state.nut");

sq_RunScript("../common/monster/config/monster_flash_screen.dat");
sq_RunScript("../common/monster/config/monster_play_animation.dat");
sq_RunScript("../common/monster/config/monster_play_sound.dat");
sq_RunScript("../common/monster/config/monster_circle_passiveobject.dat");
sq_RunScript("../common/monster/config/monster_string.dat");
sq_RunScript("../common/monster/config/monster_fristread.dat");
sq_RunScript("../common/monster/config/dungeon_frist_read.dat");
sq_RunScript("equipment/equipment_main.nut");

IRDSQRCharacter.pushPassiveObj("monster/po_move/main.nut", 24377);

sq_RunScript("common_class.nut");
sq_RunScript("ui/ui_function.nut");
sq_RunScript("common_function.nut");
sq_RunScript("ui/ui.nut");
sq_RunScript("qq358332886_monster_appendage/monster.nut");
sq_RunScript("Character/gunner/appendage/ap_gunner_huashi.nut");
sq_RunScript("Custom/Content/Trainroom1.nut");
sq_RunScript("Custom/Content/Trainroom2.nut");
sq_RunScript("Custom/Content/Trainroom3.nut");

try{ dofile("momotest.nut") }catch(ex){}
try{ dofile("Script.cfg") }catch(ex){}
try{ dofile("SoundPacks/sounds_mon_act18.npk") }catch(ex){}

