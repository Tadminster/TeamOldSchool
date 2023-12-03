#pragma once
enum class EffectType
{
    //너도밤나무 관련 파티클
    WOODDROP,
    HITWOOD,
    WOODHITDUST,
    //피격 관련 파티클
    HITBLOOD,
    //바위 관련 파티클
    HITROCK,
    //레벨업 파티클
    LEVELUP,
    LEVELUPONHEAD,
    HEALEFFECT,
    HEALEFFECT2,
    WATERSPLASH,
    WATERWAVE,
    ELDERSTOMP,
    ELDERATTACK
};

class Particle : public Actor
{
protected:
    //현재 재생중인 시간
    float playTime = 0.0f;
    //재생중인가?
    bool isPlaying = false;
public:
    //총 재생시간
    float duration = 1.0f;
    virtual void    Play()
    {
        playTime = 0.0f;
        isPlaying = true;
    };
    virtual void    Stop()
    {
        isPlaying = false;
    };
    void            UpdateParticle();
    void            Gui();
    float           PlayTime() { return playTime / duration; } //재생시간 비율
    bool            IsPlaying() { return isPlaying; } //재생중인가?
};

