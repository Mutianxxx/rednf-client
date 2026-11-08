IRDSQRCharacter.pushScriptFiles("Character/ATPriest/ATPriest_Header.nut");

IRDSQRCharacter.pushScriptFiles("Character/ATPriest/ATPriest_Common.nut");

IRDSQRCharacter.pushScriptFiles("Character/ATPriest/Passive_Skill_ATPriest.nut");

IRDSQRCharacter.pushPassiveObj("Character/ATPriest/Po_Diluo_ATPriest.nut", 24240);

IRDSQRCharacter.pushPassiveObj("Character/ATPriest/seducer/ATPriest.nut", 24384);//24347

IRDSQRCharacter.pushPassiveObj("unclebang_shared_passive_object/po_atpriest_shared.nut" ,  24338);//24358


//??ÞÍ
//IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/atpriest_basic.nut", "AtPriest_Basic", 0, -1);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/RisingSlash/RisingSlash.nut", "RisingSlash", STATE_RISING_SLASH, SKILL_RISING_SLASH);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/ViolentAssault/ViolentAssault.nut", "ViolentAssault", STATE_VIOLENT_ASSAULT, SKILL_VIOLENT_ASSAULT);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/PrayerOfHeal/PrayerOfHeal.nut", "PrayerOfHeal", STATE_PRAYER_OF_HEAL, SKILL_PRAYER_OF_HEAL);

//IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/WeaponGuard/WeaponGuard.nut", "WeaponGuard", STATE_WEAPON_GUARD, SKILL_WEAPON_GUARD);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/HolySmash/HolySmash.nut", "HolySmash", STATE_HOLY_SMASH, SKILL_HOLY_SMASH);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/HeavySin/HeavySin.nut", "HeavySin", STATE_HEAVY_SIN, SKILL_HEAVY_SIN);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/NeckUpScythe/NeckUpScythe.nut", "NeckUpScythe", STATE_NECK_UP_SCYTHE, SKILL_NECK_UP_SCYTHE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/TalismanOfLightning/TalismanOfLightning.nut", "TalismanOfLightning", STATE_TALISMAN_OF_LIGHTNING, SKILL_TALISMAN_OF_LIGHTNING);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/CutInDash/CutInDash.nut", "CutInDash", STATE_CUT_IN_DASH, SKILL_CUT_IN_DASH);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/CrossOfPunishment/CrossOfPunishment.nut", "CrossOfPunishment", STATE_CROSS_OF_PUNISHMENT, SKILL_CROSS_OF_PUNISHMENT);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/HolyFlash/HolyFlash.nut", "HolyFlash", STATE_HOLY_FLASH, SKILL_HOLY_FLASH);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/LightOfHaptism/LightOfHaptism.nut", "LightOfHaptism", STATE_LIGHT_OF_HAPTISM, SKILL_LIGHT_OF_HAPTISM);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/NewSpearOfVictory/SpearOfVictory.nut", "SpearOfVictory", STATE_SPEAR_OF_VICTORY, SKILL_SPEAR_OF_VICTORY);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/ShineCross/ShineCross.nut", "ShineCross", STATE_SHINE_CROSS, SKILL_SHINE_CROSS);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/GrandCrossCrash/GrandCrossCrash.nut", "GrandCrossCrash", STATE_GRAND_CROSS_CRASH, SKILL_GRAND_CROSS_CRASH);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/SaintFlash/SaintFlash.nut", "SaintFlash", STATE_SAINT_FLASH, SKILL_SAINT_FLASH);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/HolyCirclet/HolyCirclet.nut", "HolyCirclet", STATE_HOLY_CIRCLET, SKILL_HOLY_CIRCLET);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/ThunderOfCleans/ThunderOfCleans.nut", "ThunderOfCleans", STATE_THUNDER_OF_CLEANS, SKILL_THUNDER_OF_CLEANS);

//IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/AriaOfCourage/AriaOfCourage.nut", "AriaOfCourage", STATE_ARIA_OF_COURAGE, SKILL_ARIA_OF_COURAGE);

//IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/AriaOfRegeneration/AriaOfRegeneration.nut", "AriaOfRegeneration", STATE_ARIA_OF_REGENERATION, SKILL_ARIA_OF_REGENERATION);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST, "Character/atpriest/newAriaOfCourage/AriaOfCourage.nut", "AriaOfCourage", STATE_ARIA_OF_COURAGE, SKILL_ARIA_OF_COURAGE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST, "Character/atpriest/newAriaOfRegeneration/AriaOfRegeneration.nut", "AriaOfRegeneration", STATE_ARIA_OF_REGENERATION, SKILL_ARIA_OF_REGENERATION);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/CruxOfVictoria/CruxOfVictoria.nut", "CruxOfVictoria", STATE_CRUX_OF_VICTORIA, SKILL_CRUX_OF_VICTORIA);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/RepentenceSmash/RepentenceSmash.nut", "RepentenceSmash", STATE_REPENTENCE_SMASH, SKILL_REPENTENCE_SMASH);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/ProtectionOfUriel/ProtectionOfUriel.nut", "ProtectionOfUriel", STATE_PROTECTION_OF_URIEL, SKILL_PROTECTION_OF_URIEL);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/NewBrionac/Brionac.nut", "Brionac", STATE_BRIONAC, SKILL_BRIONAC);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/Cure/Cure.nut", "Cure", STATE_CURE, SKILL_CURE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/BlessOfProtection/BlessOfProtection.nut", "BlessOfProtection", STATE_BLESS_OF_PROTECTION, SKILL_BLESS_OF_PROTECTION);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/BlessOfCourage/BlessOfCourage.nut", "BlessOfCourage", STATE_BLESS_OF_COURAGE, SKILL_BLESS_OF_COURAGE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/Edification/Edification.nut", "Edification", STATE_EDIFICATION, SKILL_EDIFICATION);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/Revive/Revive.nut", "Revive", STATE_REVIVE, SKILL_REVIVE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/BlessOfAngel/BlessOfAngel.nut", "BlessOfAngel", STATE_BLESS_OF_ANGEL, SKILL_BLESS_OF_ANGEL);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/HolyLight/HolyLight.nut", "HolyLight", STATE_HOLY_LIGHT, SKILL_HOLY_LIGHT);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/miraclechine/miraclechine.nut", "Miraclechine", STATE_MIRACLE_CHINE, SKILL_MIRACLE_CHINE);

//ë¯Øªíº
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/Attack/Attack.nut", "Attackseducer", 8, -1);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/Attack/Attack.nut", "dash_attackseducer", 15, -1);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/depravitysevensins/DepravitySevenSins.nut", "DepravitySevenSins", STATE_DEPRAVITYSEVENSINS, SKILL_DEPRAVITYSEVENSINS);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/dualslash/Dualslash.nut", "Dualslash", STATE_DUALSLASH, SKILL_DUALSLASH);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/guillotine/Guillotine.nut", "Guillotine", STATE_GUILLOTINE, SKILL_GUILLOTINE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/rollingrush/Rollingrush.nut", "Rollingrush", STATE_ROLLINGRUSH, SKILL_ROLLINGRUSH);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/Lusthand/Lusthand.nut", "Lusthand", STATE_LUSTHAND, SKILL_LUSTHAND);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/Prideaccel/Prideaccel.nut", "Prideaccel", STATE_PRIDEACCEL, SKILL_PRIDEACCEL);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/Slothbody/Slothbody.nut", "Slothbody", STATE_SLOTHBODY, SKILL_SLOTHBODY);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/Greedthelurker/Greedthelurker.nut", "Greedthelurker", STATE_GREEDTHELURKER, SKILL_GREEDTHELURKER);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/Scythemssacre/Scythemssacre.nut", "Scythemssacre", STATE_SCYTHEMSSACRE, SKILL_SCYTHEMSSACRE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/Scudthewrath/Scudthewrath.nut", "Scudthewrath", STATE_SCUDTHEWRATH, SKILL_SCUDTHEWRATH);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/Thirdrib/Thirdrib.nut", "Thirdrib", STATE_THIRDRIB, SKILL_THIRDRIB);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/Secondsoul/Secondsoul.nut", "Secondsoul", STATE_SECONDSOUL, SKILL_SECONDSOUL);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/FlowerOfPurification/FlowerOfPurification.nut", "FlowerOfPurification", STATE_FLOWEROFPURIFICATION, SKILL_FLOWEROFPURIFICATION);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/LastGenesis/LastGenesis.nut", "LastGenesis", STATE_LASTGENESIS, SKILL_LASTGENESIS);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/EnviousKiss/EnviousKiss.nut", "EnviousKiss", STATE_ENVIOUSKISS, SKILL_ENVIOUSKISS);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/GluttonyVomit/GluttonyVomit.nut", "GluttonyVomit", STATE_GLUTTONYVOMIT, SKILL_GLUTTONYVOMIT);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/TheSevenDeadlySins/TheSevenDeadlySins.nut", "TheSevenDeadlySins", STATE_THESEVENDEADLYSINS, SKILL_THESEVENDEADLYSINS);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/seducer/HandAwakenToSin/HandAwakenToSin.nut", "HandAwakenToSin", STATE_HANDAWAKENTOSIN, SKILL_HANDAWAKENTOSIN);



//ÙãÒ³
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/PrayForOracle/PrayForOracle.nut" ,  "PrayForOracle" ,  STATE_PRAYOFRORACLE ,  SKILL_PRAYOFRORACLE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/RosaryShooting/RosaryShooting.nut" ,  "RosaryShooting" ,  STATE_ROSARYSHOOTING ,  SKILL_ROSARYSHOOTING);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/RosaryStrike/RosaryStrike.nut" ,  "RosaryStrike" ,  STATE_ROSARYSTRIKE ,  SKILL_ROSARYSTRIKE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/ContractSpaceByMagic/ContractSpaceByMagic.nut" ,  "ContractSpaceByMagic" ,  STATE_CONTRACTSPACEBYMAGIC ,  SKILL_CONTRACTSPACEBYMAGIC);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/TalismanOfOppression/TalismanOfOppression.nut" ,  "TalismanOfOppression" ,  STATE_TALISMANOFOPPRESSION ,  SKILL_TALISMANOFOPPRESSION);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/Exorcismus/Exorcismus.nut" ,  "Exorcismus" ,  STATE_EXORCISMUS ,  SKILL_EXORCISMUS);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/EffortSphere/EffortSphere.nut" ,  "EffortSphere" ,  STATE_EFFORTSPHERE ,  SKILL_EFFORTSPHERE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/TalismanOfSoulSteal/TalismanOfSoulSteal.nut" ,  "TalismanOfSoulSteal" ,  STATE_TALISMANOFSOULSTEAL ,  SKILL_TALISMANOFSOULSTEAL);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/DragonWrath/DragonWrath.nut" ,  "DragonWrath" ,  STATE_DRAGONWRATH ,  SKILL_DRAGONWRATH);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/RosaryOf108Beads/RosaryOf108Beads.nut" ,  "RosaryOf108Beads" ,  STATE_ROSARYOF108BEADS ,  SKILL_ROSARYOF108BEADS);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/ImmobilityMagicLine/ImmobilityMagicLine.nut" ,  "ImmobilityMagicLine" ,  STATE_IMMOBILITYMAGICLINE ,  SKILL_IMMOBILITYMAGICLINE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/RitualForDragon/RitualForDragon.nut" ,  "RitualForDragon" ,  STATE_RITUALFORDRAGON ,  SKILL_RITUALFORDRAGON);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/TalismanOfTimeBomb/TalismanOfTimeBomb.nut" ,  "TalismanOfTimeBomb" ,  STATE_TALISMANOFTIMEBOMB ,  SKILL_TALISMANOFTIMEBOMB);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/LifeDepriveDisposition/LifeDepriveDisposition.nut" ,  "LifeDepriveDisposition" ,  STATE_LIFEDEPRIVEDISPOSITION ,  SKILL_LIFEDEPRIVEDISPOSITION);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/RosaryWildShot/RosaryWildShot.nut" ,  "RosaryWildShot" ,  STATE_ROSARYWILDSHOT ,  SKILL_ROSARYWILDSHOT);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/BigRosary/BigRosary.nut" ,  "BigRosary" ,  STATE_BIGROSARY ,  SKILL_BIGROSARY);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST ,  "Character/ATPriest/3_sorceress/WrathOfGodDragon/WrathOfGodDragon.nut" ,  "WrathOfGodDragon" ,  STATE_WRATHOFGODDRAGON ,  SKILL_WRATHOFGODDRAGON);


//?Ó®?÷÷íºinquisitor
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/JumpAttack/JumpAttack.nut", "jump_attack", 7, -1);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "Character/ATPriest/JumpAttack/JumpAttack.nut", "inquisitorjump", 6, -1);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/punishmentblow/punishmentblow.nut", "PunishmentBlow", STATE_PUNISHMENTBLOW, SKILL_PUNISHMENTBLOW);//î®Ì½ñýÌª

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/judgmentblow/judgmentblow.nut", "JudgmentBlow", STATE_JUDGMENTBLOW, SKILL_JUDGMENTBLOW);//ãû÷÷ñ£Ìª

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/holyflame/holyflame.nut", "HolyFlame", STATE_HOLYFLAME, SKILL_HOLYFLAME);//ãêæû

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/summarytiral/summarytiral.nut", "SummaryTiral", STATE_SUMMARYTIRAL, SKILL_SUMMARYTIRAL);//ãêæûóÖ

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/flameofbaptism/flameofbaptism.nut", "FlameOfBaptism", STATE_FLAMEOFBAPTISM, SKILL_FLAMEOFBAPTISM);//ãêæûá©ÖÉ

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/patrolbomb/patrolbomb.nut", "PatrolBomb", STATE_PATROLBOMB, SKILL_PATROLBOMB);//ïäûùûýæû?

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/essenceofphlege/essenceofphlege.nut", "EssenceOfPhlege", STATE_ESSENCEOFPHLEGE, SKILL_ESSENCEOFPHLEGE);//ûýæûïñü¤

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/virtuousfury/virtuousfury.nut", "VirtuousFury", STATE_VIRTUOUSFURY, SKILL_VIRTUOUSFURY);//ãêæûÒÁûý

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/decollation/decollation.nut", "DecollAtion", STATE_DECOLLATION, SKILL_DECOLLATION);//ú¼úý

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/burnatthestake/burnatthestake.nut", "BurnAtThestake", STATE_BURNATTHESTAKE, SKILL_BURNATTHESTAKE);//ûýúý

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/vortexofhellfire/vortexofhellfire.nut", "VortExOfHellFire", STATE_VORTEXOFHELLFIRE, SKILL_VORTEXOFHELLFIRE);//ãêæûàÁè¾

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/wheelofpunishment/wheelofpunishment.nut", "WheelOfPunishment", STATE_WHEELOFPUNISHMENT, SKILL_WHEELOFPUNISHMENT);//ó³×Çúý

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/fanaticism/fanaticism.nut", "Fanaticism", STATE_FANATICISM, SKILL_FANATICISM);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/dismember/dismember.nut", "Dismember", STATE_DISMEMBER, SKILL_DISMEMBER);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/purification/purification.nut", "Purification", STATE_PURIFICATION, SKILL_PURIFICATION);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_AT_PRIEST , "character/atpriest/judge/inferno/inferno.nut", "ATInferno", STATE_INFERNO, SKILL_INFERNO);
