#pragma once
class TitleScene : public Scene
{
private:
    // 타이틀 카메라
    Camera*         titleCamera;
    Ray             cameraRay;
    Vector3         rayHitPos;
    float           weightPosY{ 3.0f };

    // 바닥, 바다, 물속
    Terrain*        floor;
    Terrain*        ocean;
    UI*             underwater;

    // 플레이어
    Actor*          openingPlayer;
    
    // 버튼
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

