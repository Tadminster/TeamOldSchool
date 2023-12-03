#pragma once

enum SoundName
{
    BGM_HOMEBASE,           // 홈베이스 배경음악

    CRAFTING,               // 제작

    INVENTORY_SHOW_01,      // 인벤토리를 열 때
    INVENTORY_SHOW_02, 
    INVENTORY_SHOW_03,                                    
    INVENTORY_HIDE_01,      // 인벤토리를 닫을 때
    INVENTORY_HIDE_02, 
    INVENTORY_HIDE_03,                                    
    INVENTORY_ITEM_PICK,    // 인벤토리에서 아이템을 집을 때
    INVENTORY_ITEM_DROP,    // 인벤토리에서 아이템을 버릴 때
    INVENTORY_ITEM_USE_01,  // 인벤토리에서 아이템을 사용할 때
    INVENTORY_ITEM_USE_02, 
    INVENTORY_ITEM_USE_03, 
    INVENTORY_ITEM_USE_04, 

    TREE_HIT_01,            // 나무를 칠 때
    TREE_HIT_02, 
    TREE_HIT_03, 
    TREE_HIT_04, 
    TREE_HIT_05, 
    TREE_HIT_06, 
    TREE_HIT_07,  
    TREE_FALL_01, 		    // 나무가 넘어질 때
    TREE_FALL_02, 
    TREE_FALL_03, 
    TREE_FALL_04, 
    TREE_FALL_05,    

    WOOD_BREAK_01,          // 나무가 부서질 때
    WOOD_BREAK_02,
    WOOD_BREAK_03,
    WOOD_BREAK_04,

    ROCK_HIT_01,            // 바위를 칠 때
    ROCK_HIT_02,            
    ROCK_BREAK_01,  	    // 바위가 부서질 때
    ROCK_BREAK_02, 
    ROCK_BREAK_03, 
    ROCK_BREAK_04,                                 

    PLAYER_FIST_01,         // 플레이어 주먹
    PLAYER_FIST_02,
    PLAYER_FIST_03,

    PLAYER_WALK_01,         // 플레이어 걷기
    PLAYER_WALK_WATER_01,

    PLAYER_RUN_01,          // 플레이어 뛰기
    PLAYER_RUN_WATER_01,

    PLAYER_JUMP_01,         //플레이어 점프

    PLAYER_AXE_SWING_01,    //플레이어 도끼
    PLAYER_AXE_SWING_02,
    PLAYER_AXE_SWING_03,
    PLAYER_AXE_HIT_01,    

    PLAYER_CLUB_SWING_01,    //플레이어 클럽
    PLAYER_CLUB_SWING_02,
    PLAYER_CLUB_SWING_03,

    PLAYER_BLOCK_01,         //플레이어 방패막기
    PLAYER_BLOCK_02,
    PLAYER_BLOCK_03,
};

class Sound : public Singleton<Sound>
{
	struct SoundNode
	{
		FMOD::Sound * sound;        //출력할 사운드 데이터
		FMOD::Channel * channel;    //출력해줄 채널
        float volume = 1.0f;
    };

	map<SoundName, SoundNode*> SoundList;
	FMOD::System * system;

public:

    Sound();
    ~Sound();
    //전역에서 사운드 추가 
    bool AddSound(string File, SoundName name, bool loop = false);
    //전역에서 사운드 삭제
    bool DeleteSound(SoundName name);

    //그리고 key를 매개변수로 두고 모두 제어
    void Play(SoundName name);
    void Stop(SoundName name);
    //일시정지
    void Pause(SoundName name);
    //일시정지 해제
    void Resume(SoundName name);

    void SetVolume(SoundName name, float scale);
    void SetMasterVolume();
    void PauseAll();
    void ResumeAll();
    void Update();
};

