#pragma once
class InGame : public Scene
{
private:
    Camera*                         tempCamera;
    bool                            isDebugCam{ false };
    bool                            isDebugCamControl{ true };

    Grid*                           grid;
	
    Scattering*                     scattering;
    
    GameManager*                    gameManager;
    
    //Timer*                          worldClock;
    class Elder*                    elder;
    class Goblin*                   goblin;
public:
    InGame();
    ~InGame();
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;
};

