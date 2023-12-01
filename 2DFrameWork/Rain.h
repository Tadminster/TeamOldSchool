#pragma once

//상수버퍼
struct RAIN_DESC
{
    Vector3 velocity;
    float padding;

    Vector3 range;
    float time;
    RAIN_DESC()
    {
        velocity = Vector3(0, 10.0f, 0);
        range = Vector3(3, 3, 3);
        time = 0.0f;
    }
};
class Rain : public Particle
{
    static ID3D11Buffer* RainBuffer;
public:
    //virtual ~Rain();

    RAIN_DESC desc;
    Vector2             randomSize = Vector2(0, 0); //이미지 크기값
    int                 particleCount = 10;

    static void         CreateStaticMember();
    static void         DeleteStaticMember();
    static Rain* Create(string name = "Rain");
    virtual void        Render();
    virtual void        Update();
    void                RenderDetail();
    void                Reset();
    virtual void        Play();
    virtual void        Stop();
};

