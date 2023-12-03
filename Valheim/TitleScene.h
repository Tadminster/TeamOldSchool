#pragma once
class TitleScene : public Scene
{
private:
    // ���
    Actor*          background;

    // Ÿ��Ʋ ī�޶�
    Camera*         titleCamera;
    Ray             cameraRay;
    Vector3         rayHitPos;
    float           weightPosY{ 3.0f };
    Vector3         cameraDir{ 0.5f, 0.0f, 0.5f };

    // �ٴ�, �ٴ�, ����
    Terrain*        floor;
    Terrain*        ocean;
    UI*             underwater;
    bool			isUnderwater{ true };

    // �÷��̾�, ��, ����    
    Actor*          player;
    Actor*          karve;
    Ray             playerRay;
    Vector3         playerRayHitPos;
    Vector3         playerPos{ -0.5f, 0.2f, -1.5f };
    float           karvePosY{ 0.2f };
    
    Actor*          monster01;
    Actor*          monster02;

    // ��ư
    class TitleUI*  titleUI;

private:
    siv::PerlinNoise perlin;

public:
    TitleScene();
    ~TitleScene();
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;
};

