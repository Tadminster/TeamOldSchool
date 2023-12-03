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
	SOUND->AddSound("BGM/Homebase.ogg", BGM_HOMEBASE, true); // Ȩ���̽� �������

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
		// �κ��丮�� �� ��
		SOUND->AddSound("Inventory/Inventory_Show_01.ogg", INVENTORY_SHOW_01, false);
		SOUND->AddSound("Inventory/Inventory_Show_02.ogg", INVENTORY_SHOW_02, false);
		SOUND->AddSound("Inventory/Inventory_Show_03.ogg", INVENTORY_SHOW_03, false);

		// �κ��丮�� ���� ��
		SOUND->AddSound("Inventory/Inventory_Hide_01.ogg", INVENTORY_HIDE_01, false);
		SOUND->AddSound("Inventory/Inventory_Hide_02.ogg", INVENTORY_HIDE_02, false);
		SOUND->AddSound("Inventory/Inventory_Hide_03.ogg", INVENTORY_HIDE_03, false);

		// �κ��丮���� �������� ���� ���� ���� ��
		SOUND->AddSound("Inventory/Inventory_Item_Pick.ogg", INVENTORY_ITEM_PICK, false);
		SOUND->AddSound("Inventory/Inventory_Item_Drop.ogg", INVENTORY_ITEM_DROP, false);

		// �κ��丮���� �������� ����� ��
		SOUND->AddSound("Inventory/Inventory_Item_Use_01.ogg", INVENTORY_ITEM_USE_01, false);
		SOUND->AddSound("Inventory/Inventory_Item_Use_02.ogg", INVENTORY_ITEM_USE_02, false);
		SOUND->AddSound("Inventory/Inventory_Item_Use_03.ogg", INVENTORY_ITEM_USE_03, false);
		SOUND->AddSound("Inventory/Inventory_Item_Use_04.ogg", INVENTORY_ITEM_USE_04, false);
	}

	// Crafting
	SOUND->AddSound("System/Crafting.ogg", CRAFTING, false); // Craft

	// Player-----------------------------------------------------------------------------
	// Fist-------------------------------------------------------------------
	SOUND->AddSound("Unit/Player_Fist_01.ogg", PLAYER_FIST_01, false);
	SOUND->AddSound("Unit/Player_Fist_02.ogg", PLAYER_FIST_02, false);
	SOUND->AddSound("Unit/Player_Fist_03.ogg", PLAYER_FIST_03, false);
	// Walk-------------------------------------------------------------------
	SOUND->AddSound("Unit/Player_Walk_01.ogg", PLAYER_WALK_01, false);
	SOUND->AddSound("Unit/Player_Walk_Water_01.ogg", PLAYER_WALK_WATER_01, false);
	// Run--------------------------------------------------------------------
	SOUND->AddSound("Unit/Player_Run_01.ogg", PLAYER_RUN_01, true);
	SOUND->AddSound("Unit/Player_Run_Water_01.ogg", PLAYER_RUN_WATER_01, true);
	// Axe--------------------------------------------------------------------
	SOUND->AddSound("Unit/Player_Axe_Swing_01.ogg", PLAYER_AXE_SWING_01, false);
	SOUND->AddSound("Unit/Player_Axe_Swing_02.ogg", PLAYER_AXE_SWING_02, false);
	SOUND->AddSound("Unit/Player_Axe_Swing_03.ogg", PLAYER_AXE_SWING_03, false);
	SOUND->AddSound("Unit/Player_Axe_Hit_01.ogg", PLAYER_AXE_HIT_01, false);

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