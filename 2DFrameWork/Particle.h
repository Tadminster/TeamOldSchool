#pragma once

class Particle : public Actor
{
protected:

    //현재 재생중인 시간
    float playTime = 0.0f;
    //재생중인가?
    bool isPlaying = false;
public:
    //총 재생시간
    float duration = 10.0f;
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

