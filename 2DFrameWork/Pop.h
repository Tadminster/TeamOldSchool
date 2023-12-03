#pragma once

struct POP_DESC
{
    float duration;		//	총 재생시간
    float time;			//  현재 재생중인시간
    float gravity;		//  중력값
    float padding;
    POP_DESC()
    {
        gravity = 60.0f;
    }
};

struct POP_PS_DESC
{
    float alpha = 0.0f;	
    Vector3 padding3;
};

class Pop : public Particle
{
    static ID3D11Buffer*    PopBuffer;
    static ID3D11Buffer*    PopPsBuffer;
public:
    POP_DESC			desc;
    POP_PS_DESC			desc2;
    Vector2             randomSize = Vector2(0, 0); //이미지 크기값
    int                 particleCount = 100;
    float               velocityScalar = 10.0f;
    Vector3             randomPosition = Vector3(0, 0, 0);
    float               waveRange = 2.0f;

    static void         CreateStaticMember();
    static void         DeleteStaticMember();
    static Pop* Create(string name = "Pop");
    virtual void        Render();
    virtual void        Update();
    void                RenderDetail();
    void                Reset();
    virtual void        Play();
    virtual void        Stop();

};

