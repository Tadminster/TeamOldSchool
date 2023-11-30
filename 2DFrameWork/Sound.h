#pragma once

enum class SoundName
{

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

