#include "stdafx.h"
#include "SoundDB.h"

SoundDB::SoundDB()
{
	// 사운드 추가 방법
	// 1. Contents/Sound/분류별폴더 에 사운드 파일을 넣음
	// 2. Sound.h에서 enum class SoundName 에 사운드 이름을 추가
	// 3. SoundDB.cpp에서 SOUND->AddSound("폴더/파일이름.확장자", enum SoundName, 반복재생여부) 추가

	// 사운드 재생 방법
	// 0. SOUND->STOP() 은 호출하지 않음
	// 1. SOUND->Play(enum SoundName);

	// BGM
	SOUND->AddSound("BGM/Homebase.ogg", BGM_HOMEBASE, true); // 홈베이스 배경음악

	// TREE
	{
		// 나무를 칠 때 나는 소리
		SOUND->AddSound("Tree/Tree_Hit_01.ogg", TREE_HIT_01, false);
		SOUND->AddSound("Tree/Tree_Hit_02.ogg", TREE_HIT_02, false);
		SOUND->AddSound("Tree/Tree_Hit_03.ogg", TREE_HIT_03, false);
		SOUND->AddSound("Tree/Tree_Hit_04.ogg", TREE_HIT_04, false);
		SOUND->AddSound("Tree/Tree_Hit_05.ogg", TREE_HIT_05, false);
		SOUND->AddSound("Tree/Tree_Hit_06.ogg", TREE_HIT_06, false);
		SOUND->AddSound("Tree/Tree_Hit_07.ogg", TREE_HIT_07, false);

		// 나무가 넘어질 때 나는 소리
		SOUND->AddSound("Tree/Tree_Fall_01.ogg", TREE_FALL_01, false);
		SOUND->AddSound("Tree/Tree_Fall_02.ogg", TREE_FALL_02, false);
		SOUND->AddSound("Tree/Tree_Fall_03.ogg", TREE_FALL_03, false);
		SOUND->AddSound("Tree/Tree_Fall_04.ogg", TREE_FALL_04, false);
		SOUND->AddSound("Tree/Tree_Fall_05.ogg", TREE_FALL_05, false);
	}

	// Rock
	{
		// 바위를 칠 때 나는 소리
		SOUND->AddSound("Rock/Rock_Hit_01.ogg", ROCK_HIT_01, false);
		SOUND->AddSound("Rock/Rock_Hit_02.ogg", ROCK_HIT_02, false);

		// 바위가 부서질 때 나는 소리
		SOUND->AddSound("Rock/Rock_Break_01.ogg", ROCK_BREAK_01, false);
		SOUND->AddSound("Rock/Rock_Break_02.ogg", ROCK_BREAK_02, false);
		SOUND->AddSound("Rock/Rock_Break_03.ogg", ROCK_BREAK_03, false);
		SOUND->AddSound("Rock/Rock_Break_04.ogg", ROCK_BREAK_04, false);
	}

	// Inventory
	{
		// 인벤토리를 열 때
		SOUND->AddSound("Inventory/Inventory_Show_01.ogg", INVENTORY_SHOW_01, false);
		SOUND->AddSound("Inventory/Inventory_Show_02.ogg", INVENTORY_SHOW_02, false);
		SOUND->AddSound("Inventory/Inventory_Show_03.ogg", INVENTORY_SHOW_03, false);

		// 인벤토리를 닫을 때
		SOUND->AddSound("Inventory/Inventory_Hide_01.ogg", INVENTORY_HIDE_01, false);
		SOUND->AddSound("Inventory/Inventory_Hide_02.ogg", INVENTORY_HIDE_02, false);
		SOUND->AddSound("Inventory/Inventory_Hide_03.ogg", INVENTORY_HIDE_03, false);

		// 인벤토리에서 아이템을 집을 때와 버릴 때
		SOUND->AddSound("Inventory/Inventory_Item_Pick.ogg", INVENTORY_ITEM_PICK, false);
		SOUND->AddSound("Inventory/Inventory_Item_Drop.ogg", INVENTORY_ITEM_DROP, false);

		// 인벤토리에서 아이템을 사용할 때
		SOUND->AddSound("Inventory/Inventory_Item_Use_01.ogg", INVENTORY_ITEM_USE_01, false);
		SOUND->AddSound("Inventory/Inventory_Item_Use_02.ogg", INVENTORY_ITEM_USE_02, false);
		SOUND->AddSound("Inventory/Inventory_Item_Use_03.ogg", INVENTORY_ITEM_USE_03, false);
		SOUND->AddSound("Inventory/Inventory_Item_Use_04.ogg", INVENTORY_ITEM_USE_04, false);
	}

	// System
	SOUND->AddSound("System/Crafting.ogg", CRAFTING, false); // Craft




	// ETC

}

SoundDB::~SoundDB()
{
}

void SoundDB::Init()
{
	// 개별 사운드 소리 크기 조절
	SOUND->SetVolume(BGM_HOMEBASE, 0.3f);

	// 전체 소리 크기 조절
	App.soundScale = 0.5f;
	SOUND->SetMasterVolume();
}