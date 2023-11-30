#pragma once

enum class SoundName
{

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

