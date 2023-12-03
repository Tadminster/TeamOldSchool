#include "stdafx.h"
#include "SoundDB.h"

SoundDB::SoundDB()
{
	// 사운드 추가 방법
	// 1. Contents/Sound/분류별폴더 에 사운드 파일을 넣음
	// 2. Sound.h에서 enum class SoundName 에 사운드 이름을 추가
	// 3. SoundDB.cpp에서 SOUND->AddSound("폴더/파일이름.확장자", enum SoundName, 반복재생여부) 추가
	// 3-1. 사운드 파일 확장자는 ogg로 통일

	// 사운드 재생 방법
	// 0. SOUND->STOP() 은 호출하지 않음
	// 1. SOUND->Play(enum SoundName);

	// BGM
	SOUND->AddSound("BGM/OceanWaves.ogg", BGM_OCEANWAVE, true);		// 타이틀 배경음악
	SOUND->AddSound("BGM/Homebase.ogg",   BGM_HOMEBASE, true);		// 홈베이스 배경음악

	// WOOD
	SOUND->AddSound("Wood/Wood_Break_01.ogg", WOOD_BREAK_01, false); // 나무가 부서질 때
	SOUND->AddSound("Wood/Wood_Break_02.ogg", WOOD_BREAK_02, false);
	SOUND->AddSound("Wood/Wood_Break_03.ogg", WOOD_BREAK_03, false);
	SOUND->AddSound("Wood/Wood_Break_04.ogg", WOOD_BREAK_04, false);

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
		// 인벤토리에서 아이템을 버릴 때
		SOUND->AddSound("Inventory/Inventory_Item_Drop.ogg", INVENTORY_ITEM_DROP, false);

		// 인벤토리에서 아이템을 사용할 때
		SOUND->AddSound("Inventory/Inventory_Item_Use_01.ogg", INVENTORY_ITEM_USE_01, false);
		SOUND->AddSound("Inventory/Inventory_Item_Use_02.ogg", INVENTORY_ITEM_USE_02, false);
		SOUND->AddSound("Inventory/Inventory_Item_Use_03.ogg", INVENTORY_ITEM_USE_03, false);
		SOUND->AddSound("Inventory/Inventory_Item_Use_04.ogg", INVENTORY_ITEM_USE_04, false);
	}

	// UI
	{
		// UI를 열 때
		SOUND->AddSound("UI/UI_Show_01.ogg", UI_SHOW_01, false);
		SOUND->AddSound("UI/UI_Show_02.ogg", UI_SHOW_02, false);
		SOUND->AddSound("UI/UI_Show_03.ogg", UI_SHOW_03, false);

		// UI를 닫을 때
		SOUND->AddSound("UI/UI_Hide_01.ogg", UI_HIDE_01, false);
		SOUND->AddSound("UI/UI_Hide_02.ogg", UI_HIDE_02, false);
		SOUND->AddSound("UI/UI_Hide_03.ogg", UI_HIDE_03, false);

		// UI 클릭할 때
		SOUND->AddSound("UI/UI_Click.ogg", UI_CLICK, false);
	}

	// Crafting
	SOUND->AddSound("System/Crafting.ogg", CRAFTING, false); // Craft

	// Under Water
	{
		// 물속에서 피해를 입을 때
		SOUND->AddSound("UnderWater/UnderWater_Hurt_01.ogg", UNDERWATER_HURT_01, false); 
		SOUND->AddSound("UnderWater/UnderWater_Hurt_02.ogg", UNDERWATER_HURT_02, false);
		SOUND->AddSound("UnderWater/UnderWater_Hurt_03.ogg", UNDERWATER_HURT_03, false);

		// 물속에서 파도가 지나갈 때
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
	// 개별 사운드 소리 크기 조절
	SOUND->SetVolume(BGM_HOMEBASE, 0.3f);

	// 전체 소리 크기 조절
	App.soundScale = 0.5f;
	SOUND->SetMasterVolume();
}