#pragma once
class TitleScene : public Scene
{
private:
    // Ÿ��Ʋ ī�޶�
    Camera*         titleCamera;
    Ray             cameraRay;
    Vector3         rayHitPos;
    float           weightPosY{ 3.0f };

    // �ٴ�, �ٴ�, ����
    Terrain*        floor;
    Terrain*        ocean;
    UI*             underwater;

    // �÷��̾�
    Actor*          openingPlayer;
    
    // ��ư
    UI*             btnStart;
    UI*             btnOption;
    UI*             btnExit;

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

