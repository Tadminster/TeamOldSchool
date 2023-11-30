#pragma once

enum SoundName
{
    BGM_HOMEBASE,           // Ȩ���̽� �������

    CRAFTING,               // ����

    INVENTORY_SHOW_01,      // �κ��丮�� �� ��
    INVENTORY_SHOW_02, 
    INVENTORY_SHOW_03,                                    
    INVENTORY_HIDE_01,      // �κ��丮�� ���� ��
    INVENTORY_HIDE_02, 
    INVENTORY_HIDE_03,                                    
    INVENTORY_ITEM_PICK,    // �κ��丮���� �������� ���� ��
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
    ROCK_HIT_01,            // ������ ĥ ��
    ROCK_HIT_02,            
    ROCK_BREAK_01,  	    // ������ �μ��� ��
    ROCK_BREAK_02, 
    ROCK_BREAK_03, 
    ROCK_BREAK_04,                                 


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

    //�׸��� key�� �Ű������� �ΰ� ��� ����
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

