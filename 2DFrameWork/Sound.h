#pragma once

enum SoundName
{
    BGM_OCEANWAVE,          // 타이틀 배경음악 (파도소리)
    BGM_HOMEBASE,           // 홈베이스 배경음악

    CRAFTING,               // 제작

    UI_SHOW_01,             // UI를 열 때
    UI_SHOW_02, 
    UI_SHOW_03,                                    
    UI_HIDE_01,             // UI를 닫을 때
    UI_HIDE_02, 
    UI_HIDE_03,                                    
    UI_CLICK,               // UI 클릭할 때

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

    UNDERWATER_HURT_01,     // 물속에서 피해를 입을 때
    UNDERWATER_HURT_02,
    UNDERWATER_HURT_03,

    UNDERWATER_WAVE_PASS_BY_01,     // 물속에서 파도가 지나갈 때
    UNDERWATER_WAVE_PASS_BY_02,
    UNDERWATER_WAVE_PASS_BY_03,
    UNDERWATER_WAVE_PASS_BY_04,


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

    //key로 사운드 제어
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

