#include "stdafx.h"
#include "SoundDB.h"

SoundDB::SoundDB()
{
	// ���� �߰� ���
	// 1. Contents/Sound/�з������� �� ���� ������ ����
	// 2. Sound.h���� enum class SoundName �� ���� �̸��� �߰�
	// 3. SoundDB.cpp���� SOUND->AddSound("����/�����̸�.Ȯ����", enum SoundName, �ݺ��������) �߰�
	// 3-1. ���� ���� Ȯ���ڴ� ogg�� ����

	// ���� ��� ���
	// 0. SOUND->STOP() �� ȣ������ ����
	// 1. SOUND->Play(enum SoundName);

	// BGM
	SOUND->AddSound("BGM/OceanWaves.ogg", BGM_OCEANWAVE, true);		// Ÿ��Ʋ �������
	SOUND->AddSound("BGM/Homebase.ogg",   BGM_HOMEBASE, true);		// Ȩ���̽� �������

	// WOOD
	SOUND->AddSound("Wood/Wood_Break_01.ogg", WOOD_BREAK_01, false); // ������ �μ��� ��
	SOUND->AddSound("Wood/Wood_Break_02.ogg", WOOD_BREAK_02, false);
	SOUND->AddSound("Wood/Wood_Break_03.ogg", WOOD_BREAK_03, false);
	SOUND->AddSound("Wood/Wood_Break_04.ogg", WOOD_BREAK_04, false);

	// TREE
	{
		// ������ ĥ �� ���� �Ҹ�
		SOUND->AddSound("Tree/Tree_Hit_01.ogg", TREE_HIT_01, false);
		SOUND->AddSound("Tree/Tree_Hit_02.ogg", TREE_HIT_02, false);
		SOUND->AddSound("Tree/Tree_Hit_03.ogg", TREE_HIT_03, false);
		SOUND->AddSound("Tree/Tree_Hit_04.ogg", TREE_HIT_04, false);
		SOUND->AddSound("Tree/Tree_Hit_05.ogg", TREE_HIT_05, false);
		SOUND->AddSound("Tree/Tree_Hit_06.ogg", TREE_HIT_06, false);
		SOUND->AddSound("Tree/Tree_Hit_07.ogg", TREE_HIT_07, false);

		// ������ �Ѿ��� �� ���� �Ҹ�
		SOUND->AddSound("Tree/Tree_Fall_01.ogg", TREE_FALL_01, false);
		SOUND->AddSound("Tree/Tree_Fall_02.ogg", TREE_FALL_02, false);
		SOUND->AddSound("Tree/Tree_Fall_03.ogg", TREE_FALL_03, false);
		SOUND->AddSound("Tree/Tree_Fall_04.ogg", TREE_FALL_04, false);
		SOUND->AddSound("Tree/Tree_Fall_05.ogg", TREE_FALL_05, false);
	}

	// Rock
	{
		// ������ ĥ �� ���� �Ҹ�
		SOUND->AddSound("Rock/Rock_Hit_01.ogg", ROCK_HIT_01, false);
		SOUND->AddSound("Rock/Rock_Hit_02.ogg", ROCK_HIT_02, false);

		// ������ �μ��� �� ���� �Ҹ�
		SOUND->AddSound("Rock/Rock_Break_01.ogg", ROCK_BREAK_01, false);
		SOUND->AddSound("Rock/Rock_Break_02.ogg", ROCK_BREAK_02, false);
		SOUND->AddSound("Rock/Rock_Break_03.ogg", ROCK_BREAK_03, false);
		SOUND->AddSound("Rock/Rock_Break_04.ogg", ROCK_BREAK_04, false);
	}

	// Inventory
	{
		// �κ��丮���� �������� ���� ��
		SOUND->AddSound("Inventory/Inventory_Item_Drop.ogg", INVENTORY_ITEM_DROP, false);

		// �κ��丮���� �������� ����� ��
		SOUND->AddSound("Inventory/Inventory_Item_Use_01.ogg", INVENTORY_ITEM_USE_01, false);
		SOUND->AddSound("Inventory/Inventory_Item_Use_02.ogg", INVENTORY_ITEM_USE_02, false);
		SOUND->AddSound("Inventory/Inventory_Item_Use_03.ogg", INVENTORY_ITEM_USE_03, false);
		SOUND->AddSound("Inventory/Inventory_Item_Use_04.ogg", INVENTORY_ITEM_USE_04, false);
	}

	// UI
	{
		// UI�� �� ��
		SOUND->AddSound("UI/UI_Show_01.ogg", UI_SHOW_01, false);
		SOUND->AddSound("UI/UI_Show_02.ogg", UI_SHOW_02, false);
		SOUND->AddSound("UI/UI_Show_03.ogg", UI_SHOW_03, false);

		// UI�� ���� ��
		SOUND->AddSound("UI/UI_Hide_01.ogg", UI_HIDE_01, false);
		SOUND->AddSound("UI/UI_Hide_02.ogg", UI_HIDE_02, false);
		SOUND->AddSound("UI/UI_Hide_03.ogg", UI_HIDE_03, false);

		// UI Ŭ���� ��
		SOUND->AddSound("UI/UI_Click.ogg", UI_CLICK, false);
	}

	// Crafting
	SOUND->AddSound("System/Crafting.ogg", CRAFTING, false); // Craft

	// Under Water
	{
		// ���ӿ��� ���ظ� ���� ��
		SOUND->AddSound("UnderWater/UnderWater_Hurt_01.ogg", UNDERWATER_HURT_01, false); 
		SOUND->AddSound("UnderWater/UnderWater_Hurt_02.ogg", UNDERWATER_HURT_02, false);
		SOUND->AddSound("UnderWater/UnderWater_Hurt_03.ogg", UNDERWATER_HURT_03, false);

		// ���ӿ��� �ĵ��� ������ ��
		SOUND->AddSound("UnderWater/UnderWater_Wave_Pass_By_01.ogg", UNDERWATER_WAVE_PASS_BY_01, false);
		SOUND->AddSound("UnderWater/UnderWater_Wave_Pass_By_02.ogg", UNDERWATER_WAVE_PASS_BY_02, false);
		SOUND->AddSound("UnderWater/UnderWater_Wave_Pass_By_03.ogg", UNDERWATER_WAVE_PASS_BY_03, false);
		SOUND->AddSound("UnderWater/UnderWater_Wave_Pass_By_04.ogg", UNDERWATER_WAVE_PASS_BY_04, false);
	}

	// Monster
	SOUND->AddSound("Roar/Lizard_Roar_01.ogg", LIZARD_ROAR_01, false);
	SOUND->AddSound("Roar/Lizard_Roar_02.ogg", LIZARD_ROAR_02, false);
	SOUND->AddSound("Roar/Lizard_Roar_03.ogg", LIZARD_ROAR_03, false);

	// Player-----------------------------------------------------------------------------
	// Fist-------------------------------------------------------------------
	SOUND->AddSound("Unit/Player/Player_Fist_01.ogg", PLAYER_FIST_01, false);
	SOUND->AddSound("Unit/Player/Player_Fist_02.ogg", PLAYER_FIST_02, false);
	SOUND->AddSound("Unit/Player/Player_Fist_03.ogg", PLAYER_FIST_03, false);
	// Walk-------------------------------------------------------------------
	SOUND->AddSound("Unit/Player/Player_Walk_01.ogg", PLAYER_WALK_01, false);
	SOUND->AddSound("Unit/Player/Player_Walk_Water_01.ogg", PLAYER_WALK_WATER_01, false);
	// Run--------------------------------------------------------------------
	SOUND->AddSound("Unit/Player/Player_Run_01.ogg", PLAYER_RUN_01, false);
	SOUND->AddSound("Unit/Player/Player_Run_Water_01.ogg", PLAYER_RUN_WATER_01, false);
	// Jump--------------------------------------------------------------------
	SOUND->AddSound("Unit/Player/Player_Jump_01.ogg", PLAYER_JUMP_01, false);
	// Axe--------------------------------------------------------------------
	SOUND->AddSound("Unit/Player/Player_Axe_Swing_01.ogg", PLAYER_AXE_SWING_01, false);
	SOUND->AddSound("Unit/Player/Player_Axe_Swing_02.ogg", PLAYER_AXE_SWING_02, false);
	SOUND->AddSound("Unit/Player/Player_Axe_Swing_03.ogg", PLAYER_AXE_SWING_03, false);
	SOUND->AddSound("Unit/Player/Player_Axe_Hit_01.ogg", PLAYER_AXE_HIT_01, false);
	// Club--------------------------------------------------------------------
	SOUND->AddSound("Unit/Player/Player_Club_Swing_01.ogg", PLAYER_CLUB_SWING_01, false);
	SOUND->AddSound("Unit/Player/Player_Club_Swing_02.ogg", PLAYER_CLUB_SWING_02, false);
	SOUND->AddSound("Unit/Player/Player_Club_Swing_03.ogg", PLAYER_CLUB_SWING_03, false);
	// Shield--------------------------------------------------------------------
	SOUND->AddSound("Unit/Player/Player_Block_01.ogg", PLAYER_BLOCK_01, false);
	SOUND->AddSound("Unit/Player/Player_Block_02.ogg", PLAYER_BLOCK_02, false);
	SOUND->AddSound("Unit/Player/Player_Block_03.ogg", PLAYER_BLOCK_03, false);
	// Level Up--------------------------------------------------------------------
	SOUND->AddSound("Unit/Player/Player_LevelUp_01.ogg", PLAYER_LEVELUP_01, false);
	// Elder-----------------------------------------------------------------------------
	// Elder BGM
	SOUND->AddSound("Unit/Elder/Elder_BGM.ogg", ELDER_BGM_01, true);
	// Elder Stomp
	SOUND->AddSound("Unit/Elder/Elder_Stomp.ogg", ELDER_STOMP, false);
	// Elder JumpAttack
	SOUND->AddSound("Unit/Elder/Elder_JumpAttack.ogg", ELDER_JUMPATTACK, false);
	// Elder Spear
	SOUND->AddSound("Unit/Elder/Elder_Spear.ogg", ELDER_SPEAR, false);

	// ETC

}

SoundDB::~SoundDB()
{
}

void SoundDB::Init()
{
	// ���� ���� �Ҹ� ũ�� ����
	SOUND->SetVolume(BGM_HOMEBASE, 0.3f);

	// ��ü �Ҹ� ũ�� ����
	App.soundScale = 0.5f;
	SOUND->SetMasterVolume();
}