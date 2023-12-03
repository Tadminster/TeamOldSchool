#pragma once

enum SoundName
{
    BGM_OCEANWAVE,          // Ÿ��Ʋ ������� (�ĵ��Ҹ�)
    BGM_HOMEBASE,           // Ȩ���̽� �������

    CRAFTING,               // ����

    UI_SHOW_01,             // UI�� �� ��
    UI_SHOW_02, 
    UI_SHOW_03,                                    
    UI_HIDE_01,             // UI�� ���� ��
    UI_HIDE_02, 
    UI_HIDE_03,                                    
    UI_CLICK,               // UI Ŭ���� ��

    INVENTORY_ITEM_DROP,    // �κ��丮���� �������� ���� ��
    INVENTORY_ITEM_USE_01,  // �κ��丮���� �������� ����� ��
    INVENTORY_ITEM_USE_02, 
    INVENTORY_ITEM_USE_03, 
    INVENTORY_ITEM_USE_04, 

    TREE_HIT_01,            // ������ ĥ ��
    TREE_HIT_02, 
    TREE_HIT_03, 
    TREE_HIT_04, 
    TREE_HIT_05, 
    TREE_HIT_06, 
    TREE_HIT_07,  
    TREE_FALL_01, 		    // ������ �Ѿ��� ��
    TREE_FALL_02, 
    TREE_FALL_03, 
    TREE_FALL_04, 
    TREE_FALL_05,    

    WOOD_BREAK_01,          // ������ �μ��� ��
    WOOD_BREAK_02,
    WOOD_BREAK_03,
    WOOD_BREAK_04,

    ROCK_HIT_01,            // ������ ĥ ��
    ROCK_HIT_02,            
    ROCK_BREAK_01,  	    // ������ �μ��� ��
    ROCK_BREAK_02, 
    ROCK_BREAK_03, 
    ROCK_BREAK_04,           

    UNDERWATER_HURT_01,     // ���ӿ��� ���ظ� ���� ��
    UNDERWATER_HURT_02,
    UNDERWATER_HURT_03,

    UNDERWATER_WAVE_PASS_BY_01,     // ���ӿ��� �ĵ��� ������ ��
    UNDERWATER_WAVE_PASS_BY_02,
    UNDERWATER_WAVE_PASS_BY_03,
    UNDERWATER_WAVE_PASS_BY_04,


    PLAYER_FIST_01,         // �÷��̾� �ָ�
    PLAYER_FIST_02,
    PLAYER_FIST_03,

    PLAYER_WALK_01,         // �÷��̾� �ȱ�
    PLAYER_WALK_WATER_01,

    PLAYER_RUN_01,          // �÷��̾� �ٱ�
    PLAYER_RUN_WATER_01,

    PLAYER_JUMP_01,         //�÷��̾� ����

    PLAYER_AXE_SWING_01,    //�÷��̾� ����
    PLAYER_AXE_SWING_02,
    PLAYER_AXE_SWING_03,
    PLAYER_AXE_HIT_01,    

    PLAYER_CLUB_SWING_01,    //�÷��̾� Ŭ��
    PLAYER_CLUB_SWING_02,
    PLAYER_CLUB_SWING_03,

    PLAYER_BLOCK_01,         //�÷��̾� ���и���
    PLAYER_BLOCK_02,
    PLAYER_BLOCK_03,
};

class Sound : public Singleton<Sound>
{
	struct SoundNode
	{
		FMOD::Sound * sound;        //����� ���� ������
		FMOD::Channel * channel;    //������� ä��
        float volume = 1.0f;
    };

	map<SoundName, SoundNode*> SoundList;
	FMOD::System * system;

public:

    Sound();
    ~Sound();
    //�������� ���� �߰� 
    bool AddSound(string File, SoundName name, bool loop = false);
    //�������� ���� ����
    bool DeleteSound(SoundName name);

    //key�� ���� ����
    void Play(SoundName name);
    void Stop(SoundName name);
    //�Ͻ�����
    void Pause(SoundName name);
    //�Ͻ����� ����
    void Resume(SoundName name);

    void SetVolume(SoundName name, float scale);
    void SetMasterVolume();
    void PauseAll();
    void ResumeAll();
    void Update();
};

