#pragma once
enum class EffectType
{
    //�ʵ��㳪�� ���� ��ƼŬ
    BEECHDROP,
    HITBEECH,
    WOODHITDUST,
    //�ǰ� ���� ��ƼŬ
    HITBLOOD
};

class Particle : public Actor
{
protected:
    //���� ������� �ð�
    float playTime = 0.0f;
    //������ΰ�?
    bool isPlaying = false;
public:
    //�� ����ð�
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
    float           PlayTime() { return playTime / duration; } //����ð� ����
    bool            IsPlaying() { return isPlaying; } //������ΰ�?
};
