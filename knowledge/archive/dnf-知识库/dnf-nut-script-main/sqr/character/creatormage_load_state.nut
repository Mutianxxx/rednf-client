IRDSQRCharacter.pushScriptFiles("Character/CreatorMage/creatormage_header.nut");
//******************************************************************************************
// CreatorMage ����
//******************************************************************************************
IRDSQRCharacter.pushScriptFiles("Character/CreatorMage/CreatorMage_header.nut");	// CreatorMage ��ũ��Ʈ ������ ���� �־��?���?enum�� ����)
IRDSQRCharacter.pushScriptFiles("Character/CreatorMage/mousecontrol_lib.nut"); // 
IRDSQRCharacter.pushScriptFiles("Character/CreatorMage/CreatorMage_common.nut"); //  �̰��� state�� �������°��� �ƴ� ������ ���� �Լ� �Դϴ�

IRDSQRCharacter.pushScriptFiles("Character/CreatorMage/passive_skill_CreatorMage.nut"); // �⺻���� �нú� ��ų�� ó���ϴ� �κ��Դϴ�.


//******************************************************************************************
// ��ų���� NUT���� �ε�
//******************************************************************************************


//******************************************************************************************
// ��ų���� �нú� ������Ʈ NUT���� �ε�
//******************************************************************************************
IRDSQRCharacter.pushPassiveObj("Character/CreatorMage/MicroAttack/po_microAttack.nut", 24353);
IRDSQRCharacter.pushPassiveObj("Character/CreatorMage/WoodFence/po_WoodFence.nut", 24354);
// 24355 `Character/Mage/CreatorWindPress.obj`			// ũ�������� : ����������
//IRDSQRCharacter.pushPassiveObj("Character/CreatorMage/WindPress/po_WindPress.nut", 24355);
// 24356 `Character/Mage/CreatorWindStorm.obj`			// ũ�������� : ���彺��
//IRDSQRCharacter.pushPassiveObj("Character/CreatorMage/WindStorm/po_WindStorm.nut", 24356);


IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_CREATOR_MAGE, "Character/CreatorMage/FireHurricane/FireHurricane.nut", "FireHurricane", STATE_FIREHURRICANE, SKILL_FIREHURRICANE);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_CREATOR_MAGE, "Character/CreatorMage/IceShield/IceShield.nut", "IceShield", STATE_ICESHIELD, SKILL_ICESHIELD);
IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_CREATOR_MAGE, "Character/CreatorMage/WindPress/WindPress.nut", "WindPress", STATE_WINDPRESS, SKILL_WINDPRESS);

IRDSQRCharacter.pushScriptFiles("Character/CreatorMage/Mgrab/Mgrab.nut");
IRDSQRCharacter.pushScriptFiles("Character/CreatorMage/Firewall/Firewall.nut");
IRDSQRCharacter.pushScriptFiles("Character/CreatorMage/WoodFence/WoodFence.nut");
IRDSQRCharacter.pushScriptFiles("Character/CreatorMage/IceRock/IceRock.nut");
IRDSQRCharacter.pushScriptFiles("Character/CreatorMage/FireMeteo/FireMeteo.nut");
IRDSQRCharacter.pushScriptFiles("Character/CreatorMage/IcePlate/IcePlate.nut");
IRDSQRCharacter.pushScriptFiles("Character/CreatorMage/WindStorm/WindStorm.nut");

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_CREATOR_MAGE, "Character/CreatorMage/CreatorFlame/CreatorFlame.nut", "CreatorFlame", STATE_CREATORFLAME, SKILL_CREATORFLAME);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_CREATOR_MAGE, "Character/CreatorMage/CreatorIce/CreatorIce.nut", "CreatorIce", STATE_CREATORICE, SKILL_CREATORICE);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_CREATOR_MAGE, "Character/CreatorMage/CreatorDisturb/CreatorDisturb.nut", "CreatorDisturb", STATE_CREATORDISTURB, SKILL_CREATORDISTURB);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_CREATOR_MAGE, "Character/CreatorMage/CreatorGuardian/CreatorGuardian.nut", "CreatorGuardian", STATE_CREATORGUARDIAN, SKILL_CREATORGUARDIAN);

IRDSQRCharacter.pushState(ENUM_CHARACTERJOB_CREATOR_MAGE, "Character/CreatorMage/CreatorWind/CreatorWind.nut", "CreatorWind", STATE_CREATORWIND, SKILL_CREATORWIND);
