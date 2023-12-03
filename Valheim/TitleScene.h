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

    // �ٴ�, �ٴ�, ����
    Terrain*        floor;
    Terrain*        ocean;
    UI*             underwater;

    // �÷��̾�, ��, ����    
    Actor*          player;
    Actor*          karve;
    Ray             playerRay;
    Vector3         playerRayHitPos;
    Vector3         karvePos{ 0.0f, 0.3f, 0.0f };
    Vector3         playerPos{ -2.0f, 0.3f, -1.5f };
    
    Actor*          jellyFish;

    // ��ư
    class TitleUI*  titleUI;
    // ����â

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

